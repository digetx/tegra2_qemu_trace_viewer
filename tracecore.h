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

#include "tracea9.h"
#include "traceavp.h"
#include "tracehost1x.h"

class TraceCore : public QObject
{
    Q_OBJECT

public:
    explicit TraceCore(MainWindow *mainwindow, QObject *parent = 0);

signals:

public slots:
    void regAccess(u_int32_t hwaddr, u_int32_t offset, u_int32_t value,
                   u_int32_t new_value, u_int32_t time, bool is_write,
                   u_int32_t cpu_pc, u_int32_t cpu_id, bool is_irq);

    void chWrite(u_int32_t ch_id, u_int32_t time,
                 u_int32_t data, u_int32_t is_gather);

    void onConnect(void);

    void onDisconnect(void);

    void message(char *txt);

private:
    MainWindow *m_mainwindow;
    TraceIPC m_ipc;
    TraceAVP m_avp;
    TraceA9 m_a9;
    TraceHOST1X m_host1x;
};

#endif // TRACECORE_H
