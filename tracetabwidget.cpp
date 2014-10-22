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

#include <QTabBar>

#include "tracetabwidget.h"

TraceTabWidget::TraceTabWidget(QWidget *parent) :
    QTabWidget(parent)
{
    connect(this, SIGNAL(currentChanged(int)), this, SLOT(TabChanged(int)));
}

void TraceTabWidget::TabChanged(int index)
{
    switch (index) {
    case TraceTabWidget::ERROR_TAB:
        tabBar()->setTabTextColor(index, QColor());
        break;
    default:
        break;
    }
}

void TraceTabWidget::OnError(void)
{
    if (currentIndex() == TraceTabWidget::ERROR_TAB)
        return;

    tabBar()->setTabTextColor(TraceTabWidget::ERROR_TAB, Qt::red);
}

void TraceTabWidget::ClearErrorState(void)
{
    tabBar()->setTabTextColor(TraceTabWidget::ERROR_TAB, QColor());
}
