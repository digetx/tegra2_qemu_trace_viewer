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

#ifndef SDHCIDEV_H
#define SDHCIDEV_H

#include "device.h"

class SdhciDev : public Device
{
    Q_OBJECT

    using Device::Device;

signals:

public slots:

private:
    void fill_system_address_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_block_size_block_count_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_argument_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_cmd_xfer_mode_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_response_r0_r1_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_response_r2_r3_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_response_r4_r5_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_response_r6_r7_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_buffer_data_port_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_present_state_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_power_control_host_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_sw_reset_timeout_ctrl_clock_control_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_interrupt_status_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_interrupt_status_enable_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_interrupt_signal_enable_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_auto_cmd12_err_status_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_capabilities_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_maximum_current_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_force_event_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_adma_err_status_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_adma_system_address_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_spi_interrupt_support_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_slot_interrupt_status_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_vendor_clock_cntrl_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_vendor_spi_cntrl_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_vendor_spi_intr_status_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_vendor_ceata_cntrl_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_vendor_boot_cntrl_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_vendor_boot_ack_timeout_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_vendor_boot_dat_timeout_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_vendor_debounce_count_details(const u_int32_t &value, const u_int32_t &new_value);

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

#endif // SDHCIDEV_H
