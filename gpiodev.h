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

#ifndef GPIODEV_H
#define GPIODEV_H

#include "device.h"

class GpioDev : public Device
{
    Q_OBJECT

public:
    explicit GpioDev(QObject *parent = 0);

    GpioDev(const QString name, u_int32_t base) : Device(name, base) {}

signals:

public slots:

private:
    void fill_gpio_cnf_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_gpio_oe_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_gpio_out_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_gpio_in_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_gpio_int_sta_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_gpio_int_enb_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_gpio_int_lvl_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_gpio_int_clr_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_gpio_msk_cnf_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_gpio_msk_oe_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_gpio_msk_out_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_gpio_msk_int_sta_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_gpio_msk_int_enb_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_gpio_msk_int_lvl_details(const u_int32_t &value, const u_int32_t &new_value);

    bool is_offset_valid(const u_int32_t &offset) const;

    bool is_undef_changed(const u_int32_t &, const u_int32_t &, const u_int32_t &) const
    {
        return false;
    }

    // Device interface
private:
    QString get_register_name(const log_entry &entry) const;

    void fill_bits_details(const u_int32_t &offset, const u_int32_t &value,
                           const u_int32_t &new_value);

};

#endif // GPIODEV_H
