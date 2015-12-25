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

#include "mcdev.h"

#include <QDebug>

#define EMEM_CFG_OFFSET 0xC
#define EMEM_CFG_UNDEFMASK 0xFFC00000
union emem_cfg_u {
    struct {
        unsigned int emem_size_kb:22;
        unsigned int undefined_bits_22_31:10;
    };

    u_int32_t reg32;
};

void McDev::fill_emem_cfg_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const emem_cfg_u old_value_t = { .reg32 = value };
    const emem_cfg_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: emem_size_kb:22", "", 22, old_value_t.emem_size_kb, new_value_t.emem_size_kb };
    m_bit_details_model.bits.append(entry);
    entry = { "22: undefined_bits_22_31:10", "", 10, old_value_t.undefined_bits_22_31, new_value_t.undefined_bits_22_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "External memory size (in Kbytes): EMEM_SIZE_KB must be <= (Device size in KB * Number of Devices).\nThis is used to check for DECERR in HW. Only chip spec values are valid. This register needs to be programmed for proper operation.\nExternal memory configuration Register";
}

#define EMEM_ADR_CFG_OFFSET 0x10
#define EMEM_ADR_CFG_UNDEFMASK 0xFCF8FCF8
union emem_adr_cfg_u {
    struct {
        unsigned int emem_colwidth:3;       /* 0 = W7; 1 = W8; 2 = W9; 3 = W10; 4 = W11 */
        unsigned int undefined_bits_3_7:5;
        unsigned int emem_bankwidth:2;      /* 2 = W2; 3 = W3 */
        unsigned int undefined_bits_10_15:6;
        unsigned int emem_devsize:3;        /* 0 = D4 MB; 1 = D8 MB; 2 = D16 MB; 3 = D32 MB; 4 = D64 MB; 5 = D128 MB; 6 = D256 MB; 7 = D512 MB; 8 = D1024 MB; 8 = D1 GB */
        unsigned int undefined_bits_19_23:5;
        unsigned int emem_numdev:2;         /* 0 = N1; 1 = N2 */
        unsigned int undefined_bits_26_31:6;
    };

    u_int32_t reg32;
};

void McDev::fill_emem_adr_cfg_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const emem_adr_cfg_u old_value_t = { .reg32 = value };
    const emem_adr_cfg_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: emem_colwidth:3",
              "0 = W7;\n1 = W8;\n2 = W9;\n3 = W10;\n4 = W11",
              3, old_value_t.emem_colwidth, new_value_t.emem_colwidth };
    m_bit_details_model.bits.append(entry);
    entry = { "03: undefined_bits_3_7:5", "", 5, old_value_t.undefined_bits_3_7, new_value_t.undefined_bits_3_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: emem_bankwidth:2",
              "2 = W2;\n3 = W3",
              2, old_value_t.emem_bankwidth, new_value_t.emem_bankwidth };
    m_bit_details_model.bits.append(entry);
    entry = { "10: undefined_bits_10_15:6", "", 6, old_value_t.undefined_bits_10_15, new_value_t.undefined_bits_10_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: emem_devsize:3",
              "0 = D4 MB;\n1 = D8 MB;\n2 = D16 MB;\n3 = D32 MB;\n4 = D64 MB;\n5 = D128 MB;\n6 = D256 MB;\n7 = D512 MB;\n8 = D1024 MB;\n8 = D1 GB",
              3, old_value_t.emem_devsize, new_value_t.emem_devsize };
    m_bit_details_model.bits.append(entry);
    entry = { "19: undefined_bits_19_23:5", "", 5, old_value_t.undefined_bits_19_23, new_value_t.undefined_bits_19_23 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: emem_numdev:2",
              "0 = N1;\n1 = N2",
              2, old_value_t.emem_numdev, new_value_t.emem_numdev };
    m_bit_details_model.bits.append(entry);
    entry = { "26: undefined_bits_26_31:6", "", 6, old_value_t.undefined_bits_26_31, new_value_t.undefined_bits_26_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "This is used to specify the DRAM parameters. MC will use these parameters to derive device, row, bank, column values to EMC.\nExternal memory address configuration Register";
}

#define EMEM_ARB_CFG0_OFFSET 0x14
#define EMEM_ARB_CFG0_UNDEFMASK 0x8FC00000
union emem_arb_cfg0_u {
    struct {
        unsigned int emem_rwcnt_th:8;
        unsigned int emem_wrcnt_th:8;
        unsigned int emem_sp_max_grant_overall:6;
        unsigned int undefined_bits_22_27:6;
        unsigned int emem_clear_sp_on_autopc:1;/* 0 = DISABLE; 1 = ENABLE; 0 = DISABLED 1 = ENABLED */
        unsigned int emem_clear_ap_prev_spreq:1;/* 0 = DISABLE; 1 = ENABLE; 0 = DISABLED 1 = ENABLED */
        unsigned int emem_noblock_by_bank_when_hp:1;/* 0 = DISABLE 1 = ENABLE 0 = DISABLED 1 = ENABLED */
        unsigned int undefined_bit_31:1;
    };

    u_int32_t reg32;
};

void McDev::fill_emem_arb_cfg0_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const emem_arb_cfg0_u old_value_t = { .reg32 = value };
    const emem_arb_cfg0_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: emem_rwcnt_th:8", "", 8, old_value_t.emem_rwcnt_th, new_value_t.emem_rwcnt_th };
    m_bit_details_model.bits.append(entry);
    entry = { "08: emem_wrcnt_th:8", "", 8, old_value_t.emem_wrcnt_th, new_value_t.emem_wrcnt_th };
    m_bit_details_model.bits.append(entry);
    entry = { "16: emem_sp_max_grant_overall:6", "", 6, old_value_t.emem_sp_max_grant_overall, new_value_t.emem_sp_max_grant_overall };
    m_bit_details_model.bits.append(entry);
    entry = { "22: undefined_bits_22_27:6", "", 6, old_value_t.undefined_bits_22_27, new_value_t.undefined_bits_22_27 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: emem_clear_sp_on_autopc:1",
              "0 = DISABLE;\n1 = ENABLE;\n0 = DISABLED\n1 = ENABLED",
              1, old_value_t.emem_clear_sp_on_autopc, new_value_t.emem_clear_sp_on_autopc };
    m_bit_details_model.bits.append(entry);
    entry = { "29: emem_clear_ap_prev_spreq:1",
              "0 = DISABLE;\n1 = ENABLE;\n0 = DISABLED\n1 = ENABLED",
              1, old_value_t.emem_clear_ap_prev_spreq, new_value_t.emem_clear_ap_prev_spreq };
    m_bit_details_model.bits.append(entry);
    entry = { "30: emem_noblock_by_bank_when_hp:1",
              "0 = DISABLE\n1 = ENABLE\n0 = DISABLED\n1 = ENABLED",
              1, old_value_t.emem_noblock_by_bank_when_hp, new_value_t.emem_noblock_by_bank_when_hp };
    m_bit_details_model.bits.append(entry);
    entry = { "31: undefined_bit_31:1", "", 1, old_value_t.undefined_bit_31, new_value_t.undefined_bit_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "The read/write and write/read counter thresholds are used to generate the read/write switch for the DRAM arbiter when compared to the read/write counter. The counter is incremented every cycle and cleared when the arbitration winner changes from read to write or write to read.\nSame-Page consecutive transactions maximum count limits the maximum number of consecutive same-page-based wins the arbiter will grant to the same client before masking that client's same-page indication for one arbitration cycle.\n The value of this register is added to EMEM_SP_MAX_GRANT to ensure that the gross-masking cannot interfere with the bank-contention masking. Value of 0 disables. If not disabled, value should be greater than 1.\nThe no block by bank when high-priority is requesting field is used to disable logic that blocks, by bank, non-HP requests from arbitrating when an HP request is pending. (In other words, when this bit is ENABLED, the logic that blocks non-HP requests is DISABLED.)\nBoot requirements: This arbitration configuration register should be parameterized in the BCT and written by the OS during coldboot and warmboot.\nExternal memory arbiter configuration 0";
}

#define EMEM_ARB_CFG1_OFFSET 0x18
#define EMEM_ARB_CFG1_UNDEFMASK 0xC0C00820
union emem_arb_cfg1_u {
    struct {
        unsigned int emem_rcl_mask:5;       /* 0 = NONE; 63 = ALL */
        unsigned int undefined_bit_5:1;
        unsigned int emem_wcl_mask:5;       /* 0 = NONE; 63 = ALL */
        unsigned int undefined_bit_11:1;
        unsigned int emem_norwswitch_bkblock:1;/* 0 = DISABLE; 1 = ENABLE; 0 = DISABLED 1 = ENABLED */
        unsigned int emem_nowrswitch_bkblock:1;/* 0 = DISABLE; 1 = ENABLE; 0 = DISABLED 1 = ENABLED */
        unsigned int emem_rwswitch_rwinexpired:1;/* 0 = DISABLE; 1 = ENABLE; 0 = DISABLED 1 = ENABLED */
        unsigned int emem_wrswitch_wwinexpired:1;/* 0 = DISABLE; 1 = ENABLE; 0 = DISABLED 1 = ENABLED */
        unsigned int emem_sp_max_grant:6;
        unsigned int undefined_bits_22_23:2;
        unsigned int emem_sp_max_grant_rw:6;
        unsigned int undefined_bits_30_31:2;
    };

    u_int32_t reg32;
};

void McDev::fill_emem_arb_cfg1_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const emem_arb_cfg1_u old_value_t = { .reg32 = value };
    const emem_arb_cfg1_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: emem_rcl_mask:5",
              "0 = NONE;\n63 = ALL",
              5, old_value_t.emem_rcl_mask, new_value_t.emem_rcl_mask };
    m_bit_details_model.bits.append(entry);
    entry = { "05: undefined_bit_5:1", "", 1, old_value_t.undefined_bit_5, new_value_t.undefined_bit_5 };
    m_bit_details_model.bits.append(entry);
    entry = { "06: emem_wcl_mask:5",
              "0 = NONE;\n63 = ALL",
              5, old_value_t.emem_wcl_mask, new_value_t.emem_wcl_mask };
    m_bit_details_model.bits.append(entry);
    entry = { "11: undefined_bit_11:1", "", 1, old_value_t.undefined_bit_11, new_value_t.undefined_bit_11 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: emem_norwswitch_bkblock:1",
              "0 = DISABLE;\n1 = ENABLE;\n0 = DISABLED\n1 = ENABLED",
              1, old_value_t.emem_norwswitch_bkblock, new_value_t.emem_norwswitch_bkblock };
    m_bit_details_model.bits.append(entry);
    entry = { "13: emem_nowrswitch_bkblock:1",
              "0 = DISABLE;\n1 = ENABLE;\n0 = DISABLED\n1 = ENABLED",
              1, old_value_t.emem_nowrswitch_bkblock, new_value_t.emem_nowrswitch_bkblock };
    m_bit_details_model.bits.append(entry);
    entry = { "14: emem_rwswitch_rwinexpired:1",
              "0 = DISABLE;\n1 = ENABLE;\n0 = DISABLED\n1 = ENABLED",
              1, old_value_t.emem_rwswitch_rwinexpired, new_value_t.emem_rwswitch_rwinexpired };
    m_bit_details_model.bits.append(entry);
    entry = { "15: emem_wrswitch_wwinexpired:1",
              "0 = DISABLE;\n1 = ENABLE;\n0 = DISABLED\n1 = ENABLED",
              1, old_value_t.emem_wrswitch_wwinexpired, new_value_t.emem_wrswitch_wwinexpired };
    m_bit_details_model.bits.append(entry);
    entry = { "16: emem_sp_max_grant:6", "", 6, old_value_t.emem_sp_max_grant, new_value_t.emem_sp_max_grant };
    m_bit_details_model.bits.append(entry);
    entry = { "22: undefined_bits_22_23:2", "", 2, old_value_t.undefined_bits_22_23, new_value_t.undefined_bits_22_23 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: emem_sp_max_grant_rw:6", "", 6, old_value_t.emem_sp_max_grant_rw, new_value_t.emem_sp_max_grant_rw };
    m_bit_details_model.bits.append(entry);
    entry = { "30: undefined_bits_30_31:2", "", 2, old_value_t.undefined_bits_30_31, new_value_t.undefined_bits_30_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "The read/write client priority masks are used to mask the read/write winner client priority vector before comparison. The priority vector is made of the following fields:\n    * the 3 most-significant bits of the priority vector from arbitration\n    * whether this winner is in the same page\n    * a bit indicating whether the read/write window has expired\nWhich are computed into:\n priwin = {hp ? 3'h7 : ({timeout,bw}+fpri[1:0])}\n privec = {priwin[2:1], spwin, priwin[0], winexpire}\n for the purposes of this mask\n The lowest significant bit is controlled by the EMEM_WRSWITCH_WWINEXPIRED and EMEM_RWSWITCH_RWINEXPIRED fields described below.\nThe no-read/write (write/read) switch on bank-blocked requests fields are used to allow/disallow read/write switching when there are requests of the current window type blocked by the bank counters.\nThe read/write switch is used to make the arbiter switch from reads to writes once the read window has expired and there are read and write requests with equal priority. Otherwise the arbiter would stick with reads as it is better for DRAM bandwidth utilization. Switching is usually the desired behavior.\nThe write/read switch is used to make the arbiter switch from writes to reads once the write window has expired and there are read and write requests with equal priority. Otherwise the arbiter would stick with writes as it is better for DRAM bandwidth utilization. Switching is usually the desired behavior.\nSame-Page consecutive transactions maximum count limits, when bank-contention is detected among two or more clients, the maximum number of consecutive same-page-based wins the arbiter will grant to the same client before masking that client's same-page indication for one arbitration cycle.\nValue of 0 disables.\nValue of 16 approximates (in certain situations) the behavior of earlier architectures where bank==adr[7:6].\nSame-page consecutive transactions maximum count for read/write arbiter limits the maximum number of consecutive same-page-based wins the r/w arbiter will grant after the r/w window has expired before masking the expired window's spwin bit from the r/w arbiter priority vector.\nValue of 0 disables.\nBoot requirements: This arbitration configuration register should be parameterized in the BCT and written by the OS during coldboot and warmboot.\nExternal memory arbiter configuration 1";
}

#define EMEM_ARB_CFG2_OFFSET 0x1C
#define EMEM_ARB_CFG2_UNDEFMASK 0xC0C0C0C0
union emem_arb_cfg2_u {
    struct {
        unsigned int emem_bankcnt_rd_th:6;
        unsigned int undefined_bits_6_7:2;
        unsigned int emem_bankcnt_nsp_rd_th:6;
        unsigned int undefined_bits_14_15:2;
        unsigned int emem_bankcnt_wr_th:6;
        unsigned int undefined_bits_22_23:2;
        unsigned int emem_bankcnt_nsp_wr_th:6;
        unsigned int undefined_bits_30_31:2;
    };

    u_int32_t reg32;
};

void McDev::fill_emem_arb_cfg2_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const emem_arb_cfg2_u old_value_t = { .reg32 = value };
    const emem_arb_cfg2_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: emem_bankcnt_rd_th:6", "", 6, old_value_t.emem_bankcnt_rd_th, new_value_t.emem_bankcnt_rd_th };
    m_bit_details_model.bits.append(entry);
    entry = { "06: undefined_bits_6_7:2", "", 2, old_value_t.undefined_bits_6_7, new_value_t.undefined_bits_6_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: emem_bankcnt_nsp_rd_th:6", "", 6, old_value_t.emem_bankcnt_nsp_rd_th, new_value_t.emem_bankcnt_nsp_rd_th };
    m_bit_details_model.bits.append(entry);
    entry = { "14: undefined_bits_14_15:2", "", 2, old_value_t.undefined_bits_14_15, new_value_t.undefined_bits_14_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: emem_bankcnt_wr_th:6", "", 6, old_value_t.emem_bankcnt_wr_th, new_value_t.emem_bankcnt_wr_th };
    m_bit_details_model.bits.append(entry);
    entry = { "22: undefined_bits_22_23:2", "", 2, old_value_t.undefined_bits_22_23, new_value_t.undefined_bits_22_23 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: emem_bankcnt_nsp_wr_th:6", "", 6, old_value_t.emem_bankcnt_nsp_wr_th, new_value_t.emem_bankcnt_nsp_wr_th };
    m_bit_details_model.bits.append(entry);
    entry = { "30: undefined_bits_30_31:2", "", 2, old_value_t.undefined_bits_30_31, new_value_t.undefined_bits_30_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "The bank counter threshold is used to block non same-page requests until the number of cycles since the last arbitration bank winner was a (read|write) to the requested bank has reached the threshold. This should mimic tRAS.\nThe non same-page bank counter threshold is used to block non same-page requests until the number of cycles since the last arbitration bank winner was a (read|write) to the requested bank and it changed the same page, has reached the threshold.\nThe bank counter thresholds are incremented only when the rest of the memory controller pipeline after the arbiter is ready, so that they are kept in sync with the requests sent to the external memory controller. This should mimic (tRAS+tRP).\nThere is a one-cycle imprecision on number of cycles related to the bank counter thresholds.\nBoot requirements: This arbitration configuration register should be parameterized in the BCT and written by the OS during coldboot and warmboot.\nExternal memory arbiter config 2";
}

#define GART_CONFIG_OFFSET 0x24
#define GART_CONFIG_UNDEFMASK 0xFFFFFFFE
union gart_config_u {
    struct {
        unsigned int gart_enable:1;         /* 0 = DISABLE; 1 = ENABLE */
        unsigned int undefined_bits_1_31:31;
    };

    u_int32_t reg32;
};

void McDev::fill_gart_config_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const gart_config_u old_value_t = { .reg32 = value };
    const gart_config_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: gart_enable:1",
              "0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.gart_enable, new_value_t.gart_enable };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_31:31", "", 31, old_value_t.undefined_bits_1_31, new_value_t.undefined_bits_1_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "GART_CONFIG contains a single bit enable for the GART functionality. When DISABLED, the GART passes through addresses without modification. Because the address-bound check occurs after GART translation, an unmodified GART address will be treated as-out-of-bounds by the MC.\nWhen ENABLED, the GART remaps addresses as specified by the GART entries.";
}

#define GART_ENTRY_ADDR_OFFSET 0x28
#define GART_ENTRY_ADDR_UNDEFMASK 0xFE000FFF
union gart_entry_addr_u {
    struct {
        unsigned int undefined_bits_0_11:12;
        unsigned int gart_entry_addr_table_addr:13;
        unsigned int undefined_bits_25_31:7;
    };

    u_int32_t reg32;
};

void McDev::fill_gart_entry_addr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const gart_entry_addr_u old_value_t = { .reg32 = value };
    const gart_entry_addr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_11:12", "", 12, old_value_t.undefined_bits_0_11, new_value_t.undefined_bits_0_11 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: gart_entry_addr_table_addr:13", "", 13, old_value_t.gart_entry_addr_table_addr, new_value_t.gart_entry_addr_table_addr };
    m_bit_details_model.bits.append(entry);
    entry = { "25: undefined_bits_25_31:7", "", 7, old_value_t.undefined_bits_25_31, new_value_t.undefined_bits_25_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "GART_ENTRY_ADDR is one of two registers used to access the GART table. The GART_ENTRY_ADDR value defines which entry will be read or written by accesses to the GART_ENTRY_DATA register.";
}

#define GART_ENTRY_DATA_OFFSET 0x2C
#define GART_ENTRY_DATA_UNDEFMASK 0x00000FFF
union gart_entry_data_u {
    struct {
        unsigned int undefined_bits_0_11:12;
        unsigned int gart_entry_data_phys_addr:19;
        unsigned int gart_entry_data_phys_addr_valid:1;
    };

    u_int32_t reg32;
};

void McDev::fill_gart_entry_data_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const gart_entry_data_u old_value_t = { .reg32 = value };
    const gart_entry_data_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_11:12", "", 12, old_value_t.undefined_bits_0_11, new_value_t.undefined_bits_0_11 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: gart_entry_data_phys_addr:19", "", 19, old_value_t.gart_entry_data_phys_addr, new_value_t.gart_entry_data_phys_addr };
    m_bit_details_model.bits.append(entry);
    entry = { "31: gart_entry_data_phys_addr_valid:1", "", 1, old_value_t.gart_entry_data_phys_addr_valid, new_value_t.gart_entry_data_phys_addr_valid };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "GART_ENTRY_DATA is one of two registers used to access the GART table. A read of the GART_ENTRY_DATA register returns the GART entry addressed by GART_ENTRY_ADDR.\n Similarly, a write to the GART_ENTRY_DATA register updates the GART entry addressed by GART_ENTRY_ADDR.";
}

#define GART_ERROR_REQ_OFFSET 0x30
#define GART_ERROR_REQ_UNDEFMASK 0xFFFFFF80
union gart_error_req_u {
    struct {
        unsigned int gart_error_direction:1;/* 0 = READ; 1 = WRITE */
        unsigned int gart_error_client_id:6;
        unsigned int undefined_bits_7_31:25;
    };

    u_int32_t reg32;
};

void McDev::fill_gart_error_req_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const gart_error_req_u old_value_t = { .reg32 = value };
    const gart_error_req_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: gart_error_direction:1",
              "0 = READ;\n1 = WRITE",
              1, old_value_t.gart_error_direction, new_value_t.gart_error_direction };
    m_bit_details_model.bits.append(entry);
    entry = { "01: gart_error_client_id:6", "", 6, old_value_t.gart_error_client_id, new_value_t.gart_error_client_id };
    m_bit_details_model.bits.append(entry);
    entry = { "07: undefined_bits_7_31:25", "", 25, old_value_t.undefined_bits_7_31, new_value_t.undefined_bits_7_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "When any client attempts to access an invalid GART page for reading or writing, an INVALID_GART_PAGE_INT occurs and the attributes of the first such request are stored in GART_ERROR_REQ.\nThe global memory client IDs are defined as follows:\nTable 51 Global Memory Client IDs\nCLIENT\n ID\n UNIT\ncbr_display0a\n 0\n dc\ncbr_display0ab\n 1\n dcb\ncbr_display0b\n 2\n dc\ncbr_display0bb\n 3\n dcb\ncbr_display0c\n 4\n dc\ncbr_display0cb\n 5\n dcb\nCLIENT\n ID\n UNIT\ncbr_display1b\n 6\n dc\ncbr_display1bb\n 7\n dcb\ncbr_eppup\n 8\n epp\ncbr_g2pr\n 9\n g2\ncbr_g2sr\n 10\n g2\ncbr_mpeunifbr\n 11\n mpeb\ncbr_viruv\n 12\n vi\ncsr_avpcarm7r\n 13\n avpc\ncsr_displayhc\n 14\n dc\ncsr_displayhcb\n 15\n dcb\ncsr_fdcdrd\n 16\n nv\ncsr_g2dr\n 17\n g2\ncsr_host1xdmar\n 18\n hc\ncsr_host1xr\n 19\n hc\ncsr_idxsrd\n 20\n nv\ncsr_mpcorer\n 21\n cpu\ncsr_mpe_ipred\n 22\n mpeb\ncsr_mpeamemrd\n 23\n mpea\ncsr_mpecsrd\n 24\n mpec\ncsr_ppcsahbdmar\n 25\n ppcs\ncsr_ppcsahbslvr\n 26\n ppcs\ncsr_texsrd\n 27\n nv\ncsr_vdebsevr\n 28\n vde\ncsr_vdember\n 29\n vde\ncsr_vdemcer\n 30\n vde\ncsr_vdetper\n 31\n vde\ncbw_eppu\n 32\n epp\nCLIENT\n ID\n UNIT\ncbw_eppv\n 33\n epp\ncbw_eppy\n 34\n epp\ncbw_mpeunifbw\n 35\n mpeb\ncbw_viwsb\n 36\n vi\ncbw_viwu\n 37\n vi\ncbw_viwv\n 38\n vi\ncbw_viwy\n 39\n vi\nccw_g2dw\n 40\n g2\ncsw_avpcarm7w\n 41\n avpc\ncsw_fdcdwr\n 42\n nv\ncsw_host1xw\n 43\n hc\ncsw_ispw\n 44\n isp\ncsw_mpcorew\n 45\n CPU\ncsw_mpecswr\n 46\n mpec\ncsw_ppcsahbdmaw\n 47\n ppcs\ncsw_ppcsahbslvw\n 48\n ppcs\ncsw_vdebsevw\n 49\n vde\ncsw_vdembew\n 50\n vde\ncsw_vdetpmw\n 51\n vde";
}

#define GART_ERROR_ADDR_OFFSET 0x34
#define GART_ERROR_ADDR_UNDEFMASK 0x00000000
union gart_error_addr_u {
    struct {
        unsigned int gart_error_address:32;
    };

    u_int32_t reg32;
};

void McDev::fill_gart_error_addr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const gart_error_addr_u old_value_t = { .reg32 = value };
    const gart_error_addr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: gart_error_address:32", "", 32, old_value_t.gart_error_address, new_value_t.gart_error_address };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "When any client attempts to access an invalid GART page for reading or writing, an INVALID_GART_PAGE_INT occurs and the address of the first such request are stored in GART_ERROR_ADDR.";
}

#define TIMEOUT_CTRL_OFFSET 0x3C
#define TIMEOUT_CTRL_UNDEFMASK 0xFFFFFF87
union timeout_ctrl_u {
    struct {
        unsigned int undefined_bits_0_2:3;
        unsigned int emem_tm_sfactor:3;
        unsigned int tmcredits:1;           /* 0 = FROM_CIF_FIFO; 1 = ONE */
        unsigned int undefined_bits_7_31:25;
    };

    u_int32_t reg32;
};

void McDev::fill_timeout_ctrl_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const timeout_ctrl_u old_value_t = { .reg32 = value };
    const timeout_ctrl_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_2:3", "", 3, old_value_t.undefined_bits_0_2, new_value_t.undefined_bits_0_2 };
    m_bit_details_model.bits.append(entry);
    entry = { "03: emem_tm_sfactor:3", "", 3, old_value_t.emem_tm_sfactor, new_value_t.emem_tm_sfactor };
    m_bit_details_model.bits.append(entry);
    entry = { "06: tmcredits:1",
              "0 = FROM_CIF_FIFO;\n1 = ONE",
              1, old_value_t.tmcredits, new_value_t.tmcredits };
    m_bit_details_model.bits.append(entry);
    entry = { "07: undefined_bits_7_31:25", "", 25, old_value_t.undefined_bits_7_31, new_value_t.undefined_bits_7_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Time-out clock counter scale factors. Reset value is NV_MC_TM_SFACTOR_RESET. A value of zero means that the time-out clock counter is disabled.\n A value of N (non-zero) means that the time-out clock counter is decremented every 2^(N+1) memory cycles. This is used in conjunction with the _TMVAL registers defined below.\nTime-out control Register";
}

#define DECERR_EMEM_OTHERS_STATUS_OFFSET 0x58
#define DECERR_EMEM_OTHERS_STATUS_UNDEFMASK 0x7FFFFFC0
union decerr_emem_others_status_u {
    struct {
        unsigned int decerr_emem_others_id:6;
        unsigned int undefined_bits_6_30:25;
        unsigned int decerr_emem_others_rw:1;/* 0 = READ 1 = WRITE */
    };

    u_int32_t reg32;
};

void McDev::fill_decerr_emem_others_status_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const decerr_emem_others_status_u old_value_t = { .reg32 = value };
    const decerr_emem_others_status_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: decerr_emem_others_id:6", "", 6, old_value_t.decerr_emem_others_id, new_value_t.decerr_emem_others_id };
    m_bit_details_model.bits.append(entry);
    entry = { "06: undefined_bits_6_30:25", "", 25, old_value_t.undefined_bits_6_30, new_value_t.undefined_bits_6_30 };
    m_bit_details_model.bits.append(entry);
    entry = { "31: decerr_emem_others_rw:1",
              "0 = READ\n1 = WRITE",
              1, old_value_t.decerr_emem_others_rw, new_value_t.decerr_emem_others_rw };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "If a decode error from graphics is detected for EMEM, this register records information about this access: read/write indicator and request ID (global client ID assigned by the memory controller).\nThe values remain unchanged until the interrupt is cleared.\nThe global memory client IDs are defined as given in Global Memory Client IDs\nEMEM Decode Error from graphics status Register";
}

#define DECERR_EMEM_OTHERS_ADR_OFFSET 0x5C
#define DECERR_EMEM_OTHERS_ADR_UNDEFMASK 0x00000000
union decerr_emem_others_adr_u {
    struct {
        unsigned int decerr_emem_others_adr:32;
    };

    u_int32_t reg32;
};

void McDev::fill_decerr_emem_others_adr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const decerr_emem_others_adr_u old_value_t = { .reg32 = value };
    const decerr_emem_others_adr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: decerr_emem_others_adr:32", "", 32, old_value_t.decerr_emem_others_adr, new_value_t.decerr_emem_others_adr };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "If a decode error from graphics is detected for EMEM, this register records the request byte address.\nThe value remains unchanged until the interrupt is cleared.\nEMEM Decode Error from graphics Register";
}

#define CLIENT_CTRL_OFFSET 0x100
#define CLIENT_CTRL_UNDEFMASK 0xFFFF8000
union client_ctrl_u {
    struct {
        unsigned int avpc_enable:1;         /* 0 = DISABLE; 1 = ENABLE */
        unsigned int dc_enable:1;           /* 0 = DISABLE; 1 = ENABLE */
        unsigned int dcb_enable:1;          /* 0 = DISABLE; 1 = ENABLE */
        unsigned int epp_enable:1;          /* 0 = DISABLE; 1 = ENABLE */
        unsigned int g2_enable:1;           /* 0 = DISABLE; 1 = ENABLE */
        unsigned int hc_enable:1;           /* 0 = DISABLE; 1 = ENABLE */
        unsigned int isp_enable:1;          /* 0 = DISABLE; 1 = ENABLE */
        unsigned int mpcore_enable:1;       /* 0 = DISABLE; 1 = ENABLE */
        unsigned int mpea_enable:1;         /* 0 = DISABLE; 1 = ENABLE */
        unsigned int mpeb_enable:1;         /* 0 = DISABLE; 1 = ENABLE */
        unsigned int mpec_enable:1;         /* 0 = DISABLE; 1 = ENABLE */
        unsigned int nv_enable:1;           /* 0 = DISABLE; 1 = ENABLE */
        unsigned int ppcs_enable:1;         /* 0 = DISABLE; 1 = ENABLE */
        unsigned int vde_enable:1;          /* 0 = DISABLE; 1 = ENABLE */
        unsigned int vi_enable:1;           /* 0 = DISABLE; 1 = ENABLE */
        unsigned int undefined_bits_15_31:17;
    };

    u_int32_t reg32;
};

void McDev::fill_client_ctrl_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const client_ctrl_u old_value_t = { .reg32 = value };
    const client_ctrl_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: avpc_enable:1",
              "0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.avpc_enable, new_value_t.avpc_enable };
    m_bit_details_model.bits.append(entry);
    entry = { "01: dc_enable:1",
              "0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.dc_enable, new_value_t.dc_enable };
    m_bit_details_model.bits.append(entry);
    entry = { "02: dcb_enable:1",
              "0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.dcb_enable, new_value_t.dcb_enable };
    m_bit_details_model.bits.append(entry);
    entry = { "03: epp_enable:1",
              "0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.epp_enable, new_value_t.epp_enable };
    m_bit_details_model.bits.append(entry);
    entry = { "04: g2_enable:1",
              "0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.g2_enable, new_value_t.g2_enable };
    m_bit_details_model.bits.append(entry);
    entry = { "05: hc_enable:1",
              "0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.hc_enable, new_value_t.hc_enable };
    m_bit_details_model.bits.append(entry);
    entry = { "06: isp_enable:1",
              "0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.isp_enable, new_value_t.isp_enable };
    m_bit_details_model.bits.append(entry);
    entry = { "07: mpcore_enable:1",
              "0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.mpcore_enable, new_value_t.mpcore_enable };
    m_bit_details_model.bits.append(entry);
    entry = { "08: mpea_enable:1",
              "0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.mpea_enable, new_value_t.mpea_enable };
    m_bit_details_model.bits.append(entry);
    entry = { "09: mpeb_enable:1",
              "0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.mpeb_enable, new_value_t.mpeb_enable };
    m_bit_details_model.bits.append(entry);
    entry = { "10: mpec_enable:1",
              "0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.mpec_enable, new_value_t.mpec_enable };
    m_bit_details_model.bits.append(entry);
    entry = { "11: nv_enable:1",
              "0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.nv_enable, new_value_t.nv_enable };
    m_bit_details_model.bits.append(entry);
    entry = { "12: ppcs_enable:1",
              "0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ppcs_enable, new_value_t.ppcs_enable };
    m_bit_details_model.bits.append(entry);
    entry = { "13: vde_enable:1",
              "0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.vde_enable, new_value_t.vde_enable };
    m_bit_details_model.bits.append(entry);
    entry = { "14: vi_enable:1",
              "0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.vi_enable, new_value_t.vi_enable };
    m_bit_details_model.bits.append(entry);
    entry = { "15: undefined_bits_15_31:17", "", 17, old_value_t.undefined_bits_15_31, new_value_t.undefined_bits_15_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Active high. Reset value is enabled. When enabled, the client requests are free to go to arbitration. When disabled, the client requests are blocked before arbitration.\nMemory Client Control Register";
}

#define CLIENT_HOTRESETN_OFFSET 0x104
#define CLIENT_HOTRESETN_UNDEFMASK 0xFFFF8000
union client_hotresetn_u {
    struct {
        unsigned int avpc_hotresetn:1;      /* 0 = ENABLE; 1 = DISABLE */
        unsigned int dc_hotresetn:1;        /* 0 = ENABLE; 1 = DISABLE */
        unsigned int dcb_hotresetn:1;       /* 0 = ENABLE; 1 = DISABLE */
        unsigned int epp_hotresetn:1;       /* 0 = ENABLE; 1 = DISABLE */
        unsigned int g2_hotresetn:1;        /* 0 = ENABLE; 1 = DISABLE */
        unsigned int hc_hotresetn:1;        /* 0 = ENABLE; 1 = DISABLE */
        unsigned int isp_hotresetn:1;       /* 0 = ENABLE; 1 = DISABLE */
        unsigned int mpcore_hotresetn:1;    /* 0 = ENABLE; 1 = DISABLE */
        unsigned int mpea_hotresetn:1;      /* 0 = ENABLE; 1 = DISABLE */
        unsigned int mpeb_hotresetn:1;      /* 0 = ENABLE; 1 = DISABLE */
        unsigned int mpec_hotresetn:1;      /* 0 = ENABLE; 1 = DISABLE */
        unsigned int nv_hotresetn:1;        /* 0= ENABLE; 1 = DISABLE */
        unsigned int ppcs_hotresetn:1;      /* 0 = ENABLE; 1 = DISABLE */
        unsigned int vde_hotresetn:1;       /* 0 = ENABLE; 1 = DISABLE */
        unsigned int vi_hotresetn:1;        /* 0 = ENABLE; 1 = DISABLE */
        unsigned int undefined_bits_15_31:17;
    };

    u_int32_t reg32;
};

void McDev::fill_client_hotresetn_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const client_hotresetn_u old_value_t = { .reg32 = value };
    const client_hotresetn_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: avpc_hotresetn:1",
              "0 = ENABLE;\n1 = DISABLE",
              1, old_value_t.avpc_hotresetn, new_value_t.avpc_hotresetn };
    m_bit_details_model.bits.append(entry);
    entry = { "01: dc_hotresetn:1",
              "0 = ENABLE;\n1 = DISABLE",
              1, old_value_t.dc_hotresetn, new_value_t.dc_hotresetn };
    m_bit_details_model.bits.append(entry);
    entry = { "02: dcb_hotresetn:1",
              "0 = ENABLE;\n1 = DISABLE",
              1, old_value_t.dcb_hotresetn, new_value_t.dcb_hotresetn };
    m_bit_details_model.bits.append(entry);
    entry = { "03: epp_hotresetn:1",
              "0 = ENABLE;\n1 = DISABLE",
              1, old_value_t.epp_hotresetn, new_value_t.epp_hotresetn };
    m_bit_details_model.bits.append(entry);
    entry = { "04: g2_hotresetn:1",
              "0 = ENABLE;\n1 = DISABLE",
              1, old_value_t.g2_hotresetn, new_value_t.g2_hotresetn };
    m_bit_details_model.bits.append(entry);
    entry = { "05: hc_hotresetn:1",
              "0 = ENABLE;\n1 = DISABLE",
              1, old_value_t.hc_hotresetn, new_value_t.hc_hotresetn };
    m_bit_details_model.bits.append(entry);
    entry = { "06: isp_hotresetn:1",
              "0 = ENABLE;\n1 = DISABLE",
              1, old_value_t.isp_hotresetn, new_value_t.isp_hotresetn };
    m_bit_details_model.bits.append(entry);
    entry = { "07: mpcore_hotresetn:1",
              "0 = ENABLE;\n1 = DISABLE",
              1, old_value_t.mpcore_hotresetn, new_value_t.mpcore_hotresetn };
    m_bit_details_model.bits.append(entry);
    entry = { "08: mpea_hotresetn:1",
              "0 = ENABLE;\n1 = DISABLE",
              1, old_value_t.mpea_hotresetn, new_value_t.mpea_hotresetn };
    m_bit_details_model.bits.append(entry);
    entry = { "09: mpeb_hotresetn:1",
              "0 = ENABLE;\n1 = DISABLE",
              1, old_value_t.mpeb_hotresetn, new_value_t.mpeb_hotresetn };
    m_bit_details_model.bits.append(entry);
    entry = { "10: mpec_hotresetn:1",
              "0 = ENABLE;\n1 = DISABLE",
              1, old_value_t.mpec_hotresetn, new_value_t.mpec_hotresetn };
    m_bit_details_model.bits.append(entry);
    entry = { "11: nv_hotresetn:1",
              "0= ENABLE;\n1 = DISABLE",
              1, old_value_t.nv_hotresetn, new_value_t.nv_hotresetn };
    m_bit_details_model.bits.append(entry);
    entry = { "12: ppcs_hotresetn:1",
              "0 = ENABLE;\n1 = DISABLE",
              1, old_value_t.ppcs_hotresetn, new_value_t.ppcs_hotresetn };
    m_bit_details_model.bits.append(entry);
    entry = { "13: vde_hotresetn:1",
              "0 = ENABLE;\n1 = DISABLE",
              1, old_value_t.vde_hotresetn, new_value_t.vde_hotresetn };
    m_bit_details_model.bits.append(entry);
    entry = { "14: vi_hotresetn:1",
              "0 = ENABLE;\n1 = DISABLE",
              1, old_value_t.vi_hotresetn, new_value_t.vi_hotresetn };
    m_bit_details_model.bits.append(entry);
    entry = { "15: undefined_bits_15_31:17", "", 17, old_value_t.undefined_bits_15_31, new_value_t.undefined_bits_15_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Active low. Reset value is no hot reset. When enabled, the client requests before arbitration are cleared. A proper client reset sequence is as followed:\n    * Clear client bit in the MC_CLIENT_CTRL register to block its requests.\n    * Poll the C_OUTREQCNT register till zero.\n    * Clear module bit in the APBDEV_RSTREG register to reset the module, and clear client bit in the MC_CLIENT_HOTRESETN register to clear the client requests sitting before arbitration.\n    * Set client bit in the MC_CLIENT_HOTRESETN register to release the hot reset.\n    * Set module bit in the APBDEV_RSTREG register to release the module reset.\n    * Set client bit in the MC_CLIENT_CTRL register to allow new requests to proceed to arbitration.\nMemory Client Hot Reset Register";
}

#define LOWLATENCY_RAWLOGIC_WRITE_PARTICIPANTS_OFFSET 0x110
#define LOWLATENCY_RAWLOGIC_WRITE_PARTICIPANTS_UNDEFMASK 0xFFF00000
union lowlatency_rawlogic_write_participants_u {
    struct {
        unsigned int eppu_ll_raw_participate:1;/* 0 = DISABLE; 1 = ENABLE */
        unsigned int eppv_ll_raw_participate:1;/* 0 = DISABLE; 1 = ENABLE */
        unsigned int eppy_ll_raw_participate:1;/* 0 = DISABLE; 1 = ENABLE */
        unsigned int mpeunifbw_ll_raw_participate:1;/* 0 = DISABLE; 1 = ENABLE */
        unsigned int viwsb_ll_raw_participate:1;/* 0 = DISABLE; 1 = ENABLE */
        unsigned int viwu_ll_raw_participate:1;/* 0 = DISABLE; 1 = ENABLE */
        unsigned int viwv_ll_raw_participate:1;/* 0 = DISABLE; 1 = ENABLE */
        unsigned int viwy_ll_raw_participate:1;/* 0 = DISABLE; 1 = ENABLE */
        unsigned int g2dw_ll_raw_participate:1;/* 0 = DISABLE; 1 = ENABLE */
        unsigned int avpcarm7w_ll_raw_participate:1;/* 0 = DISABLE; 1 = ENABLE */
        unsigned int fdcdwr_ll_raw_participate:1;/* 0 = DISABLE; 1 = ENABLE */
        unsigned int host1xw_ll_raw_participate:1;/* 0 = DISABLE; 1 = ENABLE */
        unsigned int ispw_ll_raw_participate:1;/* 0 = DISABLE; 1 = ENABLE */
        unsigned int mpcorew_ll_raw_participate:1;/* 0 = DISABLE; 1 = ENABLE */
        unsigned int mpecswr_ll_raw_participate:1;/* 0 = DISABLE; 1 = ENABLE */
        unsigned int ppcsahbdmaw_ll_raw_participate:1;/* 0 = DISABLE; 1 = ENABLE */
        unsigned int ppcsahbslvw_ll_raw_participate:1;/* 0 = DISABLE; 1 = ENABLE */
        unsigned int vdebsevw_ll_raw_participate:1;/* 0 = DISABLE; 1 = ENABLE */
        unsigned int vdembew_ll_raw_participate:1;/* 0 = DISABLE; 1 = ENABLE */
        unsigned int vdetpmw_ll_raw_participate:1;/* 0 = DISABLE; 1 = ENABLE */
        unsigned int undefined_bits_20_31:12;
    };

    u_int32_t reg32;
};

void McDev::fill_lowlatency_rawlogic_write_participants_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const lowlatency_rawlogic_write_participants_u old_value_t = { .reg32 = value };
    const lowlatency_rawlogic_write_participants_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: eppu_ll_raw_participate:1",
              "0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.eppu_ll_raw_participate, new_value_t.eppu_ll_raw_participate };
    m_bit_details_model.bits.append(entry);
    entry = { "01: eppv_ll_raw_participate:1",
              "0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.eppv_ll_raw_participate, new_value_t.eppv_ll_raw_participate };
    m_bit_details_model.bits.append(entry);
    entry = { "02: eppy_ll_raw_participate:1",
              "0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.eppy_ll_raw_participate, new_value_t.eppy_ll_raw_participate };
    m_bit_details_model.bits.append(entry);
    entry = { "03: mpeunifbw_ll_raw_participate:1",
              "0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.mpeunifbw_ll_raw_participate, new_value_t.mpeunifbw_ll_raw_participate };
    m_bit_details_model.bits.append(entry);
    entry = { "04: viwsb_ll_raw_participate:1",
              "0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.viwsb_ll_raw_participate, new_value_t.viwsb_ll_raw_participate };
    m_bit_details_model.bits.append(entry);
    entry = { "05: viwu_ll_raw_participate:1",
              "0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.viwu_ll_raw_participate, new_value_t.viwu_ll_raw_participate };
    m_bit_details_model.bits.append(entry);
    entry = { "06: viwv_ll_raw_participate:1",
              "0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.viwv_ll_raw_participate, new_value_t.viwv_ll_raw_participate };
    m_bit_details_model.bits.append(entry);
    entry = { "07: viwy_ll_raw_participate:1",
              "0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.viwy_ll_raw_participate, new_value_t.viwy_ll_raw_participate };
    m_bit_details_model.bits.append(entry);
    entry = { "08: g2dw_ll_raw_participate:1",
              "0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.g2dw_ll_raw_participate, new_value_t.g2dw_ll_raw_participate };
    m_bit_details_model.bits.append(entry);
    entry = { "09: avpcarm7w_ll_raw_participate:1",
              "0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.avpcarm7w_ll_raw_participate, new_value_t.avpcarm7w_ll_raw_participate };
    m_bit_details_model.bits.append(entry);
    entry = { "10: fdcdwr_ll_raw_participate:1",
              "0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.fdcdwr_ll_raw_participate, new_value_t.fdcdwr_ll_raw_participate };
    m_bit_details_model.bits.append(entry);
    entry = { "11: host1xw_ll_raw_participate:1",
              "0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.host1xw_ll_raw_participate, new_value_t.host1xw_ll_raw_participate };
    m_bit_details_model.bits.append(entry);
    entry = { "12: ispw_ll_raw_participate:1",
              "0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ispw_ll_raw_participate, new_value_t.ispw_ll_raw_participate };
    m_bit_details_model.bits.append(entry);
    entry = { "13: mpcorew_ll_raw_participate:1",
              "0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.mpcorew_ll_raw_participate, new_value_t.mpcorew_ll_raw_participate };
    m_bit_details_model.bits.append(entry);
    entry = { "14: mpecswr_ll_raw_participate:1",
              "0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.mpecswr_ll_raw_participate, new_value_t.mpecswr_ll_raw_participate };
    m_bit_details_model.bits.append(entry);
    entry = { "15: ppcsahbdmaw_ll_raw_participate:1",
              "0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ppcsahbdmaw_ll_raw_participate, new_value_t.ppcsahbdmaw_ll_raw_participate };
    m_bit_details_model.bits.append(entry);
    entry = { "16: ppcsahbslvw_ll_raw_participate:1",
              "0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ppcsahbslvw_ll_raw_participate, new_value_t.ppcsahbslvw_ll_raw_participate };
    m_bit_details_model.bits.append(entry);
    entry = { "17: vdebsevw_ll_raw_participate:1",
              "0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.vdebsevw_ll_raw_participate, new_value_t.vdebsevw_ll_raw_participate };
    m_bit_details_model.bits.append(entry);
    entry = { "18: vdembew_ll_raw_participate:1",
              "0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.vdembew_ll_raw_participate, new_value_t.vdembew_ll_raw_participate };
    m_bit_details_model.bits.append(entry);
    entry = { "19: vdetpmw_ll_raw_participate:1",
              "0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.vdetpmw_ll_raw_participate, new_value_t.vdetpmw_ll_raw_participate };
    m_bit_details_model.bits.append(entry);
    entry = { "20: undefined_bits_20_31:12", "", 12, old_value_t.undefined_bits_20_31, new_value_t.undefined_bits_20_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "When ENABLED, the write client will participate in the low-latency RAW-protection logic.\nBy default, all clients participate. When a client is participating in the RAW logic, if that client has arbitrated a write to bank K, and while that write is arbitrated in MC but not in EMC, and if a low-latency read arrives, also to bank K, that low-latency read will be stalled until the write is committed to EMC.\nLow-latency client RAW-protection logic";
}

#define BWSHARE_TMVAL_OFFSET 0x114
#define BWSHARE_TMVAL_UNDEFMASK 0xFFFFFF00
union bwshare_tmval_u {
    struct {
        unsigned int bw_tm_sfactor1:4;
        unsigned int bw_tm_sfactor2:4;
        unsigned int undefined_bits_8_31:24;
    };

    u_int32_t reg32;
};

void McDev::fill_bwshare_tmval_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const bwshare_tmval_u old_value_t = { .reg32 = value };
    const bwshare_tmval_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: bw_tm_sfactor1:4", "", 4, old_value_t.bw_tm_sfactor1, new_value_t.bw_tm_sfactor1 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: bw_tm_sfactor2:4", "", 4, old_value_t.bw_tm_sfactor2, new_value_t.bw_tm_sfactor2 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_31:24", "", 24, old_value_t.undefined_bits_8_31, new_value_t.undefined_bits_8_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "A value of zero means that the timer counter is disabled. A value of N (non-zero) means that the BW Share increment happens every 2^(N+1) memory cycles.\nBandwidth share increment timer value";
}

#define BWSHARE_EMEM_CTRL_OFFSET 0x120
#define BWSHARE_EMEM_CTRL_UNDEFMASK 0x00000000
union bwshare_emem_ctrl_u {
    struct {
        unsigned int display0a_bw_emem:1;   /* 0 = DISABLE; 1 = ENABLE */
        unsigned int display0ab_bw_emem:1;  /* 0 = DISABLE; 1 = ENABLE */
        unsigned int display0b_bw_emem:1;   /* 0 = DISABLE; 1 = ENABLE */
        unsigned int display0bb_bw_emem:1;  /* 0 = DISABLE; 1 = ENABLE */
        unsigned int display0c_bw_emem:1;   /* 0 = DISABLE; 1 = ENABLE */
        unsigned int display0cb_bw_emem:1;  /* 0 = DISABLE; 1 = ENABLE */
        unsigned int display1b_bw_emem:1;   /* 0 = DISABLE; 1 = ENABLE */
        unsigned int display1bb_bw_emem:1;  /* 0 = DISABLE; 1 = ENABLE */
        unsigned int eppup_bw_emem:1;       /* 0 = DISABLE; 1 = ENABLE */
        unsigned int g2pr_bw_emem:1;        /* 0 = DISABLE; 1 = ENABLE */
        unsigned int g2sr_bw_emem:1;        /* 0 = DISABLE; 1 = ENABLE */
        unsigned int mpeunifbr_bw_emem:1;   /* 0 = DISABLE; 1 = ENABLE */
        unsigned int viruv_bw_emem:1;       /* 0 = DISABLE; 1 = ENABLE */
        unsigned int avpcarm7r_bw_emem:1;   /* 0 = DISABLE; 1 = ENABLE */
        unsigned int displayhc_bw_emem:1;   /* 0 = DISABLE; 1 = ENABLE */
        unsigned int displayhcb_bw_emem:1;  /* 0 = DISABLE; 1 = ENABLE */
        unsigned int fdcdrd_bw_emem:1;      /* 0 = DISABLE; 1 = ENABLE */
        unsigned int g2dr_bw_emem:1;        /* 0 = DISABLE; 1 = ENABLE */
        unsigned int host1xdmar_bw_emem:1;  /* 0 = DISABLE; 1 = ENABLE */
        unsigned int host1xr_bw_emem:1;     /* 0 = DISABLE; 1 = ENABLE */
        unsigned int idxsrd_bw_emem:1;      /* 0 = DISABLE; 1 = ENABLE */
        unsigned int mpcorer_bw_emem:1;     /* 0 = DISABLE; 1 = ENABLE */
        unsigned int mpe_ipred_bw_emem:1;   /* 0 = DISABLE; 1 = ENABLE */
        unsigned int mpeamemrd_bw_emem:1;   /* 0 = DISABLE; 1 = ENABLE */
        unsigned int mpecsrd_bw_emem:1;     /* 0 = DISABLE; 1 = ENABLE */
        unsigned int ppcsahbdmar_bw_emem:1; /* 0 = DISABLE; 1 = ENABLE */
        unsigned int ppcsahbslvr_bw_emem:1; /* 0 = DISABLE; 1 = ENABLE */
        unsigned int texsrd_bw_emem:1;      /* 0 = DISABLE; 1 = ENABLE */
        unsigned int vdebsevr_bw_emem:1;    /* 0 = DISABLE; 1 = ENABLE */
        unsigned int vdember_bw_emem:1;     /* 0 = DISABLE; 1 = ENABLE */
        unsigned int vdemcer_bw_emem:1;     /* 0 = DISABLE; 1 = ENABLE */
        unsigned int vdetper_bw_emem:1;     /* 0 = DISABLE; 1 = ENABLE */
    };

    u_int32_t reg32;
};

void McDev::fill_bwshare_emem_ctrl_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const bwshare_emem_ctrl_u old_value_t = { .reg32 = value };
    const bwshare_emem_ctrl_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: display0a_bw_emem:1",
              "0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.display0a_bw_emem, new_value_t.display0a_bw_emem };
    m_bit_details_model.bits.append(entry);
    entry = { "01: display0ab_bw_emem:1",
              "0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.display0ab_bw_emem, new_value_t.display0ab_bw_emem };
    m_bit_details_model.bits.append(entry);
    entry = { "02: display0b_bw_emem:1",
              "0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.display0b_bw_emem, new_value_t.display0b_bw_emem };
    m_bit_details_model.bits.append(entry);
    entry = { "03: display0bb_bw_emem:1",
              "0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.display0bb_bw_emem, new_value_t.display0bb_bw_emem };
    m_bit_details_model.bits.append(entry);
    entry = { "04: display0c_bw_emem:1",
              "0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.display0c_bw_emem, new_value_t.display0c_bw_emem };
    m_bit_details_model.bits.append(entry);
    entry = { "05: display0cb_bw_emem:1",
              "0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.display0cb_bw_emem, new_value_t.display0cb_bw_emem };
    m_bit_details_model.bits.append(entry);
    entry = { "06: display1b_bw_emem:1",
              "0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.display1b_bw_emem, new_value_t.display1b_bw_emem };
    m_bit_details_model.bits.append(entry);
    entry = { "07: display1bb_bw_emem:1",
              "0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.display1bb_bw_emem, new_value_t.display1bb_bw_emem };
    m_bit_details_model.bits.append(entry);
    entry = { "08: eppup_bw_emem:1",
              "0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.eppup_bw_emem, new_value_t.eppup_bw_emem };
    m_bit_details_model.bits.append(entry);
    entry = { "09: g2pr_bw_emem:1",
              "0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.g2pr_bw_emem, new_value_t.g2pr_bw_emem };
    m_bit_details_model.bits.append(entry);
    entry = { "10: g2sr_bw_emem:1",
              "0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.g2sr_bw_emem, new_value_t.g2sr_bw_emem };
    m_bit_details_model.bits.append(entry);
    entry = { "11: mpeunifbr_bw_emem:1",
              "0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.mpeunifbr_bw_emem, new_value_t.mpeunifbr_bw_emem };
    m_bit_details_model.bits.append(entry);
    entry = { "12: viruv_bw_emem:1",
              "0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.viruv_bw_emem, new_value_t.viruv_bw_emem };
    m_bit_details_model.bits.append(entry);
    entry = { "13: avpcarm7r_bw_emem:1",
              "0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.avpcarm7r_bw_emem, new_value_t.avpcarm7r_bw_emem };
    m_bit_details_model.bits.append(entry);
    entry = { "14: displayhc_bw_emem:1",
              "0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.displayhc_bw_emem, new_value_t.displayhc_bw_emem };
    m_bit_details_model.bits.append(entry);
    entry = { "15: displayhcb_bw_emem:1",
              "0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.displayhcb_bw_emem, new_value_t.displayhcb_bw_emem };
    m_bit_details_model.bits.append(entry);
    entry = { "16: fdcdrd_bw_emem:1",
              "0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.fdcdrd_bw_emem, new_value_t.fdcdrd_bw_emem };
    m_bit_details_model.bits.append(entry);
    entry = { "17: g2dr_bw_emem:1",
              "0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.g2dr_bw_emem, new_value_t.g2dr_bw_emem };
    m_bit_details_model.bits.append(entry);
    entry = { "18: host1xdmar_bw_emem:1",
              "0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.host1xdmar_bw_emem, new_value_t.host1xdmar_bw_emem };
    m_bit_details_model.bits.append(entry);
    entry = { "19: host1xr_bw_emem:1",
              "0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.host1xr_bw_emem, new_value_t.host1xr_bw_emem };
    m_bit_details_model.bits.append(entry);
    entry = { "20: idxsrd_bw_emem:1",
              "0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.idxsrd_bw_emem, new_value_t.idxsrd_bw_emem };
    m_bit_details_model.bits.append(entry);
    entry = { "21: mpcorer_bw_emem:1",
              "0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.mpcorer_bw_emem, new_value_t.mpcorer_bw_emem };
    m_bit_details_model.bits.append(entry);
    entry = { "22: mpe_ipred_bw_emem:1",
              "0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.mpe_ipred_bw_emem, new_value_t.mpe_ipred_bw_emem };
    m_bit_details_model.bits.append(entry);
    entry = { "23: mpeamemrd_bw_emem:1",
              "0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.mpeamemrd_bw_emem, new_value_t.mpeamemrd_bw_emem };
    m_bit_details_model.bits.append(entry);
    entry = { "24: mpecsrd_bw_emem:1",
              "0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.mpecsrd_bw_emem, new_value_t.mpecsrd_bw_emem };
    m_bit_details_model.bits.append(entry);
    entry = { "25: ppcsahbdmar_bw_emem:1",
              "0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ppcsahbdmar_bw_emem, new_value_t.ppcsahbdmar_bw_emem };
    m_bit_details_model.bits.append(entry);
    entry = { "26: ppcsahbslvr_bw_emem:1",
              "0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ppcsahbslvr_bw_emem, new_value_t.ppcsahbslvr_bw_emem };
    m_bit_details_model.bits.append(entry);
    entry = { "27: texsrd_bw_emem:1",
              "0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.texsrd_bw_emem, new_value_t.texsrd_bw_emem };
    m_bit_details_model.bits.append(entry);
    entry = { "28: vdebsevr_bw_emem:1",
              "0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.vdebsevr_bw_emem, new_value_t.vdebsevr_bw_emem };
    m_bit_details_model.bits.append(entry);
    entry = { "29: vdember_bw_emem:1",
              "0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.vdember_bw_emem, new_value_t.vdember_bw_emem };
    m_bit_details_model.bits.append(entry);
    entry = { "30: vdemcer_bw_emem:1",
              "0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.vdemcer_bw_emem, new_value_t.vdemcer_bw_emem };
    m_bit_details_model.bits.append(entry);
    entry = { "31: vdetper_bw_emem:1",
              "0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.vdetper_bw_emem, new_value_t.vdetper_bw_emem };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Reset value is disabled. Controls whether a client should participate in EMEM Bandwidth Share mechanism. Bandwidth share is per super client. If Enabled, make sure the super client's bandwidth share registers are programmed.\nMemory Client EMEM Bandwidth Share control register 0";
}

#define BWSHARE_EMEM_CTRL_1_OFFSET 0x124
#define BWSHARE_EMEM_CTRL_1_UNDEFMASK 0xFFF00000
union bwshare_emem_ctrl_1_u {
    struct {
        unsigned int eppu_bw_emem:1;        /* 0 = DISABLE; 1 = ENABLE */
        unsigned int eppv_bw_emem:1;        /* 0 = DISABLE; 1 = ENABLE */
        unsigned int eppy_bw_emem:1;        /* 0 = DISABLE; 1 = ENABLE */
        unsigned int mpeunifbw_bw_emem:1;   /* 0 = DISABLE; 1 = ENABLE */
        unsigned int viwsb_bw_emem:1;       /* 0 = DISABLE; 1 = ENABLE */
        unsigned int viwu_bw_emem:1;        /* 0 = DISABLE; 1 = ENABLE */
        unsigned int viwv_bw_emem:1;        /* 0 = DISABLE; 1 = ENABLE */
        unsigned int viwy_bw_emem:1;        /* 0 = DISABLE; 1 = ENABLE */
        unsigned int g2dw_bw_emem:1;        /* 0 = DISABLE; 1 = ENABLE */
        unsigned int avpcarm7w_bw_emem:1;   /* 0 = DISABLE; 1 = ENABLE */
        unsigned int fdcdwr_bw_emem:1;      /* 0 = DISABLE; 1 = ENABLE */
        unsigned int host1xw_bw_emem:1;     /* 0 = DISABLE; 1 = ENABLE */
        unsigned int ispw_bw_emem:1;        /* 0 = DISABLE; 1 = ENABLE */
        unsigned int mpcorew_bw_emem:1;     /* 0 = DISABLE; 1 = ENABLE */
        unsigned int mpecswr_bw_emem:1;     /* 0 = DISABLE; 1 = ENABLE */
        unsigned int ppcsahbdmaw_bw_emem:1; /* 0 = DISABLE; 1 = ENABLE */
        unsigned int ppcsahbslvw_bw_emem:1; /* 0 = DISABLE; 1 = ENABLE */
        unsigned int vdebsevw_bw_emem:1;    /* 0 = DISABLE; 1 = ENABLE */
        unsigned int vdembew_bw_emem:1;     /* 0 = DISABLE; 1 = ENABLE */
        unsigned int vdetpmw_bw_emem:1;     /* 0 = DISABLE; 1 = ENABLE */
        unsigned int undefined_bits_20_31:12;
    };

    u_int32_t reg32;
};

void McDev::fill_bwshare_emem_ctrl_1_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const bwshare_emem_ctrl_1_u old_value_t = { .reg32 = value };
    const bwshare_emem_ctrl_1_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: eppu_bw_emem:1",
              "0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.eppu_bw_emem, new_value_t.eppu_bw_emem };
    m_bit_details_model.bits.append(entry);
    entry = { "01: eppv_bw_emem:1",
              "0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.eppv_bw_emem, new_value_t.eppv_bw_emem };
    m_bit_details_model.bits.append(entry);
    entry = { "02: eppy_bw_emem:1",
              "0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.eppy_bw_emem, new_value_t.eppy_bw_emem };
    m_bit_details_model.bits.append(entry);
    entry = { "03: mpeunifbw_bw_emem:1",
              "0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.mpeunifbw_bw_emem, new_value_t.mpeunifbw_bw_emem };
    m_bit_details_model.bits.append(entry);
    entry = { "04: viwsb_bw_emem:1",
              "0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.viwsb_bw_emem, new_value_t.viwsb_bw_emem };
    m_bit_details_model.bits.append(entry);
    entry = { "05: viwu_bw_emem:1",
              "0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.viwu_bw_emem, new_value_t.viwu_bw_emem };
    m_bit_details_model.bits.append(entry);
    entry = { "06: viwv_bw_emem:1",
              "0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.viwv_bw_emem, new_value_t.viwv_bw_emem };
    m_bit_details_model.bits.append(entry);
    entry = { "07: viwy_bw_emem:1",
              "0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.viwy_bw_emem, new_value_t.viwy_bw_emem };
    m_bit_details_model.bits.append(entry);
    entry = { "08: g2dw_bw_emem:1",
              "0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.g2dw_bw_emem, new_value_t.g2dw_bw_emem };
    m_bit_details_model.bits.append(entry);
    entry = { "09: avpcarm7w_bw_emem:1",
              "0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.avpcarm7w_bw_emem, new_value_t.avpcarm7w_bw_emem };
    m_bit_details_model.bits.append(entry);
    entry = { "10: fdcdwr_bw_emem:1",
              "0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.fdcdwr_bw_emem, new_value_t.fdcdwr_bw_emem };
    m_bit_details_model.bits.append(entry);
    entry = { "11: host1xw_bw_emem:1",
              "0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.host1xw_bw_emem, new_value_t.host1xw_bw_emem };
    m_bit_details_model.bits.append(entry);
    entry = { "12: ispw_bw_emem:1",
              "0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ispw_bw_emem, new_value_t.ispw_bw_emem };
    m_bit_details_model.bits.append(entry);
    entry = { "13: mpcorew_bw_emem:1",
              "0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.mpcorew_bw_emem, new_value_t.mpcorew_bw_emem };
    m_bit_details_model.bits.append(entry);
    entry = { "14: mpecswr_bw_emem:1",
              "0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.mpecswr_bw_emem, new_value_t.mpecswr_bw_emem };
    m_bit_details_model.bits.append(entry);
    entry = { "15: ppcsahbdmaw_bw_emem:1",
              "0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ppcsahbdmaw_bw_emem, new_value_t.ppcsahbdmaw_bw_emem };
    m_bit_details_model.bits.append(entry);
    entry = { "16: ppcsahbslvw_bw_emem:1",
              "0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ppcsahbslvw_bw_emem, new_value_t.ppcsahbslvw_bw_emem };
    m_bit_details_model.bits.append(entry);
    entry = { "17: vdebsevw_bw_emem:1",
              "0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.vdebsevw_bw_emem, new_value_t.vdebsevw_bw_emem };
    m_bit_details_model.bits.append(entry);
    entry = { "18: vdembew_bw_emem:1",
              "0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.vdembew_bw_emem, new_value_t.vdembew_bw_emem };
    m_bit_details_model.bits.append(entry);
    entry = { "19: vdetpmw_bw_emem:1",
              "0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.vdetpmw_bw_emem, new_value_t.vdetpmw_bw_emem };
    m_bit_details_model.bits.append(entry);
    entry = { "20: undefined_bits_20_31:12", "", 12, old_value_t.undefined_bits_20_31, new_value_t.undefined_bits_20_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Reset value is disabled. Controls whether a client should participate in EMEM Bandwidth Share mechanism. Bandwidth share is per super client. If Enabled, make sure the super client's bandwidth share registers are programmed.\nMemory Client EMEM Bandwidth Share control register 1";
}

#define AVPC_ORRC_OFFSET 0x140
#define AVPC_ORRC_UNDEFMASK 0xFFFFFF00
union avpc_orrc_u {
    struct {
        unsigned int avpc_outreqcnt:8;
        unsigned int undefined_bits_8_31:24;
    };

    u_int32_t reg32;
};

void McDev::fill_avpc_orrc_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const avpc_orrc_u old_value_t = { .reg32 = value };
    const avpc_orrc_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: avpc_outreqcnt:8", "", 8, old_value_t.avpc_outreqcnt, new_value_t.avpc_outreqcnt };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_31:24", "", 24, old_value_t.undefined_bits_8_31, new_value_t.undefined_bits_8_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Read only. This reports the number of outstanding client requests after arbitration. It is incremented by HW when a client request is granted by the arbiter. For read clients, it is decremented by HW when a return data is sent back to the client.\nAVPC Outstanding Request Register";
}

#define DC_ORRC_OFFSET 0x144
#define DC_ORRC_UNDEFMASK 0xFFFFFF00
union dc_orrc_u {
    struct {
        unsigned int dc_outreqcnt:8;
        unsigned int undefined_bits_8_31:24;
    };

    u_int32_t reg32;
};

void McDev::fill_dc_orrc_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const dc_orrc_u old_value_t = { .reg32 = value };
    const dc_orrc_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: dc_outreqcnt:8", "", 8, old_value_t.dc_outreqcnt, new_value_t.dc_outreqcnt };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_31:24", "", 24, old_value_t.undefined_bits_8_31, new_value_t.undefined_bits_8_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Read only. This reports the number of outstanding client requests after arbitration. It is incremented by HW when a client request is granted by the arbiter. For read clients, it is decremented by HW when a return data is sent back to the client.\nDC Outstanding Request Register";
}

#define DCB_ORRC_OFFSET 0x148
#define DCB_ORRC_UNDEFMASK 0xFFFFFF00
union dcb_orrc_u {
    struct {
        unsigned int dcb_outreqcnt:8;
        unsigned int undefined_bits_8_31:24;
    };

    u_int32_t reg32;
};

void McDev::fill_dcb_orrc_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const dcb_orrc_u old_value_t = { .reg32 = value };
    const dcb_orrc_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: dcb_outreqcnt:8", "", 8, old_value_t.dcb_outreqcnt, new_value_t.dcb_outreqcnt };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_31:24", "", 24, old_value_t.undefined_bits_8_31, new_value_t.undefined_bits_8_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Read only. This reports the number of outstanding client requests after arbitration. It is incremented by HW when a client request is granted by the arbiter. For read clients, it is decremented by HW when a return data is sent back to the client.\nDCB Outstanding Request Register";
}

#define EPP_ORRC_OFFSET 0x14C
#define EPP_ORRC_UNDEFMASK 0xFFFFFF00
union epp_orrc_u {
    struct {
        unsigned int epp_outreqcnt:8;
        unsigned int undefined_bits_8_31:24;
    };

    u_int32_t reg32;
};

void McDev::fill_epp_orrc_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const epp_orrc_u old_value_t = { .reg32 = value };
    const epp_orrc_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: epp_outreqcnt:8", "", 8, old_value_t.epp_outreqcnt, new_value_t.epp_outreqcnt };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_31:24", "", 24, old_value_t.undefined_bits_8_31, new_value_t.undefined_bits_8_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Read only. This reports the number of outstanding client requests after arbitration. It is incremented by HW when a client request is granted by the arbiter. For read clients, it is decremented by HW when a return data is sent back to the client.\nEPP Outstanding Request Register";
}

#define G2_ORRC_OFFSET 0x150
#define G2_ORRC_UNDEFMASK 0xFFFFFF00
union g2_orrc_u {
    struct {
        unsigned int g2_outreqcnt:8;
        unsigned int undefined_bits_8_31:24;
    };

    u_int32_t reg32;
};

void McDev::fill_g2_orrc_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const g2_orrc_u old_value_t = { .reg32 = value };
    const g2_orrc_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: g2_outreqcnt:8", "", 8, old_value_t.g2_outreqcnt, new_value_t.g2_outreqcnt };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_31:24", "", 24, old_value_t.undefined_bits_8_31, new_value_t.undefined_bits_8_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Read only. This reports the number of outstanding client requests after arbitration. It is incremented by HW when a client request is granted by the arbiter. For read clients, it is decremented by HW when a return data is sent back to the client.\nG2 Outstanding Request Register";
}

#define HC_ORRC_OFFSET 0x154
#define HC_ORRC_UNDEFMASK 0xFFFFFF00
union hc_orrc_u {
    struct {
        unsigned int hc_outreqcnt:8;
        unsigned int undefined_bits_8_31:24;
    };

    u_int32_t reg32;
};

void McDev::fill_hc_orrc_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const hc_orrc_u old_value_t = { .reg32 = value };
    const hc_orrc_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: hc_outreqcnt:8", "", 8, old_value_t.hc_outreqcnt, new_value_t.hc_outreqcnt };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_31:24", "", 24, old_value_t.undefined_bits_8_31, new_value_t.undefined_bits_8_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Read only. This reports the number of outstanding client requests after arbitration. It is incremented by HW when a client request is granted by the arbiter. For read clients, it is decremented by HW when a return data is sent back to the client.\nHC Outstanding Request Register";
}

#define ISP_ORRC_OFFSET 0x158
#define ISP_ORRC_UNDEFMASK 0xFFFFFF00
union isp_orrc_u {
    struct {
        unsigned int isp_outreqcnt:8;
        unsigned int undefined_bits_8_31:24;
    };

    u_int32_t reg32;
};

void McDev::fill_isp_orrc_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const isp_orrc_u old_value_t = { .reg32 = value };
    const isp_orrc_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: isp_outreqcnt:8", "", 8, old_value_t.isp_outreqcnt, new_value_t.isp_outreqcnt };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_31:24", "", 24, old_value_t.undefined_bits_8_31, new_value_t.undefined_bits_8_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Read only. This reports the number of outstanding client requests after arbitration. It is incremented by HW when a client request is granted by the arbiter. For read clients, it is decremented by HW when a return data is sent back to the client.\nISP Outstanding Request Register";
}

#define MPCORE_ORRC_OFFSET 0x15C
#define MPCORE_ORRC_UNDEFMASK 0xFFFFFF00
union mpcore_orrc_u {
    struct {
        unsigned int mpcore_outreqcnt:8;
        unsigned int undefined_bits_8_31:24;
    };

    u_int32_t reg32;
};

void McDev::fill_mpcore_orrc_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const mpcore_orrc_u old_value_t = { .reg32 = value };
    const mpcore_orrc_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: mpcore_outreqcnt:8", "", 8, old_value_t.mpcore_outreqcnt, new_value_t.mpcore_outreqcnt };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_31:24", "", 24, old_value_t.undefined_bits_8_31, new_value_t.undefined_bits_8_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Read only. This reports the number of outstanding client requests after arbitration. It is incremented by HW when a client request is granted by the arbiter. For read clients, it is decremented by HW when a return data is sent back to the client.\nCPU Outstanding Request Register";
}

#define MPEA_ORRC_OFFSET 0x160
#define MPEA_ORRC_UNDEFMASK 0xFFFFFF00
union mpea_orrc_u {
    struct {
        unsigned int mpea_outreqcnt:8;
        unsigned int undefined_bits_8_31:24;
    };

    u_int32_t reg32;
};

void McDev::fill_mpea_orrc_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const mpea_orrc_u old_value_t = { .reg32 = value };
    const mpea_orrc_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: mpea_outreqcnt:8", "", 8, old_value_t.mpea_outreqcnt, new_value_t.mpea_outreqcnt };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_31:24", "", 24, old_value_t.undefined_bits_8_31, new_value_t.undefined_bits_8_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Read only. This reports the number of outstanding client requests after arbitration. It is incremented by HW when a client request is granted by the arbiter. For read clients, it is decremented by HW when a return data is sent back to the client.\nMPEA Outstanding Request Register";
}

#define MPEB_ORRC_OFFSET 0x164
#define MPEB_ORRC_UNDEFMASK 0xFFFFFF00
union mpeb_orrc_u {
    struct {
        unsigned int mpeb_outreqcnt:8;
        unsigned int undefined_bits_8_31:24;
    };

    u_int32_t reg32;
};

void McDev::fill_mpeb_orrc_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const mpeb_orrc_u old_value_t = { .reg32 = value };
    const mpeb_orrc_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: mpeb_outreqcnt:8", "", 8, old_value_t.mpeb_outreqcnt, new_value_t.mpeb_outreqcnt };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_31:24", "", 24, old_value_t.undefined_bits_8_31, new_value_t.undefined_bits_8_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Read only. This reports the number of outstanding client requests after arbitration. It is incremented by HW when a client request is granted by the arbiter. For read clients, it is decremented by HW when a return data is sent back to the client.\nMPEB Outstanding Request Register";
}

#define MPEC_ORRC_OFFSET 0x168
#define MPEC_ORRC_UNDEFMASK 0xFFFFFF00
union mpec_orrc_u {
    struct {
        unsigned int mpec_outreqcnt:8;
        unsigned int undefined_bits_8_31:24;
    };

    u_int32_t reg32;
};

void McDev::fill_mpec_orrc_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const mpec_orrc_u old_value_t = { .reg32 = value };
    const mpec_orrc_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: mpec_outreqcnt:8", "", 8, old_value_t.mpec_outreqcnt, new_value_t.mpec_outreqcnt };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_31:24", "", 24, old_value_t.undefined_bits_8_31, new_value_t.undefined_bits_8_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Read only. This reports the number of outstanding client requests after arbitration. It is incremented by HW when a client request is granted by the arbiter. For read clients, it is decremented by HW when a return data is sent back to the client.\nMPEC Outstanding Request Register";
}

#define NV_ORRC_OFFSET 0x16C
#define NV_ORRC_UNDEFMASK 0xFFFFFF00
union nv_orrc_u {
    struct {
        unsigned int nv_outreqcnt:8;
        unsigned int undefined_bits_8_31:24;
    };

    u_int32_t reg32;
};

void McDev::fill_nv_orrc_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const nv_orrc_u old_value_t = { .reg32 = value };
    const nv_orrc_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: nv_outreqcnt:8", "", 8, old_value_t.nv_outreqcnt, new_value_t.nv_outreqcnt };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_31:24", "", 24, old_value_t.undefined_bits_8_31, new_value_t.undefined_bits_8_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Read only. This reports the number of outstanding client requests after arbitration. It is incremented by HW when a client request is granted by the arbiter. For read clients, it is decremented by HW when a return data is sent back to the client.\nNV Outstanding Request Register";
}

#define PPCS_ORRC_OFFSET 0x170
#define PPCS_ORRC_UNDEFMASK 0xFFFFFF00
union ppcs_orrc_u {
    struct {
        unsigned int ppcs_outreqcnt:8;
        unsigned int undefined_bits_8_31:24;
    };

    u_int32_t reg32;
};

void McDev::fill_ppcs_orrc_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const ppcs_orrc_u old_value_t = { .reg32 = value };
    const ppcs_orrc_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: ppcs_outreqcnt:8", "", 8, old_value_t.ppcs_outreqcnt, new_value_t.ppcs_outreqcnt };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_31:24", "", 24, old_value_t.undefined_bits_8_31, new_value_t.undefined_bits_8_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Read only. This reports the number of outstanding client requests after arbitration. It is incremented by HW when a client request is granted by the arbiter. For read clients, it is decremented by HW when a return data is sent back to the client.\nPPCS Outstanding Request Register";
}

#define VDE_ORRC_OFFSET 0x174
#define VDE_ORRC_UNDEFMASK 0xFFFFFF00
union vde_orrc_u {
    struct {
        unsigned int vde_outreqcnt:8;
        unsigned int undefined_bits_8_31:24;
    };

    u_int32_t reg32;
};

void McDev::fill_vde_orrc_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const vde_orrc_u old_value_t = { .reg32 = value };
    const vde_orrc_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: vde_outreqcnt:8", "", 8, old_value_t.vde_outreqcnt, new_value_t.vde_outreqcnt };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_31:24", "", 24, old_value_t.undefined_bits_8_31, new_value_t.undefined_bits_8_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Read only. This reports the number of outstanding client requests after arbitration. It is incremented by HW when a client request is granted by the arbiter. For read clients, it is decremented by HW when a return data is sent back to the client.\nVDE Outstanding Request Register";
}

#define VI_ORRC_OFFSET 0x178
#define VI_ORRC_UNDEFMASK 0xFFFFFF00
union vi_orrc_u {
    struct {
        unsigned int vi_outreqcnt:8;
        unsigned int undefined_bits_8_31:24;
    };

    u_int32_t reg32;
};

void McDev::fill_vi_orrc_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const vi_orrc_u old_value_t = { .reg32 = value };
    const vi_orrc_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: vi_outreqcnt:8", "", 8, old_value_t.vi_outreqcnt, new_value_t.vi_outreqcnt };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_31:24", "", 24, old_value_t.undefined_bits_8_31, new_value_t.undefined_bits_8_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Read only. This reports the number of outstanding client requests after arbitration. It is incremented by HW when a client request is granted by the arbiter. For read clients, it is decremented by HW when a return data is sent back to the client.\nVI Outstanding Request Register";
}

#define FPRI_CTRL_AVPC_OFFSET 0x17C
#define FPRI_CTRL_AVPC_UNDEFMASK 0xFFFFFFF0
union fpri_ctrl_avpc_u {
    struct {
        unsigned int avpcarm7r_prival:2;
        unsigned int avpcarm7w_prival:2;
        unsigned int undefined_bits_4_31:28;
    };

    u_int32_t reg32;
};

void McDev::fill_fpri_ctrl_avpc_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const fpri_ctrl_avpc_u old_value_t = { .reg32 = value };
    const fpri_ctrl_avpc_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: avpcarm7r_prival:2", "", 2, old_value_t.avpcarm7r_prival, new_value_t.avpcarm7r_prival };
    m_bit_details_model.bits.append(entry);
    entry = { "02: avpcarm7w_prival:2", "", 2, old_value_t.avpcarm7w_prival, new_value_t.avpcarm7w_prival };
    m_bit_details_model.bits.append(entry);
    entry = { "04: undefined_bits_4_31:28", "", 28, old_value_t.undefined_bits_4_31, new_value_t.undefined_bits_4_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Reset value defaults to LOW for most clients, but may be different for certain clients.\nFixed-priority Register for AVPC clients";
}

#define FPRI_CTRL_DC_OFFSET 0x180
#define FPRI_CTRL_DC_UNDEFMASK 0xFFFFFC00
union fpri_ctrl_dc_u {
    struct {
        unsigned int display0a_prival:2;    /* 0 = LOWEST; 1 = LOW; 2 = MED; 3 = HIGH */
        unsigned int display0b_prival:2;    /* 0 = LOWEST; 1 = LOW; 2 = MED; 3 = HIGH */
        unsigned int display0c_prival:2;    /* 0 = LOWEST; 1 = LOW; 2 = MED; 3 = HIGH */
        unsigned int display1b_prival:2;    /* 0 = LOWEST; 1 = LOW; 2 = MED; 3 = HIGH */
        unsigned int displayhc_prival:2;    /* 0 = LOWEST; 1 = LOW; 2 = MED; 3 = HIGH */
        unsigned int undefined_bits_10_31:22;
    };

    u_int32_t reg32;
};

void McDev::fill_fpri_ctrl_dc_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const fpri_ctrl_dc_u old_value_t = { .reg32 = value };
    const fpri_ctrl_dc_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: display0a_prival:2",
              "0 = LOWEST;\n1 = LOW;\n2 = MED;\n3 = HIGH",
              2, old_value_t.display0a_prival, new_value_t.display0a_prival };
    m_bit_details_model.bits.append(entry);
    entry = { "02: display0b_prival:2",
              "0 = LOWEST;\n1 = LOW;\n2 = MED;\n3 = HIGH",
              2, old_value_t.display0b_prival, new_value_t.display0b_prival };
    m_bit_details_model.bits.append(entry);
    entry = { "04: display0c_prival:2",
              "0 = LOWEST;\n1 = LOW;\n2 = MED;\n3 = HIGH",
              2, old_value_t.display0c_prival, new_value_t.display0c_prival };
    m_bit_details_model.bits.append(entry);
    entry = { "06: display1b_prival:2",
              "0 = LOWEST;\n1 = LOW;\n2 = MED;\n3 = HIGH",
              2, old_value_t.display1b_prival, new_value_t.display1b_prival };
    m_bit_details_model.bits.append(entry);
    entry = { "08: displayhc_prival:2",
              "0 = LOWEST;\n1 = LOW;\n2 = MED;\n3 = HIGH",
              2, old_value_t.displayhc_prival, new_value_t.displayhc_prival };
    m_bit_details_model.bits.append(entry);
    entry = { "10: undefined_bits_10_31:22", "", 22, old_value_t.undefined_bits_10_31, new_value_t.undefined_bits_10_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Reset value defaults to LOW for most clients, but may be different for certain clients.\nFixed-priority Register for dc clients";
}

#define FPRI_CTRL_DCB_OFFSET 0x184
#define FPRI_CTRL_DCB_UNDEFMASK 0xFFFFFC00
union fpri_ctrl_dcb_u {
    struct {
        unsigned int display0ab_prival:2;   /* 0 = LOWEST; 1 = LOW; 2 = MED; 3 = HIGH */
        unsigned int display0bb_prival:2;   /* 0 = LOWEST; 1 = LOW; 2 = MED; 3 = HIGH */
        unsigned int display0cb_prival:2;   /* 0 = LOWEST; 1 = LOW; 2 = MED; 3 = HIGH */
        unsigned int display1bb_prival:2;   /* 0 = LOWEST; 1 = LOW; 2 = MED; 3 = HIGH */
        unsigned int displayhcb_prival:2;   /* 0 = LOWEST; 1 = LOW; 2 = MED; 3 = HIGH */
        unsigned int undefined_bits_10_31:22;
    };

    u_int32_t reg32;
};

void McDev::fill_fpri_ctrl_dcb_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const fpri_ctrl_dcb_u old_value_t = { .reg32 = value };
    const fpri_ctrl_dcb_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: display0ab_prival:2",
              "0 = LOWEST;\n1 = LOW;\n2 = MED;\n3 = HIGH",
              2, old_value_t.display0ab_prival, new_value_t.display0ab_prival };
    m_bit_details_model.bits.append(entry);
    entry = { "02: display0bb_prival:2",
              "0 = LOWEST;\n1 = LOW;\n2 = MED;\n3 = HIGH",
              2, old_value_t.display0bb_prival, new_value_t.display0bb_prival };
    m_bit_details_model.bits.append(entry);
    entry = { "04: display0cb_prival:2",
              "0 = LOWEST;\n1 = LOW;\n2 = MED;\n3 = HIGH",
              2, old_value_t.display0cb_prival, new_value_t.display0cb_prival };
    m_bit_details_model.bits.append(entry);
    entry = { "06: display1bb_prival:2",
              "0 = LOWEST;\n1 = LOW;\n2 = MED;\n3 = HIGH",
              2, old_value_t.display1bb_prival, new_value_t.display1bb_prival };
    m_bit_details_model.bits.append(entry);
    entry = { "08: displayhcb_prival:2",
              "0 = LOWEST;\n1 = LOW;\n2 = MED;\n3 = HIGH",
              2, old_value_t.displayhcb_prival, new_value_t.displayhcb_prival };
    m_bit_details_model.bits.append(entry);
    entry = { "10: undefined_bits_10_31:22", "", 22, old_value_t.undefined_bits_10_31, new_value_t.undefined_bits_10_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Reset value defaults to LOW for most clients, but may be different for certain clients\nFixed-priority Register for dcb clients";
}

#define FPRI_CTRL_EPP_OFFSET 0x188
#define FPRI_CTRL_EPP_UNDEFMASK 0xFFFFFF00
union fpri_ctrl_epp_u {
    struct {
        unsigned int eppup_prival:2;        /* 0 = LOWEST; 1 = LOW; 2 = MED; 3 = HIGH */
        unsigned int eppu_prival:2;         /* 0 = LOWEST; 1 = LOW; 2 = MED; 3 = HIGH */
        unsigned int eppv_prival:2;         /* 0 = LOWEST; 1 = LOW; 2 = MED; 3 = HIGH */
        unsigned int eppy_prival:2;         /* 0 = LOWEST; 1 = LOW; 2 = MED; 3 = HIGH */
        unsigned int undefined_bits_8_31:24;
    };

    u_int32_t reg32;
};

void McDev::fill_fpri_ctrl_epp_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const fpri_ctrl_epp_u old_value_t = { .reg32 = value };
    const fpri_ctrl_epp_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: eppup_prival:2",
              "0 = LOWEST;\n1 = LOW;\n2 = MED;\n3 = HIGH",
              2, old_value_t.eppup_prival, new_value_t.eppup_prival };
    m_bit_details_model.bits.append(entry);
    entry = { "02: eppu_prival:2",
              "0 = LOWEST;\n1 = LOW;\n2 = MED;\n3 = HIGH",
              2, old_value_t.eppu_prival, new_value_t.eppu_prival };
    m_bit_details_model.bits.append(entry);
    entry = { "04: eppv_prival:2",
              "0 = LOWEST;\n1 = LOW;\n2 = MED;\n3 = HIGH",
              2, old_value_t.eppv_prival, new_value_t.eppv_prival };
    m_bit_details_model.bits.append(entry);
    entry = { "06: eppy_prival:2",
              "0 = LOWEST;\n1 = LOW;\n2 = MED;\n3 = HIGH",
              2, old_value_t.eppy_prival, new_value_t.eppy_prival };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_31:24", "", 24, old_value_t.undefined_bits_8_31, new_value_t.undefined_bits_8_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Reset value defaults to LOW for most clients, but may be different for certain clients\nFixed-priority Register for epp clients";
}

#define FPRI_CTRL_G2_OFFSET 0x18C
#define FPRI_CTRL_G2_UNDEFMASK 0xFFFFFF00
union fpri_ctrl_g2_u {
    struct {
        unsigned int g2pr_prival:2;         /* 0 = LOWEST; 1 = LOW; 2 = MED; 3 = HIGH */
        unsigned int g2sr_prival:2;         /* 0 = LOWEST; 1 = LOW; 2 = MED; 3 = HIGH */
        unsigned int g2dr_prival:2;         /* 0 = LOWEST; 1 = LOW; 2 = MED; 3 = HIGH */
        unsigned int g2dw_prival:2;         /* 0 = LOWEST; 1 = LOW; 2 = MED; 3 = HIGH */
        unsigned int undefined_bits_8_31:24;
    };

    u_int32_t reg32;
};

void McDev::fill_fpri_ctrl_g2_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const fpri_ctrl_g2_u old_value_t = { .reg32 = value };
    const fpri_ctrl_g2_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: g2pr_prival:2",
              "0 = LOWEST;\n1 = LOW;\n2 = MED;\n3 = HIGH",
              2, old_value_t.g2pr_prival, new_value_t.g2pr_prival };
    m_bit_details_model.bits.append(entry);
    entry = { "02: g2sr_prival:2",
              "0 = LOWEST;\n1 = LOW;\n2 = MED;\n3 = HIGH",
              2, old_value_t.g2sr_prival, new_value_t.g2sr_prival };
    m_bit_details_model.bits.append(entry);
    entry = { "04: g2dr_prival:2",
              "0 = LOWEST;\n1 = LOW;\n2 = MED;\n3 = HIGH",
              2, old_value_t.g2dr_prival, new_value_t.g2dr_prival };
    m_bit_details_model.bits.append(entry);
    entry = { "06: g2dw_prival:2",
              "0 = LOWEST;\n1 = LOW;\n2 = MED;\n3 = HIGH",
              2, old_value_t.g2dw_prival, new_value_t.g2dw_prival };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_31:24", "", 24, old_value_t.undefined_bits_8_31, new_value_t.undefined_bits_8_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Reset value defaults to LOW for most clients, but may be different for certain clients\nFixed-priority Register for g2 clients";
}

#define FPRI_CTRL_HC_OFFSET 0x190
#define FPRI_CTRL_HC_UNDEFMASK 0xFFFFFFC0
union fpri_ctrl_hc_u {
    struct {
        unsigned int host1xdmar_prival:2;   /* 0 = LOWEST; 1 = LOW; 2 = MED; 3 = HIGH */
        unsigned int host1xr_prival:2;      /* 0 = LOWEST; 1 = LOW; 2 = MED; 3 = HIGH */
        unsigned int host1xw_prival:2;      /* 0 = LOWEST; 1 = LOW; 2 = MED; 3 = HIGH */
        unsigned int undefined_bits_6_31:26;
    };

    u_int32_t reg32;
};

void McDev::fill_fpri_ctrl_hc_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const fpri_ctrl_hc_u old_value_t = { .reg32 = value };
    const fpri_ctrl_hc_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: host1xdmar_prival:2",
              "0 = LOWEST;\n1 = LOW;\n2 = MED;\n3 = HIGH",
              2, old_value_t.host1xdmar_prival, new_value_t.host1xdmar_prival };
    m_bit_details_model.bits.append(entry);
    entry = { "02: host1xr_prival:2",
              "0 = LOWEST;\n1 = LOW;\n2 = MED;\n3 = HIGH",
              2, old_value_t.host1xr_prival, new_value_t.host1xr_prival };
    m_bit_details_model.bits.append(entry);
    entry = { "04: host1xw_prival:2",
              "0 = LOWEST;\n1 = LOW;\n2 = MED;\n3 = HIGH",
              2, old_value_t.host1xw_prival, new_value_t.host1xw_prival };
    m_bit_details_model.bits.append(entry);
    entry = { "06: undefined_bits_6_31:26", "", 26, old_value_t.undefined_bits_6_31, new_value_t.undefined_bits_6_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Reset value defaults to LOW for most clients, but may be different for certain clients.\nFixed-priority Register for hc clients";
}

#define FPRI_CTRL_ISP_OFFSET 0x194
#define FPRI_CTRL_ISP_UNDEFMASK 0xFFFFFFFC
union fpri_ctrl_isp_u {
    struct {
        unsigned int ispw_prival:2;         /* 0 = LOWEST; 1 = LOW; 2 = MED; 3 = HIGH */
        unsigned int undefined_bits_2_31:30;
    };

    u_int32_t reg32;
};

void McDev::fill_fpri_ctrl_isp_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const fpri_ctrl_isp_u old_value_t = { .reg32 = value };
    const fpri_ctrl_isp_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: ispw_prival:2",
              "0 = LOWEST;\n1 = LOW;\n2 = MED;\n3 = HIGH",
              2, old_value_t.ispw_prival, new_value_t.ispw_prival };
    m_bit_details_model.bits.append(entry);
    entry = { "02: undefined_bits_2_31:30", "", 30, old_value_t.undefined_bits_2_31, new_value_t.undefined_bits_2_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Reset value defaults to LOW for most clients, but may be different for certain clients.\nFixed-priority Register for isp clients";
}

#define FPRI_CTRL_MPCORE_OFFSET 0x198
#define FPRI_CTRL_MPCORE_UNDEFMASK 0xFFFFFFF0
union fpri_ctrl_mpcore_u {
    struct {
        unsigned int mpcorer_prival:2;      /* 0 = LOWEST; 1 = LOW; 2 = MED; 3 = HIGH */
        unsigned int mpcorew_prival:2;      /* 0 = LOWEST; 1 = LOW; 2 = MED; 3 = HIGH */
        unsigned int undefined_bits_4_31:28;
    };

    u_int32_t reg32;
};

void McDev::fill_fpri_ctrl_mpcore_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const fpri_ctrl_mpcore_u old_value_t = { .reg32 = value };
    const fpri_ctrl_mpcore_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: mpcorer_prival:2",
              "0 = LOWEST;\n1 = LOW;\n2 = MED;\n3 = HIGH",
              2, old_value_t.mpcorer_prival, new_value_t.mpcorer_prival };
    m_bit_details_model.bits.append(entry);
    entry = { "02: mpcorew_prival:2",
              "0 = LOWEST;\n1 = LOW;\n2 = MED;\n3 = HIGH",
              2, old_value_t.mpcorew_prival, new_value_t.mpcorew_prival };
    m_bit_details_model.bits.append(entry);
    entry = { "04: undefined_bits_4_31:28", "", 28, old_value_t.undefined_bits_4_31, new_value_t.undefined_bits_4_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Reset value defaults to LOW for most clients, but may be different for certain clients.\nFixed-priority Register for CPU clients";
}

#define FPRI_CTRL_MPEA_OFFSET 0x19C
#define FPRI_CTRL_MPEA_UNDEFMASK 0xFFFFFFFC
union fpri_ctrl_mpea_u {
    struct {
        unsigned int mpeamemrd_prival:2;    /* 0 = LOWEST; 1 = LOW; 2 = MED; 3 = HIGH */
        unsigned int undefined_bits_2_31:30;
    };

    u_int32_t reg32;
};

void McDev::fill_fpri_ctrl_mpea_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const fpri_ctrl_mpea_u old_value_t = { .reg32 = value };
    const fpri_ctrl_mpea_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: mpeamemrd_prival:2",
              "0 = LOWEST;\n1 = LOW;\n2 = MED;\n3 = HIGH",
              2, old_value_t.mpeamemrd_prival, new_value_t.mpeamemrd_prival };
    m_bit_details_model.bits.append(entry);
    entry = { "02: undefined_bits_2_31:30", "", 30, old_value_t.undefined_bits_2_31, new_value_t.undefined_bits_2_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Reset value defaults to LOW for most clients, but may be different for certain clients.\nFixed-priority Register for mpea clients";
}

#define FPRI_CTRL_MPEB_OFFSET 0x1A0
#define FPRI_CTRL_MPEB_UNDEFMASK 0xFFFFFFC0
union fpri_ctrl_mpeb_u {
    struct {
        unsigned int mpeunifbr_prival:2;    /* 0 = LOWEST; 1 = LOW; 2 = MED; 3 = HIGH */
        unsigned int mpe_ipred_prival:2;    /* 0 = LOWEST; 1 = LOW; 2 = MED; 3 = HIGH */
        unsigned int mpeunifbw_prival:2;    /* 0 = LOWEST; 1 = LOW; 2 = MED; 3 = HIGH */
        unsigned int undefined_bits_6_31:26;
    };

    u_int32_t reg32;
};

void McDev::fill_fpri_ctrl_mpeb_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const fpri_ctrl_mpeb_u old_value_t = { .reg32 = value };
    const fpri_ctrl_mpeb_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: mpeunifbr_prival:2",
              "0 = LOWEST;\n1 = LOW;\n2 = MED;\n3 = HIGH",
              2, old_value_t.mpeunifbr_prival, new_value_t.mpeunifbr_prival };
    m_bit_details_model.bits.append(entry);
    entry = { "02: mpe_ipred_prival:2",
              "0 = LOWEST;\n1 = LOW;\n2 = MED;\n3 = HIGH",
              2, old_value_t.mpe_ipred_prival, new_value_t.mpe_ipred_prival };
    m_bit_details_model.bits.append(entry);
    entry = { "04: mpeunifbw_prival:2",
              "0 = LOWEST;\n1 = LOW;\n2 = MED;\n3 = HIGH",
              2, old_value_t.mpeunifbw_prival, new_value_t.mpeunifbw_prival };
    m_bit_details_model.bits.append(entry);
    entry = { "06: undefined_bits_6_31:26", "", 26, old_value_t.undefined_bits_6_31, new_value_t.undefined_bits_6_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Reset value defaults to LOW for most clients, but may be different for certain clients.\nFixed-priority Register for mpeb clients";
}

#define FPRI_CTRL_MPEC_OFFSET 0x1A4
#define FPRI_CTRL_MPEC_UNDEFMASK 0xFFFFFFF0
union fpri_ctrl_mpec_u {
    struct {
        unsigned int mpecsrd_prival:2;      /* 0 = LOWEST; 1 = LOW; 2 = MED; 3 = HIGH */
        unsigned int mpecswr_prival:2;      /* 0 = LOWEST; 1 = LOW; 2 = MED; 3 = HIGH */
        unsigned int undefined_bits_4_31:28;
    };

    u_int32_t reg32;
};

void McDev::fill_fpri_ctrl_mpec_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const fpri_ctrl_mpec_u old_value_t = { .reg32 = value };
    const fpri_ctrl_mpec_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: mpecsrd_prival:2",
              "0 = LOWEST;\n1 = LOW;\n2 = MED;\n3 = HIGH",
              2, old_value_t.mpecsrd_prival, new_value_t.mpecsrd_prival };
    m_bit_details_model.bits.append(entry);
    entry = { "02: mpecswr_prival:2",
              "0 = LOWEST;\n1 = LOW;\n2 = MED;\n3 = HIGH",
              2, old_value_t.mpecswr_prival, new_value_t.mpecswr_prival };
    m_bit_details_model.bits.append(entry);
    entry = { "04: undefined_bits_4_31:28", "", 28, old_value_t.undefined_bits_4_31, new_value_t.undefined_bits_4_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Reset value defaults to LOW for most clients, but may be different for certain clients.\nFixed-priority Register for mpec clients";
}

#define FPRI_CTRL_NV_OFFSET 0x1A8
#define FPRI_CTRL_NV_UNDEFMASK 0xFFFFFF00
union fpri_ctrl_nv_u {
    struct {
        unsigned int fdcdrd_prival:2;       /* 0 = LOWEST; 1 = LOW; 2 = MED; 3 = HIGH */
        unsigned int idxsrd_prival:2;       /* 0 = LOWEST; 1 = LOW; 2 = MED; 3 = HIGH */
        unsigned int texsrd_prival:2;       /* 0 = LOWEST; 1 = LOW; 2 = MED; 3 = HIGH */
        unsigned int fdcdwr_prival:2;       /* 0 = LOWEST; 1 = LOW; 2 = MED; 3 = HIGH */
        unsigned int undefined_bits_8_31:24;
    };

    u_int32_t reg32;
};

void McDev::fill_fpri_ctrl_nv_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const fpri_ctrl_nv_u old_value_t = { .reg32 = value };
    const fpri_ctrl_nv_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: fdcdrd_prival:2",
              "0 = LOWEST;\n1 = LOW;\n2 = MED;\n3 = HIGH",
              2, old_value_t.fdcdrd_prival, new_value_t.fdcdrd_prival };
    m_bit_details_model.bits.append(entry);
    entry = { "02: idxsrd_prival:2",
              "0 = LOWEST;\n1 = LOW;\n2 = MED;\n3 = HIGH",
              2, old_value_t.idxsrd_prival, new_value_t.idxsrd_prival };
    m_bit_details_model.bits.append(entry);
    entry = { "04: texsrd_prival:2",
              "0 = LOWEST;\n1 = LOW;\n2 = MED;\n3 = HIGH",
              2, old_value_t.texsrd_prival, new_value_t.texsrd_prival };
    m_bit_details_model.bits.append(entry);
    entry = { "06: fdcdwr_prival:2",
              "0 = LOWEST;\n1 = LOW;\n2 = MED;\n3 = HIGH",
              2, old_value_t.fdcdwr_prival, new_value_t.fdcdwr_prival };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_31:24", "", 24, old_value_t.undefined_bits_8_31, new_value_t.undefined_bits_8_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Reset value defaults to LOW for most clients, but may be different for certain clients.\nFixed-priority Register for nv clients";
}

#define FPRI_CTRL_PPCS_OFFSET 0x1AC
#define FPRI_CTRL_PPCS_UNDEFMASK 0xFFFFFF00
union fpri_ctrl_ppcs_u {
    struct {
        unsigned int ppcsahbdmar_prival:2;  /* 0 = LOWEST; 1 = LOW; 2 = MED; 3 = HIGH */
        unsigned int ppcsahbslvr_prival:2;  /* 0 = LOWEST; 1 = LOW; 2 = MED; 3 = HIGH */
        unsigned int ppcsahbdmaw_prival:2;
        unsigned int ppcsahbslvw_prival:2;
        unsigned int undefined_bits_8_31:24;
    };

    u_int32_t reg32;
};

void McDev::fill_fpri_ctrl_ppcs_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const fpri_ctrl_ppcs_u old_value_t = { .reg32 = value };
    const fpri_ctrl_ppcs_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: ppcsahbdmar_prival:2",
              "0 = LOWEST;\n1 = LOW;\n2 = MED;\n3 = HIGH",
              2, old_value_t.ppcsahbdmar_prival, new_value_t.ppcsahbdmar_prival };
    m_bit_details_model.bits.append(entry);
    entry = { "02: ppcsahbslvr_prival:2",
              "0 = LOWEST;\n1 = LOW;\n2 = MED;\n3 = HIGH",
              2, old_value_t.ppcsahbslvr_prival, new_value_t.ppcsahbslvr_prival };
    m_bit_details_model.bits.append(entry);
    entry = { "04: ppcsahbdmaw_prival:2", "", 2, old_value_t.ppcsahbdmaw_prival, new_value_t.ppcsahbdmaw_prival };
    m_bit_details_model.bits.append(entry);
    entry = { "06: ppcsahbslvw_prival:2", "", 2, old_value_t.ppcsahbslvw_prival, new_value_t.ppcsahbslvw_prival };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_31:24", "", 24, old_value_t.undefined_bits_8_31, new_value_t.undefined_bits_8_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Reset value defaults to LOW for most clients, but may be different for certain clients.\nFixed-priority Register for ppcs clients";
}

#define FPRI_CTRL_VDE_OFFSET 0x1B0
#define FPRI_CTRL_VDE_UNDEFMASK 0xFFFFC000
union fpri_ctrl_vde_u {
    struct {
        unsigned int vdebsevr_prival:2;     /* 0 = LOWEST; 1 = LOW; 2 = MED; 3 = HIGH */
        unsigned int vdember_prival:2;      /* 0 = LOWEST; 1 = LOW; 2 = MED; 3 = HIGH */
        unsigned int vdemcer_prival:2;      /* 0 = LOWEST; 1 = LOW; 2 = MED; 3 = HIGH */
        unsigned int vdetper_prival:2;      /* 0 = LOWEST; 1 = LOW; 2 = MED; 3 = HIGH */
        unsigned int vdebsevw_prival:2;     /* 0 = LOWEST; 1 = LOW; 2 = MED; 3 = HIGH */
        unsigned int vdembew_prival:2;      /* 0 = LOWEST; 1 = LOW; 2 = MED; 3 = HIGH */
        unsigned int vdetpmw_prival:2;      /* 0 = LOWEST; 1 = LOW; 2 = MED; 3 = HIGH */
        unsigned int undefined_bits_14_31:18;
    };

    u_int32_t reg32;
};

void McDev::fill_fpri_ctrl_vde_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const fpri_ctrl_vde_u old_value_t = { .reg32 = value };
    const fpri_ctrl_vde_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: vdebsevr_prival:2",
              "0 = LOWEST;\n1 = LOW;\n2 = MED;\n3 = HIGH",
              2, old_value_t.vdebsevr_prival, new_value_t.vdebsevr_prival };
    m_bit_details_model.bits.append(entry);
    entry = { "02: vdember_prival:2",
              "0 = LOWEST;\n1 = LOW;\n2 = MED;\n3 = HIGH",
              2, old_value_t.vdember_prival, new_value_t.vdember_prival };
    m_bit_details_model.bits.append(entry);
    entry = { "04: vdemcer_prival:2",
              "0 = LOWEST;\n1 = LOW;\n2 = MED;\n3 = HIGH",
              2, old_value_t.vdemcer_prival, new_value_t.vdemcer_prival };
    m_bit_details_model.bits.append(entry);
    entry = { "06: vdetper_prival:2",
              "0 = LOWEST;\n1 = LOW;\n2 = MED;\n3 = HIGH",
              2, old_value_t.vdetper_prival, new_value_t.vdetper_prival };
    m_bit_details_model.bits.append(entry);
    entry = { "08: vdebsevw_prival:2",
              "0 = LOWEST;\n1 = LOW;\n2 = MED;\n3 = HIGH",
              2, old_value_t.vdebsevw_prival, new_value_t.vdebsevw_prival };
    m_bit_details_model.bits.append(entry);
    entry = { "10: vdembew_prival:2",
              "0 = LOWEST;\n1 = LOW;\n2 = MED;\n3 = HIGH",
              2, old_value_t.vdembew_prival, new_value_t.vdembew_prival };
    m_bit_details_model.bits.append(entry);
    entry = { "12: vdetpmw_prival:2",
              "0 = LOWEST;\n1 = LOW;\n2 = MED;\n3 = HIGH",
              2, old_value_t.vdetpmw_prival, new_value_t.vdetpmw_prival };
    m_bit_details_model.bits.append(entry);
    entry = { "14: undefined_bits_14_31:18", "", 18, old_value_t.undefined_bits_14_31, new_value_t.undefined_bits_14_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Reset value defaults to LOW for most clients, but may be different for certain clients.\nFixed-priority Register for vde clients";
}

#define FPRI_CTRL_VI_OFFSET 0x1B4
#define FPRI_CTRL_VI_UNDEFMASK 0xFFFFFC00
union fpri_ctrl_vi_u {
    struct {
        unsigned int viruv_prival:2;        /* 0 = LOWEST; 1 = LOW; 2 = MED; 3 = HIGH */
        unsigned int viwsb_prival:2;        /* 0 = LOWEST; 1 = LOW; 2 = MED; 3 = HIGH */
        unsigned int viwu_prival:2;         /* 0 = LOWEST; 1 = LOW; 2 = MED; 3 = HIGH */
        unsigned int viwv_prival:2;         /* 0 = LOWEST; 1 = LOW; 2 = MED; 3 = HIGH */
        unsigned int viwy_prival:2;         /* 0 = LOWEST; 1 = LOW; 2 = MED; 3 = HIGH */
        unsigned int undefined_bits_10_31:22;
    };

    u_int32_t reg32;
};

void McDev::fill_fpri_ctrl_vi_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const fpri_ctrl_vi_u old_value_t = { .reg32 = value };
    const fpri_ctrl_vi_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: viruv_prival:2",
              "0 = LOWEST;\n1 = LOW;\n2 = MED;\n3 = HIGH",
              2, old_value_t.viruv_prival, new_value_t.viruv_prival };
    m_bit_details_model.bits.append(entry);
    entry = { "02: viwsb_prival:2",
              "0 = LOWEST;\n1 = LOW;\n2 = MED;\n3 = HIGH",
              2, old_value_t.viwsb_prival, new_value_t.viwsb_prival };
    m_bit_details_model.bits.append(entry);
    entry = { "04: viwu_prival:2",
              "0 = LOWEST;\n1 = LOW;\n2 = MED;\n3 = HIGH",
              2, old_value_t.viwu_prival, new_value_t.viwu_prival };
    m_bit_details_model.bits.append(entry);
    entry = { "06: viwv_prival:2",
              "0 = LOWEST;\n1 = LOW;\n2 = MED;\n3 = HIGH",
              2, old_value_t.viwv_prival, new_value_t.viwv_prival };
    m_bit_details_model.bits.append(entry);
    entry = { "08: viwy_prival:2",
              "0 = LOWEST;\n1 = LOW;\n2 = MED;\n3 = HIGH",
              2, old_value_t.viwy_prival, new_value_t.viwy_prival };
    m_bit_details_model.bits.append(entry);
    entry = { "10: undefined_bits_10_31:22", "", 22, old_value_t.undefined_bits_10_31, new_value_t.undefined_bits_10_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Reset value defaults to LOW for most clients, but may be different for certain clients.\nFixed-priority Register for vi clients";
}

#define TIMEOUT_AVPC_OFFSET 0x1B8
#define TIMEOUT_AVPC_UNDEFMASK 0xFFFFFF00
union timeout_avpc_u {
    struct {
        unsigned int avpcarm7r_tmval:4;
        unsigned int avpcarm7w_tmval:4;
        unsigned int undefined_bits_8_31:24;
    };

    u_int32_t reg32;
};

void McDev::fill_timeout_avpc_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const timeout_avpc_u old_value_t = { .reg32 = value };
    const timeout_avpc_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: avpcarm7r_tmval:4", "", 4, old_value_t.avpcarm7r_tmval, new_value_t.avpcarm7r_tmval };
    m_bit_details_model.bits.append(entry);
    entry = { "04: avpcarm7w_tmval:4", "", 4, old_value_t.avpcarm7w_tmval, new_value_t.avpcarm7w_tmval };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_31:24", "", 24, old_value_t.undefined_bits_8_31, new_value_t.undefined_bits_8_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Reset value defaults to 8 for most clients, but may be different for certain clients If not zero, the client request time-out counter is reloaded with this value when it reaches zero. It is decremented when there is a pending request and the time-out clock counter for the request destination (internal/external memory) reaches zero.\nWhen the client request time-out counter reaches zero, a number of time-out credits equal to the number of its requests pending inside the memory controller client FIFO are allocated to this client.\nThe number of time-out credits is decremented each time a request is granted. As long as there are credits, the client time-out priority bit is set.\nRequest time-out Register for AVPC clients";
}

#define TIMEOUT_DC_OFFSET 0x1BC
#define TIMEOUT_DC_UNDEFMASK 0xFFF00000
union timeout_dc_u {
    struct {
        unsigned int display0a_tmval:4;
        unsigned int display0b_tmval:4;
        unsigned int display0c_tmval:4;
        unsigned int display1b_tmval:4;
        unsigned int displayhc_tmval:4;
        unsigned int undefined_bits_20_31:12;
    };

    u_int32_t reg32;
};

void McDev::fill_timeout_dc_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const timeout_dc_u old_value_t = { .reg32 = value };
    const timeout_dc_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: display0a_tmval:4", "", 4, old_value_t.display0a_tmval, new_value_t.display0a_tmval };
    m_bit_details_model.bits.append(entry);
    entry = { "04: display0b_tmval:4", "", 4, old_value_t.display0b_tmval, new_value_t.display0b_tmval };
    m_bit_details_model.bits.append(entry);
    entry = { "08: display0c_tmval:4", "", 4, old_value_t.display0c_tmval, new_value_t.display0c_tmval };
    m_bit_details_model.bits.append(entry);
    entry = { "12: display1b_tmval:4", "", 4, old_value_t.display1b_tmval, new_value_t.display1b_tmval };
    m_bit_details_model.bits.append(entry);
    entry = { "16: displayhc_tmval:4", "", 4, old_value_t.displayhc_tmval, new_value_t.displayhc_tmval };
    m_bit_details_model.bits.append(entry);
    entry = { "20: undefined_bits_20_31:12", "", 12, old_value_t.undefined_bits_20_31, new_value_t.undefined_bits_20_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Reset value defaults to 8 for most clients, but may be different for certain clients. If not zero, the client request time-out counter is reloaded with this value when it reaches zero. It is decremented when there is a pending request and the time-out clock counter for the request destination (internal/external memory) reaches zero.\nWhen the client request time-out counter reaches zero, a number of time-out credits equal to the number of its requests pending inside the memory controller client FIFO are allocated to this client.\nThe number of time-out credits is decremented each time a request is granted. As long as there are credits, the client time-out priority bit is set.\nRequest time-out Register for dc clients";
}

#define TIMEOUT_DCB_OFFSET 0x1C0
#define TIMEOUT_DCB_UNDEFMASK 0xFFF00000
union timeout_dcb_u {
    struct {
        unsigned int display0ab_tmval:4;
        unsigned int display0bb_tmval:4;
        unsigned int display0cb_tmval:4;
        unsigned int display1bb_tmval:4;
        unsigned int displayhcb_tmval:4;
        unsigned int undefined_bits_20_31:12;
    };

    u_int32_t reg32;
};

void McDev::fill_timeout_dcb_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const timeout_dcb_u old_value_t = { .reg32 = value };
    const timeout_dcb_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: display0ab_tmval:4", "", 4, old_value_t.display0ab_tmval, new_value_t.display0ab_tmval };
    m_bit_details_model.bits.append(entry);
    entry = { "04: display0bb_tmval:4", "", 4, old_value_t.display0bb_tmval, new_value_t.display0bb_tmval };
    m_bit_details_model.bits.append(entry);
    entry = { "08: display0cb_tmval:4", "", 4, old_value_t.display0cb_tmval, new_value_t.display0cb_tmval };
    m_bit_details_model.bits.append(entry);
    entry = { "12: display1bb_tmval:4", "", 4, old_value_t.display1bb_tmval, new_value_t.display1bb_tmval };
    m_bit_details_model.bits.append(entry);
    entry = { "16: displayhcb_tmval:4", "", 4, old_value_t.displayhcb_tmval, new_value_t.displayhcb_tmval };
    m_bit_details_model.bits.append(entry);
    entry = { "20: undefined_bits_20_31:12", "", 12, old_value_t.undefined_bits_20_31, new_value_t.undefined_bits_20_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Reset value defaults to 8 for most clients, but may be different for certain clients. If not zero, the client request time-out counter is reloaded with this value when it reaches zero. It is decremented when there is a pending request and the time-out clock counter for the request destination (internal/external memory) reaches zero.\nWhen the client request time-out counter reaches zero, a number of time-out credits equal to the number of its requests pending inside the memory controller client FIFO are allocated to this client.\nThe number of time-out credits is decremented each time a request is granted. As long as there are credits, the client time-out priority bit is set.\nRequest time-out Register for dcb clients";
}

#define TIMEOUT_EPP_OFFSET 0x1C4
#define TIMEOUT_EPP_UNDEFMASK 0xFFFF0000
union timeout_epp_u {
    struct {
        unsigned int eppup_tmval:4;
        unsigned int eppu_tmval:4;
        unsigned int eppv_tmval:4;
        unsigned int eppy_tmval:4;
        unsigned int undefined_bits_16_31:16;
    };

    u_int32_t reg32;
};

void McDev::fill_timeout_epp_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const timeout_epp_u old_value_t = { .reg32 = value };
    const timeout_epp_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: eppup_tmval:4", "", 4, old_value_t.eppup_tmval, new_value_t.eppup_tmval };
    m_bit_details_model.bits.append(entry);
    entry = { "04: eppu_tmval:4", "", 4, old_value_t.eppu_tmval, new_value_t.eppu_tmval };
    m_bit_details_model.bits.append(entry);
    entry = { "08: eppv_tmval:4", "", 4, old_value_t.eppv_tmval, new_value_t.eppv_tmval };
    m_bit_details_model.bits.append(entry);
    entry = { "12: eppy_tmval:4", "", 4, old_value_t.eppy_tmval, new_value_t.eppy_tmval };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_31:16", "", 16, old_value_t.undefined_bits_16_31, new_value_t.undefined_bits_16_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Reset value defaults to 8 for most clients, but may be different for certain clients. If not zero, the client request time-out counter is reloaded with this value when it reaches zero. It is decremented when there is a pending request and the time-out clock counter for the request destination (internal/external memory) reaches zero.\nWhen the client request time-out counter reaches zero, a number of time-out credits equal to the number of its requests pending inside the memory controller client FIFO are allocated to this client.\nThe number of time-out credits is decremented each time a request is granted. As long as there are credits, the client time-out priority bit is set.\nRequest time-out Register for epp clients";
}

#define TIMEOUT_G2_OFFSET 0x1C8
#define TIMEOUT_G2_UNDEFMASK 0xFFFF0000
union timeout_g2_u {
    struct {
        unsigned int g2pr_tmval:4;
        unsigned int g2sr_tmval:4;
        unsigned int g2dr_tmval:4;
        unsigned int g2dw_tmval:4;
        unsigned int undefined_bits_16_31:16;
    };

    u_int32_t reg32;
};

void McDev::fill_timeout_g2_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const timeout_g2_u old_value_t = { .reg32 = value };
    const timeout_g2_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: g2pr_tmval:4", "", 4, old_value_t.g2pr_tmval, new_value_t.g2pr_tmval };
    m_bit_details_model.bits.append(entry);
    entry = { "04: g2sr_tmval:4", "", 4, old_value_t.g2sr_tmval, new_value_t.g2sr_tmval };
    m_bit_details_model.bits.append(entry);
    entry = { "08: g2dr_tmval:4", "", 4, old_value_t.g2dr_tmval, new_value_t.g2dr_tmval };
    m_bit_details_model.bits.append(entry);
    entry = { "12: g2dw_tmval:4", "", 4, old_value_t.g2dw_tmval, new_value_t.g2dw_tmval };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_31:16", "", 16, old_value_t.undefined_bits_16_31, new_value_t.undefined_bits_16_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Reset value defaults to 8 for most clients, but may be different for certain clients. If not zero, the client request time-out counter is reloaded with this value when it reaches zero. It is decremented when there is a pending request and the time-out clock counter for the request destination (internal/external memory) reaches zero.\nWhen the client request time-out counter reaches zero, a number of time-out credits equal to the number of its requests pending inside the memory controller client FIFO are allocated to this client.\nThe number of time-out credits is decremented each time a request is granted. As long as there are credits, the client time-out priority bit is set.\nRequest time-out Register for g2 clients";
}

#define TIMEOUT_HC_OFFSET 0x1CC
#define TIMEOUT_HC_UNDEFMASK 0xFFFFF000
union timeout_hc_u {
    struct {
        unsigned int host1xdmar_tmval:4;
        unsigned int host1xr_tmval:4;
        unsigned int host1xw_tmval:4;
        unsigned int undefined_bits_12_31:20;
    };

    u_int32_t reg32;
};

void McDev::fill_timeout_hc_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const timeout_hc_u old_value_t = { .reg32 = value };
    const timeout_hc_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: host1xdmar_tmval:4", "", 4, old_value_t.host1xdmar_tmval, new_value_t.host1xdmar_tmval };
    m_bit_details_model.bits.append(entry);
    entry = { "04: host1xr_tmval:4", "", 4, old_value_t.host1xr_tmval, new_value_t.host1xr_tmval };
    m_bit_details_model.bits.append(entry);
    entry = { "08: host1xw_tmval:4", "", 4, old_value_t.host1xw_tmval, new_value_t.host1xw_tmval };
    m_bit_details_model.bits.append(entry);
    entry = { "12: undefined_bits_12_31:20", "", 20, old_value_t.undefined_bits_12_31, new_value_t.undefined_bits_12_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Reset value defaults to 8 for most clients, but may be different for certain clients. If not zero, the client request time-out counter is reloaded with this value when it reaches zero. It is decremented when there is a pending request and the time-out clock counter for the request destination (internal/external memory) reaches zero.\nWhen the client request time-out counter reaches zero, a number of time-out credits equal to the number of its requests pending inside the memory controller client FIFO are allocated to this client.\nThe number of time-out credits is decremented each time a request is granted. As long as there are credits, the client time-out priority bit is set.\nRequest time-out Register for hc clients";
}

#define TIMEOUT_ISP_OFFSET 0x1D0
#define TIMEOUT_ISP_UNDEFMASK 0xFFFFFFF0
union timeout_isp_u {
    struct {
        unsigned int ispw_tmval:4;
        unsigned int undefined_bits_4_31:28;
    };

    u_int32_t reg32;
};

void McDev::fill_timeout_isp_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const timeout_isp_u old_value_t = { .reg32 = value };
    const timeout_isp_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: ispw_tmval:4", "", 4, old_value_t.ispw_tmval, new_value_t.ispw_tmval };
    m_bit_details_model.bits.append(entry);
    entry = { "04: undefined_bits_4_31:28", "", 28, old_value_t.undefined_bits_4_31, new_value_t.undefined_bits_4_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Reset value defaults to 8 for most clients, but may be different for certain clients. If not zero, the client request time-out counter is reloaded with this value when it reaches zero. It is decremented when there is a pending request and the time-out clock counter for the request destination (internal/external memory) reaches zero.\nWhen the client request time-out counter reaches zero, a number of time-out credits equal to the number of its requests pending inside the memory controller client FIFO are allocated to this client.\nThe number of time-out credits is decremented each time a request is granted. As long as there are credits, the client time-out priority bit is set.\nRequest time-out Register for isp clients";
}

#define TIMEOUT_MPCORE_OFFSET 0x1D4
#define TIMEOUT_MPCORE_UNDEFMASK 0xFFFFFF00
union timeout_mpcore_u {
    struct {
        unsigned int mpcorer_tmval:4;
        unsigned int mpcorew_tmval:4;
        unsigned int undefined_bits_8_31:24;
    };

    u_int32_t reg32;
};

void McDev::fill_timeout_mpcore_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const timeout_mpcore_u old_value_t = { .reg32 = value };
    const timeout_mpcore_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: mpcorer_tmval:4", "", 4, old_value_t.mpcorer_tmval, new_value_t.mpcorer_tmval };
    m_bit_details_model.bits.append(entry);
    entry = { "04: mpcorew_tmval:4", "", 4, old_value_t.mpcorew_tmval, new_value_t.mpcorew_tmval };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_31:24", "", 24, old_value_t.undefined_bits_8_31, new_value_t.undefined_bits_8_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Reset value defaults to 8 for most clients, but may be different for certain clients. If not zero, the client request time-out counter is reloaded with this value when it reaches zero. It is decremented when there is a pending request and the time-out clock counter for the request destination (internal/external memory) reaches zero.\nWhen the client request time-out counter reaches zero, a number of time-out credits equal to the number of its requests pending inside the memory controller client FIFO are allocated to this client.\nThe number of time-out credits is decremented each time a request is granted. As long as there are credits, the client time-out priority bit is set.\nRequest time-out Register for CPU clients";
}

#define TIMEOUT_MPEA_OFFSET 0x1D8
#define TIMEOUT_MPEA_UNDEFMASK 0xFFFFFFF0
union timeout_mpea_u {
    struct {
        unsigned int mpeamemrd_tmval:4;
        unsigned int undefined_bits_4_31:28;
    };

    u_int32_t reg32;
};

void McDev::fill_timeout_mpea_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const timeout_mpea_u old_value_t = { .reg32 = value };
    const timeout_mpea_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: mpeamemrd_tmval:4", "", 4, old_value_t.mpeamemrd_tmval, new_value_t.mpeamemrd_tmval };
    m_bit_details_model.bits.append(entry);
    entry = { "04: undefined_bits_4_31:28", "", 28, old_value_t.undefined_bits_4_31, new_value_t.undefined_bits_4_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Reset value defaults to 8 for most clients, but may be different for certain clients. If not zero, the client request time-out counter is reloaded with this value when it reaches zero. It is decremented when there is a pending request and the time-out clock counter for the request destination (internal/external memory) reaches zero.\nWhen the client request time-out counter reaches zero, a number of time-out credits equal to the number of its requests pending inside the memory controller client FIFO are allocated to this client.\nThe number of time-out credits is decremented each time a request is granted. As long as there are credits, the client time-out priority bit is set.\nRequest time-out Register for mpea clients";
}

#define TIMEOUT_MPEB_OFFSET 0x1DC
#define TIMEOUT_MPEB_UNDEFMASK 0xFFFFF000
union timeout_mpeb_u {
    struct {
        unsigned int mpeunifbr_tmval:4;
        unsigned int mpe_ipred_tmval:4;
        unsigned int mpeunifbw_tmval:4;
        unsigned int undefined_bits_12_31:20;
    };

    u_int32_t reg32;
};

void McDev::fill_timeout_mpeb_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const timeout_mpeb_u old_value_t = { .reg32 = value };
    const timeout_mpeb_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: mpeunifbr_tmval:4", "", 4, old_value_t.mpeunifbr_tmval, new_value_t.mpeunifbr_tmval };
    m_bit_details_model.bits.append(entry);
    entry = { "04: mpe_ipred_tmval:4", "", 4, old_value_t.mpe_ipred_tmval, new_value_t.mpe_ipred_tmval };
    m_bit_details_model.bits.append(entry);
    entry = { "08: mpeunifbw_tmval:4", "", 4, old_value_t.mpeunifbw_tmval, new_value_t.mpeunifbw_tmval };
    m_bit_details_model.bits.append(entry);
    entry = { "12: undefined_bits_12_31:20", "", 20, old_value_t.undefined_bits_12_31, new_value_t.undefined_bits_12_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Reset value defaults to 8 for most clients, but may be different for certain clients. If not zero, the client request time-out counter is reloaded with this value when it reaches zero. It is decremented when there is a pending request and the time-out clock counter for the request destination (internal/external memory) reaches zero.\nWhen the client request time-out counter reaches zero, a number of time-out credits equal to the number of its requests pending inside the memory controller client FIFO are allocated to this client.\nThe number of time-out credits is decremented each time a request is granted. As long as there are credits, the client time-out priority bit is set.\nRequest time-out Register for mpeb clients";
}

#define TIMEOUT_MPEC_OFFSET 0x1E0
#define TIMEOUT_MPEC_UNDEFMASK 0xFFFFFF00
union timeout_mpec_u {
    struct {
        unsigned int mpecsrd_tmval:4;
        unsigned int mpecswr_tmval:4;
        unsigned int undefined_bits_8_31:24;
    };

    u_int32_t reg32;
};

void McDev::fill_timeout_mpec_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const timeout_mpec_u old_value_t = { .reg32 = value };
    const timeout_mpec_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: mpecsrd_tmval:4", "", 4, old_value_t.mpecsrd_tmval, new_value_t.mpecsrd_tmval };
    m_bit_details_model.bits.append(entry);
    entry = { "04: mpecswr_tmval:4", "", 4, old_value_t.mpecswr_tmval, new_value_t.mpecswr_tmval };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_31:24", "", 24, old_value_t.undefined_bits_8_31, new_value_t.undefined_bits_8_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Reset value defaults to 8 for most clients, but may be different for certain clients. If not zero, the client request time-out counter is reloaded with this value when it reaches zero. It is decremented when there is a pending request and the time-out clock counter for the request destination (internal/external memory) reaches zero.\nWhen the client request time-out counter reaches zero, a number of time-out credits equal to the number of its requests pending inside the memory controller client FIFO are allocated to this client.\nThe number of time-out credits is decremented each time a request is granted. As long as there are credits, the client time-out priority bit is set.\nRequest time-out Register for mpec clients";
}

#define TIMEOUT_NV_OFFSET 0x1E4
#define TIMEOUT_NV_UNDEFMASK 0xFFFF0000
union timeout_nv_u {
    struct {
        unsigned int fdcdrd_tmval:4;
        unsigned int idxsrd_tmval:4;
        unsigned int texsrd_tmval:4;
        unsigned int fdcdwr_tmval:4;
        unsigned int undefined_bits_16_31:16;
    };

    u_int32_t reg32;
};

void McDev::fill_timeout_nv_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const timeout_nv_u old_value_t = { .reg32 = value };
    const timeout_nv_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: fdcdrd_tmval:4", "", 4, old_value_t.fdcdrd_tmval, new_value_t.fdcdrd_tmval };
    m_bit_details_model.bits.append(entry);
    entry = { "04: idxsrd_tmval:4", "", 4, old_value_t.idxsrd_tmval, new_value_t.idxsrd_tmval };
    m_bit_details_model.bits.append(entry);
    entry = { "08: texsrd_tmval:4", "", 4, old_value_t.texsrd_tmval, new_value_t.texsrd_tmval };
    m_bit_details_model.bits.append(entry);
    entry = { "12: fdcdwr_tmval:4", "", 4, old_value_t.fdcdwr_tmval, new_value_t.fdcdwr_tmval };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_31:16", "", 16, old_value_t.undefined_bits_16_31, new_value_t.undefined_bits_16_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Reset value defaults to 8 for most clients, but may be different for certain clients. If not zero, the client request time-out counter is reloaded with this value when it reaches zero. It is decremented when there is a pending request and the time-out clock counter for the request destination (internal/external memory) reaches zero.\nWhen the client request time-out counter reaches zero, a number of time-out credits equal to the number of its requests pending inside the memory controller client FIFO are allocated to this client.\nThe number of time-out credits is decremented each time a request is granted. As long as there are credits, the client time-out priority bit is set.\nRequest time-out Register for nv clients";
}

#define TIMEOUT_PPCS_OFFSET 0x1E8
#define TIMEOUT_PPCS_UNDEFMASK 0xFFFF0000
union timeout_ppcs_u {
    struct {
        unsigned int ppcsahbdmar_tmval:4;
        unsigned int ppcsahbslvr_tmval:4;
        unsigned int ppcsahbdmaw_tmval:4;
        unsigned int ppcsahbslvw_tmval:4;
        unsigned int undefined_bits_16_31:16;
    };

    u_int32_t reg32;
};

void McDev::fill_timeout_ppcs_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const timeout_ppcs_u old_value_t = { .reg32 = value };
    const timeout_ppcs_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: ppcsahbdmar_tmval:4", "", 4, old_value_t.ppcsahbdmar_tmval, new_value_t.ppcsahbdmar_tmval };
    m_bit_details_model.bits.append(entry);
    entry = { "04: ppcsahbslvr_tmval:4", "", 4, old_value_t.ppcsahbslvr_tmval, new_value_t.ppcsahbslvr_tmval };
    m_bit_details_model.bits.append(entry);
    entry = { "08: ppcsahbdmaw_tmval:4", "", 4, old_value_t.ppcsahbdmaw_tmval, new_value_t.ppcsahbdmaw_tmval };
    m_bit_details_model.bits.append(entry);
    entry = { "12: ppcsahbslvw_tmval:4", "", 4, old_value_t.ppcsahbslvw_tmval, new_value_t.ppcsahbslvw_tmval };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_31:16", "", 16, old_value_t.undefined_bits_16_31, new_value_t.undefined_bits_16_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Reset value defaults to 8 for most clients, but may be different for certain clients. If not zero, the client request time-out counter is reloaded with this value when it reaches zero. It is decremented when there is a pending request and the time-out clock counter for the request destination (internal/external memory) reaches zero.\nWhen the client request time-out counter reaches zero, a number of time-out credits equal to the number of its requests pending inside the memory controller client FIFO are allocated to this client.\nThe number of time-out credits is decremented each time a request is granted. As long as there are credits, the client time-out priority bit is set.\nRequest time-out Register for ppcs clients";
}

#define TIMEOUT_VDE_OFFSET 0x1EC
#define TIMEOUT_VDE_UNDEFMASK 0xF0000000
union timeout_vde_u {
    struct {
        unsigned int vdebsevr_tmval:4;
        unsigned int vdember_tmval:4;
        unsigned int vdemcer_tmval:4;
        unsigned int vdetper_tmval:4;
        unsigned int vdebsevw_tmval:4;
        unsigned int vdembew_tmval:4;
        unsigned int vdetpmw_tmval:4;
        unsigned int undefined_bits_28_31:4;
    };

    u_int32_t reg32;
};

void McDev::fill_timeout_vde_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const timeout_vde_u old_value_t = { .reg32 = value };
    const timeout_vde_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: vdebsevr_tmval:4", "", 4, old_value_t.vdebsevr_tmval, new_value_t.vdebsevr_tmval };
    m_bit_details_model.bits.append(entry);
    entry = { "04: vdember_tmval:4", "", 4, old_value_t.vdember_tmval, new_value_t.vdember_tmval };
    m_bit_details_model.bits.append(entry);
    entry = { "08: vdemcer_tmval:4", "", 4, old_value_t.vdemcer_tmval, new_value_t.vdemcer_tmval };
    m_bit_details_model.bits.append(entry);
    entry = { "12: vdetper_tmval:4", "", 4, old_value_t.vdetper_tmval, new_value_t.vdetper_tmval };
    m_bit_details_model.bits.append(entry);
    entry = { "16: vdebsevw_tmval:4", "", 4, old_value_t.vdebsevw_tmval, new_value_t.vdebsevw_tmval };
    m_bit_details_model.bits.append(entry);
    entry = { "20: vdembew_tmval:4", "", 4, old_value_t.vdembew_tmval, new_value_t.vdembew_tmval };
    m_bit_details_model.bits.append(entry);
    entry = { "24: vdetpmw_tmval:4", "", 4, old_value_t.vdetpmw_tmval, new_value_t.vdetpmw_tmval };
    m_bit_details_model.bits.append(entry);
    entry = { "28: undefined_bits_28_31:4", "", 4, old_value_t.undefined_bits_28_31, new_value_t.undefined_bits_28_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Reset value defaults to 8 for most clients, but may be different for certain clients. If not zero, the client request time-out counter is reloaded with this value when it reaches zero. It is decremented when there is a pending request and the time-out clock counter for the request destination (internal/external memory) reaches zero.\nWhen the client request time-out counter reaches zero, a number of time-out credits equal to the number of its requests pending inside the memory controller client FIFO are allocated to this client.\nThe number of time-out credits is decremented each time a request is granted. As long as there are credits, the client time-out priority bit is set.\nRequest time-out Register for vde clients";
}

#define TIMEOUT_VI_OFFSET 0x1F0
#define TIMEOUT_VI_UNDEFMASK 0xFFF00000
union timeout_vi_u {
    struct {
        unsigned int viruv_tmval:4;
        unsigned int viwsb_tmval:4;
        unsigned int viwu_tmval:4;
        unsigned int viwv_tmval:4;
        unsigned int viwy_tmval:4;
        unsigned int undefined_bits_20_31:12;
    };

    u_int32_t reg32;
};

void McDev::fill_timeout_vi_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const timeout_vi_u old_value_t = { .reg32 = value };
    const timeout_vi_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: viruv_tmval:4", "", 4, old_value_t.viruv_tmval, new_value_t.viruv_tmval };
    m_bit_details_model.bits.append(entry);
    entry = { "04: viwsb_tmval:4", "", 4, old_value_t.viwsb_tmval, new_value_t.viwsb_tmval };
    m_bit_details_model.bits.append(entry);
    entry = { "08: viwu_tmval:4", "", 4, old_value_t.viwu_tmval, new_value_t.viwu_tmval };
    m_bit_details_model.bits.append(entry);
    entry = { "12: viwv_tmval:4", "", 4, old_value_t.viwv_tmval, new_value_t.viwv_tmval };
    m_bit_details_model.bits.append(entry);
    entry = { "16: viwy_tmval:4", "", 4, old_value_t.viwy_tmval, new_value_t.viwy_tmval };
    m_bit_details_model.bits.append(entry);
    entry = { "20: undefined_bits_20_31:12", "", 12, old_value_t.undefined_bits_20_31, new_value_t.undefined_bits_20_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Reset value defaults to 8 for most clients, but may be different for certain clients. If not zero, the client request time-out counter is reloaded with this value when it reaches zero. It is decremented when there is a pending request and the time-out clock counter for the request destination (internal/external memory) reaches zero.\nWhen the client request time-out counter reaches zero, a number of time-out credits equal to the number of its requests pending inside the memory controller client FIFO are allocated to this client.\nThe number of time-out credits is decremented each time a request is granted. As long as there are credits, the client time-out priority bit is set.\nRequest time-out Register for vi clients";
}

#define TIMEOUT_RCOAL_AVPC_OFFSET 0x1F4
#define TIMEOUT_RCOAL_AVPC_UNDEFMASK 0xFFFFFF00
union timeout_rcoal_avpc_u {
    struct {
        unsigned int avpcarm7r_rcoal_tmval:8;
        unsigned int undefined_bits_8_31:24;
    };

    u_int32_t reg32;
};

void McDev::fill_timeout_rcoal_avpc_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const timeout_rcoal_avpc_u old_value_t = { .reg32 = value };
    const timeout_rcoal_avpc_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: avpcarm7r_rcoal_tmval:8", "", 8, old_value_t.avpcarm7r_rcoal_tmval, new_value_t.avpcarm7r_rcoal_tmval };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_31:24", "", 24, old_value_t.undefined_bits_8_31, new_value_t.undefined_bits_8_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Read Coalescing time-out register for AVPC read clients";
}

#define TIMEOUT_RCOAL_DC_OFFSET 0x1F8
#define TIMEOUT_RCOAL_DC_UNDEFMASK 0x00000000
union timeout_rcoal_dc_u {
    struct {
        unsigned int display0a_rcoal_tmval:8;
        unsigned int display0b_rcoal_tmval:8;
        unsigned int display0c_rcoal_tmval:8;
        unsigned int display1b_rcoal_tmval:8;
    };

    u_int32_t reg32;
};

void McDev::fill_timeout_rcoal_dc_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const timeout_rcoal_dc_u old_value_t = { .reg32 = value };
    const timeout_rcoal_dc_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: display0a_rcoal_tmval:8", "", 8, old_value_t.display0a_rcoal_tmval, new_value_t.display0a_rcoal_tmval };
    m_bit_details_model.bits.append(entry);
    entry = { "08: display0b_rcoal_tmval:8", "", 8, old_value_t.display0b_rcoal_tmval, new_value_t.display0b_rcoal_tmval };
    m_bit_details_model.bits.append(entry);
    entry = { "16: display0c_rcoal_tmval:8", "", 8, old_value_t.display0c_rcoal_tmval, new_value_t.display0c_rcoal_tmval };
    m_bit_details_model.bits.append(entry);
    entry = { "24: display1b_rcoal_tmval:8", "", 8, old_value_t.display1b_rcoal_tmval, new_value_t.display1b_rcoal_tmval };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Reset value defaults to 4 for most clients, but may be different for certain clients. Read coalescing happens inside the memory controller, right before arbitration. Coalescing means two (NV_MC_MW/2)-bit requests are grouped together in one NV_MC_WM-bit request.\nThe register value indicates how many cycles a first write request is going to wait for a subsequent one for possible coalescing. The coalescing can only happen if the request addresses are compatible. A value of zero means that coalescing is off and requests are sent right away to the arbiters.\nRead coalescing can have a very significant impact performance when accessing the internal memory, because its memory word is NV_MC_WM-bit wide. Grouping two half-word accesses is much more efficient, because the two accesses would actually have taken three cycles, due to a stall when accessing the same memory bank. It also reduces the number of accessing (one instead of two), freeing up internal memory bandwidth for other accesses.\nThe impact on external memory accesses is not as significant as the burst access is for NV_MC_MW/2 bits. But a coalesced read guarantees two consecutive same page accesses which is good for external memory bandwidth utilization.\nThe read coalescing time-out should be programmed depending on the client behavior and the client versus memory controller clock ratio. The first read is obviously delayed by an amount of memory controller cycles equal to the time-out value.\nRead Coalescing time-out register for dc read clients";
}

#define TIMEOUT1_RCOAL_DC_OFFSET 0x1FC
#define TIMEOUT1_RCOAL_DC_UNDEFMASK 0xFFFFFF00
union timeout1_rcoal_dc_u {
    struct {
        unsigned int displayhc_rcoal_tmval:8;
        unsigned int undefined_bits_8_31:24;
    };

    u_int32_t reg32;
};

void McDev::fill_timeout1_rcoal_dc_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const timeout1_rcoal_dc_u old_value_t = { .reg32 = value };
    const timeout1_rcoal_dc_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: displayhc_rcoal_tmval:8", "", 8, old_value_t.displayhc_rcoal_tmval, new_value_t.displayhc_rcoal_tmval };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_31:24", "", 24, old_value_t.undefined_bits_8_31, new_value_t.undefined_bits_8_31 };
    m_bit_details_model.bits.append(entry);
}

#define TIMEOUT_RCOAL_DCB_OFFSET 0x200
#define TIMEOUT_RCOAL_DCB_UNDEFMASK 0x00000000
union timeout_rcoal_dcb_u {
    struct {
        unsigned int display0ab_rcoal_tmval:8;
        unsigned int display0bb_rcoal_tmval:8;
        unsigned int display0cb_rcoal_tmval:8;
        unsigned int display1bb_rcoal_tmval:8;
    };

    u_int32_t reg32;
};

void McDev::fill_timeout_rcoal_dcb_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const timeout_rcoal_dcb_u old_value_t = { .reg32 = value };
    const timeout_rcoal_dcb_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: display0ab_rcoal_tmval:8", "", 8, old_value_t.display0ab_rcoal_tmval, new_value_t.display0ab_rcoal_tmval };
    m_bit_details_model.bits.append(entry);
    entry = { "08: display0bb_rcoal_tmval:8", "", 8, old_value_t.display0bb_rcoal_tmval, new_value_t.display0bb_rcoal_tmval };
    m_bit_details_model.bits.append(entry);
    entry = { "16: display0cb_rcoal_tmval:8", "", 8, old_value_t.display0cb_rcoal_tmval, new_value_t.display0cb_rcoal_tmval };
    m_bit_details_model.bits.append(entry);
    entry = { "24: display1bb_rcoal_tmval:8", "", 8, old_value_t.display1bb_rcoal_tmval, new_value_t.display1bb_rcoal_tmval };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Reset value defaults to 4 for most clients, but may be different for certain clients. Read coalescing happens inside the memory controller, right before arbitration. Coalescing means two (NV_MC_MW/2)-bit requests are grouped together in one NV_MC_WM-bit request.\nThe register value indicates how many cycles a first write request is going to wait for a subsequent one for possible coalescing. The coalescing can only happen if the request addresses are compatible. A value of zero means that coalescing is off and requests are sent right away to the arbiters.\nRead coalescing can have a very significant impact performance when accessing the internal memory, because its memory word is NV_MC_WM-bit wide. Grouping two half-word accesses is much more efficient, because the two accesses would actually have taken three cycles, due to a stall when accessing the same memory bank. It also reduces the number of accessing (one instead of two), freeing up internal memory bandwidth for other accesses.\nThe impact on external memory accesses is not as significant as the burst access is for NV_MC_MW/2 bits. But a coalesced read guarantees two consecutive same page accesses which is good for external memory bandwidth utilization.\nThe read coalescing time-out should be programmed depending on the client behavior and the client versus memory controller clock ratio. The first read is obviously delayed by an amount of memory controller cycles equal to the time-out value.\nRead Coalescing time-out register for dcb read clients";
}

#define TIMEOUT1_RCOAL_DCB_OFFSET 0x204
#define TIMEOUT1_RCOAL_DCB_UNDEFMASK 0xFFFFFF00
union timeout1_rcoal_dcb_u {
    struct {
        unsigned int displayhcb_rcoal_tmval:8;
        unsigned int undefined_bits_8_31:24;
    };

    u_int32_t reg32;
};

void McDev::fill_timeout1_rcoal_dcb_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const timeout1_rcoal_dcb_u old_value_t = { .reg32 = value };
    const timeout1_rcoal_dcb_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: displayhcb_rcoal_tmval:8", "", 8, old_value_t.displayhcb_rcoal_tmval, new_value_t.displayhcb_rcoal_tmval };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_31:24", "", 24, old_value_t.undefined_bits_8_31, new_value_t.undefined_bits_8_31 };
    m_bit_details_model.bits.append(entry);
}

#define TIMEOUT_RCOAL_EPP_OFFSET 0x208
#define TIMEOUT_RCOAL_EPP_UNDEFMASK 0xFFFFFF00
union timeout_rcoal_epp_u {
    struct {
        unsigned int eppup_rcoal_tmval:8;
        unsigned int undefined_bits_8_31:24;
    };

    u_int32_t reg32;
};

void McDev::fill_timeout_rcoal_epp_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const timeout_rcoal_epp_u old_value_t = { .reg32 = value };
    const timeout_rcoal_epp_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: eppup_rcoal_tmval:8", "", 8, old_value_t.eppup_rcoal_tmval, new_value_t.eppup_rcoal_tmval };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_31:24", "", 24, old_value_t.undefined_bits_8_31, new_value_t.undefined_bits_8_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Reset value defaults to 4 for most clients, but may be different for certain clients. Read coalescing happens inside the memory controller, right before arbitration. Coalescing means two (NV_MC_MW/2)-bit requests are grouped together in one NV_MC_WM-bit request.\nThe register value indicates how many cycles a first write request is going to wait for a subsequent one for possible coalescing. The coalescing can only happen if the request addresses are compatible. A value of zero means that coalescing is off and requests are sent right away to the arbiters.\nRead coalescing can have a very significant impact performance when accessing the internal memory, because its memory word is NV_MC_WM-bit wide. Grouping two half-word accesses is much more efficient, because the two accesses would actually have taken three cycles, due to a stall when accessing the same memory bank. It also reduces the number of accessing (one instead of two), freeing up internal memory bandwidth for other accesses.\nThe impact on external memory accesses is not as significant as the burst access is for NV_MC_MW/2 bits. But a coalesced read guarantees two consecutive same page accesses which is good for external memory bandwidth utilization.\nThe read coalescing time-out should be programmed depending on the client behavior and the client versus memory controller clock ratio. The first read is obviously delayed by an amount of memory controller cycles equal to the time-out value.\nRead Coalescing time-out register for epp read clients";
}

#define TIMEOUT_RCOAL_G2_OFFSET 0x20C
#define TIMEOUT_RCOAL_G2_UNDEFMASK 0xFF000000
union timeout_rcoal_g2_u {
    struct {
        unsigned int g2pr_rcoal_tmval:8;
        unsigned int g2sr_rcoal_tmval:8;
        unsigned int g2dr_rcoal_tmval:8;
        unsigned int undefined_bits_24_31:8;
    };

    u_int32_t reg32;
};

void McDev::fill_timeout_rcoal_g2_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const timeout_rcoal_g2_u old_value_t = { .reg32 = value };
    const timeout_rcoal_g2_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: g2pr_rcoal_tmval:8", "", 8, old_value_t.g2pr_rcoal_tmval, new_value_t.g2pr_rcoal_tmval };
    m_bit_details_model.bits.append(entry);
    entry = { "08: g2sr_rcoal_tmval:8", "", 8, old_value_t.g2sr_rcoal_tmval, new_value_t.g2sr_rcoal_tmval };
    m_bit_details_model.bits.append(entry);
    entry = { "16: g2dr_rcoal_tmval:8", "", 8, old_value_t.g2dr_rcoal_tmval, new_value_t.g2dr_rcoal_tmval };
    m_bit_details_model.bits.append(entry);
    entry = { "24: undefined_bits_24_31:8", "", 8, old_value_t.undefined_bits_24_31, new_value_t.undefined_bits_24_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Reset value defaults to 4 for most clients, but may be different for certain clients. Read coalescing happens inside the memory controller, right before arbitration. Coalescing means two (NV_MC_MW/2)-bit requests are grouped together in one NV_MC_WM-bit request.\nThe register value indicates how many cycles a first write request is going to wait for a subsequent one for possible coalescing. The coalescing can only happen if the request addresses are compatible. A value of zero means that coalescing is off and requests are sent right away to the arbiters.\nRead coalescing can have a very significant impact performance when accessing the internal memory, because its memory word is NV_MC_WM-bit wide. Grouping two half-word accesses is much more efficient, because the two accesses would actually have taken three cycles, due to a stall when accessing the same memory bank. It also reduces the number of accessing (one instead of two), freeing up internal memory bandwidth for other accesses.\nThe impact on external memory accesses is not as significant as the burst access is for NV_MC_MW/2 bits. But a coalesced read guarantees two consecutive same page accesses which is good for external memory bandwidth utilization.\nThe read coalescing time-out should be programmed depending on the client behavior and the client versus memory controller clock ratio. The first read is obviously delayed by an amount of memory controller cycles equal to the time-out value.\nRead Coalescing time-out register for g2 read clients";
}

#define TIMEOUT_RCOAL_HC_OFFSET 0x210
#define TIMEOUT_RCOAL_HC_UNDEFMASK 0xFFFF0000
union timeout_rcoal_hc_u {
    struct {
        unsigned int host1xdmar_rcoal_tmval:8;
        unsigned int host1xr_rcoal_tmval:8;
        unsigned int undefined_bits_16_31:16;
    };

    u_int32_t reg32;
};

void McDev::fill_timeout_rcoal_hc_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const timeout_rcoal_hc_u old_value_t = { .reg32 = value };
    const timeout_rcoal_hc_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: host1xdmar_rcoal_tmval:8", "", 8, old_value_t.host1xdmar_rcoal_tmval, new_value_t.host1xdmar_rcoal_tmval };
    m_bit_details_model.bits.append(entry);
    entry = { "08: host1xr_rcoal_tmval:8", "", 8, old_value_t.host1xr_rcoal_tmval, new_value_t.host1xr_rcoal_tmval };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_31:16", "", 16, old_value_t.undefined_bits_16_31, new_value_t.undefined_bits_16_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Reset value defaults to 4 for most clients, but may be different for certain clients. Read coalescing happens inside the memory controller, right before arbitration. Coalescing means two (NV_MC_MW/2)-bit requests are grouped together in one NV_MC_WM-bit request.\nThe register value indicates how many cycles a first write request is going to wait for a subsequent one for possible coalescing. The coalescing can only happen if the request addresses are compatible. A value of zero means that coalescing is off and requests are sent right away to the arbiters.\nRead coalescing can have a very significant impact performance when accessing the internal memory, because its memory word is NV_MC_WM-bit wide. Grouping two half-word accesses is much more efficient, because the two accesses would actually have taken three cycles, due to a stall when accessing the same memory bank. It also reduces the number of accessing (one instead of two), freeing up internal memory bandwidth for other accesses.\nThe impact on external memory accesses is not as significant as the burst access is for NV_MC_MW/2 bits. But a coalesced read guarantees two consecutive same page accesses which is good for external memory bandwidth utilization.\nThe read coalescing time-out should be programmed depending on the client behavior and the client versus memory controller clock ratio. The first read is obviously delayed by an amount of memory controller cycles equal to the time-out value.\nRead Coalescing time-out register for hc read clients";
}

#define TIMEOUT_RCOAL_MPCORE_OFFSET 0x214
#define TIMEOUT_RCOAL_MPCORE_UNDEFMASK 0xFFFFFF00
union timeout_rcoal_mpcore_u {
    struct {
        unsigned int mpcorer_rcoal_tmval:8;
        unsigned int undefined_bits_8_31:24;
    };

    u_int32_t reg32;
};

void McDev::fill_timeout_rcoal_mpcore_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const timeout_rcoal_mpcore_u old_value_t = { .reg32 = value };
    const timeout_rcoal_mpcore_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: mpcorer_rcoal_tmval:8", "", 8, old_value_t.mpcorer_rcoal_tmval, new_value_t.mpcorer_rcoal_tmval };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_31:24", "", 24, old_value_t.undefined_bits_8_31, new_value_t.undefined_bits_8_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Reset value defaults to 4 for most clients, but may be different for certain clients. Read coalescing happens inside the memory controller, right before arbitration. Coalescing means two (NV_MC_MW/2)-bit requests are grouped together in one NV_MC_WM-bit request.\nThe register value indicates how many cycles a first write request is going to wait for a subsequent one for possible coalescing. The coalescing can only happen if the request addresses are compatible. A value of zero means that coalescing is off and requests are sent right away to the arbiters.\nRead coalescing can have a very significant impact performance when accessing the internal memory, because its memory word is NV_MC_WM-bit wide. Grouping two half-word accesses is much more efficient, because the two accesses would actually have taken three cycles, due to a stall when accessing the same memory bank. It also reduces the number of accessing (one instead of two), freeing up internal memory bandwidth for other accesses.\nThe impact on external memory accesses is not as significant as the burst access is for NV_MC_MW/2 bits. But a coalesced read guarantees two consecutive same page accesses which is good for external memory bandwidth utilization.\nThe read coalescing time-out should be programmed depending on the client behavior and the client versus memory controller clock ratio. The first read is obviously delayed by an amount of memory controller cycles equal to the time-out value.\nRead Coalescing time-out register for CPU read clients";
}

#define TIMEOUT_RCOAL_MPEA_OFFSET 0x218
#define TIMEOUT_RCOAL_MPEA_UNDEFMASK 0xFFFFFF00
union timeout_rcoal_mpea_u {
    struct {
        unsigned int mpeamemrd_rcoal_tmval:8;
        unsigned int undefined_bits_8_31:24;
    };

    u_int32_t reg32;
};

void McDev::fill_timeout_rcoal_mpea_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const timeout_rcoal_mpea_u old_value_t = { .reg32 = value };
    const timeout_rcoal_mpea_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: mpeamemrd_rcoal_tmval:8", "", 8, old_value_t.mpeamemrd_rcoal_tmval, new_value_t.mpeamemrd_rcoal_tmval };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_31:24", "", 24, old_value_t.undefined_bits_8_31, new_value_t.undefined_bits_8_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Reset value defaults to 4 for most clients, but may be different for certain clients. Read coalescing happens inside the memory controller, right before arbitration. Coalescing means two (NV_MC_MW/2)-bit requests are grouped together in one NV_MC_WM-bit request.\nThe register value indicates how many cycles a first write request is going to wait for a subsequent one for possible coalescing. The coalescing can only happen if the request addresses are compatible. A value of zero means that coalescing is off and requests are sent right away to the arbiters.\nRead coalescing can have a very significant impact performance when accessing the internal memory, because its memory word is NV_MC_WM-bit wide. Grouping two half-word accesses is much more efficient, because the two accesses would actually have taken three cycles, due to a stall when accessing the same memory bank. It also reduces the number of accessing (one instead of two), freeing up internal memory bandwidth for other accesses.\nThe impact on external memory accesses is not as significant as the burst access is for NV_MC_MW/2 bits. But a coalesced read guarantees two consecutive same page accesses which is good for external memory bandwidth utilization.\nThe read coalescing time-out should be programmed depending on the client behavior and the client versus memory controller clock ratio. The first read is obviously delayed by an amount of memory controller cycles equal to the time-out value.\nRead Coalescing time-out register for mpea read clients";
}

#define TIMEOUT_RCOAL_MPEB_OFFSET 0x21C
#define TIMEOUT_RCOAL_MPEB_UNDEFMASK 0xFFFF0000
union timeout_rcoal_mpeb_u {
    struct {
        unsigned int mpeunifbr_rcoal_tmval:8;
        unsigned int mpe_ipred_rcoal_tmval:8;
        unsigned int undefined_bits_16_31:16;
    };

    u_int32_t reg32;
};

void McDev::fill_timeout_rcoal_mpeb_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const timeout_rcoal_mpeb_u old_value_t = { .reg32 = value };
    const timeout_rcoal_mpeb_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: mpeunifbr_rcoal_tmval:8", "", 8, old_value_t.mpeunifbr_rcoal_tmval, new_value_t.mpeunifbr_rcoal_tmval };
    m_bit_details_model.bits.append(entry);
    entry = { "08: mpe_ipred_rcoal_tmval:8", "", 8, old_value_t.mpe_ipred_rcoal_tmval, new_value_t.mpe_ipred_rcoal_tmval };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_31:16", "", 16, old_value_t.undefined_bits_16_31, new_value_t.undefined_bits_16_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Reset value defaults to 4 for most clients, but may be different for certain clients. Read coalescing happens inside the memory controller, right before arbitration. Coalescing means two (NV_MC_MW/2)-bit requests are grouped together in one NV_MC_WM-bit request.\nThe register value indicates how many cycles a first write request is going to wait for a subsequent one for possible coalescing. The coalescing can only happen if the request addresses are compatible. A value of zero means that coalescing is off and requests are sent right away to the arbiters.\nRead coalescing can have a very significant impact performance when accessing the internal memory, because its memory word is NV_MC_WM-bit wide. Grouping two half-word accesses is much more efficient, because the two accesses would actually have taken three cycles, due to a stall when accessing the same memory bank. It also reduces the number of accessing (one instead of two), freeing up internal memory bandwidth for other accesses.\nThe impact on external memory accesses is not as significant as the burst access is for NV_MC_MW/2 bits. But a coalesced read guarantees two consecutive same page accesses which is good for external memory bandwidth utilization.\nThe read coalescing time-out should be programmed depending on the client behavior and the client versus memory controller clock ratio. The first read is obviously delayed by an amount of memory controller cycles equal to the time-out value.\nRead Coalescing time-out register for mpeb read clients";
}

#define TIMEOUT_RCOAL_MPEC_OFFSET 0x220
#define TIMEOUT_RCOAL_MPEC_UNDEFMASK 0xFFFFFF00
union timeout_rcoal_mpec_u {
    struct {
        unsigned int mpecsrd_rcoal_tmval:8;
        unsigned int undefined_bits_8_31:24;
    };

    u_int32_t reg32;
};

void McDev::fill_timeout_rcoal_mpec_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const timeout_rcoal_mpec_u old_value_t = { .reg32 = value };
    const timeout_rcoal_mpec_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: mpecsrd_rcoal_tmval:8", "", 8, old_value_t.mpecsrd_rcoal_tmval, new_value_t.mpecsrd_rcoal_tmval };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_31:24", "", 24, old_value_t.undefined_bits_8_31, new_value_t.undefined_bits_8_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Reset value defaults to 4 for most clients, but may be different for certain clients. Read coalescing happens inside the memory controller, right before arbitration. Coalescing means two (NV_MC_MW/2)-bit requests are grouped together in one NV_MC_WM-bit request.\nThe register value indicates how many cycles a first write request is going to wait for a subsequent one for possible coalescing. The coalescing can only happen if the request addresses are compatible. A value of zero means that coalescing is off and requests are sent right away to the arbiters.\nRead coalescing can have a very significant impact performance when accessing the internal memory, because its memory word is NV_MC_WM-bit wide. Grouping two half-word accesses is much more efficient, because the two accesses would actually have taken three cycles, due to a stall when accessing the same memory bank. It also reduces the number of accessing (one instead of two), freeing up internal memory bandwidth for other accesses.\nThe impact on external memory accesses is not as significant as the burst access is for NV_MC_MW/2 bits. But a coalesced read guarantees two consecutive same page accesses which is good for external memory bandwidth utilization.\nThe read coalescing time-out should be programmed depending on the client behavior and the client versus memory controller clock ratio. The first read is obviously delayed by an amount of memory controller cycles equal to the time-out value.\nRead Coalescing time-out register for mpec read clients";
}

#define TIMEOUT_RCOAL_NV_OFFSET 0x224
#define TIMEOUT_RCOAL_NV_UNDEFMASK 0xFFFF0000
union timeout_rcoal_nv_u {
    struct {
        unsigned int idxsrd_rcoal_tmval:8;
        unsigned int texsrd_rcoal_tmval:8;
        unsigned int undefined_bits_16_31:16;
    };

    u_int32_t reg32;
};

void McDev::fill_timeout_rcoal_nv_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const timeout_rcoal_nv_u old_value_t = { .reg32 = value };
    const timeout_rcoal_nv_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: idxsrd_rcoal_tmval:8", "", 8, old_value_t.idxsrd_rcoal_tmval, new_value_t.idxsrd_rcoal_tmval };
    m_bit_details_model.bits.append(entry);
    entry = { "08: texsrd_rcoal_tmval:8", "", 8, old_value_t.texsrd_rcoal_tmval, new_value_t.texsrd_rcoal_tmval };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_31:16", "", 16, old_value_t.undefined_bits_16_31, new_value_t.undefined_bits_16_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Reset value defaults to 4 for most clients, but may be different for certain clients. Read coalescing happens inside the memory controller, right before arbitration. Coalescing means two (NV_MC_MW/2)-bit requests are grouped together in one NV_MC_WM-bit request.\nThe register value indicates how many cycles a first write request is going to wait for a subsequent one for possible coalescing. The coalescing can only happen if the request addresses are compatible. A value of zero means that coalescing is off and requests are sent right away to the arbiters.\nRead coalescing can have a very significant impact performance when accessing the internal memory, because its memory word is NV_MC_WM-bit wide. Grouping two half-word accesses is much more efficient, because the two accesses would actually have taken three cycles, due to a stall when accessing the same memory bank. It also reduces the number of accessing (one instead of two), freeing up internal memory bandwidth for other accesses.\nThe impact on external memory accesses is not as significant as the burst access is for NV_MC_MW/2 bits. But a coalesced read guarantees two consecutive same page accesses which is good for external memory bandwidth utilization.\nThe read coalescing time-out should be programmed depending on the client behavior and the client versus memory controller clock ratio. The first read is obviously delayed by an amount of memory controller cycles equal to the time-out value.\nRead Coalescing time-out register for nv read clients";
}

#define TIMEOUT_RCOAL_PPCS_OFFSET 0x228
#define TIMEOUT_RCOAL_PPCS_UNDEFMASK 0xFFFF0000
union timeout_rcoal_ppcs_u {
    struct {
        unsigned int ppcsahbdmar_rcoal_tmval:8;
        unsigned int ppcsahbslvr_rcoal_tmval:8;
        unsigned int undefined_bits_16_31:16;
    };

    u_int32_t reg32;
};

void McDev::fill_timeout_rcoal_ppcs_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const timeout_rcoal_ppcs_u old_value_t = { .reg32 = value };
    const timeout_rcoal_ppcs_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: ppcsahbdmar_rcoal_tmval:8", "", 8, old_value_t.ppcsahbdmar_rcoal_tmval, new_value_t.ppcsahbdmar_rcoal_tmval };
    m_bit_details_model.bits.append(entry);
    entry = { "08: ppcsahbslvr_rcoal_tmval:8", "", 8, old_value_t.ppcsahbslvr_rcoal_tmval, new_value_t.ppcsahbslvr_rcoal_tmval };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_31:16", "", 16, old_value_t.undefined_bits_16_31, new_value_t.undefined_bits_16_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Reset value defaults to 4 for most clients, but may be different for certain clients. Read coalescing happens inside the memory controller, right before arbitration. Coalescing means two (NV_MC_MW/2)-bit requests are grouped together in one NV_MC_WM-bit request.\nThe register value indicates how many cycles a first write request is going to wait for a subsequent one for possible coalescing. The coalescing can only happen if the request addresses are compatible. A value of zero means that coalescing is off and requests are sent right away to the arbiters.\nRead coalescing can have a very significant impact performance when accessing the internal memory, because its memory word is NV_MC_WM-bit wide. Grouping two half-word accesses is much more efficient, because the two accesses would actually have taken three cycles, due to a stall when accessing the same memory bank. It also reduces the number of accessing (one instead of two), freeing up internal memory bandwidth for other accesses.\nThe impact on external memory accesses is not as significant as the burst access is for NV_MC_MW/2 bits. But a coalesced read guarantees two consecutive same page accesses which is good for external memory bandwidth utilization.\nThe read coalescing time-out should be programmed depending on the client behavior and the client versus memory controller clock ratio. The first read is obviously delayed by an amount of memory controller cycles equal to the time-out value.\nRead Coalescing time-out register for ppcs read clients";
}

#define TIMEOUT_RCOAL_VDE_OFFSET 0x22C
#define TIMEOUT_RCOAL_VDE_UNDEFMASK 0x00000000
union timeout_rcoal_vde_u {
    struct {
        unsigned int vdebsevr_rcoal_tmval:8;
        unsigned int vdember_rcoal_tmval:8;
        unsigned int vdemcer_rcoal_tmval:8;
        unsigned int vdetper_rcoal_tmval:8;
    };

    u_int32_t reg32;
};

void McDev::fill_timeout_rcoal_vde_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const timeout_rcoal_vde_u old_value_t = { .reg32 = value };
    const timeout_rcoal_vde_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: vdebsevr_rcoal_tmval:8", "", 8, old_value_t.vdebsevr_rcoal_tmval, new_value_t.vdebsevr_rcoal_tmval };
    m_bit_details_model.bits.append(entry);
    entry = { "08: vdember_rcoal_tmval:8", "", 8, old_value_t.vdember_rcoal_tmval, new_value_t.vdember_rcoal_tmval };
    m_bit_details_model.bits.append(entry);
    entry = { "16: vdemcer_rcoal_tmval:8", "", 8, old_value_t.vdemcer_rcoal_tmval, new_value_t.vdemcer_rcoal_tmval };
    m_bit_details_model.bits.append(entry);
    entry = { "24: vdetper_rcoal_tmval:8", "", 8, old_value_t.vdetper_rcoal_tmval, new_value_t.vdetper_rcoal_tmval };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Reset value defaults to 4 for most clients, but may be different for certain clients. Read coalescing happens inside the memory controller, right before arbitration. Coalescing means two (NV_MC_MW/2)-bit requests are grouped together in one NV_MC_WM-bit request.\nThe register value indicates how many cycles a first write request is going to wait for a subsequent one for possible coalescing. The coalescing can only happen if the request addresses are compatible. A value of zero means that coalescing is off and requests are sent right away to the arbiters.\nRead coalescing can have a very significant impact performance when accessing the internal memory, because its memory word is NV_MC_WM-bit wide. Grouping two half-word accesses is much more efficient, because the two accesses would actually have taken three cycles, due to a stall when accessing the same memory bank. It also reduces the number of accessing (one instead of two), freeing up internal memory bandwidth for other accesses.\nThe impact on external memory accesses is not as significant as the burst access is for NV_MC_MW/2 bits. But a coalesced read guarantees two consecutive same page accesses which is good for external memory bandwidth utilization.\nThe read coalescing time-out should be programmed depending on the client behavior and the client versus memory controller clock ratio. The first read is obviously delayed by an amount of memory controller cycles equal to the time-out value.\nRead Coalescing time-out register for vde read clients";
}

#define TIMEOUT_RCOAL_VI_OFFSET 0x230
#define TIMEOUT_RCOAL_VI_UNDEFMASK 0xFFFFFF00
union timeout_rcoal_vi_u {
    struct {
        unsigned int viruv_rcoal_tmval:8;
        unsigned int undefined_bits_8_31:24;
    };

    u_int32_t reg32;
};

void McDev::fill_timeout_rcoal_vi_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const timeout_rcoal_vi_u old_value_t = { .reg32 = value };
    const timeout_rcoal_vi_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: viruv_rcoal_tmval:8", "", 8, old_value_t.viruv_rcoal_tmval, new_value_t.viruv_rcoal_tmval };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_31:24", "", 24, old_value_t.undefined_bits_8_31, new_value_t.undefined_bits_8_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Reset value defaults to 4 for most clients, but may be different for certain clients. Read coalescing happens inside the memory controller, right before arbitration. Coalescing means two (NV_MC_MW/2)-bit requests are grouped together in one NV_MC_WM-bit request.\nThe register value indicates how many cycles a first write request is going to wait for a subsequent one for possible coalescing. The coalescing can only happen if the request addresses are compatible. A value of zero means that coalescing is off and requests are sent right away to the arbiters.\nRead coalescing can have a very significant impact performance when accessing the internal memory, because its memory word is NV_MC_WM-bit wide. Grouping two half-word accesses is much more efficient, because the two accesses would actually have taken three cycles, due to a stall when accessing the same memory bank. It also reduces the number of accessing (one instead of two), freeing up internal memory bandwidth for other accesses.\nThe impact on external memory accesses is not as significant as the burst access is for NV_MC_MW/2 bits. But a coalesced read guarantees two consecutive same page accesses which is good for external memory bandwidth utilization.\nThe read coalescing time-out should be programmed depending on the client behavior and the client versus memory controller clock ratio. The first read is obviously delayed by an amount of memory controller cycles equal to the time-out value.\nRead Coalescing time-out register for vi read clients";
}

#define RCOAL_AUTODISABLE_OFFSET 0x234
#define RCOAL_AUTODISABLE_UNDEFMASK 0xFFFFE000
union rcoal_autodisable_u {
    struct {
        unsigned int display0a_rcoal_autodisable_en:1;/* 0 = DISABLE 1 = ENABLE 0 = DISABLED 1 = ENABLED */
        unsigned int display0ab_rcoal_autodisable_en:1;/* 0 = DISABLE 1 = ENABLE 0 = DISABLED 1 = ENABLED */
        unsigned int display0b_rcoal_autodisable_en:1;/* 0 = DISABLE 1 = ENABLE 0 = DISABLED 1 = ENABLED */
        unsigned int display0bb_rcoal_autodisable_en:1;/* 0 = DISABLE 1 = ENABLE 0 = DISABLED 1 = ENABLED */
        unsigned int display0c_rcoal_autodisable_en:1;/* 0 = DISABLE 1 = ENABLE 0 = DISABLED 1 = ENABLED */
        unsigned int display0cb_rcoal_autodisable_en:1;/* 0 = DISABLE 1 = ENABLE 0 = DISABLED 1 = ENABLED */
        unsigned int display1b_rcoal_autodisable_en:1;/* 0 = DISABLE 1 = ENABLE 0 = DISABLED 1 = ENABLED */
        unsigned int display1bb_rcoal_autodisable_en:1;/* 0 = DISABLE 1 = ENABLE 0 = DISABLED 1 = ENABLED */
        unsigned int eppup_rcoal_autodisable_en:1;/* 0 = DISABLE 1 = ENABLE 0 = DISABLED 1 = ENABLED */
        unsigned int g2pr_rcoal_autodisable_en:1;/* 0 = DISABLE 1 = ENABLE 0 = DISABLED 1 = ENABLED */
        unsigned int g2sr_rcoal_autodisable_en:1;/* 0 = DISABLE 1 = ENABLE 0 = DISABLED 1 = ENABLED */
        unsigned int mpeunifbr_rcoal_autodisable_en:1;/* 0 = DISABLE 1 = ENABLE 0 = DISABLED 1 = ENABLED */
        unsigned int viruv_rcoal_autodisable_en:1;/* 0 = DISABLE 1 = ENABLE 0 = DISABLED 1 = ENABLED */
        unsigned int undefined_bits_13_31:19;
    };

    u_int32_t reg32;
};

void McDev::fill_rcoal_autodisable_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const rcoal_autodisable_u old_value_t = { .reg32 = value };
    const rcoal_autodisable_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: display0a_rcoal_autodisable_en:1",
              "0 = DISABLE\n1 = ENABLE\n0 = DISABLED\n1 = ENABLED",
              1, old_value_t.display0a_rcoal_autodisable_en, new_value_t.display0a_rcoal_autodisable_en };
    m_bit_details_model.bits.append(entry);
    entry = { "01: display0ab_rcoal_autodisable_en:1",
              "0 = DISABLE\n1 = ENABLE\n0 = DISABLED\n1 = ENABLED",
              1, old_value_t.display0ab_rcoal_autodisable_en, new_value_t.display0ab_rcoal_autodisable_en };
    m_bit_details_model.bits.append(entry);
    entry = { "02: display0b_rcoal_autodisable_en:1",
              "0 = DISABLE\n1 = ENABLE\n0 = DISABLED\n1 = ENABLED",
              1, old_value_t.display0b_rcoal_autodisable_en, new_value_t.display0b_rcoal_autodisable_en };
    m_bit_details_model.bits.append(entry);
    entry = { "03: display0bb_rcoal_autodisable_en:1",
              "0 = DISABLE\n1 = ENABLE\n0 = DISABLED\n1 = ENABLED",
              1, old_value_t.display0bb_rcoal_autodisable_en, new_value_t.display0bb_rcoal_autodisable_en };
    m_bit_details_model.bits.append(entry);
    entry = { "04: display0c_rcoal_autodisable_en:1",
              "0 = DISABLE\n1 = ENABLE\n0 = DISABLED\n1 = ENABLED",
              1, old_value_t.display0c_rcoal_autodisable_en, new_value_t.display0c_rcoal_autodisable_en };
    m_bit_details_model.bits.append(entry);
    entry = { "05: display0cb_rcoal_autodisable_en:1",
              "0 = DISABLE\n1 = ENABLE\n0 = DISABLED\n1 = ENABLED",
              1, old_value_t.display0cb_rcoal_autodisable_en, new_value_t.display0cb_rcoal_autodisable_en };
    m_bit_details_model.bits.append(entry);
    entry = { "06: display1b_rcoal_autodisable_en:1",
              "0 = DISABLE\n1 = ENABLE\n0 = DISABLED\n1 = ENABLED",
              1, old_value_t.display1b_rcoal_autodisable_en, new_value_t.display1b_rcoal_autodisable_en };
    m_bit_details_model.bits.append(entry);
    entry = { "07: display1bb_rcoal_autodisable_en:1",
              "0 = DISABLE\n1 = ENABLE\n0 = DISABLED\n1 = ENABLED",
              1, old_value_t.display1bb_rcoal_autodisable_en, new_value_t.display1bb_rcoal_autodisable_en };
    m_bit_details_model.bits.append(entry);
    entry = { "08: eppup_rcoal_autodisable_en:1",
              "0 = DISABLE\n1 = ENABLE\n0 = DISABLED\n1 = ENABLED",
              1, old_value_t.eppup_rcoal_autodisable_en, new_value_t.eppup_rcoal_autodisable_en };
    m_bit_details_model.bits.append(entry);
    entry = { "09: g2pr_rcoal_autodisable_en:1",
              "0 = DISABLE\n1 = ENABLE\n0 = DISABLED\n1 = ENABLED",
              1, old_value_t.g2pr_rcoal_autodisable_en, new_value_t.g2pr_rcoal_autodisable_en };
    m_bit_details_model.bits.append(entry);
    entry = { "10: g2sr_rcoal_autodisable_en:1",
              "0 = DISABLE\n1 = ENABLE\n0 = DISABLED\n1 = ENABLED",
              1, old_value_t.g2sr_rcoal_autodisable_en, new_value_t.g2sr_rcoal_autodisable_en };
    m_bit_details_model.bits.append(entry);
    entry = { "11: mpeunifbr_rcoal_autodisable_en:1",
              "0 = DISABLE\n1 = ENABLE\n0 = DISABLED\n1 = ENABLED",
              1, old_value_t.mpeunifbr_rcoal_autodisable_en, new_value_t.mpeunifbr_rcoal_autodisable_en };
    m_bit_details_model.bits.append(entry);
    entry = { "12: viruv_rcoal_autodisable_en:1",
              "0 = DISABLE\n1 = ENABLE\n0 = DISABLED\n1 = ENABLED",
              1, old_value_t.viruv_rcoal_autodisable_en, new_value_t.viruv_rcoal_autodisable_en };
    m_bit_details_model.bits.append(entry);
    entry = { "13: undefined_bits_13_31:19", "", 19, old_value_t.undefined_bits_13_31, new_value_t.undefined_bits_13_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Reset value is enabled. Control whether read coalesce logic for the listed block-read clients will attempt to detect when the client is producing a long sequence of non-coalescable requests (as is common in horizontal-linear walks through a tiled surface) and proactively disable read-coalescing while the client appears to be in that mode.\nRead Coalescing Autodisable Control Register.";
}

#define BWSHARE_AVPC_OFFSET 0x238
#define BWSHARE_AVPC_UNDEFMASK 0xE0000000
union bwshare_avpc_u {
    struct {
        unsigned int avpc_bw_incval:11;
        unsigned int avpc_bw_highth:8;
        unsigned int avpc_bw_maxth:8;
        unsigned int avpc_bw_alwaysinc:1;   /* 0 = DISABLE; 1 = ENABLE; 0 = DISABLED 1 = ENABLED */
        unsigned int avpc_bw_tmsfactorsel:1;/* 0 = TM_SFACTOR1; 1 = TM_SFACTOR2 */
        unsigned int undefined_bits_29_31:3;
    };

    u_int32_t reg32;
};

void McDev::fill_bwshare_avpc_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const bwshare_avpc_u old_value_t = { .reg32 = value };
    const bwshare_avpc_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: avpc_bw_incval:11", "", 11, old_value_t.avpc_bw_incval, new_value_t.avpc_bw_incval };
    m_bit_details_model.bits.append(entry);
    entry = { "11: avpc_bw_highth:8", "", 8, old_value_t.avpc_bw_highth, new_value_t.avpc_bw_highth };
    m_bit_details_model.bits.append(entry);
    entry = { "19: avpc_bw_maxth:8", "", 8, old_value_t.avpc_bw_maxth, new_value_t.avpc_bw_maxth };
    m_bit_details_model.bits.append(entry);
    entry = { "27: avpc_bw_alwaysinc:1",
              "0 = DISABLE;\n1 = ENABLE;\n0 = DISABLED\n1 = ENABLED",
              1, old_value_t.avpc_bw_alwaysinc, new_value_t.avpc_bw_alwaysinc };
    m_bit_details_model.bits.append(entry);
    entry = { "28: avpc_bw_tmsfactorsel:1",
              "0 = TM_SFACTOR1;\n1 = TM_SFACTOR2",
              1, old_value_t.avpc_bw_tmsfactorsel, new_value_t.avpc_bw_tmsfactorsel };
    m_bit_details_model.bits.append(entry);
    entry = { "29: undefined_bits_29_31:3", "", 3, old_value_t.undefined_bits_29_31, new_value_t.undefined_bits_29_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Reset value is 0. The values reflect the bandwidth share for EMEM.\nINC_VAL specifies the number of bytes the Bandwidth credit has to be incremented. A value of zero disables the bandwidth share for all AVPC clients, and reset the accumulated credit.\n HIGH_TH specifies the high threshold [11:4]. If accumulated credit >= high threshold, BW bit is set. BW bit is reset when accumulated credit is zero. SAT_TH specifies the saturation threshold [11:4] for accumulated credit.\nBandwidth share register for AVPC clients";
}

#define BWSHARE_DC_OFFSET 0x23C
#define BWSHARE_DC_UNDEFMASK 0xE0000000
union bwshare_dc_u {
    struct {
        unsigned int dc_bw_incval:11;
        unsigned int dc_bw_highth:8;
        unsigned int dc_bw_maxth:8;
        unsigned int dc_bw_alwaysinc:1;     /* 0 = DISABLE 1 = ENABLE 0 = DISABLED 1 = ENABLED */
        unsigned int dc_bw_tmsfactorsel:1;  /* 0 = TM_SFACTOR1 1 = TM_SFACTOR2 */
        unsigned int undefined_bits_29_31:3;
    };

    u_int32_t reg32;
};

void McDev::fill_bwshare_dc_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const bwshare_dc_u old_value_t = { .reg32 = value };
    const bwshare_dc_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: dc_bw_incval:11", "", 11, old_value_t.dc_bw_incval, new_value_t.dc_bw_incval };
    m_bit_details_model.bits.append(entry);
    entry = { "11: dc_bw_highth:8", "", 8, old_value_t.dc_bw_highth, new_value_t.dc_bw_highth };
    m_bit_details_model.bits.append(entry);
    entry = { "19: dc_bw_maxth:8", "", 8, old_value_t.dc_bw_maxth, new_value_t.dc_bw_maxth };
    m_bit_details_model.bits.append(entry);
    entry = { "27: dc_bw_alwaysinc:1",
              "0 = DISABLE\n1 = ENABLE\n0 = DISABLED\n1 = ENABLED",
              1, old_value_t.dc_bw_alwaysinc, new_value_t.dc_bw_alwaysinc };
    m_bit_details_model.bits.append(entry);
    entry = { "28: dc_bw_tmsfactorsel:1",
              "0 = TM_SFACTOR1\n1 = TM_SFACTOR2",
              1, old_value_t.dc_bw_tmsfactorsel, new_value_t.dc_bw_tmsfactorsel };
    m_bit_details_model.bits.append(entry);
    entry = { "29: undefined_bits_29_31:3", "", 3, old_value_t.undefined_bits_29_31, new_value_t.undefined_bits_29_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Reset value is 0. The values reflect the bandwidth share for EMEM.\nINC_VAL specifies the number of bytes the Bandwidth credit has to be incremented. A value of zero disables the bandwidth share for all DC clients, and reset the accumulated credit.\n HIGH_TH specifies the high threshold [11:4]. If accumulated credit >= high threshold, BW bit is set. BW bit is reset when accumulated credit is zero. SAT_TH specifies the saturation threshold [11:4] for accumulated credit.\nBandwidth share register for DC clients";
}

#define BWSHARE_DCB_OFFSET 0x240
#define BWSHARE_DCB_UNDEFMASK 0xE0000000
union bwshare_dcb_u {
    struct {
        unsigned int dcb_bw_incval:11;
        unsigned int dcb_bw_highth:8;
        unsigned int dcb_bw_maxth:8;
        unsigned int dcb_bw_alwaysinc:1;    /* 0 = DISABLE 1 = ENABLE 0 = DISABLED 1 = ENABLED */
        unsigned int dcb_bw_tmsfactorsel:1; /* 0 = TM_SFACTOR1 1 = TM_SFACTOR2 */
        unsigned int undefined_bits_29_31:3;
    };

    u_int32_t reg32;
};

void McDev::fill_bwshare_dcb_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const bwshare_dcb_u old_value_t = { .reg32 = value };
    const bwshare_dcb_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: dcb_bw_incval:11", "", 11, old_value_t.dcb_bw_incval, new_value_t.dcb_bw_incval };
    m_bit_details_model.bits.append(entry);
    entry = { "11: dcb_bw_highth:8", "", 8, old_value_t.dcb_bw_highth, new_value_t.dcb_bw_highth };
    m_bit_details_model.bits.append(entry);
    entry = { "19: dcb_bw_maxth:8", "", 8, old_value_t.dcb_bw_maxth, new_value_t.dcb_bw_maxth };
    m_bit_details_model.bits.append(entry);
    entry = { "27: dcb_bw_alwaysinc:1",
              "0 = DISABLE\n1 = ENABLE\n0 = DISABLED\n1 = ENABLED",
              1, old_value_t.dcb_bw_alwaysinc, new_value_t.dcb_bw_alwaysinc };
    m_bit_details_model.bits.append(entry);
    entry = { "28: dcb_bw_tmsfactorsel:1",
              "0 = TM_SFACTOR1\n1 = TM_SFACTOR2",
              1, old_value_t.dcb_bw_tmsfactorsel, new_value_t.dcb_bw_tmsfactorsel };
    m_bit_details_model.bits.append(entry);
    entry = { "29: undefined_bits_29_31:3", "", 3, old_value_t.undefined_bits_29_31, new_value_t.undefined_bits_29_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Reset value is 0. The values reflect the bandwidth share for EMEM.\nINC_VAL specifies the number of bytes the Bandwidth credit has to be incremented. A value of zero disables the bandwidth share for all DCB clients, and reset the accumulated credit.\n HIGH_TH specifies the high threshold [11:4]. If accumulated credit >= high threshold, BW bit is set. BW bit is reset when accumulated credit is zero. SAT_TH specifies the saturation threshold [11:4] for accumulated credit.\nBandwidth share register for DCB clients";
}

#define BWSHARE_EPP_OFFSET 0x244
#define BWSHARE_EPP_UNDEFMASK 0xE0000000
union bwshare_epp_u {
    struct {
        unsigned int epp_bw_incval:11;
        unsigned int epp_bw_highth:8;
        unsigned int epp_bw_maxth:8;
        unsigned int epp_bw_alwaysinc:1;    /* 0 = DISABLE; 1 = ENABLE; 0 = DISABLED 1 = ENABLED */
        unsigned int epp_bw_tmsfactorsel:1; /* 0 = TM_SFACTOR1; 1 = TM_SFACTOR2 */
        unsigned int undefined_bits_29_31:3;
    };

    u_int32_t reg32;
};

void McDev::fill_bwshare_epp_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const bwshare_epp_u old_value_t = { .reg32 = value };
    const bwshare_epp_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: epp_bw_incval:11", "", 11, old_value_t.epp_bw_incval, new_value_t.epp_bw_incval };
    m_bit_details_model.bits.append(entry);
    entry = { "11: epp_bw_highth:8", "", 8, old_value_t.epp_bw_highth, new_value_t.epp_bw_highth };
    m_bit_details_model.bits.append(entry);
    entry = { "19: epp_bw_maxth:8", "", 8, old_value_t.epp_bw_maxth, new_value_t.epp_bw_maxth };
    m_bit_details_model.bits.append(entry);
    entry = { "27: epp_bw_alwaysinc:1",
              "0 = DISABLE;\n1 = ENABLE;\n0 = DISABLED\n1 = ENABLED",
              1, old_value_t.epp_bw_alwaysinc, new_value_t.epp_bw_alwaysinc };
    m_bit_details_model.bits.append(entry);
    entry = { "28: epp_bw_tmsfactorsel:1",
              "0 = TM_SFACTOR1;\n1 = TM_SFACTOR2",
              1, old_value_t.epp_bw_tmsfactorsel, new_value_t.epp_bw_tmsfactorsel };
    m_bit_details_model.bits.append(entry);
    entry = { "29: undefined_bits_29_31:3", "", 3, old_value_t.undefined_bits_29_31, new_value_t.undefined_bits_29_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "The values reflect the bandwidth share for EMEM. Reset value is 0.\nINC_VAL specifies the number of bytes the Bandwidth credit has to be incremented. A value of zero disables the bandwidth share for all EPP clients, and reset the accumulated credit.\nHIGH_TH specifies the high threshold[11:4]. If accumulated credit >= high threshold, BW bit is set. BW bit is reset when accumulated credit is zero. SAT_TH specifies the saturation threshold[11:4] for accumulated credit.\nBandwidth share register for EPP clients";
}

#define BWSHARE_G2_OFFSET 0x248
#define BWSHARE_G2_UNDEFMASK 0xE0000000
union bwshare_g2_u {
    struct {
        unsigned int g2_bw_incval:11;
        unsigned int g2_bw_highth:8;
        unsigned int g2_bw_maxth:8;
        unsigned int g2_bw_alwaysinc:1;     /* 0 = DISABLE; 1 = ENABLE; 0 = DISABLED 1 = ENABLED */
        unsigned int g2_bw_tmsfactorsel:1;  /* 0 = TM_SFACTOR1; 1 = TM_SFACTOR2 */
        unsigned int undefined_bits_29_31:3;
    };

    u_int32_t reg32;
};

void McDev::fill_bwshare_g2_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const bwshare_g2_u old_value_t = { .reg32 = value };
    const bwshare_g2_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: g2_bw_incval:11", "", 11, old_value_t.g2_bw_incval, new_value_t.g2_bw_incval };
    m_bit_details_model.bits.append(entry);
    entry = { "11: g2_bw_highth:8", "", 8, old_value_t.g2_bw_highth, new_value_t.g2_bw_highth };
    m_bit_details_model.bits.append(entry);
    entry = { "19: g2_bw_maxth:8", "", 8, old_value_t.g2_bw_maxth, new_value_t.g2_bw_maxth };
    m_bit_details_model.bits.append(entry);
    entry = { "27: g2_bw_alwaysinc:1",
              "0 = DISABLE;\n1 = ENABLE;\n0 = DISABLED\n1 = ENABLED",
              1, old_value_t.g2_bw_alwaysinc, new_value_t.g2_bw_alwaysinc };
    m_bit_details_model.bits.append(entry);
    entry = { "28: g2_bw_tmsfactorsel:1",
              "0 = TM_SFACTOR1;\n1 = TM_SFACTOR2",
              1, old_value_t.g2_bw_tmsfactorsel, new_value_t.g2_bw_tmsfactorsel };
    m_bit_details_model.bits.append(entry);
    entry = { "29: undefined_bits_29_31:3", "", 3, old_value_t.undefined_bits_29_31, new_value_t.undefined_bits_29_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "The values reflect the bandwidth share for EMEM. Reset value is 0.\nINC_VAL specifies the number of bytes the Bandwidth credit has to be incremented. A value of zero disables the bandwidth share for all G2 clients, and reset the accumulated credit.\nHIGH_TH specifies the high threshold[11:4]. If accumulated credit >= high threshold, BW bit is set. BW bit is reset when accumulated credit is zero. SAT_TH specifies the saturation threshold[11:4] for accumulated credit.\nBandwidth share register for G2 clients";
}

#define BWSHARE_HC_OFFSET 0x24C
#define BWSHARE_HC_UNDEFMASK 0xE0000000
union bwshare_hc_u {
    struct {
        unsigned int hc_bw_incval:11;
        unsigned int hc_bw_highth:8;
        unsigned int hc_bw_maxth:8;
        unsigned int hc_bw_alwaysinc:1;     /* 0 = DISABLE; 1 = ENABLE; 0 = DISABLED 1 = ENABLED */
        unsigned int hc_bw_tmsfactorsel:1;  /* 0 = TM_SFACTOR1; 1 = TM_SFACTOR2 */
        unsigned int undefined_bits_29_31:3;
    };

    u_int32_t reg32;
};

void McDev::fill_bwshare_hc_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const bwshare_hc_u old_value_t = { .reg32 = value };
    const bwshare_hc_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: hc_bw_incval:11", "", 11, old_value_t.hc_bw_incval, new_value_t.hc_bw_incval };
    m_bit_details_model.bits.append(entry);
    entry = { "11: hc_bw_highth:8", "", 8, old_value_t.hc_bw_highth, new_value_t.hc_bw_highth };
    m_bit_details_model.bits.append(entry);
    entry = { "19: hc_bw_maxth:8", "", 8, old_value_t.hc_bw_maxth, new_value_t.hc_bw_maxth };
    m_bit_details_model.bits.append(entry);
    entry = { "27: hc_bw_alwaysinc:1",
              "0 = DISABLE;\n1 = ENABLE;\n0 = DISABLED\n1 = ENABLED",
              1, old_value_t.hc_bw_alwaysinc, new_value_t.hc_bw_alwaysinc };
    m_bit_details_model.bits.append(entry);
    entry = { "28: hc_bw_tmsfactorsel:1",
              "0 = TM_SFACTOR1;\n1 = TM_SFACTOR2",
              1, old_value_t.hc_bw_tmsfactorsel, new_value_t.hc_bw_tmsfactorsel };
    m_bit_details_model.bits.append(entry);
    entry = { "29: undefined_bits_29_31:3", "", 3, old_value_t.undefined_bits_29_31, new_value_t.undefined_bits_29_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "The values reflect the bandwidth share for EMEM. Reset value is 0.\nINC_VAL specifies the number of bytes the Bandwidth credit has to be incremented. A value of zero disables the bandwidth share for all HC clients, and reset the accumulated credit.\nHIGH_TH specifies the high threshold[11:4]. If accumulated credit >= high threshold, BW bit is set. BW bit is reset when accumulated credit is zero. SAT_TH specifies the saturation threshold[11:4] for accumulated credit.\nBandwidth share register for HC clients";
}

#define BWSHARE_ISP_OFFSET 0x250
#define BWSHARE_ISP_UNDEFMASK 0xE0000000
union bwshare_isp_u {
    struct {
        unsigned int isp_bw_incval:11;
        unsigned int isp_bw_highth:8;
        unsigned int isp_bw_maxth:8;
        unsigned int isp_bw_alwaysinc:1;    /* 0 = DISABLE; 1 = ENABLE */
        unsigned int isp_bw_tmsfactorsel:1; /* 0 = TM_SFACTOR1; 1 = TM_SFACTOR2 */
        unsigned int undefined_bits_29_31:3;
    };

    u_int32_t reg32;
};

void McDev::fill_bwshare_isp_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const bwshare_isp_u old_value_t = { .reg32 = value };
    const bwshare_isp_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: isp_bw_incval:11", "", 11, old_value_t.isp_bw_incval, new_value_t.isp_bw_incval };
    m_bit_details_model.bits.append(entry);
    entry = { "11: isp_bw_highth:8", "", 8, old_value_t.isp_bw_highth, new_value_t.isp_bw_highth };
    m_bit_details_model.bits.append(entry);
    entry = { "19: isp_bw_maxth:8", "", 8, old_value_t.isp_bw_maxth, new_value_t.isp_bw_maxth };
    m_bit_details_model.bits.append(entry);
    entry = { "27: isp_bw_alwaysinc:1",
              "0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.isp_bw_alwaysinc, new_value_t.isp_bw_alwaysinc };
    m_bit_details_model.bits.append(entry);
    entry = { "28: isp_bw_tmsfactorsel:1",
              "0 = TM_SFACTOR1;\n1 = TM_SFACTOR2",
              1, old_value_t.isp_bw_tmsfactorsel, new_value_t.isp_bw_tmsfactorsel };
    m_bit_details_model.bits.append(entry);
    entry = { "29: undefined_bits_29_31:3", "", 3, old_value_t.undefined_bits_29_31, new_value_t.undefined_bits_29_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "The values reflect the bandwidth share for EMEM. Reset value is 0.\nINC_VAL specifies the number of bytes the Bandwidth credit has to be incremented. A value of zero disables the bandwidth share for all ISP clients, and reset the accumulated credit.\nHIGH_TH specifies the high threshold[11:4]. If accumulated credit >= high threshold, BW bit is set. BW bit is reset when accumulated credit is zero. SAT_TH specifies the saturation threshold[11:4] for accumulated credit.\nBandwidth share register for ISP clients";
}

#define BWSHARE_MPCORE_OFFSET 0x254
#define BWSHARE_MPCORE_UNDEFMASK 0xE0000000
union bwshare_mpcore_u {
    struct {
        unsigned int mpcore_bw_incval:11;
        unsigned int mpcore_bw_highth:8;
        unsigned int mpcore_bw_maxth:8;
        unsigned int mpcore_bw_alwaysinc:1; /* 0 = DISABLE; 1 = ENABLE */
        unsigned int mpcore_bw_tmsfactorsel:1;/* 0 = TM_SFACTOR1; 1 = TM_SFACTOR2 */
        unsigned int undefined_bits_29_31:3;
    };

    u_int32_t reg32;
};

void McDev::fill_bwshare_mpcore_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const bwshare_mpcore_u old_value_t = { .reg32 = value };
    const bwshare_mpcore_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: mpcore_bw_incval:11", "", 11, old_value_t.mpcore_bw_incval, new_value_t.mpcore_bw_incval };
    m_bit_details_model.bits.append(entry);
    entry = { "11: mpcore_bw_highth:8", "", 8, old_value_t.mpcore_bw_highth, new_value_t.mpcore_bw_highth };
    m_bit_details_model.bits.append(entry);
    entry = { "19: mpcore_bw_maxth:8", "", 8, old_value_t.mpcore_bw_maxth, new_value_t.mpcore_bw_maxth };
    m_bit_details_model.bits.append(entry);
    entry = { "27: mpcore_bw_alwaysinc:1",
              "0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.mpcore_bw_alwaysinc, new_value_t.mpcore_bw_alwaysinc };
    m_bit_details_model.bits.append(entry);
    entry = { "28: mpcore_bw_tmsfactorsel:1",
              "0 = TM_SFACTOR1;\n1 = TM_SFACTOR2",
              1, old_value_t.mpcore_bw_tmsfactorsel, new_value_t.mpcore_bw_tmsfactorsel };
    m_bit_details_model.bits.append(entry);
    entry = { "29: undefined_bits_29_31:3", "", 3, old_value_t.undefined_bits_29_31, new_value_t.undefined_bits_29_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "The values reflect the bandwidth share for EMEM. Reset value is 0.\nINC_VAL specifies the number of bytes the Bandwidth credit has to be incremented. A value of zero disables the bandwidth share for all CPU clients, and reset the accumulated credit.\nHIGH_TH specifies the high threshold[11:4]. If accumulated credit >= high threshold, BW bit is set. BW bit is reset when accumulated credit is zero. SAT_TH specifies the saturation threshold[11:4] for accumulated credit.\nBandwidth share register for CPU clients";
}

#define BWSHARE_MPEA_OFFSET 0x258
#define BWSHARE_MPEA_UNDEFMASK 0xE0000000
union bwshare_mpea_u {
    struct {
        unsigned int mpea_bw_incval:11;
        unsigned int mpea_bw_highth:8;
        unsigned int mpea_bw_maxth:8;
        unsigned int mpea_bw_alwaysinc:1;   /* 0 = DISABLE; 1 = ENABLE */
        unsigned int mpea_bw_tmsfactorsel:1;/* 0 = TM_SFACTOR1; 1 = TM_SFACTOR2 */
        unsigned int undefined_bits_29_31:3;
    };

    u_int32_t reg32;
};

void McDev::fill_bwshare_mpea_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const bwshare_mpea_u old_value_t = { .reg32 = value };
    const bwshare_mpea_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: mpea_bw_incval:11", "", 11, old_value_t.mpea_bw_incval, new_value_t.mpea_bw_incval };
    m_bit_details_model.bits.append(entry);
    entry = { "11: mpea_bw_highth:8", "", 8, old_value_t.mpea_bw_highth, new_value_t.mpea_bw_highth };
    m_bit_details_model.bits.append(entry);
    entry = { "19: mpea_bw_maxth:8", "", 8, old_value_t.mpea_bw_maxth, new_value_t.mpea_bw_maxth };
    m_bit_details_model.bits.append(entry);
    entry = { "27: mpea_bw_alwaysinc:1",
              "0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.mpea_bw_alwaysinc, new_value_t.mpea_bw_alwaysinc };
    m_bit_details_model.bits.append(entry);
    entry = { "28: mpea_bw_tmsfactorsel:1",
              "0 = TM_SFACTOR1;\n1 = TM_SFACTOR2",
              1, old_value_t.mpea_bw_tmsfactorsel, new_value_t.mpea_bw_tmsfactorsel };
    m_bit_details_model.bits.append(entry);
    entry = { "29: undefined_bits_29_31:3", "", 3, old_value_t.undefined_bits_29_31, new_value_t.undefined_bits_29_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "The values reflect the bandwidth share for EMEM. Reset value is 0.\nINC_VAL specifies the number of bytes the Bandwidth credit has to be incremented. A value of zero disables the bandwidth share for all MPEA clients, and reset the accumulated credit.\nHIGH_TH specifies the high threshold[11:4]. If accumulated credit >= high threshold, BW bit is set. BW bit is reset when accumulated credit is zero. SAT_TH specifies the saturation threshold[11:4] for accumulated credit.\nBandwidth share register for MPEA clients";
}

#define BWSHARE_MPEB_OFFSET 0x25C
#define BWSHARE_MPEB_UNDEFMASK 0xE0000000
union bwshare_mpeb_u {
    struct {
        unsigned int mpeb_bw_incval:11;
        unsigned int mpeb_bw_highth:8;
        unsigned int mpeb_bw_maxth:8;
        unsigned int mpeb_bw_alwaysinc:1;   /* 0 = DISABLE; 1 = ENABLE */
        unsigned int mpeb_bw_tmsfactorsel:1;/* 0 = TM_SFACTOR1; 1 = TM_SFACTOR2 */
        unsigned int undefined_bits_29_31:3;
    };

    u_int32_t reg32;
};

void McDev::fill_bwshare_mpeb_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const bwshare_mpeb_u old_value_t = { .reg32 = value };
    const bwshare_mpeb_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: mpeb_bw_incval:11", "", 11, old_value_t.mpeb_bw_incval, new_value_t.mpeb_bw_incval };
    m_bit_details_model.bits.append(entry);
    entry = { "11: mpeb_bw_highth:8", "", 8, old_value_t.mpeb_bw_highth, new_value_t.mpeb_bw_highth };
    m_bit_details_model.bits.append(entry);
    entry = { "19: mpeb_bw_maxth:8", "", 8, old_value_t.mpeb_bw_maxth, new_value_t.mpeb_bw_maxth };
    m_bit_details_model.bits.append(entry);
    entry = { "27: mpeb_bw_alwaysinc:1",
              "0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.mpeb_bw_alwaysinc, new_value_t.mpeb_bw_alwaysinc };
    m_bit_details_model.bits.append(entry);
    entry = { "28: mpeb_bw_tmsfactorsel:1",
              "0 = TM_SFACTOR1;\n1 = TM_SFACTOR2",
              1, old_value_t.mpeb_bw_tmsfactorsel, new_value_t.mpeb_bw_tmsfactorsel };
    m_bit_details_model.bits.append(entry);
    entry = { "29: undefined_bits_29_31:3", "", 3, old_value_t.undefined_bits_29_31, new_value_t.undefined_bits_29_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "The values reflect the bandwidth share for EMEM. Reset value is 0.\nINC_VAL specifies the number of bytes the Bandwidth credit has to be incremented. A value of zero disables the bandwidth share for all MPEB clients, and reset the accumulated credit.\nHIGH_TH specifies the high threshold[11:4]. If accumulated credit >= high threshold, BW bit is set. BW bit is reset when accumulated credit is zero. SAT_TH specifies the saturation threshold[11:4] for accumulated credit.\nBandwidth share register for MPEB clients";
}

#define BWSHARE_MPEC_OFFSET 0x260
#define BWSHARE_MPEC_UNDEFMASK 0xE0000000
union bwshare_mpec_u {
    struct {
        unsigned int mpec_bw_incval:11;
        unsigned int mpec_bw_highth:8;
        unsigned int mpec_bw_maxth:8;
        unsigned int mpec_bw_alwaysinc:1;   /* 0 = DISABLE; 1 = ENABLE */
        unsigned int mpec_bw_tmsfactorsel:1;/* 0 = TM_SFACTOR1; 1 = TM_SFACTOR2 */
        unsigned int undefined_bits_29_31:3;
    };

    u_int32_t reg32;
};

void McDev::fill_bwshare_mpec_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const bwshare_mpec_u old_value_t = { .reg32 = value };
    const bwshare_mpec_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: mpec_bw_incval:11", "", 11, old_value_t.mpec_bw_incval, new_value_t.mpec_bw_incval };
    m_bit_details_model.bits.append(entry);
    entry = { "11: mpec_bw_highth:8", "", 8, old_value_t.mpec_bw_highth, new_value_t.mpec_bw_highth };
    m_bit_details_model.bits.append(entry);
    entry = { "19: mpec_bw_maxth:8", "", 8, old_value_t.mpec_bw_maxth, new_value_t.mpec_bw_maxth };
    m_bit_details_model.bits.append(entry);
    entry = { "27: mpec_bw_alwaysinc:1",
              "0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.mpec_bw_alwaysinc, new_value_t.mpec_bw_alwaysinc };
    m_bit_details_model.bits.append(entry);
    entry = { "28: mpec_bw_tmsfactorsel:1",
              "0 = TM_SFACTOR1;\n1 = TM_SFACTOR2",
              1, old_value_t.mpec_bw_tmsfactorsel, new_value_t.mpec_bw_tmsfactorsel };
    m_bit_details_model.bits.append(entry);
    entry = { "29: undefined_bits_29_31:3", "", 3, old_value_t.undefined_bits_29_31, new_value_t.undefined_bits_29_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "The values reflect the bandwidth share for EMEM. Reset value is 0.\nINC_VAL specifies the number of bytes the Bandwidth credit has to be incremented. A value of zero disables the bandwidth share for all MPEC clients, and reset the accumulated credit.\nHIGH_TH specifies the high threshold[11:4]. If accumulated credit >= high threshold, BW bit is set. BW bit is reset when accumulated credit is zero. SAT_TH specifies the saturation threshold[11:4] for accumulated credit.\nBandwidth share register for MPEC clients";
}

#define BWSHARE_NV_OFFSET 0x264
#define BWSHARE_NV_UNDEFMASK 0xE0000000
union bwshare_nv_u {
    struct {
        unsigned int nv_bw_incval:11;
        unsigned int nv_bw_highth:8;
        unsigned int nv_bw_maxth:8;
        unsigned int nv_bw_alwaysinc:1;     /* 0 = DISABLE; 1 = ENABLE */
        unsigned int nv_bw_tmsfactorsel:1;  /* 0 = TM_SFACTOR1; 1 = TM_SFACTOR2 */
        unsigned int undefined_bits_29_31:3;
    };

    u_int32_t reg32;
};

void McDev::fill_bwshare_nv_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const bwshare_nv_u old_value_t = { .reg32 = value };
    const bwshare_nv_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: nv_bw_incval:11", "", 11, old_value_t.nv_bw_incval, new_value_t.nv_bw_incval };
    m_bit_details_model.bits.append(entry);
    entry = { "11: nv_bw_highth:8", "", 8, old_value_t.nv_bw_highth, new_value_t.nv_bw_highth };
    m_bit_details_model.bits.append(entry);
    entry = { "19: nv_bw_maxth:8", "", 8, old_value_t.nv_bw_maxth, new_value_t.nv_bw_maxth };
    m_bit_details_model.bits.append(entry);
    entry = { "27: nv_bw_alwaysinc:1",
              "0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.nv_bw_alwaysinc, new_value_t.nv_bw_alwaysinc };
    m_bit_details_model.bits.append(entry);
    entry = { "28: nv_bw_tmsfactorsel:1",
              "0 = TM_SFACTOR1;\n1 = TM_SFACTOR2",
              1, old_value_t.nv_bw_tmsfactorsel, new_value_t.nv_bw_tmsfactorsel };
    m_bit_details_model.bits.append(entry);
    entry = { "29: undefined_bits_29_31:3", "", 3, old_value_t.undefined_bits_29_31, new_value_t.undefined_bits_29_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "The values reflect the bandwidth share for EMEM. Reset value is 0.\nINC_VAL specifies the number of bytes the Bandwidth credit has to be incremented. A value of zero disables the bandwidth share for all NV clients, and reset the accumulated credit.\nHIGH_TH specifies the high threshold[11:4]. If accumulated credit >= high threshold, BW bit is set. BW bit is reset when accumulated credit is zero. SAT_TH specifies the saturation threshold[11:4] for accumulated credit.\nBandwidth share register for NV clients";
}

#define BWSHARE_PPCS_OFFSET 0x268
#define BWSHARE_PPCS_UNDEFMASK 0xE0000000
union bwshare_ppcs_u {
    struct {
        unsigned int ppcs_bw_incval:11;
        unsigned int ppcs_bw_highth:8;
        unsigned int ppcs_bw_maxth:8;
        unsigned int ppcs_bw_alwaysinc:1;   /* 0 = DISABLE; 1 = ENABLE */
        unsigned int ppcs_bw_tmsfactorsel:1;/* 0 = TM_SFACTOR1; 1 = TM_SFACTOR2 */
        unsigned int undefined_bits_29_31:3;
    };

    u_int32_t reg32;
};

void McDev::fill_bwshare_ppcs_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const bwshare_ppcs_u old_value_t = { .reg32 = value };
    const bwshare_ppcs_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: ppcs_bw_incval:11", "", 11, old_value_t.ppcs_bw_incval, new_value_t.ppcs_bw_incval };
    m_bit_details_model.bits.append(entry);
    entry = { "11: ppcs_bw_highth:8", "", 8, old_value_t.ppcs_bw_highth, new_value_t.ppcs_bw_highth };
    m_bit_details_model.bits.append(entry);
    entry = { "19: ppcs_bw_maxth:8", "", 8, old_value_t.ppcs_bw_maxth, new_value_t.ppcs_bw_maxth };
    m_bit_details_model.bits.append(entry);
    entry = { "27: ppcs_bw_alwaysinc:1",
              "0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ppcs_bw_alwaysinc, new_value_t.ppcs_bw_alwaysinc };
    m_bit_details_model.bits.append(entry);
    entry = { "28: ppcs_bw_tmsfactorsel:1",
              "0 = TM_SFACTOR1;\n1 = TM_SFACTOR2",
              1, old_value_t.ppcs_bw_tmsfactorsel, new_value_t.ppcs_bw_tmsfactorsel };
    m_bit_details_model.bits.append(entry);
    entry = { "29: undefined_bits_29_31:3", "", 3, old_value_t.undefined_bits_29_31, new_value_t.undefined_bits_29_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "The values reflect the bandwidth share for EMEM. Reset value is 0.\nINC_VAL specifies the number of bytes the Bandwidth credit has to be incremented. A value of zero disables the bandwidth share for all PPCS clients, and reset the accumulated credit.\nHIGH_TH specifies the high threshold[11:4]. If accumulated credit >= high threshold, BW bit is set. BW bit is reset when accumulated credit is zero. SAT_TH specifies the saturation threshold[11:4] for accumulated credit.\nBandwidth share register for PPCS clients";
}

#define BWSHARE_VDE_OFFSET 0x26C
#define BWSHARE_VDE_UNDEFMASK 0xE0000000
union bwshare_vde_u {
    struct {
        unsigned int vde_bw_incval:11;
        unsigned int vde_bw_highth:8;
        unsigned int vde_bw_maxth:8;
        unsigned int vde_bw_alwaysinc:1;    /* 0 = DISABLE; 1 = ENABLE */
        unsigned int vde_bw_tmsfactorsel:1; /* 0 = TM_SFACTOR1; 1 = TM_SFACTOR2 */
        unsigned int undefined_bits_29_31:3;
    };

    u_int32_t reg32;
};

void McDev::fill_bwshare_vde_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const bwshare_vde_u old_value_t = { .reg32 = value };
    const bwshare_vde_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: vde_bw_incval:11", "", 11, old_value_t.vde_bw_incval, new_value_t.vde_bw_incval };
    m_bit_details_model.bits.append(entry);
    entry = { "11: vde_bw_highth:8", "", 8, old_value_t.vde_bw_highth, new_value_t.vde_bw_highth };
    m_bit_details_model.bits.append(entry);
    entry = { "19: vde_bw_maxth:8", "", 8, old_value_t.vde_bw_maxth, new_value_t.vde_bw_maxth };
    m_bit_details_model.bits.append(entry);
    entry = { "27: vde_bw_alwaysinc:1",
              "0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.vde_bw_alwaysinc, new_value_t.vde_bw_alwaysinc };
    m_bit_details_model.bits.append(entry);
    entry = { "28: vde_bw_tmsfactorsel:1",
              "0 = TM_SFACTOR1;\n1 = TM_SFACTOR2",
              1, old_value_t.vde_bw_tmsfactorsel, new_value_t.vde_bw_tmsfactorsel };
    m_bit_details_model.bits.append(entry);
    entry = { "29: undefined_bits_29_31:3", "", 3, old_value_t.undefined_bits_29_31, new_value_t.undefined_bits_29_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "The values reflect the bandwidth share for EMEM. Reset value is 0.\nINC_VAL specifies the number of bytes the Bandwidth credit has to be incremented. A value of zero disables the bandwidth share for all VDE clients, and reset the accumulated credit.\nHIGH_TH specifies the high threshold[11:4]. If accumulated credit >= high threshold, BW bit is set. BW bit is reset when accumulated credit is zero. SAT_TH specifies the saturation threshold[11:4] for accumulated credit.\nBandwidth share register for VDE clients";
}

#define BWSHARE_VI_OFFSET 0x270
#define BWSHARE_VI_UNDEFMASK 0xE0000000
union bwshare_vi_u {
    struct {
        unsigned int vi_bw_incval:11;
        unsigned int vi_bw_highth:8;
        unsigned int vi_bw_maxth:8;
        unsigned int vi_bw_alwaysinc:1;     /* 0 = DISABLE; 1 = ENABLE */
        unsigned int vi_bw_tmsfactorsel:1;  /* 0 = TM_SFACTOR1; 1 = TM_SFACTOR2 */
        unsigned int undefined_bits_29_31:3;
    };

    u_int32_t reg32;
};

void McDev::fill_bwshare_vi_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const bwshare_vi_u old_value_t = { .reg32 = value };
    const bwshare_vi_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: vi_bw_incval:11", "", 11, old_value_t.vi_bw_incval, new_value_t.vi_bw_incval };
    m_bit_details_model.bits.append(entry);
    entry = { "11: vi_bw_highth:8", "", 8, old_value_t.vi_bw_highth, new_value_t.vi_bw_highth };
    m_bit_details_model.bits.append(entry);
    entry = { "19: vi_bw_maxth:8", "", 8, old_value_t.vi_bw_maxth, new_value_t.vi_bw_maxth };
    m_bit_details_model.bits.append(entry);
    entry = { "27: vi_bw_alwaysinc:1",
              "0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.vi_bw_alwaysinc, new_value_t.vi_bw_alwaysinc };
    m_bit_details_model.bits.append(entry);
    entry = { "28: vi_bw_tmsfactorsel:1",
              "0 = TM_SFACTOR1;\n1 = TM_SFACTOR2",
              1, old_value_t.vi_bw_tmsfactorsel, new_value_t.vi_bw_tmsfactorsel };
    m_bit_details_model.bits.append(entry);
    entry = { "29: undefined_bits_29_31:3", "", 3, old_value_t.undefined_bits_29_31, new_value_t.undefined_bits_29_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "The values reflect the bandwidth share for EMEM. Reset value is 0.\nINC_VAL specifies the number of bytes the Bandwidth credit has to be incremented. A value of zero disables the bandwidth share for all VI clients, and reset the accumulated credit.\nHIGH_TH specifies the high threshold[11:4]. If accumulated credit >= high threshold, BW bit is set. BW bit is reset when accumulated credit is zero. SAT_TH specifies the saturation threshold[11:4] for accumulated credit.\nBandwidth share register for VI clients";
}

#define INTSTATUS_OFFSET 0x0
#define INTSTATUS_UNDEFMASK 0xFFFFFE3F
union mc_intstatus_u {
    struct {
        unsigned int undefined_bits_0_5:6;
        unsigned int decerr_emem_others_int:1;/* EMEM Address Decode Error for a non AXI client. */
        unsigned int invalid_gart_page_int:1;/* A GART access was attepted to an invalid page. */
        unsigned int security_violation_int:1;/* A nonsecure access was attempted to a secured region. */
        unsigned int undefined_bits_9_31:23;
    };

    u_int32_t reg32;
};

void McDev::fill_intstatus_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const mc_intstatus_u old_value_t = { .reg32 = value };
    const mc_intstatus_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_5:6", "", 6, old_value_t.undefined_bits_0_5, new_value_t.undefined_bits_0_5 };
    m_bit_details_model.bits.append(entry);
    entry = { "06: decerr_emem_others_int:1",
              "EMEM Address Decode Error for a non AXI client.",
              1, old_value_t.decerr_emem_others_int, new_value_t.decerr_emem_others_int };
    m_bit_details_model.bits.append(entry);
    entry = { "07: invalid_gart_page_int:1",
              "A GART access was attepted to an invalid page.",
              1, old_value_t.invalid_gart_page_int, new_value_t.invalid_gart_page_int };
    m_bit_details_model.bits.append(entry);
    entry = { "08: security_violation_int:1",
              "A nonsecure access was attempted to a secured region.",
              1, old_value_t.security_violation_int, new_value_t.security_violation_int };
    m_bit_details_model.bits.append(entry);
    entry = { "09: undefined_bits_9_31:23", "", 23, old_value_t.undefined_bits_9_31, new_value_t.undefined_bits_9_31 };
    m_bit_details_model.bits.append(entry);
}

#define INTMASK_OFFSET 0x4
#define INTMASK_UNDEFMASK 0xFFFFFE3F
union mc_intmask_u {
    struct {
        unsigned int undefined_bits_0_5:6;
        unsigned int decerr_emem_others_intmask:1;/* EMEM Address Decode Error for a non AXI client. */
        unsigned int invalid_gart_page_intmask:1;/* A GART access was attepted to an invalid page. */
        unsigned int security_violation_intmask:1;/* A nonsecure access was attempted to a secured region. */
        unsigned int undefined_bits_9_31:23;
    };

    u_int32_t reg32;
};

void McDev::fill_intmask_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const mc_intmask_u old_value_t = { .reg32 = value };
    const mc_intmask_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_5:6", "", 6, old_value_t.undefined_bits_0_5, new_value_t.undefined_bits_0_5 };
    m_bit_details_model.bits.append(entry);
    entry = { "06: decerr_emem_others_intmask:1",
              "EMEM Address Decode Error for a non AXI client.",
              1, old_value_t.decerr_emem_others_intmask, new_value_t.decerr_emem_others_intmask };
    m_bit_details_model.bits.append(entry);
    entry = { "07: invalid_gart_page_intmask:1",
              "A GART access was attepted to an invalid page.",
              1, old_value_t.invalid_gart_page_intmask, new_value_t.invalid_gart_page_intmask };
    m_bit_details_model.bits.append(entry);
    entry = { "08: security_violation_intmask:1",
              "A nonsecure access was attempted to a secured region.",
              1, old_value_t.security_violation_intmask, new_value_t.security_violation_intmask };
    m_bit_details_model.bits.append(entry);
    entry = { "09: undefined_bits_9_31:23", "", 23, old_value_t.undefined_bits_9_31, new_value_t.undefined_bits_9_31 };
    m_bit_details_model.bits.append(entry);
}

#define CLKEN_OVERRIDE_OFFSET 0x68
#define CLKEN_OVERRIDE_UNDEFMASK 0xFFFFFFE2
union mc_clken_override_u {
    struct {
        unsigned int cif_clken_ovr:1;
        unsigned int undefined_bit_1:1;
        unsigned int eseq_clken_ovr:1;
        unsigned int regs_clken_ovr:1;
        unsigned int gart_clken_ovr:1;
        unsigned int undefined_bits_5_31:27;
    };

    u_int32_t reg32;
};

void McDev::fill_clken_override_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const mc_clken_override_u old_value_t = { .reg32 = value };
    const mc_clken_override_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: cif_clken_ovr:1", "", 1, old_value_t.cif_clken_ovr, new_value_t.cif_clken_ovr };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bit_1:1", "", 1, old_value_t.undefined_bit_1, new_value_t.undefined_bit_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: eseq_clken_ovr:1", "", 1, old_value_t.eseq_clken_ovr, new_value_t.eseq_clken_ovr };
    m_bit_details_model.bits.append(entry);
    entry = { "03: regs_clken_ovr:1", "", 1, old_value_t.regs_clken_ovr, new_value_t.regs_clken_ovr };
    m_bit_details_model.bits.append(entry);
    entry = { "04: gart_clken_ovr:1", "", 1, old_value_t.gart_clken_ovr, new_value_t.gart_clken_ovr };
    m_bit_details_model.bits.append(entry);
    entry = { "05: undefined_bits_5_31:27", "", 27, old_value_t.undefined_bits_5_31, new_value_t.undefined_bits_5_31 };
    m_bit_details_model.bits.append(entry);
}

#define SECURITY_CFG0_OFFSET 0x6C
#define SECURITY_CFG0_UNDEFMASK 0x000FFFFF
union security_cfg0_u {
    struct {
        unsigned int undefined_bits_0_19:20;
        unsigned int security_bom:12;
    };

    u_int32_t reg32;
};

void McDev::fill_security_cfg0_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const security_cfg0_u old_value_t = { .reg32 = value };
    const security_cfg0_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_19:20", "", 20, old_value_t.undefined_bits_0_19, new_value_t.undefined_bits_0_19 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: security_bom:12", "", 12, old_value_t.security_bom, new_value_t.security_bom };
    m_bit_details_model.bits.append(entry);
}

#define SECURITY_CFG1_OFFSET 0x70
#define SECURITY_CFG1_UNDEFMASK 0xFFFFF000
union security_cfg1_u {
    struct {
        unsigned int security_size_mb:12;
        unsigned int undefined_bits_12_31:20;
    };

    u_int32_t reg32;
};

void McDev::fill_security_cfg1_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const security_cfg1_u old_value_t = { .reg32 = value };
    const security_cfg1_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: security_size_mb:12", "", 12, old_value_t.security_size_mb, new_value_t.security_size_mb };
    m_bit_details_model.bits.append(entry);
    entry = { "12: undefined_bits_12_31:20", "", 20, old_value_t.undefined_bits_12_31, new_value_t.undefined_bits_12_31 };
    m_bit_details_model.bits.append(entry);
}

#define SECURITY_VIOLATION_STATUS_OFFSET 0x74
#define SECURITY_VIOLATION_STATUS_UNDEFMASK 0x3FFFFFC0
union security_violation_status_u {
    struct {
        unsigned int security_violation_id:6;
        unsigned int undefined_bits_6_29:24;
        unsigned int security_violation_type:1;
        unsigned int security_violation_rw:1;
    };

    u_int32_t reg32;
};

void McDev::fill_security_violation_status_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const security_violation_status_u old_value_t = { .reg32 = value };
    const security_violation_status_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: security_violation_id:6", "", 6, old_value_t.security_violation_id, new_value_t.security_violation_id };
    m_bit_details_model.bits.append(entry);
    entry = { "06: undefined_bits_6_29:24", "", 24, old_value_t.undefined_bits_6_29, new_value_t.undefined_bits_6_29 };
    m_bit_details_model.bits.append(entry);
    entry = { "30: security_violation_type:1", "", 1, old_value_t.security_violation_type, new_value_t.security_violation_type };
    m_bit_details_model.bits.append(entry);
    entry = { "31: security_violation_rw:1", "", 1, old_value_t.security_violation_rw, new_value_t.security_violation_rw };
    m_bit_details_model.bits.append(entry);
}

#define SECURITY_VIOLATION_ADR_OFFSET 0x78
#define SECURITY_VIOLATION_ADR_UNDEFMASK 0x00000000
union security_violation_adr_u {
    struct {
        unsigned int security_violation_adr:32;
    };

    u_int32_t reg32;
};

void McDev::fill_security_violation_adr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const security_violation_adr_u old_value_t = { .reg32 = value };
    const security_violation_adr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: security_violation_adr:32", "", 32, old_value_t.security_violation_adr, new_value_t.security_violation_adr };
    m_bit_details_model.bits.append(entry);
}

#define SECURITY_CFG2_OFFSET 0x7C
#define SECURITY_CFG2_UNDEFMASK 0x000FFFFF
union security_cfg2_u {
    struct {
        unsigned int undefined_bits_0_19:20;
        unsigned int carveout_bom:12;
    };

    u_int32_t reg32;
};

void McDev::fill_security_cfg2_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const security_cfg2_u old_value_t = { .reg32 = value };
    const security_cfg2_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_19:20", "", 20, old_value_t.undefined_bits_0_19, new_value_t.undefined_bits_0_19 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: carveout_bom:12", "", 12, old_value_t.carveout_bom, new_value_t.carveout_bom };
    m_bit_details_model.bits.append(entry);
}

#define STAT_CONTROL_OFFSET 0x90
#define STAT_CONTROL_UNDEFMASK 0xFFFFFCFF
union mc_stat_control_u {
    struct {
        unsigned int undefined_bits_0_7:8;
        unsigned int emc_gather:2;
        unsigned int undefined_bits_10_31:22;
    };

    u_int32_t reg32;
};

void McDev::fill_stat_control_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const mc_stat_control_u old_value_t = { .reg32 = value };
    const mc_stat_control_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_7:8", "", 8, old_value_t.undefined_bits_0_7, new_value_t.undefined_bits_0_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: emc_gather:2", "", 2, old_value_t.emc_gather, new_value_t.emc_gather };
    m_bit_details_model.bits.append(entry);
    entry = { "10: undefined_bits_10_31:22", "", 22, old_value_t.undefined_bits_10_31, new_value_t.undefined_bits_10_31 };
    m_bit_details_model.bits.append(entry);
}

#define STAT_STATUS_OFFSET 0x94
#define STAT_STATUS_UNDEFMASK 0xFFFFFEFF
union mc_stat_status_u {
    struct {
        unsigned int undefined_bits_0_7:8;
        unsigned int emc_limit:1;
        unsigned int undefined_bits_9_31:23;
    };

    u_int32_t reg32;
};

void McDev::fill_stat_status_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const mc_stat_status_u old_value_t = { .reg32 = value };
    const mc_stat_status_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_7:8", "", 8, old_value_t.undefined_bits_0_7, new_value_t.undefined_bits_0_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: emc_limit:1", "", 1, old_value_t.emc_limit, new_value_t.emc_limit };
    m_bit_details_model.bits.append(entry);
    entry = { "09: undefined_bits_9_31:23", "", 23, old_value_t.undefined_bits_9_31, new_value_t.undefined_bits_9_31 };
    m_bit_details_model.bits.append(entry);
}

#define STAT_EMC_ADDR_LOW_OFFSET 0x98
#define STAT_EMC_ADDR_LOW_UNDEFMASK 0xC000000F
union stat_emc_addr_low_u {
    struct {
        unsigned int undefined_bits_0_3:4;
        unsigned int emc_addr_low:26;
        unsigned int undefined_bits_30_31:2;
    };

    u_int32_t reg32;
};

void McDev::fill_stat_emc_addr_low_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const stat_emc_addr_low_u old_value_t = { .reg32 = value };
    const stat_emc_addr_low_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_3:4", "", 4, old_value_t.undefined_bits_0_3, new_value_t.undefined_bits_0_3 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: emc_addr_low:26", "", 26, old_value_t.emc_addr_low, new_value_t.emc_addr_low };
    m_bit_details_model.bits.append(entry);
    entry = { "30: undefined_bits_30_31:2", "", 2, old_value_t.undefined_bits_30_31, new_value_t.undefined_bits_30_31 };
    m_bit_details_model.bits.append(entry);
}

#define STAT_EMC_ADDR_HIGH_OFFSET 0x9C
#define STAT_EMC_ADDR_HIGH_UNDEFMASK 0xC000000F
union stat_emc_addr_high_u {
    struct {
        unsigned int undefined_bits_0_3:4;
        unsigned int emc_addr_high:26;
        unsigned int undefined_bits_30_31:2;
    };

    u_int32_t reg32;
};

void McDev::fill_stat_emc_addr_high_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const stat_emc_addr_high_u old_value_t = { .reg32 = value };
    const stat_emc_addr_high_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_3:4", "", 4, old_value_t.undefined_bits_0_3, new_value_t.undefined_bits_0_3 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: emc_addr_high:26", "", 26, old_value_t.emc_addr_high, new_value_t.emc_addr_high };
    m_bit_details_model.bits.append(entry);
    entry = { "30: undefined_bits_30_31:2", "", 2, old_value_t.undefined_bits_30_31, new_value_t.undefined_bits_30_31 };
    m_bit_details_model.bits.append(entry);
}

#define STAT_EMC_CLOCK_LIMIT_OFFSET 0xA0
#define STAT_EMC_CLOCK_LIMIT_UNDEFMASK 0x00000000
union stat_emc_clock_limit_u {
    struct {
        unsigned int emc_clock_limit:32;
    };

    u_int32_t reg32;
};

void McDev::fill_stat_emc_clock_limit_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const stat_emc_clock_limit_u old_value_t = { .reg32 = value };
    const stat_emc_clock_limit_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: emc_clock_limit:32", "", 32, old_value_t.emc_clock_limit, new_value_t.emc_clock_limit };
    m_bit_details_model.bits.append(entry);
}

#define STAT_EMC_CLOCKS_OFFSET 0xA4
#define STAT_EMC_CLOCKS_UNDEFMASK 0x00000000
union stat_emc_clocks_u {
    struct {
        unsigned int emc_clocks:32;
    };

    u_int32_t reg32;
};

void McDev::fill_stat_emc_clocks_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const stat_emc_clocks_u old_value_t = { .reg32 = value };
    const stat_emc_clocks_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: emc_clocks:32", "", 32, old_value_t.emc_clocks, new_value_t.emc_clocks };
    m_bit_details_model.bits.append(entry);
}

#define STAT_EMC_CONTROL_OFFSET 0xA8
#define STAT_EMC_CONTROL_UNDEFMASK 0x00000000
union stat_emc_control_u {
    struct {
        unsigned int emc_control_0:32;
    };

    u_int32_t reg32;
};

void McDev::fill_stat_emc_control_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const stat_emc_control_u old_value_t = { .reg32 = value };
    const stat_emc_control_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: emc_control_0:32", "", 32, old_value_t.emc_control_0, new_value_t.emc_control_0 };
    m_bit_details_model.bits.append(entry);
}

#define STAT_EMC_CONTROL_1_OFFSET 0xAC
#define STAT_EMC_CONTROL_1_UNDEFMASK 0x00000000
union stat_emc_control_1_u {
    struct {
        unsigned int emc_control_1:32;
    };

    u_int32_t reg32;
};

void McDev::fill_stat_emc_control_1_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const stat_emc_control_1_u old_value_t = { .reg32 = value };
    const stat_emc_control_1_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: emc_control_1:32", "", 32, old_value_t.emc_control_1, new_value_t.emc_control_1 };
    m_bit_details_model.bits.append(entry);
}

#define STAT_EMC_HIST_LIMIT_OFFSET 0xB0
#define STAT_EMC_HIST_LIMIT_UNDEFMASK 0x00000000
union stat_emc_hist_limit_u {
    struct {
        unsigned int emc_hist_limit_0:32;
    };

    u_int32_t reg32;
};

void McDev::fill_stat_emc_hist_limit_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const stat_emc_hist_limit_u old_value_t = { .reg32 = value };
    const stat_emc_hist_limit_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: emc_hist_limit_0:32", "", 32, old_value_t.emc_hist_limit_0, new_value_t.emc_hist_limit_0 };
    m_bit_details_model.bits.append(entry);
}

#define STAT_EMC_HIST_LIMIT_1_OFFSET 0xB4
#define STAT_EMC_HIST_LIMIT_1_UNDEFMASK 0x00000000
union stat_emc_hist_limit_1_u {
    struct {
        unsigned int emc_hist_limit_1:32;
    };

    u_int32_t reg32;
};

void McDev::fill_stat_emc_hist_limit_1_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const stat_emc_hist_limit_1_u old_value_t = { .reg32 = value };
    const stat_emc_hist_limit_1_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: emc_hist_limit_1:32", "", 32, old_value_t.emc_hist_limit_1, new_value_t.emc_hist_limit_1 };
    m_bit_details_model.bits.append(entry);
}

#define STAT_EMC_COUNT_OFFSET 0xB8
#define STAT_EMC_COUNT_UNDEFMASK 0x00000000
union stat_emc_count_u {
    struct {
        unsigned int emc_count_0:32;
    };

    u_int32_t reg32;
};

void McDev::fill_stat_emc_count_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const stat_emc_count_u old_value_t = { .reg32 = value };
    const stat_emc_count_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: emc_count_0:32", "", 32, old_value_t.emc_count_0, new_value_t.emc_count_0 };
    m_bit_details_model.bits.append(entry);
}

#define STAT_EMC_COUNT_1_OFFSET 0xBC
#define STAT_EMC_COUNT_1_UNDEFMASK 0x00000000
union stat_emc_count_1_u {
    struct {
        unsigned int emc_count_1:32;
    };

    u_int32_t reg32;
};

void McDev::fill_stat_emc_count_1_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const stat_emc_count_1_u old_value_t = { .reg32 = value };
    const stat_emc_count_1_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: emc_count_1:32", "", 32, old_value_t.emc_count_1, new_value_t.emc_count_1 };
    m_bit_details_model.bits.append(entry);
}

#define STAT_EMC_HIST_OFFSET 0xC0
#define STAT_EMC_HIST_UNDEFMASK 0x00000000
union stat_emc_hist_u {
    struct {
        unsigned int emc_hist_0:32;
    };

    u_int32_t reg32;
};

void McDev::fill_stat_emc_hist_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const stat_emc_hist_u old_value_t = { .reg32 = value };
    const stat_emc_hist_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: emc_hist_0:32", "", 32, old_value_t.emc_hist_0, new_value_t.emc_hist_0 };
    m_bit_details_model.bits.append(entry);
}

#define STAT_EMC_HIST_1_OFFSET 0xC4
#define STAT_EMC_HIST_1_UNDEFMASK 0x00000000
union stat_emc_hist_1_u {
    struct {
        unsigned int emc_hist_1:32;
    };

    u_int32_t reg32;
};

void McDev::fill_stat_emc_hist_1_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const stat_emc_hist_1_u old_value_t = { .reg32 = value };
    const stat_emc_hist_1_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: emc_hist_1:32", "", 32, old_value_t.emc_hist_1, new_value_t.emc_hist_1 };
    m_bit_details_model.bits.append(entry);
}

#define AXI_DECERR_OVR_OFFSET 0x108
#define AXI_DECERR_OVR_UNDEFMASK 0xFFFFFFFC
union axi_decerr_ovr_u {
    struct {
        unsigned int mpcorer_decerr_ovr:1;
        unsigned int mpcorew_decerr_ovr:1;
        unsigned int undefined_bits_2_31:30;
    };

    u_int32_t reg32;
};

void McDev::fill_axi_decerr_ovr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const axi_decerr_ovr_u old_value_t = { .reg32 = value };
    const axi_decerr_ovr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: mpcorer_decerr_ovr:1", "", 1, old_value_t.mpcorer_decerr_ovr, new_value_t.mpcorer_decerr_ovr };
    m_bit_details_model.bits.append(entry);
    entry = { "01: mpcorew_decerr_ovr:1", "", 1, old_value_t.mpcorew_decerr_ovr, new_value_t.mpcorew_decerr_ovr };
    m_bit_details_model.bits.append(entry);
    entry = { "02: undefined_bits_2_31:30", "", 30, old_value_t.undefined_bits_2_31, new_value_t.undefined_bits_2_31 };
    m_bit_details_model.bits.append(entry);
}

#define LOWLATENCY_CONFIG_OFFSET 0x10C
#define LOWLATENCY_CONFIG_UNDEFMASK 0x7FFFFFFC
union lowlatency_config_u {
    struct {
        unsigned int mpcorer_ll_ctrl:1;
        unsigned int mpcorer_ll_send_both:1;
        unsigned int undefined_bits_2_30:29;
        unsigned int ll_dram_interleave:1;
    };

    u_int32_t reg32;
};

void McDev::fill_lowlatency_config_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const lowlatency_config_u old_value_t = { .reg32 = value };
    const lowlatency_config_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: mpcorer_ll_ctrl:1", "", 1, old_value_t.mpcorer_ll_ctrl, new_value_t.mpcorer_ll_ctrl };
    m_bit_details_model.bits.append(entry);
    entry = { "01: mpcorer_ll_send_both:1", "", 1, old_value_t.mpcorer_ll_send_both, new_value_t.mpcorer_ll_send_both };
    m_bit_details_model.bits.append(entry);
    entry = { "02: undefined_bits_2_30:29", "", 29, old_value_t.undefined_bits_2_30, new_value_t.undefined_bits_2_30 };
    m_bit_details_model.bits.append(entry);
    entry = { "31: ll_dram_interleave:1", "", 1, old_value_t.ll_dram_interleave, new_value_t.ll_dram_interleave };
    m_bit_details_model.bits.append(entry);
}

#define AP_CTRL_OFFSET 0x128
#define AP_CTRL_UNDEFMASK 0x00000000
union ap_ctrl_u {
    struct {
        unsigned int display0a_apval:1;
        unsigned int display0ab_apval:1;
        unsigned int display0b_apval:1;
        unsigned int display0bb_apval:1;
        unsigned int display0c_apval:1;
        unsigned int display0cb_apval:1;
        unsigned int display1b_apval:1;
        unsigned int display1bb_apval:1;
        unsigned int eppup_apval:1;
        unsigned int g2pr_apval:1;
        unsigned int g2sr_apval:1;
        unsigned int mpeunifbr_apval:1;
        unsigned int viruv_apval:1;
        unsigned int avpcarm7r_apval:1;
        unsigned int displayhc_apval:1;
        unsigned int displayhcb_apval:1;
        unsigned int fdcdrd_apval:1;
        unsigned int g2dr_apval:1;
        unsigned int host1xdmar_apval:1;
        unsigned int host1xr_apval:1;
        unsigned int idxsrd_apval:1;
        unsigned int mpcorer_apval:1;
        unsigned int mpe_ipred_apval:1;
        unsigned int mpeamemrd_apval:1;
        unsigned int mpecsrd_apval:1;
        unsigned int ppcsahbdmar_apval:1;
        unsigned int ppcsahbslvr_apval:1;
        unsigned int texsrd_apval:1;
        unsigned int vdebsevr_apval:1;
        unsigned int vdember_apval:1;
        unsigned int vdemcer_apval:1;
        unsigned int vdetper_apval:1;
    };

    u_int32_t reg32;
};

void McDev::fill_ap_ctrl_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const ap_ctrl_u old_value_t = { .reg32 = value };
    const ap_ctrl_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: display0a_apval:1", "", 1, old_value_t.display0a_apval, new_value_t.display0a_apval };
    m_bit_details_model.bits.append(entry);
    entry = { "01: display0ab_apval:1", "", 1, old_value_t.display0ab_apval, new_value_t.display0ab_apval };
    m_bit_details_model.bits.append(entry);
    entry = { "02: display0b_apval:1", "", 1, old_value_t.display0b_apval, new_value_t.display0b_apval };
    m_bit_details_model.bits.append(entry);
    entry = { "03: display0bb_apval:1", "", 1, old_value_t.display0bb_apval, new_value_t.display0bb_apval };
    m_bit_details_model.bits.append(entry);
    entry = { "04: display0c_apval:1", "", 1, old_value_t.display0c_apval, new_value_t.display0c_apval };
    m_bit_details_model.bits.append(entry);
    entry = { "05: display0cb_apval:1", "", 1, old_value_t.display0cb_apval, new_value_t.display0cb_apval };
    m_bit_details_model.bits.append(entry);
    entry = { "06: display1b_apval:1", "", 1, old_value_t.display1b_apval, new_value_t.display1b_apval };
    m_bit_details_model.bits.append(entry);
    entry = { "07: display1bb_apval:1", "", 1, old_value_t.display1bb_apval, new_value_t.display1bb_apval };
    m_bit_details_model.bits.append(entry);
    entry = { "08: eppup_apval:1", "", 1, old_value_t.eppup_apval, new_value_t.eppup_apval };
    m_bit_details_model.bits.append(entry);
    entry = { "09: g2pr_apval:1", "", 1, old_value_t.g2pr_apval, new_value_t.g2pr_apval };
    m_bit_details_model.bits.append(entry);
    entry = { "10: g2sr_apval:1", "", 1, old_value_t.g2sr_apval, new_value_t.g2sr_apval };
    m_bit_details_model.bits.append(entry);
    entry = { "11: mpeunifbr_apval:1", "", 1, old_value_t.mpeunifbr_apval, new_value_t.mpeunifbr_apval };
    m_bit_details_model.bits.append(entry);
    entry = { "12: viruv_apval:1", "", 1, old_value_t.viruv_apval, new_value_t.viruv_apval };
    m_bit_details_model.bits.append(entry);
    entry = { "13: avpcarm7r_apval:1", "", 1, old_value_t.avpcarm7r_apval, new_value_t.avpcarm7r_apval };
    m_bit_details_model.bits.append(entry);
    entry = { "14: displayhc_apval:1", "", 1, old_value_t.displayhc_apval, new_value_t.displayhc_apval };
    m_bit_details_model.bits.append(entry);
    entry = { "15: displayhcb_apval:1", "", 1, old_value_t.displayhcb_apval, new_value_t.displayhcb_apval };
    m_bit_details_model.bits.append(entry);
    entry = { "16: fdcdrd_apval:1", "", 1, old_value_t.fdcdrd_apval, new_value_t.fdcdrd_apval };
    m_bit_details_model.bits.append(entry);
    entry = { "17: g2dr_apval:1", "", 1, old_value_t.g2dr_apval, new_value_t.g2dr_apval };
    m_bit_details_model.bits.append(entry);
    entry = { "18: host1xdmar_apval:1", "", 1, old_value_t.host1xdmar_apval, new_value_t.host1xdmar_apval };
    m_bit_details_model.bits.append(entry);
    entry = { "19: host1xr_apval:1", "", 1, old_value_t.host1xr_apval, new_value_t.host1xr_apval };
    m_bit_details_model.bits.append(entry);
    entry = { "20: idxsrd_apval:1", "", 1, old_value_t.idxsrd_apval, new_value_t.idxsrd_apval };
    m_bit_details_model.bits.append(entry);
    entry = { "21: mpcorer_apval:1", "", 1, old_value_t.mpcorer_apval, new_value_t.mpcorer_apval };
    m_bit_details_model.bits.append(entry);
    entry = { "22: mpe_ipred_apval:1", "", 1, old_value_t.mpe_ipred_apval, new_value_t.mpe_ipred_apval };
    m_bit_details_model.bits.append(entry);
    entry = { "23: mpeamemrd_apval:1", "", 1, old_value_t.mpeamemrd_apval, new_value_t.mpeamemrd_apval };
    m_bit_details_model.bits.append(entry);
    entry = { "24: mpecsrd_apval:1", "", 1, old_value_t.mpecsrd_apval, new_value_t.mpecsrd_apval };
    m_bit_details_model.bits.append(entry);
    entry = { "25: ppcsahbdmar_apval:1", "", 1, old_value_t.ppcsahbdmar_apval, new_value_t.ppcsahbdmar_apval };
    m_bit_details_model.bits.append(entry);
    entry = { "26: ppcsahbslvr_apval:1", "", 1, old_value_t.ppcsahbslvr_apval, new_value_t.ppcsahbslvr_apval };
    m_bit_details_model.bits.append(entry);
    entry = { "27: texsrd_apval:1", "", 1, old_value_t.texsrd_apval, new_value_t.texsrd_apval };
    m_bit_details_model.bits.append(entry);
    entry = { "28: vdebsevr_apval:1", "", 1, old_value_t.vdebsevr_apval, new_value_t.vdebsevr_apval };
    m_bit_details_model.bits.append(entry);
    entry = { "29: vdember_apval:1", "", 1, old_value_t.vdember_apval, new_value_t.vdember_apval };
    m_bit_details_model.bits.append(entry);
    entry = { "30: vdemcer_apval:1", "", 1, old_value_t.vdemcer_apval, new_value_t.vdemcer_apval };
    m_bit_details_model.bits.append(entry);
    entry = { "31: vdetper_apval:1", "", 1, old_value_t.vdetper_apval, new_value_t.vdetper_apval };
    m_bit_details_model.bits.append(entry);
}

#define AP_CTRL_1_OFFSET 0x12C
#define AP_CTRL_1_UNDEFMASK 0xFFF00000
union ap_ctrl_1_u {
    struct {
        unsigned int eppu_apval:1;
        unsigned int eppv_apval:1;
        unsigned int eppy_apval:1;
        unsigned int mpeunifbw_apval:1;
        unsigned int viwsb_apval:1;
        unsigned int viwu_apval:1;
        unsigned int viwv_apval:1;
        unsigned int viwy_apval:1;
        unsigned int g2dw_apval:1;
        unsigned int avpcarm7w_apval:1;
        unsigned int fdcdwr_apval:1;
        unsigned int host1xw_apval:1;
        unsigned int ispw_apval:1;
        unsigned int mpcorew_apval:1;
        unsigned int mpecswr_apval:1;
        unsigned int ppcsahbdmaw_apval:1;
        unsigned int ppcsahbslvw_apval:1;
        unsigned int vdebsevw_apval:1;
        unsigned int vdembew_apval:1;
        unsigned int vdetpmw_apval:1;
        unsigned int undefined_bits_20_31:12;
    };

    u_int32_t reg32;
};

void McDev::fill_ap_ctrl_1_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const ap_ctrl_1_u old_value_t = { .reg32 = value };
    const ap_ctrl_1_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: eppu_apval:1", "", 1, old_value_t.eppu_apval, new_value_t.eppu_apval };
    m_bit_details_model.bits.append(entry);
    entry = { "01: eppv_apval:1", "", 1, old_value_t.eppv_apval, new_value_t.eppv_apval };
    m_bit_details_model.bits.append(entry);
    entry = { "02: eppy_apval:1", "", 1, old_value_t.eppy_apval, new_value_t.eppy_apval };
    m_bit_details_model.bits.append(entry);
    entry = { "03: mpeunifbw_apval:1", "", 1, old_value_t.mpeunifbw_apval, new_value_t.mpeunifbw_apval };
    m_bit_details_model.bits.append(entry);
    entry = { "04: viwsb_apval:1", "", 1, old_value_t.viwsb_apval, new_value_t.viwsb_apval };
    m_bit_details_model.bits.append(entry);
    entry = { "05: viwu_apval:1", "", 1, old_value_t.viwu_apval, new_value_t.viwu_apval };
    m_bit_details_model.bits.append(entry);
    entry = { "06: viwv_apval:1", "", 1, old_value_t.viwv_apval, new_value_t.viwv_apval };
    m_bit_details_model.bits.append(entry);
    entry = { "07: viwy_apval:1", "", 1, old_value_t.viwy_apval, new_value_t.viwy_apval };
    m_bit_details_model.bits.append(entry);
    entry = { "08: g2dw_apval:1", "", 1, old_value_t.g2dw_apval, new_value_t.g2dw_apval };
    m_bit_details_model.bits.append(entry);
    entry = { "09: avpcarm7w_apval:1", "", 1, old_value_t.avpcarm7w_apval, new_value_t.avpcarm7w_apval };
    m_bit_details_model.bits.append(entry);
    entry = { "10: fdcdwr_apval:1", "", 1, old_value_t.fdcdwr_apval, new_value_t.fdcdwr_apval };
    m_bit_details_model.bits.append(entry);
    entry = { "11: host1xw_apval:1", "", 1, old_value_t.host1xw_apval, new_value_t.host1xw_apval };
    m_bit_details_model.bits.append(entry);
    entry = { "12: ispw_apval:1", "", 1, old_value_t.ispw_apval, new_value_t.ispw_apval };
    m_bit_details_model.bits.append(entry);
    entry = { "13: mpcorew_apval:1", "", 1, old_value_t.mpcorew_apval, new_value_t.mpcorew_apval };
    m_bit_details_model.bits.append(entry);
    entry = { "14: mpecswr_apval:1", "", 1, old_value_t.mpecswr_apval, new_value_t.mpecswr_apval };
    m_bit_details_model.bits.append(entry);
    entry = { "15: ppcsahbdmaw_apval:1", "", 1, old_value_t.ppcsahbdmaw_apval, new_value_t.ppcsahbdmaw_apval };
    m_bit_details_model.bits.append(entry);
    entry = { "16: ppcsahbslvw_apval:1", "", 1, old_value_t.ppcsahbslvw_apval, new_value_t.ppcsahbslvw_apval };
    m_bit_details_model.bits.append(entry);
    entry = { "17: vdebsevw_apval:1", "", 1, old_value_t.vdebsevw_apval, new_value_t.vdebsevw_apval };
    m_bit_details_model.bits.append(entry);
    entry = { "18: vdembew_apval:1", "", 1, old_value_t.vdembew_apval, new_value_t.vdembew_apval };
    m_bit_details_model.bits.append(entry);
    entry = { "19: vdetpmw_apval:1", "", 1, old_value_t.vdetpmw_apval, new_value_t.vdetpmw_apval };
    m_bit_details_model.bits.append(entry);
    entry = { "20: undefined_bits_20_31:12", "", 12, old_value_t.undefined_bits_20_31, new_value_t.undefined_bits_20_31 };
    m_bit_details_model.bits.append(entry);
}

#define CLIENT_ACTIVITY_MONITOR_EMEM_OFFSET 0x138
#define CLIENT_ACTIVITY_MONITOR_EMEM_UNDEFMASK 0x00000000
union client_activity_monitor_emem_u {
    struct {
        unsigned int display0a_emem_activity:1;
        unsigned int display0ab_emem_activity:1;
        unsigned int display0b_emem_activity:1;
        unsigned int display0bb_emem_activity:1;
        unsigned int display0c_emem_activity:1;
        unsigned int display0cb_emem_activity:1;
        unsigned int display1b_emem_activity:1;
        unsigned int display1bb_emem_activity:1;
        unsigned int eppup_emem_activity:1;
        unsigned int g2pr_emem_activity:1;
        unsigned int g2sr_emem_activity:1;
        unsigned int mpeunifbr_emem_activity:1;
        unsigned int viruv_emem_activity:1;
        unsigned int avpcarm7r_emem_activity:1;
        unsigned int displayhc_emem_activity:1;
        unsigned int displayhcb_emem_activity:1;
        unsigned int fdcdrd_emem_activity:1;
        unsigned int g2dr_emem_activity:1;
        unsigned int host1xdmar_emem_activity:1;
        unsigned int host1xr_emem_activity:1;
        unsigned int idxsrd_emem_activity:1;
        unsigned int mpcorer_emem_activity:1;
        unsigned int mpe_ipred_emem_activity:1;
        unsigned int mpeamemrd_emem_activity:1;
        unsigned int mpecsrd_emem_activity:1;
        unsigned int ppcsahbdmar_emem_activity:1;
        unsigned int ppcsahbslvr_emem_activity:1;
        unsigned int texsrd_emem_activity:1;
        unsigned int vdebsevr_emem_activity:1;
        unsigned int vdember_emem_activity:1;
        unsigned int vdemcer_emem_activity:1;
        unsigned int vdetper_emem_activity:1;
    };

    u_int32_t reg32;
};

void McDev::fill_client_activity_monitor_emem_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const client_activity_monitor_emem_u old_value_t = { .reg32 = value };
    const client_activity_monitor_emem_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: display0a_emem_activity:1", "", 1, old_value_t.display0a_emem_activity, new_value_t.display0a_emem_activity };
    m_bit_details_model.bits.append(entry);
    entry = { "01: display0ab_emem_activity:1", "", 1, old_value_t.display0ab_emem_activity, new_value_t.display0ab_emem_activity };
    m_bit_details_model.bits.append(entry);
    entry = { "02: display0b_emem_activity:1", "", 1, old_value_t.display0b_emem_activity, new_value_t.display0b_emem_activity };
    m_bit_details_model.bits.append(entry);
    entry = { "03: display0bb_emem_activity:1", "", 1, old_value_t.display0bb_emem_activity, new_value_t.display0bb_emem_activity };
    m_bit_details_model.bits.append(entry);
    entry = { "04: display0c_emem_activity:1", "", 1, old_value_t.display0c_emem_activity, new_value_t.display0c_emem_activity };
    m_bit_details_model.bits.append(entry);
    entry = { "05: display0cb_emem_activity:1", "", 1, old_value_t.display0cb_emem_activity, new_value_t.display0cb_emem_activity };
    m_bit_details_model.bits.append(entry);
    entry = { "06: display1b_emem_activity:1", "", 1, old_value_t.display1b_emem_activity, new_value_t.display1b_emem_activity };
    m_bit_details_model.bits.append(entry);
    entry = { "07: display1bb_emem_activity:1", "", 1, old_value_t.display1bb_emem_activity, new_value_t.display1bb_emem_activity };
    m_bit_details_model.bits.append(entry);
    entry = { "08: eppup_emem_activity:1", "", 1, old_value_t.eppup_emem_activity, new_value_t.eppup_emem_activity };
    m_bit_details_model.bits.append(entry);
    entry = { "09: g2pr_emem_activity:1", "", 1, old_value_t.g2pr_emem_activity, new_value_t.g2pr_emem_activity };
    m_bit_details_model.bits.append(entry);
    entry = { "10: g2sr_emem_activity:1", "", 1, old_value_t.g2sr_emem_activity, new_value_t.g2sr_emem_activity };
    m_bit_details_model.bits.append(entry);
    entry = { "11: mpeunifbr_emem_activity:1", "", 1, old_value_t.mpeunifbr_emem_activity, new_value_t.mpeunifbr_emem_activity };
    m_bit_details_model.bits.append(entry);
    entry = { "12: viruv_emem_activity:1", "", 1, old_value_t.viruv_emem_activity, new_value_t.viruv_emem_activity };
    m_bit_details_model.bits.append(entry);
    entry = { "13: avpcarm7r_emem_activity:1", "", 1, old_value_t.avpcarm7r_emem_activity, new_value_t.avpcarm7r_emem_activity };
    m_bit_details_model.bits.append(entry);
    entry = { "14: displayhc_emem_activity:1", "", 1, old_value_t.displayhc_emem_activity, new_value_t.displayhc_emem_activity };
    m_bit_details_model.bits.append(entry);
    entry = { "15: displayhcb_emem_activity:1", "", 1, old_value_t.displayhcb_emem_activity, new_value_t.displayhcb_emem_activity };
    m_bit_details_model.bits.append(entry);
    entry = { "16: fdcdrd_emem_activity:1", "", 1, old_value_t.fdcdrd_emem_activity, new_value_t.fdcdrd_emem_activity };
    m_bit_details_model.bits.append(entry);
    entry = { "17: g2dr_emem_activity:1", "", 1, old_value_t.g2dr_emem_activity, new_value_t.g2dr_emem_activity };
    m_bit_details_model.bits.append(entry);
    entry = { "18: host1xdmar_emem_activity:1", "", 1, old_value_t.host1xdmar_emem_activity, new_value_t.host1xdmar_emem_activity };
    m_bit_details_model.bits.append(entry);
    entry = { "19: host1xr_emem_activity:1", "", 1, old_value_t.host1xr_emem_activity, new_value_t.host1xr_emem_activity };
    m_bit_details_model.bits.append(entry);
    entry = { "20: idxsrd_emem_activity:1", "", 1, old_value_t.idxsrd_emem_activity, new_value_t.idxsrd_emem_activity };
    m_bit_details_model.bits.append(entry);
    entry = { "21: mpcorer_emem_activity:1", "", 1, old_value_t.mpcorer_emem_activity, new_value_t.mpcorer_emem_activity };
    m_bit_details_model.bits.append(entry);
    entry = { "22: mpe_ipred_emem_activity:1", "", 1, old_value_t.mpe_ipred_emem_activity, new_value_t.mpe_ipred_emem_activity };
    m_bit_details_model.bits.append(entry);
    entry = { "23: mpeamemrd_emem_activity:1", "", 1, old_value_t.mpeamemrd_emem_activity, new_value_t.mpeamemrd_emem_activity };
    m_bit_details_model.bits.append(entry);
    entry = { "24: mpecsrd_emem_activity:1", "", 1, old_value_t.mpecsrd_emem_activity, new_value_t.mpecsrd_emem_activity };
    m_bit_details_model.bits.append(entry);
    entry = { "25: ppcsahbdmar_emem_activity:1", "", 1, old_value_t.ppcsahbdmar_emem_activity, new_value_t.ppcsahbdmar_emem_activity };
    m_bit_details_model.bits.append(entry);
    entry = { "26: ppcsahbslvr_emem_activity:1", "", 1, old_value_t.ppcsahbslvr_emem_activity, new_value_t.ppcsahbslvr_emem_activity };
    m_bit_details_model.bits.append(entry);
    entry = { "27: texsrd_emem_activity:1", "", 1, old_value_t.texsrd_emem_activity, new_value_t.texsrd_emem_activity };
    m_bit_details_model.bits.append(entry);
    entry = { "28: vdebsevr_emem_activity:1", "", 1, old_value_t.vdebsevr_emem_activity, new_value_t.vdebsevr_emem_activity };
    m_bit_details_model.bits.append(entry);
    entry = { "29: vdember_emem_activity:1", "", 1, old_value_t.vdember_emem_activity, new_value_t.vdember_emem_activity };
    m_bit_details_model.bits.append(entry);
    entry = { "30: vdemcer_emem_activity:1", "", 1, old_value_t.vdemcer_emem_activity, new_value_t.vdemcer_emem_activity };
    m_bit_details_model.bits.append(entry);
    entry = { "31: vdetper_emem_activity:1", "", 1, old_value_t.vdetper_emem_activity, new_value_t.vdetper_emem_activity };
    m_bit_details_model.bits.append(entry);
}

#define CLIENT_ACTIVITY_MONITOR_EMEM_1_OFFSET 0x13C
#define CLIENT_ACTIVITY_MONITOR_EMEM_1_UNDEFMASK 0xFFF00000
union client_activity_monitor_emem_1_u {
    struct {
        unsigned int eppu_emem_activity:1;
        unsigned int eppv_emem_activity:1;
        unsigned int eppy_emem_activity:1;
        unsigned int mpeunifbw_emem_activity:1;
        unsigned int viwsb_emem_activity:1;
        unsigned int viwu_emem_activity:1;
        unsigned int viwv_emem_activity:1;
        unsigned int viwy_emem_activity:1;
        unsigned int g2dw_emem_activity:1;
        unsigned int avpcarm7w_emem_activity:1;
        unsigned int fdcdwr_emem_activity:1;
        unsigned int host1xw_emem_activity:1;
        unsigned int ispw_emem_activity:1;
        unsigned int mpcorew_emem_activity:1;
        unsigned int mpecswr_emem_activity:1;
        unsigned int ppcsahbdmaw_emem_activity:1;
        unsigned int ppcsahbslvw_emem_activity:1;
        unsigned int vdebsevw_emem_activity:1;
        unsigned int vdembew_emem_activity:1;
        unsigned int vdetpmw_emem_activity:1;
        unsigned int undefined_bits_20_31:12;
    };

    u_int32_t reg32;
};

void McDev::fill_client_activity_monitor_emem_1_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const client_activity_monitor_emem_1_u old_value_t = { .reg32 = value };
    const client_activity_monitor_emem_1_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: eppu_emem_activity:1", "", 1, old_value_t.eppu_emem_activity, new_value_t.eppu_emem_activity };
    m_bit_details_model.bits.append(entry);
    entry = { "01: eppv_emem_activity:1", "", 1, old_value_t.eppv_emem_activity, new_value_t.eppv_emem_activity };
    m_bit_details_model.bits.append(entry);
    entry = { "02: eppy_emem_activity:1", "", 1, old_value_t.eppy_emem_activity, new_value_t.eppy_emem_activity };
    m_bit_details_model.bits.append(entry);
    entry = { "03: mpeunifbw_emem_activity:1", "", 1, old_value_t.mpeunifbw_emem_activity, new_value_t.mpeunifbw_emem_activity };
    m_bit_details_model.bits.append(entry);
    entry = { "04: viwsb_emem_activity:1", "", 1, old_value_t.viwsb_emem_activity, new_value_t.viwsb_emem_activity };
    m_bit_details_model.bits.append(entry);
    entry = { "05: viwu_emem_activity:1", "", 1, old_value_t.viwu_emem_activity, new_value_t.viwu_emem_activity };
    m_bit_details_model.bits.append(entry);
    entry = { "06: viwv_emem_activity:1", "", 1, old_value_t.viwv_emem_activity, new_value_t.viwv_emem_activity };
    m_bit_details_model.bits.append(entry);
    entry = { "07: viwy_emem_activity:1", "", 1, old_value_t.viwy_emem_activity, new_value_t.viwy_emem_activity };
    m_bit_details_model.bits.append(entry);
    entry = { "08: g2dw_emem_activity:1", "", 1, old_value_t.g2dw_emem_activity, new_value_t.g2dw_emem_activity };
    m_bit_details_model.bits.append(entry);
    entry = { "09: avpcarm7w_emem_activity:1", "", 1, old_value_t.avpcarm7w_emem_activity, new_value_t.avpcarm7w_emem_activity };
    m_bit_details_model.bits.append(entry);
    entry = { "10: fdcdwr_emem_activity:1", "", 1, old_value_t.fdcdwr_emem_activity, new_value_t.fdcdwr_emem_activity };
    m_bit_details_model.bits.append(entry);
    entry = { "11: host1xw_emem_activity:1", "", 1, old_value_t.host1xw_emem_activity, new_value_t.host1xw_emem_activity };
    m_bit_details_model.bits.append(entry);
    entry = { "12: ispw_emem_activity:1", "", 1, old_value_t.ispw_emem_activity, new_value_t.ispw_emem_activity };
    m_bit_details_model.bits.append(entry);
    entry = { "13: mpcorew_emem_activity:1", "", 1, old_value_t.mpcorew_emem_activity, new_value_t.mpcorew_emem_activity };
    m_bit_details_model.bits.append(entry);
    entry = { "14: mpecswr_emem_activity:1", "", 1, old_value_t.mpecswr_emem_activity, new_value_t.mpecswr_emem_activity };
    m_bit_details_model.bits.append(entry);
    entry = { "15: ppcsahbdmaw_emem_activity:1", "", 1, old_value_t.ppcsahbdmaw_emem_activity, new_value_t.ppcsahbdmaw_emem_activity };
    m_bit_details_model.bits.append(entry);
    entry = { "16: ppcsahbslvw_emem_activity:1", "", 1, old_value_t.ppcsahbslvw_emem_activity, new_value_t.ppcsahbslvw_emem_activity };
    m_bit_details_model.bits.append(entry);
    entry = { "17: vdebsevw_emem_activity:1", "", 1, old_value_t.vdebsevw_emem_activity, new_value_t.vdebsevw_emem_activity };
    m_bit_details_model.bits.append(entry);
    entry = { "18: vdembew_emem_activity:1", "", 1, old_value_t.vdembew_emem_activity, new_value_t.vdembew_emem_activity };
    m_bit_details_model.bits.append(entry);
    entry = { "19: vdetpmw_emem_activity:1", "", 1, old_value_t.vdetpmw_emem_activity, new_value_t.vdetpmw_emem_activity };
    m_bit_details_model.bits.append(entry);
    entry = { "20: undefined_bits_20_31:12", "", 12, old_value_t.undefined_bits_20_31, new_value_t.undefined_bits_20_31 };
    m_bit_details_model.bits.append(entry);
}

bool McDev::is_offset_valid(const u_int32_t &offset) const
{
    switch (offset) {
    case EMEM_CFG_OFFSET:
    case EMEM_ADR_CFG_OFFSET:
    case EMEM_ARB_CFG0_OFFSET:
    case EMEM_ARB_CFG1_OFFSET:
    case EMEM_ARB_CFG2_OFFSET:
    case GART_CONFIG_OFFSET:
    case GART_ENTRY_ADDR_OFFSET:
    case GART_ENTRY_DATA_OFFSET:
    case GART_ERROR_REQ_OFFSET:
    case GART_ERROR_ADDR_OFFSET:
    case TIMEOUT_CTRL_OFFSET:
    case DECERR_EMEM_OTHERS_STATUS_OFFSET:
    case DECERR_EMEM_OTHERS_ADR_OFFSET:
    case CLIENT_CTRL_OFFSET:
    case CLIENT_HOTRESETN_OFFSET:
    case LOWLATENCY_RAWLOGIC_WRITE_PARTICIPANTS_OFFSET:
    case BWSHARE_TMVAL_OFFSET:
    case BWSHARE_EMEM_CTRL_OFFSET:
    case BWSHARE_EMEM_CTRL_1_OFFSET:
    case AVPC_ORRC_OFFSET:
    case DC_ORRC_OFFSET:
    case DCB_ORRC_OFFSET:
    case EPP_ORRC_OFFSET:
    case G2_ORRC_OFFSET:
    case HC_ORRC_OFFSET:
    case ISP_ORRC_OFFSET:
    case MPCORE_ORRC_OFFSET:
    case MPEA_ORRC_OFFSET:
    case MPEB_ORRC_OFFSET:
    case MPEC_ORRC_OFFSET:
    case NV_ORRC_OFFSET:
    case PPCS_ORRC_OFFSET:
    case VDE_ORRC_OFFSET:
    case VI_ORRC_OFFSET:
    case FPRI_CTRL_AVPC_OFFSET:
    case FPRI_CTRL_DC_OFFSET:
    case FPRI_CTRL_DCB_OFFSET:
    case FPRI_CTRL_EPP_OFFSET:
    case FPRI_CTRL_G2_OFFSET:
    case FPRI_CTRL_HC_OFFSET:
    case FPRI_CTRL_ISP_OFFSET:
    case FPRI_CTRL_MPCORE_OFFSET:
    case FPRI_CTRL_MPEA_OFFSET:
    case FPRI_CTRL_MPEB_OFFSET:
    case FPRI_CTRL_MPEC_OFFSET:
    case FPRI_CTRL_NV_OFFSET:
    case FPRI_CTRL_PPCS_OFFSET:
    case FPRI_CTRL_VDE_OFFSET:
    case FPRI_CTRL_VI_OFFSET:
    case TIMEOUT_AVPC_OFFSET:
    case TIMEOUT_DC_OFFSET:
    case TIMEOUT_DCB_OFFSET:
    case TIMEOUT_EPP_OFFSET:
    case TIMEOUT_G2_OFFSET:
    case TIMEOUT_HC_OFFSET:
    case TIMEOUT_ISP_OFFSET:
    case TIMEOUT_MPCORE_OFFSET:
    case TIMEOUT_MPEA_OFFSET:
    case TIMEOUT_MPEB_OFFSET:
    case TIMEOUT_MPEC_OFFSET:
    case TIMEOUT_NV_OFFSET:
    case TIMEOUT_PPCS_OFFSET:
    case TIMEOUT_VDE_OFFSET:
    case TIMEOUT_VI_OFFSET:
    case TIMEOUT_RCOAL_AVPC_OFFSET:
    case TIMEOUT_RCOAL_DC_OFFSET:
    case TIMEOUT1_RCOAL_DC_OFFSET:
    case TIMEOUT_RCOAL_DCB_OFFSET:
    case TIMEOUT1_RCOAL_DCB_OFFSET:
    case TIMEOUT_RCOAL_EPP_OFFSET:
    case TIMEOUT_RCOAL_G2_OFFSET:
    case TIMEOUT_RCOAL_HC_OFFSET:
    case TIMEOUT_RCOAL_MPCORE_OFFSET:
    case TIMEOUT_RCOAL_MPEA_OFFSET:
    case TIMEOUT_RCOAL_MPEB_OFFSET:
    case TIMEOUT_RCOAL_MPEC_OFFSET:
    case TIMEOUT_RCOAL_NV_OFFSET:
    case TIMEOUT_RCOAL_PPCS_OFFSET:
    case TIMEOUT_RCOAL_VDE_OFFSET:
    case TIMEOUT_RCOAL_VI_OFFSET:
    case RCOAL_AUTODISABLE_OFFSET:
    case BWSHARE_AVPC_OFFSET:
    case BWSHARE_DC_OFFSET:
    case BWSHARE_DCB_OFFSET:
    case BWSHARE_EPP_OFFSET:
    case BWSHARE_G2_OFFSET:
    case BWSHARE_HC_OFFSET:
    case BWSHARE_ISP_OFFSET:
    case BWSHARE_MPCORE_OFFSET:
    case BWSHARE_MPEA_OFFSET:
    case BWSHARE_MPEB_OFFSET:
    case BWSHARE_MPEC_OFFSET:
    case BWSHARE_NV_OFFSET:
    case BWSHARE_PPCS_OFFSET:
    case BWSHARE_VDE_OFFSET:
    case BWSHARE_VI_OFFSET:
    case INTSTATUS_OFFSET:
    case INTMASK_OFFSET:
    case CLKEN_OVERRIDE_OFFSET:
    case SECURITY_CFG0_OFFSET:
    case SECURITY_CFG1_OFFSET:
    case SECURITY_VIOLATION_STATUS_OFFSET:
    case SECURITY_VIOLATION_ADR_OFFSET:
    case SECURITY_CFG2_OFFSET:
    case STAT_CONTROL_OFFSET:
    case STAT_STATUS_OFFSET:
    case STAT_EMC_ADDR_LOW_OFFSET:
    case STAT_EMC_ADDR_HIGH_OFFSET:
    case STAT_EMC_CLOCK_LIMIT_OFFSET:
    case STAT_EMC_CLOCKS_OFFSET:
    case STAT_EMC_CONTROL_OFFSET:
    case STAT_EMC_CONTROL_1_OFFSET:
    case STAT_EMC_HIST_LIMIT_OFFSET:
    case STAT_EMC_HIST_LIMIT_1_OFFSET:
    case STAT_EMC_COUNT_OFFSET:
    case STAT_EMC_COUNT_1_OFFSET:
    case STAT_EMC_HIST_OFFSET:
    case STAT_EMC_HIST_1_OFFSET:
    case AXI_DECERR_OVR_OFFSET:
    case LOWLATENCY_CONFIG_OFFSET:
    case AP_CTRL_OFFSET:
    case AP_CTRL_1_OFFSET:
    case CLIENT_ACTIVITY_MONITOR_EMEM_OFFSET:
    case CLIENT_ACTIVITY_MONITOR_EMEM_1_OFFSET:
        return true;
    default:
        break;
    }

    return false;
}

bool McDev::is_undef_changed(const u_int32_t &offset,
                                           const u_int32_t &value,
                                           const u_int32_t &new_value) const
{
    switch (offset) {
    case EMEM_CFG_OFFSET:
        if ((value ^ new_value) & EMEM_CFG_UNDEFMASK)
            return true;
        break;
    case EMEM_ADR_CFG_OFFSET:
        if ((value ^ new_value) & EMEM_ADR_CFG_UNDEFMASK)
            return true;
        break;
    case EMEM_ARB_CFG0_OFFSET:
        if ((value ^ new_value) & EMEM_ARB_CFG0_UNDEFMASK)
            return true;
        break;
    case EMEM_ARB_CFG1_OFFSET:
        if ((value ^ new_value) & EMEM_ARB_CFG1_UNDEFMASK)
            return true;
        break;
    case EMEM_ARB_CFG2_OFFSET:
        if ((value ^ new_value) & EMEM_ARB_CFG2_UNDEFMASK)
            return true;
        break;
    case GART_CONFIG_OFFSET:
        if ((value ^ new_value) & GART_CONFIG_UNDEFMASK)
            return true;
        break;
    case GART_ENTRY_ADDR_OFFSET:
        if ((value ^ new_value) & GART_ENTRY_ADDR_UNDEFMASK)
            return true;
        break;
    case GART_ENTRY_DATA_OFFSET:
        if ((value ^ new_value) & GART_ENTRY_DATA_UNDEFMASK)
            return true;
        break;
    case GART_ERROR_REQ_OFFSET:
        if ((value ^ new_value) & GART_ERROR_REQ_UNDEFMASK)
            return true;
        break;
    case GART_ERROR_ADDR_OFFSET:
        if ((value ^ new_value) & GART_ERROR_ADDR_UNDEFMASK)
            return true;
        break;
    case TIMEOUT_CTRL_OFFSET:
        if ((value ^ new_value) & TIMEOUT_CTRL_UNDEFMASK)
            return true;
        break;
    case DECERR_EMEM_OTHERS_STATUS_OFFSET:
        if ((value ^ new_value) & DECERR_EMEM_OTHERS_STATUS_UNDEFMASK)
            return true;
        break;
    case DECERR_EMEM_OTHERS_ADR_OFFSET:
        if ((value ^ new_value) & DECERR_EMEM_OTHERS_ADR_UNDEFMASK)
            return true;
        break;
    case CLIENT_CTRL_OFFSET:
        if ((value ^ new_value) & CLIENT_CTRL_UNDEFMASK)
            return true;
        break;
    case CLIENT_HOTRESETN_OFFSET:
        if ((value ^ new_value) & CLIENT_HOTRESETN_UNDEFMASK)
            return true;
        break;
    case LOWLATENCY_RAWLOGIC_WRITE_PARTICIPANTS_OFFSET:
        if ((value ^ new_value) & LOWLATENCY_RAWLOGIC_WRITE_PARTICIPANTS_UNDEFMASK)
            return true;
        break;
    case BWSHARE_TMVAL_OFFSET:
        if ((value ^ new_value) & BWSHARE_TMVAL_UNDEFMASK)
            return true;
        break;
    case BWSHARE_EMEM_CTRL_OFFSET:
        if ((value ^ new_value) & BWSHARE_EMEM_CTRL_UNDEFMASK)
            return true;
        break;
    case BWSHARE_EMEM_CTRL_1_OFFSET:
        if ((value ^ new_value) & BWSHARE_EMEM_CTRL_1_UNDEFMASK)
            return true;
        break;
    case AVPC_ORRC_OFFSET:
        if ((value ^ new_value) & AVPC_ORRC_UNDEFMASK)
            return true;
        break;
    case DC_ORRC_OFFSET:
        if ((value ^ new_value) & DC_ORRC_UNDEFMASK)
            return true;
        break;
    case DCB_ORRC_OFFSET:
        if ((value ^ new_value) & DCB_ORRC_UNDEFMASK)
            return true;
        break;
    case EPP_ORRC_OFFSET:
        if ((value ^ new_value) & EPP_ORRC_UNDEFMASK)
            return true;
        break;
    case G2_ORRC_OFFSET:
        if ((value ^ new_value) & G2_ORRC_UNDEFMASK)
            return true;
        break;
    case HC_ORRC_OFFSET:
        if ((value ^ new_value) & HC_ORRC_UNDEFMASK)
            return true;
        break;
    case ISP_ORRC_OFFSET:
        if ((value ^ new_value) & ISP_ORRC_UNDEFMASK)
            return true;
        break;
    case MPCORE_ORRC_OFFSET:
        if ((value ^ new_value) & MPCORE_ORRC_UNDEFMASK)
            return true;
        break;
    case MPEA_ORRC_OFFSET:
        if ((value ^ new_value) & MPEA_ORRC_UNDEFMASK)
            return true;
        break;
    case MPEB_ORRC_OFFSET:
        if ((value ^ new_value) & MPEB_ORRC_UNDEFMASK)
            return true;
        break;
    case MPEC_ORRC_OFFSET:
        if ((value ^ new_value) & MPEC_ORRC_UNDEFMASK)
            return true;
        break;
    case NV_ORRC_OFFSET:
        if ((value ^ new_value) & NV_ORRC_UNDEFMASK)
            return true;
        break;
    case PPCS_ORRC_OFFSET:
        if ((value ^ new_value) & PPCS_ORRC_UNDEFMASK)
            return true;
        break;
    case VDE_ORRC_OFFSET:
        if ((value ^ new_value) & VDE_ORRC_UNDEFMASK)
            return true;
        break;
    case VI_ORRC_OFFSET:
        if ((value ^ new_value) & VI_ORRC_UNDEFMASK)
            return true;
        break;
    case FPRI_CTRL_AVPC_OFFSET:
        if ((value ^ new_value) & FPRI_CTRL_AVPC_UNDEFMASK)
            return true;
        break;
    case FPRI_CTRL_DC_OFFSET:
        if ((value ^ new_value) & FPRI_CTRL_DC_UNDEFMASK)
            return true;
        break;
    case FPRI_CTRL_DCB_OFFSET:
        if ((value ^ new_value) & FPRI_CTRL_DCB_UNDEFMASK)
            return true;
        break;
    case FPRI_CTRL_EPP_OFFSET:
        if ((value ^ new_value) & FPRI_CTRL_EPP_UNDEFMASK)
            return true;
        break;
    case FPRI_CTRL_G2_OFFSET:
        if ((value ^ new_value) & FPRI_CTRL_G2_UNDEFMASK)
            return true;
        break;
    case FPRI_CTRL_HC_OFFSET:
        if ((value ^ new_value) & FPRI_CTRL_HC_UNDEFMASK)
            return true;
        break;
    case FPRI_CTRL_ISP_OFFSET:
        if ((value ^ new_value) & FPRI_CTRL_ISP_UNDEFMASK)
            return true;
        break;
    case FPRI_CTRL_MPCORE_OFFSET:
        if ((value ^ new_value) & FPRI_CTRL_MPCORE_UNDEFMASK)
            return true;
        break;
    case FPRI_CTRL_MPEA_OFFSET:
        if ((value ^ new_value) & FPRI_CTRL_MPEA_UNDEFMASK)
            return true;
        break;
    case FPRI_CTRL_MPEB_OFFSET:
        if ((value ^ new_value) & FPRI_CTRL_MPEB_UNDEFMASK)
            return true;
        break;
    case FPRI_CTRL_MPEC_OFFSET:
        if ((value ^ new_value) & FPRI_CTRL_MPEC_UNDEFMASK)
            return true;
        break;
    case FPRI_CTRL_NV_OFFSET:
        if ((value ^ new_value) & FPRI_CTRL_NV_UNDEFMASK)
            return true;
        break;
    case FPRI_CTRL_PPCS_OFFSET:
        if ((value ^ new_value) & FPRI_CTRL_PPCS_UNDEFMASK)
            return true;
        break;
    case FPRI_CTRL_VDE_OFFSET:
        if ((value ^ new_value) & FPRI_CTRL_VDE_UNDEFMASK)
            return true;
        break;
    case FPRI_CTRL_VI_OFFSET:
        if ((value ^ new_value) & FPRI_CTRL_VI_UNDEFMASK)
            return true;
        break;
    case TIMEOUT_AVPC_OFFSET:
        if ((value ^ new_value) & TIMEOUT_AVPC_UNDEFMASK)
            return true;
        break;
    case TIMEOUT_DC_OFFSET:
        if ((value ^ new_value) & TIMEOUT_DC_UNDEFMASK)
            return true;
        break;
    case TIMEOUT_DCB_OFFSET:
        if ((value ^ new_value) & TIMEOUT_DCB_UNDEFMASK)
            return true;
        break;
    case TIMEOUT_EPP_OFFSET:
        if ((value ^ new_value) & TIMEOUT_EPP_UNDEFMASK)
            return true;
        break;
    case TIMEOUT_G2_OFFSET:
        if ((value ^ new_value) & TIMEOUT_G2_UNDEFMASK)
            return true;
        break;
    case TIMEOUT_HC_OFFSET:
        if ((value ^ new_value) & TIMEOUT_HC_UNDEFMASK)
            return true;
        break;
    case TIMEOUT_ISP_OFFSET:
        if ((value ^ new_value) & TIMEOUT_ISP_UNDEFMASK)
            return true;
        break;
    case TIMEOUT_MPCORE_OFFSET:
        if ((value ^ new_value) & TIMEOUT_MPCORE_UNDEFMASK)
            return true;
        break;
    case TIMEOUT_MPEA_OFFSET:
        if ((value ^ new_value) & TIMEOUT_MPEA_UNDEFMASK)
            return true;
        break;
    case TIMEOUT_MPEB_OFFSET:
        if ((value ^ new_value) & TIMEOUT_MPEB_UNDEFMASK)
            return true;
        break;
    case TIMEOUT_MPEC_OFFSET:
        if ((value ^ new_value) & TIMEOUT_MPEC_UNDEFMASK)
            return true;
        break;
    case TIMEOUT_NV_OFFSET:
        if ((value ^ new_value) & TIMEOUT_NV_UNDEFMASK)
            return true;
        break;
    case TIMEOUT_PPCS_OFFSET:
        if ((value ^ new_value) & TIMEOUT_PPCS_UNDEFMASK)
            return true;
        break;
    case TIMEOUT_VDE_OFFSET:
        if ((value ^ new_value) & TIMEOUT_VDE_UNDEFMASK)
            return true;
        break;
    case TIMEOUT_VI_OFFSET:
        if ((value ^ new_value) & TIMEOUT_VI_UNDEFMASK)
            return true;
        break;
    case TIMEOUT_RCOAL_AVPC_OFFSET:
        if ((value ^ new_value) & TIMEOUT_RCOAL_AVPC_UNDEFMASK)
            return true;
        break;
    case TIMEOUT_RCOAL_DC_OFFSET:
        if ((value ^ new_value) & TIMEOUT_RCOAL_DC_UNDEFMASK)
            return true;
        break;
    case TIMEOUT1_RCOAL_DC_OFFSET:
        if ((value ^ new_value) & TIMEOUT1_RCOAL_DC_UNDEFMASK)
            return true;
        break;
    case TIMEOUT_RCOAL_DCB_OFFSET:
        if ((value ^ new_value) & TIMEOUT_RCOAL_DCB_UNDEFMASK)
            return true;
        break;
    case TIMEOUT1_RCOAL_DCB_OFFSET:
        if ((value ^ new_value) & TIMEOUT1_RCOAL_DCB_UNDEFMASK)
            return true;
        break;
    case TIMEOUT_RCOAL_EPP_OFFSET:
        if ((value ^ new_value) & TIMEOUT_RCOAL_EPP_UNDEFMASK)
            return true;
        break;
    case TIMEOUT_RCOAL_G2_OFFSET:
        if ((value ^ new_value) & TIMEOUT_RCOAL_G2_UNDEFMASK)
            return true;
        break;
    case TIMEOUT_RCOAL_HC_OFFSET:
        if ((value ^ new_value) & TIMEOUT_RCOAL_HC_UNDEFMASK)
            return true;
        break;
    case TIMEOUT_RCOAL_MPCORE_OFFSET:
        if ((value ^ new_value) & TIMEOUT_RCOAL_MPCORE_UNDEFMASK)
            return true;
        break;
    case TIMEOUT_RCOAL_MPEA_OFFSET:
        if ((value ^ new_value) & TIMEOUT_RCOAL_MPEA_UNDEFMASK)
            return true;
        break;
    case TIMEOUT_RCOAL_MPEB_OFFSET:
        if ((value ^ new_value) & TIMEOUT_RCOAL_MPEB_UNDEFMASK)
            return true;
        break;
    case TIMEOUT_RCOAL_MPEC_OFFSET:
        if ((value ^ new_value) & TIMEOUT_RCOAL_MPEC_UNDEFMASK)
            return true;
        break;
    case TIMEOUT_RCOAL_NV_OFFSET:
        if ((value ^ new_value) & TIMEOUT_RCOAL_NV_UNDEFMASK)
            return true;
        break;
    case TIMEOUT_RCOAL_PPCS_OFFSET:
        if ((value ^ new_value) & TIMEOUT_RCOAL_PPCS_UNDEFMASK)
            return true;
        break;
    case TIMEOUT_RCOAL_VDE_OFFSET:
        if ((value ^ new_value) & TIMEOUT_RCOAL_VDE_UNDEFMASK)
            return true;
        break;
    case TIMEOUT_RCOAL_VI_OFFSET:
        if ((value ^ new_value) & TIMEOUT_RCOAL_VI_UNDEFMASK)
            return true;
        break;
    case RCOAL_AUTODISABLE_OFFSET:
        if ((value ^ new_value) & RCOAL_AUTODISABLE_UNDEFMASK)
            return true;
        break;
    case BWSHARE_AVPC_OFFSET:
        if ((value ^ new_value) & BWSHARE_AVPC_UNDEFMASK)
            return true;
        break;
    case BWSHARE_DC_OFFSET:
        if ((value ^ new_value) & BWSHARE_DC_UNDEFMASK)
            return true;
        break;
    case BWSHARE_DCB_OFFSET:
        if ((value ^ new_value) & BWSHARE_DCB_UNDEFMASK)
            return true;
        break;
    case BWSHARE_EPP_OFFSET:
        if ((value ^ new_value) & BWSHARE_EPP_UNDEFMASK)
            return true;
        break;
    case BWSHARE_G2_OFFSET:
        if ((value ^ new_value) & BWSHARE_G2_UNDEFMASK)
            return true;
        break;
    case BWSHARE_HC_OFFSET:
        if ((value ^ new_value) & BWSHARE_HC_UNDEFMASK)
            return true;
        break;
    case BWSHARE_ISP_OFFSET:
        if ((value ^ new_value) & BWSHARE_ISP_UNDEFMASK)
            return true;
        break;
    case BWSHARE_MPCORE_OFFSET:
        if ((value ^ new_value) & BWSHARE_MPCORE_UNDEFMASK)
            return true;
        break;
    case BWSHARE_MPEA_OFFSET:
        if ((value ^ new_value) & BWSHARE_MPEA_UNDEFMASK)
            return true;
        break;
    case BWSHARE_MPEB_OFFSET:
        if ((value ^ new_value) & BWSHARE_MPEB_UNDEFMASK)
            return true;
        break;
    case BWSHARE_MPEC_OFFSET:
        if ((value ^ new_value) & BWSHARE_MPEC_UNDEFMASK)
            return true;
        break;
    case BWSHARE_NV_OFFSET:
        if ((value ^ new_value) & BWSHARE_NV_UNDEFMASK)
            return true;
        break;
    case BWSHARE_PPCS_OFFSET:
        if ((value ^ new_value) & BWSHARE_PPCS_UNDEFMASK)
            return true;
        break;
    case BWSHARE_VDE_OFFSET:
        if ((value ^ new_value) & BWSHARE_VDE_UNDEFMASK)
            return true;
        break;
    case BWSHARE_VI_OFFSET:
        if ((value ^ new_value) & BWSHARE_VI_UNDEFMASK)
            return true;
        break;
    case INTSTATUS_OFFSET:
        if ((value ^ new_value) & INTSTATUS_UNDEFMASK)
            return true;
        break;
    case INTMASK_OFFSET:
        if ((value ^ new_value) & INTMASK_UNDEFMASK)
            return true;
        break;
    case CLKEN_OVERRIDE_OFFSET:
        if ((value ^ new_value) & CLKEN_OVERRIDE_UNDEFMASK)
            return true;
        break;
    case SECURITY_CFG0_OFFSET:
        if ((value ^ new_value) & SECURITY_CFG0_UNDEFMASK)
            return true;
        break;
    case SECURITY_CFG1_OFFSET:
        if ((value ^ new_value) & SECURITY_CFG1_UNDEFMASK)
            return true;
        break;
    case SECURITY_VIOLATION_STATUS_OFFSET:
        if ((value ^ new_value) & SECURITY_VIOLATION_STATUS_UNDEFMASK)
            return true;
        break;
    case SECURITY_VIOLATION_ADR_OFFSET:
        if ((value ^ new_value) & SECURITY_VIOLATION_ADR_UNDEFMASK)
            return true;
        break;
    case SECURITY_CFG2_OFFSET:
        if ((value ^ new_value) & SECURITY_CFG2_UNDEFMASK)
            return true;
        break;
    case STAT_CONTROL_OFFSET:
        if ((value ^ new_value) & STAT_CONTROL_UNDEFMASK)
            return true;
        break;
    case STAT_STATUS_OFFSET:
        if ((value ^ new_value) & STAT_STATUS_UNDEFMASK)
            return true;
        break;
    case STAT_EMC_ADDR_LOW_OFFSET:
        if ((value ^ new_value) & STAT_EMC_ADDR_LOW_UNDEFMASK)
            return true;
        break;
    case STAT_EMC_ADDR_HIGH_OFFSET:
        if ((value ^ new_value) & STAT_EMC_ADDR_HIGH_UNDEFMASK)
            return true;
        break;
    case STAT_EMC_CLOCK_LIMIT_OFFSET:
        if ((value ^ new_value) & STAT_EMC_CLOCK_LIMIT_UNDEFMASK)
            return true;
        break;
    case STAT_EMC_CLOCKS_OFFSET:
        if ((value ^ new_value) & STAT_EMC_CLOCKS_UNDEFMASK)
            return true;
        break;
    case STAT_EMC_CONTROL_OFFSET:
        if ((value ^ new_value) & STAT_EMC_CONTROL_UNDEFMASK)
            return true;
        break;
    case STAT_EMC_CONTROL_1_OFFSET:
        if ((value ^ new_value) & STAT_EMC_CONTROL_1_UNDEFMASK)
            return true;
        break;
    case STAT_EMC_HIST_LIMIT_OFFSET:
        if ((value ^ new_value) & STAT_EMC_HIST_LIMIT_UNDEFMASK)
            return true;
        break;
    case STAT_EMC_HIST_LIMIT_1_OFFSET:
        if ((value ^ new_value) & STAT_EMC_HIST_LIMIT_1_UNDEFMASK)
            return true;
        break;
    case STAT_EMC_COUNT_OFFSET:
        if ((value ^ new_value) & STAT_EMC_COUNT_UNDEFMASK)
            return true;
        break;
    case STAT_EMC_COUNT_1_OFFSET:
        if ((value ^ new_value) & STAT_EMC_COUNT_1_UNDEFMASK)
            return true;
        break;
    case STAT_EMC_HIST_OFFSET:
        if ((value ^ new_value) & STAT_EMC_HIST_UNDEFMASK)
            return true;
        break;
    case STAT_EMC_HIST_1_OFFSET:
        if ((value ^ new_value) & STAT_EMC_HIST_1_UNDEFMASK)
            return true;
        break;
    case AXI_DECERR_OVR_OFFSET:
        if ((value ^ new_value) & AXI_DECERR_OVR_UNDEFMASK)
            return true;
        break;
    case LOWLATENCY_CONFIG_OFFSET:
        if ((value ^ new_value) & LOWLATENCY_CONFIG_UNDEFMASK)
            return true;
        break;
    case AP_CTRL_OFFSET:
        if ((value ^ new_value) & AP_CTRL_UNDEFMASK)
            return true;
        break;
    case AP_CTRL_1_OFFSET:
        if ((value ^ new_value) & AP_CTRL_1_UNDEFMASK)
            return true;
        break;
    case CLIENT_ACTIVITY_MONITOR_EMEM_OFFSET:
        if ((value ^ new_value) & CLIENT_ACTIVITY_MONITOR_EMEM_UNDEFMASK)
            return true;
        break;
    case CLIENT_ACTIVITY_MONITOR_EMEM_1_OFFSET:
        if ((value ^ new_value) & CLIENT_ACTIVITY_MONITOR_EMEM_1_UNDEFMASK)
            return true;
        break;

    default:
        break;
    }

    return false;
}

QString McDev::get_register_name(const log_entry &entry) const
{
    switch (entry.offset) {
    case EMEM_CFG_OFFSET:
        return QString("EMEM_CFG");
    case EMEM_ADR_CFG_OFFSET:
        return QString("EMEM_ADR_CFG");
    case EMEM_ARB_CFG0_OFFSET:
        return QString("EMEM_ARB_CFG0");
    case EMEM_ARB_CFG1_OFFSET:
        return QString("EMEM_ARB_CFG1");
    case EMEM_ARB_CFG2_OFFSET:
        return QString("EMEM_ARB_CFG2");
    case GART_CONFIG_OFFSET:
        return QString("GART_CONFIG");
    case GART_ENTRY_ADDR_OFFSET:
        return QString("GART_ENTRY_ADDR");
    case GART_ENTRY_DATA_OFFSET:
        return QString("GART_ENTRY_DATA");
    case GART_ERROR_REQ_OFFSET:
        return QString("GART_ERROR_REQ");
    case GART_ERROR_ADDR_OFFSET:
        return QString("GART_ERROR_ADDR");
    case TIMEOUT_CTRL_OFFSET:
        return QString("TIMEOUT_CTRL");
    case DECERR_EMEM_OTHERS_STATUS_OFFSET:
        return QString("DECERR_EMEM_OTHERS_STATUS");
    case DECERR_EMEM_OTHERS_ADR_OFFSET:
        return QString("DECERR_EMEM_OTHERS_ADR");
    case CLIENT_CTRL_OFFSET:
        return QString("CLIENT_CTRL");
    case CLIENT_HOTRESETN_OFFSET:
        return QString("CLIENT_HOTRESETN");
    case LOWLATENCY_RAWLOGIC_WRITE_PARTICIPANTS_OFFSET:
        return QString("LOWLATENCY_RAWLOGIC_WRITE_PARTICIPANTS");
    case BWSHARE_TMVAL_OFFSET:
        return QString("BWSHARE_TMVAL");
    case BWSHARE_EMEM_CTRL_OFFSET:
        return QString("BWSHARE_EMEM_CTRL");
    case BWSHARE_EMEM_CTRL_1_OFFSET:
        return QString("BWSHARE_EMEM_CTRL_1");
    case AVPC_ORRC_OFFSET:
        return QString("AVPC_ORRC");
    case DC_ORRC_OFFSET:
        return QString("DC_ORRC");
    case DCB_ORRC_OFFSET:
        return QString("DCB_ORRC");
    case EPP_ORRC_OFFSET:
        return QString("EPP_ORRC");
    case G2_ORRC_OFFSET:
        return QString("G2_ORRC");
    case HC_ORRC_OFFSET:
        return QString("HC_ORRC");
    case ISP_ORRC_OFFSET:
        return QString("ISP_ORRC");
    case MPCORE_ORRC_OFFSET:
        return QString("MPCORE_ORRC");
    case MPEA_ORRC_OFFSET:
        return QString("MPEA_ORRC");
    case MPEB_ORRC_OFFSET:
        return QString("MPEB_ORRC");
    case MPEC_ORRC_OFFSET:
        return QString("MPEC_ORRC");
    case NV_ORRC_OFFSET:
        return QString("NV_ORRC");
    case PPCS_ORRC_OFFSET:
        return QString("PPCS_ORRC");
    case VDE_ORRC_OFFSET:
        return QString("VDE_ORRC");
    case VI_ORRC_OFFSET:
        return QString("VI_ORRC");
    case FPRI_CTRL_AVPC_OFFSET:
        return QString("FPRI_CTRL_AVPC");
    case FPRI_CTRL_DC_OFFSET:
        return QString("FPRI_CTRL_DC");
    case FPRI_CTRL_DCB_OFFSET:
        return QString("FPRI_CTRL_DCB");
    case FPRI_CTRL_EPP_OFFSET:
        return QString("FPRI_CTRL_EPP");
    case FPRI_CTRL_G2_OFFSET:
        return QString("FPRI_CTRL_G2");
    case FPRI_CTRL_HC_OFFSET:
        return QString("FPRI_CTRL_HC");
    case FPRI_CTRL_ISP_OFFSET:
        return QString("FPRI_CTRL_ISP");
    case FPRI_CTRL_MPCORE_OFFSET:
        return QString("FPRI_CTRL_MPCORE");
    case FPRI_CTRL_MPEA_OFFSET:
        return QString("FPRI_CTRL_MPEA");
    case FPRI_CTRL_MPEB_OFFSET:
        return QString("FPRI_CTRL_MPEB");
    case FPRI_CTRL_MPEC_OFFSET:
        return QString("FPRI_CTRL_MPEC");
    case FPRI_CTRL_NV_OFFSET:
        return QString("FPRI_CTRL_NV");
    case FPRI_CTRL_PPCS_OFFSET:
        return QString("FPRI_CTRL_PPCS");
    case FPRI_CTRL_VDE_OFFSET:
        return QString("FPRI_CTRL_VDE");
    case FPRI_CTRL_VI_OFFSET:
        return QString("FPRI_CTRL_VI");
    case TIMEOUT_AVPC_OFFSET:
        return QString("TIMEOUT_AVPC");
    case TIMEOUT_DC_OFFSET:
        return QString("TIMEOUT_DC");
    case TIMEOUT_DCB_OFFSET:
        return QString("TIMEOUT_DCB");
    case TIMEOUT_EPP_OFFSET:
        return QString("TIMEOUT_EPP");
    case TIMEOUT_G2_OFFSET:
        return QString("TIMEOUT_G2");
    case TIMEOUT_HC_OFFSET:
        return QString("TIMEOUT_HC");
    case TIMEOUT_ISP_OFFSET:
        return QString("TIMEOUT_ISP");
    case TIMEOUT_MPCORE_OFFSET:
        return QString("TIMEOUT_MPCORE");
    case TIMEOUT_MPEA_OFFSET:
        return QString("TIMEOUT_MPEA");
    case TIMEOUT_MPEB_OFFSET:
        return QString("TIMEOUT_MPEB");
    case TIMEOUT_MPEC_OFFSET:
        return QString("TIMEOUT_MPEC");
    case TIMEOUT_NV_OFFSET:
        return QString("TIMEOUT_NV");
    case TIMEOUT_PPCS_OFFSET:
        return QString("TIMEOUT_PPCS");
    case TIMEOUT_VDE_OFFSET:
        return QString("TIMEOUT_VDE");
    case TIMEOUT_VI_OFFSET:
        return QString("TIMEOUT_VI");
    case TIMEOUT_RCOAL_AVPC_OFFSET:
        return QString("TIMEOUT_RCOAL_AVPC");
    case TIMEOUT_RCOAL_DC_OFFSET:
        return QString("TIMEOUT_RCOAL_DC");
    case TIMEOUT1_RCOAL_DC_OFFSET:
        return QString("TIMEOUT1_RCOAL_DC");
    case TIMEOUT_RCOAL_DCB_OFFSET:
        return QString("TIMEOUT_RCOAL_DCB");
    case TIMEOUT1_RCOAL_DCB_OFFSET:
        return QString("TIMEOUT1_RCOAL_DCB");
    case TIMEOUT_RCOAL_EPP_OFFSET:
        return QString("TIMEOUT_RCOAL_EPP");
    case TIMEOUT_RCOAL_G2_OFFSET:
        return QString("TIMEOUT_RCOAL_G2");
    case TIMEOUT_RCOAL_HC_OFFSET:
        return QString("TIMEOUT_RCOAL_HC");
    case TIMEOUT_RCOAL_MPCORE_OFFSET:
        return QString("TIMEOUT_RCOAL_MPCORE");
    case TIMEOUT_RCOAL_MPEA_OFFSET:
        return QString("TIMEOUT_RCOAL_MPEA");
    case TIMEOUT_RCOAL_MPEB_OFFSET:
        return QString("TIMEOUT_RCOAL_MPEB");
    case TIMEOUT_RCOAL_MPEC_OFFSET:
        return QString("TIMEOUT_RCOAL_MPEC");
    case TIMEOUT_RCOAL_NV_OFFSET:
        return QString("TIMEOUT_RCOAL_NV");
    case TIMEOUT_RCOAL_PPCS_OFFSET:
        return QString("TIMEOUT_RCOAL_PPCS");
    case TIMEOUT_RCOAL_VDE_OFFSET:
        return QString("TIMEOUT_RCOAL_VDE");
    case TIMEOUT_RCOAL_VI_OFFSET:
        return QString("TIMEOUT_RCOAL_VI");
    case RCOAL_AUTODISABLE_OFFSET:
        return QString("RCOAL_AUTODISABLE");
    case BWSHARE_AVPC_OFFSET:
        return QString("BWSHARE_AVPC");
    case BWSHARE_DC_OFFSET:
        return QString("BWSHARE_DC");
    case BWSHARE_DCB_OFFSET:
        return QString("BWSHARE_DCB");
    case BWSHARE_EPP_OFFSET:
        return QString("BWSHARE_EPP");
    case BWSHARE_G2_OFFSET:
        return QString("BWSHARE_G2");
    case BWSHARE_HC_OFFSET:
        return QString("BWSHARE_HC");
    case BWSHARE_ISP_OFFSET:
        return QString("BWSHARE_ISP");
    case BWSHARE_MPCORE_OFFSET:
        return QString("BWSHARE_MPCORE");
    case BWSHARE_MPEA_OFFSET:
        return QString("BWSHARE_MPEA");
    case BWSHARE_MPEB_OFFSET:
        return QString("BWSHARE_MPEB");
    case BWSHARE_MPEC_OFFSET:
        return QString("BWSHARE_MPEC");
    case BWSHARE_NV_OFFSET:
        return QString("BWSHARE_NV");
    case BWSHARE_PPCS_OFFSET:
        return QString("BWSHARE_PPCS");
    case BWSHARE_VDE_OFFSET:
        return QString("BWSHARE_VDE");
    case BWSHARE_VI_OFFSET:
        return QString("BWSHARE_VI");
    case INTSTATUS_OFFSET:
        return QString("INTSTATUS");
    case INTMASK_OFFSET:
        return QString("INTMASK");
    case CLKEN_OVERRIDE_OFFSET:
        return QString("CLKEN_OVERRIDE");
    case SECURITY_CFG0_OFFSET:
        return QString("SECURITY_CFG0");
    case SECURITY_CFG1_OFFSET:
        return QString("SECURITY_CFG1");
    case SECURITY_VIOLATION_STATUS_OFFSET:
        return QString("SECURITY_VIOLATION_STATUS");
    case SECURITY_VIOLATION_ADR_OFFSET:
        return QString("SECURITY_VIOLATION_ADR");
    case SECURITY_CFG2_OFFSET:
        return QString("SECURITY_CFG2");
    case STAT_CONTROL_OFFSET:
        return QString("STAT_CONTROL");
    case STAT_STATUS_OFFSET:
        return QString("STAT_STATUS");
    case STAT_EMC_ADDR_LOW_OFFSET:
        return QString("STAT_EMC_ADDR_LOW");
    case STAT_EMC_ADDR_HIGH_OFFSET:
        return QString("STAT_EMC_ADDR_HIGH");
    case STAT_EMC_CLOCK_LIMIT_OFFSET:
        return QString("STAT_EMC_CLOCK_LIMIT");
    case STAT_EMC_CLOCKS_OFFSET:
        return QString("STAT_EMC_CLOCKS");
    case STAT_EMC_CONTROL_OFFSET:
        return QString("STAT_EMC_CONTROL");
    case STAT_EMC_CONTROL_1_OFFSET:
        return QString("STAT_EMC_CONTROL_1");
    case STAT_EMC_HIST_LIMIT_OFFSET:
        return QString("STAT_EMC_HIST_LIMIT");
    case STAT_EMC_HIST_LIMIT_1_OFFSET:
        return QString("STAT_EMC_HIST_LIMIT_1");
    case STAT_EMC_COUNT_OFFSET:
        return QString("STAT_EMC_COUNT");
    case STAT_EMC_COUNT_1_OFFSET:
        return QString("STAT_EMC_COUNT_1");
    case STAT_EMC_HIST_OFFSET:
        return QString("STAT_EMC_HIST");
    case STAT_EMC_HIST_1_OFFSET:
        return QString("STAT_EMC_HIST_1");
    case AXI_DECERR_OVR_OFFSET:
        return QString("AXI_DECERR_OVR");
    case LOWLATENCY_CONFIG_OFFSET:
        return QString("LOWLATENCY_CONFIG");
    case AP_CTRL_OFFSET:
        return QString("AP_CTRL");
    case AP_CTRL_1_OFFSET:
        return QString("AP_CTRL_1");
    case CLIENT_ACTIVITY_MONITOR_EMEM_OFFSET:
        return QString("CLIENT_ACTIVITY_MONITOR_EMEM");
    case CLIENT_ACTIVITY_MONITOR_EMEM_1_OFFSET:
        return QString("CLIENT_ACTIVITY_MONITOR_EMEM_1");

    default:
        break;
    }

    qDebug() << QString().sprintf("MC: %s: Ooops... 0x%x", __func__, entry.offset);

    return QString().sprintf("Ooops... @0x%X", entry.offset);
}

void McDev::fill_bits_details(const u_int32_t &offset,
                                      const u_int32_t &value, const u_int32_t &new_value)
{
    switch (offset) {
    case EMEM_CFG_OFFSET:
        fill_emem_cfg_details(value, new_value);
        break;
    case EMEM_ADR_CFG_OFFSET:
        fill_emem_adr_cfg_details(value, new_value);
        break;
    case EMEM_ARB_CFG0_OFFSET:
        fill_emem_arb_cfg0_details(value, new_value);
        break;
    case EMEM_ARB_CFG1_OFFSET:
        fill_emem_arb_cfg1_details(value, new_value);
        break;
    case EMEM_ARB_CFG2_OFFSET:
        fill_emem_arb_cfg2_details(value, new_value);
        break;
    case GART_CONFIG_OFFSET:
        fill_gart_config_details(value, new_value);
        break;
    case GART_ENTRY_ADDR_OFFSET:
        fill_gart_entry_addr_details(value, new_value);
        break;
    case GART_ENTRY_DATA_OFFSET:
        fill_gart_entry_data_details(value, new_value);
        break;
    case GART_ERROR_REQ_OFFSET:
        fill_gart_error_req_details(value, new_value);
        break;
    case GART_ERROR_ADDR_OFFSET:
        fill_gart_error_addr_details(value, new_value);
        break;
    case TIMEOUT_CTRL_OFFSET:
        fill_timeout_ctrl_details(value, new_value);
        break;
    case DECERR_EMEM_OTHERS_STATUS_OFFSET:
        fill_decerr_emem_others_status_details(value, new_value);
        break;
    case DECERR_EMEM_OTHERS_ADR_OFFSET:
        fill_decerr_emem_others_adr_details(value, new_value);
        break;
    case CLIENT_CTRL_OFFSET:
        fill_client_ctrl_details(value, new_value);
        break;
    case CLIENT_HOTRESETN_OFFSET:
        fill_client_hotresetn_details(value, new_value);
        break;
    case LOWLATENCY_RAWLOGIC_WRITE_PARTICIPANTS_OFFSET:
        fill_lowlatency_rawlogic_write_participants_details(value, new_value);
        break;
    case BWSHARE_TMVAL_OFFSET:
        fill_bwshare_tmval_details(value, new_value);
        break;
    case BWSHARE_EMEM_CTRL_OFFSET:
        fill_bwshare_emem_ctrl_details(value, new_value);
        break;
    case BWSHARE_EMEM_CTRL_1_OFFSET:
        fill_bwshare_emem_ctrl_1_details(value, new_value);
        break;
    case AVPC_ORRC_OFFSET:
        fill_avpc_orrc_details(value, new_value);
        break;
    case DC_ORRC_OFFSET:
        fill_dc_orrc_details(value, new_value);
        break;
    case DCB_ORRC_OFFSET:
        fill_dcb_orrc_details(value, new_value);
        break;
    case EPP_ORRC_OFFSET:
        fill_epp_orrc_details(value, new_value);
        break;
    case G2_ORRC_OFFSET:
        fill_g2_orrc_details(value, new_value);
        break;
    case HC_ORRC_OFFSET:
        fill_hc_orrc_details(value, new_value);
        break;
    case ISP_ORRC_OFFSET:
        fill_isp_orrc_details(value, new_value);
        break;
    case MPCORE_ORRC_OFFSET:
        fill_mpcore_orrc_details(value, new_value);
        break;
    case MPEA_ORRC_OFFSET:
        fill_mpea_orrc_details(value, new_value);
        break;
    case MPEB_ORRC_OFFSET:
        fill_mpeb_orrc_details(value, new_value);
        break;
    case MPEC_ORRC_OFFSET:
        fill_mpec_orrc_details(value, new_value);
        break;
    case NV_ORRC_OFFSET:
        fill_nv_orrc_details(value, new_value);
        break;
    case PPCS_ORRC_OFFSET:
        fill_ppcs_orrc_details(value, new_value);
        break;
    case VDE_ORRC_OFFSET:
        fill_vde_orrc_details(value, new_value);
        break;
    case VI_ORRC_OFFSET:
        fill_vi_orrc_details(value, new_value);
        break;
    case FPRI_CTRL_AVPC_OFFSET:
        fill_fpri_ctrl_avpc_details(value, new_value);
        break;
    case FPRI_CTRL_DC_OFFSET:
        fill_fpri_ctrl_dc_details(value, new_value);
        break;
    case FPRI_CTRL_DCB_OFFSET:
        fill_fpri_ctrl_dcb_details(value, new_value);
        break;
    case FPRI_CTRL_EPP_OFFSET:
        fill_fpri_ctrl_epp_details(value, new_value);
        break;
    case FPRI_CTRL_G2_OFFSET:
        fill_fpri_ctrl_g2_details(value, new_value);
        break;
    case FPRI_CTRL_HC_OFFSET:
        fill_fpri_ctrl_hc_details(value, new_value);
        break;
    case FPRI_CTRL_ISP_OFFSET:
        fill_fpri_ctrl_isp_details(value, new_value);
        break;
    case FPRI_CTRL_MPCORE_OFFSET:
        fill_fpri_ctrl_mpcore_details(value, new_value);
        break;
    case FPRI_CTRL_MPEA_OFFSET:
        fill_fpri_ctrl_mpea_details(value, new_value);
        break;
    case FPRI_CTRL_MPEB_OFFSET:
        fill_fpri_ctrl_mpeb_details(value, new_value);
        break;
    case FPRI_CTRL_MPEC_OFFSET:
        fill_fpri_ctrl_mpec_details(value, new_value);
        break;
    case FPRI_CTRL_NV_OFFSET:
        fill_fpri_ctrl_nv_details(value, new_value);
        break;
    case FPRI_CTRL_PPCS_OFFSET:
        fill_fpri_ctrl_ppcs_details(value, new_value);
        break;
    case FPRI_CTRL_VDE_OFFSET:
        fill_fpri_ctrl_vde_details(value, new_value);
        break;
    case FPRI_CTRL_VI_OFFSET:
        fill_fpri_ctrl_vi_details(value, new_value);
        break;
    case TIMEOUT_AVPC_OFFSET:
        fill_timeout_avpc_details(value, new_value);
        break;
    case TIMEOUT_DC_OFFSET:
        fill_timeout_dc_details(value, new_value);
        break;
    case TIMEOUT_DCB_OFFSET:
        fill_timeout_dcb_details(value, new_value);
        break;
    case TIMEOUT_EPP_OFFSET:
        fill_timeout_epp_details(value, new_value);
        break;
    case TIMEOUT_G2_OFFSET:
        fill_timeout_g2_details(value, new_value);
        break;
    case TIMEOUT_HC_OFFSET:
        fill_timeout_hc_details(value, new_value);
        break;
    case TIMEOUT_ISP_OFFSET:
        fill_timeout_isp_details(value, new_value);
        break;
    case TIMEOUT_MPCORE_OFFSET:
        fill_timeout_mpcore_details(value, new_value);
        break;
    case TIMEOUT_MPEA_OFFSET:
        fill_timeout_mpea_details(value, new_value);
        break;
    case TIMEOUT_MPEB_OFFSET:
        fill_timeout_mpeb_details(value, new_value);
        break;
    case TIMEOUT_MPEC_OFFSET:
        fill_timeout_mpec_details(value, new_value);
        break;
    case TIMEOUT_NV_OFFSET:
        fill_timeout_nv_details(value, new_value);
        break;
    case TIMEOUT_PPCS_OFFSET:
        fill_timeout_ppcs_details(value, new_value);
        break;
    case TIMEOUT_VDE_OFFSET:
        fill_timeout_vde_details(value, new_value);
        break;
    case TIMEOUT_VI_OFFSET:
        fill_timeout_vi_details(value, new_value);
        break;
    case TIMEOUT_RCOAL_AVPC_OFFSET:
        fill_timeout_rcoal_avpc_details(value, new_value);
        break;
    case TIMEOUT_RCOAL_DC_OFFSET:
        fill_timeout_rcoal_dc_details(value, new_value);
        break;
    case TIMEOUT1_RCOAL_DC_OFFSET:
        fill_timeout1_rcoal_dc_details(value, new_value);
        break;
    case TIMEOUT_RCOAL_DCB_OFFSET:
        fill_timeout_rcoal_dcb_details(value, new_value);
        break;
    case TIMEOUT1_RCOAL_DCB_OFFSET:
        fill_timeout1_rcoal_dcb_details(value, new_value);
        break;
    case TIMEOUT_RCOAL_EPP_OFFSET:
        fill_timeout_rcoal_epp_details(value, new_value);
        break;
    case TIMEOUT_RCOAL_G2_OFFSET:
        fill_timeout_rcoal_g2_details(value, new_value);
        break;
    case TIMEOUT_RCOAL_HC_OFFSET:
        fill_timeout_rcoal_hc_details(value, new_value);
        break;
    case TIMEOUT_RCOAL_MPCORE_OFFSET:
        fill_timeout_rcoal_mpcore_details(value, new_value);
        break;
    case TIMEOUT_RCOAL_MPEA_OFFSET:
        fill_timeout_rcoal_mpea_details(value, new_value);
        break;
    case TIMEOUT_RCOAL_MPEB_OFFSET:
        fill_timeout_rcoal_mpeb_details(value, new_value);
        break;
    case TIMEOUT_RCOAL_MPEC_OFFSET:
        fill_timeout_rcoal_mpec_details(value, new_value);
        break;
    case TIMEOUT_RCOAL_NV_OFFSET:
        fill_timeout_rcoal_nv_details(value, new_value);
        break;
    case TIMEOUT_RCOAL_PPCS_OFFSET:
        fill_timeout_rcoal_ppcs_details(value, new_value);
        break;
    case TIMEOUT_RCOAL_VDE_OFFSET:
        fill_timeout_rcoal_vde_details(value, new_value);
        break;
    case TIMEOUT_RCOAL_VI_OFFSET:
        fill_timeout_rcoal_vi_details(value, new_value);
        break;
    case RCOAL_AUTODISABLE_OFFSET:
        fill_rcoal_autodisable_details(value, new_value);
        break;
    case BWSHARE_AVPC_OFFSET:
        fill_bwshare_avpc_details(value, new_value);
        break;
    case BWSHARE_DC_OFFSET:
        fill_bwshare_dc_details(value, new_value);
        break;
    case BWSHARE_DCB_OFFSET:
        fill_bwshare_dcb_details(value, new_value);
        break;
    case BWSHARE_EPP_OFFSET:
        fill_bwshare_epp_details(value, new_value);
        break;
    case BWSHARE_G2_OFFSET:
        fill_bwshare_g2_details(value, new_value);
        break;
    case BWSHARE_HC_OFFSET:
        fill_bwshare_hc_details(value, new_value);
        break;
    case BWSHARE_ISP_OFFSET:
        fill_bwshare_isp_details(value, new_value);
        break;
    case BWSHARE_MPCORE_OFFSET:
        fill_bwshare_mpcore_details(value, new_value);
        break;
    case BWSHARE_MPEA_OFFSET:
        fill_bwshare_mpea_details(value, new_value);
        break;
    case BWSHARE_MPEB_OFFSET:
        fill_bwshare_mpeb_details(value, new_value);
        break;
    case BWSHARE_MPEC_OFFSET:
        fill_bwshare_mpec_details(value, new_value);
        break;
    case BWSHARE_NV_OFFSET:
        fill_bwshare_nv_details(value, new_value);
        break;
    case BWSHARE_PPCS_OFFSET:
        fill_bwshare_ppcs_details(value, new_value);
        break;
    case BWSHARE_VDE_OFFSET:
        fill_bwshare_vde_details(value, new_value);
        break;
    case BWSHARE_VI_OFFSET:
        fill_bwshare_vi_details(value, new_value);
        break;
    case INTSTATUS_OFFSET:
        fill_intstatus_details(value, new_value);
        break;
    case INTMASK_OFFSET:
        fill_intmask_details(value, new_value);
        break;
    case CLKEN_OVERRIDE_OFFSET:
        fill_clken_override_details(value, new_value);
        break;
    case SECURITY_CFG0_OFFSET:
        fill_security_cfg0_details(value, new_value);
        break;
    case SECURITY_CFG1_OFFSET:
        fill_security_cfg1_details(value, new_value);
        break;
    case SECURITY_VIOLATION_STATUS_OFFSET:
        fill_security_violation_status_details(value, new_value);
        break;
    case SECURITY_VIOLATION_ADR_OFFSET:
        fill_security_violation_adr_details(value, new_value);
        break;
    case SECURITY_CFG2_OFFSET:
        fill_security_cfg2_details(value, new_value);
        break;
    case STAT_CONTROL_OFFSET:
        fill_stat_control_details(value, new_value);
        break;
    case STAT_STATUS_OFFSET:
        fill_stat_status_details(value, new_value);
        break;
    case STAT_EMC_ADDR_LOW_OFFSET:
        fill_stat_emc_addr_low_details(value, new_value);
        break;
    case STAT_EMC_ADDR_HIGH_OFFSET:
        fill_stat_emc_addr_high_details(value, new_value);
        break;
    case STAT_EMC_CLOCK_LIMIT_OFFSET:
        fill_stat_emc_clock_limit_details(value, new_value);
        break;
    case STAT_EMC_CLOCKS_OFFSET:
        fill_stat_emc_clocks_details(value, new_value);
        break;
    case STAT_EMC_CONTROL_OFFSET:
        fill_stat_emc_control_details(value, new_value);
        break;
    case STAT_EMC_CONTROL_1_OFFSET:
        fill_stat_emc_control_1_details(value, new_value);
        break;
    case STAT_EMC_HIST_LIMIT_OFFSET:
        fill_stat_emc_hist_limit_details(value, new_value);
        break;
    case STAT_EMC_HIST_LIMIT_1_OFFSET:
        fill_stat_emc_hist_limit_1_details(value, new_value);
        break;
    case STAT_EMC_COUNT_OFFSET:
        fill_stat_emc_count_details(value, new_value);
        break;
    case STAT_EMC_COUNT_1_OFFSET:
        fill_stat_emc_count_1_details(value, new_value);
        break;
    case STAT_EMC_HIST_OFFSET:
        fill_stat_emc_hist_details(value, new_value);
        break;
    case STAT_EMC_HIST_1_OFFSET:
        fill_stat_emc_hist_1_details(value, new_value);
        break;
    case AXI_DECERR_OVR_OFFSET:
        fill_axi_decerr_ovr_details(value, new_value);
        break;
    case LOWLATENCY_CONFIG_OFFSET:
        fill_lowlatency_config_details(value, new_value);
        break;
    case AP_CTRL_OFFSET:
        fill_ap_ctrl_details(value, new_value);
        break;
    case AP_CTRL_1_OFFSET:
        fill_ap_ctrl_1_details(value, new_value);
        break;
    case CLIENT_ACTIVITY_MONITOR_EMEM_OFFSET:
        fill_client_activity_monitor_emem_details(value, new_value);
        break;
    case CLIENT_ACTIVITY_MONITOR_EMEM_1_OFFSET:
        fill_client_activity_monitor_emem_1_details(value, new_value);
        break;

    default:
        m_bit_details_model.bits.clear();
        break;
    }
}
