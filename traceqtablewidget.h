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

#ifndef TRACEQTABLEWIDGET_H
#define TRACEQTABLEWIDGET_H

#include <QTableWidget>

class TraceQTableWidget : public QTableWidget
{
public:
    explicit TraceQTableWidget(QWidget *parent = 0);
    explicit TraceQTableWidget(int rows, int columns, QWidget * parent = 0);

    // QAbstractItemView interface
protected slots:
    void rowsInserted(const QModelIndex &parent, int start, int end);

};

#endif // TRACEQTABLEWIDGET_H
