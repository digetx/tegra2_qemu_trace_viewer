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

#include "devices/emcdev.h"
#include "devices/mcdev.h"
#include "devices/gizmodev.h"
#include "devices/apb_dmadev.h"
#include "devices/apb_miscdev.h"
#include "devices/cardev.h"
#include "devices/flowdev.h"
#include "devices/gpiodev.h"
#include "devices/pmcdev.h"
#include "devices/rtcdev.h"
#include "devices/sdhcidev.h"
#include "devices/timer_usdev.h"
#include "devices/timerdev.h"
#include "devices/uartdev.h"
#include "devices/fusedev.h"
#include "devices/dcdev.h"
#include "devices/bsedev.h"
#include "devices/host1x_channeldev.h"
#include "devices/host1x_syncdev.h"
#include "devices/arb_semadev.h"
#include "devices/arb_gnt_ictlrdev.h"
#include "devices/evpdev.h"
#include "devices/ictlr_pridev.h"
#include "devices/ictlr_secdev.h"
#include "devices/ictlr_tridev.h"
#include "devices/ictlr_quaddev.h"
#include "devices/host1x_dev.h"
#include "devices/gr2ddev.h"
#include "devices/avp_cch.h"
#include "devices/res_semadev.h"
#include "devices/dummydev.h"

#include "iomap.h"
#include "traceavp.h"

#define RECORD_IRQ      0
#define RECORD_READ     1
#define RECORD_WRITE    2

TraceAVP::TraceAVP(MainWindow *window, QString name, QObject *parent) :
    TraceSRC(window, name, parent), m_record_en(false)
{
    addDevice( new EmcDev("emc", TEGRA_EMC_BASE) );
    addDevice( new McDev("mc", TEGRA_MC_BASE) );
    addDevice( new GizmoDev("ahb gizmo", TEGRA_AHB_GIZMO_BASE) );
    addDevice( new FuseDev("apb fuse", TEGRA_FUSE_BASE) );
    addDevice( new Apb_dmaDev("apb dma", TEGRA_APB_DMA_BASE) );
    addDevice( new Apb_miscDev("apb misc", TEGRA_APB_MISC_BASE) );
    addDevice( new CarDev("car", TEGRA_CLK_RESET_BASE) );
    addDevice( new FlowDev("flow", TEGRA_FLOW_CTRL_BASE) );
    addDevice( new GpioDev("gpio", TEGRA_GPIO_BASE) );
    addDevice( new PmcDev("pmc", TEGRA_PMC_BASE) );
    addDevice( new RtcDev("rtc", TEGRA_RTC_BASE) );
    addDevice( new TimerDev("timer1", TEGRA_TMR1_BASE) );
    addDevice( new TimerDev("timer2", TEGRA_TMR2_BASE) );
    addDevice( new Timer_usDev("timer us", TEGRA_TMRUS_BASE) );
    addDevice( new TimerDev("timer3", TEGRA_TMR3_BASE) );
    addDevice( new TimerDev("timer4", TEGRA_TMR4_BASE) );
    addDevice( new DummyDev("ucq", 0x60010000) );
    addDevice( new BseDev("bsea", TEGRA_BSEA_BASE + 0x1000) );
    addDevice( new DummyDev("sxe", 0x6001A000) );
    addDevice( new BseDev("bsev", TEGRA_VDE_BASE + 0x1000) );
    addDevice( new DummyDev("mbe", 0x6001C000) );
    addDevice( new DummyDev("ppe", 0x6001C200) );
    addDevice( new DummyDev("mce", 0x6001C400) );
    addDevice( new DummyDev("tfe", 0x6001C600) );
    addDevice( new DummyDev("ppb", 0x6001C800) );
    addDevice( new DummyDev("vdma", 0x6001CA00) );
    addDevice( new DummyDev("ucq", 0x6001CC00) );
    addDevice( new DummyDev("bsea", 0x6001D000) );
    addDevice( new DummyDev("frameid", 0x6001D800) );
//    addDevice( new Host1x_channelDev("host1x ch prot", TEGRA_HOST1X_BASE + 0x20000) );
    addDevice( new Res_semaDev("res sema", TEGRA_RES_SEMA_BASE) );
    addDevice( new Arb_semaDev("arb sema", TEGRA_ARB_SEMA_BASE) );
    addDevice( new Arb_gnt_ictlrDev("arb gnt icrtrl", TEGRA_ARBGNT_ICTLR_BASE) );
    addDevice( new SdhciDev("sdhci4", TEGRA_SDMMC4_BASE) );
    addDevice( new EvpDev("evp", TEGRA_EXCEPTION_VECTORS_BASE) );
    addDevice( new Ictlr_priDev("ictlr_pri", TEGRA_PRIMARY_ICTLR_BASE) );
    addDevice( new Ictlr_secDev("ictlr_sec", TEGRA_SECONDARY_ICTLR_BASE) );
    addDevice( new Ictlr_triDev("ictlr_tri", TEGRA_TERTIARY_ICTLR_BASE) );
    addDevice( new Ictlr_quadDev("ictlr_quad", TEGRA_QUATERNARY_ICTLR_BASE) );
    addDevice( new AVP_CchDev("AVP MMU", 0xF0000000) );

    addDevice( new Host1x_channelDev("host1x ch0", TEGRA_HOST1X_BASE) );
    addDevice( new Host1x_syncDev("host1x sync0", TEGRA_HOST1X_BASE + 0x3000) );
    addDevice( new Host1x_channelDev("host1x ch1", TEGRA_HOST1X_BASE + 0x4000) );
    addDevice( new Host1x_syncDev("host1x sync1", TEGRA_HOST1X_BASE + 0x7000) );
    addDevice( new Host1x_channelDev("host1x ch2", TEGRA_HOST1X_BASE + 0x8000) );
    addDevice( new Host1x_syncDev("host1x sync2", TEGRA_HOST1X_BASE + 0xB000) );
    addDevice( new Host1x_channelDev("host1x ch3", TEGRA_HOST1X_BASE + 0xC000) );
    addDevice( new Host1x_syncDev("host1x sync3", TEGRA_HOST1X_BASE + 0x9000) );
    addDevice( new Host1x_channelDev("host1x ch4", TEGRA_HOST1X_BASE + 0x10000) );
    addDevice( new Host1x_syncDev("host1x sync4", TEGRA_HOST1X_BASE + 0x13000) );
    addDevice( new Host1x_channelDev("host1x ch5", TEGRA_HOST1X_BASE + 0x14000) );
    addDevice( new Host1x_syncDev("host1x sync5", TEGRA_HOST1X_BASE + 0x17000) );
    addDevice( new Host1x_channelDev("host1x ch6", TEGRA_HOST1X_BASE + 0x18000) );
    addDevice( new Host1x_syncDev("host1x sync6", TEGRA_HOST1X_BASE + 0x1B000) );
    addDevice( new Host1x_channelDev("host1x ch7", TEGRA_HOST1X_BASE + 0x1C000) );
    addDevice( new Host1x_syncDev("host1x sync7", TEGRA_HOST1X_BASE + 0x1F000) );
    addDevice( new DcDev("host1x dc1", TEGRA_DISPLAY_BASE) );

    addDevice( new Host1xDev("host1x", 0x1) );
    addDevice( new Gr2dDev("host1x gr2d", 0x51) );
    addDevice( new Gr2dDev("host1x gr2d_sb", 0x52) );
    addDevice( new Gr2dDev("host1x gr3d", 0x60) );

    m_rec_button = window->getUi()->pushButton_RecodAVP;

    connect(m_rec_button, SIGNAL(clicked(bool)), this, SLOT(recordingToggle()));
}

void TraceAVP::addDevice(TraceDev *dev)
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

    m_recordstream.setDevice(&m_recordfile);
}

void TraceAVP::firstTimeStatUpdated(int id)
{
    emit dataChanged(index(id, 0), index(id, COLUMS_NB - 1));
}

void TraceAVP::irqStatUpdated(int id)
{
    const QModelIndex idx = index(id, IRQ_ACTIONS);
    emit dataChanged(idx, idx);
    flushRecordFile();
}

void TraceAVP::readStatUpdated(int id)
{
    const QModelIndex idx = index(id, READS);
    emit dataChanged(idx, idx);
    flushRecordFile();
}

void TraceAVP::writeStatUpdated(int id)
{
    const QModelIndex idx = index(id, WRITES);
    emit dataChanged(idx, idx);
    flushRecordFile();
}

void TraceAVP::errorStatUpdated(int id)
{
    const QModelIndex idx = index(id, ERRORS);
    emit dataChanged(idx, idx);
}

bool TraceAVP::openRecordFile(void)
{
    QString date;

    if (m_recordfile.isOpen()) {
        return true;
    }

    date = QDateTime::currentDateTime().toString("hh:mm:ss");
    m_recordfile.setFileName(m_log_path + "/"+"AVP_Record_" + date + ".bin");
    m_recordfile.open(QIODevice::WriteOnly);

    return m_recordfile.isOpen();
}

void TraceAVP::flushRecordFile(void)
{
    if (m_recordfile.isOpen()) {
        m_recordfile.flush();
    }
}

void TraceAVP::recordingSet(bool en)
{
    m_record_en = en;

    m_rec_button->setText(m_record_en ? "Stop recording" : "Record AVP IO");
    m_rec_button->setStyleSheet(m_record_en ? "background: red" : "");

    if (!m_record_en) {
        m_recordfile.close();
    }
}

void TraceAVP::recordingToggle(void)
{
    recordingSet(!m_record_en);
}

void TraceAVP::stopRecording(void)
{
    recordingSet(false);
}

void TraceAVP::restartRecording(void)
{
    if (!m_record_en) {
        return;
    }

    recordingSet(false);
    recordingSet(true);
}

void TraceAVP::regAccess(const u_int32_t &hwaddr, const u_int32_t &offset,
                         const u_int32_t &value, const u_int32_t &new_value,
                         const u_int32_t &time, const bool &is_write,
                         const u_int32_t &cpu_pc, const u_int32_t &cpu_id,
                         const bool &is_irq)
{
    TraceSRC::regAccess(hwaddr, offset, value, new_value, time, is_write,
                        cpu_pc, cpu_id, is_irq);

    Device *dev = static_cast<Device *> (getDevByAddr(hwaddr, TraceDev::MMIO));

    if (dev != NULL && dev->rec_enb && m_record_en && openRecordFile()) {
        if (is_irq) {
            quint32 irq_nb = offset;
            quint32 irq_sts = value;

            m_recordstream << quint32(RECORD_IRQ) << irq_nb << irq_sts;
        } else {
            quint32 type  = is_write ? RECORD_WRITE : RECORD_READ;
            quint32 val  = is_write ? new_value : value;
            quint32 addr = hwaddr + offset;

            m_recordstream << type << addr << val;
        }
    }
}

void TraceAVP::reset(QString log_path)
{
    TraceSRC::reset(log_path);
    m_log_path = log_path;

    restartRecording();
}

int TraceAVP::columnCount(const QModelIndex &) const
{
    return COLUMS_NB;
}

QVariant TraceAVP::data(const QModelIndex &index, int role) const
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

bool TraceAVP::setData(const QModelIndex &index, const QVariant &value, int role)
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

Qt::ItemFlags TraceAVP::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = Qt::ItemIsEditable;

    if (index.column() == RECORDING_EN) {
        flags |= Qt::ItemIsUserCheckable;
    }

    return QAbstractItemModel::flags(index) | flags;
}

QVariant TraceAVP::headerData(int section, Qt::Orientation, int role) const
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
