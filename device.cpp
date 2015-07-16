/*
 * Copyright (c) 2014-2015 Dmitry Osipenko <digetx@gmail.com>
 *
 *  This program is free software; you can redistribute it and/or modify it
 *  under the terms of the GNU General Public License as published by the
 *  Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful, but WITHOUT
 *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 *  FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
 *  for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, see <http://www.gnu.org/licenses/>.
 */

#include <QTime>
#include <QtCore/qmath.h>

#include "device.h"
#include "tracecore.h"

BitDetails::BitDetails(QObject *parent) :
    QAbstractTableModel(parent), has_changed_bits(false)
{
}

int BitDetails::rowCount(const QModelIndex &) const
{
    return bits.size();
}

int BitDetails::columnCount(const QModelIndex &) const
{
    return has_changed_bits ? BitDetails::COLUMNS_NB : BitDetails::COLUMNS_NB - 1;
}

QVariant BitDetails::data(const QModelIndex &index, int role) const
{
    int bit_index = index.row();

    switch (role) {
    case Qt::EditRole:
    case Qt::DisplayRole:
        switch (index.column()) {
        case BitDetails::NAME:
            return bits.at(bit_index).name;
//        case BIT_SIZE:
//            return QString::number(bits.at(bit_index).bits);
        case BitDetails::VALUE:
            return QString().sprintf("0x%0*X", qCeil(bits.at(bit_index).bits / 4),
                                     bits.at(bit_index).value);
        case BitDetails::NEW_VALUE:
            return QString().sprintf("0x%0*X", qCeil(bits.at(bit_index).bits / 4),
                                     bits.at(bit_index).new_value);
        default:
            break;
        }
        break;
    case Qt::BackgroundRole:
        if (bits.at(bit_index).value != bits.at(bit_index).new_value)
            return QColor(255, 255, 150); // light yellow
        break;
    case Qt::ToolTipRole:
        switch (index.column()) {
        case BitDetails::NAME:
            return bits.at(bit_index).comment;
        case BitDetails::VALUE: {
            QString bin = QString::number(bits.at(bit_index).value, 2);
            return QString().sprintf("%0*d%s (%d)",
                                     bits.at(bit_index).bits - bin.length(), 0,
                                     bin.toLatin1().data(),
                                     bits.at(bit_index).value);
        }
        case BitDetails::NEW_VALUE: {
            QString bin = QString::number(bits.at(bit_index).new_value, 2);
            return QString().sprintf("%0*d%s (%d)",
                                     bits.at(bit_index).bits - bin.length(), 0,
                                     bin.toLatin1().data(),
                                     bits.at(bit_index).new_value);
        }
        default:
            break;
        }
    default:
        break;
    }

    return QVariant();
}

QVariant BitDetails::headerData(int section, Qt::Orientation, int role) const
{
    switch (role) {
    case Qt::DisplayRole:
        switch (section) {
        case BitDetails::NAME:
            return "Bit name";
        case BitDetails::VALUE:
            return "Bit value";
        case BitDetails::NEW_VALUE:
            return "New value";
        default:
            break;
        }
    default:
        break;
    }

    return QVariant();
}

void BitDetails::signalUpdate(void)
{
    emit layoutChanged();
}

Qt::ItemFlags BitDetails::flags(const QModelIndex &index) const
{
    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

Device::Device(QObject *parent) :
    TraceDev(parent), m_base(0)
{
}

Device::log_entry Device::read_log_entry(int index) const
{
    if (m_log_size < m_max_log_size)
        return m_log.value(index);

    index += m_log_pointer;

    if (index < m_log_size)
        return m_log.value(index);

    return m_log.value(index - m_max_log_size);
}

void Device::set_log_dir(const QString ldir)
{
    m_file = new QFile(ldir + m_name + ".txt", this);

    Q_ASSERT( m_file->open(QIODevice::WriteOnly | QIODevice::Text) );

    m_out = new QTextStream(m_file);
}

void Device::update_internal(log_entry &)
{
}

void Device::write_log(const u_int32_t &offset, const u_int32_t &value,
                       const u_int32_t &new_value, const u_int32_t &time,
                       const bool &is_write, const u_int32_t &cpu_pc,
                       const u_int32_t &cpu_id, const bool &is_irq)
{
    log_entry entry = {
        offset,
        value,
        is_write ? new_value : value,
        time,
        cpu_pc,
        cpu_id,
        is_write,
        is_irq ? false : !is_offset_valid(offset),
        false,
        is_irq,
        0
    };

    update_internal(entry);

    if (m_log_size < m_max_log_size)
        m_log.append(entry);
    else
        m_log.replace(m_log_pointer, entry);

    m_log_pointer_last = m_log_pointer;
    m_log_pointer = (++m_log_pointer == m_max_log_size) ? 0 : m_log_pointer;

    m_log_size = qMin(m_log_size + 1, m_max_log_size);

    emit layoutChanged();
    emit logItemInserted(m_log_size == m_max_log_size);

    if (entry.is_error) {
        m_dev_errs_nb++;
        emit ErrorUnknownReg(text(), entry);
    } else if (is_write && is_undef_changed(offset, value, new_value)) {
        QString name = m_name;
        QString text = "changing undef bit ";
                text += get_register_name(entry) + " ";
                text += QString().sprintf("0x%08X -> 0x%08X", value, new_value) + " ";
                text += QString().sprintf("cpu=0x%08x", cpu_pc);
        emit ErrorCustom(name, text, time);
    }

    if (is_irq)
        m_dev_irqs_nb++;
    else if (is_write)
        m_dev_writes_nb++;
    else
        m_dev_reads_nb++;

    if (!update_dev_stats_timer.isActive())
        update_dev_stats_timer.start(300);
    blink_reset_timer.start(1500);

    // ----------- LOG TO FILE -----------
    if (!entry.is_error && m_out && m_out->status() == QTextStream::Ok) {
        QTime mstime = QTime(0, 0).addMSecs(time / 1000);
        *m_out << mstime.toString("hh:mm:ss.zzz") +
                        QString().sprintf(".%03d", time % 1000) + "\t";
        if (!is_irq) {
            *m_out << (is_write ? QString("writing ") : QString("reading "));
            *m_out << QString().sprintf("0x%08X",
                            is_write? new_value : value);
            *m_out << (is_write ? QString(" to ") : QString(" from "));
            *m_out << get_register_name(entry);
        } else {
            *m_out << QString("irq ") + QString::number(offset);
            *m_out << "\tstatus: " + QString::number(value);
        }
        *m_out << endl;
    }
}

QString Device::updateDetails(const int &index)
{
    log_entry entry = read_log_entry(index);

    m_bit_details_model.bits.clear();
    m_bit_details_model.desc.clear();

    if (!entry.is_irq)
        fill_bits_details(entry.offset, entry.value, entry.new_value);

    m_bit_details_model.signalUpdate();

    return m_bit_details_model.desc;
}

QAbstractTableModel* Device::getBitDetailsModel(void)
{
    return &m_bit_details_model;
}

void Device::update_dev_stats(void)
{
    const log_entry entry = m_log.value(m_log_pointer_last);
    static const QBrush bcolor_irq_on = QBrush ( QColor(255, 192, 255) );
    static const QBrush bcolor_irq_off = QBrush ( QColor(192, 255, 255) );
    static const QBrush bcolor_err = QBrush ( Qt::red );
    static const QBrush bcolor_read = QBrush ( Qt::green );
    static const QBrush bcolor_wr_new_value = QBrush ( QColor(0xf4, 0xa7, 0) );
    static const QBrush bcolor_wr_no_upd = QBrush ( QColor(255, 255, 150) );

    updateName();

    if (entry.is_irq) {
        if (entry.value)
            setBackground( bcolor_irq_on );
        else
            setBackground( bcolor_irq_off );
    } else if (entry.is_error)
        setBackground( bcolor_err );
    else if (!entry.is_write)
        setBackground( bcolor_read );
    else if (entry.value != entry.new_value)
        setBackground( bcolor_wr_new_value );
    else
        setBackground( bcolor_wr_no_upd );
}

void Device::blink_reset(void)
{
    setBackground( QBrush() );
}

QVariant Device::data(const QModelIndex &index, int role) const
{
    log_entry entry;
    QTime mstime;
    int div = 1;

    Q_ASSERT(index.row() < m_log_size);

    switch (role) {
    case Qt::EditRole:
        switch ( index.column() ) {
        case Device::REGISTER:
            entry = read_log_entry( index.row() );
            return get_register_name(entry) +
                        QString().sprintf(" 0x%08X", entry.offset + (m_base >= 0x50000000 ? m_base : 0));
        default:
            break;
        }
    case Qt::DisplayRole:
        entry = read_log_entry( index.row() );

        switch ( index.column() ) {
        case Device::REGISTER:
            if (entry.is_irq)
                return QString("IRQ ") + QString::number(entry.offset);

            if (entry.is_error)
                return QString().sprintf("%s 0x%X",
                                         entry.is_write ? "write to" : "read",
                                         entry.offset);

            return get_register_name(entry);
        case Device::VALUE:
            if (entry.is_irq)
                return QString("STATUS ") + QString::number(entry.value);

            return QString().sprintf("0x%08X",
                            entry.is_write? entry.new_value : entry.value);
        case Device::TIME:
            mstime = QTime(0, 0).addMSecs(entry.time / 1000);
            return mstime.toString("hh:mm:ss.zzz") +
                            QString().sprintf(".%03d", entry.time % 1000);
        case Device::CPU_PC:
            return QString().sprintf("[%d] @0x%08x", entry.cpu_id, entry.cpu_pc);
        default:
            break;
        }
        break;
    case Qt::BackgroundRole:
        entry = read_log_entry( index.row() );

        if (m_regFilter.length() && get_register_name(entry).indexOf(m_regFilter) == -1)
            div = 2;

        if (index.column() == Device::CPU_PC)
            return QColor(255 / div, 255 / div, 255 / div);

        if (entry.is_irq) {
            if (entry.value)
                return QColor(255 / div, 192 / div, 255 / div);
            else
                return QColor(192 / div, 255 / div, 255 / div);
        }

        if (entry.is_error)
            return QColor(255 / div, 150 / div, 150 / div); // light red

        if (!entry.is_write)
            return QColor(200 / div, 255 / div, 200 / div); // light green

        if (entry.value != entry.new_value)
            return QColor(0xf4 / div, 0xa7 / div, 0); // brown

        return QColor(255 / div, 255 / div, 150 / div); // light yellow
    case Qt::ToolTipRole:
        switch ( index.column() ) {
        case Device::TIME:
            entry = read_log_entry( index.row() );
            return QString::number(entry.time) + "us";
        case Device::REGISTER:
            entry = read_log_entry( index.row() );
            return QString().sprintf("0x%08X", entry.offset);
        default:
            break;
        }
        break;
    default:
        break;
    }

    return QVariant();
}

int Device::rowCount(const QModelIndex &) const
{
    return m_log_size;
}

int Device::columnCount(const QModelIndex &) const
{
    return Device::COLUMNS_NB;
}

QVariant Device::headerData(int section, Qt::Orientation, int role) const
{
    switch (role) {
    case Qt::DisplayRole:
        switch (section) {
        case Device::REGISTER:
            return "Register";
        case Device::VALUE:
            return "Value";
        case Device::TIME:
            return "Time";
        case Device::CPU_PC:
            return "CPU";
        default:
            break;
        }
    default:
        break;
    }

    return QVariant();
}

void Device::ClearLog(void)
{
    m_log.clear();
    m_log_size = 0;
    m_bit_details_model.bits.clear();
    m_bit_details_model.desc.clear();
    m_dev_reads_nb = 0;
    m_dev_writes_nb = 0;
    m_dev_irqs_nb = 0;
    m_dev_errs_nb = 0;

    emit layoutChanged();
    m_bit_details_model.signalUpdate();
    updateName();

    delete m_out;
    if (m_file)
        m_file->close();
    delete m_file;
}

void Device::updateName(void)
{
    /* FIXME: sprintf() is a CPU consumption hog */
    setText(m_name +
            QString().sprintf(" (r %lu, w %lu, i %lu, e %lu)",
                              m_dev_reads_nb, m_dev_writes_nb,
                              m_dev_irqs_nb, m_dev_errs_nb));
}

Qt::ItemFlags Device::flags(const QModelIndex &index) const
{
    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

void Device::regFilterChanged(const QString &text)
{
    m_regFilter = text;
    emit layoutChanged();
}

int Device::deviceType() const
{
    return TraceDev::MMIO;
}

bool Device::hasCap(TraceDev::dev_caps cap) const
{
    switch (cap) {
    case TraceDev::REG_DESC:
    case TraceDev::BITS_DESC:
        return true;
    default:
        break;
    }

    return false;
}
