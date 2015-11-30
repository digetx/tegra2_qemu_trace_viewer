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

#ifndef EVPDEV_H
#define EVPDEV_H

#include "device.h"

class EvpDev : public Device
{
    Q_OBJECT

    using Device::Device;

signals:

public slots:

private:
    void fill_evp_reset_vector_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_evp_undef_vector_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_evp_swi_vector_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_evp_prefetch_abort_vector_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_evp_data_abort_vector_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_evp_rsvd_vector_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_evp_irq_vector_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_evp_fiq_vector_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_evp_irq_sts_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_evp_pri_irq_sts_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_evp_fiq_sts_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_evp_pri_fiq_sts_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_evp_pri_irq_num_0_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_evp_pri_irq_vec_0_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_evp_pri_irq_num_1_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_evp_pri_irq_vec_1_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_evp_pri_irq_num_2_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_evp_pri_irq_vec_2_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_evp_pri_irq_num_3_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_evp_pri_irq_vec_3_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_evp_pri_irq_num_4_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_evp_pri_irq_vec_4_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_evp_pri_irq_num_5_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_evp_pri_irq_vec_5_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_evp_pri_irq_num_6_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_evp_pri_irq_vec_6_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_evp_pri_irq_num_7_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_evp_pri_irq_vec_7_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_evp_pri_fiq_num_0_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_evp_pri_fiq_vec_0_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_evp_pri_fiq_num_1_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_evp_pri_fiq_vec_1_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_evp_pri_fiq_num_2_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_evp_pri_fiq_vec_2_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_evp_pri_fiq_num_3_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_evp_pri_fiq_vec_3_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_evp_cpu_reset_vector_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_evp_cpu_undef_vector_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_evp_cpu_swi_vector_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_evp_cpu_prefetch_abort_vector_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_evp_cpu_data_abort_vector_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_evp_cpu_rsvd_vector_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_evp_cpu_irq_vector_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_evp_cpu_fiq_vector_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_evp_cpu_irq_sts_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_evp_cpu_pri_irq_sts_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_evp_cpu_fiq_sts_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_evp_cpu_pri_fiq_sts_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_evp_cpu_pri_irq_num_0_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_evp_cpu_pri_irq_vec_0_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_evp_cpu_pri_irq_num_1_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_evp_cpu_pri_irq_vec_1_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_evp_cpu_pri_irq_num_2_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_evp_cpu_pri_irq_vec_2_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_evp_cpu_pri_irq_num_3_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_evp_cpu_pri_irq_vec_3_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_evp_cpu_pri_irq_num_4_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_evp_cpu_pri_irq_vec_4_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_evp_cpu_pri_irq_num_5_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_evp_cpu_pri_irq_vec_5_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_evp_cpu_pri_irq_num_6_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_evp_cpu_pri_irq_vec_6_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_evp_cpu_pri_irq_num_7_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_evp_cpu_pri_irq_vec_7_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_evp_cpu_pri_fiq_num_0_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_evp_cpu_pri_fiq_vec_0_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_evp_cpu_pri_fiq_num_1_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_evp_cpu_pri_fiq_vec_1_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_evp_cpu_pri_fiq_num_2_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_evp_cpu_pri_fiq_vec_2_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_evp_cpu_pri_fiq_num_3_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_evp_cpu_pri_fiq_vec_3_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_evp_cop_reset_vector_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_evp_cop_undef_vector_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_evp_cop_swi_vector_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_evp_cop_prefetch_abort_vector_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_evp_cop_data_abort_vector_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_evp_cop_rsvd_vector_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_evp_cop_irq_vector_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_evp_cop_fiq_vector_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_evp_cop_irq_sts_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_evp_cop_pri_irq_sts_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_evp_cop_fiq_sts_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_evp_cop_pri_fiq_sts_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_evp_cop_pri_irq_num_0_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_evp_cop_pri_irq_vec_0_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_evp_cop_pri_irq_num_1_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_evp_cop_pri_irq_vec_1_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_evp_cop_pri_irq_num_2_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_evp_cop_pri_irq_vec_2_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_evp_cop_pri_irq_num_3_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_evp_cop_pri_irq_vec_3_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_evp_cop_pri_irq_num_4_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_evp_cop_pri_irq_vec_4_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_evp_cop_pri_irq_num_5_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_evp_cop_pri_irq_vec_5_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_evp_cop_pri_irq_num_6_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_evp_cop_pri_irq_vec_6_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_evp_cop_pri_irq_num_7_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_evp_cop_pri_irq_vec_7_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_evp_cop_pri_fiq_num_0_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_evp_cop_pri_fiq_vec_0_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_evp_cop_pri_fiq_num_1_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_evp_cop_pri_fiq_vec_1_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_evp_cop_pri_fiq_num_2_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_evp_cop_pri_fiq_vec_2_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_evp_cop_pri_fiq_num_3_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_evp_cop_pri_fiq_vec_3_details(const u_int32_t &value, const u_int32_t &new_value);


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

#endif // EVPDEV_H
