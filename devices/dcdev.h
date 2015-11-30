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

#ifndef DCDEV_H
#define DCDEV_H

#include "device.h"

class DcDev : public Device
{
    Q_OBJECT

    using Device::Device;

signals:

public slots:

private:
    void fill_cmd_general_incr_syncpt_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_cmd_general_incr_syncpt_cntrl_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_cmd_general_incr_syncpt_error_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_cmd_win_a_incr_syncpt_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_cmd_win_a_incr_syncpt_cntrl_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_cmd_win_a_incr_syncpt_error_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_cmd_win_b_incr_syncpt_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_cmd_win_b_incr_syncpt_cntrl_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_cmd_win_b_incr_syncpt_error_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_cmd_win_c_incr_syncpt_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_cmd_win_c_incr_syncpt_cntrl_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_cmd_win_c_incr_syncpt_error_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_cmd_cont_syncpt_vsync_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_cmd_ctxsw_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_cmd_display_command_option0_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_cmd_display_command_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_cmd_signal_raise_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_cmd_display_power_control_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_cmd_int_status_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_cmd_int_mask_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_cmd_int_enable_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_cmd_int_type_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_cmd_int_polarity_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_cmd_signal_raise1_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_cmd_signal_raise2_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_cmd_signal_raise3_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_cmd_state_access_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_cmd_state_control_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_cmd_display_window_header_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_cmd_reg_act_control_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_com_crc_control_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_com_crc_checksum_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_com_pin_output_enable0_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_com_pin_output_enable1_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_com_pin_output_enable2_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_com_pin_output_enable3_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_com_pin_output_polarity0_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_com_pin_output_polarity1_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_com_pin_output_polarity2_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_com_pin_output_polarity3_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_com_pin_output_data0_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_com_pin_output_data1_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_com_pin_output_data2_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_com_pin_output_data3_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_com_pin_input_enable0_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_com_pin_input_enable1_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_com_pin_input_enable2_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_com_pin_input_enable3_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_com_pin_input_data0_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_com_pin_input_data1_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_com_pin_output_select0_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_com_pin_output_select1_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_com_pin_output_select2_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_com_pin_output_select3_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_com_pin_output_select4_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_com_pin_output_select5_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_com_pin_output_select6_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_com_pin_misc_control_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_com_pm0_control_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_com_pm0_duty_cycle_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_com_pm1_control_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_com_pm1_duty_cycle_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_com_spi_control_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_com_spi_start_byte_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_com_hspi_write_data_ab_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_com_hspi_write_data_cd_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_com_hspi_cs_dc_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_com_scratch_register_a_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_com_scratch_register_b_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_com_gpio_ctrl_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_com_gpio_debounce_counter_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_com_crc_checksum_latched_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_disp_disp_signal_options0_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_disp_disp_signal_options1_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_disp_disp_win_options_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_disp_mem_high_priority_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_disp_mem_high_priority_timer_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_disp_disp_timing_options_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_disp_ref_to_sync_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_disp_sync_width_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_disp_back_porch_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_disp_disp_active_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_disp_front_porch_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_disp_h_pulse0_control_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_disp_h_pulse0_position_a_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_disp_h_pulse0_position_b_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_disp_h_pulse0_position_c_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_disp_h_pulse0_position_d_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_disp_h_pulse1_control_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_disp_h_pulse1_position_a_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_disp_h_pulse1_position_b_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_disp_h_pulse1_position_c_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_disp_h_pulse1_position_d_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_disp_h_pulse2_control_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_disp_h_pulse2_position_a_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_disp_h_pulse2_position_b_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_disp_h_pulse2_position_c_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_disp_h_pulse2_position_d_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_disp_v_pulse0_control_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_disp_v_pulse0_position_a_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_disp_v_pulse0_position_b_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_disp_v_pulse0_position_c_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_disp_v_pulse1_control_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_disp_v_pulse1_position_a_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_disp_v_pulse1_position_b_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_disp_v_pulse1_position_c_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_disp_v_pulse2_control_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_disp_v_pulse2_position_a_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_disp_v_pulse3_control_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_disp_v_pulse3_position_a_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_disp_m0_control_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_disp_m1_control_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_disp_di_control_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_disp_pp_control_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_disp_pp_select_a_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_disp_pp_select_b_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_disp_pp_select_c_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_disp_pp_select_d_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_disp_disp_clock_control_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_disp_disp_interface_control_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_disp_disp_color_control_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_disp_shift_clock_options_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_disp_data_enable_options_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_disp_serial_interface_options_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_disp_lcd_spi_options_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_disp_border_color_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_disp_color_key0_lower_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_disp_color_key0_upper_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_disp_color_key1_lower_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_disp_color_key1_upper_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_disp_cursor_foreground_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_disp_cursor_background_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_disp_cursor_start_addr_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_disp_cursor_start_addr_ns_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_disp_cursor_position_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_disp_cursor_position_ns_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_disp_init_seq_control_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_disp_spi_init_seq_data_a_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_disp_spi_init_seq_data_b_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_disp_spi_init_seq_data_c_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_disp_spi_init_seq_data_d_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_disp_dc_mccif_fifoctrl_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_disp_mccif_display0a_hyst_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_disp_mccif_display0b_hyst_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_disp_mccif_display0c_hyst_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_disp_mccif_display1b_hyst_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_disp_dac_crt_ctrl_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_disp_disp_misc_control_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_winc_a_color_palette_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_winc_a_palette_color_ext_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_win_a_win_options_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_win_a_byte_swap_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_win_a_buffer_control_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_win_a_color_depth_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_win_a_position_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_win_a_size_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_win_a_prescaled_size_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_win_a_h_initial_dda_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_win_a_v_initial_dda_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_win_a_dda_increment_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_win_a_line_stride_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_win_a_buf_stride_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_win_a_buffer_addr_mode_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_win_a_dv_control_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_win_a_blend_nokey_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_win_a_blend_1win_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_win_a_blend_2win_b_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_win_a_blend_2win_c_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_win_a_blend_3win_bc_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_win_a_hp_fetch_control_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_winbuf_a_start_addr_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_winbuf_a_start_addr_ns_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_winbuf_a_addr_h_offset_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_winbuf_a_addr_h_offset_ns_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_winbuf_a_addr_v_offset_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_winbuf_a_addr_v_offset_ns_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_winbuf_a_uflow_status_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_winc_b_color_palette_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_winc_b_palette_color_ext_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_winc_b_h_filter_p00_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_winc_b_h_filter_p01_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_winc_b_h_filter_p02_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_winc_b_h_filter_p03_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_winc_b_h_filter_p04_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_winc_b_h_filter_p05_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_winc_b_h_filter_p06_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_winc_b_h_filter_p07_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_winc_b_h_filter_p08_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_winc_b_h_filter_p09_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_winc_b_h_filter_p0a_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_winc_b_h_filter_p0b_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_winc_b_h_filter_p0c_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_winc_b_h_filter_p0d_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_winc_b_h_filter_p0e_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_winc_b_h_filter_p0f_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_winc_b_csc_yof_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_winc_b_csc_kyrgb_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_winc_b_csc_kur_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_winc_b_csc_kvr_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_winc_b_csc_kug_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_winc_b_csc_kvg_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_winc_b_csc_kub_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_winc_b_csc_kvb_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_winc_b_v_filter_p00_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_winc_b_v_filter_p01_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_winc_b_v_filter_p02_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_winc_b_v_filter_p03_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_winc_b_v_filter_p04_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_winc_b_v_filter_p05_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_winc_b_v_filter_p06_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_winc_b_v_filter_p07_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_winc_b_v_filter_p08_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_winc_b_v_filter_p09_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_winc_b_v_filter_p0a_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_winc_b_v_filter_p0b_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_winc_b_v_filter_p0c_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_winc_b_v_filter_p0d_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_winc_b_v_filter_p0e_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_winc_b_v_filter_p0f_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_win_b_win_options_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_win_b_byte_swap_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_win_b_buffer_control_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_win_b_color_depth_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_win_b_position_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_win_b_size_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_win_b_prescaled_size_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_win_b_h_initial_dda_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_win_b_v_initial_dda_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_win_b_dda_increment_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_win_b_line_stride_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_win_b_buf_stride_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_win_b_uv_buf_stride_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_win_b_buffer_addr_mode_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_win_b_dv_control_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_win_b_blend_nokey_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_win_b_blend_1win_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_win_b_blend_2win_a_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_win_b_blend_2win_c_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_win_b_blend_3win_ac_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_win_b_hp_fetch_control_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_winbuf_b_start_addr_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_winbuf_b_start_addr_ns_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_winbuf_b_start_addr_u_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_winbuf_b_start_addr_u_ns_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_winbuf_b_start_addr_v_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_winbuf_b_start_addr_v_ns_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_winbuf_b_addr_h_offset_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_winbuf_b_addr_h_offset_ns_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_winbuf_b_addr_v_offset_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_winbuf_b_addr_v_offset_ns_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_winbuf_b_uflow_status_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_winc_c_color_palette_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_winc_c_palette_color_ext_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_winc_c_h_filter_p00_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_winc_c_h_filter_p01_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_winc_c_h_filter_p02_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_winc_c_h_filter_p03_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_winc_c_h_filter_p04_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_winc_c_h_filter_p05_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_winc_c_h_filter_p06_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_winc_c_h_filter_p07_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_winc_c_h_filter_p08_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_winc_c_h_filter_p09_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_winc_c_h_filter_p0a_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_winc_c_h_filter_p0b_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_winc_c_h_filter_p0c_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_winc_c_h_filter_p0d_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_winc_c_h_filter_p0e_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_winc_c_h_filter_p0f_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_winc_c_csc_yof_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_winc_c_csc_kyrgb_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_winc_c_csc_kur_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_winc_c_csc_kvr_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_winc_c_csc_kug_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_winc_c_csc_kvg_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_winc_c_csc_kub_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_winc_c_csc_kvb_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_win_c_win_options_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_win_c_byte_swap_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_win_c_buffer_control_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_win_c_color_depth_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_win_c_position_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_win_c_size_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_win_c_prescaled_size_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_win_c_h_initial_dda_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_win_c_v_initial_dda_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_win_c_dda_increment_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_win_c_line_stride_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_win_c_buf_stride_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_win_c_uv_buf_stride_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_win_c_buffer_addr_mode_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_win_c_dv_control_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_win_c_blend_nokey_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_win_c_blend_1win_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_win_c_blend_2win_a_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_win_c_blend_2win_b_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_win_c_blend_3win_ab_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_win_c_hp_fetch_control_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_winbuf_c_start_addr_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_winbuf_c_start_addr_ns_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_winbuf_c_start_addr_u_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_winbuf_c_start_addr_u_ns_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_winbuf_c_start_addr_v_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_winbuf_c_start_addr_v_ns_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_winbuf_c_addr_h_offset_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_winbuf_c_addr_h_offset_ns_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_winbuf_c_addr_v_offset_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_winbuf_c_addr_v_offset_ns_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_winbuf_c_uflow_status_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_disp_sd_control_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_disp_sd_csc_coeff_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_disp_sd_lut_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_disp_sd_lut_1_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_disp_sd_lut_2_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_disp_sd_lut_3_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_disp_sd_lut_4_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_disp_sd_lut_5_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_disp_sd_lut_6_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_disp_sd_lut_7_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_disp_sd_lut_8_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_disp_sd_flicker_control_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_disp_sd_pixel_count_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_disp_sd_histogram_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_disp_sd_histogram_1_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_disp_sd_histogram_2_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_disp_sd_histogram_3_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_disp_sd_histogram_4_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_disp_sd_histogram_5_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_disp_sd_histogram_6_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_disp_sd_histogram_7_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_disp_sd_bl_parameters_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_disp_sd_bl_tf_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_disp_sd_bl_tf_1_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_disp_sd_bl_tf_2_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_disp_sd_bl_tf_3_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_disp_sd_bl_control_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_winc_b_color_palette_1_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_winc_b_color_palette_2_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_winc_b_color_palette_3_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_winc_b_color_palette_4_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_winc_b_color_palette_5_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_winc_b_color_palette_6_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_winc_b_color_palette_7_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_winc_b_color_palette_8_details(const u_int32_t &value, const u_int32_t &new_value);
    void fill_winc_b_color_palette_9_details(const u_int32_t &value, const u_int32_t &new_value);

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

#endif // DCDEV_H
