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

#ifndef TRACECORE_H
#define TRACECORE_H

#include <QObject>
#include <QListWidgetItem>
#include <QVarLengthArray>
#include <QTableView>

#include "mainwindow.h"
#include "traceipc.h"

#include "tracedev.h"

#define CHANNELS_NB 8

class TraceCore : public QObject
{
    Q_OBJECT

public:

    explicit TraceCore(QObject *parent = 0);

    TraceCore(MainWindow *mainwindow, QObject *parent = 0);

signals:
    void ErrorUnknownDev(const u_int32_t offset, const u_int32_t time);

public slots:
    void uiActiveDeviceChanged(QListWidgetItem *item);

    void uiTraceSelectionChanged(const QItemSelection & selected,
                                 const QItemSelection &);

    void logItemInserted(bool);

    void regWrite(u_int32_t hwaddr, u_int32_t offset, u_int32_t value,
                  u_int32_t new_value, u_int32_t time, bool is_write,
                  u_int32_t cpu_pc, u_int32_t cpu_id, bool is_irq);

    void chWrite(u_int32_t ch_id, u_int32_t time,
                 u_int32_t data, u_int32_t is_gather);

    void onConnect(void);

    void onDisconnect(void);

    void message(char *txt);

private:
    MainWindow *m_mainwindow;
    TraceDev *m_activeDevice;
    TraceIPC m_ipc;
    int m_dev_sel_index;

//    TestDev testdev;
    QVarLengthArray<TraceDev*> m_devices;

    void addDeviceToList(TraceDev *dev);
    void scrollTraceView(QTableView *tableView, bool is_full, bool force);
};

#endif // TRACECORE_H
