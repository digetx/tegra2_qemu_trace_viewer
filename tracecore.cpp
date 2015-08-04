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

#include <QDateTime>
#include <QDir>
#include <QScrollBar>

#include "tracecore.h"

#include "cdmatrace.h"
#include "device.h"

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

#include "iomap.h"
#include "ui_mainwindow.h"

#define LOGS_DIR    "/home/dima/vl/logs/"
#define REMOTE_ADDR "192.168.1.145"

TraceCore::TraceCore(QObject *parent) :
    QObject(parent), m_activeDevice(NULL)
{
    connect(&m_ipc, SIGNAL(regWrite(u_int32_t, u_int32_t, u_int32_t, u_int32_t, u_int32_t, bool, u_int32_t, u_int32_t, bool)),
            this, SLOT(regWrite(u_int32_t, u_int32_t, u_int32_t, u_int32_t, u_int32_t, bool, u_int32_t, u_int32_t, bool)));

    connect(&m_ipc, SIGNAL(message(char*)), this, SLOT(message(char*)));

    connect(&m_ipc, SIGNAL(chWrite(u_int32_t, u_int32_t, u_int32_t, u_int32_t)),
            this, SLOT(chWrite(u_int32_t, u_int32_t, u_int32_t, u_int32_t)));
}

void TraceCore::addDeviceToList(TraceDev *dev)
{
    m_devices.append(dev);
    m_mainwindow->addDeviceListItem(dev);

    m_mainwindow->connectDeviceErrorsLog(dev,
        SIGNAL(ErrorUnknownReg(const QString, const Device::log_entry)),
        SIGNAL(ErrorCustom(const QString, const QString, const u_int32_t)));
}

void TraceCore::onConnect(void)
{
    QString ldir = LOGS_DIR + QDateTime::currentDateTime().toString("dd.M_hh:mm:ss") + "/";
    QVarLengthArray<TraceDev*>::const_iterator dev;

    qDebug() << ldir;
    Q_ASSERT( QDir().mkdir(ldir) );

    for (dev = m_devices.constBegin(); dev != m_devices.constEnd(); dev++) {
            (*dev)->ClearLog();
            (*dev)->set_log_dir(ldir);
    }

    m_mainwindow->setRegDesc("");
    m_mainwindow->getUi()->plainTextEditMessages->clear();
}

void TraceCore::onDisconnect(void)
{
}

TraceCore::TraceCore(MainWindow *mainwindow, QObject *parent) :
    TraceCore(parent)
{
    m_mainwindow = mainwindow;

    m_mainwindow->connectDevicesListItemClick(this, SLOT(uiActiveDeviceChanged(QListWidgetItem*)));

    m_mainwindow->connectUnkDeviceErrorsLog(this,
        SIGNAL(ErrorUnknownDev(const u_int32_t, const u_int32_t)));
    m_mainwindow->connectClearErrorsLog(&m_ipc, SIGNAL(connected(void)));

    connect(&m_ipc, SIGNAL(connected(void)), this, SLOT(onConnect(void)));
    connect(&m_ipc, SIGNAL(disconnected(void)), this, SLOT(onDisconnect(void)));

    addDeviceToList( new EmcDev("emc", TEGRA_EMC_BASE) );
    addDeviceToList( new McDev("mc", TEGRA_MC_BASE) );
    addDeviceToList( new GizmoDev("ahb gizmo", TEGRA_AHB_GIZMO_BASE) );
    addDeviceToList( new FuseDev("apb fuse", TEGRA_FUSE_BASE) );
    addDeviceToList( new Apb_dmaDev("apb dma", TEGRA_APB_DMA_BASE) );
    addDeviceToList( new Apb_miscDev("apb misc", TEGRA_APB_MISC_BASE) );
    addDeviceToList( new CarDev("car", TEGRA_CLK_RESET_BASE) );
    addDeviceToList( new FlowDev("flow", TEGRA_FLOW_CTRL_BASE) );
    addDeviceToList( new GpioDev("gpio", TEGRA_GPIO_BASE) );
    addDeviceToList( new PmcDev("pmc", TEGRA_PMC_BASE) );
    addDeviceToList( new RtcDev("rtc", TEGRA_RTC_BASE) );
    addDeviceToList( new TimerDev("timer1", TEGRA_TMR1_BASE) );
    addDeviceToList( new TimerDev("timer2", TEGRA_TMR2_BASE) );
    addDeviceToList( new Timer_usDev("timer us", TEGRA_TMRUS_BASE) );
    addDeviceToList( new TimerDev("timer3", TEGRA_TMR3_BASE) );
    addDeviceToList( new TimerDev("timer4", TEGRA_TMR4_BASE) );
    addDeviceToList( new BseDev("bsea", TEGRA_BSEA_BASE + 0x1000) );
    addDeviceToList( new BseDev("bsev", TEGRA_VDE_BASE + 0x1000) );
//    addDeviceToList( new Host1x_channelDev("host1x ch prot", TEGRA_HOST1X_BASE + 0x20000) );
    addDeviceToList( new Arb_semaDev("arb sema", TEGRA_ARB_SEMA_BASE) );
    addDeviceToList( new Arb_gnt_ictlrDev("arb gnt icrtrl", TEGRA_ARBGNT_ICTLR_BASE) );
    addDeviceToList( new SdhciDev("sdhci4", TEGRA_SDMMC4_BASE) );
    addDeviceToList( new EvpDev("evp", TEGRA_EXCEPTION_VECTORS_BASE) );
    addDeviceToList( new Ictlr_priDev("ictlr_pri", TEGRA_PRIMARY_ICTLR_BASE) );
    addDeviceToList( new Ictlr_secDev("ictlr_sec", TEGRA_SECONDARY_ICTLR_BASE) );
    addDeviceToList( new Ictlr_triDev("ictlr_tri", TEGRA_TERTIARY_ICTLR_BASE) );
    addDeviceToList( new Ictlr_quadDev("ictlr_quad", TEGRA_QUATERNARY_ICTLR_BASE) );

    addDeviceToList( new Host1x_channelDev("host1x ch0", TEGRA_HOST1X_BASE) );
    addDeviceToList( new Host1x_syncDev("host1x sync0", TEGRA_HOST1X_BASE + 0x3000) );
    addDeviceToList( new Host1x_channelDev("host1x ch1", TEGRA_HOST1X_BASE + 0x4000) );
    addDeviceToList( new Host1x_syncDev("host1x sync1", TEGRA_HOST1X_BASE + 0x7000) );
    addDeviceToList( new Host1x_channelDev("host1x ch2", TEGRA_HOST1X_BASE + 0x8000) );
    addDeviceToList( new Host1x_syncDev("host1x sync2", TEGRA_HOST1X_BASE + 0xB000) );
    addDeviceToList( new Host1x_channelDev("host1x ch3", TEGRA_HOST1X_BASE + 0xC000) );
    addDeviceToList( new Host1x_syncDev("host1x sync3", TEGRA_HOST1X_BASE + 0x9000) );
    addDeviceToList( new Host1x_channelDev("host1x ch4", TEGRA_HOST1X_BASE + 0x10000) );
    addDeviceToList( new Host1x_syncDev("host1x sync4", TEGRA_HOST1X_BASE + 0x13000) );
    addDeviceToList( new Host1x_channelDev("host1x ch5", TEGRA_HOST1X_BASE + 0x14000) );
    addDeviceToList( new Host1x_syncDev("host1x sync5", TEGRA_HOST1X_BASE + 0x17000) );
    addDeviceToList( new Host1x_channelDev("host1x ch6", TEGRA_HOST1X_BASE + 0x18000) );
    addDeviceToList( new Host1x_syncDev("host1x sync6", TEGRA_HOST1X_BASE + 0x1B000) );
    addDeviceToList( new Host1x_channelDev("host1x ch7", TEGRA_HOST1X_BASE + 0x1C000) );
    addDeviceToList( new Host1x_syncDev("host1x sync7", TEGRA_HOST1X_BASE + 0x1F000) );
    addDeviceToList( new DcDev("host1x dc1", TEGRA_DISPLAY_BASE) );

    addDeviceToList( new CdmaTrace(0) );
    addDeviceToList( new CdmaTrace(1) );
    addDeviceToList( new CdmaTrace(2) );
    addDeviceToList( new CdmaTrace(3) );
    addDeviceToList( new CdmaTrace(4) );
    addDeviceToList( new CdmaTrace(5) );
    addDeviceToList( new CdmaTrace(6) );
    addDeviceToList( new CdmaTrace(7) );

    addDeviceToList( new Host1xDev("host1x", 0x1) );
    addDeviceToList( new Gr2dDev("host1x gr2d", 0x51) );
    addDeviceToList( new Gr2dDev("host1x gr2d_sb", 0x52) );
    addDeviceToList( new Gr2dDev("host1x gr3d", 0x60) );

#ifdef LOCAL_SOCKET
    m_ipc.connectTo("/tmp/trace.sock");
#else
    m_ipc.connectTo(REMOTE_ADDR);
#endif
}

void TraceCore::uiActiveDeviceChanged(QListWidgetItem *item)
{
    if (m_activeDevice != NULL) {
        disconnect(m_activeDevice, SIGNAL(logItemInserted(bool)),
                   this, SLOT(logItemInserted(bool)));
        m_mainwindow->disconnectDeviceRegFilter(m_activeDevice,
            SLOT(regFilterChanged(const QString)));
    }
    m_dev_sel_index = -1;

    m_activeDevice = static_cast<TraceDev *> (item);

    m_mainwindow->setTableViewTraceModel(m_activeDevice);

    m_mainwindow->setDetailsModel(m_activeDevice->getBitDetailsModel());

    m_mainwindow->getUi()->tableViewBitDetails->setVisible(
                m_activeDevice->hasCap(TraceDev::BITS_DESC) );

    m_mainwindow->getUi()->textRegDesc->setVisible(
                m_activeDevice->hasCap(TraceDev::REG_DESC) );

    scrollTraceView(m_mainwindow->getUi()->tableViewTrace, false, true);

    m_mainwindow->connectTraceSelectionChanged(this,
        SLOT(uiTraceSelectionChanged(const QItemSelection &, const QItemSelection &)));

    m_mainwindow->connectDeviceRegFilter(m_activeDevice,
        SLOT(regFilterChanged(const QString)));

    connect(m_activeDevice, SIGNAL(logItemInserted(bool)), this, SLOT(logItemInserted(bool)));
}

void TraceCore::scrollTraceView(QTableView *tableView,
                                bool is_full, bool force)
{
    QItemSelectionModel *select = tableView->selectionModel();
    QAbstractItemModel *model = tableView->model();
    QScrollBar *sb = tableView->verticalScrollBar();
    int first_visible_row = qMax(0, tableView->rowAt(0) - 1);
    bool in_bottom = (sb->value() == sb->maximum());

    if (is_full) {
        if (select->hasSelection()) {
            int prev_row = qMax(0, select->selectedIndexes().at(0).row() - 1);

            tableView->selectRow(prev_row);
        }

        if (!in_bottom)
            tableView->scrollTo(model->index(first_visible_row, 0),
                                QAbstractItemView::PositionAtTop);
    }

    if (in_bottom || force)
        tableView->scrollToBottom();
}

void TraceCore::logItemInserted(bool is_full)
{
    if (is_full)
        m_dev_sel_index = qMax(m_dev_sel_index - 1, 0);
    scrollTraceView(m_mainwindow->getUi()->tableViewTrace, is_full, false);
}

void TraceCore::uiTraceSelectionChanged(const QItemSelection & selected,
                                        const QItemSelection &)
{
    QModelIndexList indexes = selected.indexes();
    int index;

    if (indexes.count() == 0)
        return;

    index = indexes.at(0).row();

//    qDebug() << "selectedIndex:" << index;

    if (m_dev_sel_index == index)
        return;

    m_mainwindow->setRegDesc( m_activeDevice->updateDetails(index) );
    m_dev_sel_index = index;
}

void TraceCore::message(char *txt)
{
    m_mainwindow->getUi()->plainTextEditMessages->textCursor().movePosition(QTextCursor::End, QTextCursor::MoveAnchor);
    m_mainwindow->getUi()->plainTextEditMessages->textCursor().insertText(QString(txt));
    delete[] txt;
}

void TraceCore::regWrite(u_int32_t hwaddr, u_int32_t offset, u_int32_t value,
                         u_int32_t new_value, u_int32_t time, bool is_write,
                         u_int32_t cpu_pc, u_int32_t cpu_id, bool is_irq)
{
    QVarLengthArray<TraceDev*>::const_iterator tdev;

    for (tdev = m_devices.constBegin(); tdev != m_devices.constEnd(); tdev++) {
        if ((*tdev)->deviceType() != TraceDev::MMIO)
            continue;

        if ((*tdev)->is_valid(hwaddr)) {
            Device *dev = static_cast<Device *> (*tdev);

            dev->write_log(offset, value, new_value, time,
                           is_write, cpu_pc, cpu_id, is_irq);
            return;
        }
    }

    emit ErrorUnknownDev(hwaddr, time);
}

void TraceCore::chWrite(u_int32_t ch_id, u_int32_t time,
                        u_int32_t data, u_int32_t is_gather)
{
    QVarLengthArray<TraceDev*>::const_iterator tdev;

    Q_ASSERT(ch_id < CHANNELS_NB);

    qDebug() << "ch_id: " << ch_id;

    for (tdev = m_devices.constBegin(); tdev != m_devices.constEnd(); tdev++) {
        if ((*tdev)->deviceType() != TraceDev::HOST1X_CDMA)
            continue;

        if ((*tdev)->is_valid(ch_id)) {
            CdmaTrace *dev = static_cast<CdmaTrace *> (*tdev);

            dev->trace(time, data, is_gather);
            return;
        }
    }
}
