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

#ifndef CARDEV_H
#define CARDEV_H

#include "device.h"

class CarDev : public Device
{
    Q_OBJECT

public:
    explicit CarDev(QObject *parent = 0);

    CarDev(const QString name, u_int32_t base) : Device(name, base) {}

signals:

public slots:

private:
    void fill_rst_source_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_rst_devices_l_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_rst_devices_h_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_rst_devices_u_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_clk_out_enb_l_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_clk_out_enb_h_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_clk_out_enb_u_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_cclk_burst_policy_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_super_cclk_divider_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_sclk_burst_policy_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_super_sclk_divider_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_clk_system_rate_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_prog_dly_clk_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_audio_sync_clk_rate_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_cop_clk_skip_policy_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_clk_mask_arm_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_misc_clk_enb_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_clk_cpu_cmplx_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_osc_ctrl_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_pll_lfsr_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_osc_freq_det_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_osc_freq_det_status_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_pllc_base_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_pllc_out_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_pllc_misc_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_pllm_base_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_pllm_out_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_pllm_misc_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_pllp_base_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_pllp_outa_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_pllp_outb_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_pllp_misc_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_plla_base_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_plla_out_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_plla_misc_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_pllu_base_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_pllu_misc_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_plld_base_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_plld_misc_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_pllx_base_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_pllx_misc_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_plle_base_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_plle_misc_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_clk_source_i2s1_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_clk_source_i2s2_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_clk_source_spdif_out_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_clk_source_spdif_in_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_clk_source_pwm_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_clk_source_spi1_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_clk_source_spi22_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_clk_source_spi3_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_clk_source_xio_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_clk_source_i2c1_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_clk_source_dvc_i2c_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_clk_source_twc_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_clk_source_sbc1_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_clk_source_disp1_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_clk_source_disp2_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_clk_source_cve_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_clk_source_ide_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_clk_source_vi_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_clk_source_sdmmc1_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_clk_source_sdmmc2_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_clk_source_g3d_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_clk_source_g2d_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_clk_source_ndflash_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_clk_source_sdmmc4_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_clk_source_vfir_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_clk_source_epp_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_clk_source_mpe_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_clk_source_mipi_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_clk_source_uart1_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_clk_source_uart2_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_clk_source_host1x_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_clk_source_tvo_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_clk_source_hdmi_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_clk_source_tvdac_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_clk_source_i2c2_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_clk_source_emc_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_clk_source_uart3_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_clk_source_vi_sensor_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_clk_source_spi4_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_clk_source_i2c3_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_clk_source_sdmmc3_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_clk_source_uart4_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_clk_source_uart5_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_clk_source_vde_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_clk_source_owr_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_clk_source_nor_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_clk_source_csite_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_clk_source_osc_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_rst_dev_l_set_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_rst_dev_l_clr_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_rst_dev_h_set_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_rst_dev_h_clr_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_rst_dev_u_set_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_rst_dev_u_clr_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_clk_enb_l_set_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_clk_enb_l_clr_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_clk_enb_h_set_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_clk_enb_h_clr_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_clk_enb_u_set_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_clk_enb_u_clr_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_rst_cpu_cmplx_set_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_rst_cpu_cmplx_clr_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_clk_source_la_details(const u_int32_t &value, const u_int32_t &new_value);

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

#endif // CARDEV_H
