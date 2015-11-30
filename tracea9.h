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

#ifndef TraceA9_H
#define TraceA9_H

#include "tracesrc.h"

class TraceA9 : public TraceSRC
{
    Q_OBJECT
public:
    explicit TraceA9(MainWindow *window, QString name, QObject *parent = 0);

    enum {
        BASE,
        NAME,
        READS,
        WRITES,
        IRQ_ACTIONS,
        ERRORS,
        COLUMS_NB,
    };

private slots:
    void firstTimeStatUpdated(int);
    void readStatUpdated(int);
    void writeStatUpdated(int);
    void irqStatUpdated(int);
    void errorStatUpdated(int);

    // TraceSRC interface
public:
    void addDevice(TraceDev *dev);

    // QAbstractItemModel interface
public:
    int columnCount(const QModelIndex &) const;
    QVariant data(const QModelIndex &, int) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
};

#endif // TraceA9_H
