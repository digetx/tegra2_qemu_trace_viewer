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

#ifndef TRACESETTINGS_H
#define TRACESETTINGS_H

#include <QFileDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QSettings>

#include "mainwindow.h"
#include "ui_mainwindow.h"

class TraceSettings : public QObject
{
    Q_OBJECT
public:
    static TraceSettings * instance(void)
    {
        Q_ASSERT(m_inst != NULL);
        return m_inst;
    }

    static void createInstance(MainWindow *mainwindow)
    {
        m_inst = new TraceSettings(mainwindow->getUi()->pushButtonSeveDir,
                                   mainwindow->getUi()->pushButtonRemoteAddr,
                                   mainwindow->getUi()->lineEditSaveDir,
                                   mainwindow->getUi()->lineEditRemoteAddr);
    }

    static QString logsDirPath(void)
    {
        return m_inst->m_edit_savedir->text();
    }

    static QString remoteAddr(void)
    {
        return m_inst->m_edit_remoteaddr->text();
    }

private:
    explicit TraceSettings(QPushButton *b_savedir, QPushButton *b_remoteaddr,
                           QLineEdit *e_savedir, QLineEdit *e_remoteaddr);

    QSettings m_settings;

    QFileDialog m_savedirdialog;
    QLineEdit *m_edit_savedir;

    QPushButton *m_b_remoteaddr;
    QLineEdit *m_edit_remoteaddr;
    QString m_remoteaddr;

    Q_DISABLE_COPY(TraceSettings)

    static TraceSettings *m_inst;

signals:
    void remoteAddrChanged(const QString &);

private slots:
    void updateSaveDir(void);
    void updateRemoteAddr(void);
    void remoteAddrTextChanged(const QString &text);
};

#endif // TRACESETTINGS_H
