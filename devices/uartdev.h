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

#ifndef UARTDEV_H
#define UARTDEV_H

#include "device.h"

class UartDev : public Device
{
    Q_OBJECT

public:
    explicit UartDev(QObject *parent = 0);

    UartDev(const QString name, u_int32_t base) : Device(name, base) {}

signals:

public slots:

private:
    void fill_thr_dlab_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_ier_dlab_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_iir_fcr_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_lcr_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_mcr_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_lsr_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_msr_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_spr_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_irda_csr_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_asr_details(const u_int32_t &value, const u_int32_t &new_value);

    bool is_offset_valid(const u_int32_t &offset) const;

    bool is_undef_changed(const u_int32_t &offset,
                          const u_int32_t &value,
                          const u_int32_t &new_value) const;

    // Device interface
private:
    QString get_register_name(const log_entry &entry) const;

    void fill_bits_details(const u_int32_t &offset, const u_int32_t &value,
                           const u_int32_t &new_value);

};

#endif // UARTDEV_H
