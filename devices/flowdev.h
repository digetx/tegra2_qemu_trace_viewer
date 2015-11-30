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

#ifndef FLOWDEV_H
#define FLOWDEV_H

#include "device.h"

class FlowDev : public Device
{
    Q_OBJECT

    using Device::Device;

signals:

public slots:

private:
    void fill_halt_cpu_events_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_halt_cop_events_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_cpu_csr_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_cop_csr_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_xrq_events_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_halt_cpu1_events_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_cpu1_csr_details(const u_int32_t &value, const u_int32_t &new_value);

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

#endif // FLOWDEV_H
