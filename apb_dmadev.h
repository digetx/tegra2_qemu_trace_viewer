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

#ifndef APB_DMADEV_H
#define APB_DMADEV_H

#include "device.h"

class Apb_dmaDev : public Device
{
    Q_OBJECT

public:
    explicit Apb_dmaDev(QObject *parent = 0);

    Apb_dmaDev(const QString name, u_int32_t base) : Device(name, base) {}

signals:

public slots:

private:
    void fill_command_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_status_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_requestors_tx_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_requestors_rx_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_cntrl_reg_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_irq_sta_cpu_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_irq_sta_cop_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_irq_mask_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_irq_mask_set_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_irq_mask_clr_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_trig_reg_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_channel_0_csr_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_channel_0_sta_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_channel_0_ahb_ptr_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_channel_0_ahb_seq_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_channel_0_apb_ptr_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_channel_0_apb_seq_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_channel_1_csr_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_channel_1_sta_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_channel_1_ahb_ptr_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_channel_1_ahb_seq_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_channel_1_apb_ptr_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_channel_1_apb_seq_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_channel_2_csr_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_channel_2_sta_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_channel_2_ahb_ptr_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_channel_2_ahb_seq_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_channel_2_apb_ptr_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_channel_2_apb_seq_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_channel_3_csr_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_channel_3_sta_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_channel_3_ahb_ptr_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_channel_3_ahb_seq_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_channel_3_apb_ptr_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_channel_3_apb_seq_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_channel_4_csr_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_channel_4_sta_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_channel_4_ahb_ptr_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_channel_4_ahb_seq_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_channel_4_apb_ptr_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_channel_4_apb_seq_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_channel_5_csr_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_channel_5_sta_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_channel_5_ahb_ptr_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_channel_5_ahb_seq_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_channel_5_apb_ptr_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_channel_5_apb_seq_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_channel_6_csr_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_channel_6_sta_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_channel_6_ahb_ptr_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_channel_6_ahb_seq_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_channel_6_apb_ptr_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_channel_6_apb_seq_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_channel_7_csr_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_channel_7_sta_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_channel_7_ahb_ptr_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_channel_7_ahb_seq_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_channel_7_apb_ptr_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_channel_7_apb_seq_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_channel_8_csr_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_channel_8_sta_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_channel_8_ahb_ptr_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_channel_8_ahb_seq_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_channel_8_apb_ptr_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_channel_8_apb_seq_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_channel_9_csr_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_channel_9_sta_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_channel_9_ahb_ptr_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_channel_9_ahb_seq_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_channel_9_apb_ptr_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_channel_9_apb_seq_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_channel_10_csr_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_channel_10_sta_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_channel_10_ahb_ptr_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_channel_10_ahb_seq_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_channel_10_apb_ptr_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_channel_10_apb_seq_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_channel_11_csr_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_channel_11_sta_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_channel_11_ahb_ptr_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_channel_11_ahb_seq_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_channel_11_apb_ptr_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_channel_11_apb_seq_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_channel_12_csr_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_channel_12_sta_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_channel_12_ahb_ptr_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_channel_12_ahb_seq_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_channel_12_apb_ptr_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_channel_12_apb_seq_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_channel_13_csr_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_channel_13_sta_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_channel_13_ahb_ptr_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_channel_13_ahb_seq_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_channel_13_apb_ptr_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_channel_13_apb_seq_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_channel_14_csr_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_channel_14_sta_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_channel_14_ahb_ptr_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_channel_14_ahb_seq_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_channel_14_apb_ptr_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_channel_14_apb_seq_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_channel_15_csr_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_channel_15_sta_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_channel_15_ahb_ptr_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_channel_15_ahb_seq_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_channel_15_apb_ptr_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_channel_15_apb_seq_details(const u_int32_t &value, const u_int32_t &new_value);

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

#endif // APB_DMADEV_H
