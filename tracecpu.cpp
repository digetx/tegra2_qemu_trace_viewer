/*
 * Copyright (c) 2015 Dmitry Osipenko <digetx@gmail.com>
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

#include <QCheckBox>
#include <QDate>
#include "ui_mainwindow.h"

#include "iomap.h"
#include "tracecore.h"
#include "tracecpu.h"

#define RECORD_VER      16122015
#define RECORD_IRQ      0
#define RECORD_READ     1
#define RECORD_WRITE    2
#define RECORD_READNF   3

TraceCPU::TraceCPU(MainWindow *window, QString name, QFile *recfile,
                   QObject *parent) :
    TraceSRC(window, name, parent), m_recordfile(recfile), m_record_en(false)
{
    connect(m_tui->m_rec_button, SIGNAL(clicked(bool)),
            this, SLOT(recordingToggle()));

    m_recordstream.setDevice(m_recordfile);
}

void TraceCPU::addDevice(TraceDev *dev)
{
    Device *dev_ = static_cast<Device *> (dev);

    TraceSRC::addDevice(dev);

    connect(dev_, SIGNAL(firstTimeStatUpdated(int)),
            this, SLOT(firstTimeStatUpdated(int)));

    connect(dev_, SIGNAL(irqStatUpdated(int)),
            this, SLOT(irqStatUpdated(int)));

    connect(dev_, SIGNAL(readStatUpdated(int)),
            this, SLOT(readStatUpdated(int)));

    connect(dev_, SIGNAL(writeStatUpdated(int)),
            this, SLOT(writeStatUpdated(int)));

    connect(dev_, SIGNAL(errorStatUpdated(int)),
            this, SLOT(errorStatUpdated(int)));
}

void TraceCPU::firstTimeStatUpdated(int id)
{
    emit dataChanged(index(id, 0), index(id, COLUMS_NB - 1));
}

void TraceCPU::irqStatUpdated(int id)
{
    const QModelIndex idx = index(id, IRQ_ACTIONS);
    emit dataChanged(idx, idx);
    flushRecordFile();
}

void TraceCPU::readStatUpdated(int id)
{
    const QModelIndex idx = index(id, READS);
    emit dataChanged(idx, idx);
    flushRecordFile();
}

void TraceCPU::writeStatUpdated(int id)
{
    const QModelIndex idx = index(id, WRITES);
    emit dataChanged(idx, idx);
    flushRecordFile();
}

void TraceCPU::errorStatUpdated(int id)
{
    const QModelIndex idx = index(id, ERRORS);
    emit dataChanged(idx, idx);
}

bool TraceCPU::openRecordFile(void)
{
    QString date;

    if (m_recordfile->isOpen()) {
        return true;
    }

    date = QDateTime::currentDateTime().toString("hh:mm:ss");
    m_recordfile->setFileName(m_log_path + "/" + "Record_" + date + ".bin");
    m_recordfile->open(QIODevice::WriteOnly);

    if (m_recordfile->isOpen()) {
        m_recordstream << quint32(RECORD_VER);
    }

    return m_recordfile->isOpen();
}

void TraceCPU::flushRecordFile(void)
{
    if (m_recordfile->isOpen()) {
        m_recordfile->flush();
    }
}

void TraceCPU::recordingSet(bool en)
{
    m_record_en = en;

    m_tui->m_rec_button->setText(m_record_en ? "Stop recording" : "Record IO");
    m_tui->m_rec_button->setStyleSheet(m_record_en ? "background: red" : "");

    if (!m_record_en) {
        m_recordfile->close();
    }
}

void TraceCPU::recordingToggle(void)
{
    recordingSet(!m_record_en);
}

void TraceCPU::stopRecording(void)
{
    recordingSet(false);
}

void TraceCPU::restartRecording(void)
{
    if (!m_record_en) {
        return;
    }

    recordingSet(false);
    recordingSet(true);
}

void TraceCPU::regAccess(const u_int32_t &hwaddr, const u_int32_t &offset,
                         const u_int32_t &value, const u_int32_t &new_value,
                         const u_int32_t &time, const u_int32_t &is_write,
                         const u_int32_t &cpu_pc, const u_int32_t &cpu_id,
                         const bool &is_irq)
{
    TraceSRC::regAccess(hwaddr, offset, value, new_value, time, is_write,
                        cpu_pc, cpu_id, is_irq);

    Device *dev = static_cast<Device *> (getDevByAddr(hwaddr, TraceDev::MMIO));

    if (dev != NULL && dev->rec_enb && m_record_en && openRecordFile()) {
        m_recordstream << quint8(cpu_id == TEGRA2_COP);

        if (is_irq) {
            quint32 irq_nb = offset;
            quint32 irq_sts = value;

            m_recordstream << quint32(RECORD_IRQ) << irq_nb << irq_sts;
        } else {
            quint32 type = (is_write & 1) ? RECORD_WRITE : RECORD_READ;
            quint32 val  = (is_write & 1) ? new_value : value;
            quint32 addr = hwaddr + offset;
            bool clk_disabled = !!(is_write & 2);

            if (type == RECORD_READ && clk_disabled) {
                type = RECORD_READNF;
            }

            m_recordstream << type << addr << val;
        }
    }
}

void TraceCPU::reset(QString log_path)
{
    TraceSRC::reset(log_path);
    m_log_path = log_path;

    restartRecording();
}

int TraceCPU::columnCount(const QModelIndex &) const
{
    return COLUMS_NB;
}

QVariant TraceCPU::data(const QModelIndex &index, int role) const
{
    Device *dev = static_cast<Device *> ( getDevAt(index.row()) );

    switch (role) {
    case Qt::EditRole:
    case Qt::DisplayRole:
        switch ( index.column() ) {
        case BASE:
            return QString().sprintf("0x%08X", dev->base());
        case NAME:
            return dev->name();
        case READS:
            return dev->reads();
        case WRITES:
            return dev->writes();
        case IRQ_ACTIONS:
            return dev->irqs();
        case ERRORS:
            return dev->errors();
        case RECORDING_EN:
            return "enabled";
        default:
            break;
        }
        break;
    case Qt::BackgroundRole:
        if ( index.column() == IRQ_ACTIONS && dev->irq_active() ) {
            return QColor(255, 192, 255);
        }
        if ( index.column() == ERRORS && dev->errors() ) {
            return QColor(255, 150, 150); // light red
        }
        if (!dev->nostats()) {
            return QColor(220, 220, 220); // light gray
        }
        break;
    case Qt::ForegroundRole:
        if (!dev->nostats()) {
            return QColor(Qt::black);
        }
        break;
    case Qt::CheckStateRole:
        switch ( index.column() ) {
        case RECORDING_EN:
            return dev->rec_enb ? Qt::Checked : Qt::Unchecked;
        default:
            break;
        }
        break;
    default:
        break;
    }

    return QVariant();
}

bool TraceCPU::setData(const QModelIndex &index, const QVariant &value, int role)
{
    Device *dev = static_cast<Device *> ( getDevAt(index.row()) );

    switch (role) {
    case Qt::CheckStateRole:
        switch ( index.column() ) {
        case RECORDING_EN:
            dev->rec_enb = value.toBool();
            emit dataChanged(index, index);
            return true;
        default:
            break;
        }
        break;
    default:
        break;
    }

    return false;
}

Qt::ItemFlags TraceCPU::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = Qt::ItemIsEditable;

    if (index.column() == RECORDING_EN) {
        flags |= Qt::ItemIsUserCheckable;
    }

    return QAbstractItemModel::flags(index) | flags;
}

QVariant TraceCPU::headerData(int section, Qt::Orientation, int role) const
{
    switch (role) {
    case Qt::DisplayRole:
        switch (section) {
        case BASE:
            return "Base";
        case NAME:
            return "Name";
        case READS:
            return "Reads";
        case WRITES:
            return "Writes";
        case IRQ_ACTIONS:
            return "IRQ's";
        case ERRORS:
            return "Errors";
        case RECORDING_EN:
            return "Recording";
        default:
            break;
        }
    default:
        break;
    }

    return QVariant();
}
