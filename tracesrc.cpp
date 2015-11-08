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

#include "cdmatrace.h"
#include "device.h"
#include "tracesrc.h"
#include "ui_mainwindow.h"

TraceSRC::TraceSRC(MainWindow *window, QString name, QObject *parent) :
    QObject(parent), m_tui(window, name, this), m_name(name)
{
    ErrorsTableWidget *e = window->getUi()->tableWidgetErrors;
    TraceTabWidget *tab = window->getUi()->tabWidgetTrace;

    connect(this, SIGNAL(ErrUnkDev(const u_int32_t, const u_int32_t)),
            e, SLOT(AddEntry(const u_int32_t, const u_int32_t)));

    connect(this, SIGNAL(ErrUnkDev(const u_int32_t, const u_int32_t)),
            tab, SLOT(OnError(void)));
}

void TraceSRC::addDevice(TraceDev *dev)
{
    m_devices.append(dev);
    m_tui.addDevice(dev);
}

void TraceSRC::regAccess(const u_int32_t &hwaddr, const u_int32_t &offset,
                         const u_int32_t &value, const u_int32_t &new_value,
                         const u_int32_t &time, const bool &is_write,
                         const u_int32_t &cpu_pc, const u_int32_t &cpu_id,
                         const bool &is_irq)
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

    emit ErrUnkDev(hwaddr, time);
}

void TraceSRC::chWrite(const u_int32_t &ch_id, const u_int32_t &time,
                       const u_int32_t &data, const u_int32_t &is_gather)
{
    QVarLengthArray<TraceDev*>::const_iterator tdev;

    Q_ASSERT(ch_id < CHANNELS_NB);

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

void TraceSRC::reset(QString log_path)
{
    QVarLengthArray<TraceDev*>::const_iterator dev;

    for (dev = m_devices.constBegin(); dev != m_devices.constEnd(); dev++) {
            (*dev)->ClearLog();
            (*dev)->setLogPath(log_path + m_name + "_");
    }

    m_tui.resetUI();
}
