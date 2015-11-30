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

#ifndef ICTLR_TRIDEV_H
#define ICTLR_TRIDEV_H

#include "device.h"

class Ictlr_triDev : public Device
{
    Q_OBJECT

    using Device::Device;

signals:

public slots:

private:
    void fill_tri_ictlr_virq_cpu_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_tri_ictlr_virq_cop_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_tri_ictlr_vfiq_cpu_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_tri_ictlr_vfiq_cop_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_tri_ictlr_isr_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_tri_ictlr_fir_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_tri_ictlr_fir_set_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_tri_ictlr_fir_clr_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_tri_ictlr_cpu_ier_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_tri_ictlr_cpu_ier_set_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_tri_ictlr_cpu_ier_clr_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_tri_ictlr_cpu_iep_class_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_tri_ictlr_cop_ier_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_tri_ictlr_cop_ier_set_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_tri_ictlr_cop_ier_clr_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_tri_ictlr_cop_iep_class_details(const u_int32_t &value, const u_int32_t &new_value);


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

#endif // ICTLR_TRIDEV_H
