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

#ifndef HOST1XDEV_H
#define HOST1XDEV_H

#include "device.h"

class Host1xDev : public Device
{
    Q_OBJECT

public:
    explicit Host1xDev(QObject *parent = 0);

    Host1xDev(const QString name, u_int32_t base) : Device(name, base) {}

signals:

public slots:

private:
    void fill_nv_class_host_incr_syncpt_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_nv_class_host_incr_syncpt_cntrl_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_nv_class_host_incr_syncpt_error_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_nv_class_host_wait_syncpt_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_nv_class_host_wait_syncpt_base_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_nv_class_host_wait_syncpt_incr_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_nv_class_host_load_syncpt_base_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_nv_class_host_incr_syncpt_base_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_nv_class_host_delay_usec_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_nv_class_host_tickcount_hi_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_nv_class_host_tickcount_lo_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_nv_class_host_tickctrl_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_nv_class_host_indctrl_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_nv_class_host_indoff2_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_nv_class_host_indoff2fb_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_nv_class_host_indoff_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_nv_class_host_indofffb_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_nv_class_host_inddata_details(const u_int32_t &value, const u_int32_t &new_value);


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

#endif // HOST1XDEV_H
