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

#ifndef APB_MISCDEV_H
#define APB_MISCDEV_H

#include "device.h"

class Apb_miscDev : public Device
{
    Q_OBJECT

public:
    explicit Apb_miscDev(QObject *parent = 0);

    Apb_miscDev(const QString name, u_int32_t base) : Device(name, base) {}

signals:

public slots:

private:
    void fill_pp_strapping_opt_a_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_pp_tristate_reg_a_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_pp_tristate_reg_b_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_pp_tristate_reg_c_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_pp_tristate_reg_d_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_pp_config_ctl_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_pp_misc_usb_otg_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_pp_usb_phy_param_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_pp_usb_phy_vbus_sensors_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_pp_usb_phy_vbus_wakeup_id_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_pp_usb_phy_alt_vbus_sts_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_pp_pin_mux_ctl_a_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_pp_pin_mux_ctl_b_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_pp_pin_mux_ctl_c_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_pp_pin_mux_ctl_d_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_pp_pin_mux_ctl_e_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_pp_pin_mux_ctl_f_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_pp_pin_mux_ctl_g_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_pp_pin_mux_ctl_h_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_pp_pullupdown_reg_a_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_pp_pullupdown_reg_b_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_pp_pullupdown_reg_c_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_pp_pullupdown_reg_d_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_pp_pullupdown_reg_e_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_pp_misc_usb_clk_rst_ctl_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_gp_modereg_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_gp_hidrev_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_gp_emu_revid_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_gp_transactor_scratch_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_gp_aocfg1padctrl_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_gp_aocfg2padctrl_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_gp_atcfg1padctrl_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_gp_atcfg2padctrl_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_gp_cdev1cfgpadctrl_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_gp_cdev2cfgpadctrl_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_gp_csuscfgpadctrl_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_gp_dap1cfgpadctrl_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_gp_dap2cfgpadctrl_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_gp_dap3cfgpadctrl_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_gp_dap4cfgpadctrl_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_gp_dbgcfgpadctrl_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_gp_lcdcfg1padctrl_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_gp_lcdcfg2padctrl_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_gp_sdio2cfgpadctrl_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_gp_sdio3cfgpadctrl_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_gp_spicfgpadctrl_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_gp_uaacfgpadctrl_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_gp_uabcfgpadctrl_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_gp_uart2cfgpadctrl_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_gp_uart3cfgpadctrl_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_gp_vicfg1padctrl_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_gp_vicfg2padctrl_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_gp_xm2cfgapadctrl_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_gp_xm2cfgcpadctrl_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_gp_xm2cfgdpadctrl_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_gp_xm2clkcfgpadctrl_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_gp_xm2comppadctrl_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_gp_xm2vttgenpadctrl_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_gp_padctl_dft_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_gp_sdio1cfgpadctrl_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_gp_xm2cfgcpadctrl2_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_gp_xm2cfgdpadctrl2_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_gp_crtcfgpadctrl_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_gp_ddccfgpadctrl_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_gp_gmacfgpadctrl_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_gp_gmbcfgpadctrl_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_gp_gmccfgpadctrl_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_gp_gmdcfgpadctrl_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_gp_gmecfgpadctrl_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_gp_owrcfgpadctrl_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_gp_uadcfgpadctrl_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_das_dap_ctrl_sel_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_das_dac_input_data_clk_sel_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_pp_misc_save_the_day_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_async_corepwrconfig_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_async_emcpaden_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_async_vclkctrl_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_async_tvdacvhsyncctrl_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_async_tvdaccntl_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_async_tvdacstatus_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_async_tvdacdinconfig_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_async_int_status_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_async_int_mask_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_async_int_polarity_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_async_int_type_select_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_das_dap_ctrl_sel_1_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_das_dap_ctrl_sel_2_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_das_dap_ctrl_sel_3_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_das_dap_ctrl_sel_4_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_das_dac_input_data_clk_sel_1_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_das_dac_input_data_clk_sel_2_details(const u_int32_t &value, const u_int32_t &new_value);

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

#endif // APB_MISCDEV_H
