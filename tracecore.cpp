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
#include <QtDBus/QtDBus>
#include <QDir>

#include "tracecore.h"
#include "tracesettings.h"
#include "ui_mainwindow.h"

#define HOST1X_CDMA     0x1010
#define QEMU_DEBUGGER   0xFF

#define CMD_CHANGE_TIMERS_SPEED     0x122

void TraceCore::startRecordingAVP(void)
{
    m_avp.startRecording();
}

void TraceCore::stopRecordingAVP(void)
{
    m_avp.stopRecording();
}

void TraceCore::startRecordingCPU(void)
{
    m_a9.startRecording();
}

void TraceCore::stopRecordingCPU(void)
{
    m_a9.stopRecording();
}

QString TraceCore::recordingFilePath(void)
{
    return m_recordfile.fileName();
}

void TraceCore::setTimeSpeed(bool slowdown)
{
    quint32 cmd = CMD_CHANGE_TIMERS_SPEED;
    quint32 speed = slowdown ? 5000 : 1000000;

    m_ipc.send(&cmd, sizeof(cmd));
    m_ipc.send(&speed, sizeof(speed));

    m_mainwindow->getUi()->pushButton_SlowDownTime->setText(
                slowdown ? "Normal speed" : "Slow down time");
    m_mainwindow->getUi()->pushButton_SlowDownTime->setStyleSheet(
                slowdown ? "background: blue" : "");

    m_slowdowntime = slowdown;
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

    if (m_slowdowntime) {
        setTimeSpeed(true);
    }
}

void TraceCore::onDisconnect(void)
{
    setTimeSpeed(false);
}

void TraceCore::timeSpeedToggle(void)
{
    setTimeSpeed(!m_slowdowntime);
}

TraceCore::TraceCore(MainWindow *mainwindow)
    : QDBusAbstractAdaptor(mainwindow),
      m_mainwindow(mainwindow),
      m_avp(mainwindow, "AVP", &m_recordfile, this),
      m_a9(mainwindow, "CPU", &m_recordfile, this),
      m_host1x(mainwindow, "Host1x", this),
      m_slowdowntime(false)
{
    connect(&m_ipc, SIGNAL(connected(void)), this, SLOT(onConnect(void)));

    connect(&m_ipc, SIGNAL(disconnected(void)), this, SLOT(onDisconnect(void)));

    connect(&m_ipc, SIGNAL(regAccess(TraceIPC::packet_rw)),
            this, SLOT(regAccess(TraceIPC::packet_rw)));

    connect(&m_ipc, SIGNAL(irqEvent(TraceIPC::packet_irq)),
            this, SLOT(irqEvent(TraceIPC::packet_irq)));

    connect(&m_ipc, SIGNAL(message(char*)), this, SLOT(message(char*)));

    connect(&m_ipc, SIGNAL(chWrite(u_int32_t, u_int32_t, u_int32_t, u_int32_t)),
            this, SLOT(chWrite(u_int32_t, u_int32_t, u_int32_t, u_int32_t)));

    TraceSettings::createInstance(m_mainwindow);

    connect(TraceSettings::instance(), SIGNAL(remoteAddrChanged(const QString &)),
            &m_ipc, SLOT(changeAddr(const QString &)));

    connect(m_mainwindow->getUi()->pushButton_SlowDownTime, SIGNAL(clicked(bool)),
            this, SLOT(timeSpeedToggle()));

    m_ipc.connectTo(TraceSettings::instance()->remoteAddr());

    QDBusConnection::sessionBus().registerObject("/", mainwindow);

    if (!QDBusConnection::sessionBus().registerService("org.traceviewer")) {
        fprintf(stderr, "%s\n",
                qPrintable(QDBusConnection::sessionBus().lastError().message()));
    }
}

void TraceCore::message(char *txt)
{
    m_mainwindow->getUi()->tableWidgetMessages->insertMessage(txt);
    delete[] txt;
}

void TraceCore::regAccess(TraceIPC::packet_rw pak_rw)
{
    switch (pak_rw.cpu_id) {
    case TEGRA2_A9_CORE0:
    case TEGRA2_A9_CORE1:
        m_a9.handle(pak_rw);
        break;
    case TEGRA2_COP:
        m_avp.handle(pak_rw);
        break;
    case HOST1X_CDMA:
        m_host1x.handle(pak_rw);
        break;
    case QEMU_DEBUGGER:
        break;
    default:
        Q_ASSERT(0);
        break;
    }
}

void TraceCore::irqEvent(TraceIPC::packet_irq pak_irq)
{
    bool host1x_irq = false;

    if (pak_irq.hwirq == 65 || pak_irq.hwirq == 67) {
        pak_irq.cpu_id = TEGRA2_A9_CORE0;
        host1x_irq = true;
    } else if (pak_irq.hwirq == 64 || pak_irq.hwirq == 66) {
        pak_irq.cpu_id = TEGRA2_COP;
    }

    switch (pak_irq.cpu_id) {
    case TEGRA2_A9_CORE0:
    case TEGRA2_A9_CORE1:
        m_a9.handle(pak_irq);
        if (host1x_irq) {
            break;
        }
    case TEGRA2_COP:
        m_avp.handle(pak_irq);
        break;
    case HOST1X_CDMA:
        m_host1x.handle(pak_irq);
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
