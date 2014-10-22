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

#include <QDebug>
#include <QSettings>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "device.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QSettings settings;

    ui->setupUi(this);

    restoreGeometry(settings.value("mainWindowGeometry").toByteArray());
    restoreState(settings.value("mainWindowState").toByteArray());
}

MainWindow::~MainWindow()
{
    delete ui;
}

Ui::MainWindow *MainWindow::getUi()
{
    return ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QSettings settings;

    settings.setValue("mainWindowGeometry", saveGeometry());
    settings.setValue("mainWindowState", saveState());

    QMainWindow::closeEvent(event);
}

void MainWindow::addDeviceListItem(QListWidgetItem *item)
{
    ui->listWidgetDevices->addItem(item);
}

void MainWindow::connectDevicesListItemClick(QObject *obj, const char *slot)
{
    connect(ui->listWidgetDevices,
            SIGNAL(currentItemChanged(QListWidgetItem*, QListWidgetItem*)),
            obj, slot);
}

void MainWindow::connectTraceSelectionChanged(QObject *obj, const char *slot)
{
    connect(ui->tableViewTrace->selectionModel(),
            SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)),
            obj, slot);
}

void MainWindow::setTableViewTraceModel(QAbstractTableModel *model)
{
    ui->tableViewTrace->setModel(model);
}

void MainWindow::setDetailsModel(QAbstractTableModel *model)
{
    ui->tableViewBitDetails->setModel(model);
    ui->tableViewBitDetails->setColumnWidth(0, 350);
    ui->tableViewBitDetails->setColumnWidth(1, 150);
    ui->tableViewBitDetails->setColumnWidth(2, 150);
}

void MainWindow::connectDeviceErrorsLog(QObject *obj,
                                        const char *signal_reg,
                                        const char *signal_cust)
{
    connect(obj, signal_reg, ui->tableWidgetErrors,
            SLOT(AddEntry(const QString, const Device::log_entry)));
    connect(obj, signal_cust, ui->tableWidgetErrors,
            SLOT(AddCustomEntry(const QString, const QString,
                                const u_int32_t)));
    connect(obj, signal_reg, ui->tabWidgetTrace, SLOT(OnError(void)));
    connect(obj, signal_cust, ui->tabWidgetTrace, SLOT(OnError(void)));
}

void MainWindow::connectUnkDeviceErrorsLog(QObject *obj, const char *signal)
{
    connect(obj, signal, ui->tableWidgetErrors,
            SLOT(AddEntry(const u_int32_t, const u_int32_t)));
    connect(obj, signal, ui->tabWidgetTrace, SLOT(OnError(void)));
}

void MainWindow::connectClearErrorsLog(QObject *obj, const char *signal)
{
    connect(obj, signal, ui->tableWidgetErrors, SLOT(ClearLog()));
    connect(obj, signal, ui->tabWidgetTrace, SLOT(ClearErrorState()));
}

void MainWindow::setRegDesc(QString text)
{
    ui->textRegDesc->setPlainText(text);
}

void MainWindow::connectDeviceRegFilter(QObject *obj,
                                        const char *slot_regfilter)
{
    connect(ui->lineEditRegFilter, SIGNAL(textEdited(const QString)),
            obj, slot_regfilter);
}

void MainWindow::disconnectDeviceRegFilter(QObject *obj,
                                           const char *slot_regfilter)
{
    disconnect(ui->lineEditRegFilter, SIGNAL(textEdited(const QString)),
               obj, slot_regfilter);
}
