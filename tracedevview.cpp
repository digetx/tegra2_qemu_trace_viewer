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

#include <QHeaderView>
#include <QScrollBar>

#include "tracedevview.h"

TraceDevView::TraceDevView(QWidget *parent) :
    QTableView(parent)
{
    connect(this->verticalHeader(), SIGNAL(sectionCountChanged(int, int)),
            this, SLOT(sectionCountChanged(int, int)));
}

void TraceDevView::setModel(TraceDev *dev)
{
    disconnect(this->model(), SIGNAL(itemInserted(void)),
               this, SLOT(itemInserted(void)));

    connect(dev, SIGNAL(itemInserted(void)),
            this, SLOT(itemInserted(void)));

    QTableView::setModel(dev);

    scrollToBottom();
}

void TraceDevView::sectionCountChanged(int, int)
{
    QScrollBar *sb = this->verticalScrollBar();
    bool in_bottom = (sb->value() == sb->maximum());

    if (in_bottom) {
        scrollToBottom();
    }
}

void TraceDevView::itemInserted(void)
{
    QItemSelectionModel *select = this->selectionModel();
    QAbstractItemModel *model = this->model();
    QScrollBar *sb = this->verticalScrollBar();
    int first_visible_row = qMax(0, this->rowAt(0) - 1);
    bool in_bottom = (sb->value() == sb->maximum());

    if (select->hasSelection()) {
        int prev_row = qMax(0, select->selectedIndexes().at(0).row() - 1);

        selectRow(prev_row);
    }

    if (!in_bottom) {
        scrollTo(model->index(first_visible_row, 0),
                 QAbstractItemView::PositionAtTop);
    }
}
