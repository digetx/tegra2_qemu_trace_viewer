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

#include "pmcdev.h"

#include <QDebug>

PmcDev::PmcDev(QObject *parent) :
    Device(parent)
{
}

#define CNTRL_OFFSET 0x0
#define CNTRL_UNDEFMASK 0xFFF80000
union cntrl_u {
    struct {
        unsigned int kbc_clk_dis:1;         /* Disable 32KHz clock to KBC; 0 = DISABLE; 1 = ENABLE */
        unsigned int rtc_clk_dis:1;         /* Disable 32KHz clock to RTC; 0 = DISABLE; 1 = ENABLE */
        unsigned int rtc_rst:1;             /* Software reset to RTC; 0 = DISABLE; 1 = ENABLE */
        unsigned int kbc_rst:1;             /* Software reset to KBC; 0 = DISABLE; 1 = ENABLE */
        unsigned int main_rst:1;            /* Reset to CAR; 0 = DISABLE; 1 = ENABLE */
        unsigned int latchwake_en:1;        /* Enables latching wakeup events on transition from 1 to 0(sequence - set to 1,set to 0); 0 = DISABLE; 1 = ENABLE */
        unsigned int glitchdet_dis:1;       /* Disable detecting glitch on wake-up event; 0 = DISABLE; 1 = ENABLE */
        unsigned int blink_en:1;            /* Enables blinking counter and blink output  (on CLK_32K_OUT pin); 0 = DISABLE; 1 = ENABLE */
        unsigned int pwrreq_polarity:1;     /* Inverts CORE_PWR_REQ polarity; 0 = NORMAL; 1 = INVERT */
        unsigned int pwrreq_oe:1;           /* CORE_PWR_REQ output enable. resets to tristate; 0 = DISABLE; 1 = ENABLE */
        unsigned int sysclk_polarity:1;     /* Inverts SYS_CLK_REQ enable polarity; 0 = NORMAL; 1 = INVERT */
        unsigned int sysclk_oe:1;           /* Enables output of system enable clock; 0 = DISABLE; 1 = ENABLE */
        unsigned int pwrgate_dis:1;         /* Disable power gating; 0 = DISABLE; 1 = ENABLE */
        unsigned int aoinit:1;              /* AO(Always On or RTC domain) initialized purely SW diagnostic and interpretation; 0 = NOTDONE; 1 = DONE */
        unsigned int side_effect_lp0:1;     /* when set causes side effect of entering Deep Sleep after powering down CPU; 0 = DISABLE; 1 = ENABLE */
        unsigned int cpupwrreq_polarity:1;  /* Inverts power request polarity 0 = NORMAL 1 = INVERT */
        unsigned int cpupwrreq_oe:1;        /* Power request output enable. resets to tri-state 0 = DISABLE 1 = ENABLE */
        unsigned int intr_polarity:1;       /* Inverts INTR polarity 0 = DISABLE 1 = ENABLE */
        unsigned int fuse_override:1;       /* Fuse override 0 = DISABLE 1 = ENABLE */
        unsigned int undefined_bits_19_31:13;
    };

    u_int32_t reg32;
};

void PmcDev::fill_cntrl_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const cntrl_u old_value_t = { .reg32 = value };
    const cntrl_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: kbc_clk_dis:1",
              "Disable 32KHz clock to KBC;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.kbc_clk_dis, new_value_t.kbc_clk_dis };
    m_bit_details_model.bits.append(entry);
    entry = { "01: rtc_clk_dis:1",
              "Disable 32KHz clock to RTC;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.rtc_clk_dis, new_value_t.rtc_clk_dis };
    m_bit_details_model.bits.append(entry);
    entry = { "02: rtc_rst:1",
              "Software reset to RTC;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.rtc_rst, new_value_t.rtc_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "03: kbc_rst:1",
              "Software reset to KBC;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.kbc_rst, new_value_t.kbc_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "04: main_rst:1",
              "Reset to CAR;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.main_rst, new_value_t.main_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "05: latchwake_en:1",
              "Enables latching wakeup events on transition from 1 to 0(sequence - set to 1,set to 0);\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.latchwake_en, new_value_t.latchwake_en };
    m_bit_details_model.bits.append(entry);
    entry = { "06: glitchdet_dis:1",
              "Disable detecting glitch on wake-up event;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.glitchdet_dis, new_value_t.glitchdet_dis };
    m_bit_details_model.bits.append(entry);
    entry = { "07: blink_en:1",
              "Enables blinking counter and blink output  (on CLK_32K_OUT pin);\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.blink_en, new_value_t.blink_en };
    m_bit_details_model.bits.append(entry);
    entry = { "08: pwrreq_polarity:1",
              "Inverts CORE_PWR_REQ polarity;\n0 = NORMAL;\n1 = INVERT",
              1, old_value_t.pwrreq_polarity, new_value_t.pwrreq_polarity };
    m_bit_details_model.bits.append(entry);
    entry = { "09: pwrreq_oe:1",
              "CORE_PWR_REQ output enable. resets to tristate;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.pwrreq_oe, new_value_t.pwrreq_oe };
    m_bit_details_model.bits.append(entry);
    entry = { "10: sysclk_polarity:1",
              "Inverts SYS_CLK_REQ enable polarity;\n0 = NORMAL;\n1 = INVERT",
              1, old_value_t.sysclk_polarity, new_value_t.sysclk_polarity };
    m_bit_details_model.bits.append(entry);
    entry = { "11: sysclk_oe:1",
              "Enables output of system enable clock;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.sysclk_oe, new_value_t.sysclk_oe };
    m_bit_details_model.bits.append(entry);
    entry = { "12: pwrgate_dis:1",
              "Disable power gating;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.pwrgate_dis, new_value_t.pwrgate_dis };
    m_bit_details_model.bits.append(entry);
    entry = { "13: aoinit:1",
              "AO(Always On or RTC domain) initialized purely SW diagnostic and interpretation;\n0 = NOTDONE;\n1 = DONE",
              1, old_value_t.aoinit, new_value_t.aoinit };
    m_bit_details_model.bits.append(entry);
    entry = { "14: side_effect_lp0:1",
              "when set causes side effect of entering Deep Sleep after powering down CPU;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.side_effect_lp0, new_value_t.side_effect_lp0 };
    m_bit_details_model.bits.append(entry);
    entry = { "15: cpupwrreq_polarity:1",
              "Inverts power request polarity\n0 = NORMAL\n1 = INVERT",
              1, old_value_t.cpupwrreq_polarity, new_value_t.cpupwrreq_polarity };
    m_bit_details_model.bits.append(entry);
    entry = { "16: cpupwrreq_oe:1",
              "Power request output enable. resets to tri-state\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.cpupwrreq_oe, new_value_t.cpupwrreq_oe };
    m_bit_details_model.bits.append(entry);
    entry = { "17: intr_polarity:1",
              "Inverts INTR polarity\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.intr_polarity, new_value_t.intr_polarity };
    m_bit_details_model.bits.append(entry);
    entry = { "18: fuse_override:1",
              "Fuse override\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.fuse_override, new_value_t.fuse_override };
    m_bit_details_model.bits.append(entry);
    entry = { "19: undefined_bits_19_31:13", "", 13, old_value_t.undefined_bits_19_31, new_value_t.undefined_bits_19_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Base offset in APB device space.\nThis register controls clock to KBC, RTC, reset to car, KBC, RTC. It also manages polarity and output enable of sys_clk_req pin and core_pwr_req pin at reset both are disabled since PMU properties are unknown.\nAuxiliary functions - enables blinking functions, and software wake-up latching.\nPMC Control Register";
}

#define SEC_DISABLE_OFFSET 0x4
#define SEC_DISABLE_UNDEFMASK 0xFFFFFFF0
union sec_disable_u {
    struct {
        unsigned int write:1;               /* disable write to secure registers; 0 = OFF; 1 = ON */
        unsigned int read:1;                /* disable read from secure registers; 0 = OFF 1 = ON */
        unsigned int bwrite:1;              /* disable write to bondout secure registers 0 = OFF 1 = ON */
        unsigned int bread:1;               /* disable read from bondout secure registers 0 = OFF 1 = ON */
        unsigned int undefined_bits_4_31:28;
    };

    u_int32_t reg32;
};

void PmcDev::fill_sec_disable_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const sec_disable_u old_value_t = { .reg32 = value };
    const sec_disable_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: write:1",
              "disable write to secure registers;\n0 = OFF;\n1 = ON",
              1, old_value_t.write, new_value_t.write };
    m_bit_details_model.bits.append(entry);
    entry = { "01: read:1",
              "disable read from secure registers;\n0 = OFF\n1 = ON",
              1, old_value_t.read, new_value_t.read };
    m_bit_details_model.bits.append(entry);
    entry = { "02: bwrite:1",
              "disable write to bondout secure registers\n0 = OFF\n1 = ON",
              1, old_value_t.bwrite, new_value_t.bwrite };
    m_bit_details_model.bits.append(entry);
    entry = { "03: bread:1",
              "disable read from bondout secure registers\n0 = OFF\n1 = ON",
              1, old_value_t.bread, new_value_t.bread };
    m_bit_details_model.bits.append(entry);
    entry = { "04: undefined_bits_4_31:28", "", 28, old_value_t.undefined_bits_4_31, new_value_t.undefined_bits_4_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "On separate reset (same as car), disables access (read/write to secure scratch registers). Once write is disabled, secure registers cannot be written until power on reset or reset on exiting Deep Sleep.\n Once read is disabled, read from scratch registers will return 0 until power on reset or reset on exiting Deep Sleep mode.\nSecure Register Disable";
}

#define PMC_SWRST_OFFSET 0x8
#define PMC_SWRST_UNDEFMASK 0xFFFFFFFE
union pmc_swrst_u {
    struct {
        unsigned int rst:1;                 /* software reset to pmc only; 0 = DISABLE; 1 = ENABLE */
        unsigned int undefined_bits_1_31:31;
    };

    u_int32_t reg32;
};

void PmcDev::fill_pmc_swrst_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const pmc_swrst_u old_value_t = { .reg32 = value };
    const pmc_swrst_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: rst:1",
              "software reset to pmc only;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.rst, new_value_t.rst };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_31:31", "", 31, old_value_t.undefined_bits_1_31, new_value_t.undefined_bits_1_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Reset only by por cell and sets itself back to inactive after 2 clock cycles. Only for emergency debugging  purpose and not to be used in any functional mode.\nRegister write which resets PMC only";
}

#define WAKE_MASK_OFFSET 0xC
#define WAKE_MASK_UNDEFMASK 0x00000000
union wake_mask_u {
    struct {
        unsigned int event:16;              /* pin 0-15 wake enable; 0 = DISABLE; 1 = ENABLE */
        unsigned int rtc:1;                 /* RTC wake enable; 0 = DISABLE; 1 = ENABLE */
        unsigned int kbc:1;                 /* KBC wake enable; 0 = DISABLE; 1 = ENABLE */
        unsigned int pwr_int_n:1;           /* PWR_INT_N wake enable; 0 = DISABLE; 1 = ENABLE */
        unsigned int usb_event:4;           /* 0 = ACTIVE_LOW; 1 = ACTIVE_HIGH */
        unsigned int event_res:8;           /* 0 = DISABLE; 1 = ENABLE */
        unsigned int reset_n:1;             /* external reset wake enable; 0 = DISABLE; 1 = ENABLE */
    };

    u_int32_t reg32;
};

void PmcDev::fill_wake_mask_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const wake_mask_u old_value_t = { .reg32 = value };
    const wake_mask_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: event:16",
              "pin 0-15 wake enable;\n0 = DISABLE;\n1 = ENABLE",
              16, old_value_t.event, new_value_t.event };
    m_bit_details_model.bits.append(entry);
    entry = { "16: rtc:1",
              "RTC wake enable;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.rtc, new_value_t.rtc };
    m_bit_details_model.bits.append(entry);
    entry = { "17: kbc:1",
              "KBC wake enable;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.kbc, new_value_t.kbc };
    m_bit_details_model.bits.append(entry);
    entry = { "18: pwr_int_n:1",
              "PWR_INT_N wake enable;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.pwr_int_n, new_value_t.pwr_int_n };
    m_bit_details_model.bits.append(entry);
    entry = { "19: usb_event:4",
              "0 = ACTIVE_LOW;\n1 = ACTIVE_HIGH",
              4, old_value_t.usb_event, new_value_t.usb_event };
    m_bit_details_model.bits.append(entry);
    entry = { "23: event_res:8",
              "0 = DISABLE;\n1 = ENABLE",
              8, old_value_t.event_res, new_value_t.event_res };
    m_bit_details_model.bits.append(entry);
    entry = { "31: reset_n:1",
              "external reset wake enable;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.reset_n, new_value_t.reset_n };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Masks which event can cause wake-up from Deep Sleep mode. Has to be setup before entering Deep Sleep. Works in conjunction with WAKE_LVL register.\nOnly enabled events at the proper wake_lvl will cause exit from Deep Sleep mode.\nCurrent pin assignments wake_mask, wake_status, sw_wake_status and wake levels:\n    * WAKE_STATUS[0] =   ulpi_data4\n    *  WAKE_STATUS[1] =   gp3_pv[3]\n    *  WAKE_STATUS[2] =   dvi_d3\n    *  WAKE_STATUS[3] =   sdio3_dat1\n    *  WAKE_STATUS[4] =   hdmi_int\n    *  WAKE_STATUS[5] =   vgp[6]\n    *  WAKE_STATUS[6] =   gp3_pu[5]\n    *  WAKE_STATUS[7] =   gp3_pu[6]\n    *  WAKE_STATUS[8] =   gmi_wp_n\n    *  WAKE_STATUS[9] =   gp3_ps[2]\n    *  WAKE_STATUS[10] =  gmi_ad21\n    *  WAKE_STATUS[11] =  spi2_cs2\n    *  WAKE_STATUS[12] =  spi2_cs1\n    *  WAKE_STATUS[13] =  sdio1_dat1\n    *  WAKE_STATUS[14] =  gp3_pv[6]\n    *  WAKE_STATUS[15] =  gmi_ad16\n    *  WAKE_STATUS[16] =  rtc_irq\n    *  WAKE_STATUS[17] =  kbc_interrupt\n    *  WAKE_STATUS[18] =  pwr_int\n    *  WAKE_STATUS[19] =  usb_vbus_wakeup[0]\n    *  WAKE_STATUS[20] =  usb_vbus_wakeup[1]\n    *  WAKE_STATUS[21] =  usb_iddig[0]\n    *  WAKE_STATUS[22] =  usb_iddig[1]\n    *  WAKE_STATUS[23] =  gmi_iordy\n    * WAKE_STATUS[24] = gp3_pv[2]\n    *  WAKE_STATUS[25] = gp3_ps[4]\n    *  WAKE_STATUS[26] = gp3_ps[5]\n    *  WAKE_STATUS[27] = gp3_ps[0]\n    *  WAKE_STATUS[28] = gp3_pq[6]\n    *  WAKE_STATUS[29] = gp3_pq[7]\n    *  WAKE_STATUS[30] = dap1_dout\n    *  WAKE_STATUS[31] = 0\nPMC Wake-up Event Mask";
}

#define WAKE_LVL_OFFSET 0x10
#define WAKE_LVL_UNDEFMASK 0x00000000
union wake_lvl_u {
    struct {
        unsigned int event:16;              /* pin 0-15 wake level; 0 = ACTIVE_LOW; 1 = ACTIVE_HIGH */
        unsigned int rtc:1;                 /* RTC wake level; 0 = ACTIVE_LOW; 1 = ACTIVE_HIGH */
        unsigned int kbc:1;                 /* KBC wake level; 0 = ACTIVE_LOW; 1 = ACTIVE_HIGH */
        unsigned int pwr_int_n:1;           /* power interrupt - now permanently tied to bit 18; 0 = ACTIVE_LOW; 1 = ACTIVE_HIGH */
        unsigned int usb_event:4;           /* 0 = ACTIVE_LOW; 1 = ACTIVE_HIGH */
        unsigned int event_res:8;           /* 0 = ACTIVE_LOW; 1 = ACTIVE_HIGH */
        unsigned int reset_n:1;             /* external reset wake level (low active!); 0 = ACTIVE_LOW; 1 = ACTIVE_HIGH */
    };

    u_int32_t reg32;
};

void PmcDev::fill_wake_lvl_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const wake_lvl_u old_value_t = { .reg32 = value };
    const wake_lvl_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: event:16",
              "pin 0-15 wake level;\n0 = ACTIVE_LOW;\n1 = ACTIVE_HIGH",
              16, old_value_t.event, new_value_t.event };
    m_bit_details_model.bits.append(entry);
    entry = { "16: rtc:1",
              "RTC wake level;\n0 = ACTIVE_LOW;\n1 = ACTIVE_HIGH",
              1, old_value_t.rtc, new_value_t.rtc };
    m_bit_details_model.bits.append(entry);
    entry = { "17: kbc:1",
              "KBC wake level;\n0 = ACTIVE_LOW;\n1 = ACTIVE_HIGH",
              1, old_value_t.kbc, new_value_t.kbc };
    m_bit_details_model.bits.append(entry);
    entry = { "18: pwr_int_n:1",
              "power interrupt - now permanently tied to bit 18;\n0 = ACTIVE_LOW;\n1 = ACTIVE_HIGH",
              1, old_value_t.pwr_int_n, new_value_t.pwr_int_n };
    m_bit_details_model.bits.append(entry);
    entry = { "19: usb_event:4",
              "0 = ACTIVE_LOW;\n1 = ACTIVE_HIGH",
              4, old_value_t.usb_event, new_value_t.usb_event };
    m_bit_details_model.bits.append(entry);
    entry = { "23: event_res:8",
              "0 = ACTIVE_LOW;\n1 = ACTIVE_HIGH",
              8, old_value_t.event_res, new_value_t.event_res };
    m_bit_details_model.bits.append(entry);
    entry = { "31: reset_n:1",
              "external reset wake level (low active!);\n0 = ACTIVE_LOW;\n1 = ACTIVE_HIGH",
              1, old_value_t.reset_n, new_value_t.reset_n };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "This register sets level which is active level for wake event. Will cause exit from Deep Sleep mode if input signal level matches level set in this register and WAKE_MASK is set for the event to 1\nPMC Wake Level";
}

#define WAKE_STATUS_OFFSET 0x14
#define WAKE_STATUS_UNDEFMASK 0x00000000
union wake_status_u {
    struct {
        unsigned int event:16;              /* pin 0-15 wake; 0 = NOT_SET; 1 = SET */
        unsigned int rtc:1;                 /* RTC wake; 0 = NOT_SET; 1 = SET */
        unsigned int kbc:1;                 /* KBC wake; 0 = NOT_SET; 1 = SET */
        unsigned int pwr_int_n:1;           /* power interrupt; 0 = NOT_SET; 1 = SET */
        unsigned int usb_event:4;           /* USB wake events; 0 = NOT_SET; 1 = SET */
        unsigned int event_res:8;           /* 0 = NOT_SET; 1 = SET */
        unsigned int reset_n:1;             /* external reset; 0 = NOT_SET; 1 = SET */
    };

    u_int32_t reg32;
};

void PmcDev::fill_wake_status_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const wake_status_u old_value_t = { .reg32 = value };
    const wake_status_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: event:16",
              "pin 0-15 wake;\n0 = NOT_SET;\n1 = SET",
              16, old_value_t.event, new_value_t.event };
    m_bit_details_model.bits.append(entry);
    entry = { "16: rtc:1",
              "RTC wake;\n0 = NOT_SET;\n1 = SET",
              1, old_value_t.rtc, new_value_t.rtc };
    m_bit_details_model.bits.append(entry);
    entry = { "17: kbc:1",
              "KBC wake;\n0 = NOT_SET;\n1 = SET",
              1, old_value_t.kbc, new_value_t.kbc };
    m_bit_details_model.bits.append(entry);
    entry = { "18: pwr_int_n:1",
              "power interrupt;\n0 = NOT_SET;\n1 = SET",
              1, old_value_t.pwr_int_n, new_value_t.pwr_int_n };
    m_bit_details_model.bits.append(entry);
    entry = { "19: usb_event:4",
              "USB wake events;\n0 = NOT_SET;\n1 = SET",
              4, old_value_t.usb_event, new_value_t.usb_event };
    m_bit_details_model.bits.append(entry);
    entry = { "23: event_res:8",
              "0 = NOT_SET;\n1 = SET",
              8, old_value_t.event_res, new_value_t.event_res };
    m_bit_details_model.bits.append(entry);
    entry = { "31: reset_n:1",
              "external reset;\n0 = NOT_SET;\n1 = SET",
              1, old_value_t.reset_n, new_value_t.reset_n };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "This register stores status of the wake events. Event will be set if level matches and is not masked.\nEvents will be latched from the time when minimum power down timer expires (see scratch register 23) to first non-masked event being active. Due to 32 kHz granularity on the control, more than one event can become active before latching is disabled.\nThis register has valid content only after leaving Deep Sleep mode. Writing 1 (bitwise) resets status for the event.\nPMC Wake Status";
}

#define SW_WAKE_STATUS_OFFSET 0x18
#define SW_WAKE_STATUS_UNDEFMASK 0x00000000
union sw_wake_status_u {
    struct {
        unsigned int event:16;              /* pin 0-15 wake; 0 = DISABLE; 1 = ENABLE */
        unsigned int rtc:1;                 /* RTC wake; 0 = DISABLE; 1 = ENABLE */
        unsigned int kbc:1;                 /* KBC wake; 0 = DISABLE; 1 = ENABLE */
        unsigned int pwr_int:1;             /* power interrupt; 0 = NOT_SET; 1 = SET */
        unsigned int usb_event:4;           /* USB wake events; 0 = NOT_SET; 1 = SET */
        unsigned int event_res:8;           /* 0 = NOT_SET; 1 = SET */
        unsigned int reset_n:1;             /* external reset; 0 = NOT_SET; 1 = SET */
    };

    u_int32_t reg32;
};

void PmcDev::fill_sw_wake_status_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const sw_wake_status_u old_value_t = { .reg32 = value };
    const sw_wake_status_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: event:16",
              "pin 0-15 wake;\n0 = DISABLE;\n1 = ENABLE",
              16, old_value_t.event, new_value_t.event };
    m_bit_details_model.bits.append(entry);
    entry = { "16: rtc:1",
              "RTC wake;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.rtc, new_value_t.rtc };
    m_bit_details_model.bits.append(entry);
    entry = { "17: kbc:1",
              "KBC wake;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.kbc, new_value_t.kbc };
    m_bit_details_model.bits.append(entry);
    entry = { "18: pwr_int:1",
              "power interrupt;\n0 = NOT_SET;\n1 = SET",
              1, old_value_t.pwr_int, new_value_t.pwr_int };
    m_bit_details_model.bits.append(entry);
    entry = { "19: usb_event:4",
              "USB wake events;\n0 = NOT_SET;\n1 = SET",
              4, old_value_t.usb_event, new_value_t.usb_event };
    m_bit_details_model.bits.append(entry);
    entry = { "23: event_res:8",
              "0 = NOT_SET;\n1 = SET",
              8, old_value_t.event_res, new_value_t.event_res };
    m_bit_details_model.bits.append(entry);
    entry = { "31: reset_n:1",
              "external reset;\n0 = NOT_SET;\n1 = SET",
              1, old_value_t.reset_n, new_value_t.reset_n };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "This register stores status of the wake events. Latching of the events in software wake status is enabled by PMC_CNRL register bit LATCHWAKE_EN.\nLatching will stop at 1 to 0 transition on this bit. Event will be set if level matches. Masking is not affecting this register. Write will reset wake events set.\nPMC Software Wake Status";
}

#define DPD_PADS_ORIDE_OFFSET 0x1C
#define DPD_PADS_ORIDE_UNDEFMASK 0xFC000000
union dpd_pads_oride_u {
    struct {
        unsigned int kbc_row0:1;            /* override dpd idle state with row 0 output 0 = DISABLE 1 = ENABLE */
        unsigned int kbc_row1:1;            /* override dpd idle state with row 1 output 0 = DISABLE 1 = ENABLE */
        unsigned int kbc_row2:1;            /* override dpd idle state with row 2 output 0 = DISABLE 1 = ENABLE */
        unsigned int kbc_row3:1;            /* override dpd idle state with row 3 output 0 = DISABLE 1 = ENABLE */
        unsigned int kbc_row4:1;            /* override dpd idle state with row 4 output 0 = DISABLE 1 = ENABLE */
        unsigned int kbc_row5:1;            /* override dpd idle state with row 5 output 0 = DISABLE 1 = ENABLE */
        unsigned int kbc_row6:1;            /* override dpd idle state with row 6 output 0 = DISABLE 1 = ENABLE */
        unsigned int kbc_row7:1;            /* override dpd idle state with row 7 output 0 = DISABLE 1 = ENABLE */
        unsigned int kbc_row8:1;            /* override dpd idle state with row 8 output 0 = DISABLE 1 = ENABLE */
        unsigned int kbc_row9:1;            /* override dpd idle state with row 9 output 0 = DISABLE 1 = ENABLE */
        unsigned int kbc_row10:1;           /* override dpd idle state with row 10 output 0 = DISABLE 1 = ENABLE */
        unsigned int kbc_row11:1;           /* override dpd idle state with row 11 output 0 = DISABLE 1 = ENABLE */
        unsigned int kbc_row12:1;           /* override dpd idle state with row 12 output 0 = DISABLE 1 = ENABLE */
        unsigned int kbc_row13:1;           /* override dpd idle state with row 13 output 0 = DISABLE 1 = ENABLE */
        unsigned int kbc_row14:1;           /* override dpd idle state with row 14 output 0 = DISABLE 1 = ENABLE */
        unsigned int kbc_row15:1;           /* override dpd idle state with row 15 output 0 = DISABLE 1 = ENABLE */
        unsigned int kbc_col0:1;            /* override dpd idle state with column 0 output 0 = DISABLE 1 = ENABLE */
        unsigned int kbc_col1:1;            /* override dpd idle state with column 1 output 0 = DISABLE 1 = ENABLE */
        unsigned int kbc_col2:1;            /* override dpd idle state with column 2 output 0 = DISABLE 1 = ENABLE */
        unsigned int kbc_col3:1;            /* override dpd idle state with column 3 output 0 = DISABLE 1 = ENABLE */
        unsigned int blink:1;               /* override dpd idle state with blink ouptut 0 = DISABLE 1 = ENABLE */
        unsigned int sys_clk:1;             /* override dpd idle state with column with sys_clk_request output 0 = DISABLE 1 = ENABLE */
        unsigned int kbc_col4:1;            /* override dpd idle state with column 4 output 0 = DISABLE 1 = ENABLE */
        unsigned int kbc_col5:1;            /* override dpd idle state with column 5 output 0 = DISABLE 1 = ENABLE */
        unsigned int kbc_col6:1;            /* override dpd idle state with column 6 output 0 = DISABLE 1 = ENABLE */
        unsigned int kbc_col7:1;            /* override dpd idle state with column 7 output 0 = DISABLE 1 = ENABLE */
        unsigned int undefined_bits_26_31:6;
    };

    u_int32_t reg32;
};

void PmcDev::fill_dpd_pads_oride_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const dpd_pads_oride_u old_value_t = { .reg32 = value };
    const dpd_pads_oride_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: kbc_row0:1",
              "override dpd idle state with row 0 output\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.kbc_row0, new_value_t.kbc_row0 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: kbc_row1:1",
              "override dpd idle state with row 1 output\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.kbc_row1, new_value_t.kbc_row1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: kbc_row2:1",
              "override dpd idle state with row 2 output\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.kbc_row2, new_value_t.kbc_row2 };
    m_bit_details_model.bits.append(entry);
    entry = { "03: kbc_row3:1",
              "override dpd idle state with row 3 output\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.kbc_row3, new_value_t.kbc_row3 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: kbc_row4:1",
              "override dpd idle state with row 4 output\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.kbc_row4, new_value_t.kbc_row4 };
    m_bit_details_model.bits.append(entry);
    entry = { "05: kbc_row5:1",
              "override dpd idle state with row 5 output\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.kbc_row5, new_value_t.kbc_row5 };
    m_bit_details_model.bits.append(entry);
    entry = { "06: kbc_row6:1",
              "override dpd idle state with row 6 output\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.kbc_row6, new_value_t.kbc_row6 };
    m_bit_details_model.bits.append(entry);
    entry = { "07: kbc_row7:1",
              "override dpd idle state with row 7 output\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.kbc_row7, new_value_t.kbc_row7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: kbc_row8:1",
              "override dpd idle state with row 8 output\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.kbc_row8, new_value_t.kbc_row8 };
    m_bit_details_model.bits.append(entry);
    entry = { "09: kbc_row9:1",
              "override dpd idle state with row 9 output\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.kbc_row9, new_value_t.kbc_row9 };
    m_bit_details_model.bits.append(entry);
    entry = { "10: kbc_row10:1",
              "override dpd idle state with row 10 output\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.kbc_row10, new_value_t.kbc_row10 };
    m_bit_details_model.bits.append(entry);
    entry = { "11: kbc_row11:1",
              "override dpd idle state with row 11 output\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.kbc_row11, new_value_t.kbc_row11 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: kbc_row12:1",
              "override dpd idle state with row 12 output\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.kbc_row12, new_value_t.kbc_row12 };
    m_bit_details_model.bits.append(entry);
    entry = { "13: kbc_row13:1",
              "override dpd idle state with row 13 output\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.kbc_row13, new_value_t.kbc_row13 };
    m_bit_details_model.bits.append(entry);
    entry = { "14: kbc_row14:1",
              "override dpd idle state with row 14 output\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.kbc_row14, new_value_t.kbc_row14 };
    m_bit_details_model.bits.append(entry);
    entry = { "15: kbc_row15:1",
              "override dpd idle state with row 15 output\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.kbc_row15, new_value_t.kbc_row15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: kbc_col0:1",
              "override dpd idle state with column 0 output\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.kbc_col0, new_value_t.kbc_col0 };
    m_bit_details_model.bits.append(entry);
    entry = { "17: kbc_col1:1",
              "override dpd idle state with column 1 output\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.kbc_col1, new_value_t.kbc_col1 };
    m_bit_details_model.bits.append(entry);
    entry = { "18: kbc_col2:1",
              "override dpd idle state with column 2 output\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.kbc_col2, new_value_t.kbc_col2 };
    m_bit_details_model.bits.append(entry);
    entry = { "19: kbc_col3:1",
              "override dpd idle state with column 3 output\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.kbc_col3, new_value_t.kbc_col3 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: blink:1",
              "override dpd idle state with blink ouptut\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.blink, new_value_t.blink };
    m_bit_details_model.bits.append(entry);
    entry = { "21: sys_clk:1",
              "override dpd idle state with column with sys_clk_request output\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.sys_clk, new_value_t.sys_clk };
    m_bit_details_model.bits.append(entry);
    entry = { "22: kbc_col4:1",
              "override dpd idle state with column 4 output\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.kbc_col4, new_value_t.kbc_col4 };
    m_bit_details_model.bits.append(entry);
    entry = { "23: kbc_col5:1",
              "override dpd idle state with column 5 output\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.kbc_col5, new_value_t.kbc_col5 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: kbc_col6:1",
              "override dpd idle state with column 6 output\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.kbc_col6, new_value_t.kbc_col6 };
    m_bit_details_model.bits.append(entry);
    entry = { "25: kbc_col7:1",
              "override dpd idle state with column 7 output\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.kbc_col7, new_value_t.kbc_col7 };
    m_bit_details_model.bits.append(entry);
    entry = { "26: undefined_bits_26_31:6", "", 6, old_value_t.undefined_bits_26_31, new_value_t.undefined_bits_26_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "This register enables overriding values from pinmux with values driven by KBC (keyboard) or PMC (sys_clk_req, blink).\nIf bit is set to 1, particular IO will drive direct value from KBC or PMC, and not the pinmux value. During LP0 mode, the pads with the bit set to 1 will not be in deep power down mode. The IO will not drive data from mini pad macros stored during sample cycle, but direct data from KBC or PMC.\nNote:\n This register has to be set before entering LP0 mode.\nDPD Pads Override";
}

#define DPD_SAMPLE_OFFSET 0x20
#define DPD_SAMPLE_UNDEFMASK 0xFFFFFFFE
union dpd_sample_u {
    struct {
        unsigned int on:1;                  /* will set sampling of pads value; 0 = DISABLE; 1 = ENABLE */
        unsigned int undefined_bits_1_31:31;
    };

    u_int32_t reg32;
};

void PmcDev::fill_dpd_sample_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const dpd_sample_u old_value_t = { .reg32 = value };
    const dpd_sample_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: on:1",
              "will set sampling of pads value;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.on, new_value_t.on };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_31:31", "", 31, old_value_t.undefined_bits_1_31, new_value_t.undefined_bits_1_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Setting this register will trigger sampling pads data and direction in which pad will be driven during Deep Sleep mode.\nBefore writing to this register, all interfaces going to pads must be set to ideal \"idle\" mode, which is expected to be driven by pads when chip enters Deep Sleep.\nDPS Power Down Sample has to precede Deep Power Down Enable write. DPD Sample shouldn't be de-asserted until transition from Deep Sleep to WB0.\nDeep Power Down Sample";
}

#define DPD_ENABLE_OFFSET 0x24
#define DPD_ENABLE_UNDEFMASK 0xFFFFFFFE
union dpd_enable_u {
    struct {
        unsigned int on:1;                  /* will set sampling of pads value; 0 = DISABLE; 1 = ENABLE */
        unsigned int undefined_bits_1_31:31;
    };

    u_int32_t reg32;
};

void PmcDev::fill_dpd_enable_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const dpd_enable_u old_value_t = { .reg32 = value };
    const dpd_enable_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: on:1",
              "will set sampling of pads value;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.on, new_value_t.on };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_31:31", "", 31, old_value_t.undefined_bits_1_31, new_value_t.undefined_bits_1_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Setting this register will trigger entering Deep Sleep state. Must be preceded by DPD_SAMPLE write.\nEntering deep power down mode (Deep Sleep) will trigger shut down core power request and shut down system clock request. PLLs, IOs will enter power deep down mode. All signals going from core power to RTC and pads will be cut off (clamped)\nIf none of the wake-up events is set, only power on reset can enable back access to the chip.\nAfter serving wake-up event is completed, the register should be set back to 0 to complete Deep Sleep cycle.\nDeed Power Down Enable";
}

#define PWRGATE_TIMER_OFF_OFFSET 0x28
#define PWRGATE_TIMER_OFF_UNDEFMASK 0x00000000
union pwrgate_timer_off_u {
    struct {
        unsigned int rail0:4;               /* timer value for rail 0 */
        unsigned int rail1:4;               /* timer value for rail 1 */
        unsigned int rail2:4;               /* timer value for rail 2 */
        unsigned int rail3:4;               /* timer value for rail 3 */
        unsigned int rail4:4;               /* timer value for rail 4 */
        unsigned int rail5:4;               /* timer value for rail 5 */
        unsigned int rail6:4;               /* timer value for rail 6 */
        unsigned int rail7:4;               /* timer value for rail 7 */
    };

    u_int32_t reg32;
};

void PmcDev::fill_pwrgate_timer_off_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const pwrgate_timer_off_u old_value_t = { .reg32 = value };
    const pwrgate_timer_off_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: rail0:4",
              "timer value for rail 0",
              4, old_value_t.rail0, new_value_t.rail0 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: rail1:4",
              "timer value for rail 1",
              4, old_value_t.rail1, new_value_t.rail1 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: rail2:4",
              "timer value for rail 2",
              4, old_value_t.rail2, new_value_t.rail2 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: rail3:4",
              "timer value for rail 3",
              4, old_value_t.rail3, new_value_t.rail3 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: rail4:4",
              "timer value for rail 4",
              4, old_value_t.rail4, new_value_t.rail4 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: rail5:4",
              "timer value for rail 5",
              4, old_value_t.rail5, new_value_t.rail5 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: rail6:4",
              "timer value for rail 6",
              4, old_value_t.rail6, new_value_t.rail6 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: rail7:4",
              "timer value for rail 7",
              4, old_value_t.rail7, new_value_t.rail7 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Specifies number of APB cycles after which the rail line goes off (turns the power to part of power gated partition). Each rail controls part of powered partition. This register should be set before write to Power Gate Toggle. Shared between all power partitions.\nPower Gate Timer Register";
}

#define PWRGATE_TIMER_ON_OFFSET 0x2C
#define PWRGATE_TIMER_ON_UNDEFMASK 0x00000000
union pwrgate_timer_on_u {
    struct {
        unsigned int rail0:4;               /* timer value for rail 0 */
        unsigned int rail1:4;               /* timer value for rail 1 */
        unsigned int rail2:4;               /* timer value for rail 2 */
        unsigned int rail3:4;               /* timer value for rail 3 */
        unsigned int rail4:4;               /* timer value for rail 4 */
        unsigned int rail5:4;               /* timer value for rail 5 */
        unsigned int rail6:4;               /* timer value for rail 6 */
        unsigned int rail7:4;               /* timer value for rail 7 */
    };

    u_int32_t reg32;
};

void PmcDev::fill_pwrgate_timer_on_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const pwrgate_timer_on_u old_value_t = { .reg32 = value };
    const pwrgate_timer_on_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: rail0:4",
              "timer value for rail 0",
              4, old_value_t.rail0, new_value_t.rail0 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: rail1:4",
              "timer value for rail 1",
              4, old_value_t.rail1, new_value_t.rail1 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: rail2:4",
              "timer value for rail 2",
              4, old_value_t.rail2, new_value_t.rail2 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: rail3:4",
              "timer value for rail 3",
              4, old_value_t.rail3, new_value_t.rail3 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: rail4:4",
              "timer value for rail 4",
              4, old_value_t.rail4, new_value_t.rail4 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: rail5:4",
              "timer value for rail 5",
              4, old_value_t.rail5, new_value_t.rail5 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: rail6:4",
              "timer value for rail 6",
              4, old_value_t.rail6, new_value_t.rail6 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: rail7:4",
              "timer value for rail 7",
              4, old_value_t.rail7, new_value_t.rail7 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Specifies number of APB cycles after which the rail line goes on. Shared between all power partitions. Has to be reloaded before each power gate on/off command.\nPower Gate Timer Register";
}

#define PWRGATE_TOGGLE_OFFSET 0x30
#define PWRGATE_TOGGLE_UNDEFMASK 0xFFFFFEF8
union pwrgate_toggle_u {
    struct {
        unsigned int partid:3;              /* id of partition to be toggled; 0 = CPU Partition; 1 = TD (3D); 2 = Video Encode; 4 = Video Decode; 3 = PCI Express; 5 = L2 Cache; 6 = MPEG Encode */
        unsigned int undefined_bits_3_7:5;
        unsigned int start:1;               /* start power down/up; 0 = DISABLE; 1 = ENABLE */
        unsigned int undefined_bits_9_31:23;
    };

    u_int32_t reg32;
};

void PmcDev::fill_pwrgate_toggle_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const pwrgate_toggle_u old_value_t = { .reg32 = value };
    const pwrgate_toggle_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: partid:3",
              "id of partition to be toggled;\n0 = CPU Partition;\n1 = TD (3D);\n2 = Video Encode;\n4 = Video Decode;\n3 = PCI Express;\n5 = L2 Cache;\n6 = MPEG Encode",
              3, old_value_t.partid, new_value_t.partid };
    m_bit_details_model.bits.append(entry);
    entry = { "03: undefined_bits_3_7:5", "", 5, old_value_t.undefined_bits_3_7, new_value_t.undefined_bits_3_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: start:1",
              "start power down/up;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.start, new_value_t.start };
    m_bit_details_model.bits.append(entry);
    entry = { "09: undefined_bits_9_31:23", "", 23, old_value_t.undefined_bits_9_31, new_value_t.undefined_bits_9_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Write to this register will turn power on/off on to specified power gated partition. Only one partition will be turned on/off at the time.\nPWRGATE_STATUS should be read to determine state of the partition before writing to this register.\nTurning partition off will cause automatic clamping of all signals generated by the power gated partition being turned off. Before partition is turned off, all clocks to the partition should be stopped and reset to the partition should be asserted.\nTurning partition on will not remove clamping. Clamping will be removed only after REMOVE_CLAMPING_CMD write.\nPower Gate Toggle";
}

#define REMOVE_CLAMPING_CMD_OFFSET 0x34
#define REMOVE_CLAMPING_CMD_UNDEFMASK 0xFFFFFF80
union remove_clamping_cmd_u {
    struct {
        unsigned int cpu:1;                 /* remove clamping to CPU; 0 = DISABLE; 1 = ENABLE */
        unsigned int td:1;                  /* remove clamping to TD; 0 = DISABLE; 1 = ENABLE */
        unsigned int ve:1;                  /* remove clamping to VE; 0 = DISABLE; 1 = ENABLE */
        unsigned int vde:1;                 /* remove clamping to VDE; 0 = DISABLE; 1 = ENABLE */
        unsigned int pcx:1;                 /* remove clamping to PCX; 0 = DISABLE; 1 = ENABLE */
        unsigned int l2c:1;                 /* remove clamping to L2_CACHE; 0 = DISABLE; 1 = ENABLE */
        unsigned int mpe:1;                 /* remove clamping to MPE_CACHE; 0 = DISABLE; 1 = ENABLE */
        unsigned int undefined_bits_7_31:25;
    };

    u_int32_t reg32;
};

void PmcDev::fill_remove_clamping_cmd_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const remove_clamping_cmd_u old_value_t = { .reg32 = value };
    const remove_clamping_cmd_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: cpu:1",
              "remove clamping to CPU;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.cpu, new_value_t.cpu };
    m_bit_details_model.bits.append(entry);
    entry = { "01: td:1",
              "remove clamping to TD;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.td, new_value_t.td };
    m_bit_details_model.bits.append(entry);
    entry = { "02: ve:1",
              "remove clamping to VE;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ve, new_value_t.ve };
    m_bit_details_model.bits.append(entry);
    entry = { "03: vde:1",
              "remove clamping to VDE;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.vde, new_value_t.vde };
    m_bit_details_model.bits.append(entry);
    entry = { "04: pcx:1",
              "remove clamping to PCX;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.pcx, new_value_t.pcx };
    m_bit_details_model.bits.append(entry);
    entry = { "05: l2c:1",
              "remove clamping to L2_CACHE;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.l2c, new_value_t.l2c };
    m_bit_details_model.bits.append(entry);
    entry = { "06: mpe:1",
              "remove clamping to MPE_CACHE;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.mpe, new_value_t.mpe };
    m_bit_details_model.bits.append(entry);
    entry = { "07: undefined_bits_7_31:25", "", 25, old_value_t.undefined_bits_7_31, new_value_t.undefined_bits_7_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "This is a bit map with one bit per power partition controller by PMC.\nWhen written to 1, the PMC removes the clamp signals to the corresponding partition. If the partition is not powered on, the register write will be ignored and clamping of the partition will continue\nThe bit is automatically reset to 0 when the clamping has been removed. SW is responsible to write to this register at a correct time, that is, when the clocks are started but the blocks in that partition are still held in reset.\nRemove Clamping";
}

#define PWRGATE_STATUS_OFFSET 0x38
#define PWRGATE_STATUS_UNDEFMASK 0xFFFFFF80
union pwrgate_status_u {
    struct {
        unsigned int cpu:1;                 /* status of CPU partition; 0 = OFF; 1 = ON */
        unsigned int td:1;                  /* status of TD Partition; 0 = OFF; 1 = ON */
        unsigned int ve:1;                  /* status of VE partition; 0 = OFF; 1 = ON */
        unsigned int pcx:1;                 /* status of PCX partition; 0 = OFF; 1 = ON */
        unsigned int vde:1;                 /* status of VDE partition; 0 = OFF; 1 = ON */
        unsigned int l2c:1;                 /* status of L2C partition; 0 = OFF; 1 = ON */
        unsigned int mpe:1;                 /* status of MPE partition; 0 = OFF; 1 = ON */
        unsigned int undefined_bits_7_31:25;
    };

    u_int32_t reg32;
};

void PmcDev::fill_pwrgate_status_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const pwrgate_status_u old_value_t = { .reg32 = value };
    const pwrgate_status_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: cpu:1",
              "status of CPU partition;\n0 = OFF;\n1 = ON",
              1, old_value_t.cpu, new_value_t.cpu };
    m_bit_details_model.bits.append(entry);
    entry = { "01: td:1",
              "status of TD Partition;\n0 = OFF;\n1 = ON",
              1, old_value_t.td, new_value_t.td };
    m_bit_details_model.bits.append(entry);
    entry = { "02: ve:1",
              "status of VE partition;\n0 = OFF;\n1 = ON",
              1, old_value_t.ve, new_value_t.ve };
    m_bit_details_model.bits.append(entry);
    entry = { "03: pcx:1",
              "status of PCX partition;\n0 = OFF;\n1 = ON",
              1, old_value_t.pcx, new_value_t.pcx };
    m_bit_details_model.bits.append(entry);
    entry = { "04: vde:1",
              "status of VDE partition;\n0 = OFF;\n1 = ON",
              1, old_value_t.vde, new_value_t.vde };
    m_bit_details_model.bits.append(entry);
    entry = { "05: l2c:1",
              "status of L2C partition;\n0 = OFF;\n1 = ON",
              1, old_value_t.l2c, new_value_t.l2c };
    m_bit_details_model.bits.append(entry);
    entry = { "06: mpe:1",
              "status of MPE partition;\n0 = OFF;\n1 = ON",
              1, old_value_t.mpe, new_value_t.mpe };
    m_bit_details_model.bits.append(entry);
    entry = { "07: undefined_bits_7_31:25", "", 25, old_value_t.undefined_bits_7_31, new_value_t.undefined_bits_7_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Displays status of the power partitions. This register should be read before writing to PWRGATE_TOGGLE. Read only register.\nPower Gate Status";
}

#define PWRGOOD_TIMER_OFFSET 0x3C
#define PWRGOOD_TIMER_UNDEFMASK 0xFFFF0000
union pwrgood_timer_u {
    struct {
        unsigned int power:8;
        unsigned int oscillator:8;
        unsigned int undefined_bits_16_31:16;
    };

    u_int32_t reg32;
};

void PmcDev::fill_pwrgood_timer_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const pwrgood_timer_u old_value_t = { .reg32 = value };
    const pwrgood_timer_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: power:8", "", 8, old_value_t.power, new_value_t.power };
    m_bit_details_model.bits.append(entry);
    entry = { "08: oscillator:8", "", 8, old_value_t.oscillator, new_value_t.oscillator };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_31:16", "", 16, old_value_t.undefined_bits_16_31, new_value_t.undefined_bits_16_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "There are two time periods controlled by this register:\n    * Power Stabilization Time from Core Power Request – the time required for the PMIC to provide a stable Core Power Rail.\n    * Oscillator Stabilization Time – the time required to ensure that an external oscillator or the internal oscillator is stabilized prior to PMC de-asserting the internal reset signal as the processor resumes from the Deep Sleep state.\nPower Good Timer";
}

#define BLINK_TIMER_OFFSET 0x40
#define BLINK_TIMER_UNDEFMASK 0x00000000
union blink_timer_u {
    struct {
        unsigned int data_on:15;            /* time on */
        unsigned int force_blink:1;         /* if 0 32khz clock */
        unsigned int data_off:16;           /* time off */
    };

    u_int32_t reg32;
};

void PmcDev::fill_blink_timer_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const blink_timer_u old_value_t = { .reg32 = value };
    const blink_timer_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: data_on:15",
              "time on",
              15, old_value_t.data_on, new_value_t.data_on };
    m_bit_details_model.bits.append(entry);
    entry = { "15: force_blink:1",
              "if 0 32khz clock",
              1, old_value_t.force_blink, new_value_t.force_blink };
    m_bit_details_model.bits.append(entry);
    entry = { "16: data_off:16",
              "time off",
              16, old_value_t.data_off, new_value_t.data_off };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Blinker Timer, for external blinker Will output value to pad only if PMC Control Register has BLINK_EN set and DPD_PADS_ORIDE has blink bit set.\nSetting bit 15 to 1 will output 32 KHz clock (the registers above still have to be set)\n    * On time DATA_ON<<4 x  30.51 us\n    * Off time DATA_OFF<<4 x 30.51 us.\nBlinker Timer";
}

#define NO_IOPOWER_OFFSET 0x44
#define NO_IOPOWER_UNDEFMASK 0xFFFFFC00
union no_iopower_u {
    struct {
        unsigned int sys:1;                 /* rail ao IOs; 0 = DISABLE; 1 = ENABLE */
        unsigned int nand:1;                /* rail at3 IOs; 0 = DISABLE; 1 = ENABLE */
        unsigned int uart:1;                /* rail dbg IOs; 0 = DISABLE; 1 = ENABLE */
        unsigned int bb:1;                  /* dlcd IOs; 0 = DISABLE; 1 = ENABLE */
        unsigned int vi:1;                  /* rail dvi IOs; 0 = DISABLE; 1 = ENABLE */
        unsigned int audio:1;               /* rail i2s IOs; 0 = DISABLE; 1 = ENABLE */
        unsigned int lcd:1;                 /* rail lcd IOs; 0 = DISABLE; 1 = ENABLE */
        unsigned int mem:1;                 /* rail mem IOs; 0 = DISABLE; 1 = ENABLE */
        unsigned int sd:1;                  /* rail sd IOs; 0 = DISABLE; 1 = ENABLE */
        unsigned int dsi_csi:1;             /* rail dsi_csi  IOs; 0 = DISABLE; 1 = ENABLE */
        unsigned int undefined_bits_10_31:22;
    };

    u_int32_t reg32;
};

void PmcDev::fill_no_iopower_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const no_iopower_u old_value_t = { .reg32 = value };
    const no_iopower_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: sys:1",
              "rail ao IOs;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.sys, new_value_t.sys };
    m_bit_details_model.bits.append(entry);
    entry = { "01: nand:1",
              "rail at3 IOs;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.nand, new_value_t.nand };
    m_bit_details_model.bits.append(entry);
    entry = { "02: uart:1",
              "rail dbg IOs;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.uart, new_value_t.uart };
    m_bit_details_model.bits.append(entry);
    entry = { "03: bb:1",
              "dlcd IOs;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.bb, new_value_t.bb };
    m_bit_details_model.bits.append(entry);
    entry = { "04: vi:1",
              "rail dvi IOs;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.vi, new_value_t.vi };
    m_bit_details_model.bits.append(entry);
    entry = { "05: audio:1",
              "rail i2s IOs;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.audio, new_value_t.audio };
    m_bit_details_model.bits.append(entry);
    entry = { "06: lcd:1",
              "rail lcd IOs;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.lcd, new_value_t.lcd };
    m_bit_details_model.bits.append(entry);
    entry = { "07: mem:1",
              "rail mem IOs;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.mem, new_value_t.mem };
    m_bit_details_model.bits.append(entry);
    entry = { "08: sd:1",
              "rail sd IOs;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.sd, new_value_t.sd };
    m_bit_details_model.bits.append(entry);
    entry = { "09: dsi_csi:1",
              "rail dsi_csi  IOs;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.dsi_csi, new_value_t.dsi_csi };
    m_bit_details_model.bits.append(entry);
    entry = { "10: undefined_bits_10_31:22", "", 22, old_value_t.undefined_bits_10_31, new_value_t.undefined_bits_10_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = " Controls power rails for each IO level. Can only be set when specific power rail is off. Setting it otherwise will damage the pad.\nNo IO Power Register";
}

#define PWR_DET_OFFSET 0x48
#define PWR_DET_UNDEFMASK 0xFFFFFE00
union pwr_det_u {
    struct {
        unsigned int sys:1;                 /* rail ao IOs; 0 = ENABLE; 1 = DISABLE */
        unsigned int nand:1;                /* rail at3 IOs; 0 = ENABLE; 1 = DISABLE */
        unsigned int uart:1;                /* rail dbg IOs; 0 = ENABLE; 1 = DISABLE */
        unsigned int bb:1;                  /* rail dlcd IOs; 0 = ENABLE; 1 = DISABLE */
        unsigned int vi:1;                  /* rail dvi IOs; 0 = ENABLE; 1 = DISABLE */
        unsigned int audio:1;               /* rail i2s IOs; 0 = ENABLE; 1 = DISABLE */
        unsigned int lcd:1;                 /* rail lcd IOs; 0 = ENABLE; 1 = DISABLE */
        unsigned int mem:1;                 /* rail mem IOs; 0 = ENABLE; 1 = DISABLE */
        unsigned int sd:1;                  /* rail sd IOs; 0 = ENABLE; 1 = DISABLE */
        unsigned int undefined_bits_9_31:23;
    };

    u_int32_t reg32;
};

void PmcDev::fill_pwr_det_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const pwr_det_u old_value_t = { .reg32 = value };
    const pwr_det_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: sys:1",
              "rail ao IOs;\n0 = ENABLE;\n1 = DISABLE",
              1, old_value_t.sys, new_value_t.sys };
    m_bit_details_model.bits.append(entry);
    entry = { "01: nand:1",
              "rail at3 IOs;\n0 = ENABLE;\n1 = DISABLE",
              1, old_value_t.nand, new_value_t.nand };
    m_bit_details_model.bits.append(entry);
    entry = { "02: uart:1",
              "rail dbg IOs;\n0 = ENABLE;\n1 = DISABLE",
              1, old_value_t.uart, new_value_t.uart };
    m_bit_details_model.bits.append(entry);
    entry = { "03: bb:1",
              "rail dlcd IOs;\n0 = ENABLE;\n1 = DISABLE",
              1, old_value_t.bb, new_value_t.bb };
    m_bit_details_model.bits.append(entry);
    entry = { "04: vi:1",
              "rail dvi IOs;\n0 = ENABLE;\n1 = DISABLE",
              1, old_value_t.vi, new_value_t.vi };
    m_bit_details_model.bits.append(entry);
    entry = { "05: audio:1",
              "rail i2s IOs;\n0 = ENABLE;\n1 = DISABLE",
              1, old_value_t.audio, new_value_t.audio };
    m_bit_details_model.bits.append(entry);
    entry = { "06: lcd:1",
              "rail lcd IOs;\n0 = ENABLE;\n1 = DISABLE",
              1, old_value_t.lcd, new_value_t.lcd };
    m_bit_details_model.bits.append(entry);
    entry = { "07: mem:1",
              "rail mem IOs;\n0 = ENABLE;\n1 = DISABLE",
              1, old_value_t.mem, new_value_t.mem };
    m_bit_details_model.bits.append(entry);
    entry = { "08: sd:1",
              "rail sd IOs;\n0 = ENABLE;\n1 = DISABLE",
              1, old_value_t.sd, new_value_t.sd };
    m_bit_details_model.bits.append(entry);
    entry = { "09: undefined_bits_9_31:23", "", 23, old_value_t.undefined_bits_9_31, new_value_t.undefined_bits_9_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Power detect cells identify rails that are higher than 2.5V to ensure IO cells are properly configured for these interfaces. After an IO interface rail is powered, the power detect cell for that rail must be enabled and the power detect output latched before the interface is enabled for use by Tegra 2 Series devices.\nAfter the power detect output has been latched, the power detect cell should be disabled to reduce idle power for Tegra 2 Series devices.\nActive high, sets power detection, only for nine power rails - DSI_CSI doesn't have power detect.\nThe proper sequence for turning on power detects:\n    * write 1 to PWR_DET register for fields requiring power detect\n    *  Allow for 3 us delay (in abp clock cycles)\n    * write 1 to PWR_DET_LATCH\nFor turning PWR_DET off:\n    * write 0 to PWR_DET_LATCH\n    * no delay necessary\n    * write 0 to PWR_DET\nPower Detect";
}

#define PWR_DET_LATCH_OFFSET 0x4C
#define PWR_DET_LATCH_UNDEFMASK 0xFFFFFFFE
union pwr_det_latch_u {
    struct {
        unsigned int latch:1;               /* power detect latch, latches value from the pads as long set to 1; 0 = ENABLE; 1 = DISABLE */
        unsigned int undefined_bits_1_31:31;
    };

    u_int32_t reg32;
};

void PmcDev::fill_pwr_det_latch_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const pwr_det_latch_u old_value_t = { .reg32 = value };
    const pwr_det_latch_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: latch:1",
              "power detect latch, latches value from the pads as long set to 1;\n0 = ENABLE;\n1 = DISABLE",
              1, old_value_t.latch, new_value_t.latch };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_31:31", "", 31, old_value_t.undefined_bits_1_31, new_value_t.undefined_bits_1_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Latches power detect for power rails enabled by Power Detect register.\nPower Detect Latch";
}

#define SCRATCH0_OFFSET 0x50
#define SCRATCH0_UNDEFMASK 0x00000000
union scratch0_u {
    struct {
        unsigned int scratch0:32;           /* General purpose register storage */
    };

    u_int32_t reg32;
};

void PmcDev::fill_scratch0_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const scratch0_u old_value_t = { .reg32 = value };
    const scratch0_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: scratch0:32",
              "General purpose register storage",
              32, old_value_t.scratch0, new_value_t.scratch0 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Scratch Register\nScratch registers for restoring context after wake-up. On a cold power up, the content of reg 0 will be reset to 0x0.";
}

#define SCRATCH1_OFFSET 0x54
#define SCRATCH1_UNDEFMASK 0x00000000
union scratch1_u {
    struct {
        unsigned int scratch1:32;           /* General purpose register storage */
    };

    u_int32_t reg32;
};

void PmcDev::fill_scratch1_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const scratch1_u old_value_t = { .reg32 = value };
    const scratch1_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: scratch1:32",
              "General purpose register storage",
              32, old_value_t.scratch1, new_value_t.scratch1 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Scratch Register";
}

#define SCRATCH2_OFFSET 0x58
#define SCRATCH2_UNDEFMASK 0x00000000
union scratch2_u {
    struct {
        unsigned int scratch2:32;           /* General purpose register storage */
    };

    u_int32_t reg32;
};

void PmcDev::fill_scratch2_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const scratch2_u old_value_t = { .reg32 = value };
    const scratch2_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: scratch2:32",
              "General purpose register storage",
              32, old_value_t.scratch2, new_value_t.scratch2 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Scratch Register";
}

#define SCRATCH3_OFFSET 0x5C
#define SCRATCH3_UNDEFMASK 0x00000000
union scratch3_u {
    struct {
        unsigned int scratch3:32;           /* General purpose register storage */
    };

    u_int32_t reg32;
};

void PmcDev::fill_scratch3_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const scratch3_u old_value_t = { .reg32 = value };
    const scratch3_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: scratch3:32",
              "General purpose register storage",
              32, old_value_t.scratch3, new_value_t.scratch3 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Scratch Register";
}

#define SCRATCH4_OFFSET 0x60
#define SCRATCH4_UNDEFMASK 0x00000000
union scratch4_u {
    struct {
        unsigned int scratch4:32;           /* General purpose register storage */
    };

    u_int32_t reg32;
};

void PmcDev::fill_scratch4_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const scratch4_u old_value_t = { .reg32 = value };
    const scratch4_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: scratch4:32",
              "General purpose register storage",
              32, old_value_t.scratch4, new_value_t.scratch4 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Scratch Register";
}

#define SCRATCH5_OFFSET 0x64
#define SCRATCH5_UNDEFMASK 0x00000000
union scratch5_u {
    struct {
        unsigned int scratch5:32;           /* General purpose register storage */
    };

    u_int32_t reg32;
};

void PmcDev::fill_scratch5_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const scratch5_u old_value_t = { .reg32 = value };
    const scratch5_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: scratch5:32",
              "General purpose register storage",
              32, old_value_t.scratch5, new_value_t.scratch5 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Scratch Register";
}

#define SCRATCH6_OFFSET 0x68
#define SCRATCH6_UNDEFMASK 0x00000000
union scratch6_u {
    struct {
        unsigned int scratch6:32;           /* General purpose register storage */
    };

    u_int32_t reg32;
};

void PmcDev::fill_scratch6_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const scratch6_u old_value_t = { .reg32 = value };
    const scratch6_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: scratch6:32",
              "General purpose register storage",
              32, old_value_t.scratch6, new_value_t.scratch6 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Scratch Register";
}

#define SCRATCH7_OFFSET 0x6C
#define SCRATCH7_UNDEFMASK 0x00000000
union scratch7_u {
    struct {
        unsigned int scratch7:32;           /* General purpose register storage */
    };

    u_int32_t reg32;
};

void PmcDev::fill_scratch7_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const scratch7_u old_value_t = { .reg32 = value };
    const scratch7_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: scratch7:32",
              "General purpose register storage",
              32, old_value_t.scratch7, new_value_t.scratch7 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Scratch Register";
}

#define SCRATCH8_OFFSET 0x70
#define SCRATCH8_UNDEFMASK 0x00000000
union scratch8_u {
    struct {
        unsigned int scratch8:32;           /* General purpose register storage */
    };

    u_int32_t reg32;
};

void PmcDev::fill_scratch8_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const scratch8_u old_value_t = { .reg32 = value };
    const scratch8_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: scratch8:32",
              "General purpose register storage",
              32, old_value_t.scratch8, new_value_t.scratch8 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Scratch Register";
}

#define SCRATCH9_OFFSET 0x74
#define SCRATCH9_UNDEFMASK 0x00000000
union scratch9_u {
    struct {
        unsigned int scratch9:32;           /* General purpose register storage */
    };

    u_int32_t reg32;
};

void PmcDev::fill_scratch9_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const scratch9_u old_value_t = { .reg32 = value };
    const scratch9_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: scratch9:32",
              "General purpose register storage",
              32, old_value_t.scratch9, new_value_t.scratch9 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Scratch Register";
}

#define SCRATCH10_OFFSET 0x78
#define SCRATCH10_UNDEFMASK 0x00000000
union scratch10_u {
    struct {
        unsigned int scratch10:32;          /* General purpose register storage */
    };

    u_int32_t reg32;
};

void PmcDev::fill_scratch10_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const scratch10_u old_value_t = { .reg32 = value };
    const scratch10_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: scratch10:32",
              "General purpose register storage",
              32, old_value_t.scratch10, new_value_t.scratch10 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Scratch Register";
}

#define SCRATCH11_OFFSET 0x7C
#define SCRATCH11_UNDEFMASK 0x00000000
union scratch11_u {
    struct {
        unsigned int scratch11:32;          /* General purpose register storage */
    };

    u_int32_t reg32;
};

void PmcDev::fill_scratch11_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const scratch11_u old_value_t = { .reg32 = value };
    const scratch11_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: scratch11:32",
              "General purpose register storage",
              32, old_value_t.scratch11, new_value_t.scratch11 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Scratch Register";
}

#define SCRATCH12_OFFSET 0x80
#define SCRATCH12_UNDEFMASK 0x00000000
union scratch12_u {
    struct {
        unsigned int scratch12:32;          /* General purpose register storage */
    };

    u_int32_t reg32;
};

void PmcDev::fill_scratch12_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const scratch12_u old_value_t = { .reg32 = value };
    const scratch12_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: scratch12:32",
              "General purpose register storage",
              32, old_value_t.scratch12, new_value_t.scratch12 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Scratch Register";
}

#define SCRATCH13_OFFSET 0x84
#define SCRATCH13_UNDEFMASK 0x00000000
union scratch13_u {
    struct {
        unsigned int scratch13:32;          /* General purpose register storage */
    };

    u_int32_t reg32;
};

void PmcDev::fill_scratch13_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const scratch13_u old_value_t = { .reg32 = value };
    const scratch13_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: scratch13:32",
              "General purpose register storage",
              32, old_value_t.scratch13, new_value_t.scratch13 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Scratch Register";
}

#define SCRATCH14_OFFSET 0x88
#define SCRATCH14_UNDEFMASK 0x00000000
union scratch14_u {
    struct {
        unsigned int scratch14:32;          /* General purpose register storage */
    };

    u_int32_t reg32;
};

void PmcDev::fill_scratch14_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const scratch14_u old_value_t = { .reg32 = value };
    const scratch14_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: scratch14:32",
              "General purpose register storage",
              32, old_value_t.scratch14, new_value_t.scratch14 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Scratch Register";
}

#define SCRATCH15_OFFSET 0x8C
#define SCRATCH15_UNDEFMASK 0x00000000
union scratch15_u {
    struct {
        unsigned int scratch15:32;          /* General purpose register storage */
    };

    u_int32_t reg32;
};

void PmcDev::fill_scratch15_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const scratch15_u old_value_t = { .reg32 = value };
    const scratch15_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: scratch15:32",
              "General purpose register storage",
              32, old_value_t.scratch15, new_value_t.scratch15 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Scratch Register";
}

#define SCRATCH16_OFFSET 0x90
#define SCRATCH16_UNDEFMASK 0x00000000
union scratch16_u {
    struct {
        unsigned int scratch16:32;          /* General purpose register storage */
    };

    u_int32_t reg32;
};

void PmcDev::fill_scratch16_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const scratch16_u old_value_t = { .reg32 = value };
    const scratch16_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: scratch16:32",
              "General purpose register storage",
              32, old_value_t.scratch16, new_value_t.scratch16 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Scratch Register";
}

#define SCRATCH17_OFFSET 0x94
#define SCRATCH17_UNDEFMASK 0x00000000
union scratch17_u {
    struct {
        unsigned int scratch17:32;          /* General purpose register storage */
    };

    u_int32_t reg32;
};

void PmcDev::fill_scratch17_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const scratch17_u old_value_t = { .reg32 = value };
    const scratch17_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: scratch17:32",
              "General purpose register storage",
              32, old_value_t.scratch17, new_value_t.scratch17 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Scratch Register";
}

#define SCRATCH18_OFFSET 0x98
#define SCRATCH18_UNDEFMASK 0x00000000
union scratch18_u {
    struct {
        unsigned int scratch18:32;          /* General purpose register storage */
    };

    u_int32_t reg32;
};

void PmcDev::fill_scratch18_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const scratch18_u old_value_t = { .reg32 = value };
    const scratch18_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: scratch18:32",
              "General purpose register storage",
              32, old_value_t.scratch18, new_value_t.scratch18 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Scratch Register";
}

#define SCRATCH19_OFFSET 0x9C
#define SCRATCH19_UNDEFMASK 0x00000000
union scratch19_u {
    struct {
        unsigned int scratch19:32;          /* General purpose register storage */
    };

    u_int32_t reg32;
};

void PmcDev::fill_scratch19_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const scratch19_u old_value_t = { .reg32 = value };
    const scratch19_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: scratch19:32",
              "General purpose register storage",
              32, old_value_t.scratch19, new_value_t.scratch19 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Scratch Register";
}

#define SCRATCH20_OFFSET 0xA0
#define SCRATCH20_UNDEFMASK 0x00000000
union scratch20_u {
    struct {
        unsigned int scratch20:32;          /* General purpose register storage */
    };

    u_int32_t reg32;
};

void PmcDev::fill_scratch20_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const scratch20_u old_value_t = { .reg32 = value };
    const scratch20_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: scratch20:32",
              "General purpose register storage",
              32, old_value_t.scratch20, new_value_t.scratch20 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Scratch Register";
}

#define SCRATCH21_OFFSET 0xA4
#define SCRATCH21_UNDEFMASK 0x00000000
union scratch21_u {
    struct {
        unsigned int scratch21:32;          /* General purpose register storage */
    };

    u_int32_t reg32;
};

void PmcDev::fill_scratch21_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const scratch21_u old_value_t = { .reg32 = value };
    const scratch21_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: scratch21:32",
              "General purpose register storage",
              32, old_value_t.scratch21, new_value_t.scratch21 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Scratch Register";
}

#define SCRATCH22_OFFSET 0xA8
#define SCRATCH22_UNDEFMASK 0x00000000
union scratch22_u {
    struct {
        unsigned int scratch22:32;          /* General purpose register storage */
    };

    u_int32_t reg32;
};

void PmcDev::fill_scratch22_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const scratch22_u old_value_t = { .reg32 = value };
    const scratch22_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: scratch22:32",
              "General purpose register storage",
              32, old_value_t.scratch22, new_value_t.scratch22 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Scratch Register";
}

#define SCRATCH23_OFFSET 0xAC
#define SCRATCH23_UNDEFMASK 0x00000000
union scratch23_u {
    struct {
        unsigned int scratch23:32;          /* General purpose register storage */
    };

    u_int32_t reg32;
};

void PmcDev::fill_scratch23_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const scratch23_u old_value_t = { .reg32 = value };
    const scratch23_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: scratch23:32",
              "General purpose register storage",
              32, old_value_t.scratch23, new_value_t.scratch23 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Scratch Register";
}

#define SECURE_SCRATCH0_OFFSET 0xB0
#define SECURE_SCRATCH0_UNDEFMASK 0x00000000
union secure_scratch0_u {
    struct {
        unsigned int secure_scratch0:32;
    };

    u_int32_t reg32;
};

void PmcDev::fill_secure_scratch0_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const secure_scratch0_u old_value_t = { .reg32 = value };
    const secure_scratch0_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: secure_scratch0:32", "", 32, old_value_t.secure_scratch0, new_value_t.secure_scratch0 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Secure Scratch Register";
}

#define SECURE_SCRATCH1_OFFSET 0xB4
#define SECURE_SCRATCH1_UNDEFMASK 0x00000000
union secure_scratch1_u {
    struct {
        unsigned int secure_scratch1:32;
    };

    u_int32_t reg32;
};

void PmcDev::fill_secure_scratch1_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const secure_scratch1_u old_value_t = { .reg32 = value };
    const secure_scratch1_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: secure_scratch1:32", "", 32, old_value_t.secure_scratch1, new_value_t.secure_scratch1 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Secure Scratch Register";
}

#define SECURE_SCRATCH2_OFFSET 0xB8
#define SECURE_SCRATCH2_UNDEFMASK 0x00000000
union secure_scratch2_u {
    struct {
        unsigned int secure_scratch2:32;
    };

    u_int32_t reg32;
};

void PmcDev::fill_secure_scratch2_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const secure_scratch2_u old_value_t = { .reg32 = value };
    const secure_scratch2_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: secure_scratch2:32", "", 32, old_value_t.secure_scratch2, new_value_t.secure_scratch2 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Secure Scratch Register";
}

#define SECURE_SCRATCH3_OFFSET 0xBC
#define SECURE_SCRATCH3_UNDEFMASK 0x00000000
union secure_scratch3_u {
    struct {
        unsigned int secure_scratch3:32;
    };

    u_int32_t reg32;
};

void PmcDev::fill_secure_scratch3_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const secure_scratch3_u old_value_t = { .reg32 = value };
    const secure_scratch3_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: secure_scratch3:32", "", 32, old_value_t.secure_scratch3, new_value_t.secure_scratch3 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Secure Scratch Register";
}

#define SECURE_SCRATCH4_OFFSET 0xC0
#define SECURE_SCRATCH4_UNDEFMASK 0x00000000
union secure_scratch4_u {
    struct {
        unsigned int secure_scratch4:32;
    };

    u_int32_t reg32;
};

void PmcDev::fill_secure_scratch4_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const secure_scratch4_u old_value_t = { .reg32 = value };
    const secure_scratch4_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: secure_scratch4:32", "", 32, old_value_t.secure_scratch4, new_value_t.secure_scratch4 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Secure Scratch Register";
}

#define SECURE_SCRATCH5_OFFSET 0xC4
#define SECURE_SCRATCH5_UNDEFMASK 0x00000000
union secure_scratch5_u {
    struct {
        unsigned int secure_scratch5:32;
    };

    u_int32_t reg32;
};

void PmcDev::fill_secure_scratch5_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const secure_scratch5_u old_value_t = { .reg32 = value };
    const secure_scratch5_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: secure_scratch5:32", "", 32, old_value_t.secure_scratch5, new_value_t.secure_scratch5 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Secure Scratch Register";
}

#define CPUPWRGOOD_TIMER_OFFSET 0xC8
#define CPUPWRGOOD_TIMER_UNDEFMASK 0x00000000
union cpupwrgood_timer_u {
    struct {
        unsigned int data:32;               /* timer data */
    };

    u_int32_t reg32;
};

void PmcDev::fill_cpupwrgood_timer_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const cpupwrgood_timer_u old_value_t = { .reg32 = value };
    const cpupwrgood_timer_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: data:32",
              "timer data",
              32, old_value_t.data, new_value_t.data };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "CPU Power Good Timer\nSW 33v override - will work only if SW_E33V_OVR_EN is enabled. 1 will set value to 33v, 0 to 2.5\nWARNING!\n Setting 0 on 3.3v interface will damage the chip!\nEach rail has enable bit, only when enable is set, the value is written.\nThe behavior for timer DATA of zero and one will be the same (i.e., 1 cycle of delay)";
}

#define CPUPWROFF_TIMER_OFFSET 0xCC
#define CPUPWROFF_TIMER_UNDEFMASK 0x00000000
union cpupwroff_timer_u {
    struct {
        unsigned int data:32;               /* timer data */
    };

    u_int32_t reg32;
};

void PmcDev::fill_cpupwroff_timer_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const cpupwroff_timer_u old_value_t = { .reg32 = value };
    const cpupwroff_timer_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: data:32",
              "timer data",
              32, old_value_t.data, new_value_t.data };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "CPU Power Off Timer\nUsed for On to Off transition.";
}

#define PG_MASK_OFFSET 0xD0
#define PG_MASK_UNDEFMASK 0x00000000
union pg_mask_u {
    struct {
        unsigned int td:8;                  /* Mask TD rail */
        unsigned int ve:8;                  /* Mask VE rail */
        unsigned int vd:8;                  /* Mask VDE rail */
        unsigned int px:8;                  /* Mask PCX rail */
    };

    u_int32_t reg32;
};

void PmcDev::fill_pg_mask_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const pg_mask_u old_value_t = { .reg32 = value };
    const pg_mask_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: td:8",
              "Mask TD rail",
              8, old_value_t.td, new_value_t.td };
    m_bit_details_model.bits.append(entry);
    entry = { "08: ve:8",
              "Mask VE rail",
              8, old_value_t.ve, new_value_t.ve };
    m_bit_details_model.bits.append(entry);
    entry = { "16: vd:8",
              "Mask VDE rail",
              8, old_value_t.vd, new_value_t.vd };
    m_bit_details_model.bits.append(entry);
    entry = { "24: px:8",
              "Mask PCX rail",
              8, old_value_t.px, new_value_t.px };
    m_bit_details_model.bits.append(entry);
}

#define PG_MASK_1_OFFSET 0xD4
#define PG_MASK_1_UNDEFMASK 0xFFFF00FE
union pg_mask_1_u {
    struct {
        unsigned int l2c:1;                 /* MASK L2C rail */
        unsigned int undefined_bits_1_7:7;
        unsigned int mpe:8;                 /* MASK MPE rail */
        unsigned int undefined_bits_16_31:16;
    };

    u_int32_t reg32;
};

void PmcDev::fill_pg_mask_1_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const pg_mask_1_u old_value_t = { .reg32 = value };
    const pg_mask_1_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: l2c:1",
              "MASK L2C rail",
              1, old_value_t.l2c, new_value_t.l2c };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_7:7", "", 7, old_value_t.undefined_bits_1_7, new_value_t.undefined_bits_1_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: mpe:8",
              "MASK MPE rail",
              8, old_value_t.mpe, new_value_t.mpe };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_31:16", "", 16, old_value_t.undefined_bits_16_31, new_value_t.undefined_bits_16_31 };
    m_bit_details_model.bits.append(entry);
}

#define AUTO_WAKE_LVL_OFFSET 0xD8
#define AUTO_WAKE_LVL_UNDEFMASK 0xFFFFFFFE
union auto_wake_lvl_u {
    struct {
        unsigned int smpl:1;                /* Causes PMC to sample the wake pads 0 = DISABLE 1 = ENABLE */
        unsigned int undefined_bits_1_31:31;
    };

    u_int32_t reg32;
};

void PmcDev::fill_auto_wake_lvl_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const auto_wake_lvl_u old_value_t = { .reg32 = value };
    const auto_wake_lvl_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: smpl:1",
              "Causes PMC to sample the wake pads\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.smpl, new_value_t.smpl };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_31:31", "", 31, old_value_t.undefined_bits_1_31, new_value_t.undefined_bits_1_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Note:\n This register should not be programmed.\nThe wake levels are snapped just before entering DPD by default.";
}

#define AUTO_WAKE_LVL_MASK_OFFSET 0xDC
#define AUTO_WAKE_LVL_MASK_UNDEFMASK 0x00000000
union auto_wake_lvl_mask_u {
    struct {
        unsigned int value:32;
    };

    u_int32_t reg32;
};

void PmcDev::fill_auto_wake_lvl_mask_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const auto_wake_lvl_mask_u old_value_t = { .reg32 = value };
    const auto_wake_lvl_mask_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: value:32", "", 32, old_value_t.value, new_value_t.value };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "This register is used by s/w to enable sampling of the wake pads before entering LP0\nSetting a '1' would cause the associated pad to be sampled and value transferred to WAKE_LVL register";
}

#define WAKE_DELAY_OFFSET 0xE0
#define WAKE_DELAY_UNDEFMASK 0xFFFF0000
union wake_delay_u {
    struct {
        unsigned int value:16;
        unsigned int undefined_bits_16_31:16;
    };

    u_int32_t reg32;
};

void PmcDev::fill_wake_delay_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const wake_delay_u old_value_t = { .reg32 = value };
    const wake_delay_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: value:16", "", 16, old_value_t.value, new_value_t.value };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_31:16", "", 16, old_value_t.undefined_bits_16_31, new_value_t.undefined_bits_16_31 };
    m_bit_details_model.bits.append(entry);
}

#define PWR_DET_VAL_OFFSET 0xE4
#define PWR_DET_VAL_UNDEFMASK 0xFFFFFE00
union pwr_det_val_u {
    struct {
        unsigned int sys:1;                 /* rail ao IOs  0 = ENABLE 1 = DISABLE */
        unsigned int nand:1;                /* rail at3 IOs  0 = ENABLE 1 = DISABLE */
        unsigned int uart:1;                /* rail dbg IOs  0 = ENABLE 1 = DISABLE */
        unsigned int bb:1;                  /* rail dlcd IOs  0 = ENABLE 1 = DISABLE */
        unsigned int vi:1;                  /* rail dvi IOs  0 = ENABLE 1 = DISABLE */
        unsigned int audio:1;               /* rail i2s IOs  0 = ENABLE 1 = DISABLE */
        unsigned int lcd:1;                 /* rail lcd IOs  0 = ENABLE 1 = DISABLE */
        unsigned int mem:1;                 /* rail mem IOs  0 = ENABLE 1 = DISABLE */
        unsigned int sd:1;                  /* rail sd IOs  0 = ENABLE 1 = DISABLE */
        unsigned int undefined_bits_9_31:23;
    };

    u_int32_t reg32;
};

void PmcDev::fill_pwr_det_val_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const pwr_det_val_u old_value_t = { .reg32 = value };
    const pwr_det_val_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: sys:1",
              "rail ao IOs \n0 = ENABLE\n1 = DISABLE",
              1, old_value_t.sys, new_value_t.sys };
    m_bit_details_model.bits.append(entry);
    entry = { "01: nand:1",
              "rail at3 IOs \n0 = ENABLE\n1 = DISABLE",
              1, old_value_t.nand, new_value_t.nand };
    m_bit_details_model.bits.append(entry);
    entry = { "02: uart:1",
              "rail dbg IOs \n0 = ENABLE\n1 = DISABLE",
              1, old_value_t.uart, new_value_t.uart };
    m_bit_details_model.bits.append(entry);
    entry = { "03: bb:1",
              "rail dlcd IOs \n0 = ENABLE\n1 = DISABLE",
              1, old_value_t.bb, new_value_t.bb };
    m_bit_details_model.bits.append(entry);
    entry = { "04: vi:1",
              "rail dvi IOs \n0 = ENABLE\n1 = DISABLE",
              1, old_value_t.vi, new_value_t.vi };
    m_bit_details_model.bits.append(entry);
    entry = { "05: audio:1",
              "rail i2s IOs \n0 = ENABLE\n1 = DISABLE",
              1, old_value_t.audio, new_value_t.audio };
    m_bit_details_model.bits.append(entry);
    entry = { "06: lcd:1",
              "rail lcd IOs \n0 = ENABLE\n1 = DISABLE",
              1, old_value_t.lcd, new_value_t.lcd };
    m_bit_details_model.bits.append(entry);
    entry = { "07: mem:1",
              "rail mem IOs \n0 = ENABLE\n1 = DISABLE",
              1, old_value_t.mem, new_value_t.mem };
    m_bit_details_model.bits.append(entry);
    entry = { "08: sd:1",
              "rail sd IOs \n0 = ENABLE\n1 = DISABLE",
              1, old_value_t.sd, new_value_t.sd };
    m_bit_details_model.bits.append(entry);
    entry = { "09: undefined_bits_9_31:23", "", 23, old_value_t.undefined_bits_9_31, new_value_t.undefined_bits_9_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "This register is used to override the power-detect cells and manually set the values (in unlikely case the power-detect cells are broken).  A write to this register also causes the values from the power-detect cells to be captured and which can be subsequently read out.";
}

#define DDR_PWR_OFFSET 0xE8
#define DDR_PWR_UNDEFMASK 0xFFFFFFFE
union ddr_pwr_u {
    struct {
        unsigned int val:1;                 /* 0 = E_12V 1 = E_18V */
        unsigned int undefined_bits_1_31:31;
    };

    u_int32_t reg32;
};

void PmcDev::fill_ddr_pwr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const ddr_pwr_u old_value_t = { .reg32 = value };
    const ddr_pwr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: val:1",
              "0 = E_12V\n1 = E_18V",
              1, old_value_t.val, new_value_t.val };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_31:31", "", 31, old_value_t.undefined_bits_1_31, new_value_t.undefined_bits_1_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = " This register is used to program the \"E_18V\" pin of the ddr pads.";
}

#define USB_DEBOUNCE_DEL_OFFSET 0xEC
#define USB_DEBOUNCE_DEL_UNDEFMASK 0xFFFF0000
union usb_debounce_del_u {
    struct {
        unsigned int val:16;
        unsigned int undefined_bits_16_31:16;
    };

    u_int32_t reg32;
};

void PmcDev::fill_usb_debounce_del_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const usb_debounce_del_u old_value_t = { .reg32 = value };
    const usb_debounce_del_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: val:16", "", 16, old_value_t.val, new_value_t.val };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_31:16", "", 16, old_value_t.undefined_bits_16_31, new_value_t.undefined_bits_16_31 };
    m_bit_details_model.bits.append(entry);
}

#define USB_AO_OFFSET 0xF0
#define USB_AO_UNDEFMASK 0xFFFFFFF0
union usb_ao_u {
    struct {
        unsigned int ub_id_pd:2;
        unsigned int vbus_wakeup_pd:2;
        unsigned int undefined_bits_4_31:28;
    };

    u_int32_t reg32;
};

void PmcDev::fill_usb_ao_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const usb_ao_u old_value_t = { .reg32 = value };
    const usb_ao_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: ub_id_pd:2", "", 2, old_value_t.ub_id_pd, new_value_t.ub_id_pd };
    m_bit_details_model.bits.append(entry);
    entry = { "02: vbus_wakeup_pd:2", "", 2, old_value_t.vbus_wakeup_pd, new_value_t.vbus_wakeup_pd };
    m_bit_details_model.bits.append(entry);
    entry = { "04: undefined_bits_4_31:28", "", 28, old_value_t.undefined_bits_4_31, new_value_t.undefined_bits_4_31 };
    m_bit_details_model.bits.append(entry);
}

#define CRYPTO_OP_OFFSET 0xF4
#define CRYPTO_OP_UNDEFMASK 0xFFFFFFFE
union crypto_op_u {
    struct {
        unsigned int val:1;                 /* Disabled by default 0 = ENABLE 1 = DISABLE */
        unsigned int undefined_bits_1_31:31;
    };

    u_int32_t reg32;
};

void PmcDev::fill_crypto_op_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const crypto_op_u old_value_t = { .reg32 = value };
    const crypto_op_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: val:1",
              "Disabled by default\n0 = ENABLE\n1 = DISABLE",
              1, old_value_t.val, new_value_t.val };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_31:31", "", 31, old_value_t.undefined_bits_1_31, new_value_t.undefined_bits_1_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "A complete solution requires a \"semi-sticky\" bit in the always-on domain. The Boot ROM would clear this semi-sticky bit for cold boots, but use its value to propagate the crypto-disable flag across LP0. (The Boot ROM always requires crypto functionality, so a pure hardware solution probably isn't reasonable.)\nThe Boot ROM would be able to clear (to zero) and read the sticky bit, but outside the Boot ROM users would only be able to set (to one) and read the sticky bit. On cold boot, the Boot ROM would always clear the stick bit. On WB0, the Boot ROM would read the sticky bit and copy it's setting to the crypto disable flag.\nCrypto Engine Disable Sticky Bit";
}

#define PLLP_WB0_OVERRIDE_OFFSET 0xF8
#define PLLP_WB0_OVERRIDE_UNDEFMASK 0xFFFFFFF0
union pllp_wb0_override_u {
    struct {
        unsigned int override_enable:1;     /* 1 = override CAR PLLP setting, 0 = no override */
        unsigned int pllp_enable:1;         /* 1 = enable PLLP, 0 = disable PLLP */
        unsigned int osc_freq:2;            /* 00 = 13MHz, 01 = 19.2MHz, 10 = 12MHz, 11 = 26MHz */
        unsigned int undefined_bits_4_31:28;
    };

    u_int32_t reg32;
};

void PmcDev::fill_pllp_wb0_override_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const pllp_wb0_override_u old_value_t = { .reg32 = value };
    const pllp_wb0_override_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: override_enable:1",
              "1 = override CAR PLLP setting,\n0 = no override",
              1, old_value_t.override_enable, new_value_t.override_enable };
    m_bit_details_model.bits.append(entry);
    entry = { "01: pllp_enable:1",
              "1 = enable PLLP,\n0 = disable PLLP",
              1, old_value_t.pllp_enable, new_value_t.pllp_enable };
    m_bit_details_model.bits.append(entry);
    entry = { "02: osc_freq:2",
              "00 = 13MHz,\n01 = 19.2MHz,\n10 = 12MHz,\n11 = 26MHz",
              2, old_value_t.osc_freq, new_value_t.osc_freq };
    m_bit_details_model.bits.append(entry);
    entry = { "04: undefined_bits_4_31:28", "", 28, old_value_t.undefined_bits_4_31, new_value_t.undefined_bits_4_31 };
    m_bit_details_model.bits.append(entry);
}

#define SCRATCH24_OFFSET 0xFC
#define SCRATCH24_UNDEFMASK 0x00000000
union scratch24_u {
    struct {
        unsigned int scratch24:32;          /* General purpose register storage */
    };

    u_int32_t reg32;
};

void PmcDev::fill_scratch24_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const scratch24_u old_value_t = { .reg32 = value };
    const scratch24_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: scratch24:32",
              "General purpose register storage",
              32, old_value_t.scratch24, new_value_t.scratch24 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Scratch Register";
}

#define SCRATCH25_OFFSET 0x100
#define SCRATCH25_UNDEFMASK 0x00000000
union scratch25_u {
    struct {
        unsigned int scratch25:32;          /* General purpose register storage */
    };

    u_int32_t reg32;
};

void PmcDev::fill_scratch25_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const scratch25_u old_value_t = { .reg32 = value };
    const scratch25_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: scratch25:32",
              "General purpose register storage",
              32, old_value_t.scratch25, new_value_t.scratch25 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Scratch Register";
}

#define SCRATCH26_OFFSET 0x104
#define SCRATCH26_UNDEFMASK 0x00000000
union scratch26_u {
    struct {
        unsigned int scratch26:32;          /* General purpose register storage */
    };

    u_int32_t reg32;
};

void PmcDev::fill_scratch26_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const scratch26_u old_value_t = { .reg32 = value };
    const scratch26_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: scratch26:32",
              "General purpose register storage",
              32, old_value_t.scratch26, new_value_t.scratch26 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Scratch Register";
}

#define SCRATCH27_OFFSET 0x108
#define SCRATCH27_UNDEFMASK 0x00000000
union scratch27_u {
    struct {
        unsigned int scratch27:32;          /* General purpose register storage */
    };

    u_int32_t reg32;
};

void PmcDev::fill_scratch27_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const scratch27_u old_value_t = { .reg32 = value };
    const scratch27_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: scratch27:32",
              "General purpose register storage",
              32, old_value_t.scratch27, new_value_t.scratch27 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Scratch Register";
}

#define SCRATCH28_OFFSET 0x10C
#define SCRATCH28_UNDEFMASK 0x00000000
union scratch28_u {
    struct {
        unsigned int scratch28:32;          /* General purpose register storage */
    };

    u_int32_t reg32;
};

void PmcDev::fill_scratch28_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const scratch28_u old_value_t = { .reg32 = value };
    const scratch28_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: scratch28:32",
              "General purpose register storage",
              32, old_value_t.scratch28, new_value_t.scratch28 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Scratch Register";
}

#define SCRATCH29_OFFSET 0x110
#define SCRATCH29_UNDEFMASK 0x00000000
union scratch29_u {
    struct {
        unsigned int scratch29:32;          /* General purpose register storage */
    };

    u_int32_t reg32;
};

void PmcDev::fill_scratch29_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const scratch29_u old_value_t = { .reg32 = value };
    const scratch29_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: scratch29:32",
              "General purpose register storage",
              32, old_value_t.scratch29, new_value_t.scratch29 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Scratch Register";
}

#define SCRATCH30_OFFSET 0x114
#define SCRATCH30_UNDEFMASK 0x00000000
union scratch30_u {
    struct {
        unsigned int scratch30:32;          /* General purpose register storage */
    };

    u_int32_t reg32;
};

void PmcDev::fill_scratch30_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const scratch30_u old_value_t = { .reg32 = value };
    const scratch30_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: scratch30:32",
              "General purpose register storage",
              32, old_value_t.scratch30, new_value_t.scratch30 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Scratch Register";
}

#define SCRATCH31_OFFSET 0x118
#define SCRATCH31_UNDEFMASK 0x00000000
union scratch31_u {
    struct {
        unsigned int scratch31:32;          /* General purpose register storage */
    };

    u_int32_t reg32;
};

void PmcDev::fill_scratch31_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const scratch31_u old_value_t = { .reg32 = value };
    const scratch31_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: scratch31:32",
              "General purpose register storage",
              32, old_value_t.scratch31, new_value_t.scratch31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Scratch Register";
}

#define SCRATCH32_OFFSET 0x11C
#define SCRATCH32_UNDEFMASK 0x00000000
union scratch32_u {
    struct {
        unsigned int scratch32:32;          /* General purpose register storage */
    };

    u_int32_t reg32;
};

void PmcDev::fill_scratch32_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const scratch32_u old_value_t = { .reg32 = value };
    const scratch32_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: scratch32:32",
              "General purpose register storage",
              32, old_value_t.scratch32, new_value_t.scratch32 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Scratch Register";
}

#define SCRATCH33_OFFSET 0x120
#define SCRATCH33_UNDEFMASK 0x00000000
union scratch33_u {
    struct {
        unsigned int scratch33:32;          /* General purpose register storage */
    };

    u_int32_t reg32;
};

void PmcDev::fill_scratch33_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const scratch33_u old_value_t = { .reg32 = value };
    const scratch33_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: scratch33:32",
              "General purpose register storage",
              32, old_value_t.scratch33, new_value_t.scratch33 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Scratch Register";
}

#define SCRATCH34_OFFSET 0x124
#define SCRATCH34_UNDEFMASK 0x00000000
union scratch34_u {
    struct {
        unsigned int scratch34:32;          /* General purpose register storage */
    };

    u_int32_t reg32;
};

void PmcDev::fill_scratch34_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const scratch34_u old_value_t = { .reg32 = value };
    const scratch34_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: scratch34:32",
              "General purpose register storage",
              32, old_value_t.scratch34, new_value_t.scratch34 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Scratch Register";
}

#define SCRATCH35_OFFSET 0x128
#define SCRATCH35_UNDEFMASK 0x00000000
union scratch35_u {
    struct {
        unsigned int scratch35:32;          /* General purpose register storage */
    };

    u_int32_t reg32;
};

void PmcDev::fill_scratch35_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const scratch35_u old_value_t = { .reg32 = value };
    const scratch35_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: scratch35:32",
              "General purpose register storage",
              32, old_value_t.scratch35, new_value_t.scratch35 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Scratch Register";
}

#define SCRATCH36_OFFSET 0x12C
#define SCRATCH36_UNDEFMASK 0x00000000
union scratch36_u {
    struct {
        unsigned int scratch36:32;          /* General purpose register storage */
    };

    u_int32_t reg32;
};

void PmcDev::fill_scratch36_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const scratch36_u old_value_t = { .reg32 = value };
    const scratch36_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: scratch36:32",
              "General purpose register storage",
              32, old_value_t.scratch36, new_value_t.scratch36 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Scratch Register";
}

#define SCRATCH37_OFFSET 0x130
#define SCRATCH37_UNDEFMASK 0x00000000
union scratch37_u {
    struct {
        unsigned int scratch37:32;          /* General purpose register storage */
    };

    u_int32_t reg32;
};

void PmcDev::fill_scratch37_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const scratch37_u old_value_t = { .reg32 = value };
    const scratch37_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: scratch37:32",
              "General purpose register storage",
              32, old_value_t.scratch37, new_value_t.scratch37 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Scratch Register";
}

#define SCRATCH38_OFFSET 0x134
#define SCRATCH38_UNDEFMASK 0x00000000
union scratch38_u {
    struct {
        unsigned int scratch38:32;          /* General purpose register storage */
    };

    u_int32_t reg32;
};

void PmcDev::fill_scratch38_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const scratch38_u old_value_t = { .reg32 = value };
    const scratch38_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: scratch38:32",
              "General purpose register storage",
              32, old_value_t.scratch38, new_value_t.scratch38 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Scratch Register";
}

#define SCRATCH39_OFFSET 0x138
#define SCRATCH39_UNDEFMASK 0x00000000
union scratch39_u {
    struct {
        unsigned int scratch39:32;          /* General purpose register storage */
    };

    u_int32_t reg32;
};

void PmcDev::fill_scratch39_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const scratch39_u old_value_t = { .reg32 = value };
    const scratch39_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: scratch39:32",
              "General purpose register storage",
              32, old_value_t.scratch39, new_value_t.scratch39 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Scratch Register";
}

#define SCRATCH40_OFFSET 0x13C
#define SCRATCH40_UNDEFMASK 0x00000000
union scratch40_u {
    struct {
        unsigned int scratch40:32;          /* General purpose register storage */
    };

    u_int32_t reg32;
};

void PmcDev::fill_scratch40_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const scratch40_u old_value_t = { .reg32 = value };
    const scratch40_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: scratch40:32",
              "General purpose register storage",
              32, old_value_t.scratch40, new_value_t.scratch40 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Scratch Register";
}

#define SCRATCH41_OFFSET 0x140
#define SCRATCH41_UNDEFMASK 0x00000000
union scratch41_u {
    struct {
        unsigned int scratch41:32;          /* General purpose register storage */
    };

    u_int32_t reg32;
};

void PmcDev::fill_scratch41_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const scratch41_u old_value_t = { .reg32 = value };
    const scratch41_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: scratch41:32",
              "General purpose register storage",
              32, old_value_t.scratch41, new_value_t.scratch41 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Scratch Register";
}

#define SCRATCH42_OFFSET 0x144
#define SCRATCH42_UNDEFMASK 0x00000000
union scratch42_u {
    struct {
        unsigned int scratch42:32;          /* General purpose register storage */
    };

    u_int32_t reg32;
};

void PmcDev::fill_scratch42_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const scratch42_u old_value_t = { .reg32 = value };
    const scratch42_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: scratch42:32",
              "General purpose register storage",
              32, old_value_t.scratch42, new_value_t.scratch42 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Scratch Register\nBit 0 of this register is tied to PCX_CLAMP.";
}

#define BONDOUT_MIRROR0_OFFSET 0x148
#define BONDOUT_MIRROR0_UNDEFMASK 0x00000000
union bondout_mirror0_u {
    struct {
        unsigned int bondout_mirror0:32;
    };

    u_int32_t reg32;
};

void PmcDev::fill_bondout_mirror0_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const bondout_mirror0_u old_value_t = { .reg32 = value };
    const bondout_mirror0_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: bondout_mirror0:32", "", 32, old_value_t.bondout_mirror0, new_value_t.bondout_mirror0 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Secure Scratch Register";
}

#define BONDOUT_MIRROR1_OFFSET 0x14C
#define BONDOUT_MIRROR1_UNDEFMASK 0x00000000
union bondout_mirror1_u {
    struct {
        unsigned int bondout_mirror1:32;
    };

    u_int32_t reg32;
};

void PmcDev::fill_bondout_mirror1_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const bondout_mirror1_u old_value_t = { .reg32 = value };
    const bondout_mirror1_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: bondout_mirror1:32", "", 32, old_value_t.bondout_mirror1, new_value_t.bondout_mirror1 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Secure Scratch Register";
}

#define BONDOUT_MIRROR2_OFFSET 0x150
#define BONDOUT_MIRROR2_UNDEFMASK 0x00000000
union bondout_mirror2_u {
    struct {
        unsigned int bondout_mirror2:32;
    };

    u_int32_t reg32;
};

void PmcDev::fill_bondout_mirror2_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const bondout_mirror2_u old_value_t = { .reg32 = value };
    const bondout_mirror2_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: bondout_mirror2:32", "", 32, old_value_t.bondout_mirror2, new_value_t.bondout_mirror2 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Secure Scratch Register";
}

#define SYS_33V_EN_OFFSET 0x154
#define SYS_33V_EN_UNDEFMASK 0xFFFFFFFE
union sys_33v_en_u {
    struct {
        unsigned int val:1;                 /* 1 = 3.3v 0 = 1.8v */
        unsigned int undefined_bits_1_31:31;
    };

    u_int32_t reg32;
};

void PmcDev::fill_sys_33v_en_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const sys_33v_en_u old_value_t = { .reg32 = value };
    const sys_33v_en_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: val:1",
              "1 = 3.3v\n0 = 1.8v",
              1, old_value_t.val, new_value_t.val };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_31:31", "", 31, old_value_t.undefined_bits_1_31, new_value_t.undefined_bits_1_31 };
    m_bit_details_model.bits.append(entry);
}

#define BONDOUT_MIRROR_ACCESS_OFFSET 0x158
#define BONDOUT_MIRROR_ACCESS_UNDEFMASK 0xFFFFFFFC
union bondout_mirror_access_u {
    struct {
        unsigned int bwrite:1;              /* disable write to bondout secure registers 0 = OFF 1 = ON */
        unsigned int bread:1;               /* disable read from bondout secure registers 0 = OFF 1 = ON */
        unsigned int undefined_bits_2_31:30;
    };

    u_int32_t reg32;
};

void PmcDev::fill_bondout_mirror_access_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const bondout_mirror_access_u old_value_t = { .reg32 = value };
    const bondout_mirror_access_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: bwrite:1",
              "disable write to bondout secure registers\n0 = OFF\n1 = ON",
              1, old_value_t.bwrite, new_value_t.bwrite };
    m_bit_details_model.bits.append(entry);
    entry = { "01: bread:1",
              "disable read from bondout secure registers\n0 = OFF\n1 = ON",
              1, old_value_t.bread, new_value_t.bread };
    m_bit_details_model.bits.append(entry);
    entry = { "02: undefined_bits_2_31:30", "", 30, old_value_t.undefined_bits_2_31, new_value_t.undefined_bits_2_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "On separate reset (same as car) disables access (read/write to secure scratch registers)";
}

#define GATE_OFFSET 0x15C
#define GATE_UNDEFMASK 0xFFFFFFFC
union gate_u {
    struct {
        unsigned int gate_dbns:1;           /* 0 = OFF 1 = ON */
        unsigned int gate_wake:1;           /* 0 = OFF 1 = ON */
        unsigned int undefined_bits_2_31:30;
    };

    u_int32_t reg32;
};

void PmcDev::fill_gate_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const gate_u old_value_t = { .reg32 = value };
    const gate_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: gate_dbns:1",
              "0 = OFF\n1 = ON",
              1, old_value_t.gate_dbns, new_value_t.gate_dbns };
    m_bit_details_model.bits.append(entry);
    entry = { "01: gate_wake:1",
              "0 = OFF\n1 = ON",
              1, old_value_t.gate_wake, new_value_t.gate_wake };
    m_bit_details_model.bits.append(entry);
    entry = { "02: undefined_bits_2_31:30", "", 30, old_value_t.undefined_bits_2_31, new_value_t.undefined_bits_2_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "This register is used for SW controlled synchronization between APB domain and the 32 KHz domain.  SW is expected to set the GAKE_WAKE/GATE_DBNS field high to cut the 32 KHz gated clock before updating WAKE_LVL, AUTO_WAKE_LVL, WAKE_MASK and USB_DEBOUNCE_DEL registers. After these registers have been written the GATE_WAKE/GATE_DBNS bit should be written back to '0' to enabled the 32 khz gated clock.\nThis gates the 32 KHz clock to just the flops that store the above fields.";
}

bool PmcDev::is_offset_valid(const u_int32_t &offset) const
{
    switch (offset) {
    case CNTRL_OFFSET:
    case SEC_DISABLE_OFFSET:
    case PMC_SWRST_OFFSET:
    case WAKE_MASK_OFFSET:
    case WAKE_LVL_OFFSET:
    case WAKE_STATUS_OFFSET:
    case SW_WAKE_STATUS_OFFSET:
    case DPD_PADS_ORIDE_OFFSET:
    case DPD_SAMPLE_OFFSET:
    case DPD_ENABLE_OFFSET:
    case PWRGATE_TIMER_OFF_OFFSET:
    case PWRGATE_TIMER_ON_OFFSET:
    case PWRGATE_TOGGLE_OFFSET:
    case REMOVE_CLAMPING_CMD_OFFSET:
    case PWRGATE_STATUS_OFFSET:
    case PWRGOOD_TIMER_OFFSET:
    case BLINK_TIMER_OFFSET:
    case NO_IOPOWER_OFFSET:
    case PWR_DET_OFFSET:
    case PWR_DET_LATCH_OFFSET:
    case SCRATCH0_OFFSET:
    case SCRATCH1_OFFSET:
    case SCRATCH2_OFFSET:
    case SCRATCH3_OFFSET:
    case SCRATCH4_OFFSET:
    case SCRATCH5_OFFSET:
    case SCRATCH6_OFFSET:
    case SCRATCH7_OFFSET:
    case SCRATCH8_OFFSET:
    case SCRATCH9_OFFSET:
    case SCRATCH10_OFFSET:
    case SCRATCH11_OFFSET:
    case SCRATCH12_OFFSET:
    case SCRATCH13_OFFSET:
    case SCRATCH14_OFFSET:
    case SCRATCH15_OFFSET:
    case SCRATCH16_OFFSET:
    case SCRATCH17_OFFSET:
    case SCRATCH18_OFFSET:
    case SCRATCH19_OFFSET:
    case SCRATCH20_OFFSET:
    case SCRATCH21_OFFSET:
    case SCRATCH22_OFFSET:
    case SCRATCH23_OFFSET:
    case SECURE_SCRATCH0_OFFSET:
    case SECURE_SCRATCH1_OFFSET:
    case SECURE_SCRATCH2_OFFSET:
    case SECURE_SCRATCH3_OFFSET:
    case SECURE_SCRATCH4_OFFSET:
    case SECURE_SCRATCH5_OFFSET:
    case CPUPWRGOOD_TIMER_OFFSET:
    case CPUPWROFF_TIMER_OFFSET:
    case PG_MASK_OFFSET:
    case PG_MASK_1_OFFSET:
    case AUTO_WAKE_LVL_OFFSET:
    case AUTO_WAKE_LVL_MASK_OFFSET:
    case WAKE_DELAY_OFFSET:
    case PWR_DET_VAL_OFFSET:
    case DDR_PWR_OFFSET:
    case USB_DEBOUNCE_DEL_OFFSET:
    case USB_AO_OFFSET:
    case CRYPTO_OP_OFFSET:
    case PLLP_WB0_OVERRIDE_OFFSET:
    case SCRATCH24_OFFSET:
    case SCRATCH25_OFFSET:
    case SCRATCH26_OFFSET:
    case SCRATCH27_OFFSET:
    case SCRATCH28_OFFSET:
    case SCRATCH29_OFFSET:
    case SCRATCH30_OFFSET:
    case SCRATCH31_OFFSET:
    case SCRATCH32_OFFSET:
    case SCRATCH33_OFFSET:
    case SCRATCH34_OFFSET:
    case SCRATCH35_OFFSET:
    case SCRATCH36_OFFSET:
    case SCRATCH37_OFFSET:
    case SCRATCH38_OFFSET:
    case SCRATCH39_OFFSET:
    case SCRATCH40_OFFSET:
    case SCRATCH41_OFFSET:
    case SCRATCH42_OFFSET:
    case BONDOUT_MIRROR0_OFFSET:
    case BONDOUT_MIRROR1_OFFSET:
    case BONDOUT_MIRROR2_OFFSET:
    case SYS_33V_EN_OFFSET:
    case BONDOUT_MIRROR_ACCESS_OFFSET:
    case GATE_OFFSET:
        return true;
    default:
        break;
    }

    return false;
}

bool PmcDev::is_undef_changed(const u_int32_t &offset,
                                           const u_int32_t &value,
                                           const u_int32_t &new_value) const
{
    switch (offset) {
    case CNTRL_OFFSET:
        if ((value ^ new_value) & CNTRL_UNDEFMASK)
            return true;
        break;
    case SEC_DISABLE_OFFSET:
        if ((value ^ new_value) & SEC_DISABLE_UNDEFMASK)
            return true;
        break;
    case PMC_SWRST_OFFSET:
        if ((value ^ new_value) & PMC_SWRST_UNDEFMASK)
            return true;
        break;
    case WAKE_MASK_OFFSET:
        if ((value ^ new_value) & WAKE_MASK_UNDEFMASK)
            return true;
        break;
    case WAKE_LVL_OFFSET:
        if ((value ^ new_value) & WAKE_LVL_UNDEFMASK)
            return true;
        break;
    case WAKE_STATUS_OFFSET:
        if ((value ^ new_value) & WAKE_STATUS_UNDEFMASK)
            return true;
        break;
    case SW_WAKE_STATUS_OFFSET:
        if ((value ^ new_value) & SW_WAKE_STATUS_UNDEFMASK)
            return true;
        break;
    case DPD_PADS_ORIDE_OFFSET:
        if ((value ^ new_value) & DPD_PADS_ORIDE_UNDEFMASK)
            return true;
        break;
    case DPD_SAMPLE_OFFSET:
        if ((value ^ new_value) & DPD_SAMPLE_UNDEFMASK)
            return true;
        break;
    case DPD_ENABLE_OFFSET:
        if ((value ^ new_value) & DPD_ENABLE_UNDEFMASK)
            return true;
        break;
    case PWRGATE_TIMER_OFF_OFFSET:
        if ((value ^ new_value) & PWRGATE_TIMER_OFF_UNDEFMASK)
            return true;
        break;
    case PWRGATE_TIMER_ON_OFFSET:
        if ((value ^ new_value) & PWRGATE_TIMER_ON_UNDEFMASK)
            return true;
        break;
    case PWRGATE_TOGGLE_OFFSET:
        if ((value ^ new_value) & PWRGATE_TOGGLE_UNDEFMASK)
            return true;
        break;
    case REMOVE_CLAMPING_CMD_OFFSET:
        if ((value ^ new_value) & REMOVE_CLAMPING_CMD_UNDEFMASK)
            return true;
        break;
    case PWRGATE_STATUS_OFFSET:
        if ((value ^ new_value) & PWRGATE_STATUS_UNDEFMASK)
            return true;
        break;
    case PWRGOOD_TIMER_OFFSET:
        if ((value ^ new_value) & PWRGOOD_TIMER_UNDEFMASK)
            return true;
        break;
    case BLINK_TIMER_OFFSET:
        if ((value ^ new_value) & BLINK_TIMER_UNDEFMASK)
            return true;
        break;
    case NO_IOPOWER_OFFSET:
        if ((value ^ new_value) & NO_IOPOWER_UNDEFMASK)
            return true;
        break;
    case PWR_DET_OFFSET:
        if ((value ^ new_value) & PWR_DET_UNDEFMASK)
            return true;
        break;
    case PWR_DET_LATCH_OFFSET:
        if ((value ^ new_value) & PWR_DET_LATCH_UNDEFMASK)
            return true;
        break;
    case SCRATCH0_OFFSET:
        if ((value ^ new_value) & SCRATCH0_UNDEFMASK)
            return true;
        break;
    case SCRATCH1_OFFSET:
        if ((value ^ new_value) & SCRATCH1_UNDEFMASK)
            return true;
        break;
    case SCRATCH2_OFFSET:
        if ((value ^ new_value) & SCRATCH2_UNDEFMASK)
            return true;
        break;
    case SCRATCH3_OFFSET:
        if ((value ^ new_value) & SCRATCH3_UNDEFMASK)
            return true;
        break;
    case SCRATCH4_OFFSET:
        if ((value ^ new_value) & SCRATCH4_UNDEFMASK)
            return true;
        break;
    case SCRATCH5_OFFSET:
        if ((value ^ new_value) & SCRATCH5_UNDEFMASK)
            return true;
        break;
    case SCRATCH6_OFFSET:
        if ((value ^ new_value) & SCRATCH6_UNDEFMASK)
            return true;
        break;
    case SCRATCH7_OFFSET:
        if ((value ^ new_value) & SCRATCH7_UNDEFMASK)
            return true;
        break;
    case SCRATCH8_OFFSET:
        if ((value ^ new_value) & SCRATCH8_UNDEFMASK)
            return true;
        break;
    case SCRATCH9_OFFSET:
        if ((value ^ new_value) & SCRATCH9_UNDEFMASK)
            return true;
        break;
    case SCRATCH10_OFFSET:
        if ((value ^ new_value) & SCRATCH10_UNDEFMASK)
            return true;
        break;
    case SCRATCH11_OFFSET:
        if ((value ^ new_value) & SCRATCH11_UNDEFMASK)
            return true;
        break;
    case SCRATCH12_OFFSET:
        if ((value ^ new_value) & SCRATCH12_UNDEFMASK)
            return true;
        break;
    case SCRATCH13_OFFSET:
        if ((value ^ new_value) & SCRATCH13_UNDEFMASK)
            return true;
        break;
    case SCRATCH14_OFFSET:
        if ((value ^ new_value) & SCRATCH14_UNDEFMASK)
            return true;
        break;
    case SCRATCH15_OFFSET:
        if ((value ^ new_value) & SCRATCH15_UNDEFMASK)
            return true;
        break;
    case SCRATCH16_OFFSET:
        if ((value ^ new_value) & SCRATCH16_UNDEFMASK)
            return true;
        break;
    case SCRATCH17_OFFSET:
        if ((value ^ new_value) & SCRATCH17_UNDEFMASK)
            return true;
        break;
    case SCRATCH18_OFFSET:
        if ((value ^ new_value) & SCRATCH18_UNDEFMASK)
            return true;
        break;
    case SCRATCH19_OFFSET:
        if ((value ^ new_value) & SCRATCH19_UNDEFMASK)
            return true;
        break;
    case SCRATCH20_OFFSET:
        if ((value ^ new_value) & SCRATCH20_UNDEFMASK)
            return true;
        break;
    case SCRATCH21_OFFSET:
        if ((value ^ new_value) & SCRATCH21_UNDEFMASK)
            return true;
        break;
    case SCRATCH22_OFFSET:
        if ((value ^ new_value) & SCRATCH22_UNDEFMASK)
            return true;
        break;
    case SCRATCH23_OFFSET:
        if ((value ^ new_value) & SCRATCH23_UNDEFMASK)
            return true;
        break;
    case SECURE_SCRATCH0_OFFSET:
        if ((value ^ new_value) & SECURE_SCRATCH0_UNDEFMASK)
            return true;
        break;
    case SECURE_SCRATCH1_OFFSET:
        if ((value ^ new_value) & SECURE_SCRATCH1_UNDEFMASK)
            return true;
        break;
    case SECURE_SCRATCH2_OFFSET:
        if ((value ^ new_value) & SECURE_SCRATCH2_UNDEFMASK)
            return true;
        break;
    case SECURE_SCRATCH3_OFFSET:
        if ((value ^ new_value) & SECURE_SCRATCH3_UNDEFMASK)
            return true;
        break;
    case SECURE_SCRATCH4_OFFSET:
        if ((value ^ new_value) & SECURE_SCRATCH4_UNDEFMASK)
            return true;
        break;
    case SECURE_SCRATCH5_OFFSET:
        if ((value ^ new_value) & SECURE_SCRATCH5_UNDEFMASK)
            return true;
        break;
    case CPUPWRGOOD_TIMER_OFFSET:
        if ((value ^ new_value) & CPUPWRGOOD_TIMER_UNDEFMASK)
            return true;
        break;
    case CPUPWROFF_TIMER_OFFSET:
        if ((value ^ new_value) & CPUPWROFF_TIMER_UNDEFMASK)
            return true;
        break;
    case PG_MASK_OFFSET:
        if ((value ^ new_value) & PG_MASK_UNDEFMASK)
            return true;
        break;
    case PG_MASK_1_OFFSET:
        if ((value ^ new_value) & PG_MASK_1_UNDEFMASK)
            return true;
        break;
    case AUTO_WAKE_LVL_OFFSET:
        if ((value ^ new_value) & AUTO_WAKE_LVL_UNDEFMASK)
            return true;
        break;
    case AUTO_WAKE_LVL_MASK_OFFSET:
        if ((value ^ new_value) & AUTO_WAKE_LVL_MASK_UNDEFMASK)
            return true;
        break;
    case WAKE_DELAY_OFFSET:
        if ((value ^ new_value) & WAKE_DELAY_UNDEFMASK)
            return true;
        break;
    case PWR_DET_VAL_OFFSET:
        if ((value ^ new_value) & PWR_DET_VAL_UNDEFMASK)
            return true;
        break;
    case DDR_PWR_OFFSET:
        if ((value ^ new_value) & DDR_PWR_UNDEFMASK)
            return true;
        break;
    case USB_DEBOUNCE_DEL_OFFSET:
        if ((value ^ new_value) & USB_DEBOUNCE_DEL_UNDEFMASK)
            return true;
        break;
    case USB_AO_OFFSET:
        if ((value ^ new_value) & USB_AO_UNDEFMASK)
            return true;
        break;
    case CRYPTO_OP_OFFSET:
        if ((value ^ new_value) & CRYPTO_OP_UNDEFMASK)
            return true;
        break;
    case PLLP_WB0_OVERRIDE_OFFSET:
        if ((value ^ new_value) & PLLP_WB0_OVERRIDE_UNDEFMASK)
            return true;
        break;
    case SCRATCH24_OFFSET:
        if ((value ^ new_value) & SCRATCH24_UNDEFMASK)
            return true;
        break;
    case SCRATCH25_OFFSET:
        if ((value ^ new_value) & SCRATCH25_UNDEFMASK)
            return true;
        break;
    case SCRATCH26_OFFSET:
        if ((value ^ new_value) & SCRATCH26_UNDEFMASK)
            return true;
        break;
    case SCRATCH27_OFFSET:
        if ((value ^ new_value) & SCRATCH27_UNDEFMASK)
            return true;
        break;
    case SCRATCH28_OFFSET:
        if ((value ^ new_value) & SCRATCH28_UNDEFMASK)
            return true;
        break;
    case SCRATCH29_OFFSET:
        if ((value ^ new_value) & SCRATCH29_UNDEFMASK)
            return true;
        break;
    case SCRATCH30_OFFSET:
        if ((value ^ new_value) & SCRATCH30_UNDEFMASK)
            return true;
        break;
    case SCRATCH31_OFFSET:
        if ((value ^ new_value) & SCRATCH31_UNDEFMASK)
            return true;
        break;
    case SCRATCH32_OFFSET:
        if ((value ^ new_value) & SCRATCH32_UNDEFMASK)
            return true;
        break;
    case SCRATCH33_OFFSET:
        if ((value ^ new_value) & SCRATCH33_UNDEFMASK)
            return true;
        break;
    case SCRATCH34_OFFSET:
        if ((value ^ new_value) & SCRATCH34_UNDEFMASK)
            return true;
        break;
    case SCRATCH35_OFFSET:
        if ((value ^ new_value) & SCRATCH35_UNDEFMASK)
            return true;
        break;
    case SCRATCH36_OFFSET:
        if ((value ^ new_value) & SCRATCH36_UNDEFMASK)
            return true;
        break;
    case SCRATCH37_OFFSET:
        if ((value ^ new_value) & SCRATCH37_UNDEFMASK)
            return true;
        break;
    case SCRATCH38_OFFSET:
        if ((value ^ new_value) & SCRATCH38_UNDEFMASK)
            return true;
        break;
    case SCRATCH39_OFFSET:
        if ((value ^ new_value) & SCRATCH39_UNDEFMASK)
            return true;
        break;
    case SCRATCH40_OFFSET:
        if ((value ^ new_value) & SCRATCH40_UNDEFMASK)
            return true;
        break;
    case SCRATCH41_OFFSET:
        if ((value ^ new_value) & SCRATCH41_UNDEFMASK)
            return true;
        break;
    case SCRATCH42_OFFSET:
        if ((value ^ new_value) & SCRATCH42_UNDEFMASK)
            return true;
        break;
    case BONDOUT_MIRROR0_OFFSET:
        if ((value ^ new_value) & BONDOUT_MIRROR0_UNDEFMASK)
            return true;
        break;
    case BONDOUT_MIRROR1_OFFSET:
        if ((value ^ new_value) & BONDOUT_MIRROR1_UNDEFMASK)
            return true;
        break;
    case BONDOUT_MIRROR2_OFFSET:
        if ((value ^ new_value) & BONDOUT_MIRROR2_UNDEFMASK)
            return true;
        break;
    case SYS_33V_EN_OFFSET:
        if ((value ^ new_value) & SYS_33V_EN_UNDEFMASK)
            return true;
        break;
    case BONDOUT_MIRROR_ACCESS_OFFSET:
        if ((value ^ new_value) & BONDOUT_MIRROR_ACCESS_UNDEFMASK)
            return true;
        break;
    case GATE_OFFSET:
        if ((value ^ new_value) & GATE_UNDEFMASK)
            return true;
        break;

    default:
        break;
    }

    return false;
}

QString PmcDev::get_register_name(const log_entry &entry) const
{
    switch (entry.offset) {
    case CNTRL_OFFSET:
        return QString("CNTRL");
    case SEC_DISABLE_OFFSET:
        return QString("SEC_DISABLE");
    case PMC_SWRST_OFFSET:
        return QString("PMC_SWRST");
    case WAKE_MASK_OFFSET:
        return QString("WAKE_MASK");
    case WAKE_LVL_OFFSET:
        return QString("WAKE_LVL");
    case WAKE_STATUS_OFFSET:
        return QString("WAKE_STATUS");
    case SW_WAKE_STATUS_OFFSET:
        return QString("SW_WAKE_STATUS");
    case DPD_PADS_ORIDE_OFFSET:
        return QString("DPD_PADS_ORIDE");
    case DPD_SAMPLE_OFFSET:
        return QString("DPD_SAMPLE");
    case DPD_ENABLE_OFFSET:
        return QString("DPD_ENABLE");
    case PWRGATE_TIMER_OFF_OFFSET:
        return QString("PWRGATE_TIMER_OFF");
    case PWRGATE_TIMER_ON_OFFSET:
        return QString("PWRGATE_TIMER_ON");
    case PWRGATE_TOGGLE_OFFSET:
        return QString("PWRGATE_TOGGLE");
    case REMOVE_CLAMPING_CMD_OFFSET:
        return QString("REMOVE_CLAMPING_CMD");
    case PWRGATE_STATUS_OFFSET:
        return QString("PWRGATE_STATUS");
    case PWRGOOD_TIMER_OFFSET:
        return QString("PWRGOOD_TIMER");
    case BLINK_TIMER_OFFSET:
        return QString("BLINK_TIMER");
    case NO_IOPOWER_OFFSET:
        return QString("NO_IOPOWER");
    case PWR_DET_OFFSET:
        return QString("PWR_DET");
    case PWR_DET_LATCH_OFFSET:
        return QString("PWR_DET_LATCH");
    case SCRATCH0_OFFSET:
        return QString("SCRATCH0");
    case SCRATCH1_OFFSET:
        return QString("SCRATCH1");
    case SCRATCH2_OFFSET:
        return QString("SCRATCH2");
    case SCRATCH3_OFFSET:
        return QString("SCRATCH3");
    case SCRATCH4_OFFSET:
        return QString("SCRATCH4");
    case SCRATCH5_OFFSET:
        return QString("SCRATCH5");
    case SCRATCH6_OFFSET:
        return QString("SCRATCH6");
    case SCRATCH7_OFFSET:
        return QString("SCRATCH7");
    case SCRATCH8_OFFSET:
        return QString("SCRATCH8");
    case SCRATCH9_OFFSET:
        return QString("SCRATCH9");
    case SCRATCH10_OFFSET:
        return QString("SCRATCH10");
    case SCRATCH11_OFFSET:
        return QString("SCRATCH11");
    case SCRATCH12_OFFSET:
        return QString("SCRATCH12");
    case SCRATCH13_OFFSET:
        return QString("SCRATCH13");
    case SCRATCH14_OFFSET:
        return QString("SCRATCH14");
    case SCRATCH15_OFFSET:
        return QString("SCRATCH15");
    case SCRATCH16_OFFSET:
        return QString("SCRATCH16");
    case SCRATCH17_OFFSET:
        return QString("SCRATCH17");
    case SCRATCH18_OFFSET:
        return QString("SCRATCH18");
    case SCRATCH19_OFFSET:
        return QString("SCRATCH19");
    case SCRATCH20_OFFSET:
        return QString("SCRATCH20");
    case SCRATCH21_OFFSET:
        return QString("SCRATCH21");
    case SCRATCH22_OFFSET:
        return QString("SCRATCH22");
    case SCRATCH23_OFFSET:
        return QString("SCRATCH23");
    case SECURE_SCRATCH0_OFFSET:
        return QString("SECURE_SCRATCH0");
    case SECURE_SCRATCH1_OFFSET:
        return QString("SECURE_SCRATCH1");
    case SECURE_SCRATCH2_OFFSET:
        return QString("SECURE_SCRATCH2");
    case SECURE_SCRATCH3_OFFSET:
        return QString("SECURE_SCRATCH3");
    case SECURE_SCRATCH4_OFFSET:
        return QString("SECURE_SCRATCH4");
    case SECURE_SCRATCH5_OFFSET:
        return QString("SECURE_SCRATCH5");
    case CPUPWRGOOD_TIMER_OFFSET:
        return QString("CPUPWRGOOD_TIMER");
    case CPUPWROFF_TIMER_OFFSET:
        return QString("CPUPWROFF_TIMER");
    case PG_MASK_OFFSET:
        return QString("PG_MASK");
    case PG_MASK_1_OFFSET:
        return QString("PG_MASK_1");
    case AUTO_WAKE_LVL_OFFSET:
        return QString("AUTO_WAKE_LVL");
    case AUTO_WAKE_LVL_MASK_OFFSET:
        return QString("AUTO_WAKE_LVL_MASK");
    case WAKE_DELAY_OFFSET:
        return QString("WAKE_DELAY");
    case PWR_DET_VAL_OFFSET:
        return QString("PWR_DET_VAL");
    case DDR_PWR_OFFSET:
        return QString("DDR_PWR");
    case USB_DEBOUNCE_DEL_OFFSET:
        return QString("USB_DEBOUNCE_DEL");
    case USB_AO_OFFSET:
        return QString("USB_AO");
    case CRYPTO_OP_OFFSET:
        return QString("CRYPTO_OP");
    case PLLP_WB0_OVERRIDE_OFFSET:
        return QString("PLLP_WB0_OVERRIDE");
    case SCRATCH24_OFFSET:
        return QString("SCRATCH24");
    case SCRATCH25_OFFSET:
        return QString("SCRATCH25");
    case SCRATCH26_OFFSET:
        return QString("SCRATCH26");
    case SCRATCH27_OFFSET:
        return QString("SCRATCH27");
    case SCRATCH28_OFFSET:
        return QString("SCRATCH28");
    case SCRATCH29_OFFSET:
        return QString("SCRATCH29");
    case SCRATCH30_OFFSET:
        return QString("SCRATCH30");
    case SCRATCH31_OFFSET:
        return QString("SCRATCH31");
    case SCRATCH32_OFFSET:
        return QString("SCRATCH32");
    case SCRATCH33_OFFSET:
        return QString("SCRATCH33");
    case SCRATCH34_OFFSET:
        return QString("SCRATCH34");
    case SCRATCH35_OFFSET:
        return QString("SCRATCH35");
    case SCRATCH36_OFFSET:
        return QString("SCRATCH36");
    case SCRATCH37_OFFSET:
        return QString("SCRATCH37");
    case SCRATCH38_OFFSET:
        return QString("SCRATCH38");
    case SCRATCH39_OFFSET:
        return QString("SCRATCH39");
    case SCRATCH40_OFFSET:
        return QString("SCRATCH40");
    case SCRATCH41_OFFSET:
        return QString("SCRATCH41");
    case SCRATCH42_OFFSET:
        return QString("SCRATCH42");
    case BONDOUT_MIRROR0_OFFSET:
        return QString("BONDOUT_MIRROR0");
    case BONDOUT_MIRROR1_OFFSET:
        return QString("BONDOUT_MIRROR1");
    case BONDOUT_MIRROR2_OFFSET:
        return QString("BONDOUT_MIRROR2");
    case SYS_33V_EN_OFFSET:
        return QString("SYS_33V_EN");
    case BONDOUT_MIRROR_ACCESS_OFFSET:
        return QString("BONDOUT_MIRROR_ACCESS");
    case GATE_OFFSET:
        return QString("GATE");

    default:
        break;
    }

    qDebug() << QString().sprintf("PMC: %s: Ooops... 0x%x", __func__, entry.offset);

    return QString().sprintf("Ooops... @0x%X", entry.offset);
}

void PmcDev::fill_bits_details(const u_int32_t &offset,
                                      const u_int32_t &value, const u_int32_t &new_value)
{
    switch (offset) {
    case CNTRL_OFFSET:
        fill_cntrl_details(value, new_value);
        break;
    case SEC_DISABLE_OFFSET:
        fill_sec_disable_details(value, new_value);
        break;
    case PMC_SWRST_OFFSET:
        fill_pmc_swrst_details(value, new_value);
        break;
    case WAKE_MASK_OFFSET:
        fill_wake_mask_details(value, new_value);
        break;
    case WAKE_LVL_OFFSET:
        fill_wake_lvl_details(value, new_value);
        break;
    case WAKE_STATUS_OFFSET:
        fill_wake_status_details(value, new_value);
        break;
    case SW_WAKE_STATUS_OFFSET:
        fill_sw_wake_status_details(value, new_value);
        break;
    case DPD_PADS_ORIDE_OFFSET:
        fill_dpd_pads_oride_details(value, new_value);
        break;
    case DPD_SAMPLE_OFFSET:
        fill_dpd_sample_details(value, new_value);
        break;
    case DPD_ENABLE_OFFSET:
        fill_dpd_enable_details(value, new_value);
        break;
    case PWRGATE_TIMER_OFF_OFFSET:
        fill_pwrgate_timer_off_details(value, new_value);
        break;
    case PWRGATE_TIMER_ON_OFFSET:
        fill_pwrgate_timer_on_details(value, new_value);
        break;
    case PWRGATE_TOGGLE_OFFSET:
        fill_pwrgate_toggle_details(value, new_value);
        break;
    case REMOVE_CLAMPING_CMD_OFFSET:
        fill_remove_clamping_cmd_details(value, new_value);
        break;
    case PWRGATE_STATUS_OFFSET:
        fill_pwrgate_status_details(value, new_value);
        break;
    case PWRGOOD_TIMER_OFFSET:
        fill_pwrgood_timer_details(value, new_value);
        break;
    case BLINK_TIMER_OFFSET:
        fill_blink_timer_details(value, new_value);
        break;
    case NO_IOPOWER_OFFSET:
        fill_no_iopower_details(value, new_value);
        break;
    case PWR_DET_OFFSET:
        fill_pwr_det_details(value, new_value);
        break;
    case PWR_DET_LATCH_OFFSET:
        fill_pwr_det_latch_details(value, new_value);
        break;
    case SCRATCH0_OFFSET:
        fill_scratch0_details(value, new_value);
        break;
    case SCRATCH1_OFFSET:
        fill_scratch1_details(value, new_value);
        break;
    case SCRATCH2_OFFSET:
        fill_scratch2_details(value, new_value);
        break;
    case SCRATCH3_OFFSET:
        fill_scratch3_details(value, new_value);
        break;
    case SCRATCH4_OFFSET:
        fill_scratch4_details(value, new_value);
        break;
    case SCRATCH5_OFFSET:
        fill_scratch5_details(value, new_value);
        break;
    case SCRATCH6_OFFSET:
        fill_scratch6_details(value, new_value);
        break;
    case SCRATCH7_OFFSET:
        fill_scratch7_details(value, new_value);
        break;
    case SCRATCH8_OFFSET:
        fill_scratch8_details(value, new_value);
        break;
    case SCRATCH9_OFFSET:
        fill_scratch9_details(value, new_value);
        break;
    case SCRATCH10_OFFSET:
        fill_scratch10_details(value, new_value);
        break;
    case SCRATCH11_OFFSET:
        fill_scratch11_details(value, new_value);
        break;
    case SCRATCH12_OFFSET:
        fill_scratch12_details(value, new_value);
        break;
    case SCRATCH13_OFFSET:
        fill_scratch13_details(value, new_value);
        break;
    case SCRATCH14_OFFSET:
        fill_scratch14_details(value, new_value);
        break;
    case SCRATCH15_OFFSET:
        fill_scratch15_details(value, new_value);
        break;
    case SCRATCH16_OFFSET:
        fill_scratch16_details(value, new_value);
        break;
    case SCRATCH17_OFFSET:
        fill_scratch17_details(value, new_value);
        break;
    case SCRATCH18_OFFSET:
        fill_scratch18_details(value, new_value);
        break;
    case SCRATCH19_OFFSET:
        fill_scratch19_details(value, new_value);
        break;
    case SCRATCH20_OFFSET:
        fill_scratch20_details(value, new_value);
        break;
    case SCRATCH21_OFFSET:
        fill_scratch21_details(value, new_value);
        break;
    case SCRATCH22_OFFSET:
        fill_scratch22_details(value, new_value);
        break;
    case SCRATCH23_OFFSET:
        fill_scratch23_details(value, new_value);
        break;
    case SECURE_SCRATCH0_OFFSET:
        fill_secure_scratch0_details(value, new_value);
        break;
    case SECURE_SCRATCH1_OFFSET:
        fill_secure_scratch1_details(value, new_value);
        break;
    case SECURE_SCRATCH2_OFFSET:
        fill_secure_scratch2_details(value, new_value);
        break;
    case SECURE_SCRATCH3_OFFSET:
        fill_secure_scratch3_details(value, new_value);
        break;
    case SECURE_SCRATCH4_OFFSET:
        fill_secure_scratch4_details(value, new_value);
        break;
    case SECURE_SCRATCH5_OFFSET:
        fill_secure_scratch5_details(value, new_value);
        break;
    case CPUPWRGOOD_TIMER_OFFSET:
        fill_cpupwrgood_timer_details(value, new_value);
        break;
    case CPUPWROFF_TIMER_OFFSET:
        fill_cpupwroff_timer_details(value, new_value);
        break;
    case PG_MASK_OFFSET:
        fill_pg_mask_details(value, new_value);
        break;
    case PG_MASK_1_OFFSET:
        fill_pg_mask_1_details(value, new_value);
        break;
    case AUTO_WAKE_LVL_OFFSET:
        fill_auto_wake_lvl_details(value, new_value);
        break;
    case AUTO_WAKE_LVL_MASK_OFFSET:
        fill_auto_wake_lvl_mask_details(value, new_value);
        break;
    case WAKE_DELAY_OFFSET:
        fill_wake_delay_details(value, new_value);
        break;
    case PWR_DET_VAL_OFFSET:
        fill_pwr_det_val_details(value, new_value);
        break;
    case DDR_PWR_OFFSET:
        fill_ddr_pwr_details(value, new_value);
        break;
    case USB_DEBOUNCE_DEL_OFFSET:
        fill_usb_debounce_del_details(value, new_value);
        break;
    case USB_AO_OFFSET:
        fill_usb_ao_details(value, new_value);
        break;
    case CRYPTO_OP_OFFSET:
        fill_crypto_op_details(value, new_value);
        break;
    case PLLP_WB0_OVERRIDE_OFFSET:
        fill_pllp_wb0_override_details(value, new_value);
        break;
    case SCRATCH24_OFFSET:
        fill_scratch24_details(value, new_value);
        break;
    case SCRATCH25_OFFSET:
        fill_scratch25_details(value, new_value);
        break;
    case SCRATCH26_OFFSET:
        fill_scratch26_details(value, new_value);
        break;
    case SCRATCH27_OFFSET:
        fill_scratch27_details(value, new_value);
        break;
    case SCRATCH28_OFFSET:
        fill_scratch28_details(value, new_value);
        break;
    case SCRATCH29_OFFSET:
        fill_scratch29_details(value, new_value);
        break;
    case SCRATCH30_OFFSET:
        fill_scratch30_details(value, new_value);
        break;
    case SCRATCH31_OFFSET:
        fill_scratch31_details(value, new_value);
        break;
    case SCRATCH32_OFFSET:
        fill_scratch32_details(value, new_value);
        break;
    case SCRATCH33_OFFSET:
        fill_scratch33_details(value, new_value);
        break;
    case SCRATCH34_OFFSET:
        fill_scratch34_details(value, new_value);
        break;
    case SCRATCH35_OFFSET:
        fill_scratch35_details(value, new_value);
        break;
    case SCRATCH36_OFFSET:
        fill_scratch36_details(value, new_value);
        break;
    case SCRATCH37_OFFSET:
        fill_scratch37_details(value, new_value);
        break;
    case SCRATCH38_OFFSET:
        fill_scratch38_details(value, new_value);
        break;
    case SCRATCH39_OFFSET:
        fill_scratch39_details(value, new_value);
        break;
    case SCRATCH40_OFFSET:
        fill_scratch40_details(value, new_value);
        break;
    case SCRATCH41_OFFSET:
        fill_scratch41_details(value, new_value);
        break;
    case SCRATCH42_OFFSET:
        fill_scratch42_details(value, new_value);
        break;
    case BONDOUT_MIRROR0_OFFSET:
        fill_bondout_mirror0_details(value, new_value);
        break;
    case BONDOUT_MIRROR1_OFFSET:
        fill_bondout_mirror1_details(value, new_value);
        break;
    case BONDOUT_MIRROR2_OFFSET:
        fill_bondout_mirror2_details(value, new_value);
        break;
    case SYS_33V_EN_OFFSET:
        fill_sys_33v_en_details(value, new_value);
        break;
    case BONDOUT_MIRROR_ACCESS_OFFSET:
        fill_bondout_mirror_access_details(value, new_value);
        break;
    case GATE_OFFSET:
        fill_gate_details(value, new_value);
        break;

    default:
        m_bit_details_model.bits.clear();
        break;
    }
}
