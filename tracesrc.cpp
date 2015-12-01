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
#include "tracecore.h"
#include "tracesrc.h"
#include "ui_mainwindow.h"

TraceSRC::TraceSRC(MainWindow *window, QString name, QObject *parent) :
    QAbstractTableModel(parent), m_name(name),
    m_prev_addr(~0), m_prev_dev(NULL)
{
    ErrorsTableWidget *e = window->getUi()->tableWidgetErrors;
    TraceTabWidget *tab = window->getUi()->tabWidgetTrace;

    connect(this, SIGNAL(ErrUnkDev(const QString, const Device::log_entry)),
            e, SLOT(AddEntry(const QString, const Device::log_entry)));

    connect(this, SIGNAL(ErrUnkDev(const QString, const Device::log_entry)),
            tab, SLOT(OnError(void)));

    m_tui = new TraceUI(window, name, this);
}

void TraceSRC::addDevice(TraceDev *dev)
{
    dev->id = m_devices.size();
    m_devices.append(dev);
    m_tui->addDevice(dev);

    emit layoutChanged();
}

TraceDev * TraceSRC::getDevByAddr(const u_int32_t &addr,
                                  const TraceDev::dev_type &type)
{
    QVarLengthArray<TraceDev*>::const_iterator tdev;

    QMutexLocker locker(&m_mutex);

    if (m_prev_addr == addr) {
        if (m_prev_dev == NULL || m_prev_dev->deviceType() == type) {
            return m_prev_dev;
        }
    }

    m_prev_addr = addr;

    for (tdev = m_devices.constBegin(); tdev != m_devices.constEnd(); tdev++) {
        m_prev_dev = (*tdev);

        if (m_prev_dev->deviceType() != type) {
            continue;
        }

        if (m_prev_dev->is_valid(addr)) {
            return (*tdev);
        }
    }

    m_prev_dev = NULL;

    return NULL;
}

void TraceSRC::regAccess(const u_int32_t &hwaddr, const u_int32_t &offset,
                         const u_int32_t &value, const u_int32_t &new_value,
                         const u_int32_t &time, const bool &is_write,
                         const u_int32_t &cpu_pc, const u_int32_t &cpu_id,
                         const bool &is_irq)
{
    Device *dev = static_cast<Device *> (getDevByAddr(hwaddr, TraceDev::MMIO));

    if (dev != NULL) {
        dev->write_log(offset, value, new_value, time,
                       is_write, cpu_pc, cpu_id, is_irq);
    } else {
        Device::log_entry err_entry;

        err_entry.time = time;
        err_entry.value = value;
        err_entry.cpu_pc = cpu_pc;
        err_entry.cpu_id = cpu_id;
        err_entry.offset = hwaddr + offset;
        err_entry.is_write = is_write;

        emit ErrUnkDev("Unknown device", err_entry);
    }
}

void TraceSRC::chWrite(const u_int32_t &ch_id, const u_int32_t &time,
                       const u_int32_t &data, const u_int32_t &is_gather)
{
    CdmaTrace *dev =
            static_cast<CdmaTrace *> (getDevByAddr(ch_id, TraceDev::HOST1X_CDMA));

    Q_ASSERT(dev != NULL);

    if (dev != NULL) {
        dev->trace(time, data, is_gather);
    }
}

void TraceSRC::reset(QString log_path)
{
    QVarLengthArray<TraceDev*>::const_iterator dev;

    for (dev = m_devices.constBegin(); dev != m_devices.constEnd(); dev++) {
            (*dev)->ClearLog();
            (*dev)->setLogPath(log_path + m_name + "_");
    }

    m_tui->resetUI();

    emit layoutChanged();
}

TraceDev * TraceSRC::getDevAt(int idx) const
{
    return m_devices.at(idx);
}
