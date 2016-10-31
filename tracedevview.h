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

#ifndef TRACEDEVVIEW_H
#define TRACEDEVVIEW_H

#include <QTableView>

#include "tracedev.h"

class TraceDevView : public QTableView
{
    Q_OBJECT

public:
    TraceDevView(QWidget *parent = 0);

    void setModel(TraceDev *dev);

signals:
    void selected(const QModelIndex &);

private slots:
    void sectionCountChanged(int oldCount, int newCount);

public slots:
    void itemInserted(void);

    // QAbstractItemView interface
protected slots:
    void currentChanged(const QModelIndex &current, const QModelIndex &)
    {
        emit selected(current);
    }
};

#endif // TRACEDEVVIEW_H
