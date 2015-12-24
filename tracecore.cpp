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
#include "tracesettings.h"
#include "ui_mainwindow.h"

#define HOST1X_CDMA	0x1010

#define CMD_CHANGE_TIMERS_SPEED     0x122

static void changeSpeedButtonText(bool slowdown, QPushButton *button)
{
    button->setText(slowdown ? "Normal speed" : "Slow down time");
    button->setStyleSheet(slowdown ? "background: blue" : "");
}

void TraceCore::onConnect(void)
{
    QString ldir = TraceSettings::instance()->logsDirPath() + "/" +
                QDateTime::currentDateTime().toString("dd.M_hh:mm:ss") + "/";
    QDir().mkdir(ldir);

    m_a9.reset(ldir);
    m_avp.reset(ldir);
    m_host1x.reset(ldir);

    m_mainwindow->getUi()->tableWidgetMessages->setRowCount(0);
    m_mainwindow->getUi()->tableWidgetErrors->ClearLog();
}

void TraceCore::onDisconnect(void)
{
    changeSpeedButtonText(false,
                          m_mainwindow->getUi()->pushButton_SlowDownTime);
}

void TraceCore::timeSpeedToggle(void)
{
    static bool slow = false;
    quint32 cmd = CMD_CHANGE_TIMERS_SPEED;
    quint32 speed;

    slow = !slow;
    speed = slow ? 5000 : 1000000;

    if (m_ipc.send(&cmd, sizeof(cmd)) && m_ipc.send(&speed, sizeof(speed))) {
        changeSpeedButtonText(slow,
                              m_mainwindow->getUi()->pushButton_SlowDownTime);
    }
}

TraceCore::TraceCore(MainWindow *mainwindow, QObject *parent)
    : QObject(parent),
      m_mainwindow(mainwindow),
      m_avp(mainwindow, "AVP", &m_recordfile, this),
      m_a9(mainwindow, "CPU", &m_recordfile, this),
      m_host1x(mainwindow, "Host1x", this)
{
    connect(&m_ipc, SIGNAL(connected(void)), this, SLOT(onConnect(void)));

    connect(&m_ipc, SIGNAL(disconnected(void)), this, SLOT(onDisconnect(void)));

    connect(&m_ipc, SIGNAL(regAccess(u_int32_t, u_int32_t, u_int32_t, u_int32_t, u_int32_t, u_int32_t, u_int32_t, u_int32_t, bool)),
            this, SLOT(regAccess(u_int32_t, u_int32_t, u_int32_t, u_int32_t, u_int32_t, u_int32_t, u_int32_t, u_int32_t, bool)));

    connect(&m_ipc, SIGNAL(message(char*)), this, SLOT(message(char*)));

    connect(&m_ipc, SIGNAL(chWrite(u_int32_t, u_int32_t, u_int32_t, u_int32_t)),
            this, SLOT(chWrite(u_int32_t, u_int32_t, u_int32_t, u_int32_t)));

    TraceSettings::createInstance(m_mainwindow);

    connect(TraceSettings::instance(), SIGNAL(remoteAddrChanged(const QString &)),
            &m_ipc, SLOT(changeAddr(const QString &)));

    connect(m_mainwindow->getUi()->pushButton_SlowDownTime, SIGNAL(clicked(bool)),
            this, SLOT(timeSpeedToggle()));

    m_ipc.connectTo(TraceSettings::instance()->remoteAddr());
}

void TraceCore::message(char *txt)
{
    m_mainwindow->getUi()->tableWidgetMessages->insertMessage(txt);
    delete[] txt;
}

void TraceCore::regAccess(u_int32_t hwaddr, u_int32_t offset, u_int32_t value,
                          u_int32_t new_value, u_int32_t time, u_int32_t is_write,
                          u_int32_t cpu_pc, u_int32_t cpu_id, bool is_irq)
{
    bool host1x_irq = false;

    if (is_irq) {
        if (offset == 65 || offset == 67) {
            cpu_id = TEGRA2_A9_CORE0;
            host1x_irq = true;
        } else if (offset == 64 || offset == 66) {
            cpu_id = TEGRA2_COP;
        }
    }

    switch (cpu_id) {
    case TEGRA2_A9_CORE0:
    case TEGRA2_A9_CORE1:
        m_a9.regAccess(hwaddr, offset, value, new_value, time, is_write,
                       cpu_pc, cpu_id, is_irq);
        if (!is_irq || host1x_irq) {
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
