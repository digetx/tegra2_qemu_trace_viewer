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

#include "cardev.h"

#include <QDebug>

CarDev::CarDev(QObject *parent) :
    Device(parent)
{
}

#define RST_SOURCE_OFFSET 0x0
#define RST_SOURCE_UNDEFMASK 0xFFFFC0C8
union rst_source_u {
    struct {
        unsigned int wdt_cpu_rst_en:1;      /* Enable Watch Dog Timer reset for CPU */
        unsigned int wdt_cop_rst_en:1;      /* Enable Watch Dog Timer reset for COP */
        unsigned int wdt_sys_rst_en:1;      /* Enable Watch Dog Timer reset for system */
        unsigned int undefined_bit_3:1;
        unsigned int wdt_sel:1;             /* Watch Dog Timer Select */
        unsigned int wdt_en:1;              /* Enable Watch Dog Timer (Dead Man Timer)  0 = DISABLE 1 = ENABLE */
        unsigned int undefined_bits_6_7:2;
        unsigned int wdt_cpu_rst_sta:1;     /* CPU reset by watch dog timer (RO) */
        unsigned int swr_cpu_rst_sta:1;     /* CPU reset by SW (RO) */
        unsigned int wdt_cop_rst_sta:1;     /* COP reset by watch dog timer (RO) */
        unsigned int swr_cop_rst_sta:1;     /* COP reset by SW (RO) */
        unsigned int wdt_sys_rst_sta:1;     /* System reset by watch dog timer (RO) */
        unsigned int swr_sys_rst_sta:1;     /* System reset by SW (RO) */
        unsigned int undefined_bits_14_31:18;
    };

    u_int32_t reg32;
};

void CarDev::fill_rst_source_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const rst_source_u old_value_t = { .reg32 = value };
    const rst_source_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: wdt_cpu_rst_en:1",
              "Enable Watch Dog Timer reset for CPU",
              1, old_value_t.wdt_cpu_rst_en, new_value_t.wdt_cpu_rst_en };
    m_bit_details_model.bits.append(entry);
    entry = { "01: wdt_cop_rst_en:1",
              "Enable Watch Dog Timer reset for COP",
              1, old_value_t.wdt_cop_rst_en, new_value_t.wdt_cop_rst_en };
    m_bit_details_model.bits.append(entry);
    entry = { "02: wdt_sys_rst_en:1",
              "Enable Watch Dog Timer reset for system",
              1, old_value_t.wdt_sys_rst_en, new_value_t.wdt_sys_rst_en };
    m_bit_details_model.bits.append(entry);
    entry = { "03: undefined_bit_3:1", "", 1, old_value_t.undefined_bit_3, new_value_t.undefined_bit_3 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: wdt_sel:1",
              "Watch Dog Timer Select",
              1, old_value_t.wdt_sel, new_value_t.wdt_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "05: wdt_en:1",
              "Enable Watch Dog Timer (Dead Man Timer) \n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.wdt_en, new_value_t.wdt_en };
    m_bit_details_model.bits.append(entry);
    entry = { "06: undefined_bits_6_7:2", "", 2, old_value_t.undefined_bits_6_7, new_value_t.undefined_bits_6_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: wdt_cpu_rst_sta:1",
              "CPU reset by watch dog timer (RO)",
              1, old_value_t.wdt_cpu_rst_sta, new_value_t.wdt_cpu_rst_sta };
    m_bit_details_model.bits.append(entry);
    entry = { "09: swr_cpu_rst_sta:1",
              "CPU reset by SW (RO)",
              1, old_value_t.swr_cpu_rst_sta, new_value_t.swr_cpu_rst_sta };
    m_bit_details_model.bits.append(entry);
    entry = { "10: wdt_cop_rst_sta:1",
              "COP reset by watch dog timer (RO)",
              1, old_value_t.wdt_cop_rst_sta, new_value_t.wdt_cop_rst_sta };
    m_bit_details_model.bits.append(entry);
    entry = { "11: swr_cop_rst_sta:1",
              "COP reset by SW (RO)",
              1, old_value_t.swr_cop_rst_sta, new_value_t.swr_cop_rst_sta };
    m_bit_details_model.bits.append(entry);
    entry = { "12: wdt_sys_rst_sta:1",
              "System reset by watch dog timer (RO)",
              1, old_value_t.wdt_sys_rst_sta, new_value_t.wdt_sys_rst_sta };
    m_bit_details_model.bits.append(entry);
    entry = { "13: swr_sys_rst_sta:1",
              "System reset by SW (RO)",
              1, old_value_t.swr_sys_rst_sta, new_value_t.swr_sys_rst_sta };
    m_bit_details_model.bits.append(entry);
    entry = { "14: undefined_bits_14_31:18", "", 18, old_value_t.undefined_bits_14_31, new_value_t.undefined_bits_14_31 };
    m_bit_details_model.bits.append(entry);
}

#define RST_DEVICES_L_OFFSET 0x4
#define RST_DEVICES_L_UNDEFMASK 0x40000000
union rst_devices_l_u {
    struct {
        unsigned int swr_cpu_rst:1;         /* Write 1 to force CPU Reset Signal. SW needs to clear this bit when done. 0 = DISABLE 1 = ENABLE */
        unsigned int swr_cop_rst:1;         /* Write 1 to force COP Reset Signal. SW needs to clear this bit when done. 0 = DISABLE 1 = ENABLE */
        unsigned int swr_trig_sys_rst:1;    /* Write 1 to pulse System Reset Signal. HW clears this bit 0 = DISABLE 1 = ENABLE */
        unsigned int swr_ac97_rst:1;        /* Reset AC97 Controller 0 = DISABLE 1 = ENABLE */
        unsigned int swr_rtc_rst:1;         /* Reset RTC Controller */
        unsigned int swr_tmr_rst:1;         /* Reset Timer Controller 0 = DISABLE 1 = ENABLE */
        unsigned int swr_uart1_rst:1;       /* Reset UART1 Controller  0 = DISABLE 1 = ENABLE */
        unsigned int swr_uart2_rst:1;       /* Reset UART2/VFIR Controller 0 = DISABLE 1 = ENABLE */
        unsigned int swr_gpio_rst:1;        /* Reset GPIO Controller 0 = DISABLE 1 = ENABLE */
        unsigned int swr_sdmmc2_rst:1;      /* Reset SDMMC2 Controller 0 = DISABLE 1 = ENABLE */
        unsigned int swr_spdif_rst:1;       /* Reset SPDIF Controller 0 = DISABLE 1 = ENABLE */
        unsigned int swr_i2s1_rst:1;        /* Reset I2S 1 Controller 0 = DISABLE 1 = ENABLE */
        unsigned int swr_i2c1_rst:1;        /* Reset I2C1 Controller 0 = DISABLE 1 = ENABLE */
        unsigned int swr_ndflash_rst:1;     /* Reset NAND flash controller. 0 = DISABLE 1 = ENABLE */
        unsigned int swr_sdmmc1_rst:1;      /* Reset SDMMC1 controller. 0 = DISABLE 1 = ENABLE */
        unsigned int swr_sdmmc4_rst:1;      /* Reset SDMMC4 controller. 0 = DISABLE 1 = ENABLE */
        unsigned int swr_twc_rst:1;         /* Reset Three Wire Controller 0 = DISABLE 1 = ENABLE */
        unsigned int swr_pwm_rst:1;         /* Reset Pulse Width Modulator 0 = DISABLE 1 = ENABLE */
        unsigned int swr_i2s2_rst:1;        /* Reset I2S 2 Controller 0 = DISABLE 1 = ENABLE */
        unsigned int swr_epp_rst:1;         /* Reset EPP controller. 0 = DISABLE 1 = ENABLE */
        unsigned int swr_vi_rst:1;          /* Reset VI controller. 0 = DISABLE 1 = ENABLE */
        unsigned int swr_2d_rst:1;          /* Reset 2D graphics engine controller. 0 = DISABLE 1 = ENABLE */
        unsigned int swr_usbd_rst:1;        /* Reset USB controller 0 = DISABLE 1 = ENABLE */
        unsigned int swr_isp_rst:1;         /* Reset ISP controller. 0 = DISABLE 1 = ENABLE */
        unsigned int swr_3d_rst:1;          /* Reset 3D controller. 0 = DISABLE 1 = ENABLE */
        unsigned int swr_ide_rst:1;         /* Reset IDE controller. 0 = DISABLE 1 = ENABLE */
        unsigned int swr_disp2_rst:1;       /* Reset DISP2 controller. 0 = DISABLE 1 = ENABLE */
        unsigned int swr_disp1_rst:1;       /* Reset DISP1 controller. 0 = DISABLE 1 = ENABLE */
        unsigned int swr_host1x_rst:1;      /* Reset HOST1X. 0 = DISABLE 1 = ENABLE */
        unsigned int swr_vcp_rst:1;         /* Reset vector co-processor. 0 = DISABLE 1 = ENABLE */
        unsigned int undefined_bit_30:1;
        unsigned int swr_cache2_rst:1;      /* Reset COP cache controller. 0 = DISABLE 1 = ENABLE */
    };

    u_int32_t reg32;
};

void CarDev::fill_rst_devices_l_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const rst_devices_l_u old_value_t = { .reg32 = value };
    const rst_devices_l_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: swr_cpu_rst:1",
              "Write 1 to force CPU Reset Signal. SW needs to clear this bit when done.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.swr_cpu_rst, new_value_t.swr_cpu_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "01: swr_cop_rst:1",
              "Write 1 to force COP Reset Signal. SW needs to clear this bit when done.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.swr_cop_rst, new_value_t.swr_cop_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "02: swr_trig_sys_rst:1",
              "Write 1 to pulse System Reset Signal. HW clears this bit\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.swr_trig_sys_rst, new_value_t.swr_trig_sys_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "03: swr_ac97_rst:1",
              "Reset AC97 Controller\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.swr_ac97_rst, new_value_t.swr_ac97_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "04: swr_rtc_rst:1",
              "Reset RTC Controller",
              1, old_value_t.swr_rtc_rst, new_value_t.swr_rtc_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "05: swr_tmr_rst:1",
              "Reset Timer Controller\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.swr_tmr_rst, new_value_t.swr_tmr_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "06: swr_uart1_rst:1",
              "Reset UART1 Controller \n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.swr_uart1_rst, new_value_t.swr_uart1_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "07: swr_uart2_rst:1",
              "Reset UART2/VFIR Controller\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.swr_uart2_rst, new_value_t.swr_uart2_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "08: swr_gpio_rst:1",
              "Reset GPIO Controller\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.swr_gpio_rst, new_value_t.swr_gpio_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "09: swr_sdmmc2_rst:1",
              "Reset SDMMC2 Controller\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.swr_sdmmc2_rst, new_value_t.swr_sdmmc2_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "10: swr_spdif_rst:1",
              "Reset SPDIF Controller\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.swr_spdif_rst, new_value_t.swr_spdif_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "11: swr_i2s1_rst:1",
              "Reset I2S 1 Controller\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.swr_i2s1_rst, new_value_t.swr_i2s1_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "12: swr_i2c1_rst:1",
              "Reset I2C1 Controller\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.swr_i2c1_rst, new_value_t.swr_i2c1_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "13: swr_ndflash_rst:1",
              "Reset NAND flash controller.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.swr_ndflash_rst, new_value_t.swr_ndflash_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "14: swr_sdmmc1_rst:1",
              "Reset SDMMC1 controller.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.swr_sdmmc1_rst, new_value_t.swr_sdmmc1_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "15: swr_sdmmc4_rst:1",
              "Reset SDMMC4 controller.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.swr_sdmmc4_rst, new_value_t.swr_sdmmc4_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "16: swr_twc_rst:1",
              "Reset Three Wire Controller\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.swr_twc_rst, new_value_t.swr_twc_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "17: swr_pwm_rst:1",
              "Reset Pulse Width Modulator\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.swr_pwm_rst, new_value_t.swr_pwm_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "18: swr_i2s2_rst:1",
              "Reset I2S 2 Controller\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.swr_i2s2_rst, new_value_t.swr_i2s2_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "19: swr_epp_rst:1",
              "Reset EPP controller.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.swr_epp_rst, new_value_t.swr_epp_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "20: swr_vi_rst:1",
              "Reset VI controller.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.swr_vi_rst, new_value_t.swr_vi_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "21: swr_2d_rst:1",
              "Reset 2D graphics engine controller.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.swr_2d_rst, new_value_t.swr_2d_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "22: swr_usbd_rst:1",
              "Reset USB controller\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.swr_usbd_rst, new_value_t.swr_usbd_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "23: swr_isp_rst:1",
              "Reset ISP controller.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.swr_isp_rst, new_value_t.swr_isp_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "24: swr_3d_rst:1",
              "Reset 3D controller.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.swr_3d_rst, new_value_t.swr_3d_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "25: swr_ide_rst:1",
              "Reset IDE controller.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.swr_ide_rst, new_value_t.swr_ide_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "26: swr_disp2_rst:1",
              "Reset DISP2 controller.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.swr_disp2_rst, new_value_t.swr_disp2_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "27: swr_disp1_rst:1",
              "Reset DISP1 controller.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.swr_disp1_rst, new_value_t.swr_disp1_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "28: swr_host1x_rst:1",
              "Reset HOST1X.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.swr_host1x_rst, new_value_t.swr_host1x_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "29: swr_vcp_rst:1",
              "Reset vector co-processor.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.swr_vcp_rst, new_value_t.swr_vcp_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "30: undefined_bit_30:1", "", 1, old_value_t.undefined_bit_30, new_value_t.undefined_bit_30 };
    m_bit_details_model.bits.append(entry);
    entry = { "31: swr_cache2_rst:1",
              "Reset COP cache controller.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.swr_cache2_rst, new_value_t.swr_cache2_rst };
    m_bit_details_model.bits.append(entry);
}

#define RST_DEVICES_H_OFFSET 0x8
#define RST_DEVICES_H_UNDEFMASK 0x01000008
union rst_devices_h_u {
    struct {
        unsigned int swr_mem_rst:1;         /* Reset MC. 0 = DISABLE 1 = ENABLE */
        unsigned int swr_ahbdma_rst:1;      /* Reset AHB-DMA. 0 = DISABLE 1 = ENABLE */
        unsigned int swr_apbdma_rst:1;      /* Reset APB-DMA. 0 = DISABLE 1 = ENABLE */
        unsigned int undefined_bit_3:1;
        unsigned int swr_kbc_rst:1;         /* Reset Keyboard controller. */
        unsigned int swr_stat_mon_rst:1;    /* Reset statistic monitor 0 = DISABLE 1 = ENABLE */
        unsigned int swr_pmc_rst:1;         /* Reset PMC controller. */
        unsigned int swr_fuse_rst:1;        /* Reset Fuse controller. */
        unsigned int swr_kfuse_rst:1;       /* Reset KFuse controller. 0 = DISABLE 1 = ENABLE */
        unsigned int swr_sbc1_rst:1;        /* Reset SBC 1 (SPI 1) Controller. 0 = DISABLE 1 = ENABLE */
        unsigned int swr_snor_rst:1;        /* Reset NOR Flash Controller. 0 = DISABLE 1 = ENABLE */
        unsigned int swr_spi1_rst:1;        /* Reset SPI 1 Controller 0 = DISABLE 1 = ENABLE */
        unsigned int swr_sbc2_rst:1;        /* Reset SBC 2 (SPI 2) Controller. 0 = DISABLE 1 = ENABLE */
        unsigned int swr_xio_rst:1;         /* Reset XIO controller. 0 = DISABLE 1 = ENABLE */
        unsigned int swr_sbc3_rst:1;        /* Reset SBC 3 (SPI 3) Controller. 0 = DISABLE 1 = ENABLE */
        unsigned int swr_dvc_i2c_rst:1;     /* Reset DVC-I2C Controller 0 = DISABLE 1 = ENABLE */
        unsigned int swr_dsi_rst:1;         /* Reset DSI controller 0 = DISABLE 1 = ENABLE */
        unsigned int swr_tvo_rst:1;         /* Reset TVO/CVE controller 0 = DISABLE 1 = ENABLE */
        unsigned int swr_mipi_rst:1;        /* Reset MIPI base-band controller. 0 = DISABLE 1 = ENABLE */
        unsigned int swr_hdmi_rst:1;        /* Reset HDMI 0 = DISABLE 1 = ENABLE */
        unsigned int swr_csi_rst:1;         /* Reset CSI controller. 0 = DISABLE 1 = ENABLE */
        unsigned int swr_tvdac_rst:1;       /* Reset TVDAC controller. 0 = DISABLE 1 = ENABLE */
        unsigned int swr_i2c2_rst:1;        /* Reset I2C 2 controller. 0 = DISABLE 1 = ENABLE */
        unsigned int swr_uart3_rst:1;       /* Reset UART3 Controller 0 = DISABLE 1 = ENABLE */
        unsigned int undefined_bit_24:1;
        unsigned int swr_emc_rst:1;         /* Reset EMC controller. 0 = DISABLE 1 = ENABLE */
        unsigned int swr_usb2_rst:1;        /* Reset USB2 controller. 0 = DISABLE 1 = ENABLE */
        unsigned int swr_usb3_rst:1;        /* Reset USB3 controller. 0 = DISABLE 1 = ENABLE */
        unsigned int swr_mpe_rst:1;         /* Reset MPE controller. 0 = DISABLE 1 = ENABLE */
        unsigned int swr_vde_rst:1;         /* Reset VDE & BSEV controller. 0 = DISABLE 1 = ENABLE */
        unsigned int swr_bsea_rst:1;        /* Reset BSEA controller. 0 = DISABLE 1 = ENABLE */
        unsigned int swr_bsev_rst:1;        /* Reset BSEV controller. 0 = DISABLE 1 = ENABLE */
    };

    u_int32_t reg32;
};

void CarDev::fill_rst_devices_h_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const rst_devices_h_u old_value_t = { .reg32 = value };
    const rst_devices_h_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: swr_mem_rst:1",
              "Reset MC.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.swr_mem_rst, new_value_t.swr_mem_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "01: swr_ahbdma_rst:1",
              "Reset AHB-DMA.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.swr_ahbdma_rst, new_value_t.swr_ahbdma_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "02: swr_apbdma_rst:1",
              "Reset APB-DMA.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.swr_apbdma_rst, new_value_t.swr_apbdma_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "03: undefined_bit_3:1", "", 1, old_value_t.undefined_bit_3, new_value_t.undefined_bit_3 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: swr_kbc_rst:1",
              "Reset Keyboard controller.",
              1, old_value_t.swr_kbc_rst, new_value_t.swr_kbc_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "05: swr_stat_mon_rst:1",
              "Reset statistic monitor\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.swr_stat_mon_rst, new_value_t.swr_stat_mon_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "06: swr_pmc_rst:1",
              "Reset PMC controller.",
              1, old_value_t.swr_pmc_rst, new_value_t.swr_pmc_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "07: swr_fuse_rst:1",
              "Reset Fuse controller.",
              1, old_value_t.swr_fuse_rst, new_value_t.swr_fuse_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "08: swr_kfuse_rst:1",
              "Reset KFuse controller.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.swr_kfuse_rst, new_value_t.swr_kfuse_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "09: swr_sbc1_rst:1",
              "Reset SBC 1 (SPI 1) Controller.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.swr_sbc1_rst, new_value_t.swr_sbc1_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "10: swr_snor_rst:1",
              "Reset NOR Flash Controller.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.swr_snor_rst, new_value_t.swr_snor_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "11: swr_spi1_rst:1",
              "Reset SPI 1 Controller\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.swr_spi1_rst, new_value_t.swr_spi1_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "12: swr_sbc2_rst:1",
              "Reset SBC 2 (SPI 2) Controller.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.swr_sbc2_rst, new_value_t.swr_sbc2_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "13: swr_xio_rst:1",
              "Reset XIO controller.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.swr_xio_rst, new_value_t.swr_xio_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "14: swr_sbc3_rst:1",
              "Reset SBC 3 (SPI 3) Controller.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.swr_sbc3_rst, new_value_t.swr_sbc3_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "15: swr_dvc_i2c_rst:1",
              "Reset DVC-I2C Controller\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.swr_dvc_i2c_rst, new_value_t.swr_dvc_i2c_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "16: swr_dsi_rst:1",
              "Reset DSI controller\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.swr_dsi_rst, new_value_t.swr_dsi_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "17: swr_tvo_rst:1",
              "Reset TVO/CVE controller\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.swr_tvo_rst, new_value_t.swr_tvo_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "18: swr_mipi_rst:1",
              "Reset MIPI base-band controller.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.swr_mipi_rst, new_value_t.swr_mipi_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "19: swr_hdmi_rst:1",
              "Reset HDMI\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.swr_hdmi_rst, new_value_t.swr_hdmi_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "20: swr_csi_rst:1",
              "Reset CSI controller.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.swr_csi_rst, new_value_t.swr_csi_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "21: swr_tvdac_rst:1",
              "Reset TVDAC controller.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.swr_tvdac_rst, new_value_t.swr_tvdac_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "22: swr_i2c2_rst:1",
              "Reset I2C 2 controller.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.swr_i2c2_rst, new_value_t.swr_i2c2_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "23: swr_uart3_rst:1",
              "Reset UART3 Controller\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.swr_uart3_rst, new_value_t.swr_uart3_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "24: undefined_bit_24:1", "", 1, old_value_t.undefined_bit_24, new_value_t.undefined_bit_24 };
    m_bit_details_model.bits.append(entry);
    entry = { "25: swr_emc_rst:1",
              "Reset EMC controller.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.swr_emc_rst, new_value_t.swr_emc_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "26: swr_usb2_rst:1",
              "Reset USB2 controller.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.swr_usb2_rst, new_value_t.swr_usb2_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "27: swr_usb3_rst:1",
              "Reset USB3 controller.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.swr_usb3_rst, new_value_t.swr_usb3_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "28: swr_mpe_rst:1",
              "Reset MPE controller.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.swr_mpe_rst, new_value_t.swr_mpe_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "29: swr_vde_rst:1",
              "Reset VDE & BSEV controller.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.swr_vde_rst, new_value_t.swr_vde_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "30: swr_bsea_rst:1",
              "Reset BSEA controller.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.swr_bsea_rst, new_value_t.swr_bsea_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "31: swr_bsev_rst:1",
              "Reset BSEV controller.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.swr_bsev_rst, new_value_t.swr_bsev_rst };
    m_bit_details_model.bits.append(entry);
}

#define RST_DEVICES_U_OFFSET 0xC
#define RST_DEVICES_U_UNDEFMASK 0xFFFFE000
union rst_devices_u_u {
    struct {
        unsigned int swr_speedo_rst:1;      /* Reset SPEEDO controller. 0 = DISABLE 1 = ENABLE */
        unsigned int swr_uart4_rst:1;       /* Reset UART4 controller. 0 = DISABLE 1 = ENABLE */
        unsigned int swr_uart5_rst:1;       /* Reset UART5 controller. 0 = DISABLE 1 = ENABLE */
        unsigned int swr_i2c3_rst:1;        /* Reset I2C3 controller. 0 = DISABLE 1 = ENABLE */
        unsigned int swr_sbc4_rst:1;        /* Reset SBC4 (SPI 4) controller. 0 = DISABLE 1 = ENABLE */
        unsigned int swr_sdmmc3_rst:1;      /* Reset SDMMC3 controller. 0 = DISABLE 1 = ENABLE */
        unsigned int swr_pcie_rst:1;        /* Reset PCIE controller. 0 = DISABLE 1 = ENABLE */
        unsigned int swr_owr_rst:1;         /* Reset OWR controller. 0 = DISABLE 1 = ENABLE */
        unsigned int swr_afi_rst:1;         /* Reset AFI controller. 0 = DISABLE 1 = ENABLE */
        unsigned int swr_csite_rst:1;       /* Reset Coresight controller. 0 = DISABLE 1 = ENABLE */
        unsigned int swr_pciexclk_rst:1;    /* Reset PCIEXCLK logic. 0 = DISABLE 1 = ENABLE */
        unsigned int swr_avpucq_rst:1;      /* Reset AVPUCQ logic. 0 = DISABLE 1 = ENABLE */
        unsigned int swr_la_rst:1;          /* Reset LA logic. */
        unsigned int undefined_bits_13_31:19;
    };

    u_int32_t reg32;
};

void CarDev::fill_rst_devices_u_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const rst_devices_u_u old_value_t = { .reg32 = value };
    const rst_devices_u_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: swr_speedo_rst:1",
              "Reset SPEEDO controller.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.swr_speedo_rst, new_value_t.swr_speedo_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "01: swr_uart4_rst:1",
              "Reset UART4 controller.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.swr_uart4_rst, new_value_t.swr_uart4_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "02: swr_uart5_rst:1",
              "Reset UART5 controller.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.swr_uart5_rst, new_value_t.swr_uart5_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "03: swr_i2c3_rst:1",
              "Reset I2C3 controller.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.swr_i2c3_rst, new_value_t.swr_i2c3_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "04: swr_sbc4_rst:1",
              "Reset SBC4 (SPI 4) controller.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.swr_sbc4_rst, new_value_t.swr_sbc4_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "05: swr_sdmmc3_rst:1",
              "Reset SDMMC3 controller.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.swr_sdmmc3_rst, new_value_t.swr_sdmmc3_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "06: swr_pcie_rst:1",
              "Reset PCIE controller.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.swr_pcie_rst, new_value_t.swr_pcie_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "07: swr_owr_rst:1",
              "Reset OWR controller.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.swr_owr_rst, new_value_t.swr_owr_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "08: swr_afi_rst:1",
              "Reset AFI controller.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.swr_afi_rst, new_value_t.swr_afi_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "09: swr_csite_rst:1",
              "Reset Coresight controller.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.swr_csite_rst, new_value_t.swr_csite_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "10: swr_pciexclk_rst:1",
              "Reset PCIEXCLK logic.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.swr_pciexclk_rst, new_value_t.swr_pciexclk_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "11: swr_avpucq_rst:1",
              "Reset AVPUCQ logic.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.swr_avpucq_rst, new_value_t.swr_avpucq_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "12: swr_la_rst:1",
              "Reset LA logic.",
              1, old_value_t.swr_la_rst, new_value_t.swr_la_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "13: undefined_bits_13_31:19", "", 19, old_value_t.undefined_bits_13_31, new_value_t.undefined_bits_13_31 };
    m_bit_details_model.bits.append(entry);
}

#define CLK_OUT_ENB_L_OFFSET 0x10
#define CLK_OUT_ENB_L_UNDEFMASK 0x40000006
union clk_out_enb_l_u {
    struct {
        unsigned int clk_enb_cpu:1;         /* Enable clock to CPU. 0 = DISABLE 1 = ENABLE */
        unsigned int undefined_bits_1_2:2;
        unsigned int clk_enb_ac97:1;        /* Enable clock to AC97 Controller 0 = DISABLE 1 = ENABLE */
        unsigned int clk_enb_rtc:1;         /* Enable clock to RTC Controller 0 = DISABLE 1 = ENABLE */
        unsigned int clk_enb_tmr:1;         /* Enable clock to Timer Controller 0 = DISABLE 1 = ENABLE */
        unsigned int clk_enb_uart1:1;       /* Enable clock to UART1 Controller 0 = DISABLE 1 = ENABLE */
        unsigned int clk_enb_uart2:1;       /* Enable clock to UART2/VFIR Controller 0 = DISABLE 1 = ENABLE */
        unsigned int clk_enb_gpio:1;        /* Enable clock to GPIO Controller 0 = DISABLE 1 = ENABLE */
        unsigned int clk_enb_sdmmc2:1;      /* Enable clock to SDMMC2 controller. 0 = DISABLE 1 = ENABLE */
        unsigned int clk_enb_spdif:1;       /* Enable clock to SPDIF Controller 0 = DISABLE 1 = ENABLE */
        unsigned int clk_enb_i2s1:1;        /* Enable clock to I2S1 Controller 0 = DISABLE 1 = ENABLE */
        unsigned int clk_enb_i2c1:1;        /* Enable clock to I2C1 Controller 0 = DISABLE 1 = ENABLE */
        unsigned int clk_enb_ndflash:1;     /* Enable clock to NAND flash controller. 0 = DISABLE 1 = ENABLE */
        unsigned int clk_enb_sdmmc1:1;      /* Enable clock to SDMMC1 controller. 0 = DISABLE 1 = ENABLE */
        unsigned int clk_enb_sdmmc4:1;      /* Enable clock to SDMMC4 controller. 0 = DISABLE 1 = ENABLE */
        unsigned int clk_enb_twc:1;         /* Enable clock to 3-Wire Interface Controller 0 = DISABLE 1 = ENABLE */
        unsigned int clk_enb_pwm:1;         /* Enable clock to PWM (Pulse Width Modulator) 0 = DISABLE 1 = ENABLE */
        unsigned int clk_enb_i2s2:1;        /* Enable clock to I2S 2 controller 0 = DISABLE 1 = ENABLE */
        unsigned int clk_enb_epp:1;         /* Enable clock to EPP controller. 0 = DISABLE 1 = ENABLE */
        unsigned int clk_enb_vi:1;          /* Enable clock to VI controller. 0 = DISABLE 1 = ENABLE */
        unsigned int clk_enb_2d:1;          /* Enable clock to 2D graphics engine. 0 = DISABLE 1 = ENABLE */
        unsigned int clk_enb_usbd:1;        /* Enable clock to USB controller 0 = DISABLE 1 = ENABLE */
        unsigned int clk_enb_isp:1;         /* Enable clock to ISP controller. 0 = DISABLE 1 = ENABLE */
        unsigned int clk_enb_3d:1;          /* Enable clock to 3D controller. 0 = DISABLE 1 = ENABLE */
        unsigned int clk_enb_ide:1;         /* Enable clock to IDE controller 0 = DISABLE 1 = ENABLE */
        unsigned int clk_enb_disp2:1;       /* Enable clock to DISP2 controller. 0 = DISABLE 1 = ENABLE */
        unsigned int clk_enb_disp1:1;       /* Enable clock to DISP1 controller. 0 = DISABLE 1 = ENABLE */
        unsigned int clk_enb_host1x:1;      /* Enable clock to HOST1X. 0 = DISABLE 1 = ENABLE */
        unsigned int clk_enb_vcp:1;         /* Enable clock to vector co-processor. 0 = DISABLE 1 = ENABLE */
        unsigned int undefined_bit_30:1;
        unsigned int clk_enb_cache2:1;      /* Enable clock to COP cache controller. 0 = DISABLE 1 = ENABLE */
    };

    u_int32_t reg32;
};

void CarDev::fill_clk_out_enb_l_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const clk_out_enb_l_u old_value_t = { .reg32 = value };
    const clk_out_enb_l_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: clk_enb_cpu:1",
              "Enable clock to CPU.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.clk_enb_cpu, new_value_t.clk_enb_cpu };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_2:2", "", 2, old_value_t.undefined_bits_1_2, new_value_t.undefined_bits_1_2 };
    m_bit_details_model.bits.append(entry);
    entry = { "03: clk_enb_ac97:1",
              "Enable clock to AC97 Controller\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.clk_enb_ac97, new_value_t.clk_enb_ac97 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: clk_enb_rtc:1",
              "Enable clock to RTC Controller\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.clk_enb_rtc, new_value_t.clk_enb_rtc };
    m_bit_details_model.bits.append(entry);
    entry = { "05: clk_enb_tmr:1",
              "Enable clock to Timer Controller\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.clk_enb_tmr, new_value_t.clk_enb_tmr };
    m_bit_details_model.bits.append(entry);
    entry = { "06: clk_enb_uart1:1",
              "Enable clock to UART1 Controller\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.clk_enb_uart1, new_value_t.clk_enb_uart1 };
    m_bit_details_model.bits.append(entry);
    entry = { "07: clk_enb_uart2:1",
              "Enable clock to UART2/VFIR Controller\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.clk_enb_uart2, new_value_t.clk_enb_uart2 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: clk_enb_gpio:1",
              "Enable clock to GPIO Controller\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.clk_enb_gpio, new_value_t.clk_enb_gpio };
    m_bit_details_model.bits.append(entry);
    entry = { "09: clk_enb_sdmmc2:1",
              "Enable clock to SDMMC2 controller.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.clk_enb_sdmmc2, new_value_t.clk_enb_sdmmc2 };
    m_bit_details_model.bits.append(entry);
    entry = { "10: clk_enb_spdif:1",
              "Enable clock to SPDIF Controller\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.clk_enb_spdif, new_value_t.clk_enb_spdif };
    m_bit_details_model.bits.append(entry);
    entry = { "11: clk_enb_i2s1:1",
              "Enable clock to I2S1 Controller\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.clk_enb_i2s1, new_value_t.clk_enb_i2s1 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: clk_enb_i2c1:1",
              "Enable clock to I2C1 Controller\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.clk_enb_i2c1, new_value_t.clk_enb_i2c1 };
    m_bit_details_model.bits.append(entry);
    entry = { "13: clk_enb_ndflash:1",
              "Enable clock to NAND flash controller.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.clk_enb_ndflash, new_value_t.clk_enb_ndflash };
    m_bit_details_model.bits.append(entry);
    entry = { "14: clk_enb_sdmmc1:1",
              "Enable clock to SDMMC1 controller.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.clk_enb_sdmmc1, new_value_t.clk_enb_sdmmc1 };
    m_bit_details_model.bits.append(entry);
    entry = { "15: clk_enb_sdmmc4:1",
              "Enable clock to SDMMC4 controller.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.clk_enb_sdmmc4, new_value_t.clk_enb_sdmmc4 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: clk_enb_twc:1",
              "Enable clock to 3-Wire Interface Controller\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.clk_enb_twc, new_value_t.clk_enb_twc };
    m_bit_details_model.bits.append(entry);
    entry = { "17: clk_enb_pwm:1",
              "Enable clock to PWM (Pulse Width Modulator)\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.clk_enb_pwm, new_value_t.clk_enb_pwm };
    m_bit_details_model.bits.append(entry);
    entry = { "18: clk_enb_i2s2:1",
              "Enable clock to I2S 2 controller\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.clk_enb_i2s2, new_value_t.clk_enb_i2s2 };
    m_bit_details_model.bits.append(entry);
    entry = { "19: clk_enb_epp:1",
              "Enable clock to EPP controller.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.clk_enb_epp, new_value_t.clk_enb_epp };
    m_bit_details_model.bits.append(entry);
    entry = { "20: clk_enb_vi:1",
              "Enable clock to VI controller.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.clk_enb_vi, new_value_t.clk_enb_vi };
    m_bit_details_model.bits.append(entry);
    entry = { "21: clk_enb_2d:1",
              "Enable clock to 2D graphics engine.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.clk_enb_2d, new_value_t.clk_enb_2d };
    m_bit_details_model.bits.append(entry);
    entry = { "22: clk_enb_usbd:1",
              "Enable clock to USB controller\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.clk_enb_usbd, new_value_t.clk_enb_usbd };
    m_bit_details_model.bits.append(entry);
    entry = { "23: clk_enb_isp:1",
              "Enable clock to ISP controller.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.clk_enb_isp, new_value_t.clk_enb_isp };
    m_bit_details_model.bits.append(entry);
    entry = { "24: clk_enb_3d:1",
              "Enable clock to 3D controller.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.clk_enb_3d, new_value_t.clk_enb_3d };
    m_bit_details_model.bits.append(entry);
    entry = { "25: clk_enb_ide:1",
              "Enable clock to IDE controller\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.clk_enb_ide, new_value_t.clk_enb_ide };
    m_bit_details_model.bits.append(entry);
    entry = { "26: clk_enb_disp2:1",
              "Enable clock to DISP2 controller.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.clk_enb_disp2, new_value_t.clk_enb_disp2 };
    m_bit_details_model.bits.append(entry);
    entry = { "27: clk_enb_disp1:1",
              "Enable clock to DISP1 controller.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.clk_enb_disp1, new_value_t.clk_enb_disp1 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: clk_enb_host1x:1",
              "Enable clock to HOST1X.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.clk_enb_host1x, new_value_t.clk_enb_host1x };
    m_bit_details_model.bits.append(entry);
    entry = { "29: clk_enb_vcp:1",
              "Enable clock to vector co-processor.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.clk_enb_vcp, new_value_t.clk_enb_vcp };
    m_bit_details_model.bits.append(entry);
    entry = { "30: undefined_bit_30:1", "", 1, old_value_t.undefined_bit_30, new_value_t.undefined_bit_30 };
    m_bit_details_model.bits.append(entry);
    entry = { "31: clk_enb_cache2:1",
              "Enable clock to COP cache controller.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.clk_enb_cache2, new_value_t.clk_enb_cache2 };
    m_bit_details_model.bits.append(entry);
}

#define CLK_OUT_ENB_H_OFFSET 0x14
#define CLK_OUT_ENB_H_UNDEFMASK 0x01000008
union clk_out_enb_h_u {
    struct {
        unsigned int clk_enb_mem:1;         /* Enable clock to MC/EMC. 0 = DISABLE 1 = ENABLE */
        unsigned int clk_enb_ahbdma:1;      /* Enable clock to AHB-DMA. 0 = DISABLE 1 = ENABLE */
        unsigned int clk_enb_apbdma:1;      /* Enable clock to APB-DMA. 0 = DISABLE 1 = ENABLE */
        unsigned int undefined_bit_3:1;
        unsigned int clk_enb_kbc:1;         /* Enable clock to keyboard controller. 0 = DISABLE 1 = ENABLE */
        unsigned int clk_enb_stat_mon:1;    /* Enable clock to statistic monitor. 0 = DISABLE 1 = ENABLE */
        unsigned int clk_enb_pmc:1;         /* Enable clock to PMC controller. 0 = DISABLE 1 = ENABLE */
        unsigned int clk_enb_fuse:1;        /* Enable clock to FUSE controller. 0 = DISABLE 1 = ENABLE */
        unsigned int clk_enb_kfuse:1;       /* Enable clock to KFUSE controller. 0 = DISABLE 1 = ENABLE */
        unsigned int clk_enb_sbc1:1;        /* Enable clock to SBC 1 (SPI 1) Controller. 0 = DISABLE 1 = ENABLE */
        unsigned int clk_enb_snor:1;        /* Enable clock to NOR Flash Controller. 0 = DISABLE 1 = ENABLE */
        unsigned int clk_enb_spi1:1;        /* Enable clock to SPI 1 Controller 0 = DISABLE 1 = ENABLE */
        unsigned int clk_enb_sbc2:1;        /* Enable clock to SBC 2 (SPI 2) Controller. 0 = DISABLE 1 = ENABLE */
        unsigned int clk_enb_xio:1;         /* Enable clock to XIO Controller. 0 = DISABLE 1 = ENABLE */
        unsigned int clk_enb_sbc3:1;        /* Enable clock to SBC 3 (SPI 3) Controller. 0 = DISABLE 1 = ENABLE */
        unsigned int clk_enb_dvc_i2c:1;     /* Enable clock to DVC-I2C Controller 0 = DISABLE 1 = ENABLE */
        unsigned int clk_enb_dsi:1;         /* Enable clock to DSI controller 0 = DISABLE 1 = ENABLE */
        unsigned int clk_enb_tvo:1;         /* Enable clock to TVO/CVE controller 0 = DISABLE 1 = ENABLE */
        unsigned int clk_enb_mipi:1;        /* Enable clock to MIPI base-band controller 0 = DISABLE 1 = ENABLE */
        unsigned int clk_enb_hdmi:1;        /* Enable clock to HDMI 0 = DISABLE 1 = ENABLE */
        unsigned int clk_enb_csi:1;         /* Enable clock to CSI controller 0 = DISABLE 1 = ENABLE */
        unsigned int clk_enb_tvdac:1;       /* Enable clock to TVDAC controller. 0 = DISABLE 1 = ENABLE */
        unsigned int clk_enb_i2c2:1;        /* Enable clock to I2C2 controller. 0 = DISABLE 1 = ENABLE */
        unsigned int clk_enb_uart3:1;       /* Enable clock to UART3 Controller 0 = DISABLE 1 = ENABLE */
        unsigned int undefined_bit_24:1;
        unsigned int clk_enb_emc:1;         /* Enable clock to EMC controller. 0 = DISABLE 1 = ENABLE */
        unsigned int clk_enb_usb2:1;        /* Enable clock to USB2 controller. 0 = DISABLE 1 = ENABLE */
        unsigned int clk_enb_usb3:1;        /* Enable clock to USB3 controller. 0 = DISABLE 1 = ENABLE */
        unsigned int clk_enb_mpe:1;         /* Enable clock to MPE controller. 0 = DISABLE 1 = ENABLE */
        unsigned int clk_enb_vde:1;         /* Enable clock to VDE Controller 0 = DISABLE 1 = ENABLE */
        unsigned int clk_enb_bsea:1;        /* Enable clock to BSEA Controller 0 = DISABLE 1 = ENABLE */
        unsigned int clk_enb_bsev:1;        /* Enable clock to BSEV Controller. 0 = DISABLE 1 = ENABLE */
    };

    u_int32_t reg32;
};

void CarDev::fill_clk_out_enb_h_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const clk_out_enb_h_u old_value_t = { .reg32 = value };
    const clk_out_enb_h_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: clk_enb_mem:1",
              "Enable clock to MC/EMC.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.clk_enb_mem, new_value_t.clk_enb_mem };
    m_bit_details_model.bits.append(entry);
    entry = { "01: clk_enb_ahbdma:1",
              "Enable clock to AHB-DMA.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.clk_enb_ahbdma, new_value_t.clk_enb_ahbdma };
    m_bit_details_model.bits.append(entry);
    entry = { "02: clk_enb_apbdma:1",
              "Enable clock to APB-DMA.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.clk_enb_apbdma, new_value_t.clk_enb_apbdma };
    m_bit_details_model.bits.append(entry);
    entry = { "03: undefined_bit_3:1", "", 1, old_value_t.undefined_bit_3, new_value_t.undefined_bit_3 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: clk_enb_kbc:1",
              "Enable clock to keyboard controller.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.clk_enb_kbc, new_value_t.clk_enb_kbc };
    m_bit_details_model.bits.append(entry);
    entry = { "05: clk_enb_stat_mon:1",
              "Enable clock to statistic monitor.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.clk_enb_stat_mon, new_value_t.clk_enb_stat_mon };
    m_bit_details_model.bits.append(entry);
    entry = { "06: clk_enb_pmc:1",
              "Enable clock to PMC controller.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.clk_enb_pmc, new_value_t.clk_enb_pmc };
    m_bit_details_model.bits.append(entry);
    entry = { "07: clk_enb_fuse:1",
              "Enable clock to FUSE controller.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.clk_enb_fuse, new_value_t.clk_enb_fuse };
    m_bit_details_model.bits.append(entry);
    entry = { "08: clk_enb_kfuse:1",
              "Enable clock to KFUSE controller.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.clk_enb_kfuse, new_value_t.clk_enb_kfuse };
    m_bit_details_model.bits.append(entry);
    entry = { "09: clk_enb_sbc1:1",
              "Enable clock to SBC 1 (SPI 1) Controller.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.clk_enb_sbc1, new_value_t.clk_enb_sbc1 };
    m_bit_details_model.bits.append(entry);
    entry = { "10: clk_enb_snor:1",
              "Enable clock to NOR Flash Controller.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.clk_enb_snor, new_value_t.clk_enb_snor };
    m_bit_details_model.bits.append(entry);
    entry = { "11: clk_enb_spi1:1",
              "Enable clock to SPI 1 Controller\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.clk_enb_spi1, new_value_t.clk_enb_spi1 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: clk_enb_sbc2:1",
              "Enable clock to SBC 2 (SPI 2) Controller.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.clk_enb_sbc2, new_value_t.clk_enb_sbc2 };
    m_bit_details_model.bits.append(entry);
    entry = { "13: clk_enb_xio:1",
              "Enable clock to XIO Controller.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.clk_enb_xio, new_value_t.clk_enb_xio };
    m_bit_details_model.bits.append(entry);
    entry = { "14: clk_enb_sbc3:1",
              "Enable clock to SBC 3 (SPI 3) Controller.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.clk_enb_sbc3, new_value_t.clk_enb_sbc3 };
    m_bit_details_model.bits.append(entry);
    entry = { "15: clk_enb_dvc_i2c:1",
              "Enable clock to DVC-I2C Controller\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.clk_enb_dvc_i2c, new_value_t.clk_enb_dvc_i2c };
    m_bit_details_model.bits.append(entry);
    entry = { "16: clk_enb_dsi:1",
              "Enable clock to DSI controller\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.clk_enb_dsi, new_value_t.clk_enb_dsi };
    m_bit_details_model.bits.append(entry);
    entry = { "17: clk_enb_tvo:1",
              "Enable clock to TVO/CVE controller\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.clk_enb_tvo, new_value_t.clk_enb_tvo };
    m_bit_details_model.bits.append(entry);
    entry = { "18: clk_enb_mipi:1",
              "Enable clock to MIPI base-band controller\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.clk_enb_mipi, new_value_t.clk_enb_mipi };
    m_bit_details_model.bits.append(entry);
    entry = { "19: clk_enb_hdmi:1",
              "Enable clock to HDMI\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.clk_enb_hdmi, new_value_t.clk_enb_hdmi };
    m_bit_details_model.bits.append(entry);
    entry = { "20: clk_enb_csi:1",
              "Enable clock to CSI controller\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.clk_enb_csi, new_value_t.clk_enb_csi };
    m_bit_details_model.bits.append(entry);
    entry = { "21: clk_enb_tvdac:1",
              "Enable clock to TVDAC controller.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.clk_enb_tvdac, new_value_t.clk_enb_tvdac };
    m_bit_details_model.bits.append(entry);
    entry = { "22: clk_enb_i2c2:1",
              "Enable clock to I2C2 controller.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.clk_enb_i2c2, new_value_t.clk_enb_i2c2 };
    m_bit_details_model.bits.append(entry);
    entry = { "23: clk_enb_uart3:1",
              "Enable clock to UART3 Controller\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.clk_enb_uart3, new_value_t.clk_enb_uart3 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: undefined_bit_24:1", "", 1, old_value_t.undefined_bit_24, new_value_t.undefined_bit_24 };
    m_bit_details_model.bits.append(entry);
    entry = { "25: clk_enb_emc:1",
              "Enable clock to EMC controller.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.clk_enb_emc, new_value_t.clk_enb_emc };
    m_bit_details_model.bits.append(entry);
    entry = { "26: clk_enb_usb2:1",
              "Enable clock to USB2 controller.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.clk_enb_usb2, new_value_t.clk_enb_usb2 };
    m_bit_details_model.bits.append(entry);
    entry = { "27: clk_enb_usb3:1",
              "Enable clock to USB3 controller.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.clk_enb_usb3, new_value_t.clk_enb_usb3 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: clk_enb_mpe:1",
              "Enable clock to MPE controller.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.clk_enb_mpe, new_value_t.clk_enb_mpe };
    m_bit_details_model.bits.append(entry);
    entry = { "29: clk_enb_vde:1",
              "Enable clock to VDE Controller\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.clk_enb_vde, new_value_t.clk_enb_vde };
    m_bit_details_model.bits.append(entry);
    entry = { "30: clk_enb_bsea:1",
              "Enable clock to BSEA Controller\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.clk_enb_bsea, new_value_t.clk_enb_bsea };
    m_bit_details_model.bits.append(entry);
    entry = { "31: clk_enb_bsev:1",
              "Enable clock to BSEV Controller.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.clk_enb_bsev, new_value_t.clk_enb_bsev };
    m_bit_details_model.bits.append(entry);
}

#define CLK_OUT_ENB_U_OFFSET 0x18
#define CLK_OUT_ENB_U_UNDEFMASK 0x880FE400
union clk_out_enb_u_u {
    struct {
        unsigned int clk_enb_speedo:1;      /* Enable clock to SPEEDO. 0 = DISABLE 1 = ENABLE */
        unsigned int clk_enb_uart4:1;       /* Enable clock to UART4. 0 = DISABLE 1 = ENABLE */
        unsigned int clk_enb_uart5:1;       /* Enable clock to UART5. 0 = DISABLE 1 = ENABLE */
        unsigned int clk_enb_i2c3:1;        /* Enable clock to I2C3. 0 = DISABLE 1 = ENABLE */
        unsigned int clk_enb_sbc4:1;        /* Enable clock to SBC4 (SPI 4). 0 = DISABLE 1 = ENABLE */
        unsigned int clk_enb_sdmmc3:1;      /* Enable clock to SDMMC3. 0 = DISABLE 1 = ENABLE */
        unsigned int clk_enb_pcie:1;        /* Enable clock to PCIE. 0 = DISABLE 1 = ENABLE */
        unsigned int clk_enb_owr:1;         /* Enable clock to OWR. 0 = DISABLE 1 = ENABLE */
        unsigned int clk_enb_afi:1;         /* Enable clock to AFI. 0 = DISABLE 1 = ENABLE */
        unsigned int clk_enb_csite:1;       /* Enable clock to Coresight. 0 = DISABLE 1 = ENABLE */
        unsigned int undefined_bit_10:1;
        unsigned int clk_enb_avpucq:1;      /* Enable clock to AVPUCQ. 0 = DISABLE 1 = ENABLE */
        unsigned int clk_enb_la:1;          /* Enable clock to LA. */
        unsigned int undefined_bits_13_19:7;
        unsigned int clk_enb_irama:1;       /* Enable IRAMB clk. 0 = DISABLE 1 = ENABLE */
        unsigned int clk_enb_iramb:1;       /* Enable IRAMB clk. 0 = DISABLE 1 = ENABLE */
        unsigned int clk_enb_iramc:1;       /* Enable IRAMC clk. 0 = DISABLE 1 = ENABLE */
        unsigned int clk_enb_iramd:1;       /* Enable IRAMD clk. 0 = DISABLE 1 = ENABLE */
        unsigned int clk_enb_cram2:1;       /* Enable COP cache ram clk. 0 = DISABLE 1 = ENABLE */
        unsigned int sync_clk_doubler_enb:1;/* Enable audio sync clk doubler. 0 = DISABLE 1 = ENABLE */
        unsigned int clk_m_doubler_enb:1;   /* Enable CLK_M clk doubler. 0 = DISABLE 1 = ENABLE */
        unsigned int undefined_bit_27:1;
        unsigned int clk_enb_sus_out:1;     /* Enable clock to SUS pad. 0 = DISABLE 1 = ENABLE */
        unsigned int clk_enb_dev2_out:1;    /* Enable clock to DEV2 pad. 0 = DISABLE 1 = ENABLE */
        unsigned int clk_enb_dev1_out:1;    /* Enable clock to DEV1 pad. 0 = DISABLE 1 = ENABLE */
        unsigned int undefined_bit_31:1;
    };

    u_int32_t reg32;
};

void CarDev::fill_clk_out_enb_u_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const clk_out_enb_u_u old_value_t = { .reg32 = value };
    const clk_out_enb_u_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: clk_enb_speedo:1",
              "Enable clock to SPEEDO.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.clk_enb_speedo, new_value_t.clk_enb_speedo };
    m_bit_details_model.bits.append(entry);
    entry = { "01: clk_enb_uart4:1",
              "Enable clock to UART4.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.clk_enb_uart4, new_value_t.clk_enb_uart4 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: clk_enb_uart5:1",
              "Enable clock to UART5.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.clk_enb_uart5, new_value_t.clk_enb_uart5 };
    m_bit_details_model.bits.append(entry);
    entry = { "03: clk_enb_i2c3:1",
              "Enable clock to I2C3.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.clk_enb_i2c3, new_value_t.clk_enb_i2c3 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: clk_enb_sbc4:1",
              "Enable clock to SBC4 (SPI 4).\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.clk_enb_sbc4, new_value_t.clk_enb_sbc4 };
    m_bit_details_model.bits.append(entry);
    entry = { "05: clk_enb_sdmmc3:1",
              "Enable clock to SDMMC3.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.clk_enb_sdmmc3, new_value_t.clk_enb_sdmmc3 };
    m_bit_details_model.bits.append(entry);
    entry = { "06: clk_enb_pcie:1",
              "Enable clock to PCIE.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.clk_enb_pcie, new_value_t.clk_enb_pcie };
    m_bit_details_model.bits.append(entry);
    entry = { "07: clk_enb_owr:1",
              "Enable clock to OWR.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.clk_enb_owr, new_value_t.clk_enb_owr };
    m_bit_details_model.bits.append(entry);
    entry = { "08: clk_enb_afi:1",
              "Enable clock to AFI.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.clk_enb_afi, new_value_t.clk_enb_afi };
    m_bit_details_model.bits.append(entry);
    entry = { "09: clk_enb_csite:1",
              "Enable clock to Coresight.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.clk_enb_csite, new_value_t.clk_enb_csite };
    m_bit_details_model.bits.append(entry);
    entry = { "10: undefined_bit_10:1", "", 1, old_value_t.undefined_bit_10, new_value_t.undefined_bit_10 };
    m_bit_details_model.bits.append(entry);
    entry = { "11: clk_enb_avpucq:1",
              "Enable clock to AVPUCQ.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.clk_enb_avpucq, new_value_t.clk_enb_avpucq };
    m_bit_details_model.bits.append(entry);
    entry = { "12: clk_enb_la:1",
              "Enable clock to LA.",
              1, old_value_t.clk_enb_la, new_value_t.clk_enb_la };
    m_bit_details_model.bits.append(entry);
    entry = { "13: undefined_bits_13_19:7", "", 7, old_value_t.undefined_bits_13_19, new_value_t.undefined_bits_13_19 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: clk_enb_irama:1",
              "Enable IRAMB clk.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.clk_enb_irama, new_value_t.clk_enb_irama };
    m_bit_details_model.bits.append(entry);
    entry = { "21: clk_enb_iramb:1",
              "Enable IRAMB clk.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.clk_enb_iramb, new_value_t.clk_enb_iramb };
    m_bit_details_model.bits.append(entry);
    entry = { "22: clk_enb_iramc:1",
              "Enable IRAMC clk.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.clk_enb_iramc, new_value_t.clk_enb_iramc };
    m_bit_details_model.bits.append(entry);
    entry = { "23: clk_enb_iramd:1",
              "Enable IRAMD clk.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.clk_enb_iramd, new_value_t.clk_enb_iramd };
    m_bit_details_model.bits.append(entry);
    entry = { "24: clk_enb_cram2:1",
              "Enable COP cache ram clk.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.clk_enb_cram2, new_value_t.clk_enb_cram2 };
    m_bit_details_model.bits.append(entry);
    entry = { "25: sync_clk_doubler_enb:1",
              "Enable audio sync clk doubler.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.sync_clk_doubler_enb, new_value_t.sync_clk_doubler_enb };
    m_bit_details_model.bits.append(entry);
    entry = { "26: clk_m_doubler_enb:1",
              "Enable CLK_M clk doubler.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.clk_m_doubler_enb, new_value_t.clk_m_doubler_enb };
    m_bit_details_model.bits.append(entry);
    entry = { "27: undefined_bit_27:1", "", 1, old_value_t.undefined_bit_27, new_value_t.undefined_bit_27 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: clk_enb_sus_out:1",
              "Enable clock to SUS pad.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.clk_enb_sus_out, new_value_t.clk_enb_sus_out };
    m_bit_details_model.bits.append(entry);
    entry = { "29: clk_enb_dev2_out:1",
              "Enable clock to DEV2 pad.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.clk_enb_dev2_out, new_value_t.clk_enb_dev2_out };
    m_bit_details_model.bits.append(entry);
    entry = { "30: clk_enb_dev1_out:1",
              "Enable clock to DEV1 pad.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.clk_enb_dev1_out, new_value_t.clk_enb_dev1_out };
    m_bit_details_model.bits.append(entry);
    entry = { "31: undefined_bit_31:1", "", 1, old_value_t.undefined_bit_31, new_value_t.undefined_bit_31 };
    m_bit_details_model.bits.append(entry);
}

#define CCLK_BURST_POLICY_OFFSET 0x20
#define CCLK_BURST_POLICY_UNDEFMASK 0x00FF0000
union cclk_burst_policy_u {
    struct {
        unsigned int cwakeup_idle_source:4; /* Same definitions as CWAKEUP_FIQ 0 = CLKM 1 = PLLC_OUT0 2 = CLKS 3 = PLLM_OUT0 4 = PLLP_OUT0 5 = PLLP_OUT4 6 = PLLP_OUT3 7 = CLKD 8 = PLLX_OUT0 */
        unsigned int cwakeup_run_source:4;  /* Same definitions as CWAKEUP_FIQ_SOURCE 0 = CLKM 1 = PLLC_OUT0 2 = CLKS 3 = PLLM_OUT0 4 = PLLP_OUT0 5 = PLLP_OUT4 6 = PLLP_OUT3 7 = CLKD 8 = PLLX_OUT0 */
        unsigned int cwakeup_irq_source:4;  /* Same definitions as CWAKEUP_FIQ_SOURCE 0 = CLKM 1 = PLLC_OUT0 2 = CLKS 3 = PLLM_OUT0 4 = PLLP_OUT0 5 = PLLP_OUT4 6 = PLLP_OUT3 7 = CLKD 8 = PLLX_OUT0 */
        unsigned int cwakeup_fiq_source:4;  /* 0000 = clk_m, 0001 = pllC_out0, 0010 = clk_s, 0011 = pllM_out0, 0100 = pllP_out0, 0101 = pllP_out4, 0110 = pllP_out3, 0111 = clk_d, 1xxx = PLLX_out0, 0 = CLKM 1 = PLLC_OUT0 2 = CLKS 3 = PLLM_OUT0 4 = PLLP_OUT0 5 = PLLP_OUT4 6 = PLLP_OUT3 7 = CLKD 8 = PLLX_OUT0 */
        unsigned int undefined_bits_16_23:8;
        unsigned int cpu_auto_cwakeup_from_irq:1;/* 0 = NOP ; 1=Burst on CPU IRQ */
        unsigned int cop_auto_cwakeup_from_irq:1;/* 0 = NOP ; 1=Burst on COP IRQ */
        unsigned int cpu_auto_cwakeup_from_fiq:1;/* 0 = NOP ; 1=Burst on CPU FIQ */
        unsigned int cop_auto_cwakeup_from_fiq:1;/* 0 = NOP ; 1=Burst on COP FIQ */
        unsigned int cpu_state:4;           /* 0000=32 kHz Clock source; 0001=IDLE Clock Source; 001X=Run clock source; 01XX=IRQ Clock Source; 1XXX=FIQ Clock Source 0 = STDBY 1 = IDLE 2 = RUN 4 = IRQ 8 = FIQ */
    };

    u_int32_t reg32;
};

void CarDev::fill_cclk_burst_policy_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const cclk_burst_policy_u old_value_t = { .reg32 = value };
    const cclk_burst_policy_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: cwakeup_idle_source:4",
              "Same definitions as CWAKEUP_FIQ\n0 = CLKM\n1 = PLLC_OUT0\n2 = CLKS\n3 = PLLM_OUT0\n4 = PLLP_OUT0\n5 = PLLP_OUT4\n6 = PLLP_OUT3\n7 = CLKD\n8 = PLLX_OUT0",
              4, old_value_t.cwakeup_idle_source, new_value_t.cwakeup_idle_source };
    m_bit_details_model.bits.append(entry);
    entry = { "04: cwakeup_run_source:4",
              "Same definitions as CWAKEUP_FIQ_SOURCE\n0 = CLKM\n1 = PLLC_OUT0\n2 = CLKS\n3 = PLLM_OUT0\n4 = PLLP_OUT0\n5 = PLLP_OUT4\n6 = PLLP_OUT3\n7 = CLKD\n8 = PLLX_OUT0",
              4, old_value_t.cwakeup_run_source, new_value_t.cwakeup_run_source };
    m_bit_details_model.bits.append(entry);
    entry = { "08: cwakeup_irq_source:4",
              "Same definitions as CWAKEUP_FIQ_SOURCE\n0 = CLKM\n1 = PLLC_OUT0\n2 = CLKS\n3 = PLLM_OUT0\n4 = PLLP_OUT0\n5 = PLLP_OUT4\n6 = PLLP_OUT3\n7 = CLKD\n8 = PLLX_OUT0",
              4, old_value_t.cwakeup_irq_source, new_value_t.cwakeup_irq_source };
    m_bit_details_model.bits.append(entry);
    entry = { "12: cwakeup_fiq_source:4",
              "0000 = clk_m,\n0001 = pllC_out0,\n0010 = clk_s,\n0011 = pllM_out0,\n0100 = pllP_out0,\n0101 = pllP_out4,\n0110 = pllP_out3,\n0111 = clk_d, 1xxx = PLLX_out0,\n0 = CLKM\n1 = PLLC_OUT0\n2 = CLKS\n3 = PLLM_OUT0\n4 = PLLP_OUT0\n5 = PLLP_OUT4\n6 = PLLP_OUT3\n7 = CLKD\n8 = PLLX_OUT0",
              4, old_value_t.cwakeup_fiq_source, new_value_t.cwakeup_fiq_source };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_23:8", "", 8, old_value_t.undefined_bits_16_23, new_value_t.undefined_bits_16_23 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: cpu_auto_cwakeup_from_irq:1",
              "0 = NOP ;\n1=Burst on CPU IRQ",
              1, old_value_t.cpu_auto_cwakeup_from_irq, new_value_t.cpu_auto_cwakeup_from_irq };
    m_bit_details_model.bits.append(entry);
    entry = { "25: cop_auto_cwakeup_from_irq:1",
              "0 = NOP ;\n1=Burst on COP IRQ",
              1, old_value_t.cop_auto_cwakeup_from_irq, new_value_t.cop_auto_cwakeup_from_irq };
    m_bit_details_model.bits.append(entry);
    entry = { "26: cpu_auto_cwakeup_from_fiq:1",
              "0 = NOP ;\n1=Burst on CPU FIQ",
              1, old_value_t.cpu_auto_cwakeup_from_fiq, new_value_t.cpu_auto_cwakeup_from_fiq };
    m_bit_details_model.bits.append(entry);
    entry = { "27: cop_auto_cwakeup_from_fiq:1",
              "0 = NOP ;\n1=Burst on COP FIQ",
              1, old_value_t.cop_auto_cwakeup_from_fiq, new_value_t.cop_auto_cwakeup_from_fiq };
    m_bit_details_model.bits.append(entry);
    entry = { "28: cpu_state:4",
              "0000=32 kHz Clock source;\n0001=IDLE Clock Source; 001X=Run clock source; 01XX=IRQ Clock Source; 1XXX=FIQ Clock Source\n0 = STDBY\n1 = IDLE\n2 = RUN\n4 = IRQ\n8 = FIQ",
              4, old_value_t.cpu_state, new_value_t.cpu_state };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "CPU (CCLK) and COP/System (SCLK) Clock Control\nHere, the Cortex-A9 CPU Complex is referred to as CPU while ARM7 is referred to as COP. The clock control mechanism for CPU and COP/system are identical. Each CCLK and SCLK clock domain can have 5 states. They are SUSP (suspend) where the clock source is 32 kHz, and normal states (IDLE, RUN, IRQ, FIQ). Each of the normal states can be selected by SW from 8 different clock sources. Furthermore, if any of the CPU/COP FIQ/IRQ bit is enabled, a hardware auto trigger feature will be enabled such that HW will jump from any state to IRQ or to FIQ automatically. Of course, if the source is from a PLL, SW needs to guarantee that the PLL clock is running and stable before changing clock sources.\nThere are many usage models that can be derived from this mechanism: For example:\n    * SW can simply just keep changing the clock source to one state (i.e. just CWAKEUP_IDLE_SOURCE) without changing the CPU_STATE field.\n    * SW can have the concept of multiple states by first setup CWAKEUP__SOURCE and then just keep changing CPU_STATE field.\n    * SW can enable HW auto detect of IRQ/FIQ to jump to IRQ or FIQ state.\nNote:\n Whenever clock source is switched, there is about a 400-600ns time where clock will be stopped.\nCCLK and SCLK Super Clock Divider Control\nThe super clock divider allows a very fine tune of clock frequency going to CPU and COP/system using clock skipping technique. It's different from traditional divider (1/n) in that both the numerator and denominator are programmable (m/n). Both the numerator and denominator are 8-bits each. Thus, \"effective\" frequency = source frequency * (m/n). Furthermore, if any of the CPU/COP FIQ/IRQ bit is enabled, hardware will auto disable the super clock divider functionality.\nThere are many usage models that can be derived from this mechanism. For example:\n    * It has no clock source switching penalty. SW can just pick a PLL output as a max frequency source via CCLK/SCLK_BURST_POLICY and just keep changing SUPER_CCLK/SCLK_DIVIDER to yield the desire lower \"effective\" frequency.\n    * For application where the \"osc\" or \"osc*2\" frequency is more than sufficient to do the job. PLLs can be turned off to save power and super clock divider can further divide down the \"osc\" or \"osc*2\" clock to yield even more power saving.\n    * If auto IRQ/FIQ feature is enabled, CCLK/SCLK will automatically jump back to full frequency to handle high priority interrupt routine.\nNote:\n From a dynamic voltage scaling (DVS) standpoint, the full clock frequency source (not the output frequency of the super clock divider) going into the super clock divider should be used to determine how low one can lower the voltage.\nIf m > n, the resulting super clock divider output frequency will simply be the same as the input frequency. In other words, there will be no clock skip or divide down.";
}

#define SUPER_CCLK_DIVIDER_OFFSET 0x24
#define SUPER_CCLK_DIVIDER_UNDEFMASK 0x70FF0000
union super_cclk_divider_u {
    struct {
        unsigned int super_cdiv_divisor:8;  /* Actual value = n + 1 */
        unsigned int super_cdiv_dividend:8; /* Actual value = n + 1 */
        unsigned int undefined_bits_16_23:8;
        unsigned int super_cdiv_dis_from_cpu_irq:1;/* 0 = enable IRQ, disable IRQ */
        unsigned int super_cdiv_dis_from_cop_irq:1;/* 0 = enable IRQ, disable IRQ */
        unsigned int super_cdiv_dis_from_cpu_fiq:1;/* 0 = enable FIQ, disable FIQ */
        unsigned int super_cdiv_dis_from_cop_fiq:1;/* 0 = enable FIQ, disable FIQ */
        unsigned int undefined_bits_28_30:3;
        unsigned int super_cdiv_enb:1;      /* 0 = disable divider. 0 = DISABLE 1 = ENABLE */
    };

    u_int32_t reg32;
};

void CarDev::fill_super_cclk_divider_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const super_cclk_divider_u old_value_t = { .reg32 = value };
    const super_cclk_divider_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: super_cdiv_divisor:8",
              "Actual value = n + 1",
              8, old_value_t.super_cdiv_divisor, new_value_t.super_cdiv_divisor };
    m_bit_details_model.bits.append(entry);
    entry = { "08: super_cdiv_dividend:8",
              "Actual value = n + 1",
              8, old_value_t.super_cdiv_dividend, new_value_t.super_cdiv_dividend };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_23:8", "", 8, old_value_t.undefined_bits_16_23, new_value_t.undefined_bits_16_23 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: super_cdiv_dis_from_cpu_irq:1",
              "0 = enable IRQ, disable IRQ",
              1, old_value_t.super_cdiv_dis_from_cpu_irq, new_value_t.super_cdiv_dis_from_cpu_irq };
    m_bit_details_model.bits.append(entry);
    entry = { "25: super_cdiv_dis_from_cop_irq:1",
              "0 = enable IRQ, disable IRQ",
              1, old_value_t.super_cdiv_dis_from_cop_irq, new_value_t.super_cdiv_dis_from_cop_irq };
    m_bit_details_model.bits.append(entry);
    entry = { "26: super_cdiv_dis_from_cpu_fiq:1",
              "0 = enable FIQ, disable FIQ",
              1, old_value_t.super_cdiv_dis_from_cpu_fiq, new_value_t.super_cdiv_dis_from_cpu_fiq };
    m_bit_details_model.bits.append(entry);
    entry = { "27: super_cdiv_dis_from_cop_fiq:1",
              "0 = enable FIQ, disable FIQ",
              1, old_value_t.super_cdiv_dis_from_cop_fiq, new_value_t.super_cdiv_dis_from_cop_fiq };
    m_bit_details_model.bits.append(entry);
    entry = { "28: undefined_bits_28_30:3", "", 3, old_value_t.undefined_bits_28_30, new_value_t.undefined_bits_28_30 };
    m_bit_details_model.bits.append(entry);
    entry = { "31: super_cdiv_enb:1",
              "0 = disable divider.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.super_cdiv_enb, new_value_t.super_cdiv_enb };
    m_bit_details_model.bits.append(entry);
}

#define SCLK_BURST_POLICY_OFFSET 0x28
#define SCLK_BURST_POLICY_UNDEFMASK 0x00FF8888
union sclk_burst_policy_u {
    struct {
        unsigned int swakeup_idle_source:3; /* Same definitions as SWAKEUP_FIQ_SOURCE 0 = CLKM 1 = PLLC_OUT1 2 = PLLP_OUT4 3 = PLLP_OUT3 4 = PLLP_OUT2 5 = CLKD 6 = CLKS 7 = PLLM_OUT1 */
        unsigned int undefined_bit_3:1;
        unsigned int swakeup_run_source:3;  /* Same definitions as SWAKEUP_FIQ_SOURCE 0 = CLKM 1 = PLLC_OUT1 2 = PLLP_OUT4 3 = PLLP_OUT3 4 = PLLP_OUT2 5 = CLKD 6 = CLKS 7 = PLLM_OUT1 */
        unsigned int undefined_bit_7:1;
        unsigned int swakeup_irq_source:3;  /* Same definitions as SWAKEUP_FIQ_SOURCE 0 = CLKM 1 = PLLC_OUT1 2 = PLLP_OUT4 3 = PLLP_OUT3 4 = PLLP_OUT2 5 = CLKD 6 = CLKS 7 = PLLM_OUT1 */
        unsigned int undefined_bit_11:1;
        unsigned int swakeup_fiq_source:3;  /* 000 = clk_m, 001 = pllC_out1, 010 = pllP_out4, 011 = pllP_out3, 100 = pllP_out2, 101 = clk_d, 110 = clk_s, 111 = pllM_out1, 0 = CLKM 1 = PLLC_OUT1 2 = PLLP_OUT4 3 = PLLP_OUT3 4 = PLLP_OUT2 5 = CLKD 6 = CLKS 7 = PLLM_OUT1 */
        unsigned int undefined_bits_15_23:9;
        unsigned int cpu_auto_swakeup_from_irq:1;/* 0 = NOP ; 1=Burst on CPU IRQ */
        unsigned int cop_auto_swakeup_from_irq:1;/* 0 = NOP ; 1=Burst on COP IRQ */
        unsigned int cpu_auto_swakeup_from_fiq:1;/* 0 = NOP ; 1=Burst on CPU FIQ */
        unsigned int cop_auto_swakeup_from_fiq:1;/* 0 = NOP ; 1=Burst on COP FIQ */
        unsigned int sys_state:4;           /* 0000=32 kHz Clock source; 0001=IDLE Clock Source; 001X=Run clock source; 01XX=IRQ Clock Source; 1XXX=FIQ Clock Source 0 = STDBY 1 = IDLE 2 = RUN 4 = IRQ 8 = FIQ */
    };

    u_int32_t reg32;
};

void CarDev::fill_sclk_burst_policy_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const sclk_burst_policy_u old_value_t = { .reg32 = value };
    const sclk_burst_policy_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: swakeup_idle_source:3",
              "Same definitions as SWAKEUP_FIQ_SOURCE\n0 = CLKM\n1 = PLLC_OUT1\n2 = PLLP_OUT4\n3 = PLLP_OUT3\n4 = PLLP_OUT2\n5 = CLKD\n6 = CLKS\n7 = PLLM_OUT1",
              3, old_value_t.swakeup_idle_source, new_value_t.swakeup_idle_source };
    m_bit_details_model.bits.append(entry);
    entry = { "03: undefined_bit_3:1", "", 1, old_value_t.undefined_bit_3, new_value_t.undefined_bit_3 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: swakeup_run_source:3",
              "Same definitions as SWAKEUP_FIQ_SOURCE\n0 = CLKM\n1 = PLLC_OUT1\n2 = PLLP_OUT4\n3 = PLLP_OUT3\n4 = PLLP_OUT2\n5 = CLKD\n6 = CLKS\n7 = PLLM_OUT1",
              3, old_value_t.swakeup_run_source, new_value_t.swakeup_run_source };
    m_bit_details_model.bits.append(entry);
    entry = { "07: undefined_bit_7:1", "", 1, old_value_t.undefined_bit_7, new_value_t.undefined_bit_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: swakeup_irq_source:3",
              "Same definitions as SWAKEUP_FIQ_SOURCE\n0 = CLKM\n1 = PLLC_OUT1\n2 = PLLP_OUT4\n3 = PLLP_OUT3\n4 = PLLP_OUT2\n5 = CLKD\n6 = CLKS\n7 = PLLM_OUT1",
              3, old_value_t.swakeup_irq_source, new_value_t.swakeup_irq_source };
    m_bit_details_model.bits.append(entry);
    entry = { "11: undefined_bit_11:1", "", 1, old_value_t.undefined_bit_11, new_value_t.undefined_bit_11 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: swakeup_fiq_source:3",
              "000 = clk_m,\n001 = pllC_out1,\n010 = pllP_out4,\n011 = pllP_out3,\n100 = pllP_out2,\n101 = clk_d,\n110 = clk_s,\n111 = pllM_out1,\n0 = CLKM\n1 = PLLC_OUT1\n2 = PLLP_OUT4\n3 = PLLP_OUT3\n4 = PLLP_OUT2\n5 = CLKD\n6 = CLKS\n7 = PLLM_OUT1",
              3, old_value_t.swakeup_fiq_source, new_value_t.swakeup_fiq_source };
    m_bit_details_model.bits.append(entry);
    entry = { "15: undefined_bits_15_23:9", "", 9, old_value_t.undefined_bits_15_23, new_value_t.undefined_bits_15_23 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: cpu_auto_swakeup_from_irq:1",
              "0 = NOP ;\n1=Burst on CPU IRQ",
              1, old_value_t.cpu_auto_swakeup_from_irq, new_value_t.cpu_auto_swakeup_from_irq };
    m_bit_details_model.bits.append(entry);
    entry = { "25: cop_auto_swakeup_from_irq:1",
              "0 = NOP ;\n1=Burst on COP IRQ",
              1, old_value_t.cop_auto_swakeup_from_irq, new_value_t.cop_auto_swakeup_from_irq };
    m_bit_details_model.bits.append(entry);
    entry = { "26: cpu_auto_swakeup_from_fiq:1",
              "0 = NOP ;\n1=Burst on CPU FIQ",
              1, old_value_t.cpu_auto_swakeup_from_fiq, new_value_t.cpu_auto_swakeup_from_fiq };
    m_bit_details_model.bits.append(entry);
    entry = { "27: cop_auto_swakeup_from_fiq:1",
              "0 = NOP ;\n1=Burst on COP FIQ",
              1, old_value_t.cop_auto_swakeup_from_fiq, new_value_t.cop_auto_swakeup_from_fiq };
    m_bit_details_model.bits.append(entry);
    entry = { "28: sys_state:4",
              "0000=32 kHz Clock source;\n0001=IDLE Clock Source; 001X=Run clock source; 01XX=IRQ Clock Source; 1XXX=FIQ Clock Source\n0 = STDBY\n1 = IDLE\n2 = RUN\n4 = IRQ\n8 = FIQ",
              4, old_value_t.sys_state, new_value_t.sys_state };
    m_bit_details_model.bits.append(entry);
}

#define SUPER_SCLK_DIVIDER_OFFSET 0x2C
#define SUPER_SCLK_DIVIDER_UNDEFMASK 0x70FF0000
union super_sclk_divider_u {
    struct {
        unsigned int super_sdiv_divisor:8;  /* Actual value = n + 1 */
        unsigned int super_sdiv_dividend:8; /* Actual value = n + 1 */
        unsigned int undefined_bits_16_23:8;
        unsigned int super_sdiv_dis_from_cpu_irq:1;/* 0 = enable IRQ, disable IRQ */
        unsigned int super_sdiv_dis_from_cop_irq:1;/* 0 = enable IRQ, disable IRQ */
        unsigned int super_sdiv_dis_from_cpu_fiq:1;/* 0 = enable FIQ, disable FIQ */
        unsigned int super_sdiv_dis_from_cop_fiq:1;/* 0 = enable FIQ, disable FIQ */
        unsigned int undefined_bits_28_30:3;
        unsigned int super_sdiv_enb:1;      /* 0 = disable divider. 0 = DISABLE 1 = ENABLE */
    };

    u_int32_t reg32;
};

void CarDev::fill_super_sclk_divider_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const super_sclk_divider_u old_value_t = { .reg32 = value };
    const super_sclk_divider_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: super_sdiv_divisor:8",
              "Actual value = n + 1",
              8, old_value_t.super_sdiv_divisor, new_value_t.super_sdiv_divisor };
    m_bit_details_model.bits.append(entry);
    entry = { "08: super_sdiv_dividend:8",
              "Actual value = n + 1",
              8, old_value_t.super_sdiv_dividend, new_value_t.super_sdiv_dividend };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_23:8", "", 8, old_value_t.undefined_bits_16_23, new_value_t.undefined_bits_16_23 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: super_sdiv_dis_from_cpu_irq:1",
              "0 = enable IRQ, disable IRQ",
              1, old_value_t.super_sdiv_dis_from_cpu_irq, new_value_t.super_sdiv_dis_from_cpu_irq };
    m_bit_details_model.bits.append(entry);
    entry = { "25: super_sdiv_dis_from_cop_irq:1",
              "0 = enable IRQ, disable IRQ",
              1, old_value_t.super_sdiv_dis_from_cop_irq, new_value_t.super_sdiv_dis_from_cop_irq };
    m_bit_details_model.bits.append(entry);
    entry = { "26: super_sdiv_dis_from_cpu_fiq:1",
              "0 = enable FIQ, disable FIQ",
              1, old_value_t.super_sdiv_dis_from_cpu_fiq, new_value_t.super_sdiv_dis_from_cpu_fiq };
    m_bit_details_model.bits.append(entry);
    entry = { "27: super_sdiv_dis_from_cop_fiq:1",
              "0 = enable FIQ, disable FIQ",
              1, old_value_t.super_sdiv_dis_from_cop_fiq, new_value_t.super_sdiv_dis_from_cop_fiq };
    m_bit_details_model.bits.append(entry);
    entry = { "28: undefined_bits_28_30:3", "", 3, old_value_t.undefined_bits_28_30, new_value_t.undefined_bits_28_30 };
    m_bit_details_model.bits.append(entry);
    entry = { "31: super_sdiv_enb:1",
              "0 = disable divider.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.super_sdiv_enb, new_value_t.super_sdiv_enb };
    m_bit_details_model.bits.append(entry);
}

#define CLK_SYSTEM_RATE_OFFSET 0x30
#define CLK_SYSTEM_RATE_UNDEFMASK 0xFFFFFF44
union clk_system_rate_u {
    struct {
        unsigned int apb_rate:2;            /* 1/(n+1) of HCLK */
        unsigned int undefined_bit_2:1;
        unsigned int pclk_dis:1;            /* 0=enable PCLK, 1=disable PCLK */
        unsigned int ahb_rate:2;            /* 1/(n+1) of SCLK */
        unsigned int undefined_bit_6:1;
        unsigned int hclk_dis:1;            /* 0=enable HCLK, 1=disable HCLK */
        unsigned int undefined_bits_8_31:24;
    };

    u_int32_t reg32;
};

void CarDev::fill_clk_system_rate_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const clk_system_rate_u old_value_t = { .reg32 = value };
    const clk_system_rate_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: apb_rate:2",
              "1/(n+1) of HCLK",
              2, old_value_t.apb_rate, new_value_t.apb_rate };
    m_bit_details_model.bits.append(entry);
    entry = { "02: undefined_bit_2:1", "", 1, old_value_t.undefined_bit_2, new_value_t.undefined_bit_2 };
    m_bit_details_model.bits.append(entry);
    entry = { "03: pclk_dis:1",
              "0=enable PCLK,\n1=disable PCLK",
              1, old_value_t.pclk_dis, new_value_t.pclk_dis };
    m_bit_details_model.bits.append(entry);
    entry = { "04: ahb_rate:2",
              "1/(n+1) of SCLK",
              2, old_value_t.ahb_rate, new_value_t.ahb_rate };
    m_bit_details_model.bits.append(entry);
    entry = { "06: undefined_bit_6:1", "", 1, old_value_t.undefined_bit_6, new_value_t.undefined_bit_6 };
    m_bit_details_model.bits.append(entry);
    entry = { "07: hclk_dis:1",
              "0=enable HCLK,\n1=disable HCLK",
              1, old_value_t.hclk_dis, new_value_t.hclk_dis };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_31:24", "", 24, old_value_t.undefined_bits_8_31, new_value_t.undefined_bits_8_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Audio Sync Clock\nThe purpose of the audio sync clock is to synchronize communication between 2 audio devices in the Tegra 2 Series devices so that it won't get into a FIFO overrun/underrun problem in either of the audio devices. For example, one can receive data from SPDIFIN and transmit the same data back out to an I2S speaker. But if SPDIFIN stream is 43.9 kHz while we are transmitting 44.1 kHz sample rate to I2S, SPDIFIN receive FIFO can get overrun while I2S transmit FIFO can get underrun.\nNote:\n There's no clock switching protection for audio sync clock so one needs to setup the desire clock source before enabling the audio transmit/receive device.\nHCLK/PCLK\nSCLK is the main system clock of the Tegra 2 Series processor which can run up-to 200 MHz.\nHCLK is the AHB clock which can run at 1, 1/2, 1/3, or 1/4 of SCLK.\nPCLK is the APB clock which can run at 1, 1/2, 1/3, or 1/4 of HCLK.";
}

#define PROG_DLY_CLK_OFFSET 0x34
#define PROG_DLY_CLK_UNDEFMASK 0xFFFF00FF
union prog_dly_clk_u {
    struct {
        unsigned int undefined_bits_0_7:8;
        unsigned int sync_clk_delclk_sel:4; /* 16 Taps of selectable delay for SYNC_CLK clk doubler */
        unsigned int clk_d_delclk_sel:4;    /* 16 Taps of selectable delay for CLK_M clk doubler */
        unsigned int undefined_bits_16_31:16;
    };

    u_int32_t reg32;
};

void CarDev::fill_prog_dly_clk_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const prog_dly_clk_u old_value_t = { .reg32 = value };
    const prog_dly_clk_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_7:8", "", 8, old_value_t.undefined_bits_0_7, new_value_t.undefined_bits_0_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: sync_clk_delclk_sel:4",
              "16 Taps of selectable delay for SYNC_CLK clk doubler",
              4, old_value_t.sync_clk_delclk_sel, new_value_t.sync_clk_delclk_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "12: clk_d_delclk_sel:4",
              "16 Taps of selectable delay for CLK_M clk doubler",
              4, old_value_t.clk_d_delclk_sel, new_value_t.clk_d_delclk_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_31:16", "", 16, old_value_t.undefined_bits_16_31, new_value_t.undefined_bits_16_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Clock Doubler\nThere are 2 clock doublers used by clock controller and PROG_DLY_CLK is used to provide programmable delay for the clock doublers.\n    * Clock double from \"osc\" clock.\n    * Clock double from \"audio sync clock\".";
}

#define AUDIO_SYNC_CLK_RATE_OFFSET 0x38
#define AUDIO_SYNC_CLK_RATE_UNDEFMASK 0xFFFFFFE0
union audio_sync_clk_rate_u {
    struct {
        unsigned int sync_clk_rate:4;       /* 0000 = SPDIFIN recovered bit clock. 0001 = I2S1 bit clock. 0010 = I2S2 bit clock. 0011 = AC97 bit clock. 0100 = pllA_out0. 0101 = external audio clock (dap_mclk2). 0110 = external audio clock (dap_mclk1). 0111 = external vimclk (vimclk). 1xxx = reserved 0 = SPDIFIN 1 = I2S1 2 = I2S2 3 = AC97 4 = PLLA_OUT0 5 = EXT_AUDIO_CLK2 6 = EXT_AUDIO_CLK1 7 = EXT_VIMCLK */
        unsigned int sync_clk_dis:1;        /* 0 = Enable AUDIO SYNC CLK */
        unsigned int undefined_bits_5_31:27;
    };

    u_int32_t reg32;
};

void CarDev::fill_audio_sync_clk_rate_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const audio_sync_clk_rate_u old_value_t = { .reg32 = value };
    const audio_sync_clk_rate_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: sync_clk_rate:4",
              "0000 = SPDIFIN recovered bit clock.\n0001 = I2S1 bit clock.\n0010 = I2S2 bit clock.\n0011 = AC97 bit clock.\n0100 = pllA_out0.\n0101 = external audio clock (dap_mclk2).\n0110 = external audio clock (dap_mclk1).\n0111 = external vimclk (vimclk). 1xxx = reserved\n0 = SPDIFIN\n1 = I2S1\n2 = I2S2\n3 = AC97\n4 = PLLA_OUT0\n5 = EXT_AUDIO_CLK2\n6 = EXT_AUDIO_CLK1\n7 = EXT_VIMCLK",
              4, old_value_t.sync_clk_rate, new_value_t.sync_clk_rate };
    m_bit_details_model.bits.append(entry);
    entry = { "04: sync_clk_dis:1",
              "0 = Enable AUDIO SYNC CLK",
              1, old_value_t.sync_clk_dis, new_value_t.sync_clk_dis };
    m_bit_details_model.bits.append(entry);
    entry = { "05: undefined_bits_5_31:27", "", 27, old_value_t.undefined_bits_5_31, new_value_t.undefined_bits_5_31 };
    m_bit_details_model.bits.append(entry);
}

#define COP_CLK_SKIP_POLICY_OFFSET 0x40
#define COP_CLK_SKIP_POLICY_UNDEFMASK 0x00FF8888
union cop_clk_skip_policy_u {
    struct {
        unsigned int cop_clk_skip_rate_idle:3;/* Same definitions as COP_CLK_SKIP_RATE_FIQ */
        unsigned int undefined_bit_3:1;
        unsigned int cop_clk_skip_rate_run:3;/* Same definitions as COP_CLK_SKIP_RATE_FIQ */
        unsigned int undefined_bit_7:1;
        unsigned int cop_clk_skip_rate_irq:3;/* Same definitions as COP_CLK_SKIP_RATE_FIQ */
        unsigned int undefined_bit_11:1;
        unsigned int cop_clk_skip_rate_fiq:3;/* skip n/16 clock */
        unsigned int undefined_bits_15_23:9;
        unsigned int cop_clk_skip_enb_from_cpu_irq:1;/* 0 = NOP ; 1=Burst on CPU IRQ */
        unsigned int cop_clk_skip_enb_from_cop_irq:1;/* 0 = NOP ; 1=Burst on COP IRQ */
        unsigned int cop_clk_skip_enb_from_cpu_fiq:1;/* 0 = NOP ; 1=Burst on CPU FIQ */
        unsigned int cop_clk_skip_enb_from_cop_fiq:1;/* 0 = NOP ; 1=Burst on COP FIQ */
        unsigned int cop_clk_skip_state:4;  /* 0000=no skip. 0001=skip base on IDLE Clock skip rate; 001X=skip base on Run clock skip rate; 01XX=skip base on IRQ Clock skip rate; 1XXX=skip base on FIQ Clock skip rate */
    };

    u_int32_t reg32;
};

void CarDev::fill_cop_clk_skip_policy_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const cop_clk_skip_policy_u old_value_t = { .reg32 = value };
    const cop_clk_skip_policy_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: cop_clk_skip_rate_idle:3",
              "Same definitions as COP_CLK_SKIP_RATE_FIQ",
              3, old_value_t.cop_clk_skip_rate_idle, new_value_t.cop_clk_skip_rate_idle };
    m_bit_details_model.bits.append(entry);
    entry = { "03: undefined_bit_3:1", "", 1, old_value_t.undefined_bit_3, new_value_t.undefined_bit_3 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: cop_clk_skip_rate_run:3",
              "Same definitions as COP_CLK_SKIP_RATE_FIQ",
              3, old_value_t.cop_clk_skip_rate_run, new_value_t.cop_clk_skip_rate_run };
    m_bit_details_model.bits.append(entry);
    entry = { "07: undefined_bit_7:1", "", 1, old_value_t.undefined_bit_7, new_value_t.undefined_bit_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: cop_clk_skip_rate_irq:3",
              "Same definitions as COP_CLK_SKIP_RATE_FIQ",
              3, old_value_t.cop_clk_skip_rate_irq, new_value_t.cop_clk_skip_rate_irq };
    m_bit_details_model.bits.append(entry);
    entry = { "11: undefined_bit_11:1", "", 1, old_value_t.undefined_bit_11, new_value_t.undefined_bit_11 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: cop_clk_skip_rate_fiq:3",
              "skip n/16 clock",
              3, old_value_t.cop_clk_skip_rate_fiq, new_value_t.cop_clk_skip_rate_fiq };
    m_bit_details_model.bits.append(entry);
    entry = { "15: undefined_bits_15_23:9", "", 9, old_value_t.undefined_bits_15_23, new_value_t.undefined_bits_15_23 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: cop_clk_skip_enb_from_cpu_irq:1",
              "0 = NOP ;\n1=Burst on CPU IRQ",
              1, old_value_t.cop_clk_skip_enb_from_cpu_irq, new_value_t.cop_clk_skip_enb_from_cpu_irq };
    m_bit_details_model.bits.append(entry);
    entry = { "25: cop_clk_skip_enb_from_cop_irq:1",
              "0 = NOP ;\n1=Burst on COP IRQ",
              1, old_value_t.cop_clk_skip_enb_from_cop_irq, new_value_t.cop_clk_skip_enb_from_cop_irq };
    m_bit_details_model.bits.append(entry);
    entry = { "26: cop_clk_skip_enb_from_cpu_fiq:1",
              "0 = NOP ;\n1=Burst on CPU FIQ",
              1, old_value_t.cop_clk_skip_enb_from_cpu_fiq, new_value_t.cop_clk_skip_enb_from_cpu_fiq };
    m_bit_details_model.bits.append(entry);
    entry = { "27: cop_clk_skip_enb_from_cop_fiq:1",
              "0 = NOP ;\n1=Burst on COP FIQ",
              1, old_value_t.cop_clk_skip_enb_from_cop_fiq, new_value_t.cop_clk_skip_enb_from_cop_fiq };
    m_bit_details_model.bits.append(entry);
    entry = { "28: cop_clk_skip_state:4",
              "0000=no skip.\n0001=skip base on IDLE Clock skip rate; 001X=skip base on Run clock skip rate; 01XX=skip base on IRQ Clock skip rate; 1XXX=skip base on FIQ Clock skip rate",
              4, old_value_t.cop_clk_skip_state, new_value_t.cop_clk_skip_state };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "COP Clock Skip\nCOP uses the same clock as the system (SCLK). The COP_CLK_SKIP_POLICY register provides a mechanism to slow down the COP without slowing down the system clock. This is done by deferring/delaying the ready signal back to the COP. Again, HW can auto detect CPU/COP IRQ/FIQ and change the skip rate as programmed by SW.";
}

#define CLK_MASK_ARM_OFFSET 0x44
#define CLK_MASK_ARM_UNDEFMASK 0x7FFCFFFC
union clk_mask_arm_u {
    struct {
        unsigned int clk_mask_cop:2;        /* 00 = no clock masking. 01 = u2_nwait_r. 10 = u2_nwait_r. 11 = no clock masking */
        unsigned int undefined_bits_2_15:14;
        unsigned int clk_mask_cpu_halt:1;   /* 1 = HW will stop clock to CPU when halt, 0 = no clock stop */
        unsigned int rst_cpu0_when_halt:1;  /*  1 = reset CPU0 when flow control assert halt. */
        unsigned int undefined_bits_18_30:13;
        unsigned int axi_flush_done:1;      /* 1 = CPU AXI pipe is flushed */
    };

    u_int32_t reg32;
};

void CarDev::fill_clk_mask_arm_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const clk_mask_arm_u old_value_t = { .reg32 = value };
    const clk_mask_arm_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: clk_mask_cop:2",
              "00 = no clock masking.\n01 = u2_nwait_r.\n10 = u2_nwait_r.\n11 = no clock masking",
              2, old_value_t.clk_mask_cop, new_value_t.clk_mask_cop };
    m_bit_details_model.bits.append(entry);
    entry = { "02: undefined_bits_2_15:14", "", 14, old_value_t.undefined_bits_2_15, new_value_t.undefined_bits_2_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: clk_mask_cpu_halt:1",
              "1 = HW will stop clock to CPU when halt,\n0 = no clock stop",
              1, old_value_t.clk_mask_cpu_halt, new_value_t.clk_mask_cpu_halt };
    m_bit_details_model.bits.append(entry);
    entry = { "17: rst_cpu0_when_halt:1",
              "1 = reset CPU0 when flow control assert halt.",
              1, old_value_t.rst_cpu0_when_halt, new_value_t.rst_cpu0_when_halt };
    m_bit_details_model.bits.append(entry);
    entry = { "18: undefined_bits_18_30:13", "", 13, old_value_t.undefined_bits_18_30, new_value_t.undefined_bits_18_30 };
    m_bit_details_model.bits.append(entry);
    entry = { "31: axi_flush_done:1",
              "1 = CPU AXI pipe is flushed",
              1, old_value_t.axi_flush_done, new_value_t.axi_flush_done };
    m_bit_details_model.bits.append(entry);
}

#define MISC_CLK_ENB_OFFSET 0x48
#define MISC_CLK_ENB_UNDEFMASK 0xEF0FFFFF
union misc_clk_enb_u {
    struct {
        unsigned int undefined_bits_0_19:20;
        unsigned int dev2_osc_div_sel:2;    /* 00 = osc, 01 = osc/2, 10 = osc/4, 11 = osc/8 */
        unsigned int dev1_osc_div_sel:2;    /* 00 = osc, 01 = osc/2, 10 = osc/4, 11 = osc/8 */
        unsigned int undefined_bits_24_27:4;
        unsigned int cfg_all_visible:1;     /* 1 = VISIBLE, 0 = NOT VISIBLE. */
        unsigned int undefined_bits_29_31:3;
    };

    u_int32_t reg32;
};

void CarDev::fill_misc_clk_enb_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const misc_clk_enb_u old_value_t = { .reg32 = value };
    const misc_clk_enb_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_19:20", "", 20, old_value_t.undefined_bits_0_19, new_value_t.undefined_bits_0_19 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: dev2_osc_div_sel:2",
              "00 = osc,\n01 = osc/2,\n10 = osc/4,\n11 = osc/8",
              2, old_value_t.dev2_osc_div_sel, new_value_t.dev2_osc_div_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "22: dev1_osc_div_sel:2",
              "00 = osc,\n01 = osc/2,\n10 = osc/4,\n11 = osc/8",
              2, old_value_t.dev1_osc_div_sel, new_value_t.dev1_osc_div_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "24: undefined_bits_24_27:4", "", 4, old_value_t.undefined_bits_24_27, new_value_t.undefined_bits_24_27 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: cfg_all_visible:1",
              "1 = VISIBLE,\n0 = NOT VISIBLE.",
              1, old_value_t.cfg_all_visible, new_value_t.cfg_all_visible };
    m_bit_details_model.bits.append(entry);
    entry = { "29: undefined_bits_29_31:3", "", 3, old_value_t.undefined_bits_29_31, new_value_t.undefined_bits_29_31 };
    m_bit_details_model.bits.append(entry);
}

#define CLK_CPU_CMPLX_OFFSET 0x4C
#define CLK_CPU_CMPLX_UNDEFMASK 0xFFFFFCFC
union clk_cpu_cmplx_u {
    struct {
        unsigned int cpu_bridge_clkdiv:2;   /* Clock divider ratio for the cpu bridge devices connected to CPU/L2-cache. 00 = div-by-1. 01 = div-by-2. 10 = div-by-3. 11 = div-by-4 */
        unsigned int undefined_bits_2_7:6;
        unsigned int cpu0_clk_stp:1;        /* 1 = CPU0 clock stop, 0 = CPU0 clock run */
        unsigned int cpu1_clk_stp:1;        /* 1 = CPU1 clock stop, 0 = CPU1 clock run */
        unsigned int undefined_bits_10_31:22;
    };

    u_int32_t reg32;
};

void CarDev::fill_clk_cpu_cmplx_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const clk_cpu_cmplx_u old_value_t = { .reg32 = value };
    const clk_cpu_cmplx_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: cpu_bridge_clkdiv:2",
              "Clock divider ratio for the cpu bridge devices connected to CPU/L2-cache.\n00 = div-by-1.\n01 = div-by-2.\n10 = div-by-3.\n11 = div-by-4",
              2, old_value_t.cpu_bridge_clkdiv, new_value_t.cpu_bridge_clkdiv };
    m_bit_details_model.bits.append(entry);
    entry = { "02: undefined_bits_2_7:6", "", 6, old_value_t.undefined_bits_2_7, new_value_t.undefined_bits_2_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: cpu0_clk_stp:1",
              "1 = CPU0 clock stop,\n0 = CPU0 clock run",
              1, old_value_t.cpu0_clk_stp, new_value_t.cpu0_clk_stp };
    m_bit_details_model.bits.append(entry);
    entry = { "09: cpu1_clk_stp:1",
              "1 = CPU1 clock stop,\n0 = CPU1 clock run",
              1, old_value_t.cpu1_clk_stp, new_value_t.cpu1_clk_stp };
    m_bit_details_model.bits.append(entry);
    entry = { "10: undefined_bits_10_31:22", "", 22, old_value_t.undefined_bits_10_31, new_value_t.undefined_bits_10_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "CPU complex consists of the CPU, L2-cache controller, and a number of bridge devices interfacing CPU/L2-cache to the rest of the system. Except the CPU, L2-cache controller, and bridge logic to external memory which always runs at non-divided-down CPU frequency, other bridge devices can run at various programmable divided-down CPU clock ratios.\nNote:\n Since the CPU clock can be selected from 1-of-9 clock sources (refer to CCLK_BURST_POLICY register), it's the user’s responsibility to not select a bridge divide down CPU clock ratio that will exceed 1/4 of the \"MAX\" CPU frequency supported.\nFor Tegra 2, the \"MAX\" CPU frequency is 1.1 GHz.";
}

#define OSC_CTRL_OFFSET 0x50
#define OSC_CTRL_UNDEFMASK 0x000E0C0C
union osc_ctrl_u {
    struct {
        unsigned int xoe:1;                 /* Crystal oscillator enable (1 = enable) */
        unsigned int xobp:1;                /* Crystal oscillator bypass enable (1 = enable bypass) */
        unsigned int undefined_bits_2_3:2;
        unsigned int xofs:6;                /* Crystal oscillator drive strength control */
        unsigned int undefined_bits_10_11:2;
        unsigned int xods:5;                /* Crystal oscillator duty cycle control */
        unsigned int undefined_bits_17_19:3;
        unsigned int oscfi_spare:8;         /* Crystal oscillator spare register control */
        unsigned int pll_ref_div:2;         /* PLL reference clock divide. 00 = /1, 01 = /2, 10 = /4, 11 = reserve */
        unsigned int osc_freq:2;            /* 00 = 13MHz, 01 = 19.2MHz, 10 = 12MHz, 11 = 26MHz */
    };

    u_int32_t reg32;
};

void CarDev::fill_osc_ctrl_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const osc_ctrl_u old_value_t = { .reg32 = value };
    const osc_ctrl_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: xoe:1",
              "Crystal oscillator enable (1 = enable)",
              1, old_value_t.xoe, new_value_t.xoe };
    m_bit_details_model.bits.append(entry);
    entry = { "01: xobp:1",
              "Crystal oscillator bypass enable (1 = enable bypass)",
              1, old_value_t.xobp, new_value_t.xobp };
    m_bit_details_model.bits.append(entry);
    entry = { "02: undefined_bits_2_3:2", "", 2, old_value_t.undefined_bits_2_3, new_value_t.undefined_bits_2_3 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: xofs:6",
              "Crystal oscillator drive strength control",
              6, old_value_t.xofs, new_value_t.xofs };
    m_bit_details_model.bits.append(entry);
    entry = { "10: undefined_bits_10_11:2", "", 2, old_value_t.undefined_bits_10_11, new_value_t.undefined_bits_10_11 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: xods:5",
              "Crystal oscillator duty cycle control",
              5, old_value_t.xods, new_value_t.xods };
    m_bit_details_model.bits.append(entry);
    entry = { "17: undefined_bits_17_19:3", "", 3, old_value_t.undefined_bits_17_19, new_value_t.undefined_bits_17_19 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: oscfi_spare:8",
              "Crystal oscillator spare register control",
              8, old_value_t.oscfi_spare, new_value_t.oscfi_spare };
    m_bit_details_model.bits.append(entry);
    entry = { "28: pll_ref_div:2",
              "PLL reference clock divide. 00 = /1, 01 = /2, 10 = /4,\n11 = reserve",
              2, old_value_t.pll_ref_div, new_value_t.pll_ref_div };
    m_bit_details_model.bits.append(entry);
    entry = { "30: osc_freq:2",
              "00 = 13MHz,\n01 = 19.2MHz,\n10 = 12MHz,\n11 = 26MHz",
              2, old_value_t.osc_freq, new_value_t.osc_freq };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Oscillator Control\n\"osc\" can have any of the four frequency (12MHz, 13MHz, 19.2MHz, 26MHz) coming in, the OSC_FREQ field provides a way for SW to tell HW what frequency is the incoming clock runs at. This information is used by hardware to auto setup the parameters (DIVN, DIVM, DIVP, CPCON, LFCON, VCOCON, DCCON, OUT1_RATIO, OUT2_RATIO, OUT3_RATIO, and OUT4_RATIO) to PLLP and its dividers. In case a frequency other than these 4 are used, there is a way to override the HW auto generated PLLP parameters.\nNote:\n Only 12 MHz required for PCIe (Tegra 250 only) operation.";
}

#define PLL_LFSR_OFFSET 0x54
#define PLL_LFSR_UNDEFMASK 0xFFFF0000
union pll_lfsr_u {
    struct {
        unsigned int rnd:16;                /* Random number generated from PLL linear feedback shift register */
        unsigned int undefined_bits_16_31:16;
    };

    u_int32_t reg32;
};

void CarDev::fill_pll_lfsr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const pll_lfsr_u old_value_t = { .reg32 = value };
    const pll_lfsr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: rnd:16",
              "Random number generated from PLL linear feedback shift register",
              16, old_value_t.rnd, new_value_t.rnd };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_31:16", "", 16, old_value_t.undefined_bits_16_31, new_value_t.undefined_bits_16_31 };
    m_bit_details_model.bits.append(entry);
}

#define OSC_FREQ_DET_OFFSET 0x58
#define OSC_FREQ_DET_UNDEFMASK 0x7FFFFFF0
union osc_freq_det_u {
    struct {
        unsigned int ref_clk_win_cfg:4;     /* Indicate the # of 32 kHz clock period as window in n+1 scheme */
        unsigned int undefined_bits_4_30:27;
        unsigned int osc_freq_det_trig:1;   /* 0 = default, 1 = enable osc frequency detect.  0 = DISABLE 1 = ENABLE */
    };

    u_int32_t reg32;
};

void CarDev::fill_osc_freq_det_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const osc_freq_det_u old_value_t = { .reg32 = value };
    const osc_freq_det_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: ref_clk_win_cfg:4",
              "Indicate the # of 32 kHz clock period as window in n+1 scheme",
              4, old_value_t.ref_clk_win_cfg, new_value_t.ref_clk_win_cfg };
    m_bit_details_model.bits.append(entry);
    entry = { "04: undefined_bits_4_30:27", "", 27, old_value_t.undefined_bits_4_30, new_value_t.undefined_bits_4_30 };
    m_bit_details_model.bits.append(entry);
    entry = { "31: osc_freq_det_trig:1",
              "0 = default,\n1 = enable osc frequency detect.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.osc_freq_det_trig, new_value_t.osc_freq_det_trig };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Oscillator Frequency Detect\n\"osc\" can have any one of the four frequency (12 MHz, 13 MHz, 19.2 MHz, 26 MHz) coming in, HW is providing a mechanism of detecting which one of the frequencies the \"osc\" is running at. To determine the \"osc\" frequency, user only needs to program the number of 32 kHz (actually, 32.768 kHz) clock periods use as a fix time window from which the \"osc\" will be used to increment a 16-bit counter and start the frequency detection process. Once the detection process is done, user can just check the 16-bit count value to determine the \"osc\" frequency.\nOSC Frequency (MHz)\n Approximate OSC_FREQ_DET_CNT (using two 32 kHz period as window)\n12.00\n 732\n13.00\n 794\n19.20\n 1172\n26.00\n 1587";
}

#define OSC_FREQ_DET_STATUS_OFFSET 0x5C
#define OSC_FREQ_DET_STATUS_UNDEFMASK 0x7FFF0000
union osc_freq_det_status_u {
    struct {
        unsigned int osc_freq_det_cnt:16;   /* indicate the number of osc count within the 32 kHz clock reference window */
        unsigned int undefined_bits_16_30:15;
        unsigned int osc_freq_det_busy:1;   /* 0 = not busy, 1 = busy */
    };

    u_int32_t reg32;
};

void CarDev::fill_osc_freq_det_status_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const osc_freq_det_status_u old_value_t = { .reg32 = value };
    const osc_freq_det_status_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: osc_freq_det_cnt:16",
              "indicate the number of osc count within the 32 kHz clock reference window",
              16, old_value_t.osc_freq_det_cnt, new_value_t.osc_freq_det_cnt };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_30:15", "", 15, old_value_t.undefined_bits_16_30, new_value_t.undefined_bits_16_30 };
    m_bit_details_model.bits.append(entry);
    entry = { "31: osc_freq_det_busy:1",
              "0 = not busy,\n1 = busy",
              1, old_value_t.osc_freq_det_busy, new_value_t.osc_freq_det_busy };
    m_bit_details_model.bits.append(entry);
}

#define PLLC_BASE_OFFSET 0x80
#define PLLC_BASE_UNDEFMASK 0x178C00E0
union pllc_base_u {
    struct {
        unsigned int pllc_divm:5;           /* PLL input divider */
        unsigned int undefined_bits_5_7:3;
        unsigned int pllc_divn:10;          /* PLL feedback divider */
        unsigned int undefined_bits_18_19:2;
        unsigned int pllc_divp:3;           /* 0 = post divider (2^n) */
        unsigned int undefined_bits_23_26:4;
        unsigned int pllc_lock:1;           /* 0 = not lock, 1 = lock */
        unsigned int undefined_bit_28:1;
        unsigned int pllc_ref_dis:1;        /* 0 = enable reference clk, 1 = disable reference clk. 0 = REF_ENABLE 1 = REF_DISABLE */
        unsigned int pllc_enable:1;         /* 0 = disable, 1 = enable. 0 = DISABLE 1 = ENABLE */
        unsigned int pllc_bypass:1;         /* 0 = no bypass, 1 = bypass. 0 = DISABLE 1 = ENABLE */
    };

    u_int32_t reg32;
};

void CarDev::fill_pllc_base_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const pllc_base_u old_value_t = { .reg32 = value };
    const pllc_base_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: pllc_divm:5",
              "PLL input divider",
              5, old_value_t.pllc_divm, new_value_t.pllc_divm };
    m_bit_details_model.bits.append(entry);
    entry = { "05: undefined_bits_5_7:3", "", 3, old_value_t.undefined_bits_5_7, new_value_t.undefined_bits_5_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: pllc_divn:10",
              "PLL feedback divider",
              10, old_value_t.pllc_divn, new_value_t.pllc_divn };
    m_bit_details_model.bits.append(entry);
    entry = { "18: undefined_bits_18_19:2", "", 2, old_value_t.undefined_bits_18_19, new_value_t.undefined_bits_18_19 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: pllc_divp:3",
              "0 = post divider (2^n)",
              3, old_value_t.pllc_divp, new_value_t.pllc_divp };
    m_bit_details_model.bits.append(entry);
    entry = { "23: undefined_bits_23_26:4", "", 4, old_value_t.undefined_bits_23_26, new_value_t.undefined_bits_23_26 };
    m_bit_details_model.bits.append(entry);
    entry = { "27: pllc_lock:1",
              "0 = not lock,\n1 = lock",
              1, old_value_t.pllc_lock, new_value_t.pllc_lock };
    m_bit_details_model.bits.append(entry);
    entry = { "28: undefined_bit_28:1", "", 1, old_value_t.undefined_bit_28, new_value_t.undefined_bit_28 };
    m_bit_details_model.bits.append(entry);
    entry = { "29: pllc_ref_dis:1",
              "0 = enable reference clk,\n1 = disable reference clk.\n0 = REF_ENABLE\n1 = REF_DISABLE",
              1, old_value_t.pllc_ref_dis, new_value_t.pllc_ref_dis };
    m_bit_details_model.bits.append(entry);
    entry = { "30: pllc_enable:1",
              "0 = disable,\n1 = enable.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.pllc_enable, new_value_t.pllc_enable };
    m_bit_details_model.bits.append(entry);
    entry = { "31: pllc_bypass:1",
              "0 = no bypass,\n1 = bypass.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.pllc_bypass, new_value_t.pllc_bypass };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "PLL Configuration\nTegra 2 has 9 PLLs controllable by clock control.\n    * \"PLLC/PLLP/PLLA\" is of type CLKPLL700_LP.\n    * \"PLLD\" is of type CLKPLL1G_MIPI.\n    * \"PLLU\" is of type CLKPLL960_USB.\n    * \"PLLM/PLLX\" are of type CLKPLL12G_LP.\n    * \"PLLE\" is of type PLL24G_SSA_CML_ESD_LP (PLLE is supported only on Tegra 250).\n.\nIn general, there are 3 requirements for each PLL that SW needs to comply with.\n    * Input frequency range (REF).\n    * Comparison frequency range (CF). CF = REF/DIVM where DIVM is the input divider control.\n    * VCO frequency range (VCO). VCO = CF * DIVN where DIVN is the feedback divider control.\nNote:\n The final PLL output frequency (FO) = VCO >> DIVP where DIVP is the post divide control.\nTable 15 PLL Requirements for software\n CLKPLL700_LP\n CLKPLL1G_MIPI\n CLKPLL12G_LP\n CLKPLL960_USB\nInput freq. (REF)\n 2-31 MHz\n 2-40 MHz\n 2-31 MHz\n 2-40 MHz\nComparison freq. (CF)\n 1-6 MHz\n 1-6 MHz\n 1-6 MHz\n 1-6 MHz\nVCO freq. (VCO)\n 20-1400 MHz\n 40-1000 MHz\n 20-1200 MHz\n 480-960 MHz\nTable 16 Charge pump current (CPCON) for CLKPLL700_LP/CLKPLL12G_LP\nN-divider\n Comparison freq.(CF)\n Charge pump current (CPCON)\n>= 200\n 1 MHz\n 4uA (1000)\n 2-3 MHz\n 2uA (0100)\n 4-6 MHz\n 1uA (0010)\n< 200\n x\n 0.5uA (0001)\nTable 17 Charge pump current (CPCON) for CLKPLL1G_MIPI/CLKPLL960_USB\nCPCON\n Description\n0000\n Charge Pump 0uA\n0001\n Charge Pump 1uA\n0010\n Charge Pump 2uA, when N-divider=50\n0011\n Charge Pump 3uA\n0100\n Charge Pump 4uA, when N-divider=300\n1000\n Charge Pump 8uA, when N-divider=600\n1100\n Charge Pump 12uA, when N-divider=1000\n1101\n Charge Pump 13uA\n1110\n Charge Pump 14uA\n1111\n Charge Pump 15uA\nTable 18 PLLP Configuration Information (reference clock is osc/clk_m and PLLP-FO is fixed at 432 MHz ).\nReference Frequency\n 13.0 MHz\n 19.2 MHz\n 12.0 MHz\n 26.0 MHz\n Resulting Frequency\nDIVN\n 432 (1b0h)\n 90 (05ah)\n 432 (1b0h)\n 432 (1b0h)\n N/A\nDIVM\n 13 (0dh)\n 4 ( 04h)\n 12 ( 0ch)\n 26 ( 1ah)\n N/A\nDIVP\n 1 (0h)\n 1 ( 0h)\n 1 ( 0h)\n 1 ( 0h)\n N/A\n CPCON\n 8 (8h)\n 1 ( 1h)\n 8 ( 8h)\n 8 ( 8h)\n N/A\n LFCON\n 0 (0h)\n 0 ( 0h)\n 0 ( 0h)\n 0 ( 0h)\n N/A\n VCOCON\n 0 (0h)\n 0 ( 0h)\n 0 ( 0h)\n 0 ( 0h)\n N/A\n DCCON\n 0 (0b)\n 0 ( 0b)\n 0 ( 0b)\n 0 ( 0b)\n N/A\nOUT1 div ratio\n 15.0 (1ch)\n 15.0( 1ch)\n 15.0( 1ch)\n 15.0( 1ch)\n 28.8MHz.\nOUT2 div ratio\n 9.0 (10h)\n 9.0( 10h)\n 9.0( 10h)\n 9.0( 10h)\n 48.0MHz.\nOUT3 div ratio\n 6.0 (0ah)\n 6.0( 0ah)\n 6.0( 0ah)\n 6.0( 0ah)\n 72.0MHz.\nOUT4 div ratio\n  4.0 (06h)\n 4.0( 06h)\n 4.0( 06h)\n 4.0( 06h)\n 108.0MHz.\nTable 19 PLLA configuration information (reference clock is taken from PLLP_OUT1 = 28.8 MHz).\nAudio Frequency\n 56.448 MHz\n 73.728 MHz\n 11.2896 MHz\n 12.2880 MHz\nDIVN\n 49 (031h)\n 64 (040h)\n 49 (031h)\n 64 (040h)\nAudio Frequency\n 56.448 MHz\n 73.728 MHz\n 11.2896 MHz\n 12.2880 MHz\nDIVM\n 25 (19h)\n 25 (19h)\n 25 (19h)\n 25 (19h)\nDIVP\n 1 (0h)\n 1 (0h)\n 1 (0h)\n 1 (0h)\nOUT0 div ratio\n 1.0 (0h)\n 1.0 (0h)\n 5.0 (08h)\n 6.0 (0ah)\nTable 20 PLLU configuration information (reference clock is osc/clk_m and PLLU-FOs are fixed at 12 MHz/60 MHz/480 MHz).\nReference Frequency\n 13.0 MHz\n 19.2 MHz\n 12.0 MHz\n 26.0 MHz\nDIVN\n 960 (3c0h)\n 200 (0c8h)\n 960 (3c0h)\n 960 (3c0h)\nDIVM\n 13 (0dh)\n 4 (04h)\n 12 (0ch)\n 26 (1ah)\nTable 21 PLLD configuration information (reference clock is osc/clk_m and PLLD-FO is max of 1GHz).\nReference Frequency\n 13.0 MHz\n 19.2 MHz\n 12.0 MHz\n 26.0 MHz\nDIVN\n 1000(3e8h)\n 625 (271h)\n 1000(3e8h)\n 1000(3e8h)\nDIVM\n 13 (0dh)\n 12 (0ch)\n 12 (0ch)\n 26 (1ah)\nDIVP\n 1 (0h)\n 1 (0h)\n 1 (0h)\n 1 (0h)\nTable 22 PLLE configuration information (reference clock is osc/clk_m and PLLE-FO is 100 MHz).\nReference Frequency\n 12.0 MHz\nNDIV\n 200 (c8h)\nMDIV\n 1 (0h)\nPLDIV\n 24 (18h)\nPLDIV_CML\n  (dh)\nTable 23 Special Consideration when Using PLLX as a Clock Source for the CPU\n(1) PLLX is physically located at the same power partition as the CPU and thus will be powered down when the CPU partition is powered-down. Therefore, if PLLX is used as a clock source for the CPU before power-down, then PLLX must be re-initialized after the CPU is powered back up.\n(2) If hardware detects that PLLX is used as a clock source for the CPU when CPU partition is powering down, it will reset the following registers to its default value automatically.\n    * CCLK_BURST_POLICY.\n    * SUPER_CCLK_DIVIDER.\n    * PLLX_BASE.\n    * PLLX_MISC.";
}

#define PLLC_OUT_OFFSET 0x84
#define PLLC_OUT_UNDEFMASK 0xFFFF00FC
union pllc_out_u {
    struct {
        unsigned int pllc_out1_rstn:1;      /* PLLC_OUT1 divider reset. 0 = reset, 1 = not reset. 0 = RESET_ENABLE 1 = RESET_DISABLE */
        unsigned int pllc_out1_clken:1;     /* PLLC_OUT1 divider clk enable. 0 = disable, 1 = enable. 0 = DISABLE 1 = ENABLE */
        unsigned int undefined_bits_2_7:6;
        unsigned int pllc_out1_ratio:8;     /* PLLC_OUT1 divider from base PLLC (lsb denote 0.5x) */
        unsigned int undefined_bits_16_31:16;
    };

    u_int32_t reg32;
};

void CarDev::fill_pllc_out_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const pllc_out_u old_value_t = { .reg32 = value };
    const pllc_out_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: pllc_out1_rstn:1",
              "PLLC_OUT1 divider reset.\n0 = reset,\n1 = not reset.\n0 = RESET_ENABLE\n1 = RESET_DISABLE",
              1, old_value_t.pllc_out1_rstn, new_value_t.pllc_out1_rstn };
    m_bit_details_model.bits.append(entry);
    entry = { "01: pllc_out1_clken:1",
              "PLLC_OUT1 divider clk enable.\n0 = disable,\n1 = enable.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.pllc_out1_clken, new_value_t.pllc_out1_clken };
    m_bit_details_model.bits.append(entry);
    entry = { "02: undefined_bits_2_7:6", "", 6, old_value_t.undefined_bits_2_7, new_value_t.undefined_bits_2_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: pllc_out1_ratio:8",
              "PLLC_OUT1 divider from base PLLC (lsb denote 0.5x)",
              8, old_value_t.pllc_out1_ratio, new_value_t.pllc_out1_ratio };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_31:16", "", 16, old_value_t.undefined_bits_16_31, new_value_t.undefined_bits_16_31 };
    m_bit_details_model.bits.append(entry);
}

#define PLLC_MISC_OFFSET 0x8C
#define PLLC_MISC_UNDEFMASK 0x3F280000
union pllc_misc_u {
    struct {
        unsigned int pllc_vcocon:4;         /* Base PLLC VCO range setup control */
        unsigned int pllc_lfcon:4;          /* Base PLLC loop filter setup control */
        unsigned int pllc_cpcon:4;          /* Base PLLC charge pump setup control */
        unsigned int pllc_lock_sel:6;       /* lock select */
        unsigned int pllc_lock_enable:1;    /* 1 = enable, 0 = disable.  0 = DISABLE 1 = ENABLE */
        unsigned int undefined_bit_19:1;
        unsigned int pllc_dccon:1;          /* Base PLLC DCCON control */
        unsigned int undefined_bit_21:1;
        unsigned int pllc_pts:2;            /* Base PLLC test output select */
        unsigned int undefined_bits_24_29:6;
        unsigned int pllc_out1_div_byp:1;   /* 1 = bypass PLLC_OUT1 divider */
        unsigned int pllc_out1_inv_clk:1;   /* 1 = invert PLLC_OUT1 clock */
    };

    u_int32_t reg32;
};

void CarDev::fill_pllc_misc_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const pllc_misc_u old_value_t = { .reg32 = value };
    const pllc_misc_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: pllc_vcocon:4",
              "Base PLLC VCO range setup control",
              4, old_value_t.pllc_vcocon, new_value_t.pllc_vcocon };
    m_bit_details_model.bits.append(entry);
    entry = { "04: pllc_lfcon:4",
              "Base PLLC loop filter setup control",
              4, old_value_t.pllc_lfcon, new_value_t.pllc_lfcon };
    m_bit_details_model.bits.append(entry);
    entry = { "08: pllc_cpcon:4",
              "Base PLLC charge pump setup control",
              4, old_value_t.pllc_cpcon, new_value_t.pllc_cpcon };
    m_bit_details_model.bits.append(entry);
    entry = { "12: pllc_lock_sel:6",
              "lock select",
              6, old_value_t.pllc_lock_sel, new_value_t.pllc_lock_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "18: pllc_lock_enable:1",
              "1 = enable,\n0 = disable.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.pllc_lock_enable, new_value_t.pllc_lock_enable };
    m_bit_details_model.bits.append(entry);
    entry = { "19: undefined_bit_19:1", "", 1, old_value_t.undefined_bit_19, new_value_t.undefined_bit_19 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: pllc_dccon:1",
              "Base PLLC DCCON control",
              1, old_value_t.pllc_dccon, new_value_t.pllc_dccon };
    m_bit_details_model.bits.append(entry);
    entry = { "21: undefined_bit_21:1", "", 1, old_value_t.undefined_bit_21, new_value_t.undefined_bit_21 };
    m_bit_details_model.bits.append(entry);
    entry = { "22: pllc_pts:2",
              "Base PLLC test output select",
              2, old_value_t.pllc_pts, new_value_t.pllc_pts };
    m_bit_details_model.bits.append(entry);
    entry = { "24: undefined_bits_24_29:6", "", 6, old_value_t.undefined_bits_24_29, new_value_t.undefined_bits_24_29 };
    m_bit_details_model.bits.append(entry);
    entry = { "30: pllc_out1_div_byp:1",
              "1 = bypass PLLC_OUT1 divider",
              1, old_value_t.pllc_out1_div_byp, new_value_t.pllc_out1_div_byp };
    m_bit_details_model.bits.append(entry);
    entry = { "31: pllc_out1_inv_clk:1",
              "1 = invert PLLC_OUT1 clock",
              1, old_value_t.pllc_out1_inv_clk, new_value_t.pllc_out1_inv_clk };
    m_bit_details_model.bits.append(entry);
}

#define PLLM_BASE_OFFSET 0x90
#define PLLM_BASE_UNDEFMASK 0x178C00E0
union pllm_base_u {
    struct {
        unsigned int pllm_divm:5;           /* PLL input divider */
        unsigned int undefined_bits_5_7:3;
        unsigned int pllm_divn:10;          /* PLL feedback divider */
        unsigned int undefined_bits_18_19:2;
        unsigned int pllm_divp:3;           /* 0 = post divider (2^n) */
        unsigned int undefined_bits_23_26:4;
        unsigned int pllm_lock:1;           /* 0 = not lock, 1 = lock */
        unsigned int undefined_bit_28:1;
        unsigned int pllm_ref_dis:1;        /* 0 = enable reference clk, 1 = disable reference clk. 0 = REF_ENABLE 1 = REF_DISABLE */
        unsigned int pllm_enable:1;         /* 0 = disable, 1 = enable. 0 = DISABLE 1 = ENABLE */
        unsigned int pllm_bypass:1;         /* 0 = no bypass, 1 = bypass. 0 = DISABLE 1 = ENABLE */
    };

    u_int32_t reg32;
};

void CarDev::fill_pllm_base_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const pllm_base_u old_value_t = { .reg32 = value };
    const pllm_base_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: pllm_divm:5",
              "PLL input divider",
              5, old_value_t.pllm_divm, new_value_t.pllm_divm };
    m_bit_details_model.bits.append(entry);
    entry = { "05: undefined_bits_5_7:3", "", 3, old_value_t.undefined_bits_5_7, new_value_t.undefined_bits_5_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: pllm_divn:10",
              "PLL feedback divider",
              10, old_value_t.pllm_divn, new_value_t.pllm_divn };
    m_bit_details_model.bits.append(entry);
    entry = { "18: undefined_bits_18_19:2", "", 2, old_value_t.undefined_bits_18_19, new_value_t.undefined_bits_18_19 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: pllm_divp:3",
              "0 = post divider (2^n)",
              3, old_value_t.pllm_divp, new_value_t.pllm_divp };
    m_bit_details_model.bits.append(entry);
    entry = { "23: undefined_bits_23_26:4", "", 4, old_value_t.undefined_bits_23_26, new_value_t.undefined_bits_23_26 };
    m_bit_details_model.bits.append(entry);
    entry = { "27: pllm_lock:1",
              "0 = not lock,\n1 = lock",
              1, old_value_t.pllm_lock, new_value_t.pllm_lock };
    m_bit_details_model.bits.append(entry);
    entry = { "28: undefined_bit_28:1", "", 1, old_value_t.undefined_bit_28, new_value_t.undefined_bit_28 };
    m_bit_details_model.bits.append(entry);
    entry = { "29: pllm_ref_dis:1",
              "0 = enable reference clk,\n1 = disable reference clk.\n0 = REF_ENABLE\n1 = REF_DISABLE",
              1, old_value_t.pllm_ref_dis, new_value_t.pllm_ref_dis };
    m_bit_details_model.bits.append(entry);
    entry = { "30: pllm_enable:1",
              "0 = disable,\n1 = enable.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.pllm_enable, new_value_t.pllm_enable };
    m_bit_details_model.bits.append(entry);
    entry = { "31: pllm_bypass:1",
              "0 = no bypass,\n1 = bypass.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.pllm_bypass, new_value_t.pllm_bypass };
    m_bit_details_model.bits.append(entry);
}

#define PLLM_OUT_OFFSET 0x94
#define PLLM_OUT_UNDEFMASK 0xFFFF00FC
union pllm_out_u {
    struct {
        unsigned int pllm_out1_rstn:1;      /* PLLM_OUT1 divider reset. 0 = reset, 1 = not reset. 0 = RESET_ENABLE 1 = RESET_DISABLE */
        unsigned int pllm_out1_clken:1;     /* PLLM_OUT1 divider clk enable. 0 = disable, 1 = enable. 0 = DISABLE 1 = ENABLE */
        unsigned int undefined_bits_2_7:6;
        unsigned int pllm_out1_ratio:8;     /* PLLM_OUT1 divider from base PLLM (lsb denote 0.5x) */
        unsigned int undefined_bits_16_31:16;
    };

    u_int32_t reg32;
};

void CarDev::fill_pllm_out_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const pllm_out_u old_value_t = { .reg32 = value };
    const pllm_out_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: pllm_out1_rstn:1",
              "PLLM_OUT1 divider reset.\n0 = reset,\n1 = not reset.\n0 = RESET_ENABLE\n1 = RESET_DISABLE",
              1, old_value_t.pllm_out1_rstn, new_value_t.pllm_out1_rstn };
    m_bit_details_model.bits.append(entry);
    entry = { "01: pllm_out1_clken:1",
              "PLLM_OUT1 divider clk enable.\n0 = disable,\n1 = enable.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.pllm_out1_clken, new_value_t.pllm_out1_clken };
    m_bit_details_model.bits.append(entry);
    entry = { "02: undefined_bits_2_7:6", "", 6, old_value_t.undefined_bits_2_7, new_value_t.undefined_bits_2_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: pllm_out1_ratio:8",
              "PLLM_OUT1 divider from base PLLM (lsb denote 0.5x)",
              8, old_value_t.pllm_out1_ratio, new_value_t.pllm_out1_ratio };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_31:16", "", 16, old_value_t.undefined_bits_16_31, new_value_t.undefined_bits_16_31 };
    m_bit_details_model.bits.append(entry);
}

#define PLLM_MISC_OFFSET 0x9C
#define PLLM_MISC_UNDEFMASK 0x30280000
union pllm_misc_u {
    struct {
        unsigned int pllm_vcocon:4;         /* Base PLLM VCO range setup control */
        unsigned int pllm_lfcon:4;          /* Base PLLM loop filter setup control */
        unsigned int pllm_cpcon:4;          /* Base PLLM charge pump setup control */
        unsigned int pllm_lock_sel:6;       /* lock select */
        unsigned int pllm_lock_enable:1;    /* 1 = enable, 0 = disable.  0 = DISABLE 1 = ENABLE */
        unsigned int undefined_bit_19:1;
        unsigned int pllm_dccon:1;          /* Base PLLM DCCON control */
        unsigned int undefined_bit_21:1;
        unsigned int pllm_pts:2;            /* Base PLLM test output select */
        unsigned int pllm_setup:4;          /* Base PLLM setup */
        unsigned int undefined_bits_28_29:2;
        unsigned int pllm_out1_div_byp:1;   /* 1 = bypass PLLM_OUT1 divider */
        unsigned int pllm_out1_inv_clk:1;   /* 1 = invert PLLM_OUT1 clock */
    };

    u_int32_t reg32;
};

void CarDev::fill_pllm_misc_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const pllm_misc_u old_value_t = { .reg32 = value };
    const pllm_misc_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: pllm_vcocon:4",
              "Base PLLM VCO range setup control",
              4, old_value_t.pllm_vcocon, new_value_t.pllm_vcocon };
    m_bit_details_model.bits.append(entry);
    entry = { "04: pllm_lfcon:4",
              "Base PLLM loop filter setup control",
              4, old_value_t.pllm_lfcon, new_value_t.pllm_lfcon };
    m_bit_details_model.bits.append(entry);
    entry = { "08: pllm_cpcon:4",
              "Base PLLM charge pump setup control",
              4, old_value_t.pllm_cpcon, new_value_t.pllm_cpcon };
    m_bit_details_model.bits.append(entry);
    entry = { "12: pllm_lock_sel:6",
              "lock select",
              6, old_value_t.pllm_lock_sel, new_value_t.pllm_lock_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "18: pllm_lock_enable:1",
              "1 = enable,\n0 = disable.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.pllm_lock_enable, new_value_t.pllm_lock_enable };
    m_bit_details_model.bits.append(entry);
    entry = { "19: undefined_bit_19:1", "", 1, old_value_t.undefined_bit_19, new_value_t.undefined_bit_19 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: pllm_dccon:1",
              "Base PLLM DCCON control",
              1, old_value_t.pllm_dccon, new_value_t.pllm_dccon };
    m_bit_details_model.bits.append(entry);
    entry = { "21: undefined_bit_21:1", "", 1, old_value_t.undefined_bit_21, new_value_t.undefined_bit_21 };
    m_bit_details_model.bits.append(entry);
    entry = { "22: pllm_pts:2",
              "Base PLLM test output select",
              2, old_value_t.pllm_pts, new_value_t.pllm_pts };
    m_bit_details_model.bits.append(entry);
    entry = { "24: pllm_setup:4",
              "Base PLLM setup",
              4, old_value_t.pllm_setup, new_value_t.pllm_setup };
    m_bit_details_model.bits.append(entry);
    entry = { "28: undefined_bits_28_29:2", "", 2, old_value_t.undefined_bits_28_29, new_value_t.undefined_bits_28_29 };
    m_bit_details_model.bits.append(entry);
    entry = { "30: pllm_out1_div_byp:1",
              "1 = bypass PLLM_OUT1 divider",
              1, old_value_t.pllm_out1_div_byp, new_value_t.pllm_out1_div_byp };
    m_bit_details_model.bits.append(entry);
    entry = { "31: pllm_out1_inv_clk:1",
              "1 = invert PLLM_OUT1 clock",
              1, old_value_t.pllm_out1_inv_clk, new_value_t.pllm_out1_inv_clk };
    m_bit_details_model.bits.append(entry);
}

#define PLLP_BASE_OFFSET 0xA0
#define PLLP_BASE_UNDEFMASK 0x078C00E0
union pllp_base_u {
    struct {
        unsigned int pllp_divm:5;           /* PLL input divider */
        unsigned int undefined_bits_5_7:3;
        unsigned int pllp_divn:10;          /* PLL feedback divider */
        unsigned int undefined_bits_18_19:2;
        unsigned int pllp_divp:3;           /* 0 = post divider (2^n) */
        unsigned int undefined_bits_23_26:4;
        unsigned int pllp_lock:1;           /* 0 = not lock, 1 = lock */
        unsigned int pllp_base_ovrride:1;   /* 0 = disallow base override , 1 = allow base override. 0 = DISABLE 1 = ENABLE */
        unsigned int pllp_ref_dis:1;        /* 0 = enable reference clk, 1 = disable reference clk. 0 = REF_ENABLE 1 = REF_DISABLE */
        unsigned int pllp_enable:1;         /* 0 = disable, 1 = enable. 0 = DISABLE 1 = ENABLE */
        unsigned int pllp_bypass:1;         /* 0 = no bypass, 1 = bypass. 0 = DISABLE 1 = ENABLE */
    };

    u_int32_t reg32;
};

void CarDev::fill_pllp_base_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const pllp_base_u old_value_t = { .reg32 = value };
    const pllp_base_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: pllp_divm:5",
              "PLL input divider",
              5, old_value_t.pllp_divm, new_value_t.pllp_divm };
    m_bit_details_model.bits.append(entry);
    entry = { "05: undefined_bits_5_7:3", "", 3, old_value_t.undefined_bits_5_7, new_value_t.undefined_bits_5_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: pllp_divn:10",
              "PLL feedback divider",
              10, old_value_t.pllp_divn, new_value_t.pllp_divn };
    m_bit_details_model.bits.append(entry);
    entry = { "18: undefined_bits_18_19:2", "", 2, old_value_t.undefined_bits_18_19, new_value_t.undefined_bits_18_19 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: pllp_divp:3",
              "0 = post divider (2^n)",
              3, old_value_t.pllp_divp, new_value_t.pllp_divp };
    m_bit_details_model.bits.append(entry);
    entry = { "23: undefined_bits_23_26:4", "", 4, old_value_t.undefined_bits_23_26, new_value_t.undefined_bits_23_26 };
    m_bit_details_model.bits.append(entry);
    entry = { "27: pllp_lock:1",
              "0 = not lock,\n1 = lock",
              1, old_value_t.pllp_lock, new_value_t.pllp_lock };
    m_bit_details_model.bits.append(entry);
    entry = { "28: pllp_base_ovrride:1",
              "0 = disallow base override ,\n1 = allow base override.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.pllp_base_ovrride, new_value_t.pllp_base_ovrride };
    m_bit_details_model.bits.append(entry);
    entry = { "29: pllp_ref_dis:1",
              "0 = enable reference clk,\n1 = disable reference clk.\n0 = REF_ENABLE\n1 = REF_DISABLE",
              1, old_value_t.pllp_ref_dis, new_value_t.pllp_ref_dis };
    m_bit_details_model.bits.append(entry);
    entry = { "30: pllp_enable:1",
              "0 = disable,\n1 = enable.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.pllp_enable, new_value_t.pllp_enable };
    m_bit_details_model.bits.append(entry);
    entry = { "31: pllp_bypass:1",
              "0 = no bypass,\n1 = bypass.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.pllp_bypass, new_value_t.pllp_bypass };
    m_bit_details_model.bits.append(entry);
}

#define PLLP_OUTA_OFFSET 0xA4
#define PLLP_OUTA_UNDEFMASK 0x00F800F8
union pllp_outa_u {
    struct {
        unsigned int pllp_out1_rstn:1;      /* PLLP_OUT1 divider reset. 0 = reset, 1 = not reset. 0 = RESET_ENABLE 1 = RESET_DISABLE */
        unsigned int pllp_out1_clken:1;     /* PLLP_OUT1 divider clk enable. 0 = disable, 1 = enable. 0 = DISABLE 1 = ENABLE */
        unsigned int pllp_out1_ovrride:1;   /* 0 = disallow PLLP_OUT1 ratio override, 1 = enable override. 0 = DISABLE 1 = ENABLE */
        unsigned int undefined_bits_3_7:5;
        unsigned int pllp_out1_ratio:8;     /* PLLP_OUT1 divider from base PLLP (lsb denote 0.5x) */
        unsigned int pllp_out2_rstn:1;      /* PLLP_OUT2 divider reset. 0 = reset, 1 = not reset. 0 = RESET_ENABLE 1 = RESET_DISABLE */
        unsigned int pllp_out2_clken:1;     /* PLLP_OUT2 divider clk enable. 0 = disable, 1 = enable. 0 = DISABLE 1 = ENABLE */
        unsigned int pllp_out2_ovrride:1;   /* 0 = disallow PLLP_OUT2 ratio override, 1 = enable override. 0 = DISABLE 1 = ENABLE */
        unsigned int undefined_bits_19_23:5;
        unsigned int pllp_out2_ratio:8;     /* PLLP_OUT2 divider from base PLLP (lsb denote 0.5x) */
    };

    u_int32_t reg32;
};

void CarDev::fill_pllp_outa_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const pllp_outa_u old_value_t = { .reg32 = value };
    const pllp_outa_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: pllp_out1_rstn:1",
              "PLLP_OUT1 divider reset.\n0 = reset,\n1 = not reset.\n0 = RESET_ENABLE\n1 = RESET_DISABLE",
              1, old_value_t.pllp_out1_rstn, new_value_t.pllp_out1_rstn };
    m_bit_details_model.bits.append(entry);
    entry = { "01: pllp_out1_clken:1",
              "PLLP_OUT1 divider clk enable.\n0 = disable,\n1 = enable.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.pllp_out1_clken, new_value_t.pllp_out1_clken };
    m_bit_details_model.bits.append(entry);
    entry = { "02: pllp_out1_ovrride:1",
              "0 = disallow PLLP_OUT1 ratio override,\n1 = enable override.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.pllp_out1_ovrride, new_value_t.pllp_out1_ovrride };
    m_bit_details_model.bits.append(entry);
    entry = { "03: undefined_bits_3_7:5", "", 5, old_value_t.undefined_bits_3_7, new_value_t.undefined_bits_3_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: pllp_out1_ratio:8",
              "PLLP_OUT1 divider from base PLLP (lsb denote 0.5x)",
              8, old_value_t.pllp_out1_ratio, new_value_t.pllp_out1_ratio };
    m_bit_details_model.bits.append(entry);
    entry = { "16: pllp_out2_rstn:1",
              "PLLP_OUT2 divider reset.\n0 = reset,\n1 = not reset.\n0 = RESET_ENABLE\n1 = RESET_DISABLE",
              1, old_value_t.pllp_out2_rstn, new_value_t.pllp_out2_rstn };
    m_bit_details_model.bits.append(entry);
    entry = { "17: pllp_out2_clken:1",
              "PLLP_OUT2 divider clk enable.\n0 = disable,\n1 = enable.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.pllp_out2_clken, new_value_t.pllp_out2_clken };
    m_bit_details_model.bits.append(entry);
    entry = { "18: pllp_out2_ovrride:1",
              "0 = disallow PLLP_OUT2 ratio override,\n1 = enable override.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.pllp_out2_ovrride, new_value_t.pllp_out2_ovrride };
    m_bit_details_model.bits.append(entry);
    entry = { "19: undefined_bits_19_23:5", "", 5, old_value_t.undefined_bits_19_23, new_value_t.undefined_bits_19_23 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: pllp_out2_ratio:8",
              "PLLP_OUT2 divider from base PLLP (lsb denote 0.5x)",
              8, old_value_t.pllp_out2_ratio, new_value_t.pllp_out2_ratio };
    m_bit_details_model.bits.append(entry);
}

#define PLLP_OUTB_OFFSET 0xA8
#define PLLP_OUTB_UNDEFMASK 0x00F800F8
union pllp_outb_u {
    struct {
        unsigned int pllp_out3_rstn:1;      /* PLLP_OUT3 divider reset. 0 = reset, 1 = not reset. 0 = RESET_ENABLE 1 = RESET_DISABLE */
        unsigned int pllp_out3_clken:1;     /* PLLP_OUT3 divider clk enable. 0 = disable, 1 = enable. 0 = DISABLE 1 = ENABLE */
        unsigned int pllp_out3_ovrride:1;   /* 0 = disallow PLLP_OUT3 ratio override, 1 = enable override. 0 = DISABLE 1 = ENABLE */
        unsigned int undefined_bits_3_7:5;
        unsigned int pllp_out3_ratio:8;     /* PLLP_OUT3 divider from base PLLP (lsb denote 0.5x) */
        unsigned int pllp_out4_rstn:1;      /* PLLP_OUT4 divider reset. 0 = reset, 1 = not reset. 0 = RESET_ENABLE 1 = RESET_DISABLE */
        unsigned int pllp_out4_clken:1;     /* PLLP_OUT4 divider clk enable. 0 = disable, 1 = enable. 0 = DISABLE 1 = ENABLE */
        unsigned int pllp_out4_ovrride:1;   /* 0 = disallow PLLP_OUT4 ratio override, 1 = enable override. 0 = DISABLE 1 = ENABLE */
        unsigned int undefined_bits_19_23:5;
        unsigned int pllp_out4_ratio:8;     /* PLLP_OUT4 divider from base PLLP (lsb denote 0.5x) */
    };

    u_int32_t reg32;
};

void CarDev::fill_pllp_outb_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const pllp_outb_u old_value_t = { .reg32 = value };
    const pllp_outb_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: pllp_out3_rstn:1",
              "PLLP_OUT3 divider reset.\n0 = reset,\n1 = not reset.\n0 = RESET_ENABLE\n1 = RESET_DISABLE",
              1, old_value_t.pllp_out3_rstn, new_value_t.pllp_out3_rstn };
    m_bit_details_model.bits.append(entry);
    entry = { "01: pllp_out3_clken:1",
              "PLLP_OUT3 divider clk enable.\n0 = disable,\n1 = enable.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.pllp_out3_clken, new_value_t.pllp_out3_clken };
    m_bit_details_model.bits.append(entry);
    entry = { "02: pllp_out3_ovrride:1",
              "0 = disallow PLLP_OUT3 ratio override,\n1 = enable override.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.pllp_out3_ovrride, new_value_t.pllp_out3_ovrride };
    m_bit_details_model.bits.append(entry);
    entry = { "03: undefined_bits_3_7:5", "", 5, old_value_t.undefined_bits_3_7, new_value_t.undefined_bits_3_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: pllp_out3_ratio:8",
              "PLLP_OUT3 divider from base PLLP (lsb denote 0.5x)",
              8, old_value_t.pllp_out3_ratio, new_value_t.pllp_out3_ratio };
    m_bit_details_model.bits.append(entry);
    entry = { "16: pllp_out4_rstn:1",
              "PLLP_OUT4 divider reset.\n0 = reset,\n1 = not reset.\n0 = RESET_ENABLE\n1 = RESET_DISABLE",
              1, old_value_t.pllp_out4_rstn, new_value_t.pllp_out4_rstn };
    m_bit_details_model.bits.append(entry);
    entry = { "17: pllp_out4_clken:1",
              "PLLP_OUT4 divider clk enable.\n0 = disable,\n1 = enable.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.pllp_out4_clken, new_value_t.pllp_out4_clken };
    m_bit_details_model.bits.append(entry);
    entry = { "18: pllp_out4_ovrride:1",
              "0 = disallow PLLP_OUT4 ratio override,\n1 = enable override.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.pllp_out4_ovrride, new_value_t.pllp_out4_ovrride };
    m_bit_details_model.bits.append(entry);
    entry = { "19: undefined_bits_19_23:5", "", 5, old_value_t.undefined_bits_19_23, new_value_t.undefined_bits_19_23 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: pllp_out4_ratio:8",
              "PLLP_OUT4 divider from base PLLP (lsb denote 0.5x)",
              8, old_value_t.pllp_out4_ratio, new_value_t.pllp_out4_ratio };
    m_bit_details_model.bits.append(entry);
}

#define PLLP_MISC_OFFSET 0xAC
#define PLLP_MISC_UNDEFMASK 0x00280000
union pllp_misc_u {
    struct {
        unsigned int pllp_vcocon:4;         /* Base PLLP VCO range setup control */
        unsigned int pllp_lfcon:4;          /* Base PLLP loop filter setup control */
        unsigned int pllp_cpcon:4;          /* Base PLLP charge pump setup control */
        unsigned int pllp_lock_sel:6;       /* lock select */
        unsigned int pllp_lock_enable:1;    /* 1 = enable, 0 = disable.  0 = DISABLE 1 = ENABLE */
        unsigned int undefined_bit_19:1;
        unsigned int pllp_dccon:1;          /* Base PLLP DCCON control */
        unsigned int undefined_bit_21:1;
        unsigned int pllp_pts:2;            /* Base PLLP test output select */
        unsigned int pllp_out1_div_byp:1;   /* 1 = bypass PLLP_OUT1 divider */
        unsigned int pllp_out2_div_byp:1;   /* 1 = bypass PLLP_OUT2 divider */
        unsigned int pllp_out3_div_byp:1;   /* 1 = bypass PLLP_OUT3 divider */
        unsigned int pllp_out4_div_byp:1;   /* 1 = bypass PLLP_OUT4 divider */
        unsigned int pllp_out1_inv_clk:1;   /* 1 = invert PLLP_OUT1 clock */
        unsigned int pllp_out2_inv_clk:1;   /* 1 = invert PLLP_OUT2 clock */
        unsigned int pllp_out3_inv_clk:1;   /* 1 = invert PLLP_OUT3 clock */
        unsigned int pllp_out4_inv_clk:1;   /* 1 = invert PLLP_OUT4 clock */
    };

    u_int32_t reg32;
};

void CarDev::fill_pllp_misc_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const pllp_misc_u old_value_t = { .reg32 = value };
    const pllp_misc_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: pllp_vcocon:4",
              "Base PLLP VCO range setup control",
              4, old_value_t.pllp_vcocon, new_value_t.pllp_vcocon };
    m_bit_details_model.bits.append(entry);
    entry = { "04: pllp_lfcon:4",
              "Base PLLP loop filter setup control",
              4, old_value_t.pllp_lfcon, new_value_t.pllp_lfcon };
    m_bit_details_model.bits.append(entry);
    entry = { "08: pllp_cpcon:4",
              "Base PLLP charge pump setup control",
              4, old_value_t.pllp_cpcon, new_value_t.pllp_cpcon };
    m_bit_details_model.bits.append(entry);
    entry = { "12: pllp_lock_sel:6",
              "lock select",
              6, old_value_t.pllp_lock_sel, new_value_t.pllp_lock_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "18: pllp_lock_enable:1",
              "1 = enable,\n0 = disable.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.pllp_lock_enable, new_value_t.pllp_lock_enable };
    m_bit_details_model.bits.append(entry);
    entry = { "19: undefined_bit_19:1", "", 1, old_value_t.undefined_bit_19, new_value_t.undefined_bit_19 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: pllp_dccon:1",
              "Base PLLP DCCON control",
              1, old_value_t.pllp_dccon, new_value_t.pllp_dccon };
    m_bit_details_model.bits.append(entry);
    entry = { "21: undefined_bit_21:1", "", 1, old_value_t.undefined_bit_21, new_value_t.undefined_bit_21 };
    m_bit_details_model.bits.append(entry);
    entry = { "22: pllp_pts:2",
              "Base PLLP test output select",
              2, old_value_t.pllp_pts, new_value_t.pllp_pts };
    m_bit_details_model.bits.append(entry);
    entry = { "24: pllp_out1_div_byp:1",
              "1 = bypass PLLP_OUT1 divider",
              1, old_value_t.pllp_out1_div_byp, new_value_t.pllp_out1_div_byp };
    m_bit_details_model.bits.append(entry);
    entry = { "25: pllp_out2_div_byp:1",
              "1 = bypass PLLP_OUT2 divider",
              1, old_value_t.pllp_out2_div_byp, new_value_t.pllp_out2_div_byp };
    m_bit_details_model.bits.append(entry);
    entry = { "26: pllp_out3_div_byp:1",
              "1 = bypass PLLP_OUT3 divider",
              1, old_value_t.pllp_out3_div_byp, new_value_t.pllp_out3_div_byp };
    m_bit_details_model.bits.append(entry);
    entry = { "27: pllp_out4_div_byp:1",
              "1 = bypass PLLP_OUT4 divider",
              1, old_value_t.pllp_out4_div_byp, new_value_t.pllp_out4_div_byp };
    m_bit_details_model.bits.append(entry);
    entry = { "28: pllp_out1_inv_clk:1",
              "1 = invert PLLP_OUT1 clock",
              1, old_value_t.pllp_out1_inv_clk, new_value_t.pllp_out1_inv_clk };
    m_bit_details_model.bits.append(entry);
    entry = { "29: pllp_out2_inv_clk:1",
              "1 = invert PLLP_OUT2 clock",
              1, old_value_t.pllp_out2_inv_clk, new_value_t.pllp_out2_inv_clk };
    m_bit_details_model.bits.append(entry);
    entry = { "30: pllp_out3_inv_clk:1",
              "1 = invert PLLP_OUT3 clock",
              1, old_value_t.pllp_out3_inv_clk, new_value_t.pllp_out3_inv_clk };
    m_bit_details_model.bits.append(entry);
    entry = { "31: pllp_out4_inv_clk:1",
              "1 = invert PLLP_OUT4 clock",
              1, old_value_t.pllp_out4_inv_clk, new_value_t.pllp_out4_inv_clk };
    m_bit_details_model.bits.append(entry);
}

#define PLLA_BASE_OFFSET 0xB0
#define PLLA_BASE_UNDEFMASK 0x178C00E0
union plla_base_u {
    struct {
        unsigned int plla_divm:5;           /* PLL input divider */
        unsigned int undefined_bits_5_7:3;
        unsigned int plla_divn:10;          /* PLL feedback divider */
        unsigned int undefined_bits_18_19:2;
        unsigned int plla_divp:3;           /* 0 = post divider (2^n) */
        unsigned int undefined_bits_23_26:4;
        unsigned int plla_lock:1;           /* 0 = not lock, 1 = lock */
        unsigned int undefined_bit_28:1;
        unsigned int plla_ref_dis:1;        /* 0 = enable reference clk, 1 = disable reference clk. 0 = REF_ENABLE 1 = REF_DISABLE */
        unsigned int plla_enable:1;         /* 0 = disable, 1 = enable. 0 = DISABLE 1 = ENABLE */
        unsigned int plla_bypass:1;         /* 0 = no bypass, 1 = bypass. 0 = DISABLE 1 = ENABLE */
    };

    u_int32_t reg32;
};

void CarDev::fill_plla_base_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const plla_base_u old_value_t = { .reg32 = value };
    const plla_base_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: plla_divm:5",
              "PLL input divider",
              5, old_value_t.plla_divm, new_value_t.plla_divm };
    m_bit_details_model.bits.append(entry);
    entry = { "05: undefined_bits_5_7:3", "", 3, old_value_t.undefined_bits_5_7, new_value_t.undefined_bits_5_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: plla_divn:10",
              "PLL feedback divider",
              10, old_value_t.plla_divn, new_value_t.plla_divn };
    m_bit_details_model.bits.append(entry);
    entry = { "18: undefined_bits_18_19:2", "", 2, old_value_t.undefined_bits_18_19, new_value_t.undefined_bits_18_19 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: plla_divp:3",
              "0 = post divider (2^n)",
              3, old_value_t.plla_divp, new_value_t.plla_divp };
    m_bit_details_model.bits.append(entry);
    entry = { "23: undefined_bits_23_26:4", "", 4, old_value_t.undefined_bits_23_26, new_value_t.undefined_bits_23_26 };
    m_bit_details_model.bits.append(entry);
    entry = { "27: plla_lock:1",
              "0 = not lock,\n1 = lock",
              1, old_value_t.plla_lock, new_value_t.plla_lock };
    m_bit_details_model.bits.append(entry);
    entry = { "28: undefined_bit_28:1", "", 1, old_value_t.undefined_bit_28, new_value_t.undefined_bit_28 };
    m_bit_details_model.bits.append(entry);
    entry = { "29: plla_ref_dis:1",
              "0 = enable reference clk,\n1 = disable reference clk.\n0 = REF_ENABLE\n1 = REF_DISABLE",
              1, old_value_t.plla_ref_dis, new_value_t.plla_ref_dis };
    m_bit_details_model.bits.append(entry);
    entry = { "30: plla_enable:1",
              "0 = disable,\n1 = enable.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.plla_enable, new_value_t.plla_enable };
    m_bit_details_model.bits.append(entry);
    entry = { "31: plla_bypass:1",
              "0 = no bypass,\n1 = bypass.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.plla_bypass, new_value_t.plla_bypass };
    m_bit_details_model.bits.append(entry);
}

#define PLLA_OUT_OFFSET 0xB4
#define PLLA_OUT_UNDEFMASK 0xFFFF00FC
union plla_out_u {
    struct {
        unsigned int plla_out0_rstn:1;      /* PLLA_OUT0 divider reset. 0 = reset, 1 = not reset. 0 = RESET_ENABLE 1 = RESET_DISABLE */
        unsigned int plla_out0_clken:1;     /* PLLA_OUT0 divider clk enable. 0 = disable, 1 = enable. 0 = DISABLE 1 = ENABLE */
        unsigned int undefined_bits_2_7:6;
        unsigned int plla_out0_ratio:8;     /* PLLA_OUT0 divider from base PLLA (lsb denote 0.5x). 0 = DISABLE 1 = ENABLE */
        unsigned int undefined_bits_16_31:16;
    };

    u_int32_t reg32;
};

void CarDev::fill_plla_out_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const plla_out_u old_value_t = { .reg32 = value };
    const plla_out_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: plla_out0_rstn:1",
              "PLLA_OUT0 divider reset.\n0 = reset,\n1 = not reset.\n0 = RESET_ENABLE\n1 = RESET_DISABLE",
              1, old_value_t.plla_out0_rstn, new_value_t.plla_out0_rstn };
    m_bit_details_model.bits.append(entry);
    entry = { "01: plla_out0_clken:1",
              "PLLA_OUT0 divider clk enable.\n0 = disable,\n1 = enable.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.plla_out0_clken, new_value_t.plla_out0_clken };
    m_bit_details_model.bits.append(entry);
    entry = { "02: undefined_bits_2_7:6", "", 6, old_value_t.undefined_bits_2_7, new_value_t.undefined_bits_2_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: plla_out0_ratio:8",
              "PLLA_OUT0 divider from base PLLA (lsb denote 0.5x).\n0 = DISABLE\n1 = ENABLE",
              8, old_value_t.plla_out0_ratio, new_value_t.plla_out0_ratio };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_31:16", "", 16, old_value_t.undefined_bits_16_31, new_value_t.undefined_bits_16_31 };
    m_bit_details_model.bits.append(entry);
}

#define PLLA_MISC_OFFSET 0xBC
#define PLLA_MISC_UNDEFMASK 0x3F280000
union plla_misc_u {
    struct {
        unsigned int plla_vcocon:4;         /* Base PLLA VCO range setup control */
        unsigned int plla_lfcon:4;          /* Base PLLA loop filter setup control */
        unsigned int plla_cpcon:4;          /* Base PLLA charge pump setup control */
        unsigned int plla_lock_sel:6;       /* lock select */
        unsigned int plla_lock_enable:1;    /* 1 = enable, 0 = disable.  0 = DISABLE 1 = ENABLE */
        unsigned int undefined_bit_19:1;
        unsigned int plla_dccon:1;          /* Base PLLA DCCON control */
        unsigned int undefined_bit_21:1;
        unsigned int plla_pts:2;            /* Base PLLA test output select */
        unsigned int undefined_bits_24_29:6;
        unsigned int plla_out0_div_byp:1;   /* 1 = bypass PLLA_OUT0 divider */
        unsigned int plla_out0_inv_clk:1;   /* 1 = invert PLLA_OUT0 clock */
    };

    u_int32_t reg32;
};

void CarDev::fill_plla_misc_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const plla_misc_u old_value_t = { .reg32 = value };
    const plla_misc_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: plla_vcocon:4",
              "Base PLLA VCO range setup control",
              4, old_value_t.plla_vcocon, new_value_t.plla_vcocon };
    m_bit_details_model.bits.append(entry);
    entry = { "04: plla_lfcon:4",
              "Base PLLA loop filter setup control",
              4, old_value_t.plla_lfcon, new_value_t.plla_lfcon };
    m_bit_details_model.bits.append(entry);
    entry = { "08: plla_cpcon:4",
              "Base PLLA charge pump setup control",
              4, old_value_t.plla_cpcon, new_value_t.plla_cpcon };
    m_bit_details_model.bits.append(entry);
    entry = { "12: plla_lock_sel:6",
              "lock select",
              6, old_value_t.plla_lock_sel, new_value_t.plla_lock_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "18: plla_lock_enable:1",
              "1 = enable,\n0 = disable.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.plla_lock_enable, new_value_t.plla_lock_enable };
    m_bit_details_model.bits.append(entry);
    entry = { "19: undefined_bit_19:1", "", 1, old_value_t.undefined_bit_19, new_value_t.undefined_bit_19 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: plla_dccon:1",
              "Base PLLA DCCON control",
              1, old_value_t.plla_dccon, new_value_t.plla_dccon };
    m_bit_details_model.bits.append(entry);
    entry = { "21: undefined_bit_21:1", "", 1, old_value_t.undefined_bit_21, new_value_t.undefined_bit_21 };
    m_bit_details_model.bits.append(entry);
    entry = { "22: plla_pts:2",
              "Base PLLA test output select",
              2, old_value_t.plla_pts, new_value_t.plla_pts };
    m_bit_details_model.bits.append(entry);
    entry = { "24: undefined_bits_24_29:6", "", 6, old_value_t.undefined_bits_24_29, new_value_t.undefined_bits_24_29 };
    m_bit_details_model.bits.append(entry);
    entry = { "30: plla_out0_div_byp:1",
              "1 = bypass PLLA_OUT0 divider",
              1, old_value_t.plla_out0_div_byp, new_value_t.plla_out0_div_byp };
    m_bit_details_model.bits.append(entry);
    entry = { "31: plla_out0_inv_clk:1",
              "1 = invert PLLA_OUT0 clock",
              1, old_value_t.plla_out0_inv_clk, new_value_t.plla_out0_inv_clk };
    m_bit_details_model.bits.append(entry);
}

#define PLLU_BASE_OFFSET 0xC0
#define PLLU_BASE_UNDEFMASK 0x160C00E0
union pllu_base_u {
    struct {
        unsigned int pllu_divm:5;           /* PLL input divider */
        unsigned int undefined_bits_5_7:3;
        unsigned int pllu_divn:10;          /* PLL feedback divider */
        unsigned int undefined_bits_18_19:2;
        unsigned int pllu_vco_freq:1;       /* 0 = post-div of 2, 1 = post-div of 1 */
        unsigned int pllu_clkenable_usb:1;  /* FO_USB output enable. This bit is used only when PLLU_OVERRIDE bit is set. Otherwise, USB controllers will control this automatically. 0 = disable, 1 = enable */
        unsigned int pllu_clkenable_hsic:1; /* FO_HSIC output enable. This bit is used only when PLLU_OVERRIDE bit is set. Otherwise, USB controllers will control this automatically. 0 = disable, 1 = enable */
        unsigned int pllu_clkenable_icusb:1;/* FO_ICUSB output enable. This bit is use only when PLLU_OVERRIDE bit is set */
        unsigned int pllu_override:1;       /* 0 = FO_[ICUSB,HSIC,USB] controlled by USB controllers, 1 = controlled by PLLU_CLKENABLEs. */
        unsigned int undefined_bits_25_26:2;
        unsigned int pllu_lock:1;           /* 0 = not lock, 1 = lock */
        unsigned int undefined_bit_28:1;
        unsigned int pllu_ref_dis:1;        /* 0 = enable reference clk, 1 = disable reference clk. 0 = REF_ENABLE 1 = REF_DISABLE */
        unsigned int pllu_enable:1;         /* 0 = disable, 1 = enable. This bit is used only when PLLU_OVERRIDE bit is set. 0 = DISABLE 1 = ENABLE */
        unsigned int pllu_bypass:1;         /* 0 = no bypass, 1 = bypass. 0 = DISABLE 1 = ENABLE */
    };

    u_int32_t reg32;
};

void CarDev::fill_pllu_base_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const pllu_base_u old_value_t = { .reg32 = value };
    const pllu_base_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: pllu_divm:5",
              "PLL input divider",
              5, old_value_t.pllu_divm, new_value_t.pllu_divm };
    m_bit_details_model.bits.append(entry);
    entry = { "05: undefined_bits_5_7:3", "", 3, old_value_t.undefined_bits_5_7, new_value_t.undefined_bits_5_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: pllu_divn:10",
              "PLL feedback divider",
              10, old_value_t.pllu_divn, new_value_t.pllu_divn };
    m_bit_details_model.bits.append(entry);
    entry = { "18: undefined_bits_18_19:2", "", 2, old_value_t.undefined_bits_18_19, new_value_t.undefined_bits_18_19 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: pllu_vco_freq:1",
              "0 = post-div of 2,\n1 = post-div of 1",
              1, old_value_t.pllu_vco_freq, new_value_t.pllu_vco_freq };
    m_bit_details_model.bits.append(entry);
    entry = { "21: pllu_clkenable_usb:1",
              "FO_USB output enable. This bit is used only when PLLU_OVERRIDE bit is set. Otherwise, USB controllers will control this automatically.\n0 = disable,\n1 = enable",
              1, old_value_t.pllu_clkenable_usb, new_value_t.pllu_clkenable_usb };
    m_bit_details_model.bits.append(entry);
    entry = { "22: pllu_clkenable_hsic:1",
              "FO_HSIC output enable. This bit is used only when PLLU_OVERRIDE bit is set. Otherwise, USB controllers will control this automatically.\n0 = disable,\n1 = enable",
              1, old_value_t.pllu_clkenable_hsic, new_value_t.pllu_clkenable_hsic };
    m_bit_details_model.bits.append(entry);
    entry = { "23: pllu_clkenable_icusb:1",
              "FO_ICUSB output enable. This bit is use only when PLLU_OVERRIDE bit is set",
              1, old_value_t.pllu_clkenable_icusb, new_value_t.pllu_clkenable_icusb };
    m_bit_details_model.bits.append(entry);
    entry = { "24: pllu_override:1",
              "0 = FO_[ICUSB,HSIC,USB] controlled by USB controllers,\n1 = controlled by PLLU_CLKENABLEs.",
              1, old_value_t.pllu_override, new_value_t.pllu_override };
    m_bit_details_model.bits.append(entry);
    entry = { "25: undefined_bits_25_26:2", "", 2, old_value_t.undefined_bits_25_26, new_value_t.undefined_bits_25_26 };
    m_bit_details_model.bits.append(entry);
    entry = { "27: pllu_lock:1",
              "0 = not lock,\n1 = lock",
              1, old_value_t.pllu_lock, new_value_t.pllu_lock };
    m_bit_details_model.bits.append(entry);
    entry = { "28: undefined_bit_28:1", "", 1, old_value_t.undefined_bit_28, new_value_t.undefined_bit_28 };
    m_bit_details_model.bits.append(entry);
    entry = { "29: pllu_ref_dis:1",
              "0 = enable reference clk,\n1 = disable reference clk.\n0 = REF_ENABLE\n1 = REF_DISABLE",
              1, old_value_t.pllu_ref_dis, new_value_t.pllu_ref_dis };
    m_bit_details_model.bits.append(entry);
    entry = { "30: pllu_enable:1",
              "0 = disable,\n1 = enable. This bit is used only when PLLU_OVERRIDE bit is set.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.pllu_enable, new_value_t.pllu_enable };
    m_bit_details_model.bits.append(entry);
    entry = { "31: pllu_bypass:1",
              "0 = no bypass,\n1 = bypass.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.pllu_bypass, new_value_t.pllu_bypass };
    m_bit_details_model.bits.append(entry);
}

#define PLLU_MISC_OFFSET 0xCC
#define PLLU_MISC_UNDEFMASK 0xC7BC0000
union pllu_misc_u {
    struct {
        unsigned int pllu_vcocon:4;         /* Base PLLU VCO range setup control */
        unsigned int pllu_lfcon:4;          /* Base PLLU loop filter setup control */
        unsigned int pllu_cpcon:4;          /* Base PLLU charge pump setup control */
        unsigned int pllu_lock_sel:6;       /* lock select */
        unsigned int undefined_bits_18_21:4;
        unsigned int pllu_lock_enable:1;    /* 1 = enable, 0 = disable.  0 = DISABLE 1 = ENABLE */
        unsigned int undefined_bits_23_26:4;
        unsigned int pllu_pts:3;            /* Base PLLU test output select */
        unsigned int undefined_bits_30_31:2;
    };

    u_int32_t reg32;
};

void CarDev::fill_pllu_misc_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const pllu_misc_u old_value_t = { .reg32 = value };
    const pllu_misc_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: pllu_vcocon:4",
              "Base PLLU VCO range setup control",
              4, old_value_t.pllu_vcocon, new_value_t.pllu_vcocon };
    m_bit_details_model.bits.append(entry);
    entry = { "04: pllu_lfcon:4",
              "Base PLLU loop filter setup control",
              4, old_value_t.pllu_lfcon, new_value_t.pllu_lfcon };
    m_bit_details_model.bits.append(entry);
    entry = { "08: pllu_cpcon:4",
              "Base PLLU charge pump setup control",
              4, old_value_t.pllu_cpcon, new_value_t.pllu_cpcon };
    m_bit_details_model.bits.append(entry);
    entry = { "12: pllu_lock_sel:6",
              "lock select",
              6, old_value_t.pllu_lock_sel, new_value_t.pllu_lock_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "18: undefined_bits_18_21:4", "", 4, old_value_t.undefined_bits_18_21, new_value_t.undefined_bits_18_21 };
    m_bit_details_model.bits.append(entry);
    entry = { "22: pllu_lock_enable:1",
              "1 = enable,\n0 = disable.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.pllu_lock_enable, new_value_t.pllu_lock_enable };
    m_bit_details_model.bits.append(entry);
    entry = { "23: undefined_bits_23_26:4", "", 4, old_value_t.undefined_bits_23_26, new_value_t.undefined_bits_23_26 };
    m_bit_details_model.bits.append(entry);
    entry = { "27: pllu_pts:3",
              "Base PLLU test output select",
              3, old_value_t.pllu_pts, new_value_t.pllu_pts };
    m_bit_details_model.bits.append(entry);
    entry = { "30: undefined_bits_30_31:2", "", 2, old_value_t.undefined_bits_30_31, new_value_t.undefined_bits_30_31 };
    m_bit_details_model.bits.append(entry);
}

#define PLLD_BASE_OFFSET 0xD0
#define PLLD_BASE_UNDEFMASK 0x178C00E0
union plld_base_u {
    struct {
        unsigned int plld_divm:5;           /* PLL input divider */
        unsigned int undefined_bits_5_7:3;
        unsigned int plld_divn:10;          /* PLL feedback divider */
        unsigned int undefined_bits_18_19:2;
        unsigned int plld_divp:3;           /* 0 = post divider (2^n) */
        unsigned int undefined_bits_23_26:4;
        unsigned int plld_lock:1;           /* 0 = not lock, 1 = lock */
        unsigned int undefined_bit_28:1;
        unsigned int plld_ref_dis:1;        /* 0 = enable reference clk, 1 = disable reference clk. 0 = REF_ENABLE 1 = REF_DISABLE */
        unsigned int plld_enable:1;         /* 0 = disable, 1 = enable. 0 = DISABLE 1 = ENABLE */
        unsigned int plld_bypass:1;         /* 0 = no bypass, 1 = bypass. 0 = DISABLE 1 = ENABLE */
    };

    u_int32_t reg32;
};

void CarDev::fill_plld_base_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const plld_base_u old_value_t = { .reg32 = value };
    const plld_base_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: plld_divm:5",
              "PLL input divider",
              5, old_value_t.plld_divm, new_value_t.plld_divm };
    m_bit_details_model.bits.append(entry);
    entry = { "05: undefined_bits_5_7:3", "", 3, old_value_t.undefined_bits_5_7, new_value_t.undefined_bits_5_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: plld_divn:10",
              "PLL feedback divider",
              10, old_value_t.plld_divn, new_value_t.plld_divn };
    m_bit_details_model.bits.append(entry);
    entry = { "18: undefined_bits_18_19:2", "", 2, old_value_t.undefined_bits_18_19, new_value_t.undefined_bits_18_19 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: plld_divp:3",
              "0 = post divider (2^n)",
              3, old_value_t.plld_divp, new_value_t.plld_divp };
    m_bit_details_model.bits.append(entry);
    entry = { "23: undefined_bits_23_26:4", "", 4, old_value_t.undefined_bits_23_26, new_value_t.undefined_bits_23_26 };
    m_bit_details_model.bits.append(entry);
    entry = { "27: plld_lock:1",
              "0 = not lock,\n1 = lock",
              1, old_value_t.plld_lock, new_value_t.plld_lock };
    m_bit_details_model.bits.append(entry);
    entry = { "28: undefined_bit_28:1", "", 1, old_value_t.undefined_bit_28, new_value_t.undefined_bit_28 };
    m_bit_details_model.bits.append(entry);
    entry = { "29: plld_ref_dis:1",
              "0 = enable reference clk,\n1 = disable reference clk.\n0 = REF_ENABLE\n1 = REF_DISABLE",
              1, old_value_t.plld_ref_dis, new_value_t.plld_ref_dis };
    m_bit_details_model.bits.append(entry);
    entry = { "30: plld_enable:1",
              "0 = disable,\n1 = enable.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.plld_enable, new_value_t.plld_enable };
    m_bit_details_model.bits.append(entry);
    entry = { "31: plld_bypass:1",
              "0 = no bypass,\n1 = bypass.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.plld_bypass, new_value_t.plld_bypass };
    m_bit_details_model.bits.append(entry);
}

#define PLLD_MISC_OFFSET 0xDC
#define PLLD_MISC_UNDEFMASK 0x00000000
union plld_misc_u {
    struct {
        unsigned int plld_vcocon:4;         /* Base PLLD VCO range setup control */
        unsigned int plld_lfcon:4;          /* Base PLLD loop filter setup control */
        unsigned int plld_cpcon:4;          /* Base PLLD charge pump setup control */
        unsigned int plld_dccon:4;          /* Base PLLD DCCON control */
        unsigned int plld_lock_sel:6;       /* lock select */
        unsigned int plld_lock_enable:1;    /* 1 = enable, 0 = disable.  0 = DISABLE 1 = ENABLE */
        unsigned int plld_div_rst:1;        /* 0 = normal operation, 1 = reset */
        unsigned int plld_loadadj:3;        /* load pulse position adjust */
        unsigned int plld_pts:3;            /* Base PLLD test output select */
        unsigned int plld_clkenable:1;      /* 0 = disable, 1 = normal operation */
        unsigned int plld_fo_mode:1;        /* 1 = 5-125MHz, 0 = 40-1000MHz */
    };

    u_int32_t reg32;
};

void CarDev::fill_plld_misc_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const plld_misc_u old_value_t = { .reg32 = value };
    const plld_misc_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: plld_vcocon:4",
              "Base PLLD VCO range setup control",
              4, old_value_t.plld_vcocon, new_value_t.plld_vcocon };
    m_bit_details_model.bits.append(entry);
    entry = { "04: plld_lfcon:4",
              "Base PLLD loop filter setup control",
              4, old_value_t.plld_lfcon, new_value_t.plld_lfcon };
    m_bit_details_model.bits.append(entry);
    entry = { "08: plld_cpcon:4",
              "Base PLLD charge pump setup control",
              4, old_value_t.plld_cpcon, new_value_t.plld_cpcon };
    m_bit_details_model.bits.append(entry);
    entry = { "12: plld_dccon:4",
              "Base PLLD DCCON control",
              4, old_value_t.plld_dccon, new_value_t.plld_dccon };
    m_bit_details_model.bits.append(entry);
    entry = { "16: plld_lock_sel:6",
              "lock select",
              6, old_value_t.plld_lock_sel, new_value_t.plld_lock_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "22: plld_lock_enable:1",
              "1 = enable,\n0 = disable.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.plld_lock_enable, new_value_t.plld_lock_enable };
    m_bit_details_model.bits.append(entry);
    entry = { "23: plld_div_rst:1",
              "0 = normal operation,\n1 = reset",
              1, old_value_t.plld_div_rst, new_value_t.plld_div_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "24: plld_loadadj:3",
              "load pulse position adjust",
              3, old_value_t.plld_loadadj, new_value_t.plld_loadadj };
    m_bit_details_model.bits.append(entry);
    entry = { "27: plld_pts:3",
              "Base PLLD test output select",
              3, old_value_t.plld_pts, new_value_t.plld_pts };
    m_bit_details_model.bits.append(entry);
    entry = { "30: plld_clkenable:1",
              "0 = disable,\n1 = normal operation",
              1, old_value_t.plld_clkenable, new_value_t.plld_clkenable };
    m_bit_details_model.bits.append(entry);
    entry = { "31: plld_fo_mode:1",
              "1 = 5-125MHz,\n0 = 40-1000MHz",
              1, old_value_t.plld_fo_mode, new_value_t.plld_fo_mode };
    m_bit_details_model.bits.append(entry);
}

#define PLLX_BASE_OFFSET 0xE0
#define PLLX_BASE_UNDEFMASK 0x178C00E0
union pllx_base_u {
    struct {
        unsigned int pllx_divm:5;           /* PLL input divider */
        unsigned int undefined_bits_5_7:3;
        unsigned int pllx_divn:10;          /* PLL feedback divider */
        unsigned int undefined_bits_18_19:2;
        unsigned int pllx_divp:3;           /* 0 = post divider (2^n) */
        unsigned int undefined_bits_23_26:4;
        unsigned int pllx_lock:1;           /* 0 = not lock, 1 = lock */
        unsigned int undefined_bit_28:1;
        unsigned int pllx_ref_dis:1;        /* 0 = enable reference clk, 1 = disable reference clk. 0 = REF_ENABLE 1 = REF_DISABLE */
        unsigned int pllx_enable:1;         /* 0 = disable, 1 = enable. 0 = DISABLE 1 = ENABLE */
        unsigned int pllx_bypass:1;         /* 0 = no bypass, 1 = bypass. 0 = DISABLE 1 = ENABLE */
    };

    u_int32_t reg32;
};

void CarDev::fill_pllx_base_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const pllx_base_u old_value_t = { .reg32 = value };
    const pllx_base_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: pllx_divm:5",
              "PLL input divider",
              5, old_value_t.pllx_divm, new_value_t.pllx_divm };
    m_bit_details_model.bits.append(entry);
    entry = { "05: undefined_bits_5_7:3", "", 3, old_value_t.undefined_bits_5_7, new_value_t.undefined_bits_5_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: pllx_divn:10",
              "PLL feedback divider",
              10, old_value_t.pllx_divn, new_value_t.pllx_divn };
    m_bit_details_model.bits.append(entry);
    entry = { "18: undefined_bits_18_19:2", "", 2, old_value_t.undefined_bits_18_19, new_value_t.undefined_bits_18_19 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: pllx_divp:3",
              "0 = post divider (2^n)",
              3, old_value_t.pllx_divp, new_value_t.pllx_divp };
    m_bit_details_model.bits.append(entry);
    entry = { "23: undefined_bits_23_26:4", "", 4, old_value_t.undefined_bits_23_26, new_value_t.undefined_bits_23_26 };
    m_bit_details_model.bits.append(entry);
    entry = { "27: pllx_lock:1",
              "0 = not lock,\n1 = lock",
              1, old_value_t.pllx_lock, new_value_t.pllx_lock };
    m_bit_details_model.bits.append(entry);
    entry = { "28: undefined_bit_28:1", "", 1, old_value_t.undefined_bit_28, new_value_t.undefined_bit_28 };
    m_bit_details_model.bits.append(entry);
    entry = { "29: pllx_ref_dis:1",
              "0 = enable reference clk,\n1 = disable reference clk.\n0 = REF_ENABLE\n1 = REF_DISABLE",
              1, old_value_t.pllx_ref_dis, new_value_t.pllx_ref_dis };
    m_bit_details_model.bits.append(entry);
    entry = { "30: pllx_enable:1",
              "0 = disable,\n1 = enable.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.pllx_enable, new_value_t.pllx_enable };
    m_bit_details_model.bits.append(entry);
    entry = { "31: pllx_bypass:1",
              "0 = no bypass,\n1 = bypass.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.pllx_bypass, new_value_t.pllx_bypass };
    m_bit_details_model.bits.append(entry);
}

#define PLLX_MISC_OFFSET 0xE4
#define PLLX_MISC_UNDEFMASK 0xF0280000
union pllx_misc_u {
    struct {
        unsigned int pllx_vcocon:4;         /* Base PLLX VCO range setup control */
        unsigned int pllx_lfcon:4;          /* Base PLLX loop filter setup control */
        unsigned int pllx_cpcon:4;          /* Base PLLX charge pump setup control */
        unsigned int pllx_lock_sel:6;       /* lock select */
        unsigned int pllx_lock_enable:1;    /* 1 = enable, 0 = disable.  0 = DISABLE 1 = ENABLE */
        unsigned int undefined_bit_19:1;
        unsigned int pllx_dccon:1;          /* Base PLLX DCCON control */
        unsigned int undefined_bit_21:1;
        unsigned int pllx_pts:2;            /* Base PLLX test output select */
        unsigned int pllx_setup:4;          /* Base PLLX setup */
        unsigned int undefined_bits_28_31:4;
    };

    u_int32_t reg32;
};

void CarDev::fill_pllx_misc_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const pllx_misc_u old_value_t = { .reg32 = value };
    const pllx_misc_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: pllx_vcocon:4",
              "Base PLLX VCO range setup control",
              4, old_value_t.pllx_vcocon, new_value_t.pllx_vcocon };
    m_bit_details_model.bits.append(entry);
    entry = { "04: pllx_lfcon:4",
              "Base PLLX loop filter setup control",
              4, old_value_t.pllx_lfcon, new_value_t.pllx_lfcon };
    m_bit_details_model.bits.append(entry);
    entry = { "08: pllx_cpcon:4",
              "Base PLLX charge pump setup control",
              4, old_value_t.pllx_cpcon, new_value_t.pllx_cpcon };
    m_bit_details_model.bits.append(entry);
    entry = { "12: pllx_lock_sel:6",
              "lock select",
              6, old_value_t.pllx_lock_sel, new_value_t.pllx_lock_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "18: pllx_lock_enable:1",
              "1 = enable,\n0 = disable.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.pllx_lock_enable, new_value_t.pllx_lock_enable };
    m_bit_details_model.bits.append(entry);
    entry = { "19: undefined_bit_19:1", "", 1, old_value_t.undefined_bit_19, new_value_t.undefined_bit_19 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: pllx_dccon:1",
              "Base PLLX DCCON control",
              1, old_value_t.pllx_dccon, new_value_t.pllx_dccon };
    m_bit_details_model.bits.append(entry);
    entry = { "21: undefined_bit_21:1", "", 1, old_value_t.undefined_bit_21, new_value_t.undefined_bit_21 };
    m_bit_details_model.bits.append(entry);
    entry = { "22: pllx_pts:2",
              "Base PLLX test output select",
              2, old_value_t.pllx_pts, new_value_t.pllx_pts };
    m_bit_details_model.bits.append(entry);
    entry = { "24: pllx_setup:4",
              "Base PLLX setup",
              4, old_value_t.pllx_setup, new_value_t.pllx_setup };
    m_bit_details_model.bits.append(entry);
    entry = { "28: undefined_bits_28_31:4", "", 4, old_value_t.undefined_bits_28_31, new_value_t.undefined_bits_28_31 };
    m_bit_details_model.bits.append(entry);
}

#define PLLE_BASE_OFFSET 0xE8
#define PLLE_BASE_UNDEFMASK 0x00000000
union plle_base_u {
    struct {
        unsigned int plle_mdiv:8;           /* input divider */
        unsigned int plle_ndiv:8;           /* feedback divider */
        unsigned int plle_pldiv:6;          /* post divider for CLOCKOUT and SYNC_CLOCKOUT */
        unsigned int plle_ext_setup_19_18:2;/* Base PLLE setup[19:18] */
        unsigned int plle_pldiv_cml:4;      /* divider control for CLOCKOUT_CML/CLOCKOUTB_CML */
        unsigned int plle_fdiv4b:1;         /* 0 gives vcoclk/4, 1 gives vcoclk/2 clock to the interpolator logic. Normally set to zero */
        unsigned int plle_lock_override:1;  /* Forces PLL_LOCK to 1 */
        unsigned int plle_enable:1;         /* PLL enable. 0 = disable, 1 = enable. 0 = DISABLE 1 = ENABLE */
        unsigned int plle_enable_cml:1;     /* Enable CML pdivider. 0 = disable, 1 = enable. 0 = DISABLE 1 = ENABLE */
    };

    u_int32_t reg32;
};

void CarDev::fill_plle_base_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const plle_base_u old_value_t = { .reg32 = value };
    const plle_base_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: plle_mdiv:8",
              "input divider",
              8, old_value_t.plle_mdiv, new_value_t.plle_mdiv };
    m_bit_details_model.bits.append(entry);
    entry = { "08: plle_ndiv:8",
              "feedback divider",
              8, old_value_t.plle_ndiv, new_value_t.plle_ndiv };
    m_bit_details_model.bits.append(entry);
    entry = { "16: plle_pldiv:6",
              "post divider for CLOCKOUT and SYNC_CLOCKOUT",
              6, old_value_t.plle_pldiv, new_value_t.plle_pldiv };
    m_bit_details_model.bits.append(entry);
    entry = { "22: plle_ext_setup_19_18:2",
              "Base PLLE setup[19:18]",
              2, old_value_t.plle_ext_setup_19_18, new_value_t.plle_ext_setup_19_18 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: plle_pldiv_cml:4",
              "divider control for CLOCKOUT_CML/CLOCKOUTB_CML",
              4, old_value_t.plle_pldiv_cml, new_value_t.plle_pldiv_cml };
    m_bit_details_model.bits.append(entry);
    entry = { "28: plle_fdiv4b:1",
              "0 gives vcoclk/4, 1 gives vcoclk/2 clock to the interpolator logic. Normally set to zero",
              1, old_value_t.plle_fdiv4b, new_value_t.plle_fdiv4b };
    m_bit_details_model.bits.append(entry);
    entry = { "29: plle_lock_override:1",
              "Forces PLL_LOCK to 1",
              1, old_value_t.plle_lock_override, new_value_t.plle_lock_override };
    m_bit_details_model.bits.append(entry);
    entry = { "30: plle_enable:1",
              "PLL enable.\n0 = disable,\n1 = enable.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.plle_enable, new_value_t.plle_enable };
    m_bit_details_model.bits.append(entry);
    entry = { "31: plle_enable_cml:1",
              "Enable CML pdivider.\n0 = disable,\n1 = enable.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.plle_enable_cml, new_value_t.plle_enable_cml };
    m_bit_details_model.bits.append(entry);
}

#define PLLE_MISC_OFFSET 0xEC
#define PLLE_MISC_UNDEFMASK 0x00000000
union plle_misc_u {
    struct {
        unsigned int plle_kvco:1;           /* Base PLLE VCO gain */
        unsigned int plle_sync_mode:1;      /* Base PLLE sync mode (leave it at 0) */
        unsigned int plle_ext_setup_17_16:2;/* Base PLLE setup[17:16] */
        unsigned int plle_lfres:2;          /* Base PLLE loop filter resistor control */
        unsigned int plle_kcp:2;            /* Base PLLE charge pump gain control */
        unsigned int plle_pts:1;            /* Bypass PLL (similar to PTO control of other PLL). 0 = PTO always 0 if PLLE_ENABLE=0 (SYN_CLOCKOUT=0), 0 = PTO = PLLE CLOCKIN if PLLE_ENABLE=1, 1 = PTO = PLLE FO (SYN_CLOCKOUT=VCOCLOCK/PLDIV) */
        unsigned int plle_lock_enable:1;    /* 1 = enable, 0 = disable.  0 = DISABLE 1 = ENABLE */
        unsigned int plle_ref_dis:1;        /* 0 = enable reference clk, 1 = disable reference clk. 0 = REF_ENABLE 1 = REF_DISABLE */
        unsigned int plle_lock:1;           /* 0 = not lock, 1 = lock */
        unsigned int plle_mon_testout:3;    /* Process monitor debug output */
        unsigned int plle_pll_ready:1;      /* When read, this is PLL_READY status: 1 = PLL finish training, 0 = PLL not finish training */
        unsigned int plle_setup:16;         /* Base PLLE setup[15:0] */
    };

    u_int32_t reg32;
};

void CarDev::fill_plle_misc_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const plle_misc_u old_value_t = { .reg32 = value };
    const plle_misc_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: plle_kvco:1",
              "Base PLLE VCO gain",
              1, old_value_t.plle_kvco, new_value_t.plle_kvco };
    m_bit_details_model.bits.append(entry);
    entry = { "01: plle_sync_mode:1",
              "Base PLLE sync mode (leave it at 0)",
              1, old_value_t.plle_sync_mode, new_value_t.plle_sync_mode };
    m_bit_details_model.bits.append(entry);
    entry = { "02: plle_ext_setup_17_16:2",
              "Base PLLE setup[17:16]",
              2, old_value_t.plle_ext_setup_17_16, new_value_t.plle_ext_setup_17_16 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: plle_lfres:2",
              "Base PLLE loop filter resistor control",
              2, old_value_t.plle_lfres, new_value_t.plle_lfres };
    m_bit_details_model.bits.append(entry);
    entry = { "06: plle_kcp:2",
              "Base PLLE charge pump gain control",
              2, old_value_t.plle_kcp, new_value_t.plle_kcp };
    m_bit_details_model.bits.append(entry);
    entry = { "08: plle_pts:1",
              "Bypass PLL (similar to PTO control of other PLL).\n0 = PTO always 0 if PLLE_ENABLE=0 (SYN_CLOCKOUT=0),\n0 = PTO = PLLE CLOCKIN if PLLE_ENABLE=1,\n1 = PTO = PLLE FO (SYN_CLOCKOUT=VCOCLOCK/PLDIV)",
              1, old_value_t.plle_pts, new_value_t.plle_pts };
    m_bit_details_model.bits.append(entry);
    entry = { "09: plle_lock_enable:1",
              "1 = enable,\n0 = disable.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.plle_lock_enable, new_value_t.plle_lock_enable };
    m_bit_details_model.bits.append(entry);
    entry = { "10: plle_ref_dis:1",
              "0 = enable reference clk,\n1 = disable reference clk.\n0 = REF_ENABLE\n1 = REF_DISABLE",
              1, old_value_t.plle_ref_dis, new_value_t.plle_ref_dis };
    m_bit_details_model.bits.append(entry);
    entry = { "11: plle_lock:1",
              "0 = not lock,\n1 = lock",
              1, old_value_t.plle_lock, new_value_t.plle_lock };
    m_bit_details_model.bits.append(entry);
    entry = { "12: plle_mon_testout:3",
              "Process monitor debug output",
              3, old_value_t.plle_mon_testout, new_value_t.plle_mon_testout };
    m_bit_details_model.bits.append(entry);
    entry = { "15: plle_pll_ready:1",
              "When read, this is PLL_READY status:\n1 = PLL finish training,\n0 = PLL not finish training",
              1, old_value_t.plle_pll_ready, new_value_t.plle_pll_ready };
    m_bit_details_model.bits.append(entry);
    entry = { "16: plle_setup:16",
              "Base PLLE setup[15:0]",
              16, old_value_t.plle_setup, new_value_t.plle_setup };
    m_bit_details_model.bits.append(entry);
}

#define CLK_SOURCE_I2S1_OFFSET 0x100
#define CLK_SOURCE_I2S1_UNDEFMASK 0x2FFFFF00
union clk_source_i2s1_u {
    struct {
        unsigned int i2s1_clk_divisor:8;    /* N = Divide by (n+1) (lsb denote 0.5x) */
        unsigned int undefined_bits_8_27:20;
        unsigned int i2s1_master_clken:1;   /* 1 = enable I2S1 master clock, disable I2S1 master clock */
        unsigned int undefined_bit_29:1;
        unsigned int i2s1_clk_src:2;        /* 00 = pllA_out0 01 = audio SYNC_CLK x 2 10 = pllP_out0 11 = clk_m 0 = PLLA_OUT0 1 = SYNC_CLK_X2 2 = PLLP_OUT0 3 = CLK_M */
    };

    u_int32_t reg32;
};

void CarDev::fill_clk_source_i2s1_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const clk_source_i2s1_u old_value_t = { .reg32 = value };
    const clk_source_i2s1_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: i2s1_clk_divisor:8",
              "N = Divide by (n+1) (lsb denote 0.5x)",
              8, old_value_t.i2s1_clk_divisor, new_value_t.i2s1_clk_divisor };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_27:20", "", 20, old_value_t.undefined_bits_8_27, new_value_t.undefined_bits_8_27 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: i2s1_master_clken:1",
              "1 = enable I2S1 master clock, disable I2S1 master clock",
              1, old_value_t.i2s1_master_clken, new_value_t.i2s1_master_clken };
    m_bit_details_model.bits.append(entry);
    entry = { "29: undefined_bit_29:1", "", 1, old_value_t.undefined_bit_29, new_value_t.undefined_bit_29 };
    m_bit_details_model.bits.append(entry);
    entry = { "30: i2s1_clk_src:2",
              "00 = pllA_out0\n01 = audio SYNC_CLK x 2\n10 = pllP_out0\n11 = clk_m\n0 = PLLA_OUT0\n1 = SYNC_CLK_X2\n2 = PLLP_OUT0\n3 = CLK_M",
              2, old_value_t.i2s1_clk_src, new_value_t.i2s1_clk_src };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Clock Configuration for Each Peripherals\nIn general, each block or module has a dedicated CLK_SOURCE_ register that provides clock source and clock divider control to that device. The clock source select is typically 2-bits to select one-of-the-four clock sources. The divider is typically 8-bits which consist of 7-integer bit and 1-fractional bit. Furthermore, depending on the specific module, the CLOCK_SORUCE_ register may contain additional control bits.\nNote:\n The 16-bit UART1/UART2/UART3 clock divider control is provided by the UART register set themselves and not by the CLK_SOURCE_ registers.\nIn order to switch from one clock source to the next, both clock sources must be active/running.\nSpecial PLL clock usage by certain peripheral\nAs mentioned previously, each peripheral has a clock source select in their corresponding CLK_SOURCE_ register. But in addition, there're a number of modules which also take in an additional fix PLL clock source for portion of their logic.\nListed below is the module/logic and the fix PLL clock source they use.\nModule/Logic\n Fix PLL Clock Source Used\nLFSR\n pllM_out0\nDSI\n pllP_out3\nCSI\n pllP_out3\nI2C1\n pllP_out3\nI2C2\n pllP_out3\nI2C3\n pllP_out3\nModule/Logic\n Fix PLL Clock Source Used\nUART1\n pllP_out3\nUART2\n pllP_out3\nUART3\n pllP_out3\nUART4\n pllP_out3\nUART5\n pllP_out3";
}

#define CLK_SOURCE_I2S2_OFFSET 0x104
#define CLK_SOURCE_I2S2_UNDEFMASK 0x2FFFFF00
union clk_source_i2s2_u {
    struct {
        unsigned int i2s2_clk_divisor:8;    /* N = Divide by (n+1) (lsb denote 0.5x) */
        unsigned int undefined_bits_8_27:20;
        unsigned int i2s2_master_clken:1;   /* 1 = enable I2S2 master clock, disable I2S2 master clock */
        unsigned int undefined_bit_29:1;
        unsigned int i2s2_clk_src:2;        /* 00 = pllA_out0 01 = audio SYNC_CLK x 2 10 = pllP_out0 11 = clk_m 0 = PLLA_OUT0 1 = SYNC_CLK_X2 2 = PLLP_OUT0 3 = CLK_M */
    };

    u_int32_t reg32;
};

void CarDev::fill_clk_source_i2s2_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const clk_source_i2s2_u old_value_t = { .reg32 = value };
    const clk_source_i2s2_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: i2s2_clk_divisor:8",
              "N = Divide by (n+1) (lsb denote 0.5x)",
              8, old_value_t.i2s2_clk_divisor, new_value_t.i2s2_clk_divisor };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_27:20", "", 20, old_value_t.undefined_bits_8_27, new_value_t.undefined_bits_8_27 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: i2s2_master_clken:1",
              "1 = enable I2S2 master clock, disable I2S2 master clock",
              1, old_value_t.i2s2_master_clken, new_value_t.i2s2_master_clken };
    m_bit_details_model.bits.append(entry);
    entry = { "29: undefined_bit_29:1", "", 1, old_value_t.undefined_bit_29, new_value_t.undefined_bit_29 };
    m_bit_details_model.bits.append(entry);
    entry = { "30: i2s2_clk_src:2",
              "00 = pllA_out0\n01 = audio SYNC_CLK x 2\n10 = pllP_out0\n11 = clk_m\n0 = PLLA_OUT0\n1 = SYNC_CLK_X2\n2 = PLLP_OUT0\n3 = CLK_M",
              2, old_value_t.i2s2_clk_src, new_value_t.i2s2_clk_src };
    m_bit_details_model.bits.append(entry);
}

#define CLK_SOURCE_SPDIF_OUT_OFFSET 0x108
#define CLK_SOURCE_SPDIF_OUT_UNDEFMASK 0x3FFFFF00
union clk_source_spdif_out_u {
    struct {
        unsigned int spdifout_clk_divisor:8;/* N = Divide by (n+1) (lsb denote 0.5x) */
        unsigned int undefined_bits_8_29:22;
        unsigned int spdifout_clk_src:2;    /* 00 = pllA_out0 01 = audio SYNC_CLK x 2 10 = pllP_out0 11 = clk_m 0 = PLLA_OUT0 1 = SYNC_CLK_X2 2 = PLLP_OUT0 3 = CLK_M */
    };

    u_int32_t reg32;
};

void CarDev::fill_clk_source_spdif_out_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const clk_source_spdif_out_u old_value_t = { .reg32 = value };
    const clk_source_spdif_out_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: spdifout_clk_divisor:8",
              "N = Divide by (n+1) (lsb denote 0.5x)",
              8, old_value_t.spdifout_clk_divisor, new_value_t.spdifout_clk_divisor };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_29:22", "", 22, old_value_t.undefined_bits_8_29, new_value_t.undefined_bits_8_29 };
    m_bit_details_model.bits.append(entry);
    entry = { "30: spdifout_clk_src:2",
              "00 = pllA_out0\n01 = audio SYNC_CLK x 2\n10 = pllP_out0\n11 = clk_m\n0 = PLLA_OUT0\n1 = SYNC_CLK_X2\n2 = PLLP_OUT0\n3 = CLK_M",
              2, old_value_t.spdifout_clk_src, new_value_t.spdifout_clk_src };
    m_bit_details_model.bits.append(entry);
}

#define CLK_SOURCE_SPDIF_IN_OFFSET 0x10C
#define CLK_SOURCE_SPDIF_IN_UNDEFMASK 0x3FFFFF00
union clk_source_spdif_in_u {
    struct {
        unsigned int spdifin_clk_divisor:8; /* N = Divide by (n+1) (lsb denote 0.5x) */
        unsigned int undefined_bits_8_29:22;
        unsigned int spdifin_clk_src:2;     /* 00 = pllP_out0 01 = pllC_out0 10 = pllM_out0 11 = 1'b0 0 = PLLP_OUT0 1 = PLLC_OUT0 2 = PLLM_OUT0 */
    };

    u_int32_t reg32;
};

void CarDev::fill_clk_source_spdif_in_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const clk_source_spdif_in_u old_value_t = { .reg32 = value };
    const clk_source_spdif_in_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: spdifin_clk_divisor:8",
              "N = Divide by (n+1) (lsb denote 0.5x)",
              8, old_value_t.spdifin_clk_divisor, new_value_t.spdifin_clk_divisor };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_29:22", "", 22, old_value_t.undefined_bits_8_29, new_value_t.undefined_bits_8_29 };
    m_bit_details_model.bits.append(entry);
    entry = { "30: spdifin_clk_src:2",
              "00 = pllP_out0\n01 = pllC_out0\n10 = pllM_out0\n11 = 1'b0\n0 = PLLP_OUT0\n1 = PLLC_OUT0\n2 = PLLM_OUT0",
              2, old_value_t.spdifin_clk_src, new_value_t.spdifin_clk_src };
    m_bit_details_model.bits.append(entry);
}

#define CLK_SOURCE_PWM_OFFSET 0x110
#define CLK_SOURCE_PWM_UNDEFMASK 0x8FFFFF00
union clk_source_pwm_u {
    struct {
        unsigned int pwm_clk_divisor:8;     /* N = Divide by (n+1) (lsb denote 0.5x) */
        unsigned int undefined_bits_8_27:20;
        unsigned int pwm_clk_src:3;         /* 000 = pllP_out0 001 = pllC_out0 010 = audio SYNC_CLK x 2 011 = clk_m 100 = clk_s 0 = PLLP_OUT0 1 = PLLC_OUT0 2 = SYNC_CLK_X2 3 = CLK_M 4 = CLK_S */
        unsigned int undefined_bit_31:1;
    };

    u_int32_t reg32;
};

void CarDev::fill_clk_source_pwm_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const clk_source_pwm_u old_value_t = { .reg32 = value };
    const clk_source_pwm_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: pwm_clk_divisor:8",
              "N = Divide by (n+1) (lsb denote 0.5x)",
              8, old_value_t.pwm_clk_divisor, new_value_t.pwm_clk_divisor };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_27:20", "", 20, old_value_t.undefined_bits_8_27, new_value_t.undefined_bits_8_27 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: pwm_clk_src:3",
              "000 = pllP_out0\n001 = pllC_out0\n010 = audio SYNC_CLK x 2\n011 = clk_m\n100 = clk_s\n0 = PLLP_OUT0\n1 = PLLC_OUT0\n2 = SYNC_CLK_X2\n3 = CLK_M\n4 = CLK_S",
              3, old_value_t.pwm_clk_src, new_value_t.pwm_clk_src };
    m_bit_details_model.bits.append(entry);
    entry = { "31: undefined_bit_31:1", "", 1, old_value_t.undefined_bit_31, new_value_t.undefined_bit_31 };
    m_bit_details_model.bits.append(entry);
}

#define CLK_SOURCE_SPI1_OFFSET 0x114
#define CLK_SOURCE_SPI1_UNDEFMASK 0x3FFFFF00
union clk_source_spi1_u {
    struct {
        unsigned int spi1_clk_divisor:8;    /* N = Divide by (n+1) (lsb denote 0.5x) */
        unsigned int undefined_bits_8_29:22;
        unsigned int spi1_clk_src:2;        /* 00 = pllP_out0 01 = pllC_out0 10 = pllM_out0 11 = clk_m 0 = PLLP_OUT0 1 = PLLC_OUT0 2 = PLLM_OUT0 3 = CLK_M */
    };

    u_int32_t reg32;
};

void CarDev::fill_clk_source_spi1_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const clk_source_spi1_u old_value_t = { .reg32 = value };
    const clk_source_spi1_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: spi1_clk_divisor:8",
              "N = Divide by (n+1) (lsb denote 0.5x)",
              8, old_value_t.spi1_clk_divisor, new_value_t.spi1_clk_divisor };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_29:22", "", 22, old_value_t.undefined_bits_8_29, new_value_t.undefined_bits_8_29 };
    m_bit_details_model.bits.append(entry);
    entry = { "30: spi1_clk_src:2",
              "00 = pllP_out0\n01 = pllC_out0\n10 = pllM_out0\n11 = clk_m\n0 = PLLP_OUT0\n1 = PLLC_OUT0\n2 = PLLM_OUT0\n3 = CLK_M",
              2, old_value_t.spi1_clk_src, new_value_t.spi1_clk_src };
    m_bit_details_model.bits.append(entry);
}

#define CLK_SOURCE_SPI22_OFFSET 0x118
#define CLK_SOURCE_SPI22_UNDEFMASK 0x3FFFFF00
union clk_source_spi22_u {
    struct {
        unsigned int spi2_clk_divisor:8;    /* N = Divide by (n+1) (lsb denote 0.5x) */
        unsigned int undefined_bits_8_29:22;
        unsigned int spi2_clk_src:2;        /* 00 = pllP_out0 01 = pllC_out0 10 = pllM_out0 11 = clk_m 0 = PLLP_OUT0 1 = PLLC_OUT0 2 = PLLM_OUT0 3 = CLK_M */
    };

    u_int32_t reg32;
};

void CarDev::fill_clk_source_spi22_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const clk_source_spi22_u old_value_t = { .reg32 = value };
    const clk_source_spi22_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: spi2_clk_divisor:8",
              "N = Divide by (n+1) (lsb denote 0.5x)",
              8, old_value_t.spi2_clk_divisor, new_value_t.spi2_clk_divisor };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_29:22", "", 22, old_value_t.undefined_bits_8_29, new_value_t.undefined_bits_8_29 };
    m_bit_details_model.bits.append(entry);
    entry = { "30: spi2_clk_src:2",
              "00 = pllP_out0\n01 = pllC_out0\n10 = pllM_out0\n11 = clk_m\n0 = PLLP_OUT0\n1 = PLLC_OUT0\n2 = PLLM_OUT0\n3 = CLK_M",
              2, old_value_t.spi2_clk_src, new_value_t.spi2_clk_src };
    m_bit_details_model.bits.append(entry);
}

#define CLK_SOURCE_SPI3_OFFSET 0x11C
#define CLK_SOURCE_SPI3_UNDEFMASK 0x3FFFFF00
union clk_source_spi3_u {
    struct {
        unsigned int spi3_clk_divisor:8;    /* N = Divide by (n+1) (lsb denote 0.5x) */
        unsigned int undefined_bits_8_29:22;
        unsigned int spi3_clk_src:2;        /* 00 = pllP_out0 01 = pllC_out0 10 = pllM_out0 11 = clk_m 0 = PLLP_OUT0 1 = PLLC_OUT0 2 = PLLM_OUT0 3 = CLK_M */
    };

    u_int32_t reg32;
};

void CarDev::fill_clk_source_spi3_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const clk_source_spi3_u old_value_t = { .reg32 = value };
    const clk_source_spi3_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: spi3_clk_divisor:8",
              "N = Divide by (n+1) (lsb denote 0.5x)",
              8, old_value_t.spi3_clk_divisor, new_value_t.spi3_clk_divisor };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_29:22", "", 22, old_value_t.undefined_bits_8_29, new_value_t.undefined_bits_8_29 };
    m_bit_details_model.bits.append(entry);
    entry = { "30: spi3_clk_src:2",
              "00 = pllP_out0\n01 = pllC_out0\n10 = pllM_out0\n11 = clk_m\n0 = PLLP_OUT0\n1 = PLLC_OUT0\n2 = PLLM_OUT0\n3 = CLK_M",
              2, old_value_t.spi3_clk_src, new_value_t.spi3_clk_src };
    m_bit_details_model.bits.append(entry);
}

#define CLK_SOURCE_XIO_OFFSET 0x120
#define CLK_SOURCE_XIO_UNDEFMASK 0x3FFFFF00
union clk_source_xio_u {
    struct {
        unsigned int xio_clk_divisor:8;     /* N = Divide by (n+1) (lsb denote 0.5x) */
        unsigned int undefined_bits_8_29:22;
        unsigned int xio_clk_src:2;         /* 00 = pllP_out0 01 = pllC_out0 10 = pllM_out0 11 = clk_m 0 = PLLP_OUT0 1 = PLLC_OUT0 2 = PLLM_OUT0 3 = CLK_M */
    };

    u_int32_t reg32;
};

void CarDev::fill_clk_source_xio_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const clk_source_xio_u old_value_t = { .reg32 = value };
    const clk_source_xio_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: xio_clk_divisor:8",
              "N = Divide by (n+1) (lsb denote 0.5x)",
              8, old_value_t.xio_clk_divisor, new_value_t.xio_clk_divisor };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_29:22", "", 22, old_value_t.undefined_bits_8_29, new_value_t.undefined_bits_8_29 };
    m_bit_details_model.bits.append(entry);
    entry = { "30: xio_clk_src:2",
              "00 = pllP_out0\n01 = pllC_out0\n10 = pllM_out0\n11 = clk_m\n0 = PLLP_OUT0\n1 = PLLC_OUT0\n2 = PLLM_OUT0\n3 = CLK_M",
              2, old_value_t.xio_clk_src, new_value_t.xio_clk_src };
    m_bit_details_model.bits.append(entry);
}

#define CLK_SOURCE_I2C1_OFFSET 0x124
#define CLK_SOURCE_I2C1_UNDEFMASK 0x3FFF0000
union clk_source_i2c1_u {
    struct {
        unsigned int i2c1_clk_divisor:16;   /* N = Divide by (n+1) (lsb denote 1.0x) */
        unsigned int undefined_bits_16_29:14;
        unsigned int i2c1_clk_src:2;        /* 00 = pllP_out0 01 = pllC_out0 10 = pllM_out0 11 = clk_m 0 = PLLP_OUT0 1 = PLLC_OUT0 2 = PLLM_OUT0 3 = CLK_M */
    };

    u_int32_t reg32;
};

void CarDev::fill_clk_source_i2c1_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const clk_source_i2c1_u old_value_t = { .reg32 = value };
    const clk_source_i2c1_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: i2c1_clk_divisor:16",
              "N = Divide by (n+1) (lsb denote 1.0x)",
              16, old_value_t.i2c1_clk_divisor, new_value_t.i2c1_clk_divisor };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_29:14", "", 14, old_value_t.undefined_bits_16_29, new_value_t.undefined_bits_16_29 };
    m_bit_details_model.bits.append(entry);
    entry = { "30: i2c1_clk_src:2",
              "00 = pllP_out0\n01 = pllC_out0\n10 = pllM_out0\n11 = clk_m\n0 = PLLP_OUT0\n1 = PLLC_OUT0\n2 = PLLM_OUT0\n3 = CLK_M",
              2, old_value_t.i2c1_clk_src, new_value_t.i2c1_clk_src };
    m_bit_details_model.bits.append(entry);
}

#define CLK_SOURCE_DVC_I2C_OFFSET 0x128
#define CLK_SOURCE_DVC_I2C_UNDEFMASK 0x3FFF0000
union clk_source_dvc_i2c_u {
    struct {
        unsigned int dvc_i2c_clk_divisor:16;/* N = Divide by (n+1) (lsb denote 1.0x) */
        unsigned int undefined_bits_16_29:14;
        unsigned int dvc_i2c_clk_src:2;     /* 00 = pllP_out0 01 = pllC_out0 10 = pllM_out0 11 = clk_m 0 = PLLP_OUT0 1 = PLLC_OUT0 2 = PLLM_OUT0 3 = CLK_M */
    };

    u_int32_t reg32;
};

void CarDev::fill_clk_source_dvc_i2c_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const clk_source_dvc_i2c_u old_value_t = { .reg32 = value };
    const clk_source_dvc_i2c_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: dvc_i2c_clk_divisor:16",
              "N = Divide by (n+1) (lsb denote 1.0x)",
              16, old_value_t.dvc_i2c_clk_divisor, new_value_t.dvc_i2c_clk_divisor };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_29:14", "", 14, old_value_t.undefined_bits_16_29, new_value_t.undefined_bits_16_29 };
    m_bit_details_model.bits.append(entry);
    entry = { "30: dvc_i2c_clk_src:2",
              "00 = pllP_out0\n01 = pllC_out0\n10 = pllM_out0\n11 = clk_m\n0 = PLLP_OUT0\n1 = PLLC_OUT0\n2 = PLLM_OUT0\n3 = CLK_M",
              2, old_value_t.dvc_i2c_clk_src, new_value_t.dvc_i2c_clk_src };
    m_bit_details_model.bits.append(entry);
}

#define CLK_SOURCE_TWC_OFFSET 0x12C
#define CLK_SOURCE_TWC_UNDEFMASK 0x3FFFFF00
union clk_source_twc_u {
    struct {
        unsigned int twc_clk_divisor:8;     /* N = Divide by (n+1) (lsb denote 0.5x) */
        unsigned int undefined_bits_8_29:22;
        unsigned int twc_clk_src:2;         /* 00 = pllP_out0 01 = pllC_out0 10 = pllM_out0 11 = clk_m 0 = PLLP_OUT0 1 = PLLC_OUT0 2 = PLLM_OUT0 3 = CLK_M */
    };

    u_int32_t reg32;
};

void CarDev::fill_clk_source_twc_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const clk_source_twc_u old_value_t = { .reg32 = value };
    const clk_source_twc_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: twc_clk_divisor:8",
              "N = Divide by (n+1) (lsb denote 0.5x)",
              8, old_value_t.twc_clk_divisor, new_value_t.twc_clk_divisor };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_29:22", "", 22, old_value_t.undefined_bits_8_29, new_value_t.undefined_bits_8_29 };
    m_bit_details_model.bits.append(entry);
    entry = { "30: twc_clk_src:2",
              "00 = pllP_out0\n01 = pllC_out0\n10 = pllM_out0\n11 = clk_m\n0 = PLLP_OUT0\n1 = PLLC_OUT0\n2 = PLLM_OUT0\n3 = CLK_M",
              2, old_value_t.twc_clk_src, new_value_t.twc_clk_src };
    m_bit_details_model.bits.append(entry);
}

#define CLK_SOURCE_SBC1_OFFSET 0x134
#define CLK_SOURCE_SBC1_UNDEFMASK 0x3FFFFF00
union clk_source_sbc1_u {
    struct {
        unsigned int sbc1_clk_divisor:8;    /*  N = Divide by (n+1) (lsb denote 0.5x) */
        unsigned int undefined_bits_8_29:22;
        unsigned int sbc1_clk_src:2;        /*  00 = pllP_out0  01 = pllC_out0  10 = pllM_out0  11 = clk_m */
    };

    u_int32_t reg32;
};

void CarDev::fill_clk_source_sbc1_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const clk_source_sbc1_u old_value_t = { .reg32 = value };
    const clk_source_sbc1_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: sbc1_clk_divisor:8",
              " N = Divide by (n+1) (lsb denote 0.5x)",
              8, old_value_t.sbc1_clk_divisor, new_value_t.sbc1_clk_divisor };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_29:22", "", 22, old_value_t.undefined_bits_8_29, new_value_t.undefined_bits_8_29 };
    m_bit_details_model.bits.append(entry);
    entry = { "30: sbc1_clk_src:2",
              "00 = pllP_out0 \n01 = pllC_out0 \n10 = pllM_out0 \n11 = clk_m",
              2, old_value_t.sbc1_clk_src, new_value_t.sbc1_clk_src };
    m_bit_details_model.bits.append(entry);
}

#define CLK_SOURCE_DISP1_OFFSET 0x138
#define CLK_SOURCE_DISP1_UNDEFMASK 0x3FFFFFFF
union clk_source_disp1_u {
    struct {
        unsigned int undefined_bits_0_29:30;
        unsigned int disp1_clk_src:2;       /* 00 = pllP_out0 01 = pllD_out0 10 = pllC_out0 11 = clk_m 0 = PLLP_OUT0 1 = PLLD_OUT0 2 = PLLC_OUT0 3 = CLK_M */
    };

    u_int32_t reg32;
};

void CarDev::fill_clk_source_disp1_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const clk_source_disp1_u old_value_t = { .reg32 = value };
    const clk_source_disp1_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_29:30", "", 30, old_value_t.undefined_bits_0_29, new_value_t.undefined_bits_0_29 };
    m_bit_details_model.bits.append(entry);
    entry = { "30: disp1_clk_src:2",
              "00 = pllP_out0\n01 = pllD_out0\n10 = pllC_out0\n11 = clk_m\n0 = PLLP_OUT0\n1 = PLLD_OUT0\n2 = PLLC_OUT0\n3 = CLK_M",
              2, old_value_t.disp1_clk_src, new_value_t.disp1_clk_src };
    m_bit_details_model.bits.append(entry);
}

#define CLK_SOURCE_DISP2_OFFSET 0x13C
#define CLK_SOURCE_DISP2_UNDEFMASK 0x3FFFFFFF
union clk_source_disp2_u {
    struct {
        unsigned int undefined_bits_0_29:30;
        unsigned int disp2_clk_src:2;       /* 00 = pllP_out0 01 = pllD_out0 10 = pllC_out0 11 = clk_m 0 = PLLP_OUT0 1 = PLLD_OUT0 2 = PLLC_OUT0 3 = CLK_M */
    };

    u_int32_t reg32;
};

void CarDev::fill_clk_source_disp2_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const clk_source_disp2_u old_value_t = { .reg32 = value };
    const clk_source_disp2_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_29:30", "", 30, old_value_t.undefined_bits_0_29, new_value_t.undefined_bits_0_29 };
    m_bit_details_model.bits.append(entry);
    entry = { "30: disp2_clk_src:2",
              "00 = pllP_out0\n01 = pllD_out0\n10 = pllC_out0\n11 = clk_m\n0 = PLLP_OUT0\n1 = PLLD_OUT0\n2 = PLLC_OUT0\n3 = CLK_M",
              2, old_value_t.disp2_clk_src, new_value_t.disp2_clk_src };
    m_bit_details_model.bits.append(entry);
}

#define CLK_SOURCE_CVE_OFFSET 0x140
#define CLK_SOURCE_CVE_UNDEFMASK 0x3FFFFF00
union clk_source_cve_u {
    struct {
        unsigned int cve_clk_divisor:8;     /* N = Divide by (n+1) (lsb denote 0.5x) */
        unsigned int undefined_bits_8_29:22;
        unsigned int cve_clk_src:2;         /* 00 = pllP_out0 01 = pllD_out0 10 = pllC_out0 11 = clk_m 0 = PLLP_OUT0 1 = PLLD_OUT0 2 = PLLC_OUT0 3 = CLK_M */
    };

    u_int32_t reg32;
};

void CarDev::fill_clk_source_cve_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const clk_source_cve_u old_value_t = { .reg32 = value };
    const clk_source_cve_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: cve_clk_divisor:8",
              "N = Divide by (n+1) (lsb denote 0.5x)",
              8, old_value_t.cve_clk_divisor, new_value_t.cve_clk_divisor };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_29:22", "", 22, old_value_t.undefined_bits_8_29, new_value_t.undefined_bits_8_29 };
    m_bit_details_model.bits.append(entry);
    entry = { "30: cve_clk_src:2",
              "00 = pllP_out0\n01 = pllD_out0\n10 = pllC_out0\n11 = clk_m\n0 = PLLP_OUT0\n1 = PLLD_OUT0\n2 = PLLC_OUT0\n3 = CLK_M",
              2, old_value_t.cve_clk_src, new_value_t.cve_clk_src };
    m_bit_details_model.bits.append(entry);
}

#define CLK_SOURCE_IDE_OFFSET 0x144
#define CLK_SOURCE_IDE_UNDEFMASK 0x3FFFFF00
union clk_source_ide_u {
    struct {
        unsigned int ide_clk_divisor:8;     /* N = Divide by (n+1) (lsb denote 0.5x) */
        unsigned int undefined_bits_8_29:22;
        unsigned int ide_clk_src:2;         /* 00 = pllP_out0 01 = pllC_out0 10 = pllM_out0 11 = clk_m 0 = PLLP_OUT0 1 = PLLC_OUT0 2 = PLLM_OUT0 3 = CLK_M */
    };

    u_int32_t reg32;
};

void CarDev::fill_clk_source_ide_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const clk_source_ide_u old_value_t = { .reg32 = value };
    const clk_source_ide_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: ide_clk_divisor:8",
              "N = Divide by (n+1) (lsb denote 0.5x)",
              8, old_value_t.ide_clk_divisor, new_value_t.ide_clk_divisor };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_29:22", "", 22, old_value_t.undefined_bits_8_29, new_value_t.undefined_bits_8_29 };
    m_bit_details_model.bits.append(entry);
    entry = { "30: ide_clk_src:2",
              "00 = pllP_out0\n01 = pllC_out0\n10 = pllM_out0\n11 = clk_m\n0 = PLLP_OUT0\n1 = PLLC_OUT0\n2 = PLLM_OUT0\n3 = CLK_M",
              2, old_value_t.ide_clk_src, new_value_t.ide_clk_src };
    m_bit_details_model.bits.append(entry);
}

#define CLK_SOURCE_VI_OFFSET 0x148
#define CLK_SOURCE_VI_UNDEFMASK 0x3CFFFF00
union clk_source_vi_u {
    struct {
        unsigned int vi_clk_divisor:8;      /* N = Divide by (n+1) (lsb denote 0.5x) */
        unsigned int undefined_bits_8_23:16;
        unsigned int vi_clk_sel:1;          /* 0 = select internal clock, 1 = select external clock (pd2vi_clk). 0 = INTERNAL 1 = EXTERNAL */
        unsigned int pd2vi_clk_sel:1;       /* 0 = pd2vi_clk, 1 = vi_sensor_clk */
        unsigned int undefined_bits_26_29:4;
        unsigned int vi_clk_src:2;          /* 00 = pllM_out0 01 = pllC_out0 10 = pllP_out0 11 = pllA_out0 0 = PLLM_OUT0 1 = PLLC_OUT0 2 = PLLP_OUT0 3 = PLLA_OUT0 */
    };

    u_int32_t reg32;
};

void CarDev::fill_clk_source_vi_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const clk_source_vi_u old_value_t = { .reg32 = value };
    const clk_source_vi_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: vi_clk_divisor:8",
              "N = Divide by (n+1) (lsb denote 0.5x)",
              8, old_value_t.vi_clk_divisor, new_value_t.vi_clk_divisor };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_23:16", "", 16, old_value_t.undefined_bits_8_23, new_value_t.undefined_bits_8_23 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: vi_clk_sel:1",
              "0 = select internal clock,\n1 = select external clock (pd2vi_clk).\n0 = INTERNAL\n1 = EXTERNAL",
              1, old_value_t.vi_clk_sel, new_value_t.vi_clk_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "25: pd2vi_clk_sel:1",
              "0 = pd2vi_clk,\n1 = vi_sensor_clk",
              1, old_value_t.pd2vi_clk_sel, new_value_t.pd2vi_clk_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "26: undefined_bits_26_29:4", "", 4, old_value_t.undefined_bits_26_29, new_value_t.undefined_bits_26_29 };
    m_bit_details_model.bits.append(entry);
    entry = { "30: vi_clk_src:2",
              "00 = pllM_out0\n01 = pllC_out0\n10 = pllP_out0\n11 = pllA_out0\n0 = PLLM_OUT0\n1 = PLLC_OUT0\n2 = PLLP_OUT0\n3 = PLLA_OUT0",
              2, old_value_t.vi_clk_src, new_value_t.vi_clk_src };
    m_bit_details_model.bits.append(entry);
}

#define CLK_SOURCE_SDMMC1_OFFSET 0x150
#define CLK_SOURCE_SDMMC1_UNDEFMASK 0x3F70FF00
union clk_source_sdmmc1_u {
    struct {
        unsigned int sdmmc1_clk_divisor:8;  /* N = Divide by (n+1) (lsb denote 0.5x) */
        unsigned int undefined_bits_8_15:8;
        unsigned int sdmmc1_int_fb_dly:4;   /* 16-tap of internal feedback clock delay. */
        unsigned int undefined_bits_20_22:3;
        unsigned int sdmmc1_int_fb_sel:1;   /* 1 = use internal feedback clock. 0 = use external feedback clock. */
        unsigned int undefined_bits_24_29:6;
        unsigned int sdmmc1_clk_src:2;      /* 00 = pllP_out0 01 = pllC_out0 10 = pllM_out0 11 = clk_m 0 = PLLP_OUT0 1 = PLLC_OUT0 2 = PLLM_OUT0 3 = CLK_M */
    };

    u_int32_t reg32;
};

void CarDev::fill_clk_source_sdmmc1_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const clk_source_sdmmc1_u old_value_t = { .reg32 = value };
    const clk_source_sdmmc1_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: sdmmc1_clk_divisor:8",
              "N = Divide by (n+1) (lsb denote 0.5x)",
              8, old_value_t.sdmmc1_clk_divisor, new_value_t.sdmmc1_clk_divisor };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_15:8", "", 8, old_value_t.undefined_bits_8_15, new_value_t.undefined_bits_8_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: sdmmc1_int_fb_dly:4",
              "16-tap of internal feedback clock delay.",
              4, old_value_t.sdmmc1_int_fb_dly, new_value_t.sdmmc1_int_fb_dly };
    m_bit_details_model.bits.append(entry);
    entry = { "20: undefined_bits_20_22:3", "", 3, old_value_t.undefined_bits_20_22, new_value_t.undefined_bits_20_22 };
    m_bit_details_model.bits.append(entry);
    entry = { "23: sdmmc1_int_fb_sel:1",
              "1 = use internal feedback clock.\n0 = use external feedback clock.",
              1, old_value_t.sdmmc1_int_fb_sel, new_value_t.sdmmc1_int_fb_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "24: undefined_bits_24_29:6", "", 6, old_value_t.undefined_bits_24_29, new_value_t.undefined_bits_24_29 };
    m_bit_details_model.bits.append(entry);
    entry = { "30: sdmmc1_clk_src:2",
              "00 = pllP_out0\n01 = pllC_out0\n10 = pllM_out0\n11 = clk_m\n0 = PLLP_OUT0\n1 = PLLC_OUT0\n2 = PLLM_OUT0\n3 = CLK_M",
              2, old_value_t.sdmmc1_clk_src, new_value_t.sdmmc1_clk_src };
    m_bit_details_model.bits.append(entry);
}

#define CLK_SOURCE_SDMMC2_OFFSET 0x154
#define CLK_SOURCE_SDMMC2_UNDEFMASK 0x3F70FF00
union clk_source_sdmmc2_u {
    struct {
        unsigned int sdmmc2_clk_divisor:8;  /* N = Divide by (n+1) (lsb denote 0.5x) */
        unsigned int undefined_bits_8_15:8;
        unsigned int sdmmc2_int_fb_dly:4;   /* 16-tap of internal feedback clock delay. */
        unsigned int undefined_bits_20_22:3;
        unsigned int sdmmc2_int_fb_sel:1;   /* 1 = use internal feedback clock. 0 = use external feedback clock. */
        unsigned int undefined_bits_24_29:6;
        unsigned int sdmmc2_clk_src:2;      /* 00 = pllP_out0 01 = pllC_out0 10 = pllM_out0 11 = clk_m 0 = PLLP_OUT0 1 = PLLC_OUT0 2 = PLLM_OUT0 3 = CLK_M */
    };

    u_int32_t reg32;
};

void CarDev::fill_clk_source_sdmmc2_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const clk_source_sdmmc2_u old_value_t = { .reg32 = value };
    const clk_source_sdmmc2_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: sdmmc2_clk_divisor:8",
              "N = Divide by (n+1) (lsb denote 0.5x)",
              8, old_value_t.sdmmc2_clk_divisor, new_value_t.sdmmc2_clk_divisor };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_15:8", "", 8, old_value_t.undefined_bits_8_15, new_value_t.undefined_bits_8_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: sdmmc2_int_fb_dly:4",
              "16-tap of internal feedback clock delay.",
              4, old_value_t.sdmmc2_int_fb_dly, new_value_t.sdmmc2_int_fb_dly };
    m_bit_details_model.bits.append(entry);
    entry = { "20: undefined_bits_20_22:3", "", 3, old_value_t.undefined_bits_20_22, new_value_t.undefined_bits_20_22 };
    m_bit_details_model.bits.append(entry);
    entry = { "23: sdmmc2_int_fb_sel:1",
              "1 = use internal feedback clock.\n0 = use external feedback clock.",
              1, old_value_t.sdmmc2_int_fb_sel, new_value_t.sdmmc2_int_fb_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "24: undefined_bits_24_29:6", "", 6, old_value_t.undefined_bits_24_29, new_value_t.undefined_bits_24_29 };
    m_bit_details_model.bits.append(entry);
    entry = { "30: sdmmc2_clk_src:2",
              "00 = pllP_out0\n01 = pllC_out0\n10 = pllM_out0\n11 = clk_m\n0 = PLLP_OUT0\n1 = PLLC_OUT0\n2 = PLLM_OUT0\n3 = CLK_M",
              2, old_value_t.sdmmc2_clk_src, new_value_t.sdmmc2_clk_src };
    m_bit_details_model.bits.append(entry);
}

#define CLK_SOURCE_G3D_OFFSET 0x158
#define CLK_SOURCE_G3D_UNDEFMASK 0x3FFF0000
union clk_source_g3d_u {
    struct {
        unsigned int g3d_clk_divisor:8;     /* N = Divide by (n+1) (lsb denote 0.5x) */
        unsigned int g3d_idle_divisor:8;    /* N = Divide by (n+1) (lsb denote 0.5x) if all 0's, this idle divisor field will not be used. For non-zero values, when host1x is idle, this field will be used instead of G3D_CLK_DIVISOR */
        unsigned int undefined_bits_16_29:14;
        unsigned int g3d_clk_src:2;         /* 00 = pllM_out0 01 = pllC_out0 10 = pllP_out0 11 = pllA_out0 0 = PLLM_OUT0 1 = PLLC_OUT0 2 = PLLP_OUT0 3 = PLLA_OUT0 */
    };

    u_int32_t reg32;
};

void CarDev::fill_clk_source_g3d_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const clk_source_g3d_u old_value_t = { .reg32 = value };
    const clk_source_g3d_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: g3d_clk_divisor:8",
              "N = Divide by (n+1) (lsb denote 0.5x)",
              8, old_value_t.g3d_clk_divisor, new_value_t.g3d_clk_divisor };
    m_bit_details_model.bits.append(entry);
    entry = { "08: g3d_idle_divisor:8",
              "N = Divide by (n+1) (lsb denote 0.5x) if all 0's, this idle divisor field will not be used. For non-zero values, when host1x is idle, this field will be used instead of G3D_CLK_DIVISOR",
              8, old_value_t.g3d_idle_divisor, new_value_t.g3d_idle_divisor };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_29:14", "", 14, old_value_t.undefined_bits_16_29, new_value_t.undefined_bits_16_29 };
    m_bit_details_model.bits.append(entry);
    entry = { "30: g3d_clk_src:2",
              "00 = pllM_out0\n01 = pllC_out0\n10 = pllP_out0\n11 = pllA_out0\n0 = PLLM_OUT0\n1 = PLLC_OUT0\n2 = PLLP_OUT0\n3 = PLLA_OUT0",
              2, old_value_t.g3d_clk_src, new_value_t.g3d_clk_src };
    m_bit_details_model.bits.append(entry);
}

#define CLK_SOURCE_G2D_OFFSET 0x15C
#define CLK_SOURCE_G2D_UNDEFMASK 0x3FFF0000
union clk_source_g2d_u {
    struct {
        unsigned int g2d_clk_divisor:8;     /* N = Divide by (n+1) (lsb denote 0.5x) */
        unsigned int g2d_idle_divisor:8;    /* N = Divide by (n+1) (lsb denote 0.5x) if all 0's, this idle divisor field will not be used. For non-zero values, when host1x is idle, this field will be used instead of G2D_CLK_DIVISOR */
        unsigned int undefined_bits_16_29:14;
        unsigned int g2d_clk_src:2;         /* 00 = pllM_out0 01 = pllC_out0 10 = pllP_out0 11 = pllA_out0 0 = PLLM_OUT0 1 = PLLC_OUT0 2 = PLLP_OUT0 3 = PLLA_OUT0 */
    };

    u_int32_t reg32;
};

void CarDev::fill_clk_source_g2d_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const clk_source_g2d_u old_value_t = { .reg32 = value };
    const clk_source_g2d_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: g2d_clk_divisor:8",
              "N = Divide by (n+1) (lsb denote 0.5x)",
              8, old_value_t.g2d_clk_divisor, new_value_t.g2d_clk_divisor };
    m_bit_details_model.bits.append(entry);
    entry = { "08: g2d_idle_divisor:8",
              "N = Divide by (n+1) (lsb denote 0.5x) if all 0's, this idle divisor field will not be used. For non-zero values, when host1x is idle, this field will be used instead of G2D_CLK_DIVISOR",
              8, old_value_t.g2d_idle_divisor, new_value_t.g2d_idle_divisor };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_29:14", "", 14, old_value_t.undefined_bits_16_29, new_value_t.undefined_bits_16_29 };
    m_bit_details_model.bits.append(entry);
    entry = { "30: g2d_clk_src:2",
              "00 = pllM_out0\n01 = pllC_out0\n10 = pllP_out0\n11 = pllA_out0\n0 = PLLM_OUT0\n1 = PLLC_OUT0\n2 = PLLP_OUT0\n3 = PLLA_OUT0",
              2, old_value_t.g2d_clk_src, new_value_t.g2d_clk_src };
    m_bit_details_model.bits.append(entry);
}

#define CLK_SOURCE_NDFLASH_OFFSET 0x160
#define CLK_SOURCE_NDFLASH_UNDEFMASK 0x3FFFFF00
union clk_source_ndflash_u {
    struct {
        unsigned int ndflash_clk_divisor:8; /* N = Divide by (n+1) (lsb denote 0.5x) */
        unsigned int undefined_bits_8_29:22;
        unsigned int ndflash_clk_src:2;     /* 00 = pllP_out0 01 = pllC_out0 10 = pllM_out0 11 = clk_m 0 = PLLP_OUT0 1 = PLLC_OUT0 2 = PLLM_OUT0 3 = CLK_M */
    };

    u_int32_t reg32;
};

void CarDev::fill_clk_source_ndflash_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const clk_source_ndflash_u old_value_t = { .reg32 = value };
    const clk_source_ndflash_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: ndflash_clk_divisor:8",
              "N = Divide by (n+1) (lsb denote 0.5x)",
              8, old_value_t.ndflash_clk_divisor, new_value_t.ndflash_clk_divisor };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_29:22", "", 22, old_value_t.undefined_bits_8_29, new_value_t.undefined_bits_8_29 };
    m_bit_details_model.bits.append(entry);
    entry = { "30: ndflash_clk_src:2",
              "00 = pllP_out0\n01 = pllC_out0\n10 = pllM_out0\n11 = clk_m\n0 = PLLP_OUT0\n1 = PLLC_OUT0\n2 = PLLM_OUT0\n3 = CLK_M",
              2, old_value_t.ndflash_clk_src, new_value_t.ndflash_clk_src };
    m_bit_details_model.bits.append(entry);
}

#define CLK_SOURCE_SDMMC4_OFFSET 0x164
#define CLK_SOURCE_SDMMC4_UNDEFMASK 0x3F70FF00
union clk_source_sdmmc4_u {
    struct {
        unsigned int sdmmc4_clk_divisor:8;  /* N = Divide by (n+1) (lsb denote 0.5x) */
        unsigned int undefined_bits_8_15:8;
        unsigned int sdmmc4_int_fb_dly:4;   /* 16-tap of internal feedback clock delay. */
        unsigned int undefined_bits_20_22:3;
        unsigned int sdmmc4_int_fb_sel:1;   /* 1 = use internal feedback clock. 0 = use external feedback clock. */
        unsigned int undefined_bits_24_29:6;
        unsigned int sdmmc4_clk_src:2;      /* 00 = pllP_out0 01 = pllC_out0 10 = pllM_out0 11 = CLK_M 0 = PLLP_OUT0 1 = PLLC_OUT0 2 = PLLM_OUT0 3 = CLK_M */
    };

    u_int32_t reg32;
};

void CarDev::fill_clk_source_sdmmc4_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const clk_source_sdmmc4_u old_value_t = { .reg32 = value };
    const clk_source_sdmmc4_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: sdmmc4_clk_divisor:8",
              "N = Divide by (n+1) (lsb denote 0.5x)",
              8, old_value_t.sdmmc4_clk_divisor, new_value_t.sdmmc4_clk_divisor };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_15:8", "", 8, old_value_t.undefined_bits_8_15, new_value_t.undefined_bits_8_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: sdmmc4_int_fb_dly:4",
              "16-tap of internal feedback clock delay.",
              4, old_value_t.sdmmc4_int_fb_dly, new_value_t.sdmmc4_int_fb_dly };
    m_bit_details_model.bits.append(entry);
    entry = { "20: undefined_bits_20_22:3", "", 3, old_value_t.undefined_bits_20_22, new_value_t.undefined_bits_20_22 };
    m_bit_details_model.bits.append(entry);
    entry = { "23: sdmmc4_int_fb_sel:1",
              "1 = use internal feedback clock.\n0 = use external feedback clock.",
              1, old_value_t.sdmmc4_int_fb_sel, new_value_t.sdmmc4_int_fb_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "24: undefined_bits_24_29:6", "", 6, old_value_t.undefined_bits_24_29, new_value_t.undefined_bits_24_29 };
    m_bit_details_model.bits.append(entry);
    entry = { "30: sdmmc4_clk_src:2",
              "00 = pllP_out0\n01 = pllC_out0\n10 = pllM_out0\n11 = CLK_M\n0 = PLLP_OUT0\n1 = PLLC_OUT0\n2 = PLLM_OUT0\n3 = CLK_M",
              2, old_value_t.sdmmc4_clk_src, new_value_t.sdmmc4_clk_src };
    m_bit_details_model.bits.append(entry);
}

#define CLK_SOURCE_VFIR_OFFSET 0x168
#define CLK_SOURCE_VFIR_UNDEFMASK 0x3FFFFF00
union clk_source_vfir_u {
    struct {
        unsigned int vfir_clk_divisor:8;    /* N = Divide by (n+1) (lsb denote 0.5x) */
        unsigned int undefined_bits_8_29:22;
        unsigned int vfir_clk_src:2;        /* 00 = pllP_out0 01 = pllC_out0 10 = pllM_out0 11 = clk_m 0 = PLLP_OUT0 1 = PLLC_OUT0 2 = PLLM_OUT0 3 = CLK_M */
    };

    u_int32_t reg32;
};

void CarDev::fill_clk_source_vfir_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const clk_source_vfir_u old_value_t = { .reg32 = value };
    const clk_source_vfir_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: vfir_clk_divisor:8",
              "N = Divide by (n+1) (lsb denote 0.5x)",
              8, old_value_t.vfir_clk_divisor, new_value_t.vfir_clk_divisor };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_29:22", "", 22, old_value_t.undefined_bits_8_29, new_value_t.undefined_bits_8_29 };
    m_bit_details_model.bits.append(entry);
    entry = { "30: vfir_clk_src:2",
              "00 = pllP_out0\n01 = pllC_out0\n10 = pllM_out0\n11 = clk_m\n0 = PLLP_OUT0\n1 = PLLC_OUT0\n2 = PLLM_OUT0\n3 = CLK_M",
              2, old_value_t.vfir_clk_src, new_value_t.vfir_clk_src };
    m_bit_details_model.bits.append(entry);
}

#define CLK_SOURCE_EPP_OFFSET 0x16C
#define CLK_SOURCE_EPP_UNDEFMASK 0x3FFFFF00
union clk_source_epp_u {
    struct {
        unsigned int epp_clk_divisor:8;     /* N = Divide by (n+1) (lsb denote 0.5x) */
        unsigned int undefined_bits_8_29:22;
        unsigned int epp_clk_src:2;         /* 00 = pllM_out0 01 = pllC_out0 10 = pllP_out0 11 = pllA_out0 0 = PLLM_OUT0 1 = PLLC_OUT0 2 = PLLP_OUT0 3 = PLLA_OUT0 */
    };

    u_int32_t reg32;
};

void CarDev::fill_clk_source_epp_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const clk_source_epp_u old_value_t = { .reg32 = value };
    const clk_source_epp_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: epp_clk_divisor:8",
              "N = Divide by (n+1) (lsb denote 0.5x)",
              8, old_value_t.epp_clk_divisor, new_value_t.epp_clk_divisor };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_29:22", "", 22, old_value_t.undefined_bits_8_29, new_value_t.undefined_bits_8_29 };
    m_bit_details_model.bits.append(entry);
    entry = { "30: epp_clk_src:2",
              "00 = pllM_out0\n01 = pllC_out0\n10 = pllP_out0\n11 = pllA_out0\n0 = PLLM_OUT0\n1 = PLLC_OUT0\n2 = PLLP_OUT0\n3 = PLLA_OUT0",
              2, old_value_t.epp_clk_src, new_value_t.epp_clk_src };
    m_bit_details_model.bits.append(entry);
}

#define CLK_SOURCE_MPE_OFFSET 0x170
#define CLK_SOURCE_MPE_UNDEFMASK 0x3FFFFF00
union clk_source_mpe_u {
    struct {
        unsigned int mpe_clk_divisor:8;     /* N = Divide by (n+1) (lsb denote 0.5x) */
        unsigned int undefined_bits_8_29:22;
        unsigned int mpe_clk_src:2;         /* 00 = pllM_out0 01 = pllC_out0 10 = pllP_out0 11 = pllA_out0 0 = PLLM_OUT0 1 = PLLC_OUT0 2 = PLLP_OUT0 3 = PLLA_OUT0 */
    };

    u_int32_t reg32;
};

void CarDev::fill_clk_source_mpe_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const clk_source_mpe_u old_value_t = { .reg32 = value };
    const clk_source_mpe_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: mpe_clk_divisor:8",
              "N = Divide by (n+1) (lsb denote 0.5x)",
              8, old_value_t.mpe_clk_divisor, new_value_t.mpe_clk_divisor };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_29:22", "", 22, old_value_t.undefined_bits_8_29, new_value_t.undefined_bits_8_29 };
    m_bit_details_model.bits.append(entry);
    entry = { "30: mpe_clk_src:2",
              "00 = pllM_out0\n01 = pllC_out0\n10 = pllP_out0\n11 = pllA_out0\n0 = PLLM_OUT0\n1 = PLLC_OUT0\n2 = PLLP_OUT0\n3 = PLLA_OUT0",
              2, old_value_t.mpe_clk_src, new_value_t.mpe_clk_src };
    m_bit_details_model.bits.append(entry);
}

#define CLK_SOURCE_MIPI_OFFSET 0x174
#define CLK_SOURCE_MIPI_UNDEFMASK 0x3FFFFF00
union clk_source_mipi_u {
    struct {
        unsigned int mipi_clk_divisor:8;    /* N = Divide by (n+1) (lsb denote 0.5x) */
        unsigned int undefined_bits_8_29:22;
        unsigned int mipi_clk_src:2;        /* 00 = pllP_out0 01 = pllC_out0 10 = pllM_out0 11 = clk_m 0 = PLLP_OUT0 1 = PLLC_OUT0 2 = PLLM_OUT0 3 = CLK_M */
    };

    u_int32_t reg32;
};

void CarDev::fill_clk_source_mipi_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const clk_source_mipi_u old_value_t = { .reg32 = value };
    const clk_source_mipi_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: mipi_clk_divisor:8",
              "N = Divide by (n+1) (lsb denote 0.5x)",
              8, old_value_t.mipi_clk_divisor, new_value_t.mipi_clk_divisor };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_29:22", "", 22, old_value_t.undefined_bits_8_29, new_value_t.undefined_bits_8_29 };
    m_bit_details_model.bits.append(entry);
    entry = { "30: mipi_clk_src:2",
              "00 = pllP_out0\n01 = pllC_out0\n10 = pllM_out0\n11 = clk_m\n0 = PLLP_OUT0\n1 = PLLC_OUT0\n2 = PLLM_OUT0\n3 = CLK_M",
              2, old_value_t.mipi_clk_src, new_value_t.mipi_clk_src };
    m_bit_details_model.bits.append(entry);
}

#define CLK_SOURCE_UART1_OFFSET 0x178
#define CLK_SOURCE_UART1_UNDEFMASK 0x3FFFFFFF
union clk_source_uart1_u {
    struct {
        unsigned int undefined_bits_0_29:30;
        unsigned int uart1_clk_src:2;       /* 00 = pllP_out0 01 = pllC_out0 10 = pllM_out0 11 = clk_m 0 = PLLP_OUT0 1 = PLLC_OUT0 2 = PLLM_OUT0 3 = CLK_M */
    };

    u_int32_t reg32;
};

void CarDev::fill_clk_source_uart1_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const clk_source_uart1_u old_value_t = { .reg32 = value };
    const clk_source_uart1_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_29:30", "", 30, old_value_t.undefined_bits_0_29, new_value_t.undefined_bits_0_29 };
    m_bit_details_model.bits.append(entry);
    entry = { "30: uart1_clk_src:2",
              "00 = pllP_out0\n01 = pllC_out0\n10 = pllM_out0\n11 = clk_m\n0 = PLLP_OUT0\n1 = PLLC_OUT0\n2 = PLLM_OUT0\n3 = CLK_M",
              2, old_value_t.uart1_clk_src, new_value_t.uart1_clk_src };
    m_bit_details_model.bits.append(entry);
}

#define CLK_SOURCE_UART2_OFFSET 0x17C
#define CLK_SOURCE_UART2_UNDEFMASK 0x3FFFFFFF
union clk_source_uart2_u {
    struct {
        unsigned int undefined_bits_0_29:30;
        unsigned int uart2_clk_src:2;       /* 00 = pllP_out0 01 = pllC_out0 10 = pllM_out0 11 = clk_m 0 = PLLP_OUT0 1 = PLLC_OUT0 2 = PLLM_OUT0 3 = CLK_M */
    };

    u_int32_t reg32;
};

void CarDev::fill_clk_source_uart2_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const clk_source_uart2_u old_value_t = { .reg32 = value };
    const clk_source_uart2_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_29:30", "", 30, old_value_t.undefined_bits_0_29, new_value_t.undefined_bits_0_29 };
    m_bit_details_model.bits.append(entry);
    entry = { "30: uart2_clk_src:2",
              "00 = pllP_out0\n01 = pllC_out0\n10 = pllM_out0\n11 = clk_m\n0 = PLLP_OUT0\n1 = PLLC_OUT0\n2 = PLLM_OUT0\n3 = CLK_M",
              2, old_value_t.uart2_clk_src, new_value_t.uart2_clk_src };
    m_bit_details_model.bits.append(entry);
}

#define CLK_SOURCE_HOST1X_OFFSET 0x180
#define CLK_SOURCE_HOST1X_UNDEFMASK 0x3FFF0000
union clk_source_host1x_u {
    struct {
        unsigned int host1x_clk_divisor:8;  /* N = Divide by (n+1) (lsb denote 0.5x) */
        unsigned int host1x_idle_divisor:8; /* N = Divide by (n+1) (lsb denote 0.5x) if all 0's, this idle divisor field will not be used. For non-zero values, when host1x is idle, this field will be used instead of HOST1X_CLK_DIVISOR */
        unsigned int undefined_bits_16_29:14;
        unsigned int host1x_clk_src:2;      /* 00 = pllM_out0 01 = pllC_out0 10 = pllP_out0 11 = pllA_out0 0 = PLLM_OUT0 1 = PLLC_OUT0 2 = PLLP_OUT0 3 = PLLA_OUT0 */
    };

    u_int32_t reg32;
};

void CarDev::fill_clk_source_host1x_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const clk_source_host1x_u old_value_t = { .reg32 = value };
    const clk_source_host1x_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: host1x_clk_divisor:8",
              "N = Divide by (n+1) (lsb denote 0.5x)",
              8, old_value_t.host1x_clk_divisor, new_value_t.host1x_clk_divisor };
    m_bit_details_model.bits.append(entry);
    entry = { "08: host1x_idle_divisor:8",
              "N = Divide by (n+1) (lsb denote 0.5x) if all 0's, this idle divisor field will not be used. For non-zero values, when host1x is idle, this field will be used instead of HOST1X_CLK_DIVISOR",
              8, old_value_t.host1x_idle_divisor, new_value_t.host1x_idle_divisor };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_29:14", "", 14, old_value_t.undefined_bits_16_29, new_value_t.undefined_bits_16_29 };
    m_bit_details_model.bits.append(entry);
    entry = { "30: host1x_clk_src:2",
              "00 = pllM_out0\n01 = pllC_out0\n10 = pllP_out0\n11 = pllA_out0\n0 = PLLM_OUT0\n1 = PLLC_OUT0\n2 = PLLP_OUT0\n3 = PLLA_OUT0",
              2, old_value_t.host1x_clk_src, new_value_t.host1x_clk_src };
    m_bit_details_model.bits.append(entry);
}

#define CLK_SOURCE_TVO_OFFSET 0x188
#define CLK_SOURCE_TVO_UNDEFMASK 0x3FFFFF00
union clk_source_tvo_u {
    struct {
        unsigned int tvo_clk_divisor:8;     /* N = Divide by (n+1) (lsb denote 0.5x) */
        unsigned int undefined_bits_8_29:22;
        unsigned int tvo_clk_src:2;         /* 00 = pllP_out0 01 = pllD_out0 10 = pllC_out0 11 = clk_m 0 = PLLP_OUT0 1 = PLLD_OUT0 2 = PLLC_OUT0 3 = CLK_M */
    };

    u_int32_t reg32;
};

void CarDev::fill_clk_source_tvo_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const clk_source_tvo_u old_value_t = { .reg32 = value };
    const clk_source_tvo_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: tvo_clk_divisor:8",
              "N = Divide by (n+1) (lsb denote 0.5x)",
              8, old_value_t.tvo_clk_divisor, new_value_t.tvo_clk_divisor };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_29:22", "", 22, old_value_t.undefined_bits_8_29, new_value_t.undefined_bits_8_29 };
    m_bit_details_model.bits.append(entry);
    entry = { "30: tvo_clk_src:2",
              "00 = pllP_out0\n01 = pllD_out0\n10 = pllC_out0\n11 = clk_m\n0 = PLLP_OUT0\n1 = PLLD_OUT0\n2 = PLLC_OUT0\n3 = CLK_M",
              2, old_value_t.tvo_clk_src, new_value_t.tvo_clk_src };
    m_bit_details_model.bits.append(entry);
}

#define CLK_SOURCE_HDMI_OFFSET 0x18C
#define CLK_SOURCE_HDMI_UNDEFMASK 0x3FFFFF00
union clk_source_hdmi_u {
    struct {
        unsigned int hdmi_clk_divisor:8;    /* N = Divide by (n+1) (lsb denote 0.5x) */
        unsigned int undefined_bits_8_29:22;
        unsigned int hdmi_clk_src:2;        /* 00 = pllP_out0 01 = pllD_out0 10 = pllC_out0 11 = clk_m 0 = PLLP_OUT0 1 = PLLD_OUT0 2 = PLLC_OUT0 3 = CLK_M */
    };

    u_int32_t reg32;
};

void CarDev::fill_clk_source_hdmi_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const clk_source_hdmi_u old_value_t = { .reg32 = value };
    const clk_source_hdmi_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: hdmi_clk_divisor:8",
              "N = Divide by (n+1) (lsb denote 0.5x)",
              8, old_value_t.hdmi_clk_divisor, new_value_t.hdmi_clk_divisor };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_29:22", "", 22, old_value_t.undefined_bits_8_29, new_value_t.undefined_bits_8_29 };
    m_bit_details_model.bits.append(entry);
    entry = { "30: hdmi_clk_src:2",
              "00 = pllP_out0\n01 = pllD_out0\n10 = pllC_out0\n11 = clk_m\n0 = PLLP_OUT0\n1 = PLLD_OUT0\n2 = PLLC_OUT0\n3 = CLK_M",
              2, old_value_t.hdmi_clk_src, new_value_t.hdmi_clk_src };
    m_bit_details_model.bits.append(entry);
}

#define CLK_SOURCE_TVDAC_OFFSET 0x194
#define CLK_SOURCE_TVDAC_UNDEFMASK 0x3FFFFF00
union clk_source_tvdac_u {
    struct {
        unsigned int tvdac_clk_divisor:8;   /* N = Divide by (n+1) (lsb denote 0.5x) */
        unsigned int undefined_bits_8_29:22;
        unsigned int tvdac_clk_src:2;       /* 00 = pllP_out0 01 = pllD_out0 10 = pllC_out0 11 = clk_m 0 = PLLP_OUT0 1 = PLLD_OUT0 2 = PLLC_OUT0 3 = CLK_M */
    };

    u_int32_t reg32;
};

void CarDev::fill_clk_source_tvdac_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const clk_source_tvdac_u old_value_t = { .reg32 = value };
    const clk_source_tvdac_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: tvdac_clk_divisor:8",
              "N = Divide by (n+1) (lsb denote 0.5x)",
              8, old_value_t.tvdac_clk_divisor, new_value_t.tvdac_clk_divisor };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_29:22", "", 22, old_value_t.undefined_bits_8_29, new_value_t.undefined_bits_8_29 };
    m_bit_details_model.bits.append(entry);
    entry = { "30: tvdac_clk_src:2",
              "00 = pllP_out0\n01 = pllD_out0\n10 = pllC_out0\n11 = clk_m\n0 = PLLP_OUT0\n1 = PLLD_OUT0\n2 = PLLC_OUT0\n3 = CLK_M",
              2, old_value_t.tvdac_clk_src, new_value_t.tvdac_clk_src };
    m_bit_details_model.bits.append(entry);
}

#define CLK_SOURCE_I2C2_OFFSET 0x198
#define CLK_SOURCE_I2C2_UNDEFMASK 0x3FFF0000
union clk_source_i2c2_u {
    struct {
        unsigned int i2c2_clk_divisor:16;   /* N = Divide by (n+1) (lsb denote 1.0x) */
        unsigned int undefined_bits_16_29:14;
        unsigned int i2c2_clk_src:2;        /* 00 = pllP_out0 01 = pllC_out0 10 = pllM_out0 11 = clk_m 0 = PLLP_OUT0 1 = PLLC_OUT0 2 = PLLM_OUT0 3 = CLK_M */
    };

    u_int32_t reg32;
};

void CarDev::fill_clk_source_i2c2_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const clk_source_i2c2_u old_value_t = { .reg32 = value };
    const clk_source_i2c2_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: i2c2_clk_divisor:16",
              "N = Divide by (n+1) (lsb denote 1.0x)",
              16, old_value_t.i2c2_clk_divisor, new_value_t.i2c2_clk_divisor };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_29:14", "", 14, old_value_t.undefined_bits_16_29, new_value_t.undefined_bits_16_29 };
    m_bit_details_model.bits.append(entry);
    entry = { "30: i2c2_clk_src:2",
              "00 = pllP_out0\n01 = pllC_out0\n10 = pllM_out0\n11 = clk_m\n0 = PLLP_OUT0\n1 = PLLC_OUT0\n2 = PLLM_OUT0\n3 = CLK_M",
              2, old_value_t.i2c2_clk_src, new_value_t.i2c2_clk_src };
    m_bit_details_model.bits.append(entry);
}

#define CLK_SOURCE_EMC_OFFSET 0x19C
#define CLK_SOURCE_EMC_UNDEFMASK 0x1CFFFF00
union clk_source_emc_u {
    struct {
        unsigned int emc_2x_clk_divisor:8;  /* N = Divide by (n+1) (lsb denote 0.5x) */
        unsigned int undefined_bits_8_23:16;
        unsigned int emc_1x_clk_enb:1;      /* 1 = enable EMC 1X clock. 0 = DISABLE 1 = ENABLE */
        unsigned int emc_2x_clk_enb:1;      /* 1 = enable EMC 2X clock. 0 = DISABLE 1 = ENABLE */
        unsigned int undefined_bits_26_28:3;
        unsigned int use_pllm_ud:1;         /* 1 = use un-divided PllM_out0 as clock source */
        unsigned int emc_2x_clk_src:2;      /* 00 = pllM_out0 01 = pllC_out0 10 = pllP_out0 11 = clk_m 0 = PLLM_OUT0 1 = PLLC_OUT0 2 = PLLP_OUT0 3 = CLK_M */
    };

    u_int32_t reg32;
};

void CarDev::fill_clk_source_emc_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const clk_source_emc_u old_value_t = { .reg32 = value };
    const clk_source_emc_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: emc_2x_clk_divisor:8",
              "N = Divide by (n+1) (lsb denote 0.5x)",
              8, old_value_t.emc_2x_clk_divisor, new_value_t.emc_2x_clk_divisor };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_23:16", "", 16, old_value_t.undefined_bits_8_23, new_value_t.undefined_bits_8_23 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: emc_1x_clk_enb:1",
              "1 = enable EMC 1X clock.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.emc_1x_clk_enb, new_value_t.emc_1x_clk_enb };
    m_bit_details_model.bits.append(entry);
    entry = { "25: emc_2x_clk_enb:1",
              "1 = enable EMC 2X clock.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.emc_2x_clk_enb, new_value_t.emc_2x_clk_enb };
    m_bit_details_model.bits.append(entry);
    entry = { "26: undefined_bits_26_28:3", "", 3, old_value_t.undefined_bits_26_28, new_value_t.undefined_bits_26_28 };
    m_bit_details_model.bits.append(entry);
    entry = { "29: use_pllm_ud:1",
              "1 = use un-divided PllM_out0 as clock source",
              1, old_value_t.use_pllm_ud, new_value_t.use_pllm_ud };
    m_bit_details_model.bits.append(entry);
    entry = { "30: emc_2x_clk_src:2",
              "00 = pllM_out0\n01 = pllC_out0\n10 = pllP_out0\n11 = clk_m\n0 = PLLM_OUT0\n1 = PLLC_OUT0\n2 = PLLP_OUT0\n3 = CLK_M",
              2, old_value_t.emc_2x_clk_src, new_value_t.emc_2x_clk_src };
    m_bit_details_model.bits.append(entry);
}

#define CLK_SOURCE_UART3_OFFSET 0x1A0
#define CLK_SOURCE_UART3_UNDEFMASK 0x3FFFFFFF
union clk_source_uart3_u {
    struct {
        unsigned int undefined_bits_0_29:30;
        unsigned int uart3_clk_src:2;       /* 00 = pllP_out0 01 = pllC_out0 10 = pllM_out0 11 = CLK_M 0 = PLLP_OUT0 1 = PLLC_OUT0 2 = PLLM_OUT0 3 = CLK_M */
    };

    u_int32_t reg32;
};

void CarDev::fill_clk_source_uart3_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const clk_source_uart3_u old_value_t = { .reg32 = value };
    const clk_source_uart3_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_29:30", "", 30, old_value_t.undefined_bits_0_29, new_value_t.undefined_bits_0_29 };
    m_bit_details_model.bits.append(entry);
    entry = { "30: uart3_clk_src:2",
              "00 = pllP_out0\n01 = pllC_out0\n10 = pllM_out0\n11 = CLK_M\n0 = PLLP_OUT0\n1 = PLLC_OUT0\n2 = PLLM_OUT0\n3 = CLK_M",
              2, old_value_t.uart3_clk_src, new_value_t.uart3_clk_src };
    m_bit_details_model.bits.append(entry);
}

#define CLK_SOURCE_VI_SENSOR_OFFSET 0x1A8
#define CLK_SOURCE_VI_SENSOR_UNDEFMASK 0x3FFFFF00
union clk_source_vi_sensor_u {
    struct {
        unsigned int vi_sensor_clk_divisor:8;/* N = Divide by (n+1) (lsb denote 0.5x) */
        unsigned int undefined_bits_8_29:22;
        unsigned int vi_sensor_clk_src:2;   /* 00 = pllM_out0 01 = pllC_out0 10 = pllP_out0 11 = pllA_out0 0 = PLLM_OUT0 1 = PLLC_OUT0 2 = PLLP_OUT0 3 = PLLA_OUT0 */
    };

    u_int32_t reg32;
};

void CarDev::fill_clk_source_vi_sensor_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const clk_source_vi_sensor_u old_value_t = { .reg32 = value };
    const clk_source_vi_sensor_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: vi_sensor_clk_divisor:8",
              "N = Divide by (n+1) (lsb denote 0.5x)",
              8, old_value_t.vi_sensor_clk_divisor, new_value_t.vi_sensor_clk_divisor };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_29:22", "", 22, old_value_t.undefined_bits_8_29, new_value_t.undefined_bits_8_29 };
    m_bit_details_model.bits.append(entry);
    entry = { "30: vi_sensor_clk_src:2",
              "00 = pllM_out0\n01 = pllC_out0\n10 = pllP_out0\n11 = pllA_out0\n0 = PLLM_OUT0\n1 = PLLC_OUT0\n2 = PLLP_OUT0\n3 = PLLA_OUT0",
              2, old_value_t.vi_sensor_clk_src, new_value_t.vi_sensor_clk_src };
    m_bit_details_model.bits.append(entry);
}

#define CLK_SOURCE_SPI4_OFFSET 0x1B4
#define CLK_SOURCE_SPI4_UNDEFMASK 0x3FFFFF00
union clk_source_spi4_u {
    struct {
        unsigned int spi4_clk_divisor:8;    /* N = Divide by (n+1) (lsb denote 0.5x) */
        unsigned int undefined_bits_8_29:22;
        unsigned int spi4_clk_src:2;        /* 00 = pllP_out0 01 = pllC_out0 10 = pllM_out0 11 = clk_m 0 = PLLP_OUT0 1 = PLLC_OUT0 2 = PLLM_OUT0 3 = CLK_M */
    };

    u_int32_t reg32;
};

void CarDev::fill_clk_source_spi4_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const clk_source_spi4_u old_value_t = { .reg32 = value };
    const clk_source_spi4_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: spi4_clk_divisor:8",
              "N = Divide by (n+1) (lsb denote 0.5x)",
              8, old_value_t.spi4_clk_divisor, new_value_t.spi4_clk_divisor };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_29:22", "", 22, old_value_t.undefined_bits_8_29, new_value_t.undefined_bits_8_29 };
    m_bit_details_model.bits.append(entry);
    entry = { "30: spi4_clk_src:2",
              "00 = pllP_out0\n01 = pllC_out0\n10 = pllM_out0\n11 = clk_m\n0 = PLLP_OUT0\n1 = PLLC_OUT0\n2 = PLLM_OUT0\n3 = CLK_M",
              2, old_value_t.spi4_clk_src, new_value_t.spi4_clk_src };
    m_bit_details_model.bits.append(entry);
}

#define CLK_SOURCE_I2C3_OFFSET 0x1B8
#define CLK_SOURCE_I2C3_UNDEFMASK 0x3FFF0000
union clk_source_i2c3_u {
    struct {
        unsigned int i2c3_clk_divisor:16;   /* N = Divide by (n+1) (lsb denote 1.0x) */
        unsigned int undefined_bits_16_29:14;
        unsigned int i2c3_clk_src:2;        /* 00 = pllP_out0 01 = pllC_out0 10 = pllM_out0 11 = clk_m 0 = PLLP_OUT0 1 = PLLC_OUT0 2 = PLLM_OUT0 3 = CLK_M */
    };

    u_int32_t reg32;
};

void CarDev::fill_clk_source_i2c3_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const clk_source_i2c3_u old_value_t = { .reg32 = value };
    const clk_source_i2c3_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: i2c3_clk_divisor:16",
              "N = Divide by (n+1) (lsb denote 1.0x)",
              16, old_value_t.i2c3_clk_divisor, new_value_t.i2c3_clk_divisor };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_29:14", "", 14, old_value_t.undefined_bits_16_29, new_value_t.undefined_bits_16_29 };
    m_bit_details_model.bits.append(entry);
    entry = { "30: i2c3_clk_src:2",
              "00 = pllP_out0\n01 = pllC_out0\n10 = pllM_out0\n11 = clk_m\n0 = PLLP_OUT0\n1 = PLLC_OUT0\n2 = PLLM_OUT0\n3 = CLK_M",
              2, old_value_t.i2c3_clk_src, new_value_t.i2c3_clk_src };
    m_bit_details_model.bits.append(entry);
}

#define CLK_SOURCE_SDMMC3_OFFSET 0x1BC
#define CLK_SOURCE_SDMMC3_UNDEFMASK 0x3F70FF00
union clk_source_sdmmc3_u {
    struct {
        unsigned int sdmmc3_clk_divisor:8;  /* N = Divide by (n+1) (lsb denote 0.5x) */
        unsigned int undefined_bits_8_15:8;
        unsigned int sdmmc3_int_fb_dly:4;   /* 16-tap of internal feedback clock delay. */
        unsigned int undefined_bits_20_22:3;
        unsigned int sdmmc3_int_fb_sel:1;   /* 1 = use internal feedback clock. 0 = use external feedback clock. */
        unsigned int undefined_bits_24_29:6;
        unsigned int sdmmc3_clk_src:2;      /* 00 = pllP_out0 01 = pllC_out0 10 = pllM_out0 11 = clk_m 0 = PLLP_OUT0 1 = PLLC_OUT0 2 = PLLM_OUT0 3 = CLK_M */
    };

    u_int32_t reg32;
};

void CarDev::fill_clk_source_sdmmc3_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const clk_source_sdmmc3_u old_value_t = { .reg32 = value };
    const clk_source_sdmmc3_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: sdmmc3_clk_divisor:8",
              "N = Divide by (n+1) (lsb denote 0.5x)",
              8, old_value_t.sdmmc3_clk_divisor, new_value_t.sdmmc3_clk_divisor };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_15:8", "", 8, old_value_t.undefined_bits_8_15, new_value_t.undefined_bits_8_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: sdmmc3_int_fb_dly:4",
              "16-tap of internal feedback clock delay.",
              4, old_value_t.sdmmc3_int_fb_dly, new_value_t.sdmmc3_int_fb_dly };
    m_bit_details_model.bits.append(entry);
    entry = { "20: undefined_bits_20_22:3", "", 3, old_value_t.undefined_bits_20_22, new_value_t.undefined_bits_20_22 };
    m_bit_details_model.bits.append(entry);
    entry = { "23: sdmmc3_int_fb_sel:1",
              "1 = use internal feedback clock.\n0 = use external feedback clock.",
              1, old_value_t.sdmmc3_int_fb_sel, new_value_t.sdmmc3_int_fb_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "24: undefined_bits_24_29:6", "", 6, old_value_t.undefined_bits_24_29, new_value_t.undefined_bits_24_29 };
    m_bit_details_model.bits.append(entry);
    entry = { "30: sdmmc3_clk_src:2",
              "00 = pllP_out0\n01 = pllC_out0\n10 = pllM_out0\n11 = clk_m\n0 = PLLP_OUT0\n1 = PLLC_OUT0\n2 = PLLM_OUT0\n3 = CLK_M",
              2, old_value_t.sdmmc3_clk_src, new_value_t.sdmmc3_clk_src };
    m_bit_details_model.bits.append(entry);
}

#define CLK_SOURCE_UART4_OFFSET 0x1C0
#define CLK_SOURCE_UART4_UNDEFMASK 0x3FFFFFFF
union clk_source_uart4_u {
    struct {
        unsigned int undefined_bits_0_29:30;
        unsigned int uart4_clk_src:2;       /* 00 = pllP_out0 01 = pllC_out0 10 = pllM_out0 11 = clk_m 0 = PLLP_OUT0 1 = PLLC_OUT0 2 = PLLM_OUT0 3 = CLK_M */
    };

    u_int32_t reg32;
};

void CarDev::fill_clk_source_uart4_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const clk_source_uart4_u old_value_t = { .reg32 = value };
    const clk_source_uart4_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_29:30", "", 30, old_value_t.undefined_bits_0_29, new_value_t.undefined_bits_0_29 };
    m_bit_details_model.bits.append(entry);
    entry = { "30: uart4_clk_src:2",
              "00 = pllP_out0\n01 = pllC_out0\n10 = pllM_out0\n11 = clk_m\n0 = PLLP_OUT0\n1 = PLLC_OUT0\n2 = PLLM_OUT0\n3 = CLK_M",
              2, old_value_t.uart4_clk_src, new_value_t.uart4_clk_src };
    m_bit_details_model.bits.append(entry);
}

#define CLK_SOURCE_UART5_OFFSET 0x1C4
#define CLK_SOURCE_UART5_UNDEFMASK 0x3FFFFFFF
union clk_source_uart5_u {
    struct {
        unsigned int undefined_bits_0_29:30;
        unsigned int uart5_clk_src:2;       /* 00 = pllP_out0 01 = pllC_out0 10 = pllM_out0 11 = clk_m 0 = PLLP_OUT0 1 = PLLC_OUT0 2 = PLLM_OUT0 3 = CLK_M */
    };

    u_int32_t reg32;
};

void CarDev::fill_clk_source_uart5_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const clk_source_uart5_u old_value_t = { .reg32 = value };
    const clk_source_uart5_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_29:30", "", 30, old_value_t.undefined_bits_0_29, new_value_t.undefined_bits_0_29 };
    m_bit_details_model.bits.append(entry);
    entry = { "30: uart5_clk_src:2",
              "00 = pllP_out0\n01 = pllC_out0\n10 = pllM_out0\n11 = clk_m\n0 = PLLP_OUT0\n1 = PLLC_OUT0\n2 = PLLM_OUT0\n3 = CLK_M",
              2, old_value_t.uart5_clk_src, new_value_t.uart5_clk_src };
    m_bit_details_model.bits.append(entry);
}

#define CLK_SOURCE_VDE_OFFSET 0x1C8
#define CLK_SOURCE_VDE_UNDEFMASK 0x3FFFFF00
union clk_source_vde_u {
    struct {
        unsigned int vde_clk_divisor:8;     /* N = Divide by (n+1) (lsb denote 0.5x) */
        unsigned int undefined_bits_8_29:22;
        unsigned int vde_clk_src:2;         /* 00 = pllP_out0 01 = pllC_out0 10 = pllM_out0 11 = clk_m 0 = PLLP_OUT0 1 = PLLC_OUT0 2 = PLLM_OUT0 3 = CLK_M */
    };

    u_int32_t reg32;
};

void CarDev::fill_clk_source_vde_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const clk_source_vde_u old_value_t = { .reg32 = value };
    const clk_source_vde_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: vde_clk_divisor:8",
              "N = Divide by (n+1) (lsb denote 0.5x)",
              8, old_value_t.vde_clk_divisor, new_value_t.vde_clk_divisor };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_29:22", "", 22, old_value_t.undefined_bits_8_29, new_value_t.undefined_bits_8_29 };
    m_bit_details_model.bits.append(entry);
    entry = { "30: vde_clk_src:2",
              "00 = pllP_out0\n01 = pllC_out0\n10 = pllM_out0\n11 = clk_m\n0 = PLLP_OUT0\n1 = PLLC_OUT0\n2 = PLLM_OUT0\n3 = CLK_M",
              2, old_value_t.vde_clk_src, new_value_t.vde_clk_src };
    m_bit_details_model.bits.append(entry);
}

#define CLK_SOURCE_OWR_OFFSET 0x1CC
#define CLK_SOURCE_OWR_UNDEFMASK 0x3FFFFF00
union clk_source_owr_u {
    struct {
        unsigned int owr_clk_divisor:8;     /* N = Divide by (n+1) (lsb denote 0.5x) */
        unsigned int undefined_bits_8_29:22;
        unsigned int owr_clk_src:2;         /* 00 = pllP_out0 01 = pllC_out0 10 = pllM_out0 11 = clk_m 0 = PLLP_OUT0 1 = PLLC_OUT0 2 = PLLM_OUT0 3 = CLK_M */
    };

    u_int32_t reg32;
};

void CarDev::fill_clk_source_owr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const clk_source_owr_u old_value_t = { .reg32 = value };
    const clk_source_owr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: owr_clk_divisor:8",
              "N = Divide by (n+1) (lsb denote 0.5x)",
              8, old_value_t.owr_clk_divisor, new_value_t.owr_clk_divisor };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_29:22", "", 22, old_value_t.undefined_bits_8_29, new_value_t.undefined_bits_8_29 };
    m_bit_details_model.bits.append(entry);
    entry = { "30: owr_clk_src:2",
              "00 = pllP_out0\n01 = pllC_out0\n10 = pllM_out0\n11 = clk_m\n0 = PLLP_OUT0\n1 = PLLC_OUT0\n2 = PLLM_OUT0\n3 = CLK_M",
              2, old_value_t.owr_clk_src, new_value_t.owr_clk_src };
    m_bit_details_model.bits.append(entry);
}

#define CLK_SOURCE_NOR_OFFSET 0x1D0
#define CLK_SOURCE_NOR_UNDEFMASK 0x3FFFFF00
union clk_source_nor_u {
    struct {
        unsigned int snor_clk_divisor:8;    /* N = Divide by (n+1) (lsb denote 0.5x) */
        unsigned int undefined_bits_8_29:22;
        unsigned int snor_clk_src:2;        /* 00 = pllP_out0 01 = pllC_out0 10 = pllM_out0 11 = clk_m 0 = PLLP_OUT0 1 = PLLC_OUT0 2 = PLLM_OUT0 3 = CLK_M */
    };

    u_int32_t reg32;
};

void CarDev::fill_clk_source_nor_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const clk_source_nor_u old_value_t = { .reg32 = value };
    const clk_source_nor_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: snor_clk_divisor:8",
              "N = Divide by (n+1) (lsb denote 0.5x)",
              8, old_value_t.snor_clk_divisor, new_value_t.snor_clk_divisor };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_29:22", "", 22, old_value_t.undefined_bits_8_29, new_value_t.undefined_bits_8_29 };
    m_bit_details_model.bits.append(entry);
    entry = { "30: snor_clk_src:2",
              "00 = pllP_out0\n01 = pllC_out0\n10 = pllM_out0\n11 = clk_m\n0 = PLLP_OUT0\n1 = PLLC_OUT0\n2 = PLLM_OUT0\n3 = CLK_M",
              2, old_value_t.snor_clk_src, new_value_t.snor_clk_src };
    m_bit_details_model.bits.append(entry);
}

#define CLK_SOURCE_CSITE_OFFSET 0x1D4
#define CLK_SOURCE_CSITE_UNDEFMASK 0x3FFFFF00
union clk_source_csite_u {
    struct {
        unsigned int csite_clk_divisor:8;   /* N = Divide by (n+1) (lsb denote 0.5x) */
        unsigned int undefined_bits_8_29:22;
        unsigned int csite_clk_src:2;       /* 00 = pllP_out0 01 = pllC_out0 10 = pllM_out0 11 = clk_m 0 = PLLP_OUT0 1 = PLLC_OUT0 2 = PLLM_OUT0 3 = CLK_M */
    };

    u_int32_t reg32;
};

void CarDev::fill_clk_source_csite_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const clk_source_csite_u old_value_t = { .reg32 = value };
    const clk_source_csite_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: csite_clk_divisor:8",
              "N = Divide by (n+1) (lsb denote 0.5x)",
              8, old_value_t.csite_clk_divisor, new_value_t.csite_clk_divisor };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_29:22", "", 22, old_value_t.undefined_bits_8_29, new_value_t.undefined_bits_8_29 };
    m_bit_details_model.bits.append(entry);
    entry = { "30: csite_clk_src:2",
              "00 = pllP_out0\n01 = pllC_out0\n10 = pllM_out0\n11 = clk_m\n0 = PLLP_OUT0\n1 = PLLC_OUT0\n2 = PLLM_OUT0\n3 = CLK_M",
              2, old_value_t.csite_clk_src, new_value_t.csite_clk_src };
    m_bit_details_model.bits.append(entry);
}

#define CLK_SOURCE_OSC_OFFSET 0x1FC
#define CLK_SOURCE_OSC_UNDEFMASK 0xEFFFFFFF
union clk_source_osc_u {
    struct {
        unsigned int undefined_bits_0_27:28;
        unsigned int osc_clk_src:1;         /* 0 = external oscillator 1 = internal PLL_S 0 = EXT_OSC */
        unsigned int undefined_bits_29_31:3;
    };

    u_int32_t reg32;
};

void CarDev::fill_clk_source_osc_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const clk_source_osc_u old_value_t = { .reg32 = value };
    const clk_source_osc_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_27:28", "", 28, old_value_t.undefined_bits_0_27, new_value_t.undefined_bits_0_27 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: osc_clk_src:1",
              "0 = external oscillator\n1 = internal PLL_S\n0 = EXT_OSC",
              1, old_value_t.osc_clk_src, new_value_t.osc_clk_src };
    m_bit_details_model.bits.append(entry);
    entry = { "29: undefined_bits_29_31:3", "", 3, old_value_t.undefined_bits_29_31, new_value_t.undefined_bits_29_31 };
    m_bit_details_model.bits.append(entry);
}

#define RST_DEV_L_SET_OFFSET 0x300
#define RST_DEV_L_SET_UNDEFMASK 0x40000000
union rst_dev_l_set_u {
    struct {
        unsigned int set_cpu_rst:1;         /* set reset CPU */
        unsigned int set_cop_rst:1;         /* set reset COP */
        unsigned int set_trig_sys_rst:1;    /* Write 1 to pulse System Reset Signal */
        unsigned int set_ac97_rst:1;        /* set reset AC97 Controller */
        unsigned int set_rtc_rst:1;         /* set reset RTC Controller */
        unsigned int set_tmr_rst:1;         /* set reset Timer Controller */
        unsigned int set_uart1_rst:1;       /* set reset UART1 Controller */
        unsigned int set_uart2_rst:1;       /* set reset UART2/VFIR Controller */
        unsigned int set_gpio_rst:1;        /* set reset GPIO Controller */
        unsigned int set_sdmmc2_rst:1;      /* set reset SDMMC2 Controller */
        unsigned int set_spdif_rst:1;       /* set reset SPDIF Controller */
        unsigned int set_i2s1_rst:1;        /* set reset I2S 1 Controller */
        unsigned int set_i2c1_rst:1;        /* set reset I2C1 Controller */
        unsigned int set_ndflash_rst:1;     /* set reset NAND flash controller */
        unsigned int set_sdmmc1_rst:1;      /* set reset SDMMC1 controller */
        unsigned int set_sdmmc4_rst:1;      /* set reset SDMMC4 controller */
        unsigned int set_twc_rst:1;         /* set reset Three Wire Controller */
        unsigned int set_pwm_rst:1;         /* set reset Pulse Width Modulator */
        unsigned int set_i2s2_rst:1;        /* set reset I2S 2 Controller */
        unsigned int set_epp_rst:1;         /* set reset EPP controller */
        unsigned int set_vi_rst:1;          /* set reset VI controller */
        unsigned int set_2d_rst:1;          /* set reset 2D graphics engine controller */
        unsigned int set_usbd_rst:1;        /* set reset USB controller */
        unsigned int set_isp_rst:1;         /* set reset ISP controller */
        unsigned int set_3d_rst:1;          /* set reset 3D controller */
        unsigned int set_ide_rst:1;         /* set reset IDE controller */
        unsigned int set_disp2_rst:1;       /* set reset DISP2 controller */
        unsigned int set_disp1_rst:1;       /* set reset DISP1 controller */
        unsigned int set_host1x_rst:1;      /* set reset HOST1X */
        unsigned int set_vcp_rst:1;         /* set reset vector co-processor */
        unsigned int undefined_bit_30:1;
        unsigned int set_cache2_rst:1;      /* set reset COP cache controller */
    };

    u_int32_t reg32;
};

void CarDev::fill_rst_dev_l_set_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const rst_dev_l_set_u old_value_t = { .reg32 = value };
    const rst_dev_l_set_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: set_cpu_rst:1",
              "set reset CPU",
              1, old_value_t.set_cpu_rst, new_value_t.set_cpu_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "01: set_cop_rst:1",
              "set reset COP",
              1, old_value_t.set_cop_rst, new_value_t.set_cop_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "02: set_trig_sys_rst:1",
              "Write 1 to pulse System Reset Signal",
              1, old_value_t.set_trig_sys_rst, new_value_t.set_trig_sys_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "03: set_ac97_rst:1",
              "set reset AC97 Controller",
              1, old_value_t.set_ac97_rst, new_value_t.set_ac97_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "04: set_rtc_rst:1",
              "set reset RTC Controller",
              1, old_value_t.set_rtc_rst, new_value_t.set_rtc_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "05: set_tmr_rst:1",
              "set reset Timer Controller",
              1, old_value_t.set_tmr_rst, new_value_t.set_tmr_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "06: set_uart1_rst:1",
              "set reset UART1 Controller",
              1, old_value_t.set_uart1_rst, new_value_t.set_uart1_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "07: set_uart2_rst:1",
              "set reset UART2/VFIR Controller",
              1, old_value_t.set_uart2_rst, new_value_t.set_uart2_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "08: set_gpio_rst:1",
              "set reset GPIO Controller",
              1, old_value_t.set_gpio_rst, new_value_t.set_gpio_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "09: set_sdmmc2_rst:1",
              "set reset SDMMC2 Controller",
              1, old_value_t.set_sdmmc2_rst, new_value_t.set_sdmmc2_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "10: set_spdif_rst:1",
              "set reset SPDIF Controller",
              1, old_value_t.set_spdif_rst, new_value_t.set_spdif_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "11: set_i2s1_rst:1",
              "set reset I2S 1 Controller",
              1, old_value_t.set_i2s1_rst, new_value_t.set_i2s1_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "12: set_i2c1_rst:1",
              "set reset I2C1 Controller",
              1, old_value_t.set_i2c1_rst, new_value_t.set_i2c1_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "13: set_ndflash_rst:1",
              "set reset NAND flash controller",
              1, old_value_t.set_ndflash_rst, new_value_t.set_ndflash_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "14: set_sdmmc1_rst:1",
              "set reset SDMMC1 controller",
              1, old_value_t.set_sdmmc1_rst, new_value_t.set_sdmmc1_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "15: set_sdmmc4_rst:1",
              "set reset SDMMC4 controller",
              1, old_value_t.set_sdmmc4_rst, new_value_t.set_sdmmc4_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "16: set_twc_rst:1",
              "set reset Three Wire Controller",
              1, old_value_t.set_twc_rst, new_value_t.set_twc_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "17: set_pwm_rst:1",
              "set reset Pulse Width Modulator",
              1, old_value_t.set_pwm_rst, new_value_t.set_pwm_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "18: set_i2s2_rst:1",
              "set reset I2S 2 Controller",
              1, old_value_t.set_i2s2_rst, new_value_t.set_i2s2_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "19: set_epp_rst:1",
              "set reset EPP controller",
              1, old_value_t.set_epp_rst, new_value_t.set_epp_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "20: set_vi_rst:1",
              "set reset VI controller",
              1, old_value_t.set_vi_rst, new_value_t.set_vi_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "21: set_2d_rst:1",
              "set reset 2D graphics engine controller",
              1, old_value_t.set_2d_rst, new_value_t.set_2d_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "22: set_usbd_rst:1",
              "set reset USB controller",
              1, old_value_t.set_usbd_rst, new_value_t.set_usbd_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "23: set_isp_rst:1",
              "set reset ISP controller",
              1, old_value_t.set_isp_rst, new_value_t.set_isp_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "24: set_3d_rst:1",
              "set reset 3D controller",
              1, old_value_t.set_3d_rst, new_value_t.set_3d_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "25: set_ide_rst:1",
              "set reset IDE controller",
              1, old_value_t.set_ide_rst, new_value_t.set_ide_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "26: set_disp2_rst:1",
              "set reset DISP2 controller",
              1, old_value_t.set_disp2_rst, new_value_t.set_disp2_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "27: set_disp1_rst:1",
              "set reset DISP1 controller",
              1, old_value_t.set_disp1_rst, new_value_t.set_disp1_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "28: set_host1x_rst:1",
              "set reset HOST1X",
              1, old_value_t.set_host1x_rst, new_value_t.set_host1x_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "29: set_vcp_rst:1",
              "set reset vector co-processor",
              1, old_value_t.set_vcp_rst, new_value_t.set_vcp_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "30: undefined_bit_30:1", "", 1, old_value_t.undefined_bit_30, new_value_t.undefined_bit_30 };
    m_bit_details_model.bits.append(entry);
    entry = { "31: set_cache2_rst:1",
              "set reset COP cache controller",
              1, old_value_t.set_cache2_rst, new_value_t.set_cache2_rst };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "The RST_DEV_(L,H,U)_(SET,CLR) and CLK_ENB_(L,H,U)_(SET,CLR) registers are provided as an alternate method of programming the same registers found in RST_DEVICES_(L,H,U) and CLK_OUT_ENB_(L,H,U) registers, respectively. Therefore, using either methods will change the same underlying peripherals reset, and clock enable control for write. As for read, again, user can use either method to retrieve the reset/clock-enable state of each peripherals.";
}

#define RST_DEV_L_CLR_OFFSET 0x304
#define RST_DEV_L_CLR_UNDEFMASK 0x40000004
union rst_dev_l_clr_u {
    struct {
        unsigned int clr_cpu_rst:1;         /* clear reset CPU */
        unsigned int clr_cop_rst:1;         /* clear reset COP */
        unsigned int undefined_bit_2:1;
        unsigned int clr_ac97_rst:1;        /* clear reset AC97 Controller */
        unsigned int clr_rtc_rst:1;         /* clear reset RTC Controller */
        unsigned int clr_tmr_rst:1;         /* clear reset Timer Controller */
        unsigned int clr_uart1_rst:1;       /* clear reset UART1 Controller */
        unsigned int clr_uart2_rst:1;       /* clear reset UART2/VFIR Controller */
        unsigned int clr_gpio_rst:1;        /* clear reset GPIO Controller */
        unsigned int clr_sdmmc2_rst:1;      /* clear reset SDMMC2 Controller */
        unsigned int clr_spdif_rst:1;       /* clear reset SPDIF Controller */
        unsigned int clr_i2s1_rst:1;        /* clear reset I2S 1 Controller */
        unsigned int clr_i2c1_rst:1;        /* clear reset I2C1 Controller */
        unsigned int clr_ndflash_rst:1;     /* clear reset NAND flash controller */
        unsigned int clr_sdmmc1_rst:1;      /* clear reset SDMMC1 controller */
        unsigned int clr_sdmmc4_rst:1;      /* clear reset SDMMC4 controller */
        unsigned int clr_twc_rst:1;         /* clear reset Three Wire Controller */
        unsigned int clr_pwm_rst:1;         /* clear reset Pulse Width Modulator */
        unsigned int clr_i2s2_rst:1;        /* clear reset I2S 2 Controller */
        unsigned int clr_epp_rst:1;         /* clear reset EPP controller */
        unsigned int clr_vi_rst:1;          /* clear reset VI controller */
        unsigned int clr_2d_rst:1;          /* clear reset 2D graphics engine controller */
        unsigned int clr_usbd_rst:1;        /* clear reset USB controller */
        unsigned int clr_isp_rst:1;         /* clear reset ISP controller */
        unsigned int clr_3d_rst:1;          /* clear reset 3D controller */
        unsigned int clr_ide_rst:1;         /* clear reset IDE controller */
        unsigned int clr_disp2_rst:1;       /* clear reset DISP2 controller */
        unsigned int clr_disp1_rst:1;       /* clear reset DISP1 controller */
        unsigned int clr_host1x_rst:1;      /* clear reset HOST1X */
        unsigned int clr_vcp_rst:1;         /* clear reset vector co-processor */
        unsigned int undefined_bit_30:1;
        unsigned int clr_cache2_rst:1;      /* clear reset COP cache controller */
    };

    u_int32_t reg32;
};

void CarDev::fill_rst_dev_l_clr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const rst_dev_l_clr_u old_value_t = { .reg32 = value };
    const rst_dev_l_clr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: clr_cpu_rst:1",
              "clear reset CPU",
              1, old_value_t.clr_cpu_rst, new_value_t.clr_cpu_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "01: clr_cop_rst:1",
              "clear reset COP",
              1, old_value_t.clr_cop_rst, new_value_t.clr_cop_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "02: undefined_bit_2:1", "", 1, old_value_t.undefined_bit_2, new_value_t.undefined_bit_2 };
    m_bit_details_model.bits.append(entry);
    entry = { "03: clr_ac97_rst:1",
              "clear reset AC97 Controller",
              1, old_value_t.clr_ac97_rst, new_value_t.clr_ac97_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "04: clr_rtc_rst:1",
              "clear reset RTC Controller",
              1, old_value_t.clr_rtc_rst, new_value_t.clr_rtc_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "05: clr_tmr_rst:1",
              "clear reset Timer Controller",
              1, old_value_t.clr_tmr_rst, new_value_t.clr_tmr_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "06: clr_uart1_rst:1",
              "clear reset UART1 Controller",
              1, old_value_t.clr_uart1_rst, new_value_t.clr_uart1_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "07: clr_uart2_rst:1",
              "clear reset UART2/VFIR Controller",
              1, old_value_t.clr_uart2_rst, new_value_t.clr_uart2_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "08: clr_gpio_rst:1",
              "clear reset GPIO Controller",
              1, old_value_t.clr_gpio_rst, new_value_t.clr_gpio_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "09: clr_sdmmc2_rst:1",
              "clear reset SDMMC2 Controller",
              1, old_value_t.clr_sdmmc2_rst, new_value_t.clr_sdmmc2_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "10: clr_spdif_rst:1",
              "clear reset SPDIF Controller",
              1, old_value_t.clr_spdif_rst, new_value_t.clr_spdif_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "11: clr_i2s1_rst:1",
              "clear reset I2S 1 Controller",
              1, old_value_t.clr_i2s1_rst, new_value_t.clr_i2s1_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "12: clr_i2c1_rst:1",
              "clear reset I2C1 Controller",
              1, old_value_t.clr_i2c1_rst, new_value_t.clr_i2c1_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "13: clr_ndflash_rst:1",
              "clear reset NAND flash controller",
              1, old_value_t.clr_ndflash_rst, new_value_t.clr_ndflash_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "14: clr_sdmmc1_rst:1",
              "clear reset SDMMC1 controller",
              1, old_value_t.clr_sdmmc1_rst, new_value_t.clr_sdmmc1_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "15: clr_sdmmc4_rst:1",
              "clear reset SDMMC4 controller",
              1, old_value_t.clr_sdmmc4_rst, new_value_t.clr_sdmmc4_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "16: clr_twc_rst:1",
              "clear reset Three Wire Controller",
              1, old_value_t.clr_twc_rst, new_value_t.clr_twc_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "17: clr_pwm_rst:1",
              "clear reset Pulse Width Modulator",
              1, old_value_t.clr_pwm_rst, new_value_t.clr_pwm_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "18: clr_i2s2_rst:1",
              "clear reset I2S 2 Controller",
              1, old_value_t.clr_i2s2_rst, new_value_t.clr_i2s2_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "19: clr_epp_rst:1",
              "clear reset EPP controller",
              1, old_value_t.clr_epp_rst, new_value_t.clr_epp_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "20: clr_vi_rst:1",
              "clear reset VI controller",
              1, old_value_t.clr_vi_rst, new_value_t.clr_vi_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "21: clr_2d_rst:1",
              "clear reset 2D graphics engine controller",
              1, old_value_t.clr_2d_rst, new_value_t.clr_2d_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "22: clr_usbd_rst:1",
              "clear reset USB controller",
              1, old_value_t.clr_usbd_rst, new_value_t.clr_usbd_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "23: clr_isp_rst:1",
              "clear reset ISP controller",
              1, old_value_t.clr_isp_rst, new_value_t.clr_isp_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "24: clr_3d_rst:1",
              "clear reset 3D controller",
              1, old_value_t.clr_3d_rst, new_value_t.clr_3d_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "25: clr_ide_rst:1",
              "clear reset IDE controller",
              1, old_value_t.clr_ide_rst, new_value_t.clr_ide_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "26: clr_disp2_rst:1",
              "clear reset DISP2 controller",
              1, old_value_t.clr_disp2_rst, new_value_t.clr_disp2_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "27: clr_disp1_rst:1",
              "clear reset DISP1 controller",
              1, old_value_t.clr_disp1_rst, new_value_t.clr_disp1_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "28: clr_host1x_rst:1",
              "clear reset HOST1X",
              1, old_value_t.clr_host1x_rst, new_value_t.clr_host1x_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "29: clr_vcp_rst:1",
              "clear reset vector co-processor",
              1, old_value_t.clr_vcp_rst, new_value_t.clr_vcp_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "30: undefined_bit_30:1", "", 1, old_value_t.undefined_bit_30, new_value_t.undefined_bit_30 };
    m_bit_details_model.bits.append(entry);
    entry = { "31: clr_cache2_rst:1",
              "clear reset COP cache controller",
              1, old_value_t.clr_cache2_rst, new_value_t.clr_cache2_rst };
    m_bit_details_model.bits.append(entry);
}

#define RST_DEV_H_SET_OFFSET 0x308
#define RST_DEV_H_SET_UNDEFMASK 0x01000008
union rst_dev_h_set_u {
    struct {
        unsigned int set_mem_rst:1;         /* set reset MC */
        unsigned int set_ahbdma_rst:1;      /* set reset AHB-DMA */
        unsigned int set_apbdma_rst:1;      /* set reset APB-DMA */
        unsigned int undefined_bit_3:1;
        unsigned int set_kbc_rst:1;         /* set reset Keyboard controller. */
        unsigned int set_stat_mon_rst:1;    /* set reset statistic monitor */
        unsigned int set_pmc_rst:1;         /* set reset PMC controller. */
        unsigned int set_fuse_rst:1;        /* set reset Fuse controller. */
        unsigned int set_kfuse_rst:1;       /* set reset KFuse controller */
        unsigned int set_sbc1_rst:1;        /* set reset SBC 1 (SPI 1) Controller */
        unsigned int set_snor_rst:1;        /* set reset NOR Flash Controller */
        unsigned int set_spi1_rst:1;        /* set reset SPI 1 Controller */
        unsigned int set_sbc2_rst:1;        /* set reset SBC 2 (SPI 2) Controller */
        unsigned int set_xio_rst:1;         /* set reset XIO controller */
        unsigned int set_sbc3_rst:1;        /* set reset SBC 3 (SPI 3) Controller */
        unsigned int set_dvc_i2c_rst:1;     /* set reset DVC-I2C Controller */
        unsigned int set_dsi_rst:1;         /* set reset DSI controller */
        unsigned int set_tvo_rst:1;         /* set reset TVO/CVE controller */
        unsigned int set_mipi_rst:1;        /* set reset MIPI base-band controller */
        unsigned int set_hdmi_rst:1;        /* set reset HDMI */
        unsigned int set_csi_rst:1;         /* set reset CSI controller */
        unsigned int set_tvdac_rst:1;       /* set reset TVDAC controller */
        unsigned int set_i2c2_rst:1;        /* set reset I2C 2 controller */
        unsigned int set_uart3_rst:1;       /* set reset UART3 Controller */
        unsigned int undefined_bit_24:1;
        unsigned int set_emc_rst:1;         /* set reset EMC controller */
        unsigned int set_usb2_rst:1;        /* set reset USB2 controller */
        unsigned int set_usb3_rst:1;        /* set reset USB3 controller */
        unsigned int set_mpe_rst:1;         /* set reset MPE controller */
        unsigned int set_vde_rst:1;         /* set reset VDE controller */
        unsigned int set_bsea_rst:1;        /* set reset BSEA controller */
        unsigned int set_bsev_rst:1;        /* set reset BSEV controller */
    };

    u_int32_t reg32;
};

void CarDev::fill_rst_dev_h_set_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const rst_dev_h_set_u old_value_t = { .reg32 = value };
    const rst_dev_h_set_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: set_mem_rst:1",
              "set reset MC",
              1, old_value_t.set_mem_rst, new_value_t.set_mem_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "01: set_ahbdma_rst:1",
              "set reset AHB-DMA",
              1, old_value_t.set_ahbdma_rst, new_value_t.set_ahbdma_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "02: set_apbdma_rst:1",
              "set reset APB-DMA",
              1, old_value_t.set_apbdma_rst, new_value_t.set_apbdma_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "03: undefined_bit_3:1", "", 1, old_value_t.undefined_bit_3, new_value_t.undefined_bit_3 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: set_kbc_rst:1",
              "set reset Keyboard controller.",
              1, old_value_t.set_kbc_rst, new_value_t.set_kbc_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "05: set_stat_mon_rst:1",
              "set reset statistic monitor",
              1, old_value_t.set_stat_mon_rst, new_value_t.set_stat_mon_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "06: set_pmc_rst:1",
              "set reset PMC controller.",
              1, old_value_t.set_pmc_rst, new_value_t.set_pmc_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "07: set_fuse_rst:1",
              "set reset Fuse controller.",
              1, old_value_t.set_fuse_rst, new_value_t.set_fuse_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "08: set_kfuse_rst:1",
              "set reset KFuse controller",
              1, old_value_t.set_kfuse_rst, new_value_t.set_kfuse_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "09: set_sbc1_rst:1",
              "set reset SBC 1 (SPI 1) Controller",
              1, old_value_t.set_sbc1_rst, new_value_t.set_sbc1_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "10: set_snor_rst:1",
              "set reset NOR Flash Controller",
              1, old_value_t.set_snor_rst, new_value_t.set_snor_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "11: set_spi1_rst:1",
              "set reset SPI 1 Controller",
              1, old_value_t.set_spi1_rst, new_value_t.set_spi1_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "12: set_sbc2_rst:1",
              "set reset SBC 2 (SPI 2) Controller",
              1, old_value_t.set_sbc2_rst, new_value_t.set_sbc2_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "13: set_xio_rst:1",
              "set reset XIO controller",
              1, old_value_t.set_xio_rst, new_value_t.set_xio_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "14: set_sbc3_rst:1",
              "set reset SBC 3 (SPI 3) Controller",
              1, old_value_t.set_sbc3_rst, new_value_t.set_sbc3_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "15: set_dvc_i2c_rst:1",
              "set reset DVC-I2C Controller",
              1, old_value_t.set_dvc_i2c_rst, new_value_t.set_dvc_i2c_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "16: set_dsi_rst:1",
              "set reset DSI controller",
              1, old_value_t.set_dsi_rst, new_value_t.set_dsi_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "17: set_tvo_rst:1",
              "set reset TVO/CVE controller",
              1, old_value_t.set_tvo_rst, new_value_t.set_tvo_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "18: set_mipi_rst:1",
              "set reset MIPI base-band controller",
              1, old_value_t.set_mipi_rst, new_value_t.set_mipi_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "19: set_hdmi_rst:1",
              "set reset HDMI",
              1, old_value_t.set_hdmi_rst, new_value_t.set_hdmi_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "20: set_csi_rst:1",
              "set reset CSI controller",
              1, old_value_t.set_csi_rst, new_value_t.set_csi_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "21: set_tvdac_rst:1",
              "set reset TVDAC controller",
              1, old_value_t.set_tvdac_rst, new_value_t.set_tvdac_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "22: set_i2c2_rst:1",
              "set reset I2C 2 controller",
              1, old_value_t.set_i2c2_rst, new_value_t.set_i2c2_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "23: set_uart3_rst:1",
              "set reset UART3 Controller",
              1, old_value_t.set_uart3_rst, new_value_t.set_uart3_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "24: undefined_bit_24:1", "", 1, old_value_t.undefined_bit_24, new_value_t.undefined_bit_24 };
    m_bit_details_model.bits.append(entry);
    entry = { "25: set_emc_rst:1",
              "set reset EMC controller",
              1, old_value_t.set_emc_rst, new_value_t.set_emc_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "26: set_usb2_rst:1",
              "set reset USB2 controller",
              1, old_value_t.set_usb2_rst, new_value_t.set_usb2_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "27: set_usb3_rst:1",
              "set reset USB3 controller",
              1, old_value_t.set_usb3_rst, new_value_t.set_usb3_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "28: set_mpe_rst:1",
              "set reset MPE controller",
              1, old_value_t.set_mpe_rst, new_value_t.set_mpe_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "29: set_vde_rst:1",
              "set reset VDE controller",
              1, old_value_t.set_vde_rst, new_value_t.set_vde_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "30: set_bsea_rst:1",
              "set reset BSEA controller",
              1, old_value_t.set_bsea_rst, new_value_t.set_bsea_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "31: set_bsev_rst:1",
              "set reset BSEV controller",
              1, old_value_t.set_bsev_rst, new_value_t.set_bsev_rst };
    m_bit_details_model.bits.append(entry);
}

#define RST_DEV_H_CLR_OFFSET 0x30C
#define RST_DEV_H_CLR_UNDEFMASK 0x01000008
union rst_dev_h_clr_u {
    struct {
        unsigned int clr_mem_rst:1;         /* clear reset MC */
        unsigned int clr_ahbdma_rst:1;      /* clear reset AHB-DMA */
        unsigned int clr_apbdma_rst:1;      /* clear reset APB-DMA */
        unsigned int undefined_bit_3:1;
        unsigned int clr_kbc_rst:1;         /* clear reset Keyboard controller. */
        unsigned int clr_stat_mon_rst:1;    /* clear reset statistic monitor */
        unsigned int clr_pmc_rst:1;         /* clear reset PMC controller. */
        unsigned int clr_fuse_rst:1;        /* clear reset Fuse controller. */
        unsigned int clr_kfuse_rst:1;       /* clear reset KFuse controller */
        unsigned int clr_sbc1_rst:1;        /* clear reset SBC 1 (SPI 1) Controller */
        unsigned int clr_snor_rst:1;        /* clear reset NOR Flash Controller */
        unsigned int clr_spi1_rst:1;        /* clear reset SPI 1 Controller */
        unsigned int clr_sbc2_rst:1;        /* clear reset SBC 2 (SPI 2)Controller */
        unsigned int clr_xio_rst:1;         /* clear reset XIO controller */
        unsigned int clr_sbc3_rst:1;        /* clear reset SBC 3 (SPI 3) Controller */
        unsigned int clr_dvc_i2c_rst:1;     /* clear reset DVC-I2C Controller */
        unsigned int clr_dsi_rst:1;         /* clear reset DSI controller */
        unsigned int clr_tvo_rst:1;         /* clear reset TVO/CVE controller */
        unsigned int clr_mipi_rst:1;        /* clear reset MIPI base-band controller */
        unsigned int clr_hdmi_rst:1;        /* clear reset HDMI */
        unsigned int clr_csi_rst:1;         /* clear reset CSI controller */
        unsigned int clr_tvdac_rst:1;       /* clear reset TVDAC controller */
        unsigned int clr_i2c2_rst:1;        /* clear reset I2C 2 controller */
        unsigned int clr_uart3_rst:1;       /* clear reset UART3 Controller */
        unsigned int undefined_bit_24:1;
        unsigned int clr_emc_rst:1;         /* clear reset EMC controller */
        unsigned int clr_usb2_rst:1;        /* clear reset USB2 controller */
        unsigned int clr_usb3_rst:1;        /* clear reset USB3 controller */
        unsigned int clr_mpe_rst:1;         /* clear reset MPE controller */
        unsigned int clr_vde_rst:1;         /* clear reset VDE controller */
        unsigned int clr_bsea_rst:1;        /* clear reset BSEA controller */
        unsigned int clr_bsev_rst:1;        /* clear reset BSEV controller */
    };

    u_int32_t reg32;
};

void CarDev::fill_rst_dev_h_clr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const rst_dev_h_clr_u old_value_t = { .reg32 = value };
    const rst_dev_h_clr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: clr_mem_rst:1",
              "clear reset MC",
              1, old_value_t.clr_mem_rst, new_value_t.clr_mem_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "01: clr_ahbdma_rst:1",
              "clear reset AHB-DMA",
              1, old_value_t.clr_ahbdma_rst, new_value_t.clr_ahbdma_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "02: clr_apbdma_rst:1",
              "clear reset APB-DMA",
              1, old_value_t.clr_apbdma_rst, new_value_t.clr_apbdma_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "03: undefined_bit_3:1", "", 1, old_value_t.undefined_bit_3, new_value_t.undefined_bit_3 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: clr_kbc_rst:1",
              "clear reset Keyboard controller.",
              1, old_value_t.clr_kbc_rst, new_value_t.clr_kbc_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "05: clr_stat_mon_rst:1",
              "clear reset statistic monitor",
              1, old_value_t.clr_stat_mon_rst, new_value_t.clr_stat_mon_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "06: clr_pmc_rst:1",
              "clear reset PMC controller.",
              1, old_value_t.clr_pmc_rst, new_value_t.clr_pmc_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "07: clr_fuse_rst:1",
              "clear reset Fuse controller.",
              1, old_value_t.clr_fuse_rst, new_value_t.clr_fuse_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "08: clr_kfuse_rst:1",
              "clear reset KFuse controller",
              1, old_value_t.clr_kfuse_rst, new_value_t.clr_kfuse_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "09: clr_sbc1_rst:1",
              "clear reset SBC 1 (SPI 1) Controller",
              1, old_value_t.clr_sbc1_rst, new_value_t.clr_sbc1_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "10: clr_snor_rst:1",
              "clear reset NOR Flash Controller",
              1, old_value_t.clr_snor_rst, new_value_t.clr_snor_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "11: clr_spi1_rst:1",
              "clear reset SPI 1 Controller",
              1, old_value_t.clr_spi1_rst, new_value_t.clr_spi1_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "12: clr_sbc2_rst:1",
              "clear reset SBC 2 (SPI 2)Controller",
              1, old_value_t.clr_sbc2_rst, new_value_t.clr_sbc2_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "13: clr_xio_rst:1",
              "clear reset XIO controller",
              1, old_value_t.clr_xio_rst, new_value_t.clr_xio_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "14: clr_sbc3_rst:1",
              "clear reset SBC 3 (SPI 3) Controller",
              1, old_value_t.clr_sbc3_rst, new_value_t.clr_sbc3_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "15: clr_dvc_i2c_rst:1",
              "clear reset DVC-I2C Controller",
              1, old_value_t.clr_dvc_i2c_rst, new_value_t.clr_dvc_i2c_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "16: clr_dsi_rst:1",
              "clear reset DSI controller",
              1, old_value_t.clr_dsi_rst, new_value_t.clr_dsi_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "17: clr_tvo_rst:1",
              "clear reset TVO/CVE controller",
              1, old_value_t.clr_tvo_rst, new_value_t.clr_tvo_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "18: clr_mipi_rst:1",
              "clear reset MIPI base-band controller",
              1, old_value_t.clr_mipi_rst, new_value_t.clr_mipi_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "19: clr_hdmi_rst:1",
              "clear reset HDMI",
              1, old_value_t.clr_hdmi_rst, new_value_t.clr_hdmi_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "20: clr_csi_rst:1",
              "clear reset CSI controller",
              1, old_value_t.clr_csi_rst, new_value_t.clr_csi_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "21: clr_tvdac_rst:1",
              "clear reset TVDAC controller",
              1, old_value_t.clr_tvdac_rst, new_value_t.clr_tvdac_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "22: clr_i2c2_rst:1",
              "clear reset I2C 2 controller",
              1, old_value_t.clr_i2c2_rst, new_value_t.clr_i2c2_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "23: clr_uart3_rst:1",
              "clear reset UART3 Controller",
              1, old_value_t.clr_uart3_rst, new_value_t.clr_uart3_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "24: undefined_bit_24:1", "", 1, old_value_t.undefined_bit_24, new_value_t.undefined_bit_24 };
    m_bit_details_model.bits.append(entry);
    entry = { "25: clr_emc_rst:1",
              "clear reset EMC controller",
              1, old_value_t.clr_emc_rst, new_value_t.clr_emc_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "26: clr_usb2_rst:1",
              "clear reset USB2 controller",
              1, old_value_t.clr_usb2_rst, new_value_t.clr_usb2_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "27: clr_usb3_rst:1",
              "clear reset USB3 controller",
              1, old_value_t.clr_usb3_rst, new_value_t.clr_usb3_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "28: clr_mpe_rst:1",
              "clear reset MPE controller",
              1, old_value_t.clr_mpe_rst, new_value_t.clr_mpe_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "29: clr_vde_rst:1",
              "clear reset VDE controller",
              1, old_value_t.clr_vde_rst, new_value_t.clr_vde_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "30: clr_bsea_rst:1",
              "clear reset BSEA controller",
              1, old_value_t.clr_bsea_rst, new_value_t.clr_bsea_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "31: clr_bsev_rst:1",
              "clear reset BSEV controller",
              1, old_value_t.clr_bsev_rst, new_value_t.clr_bsev_rst };
    m_bit_details_model.bits.append(entry);
}

#define RST_DEV_U_SET_OFFSET 0x310
#define RST_DEV_U_SET_UNDEFMASK 0xFFFFE000
union rst_dev_u_set_u {
    struct {
        unsigned int set_speedo_rst:1;      /* set reset SPEEDO controller */
        unsigned int set_uart4_rst:1;       /* set reset UART4 controller */
        unsigned int set_uart5_rst:1;       /* set reset UART5 controller */
        unsigned int set_i2c3_rst:1;        /* set reset I2C3 controller */
        unsigned int set_sbc4_rst:1;        /* set reset SBC4 (SPI 4) controller */
        unsigned int set_sdmmc3_rst:1;      /* set reset SDMMC3 controller */
        unsigned int set_pcie_rst:1;        /* set reset PCIE controller */
        unsigned int set_owr_rst:1;         /* set reset OWR controller */
        unsigned int set_afi_rst:1;         /* set reset AFI controller */
        unsigned int set_csite_rst:1;       /* set reset CSITE controller */
        unsigned int set_pciexclk_rst:1;    /* set reset PCIEXCLK logic */
        unsigned int set_avpucq_rst:1;      /* set reset AVPUCQ logic */
        unsigned int set_la_rst:1;          /* set reset LA logic. */
        unsigned int undefined_bits_13_31:19;
    };

    u_int32_t reg32;
};

void CarDev::fill_rst_dev_u_set_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const rst_dev_u_set_u old_value_t = { .reg32 = value };
    const rst_dev_u_set_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: set_speedo_rst:1",
              "set reset SPEEDO controller",
              1, old_value_t.set_speedo_rst, new_value_t.set_speedo_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "01: set_uart4_rst:1",
              "set reset UART4 controller",
              1, old_value_t.set_uart4_rst, new_value_t.set_uart4_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "02: set_uart5_rst:1",
              "set reset UART5 controller",
              1, old_value_t.set_uart5_rst, new_value_t.set_uart5_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "03: set_i2c3_rst:1",
              "set reset I2C3 controller",
              1, old_value_t.set_i2c3_rst, new_value_t.set_i2c3_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "04: set_sbc4_rst:1",
              "set reset SBC4 (SPI 4) controller",
              1, old_value_t.set_sbc4_rst, new_value_t.set_sbc4_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "05: set_sdmmc3_rst:1",
              "set reset SDMMC3 controller",
              1, old_value_t.set_sdmmc3_rst, new_value_t.set_sdmmc3_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "06: set_pcie_rst:1",
              "set reset PCIE controller",
              1, old_value_t.set_pcie_rst, new_value_t.set_pcie_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "07: set_owr_rst:1",
              "set reset OWR controller",
              1, old_value_t.set_owr_rst, new_value_t.set_owr_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "08: set_afi_rst:1",
              "set reset AFI controller",
              1, old_value_t.set_afi_rst, new_value_t.set_afi_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "09: set_csite_rst:1",
              "set reset CSITE controller",
              1, old_value_t.set_csite_rst, new_value_t.set_csite_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "10: set_pciexclk_rst:1",
              "set reset PCIEXCLK logic",
              1, old_value_t.set_pciexclk_rst, new_value_t.set_pciexclk_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "11: set_avpucq_rst:1",
              "set reset AVPUCQ logic",
              1, old_value_t.set_avpucq_rst, new_value_t.set_avpucq_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "12: set_la_rst:1",
              "set reset LA logic.",
              1, old_value_t.set_la_rst, new_value_t.set_la_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "13: undefined_bits_13_31:19", "", 19, old_value_t.undefined_bits_13_31, new_value_t.undefined_bits_13_31 };
    m_bit_details_model.bits.append(entry);
}

#define RST_DEV_U_CLR_OFFSET 0x314
#define RST_DEV_U_CLR_UNDEFMASK 0xFFFFE000
union rst_dev_u_clr_u {
    struct {
        unsigned int clr_speedo_rst:1;      /* clear reset SPEEDO controller */
        unsigned int clr_uart4_rst:1;       /* clear reset UART4 controller */
        unsigned int clr_uart5_rst:1;       /* clear reset UART5 controller */
        unsigned int clr_i2c3_rst:1;        /* clear reset I2C3 controller */
        unsigned int clr_sbc4_rst:1;        /* clear reset SBC4 (SPI 4) controller */
        unsigned int clr_sdmmc3_rst:1;      /* clear reset SDMMC3 controller */
        unsigned int clr_pcie_rst:1;        /* clear reset PCIE controller */
        unsigned int clr_owr_rst:1;         /* clear reset OWR controller */
        unsigned int clr_afi_rst:1;         /* clear reset AFI controller */
        unsigned int clr_csite_rst:1;       /* clear reset CSITE controller */
        unsigned int clr_pciexclk_rst:1;    /* clear reset PCIEXCLK logic */
        unsigned int clr_avpucq_rst:1;      /* clear reset AVPUCQ logic */
        unsigned int clr_la_rst:1;          /* clear reset LA logic. */
        unsigned int undefined_bits_13_31:19;
    };

    u_int32_t reg32;
};

void CarDev::fill_rst_dev_u_clr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const rst_dev_u_clr_u old_value_t = { .reg32 = value };
    const rst_dev_u_clr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: clr_speedo_rst:1",
              "clear reset SPEEDO controller",
              1, old_value_t.clr_speedo_rst, new_value_t.clr_speedo_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "01: clr_uart4_rst:1",
              "clear reset UART4 controller",
              1, old_value_t.clr_uart4_rst, new_value_t.clr_uart4_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "02: clr_uart5_rst:1",
              "clear reset UART5 controller",
              1, old_value_t.clr_uart5_rst, new_value_t.clr_uart5_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "03: clr_i2c3_rst:1",
              "clear reset I2C3 controller",
              1, old_value_t.clr_i2c3_rst, new_value_t.clr_i2c3_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "04: clr_sbc4_rst:1",
              "clear reset SBC4 (SPI 4) controller",
              1, old_value_t.clr_sbc4_rst, new_value_t.clr_sbc4_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "05: clr_sdmmc3_rst:1",
              "clear reset SDMMC3 controller",
              1, old_value_t.clr_sdmmc3_rst, new_value_t.clr_sdmmc3_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "06: clr_pcie_rst:1",
              "clear reset PCIE controller",
              1, old_value_t.clr_pcie_rst, new_value_t.clr_pcie_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "07: clr_owr_rst:1",
              "clear reset OWR controller",
              1, old_value_t.clr_owr_rst, new_value_t.clr_owr_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "08: clr_afi_rst:1",
              "clear reset AFI controller",
              1, old_value_t.clr_afi_rst, new_value_t.clr_afi_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "09: clr_csite_rst:1",
              "clear reset CSITE controller",
              1, old_value_t.clr_csite_rst, new_value_t.clr_csite_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "10: clr_pciexclk_rst:1",
              "clear reset PCIEXCLK logic",
              1, old_value_t.clr_pciexclk_rst, new_value_t.clr_pciexclk_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "11: clr_avpucq_rst:1",
              "clear reset AVPUCQ logic",
              1, old_value_t.clr_avpucq_rst, new_value_t.clr_avpucq_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "12: clr_la_rst:1",
              "clear reset LA logic.",
              1, old_value_t.clr_la_rst, new_value_t.clr_la_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "13: undefined_bits_13_31:19", "", 19, old_value_t.undefined_bits_13_31, new_value_t.undefined_bits_13_31 };
    m_bit_details_model.bits.append(entry);
}

#define CLK_ENB_L_SET_OFFSET 0x320
#define CLK_ENB_L_SET_UNDEFMASK 0x40000006
union clk_enb_l_set_u {
    struct {
        unsigned int set_clk_enb_cpu:1;     /* set enable clock to CPU */
        unsigned int undefined_bits_1_2:2;
        unsigned int set_clk_enb_ac97:1;    /* set enable clock to AC97 Controller */
        unsigned int set_clk_enb_rtc:1;     /* set enable clock to RTC Controller */
        unsigned int set_clk_enb_tmr:1;     /* set enable clock to Timer Controller */
        unsigned int set_clk_enb_uart1:1;   /* set enable clock to UART1 Controller */
        unsigned int set_clk_enb_uart2:1;   /* set enable clock to UART2/VFIR Controller */
        unsigned int set_clk_enb_gpio:1;    /* set enable clock to GPIO Controller */
        unsigned int set_clk_enb_sdmmc2:1;  /* set enable clock to SDMMC2 controller */
        unsigned int set_clk_enb_spdif:1;   /* set enable clock to SPDIF Controller */
        unsigned int set_clk_enb_i2s1:1;    /* set enable clock to I2S1 Controller */
        unsigned int set_clk_enb_i2c1:1;    /* set enable clock to I2C1 Controller */
        unsigned int set_clk_enb_ndflash:1; /* set enable clock to NAND flash controller */
        unsigned int set_clk_enb_sdmmc1:1;  /* set enable clock to SDMMC1 controller */
        unsigned int set_clk_enb_sdmmc4:1;  /* set enable clock to SDMMC4 controller */
        unsigned int set_clk_enb_twc:1;     /* set enable clock to 3-Wire Interface Controller */
        unsigned int set_clk_enb_pwm:1;     /* set enable clock to PWM (Pulse Width Modulator) */
        unsigned int set_clk_enb_i2s2:1;    /* set enable clock to I2S 2 controller */
        unsigned int set_clk_enb_epp:1;     /* set enable clock to EPP controller */
        unsigned int set_clk_enb_vi:1;      /* set enable clock to VI controller */
        unsigned int set_clk_enb_2d:1;      /* set enable clock to 2D graphics engine */
        unsigned int set_clk_enb_usbd:1;    /* set enable clock to USB controller */
        unsigned int set_clk_enb_isp:1;     /* set enable clock to ISP controller */
        unsigned int set_clk_enb_3d:1;      /* set enable clock to 3D controller */
        unsigned int set_clk_enb_ide:1;     /* set enable clock to IDE controller */
        unsigned int set_clk_enb_disp2:1;   /* set enable clock to DISP2 controller */
        unsigned int set_clk_enb_disp1:1;   /* set enable clock to DISP1 controller */
        unsigned int set_clk_enb_host1x:1;  /* set enable clock to HOST1X */
        unsigned int set_clk_enb_vcp:1;     /* set enable clock to vector co-processor */
        unsigned int undefined_bit_30:1;
        unsigned int set_clk_enb_cache2:1;  /* set enable clock to COP cache controller */
    };

    u_int32_t reg32;
};

void CarDev::fill_clk_enb_l_set_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const clk_enb_l_set_u old_value_t = { .reg32 = value };
    const clk_enb_l_set_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: set_clk_enb_cpu:1",
              "set enable clock to CPU",
              1, old_value_t.set_clk_enb_cpu, new_value_t.set_clk_enb_cpu };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_2:2", "", 2, old_value_t.undefined_bits_1_2, new_value_t.undefined_bits_1_2 };
    m_bit_details_model.bits.append(entry);
    entry = { "03: set_clk_enb_ac97:1",
              "set enable clock to AC97 Controller",
              1, old_value_t.set_clk_enb_ac97, new_value_t.set_clk_enb_ac97 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: set_clk_enb_rtc:1",
              "set enable clock to RTC Controller",
              1, old_value_t.set_clk_enb_rtc, new_value_t.set_clk_enb_rtc };
    m_bit_details_model.bits.append(entry);
    entry = { "05: set_clk_enb_tmr:1",
              "set enable clock to Timer Controller",
              1, old_value_t.set_clk_enb_tmr, new_value_t.set_clk_enb_tmr };
    m_bit_details_model.bits.append(entry);
    entry = { "06: set_clk_enb_uart1:1",
              "set enable clock to UART1 Controller",
              1, old_value_t.set_clk_enb_uart1, new_value_t.set_clk_enb_uart1 };
    m_bit_details_model.bits.append(entry);
    entry = { "07: set_clk_enb_uart2:1",
              "set enable clock to UART2/VFIR Controller",
              1, old_value_t.set_clk_enb_uart2, new_value_t.set_clk_enb_uart2 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: set_clk_enb_gpio:1",
              "set enable clock to GPIO Controller",
              1, old_value_t.set_clk_enb_gpio, new_value_t.set_clk_enb_gpio };
    m_bit_details_model.bits.append(entry);
    entry = { "09: set_clk_enb_sdmmc2:1",
              "set enable clock to SDMMC2 controller",
              1, old_value_t.set_clk_enb_sdmmc2, new_value_t.set_clk_enb_sdmmc2 };
    m_bit_details_model.bits.append(entry);
    entry = { "10: set_clk_enb_spdif:1",
              "set enable clock to SPDIF Controller",
              1, old_value_t.set_clk_enb_spdif, new_value_t.set_clk_enb_spdif };
    m_bit_details_model.bits.append(entry);
    entry = { "11: set_clk_enb_i2s1:1",
              "set enable clock to I2S1 Controller",
              1, old_value_t.set_clk_enb_i2s1, new_value_t.set_clk_enb_i2s1 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: set_clk_enb_i2c1:1",
              "set enable clock to I2C1 Controller",
              1, old_value_t.set_clk_enb_i2c1, new_value_t.set_clk_enb_i2c1 };
    m_bit_details_model.bits.append(entry);
    entry = { "13: set_clk_enb_ndflash:1",
              "set enable clock to NAND flash controller",
              1, old_value_t.set_clk_enb_ndflash, new_value_t.set_clk_enb_ndflash };
    m_bit_details_model.bits.append(entry);
    entry = { "14: set_clk_enb_sdmmc1:1",
              "set enable clock to SDMMC1 controller",
              1, old_value_t.set_clk_enb_sdmmc1, new_value_t.set_clk_enb_sdmmc1 };
    m_bit_details_model.bits.append(entry);
    entry = { "15: set_clk_enb_sdmmc4:1",
              "set enable clock to SDMMC4 controller",
              1, old_value_t.set_clk_enb_sdmmc4, new_value_t.set_clk_enb_sdmmc4 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: set_clk_enb_twc:1",
              "set enable clock to 3-Wire Interface Controller",
              1, old_value_t.set_clk_enb_twc, new_value_t.set_clk_enb_twc };
    m_bit_details_model.bits.append(entry);
    entry = { "17: set_clk_enb_pwm:1",
              "set enable clock to PWM (Pulse Width Modulator)",
              1, old_value_t.set_clk_enb_pwm, new_value_t.set_clk_enb_pwm };
    m_bit_details_model.bits.append(entry);
    entry = { "18: set_clk_enb_i2s2:1",
              "set enable clock to I2S 2 controller",
              1, old_value_t.set_clk_enb_i2s2, new_value_t.set_clk_enb_i2s2 };
    m_bit_details_model.bits.append(entry);
    entry = { "19: set_clk_enb_epp:1",
              "set enable clock to EPP controller",
              1, old_value_t.set_clk_enb_epp, new_value_t.set_clk_enb_epp };
    m_bit_details_model.bits.append(entry);
    entry = { "20: set_clk_enb_vi:1",
              "set enable clock to VI controller",
              1, old_value_t.set_clk_enb_vi, new_value_t.set_clk_enb_vi };
    m_bit_details_model.bits.append(entry);
    entry = { "21: set_clk_enb_2d:1",
              "set enable clock to 2D graphics engine",
              1, old_value_t.set_clk_enb_2d, new_value_t.set_clk_enb_2d };
    m_bit_details_model.bits.append(entry);
    entry = { "22: set_clk_enb_usbd:1",
              "set enable clock to USB controller",
              1, old_value_t.set_clk_enb_usbd, new_value_t.set_clk_enb_usbd };
    m_bit_details_model.bits.append(entry);
    entry = { "23: set_clk_enb_isp:1",
              "set enable clock to ISP controller",
              1, old_value_t.set_clk_enb_isp, new_value_t.set_clk_enb_isp };
    m_bit_details_model.bits.append(entry);
    entry = { "24: set_clk_enb_3d:1",
              "set enable clock to 3D controller",
              1, old_value_t.set_clk_enb_3d, new_value_t.set_clk_enb_3d };
    m_bit_details_model.bits.append(entry);
    entry = { "25: set_clk_enb_ide:1",
              "set enable clock to IDE controller",
              1, old_value_t.set_clk_enb_ide, new_value_t.set_clk_enb_ide };
    m_bit_details_model.bits.append(entry);
    entry = { "26: set_clk_enb_disp2:1",
              "set enable clock to DISP2 controller",
              1, old_value_t.set_clk_enb_disp2, new_value_t.set_clk_enb_disp2 };
    m_bit_details_model.bits.append(entry);
    entry = { "27: set_clk_enb_disp1:1",
              "set enable clock to DISP1 controller",
              1, old_value_t.set_clk_enb_disp1, new_value_t.set_clk_enb_disp1 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: set_clk_enb_host1x:1",
              "set enable clock to HOST1X",
              1, old_value_t.set_clk_enb_host1x, new_value_t.set_clk_enb_host1x };
    m_bit_details_model.bits.append(entry);
    entry = { "29: set_clk_enb_vcp:1",
              "set enable clock to vector co-processor",
              1, old_value_t.set_clk_enb_vcp, new_value_t.set_clk_enb_vcp };
    m_bit_details_model.bits.append(entry);
    entry = { "30: undefined_bit_30:1", "", 1, old_value_t.undefined_bit_30, new_value_t.undefined_bit_30 };
    m_bit_details_model.bits.append(entry);
    entry = { "31: set_clk_enb_cache2:1",
              "set enable clock to COP cache controller",
              1, old_value_t.set_clk_enb_cache2, new_value_t.set_clk_enb_cache2 };
    m_bit_details_model.bits.append(entry);
}

#define CLK_ENB_L_CLR_OFFSET 0x324
#define CLK_ENB_L_CLR_UNDEFMASK 0x40000006
union clk_enb_l_clr_u {
    struct {
        unsigned int clr_clk_enb_cpu:1;     /* clear enable clock to CPU */
        unsigned int undefined_bits_1_2:2;
        unsigned int clr_clk_enb_ac97:1;    /* clear enable clock to AC97 Controller */
        unsigned int clr_clk_enb_rtc:1;     /* clear enable clock to RTC Controller */
        unsigned int clr_clk_enb_tmr:1;     /* clear enable clock to Timer Controller */
        unsigned int clr_clk_enb_uart1:1;   /* clear enable clock to UART1 Controller */
        unsigned int clr_clk_enb_uart2:1;   /* clear enable clock to UART2/VFIR Controller */
        unsigned int clr_clk_enb_gpio:1;    /* clear enable clock to GPIO Controller */
        unsigned int clr_clk_enb_sdmmc2:1;  /* clear enable clock to SDMMC2 controller */
        unsigned int clr_clk_enb_spdif:1;   /* clear enable clock to SPDIF Controller */
        unsigned int clr_clk_enb_i2s1:1;    /* clear enable clock to I2S1 Controller */
        unsigned int clr_clk_enb_i2c1:1;    /* clear enable clock to I2C1 Controller */
        unsigned int clr_clk_enb_ndflash:1; /* clear enable clock to NAND flash controller */
        unsigned int clr_clk_enb_sdmmc1:1;  /* clear enable clock to SDMMC1 controller */
        unsigned int clr_clk_enb_sdmmc4:1;  /* clear enable clock to SDMMC4 controller */
        unsigned int clr_clk_enb_twc:1;     /* clear enable clock to 3-Wire Interface Controller */
        unsigned int clr_clk_enb_pwm:1;     /* clear enable clock to PWM (Pulse Width Modulator) */
        unsigned int clr_clk_enb_i2s2:1;    /* clear enable clock to I2S 2 controller */
        unsigned int clr_clk_enb_epp:1;     /* clear enable clock to EPP controller */
        unsigned int clr_clk_enb_vi:1;      /* clear enable clock to VI controller */
        unsigned int clr_clk_enb_2d:1;      /* clear enable clock to 2D graphics engine */
        unsigned int clr_clk_enb_usbd:1;    /* clear enable clock to USB controller */
        unsigned int clr_clk_enb_isp:1;     /* clear enable clock to ISP controller */
        unsigned int clr_clk_enb_3d:1;      /* clear enable clock to 3D controller */
        unsigned int clr_clk_enb_ide:1;     /* clear enable clock to IDE controller */
        unsigned int clr_clk_enb_disp2:1;   /* clear enable clock to DISP2 controller */
        unsigned int clr_clk_enb_disp1:1;   /* clear enable clock to DISP1 controller */
        unsigned int clr_clk_enb_host1x:1;  /* clear enable clock to HOST1X */
        unsigned int clr_clk_enb_vcp:1;     /* clear enable clock to vector co-processor */
        unsigned int undefined_bit_30:1;
        unsigned int clr_clk_enb_cache2:1;  /* clear enable clock to COP cache controller */
    };

    u_int32_t reg32;
};

void CarDev::fill_clk_enb_l_clr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const clk_enb_l_clr_u old_value_t = { .reg32 = value };
    const clk_enb_l_clr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: clr_clk_enb_cpu:1",
              "clear enable clock to CPU",
              1, old_value_t.clr_clk_enb_cpu, new_value_t.clr_clk_enb_cpu };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_2:2", "", 2, old_value_t.undefined_bits_1_2, new_value_t.undefined_bits_1_2 };
    m_bit_details_model.bits.append(entry);
    entry = { "03: clr_clk_enb_ac97:1",
              "clear enable clock to AC97 Controller",
              1, old_value_t.clr_clk_enb_ac97, new_value_t.clr_clk_enb_ac97 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: clr_clk_enb_rtc:1",
              "clear enable clock to RTC Controller",
              1, old_value_t.clr_clk_enb_rtc, new_value_t.clr_clk_enb_rtc };
    m_bit_details_model.bits.append(entry);
    entry = { "05: clr_clk_enb_tmr:1",
              "clear enable clock to Timer Controller",
              1, old_value_t.clr_clk_enb_tmr, new_value_t.clr_clk_enb_tmr };
    m_bit_details_model.bits.append(entry);
    entry = { "06: clr_clk_enb_uart1:1",
              "clear enable clock to UART1 Controller",
              1, old_value_t.clr_clk_enb_uart1, new_value_t.clr_clk_enb_uart1 };
    m_bit_details_model.bits.append(entry);
    entry = { "07: clr_clk_enb_uart2:1",
              "clear enable clock to UART2/VFIR Controller",
              1, old_value_t.clr_clk_enb_uart2, new_value_t.clr_clk_enb_uart2 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: clr_clk_enb_gpio:1",
              "clear enable clock to GPIO Controller",
              1, old_value_t.clr_clk_enb_gpio, new_value_t.clr_clk_enb_gpio };
    m_bit_details_model.bits.append(entry);
    entry = { "09: clr_clk_enb_sdmmc2:1",
              "clear enable clock to SDMMC2 controller",
              1, old_value_t.clr_clk_enb_sdmmc2, new_value_t.clr_clk_enb_sdmmc2 };
    m_bit_details_model.bits.append(entry);
    entry = { "10: clr_clk_enb_spdif:1",
              "clear enable clock to SPDIF Controller",
              1, old_value_t.clr_clk_enb_spdif, new_value_t.clr_clk_enb_spdif };
    m_bit_details_model.bits.append(entry);
    entry = { "11: clr_clk_enb_i2s1:1",
              "clear enable clock to I2S1 Controller",
              1, old_value_t.clr_clk_enb_i2s1, new_value_t.clr_clk_enb_i2s1 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: clr_clk_enb_i2c1:1",
              "clear enable clock to I2C1 Controller",
              1, old_value_t.clr_clk_enb_i2c1, new_value_t.clr_clk_enb_i2c1 };
    m_bit_details_model.bits.append(entry);
    entry = { "13: clr_clk_enb_ndflash:1",
              "clear enable clock to NAND flash controller",
              1, old_value_t.clr_clk_enb_ndflash, new_value_t.clr_clk_enb_ndflash };
    m_bit_details_model.bits.append(entry);
    entry = { "14: clr_clk_enb_sdmmc1:1",
              "clear enable clock to SDMMC1 controller",
              1, old_value_t.clr_clk_enb_sdmmc1, new_value_t.clr_clk_enb_sdmmc1 };
    m_bit_details_model.bits.append(entry);
    entry = { "15: clr_clk_enb_sdmmc4:1",
              "clear enable clock to SDMMC4 controller",
              1, old_value_t.clr_clk_enb_sdmmc4, new_value_t.clr_clk_enb_sdmmc4 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: clr_clk_enb_twc:1",
              "clear enable clock to 3-Wire Interface Controller",
              1, old_value_t.clr_clk_enb_twc, new_value_t.clr_clk_enb_twc };
    m_bit_details_model.bits.append(entry);
    entry = { "17: clr_clk_enb_pwm:1",
              "clear enable clock to PWM (Pulse Width Modulator)",
              1, old_value_t.clr_clk_enb_pwm, new_value_t.clr_clk_enb_pwm };
    m_bit_details_model.bits.append(entry);
    entry = { "18: clr_clk_enb_i2s2:1",
              "clear enable clock to I2S 2 controller",
              1, old_value_t.clr_clk_enb_i2s2, new_value_t.clr_clk_enb_i2s2 };
    m_bit_details_model.bits.append(entry);
    entry = { "19: clr_clk_enb_epp:1",
              "clear enable clock to EPP controller",
              1, old_value_t.clr_clk_enb_epp, new_value_t.clr_clk_enb_epp };
    m_bit_details_model.bits.append(entry);
    entry = { "20: clr_clk_enb_vi:1",
              "clear enable clock to VI controller",
              1, old_value_t.clr_clk_enb_vi, new_value_t.clr_clk_enb_vi };
    m_bit_details_model.bits.append(entry);
    entry = { "21: clr_clk_enb_2d:1",
              "clear enable clock to 2D graphics engine",
              1, old_value_t.clr_clk_enb_2d, new_value_t.clr_clk_enb_2d };
    m_bit_details_model.bits.append(entry);
    entry = { "22: clr_clk_enb_usbd:1",
              "clear enable clock to USB controller",
              1, old_value_t.clr_clk_enb_usbd, new_value_t.clr_clk_enb_usbd };
    m_bit_details_model.bits.append(entry);
    entry = { "23: clr_clk_enb_isp:1",
              "clear enable clock to ISP controller",
              1, old_value_t.clr_clk_enb_isp, new_value_t.clr_clk_enb_isp };
    m_bit_details_model.bits.append(entry);
    entry = { "24: clr_clk_enb_3d:1",
              "clear enable clock to 3D controller",
              1, old_value_t.clr_clk_enb_3d, new_value_t.clr_clk_enb_3d };
    m_bit_details_model.bits.append(entry);
    entry = { "25: clr_clk_enb_ide:1",
              "clear enable clock to IDE controller",
              1, old_value_t.clr_clk_enb_ide, new_value_t.clr_clk_enb_ide };
    m_bit_details_model.bits.append(entry);
    entry = { "26: clr_clk_enb_disp2:1",
              "clear enable clock to DISP2 controller",
              1, old_value_t.clr_clk_enb_disp2, new_value_t.clr_clk_enb_disp2 };
    m_bit_details_model.bits.append(entry);
    entry = { "27: clr_clk_enb_disp1:1",
              "clear enable clock to DISP1 controller",
              1, old_value_t.clr_clk_enb_disp1, new_value_t.clr_clk_enb_disp1 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: clr_clk_enb_host1x:1",
              "clear enable clock to HOST1X",
              1, old_value_t.clr_clk_enb_host1x, new_value_t.clr_clk_enb_host1x };
    m_bit_details_model.bits.append(entry);
    entry = { "29: clr_clk_enb_vcp:1",
              "clear enable clock to vector co-processor",
              1, old_value_t.clr_clk_enb_vcp, new_value_t.clr_clk_enb_vcp };
    m_bit_details_model.bits.append(entry);
    entry = { "30: undefined_bit_30:1", "", 1, old_value_t.undefined_bit_30, new_value_t.undefined_bit_30 };
    m_bit_details_model.bits.append(entry);
    entry = { "31: clr_clk_enb_cache2:1",
              "clear enable clock to COP cache controller",
              1, old_value_t.clr_clk_enb_cache2, new_value_t.clr_clk_enb_cache2 };
    m_bit_details_model.bits.append(entry);
}

#define CLK_ENB_H_SET_OFFSET 0x328
#define CLK_ENB_H_SET_UNDEFMASK 0x01000008
union clk_enb_h_set_u {
    struct {
        unsigned int set_clk_enb_mem:1;     /* set enable clock to MC/EMC */
        unsigned int set_clk_enb_ahbdma:1;  /* set enable clock to AHB-DMA */
        unsigned int set_clk_enb_apbdma:1;  /* set enable clock to APB-DMA */
        unsigned int undefined_bit_3:1;
        unsigned int set_clk_enb_kbc:1;     /* set enable clock to keyboard controller */
        unsigned int set_clk_enb_stat_mon:1;/* set enable clock to statistic monitor */
        unsigned int set_clk_enb_pmc:1;     /* set enable clock to PMC controller */
        unsigned int set_clk_enb_fuse:1;    /* set enable clock to FUSE controller */
        unsigned int set_clk_enb_kfuse:1;   /* set enable clock to KFUSE controller */
        unsigned int set_clk_enb_sbc1:1;    /* set enable clock to SBC 1 (SPI 1) Controller */
        unsigned int set_clk_enb_snor:1;    /* set enable clock to NOR Flash Controller */
        unsigned int set_clk_enb_spi1:1;    /* set enable clock to SPI 1 Controller */
        unsigned int set_clk_enb_sbc2:1;    /* set enable clock to SBC 2 (SPI 2) Controller */
        unsigned int set_clk_enb_xio:1;     /* set enable clock to XIO Controller */
        unsigned int set_clk_enb_sbc3:1;    /* set enable clock to SBC 3 (SPI 3) Controller */
        unsigned int set_clk_enb_dvc_i2c:1; /* set enable clock to DVC-I2C Controller */
        unsigned int set_clk_enb_dsi:1;     /* set enable clock to DSI controller */
        unsigned int set_clk_enb_tvo:1;     /* set enable clock to TVO/CVE controller */
        unsigned int set_clk_enb_mipi:1;    /* set enable clock to MIPI base-band controller */
        unsigned int set_clk_enb_hdmi:1;    /* set enable clock to HDMI */
        unsigned int set_clk_enb_csi:1;     /* set enable clock to CSI controller */
        unsigned int set_clk_enb_tvdac:1;   /* set enable clock to TVDAC controller */
        unsigned int set_clk_enb_i2c2:1;    /* set enable clock to I2C2 controller */
        unsigned int set_clk_enb_uart3:1;   /* set enable clock to UART3 Controller */
        unsigned int undefined_bit_24:1;
        unsigned int set_clk_enb_emc:1;     /* set enable clock to EMC controller */
        unsigned int set_clk_enb_usb2:1;    /* set enable clock to USB2 controller */
        unsigned int set_clk_enb_usb3:1;    /* set enable clock to USB3 controller */
        unsigned int set_clk_enb_mpe:1;     /* set enable clock to MPE controller */
        unsigned int set_clk_enb_vde:1;     /* set enable clock to VDE Controller */
        unsigned int set_clk_enb_bsea:1;    /* set enable clock to BSEA Controller */
        unsigned int set_clk_enb_bsev:1;    /* set enable clock to BSEV Controller */
    };

    u_int32_t reg32;
};

void CarDev::fill_clk_enb_h_set_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const clk_enb_h_set_u old_value_t = { .reg32 = value };
    const clk_enb_h_set_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: set_clk_enb_mem:1",
              "set enable clock to MC/EMC",
              1, old_value_t.set_clk_enb_mem, new_value_t.set_clk_enb_mem };
    m_bit_details_model.bits.append(entry);
    entry = { "01: set_clk_enb_ahbdma:1",
              "set enable clock to AHB-DMA",
              1, old_value_t.set_clk_enb_ahbdma, new_value_t.set_clk_enb_ahbdma };
    m_bit_details_model.bits.append(entry);
    entry = { "02: set_clk_enb_apbdma:1",
              "set enable clock to APB-DMA",
              1, old_value_t.set_clk_enb_apbdma, new_value_t.set_clk_enb_apbdma };
    m_bit_details_model.bits.append(entry);
    entry = { "03: undefined_bit_3:1", "", 1, old_value_t.undefined_bit_3, new_value_t.undefined_bit_3 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: set_clk_enb_kbc:1",
              "set enable clock to keyboard controller",
              1, old_value_t.set_clk_enb_kbc, new_value_t.set_clk_enb_kbc };
    m_bit_details_model.bits.append(entry);
    entry = { "05: set_clk_enb_stat_mon:1",
              "set enable clock to statistic monitor",
              1, old_value_t.set_clk_enb_stat_mon, new_value_t.set_clk_enb_stat_mon };
    m_bit_details_model.bits.append(entry);
    entry = { "06: set_clk_enb_pmc:1",
              "set enable clock to PMC controller",
              1, old_value_t.set_clk_enb_pmc, new_value_t.set_clk_enb_pmc };
    m_bit_details_model.bits.append(entry);
    entry = { "07: set_clk_enb_fuse:1",
              "set enable clock to FUSE controller",
              1, old_value_t.set_clk_enb_fuse, new_value_t.set_clk_enb_fuse };
    m_bit_details_model.bits.append(entry);
    entry = { "08: set_clk_enb_kfuse:1",
              "set enable clock to KFUSE controller",
              1, old_value_t.set_clk_enb_kfuse, new_value_t.set_clk_enb_kfuse };
    m_bit_details_model.bits.append(entry);
    entry = { "09: set_clk_enb_sbc1:1",
              "set enable clock to SBC 1 (SPI 1) Controller",
              1, old_value_t.set_clk_enb_sbc1, new_value_t.set_clk_enb_sbc1 };
    m_bit_details_model.bits.append(entry);
    entry = { "10: set_clk_enb_snor:1",
              "set enable clock to NOR Flash Controller",
              1, old_value_t.set_clk_enb_snor, new_value_t.set_clk_enb_snor };
    m_bit_details_model.bits.append(entry);
    entry = { "11: set_clk_enb_spi1:1",
              "set enable clock to SPI 1 Controller",
              1, old_value_t.set_clk_enb_spi1, new_value_t.set_clk_enb_spi1 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: set_clk_enb_sbc2:1",
              "set enable clock to SBC 2 (SPI 2) Controller",
              1, old_value_t.set_clk_enb_sbc2, new_value_t.set_clk_enb_sbc2 };
    m_bit_details_model.bits.append(entry);
    entry = { "13: set_clk_enb_xio:1",
              "set enable clock to XIO Controller",
              1, old_value_t.set_clk_enb_xio, new_value_t.set_clk_enb_xio };
    m_bit_details_model.bits.append(entry);
    entry = { "14: set_clk_enb_sbc3:1",
              "set enable clock to SBC 3 (SPI 3) Controller",
              1, old_value_t.set_clk_enb_sbc3, new_value_t.set_clk_enb_sbc3 };
    m_bit_details_model.bits.append(entry);
    entry = { "15: set_clk_enb_dvc_i2c:1",
              "set enable clock to DVC-I2C Controller",
              1, old_value_t.set_clk_enb_dvc_i2c, new_value_t.set_clk_enb_dvc_i2c };
    m_bit_details_model.bits.append(entry);
    entry = { "16: set_clk_enb_dsi:1",
              "set enable clock to DSI controller",
              1, old_value_t.set_clk_enb_dsi, new_value_t.set_clk_enb_dsi };
    m_bit_details_model.bits.append(entry);
    entry = { "17: set_clk_enb_tvo:1",
              "set enable clock to TVO/CVE controller",
              1, old_value_t.set_clk_enb_tvo, new_value_t.set_clk_enb_tvo };
    m_bit_details_model.bits.append(entry);
    entry = { "18: set_clk_enb_mipi:1",
              "set enable clock to MIPI base-band controller",
              1, old_value_t.set_clk_enb_mipi, new_value_t.set_clk_enb_mipi };
    m_bit_details_model.bits.append(entry);
    entry = { "19: set_clk_enb_hdmi:1",
              "set enable clock to HDMI",
              1, old_value_t.set_clk_enb_hdmi, new_value_t.set_clk_enb_hdmi };
    m_bit_details_model.bits.append(entry);
    entry = { "20: set_clk_enb_csi:1",
              "set enable clock to CSI controller",
              1, old_value_t.set_clk_enb_csi, new_value_t.set_clk_enb_csi };
    m_bit_details_model.bits.append(entry);
    entry = { "21: set_clk_enb_tvdac:1",
              "set enable clock to TVDAC controller",
              1, old_value_t.set_clk_enb_tvdac, new_value_t.set_clk_enb_tvdac };
    m_bit_details_model.bits.append(entry);
    entry = { "22: set_clk_enb_i2c2:1",
              "set enable clock to I2C2 controller",
              1, old_value_t.set_clk_enb_i2c2, new_value_t.set_clk_enb_i2c2 };
    m_bit_details_model.bits.append(entry);
    entry = { "23: set_clk_enb_uart3:1",
              "set enable clock to UART3 Controller",
              1, old_value_t.set_clk_enb_uart3, new_value_t.set_clk_enb_uart3 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: undefined_bit_24:1", "", 1, old_value_t.undefined_bit_24, new_value_t.undefined_bit_24 };
    m_bit_details_model.bits.append(entry);
    entry = { "25: set_clk_enb_emc:1",
              "set enable clock to EMC controller",
              1, old_value_t.set_clk_enb_emc, new_value_t.set_clk_enb_emc };
    m_bit_details_model.bits.append(entry);
    entry = { "26: set_clk_enb_usb2:1",
              "set enable clock to USB2 controller",
              1, old_value_t.set_clk_enb_usb2, new_value_t.set_clk_enb_usb2 };
    m_bit_details_model.bits.append(entry);
    entry = { "27: set_clk_enb_usb3:1",
              "set enable clock to USB3 controller",
              1, old_value_t.set_clk_enb_usb3, new_value_t.set_clk_enb_usb3 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: set_clk_enb_mpe:1",
              "set enable clock to MPE controller",
              1, old_value_t.set_clk_enb_mpe, new_value_t.set_clk_enb_mpe };
    m_bit_details_model.bits.append(entry);
    entry = { "29: set_clk_enb_vde:1",
              "set enable clock to VDE Controller",
              1, old_value_t.set_clk_enb_vde, new_value_t.set_clk_enb_vde };
    m_bit_details_model.bits.append(entry);
    entry = { "30: set_clk_enb_bsea:1",
              "set enable clock to BSEA Controller",
              1, old_value_t.set_clk_enb_bsea, new_value_t.set_clk_enb_bsea };
    m_bit_details_model.bits.append(entry);
    entry = { "31: set_clk_enb_bsev:1",
              "set enable clock to BSEV Controller",
              1, old_value_t.set_clk_enb_bsev, new_value_t.set_clk_enb_bsev };
    m_bit_details_model.bits.append(entry);
}

#define CLK_ENB_H_CLR_OFFSET 0x32C
#define CLK_ENB_H_CLR_UNDEFMASK 0x01000008
union clk_enb_h_clr_u {
    struct {
        unsigned int clr_clk_enb_mem:1;     /* clear enable clock to MC/EMC */
        unsigned int clr_clk_enb_ahbdma:1;  /* clear enable clock to AHB-DMA */
        unsigned int clr_clk_enb_apbdma:1;  /* clear enable clock to APB-DMA */
        unsigned int undefined_bit_3:1;
        unsigned int clr_clk_enb_kbc:1;     /* clear enable clock to keyboard controller */
        unsigned int clr_clk_enb_stat_mon:1;/* clear enable clock to statistic monitor */
        unsigned int clr_clk_enb_pmc:1;     /* clear enable clock to PMC controller */
        unsigned int clr_clk_enb_fuse:1;    /* clear enable clock to FUSE controller */
        unsigned int clr_clk_enb_kfuse:1;   /* clear enable clock to KFUSE controller */
        unsigned int clr_clk_enb_sbc1:1;    /* clear enable clock to SBC 1 (SPI 1) Controller */
        unsigned int clr_clk_enb_snor:1;    /* clear enable clock to NOR Flash Controller */
        unsigned int clr_clk_enb_spi1:1;    /* clear enable clock to SPI 1 Controller */
        unsigned int clr_clk_enb_sbc2:1;    /* clear enable clock to SBC 2 (SPI 2) Controller */
        unsigned int clr_clk_enb_xio:1;     /* clear enable clock to XIO Controller */
        unsigned int clr_clk_enb_sbc3:1;    /* clear enable clock to SBC 3 (SPI 3) Controller */
        unsigned int clr_clk_enb_dvc_i2c:1; /* clear enable clock to DVC-I2C Controller */
        unsigned int clr_clk_enb_dsi:1;     /* clear enable clock to DSI controller */
        unsigned int clr_clk_enb_tvo:1;     /* clear enable clock to TVO/CVE controller */
        unsigned int clr_clk_enb_mipi:1;    /* clear enable clock to MIPI base-band controller */
        unsigned int clr_clk_enb_hdmi:1;    /* clear enable clock to HDMI */
        unsigned int clr_clk_enb_csi:1;     /* clear enable clock to CSI controller */
        unsigned int clr_clk_enb_tvdac:1;   /* clear enable clock to TVDAC controller */
        unsigned int clr_clk_enb_i2c2:1;    /* clear enable clock to I2C2 controller */
        unsigned int clr_clk_enb_uart3:1;   /* clear enable clock to UART3 Controller */
        unsigned int undefined_bit_24:1;
        unsigned int clr_clk_enb_emc:1;     /* clear enable clock to EMC controller */
        unsigned int clr_clk_enb_usb2:1;    /* clear enable clock to USB2 controller */
        unsigned int clr_clk_enb_usb3:1;    /* clear enable clock to USB3 controller */
        unsigned int clr_clk_enb_mpe:1;     /* clear enable clock to MPE controller */
        unsigned int clr_clk_enb_vde:1;     /* clear enable clock to VDE Controller */
        unsigned int clr_clk_enb_bsea:1;    /* clear enable clock to BSEA Controller */
        unsigned int clr_clk_enb_bsev:1;    /* clear enable clock to BSEV Controller */
    };

    u_int32_t reg32;
};

void CarDev::fill_clk_enb_h_clr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const clk_enb_h_clr_u old_value_t = { .reg32 = value };
    const clk_enb_h_clr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: clr_clk_enb_mem:1",
              "clear enable clock to MC/EMC",
              1, old_value_t.clr_clk_enb_mem, new_value_t.clr_clk_enb_mem };
    m_bit_details_model.bits.append(entry);
    entry = { "01: clr_clk_enb_ahbdma:1",
              "clear enable clock to AHB-DMA",
              1, old_value_t.clr_clk_enb_ahbdma, new_value_t.clr_clk_enb_ahbdma };
    m_bit_details_model.bits.append(entry);
    entry = { "02: clr_clk_enb_apbdma:1",
              "clear enable clock to APB-DMA",
              1, old_value_t.clr_clk_enb_apbdma, new_value_t.clr_clk_enb_apbdma };
    m_bit_details_model.bits.append(entry);
    entry = { "03: undefined_bit_3:1", "", 1, old_value_t.undefined_bit_3, new_value_t.undefined_bit_3 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: clr_clk_enb_kbc:1",
              "clear enable clock to keyboard controller",
              1, old_value_t.clr_clk_enb_kbc, new_value_t.clr_clk_enb_kbc };
    m_bit_details_model.bits.append(entry);
    entry = { "05: clr_clk_enb_stat_mon:1",
              "clear enable clock to statistic monitor",
              1, old_value_t.clr_clk_enb_stat_mon, new_value_t.clr_clk_enb_stat_mon };
    m_bit_details_model.bits.append(entry);
    entry = { "06: clr_clk_enb_pmc:1",
              "clear enable clock to PMC controller",
              1, old_value_t.clr_clk_enb_pmc, new_value_t.clr_clk_enb_pmc };
    m_bit_details_model.bits.append(entry);
    entry = { "07: clr_clk_enb_fuse:1",
              "clear enable clock to FUSE controller",
              1, old_value_t.clr_clk_enb_fuse, new_value_t.clr_clk_enb_fuse };
    m_bit_details_model.bits.append(entry);
    entry = { "08: clr_clk_enb_kfuse:1",
              "clear enable clock to KFUSE controller",
              1, old_value_t.clr_clk_enb_kfuse, new_value_t.clr_clk_enb_kfuse };
    m_bit_details_model.bits.append(entry);
    entry = { "09: clr_clk_enb_sbc1:1",
              "clear enable clock to SBC 1 (SPI 1) Controller",
              1, old_value_t.clr_clk_enb_sbc1, new_value_t.clr_clk_enb_sbc1 };
    m_bit_details_model.bits.append(entry);
    entry = { "10: clr_clk_enb_snor:1",
              "clear enable clock to NOR Flash Controller",
              1, old_value_t.clr_clk_enb_snor, new_value_t.clr_clk_enb_snor };
    m_bit_details_model.bits.append(entry);
    entry = { "11: clr_clk_enb_spi1:1",
              "clear enable clock to SPI 1 Controller",
              1, old_value_t.clr_clk_enb_spi1, new_value_t.clr_clk_enb_spi1 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: clr_clk_enb_sbc2:1",
              "clear enable clock to SBC 2 (SPI 2) Controller",
              1, old_value_t.clr_clk_enb_sbc2, new_value_t.clr_clk_enb_sbc2 };
    m_bit_details_model.bits.append(entry);
    entry = { "13: clr_clk_enb_xio:1",
              "clear enable clock to XIO Controller",
              1, old_value_t.clr_clk_enb_xio, new_value_t.clr_clk_enb_xio };
    m_bit_details_model.bits.append(entry);
    entry = { "14: clr_clk_enb_sbc3:1",
              "clear enable clock to SBC 3 (SPI 3) Controller",
              1, old_value_t.clr_clk_enb_sbc3, new_value_t.clr_clk_enb_sbc3 };
    m_bit_details_model.bits.append(entry);
    entry = { "15: clr_clk_enb_dvc_i2c:1",
              "clear enable clock to DVC-I2C Controller",
              1, old_value_t.clr_clk_enb_dvc_i2c, new_value_t.clr_clk_enb_dvc_i2c };
    m_bit_details_model.bits.append(entry);
    entry = { "16: clr_clk_enb_dsi:1",
              "clear enable clock to DSI controller",
              1, old_value_t.clr_clk_enb_dsi, new_value_t.clr_clk_enb_dsi };
    m_bit_details_model.bits.append(entry);
    entry = { "17: clr_clk_enb_tvo:1",
              "clear enable clock to TVO/CVE controller",
              1, old_value_t.clr_clk_enb_tvo, new_value_t.clr_clk_enb_tvo };
    m_bit_details_model.bits.append(entry);
    entry = { "18: clr_clk_enb_mipi:1",
              "clear enable clock to MIPI base-band controller",
              1, old_value_t.clr_clk_enb_mipi, new_value_t.clr_clk_enb_mipi };
    m_bit_details_model.bits.append(entry);
    entry = { "19: clr_clk_enb_hdmi:1",
              "clear enable clock to HDMI",
              1, old_value_t.clr_clk_enb_hdmi, new_value_t.clr_clk_enb_hdmi };
    m_bit_details_model.bits.append(entry);
    entry = { "20: clr_clk_enb_csi:1",
              "clear enable clock to CSI controller",
              1, old_value_t.clr_clk_enb_csi, new_value_t.clr_clk_enb_csi };
    m_bit_details_model.bits.append(entry);
    entry = { "21: clr_clk_enb_tvdac:1",
              "clear enable clock to TVDAC controller",
              1, old_value_t.clr_clk_enb_tvdac, new_value_t.clr_clk_enb_tvdac };
    m_bit_details_model.bits.append(entry);
    entry = { "22: clr_clk_enb_i2c2:1",
              "clear enable clock to I2C2 controller",
              1, old_value_t.clr_clk_enb_i2c2, new_value_t.clr_clk_enb_i2c2 };
    m_bit_details_model.bits.append(entry);
    entry = { "23: clr_clk_enb_uart3:1",
              "clear enable clock to UART3 Controller",
              1, old_value_t.clr_clk_enb_uart3, new_value_t.clr_clk_enb_uart3 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: undefined_bit_24:1", "", 1, old_value_t.undefined_bit_24, new_value_t.undefined_bit_24 };
    m_bit_details_model.bits.append(entry);
    entry = { "25: clr_clk_enb_emc:1",
              "clear enable clock to EMC controller",
              1, old_value_t.clr_clk_enb_emc, new_value_t.clr_clk_enb_emc };
    m_bit_details_model.bits.append(entry);
    entry = { "26: clr_clk_enb_usb2:1",
              "clear enable clock to USB2 controller",
              1, old_value_t.clr_clk_enb_usb2, new_value_t.clr_clk_enb_usb2 };
    m_bit_details_model.bits.append(entry);
    entry = { "27: clr_clk_enb_usb3:1",
              "clear enable clock to USB3 controller",
              1, old_value_t.clr_clk_enb_usb3, new_value_t.clr_clk_enb_usb3 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: clr_clk_enb_mpe:1",
              "clear enable clock to MPE controller",
              1, old_value_t.clr_clk_enb_mpe, new_value_t.clr_clk_enb_mpe };
    m_bit_details_model.bits.append(entry);
    entry = { "29: clr_clk_enb_vde:1",
              "clear enable clock to VDE Controller",
              1, old_value_t.clr_clk_enb_vde, new_value_t.clr_clk_enb_vde };
    m_bit_details_model.bits.append(entry);
    entry = { "30: clr_clk_enb_bsea:1",
              "clear enable clock to BSEA Controller",
              1, old_value_t.clr_clk_enb_bsea, new_value_t.clr_clk_enb_bsea };
    m_bit_details_model.bits.append(entry);
    entry = { "31: clr_clk_enb_bsev:1",
              "clear enable clock to BSEV Controller",
              1, old_value_t.clr_clk_enb_bsev, new_value_t.clr_clk_enb_bsev };
    m_bit_details_model.bits.append(entry);
}

#define CLK_ENB_U_SET_OFFSET 0x330
#define CLK_ENB_U_SET_UNDEFMASK 0x880FE400
union clk_enb_u_set_u {
    struct {
        unsigned int set_clk_enb_speedo:1;  /* set enable clock to SPEEDO */
        unsigned int set_clk_enb_uart4:1;   /* set enable clock to UART4 */
        unsigned int set_clk_enb_uart5:1;   /* set enable clock to UART5 */
        unsigned int set_clk_enb_i2c3:1;    /* set enable clock to I2C3 */
        unsigned int set_clk_enb_sbc4:1;    /* set enable clock to SBC4 (SPI 4) */
        unsigned int set_clk_enb_sdmmc3:1;  /* set enable clock to SDMMC3 */
        unsigned int set_clk_enb_pcie:1;    /* set enable clock to PCIE */
        unsigned int set_clk_enb_owr:1;     /* set enable clock to OWR */
        unsigned int set_clk_enb_afi:1;     /* set enable clock to AFI */
        unsigned int set_clk_enb_csite:1;   /* set enable clock to CSITE */
        unsigned int undefined_bit_10:1;
        unsigned int set_clk_enb_avpucq:1;  /* set enable clock to AVPUCQ */
        unsigned int set_clk_enb_la:1;      /* set enable clock to LA. */
        unsigned int undefined_bits_13_19:7;
        unsigned int set_clk_enb_irama:1;   /* set enable IRAMB clk */
        unsigned int set_clk_enb_iramb:1;   /* set enable IRAMB clk */
        unsigned int set_clk_enb_iramc:1;   /* set enable IRAMC clk */
        unsigned int set_clk_enb_iramd:1;   /* set enable IRAMD clk */
        unsigned int set_clk_enb_cram2:1;   /* set enable COP cache ram clk */
        unsigned int set_sync_clk_doubler_enb:1;/* set enable audio sync clk doubler */
        unsigned int set_clk_m_doubler_enb:1;/* set enable CLK_M clk doubler */
        unsigned int undefined_bit_27:1;
        unsigned int set_clk_enb_sus_out:1; /* set enable clock to SUS pad */
        unsigned int set_clk_enb_dev2_out:1;/* set enable clock to DEV2 pad */
        unsigned int set_clk_enb_dev1_out:1;/* set enable clock to DEV1 pad */
        unsigned int undefined_bit_31:1;
    };

    u_int32_t reg32;
};

void CarDev::fill_clk_enb_u_set_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const clk_enb_u_set_u old_value_t = { .reg32 = value };
    const clk_enb_u_set_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: set_clk_enb_speedo:1",
              "set enable clock to SPEEDO",
              1, old_value_t.set_clk_enb_speedo, new_value_t.set_clk_enb_speedo };
    m_bit_details_model.bits.append(entry);
    entry = { "01: set_clk_enb_uart4:1",
              "set enable clock to UART4",
              1, old_value_t.set_clk_enb_uart4, new_value_t.set_clk_enb_uart4 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: set_clk_enb_uart5:1",
              "set enable clock to UART5",
              1, old_value_t.set_clk_enb_uart5, new_value_t.set_clk_enb_uart5 };
    m_bit_details_model.bits.append(entry);
    entry = { "03: set_clk_enb_i2c3:1",
              "set enable clock to I2C3",
              1, old_value_t.set_clk_enb_i2c3, new_value_t.set_clk_enb_i2c3 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: set_clk_enb_sbc4:1",
              "set enable clock to SBC4 (SPI 4)",
              1, old_value_t.set_clk_enb_sbc4, new_value_t.set_clk_enb_sbc4 };
    m_bit_details_model.bits.append(entry);
    entry = { "05: set_clk_enb_sdmmc3:1",
              "set enable clock to SDMMC3",
              1, old_value_t.set_clk_enb_sdmmc3, new_value_t.set_clk_enb_sdmmc3 };
    m_bit_details_model.bits.append(entry);
    entry = { "06: set_clk_enb_pcie:1",
              "set enable clock to PCIE",
              1, old_value_t.set_clk_enb_pcie, new_value_t.set_clk_enb_pcie };
    m_bit_details_model.bits.append(entry);
    entry = { "07: set_clk_enb_owr:1",
              "set enable clock to OWR",
              1, old_value_t.set_clk_enb_owr, new_value_t.set_clk_enb_owr };
    m_bit_details_model.bits.append(entry);
    entry = { "08: set_clk_enb_afi:1",
              "set enable clock to AFI",
              1, old_value_t.set_clk_enb_afi, new_value_t.set_clk_enb_afi };
    m_bit_details_model.bits.append(entry);
    entry = { "09: set_clk_enb_csite:1",
              "set enable clock to CSITE",
              1, old_value_t.set_clk_enb_csite, new_value_t.set_clk_enb_csite };
    m_bit_details_model.bits.append(entry);
    entry = { "10: undefined_bit_10:1", "", 1, old_value_t.undefined_bit_10, new_value_t.undefined_bit_10 };
    m_bit_details_model.bits.append(entry);
    entry = { "11: set_clk_enb_avpucq:1",
              "set enable clock to AVPUCQ",
              1, old_value_t.set_clk_enb_avpucq, new_value_t.set_clk_enb_avpucq };
    m_bit_details_model.bits.append(entry);
    entry = { "12: set_clk_enb_la:1",
              "set enable clock to LA.",
              1, old_value_t.set_clk_enb_la, new_value_t.set_clk_enb_la };
    m_bit_details_model.bits.append(entry);
    entry = { "13: undefined_bits_13_19:7", "", 7, old_value_t.undefined_bits_13_19, new_value_t.undefined_bits_13_19 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: set_clk_enb_irama:1",
              "set enable IRAMB clk",
              1, old_value_t.set_clk_enb_irama, new_value_t.set_clk_enb_irama };
    m_bit_details_model.bits.append(entry);
    entry = { "21: set_clk_enb_iramb:1",
              "set enable IRAMB clk",
              1, old_value_t.set_clk_enb_iramb, new_value_t.set_clk_enb_iramb };
    m_bit_details_model.bits.append(entry);
    entry = { "22: set_clk_enb_iramc:1",
              "set enable IRAMC clk",
              1, old_value_t.set_clk_enb_iramc, new_value_t.set_clk_enb_iramc };
    m_bit_details_model.bits.append(entry);
    entry = { "23: set_clk_enb_iramd:1",
              "set enable IRAMD clk",
              1, old_value_t.set_clk_enb_iramd, new_value_t.set_clk_enb_iramd };
    m_bit_details_model.bits.append(entry);
    entry = { "24: set_clk_enb_cram2:1",
              "set enable COP cache ram clk",
              1, old_value_t.set_clk_enb_cram2, new_value_t.set_clk_enb_cram2 };
    m_bit_details_model.bits.append(entry);
    entry = { "25: set_sync_clk_doubler_enb:1",
              "set enable audio sync clk doubler",
              1, old_value_t.set_sync_clk_doubler_enb, new_value_t.set_sync_clk_doubler_enb };
    m_bit_details_model.bits.append(entry);
    entry = { "26: set_clk_m_doubler_enb:1",
              "set enable CLK_M clk doubler",
              1, old_value_t.set_clk_m_doubler_enb, new_value_t.set_clk_m_doubler_enb };
    m_bit_details_model.bits.append(entry);
    entry = { "27: undefined_bit_27:1", "", 1, old_value_t.undefined_bit_27, new_value_t.undefined_bit_27 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: set_clk_enb_sus_out:1",
              "set enable clock to SUS pad",
              1, old_value_t.set_clk_enb_sus_out, new_value_t.set_clk_enb_sus_out };
    m_bit_details_model.bits.append(entry);
    entry = { "29: set_clk_enb_dev2_out:1",
              "set enable clock to DEV2 pad",
              1, old_value_t.set_clk_enb_dev2_out, new_value_t.set_clk_enb_dev2_out };
    m_bit_details_model.bits.append(entry);
    entry = { "30: set_clk_enb_dev1_out:1",
              "set enable clock to DEV1 pad",
              1, old_value_t.set_clk_enb_dev1_out, new_value_t.set_clk_enb_dev1_out };
    m_bit_details_model.bits.append(entry);
    entry = { "31: undefined_bit_31:1", "", 1, old_value_t.undefined_bit_31, new_value_t.undefined_bit_31 };
    m_bit_details_model.bits.append(entry);
}

#define CLK_ENB_U_CLR_OFFSET 0x334
#define CLK_ENB_U_CLR_UNDEFMASK 0x880FE400
union clk_enb_u_clr_u {
    struct {
        unsigned int clr_clk_enb_speedo:1;  /* clear enable clock to SPEEDO */
        unsigned int clr_clk_enb_uart4:1;   /* clear enable clock to UART4 */
        unsigned int clr_clk_enb_uart5:1;   /* clear enable clock to UART5 */
        unsigned int clr_clk_enb_i2c3:1;    /* clear enable clock to I2C3 */
        unsigned int clr_clk_enb_sbc4:1;    /* clear enable clock to SBC4 (SPI 4) */
        unsigned int clr_clk_enb_sdmmc3:1;  /* clear enable clock to SDMMC3 */
        unsigned int clr_clk_enb_pcie:1;    /* clear enable clock to PCIE */
        unsigned int clr_clk_enb_owr:1;     /* clear enable clock to OWR */
        unsigned int clr_clk_enb_afi:1;     /* clear enable clock to AFI */
        unsigned int clr_clk_enb_csite:1;   /* clear enable clock to CSITE */
        unsigned int undefined_bit_10:1;
        unsigned int clr_clk_enb_avpucq:1;  /* clear enable clock to AVPUCQ */
        unsigned int clr_clk_enb_la:1;      /* clear enable clock to LA. */
        unsigned int undefined_bits_13_19:7;
        unsigned int clr_clk_enb_irama:1;   /* clear enable IRAMB clk */
        unsigned int clr_clk_enb_iramb:1;   /* clear enable IRAMB clk */
        unsigned int clr_clk_enb_iramc:1;   /* clear enable IRAMC clk */
        unsigned int clr_clk_enb_iramd:1;   /* clear enable IRAMD clk */
        unsigned int clr_clk_enb_cram2:1;   /* clear enable COP cache ram clk */
        unsigned int clr_sync_clk_doubler_enb:1;/* clear enable audio sync clk doubler */
        unsigned int clr_clk_m_doubler_enb:1;/* clear enable CLK_M clk doubler */
        unsigned int undefined_bit_27:1;
        unsigned int clr_clk_enb_sus_out:1; /* clear enable clock to SUS pad */
        unsigned int clr_clk_enb_dev2_out:1;/* clear enable clock to DEV2 pad */
        unsigned int clr_clk_enb_dev1_out:1;/* clear enable clock to DEV1 pad */
        unsigned int undefined_bit_31:1;
    };

    u_int32_t reg32;
};

void CarDev::fill_clk_enb_u_clr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const clk_enb_u_clr_u old_value_t = { .reg32 = value };
    const clk_enb_u_clr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: clr_clk_enb_speedo:1",
              "clear enable clock to SPEEDO",
              1, old_value_t.clr_clk_enb_speedo, new_value_t.clr_clk_enb_speedo };
    m_bit_details_model.bits.append(entry);
    entry = { "01: clr_clk_enb_uart4:1",
              "clear enable clock to UART4",
              1, old_value_t.clr_clk_enb_uart4, new_value_t.clr_clk_enb_uart4 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: clr_clk_enb_uart5:1",
              "clear enable clock to UART5",
              1, old_value_t.clr_clk_enb_uart5, new_value_t.clr_clk_enb_uart5 };
    m_bit_details_model.bits.append(entry);
    entry = { "03: clr_clk_enb_i2c3:1",
              "clear enable clock to I2C3",
              1, old_value_t.clr_clk_enb_i2c3, new_value_t.clr_clk_enb_i2c3 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: clr_clk_enb_sbc4:1",
              "clear enable clock to SBC4 (SPI 4)",
              1, old_value_t.clr_clk_enb_sbc4, new_value_t.clr_clk_enb_sbc4 };
    m_bit_details_model.bits.append(entry);
    entry = { "05: clr_clk_enb_sdmmc3:1",
              "clear enable clock to SDMMC3",
              1, old_value_t.clr_clk_enb_sdmmc3, new_value_t.clr_clk_enb_sdmmc3 };
    m_bit_details_model.bits.append(entry);
    entry = { "06: clr_clk_enb_pcie:1",
              "clear enable clock to PCIE",
              1, old_value_t.clr_clk_enb_pcie, new_value_t.clr_clk_enb_pcie };
    m_bit_details_model.bits.append(entry);
    entry = { "07: clr_clk_enb_owr:1",
              "clear enable clock to OWR",
              1, old_value_t.clr_clk_enb_owr, new_value_t.clr_clk_enb_owr };
    m_bit_details_model.bits.append(entry);
    entry = { "08: clr_clk_enb_afi:1",
              "clear enable clock to AFI",
              1, old_value_t.clr_clk_enb_afi, new_value_t.clr_clk_enb_afi };
    m_bit_details_model.bits.append(entry);
    entry = { "09: clr_clk_enb_csite:1",
              "clear enable clock to CSITE",
              1, old_value_t.clr_clk_enb_csite, new_value_t.clr_clk_enb_csite };
    m_bit_details_model.bits.append(entry);
    entry = { "10: undefined_bit_10:1", "", 1, old_value_t.undefined_bit_10, new_value_t.undefined_bit_10 };
    m_bit_details_model.bits.append(entry);
    entry = { "11: clr_clk_enb_avpucq:1",
              "clear enable clock to AVPUCQ",
              1, old_value_t.clr_clk_enb_avpucq, new_value_t.clr_clk_enb_avpucq };
    m_bit_details_model.bits.append(entry);
    entry = { "12: clr_clk_enb_la:1",
              "clear enable clock to LA.",
              1, old_value_t.clr_clk_enb_la, new_value_t.clr_clk_enb_la };
    m_bit_details_model.bits.append(entry);
    entry = { "13: undefined_bits_13_19:7", "", 7, old_value_t.undefined_bits_13_19, new_value_t.undefined_bits_13_19 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: clr_clk_enb_irama:1",
              "clear enable IRAMB clk",
              1, old_value_t.clr_clk_enb_irama, new_value_t.clr_clk_enb_irama };
    m_bit_details_model.bits.append(entry);
    entry = { "21: clr_clk_enb_iramb:1",
              "clear enable IRAMB clk",
              1, old_value_t.clr_clk_enb_iramb, new_value_t.clr_clk_enb_iramb };
    m_bit_details_model.bits.append(entry);
    entry = { "22: clr_clk_enb_iramc:1",
              "clear enable IRAMC clk",
              1, old_value_t.clr_clk_enb_iramc, new_value_t.clr_clk_enb_iramc };
    m_bit_details_model.bits.append(entry);
    entry = { "23: clr_clk_enb_iramd:1",
              "clear enable IRAMD clk",
              1, old_value_t.clr_clk_enb_iramd, new_value_t.clr_clk_enb_iramd };
    m_bit_details_model.bits.append(entry);
    entry = { "24: clr_clk_enb_cram2:1",
              "clear enable COP cache ram clk",
              1, old_value_t.clr_clk_enb_cram2, new_value_t.clr_clk_enb_cram2 };
    m_bit_details_model.bits.append(entry);
    entry = { "25: clr_sync_clk_doubler_enb:1",
              "clear enable audio sync clk doubler",
              1, old_value_t.clr_sync_clk_doubler_enb, new_value_t.clr_sync_clk_doubler_enb };
    m_bit_details_model.bits.append(entry);
    entry = { "26: clr_clk_m_doubler_enb:1",
              "clear enable CLK_M clk doubler",
              1, old_value_t.clr_clk_m_doubler_enb, new_value_t.clr_clk_m_doubler_enb };
    m_bit_details_model.bits.append(entry);
    entry = { "27: undefined_bit_27:1", "", 1, old_value_t.undefined_bit_27, new_value_t.undefined_bit_27 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: clr_clk_enb_sus_out:1",
              "clear enable clock to SUS pad",
              1, old_value_t.clr_clk_enb_sus_out, new_value_t.clr_clk_enb_sus_out };
    m_bit_details_model.bits.append(entry);
    entry = { "29: clr_clk_enb_dev2_out:1",
              "clear enable clock to DEV2 pad",
              1, old_value_t.clr_clk_enb_dev2_out, new_value_t.clr_clk_enb_dev2_out };
    m_bit_details_model.bits.append(entry);
    entry = { "30: clr_clk_enb_dev1_out:1",
              "clear enable clock to DEV1 pad",
              1, old_value_t.clr_clk_enb_dev1_out, new_value_t.clr_clk_enb_dev1_out };
    m_bit_details_model.bits.append(entry);
    entry = { "31: undefined_bit_31:1", "", 1, old_value_t.undefined_bit_31, new_value_t.undefined_bit_31 };
    m_bit_details_model.bits.append(entry);
}

#define RST_CPU_CMPLX_SET_OFFSET 0x340
#define RST_CPU_CMPLX_SET_UNDEFMASK 0x8FFFCCCC
union rst_cpu_cmplx_set_u {
    struct {
        unsigned int set_cpureset0:1;       /* 1 = assert nCPURESET to CPU0 */
        unsigned int set_cpureset1:1;       /* 1 = assert nCPURESET to CPU1 */
        unsigned int undefined_bits_2_3:2;
        unsigned int set_dereset0:1;        /* 1 = assert nDERESET to CPU0 */
        unsigned int set_dereset1:1;        /* 1 = assert nDERESET to CPU1 */
        unsigned int undefined_bits_6_7:2;
        unsigned int set_wdreset0:1;        /* 1 = assert nWDRESET to CPU0 */
        unsigned int set_wdreset1:1;        /* 1 = assert nWDRESET to CPU1 */
        unsigned int undefined_bits_10_11:2;
        unsigned int set_dbgreset0:1;       /* 1 = assert nDBGRESET to CPU0 */
        unsigned int set_dbgreset1:1;       /* 1 = assert nDBGRESET to CPU1 */
        unsigned int undefined_bits_14_27:14;
        unsigned int set_periphreset:1;     /* 1 = assert nPERIPHRESET to the CPU */
        unsigned int set_scureset:1;        /* 1 = assert nSCURESET to the SCU */
        unsigned int set_presetdbg:1;       /* 1 = assert nPRESETDBG to the coresight */
        unsigned int undefined_bit_31:1;
    };

    u_int32_t reg32;
};

void CarDev::fill_rst_cpu_cmplx_set_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const rst_cpu_cmplx_set_u old_value_t = { .reg32 = value };
    const rst_cpu_cmplx_set_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: set_cpureset0:1",
              "1 = assert nCPURESET to CPU0",
              1, old_value_t.set_cpureset0, new_value_t.set_cpureset0 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: set_cpureset1:1",
              "1 = assert nCPURESET to CPU1",
              1, old_value_t.set_cpureset1, new_value_t.set_cpureset1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: undefined_bits_2_3:2", "", 2, old_value_t.undefined_bits_2_3, new_value_t.undefined_bits_2_3 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: set_dereset0:1",
              "1 = assert nDERESET to CPU0",
              1, old_value_t.set_dereset0, new_value_t.set_dereset0 };
    m_bit_details_model.bits.append(entry);
    entry = { "05: set_dereset1:1",
              "1 = assert nDERESET to CPU1",
              1, old_value_t.set_dereset1, new_value_t.set_dereset1 };
    m_bit_details_model.bits.append(entry);
    entry = { "06: undefined_bits_6_7:2", "", 2, old_value_t.undefined_bits_6_7, new_value_t.undefined_bits_6_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: set_wdreset0:1",
              "1 = assert nWDRESET to CPU0",
              1, old_value_t.set_wdreset0, new_value_t.set_wdreset0 };
    m_bit_details_model.bits.append(entry);
    entry = { "09: set_wdreset1:1",
              "1 = assert nWDRESET to CPU1",
              1, old_value_t.set_wdreset1, new_value_t.set_wdreset1 };
    m_bit_details_model.bits.append(entry);
    entry = { "10: undefined_bits_10_11:2", "", 2, old_value_t.undefined_bits_10_11, new_value_t.undefined_bits_10_11 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: set_dbgreset0:1",
              "1 = assert nDBGRESET to CPU0",
              1, old_value_t.set_dbgreset0, new_value_t.set_dbgreset0 };
    m_bit_details_model.bits.append(entry);
    entry = { "13: set_dbgreset1:1",
              "1 = assert nDBGRESET to CPU1",
              1, old_value_t.set_dbgreset1, new_value_t.set_dbgreset1 };
    m_bit_details_model.bits.append(entry);
    entry = { "14: undefined_bits_14_27:14", "", 14, old_value_t.undefined_bits_14_27, new_value_t.undefined_bits_14_27 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: set_periphreset:1",
              "1 = assert nPERIPHRESET to the CPU",
              1, old_value_t.set_periphreset, new_value_t.set_periphreset };
    m_bit_details_model.bits.append(entry);
    entry = { "29: set_scureset:1",
              "1 = assert nSCURESET to the SCU",
              1, old_value_t.set_scureset, new_value_t.set_scureset };
    m_bit_details_model.bits.append(entry);
    entry = { "30: set_presetdbg:1",
              "1 = assert nPRESETDBG to the coresight",
              1, old_value_t.set_presetdbg, new_value_t.set_presetdbg };
    m_bit_details_model.bits.append(entry);
    entry = { "31: undefined_bit_31:1", "", 1, old_value_t.undefined_bit_31, new_value_t.undefined_bit_31 };
    m_bit_details_model.bits.append(entry);
}

#define RST_CPU_CMPLX_CLR_OFFSET 0x344
#define RST_CPU_CMPLX_CLR_UNDEFMASK 0x8FFFCCCC
union rst_cpu_cmplx_clr_u {
    struct {
        unsigned int clr_cpureset0:1;       /* 1 = deassert nCPURESET to CPU0 */
        unsigned int clr_cpureset1:1;       /* 1 = deassert nCPURESET to CPU1 */
        unsigned int undefined_bits_2_3:2;
        unsigned int clr_dereset0:1;        /* 1 = deassert nDERESET to CPU0 */
        unsigned int clr_dereset1:1;        /* 1 = deassert nDERESET to CPU1 */
        unsigned int undefined_bits_6_7:2;
        unsigned int clr_wdreset0:1;        /* 1 = deassert nWDRESET to CPU0 */
        unsigned int clr_wdreset1:1;        /* 1 = deassert nWDRESET to CPU1 */
        unsigned int undefined_bits_10_11:2;
        unsigned int clr_dbgreset0:1;       /* 1 = deassert nDBGRESET to CPU0 */
        unsigned int clr_dbgreset1:1;       /* 1 = deassert nDBGRESET to CPU1 */
        unsigned int undefined_bits_14_27:14;
        unsigned int clr_periphreset:1;     /* 1 = deassert nPERIPHRESET to the CPU's interrupt/timer */
        unsigned int clr_scureset:1;        /* 1 = deassert nSCURESET to the SCU */
        unsigned int clr_presetdbg:1;       /* 1 = deassert nPRESETDBG to the coresight */
        unsigned int undefined_bit_31:1;
    };

    u_int32_t reg32;
};

void CarDev::fill_rst_cpu_cmplx_clr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const rst_cpu_cmplx_clr_u old_value_t = { .reg32 = value };
    const rst_cpu_cmplx_clr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: clr_cpureset0:1",
              "1 = deassert nCPURESET to CPU0",
              1, old_value_t.clr_cpureset0, new_value_t.clr_cpureset0 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: clr_cpureset1:1",
              "1 = deassert nCPURESET to CPU1",
              1, old_value_t.clr_cpureset1, new_value_t.clr_cpureset1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: undefined_bits_2_3:2", "", 2, old_value_t.undefined_bits_2_3, new_value_t.undefined_bits_2_3 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: clr_dereset0:1",
              "1 = deassert nDERESET to CPU0",
              1, old_value_t.clr_dereset0, new_value_t.clr_dereset0 };
    m_bit_details_model.bits.append(entry);
    entry = { "05: clr_dereset1:1",
              "1 = deassert nDERESET to CPU1",
              1, old_value_t.clr_dereset1, new_value_t.clr_dereset1 };
    m_bit_details_model.bits.append(entry);
    entry = { "06: undefined_bits_6_7:2", "", 2, old_value_t.undefined_bits_6_7, new_value_t.undefined_bits_6_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: clr_wdreset0:1",
              "1 = deassert nWDRESET to CPU0",
              1, old_value_t.clr_wdreset0, new_value_t.clr_wdreset0 };
    m_bit_details_model.bits.append(entry);
    entry = { "09: clr_wdreset1:1",
              "1 = deassert nWDRESET to CPU1",
              1, old_value_t.clr_wdreset1, new_value_t.clr_wdreset1 };
    m_bit_details_model.bits.append(entry);
    entry = { "10: undefined_bits_10_11:2", "", 2, old_value_t.undefined_bits_10_11, new_value_t.undefined_bits_10_11 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: clr_dbgreset0:1",
              "1 = deassert nDBGRESET to CPU0",
              1, old_value_t.clr_dbgreset0, new_value_t.clr_dbgreset0 };
    m_bit_details_model.bits.append(entry);
    entry = { "13: clr_dbgreset1:1",
              "1 = deassert nDBGRESET to CPU1",
              1, old_value_t.clr_dbgreset1, new_value_t.clr_dbgreset1 };
    m_bit_details_model.bits.append(entry);
    entry = { "14: undefined_bits_14_27:14", "", 14, old_value_t.undefined_bits_14_27, new_value_t.undefined_bits_14_27 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: clr_periphreset:1",
              "1 = deassert nPERIPHRESET to the CPU's interrupt/timer",
              1, old_value_t.clr_periphreset, new_value_t.clr_periphreset };
    m_bit_details_model.bits.append(entry);
    entry = { "29: clr_scureset:1",
              "1 = deassert nSCURESET to the SCU",
              1, old_value_t.clr_scureset, new_value_t.clr_scureset };
    m_bit_details_model.bits.append(entry);
    entry = { "30: clr_presetdbg:1",
              "1 = deassert nPRESETDBG to the coresight",
              1, old_value_t.clr_presetdbg, new_value_t.clr_presetdbg };
    m_bit_details_model.bits.append(entry);
    entry = { "31: undefined_bit_31:1", "", 1, old_value_t.undefined_bit_31, new_value_t.undefined_bit_31 };
    m_bit_details_model.bits.append(entry);
}

#define CLK_SOURCE_LA_OFFSET 0x1F8
#define CLK_SOURCE_LA_UNDEFMASK 0x3FFFFF00
union clk_source_la_u {
    struct {
        unsigned int la_clk_divisor:8;      /*  N = Divide by (n+1) (lsb denote 0.5x) */
        unsigned int undefined_bits_8_29:22;
        unsigned int la_clk_src:2;          /*  00 = pllP_out0  01 = pllC_out0  10 = pllM_out0  11 = clk_m */
    };

    u_int32_t reg32;
};

void CarDev::fill_clk_source_la_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const clk_source_la_u old_value_t = { .reg32 = value };
    const clk_source_la_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: la_clk_divisor:8",
              " N = Divide by (n+1) (lsb denote 0.5x)",
              8, old_value_t.la_clk_divisor, new_value_t.la_clk_divisor };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_29:22", "", 22, old_value_t.undefined_bits_8_29, new_value_t.undefined_bits_8_29 };
    m_bit_details_model.bits.append(entry);
    entry = { "30: la_clk_src:2",
              "00 = pllP_out0 \n01 = pllC_out0 \n10 = pllM_out0 \n11 = clk_m",
              2, old_value_t.la_clk_src, new_value_t.la_clk_src };
    m_bit_details_model.bits.append(entry);
}

bool CarDev::is_offset_valid(const u_int32_t &offset) const
{
    switch (offset) {
    case RST_SOURCE_OFFSET:
    case RST_DEVICES_L_OFFSET:
    case RST_DEVICES_H_OFFSET:
    case RST_DEVICES_U_OFFSET:
    case CLK_OUT_ENB_L_OFFSET:
    case CLK_OUT_ENB_H_OFFSET:
    case CLK_OUT_ENB_U_OFFSET:
    case CCLK_BURST_POLICY_OFFSET:
    case SUPER_CCLK_DIVIDER_OFFSET:
    case SCLK_BURST_POLICY_OFFSET:
    case SUPER_SCLK_DIVIDER_OFFSET:
    case CLK_SYSTEM_RATE_OFFSET:
    case PROG_DLY_CLK_OFFSET:
    case AUDIO_SYNC_CLK_RATE_OFFSET:
    case COP_CLK_SKIP_POLICY_OFFSET:
    case CLK_MASK_ARM_OFFSET:
    case MISC_CLK_ENB_OFFSET:
    case CLK_CPU_CMPLX_OFFSET:
    case OSC_CTRL_OFFSET:
    case PLL_LFSR_OFFSET:
    case OSC_FREQ_DET_OFFSET:
    case OSC_FREQ_DET_STATUS_OFFSET:
    case PLLC_BASE_OFFSET:
    case PLLC_OUT_OFFSET:
    case PLLC_MISC_OFFSET:
    case PLLM_BASE_OFFSET:
    case PLLM_OUT_OFFSET:
    case PLLM_MISC_OFFSET:
    case PLLP_BASE_OFFSET:
    case PLLP_OUTA_OFFSET:
    case PLLP_OUTB_OFFSET:
    case PLLP_MISC_OFFSET:
    case PLLA_BASE_OFFSET:
    case PLLA_OUT_OFFSET:
    case PLLA_MISC_OFFSET:
    case PLLU_BASE_OFFSET:
    case PLLU_MISC_OFFSET:
    case PLLD_BASE_OFFSET:
    case PLLD_MISC_OFFSET:
    case PLLX_BASE_OFFSET:
    case PLLX_MISC_OFFSET:
    case PLLE_BASE_OFFSET:
    case PLLE_MISC_OFFSET:
    case CLK_SOURCE_I2S1_OFFSET:
    case CLK_SOURCE_I2S2_OFFSET:
    case CLK_SOURCE_SPDIF_OUT_OFFSET:
    case CLK_SOURCE_SPDIF_IN_OFFSET:
    case CLK_SOURCE_PWM_OFFSET:
    case CLK_SOURCE_SPI1_OFFSET:
    case CLK_SOURCE_SPI22_OFFSET:
    case CLK_SOURCE_SPI3_OFFSET:
    case CLK_SOURCE_XIO_OFFSET:
    case CLK_SOURCE_I2C1_OFFSET:
    case CLK_SOURCE_DVC_I2C_OFFSET:
    case CLK_SOURCE_TWC_OFFSET:
    case CLK_SOURCE_SBC1_OFFSET:
    case CLK_SOURCE_DISP1_OFFSET:
    case CLK_SOURCE_DISP2_OFFSET:
    case CLK_SOURCE_CVE_OFFSET:
    case CLK_SOURCE_IDE_OFFSET:
    case CLK_SOURCE_VI_OFFSET:
    case CLK_SOURCE_SDMMC1_OFFSET:
    case CLK_SOURCE_SDMMC2_OFFSET:
    case CLK_SOURCE_G3D_OFFSET:
    case CLK_SOURCE_G2D_OFFSET:
    case CLK_SOURCE_NDFLASH_OFFSET:
    case CLK_SOURCE_SDMMC4_OFFSET:
    case CLK_SOURCE_VFIR_OFFSET:
    case CLK_SOURCE_EPP_OFFSET:
    case CLK_SOURCE_MPE_OFFSET:
    case CLK_SOURCE_MIPI_OFFSET:
    case CLK_SOURCE_UART1_OFFSET:
    case CLK_SOURCE_UART2_OFFSET:
    case CLK_SOURCE_HOST1X_OFFSET:
    case CLK_SOURCE_TVO_OFFSET:
    case CLK_SOURCE_HDMI_OFFSET:
    case CLK_SOURCE_TVDAC_OFFSET:
    case CLK_SOURCE_I2C2_OFFSET:
    case CLK_SOURCE_EMC_OFFSET:
    case CLK_SOURCE_UART3_OFFSET:
    case CLK_SOURCE_VI_SENSOR_OFFSET:
    case CLK_SOURCE_SPI4_OFFSET:
    case CLK_SOURCE_I2C3_OFFSET:
    case CLK_SOURCE_SDMMC3_OFFSET:
    case CLK_SOURCE_UART4_OFFSET:
    case CLK_SOURCE_UART5_OFFSET:
    case CLK_SOURCE_VDE_OFFSET:
    case CLK_SOURCE_OWR_OFFSET:
    case CLK_SOURCE_NOR_OFFSET:
    case CLK_SOURCE_CSITE_OFFSET:
    case CLK_SOURCE_OSC_OFFSET:
    case RST_DEV_L_SET_OFFSET:
    case RST_DEV_L_CLR_OFFSET:
    case RST_DEV_H_SET_OFFSET:
    case RST_DEV_H_CLR_OFFSET:
    case RST_DEV_U_SET_OFFSET:
    case RST_DEV_U_CLR_OFFSET:
    case CLK_ENB_L_SET_OFFSET:
    case CLK_ENB_L_CLR_OFFSET:
    case CLK_ENB_H_SET_OFFSET:
    case CLK_ENB_H_CLR_OFFSET:
    case CLK_ENB_U_SET_OFFSET:
    case CLK_ENB_U_CLR_OFFSET:
    case RST_CPU_CMPLX_SET_OFFSET:
    case RST_CPU_CMPLX_CLR_OFFSET:
    case CLK_SOURCE_LA_OFFSET:
        return true;
    default:
        break;
    }

    return false;
}

bool CarDev::is_undef_changed(const u_int32_t &offset,
                                           const u_int32_t &value,
                                           const u_int32_t &new_value) const
{
    switch (offset) {
    case RST_SOURCE_OFFSET:
        if ((value ^ new_value) & RST_SOURCE_UNDEFMASK)
            return true;
        break;
    case RST_DEVICES_L_OFFSET:
        if ((value ^ new_value) & RST_DEVICES_L_UNDEFMASK)
            return true;
        break;
    case RST_DEVICES_H_OFFSET:
        if ((value ^ new_value) & RST_DEVICES_H_UNDEFMASK)
            return true;
        break;
    case RST_DEVICES_U_OFFSET:
        if ((value ^ new_value) & RST_DEVICES_U_UNDEFMASK)
            return true;
        break;
    case CLK_OUT_ENB_L_OFFSET:
        if ((value ^ new_value) & CLK_OUT_ENB_L_UNDEFMASK)
            return true;
        break;
    case CLK_OUT_ENB_H_OFFSET:
        if ((value ^ new_value) & CLK_OUT_ENB_H_UNDEFMASK)
            return true;
        break;
    case CLK_OUT_ENB_U_OFFSET:
        if ((value ^ new_value) & CLK_OUT_ENB_U_UNDEFMASK)
            return true;
        break;
    case CCLK_BURST_POLICY_OFFSET:
        if ((value ^ new_value) & CCLK_BURST_POLICY_UNDEFMASK)
            return true;
        break;
    case SUPER_CCLK_DIVIDER_OFFSET:
        if ((value ^ new_value) & SUPER_CCLK_DIVIDER_UNDEFMASK)
            return true;
        break;
    case SCLK_BURST_POLICY_OFFSET:
        if ((value ^ new_value) & SCLK_BURST_POLICY_UNDEFMASK)
            return true;
        break;
    case SUPER_SCLK_DIVIDER_OFFSET:
        if ((value ^ new_value) & SUPER_SCLK_DIVIDER_UNDEFMASK)
            return true;
        break;
    case CLK_SYSTEM_RATE_OFFSET:
        if ((value ^ new_value) & CLK_SYSTEM_RATE_UNDEFMASK)
            return true;
        break;
    case PROG_DLY_CLK_OFFSET:
        if ((value ^ new_value) & PROG_DLY_CLK_UNDEFMASK)
            return true;
        break;
    case AUDIO_SYNC_CLK_RATE_OFFSET:
        if ((value ^ new_value) & AUDIO_SYNC_CLK_RATE_UNDEFMASK)
            return true;
        break;
    case COP_CLK_SKIP_POLICY_OFFSET:
        if ((value ^ new_value) & COP_CLK_SKIP_POLICY_UNDEFMASK)
            return true;
        break;
    case CLK_MASK_ARM_OFFSET:
        if ((value ^ new_value) & CLK_MASK_ARM_UNDEFMASK)
            return true;
        break;
    case MISC_CLK_ENB_OFFSET:
        if ((value ^ new_value) & MISC_CLK_ENB_UNDEFMASK)
            return true;
        break;
    case CLK_CPU_CMPLX_OFFSET:
        if ((value ^ new_value) & CLK_CPU_CMPLX_UNDEFMASK)
            return true;
        break;
    case OSC_CTRL_OFFSET:
        if ((value ^ new_value) & OSC_CTRL_UNDEFMASK)
            return true;
        break;
    case PLL_LFSR_OFFSET:
        if ((value ^ new_value) & PLL_LFSR_UNDEFMASK)
            return true;
        break;
    case OSC_FREQ_DET_OFFSET:
        if ((value ^ new_value) & OSC_FREQ_DET_UNDEFMASK)
            return true;
        break;
    case OSC_FREQ_DET_STATUS_OFFSET:
        if ((value ^ new_value) & OSC_FREQ_DET_STATUS_UNDEFMASK)
            return true;
        break;
    case PLLC_BASE_OFFSET:
        if ((value ^ new_value) & PLLC_BASE_UNDEFMASK)
            return true;
        break;
    case PLLC_OUT_OFFSET:
        if ((value ^ new_value) & PLLC_OUT_UNDEFMASK)
            return true;
        break;
    case PLLC_MISC_OFFSET:
        if ((value ^ new_value) & PLLC_MISC_UNDEFMASK)
            return true;
        break;
    case PLLM_BASE_OFFSET:
        if ((value ^ new_value) & PLLM_BASE_UNDEFMASK)
            return true;
        break;
    case PLLM_OUT_OFFSET:
        if ((value ^ new_value) & PLLM_OUT_UNDEFMASK)
            return true;
        break;
    case PLLM_MISC_OFFSET:
        if ((value ^ new_value) & PLLM_MISC_UNDEFMASK)
            return true;
        break;
    case PLLP_BASE_OFFSET:
        if ((value ^ new_value) & PLLP_BASE_UNDEFMASK)
            return true;
        break;
    case PLLP_OUTA_OFFSET:
        if ((value ^ new_value) & PLLP_OUTA_UNDEFMASK)
            return true;
        break;
    case PLLP_OUTB_OFFSET:
        if ((value ^ new_value) & PLLP_OUTB_UNDEFMASK)
            return true;
        break;
    case PLLP_MISC_OFFSET:
        if ((value ^ new_value) & PLLP_MISC_UNDEFMASK)
            return true;
        break;
    case PLLA_BASE_OFFSET:
        if ((value ^ new_value) & PLLA_BASE_UNDEFMASK)
            return true;
        break;
    case PLLA_OUT_OFFSET:
        if ((value ^ new_value) & PLLA_OUT_UNDEFMASK)
            return true;
        break;
    case PLLA_MISC_OFFSET:
        if ((value ^ new_value) & PLLA_MISC_UNDEFMASK)
            return true;
        break;
    case PLLU_BASE_OFFSET:
        if ((value ^ new_value) & PLLU_BASE_UNDEFMASK)
            return true;
        break;
    case PLLU_MISC_OFFSET:
        if ((value ^ new_value) & PLLU_MISC_UNDEFMASK)
            return true;
        break;
    case PLLD_BASE_OFFSET:
        if ((value ^ new_value) & PLLD_BASE_UNDEFMASK)
            return true;
        break;
    case PLLD_MISC_OFFSET:
        if ((value ^ new_value) & PLLD_MISC_UNDEFMASK)
            return true;
        break;
    case PLLX_BASE_OFFSET:
        if ((value ^ new_value) & PLLX_BASE_UNDEFMASK)
            return true;
        break;
    case PLLX_MISC_OFFSET:
        if ((value ^ new_value) & PLLX_MISC_UNDEFMASK)
            return true;
        break;
    case PLLE_BASE_OFFSET:
        if ((value ^ new_value) & PLLE_BASE_UNDEFMASK)
            return true;
        break;
    case PLLE_MISC_OFFSET:
        if ((value ^ new_value) & PLLE_MISC_UNDEFMASK)
            return true;
        break;
    case CLK_SOURCE_I2S1_OFFSET:
        if ((value ^ new_value) & CLK_SOURCE_I2S1_UNDEFMASK)
            return true;
        break;
    case CLK_SOURCE_I2S2_OFFSET:
        if ((value ^ new_value) & CLK_SOURCE_I2S2_UNDEFMASK)
            return true;
        break;
    case CLK_SOURCE_SPDIF_OUT_OFFSET:
        if ((value ^ new_value) & CLK_SOURCE_SPDIF_OUT_UNDEFMASK)
            return true;
        break;
    case CLK_SOURCE_SPDIF_IN_OFFSET:
        if ((value ^ new_value) & CLK_SOURCE_SPDIF_IN_UNDEFMASK)
            return true;
        break;
    case CLK_SOURCE_PWM_OFFSET:
        if ((value ^ new_value) & CLK_SOURCE_PWM_UNDEFMASK)
            return true;
        break;
    case CLK_SOURCE_SPI1_OFFSET:
        if ((value ^ new_value) & CLK_SOURCE_SPI1_UNDEFMASK)
            return true;
        break;
    case CLK_SOURCE_SPI22_OFFSET:
        if ((value ^ new_value) & CLK_SOURCE_SPI22_UNDEFMASK)
            return true;
        break;
    case CLK_SOURCE_SPI3_OFFSET:
        if ((value ^ new_value) & CLK_SOURCE_SPI3_UNDEFMASK)
            return true;
        break;
    case CLK_SOURCE_XIO_OFFSET:
        if ((value ^ new_value) & CLK_SOURCE_XIO_UNDEFMASK)
            return true;
        break;
    case CLK_SOURCE_I2C1_OFFSET:
        if ((value ^ new_value) & CLK_SOURCE_I2C1_UNDEFMASK)
            return true;
        break;
    case CLK_SOURCE_DVC_I2C_OFFSET:
        if ((value ^ new_value) & CLK_SOURCE_DVC_I2C_UNDEFMASK)
            return true;
        break;
    case CLK_SOURCE_TWC_OFFSET:
        if ((value ^ new_value) & CLK_SOURCE_TWC_UNDEFMASK)
            return true;
        break;
    case CLK_SOURCE_SBC1_OFFSET:
        if ((value ^ new_value) & CLK_SOURCE_SBC1_UNDEFMASK)
            return true;
        break;
    case CLK_SOURCE_DISP1_OFFSET:
        if ((value ^ new_value) & CLK_SOURCE_DISP1_UNDEFMASK)
            return true;
        break;
    case CLK_SOURCE_DISP2_OFFSET:
        if ((value ^ new_value) & CLK_SOURCE_DISP2_UNDEFMASK)
            return true;
        break;
    case CLK_SOURCE_CVE_OFFSET:
        if ((value ^ new_value) & CLK_SOURCE_CVE_UNDEFMASK)
            return true;
        break;
    case CLK_SOURCE_IDE_OFFSET:
        if ((value ^ new_value) & CLK_SOURCE_IDE_UNDEFMASK)
            return true;
        break;
    case CLK_SOURCE_VI_OFFSET:
        if ((value ^ new_value) & CLK_SOURCE_VI_UNDEFMASK)
            return true;
        break;
    case CLK_SOURCE_SDMMC1_OFFSET:
        if ((value ^ new_value) & CLK_SOURCE_SDMMC1_UNDEFMASK)
            return true;
        break;
    case CLK_SOURCE_SDMMC2_OFFSET:
        if ((value ^ new_value) & CLK_SOURCE_SDMMC2_UNDEFMASK)
            return true;
        break;
    case CLK_SOURCE_G3D_OFFSET:
        if ((value ^ new_value) & CLK_SOURCE_G3D_UNDEFMASK)
            return true;
        break;
    case CLK_SOURCE_G2D_OFFSET:
        if ((value ^ new_value) & CLK_SOURCE_G2D_UNDEFMASK)
            return true;
        break;
    case CLK_SOURCE_NDFLASH_OFFSET:
        if ((value ^ new_value) & CLK_SOURCE_NDFLASH_UNDEFMASK)
            return true;
        break;
    case CLK_SOURCE_SDMMC4_OFFSET:
        if ((value ^ new_value) & CLK_SOURCE_SDMMC4_UNDEFMASK)
            return true;
        break;
    case CLK_SOURCE_VFIR_OFFSET:
        if ((value ^ new_value) & CLK_SOURCE_VFIR_UNDEFMASK)
            return true;
        break;
    case CLK_SOURCE_EPP_OFFSET:
        if ((value ^ new_value) & CLK_SOURCE_EPP_UNDEFMASK)
            return true;
        break;
    case CLK_SOURCE_MPE_OFFSET:
        if ((value ^ new_value) & CLK_SOURCE_MPE_UNDEFMASK)
            return true;
        break;
    case CLK_SOURCE_MIPI_OFFSET:
        if ((value ^ new_value) & CLK_SOURCE_MIPI_UNDEFMASK)
            return true;
        break;
    case CLK_SOURCE_UART1_OFFSET:
        if ((value ^ new_value) & CLK_SOURCE_UART1_UNDEFMASK)
            return true;
        break;
    case CLK_SOURCE_UART2_OFFSET:
        if ((value ^ new_value) & CLK_SOURCE_UART2_UNDEFMASK)
            return true;
        break;
    case CLK_SOURCE_HOST1X_OFFSET:
        if ((value ^ new_value) & CLK_SOURCE_HOST1X_UNDEFMASK)
            return true;
        break;
    case CLK_SOURCE_TVO_OFFSET:
        if ((value ^ new_value) & CLK_SOURCE_TVO_UNDEFMASK)
            return true;
        break;
    case CLK_SOURCE_HDMI_OFFSET:
        if ((value ^ new_value) & CLK_SOURCE_HDMI_UNDEFMASK)
            return true;
        break;
    case CLK_SOURCE_TVDAC_OFFSET:
        if ((value ^ new_value) & CLK_SOURCE_TVDAC_UNDEFMASK)
            return true;
        break;
    case CLK_SOURCE_I2C2_OFFSET:
        if ((value ^ new_value) & CLK_SOURCE_I2C2_UNDEFMASK)
            return true;
        break;
    case CLK_SOURCE_EMC_OFFSET:
        if ((value ^ new_value) & CLK_SOURCE_EMC_UNDEFMASK)
            return true;
        break;
    case CLK_SOURCE_UART3_OFFSET:
        if ((value ^ new_value) & CLK_SOURCE_UART3_UNDEFMASK)
            return true;
        break;
    case CLK_SOURCE_VI_SENSOR_OFFSET:
        if ((value ^ new_value) & CLK_SOURCE_VI_SENSOR_UNDEFMASK)
            return true;
        break;
    case CLK_SOURCE_SPI4_OFFSET:
        if ((value ^ new_value) & CLK_SOURCE_SPI4_UNDEFMASK)
            return true;
        break;
    case CLK_SOURCE_I2C3_OFFSET:
        if ((value ^ new_value) & CLK_SOURCE_I2C3_UNDEFMASK)
            return true;
        break;
    case CLK_SOURCE_SDMMC3_OFFSET:
        if ((value ^ new_value) & CLK_SOURCE_SDMMC3_UNDEFMASK)
            return true;
        break;
    case CLK_SOURCE_UART4_OFFSET:
        if ((value ^ new_value) & CLK_SOURCE_UART4_UNDEFMASK)
            return true;
        break;
    case CLK_SOURCE_UART5_OFFSET:
        if ((value ^ new_value) & CLK_SOURCE_UART5_UNDEFMASK)
            return true;
        break;
    case CLK_SOURCE_VDE_OFFSET:
        if ((value ^ new_value) & CLK_SOURCE_VDE_UNDEFMASK)
            return true;
        break;
    case CLK_SOURCE_OWR_OFFSET:
        if ((value ^ new_value) & CLK_SOURCE_OWR_UNDEFMASK)
            return true;
        break;
    case CLK_SOURCE_NOR_OFFSET:
        if ((value ^ new_value) & CLK_SOURCE_NOR_UNDEFMASK)
            return true;
        break;
    case CLK_SOURCE_CSITE_OFFSET:
        if ((value ^ new_value) & CLK_SOURCE_CSITE_UNDEFMASK)
            return true;
        break;
    case CLK_SOURCE_OSC_OFFSET:
        if ((value ^ new_value) & CLK_SOURCE_OSC_UNDEFMASK)
            return true;
        break;
    case RST_DEV_L_SET_OFFSET:
        if ((value ^ new_value) & RST_DEV_L_SET_UNDEFMASK)
            return true;
        break;
    case RST_DEV_L_CLR_OFFSET:
        if ((value ^ new_value) & RST_DEV_L_CLR_UNDEFMASK)
            return true;
        break;
    case RST_DEV_H_SET_OFFSET:
        if ((value ^ new_value) & RST_DEV_H_SET_UNDEFMASK)
            return true;
        break;
    case RST_DEV_H_CLR_OFFSET:
        if ((value ^ new_value) & RST_DEV_H_CLR_UNDEFMASK)
            return true;
        break;
    case RST_DEV_U_SET_OFFSET:
        if ((value ^ new_value) & RST_DEV_U_SET_UNDEFMASK)
            return true;
        break;
    case RST_DEV_U_CLR_OFFSET:
        if ((value ^ new_value) & RST_DEV_U_CLR_UNDEFMASK)
            return true;
        break;
    case CLK_ENB_L_SET_OFFSET:
        if ((value ^ new_value) & CLK_ENB_L_SET_UNDEFMASK)
            return true;
        break;
    case CLK_ENB_L_CLR_OFFSET:
        if ((value ^ new_value) & CLK_ENB_L_CLR_UNDEFMASK)
            return true;
        break;
    case CLK_ENB_H_SET_OFFSET:
        if ((value ^ new_value) & CLK_ENB_H_SET_UNDEFMASK)
            return true;
        break;
    case CLK_ENB_H_CLR_OFFSET:
        if ((value ^ new_value) & CLK_ENB_H_CLR_UNDEFMASK)
            return true;
        break;
    case CLK_ENB_U_SET_OFFSET:
        if ((value ^ new_value) & CLK_ENB_U_SET_UNDEFMASK)
            return true;
        break;
    case CLK_ENB_U_CLR_OFFSET:
        if ((value ^ new_value) & CLK_ENB_U_CLR_UNDEFMASK)
            return true;
        break;
    case RST_CPU_CMPLX_SET_OFFSET:
        if ((value ^ new_value) & RST_CPU_CMPLX_SET_UNDEFMASK)
            return true;
        break;
    case RST_CPU_CMPLX_CLR_OFFSET:
        if ((value ^ new_value) & RST_CPU_CMPLX_CLR_UNDEFMASK)
            return true;
        break;
    case CLK_SOURCE_LA_OFFSET:
        if ((value ^ new_value) & CLK_SOURCE_LA_UNDEFMASK)
            return true;
        break;

    default:
        break;
    }

    return false;
}

QString CarDev::get_register_name(const log_entry &entry) const
{
    switch (entry.offset) {
    case RST_SOURCE_OFFSET:
        return QString("RST_SOURCE");
    case RST_DEVICES_L_OFFSET:
        return QString("RST_DEVICES_L");
    case RST_DEVICES_H_OFFSET:
        return QString("RST_DEVICES_H");
    case RST_DEVICES_U_OFFSET:
        return QString("RST_DEVICES_U");
    case CLK_OUT_ENB_L_OFFSET:
        return QString("CLK_OUT_ENB_L");
    case CLK_OUT_ENB_H_OFFSET:
        return QString("CLK_OUT_ENB_H");
    case CLK_OUT_ENB_U_OFFSET:
        return QString("CLK_OUT_ENB_U");
    case CCLK_BURST_POLICY_OFFSET:
        return QString("CCLK_BURST_POLICY");
    case SUPER_CCLK_DIVIDER_OFFSET:
        return QString("SUPER_CCLK_DIVIDER");
    case SCLK_BURST_POLICY_OFFSET:
        return QString("SCLK_BURST_POLICY");
    case SUPER_SCLK_DIVIDER_OFFSET:
        return QString("SUPER_SCLK_DIVIDER");
    case CLK_SYSTEM_RATE_OFFSET:
        return QString("CLK_SYSTEM_RATE");
    case PROG_DLY_CLK_OFFSET:
        return QString("PROG_DLY_CLK");
    case AUDIO_SYNC_CLK_RATE_OFFSET:
        return QString("AUDIO_SYNC_CLK_RATE");
    case COP_CLK_SKIP_POLICY_OFFSET:
        return QString("COP_CLK_SKIP_POLICY");
    case CLK_MASK_ARM_OFFSET:
        return QString("CLK_MASK_ARM");
    case MISC_CLK_ENB_OFFSET:
        return QString("MISC_CLK_ENB");
    case CLK_CPU_CMPLX_OFFSET:
        return QString("CLK_CPU_CMPLX");
    case OSC_CTRL_OFFSET:
        return QString("OSC_CTRL");
    case PLL_LFSR_OFFSET:
        return QString("PLL_LFSR");
    case OSC_FREQ_DET_OFFSET:
        return QString("OSC_FREQ_DET");
    case OSC_FREQ_DET_STATUS_OFFSET:
        return QString("OSC_FREQ_DET_STATUS");
    case PLLC_BASE_OFFSET:
        return QString("PLLC_BASE");
    case PLLC_OUT_OFFSET:
        return QString("PLLC_OUT");
    case PLLC_MISC_OFFSET:
        return QString("PLLC_MISC");
    case PLLM_BASE_OFFSET:
        return QString("PLLM_BASE");
    case PLLM_OUT_OFFSET:
        return QString("PLLM_OUT");
    case PLLM_MISC_OFFSET:
        return QString("PLLM_MISC");
    case PLLP_BASE_OFFSET:
        return QString("PLLP_BASE");
    case PLLP_OUTA_OFFSET:
        return QString("PLLP_OUTA");
    case PLLP_OUTB_OFFSET:
        return QString("PLLP_OUTB");
    case PLLP_MISC_OFFSET:
        return QString("PLLP_MISC");
    case PLLA_BASE_OFFSET:
        return QString("PLLA_BASE");
    case PLLA_OUT_OFFSET:
        return QString("PLLA_OUT");
    case PLLA_MISC_OFFSET:
        return QString("PLLA_MISC");
    case PLLU_BASE_OFFSET:
        return QString("PLLU_BASE");
    case PLLU_MISC_OFFSET:
        return QString("PLLU_MISC");
    case PLLD_BASE_OFFSET:
        return QString("PLLD_BASE");
    case PLLD_MISC_OFFSET:
        return QString("PLLD_MISC");
    case PLLX_BASE_OFFSET:
        return QString("PLLX_BASE");
    case PLLX_MISC_OFFSET:
        return QString("PLLX_MISC");
    case PLLE_BASE_OFFSET:
        return QString("PLLE_BASE");
    case PLLE_MISC_OFFSET:
        return QString("PLLE_MISC");
    case CLK_SOURCE_I2S1_OFFSET:
        return QString("CLK_SOURCE_I2S1");
    case CLK_SOURCE_I2S2_OFFSET:
        return QString("CLK_SOURCE_I2S2");
    case CLK_SOURCE_SPDIF_OUT_OFFSET:
        return QString("CLK_SOURCE_SPDIF_OUT");
    case CLK_SOURCE_SPDIF_IN_OFFSET:
        return QString("CLK_SOURCE_SPDIF_IN");
    case CLK_SOURCE_PWM_OFFSET:
        return QString("CLK_SOURCE_PWM");
    case CLK_SOURCE_SPI1_OFFSET:
        return QString("CLK_SOURCE_SPI1");
    case CLK_SOURCE_SPI22_OFFSET:
        return QString("CLK_SOURCE_SPI22");
    case CLK_SOURCE_SPI3_OFFSET:
        return QString("CLK_SOURCE_SPI3");
    case CLK_SOURCE_XIO_OFFSET:
        return QString("CLK_SOURCE_XIO");
    case CLK_SOURCE_I2C1_OFFSET:
        return QString("CLK_SOURCE_I2C1");
    case CLK_SOURCE_DVC_I2C_OFFSET:
        return QString("CLK_SOURCE_DVC_I2C");
    case CLK_SOURCE_TWC_OFFSET:
        return QString("CLK_SOURCE_TWC");
    case CLK_SOURCE_SBC1_OFFSET:
        return QString("CLK_SOURCE_SBC1");
    case CLK_SOURCE_DISP1_OFFSET:
        return QString("CLK_SOURCE_DISP1");
    case CLK_SOURCE_DISP2_OFFSET:
        return QString("CLK_SOURCE_DISP2");
    case CLK_SOURCE_CVE_OFFSET:
        return QString("CLK_SOURCE_CVE");
    case CLK_SOURCE_IDE_OFFSET:
        return QString("CLK_SOURCE_IDE");
    case CLK_SOURCE_VI_OFFSET:
        return QString("CLK_SOURCE_VI");
    case CLK_SOURCE_SDMMC1_OFFSET:
        return QString("CLK_SOURCE_SDMMC1");
    case CLK_SOURCE_SDMMC2_OFFSET:
        return QString("CLK_SOURCE_SDMMC2");
    case CLK_SOURCE_G3D_OFFSET:
        return QString("CLK_SOURCE_G3D");
    case CLK_SOURCE_G2D_OFFSET:
        return QString("CLK_SOURCE_G2D");
    case CLK_SOURCE_NDFLASH_OFFSET:
        return QString("CLK_SOURCE_NDFLASH");
    case CLK_SOURCE_SDMMC4_OFFSET:
        return QString("CLK_SOURCE_SDMMC4");
    case CLK_SOURCE_VFIR_OFFSET:
        return QString("CLK_SOURCE_VFIR");
    case CLK_SOURCE_EPP_OFFSET:
        return QString("CLK_SOURCE_EPP");
    case CLK_SOURCE_MPE_OFFSET:
        return QString("CLK_SOURCE_MPE");
    case CLK_SOURCE_MIPI_OFFSET:
        return QString("CLK_SOURCE_MIPI");
    case CLK_SOURCE_UART1_OFFSET:
        return QString("CLK_SOURCE_UART1");
    case CLK_SOURCE_UART2_OFFSET:
        return QString("CLK_SOURCE_UART2");
    case CLK_SOURCE_HOST1X_OFFSET:
        return QString("CLK_SOURCE_HOST1X");
    case CLK_SOURCE_TVO_OFFSET:
        return QString("CLK_SOURCE_TVO");
    case CLK_SOURCE_HDMI_OFFSET:
        return QString("CLK_SOURCE_HDMI");
    case CLK_SOURCE_TVDAC_OFFSET:
        return QString("CLK_SOURCE_TVDAC");
    case CLK_SOURCE_I2C2_OFFSET:
        return QString("CLK_SOURCE_I2C2");
    case CLK_SOURCE_EMC_OFFSET:
        return QString("CLK_SOURCE_EMC");
    case CLK_SOURCE_UART3_OFFSET:
        return QString("CLK_SOURCE_UART3");
    case CLK_SOURCE_VI_SENSOR_OFFSET:
        return QString("CLK_SOURCE_VI_SENSOR");
    case CLK_SOURCE_SPI4_OFFSET:
        return QString("CLK_SOURCE_SPI4");
    case CLK_SOURCE_I2C3_OFFSET:
        return QString("CLK_SOURCE_I2C3");
    case CLK_SOURCE_SDMMC3_OFFSET:
        return QString("CLK_SOURCE_SDMMC3");
    case CLK_SOURCE_UART4_OFFSET:
        return QString("CLK_SOURCE_UART4");
    case CLK_SOURCE_UART5_OFFSET:
        return QString("CLK_SOURCE_UART5");
    case CLK_SOURCE_VDE_OFFSET:
        return QString("CLK_SOURCE_VDE");
    case CLK_SOURCE_OWR_OFFSET:
        return QString("CLK_SOURCE_OWR");
    case CLK_SOURCE_NOR_OFFSET:
        return QString("CLK_SOURCE_NOR");
    case CLK_SOURCE_CSITE_OFFSET:
        return QString("CLK_SOURCE_CSITE");
    case CLK_SOURCE_OSC_OFFSET:
        return QString("CLK_SOURCE_OSC");
    case RST_DEV_L_SET_OFFSET:
        return QString("RST_DEV_L_SET");
    case RST_DEV_L_CLR_OFFSET:
        return QString("RST_DEV_L_CLR");
    case RST_DEV_H_SET_OFFSET:
        return QString("RST_DEV_H_SET");
    case RST_DEV_H_CLR_OFFSET:
        return QString("RST_DEV_H_CLR");
    case RST_DEV_U_SET_OFFSET:
        return QString("RST_DEV_U_SET");
    case RST_DEV_U_CLR_OFFSET:
        return QString("RST_DEV_U_CLR");
    case CLK_ENB_L_SET_OFFSET:
        return QString("CLK_ENB_L_SET");
    case CLK_ENB_L_CLR_OFFSET:
        return QString("CLK_ENB_L_CLR");
    case CLK_ENB_H_SET_OFFSET:
        return QString("CLK_ENB_H_SET");
    case CLK_ENB_H_CLR_OFFSET:
        return QString("CLK_ENB_H_CLR");
    case CLK_ENB_U_SET_OFFSET:
        return QString("CLK_ENB_U_SET");
    case CLK_ENB_U_CLR_OFFSET:
        return QString("CLK_ENB_U_CLR");
    case RST_CPU_CMPLX_SET_OFFSET:
        return QString("RST_CPU_CMPLX_SET");
    case RST_CPU_CMPLX_CLR_OFFSET:
        return QString("RST_CPU_CMPLX_CLR");
    case CLK_SOURCE_LA_OFFSET:
        return QString("CLK_SOURCE_LA");

    default:
        break;
    }

    qDebug() << QString().sprintf("CAR: %s: Ooops... 0x%x", __func__, entry.offset);

    return QString().sprintf("Ooops... @0x%X", entry.offset);
}

void CarDev::fill_bits_details(const u_int32_t &offset,
                                      const u_int32_t &value, const u_int32_t &new_value)
{
    switch (offset) {
    case RST_SOURCE_OFFSET:
        fill_rst_source_details(value, new_value);
        break;
    case RST_DEVICES_L_OFFSET:
        fill_rst_devices_l_details(value, new_value);
        break;
    case RST_DEVICES_H_OFFSET:
        fill_rst_devices_h_details(value, new_value);
        break;
    case RST_DEVICES_U_OFFSET:
        fill_rst_devices_u_details(value, new_value);
        break;
    case CLK_OUT_ENB_L_OFFSET:
        fill_clk_out_enb_l_details(value, new_value);
        break;
    case CLK_OUT_ENB_H_OFFSET:
        fill_clk_out_enb_h_details(value, new_value);
        break;
    case CLK_OUT_ENB_U_OFFSET:
        fill_clk_out_enb_u_details(value, new_value);
        break;
    case CCLK_BURST_POLICY_OFFSET:
        fill_cclk_burst_policy_details(value, new_value);
        break;
    case SUPER_CCLK_DIVIDER_OFFSET:
        fill_super_cclk_divider_details(value, new_value);
        break;
    case SCLK_BURST_POLICY_OFFSET:
        fill_sclk_burst_policy_details(value, new_value);
        break;
    case SUPER_SCLK_DIVIDER_OFFSET:
        fill_super_sclk_divider_details(value, new_value);
        break;
    case CLK_SYSTEM_RATE_OFFSET:
        fill_clk_system_rate_details(value, new_value);
        break;
    case PROG_DLY_CLK_OFFSET:
        fill_prog_dly_clk_details(value, new_value);
        break;
    case AUDIO_SYNC_CLK_RATE_OFFSET:
        fill_audio_sync_clk_rate_details(value, new_value);
        break;
    case COP_CLK_SKIP_POLICY_OFFSET:
        fill_cop_clk_skip_policy_details(value, new_value);
        break;
    case CLK_MASK_ARM_OFFSET:
        fill_clk_mask_arm_details(value, new_value);
        break;
    case MISC_CLK_ENB_OFFSET:
        fill_misc_clk_enb_details(value, new_value);
        break;
    case CLK_CPU_CMPLX_OFFSET:
        fill_clk_cpu_cmplx_details(value, new_value);
        break;
    case OSC_CTRL_OFFSET:
        fill_osc_ctrl_details(value, new_value);
        break;
    case PLL_LFSR_OFFSET:
        fill_pll_lfsr_details(value, new_value);
        break;
    case OSC_FREQ_DET_OFFSET:
        fill_osc_freq_det_details(value, new_value);
        break;
    case OSC_FREQ_DET_STATUS_OFFSET:
        fill_osc_freq_det_status_details(value, new_value);
        break;
    case PLLC_BASE_OFFSET:
        fill_pllc_base_details(value, new_value);
        break;
    case PLLC_OUT_OFFSET:
        fill_pllc_out_details(value, new_value);
        break;
    case PLLC_MISC_OFFSET:
        fill_pllc_misc_details(value, new_value);
        break;
    case PLLM_BASE_OFFSET:
        fill_pllm_base_details(value, new_value);
        break;
    case PLLM_OUT_OFFSET:
        fill_pllm_out_details(value, new_value);
        break;
    case PLLM_MISC_OFFSET:
        fill_pllm_misc_details(value, new_value);
        break;
    case PLLP_BASE_OFFSET:
        fill_pllp_base_details(value, new_value);
        break;
    case PLLP_OUTA_OFFSET:
        fill_pllp_outa_details(value, new_value);
        break;
    case PLLP_OUTB_OFFSET:
        fill_pllp_outb_details(value, new_value);
        break;
    case PLLP_MISC_OFFSET:
        fill_pllp_misc_details(value, new_value);
        break;
    case PLLA_BASE_OFFSET:
        fill_plla_base_details(value, new_value);
        break;
    case PLLA_OUT_OFFSET:
        fill_plla_out_details(value, new_value);
        break;
    case PLLA_MISC_OFFSET:
        fill_plla_misc_details(value, new_value);
        break;
    case PLLU_BASE_OFFSET:
        fill_pllu_base_details(value, new_value);
        break;
    case PLLU_MISC_OFFSET:
        fill_pllu_misc_details(value, new_value);
        break;
    case PLLD_BASE_OFFSET:
        fill_plld_base_details(value, new_value);
        break;
    case PLLD_MISC_OFFSET:
        fill_plld_misc_details(value, new_value);
        break;
    case PLLX_BASE_OFFSET:
        fill_pllx_base_details(value, new_value);
        break;
    case PLLX_MISC_OFFSET:
        fill_pllx_misc_details(value, new_value);
        break;
    case PLLE_BASE_OFFSET:
        fill_plle_base_details(value, new_value);
        break;
    case PLLE_MISC_OFFSET:
        fill_plle_misc_details(value, new_value);
        break;
    case CLK_SOURCE_I2S1_OFFSET:
        fill_clk_source_i2s1_details(value, new_value);
        break;
    case CLK_SOURCE_I2S2_OFFSET:
        fill_clk_source_i2s2_details(value, new_value);
        break;
    case CLK_SOURCE_SPDIF_OUT_OFFSET:
        fill_clk_source_spdif_out_details(value, new_value);
        break;
    case CLK_SOURCE_SPDIF_IN_OFFSET:
        fill_clk_source_spdif_in_details(value, new_value);
        break;
    case CLK_SOURCE_PWM_OFFSET:
        fill_clk_source_pwm_details(value, new_value);
        break;
    case CLK_SOURCE_SPI1_OFFSET:
        fill_clk_source_spi1_details(value, new_value);
        break;
    case CLK_SOURCE_SPI22_OFFSET:
        fill_clk_source_spi22_details(value, new_value);
        break;
    case CLK_SOURCE_SPI3_OFFSET:
        fill_clk_source_spi3_details(value, new_value);
        break;
    case CLK_SOURCE_XIO_OFFSET:
        fill_clk_source_xio_details(value, new_value);
        break;
    case CLK_SOURCE_I2C1_OFFSET:
        fill_clk_source_i2c1_details(value, new_value);
        break;
    case CLK_SOURCE_DVC_I2C_OFFSET:
        fill_clk_source_dvc_i2c_details(value, new_value);
        break;
    case CLK_SOURCE_TWC_OFFSET:
        fill_clk_source_twc_details(value, new_value);
        break;
    case CLK_SOURCE_SBC1_OFFSET:
        fill_clk_source_sbc1_details(value, new_value);
        break;
    case CLK_SOURCE_DISP1_OFFSET:
        fill_clk_source_disp1_details(value, new_value);
        break;
    case CLK_SOURCE_DISP2_OFFSET:
        fill_clk_source_disp2_details(value, new_value);
        break;
    case CLK_SOURCE_CVE_OFFSET:
        fill_clk_source_cve_details(value, new_value);
        break;
    case CLK_SOURCE_IDE_OFFSET:
        fill_clk_source_ide_details(value, new_value);
        break;
    case CLK_SOURCE_VI_OFFSET:
        fill_clk_source_vi_details(value, new_value);
        break;
    case CLK_SOURCE_SDMMC1_OFFSET:
        fill_clk_source_sdmmc1_details(value, new_value);
        break;
    case CLK_SOURCE_SDMMC2_OFFSET:
        fill_clk_source_sdmmc2_details(value, new_value);
        break;
    case CLK_SOURCE_G3D_OFFSET:
        fill_clk_source_g3d_details(value, new_value);
        break;
    case CLK_SOURCE_G2D_OFFSET:
        fill_clk_source_g2d_details(value, new_value);
        break;
    case CLK_SOURCE_NDFLASH_OFFSET:
        fill_clk_source_ndflash_details(value, new_value);
        break;
    case CLK_SOURCE_SDMMC4_OFFSET:
        fill_clk_source_sdmmc4_details(value, new_value);
        break;
    case CLK_SOURCE_VFIR_OFFSET:
        fill_clk_source_vfir_details(value, new_value);
        break;
    case CLK_SOURCE_EPP_OFFSET:
        fill_clk_source_epp_details(value, new_value);
        break;
    case CLK_SOURCE_MPE_OFFSET:
        fill_clk_source_mpe_details(value, new_value);
        break;
    case CLK_SOURCE_MIPI_OFFSET:
        fill_clk_source_mipi_details(value, new_value);
        break;
    case CLK_SOURCE_UART1_OFFSET:
        fill_clk_source_uart1_details(value, new_value);
        break;
    case CLK_SOURCE_UART2_OFFSET:
        fill_clk_source_uart2_details(value, new_value);
        break;
    case CLK_SOURCE_HOST1X_OFFSET:
        fill_clk_source_host1x_details(value, new_value);
        break;
    case CLK_SOURCE_TVO_OFFSET:
        fill_clk_source_tvo_details(value, new_value);
        break;
    case CLK_SOURCE_HDMI_OFFSET:
        fill_clk_source_hdmi_details(value, new_value);
        break;
    case CLK_SOURCE_TVDAC_OFFSET:
        fill_clk_source_tvdac_details(value, new_value);
        break;
    case CLK_SOURCE_I2C2_OFFSET:
        fill_clk_source_i2c2_details(value, new_value);
        break;
    case CLK_SOURCE_EMC_OFFSET:
        fill_clk_source_emc_details(value, new_value);
        break;
    case CLK_SOURCE_UART3_OFFSET:
        fill_clk_source_uart3_details(value, new_value);
        break;
    case CLK_SOURCE_VI_SENSOR_OFFSET:
        fill_clk_source_vi_sensor_details(value, new_value);
        break;
    case CLK_SOURCE_SPI4_OFFSET:
        fill_clk_source_spi4_details(value, new_value);
        break;
    case CLK_SOURCE_I2C3_OFFSET:
        fill_clk_source_i2c3_details(value, new_value);
        break;
    case CLK_SOURCE_SDMMC3_OFFSET:
        fill_clk_source_sdmmc3_details(value, new_value);
        break;
    case CLK_SOURCE_UART4_OFFSET:
        fill_clk_source_uart4_details(value, new_value);
        break;
    case CLK_SOURCE_UART5_OFFSET:
        fill_clk_source_uart5_details(value, new_value);
        break;
    case CLK_SOURCE_VDE_OFFSET:
        fill_clk_source_vde_details(value, new_value);
        break;
    case CLK_SOURCE_OWR_OFFSET:
        fill_clk_source_owr_details(value, new_value);
        break;
    case CLK_SOURCE_NOR_OFFSET:
        fill_clk_source_nor_details(value, new_value);
        break;
    case CLK_SOURCE_CSITE_OFFSET:
        fill_clk_source_csite_details(value, new_value);
        break;
    case CLK_SOURCE_OSC_OFFSET:
        fill_clk_source_osc_details(value, new_value);
        break;
    case RST_DEV_L_SET_OFFSET:
        fill_rst_dev_l_set_details(value, new_value);
        break;
    case RST_DEV_L_CLR_OFFSET:
        fill_rst_dev_l_clr_details(value, new_value);
        break;
    case RST_DEV_H_SET_OFFSET:
        fill_rst_dev_h_set_details(value, new_value);
        break;
    case RST_DEV_H_CLR_OFFSET:
        fill_rst_dev_h_clr_details(value, new_value);
        break;
    case RST_DEV_U_SET_OFFSET:
        fill_rst_dev_u_set_details(value, new_value);
        break;
    case RST_DEV_U_CLR_OFFSET:
        fill_rst_dev_u_clr_details(value, new_value);
        break;
    case CLK_ENB_L_SET_OFFSET:
        fill_clk_enb_l_set_details(value, new_value);
        break;
    case CLK_ENB_L_CLR_OFFSET:
        fill_clk_enb_l_clr_details(value, new_value);
        break;
    case CLK_ENB_H_SET_OFFSET:
        fill_clk_enb_h_set_details(value, new_value);
        break;
    case CLK_ENB_H_CLR_OFFSET:
        fill_clk_enb_h_clr_details(value, new_value);
        break;
    case CLK_ENB_U_SET_OFFSET:
        fill_clk_enb_u_set_details(value, new_value);
        break;
    case CLK_ENB_U_CLR_OFFSET:
        fill_clk_enb_u_clr_details(value, new_value);
        break;
    case RST_CPU_CMPLX_SET_OFFSET:
        fill_rst_cpu_cmplx_set_details(value, new_value);
        break;
    case RST_CPU_CMPLX_CLR_OFFSET:
        fill_rst_cpu_cmplx_clr_details(value, new_value);
        break;
    case CLK_SOURCE_LA_OFFSET:
        fill_clk_source_la_details(value, new_value);
        break;

    default:
        m_bit_details_model.bits.clear();
        break;
    }
}
