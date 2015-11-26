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

#include "traceipc.h"
#include "tracesettings.h"

TraceSettings *TraceSettings::m_inst = NULL;

TraceSettings::TraceSettings(QPushButton *b_savedir, QPushButton *b_remoteaddr,
                             QLineEdit *e_savedir, QLineEdit *e_remoteaddr)
    : QObject(NULL)
{
    m_edit_savedir = e_savedir;
    m_edit_savedir->setText(m_settings.value("saveDir").toString());

    m_b_remoteaddr = b_remoteaddr;
    m_edit_remoteaddr = e_remoteaddr;
#ifndef LOCAL_SOCKET
    m_edit_remoteaddr->setText(m_settings.value("remoteAddr").toString());
#else
    m_edit_remoteaddr->setEnabled(false);
    m_edit_remoteaddr->setText("/tmp/trace.sock");
#endif

    m_savedirdialog.setFileMode(QFileDialog::Directory);
    m_savedirdialog.setDirectory(m_edit_savedir->text());

    connect(b_savedir, SIGNAL(clicked(bool)), &m_savedirdialog, SLOT(open()));
    connect(&m_savedirdialog, SIGNAL(accepted(void)),
            this, SLOT(updateSaveDir(void)));

    connect(m_b_remoteaddr, SIGNAL(clicked(bool)), this, SLOT(updateRemoteAddr()));
    connect(m_edit_remoteaddr, SIGNAL(textChanged(const QString &)),
            this, SLOT(remoteAddrTextChanged(const QString &)));
}

void TraceSettings::updateSaveDir(void)
{
    m_settings.setValue("saveDir", m_savedirdialog.directory().path());
    m_edit_savedir->setText(m_savedirdialog.directory().path());
    m_savedirdialog.setDirectory(m_edit_savedir->text());
}

void TraceSettings::updateRemoteAddr(void)
{
    m_settings.setValue("remoteAddr", m_edit_remoteaddr->text());
    m_remoteaddr = m_edit_remoteaddr->text();
    m_b_remoteaddr->setEnabled(false);
    emit remoteAddrChanged(m_remoteaddr);
}

void TraceSettings::remoteAddrTextChanged(const QString &text)
{
    m_b_remoteaddr->setEnabled(text != m_remoteaddr);
}
