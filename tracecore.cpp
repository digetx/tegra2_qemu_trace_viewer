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

#include "tracecore.h"
#include "ui_mainwindow.h"

#define LOGS_DIR    "/home/dima/vl/logs/"
#define REMOTE_ADDR "192.168.1.145"

#define HOST1X_CDMA	0x1010

enum {
    TEGRA2_A9_CORE0,
    TEGRA2_A9_CORE1,
    TEGRA2_COP,
    TEGRA2_A9_NCORES = TEGRA2_COP,
    TEGRA2_NCPUS
};

void TraceCore::onConnect(void)
{
    QString ldir = LOGS_DIR + QDateTime::currentDateTime().toString("dd.M_hh:mm:ss") + "/";
    QDir().mkdir(ldir);

    m_a9.reset(ldir);
    m_avp.reset(ldir);
    m_host1x.reset(ldir);

    m_mainwindow->getUi()->tableWidgetMessages->setRowCount(0);
}

void TraceCore::onDisconnect(void)
{
}

TraceCore::TraceCore(MainWindow *mainwindow, QObject *parent)
    : QObject(parent),
      m_mainwindow(mainwindow),
      m_avp(mainwindow, "AVP", this),
      m_a9(mainwindow, "CPU", this),
      m_host1x(mainwindow, "Host1x", this)
{
    connect(&m_ipc, SIGNAL(connected(void)), this, SLOT(onConnect(void)));

    connect(&m_ipc, SIGNAL(disconnected(void)), this, SLOT(onDisconnect(void)));

    connect(&m_ipc, SIGNAL(regAccess(u_int32_t, u_int32_t, u_int32_t, u_int32_t, u_int32_t, bool, u_int32_t, u_int32_t, bool)),
            this, SLOT(regAccess(u_int32_t, u_int32_t, u_int32_t, u_int32_t, u_int32_t, bool, u_int32_t, u_int32_t, bool)));

    connect(&m_ipc, SIGNAL(message(char*)), this, SLOT(message(char*)));

    connect(&m_ipc, SIGNAL(chWrite(u_int32_t, u_int32_t, u_int32_t, u_int32_t)),
            this, SLOT(chWrite(u_int32_t, u_int32_t, u_int32_t, u_int32_t)));

#ifdef LOCAL_SOCKET
    m_ipc.connectTo("/tmp/trace.sock");
#else
    m_ipc.connectTo(REMOTE_ADDR);
#endif
}

void TraceCore::message(char *txt)
{
    m_mainwindow->getUi()->tableWidgetMessages->insertMessage(txt);
    delete[] txt;
}

void TraceCore::regAccess(u_int32_t hwaddr, u_int32_t offset, u_int32_t value,
                          u_int32_t new_value, u_int32_t time, bool is_write,
                          u_int32_t cpu_pc, u_int32_t cpu_id, bool is_irq)
{
    if (is_irq && offset == 65) {
        if (value & 1) {
            cpu_id = TEGRA2_A9_CORE0;
            value = !!(value & 2);
        } else if (value & 3) {
            cpu_id = TEGRA2_COP;
            value = !!(value & 5);
        } else {
            Q_ASSERT(0);
        }
    }

    switch (cpu_id) {
    case TEGRA2_A9_CORE0:
    case TEGRA2_A9_CORE1:
        m_a9.regAccess(hwaddr, offset, value, new_value, time, is_write,
                       cpu_pc, cpu_id, is_irq);
        if (!is_irq) {
            break;
        }
    case TEGRA2_COP:
        m_avp.regAccess(hwaddr, offset, value, new_value, time, is_write,
                        cpu_pc, cpu_id, is_irq);
        break;
    case HOST1X_CDMA:
        m_host1x.regAccess(hwaddr, offset, value, new_value, time, is_write,
                           cpu_pc, cpu_id, is_irq);
        break;
    default:
        Q_ASSERT(0);
        break;
    }
}

void TraceCore::chWrite(u_int32_t ch_id, u_int32_t time,
                        u_int32_t data, u_int32_t is_gather)
{
    m_host1x.chWrite(ch_id, time, data, is_gather);
}
