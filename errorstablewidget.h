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

#ifndef ERRORSTABLEWIDGET_H
#define ERRORSTABLEWIDGET_H

#include "device.h"
#include "traceqtablewidget.h"

class ErrorsTableWidget : public TraceQTableWidget
{
    Q_OBJECT
public:
    explicit ErrorsTableWidget(QWidget *parent = 0);

private:
    void AddRow(const u_int32_t &time, const QString &name,
                const QString &desc, const bool &set_color);

    enum {
        TIME = 0,
        NAME,
        DESC,
        COLUMNS_NB
    };

signals:

public slots:
    void AddEntry(const u_int32_t offset, const u_int32_t time);

    void AddEntry(const QString dev_name, const Device::log_entry entry);

    void AddCustomEntry(const QString dev_name, const QString text,
                        const u_int32_t time);

    void ClearLog(void);

};

#endif // ERRORSTABLEWIDGET_H
