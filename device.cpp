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
    case Qt::ForegroundRole:
        if (bits.at(bit_index).value != bits.at(bit_index).new_value)
            return QColor(Qt::black);
        break;
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
            return "Bitfield name";
        case BitDetails::VALUE:
            return has_changed_bits ? "Old Value" : "Value";
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

QString Device::entryAsString(void *e) const
{
    log_entry *entry = (Device::log_entry*) e;
    QTime mstime = QTime(0, 0).addMSecs(entry->time / 1000);
    QString ret;

    ret = mstime.toString("hh:mm:ss.zzz") +
                    QString().sprintf(".%03d\t", entry->time % 1000);
    if (!entry->is_irq) {
        ret += entry->is_write ? "writing" : "reading";
        ret += QString().sprintf(" 0x%08X ", entry->new_value);
        ret += (entry->is_write ? "to " : "from ");
        ret += get_register_name(*entry);
        ret += QString().sprintf("\tcpu[%d] @0x%08X", entry->cpu_id, entry->cpu_pc);
    } else {
        ret += QString().sprintf("irq %u\tstatus: %u",entry->offset, entry->value);
    }

    return ret;
}

Device::Device(QObject *parent) :
    TraceDev(parent), m_log(this, MAX_LOG_ENTRIES), m_base(0)
{
}

void Device::setLogPath(const QString ldir)
{
    m_log.setLogFilePath(ldir + m_name + ".txt");
}

void Device::update_internal(log_entry &)
{
}

void Device::write_log(const u_int32_t &offset, const u_int32_t &value,
                       const u_int32_t &new_value, const u_int32_t &time,
                       const bool &is_write, const u_int32_t &cpu_pc,
                       const u_int32_t &cpu_id, const bool &is_irq,
                       const bool &clk_disabled, const bool &in_reset)
{
    log_entry entry = {
        .offset = offset,
        .value = value,
        .new_value = is_write ? new_value : value,
        .time = time,
        .cpu_pc = cpu_pc,
        .cpu_id = cpu_id,
        .is_write = is_write,
        .is_error = is_irq ? false : !is_offset_valid(offset),
        .undefined_changed = false,
        .is_irq = is_irq,
        .clk_disabled = clk_disabled,
        .in_reset = in_reset,
        .custom = 0,
    };

    update_internal(entry);

    bool log_is_full = m_log.write(entry);
    emit layoutChanged();

    if (log_is_full) {
        emit itemInserted();
    }

    if (entry.is_error) {
        m_dev_errs_nb++;
        m_errs_stat_dirty = true;
        updateName();
        emit ErrorUnknownReg(m_name, entry);
        emit errorStatUpdated(this->id);
    } else {

        if (is_write && is_undef_changed(offset, value, new_value)) {
            QString text = "changing undefined bits ";
                    text += get_register_name(entry) + " ";
                    text += QString().sprintf("0x%08X -> 0x%08X", value, new_value) + " ";
                    text += QString().sprintf("cpu=0x%08X", cpu_pc);
            emit ErrorCustom(m_name, text, time);
        }

        if (clk_disabled || in_reset) {
            m_dev_errs_nb++;
            m_errs_stat_dirty = true;
            updateName();
            emit errorStatUpdated(this->id);
        }
    }

    if (is_irq) {
        m_irq_act = !!entry.value;
        m_dev_irqs_nb++;
        m_irqs_stat_dirty = true;
    } else if (is_write) {
        m_dev_writes_nb++;
        m_writes_stat_dirty = true;
    } else {
        m_dev_reads_nb++;
        m_reads_stat_dirty = true;
    }

    if (!m_stats_changed) {
        m_stats_changed = true;
        emit firstTimeStatUpdated(this->id);
    }

    if (!update_dev_stats_timer.isActive()) {
        update_dev_stats_timer.start(300);
    }

    blink_reset_timer.start(1500);
}

QString Device::updateDetails(const int &index)
{
    log_entry entry = m_log.read(index);

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
    const log_entry entry = m_log.read_last();
    static const QBrush bcolor_irq_on = QBrush ( QColor(255, 192, 255) );
    static const QBrush bcolor_irq_off = QBrush ( QColor(192, 255, 255) );
    static const QBrush bcolor_err = QBrush ( Qt::red );
    static const QBrush bcolor_read = QBrush ( Qt::green );
    static const QBrush bcolor_wr_new_value = QBrush ( QColor(0xf4, 0xa7, 0) );
    static const QBrush bcolor_wr_no_upd = QBrush ( QColor(255, 255, 150) );

    if (m_is_listitem) {
        updateName();

        if (entry.is_irq) {
            if (entry.value) {
                m_background = bcolor_irq_on;
                setBackground( bcolor_irq_on );
                goto LOG_FLUSH;
            } else {
                setBackground( bcolor_irq_off );
            }
        } else if (entry.is_error)
            setBackground( bcolor_err );
        else if (!entry.is_write)
            setBackground( bcolor_read );
        else if (entry.value != entry.new_value)
            setBackground( bcolor_wr_new_value );
        else
            setBackground( bcolor_wr_no_upd );

        m_background = QBrush ( Qt::lightGray );
    } else {
        if (m_irqs_stat_dirty) {
            emit irqStatUpdated(this->id);
            m_irqs_stat_dirty = false;
        }

        if (m_errs_stat_dirty) {
            emit errorStatUpdated(this->id);
            m_errs_stat_dirty = false;
        }

        if (m_reads_stat_dirty) {
            emit readStatUpdated(this->id);
            m_reads_stat_dirty = false;
        }

        if (m_writes_stat_dirty) {
            emit writeStatUpdated(this->id);
            m_writes_stat_dirty = false;
        }
    }

LOG_FLUSH:
    m_log.flush();
}

void Device::blink_reset(void)
{
    setBackground(m_background);
    emit firstTimeStatUpdated(this->id);
}

QVariant Device::data(const QModelIndex &index, int role) const
{
    log_entry entry;
    QTime mstime;
    int div = 1;

    Q_ASSERT(index.row() < m_log.size());

    switch (role) {
    case Qt::EditRole:
        switch ( index.column() ) {
        case Device::REGISTER:
            entry = m_log.read( index.row() );
            return get_register_name(entry) +
                        QString().sprintf(" 0x%08X", entry.offset + (m_base >= 0x50000000 ? m_base : 0));
        default:
            break;
        }
    case Qt::DisplayRole:
        entry = m_log.read( index.row() );

        switch ( index.column() ) {
        case Device::REGISTER:
            if (entry.is_irq)
                return QString("IRQ ") + QString::number(entry.offset);

            if (entry.is_error)
                return QString().sprintf("%s 0x%X",
                                         entry.is_write ? "write to" : "read",
                                         entry.offset);

            if (entry.clk_disabled || entry.in_reset)
                return get_register_name(entry) +
                        "\nclk_enb: " + QString::number(!entry.clk_disabled) +
                        " rst: " + QString::number(entry.in_reset);

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
            return QString().sprintf("[%d] @0x%08X", entry.cpu_id, entry.cpu_pc);
        default:
            break;
        }
        break;
    case Qt::BackgroundRole:
        entry = m_log.read( index.row() );

        if (m_regFilter.length() && get_register_name(entry).indexOf(m_regFilter) == -1)
            div = 2;

        if (index.column() == Device::CPU_PC)
            return QVariant();

        if (entry.is_irq) {
            if (entry.value)
                return QColor(255 / div, 192 / div, 255 / div);
            else
                return QColor(192 / div, 255 / div, 255 / div);
        }

        if (entry.is_error)
            return QColor(255 / div, 150 / div, 150 / div); // light red

        if (index.column() == Device::REGISTER) {
            if (entry.clk_disabled || entry.in_reset)
                return QColor(255 / div, 150 / div, 150 / div); // light red
        }

        if (!entry.is_write)
            return QColor(200 / div, 255 / div, 200 / div); // light green

        if (entry.value != entry.new_value)
            return QColor(0xf4 / div, 0xa7 / div, 0); // brown

        return QColor(255 / div, 255 / div, 150 / div); // light yellow
    case Qt::ToolTipRole:
        switch ( index.column() ) {
        case Device::TIME:
            entry = m_log.read( index.row() );
            return QString::number(entry.time) + "us";
        case Device::REGISTER:
            entry = m_log.read( index.row() );
            return QString().sprintf("0x%08X", entry.offset);
        default:
            break;
        }
        break;
    case Qt::ForegroundRole:
        if (index.column() != Device::CPU_PC)
            return QColor(Qt::black);
        break;
    default:
        break;
    }

    return QVariant();
}

int Device::rowCount(const QModelIndex &) const
{
    return m_log.size();
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
    m_bit_details_model.bits.clear();
    m_bit_details_model.desc.clear();
    m_dev_reads_nb = 0;
    m_dev_writes_nb = 0;
    m_dev_irqs_nb = 0;
    m_dev_errs_nb = 0;
    m_background = QBrush();
    m_stats_changed = false;
    m_irq_act = false;
    m_writes_stat_dirty = false;
    m_reads_stat_dirty = false;
    m_irqs_stat_dirty = false;
    m_errs_stat_dirty = false;

    emit layoutChanged();
    m_bit_details_model.signalUpdate();
    updateName();
    blink_reset();
}

void Device::updateName(void)
{
    if (!m_is_listitem) {
        return;
    }

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
