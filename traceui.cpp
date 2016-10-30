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

#include "tracesrc.h"
#include "ui_mainwindow.h"

TraceUI::TraceUI(MainWindow *window, QString name, TraceSRC *parent) :
    QObject(parent), m_mainwindow(window), m_activeDevice(NULL), m_tracesrc(parent)
{
    TraceTabWidget *tab = window->getUi()->tabWidgetTrace;

    m_tableViewDevices = tab->findChild<QTableView *>("tableViewDevices_" + name);
    m_tableViewBitDetails = tab->findChild<QTableView *>("tableViewBitDetails_" + name);
    m_listWidgetDevices = tab->findChild<QListWidget *>("listWidgetDevices_" + name);
    m_tableViewTrace = tab->findChild<TraceDevView *>("tableWidgetTrace_" + name);
    m_textRegDesc = tab->findChild<QTextEdit *>("textRegDesc_" + name);
    m_regFilter = tab->findChild<QLineEdit *>("lineEditRegFilter_" + name);
    m_rec_button = window->findChild<QPushButton *>("pushButton_Record" + name);

    connect(m_listWidgetDevices,
            SIGNAL(currentItemChanged(QListWidgetItem *, QListWidgetItem *)),
            this, SLOT(ActiveDeviceChanged(QListWidgetItem *, QListWidgetItem *)));

    connect(m_tableViewTrace, SIGNAL(selected(const QModelIndex &)),
            this, SLOT(ActiveRegChanged(const QModelIndex &)));

    if (m_tableViewDevices != NULL) {
        m_tableViewDevices->setModel(m_tracesrc);

        connect(m_tableViewDevices->selectionModel(),
                SIGNAL(currentRowChanged(const QModelIndex &, const QModelIndex &)),
                this, SLOT(ActiveDeviceChanged(const QModelIndex &, const QModelIndex &)));
    }
}

void TraceUI::addDevice(TraceDev *dev)
{
    ErrorsTableWidget *e = m_mainwindow->getUi()->tableWidgetErrors;
    TraceTabWidget *tab = m_mainwindow->getUi()->tabWidgetTrace;

    if (m_listWidgetDevices != NULL) {
        m_listWidgetDevices->addItem(dev);
    }

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
    QString reg_desc = m_activeDevice->updateDetails(index.row());

    m_textRegDesc->setVisible(
            m_activeDevice->hasCap(TraceDev::REG_DESC) && !reg_desc.isEmpty());

    m_textRegDesc->setPlainText(reg_desc);

    if (m_tableViewBitDetails->model() == NULL && m_activeDevice != NULL)
        m_tableViewBitDetails->setModel(m_activeDevice->getBitDetailsModel());

    if (m_tableViewBitDetails->model() == NULL)
        return;

    for (int i = 0; i < m_tableViewBitDetails->model()->columnCount() - 1; i++)
        m_tableViewBitDetails->resizeColumnToContents(i);

    m_tableViewBitDetails->resizeRowsToContents();
}

void TraceUI::ActiveDeviceChanged(QListWidgetItem *item, QListWidgetItem *)
{
    ActiveDeviceChanged( static_cast<TraceDev *> (item) );
}

void TraceUI::ActiveDeviceChanged(const QModelIndex &index, const QModelIndex &)
{
    ActiveDeviceChanged( m_tracesrc->getDevAt(index.row()) );
}

void TraceUI::ActiveDeviceChanged(TraceDev *dev)
{
    disconnect(m_regFilter, SIGNAL(textEdited(const QString)),
               m_activeDevice, SLOT(regFilterChanged(const QString)));

    m_activeDevice = dev;

    m_tableViewTrace->setModel(m_activeDevice);
    m_tableViewBitDetails->setModel(NULL);
    m_tableViewBitDetails->setVisible(
                m_activeDevice->hasCap(TraceDev::BITS_DESC) );

    m_textRegDesc->setVisible(false);
    m_textRegDesc->setPlainText("");

    connect(m_regFilter, SIGNAL(textEdited(const QString)),
            m_activeDevice, SLOT(regFilterChanged(const QString)));
}

void TraceUI::resetUI(void)
{
    TraceTabWidget *tab = m_mainwindow->getUi()->tabWidgetTrace;

    tab->ClearErrorState();
    m_textRegDesc->setPlainText("");
}
