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

#include <QScrollBar>

#include "traceui.h"
#include "ui_mainwindow.h"

TraceUI::TraceUI(MainWindow *window, QString name, QObject *parent) :
    QObject(parent), m_mainwindow(window), m_activeDevice(NULL)
{
    TraceTabWidget *tab = window->getUi()->tabWidgetTrace;

    m_tableViewBitDetails = tab->findChild<QTableView *>("tableViewBitDetails_" + name);
    m_listWidgetDevices = tab->findChild<QListWidget *>("listWidgetDevices_" + name);
    m_tableViewTrace = tab->findChild<QTableView *>("tableViewTrace_" + name);
    m_textRegDesc = tab->findChild<QTextEdit *>("textRegDesc_" + name);
    m_regFilter = tab->findChild<QLineEdit *>("lineEditRegFilter_" + name);

    connect(m_listWidgetDevices,
            SIGNAL(currentItemChanged(QListWidgetItem *, QListWidgetItem *)),
            this, SLOT(ActiveDeviceChanged(QListWidgetItem *, QListWidgetItem *)));
}

void TraceUI::addDevice(TraceDev *dev)
{
    ErrorsTableWidget *e = m_mainwindow->getUi()->tableWidgetErrors;
    TraceTabWidget *tab = m_mainwindow->getUi()->tabWidgetTrace;

    m_listWidgetDevices->addItem(dev);

    connect(dev, SIGNAL(ErrorUnknownReg(const QString, const Device::log_entry)),
            e, SLOT(AddEntry(const QString, const Device::log_entry)));

    connect(dev, SIGNAL(ErrorCustom(const QString, const QString, const u_int32_t)),
            e, SLOT(AddCustomEntry(const QString, const QString, const u_int32_t)));

    connect(dev, SIGNAL(ErrorUnknownReg(const QString, const Device::log_entry)),
            tab, SLOT(OnError(void)));

    connect(dev, SIGNAL(ErrorCustom(const QString, const QString, const u_int32_t)),
            tab, SLOT(OnError(void)));
}

void TraceUI::ActiveRegChanged(const QItemSelection & selected,
                               const QItemSelection &)
{
    QModelIndexList indexes = selected.indexes();
    int index;

    if (indexes.count() == 0)
        return;

    index = indexes.at(0).row();

    if (m_reg_sel_index == index)
        return;

    m_textRegDesc->setPlainText( m_activeDevice->updateDetails(index) );
    m_reg_sel_index = index;
}

void TraceUI::ActiveDeviceChanged(QListWidgetItem *item, QListWidgetItem *)
{
    if (m_activeDevice != NULL) {
        disconnect(m_activeDevice, SIGNAL(logItemInserted(bool)),
                   this, SLOT(logItemInserted(bool)));

        disconnect(m_regFilter, SIGNAL(textEdited(const QString)),
                   m_activeDevice, SLOT(regFilterChanged(const QString)));

        disconnect(m_tableViewTrace->selectionModel(),
                SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)),
                this, SLOT(ActiveRegChanged(const QItemSelection &, const QItemSelection &)));
    }

    m_activeDevice = static_cast<TraceDev *> (item);
    m_reg_sel_index = -1;

    m_tableViewTrace->setModel(m_activeDevice);
    m_tableViewBitDetails->setModel(m_activeDevice->getBitDetailsModel());
    m_tableViewBitDetails->setVisible(
                m_activeDevice->hasCap(TraceDev::BITS_DESC) );
    m_tableViewBitDetails->setColumnWidth(0, 350);
    m_tableViewBitDetails->setColumnWidth(1, 150);
    m_tableViewBitDetails->setColumnWidth(2, 150);
    m_textRegDesc->setVisible(
                m_activeDevice->hasCap(TraceDev::REG_DESC) );

    scrollTraceView(false, true);

    connect(m_regFilter, SIGNAL(textEdited(const QString)),
            m_activeDevice, SLOT(regFilterChanged(const QString)));

    connect(m_activeDevice, SIGNAL(logItemInserted(bool)),
            this, SLOT(logItemInserted(bool)));

    connect(m_tableViewTrace->selectionModel(),
            SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)),
            this, SLOT(ActiveRegChanged(const QItemSelection &, const QItemSelection &)));
}

void TraceUI::scrollTraceView(bool is_full, bool force)
{
    QItemSelectionModel *select = m_tableViewTrace->selectionModel();
    QAbstractItemModel *model = m_tableViewTrace->model();
    QScrollBar *sb = m_tableViewTrace->verticalScrollBar();
    int first_visible_row = qMax(0, m_tableViewTrace->rowAt(0) - 1);
    bool in_bottom = (sb->value() == sb->maximum());

    if (is_full) {
        if (select->hasSelection()) {
            int prev_row = qMax(0, select->selectedIndexes().at(0).row() - 1);

            m_tableViewTrace->selectRow(prev_row);
        }

        if (!in_bottom) {
            m_tableViewTrace->scrollTo(model->index(first_visible_row, 0),
                                       QAbstractItemView::PositionAtTop);
        }
    }

    if (in_bottom || force) {
        m_tableViewTrace->scrollToBottom();
    }
}

void TraceUI::logItemInserted(bool is_full)
{
    if (is_full) {
        m_reg_sel_index = qMax(m_reg_sel_index - 1, 0);
    }

    scrollTraceView(is_full, false);
}

void TraceUI::resetUI(void)
{
    m_textRegDesc->setPlainText("");
    m_reg_sel_index = -1;
}
