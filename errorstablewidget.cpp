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

#include <QTime>

#include "errorstablewidget.h"

ErrorsTableWidget::ErrorsTableWidget(QWidget *parent) :
    TraceQTableWidget(0, COLUMNS_NB, parent)
{
    setHorizontalHeaderLabels(QStringList() << "Time" << "Device" << "Description");
}

void ErrorsTableWidget::AddEntry(const u_int32_t offset, const u_int32_t time)
{
    const QString error_name("Unknown device");
    const QString error_desc = QString().sprintf("@0x%08X", offset);

    AddRow(time, error_name, error_desc, false);
}

void ErrorsTableWidget::AddEntry(const QString dev_name, const Device::log_entry entry)
{
    QString error_desc;

    if (entry.is_write)
        error_desc.sprintf("writing 0x%x to unknown reg @0x%x cpu[%d]=0x%X",
                           entry.value, entry.offset, entry.cpu_id, entry.cpu_pc);
    else
        error_desc.sprintf("reading of unknown reg @0x%x cpu[%d]=0x%X",
                           entry.offset, entry.cpu_id, entry.cpu_pc);

    AddRow(entry.time, dev_name, error_desc, true);
}

void ErrorsTableWidget::AddCustomEntry(const QString dev_name,
                                       const QString text,
                                       const u_int32_t time)
{
    AddRow(time, dev_name, text, false);
}

void ErrorsTableWidget::AddRow(const u_int32_t &time,
                               const QString &name, const QString &desc,
                               const bool &set_color)
{
    QTableWidgetItem *name_item = new QTableWidgetItem(name);
    QTableWidgetItem *desc_item = new QTableWidgetItem(desc);
    QTime mstime = QTime(0, 0).addMSecs(time / 1000);
    QString timestr =  mstime.toString("hh:mm:ss.zzz") +
                                    QString().sprintf(".%03d", time % 1000);
    QTableWidgetItem *time_item = new QTableWidgetItem(timestr);
    int next_row = rowCount();

    insertRow(next_row);

    setItem(next_row, ErrorsTableWidget::TIME, time_item);
    setItem(next_row, ErrorsTableWidget::NAME, name_item);
    setItem(next_row, ErrorsTableWidget::DESC, desc_item);

    if (set_color) {
        time_item->setBackground( QBrush( QColor(255, 190, 190) ));
        name_item->setBackground( QBrush( QColor(255, 190, 190) ));
        desc_item->setBackground( QBrush( QColor(255, 190, 190) ));
        time_item->setForeground( QBrush( Qt::black ));
        name_item->setForeground( QBrush( Qt::black ));
        desc_item->setForeground( QBrush( Qt::black ));
    }

//    resizeColumnToContents(ErrorsTableWidget::NAME);
}

void ErrorsTableWidget::ClearLog(void)
{
    while (rowCount())
        removeRow(0);
}
