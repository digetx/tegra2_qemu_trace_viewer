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

#ifndef TRACECPU_H
#define TRACECPU_H

#include <QObject>
#include <QVarLengthArray>

#include "mainwindow.h"
#include "tracedev.h"
#include "traceui.h"

class TraceSRC : public QObject
{
    Q_OBJECT
public:
    explicit TraceSRC(MainWindow *window, QString name, QObject *parent = 0);

    void regAccess(const u_int32_t &hwaddr, const u_int32_t &offset,
                   const u_int32_t &value, const u_int32_t &new_value,
                   const u_int32_t &time, const bool &is_write,
                   const u_int32_t &cpu_pc, const u_int32_t &cpu_id,
                   const bool &is_irq);

    void chWrite(const u_int32_t &ch_id, const u_int32_t &time,
                 const u_int32_t &data, const u_int32_t &is_gather);

    void reset(QString log_path);

protected:
    TraceUI m_tui;
    QString m_name;
    QVarLengthArray<TraceDev*> m_devices;

    void addDevice(TraceDev *dev);

signals:
    void ErrUnkDev(const u_int32_t, const u_int32_t);

public slots:
};

#endif // TRACECPU_H
