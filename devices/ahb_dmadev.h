/*
 * Copyright (c) 2014-2016 Dmitry Osipenko <digetx@gmail.com>
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

#ifndef AHB_DMADEV_H
#define AHB_DMADEV_H

#include "device.h"

class Ahb_dmaDev : public Device
{
    Q_OBJECT

    using Device::Device;

signals:

public slots:

private:
    void fill_cmd_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_sta_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_tx_req_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_counter_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_irq_sta_cpu_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_irq_sta_cop_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_irq_mask_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_irq_mask_set_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_irq_mask_clr_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_rdwr_coherency_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_test_bus_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_ppcs_mccif_fifoctrl_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_timeout_wcoal_ppcs_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_ahbdmachan_channel_0_csr_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_ahbdmachan_channel_0_sta_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_ahbdmachan_channel_0_ahb_ptr_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_ahbdmachan_channel_0_ahb_seq_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_ahbdmachan_channel_0_xmb_ptr_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_ahbdmachan_channel_0_xmb_seq_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_ahbdmachan_channel_1_csr_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_ahbdmachan_channel_1_sta_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_ahbdmachan_channel_1_ahb_ptr_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_ahbdmachan_channel_1_ahb_seq_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_ahbdmachan_channel_1_xmb_ptr_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_ahbdmachan_channel_1_xmb_seq_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_ahbdmachan_channel_2_csr_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_ahbdmachan_channel_2_sta_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_ahbdmachan_channel_2_ahb_ptr_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_ahbdmachan_channel_2_ahb_seq_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_ahbdmachan_channel_2_xmb_ptr_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_ahbdmachan_channel_2_xmb_seq_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_ahbdmachan_channel_3_csr_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_ahbdmachan_channel_3_sta_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_ahbdmachan_channel_3_ahb_ptr_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_ahbdmachan_channel_3_ahb_seq_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_ahbdmachan_channel_3_xmb_ptr_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_ahbdmachan_channel_3_xmb_seq_details(const u_int32_t &value, const u_int32_t &new_value);


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

#endif // AHB_DMADEV_H
