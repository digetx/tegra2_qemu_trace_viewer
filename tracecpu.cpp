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

#define RECORD_VER      20151226

enum {
    RECORD_IRQ,
    RECORD_READ32,
    RECORD_WRITE32,
    RECORD_READ32NF,
    RECORD_READ8,
    RECORD_WRITE8,
    RECORD_READ16,
    RECORD_WRITE16,
};

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

void TraceCPU::handle(const TraceIPC::packet_rw &pak_rw)
{
    TraceSRC::handle(pak_rw);

    Device *dev = static_cast<Device *> (getDevByAddr(pak_rw.hwaddr, TraceDev::MMIO));

    if (dev != NULL && dev->rec_enb && m_record_en && openRecordFile()) {
        m_recordstream << quint8(pak_rw.cpu_id == TEGRA2_COP);

        quint32 type;
        quint32 val  = (pak_rw.is_write) ? pak_rw.new_value : pak_rw.value;
        quint32 addr = pak_rw.hwaddr + pak_rw.offset;

        switch (pak_rw.size) {
        case 1:
            type = (pak_rw.is_write) ? RECORD_WRITE8 : RECORD_READ8;
            break;
        case 2:
            type = (pak_rw.is_write) ? RECORD_WRITE16 : RECORD_READ16;
            break;
        case 4:
            type = (pak_rw.is_write) ? RECORD_WRITE32 : RECORD_READ32;
            break;
        default:
            Q_ASSERT(0);
            break;
        }

        if (type == RECORD_READ32 && pak_rw.clk_disabled) {
            type = RECORD_READ32NF;
        }

        m_recordstream << type << addr << val;
    }
}

void TraceCPU::handle(const TraceIPC::packet_irq &pak_irq)
{
    TraceSRC::handle(pak_irq);

    Device *dev = static_cast<Device *> (getDevByAddr(pak_irq.hwaddr, TraceDev::MMIO));

    if (dev != NULL && dev->rec_enb && m_record_en && openRecordFile()) {
        m_recordstream << quint8(pak_irq.cpu_id == TEGRA2_COP);
        m_recordstream << quint32(RECORD_IRQ) << pak_irq.hwirq << pak_irq.status;
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
