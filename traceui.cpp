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
    m_tableViewTrace = tab->findChild<TraceDevView *>("tableWidgetTrace_" + name);
    m_textRegDesc = tab->findChild<QTextEdit *>("textRegDesc_" + name);
    m_regFilter = tab->findChild<QLineEdit *>("lineEditRegFilter_" + name);

    connect(m_listWidgetDevices,
            SIGNAL(currentItemChanged(QListWidgetItem *, QListWidgetItem *)),
            this, SLOT(ActiveDeviceChanged(QListWidgetItem *, QListWidgetItem *)));

    connect(m_tableViewTrace, SIGNAL(selected(const QModelIndex &)),
            this, SLOT(ActiveRegChanged(const QModelIndex &)));
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

void TraceUI::ActiveRegChanged(const QModelIndex &index)
{
    m_textRegDesc->setPlainText( m_activeDevice->updateDetails(index.row()) );
}

void TraceUI::ActiveDeviceChanged(QListWidgetItem *item, QListWidgetItem *)
{
    disconnect(m_regFilter, SIGNAL(textEdited(const QString)),
               m_activeDevice, SLOT(regFilterChanged(const QString)));

    m_activeDevice = static_cast<TraceDev *> (item);

    m_tableViewTrace->setModel(m_activeDevice);
    m_tableViewBitDetails->setModel(m_activeDevice->getBitDetailsModel());
    m_tableViewBitDetails->setVisible(
                m_activeDevice->hasCap(TraceDev::BITS_DESC) );
    m_tableViewBitDetails->setColumnWidth(0, 350);
    m_tableViewBitDetails->setColumnWidth(1, 150);
    m_tableViewBitDetails->setColumnWidth(2, 150);
    m_textRegDesc->setVisible(
                m_activeDevice->hasCap(TraceDev::REG_DESC) );

    connect(m_regFilter, SIGNAL(textEdited(const QString)),
            m_activeDevice, SLOT(regFilterChanged(const QString)));
}

void TraceUI::resetUI(void)
{
    m_textRegDesc->setPlainText("");
}