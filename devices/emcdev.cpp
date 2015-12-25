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

#include "emcdev.h"

#include <QDebug>

#define INTSTATUS_OFFSET 0x0
#define INTSTATUS_UNDEFMASK 0xFFFFFFC7
union emc_intstatus_u {
    struct {
        unsigned int undefined_bits_0_2:3;
        unsigned int refresh_overflow_int:1;/* Refresh request overflow timeout. 0 = CLEAR 1 = SET */
        unsigned int clkchange_complete_int:1;/* CAR/EMC clock-change handshake complete. 0 = CLEAR 1 = SET */
        unsigned int mrr_divld_int:1;       /* LPDDR2 MRR data is available to be read. 0 = CLEAR 1 = SET */
        unsigned int undefined_bits_6_31:26;
    };

    u_int32_t reg32;
};

void EmcDev::fill_intstatus_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const emc_intstatus_u old_value_t = { .reg32 = value };
    const emc_intstatus_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_2:3", "", 3, old_value_t.undefined_bits_0_2, new_value_t.undefined_bits_0_2 };
    m_bit_details_model.bits.append(entry);
    entry = { "03: refresh_overflow_int:1",
              "Refresh request overflow timeout.\n0 = CLEAR\n1 = SET",
              1, old_value_t.refresh_overflow_int, new_value_t.refresh_overflow_int };
    m_bit_details_model.bits.append(entry);
    entry = { "04: clkchange_complete_int:1",
              "CAR/EMC clock-change handshake complete.\n0 = CLEAR\n1 = SET",
              1, old_value_t.clkchange_complete_int, new_value_t.clkchange_complete_int };
    m_bit_details_model.bits.append(entry);
    entry = { "05: mrr_divld_int:1",
              "LPDDR2 MRR data is available to be read.\n0 = CLEAR\n1 = SET",
              1, old_value_t.mrr_divld_int, new_value_t.mrr_divld_int };
    m_bit_details_model.bits.append(entry);
    entry = { "06: undefined_bits_6_31:26", "", 26, old_value_t.undefined_bits_6_31, new_value_t.undefined_bits_6_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Clear on 1-write. Init value is clear.\nInterrupt Status Register";
}

#define INTMASK_OFFSET 0x4
#define INTMASK_UNDEFMASK 0xFFFFFFC7
union emc_intmask_u {
    struct {
        unsigned int undefined_bits_0_2:3;
        unsigned int refresh_overflow_intmask:1;/* Mask for refresh request overflow timeout. 0 = MASKED 1 = UNMASKED */
        unsigned int clkchange_complete_intmask:1;/* Mask for CAR/EMC clock-change handshake complete. 0 = MASKED 1 = UNMASKED */
        unsigned int mrr_divld_intmask:1;   /* Mask for MRR data available. 0 = MASKED 1 = UNMASKED */
        unsigned int undefined_bits_6_31:26;
    };

    u_int32_t reg32;
};

void EmcDev::fill_intmask_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const emc_intmask_u old_value_t = { .reg32 = value };
    const emc_intmask_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_2:3", "", 3, old_value_t.undefined_bits_0_2, new_value_t.undefined_bits_0_2 };
    m_bit_details_model.bits.append(entry);
    entry = { "03: refresh_overflow_intmask:1",
              "Mask for refresh request overflow timeout.\n0 = MASKED\n1 = UNMASKED",
              1, old_value_t.refresh_overflow_intmask, new_value_t.refresh_overflow_intmask };
    m_bit_details_model.bits.append(entry);
    entry = { "04: clkchange_complete_intmask:1",
              "Mask for CAR/EMC clock-change handshake complete.\n0 = MASKED\n1 = UNMASKED",
              1, old_value_t.clkchange_complete_intmask, new_value_t.clkchange_complete_intmask };
    m_bit_details_model.bits.append(entry);
    entry = { "05: mrr_divld_intmask:1",
              "Mask for MRR data available.\n0 = MASKED\n1 = UNMASKED",
              1, old_value_t.mrr_divld_intmask, new_value_t.mrr_divld_intmask };
    m_bit_details_model.bits.append(entry);
    entry = { "06: undefined_bits_6_31:26", "", 26, old_value_t.undefined_bits_6_31, new_value_t.undefined_bits_6_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Init value is masked.\nInterrupt Mask Register";
}

#define DBG_OFFSET 0x8
#define DBG_UNDEFMASK 0xFEFFF9C8
union dbg_u {
    struct {
        unsigned int read_mux:1;            /* controls whether reads to the configuration registers are done from the assembly or active state. 0 = ACTIVE 1 = ASSEMBLY */
        unsigned int write_mux:1;           /* controls whether writes to the configuration registers are done from the assembly or active state. 0 = ASSEMBLY 1 = ACTIVE */
        unsigned int force_update:1;        /* causes the active state to get updated with the assembly state immediately upon writing the TIMING_CONTROL register. 0 = DISABLED 1 = ENABLED */
        unsigned int undefined_bit_3:1;
        unsigned int mrs_wait:1;            /* should be set to MRS_256 when a non-mobile DRAM is used because they require a 200 cycle delay between the DLL reset and any read commands. 0 = MRS_2 1 = MRS_256 */
        unsigned int periodic_qrst:1;       /* specifies whether or not to periodic reset the FBIO read-data fifo during normal operation. The periodic resets can be used for graceful recovery from an intermittent failure condition; only the initial reset is absolutely required. 0 = DISABLED 1 = ENABLED */
        unsigned int undefined_bits_6_8:3;
        unsigned int read_dqm_ctrl:1;       /* controls whether the dqm signals during reads are managed for power (not relevant for DDR). If set to MANAGED, EMC only turns them on when necessary. If set to ALWAYS_ON, the dqm signals are enabled during non-write operation. 0 = MANAGED 1 = ALWAYS_ON */
        unsigned int ap_req_busy_ctrl:1;    /* determines whether the busy signal from the auto-precharge cancellation (APC) fifo is allowed to stall requests to the EMC. 0 = DISABLED 1 = ENABLED */
        unsigned int undefined_bits_11_23:13;
        unsigned int cfg_priority:1;        /* determines the priority of cfg accesses to the DRAM. Setting this register to ENABLED gives DRAM config cycles (refresh, mrs, emrs, etc.) higher priority over real time requestors. The DISABLED setting gives the real time requestors higher priority than DRAM config cycles. Do not program to DISABLED unless for debugging. 0 = DISABLED 1 = ENABLED */
        unsigned int undefined_bits_25_31:7;
    };

    u_int32_t reg32;
};

void EmcDev::fill_dbg_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const dbg_u old_value_t = { .reg32 = value };
    const dbg_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: read_mux:1",
              "controls whether reads to the configuration registers are done from the assembly or active state.\n0 = ACTIVE\n1 = ASSEMBLY",
              1, old_value_t.read_mux, new_value_t.read_mux };
    m_bit_details_model.bits.append(entry);
    entry = { "01: write_mux:1",
              "controls whether writes to the configuration registers are done from the assembly or active state.\n0 = ASSEMBLY\n1 = ACTIVE",
              1, old_value_t.write_mux, new_value_t.write_mux };
    m_bit_details_model.bits.append(entry);
    entry = { "02: force_update:1",
              "causes the active state to get updated with the assembly state immediately upon writing the TIMING_CONTROL register.\n0 = DISABLED\n1 = ENABLED",
              1, old_value_t.force_update, new_value_t.force_update };
    m_bit_details_model.bits.append(entry);
    entry = { "03: undefined_bit_3:1", "", 1, old_value_t.undefined_bit_3, new_value_t.undefined_bit_3 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: mrs_wait:1",
              "should be set to MRS_256 when a non-mobile DRAM is used because they require a 200 cycle delay between the DLL reset and any read commands.\n0 = MRS_2\n1 = MRS_256",
              1, old_value_t.mrs_wait, new_value_t.mrs_wait };
    m_bit_details_model.bits.append(entry);
    entry = { "05: periodic_qrst:1",
              "specifies whether or not to periodic reset the FBIO read-data fifo during normal operation. The periodic resets can be used for graceful recovery from an intermittent failure condition; only the initial reset is absolutely required.\n0 = DISABLED\n1 = ENABLED",
              1, old_value_t.periodic_qrst, new_value_t.periodic_qrst };
    m_bit_details_model.bits.append(entry);
    entry = { "06: undefined_bits_6_8:3", "", 3, old_value_t.undefined_bits_6_8, new_value_t.undefined_bits_6_8 };
    m_bit_details_model.bits.append(entry);
    entry = { "09: read_dqm_ctrl:1",
              "controls whether the dqm signals during reads are managed for power (not relevant for DDR). If set to MANAGED, EMC only turns them on when necessary. If set to ALWAYS_ON, the dqm signals are enabled during non-write operation.\n0 = MANAGED\n1 = ALWAYS_ON",
              1, old_value_t.read_dqm_ctrl, new_value_t.read_dqm_ctrl };
    m_bit_details_model.bits.append(entry);
    entry = { "10: ap_req_busy_ctrl:1",
              "determines whether the busy signal from the auto-precharge cancellation (APC) fifo is allowed to stall requests to the EMC.\n0 = DISABLED\n1 = ENABLED",
              1, old_value_t.ap_req_busy_ctrl, new_value_t.ap_req_busy_ctrl };
    m_bit_details_model.bits.append(entry);
    entry = { "11: undefined_bits_11_23:13", "", 13, old_value_t.undefined_bits_11_23, new_value_t.undefined_bits_11_23 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: cfg_priority:1",
              "determines the priority of cfg accesses to the DRAM. Setting this register to ENABLED gives DRAM config cycles (refresh, mrs, emrs, etc.) higher priority over real time requestors. The DISABLED setting gives the real time requestors higher priority than DRAM config cycles. Do not program to DISABLED unless for debugging.\n0 = DISABLED\n1 = ENABLED",
              1, old_value_t.cfg_priority, new_value_t.cfg_priority };
    m_bit_details_model.bits.append(entry);
    entry = { "25: undefined_bits_25_31:7", "", 7, old_value_t.undefined_bits_25_31, new_value_t.undefined_bits_25_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "The DBG register is used to reconfigure the EMC during debug or chip testing.\nBoot requirements\n    * This register should be parameterized in the BCT and written by the BootROM during coldboot.\n    * This register should be saved in the scratch registers and restored by the BootROM during warmboot.\nDebug Register";
}

#define CFG_OFFSET 0xC
#define CFG_UNDEFMASK 0x1CFE00FE
union emc_cfg_u {
    struct {
        unsigned int pre_idle_en:1;         /* preemptively closes all of the banks after the EMC has been idle for PRE_IDLE_CYCLES cycles and there are banks open. PRE_IDLE_EN can be enabled if violating tRAS max is an issue; 0 = DISABLE; 1 = ENABLE */
        unsigned int undefined_bits_1_7:7;
        unsigned int pre_idle_cycles:8;     /* cycles after which an idle bank may be closed. Note that 0 is an illegal setting for PRE_IDLE_CYCLES */
        unsigned int clear_ap_prev_spreq:1; /* used to try to clear the auto-precharge bit on the previous request if the next request is on the same page.  The previous request has to be in reach for this to happen. */
        unsigned int undefined_bits_17_23:7;
        unsigned int auto_pre_rd:1;         /* enable auto-precharge in the EMC for reads. This bits, when set to DISABLE, will override the settings in the MC register. Otherwise, they permit clients to make auto-precharge requests as specified by the Memory Controller. */
        unsigned int auto_pre_wr:1;         /* enable auto-precharge in the EMC for writes. This bits, when set to DISABLE, will override the settings in the MC register. Otherwise, they permit clients to make auto-precharge requests as specified by the Memory Controller. */
        unsigned int undefined_bits_26_28:3;
        unsigned int dram_acpd:1;           /* allows the DRAM controller to perform opportunistic active powerdown control using the CKE pin on the DRAM. The behavior of the powerdown control logic is controlled by the PDEX2* and *2PDEN registers. The value of DRAM_ACPD should only be changed when CKE is low, e.g., during software-controlled self-refresh or before DRAM initialization. If enabling ACPD, you should ALWAYS enable DRAM_CLKSTOP_PDSR_ONLY. Not doing so will result in sub-optimal power-down & clockstop performance. The powerdown conditions are met within a couple of cycles after the clock has stopped, so the clock must be restarted & minimum clock timings met before powerdown can be issued and clock restopped; 0 = NO_POWERDOWN; 1 = ACTIVE_POWERDOWN */
        unsigned int dram_clkstop_pdsr_only:1;/* clockstop (if enabled) only allowed to happen if CKE=0 (for all CKE bits associated w/ clock) 0 = DISABLED 1 = ENABLED */
        unsigned int dram_clkstop:1;        /* allows the DRAM controller to turn off the clock to the DRAM when it is safe to do so (no operations are ongoing, and tRFC, tMRS, tRP, etc. have all been satisfied; 0 = DISABLE; 1 = ENABLE */
    };

    u_int32_t reg32;
};

void EmcDev::fill_cfg_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const emc_cfg_u old_value_t = { .reg32 = value };
    const emc_cfg_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: pre_idle_en:1",
              "preemptively closes all of the banks after the EMC has been idle for PRE_IDLE_CYCLES cycles and there are banks open. PRE_IDLE_EN can be enabled if violating tRAS max is an issue;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.pre_idle_en, new_value_t.pre_idle_en };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_7:7", "", 7, old_value_t.undefined_bits_1_7, new_value_t.undefined_bits_1_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: pre_idle_cycles:8",
              "cycles after which an idle bank may be closed. Note that 0 is an illegal setting for PRE_IDLE_CYCLES",
              8, old_value_t.pre_idle_cycles, new_value_t.pre_idle_cycles };
    m_bit_details_model.bits.append(entry);
    entry = { "16: clear_ap_prev_spreq:1",
              "used to try to clear the auto-precharge bit on the previous request if the next request is on the same page.  The previous request has to be in reach for this to happen.",
              1, old_value_t.clear_ap_prev_spreq, new_value_t.clear_ap_prev_spreq };
    m_bit_details_model.bits.append(entry);
    entry = { "17: undefined_bits_17_23:7", "", 7, old_value_t.undefined_bits_17_23, new_value_t.undefined_bits_17_23 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: auto_pre_rd:1",
              "enable auto-precharge in the EMC for reads. This bits, when set to DISABLE, will override the settings in the MC register. Otherwise, they permit clients to make auto-precharge requests as specified by the Memory Controller.",
              1, old_value_t.auto_pre_rd, new_value_t.auto_pre_rd };
    m_bit_details_model.bits.append(entry);
    entry = { "25: auto_pre_wr:1",
              "enable auto-precharge in the EMC for writes. This bits, when set to DISABLE, will override the settings in the MC register. Otherwise, they permit clients to make auto-precharge requests as specified by the Memory Controller.",
              1, old_value_t.auto_pre_wr, new_value_t.auto_pre_wr };
    m_bit_details_model.bits.append(entry);
    entry = { "26: undefined_bits_26_28:3", "", 3, old_value_t.undefined_bits_26_28, new_value_t.undefined_bits_26_28 };
    m_bit_details_model.bits.append(entry);
    entry = { "29: dram_acpd:1",
              "allows the DRAM controller to perform opportunistic active powerdown control using the CKE pin on the DRAM. The behavior of the powerdown control logic is controlled by the PDEX2* and *2PDEN registers. The value of DRAM_ACPD should only be changed when CKE is low, e.g., during software-controlled self-refresh or before DRAM initialization. If enabling ACPD, you should ALWAYS enable DRAM_CLKSTOP_PDSR_ONLY. Not doing so will result in sub-optimal power-down & clockstop performance. The powerdown conditions are met within a couple of cycles after the clock has stopped, so the clock must be restarted & minimum clock timings met before powerdown can be issued and clock restopped;\n0 = NO_POWERDOWN;\n1 = ACTIVE_POWERDOWN",
              1, old_value_t.dram_acpd, new_value_t.dram_acpd };
    m_bit_details_model.bits.append(entry);
    entry = { "30: dram_clkstop_pdsr_only:1",
              "clockstop (if enabled) only allowed to happen if CKE=0 (for all CKE bits associated w/ clock)\n0 = DISABLED\n1 = ENABLED",
              1, old_value_t.dram_clkstop_pdsr_only, new_value_t.dram_clkstop_pdsr_only };
    m_bit_details_model.bits.append(entry);
    entry = { "31: dram_clkstop:1",
              "allows the DRAM controller to turn off the clock to the DRAM when it is safe to do so (no operations are ongoing, and tRFC, tMRS, tRP, etc. have all been satisfied;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.dram_clkstop, new_value_t.dram_clkstop };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "The CFG register is used to configure the external memory interface.\n Boot requirements\n    * This register should be parameterized in the BCT and written by the BootROM during coldboot\n    * This register should be saved in the scratch registers and restored by the BootROM during warmboot.\nConfiguration Register";
}

#define ADR_CFG_OFFSET 0x10
#define ADR_CFG_UNDEFMASK 0xFCF0FCF8
union adr_cfg_u {
    struct {
        unsigned int emem_colwidth:3;       /* width of column address of the attached SDRAM device; 0 = column width equals 7; 1 = column width equals 8; 2 = column width equals 9; 3 = column width equals 10; 4 = column width equals 11 */
        unsigned int undefined_bits_3_7:5;
        unsigned int emem_bankwidth:2;      /* width of bank address of the attached SDRAM device; 1 = device internal bank equals 2; 2 = device internal bank equals 4; 3 = device internal bank equals 8 */
        unsigned int undefined_bits_10_15:6;
        unsigned int emem_devsize:4;        /* size of the attached SDRAM device used to generate width of row address; 0 = D4 MB; 1 = D8 MB; 2 = D16 MB; 3 = D32 MB; 4 = D64 MB; 5 = D128 MB; 6 = D256 MB; 7 = D512 MB; 8 = D1024MB; 8 = D1GB */
        unsigned int undefined_bits_20_23:4;
        unsigned int emem_numdev:2;         /* : the number of attached devices. If more than one device is attached, the DEVSIZE, COLWIDTH, and BANKWIDTH configurations for the second device will be defined by the fields in ADR_CFG_1, while the fields in ADR_CFG will only apply to the first device; 0 = N1 (Number of Devices equals 1); 1 = N2 (Number of Devices equals 2) */
        unsigned int undefined_bits_26_31:6;
    };

    u_int32_t reg32;
};

void EmcDev::fill_adr_cfg_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const adr_cfg_u old_value_t = { .reg32 = value };
    const adr_cfg_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: emem_colwidth:3",
              "width of column address of the attached SDRAM device;\n0 = column width equals 7;\n1 = column width equals 8;\n2 = column width equals 9;\n3 = column width equals 10;\n4 = column width equals 11",
              3, old_value_t.emem_colwidth, new_value_t.emem_colwidth };
    m_bit_details_model.bits.append(entry);
    entry = { "03: undefined_bits_3_7:5", "", 5, old_value_t.undefined_bits_3_7, new_value_t.undefined_bits_3_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: emem_bankwidth:2",
              "width of bank address of the attached SDRAM device;\n1 = device internal bank equals 2;\n2 = device internal bank equals 4;\n3 = device internal bank equals 8",
              2, old_value_t.emem_bankwidth, new_value_t.emem_bankwidth };
    m_bit_details_model.bits.append(entry);
    entry = { "10: undefined_bits_10_15:6", "", 6, old_value_t.undefined_bits_10_15, new_value_t.undefined_bits_10_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: emem_devsize:4",
              "size of the attached SDRAM device used to generate width of row address;\n0 = D4 MB;\n1 = D8 MB;\n2 = D16 MB;\n3 = D32 MB;\n4 = D64 MB;\n5 = D128 MB;\n6 = D256 MB;\n7 = D512 MB;\n8 = D1024MB;\n8 = D1GB",
              4, old_value_t.emem_devsize, new_value_t.emem_devsize };
    m_bit_details_model.bits.append(entry);
    entry = { "20: undefined_bits_20_23:4", "", 4, old_value_t.undefined_bits_20_23, new_value_t.undefined_bits_20_23 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: emem_numdev:2",
              ": the number of attached devices. If more than one device is attached, the DEVSIZE, COLWIDTH, and BANKWIDTH configurations for the second device will be defined by the fields in ADR_CFG_1, while the fields in ADR_CFG will only apply to the first device;\n0 = N1 (Number of Devices equals 1);\n1 = N2 (Number of Devices equals 2)",
              2, old_value_t.emem_numdev, new_value_t.emem_numdev };
    m_bit_details_model.bits.append(entry);
    entry = { "26: undefined_bits_26_31:6", "", 6, old_value_t.undefined_bits_26_31, new_value_t.undefined_bits_26_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "This is used to specify the DRAM parameters. EMC will use these parameters to generate the device, row, bank, column values to the SDRAM. The ADR_CFG shadows the address configuration being used by the MC’s EMEM_ADR_CFG register. It must be programmed to the same value as the EMEM_ADR_CFG register.\nBoot requirements:\n    * This register should be parameterized in the BCT and written by the BootROM during coldboot.\n    * This register should be saved in the scratch registers and restored by the BootROM during warmboot.\nExternal Memory Address Configuration Register";
}

#define ADR_CFG_1_OFFSET 0x14
#define ADR_CFG_1_UNDEFMASK 0xFFF0FCF8
union adr_cfg_1_u {
    struct {
        unsigned int emem1_colwidth:3;      /* width of column address of the attached SDRAM device; 0 = column width equals 7; 1 = column width equals 8; 2 = column width equals 9; 3 = column width equals 10; 4 = column width equals 11 */
        unsigned int undefined_bits_3_7:5;
        unsigned int emem1_bankwidth:2;     /* width of bank address of the attached SDRAM device; 2 = device internal bank equals 4; 3 = device internal bank equals 8 */
        unsigned int undefined_bits_10_15:6;
        unsigned int emem1_devsize:4;       /* size of the attached SDRAM device used to generate width of row address; 0 = D4 MB; 1 = D8 MB; 2 = D16 MB; 3 = D32 MB; 4 = D64 MB; 5 = D128 MB; 6 = D256 MB; 7 = D512 MB; 8 = D1024MB; 8 = D1GB */
        unsigned int undefined_bits_20_31:12;
    };

    u_int32_t reg32;
};

void EmcDev::fill_adr_cfg_1_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const adr_cfg_1_u old_value_t = { .reg32 = value };
    const adr_cfg_1_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: emem1_colwidth:3",
              "width of column address of the attached SDRAM device;\n0 = column width equals 7;\n1 = column width equals 8;\n2 = column width equals 9;\n3 = column width equals 10;\n4 = column width equals 11",
              3, old_value_t.emem1_colwidth, new_value_t.emem1_colwidth };
    m_bit_details_model.bits.append(entry);
    entry = { "03: undefined_bits_3_7:5", "", 5, old_value_t.undefined_bits_3_7, new_value_t.undefined_bits_3_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: emem1_bankwidth:2",
              "width of bank address of the attached SDRAM device;\n2 = device internal bank equals 4;\n3 = device internal bank equals 8",
              2, old_value_t.emem1_bankwidth, new_value_t.emem1_bankwidth };
    m_bit_details_model.bits.append(entry);
    entry = { "10: undefined_bits_10_15:6", "", 6, old_value_t.undefined_bits_10_15, new_value_t.undefined_bits_10_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: emem1_devsize:4",
              "size of the attached SDRAM device used to generate width of row address;\n0 = D4 MB;\n1 = D8 MB;\n2 = D16 MB;\n3 = D32 MB;\n4 = D64 MB;\n5 = D128 MB;\n6 = D256 MB;\n7 = D512 MB;\n8 = D1024MB;\n8 = D1GB",
              4, old_value_t.emem1_devsize, new_value_t.emem1_devsize };
    m_bit_details_model.bits.append(entry);
    entry = { "20: undefined_bits_20_31:12", "", 12, old_value_t.undefined_bits_20_31, new_value_t.undefined_bits_20_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "This register allows for two devices with different colwidth/bankwidth to be used without creating holes in the system-level address map.\n If ADR_CFG.EMEM_NUMDEV == N2, then this register must also be programmed in addition to ADR_CFG. If the two devices are the same colwidth/bankwidth/devsize, then this can be programmed exactly the same as ADR_CFG. Otherwise, the smaller of the two devices (devsize) should be placed as Device[1] and this register should be programmed to reflect the smaller device's bankwidth, colwidth, and devsize.\n Note that due to system-level address map restrictions, more DRAM bytes may be populated in EMC than are addressable in the system.\nBoot requirements\n    * This register should be parameterized in the BCT and written by the BootROM during coldboot.\n    * This register should be saved in the scratch registers and restored by the BootROM during warmboot.\nExternal Memory Address Config Register, Device [1]";
}

#define REFCTRL_OFFSET 0x20
#define REFCTRL_UNDEFMASK 0x7FFFFFFC
union refctrl_u {
    struct {
        unsigned int device_refresh_disable:2;/* disables refresh to individual attached device (1 bit per dram chip-select) */
        unsigned int undefined_bits_2_30:29;
        unsigned int ref_valid:1;           /* enable refresh controller; 0 = DISABLE; 1 = ENABLE */
    };

    u_int32_t reg32;
};

void EmcDev::fill_refctrl_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const refctrl_u old_value_t = { .reg32 = value };
    const refctrl_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: device_refresh_disable:2",
              "disables refresh to individual attached device (1 bit per dram chip-select)",
              2, old_value_t.device_refresh_disable, new_value_t.device_refresh_disable };
    m_bit_details_model.bits.append(entry);
    entry = { "02: undefined_bits_2_30:29", "", 29, old_value_t.undefined_bits_2_30, new_value_t.undefined_bits_2_30 };
    m_bit_details_model.bits.append(entry);
    entry = { "31: ref_valid:1",
              "enable refresh controller;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ref_valid, new_value_t.ref_valid };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "The REFCTRL register allows SW to enable or disable the refresh controller. REF_VALID should be enabled after the initialization sequence is completed.\nBoot requirements\n    * If per-device DPD is used, the DEVICE_REFRESH_DISABLE field should be parameterized in the BCT and written by the BootROM during coldboot.\n    * If per-device DPD is used, the DEVICE_REFRESH_DISABLE field should be parameterized the scratch registers registers and restored by the BootROM during warmboot.\n    * REF_VALID field should always be set to ENABLED for normal use, no need to parameterize in BCT/scratch.\nRefresh Control Register";
}

#define PIN_OFFSET 0x24
#define PIN_UNDEFMASK 0xFFFFFFEE
union pin_u {
    struct {
        unsigned int pin_cke:1;             /* selects the level of the CKE pin. This can be used to place the DRAM in power down state. PIN_CKE value is applied all CKE pins; 0 = POWERDOWN; 1 = NORMAL */
        unsigned int undefined_bits_1_3:3;
        unsigned int pin_dqm:1;             /* is used to always mask DRAM writes. This pin should only be used for initialization. Certain DRAM vendors (e.g., Samsung), require the DQM to be high during initialization. The register value should be set to NORMAL after the initialization sequence; 0 = NORMAL; 1 = INACTIVE */
        unsigned int undefined_bits_5_31:27;
    };

    u_int32_t reg32;
};

void EmcDev::fill_pin_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const pin_u old_value_t = { .reg32 = value };
    const pin_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: pin_cke:1",
              "selects the level of the CKE pin. This can be used to place the DRAM in power down state. PIN_CKE value is applied all CKE pins;\n0 = POWERDOWN;\n1 = NORMAL",
              1, old_value_t.pin_cke, new_value_t.pin_cke };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_3:3", "", 3, old_value_t.undefined_bits_1_3, new_value_t.undefined_bits_1_3 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: pin_dqm:1",
              "is used to always mask DRAM writes. This pin should only be used for initialization. Certain DRAM vendors (e.g., Samsung), require the DQM to be high during initialization. The register value should be set to NORMAL after the initialization sequence;\n0 = NORMAL;\n1 = INACTIVE",
              1, old_value_t.pin_dqm, new_value_t.pin_dqm };
    m_bit_details_model.bits.append(entry);
    entry = { "05: undefined_bits_5_31:27", "", 27, old_value_t.undefined_bits_5_31, new_value_t.undefined_bits_5_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "The PIN register allows SW to control the state of the selected external DRAM pins.\nBoot requirements\n    * Both fields in this register should be set to NORMAL during coldboot.\n    * Both fields in this register should be set to NORMAL during warmboot.\nControls state of selected DRAM pins";
}

#define TIMING_CONTROL_OFFSET 0x28
#define TIMING_CONTROL_UNDEFMASK 0xFFFFFFFE
union timing_control_u {
    struct {
        unsigned int timing_update:1;
        unsigned int undefined_bits_1_31:31;
    };

    u_int32_t reg32;
};

void EmcDev::fill_timing_control_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const timing_control_u old_value_t = { .reg32 = value };
    const timing_control_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: timing_update:1", "", 1, old_value_t.timing_update, new_value_t.timing_update };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_31:31", "", 31, old_value_t.undefined_bits_1_31, new_value_t.undefined_bits_1_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "The TIMING_CONTROL register is used by SW to trigger parameter updates for timing parameter registers, rdqs/quse delay controls, and some DLL controls. Writing the TIMING_UPDATE field updates the active state of these registers with the programmed assembly state. The active state is updated during a safe interval determined by the EMC. If CLKCHANGE_REQ_ENABLE is enabled, the active value will automatically be updated on completion of the clock change.\nBoot requirements: Writing this register with 0x1 will trigger a timing update event, which should be used in both warmboot and coldboot sequences. .";
}

#define RC_OFFSET 0x2C
#define RC_UNDEFMASK 0xFFFFFFC0
union rc_u {
    struct {
        unsigned int rc:6;                  /* specifies the row cycle time. This is the minimum number of cycles between activate commands to the same bank. LPDDR2: ceil((tRASmin+tRPpb)/tCK) DDR2: ceil(tRC/tCK) */
        unsigned int undefined_bits_6_31:26;
    };

    u_int32_t reg32;
};

void EmcDev::fill_rc_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const rc_u old_value_t = { .reg32 = value };
    const rc_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: rc:6",
              "specifies the row cycle time. This is the minimum number of cycles between activate commands to the same bank. LPDDR2: ceil((tRASmin+tRPpb)/tCK) DDR2: ceil(tRC/tCK)",
              6, old_value_t.rc, new_value_t.rc };
    m_bit_details_model.bits.append(entry);
    entry = { "06: undefined_bits_6_31:26", "", 26, old_value_t.undefined_bits_6_31, new_value_t.undefined_bits_6_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "This register is shadowed.\nBoot requirements\n    * This register should be parameterized in the BCT and written by the BootROM during coldboot.\n    * This register should be saved in the scratch registers and restored by the BootROM during warmboot.\nDRAM Timing Parameter";
}

#define RFC_OFFSET 0x30
#define RFC_UNDEFMASK 0xFFFFFE00
union rfc_u {
    struct {
        unsigned int rfc:9;                 /* specifies the auto refresh cycle time. This is the minimum number of cycles between an auto refresh command and a subsequent auto refresh or activate command. LPDDR2: ceil(tRFCab/tCK)  DDR2  : ceil(tRFC/tCK) */
        unsigned int undefined_bits_9_31:23;
    };

    u_int32_t reg32;
};

void EmcDev::fill_rfc_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const rfc_u old_value_t = { .reg32 = value };
    const rfc_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: rfc:9",
              "specifies the auto refresh cycle time. This is the minimum number of cycles between an auto refresh command and a subsequent auto refresh or activate command. LPDDR2: ceil(tRFCab/tCK)  DDR2  : ceil(tRFC/tCK)",
              9, old_value_t.rfc, new_value_t.rfc };
    m_bit_details_model.bits.append(entry);
    entry = { "09: undefined_bits_9_31:23", "", 23, old_value_t.undefined_bits_9_31, new_value_t.undefined_bits_9_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "This register is shadowed.\nBoot requirements\n    * This register should be parameterized in the BCT and written by the BootROM during coldboot.\n    * This register should be saved in the scratch registers and restored by the BootROM during warmboot.\nDRAM Timing Parameter";
}

#define RAS_OFFSET 0x34
#define RAS_UNDEFMASK 0xFFFFFFC0
union ras_u {
    struct {
        unsigned int ras:6;                 /* specifies the row active time. This is the minimum number of cycles between an activate command and a precharge command to the same bank. LPDDR2: ceil(tRASmin/tCK); min = 3  DDR2  : ceil(tRASmin/tCK) */
        unsigned int undefined_bits_6_31:26;
    };

    u_int32_t reg32;
};

void EmcDev::fill_ras_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const ras_u old_value_t = { .reg32 = value };
    const ras_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: ras:6",
              "specifies the row active time. This is the minimum number of cycles between an activate command and a precharge command to the same bank. LPDDR2: ceil(tRASmin/tCK); min = 3  DDR2  : ceil(tRASmin/tCK)",
              6, old_value_t.ras, new_value_t.ras };
    m_bit_details_model.bits.append(entry);
    entry = { "06: undefined_bits_6_31:26", "", 26, old_value_t.undefined_bits_6_31, new_value_t.undefined_bits_6_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "This register is shadowed.\nBoot requirements\n    * This register should be parameterized in the BCT and written by the BootROM during coldboot.\n    * This register should be saved in the scratch registers and restored by the BootROM during warmboot.\nDRAM Timing Parameter";
}

#define RP_OFFSET 0x38
#define RP_UNDEFMASK 0xFFFFFFC0
union rp_u {
    struct {
        unsigned int rp:6;                  /* specifies the row precharge time. This is the minimum number of cycles between a precharge command and an activate command to the same bank. LPDDR2: ceil(tRPpb/tCK); min = 3  DDR2  : ceil(tRP/tCK) */
        unsigned int undefined_bits_6_31:26;
    };

    u_int32_t reg32;
};

void EmcDev::fill_rp_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const rp_u old_value_t = { .reg32 = value };
    const rp_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: rp:6",
              "specifies the row precharge time. This is the minimum number of cycles between a precharge command and an activate command to the same bank. LPDDR2: ceil(tRPpb/tCK); min = 3  DDR2  : ceil(tRP/tCK)",
              6, old_value_t.rp, new_value_t.rp };
    m_bit_details_model.bits.append(entry);
    entry = { "06: undefined_bits_6_31:26", "", 26, old_value_t.undefined_bits_6_31, new_value_t.undefined_bits_6_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "This register is shadowed.\nBoot requirements\n    * This register should be parameterized in the BCT and written by the BootROM during coldboot.\n    * This register should be saved in the scratch registers and restored by the BootROM during warmboot.\nDRAM Timing Parameter";
}

#define R2W_OFFSET 0x3C
#define R2W_UNDEFMASK 0xFFFFFFE0
union r2w_u {
    struct {
        unsigned int r2w:5;                 /* specifies the minimum number of cycles from any read command to any write command, irrespective of bank. This parameter guarantees the read->write turn-around time on the bus. Largest programming value is 29 LPDDR2: ceilRL + ceil(tDQSCKmax/tCK) + 2 - WL  DDR2 w/o ODT: 4 DDR2 w/  ODT: 5 */
        unsigned int undefined_bits_5_31:27;
    };

    u_int32_t reg32;
};

void EmcDev::fill_r2w_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const r2w_u old_value_t = { .reg32 = value };
    const r2w_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: r2w:5",
              "specifies the minimum number of cycles from any read command to any write command, irrespective of bank. This parameter guarantees the read->write turn-around time on the bus. Largest programming value is 29 LPDDR2: ceilRL + ceil(tDQSCKmax/tCK) + 2 - WL  DDR2 w/o ODT: 4 DDR2 w/  ODT: 5",
              5, old_value_t.r2w, new_value_t.r2w };
    m_bit_details_model.bits.append(entry);
    entry = { "05: undefined_bits_5_31:27", "", 27, old_value_t.undefined_bits_5_31, new_value_t.undefined_bits_5_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "This register is shadowed.\nBoot requirements\n    * This register should be parameterized in the BCT and written by the BootROM during coldboot.\n    *  This register should be saved in the scratch registers and restored by the BootROM during warmboot.\nDRAM Timing Parameter";
}

#define W2R_OFFSET 0x40
#define W2R_UNDEFMASK 0xFFFFFFE0
union w2r_u {
    struct {
        unsigned int w2r:5;                 /* specifies the minimum number of cycles from a write command to a read command, irrespective of bank. Largest programming value is 29 LPDDR2/DDR2: 2 + max(2, ceil(tWTR/tCK)) */
        unsigned int undefined_bits_5_31:27;
    };

    u_int32_t reg32;
};

void EmcDev::fill_w2r_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const w2r_u old_value_t = { .reg32 = value };
    const w2r_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: w2r:5",
              "specifies the minimum number of cycles from a write command to a read command, irrespective of bank. Largest programming value is 29 LPDDR2/DDR2: 2 + max(2, ceil(tWTR/tCK))",
              5, old_value_t.w2r, new_value_t.w2r };
    m_bit_details_model.bits.append(entry);
    entry = { "05: undefined_bits_5_31:27", "", 27, old_value_t.undefined_bits_5_31, new_value_t.undefined_bits_5_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "This register is shadowed.\nBoot requirements\n    * This register should be parameterized in the BCT and written by the BootROM during coldboot.\n    * This register should be saved in the scratch registers and restored by the BootROM during warmboot.\nDRAM Timing Parameter";
}

#define R2P_OFFSET 0x44
#define R2P_UNDEFMASK 0xFFFFFFE0
union r2p_u {
    struct {
        unsigned int r2p:5;                 /* specifies the minimum number of cycles from a read command to a precharge command for the same bank. LPDDR2: ceil(tRTP/tCK); min = 2; add 1 if LPDDR2-S2  DDR2: ceil(tRTP/tCK) */
        unsigned int undefined_bits_5_31:27;
    };

    u_int32_t reg32;
};

void EmcDev::fill_r2p_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const r2p_u old_value_t = { .reg32 = value };
    const r2p_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: r2p:5",
              "specifies the minimum number of cycles from a read command to a precharge command for the same bank. LPDDR2: ceil(tRTP/tCK); min = 2; add 1 if LPDDR2-S2  DDR2: ceil(tRTP/tCK)",
              5, old_value_t.r2p, new_value_t.r2p };
    m_bit_details_model.bits.append(entry);
    entry = { "05: undefined_bits_5_31:27", "", 27, old_value_t.undefined_bits_5_31, new_value_t.undefined_bits_5_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "This register is shadowed.\nBoot requirements\n    * This register should be parameterized in the BCT and written by the BootROM during coldboot.\n    * This register should be saved in the scratch registers and restored by the BootROM during warmboot.\nDRAM Timing Parameter";
}

#define W2P_OFFSET 0x48
#define W2P_UNDEFMASK 0xFFFFFFE0
union w2p_u {
    struct {
        unsigned int w2p:5;                 /* specifies the minimum number of cycles from a write command to a precharge command for the same bank.  LPDDR2: ceilWL + 2 + max(3, ceil(tWR/tCK))  DDR2: WL + 1 + max(2, ceil(tWR/tCK)) */
        unsigned int undefined_bits_5_31:27;
    };

    u_int32_t reg32;
};

void EmcDev::fill_w2p_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const w2p_u old_value_t = { .reg32 = value };
    const w2p_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: w2p:5",
              "specifies the minimum number of cycles from a write command to a precharge command for the same bank.  LPDDR2: ceilWL + 2 + max(3, ceil(tWR/tCK))  DDR2: WL + 1 + max(2, ceil(tWR/tCK))",
              5, old_value_t.w2p, new_value_t.w2p };
    m_bit_details_model.bits.append(entry);
    entry = { "05: undefined_bits_5_31:27", "", 27, old_value_t.undefined_bits_5_31, new_value_t.undefined_bits_5_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "This register is shadowed.\nBoot requirements\n    * This register should be parameterized in the BCT and written by the BootROM during coldboot.\n    * This register should be saved in the scratch registers and restored by the BootROM during warmboot.\nDRAM Timing Parameter";
}

#define RD_RCD_OFFSET 0x4C
#define RD_RCD_UNDEFMASK 0xFFFFFFC0
union rd_rcd_u {
    struct {
        unsigned int rd_rcd:6;              /* specifies the RAS to CAS delay. RD_RCD is the minimum number of cycles between an activate command and a read command to the same bank. LPDDR2: ceil(tRCD/tCK); min = 3  DDR2: ceil(tRCD/tCK) */
        unsigned int undefined_bits_6_31:26;
    };

    u_int32_t reg32;
};

void EmcDev::fill_rd_rcd_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const rd_rcd_u old_value_t = { .reg32 = value };
    const rd_rcd_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: rd_rcd:6",
              "specifies the RAS to CAS delay. RD_RCD is the minimum number of cycles between an activate command and a read command to the same bank. LPDDR2: ceil(tRCD/tCK); min = 3  DDR2: ceil(tRCD/tCK)",
              6, old_value_t.rd_rcd, new_value_t.rd_rcd };
    m_bit_details_model.bits.append(entry);
    entry = { "06: undefined_bits_6_31:26", "", 26, old_value_t.undefined_bits_6_31, new_value_t.undefined_bits_6_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "This register is shadowed.\nBoot requirements\n    * This register should be parameterized in the BCT and written by the BootROM during coldboot.\n    * This register should be saved in the scratch registers and restored by the BootROM during warmboot.\nDRAM Timing Parameter";
}

#define WR_RCD_OFFSET 0x50
#define WR_RCD_UNDEFMASK 0xFFFFFFC0
union wr_rcd_u {
    struct {
        unsigned int wr_rcd:6;              /* minimum number of cycles between an activate command and a write command to the same bank. LPDDR2: ceilceil(tRCD/tCK); min = 3  DDR2: ceil(tRCD/tCK) */
        unsigned int undefined_bits_6_31:26;
    };

    u_int32_t reg32;
};

void EmcDev::fill_wr_rcd_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const wr_rcd_u old_value_t = { .reg32 = value };
    const wr_rcd_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: wr_rcd:6",
              "minimum number of cycles between an activate command and a write command to the same bank. LPDDR2: ceilceil(tRCD/tCK); min = 3  DDR2: ceil(tRCD/tCK)",
              6, old_value_t.wr_rcd, new_value_t.wr_rcd };
    m_bit_details_model.bits.append(entry);
    entry = { "06: undefined_bits_6_31:26", "", 26, old_value_t.undefined_bits_6_31, new_value_t.undefined_bits_6_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "DRAM Timing Parameter\n This register is shadowed.\nBoot requirements\n    * This register should be parameterized in the BCT and written by the BootROM during coldboot.\n    * This register should be saved in the scratch registers and restored by the BootROM during warmboot.";
}

#define RRD_OFFSET 0x54
#define RRD_UNDEFMASK 0xFFFFFFF0
union rrd_u {
    struct {
        unsigned int rrd:4;                 /* specifies the Bank X Act to Bank Y Act command delay. LPDDR2: ceilceil(tRRD/tCK); min = 2  DDR2: ceil(tRRD/tCK) */
        unsigned int undefined_bits_4_31:28;
    };

    u_int32_t reg32;
};

void EmcDev::fill_rrd_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const rrd_u old_value_t = { .reg32 = value };
    const rrd_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: rrd:4",
              "specifies the Bank X Act to Bank Y Act command delay. LPDDR2: ceilceil(tRRD/tCK); min = 2  DDR2: ceil(tRRD/tCK)",
              4, old_value_t.rrd, new_value_t.rrd };
    m_bit_details_model.bits.append(entry);
    entry = { "04: undefined_bits_4_31:28", "", 28, old_value_t.undefined_bits_4_31, new_value_t.undefined_bits_4_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "This register is shadowed.\nBoot requirements\n    * This register should be parameterized in the BCT and written by the BootROM during coldboot.\n    * This register should be saved in the scratch registers and restored by the BootROM during warmboot.\nDRAM Timing Parameter";
}

#define REXT_OFFSET 0x58
#define REXT_UNDEFMASK 0xFFFFFFF0
union rext_u {
    struct {
        unsigned int rext:4;                /* specifies the read to read delay for reads when multiple physical devices are present. LPDDR2:      if (tCK >= 6) REXT = 2      else if (tCK >= 2) REXT = 3      else REXT = 4 DDR2:  1 */
        unsigned int undefined_bits_4_31:28;
    };

    u_int32_t reg32;
};

void EmcDev::fill_rext_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const rext_u old_value_t = { .reg32 = value };
    const rext_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: rext:4",
              "specifies the read to read delay for reads when multiple physical devices are present. LPDDR2:      if (tCK >= 6) REXT = 2      else if (tCK >= 2) REXT = 3      else REXT = 4 DDR2:  1",
              4, old_value_t.rext, new_value_t.rext };
    m_bit_details_model.bits.append(entry);
    entry = { "04: undefined_bits_4_31:28", "", 28, old_value_t.undefined_bits_4_31, new_value_t.undefined_bits_4_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "This register is shadowed.\nBoot requirements\n    * This register should be parameterized in the BCT and written by the BootROM during coldboot.\n    * This register should be saved in the scratch registers and restored by the BootROM during warmboot.\nDRAM Timing Parameter";
}

#define WDV_OFFSET 0x5C
#define WDV_UNDEFMASK 0xFFFFFFF0
union wdv_u {
    struct {
        unsigned int wdv:4;                 /* the number of cycles to post (delay) write data from being asserted to the rams. 15 = MAX LPDDR2: WL   DDR2: WL - 1 */
        unsigned int undefined_bits_4_31:28;
    };

    u_int32_t reg32;
};

void EmcDev::fill_wdv_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const wdv_u old_value_t = { .reg32 = value };
    const wdv_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: wdv:4",
              "the number of cycles to post (delay) write data from being asserted to the rams.\n15 = MAX LPDDR2: WL   DDR2: WL - 1",
              4, old_value_t.wdv, new_value_t.wdv };
    m_bit_details_model.bits.append(entry);
    entry = { "04: undefined_bits_4_31:28", "", 28, old_value_t.undefined_bits_4_31, new_value_t.undefined_bits_4_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "This register is shadowed.\nBoot requirements\n    * This register should be parameterized in the BCT and written by the BootROM during coldboot.\n    * This register should be saved in the scratch registers and restored by the BootROM during warmboot.\nDRAM Timing Parameter";
}

#define QUSE_OFFSET 0x60
#define QUSE_UNDEFMASK 0xFFFFFFF0
union quse_u {
    struct {
        unsigned int quse:4;                /* tells the chip when to look for read return data.  LPDDR2/DDR2: obtained from characterization */
        unsigned int undefined_bits_4_31:28;
    };

    u_int32_t reg32;
};

void EmcDev::fill_quse_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const quse_u old_value_t = { .reg32 = value };
    const quse_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: quse:4",
              "tells the chip when to look for read return data.  LPDDR2/DDR2: obtained from characterization",
              4, old_value_t.quse, new_value_t.quse };
    m_bit_details_model.bits.append(entry);
    entry = { "04: undefined_bits_4_31:28", "", 28, old_value_t.undefined_bits_4_31, new_value_t.undefined_bits_4_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "The QRST, QUSE, RDV registers specify the delays from read to internal timing signals. These fields should be set as follows:\nBecause DRAM uses a tristating clock (the DQS) a method is needed to deal with the ambiguity of when DQS is tristate. Only one such method is supported: QUSE.\n This register is shadowed.\nBoot requirements\n    * This register should be parameterized in the BCT and written by the BootROM during coldboot.\n    * This register should be saved in the scratch registers and restored by the BootROM during warmboot.\nDRAM Timing Parameter";
}

#define QRST_OFFSET 0x64
#define QRST_UNDEFMASK 0xFFFFFFF0
union qrst_u {
    struct {
        unsigned int qrst:4;                /* time from expiration of QSAFE until reset is issued LPDDR2: ceilRL - 2  DDR2: CL - 2 */
        unsigned int undefined_bits_4_31:28;
    };

    u_int32_t reg32;
};

void EmcDev::fill_qrst_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const qrst_u old_value_t = { .reg32 = value };
    const qrst_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: qrst:4",
              "time from expiration of QSAFE until reset is issued LPDDR2: ceilRL - 2  DDR2: CL - 2",
              4, old_value_t.qrst, new_value_t.qrst };
    m_bit_details_model.bits.append(entry);
    entry = { "04: undefined_bits_4_31:28", "", 28, old_value_t.undefined_bits_4_31, new_value_t.undefined_bits_4_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "This register is shadowed.\nBoot requirements\n    * This register should be parameterized in the BCT and written by the BootROM during coldboot.\n    * This register should be saved in the scratch registers and restored by the BootROM during warmboot.\nDRAM Timing Parameter";
}

#define QSAFE_OFFSET 0x68
#define QSAFE_UNDEFMASK 0xFFFFFFF0
union qsafe_u {
    struct {
        unsigned int qsafe:4;               /* time from a read command to when it is safe to issue a QRST (delayed by the QRST parameter). LPDDR2/DDR2: QSAFE &gt;= RDV - QRST */
        unsigned int undefined_bits_4_31:28;
    };

    u_int32_t reg32;
};

void EmcDev::fill_qsafe_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const qsafe_u old_value_t = { .reg32 = value };
    const qsafe_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: qsafe:4",
              "time from a read command to when it is safe to issue a QRST (delayed by the QRST parameter). LPDDR2/DDR2: QSAFE &gt;= RDV - QRST",
              4, old_value_t.qsafe, new_value_t.qsafe };
    m_bit_details_model.bits.append(entry);
    entry = { "04: undefined_bits_4_31:28", "", 28, old_value_t.undefined_bits_4_31, new_value_t.undefined_bits_4_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "When PERIODIC_QRST is enabled, the QSAFE parameter is intended to guarantee that the QRSTs will not interfere with pending reads (e.g. the queue is empty). This field must be set to at least (RDV - QRST).\nThis register is shadowed.\nBoot requirements\n    * This register should be parameterized in the BCT and written by the BootROM during coldboot.\n    * This register should be saved in the scratch registers and restored by the BootROM during warmboot.\nDRAM Timing Parameter";
}

#define RDV_OFFSET 0x6C
#define RDV_UNDEFMASK 0xFFFFFFE0
union rdv_u {
    struct {
        unsigned int rdv:5;                 /* time from read command to latching the read data from the pad macros. 15 = MAX LPDDR2: ceilRL + 5 + ceil(tDQSCKmax/tCK)  DDR2: CL + 7 for DDR2 */
        unsigned int undefined_bits_5_31:27;
    };

    u_int32_t reg32;
};

void EmcDev::fill_rdv_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const rdv_u old_value_t = { .reg32 = value };
    const rdv_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: rdv:5",
              "time from read command to latching the read data from the pad macros.\n15 = MAX LPDDR2: ceilRL + 5 + ceil(tDQSCKmax/tCK)  DDR2: CL + 7 for DDR2",
              5, old_value_t.rdv, new_value_t.rdv };
    m_bit_details_model.bits.append(entry);
    entry = { "05: undefined_bits_5_31:27", "", 27, old_value_t.undefined_bits_5_31, new_value_t.undefined_bits_5_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "RDV is the read latency register. This register value is not negotiable, it will work with the right value and will not with the wrong value. It is sequential timing, not combinational (i.e., maybe the silicon is fast enough type) timing.\n This register is shadowed.\nBoot requirements\n    * This register should be parameterized in the BCT and written by the BootROM during coldboot.\n    * This register should be saved in the scratch registers and restored by the BootROM during warmboot.\nDRAM Timing Parameter";
}

#define REFRESH_OFFSET 0x70
#define REFRESH_UNDEFMASK 0xFFFF0000
union refresh_u {
    struct {
        unsigned int refresh_lo:5;          /* specifies the interval between refresh requests (LSB portion) 31 = MAX */
        unsigned int refresh:11;            /* specifies the interval between refresh requests (MSB portion) */
        unsigned int undefined_bits_16_31:16;
    };

    u_int32_t reg32;
};

void EmcDev::fill_refresh_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const refresh_u old_value_t = { .reg32 = value };
    const refresh_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: refresh_lo:5",
              "specifies the interval between refresh requests (LSB portion)\n31 = MAX",
              5, old_value_t.refresh_lo, new_value_t.refresh_lo };
    m_bit_details_model.bits.append(entry);
    entry = { "05: refresh:11",
              "specifies the interval between refresh requests (MSB portion)",
              11, old_value_t.refresh, new_value_t.refresh };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_31:16", "", 16, old_value_t.undefined_bits_16_31, new_value_t.undefined_bits_16_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "This register is shadowed.\nBoot requirements\n    * This register should be parameterized in the BCT and written by the BootROM during coldboot.\n    * This register should be saved in the scratch registers and restored by the BootROM during warmboot.\nDRAM Timing Parameter\nThe whole register value is recommended to be about 40 less than floor(min(tREFI, tRASmax)/tCK), but no less than 80% of that value.";
}

#define BURST_REFRESH_NUM_OFFSET 0x74
#define BURST_REFRESH_NUM_UNDEFMASK 0xFFFFFFF0
union burst_refresh_num_u {
    struct {
        unsigned int burst_refresh_num:4;   /* specify the refresh burst count. 0 = Burst Refresh count equals 1 1 = Burst Refresh count equals 2 2 = Burst Refresh count equals 4 3 = Burst Refresh count equals 8 4 = Burst Refresh count equals 16 5 = Burst Refresh count equals 32 6 = Burst Refresh count equals 64 7 = Burst Refresh count equals 128 8 = Burst Refresh count equals 256 9 = Burst Refresh count equals 512 9 = MAX */
        unsigned int undefined_bits_4_31:28;
    };

    u_int32_t reg32;
};

void EmcDev::fill_burst_refresh_num_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const burst_refresh_num_u old_value_t = { .reg32 = value };
    const burst_refresh_num_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: burst_refresh_num:4",
              "specify the refresh burst count.\n0 = Burst Refresh count equals 1\n1 = Burst Refresh count equals 2\n2 = Burst Refresh count equals 4\n3 = Burst Refresh count equals 8\n4 = Burst Refresh count equals 16\n5 = Burst Refresh count equals 32\n6 = Burst Refresh count equals 64\n7 = Burst Refresh count equals 128\n8 = Burst Refresh count equals 256\n9 = Burst Refresh count equals 512\n9 = MAX",
              4, old_value_t.burst_refresh_num, new_value_t.burst_refresh_num };
    m_bit_details_model.bits.append(entry);
    entry = { "04: undefined_bits_4_31:28", "", 28, old_value_t.undefined_bits_4_31, new_value_t.undefined_bits_4_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "BURST_REFRESH_NUM is used to specify the refresh burst count. The refresh controller will wait until BURST_REFRESH_NUM refreshes have been scheduled, and then issue them all at once. This can result in a performance\nimprovement in many cases. This may increase worst-case read latency due to burst refresh, so it is recommended to be programmed to BR1 for cases where latency-sensitive modules are active.\nNote: If tRAS(max) is less than the refresh interval (tREF/#_of_rows), tRAS(max) must be used instead of the refresh interval in the formula above. This is because refresh is used to satisfy tRAS (max) timing. Accordingly, BURST_REFRESH_NUM must be programmed in such a way that queuing up multiple refreshes does not violate tRAS(max) timing. Burst length = 2^BURST_REFRESH_NUM.\n Refreshes will be throttled to meet TREFBW limitation (8/window) if TREFBW > 0.\nThis register is shadowed.\nBoot requirements\n    * This register should be parameterized in the BCT and written by the BootROM during coldboot.\n    * This register should be saved in the scratch registers and restored by the BootROM during warmboot.\nDRAM Timing Parameter";
}

#define PDEX2WR_OFFSET 0x78
#define PDEX2WR_UNDEFMASK 0xFFFFFFF0
union pdex2wr_u {
    struct {
        unsigned int pdex2wr:4;             /* specify the timing delay from exit of powerdown mode to a write command. Largest allowed value is 14 LPDDR2/DDR2: ceil(tXP/tCLK)+1 */
        unsigned int undefined_bits_4_31:28;
    };

    u_int32_t reg32;
};

void EmcDev::fill_pdex2wr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const pdex2wr_u old_value_t = { .reg32 = value };
    const pdex2wr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: pdex2wr:4",
              "specify the timing delay from exit of powerdown mode to a write command. Largest allowed value is 14 LPDDR2/DDR2: ceil(tXP/tCLK)+1",
              4, old_value_t.pdex2wr, new_value_t.pdex2wr };
    m_bit_details_model.bits.append(entry);
    entry = { "04: undefined_bits_4_31:28", "", 28, old_value_t.undefined_bits_4_31, new_value_t.undefined_bits_4_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "This register is shadowed.\nBoot requirements\n    * This register should be parameterized in the BCT and written by the BootROM during coldboot.\n    * This register should be saved in the scratch registers and restored by the BootROM during warmboot.\nDRAM Timing Parameter";
}

#define PDEX2RD_OFFSET 0x7C
#define PDEX2RD_UNDEFMASK 0xFFFFFFF0
union pdex2rd_u {
    struct {
        unsigned int pdex2rd:4;             /* specify the timing delay from exit of powerdown mode to a read command. Largest allowed value is 14 LPDDR2/DDR2: ceil(tXP/tCLK)+1 */
        unsigned int undefined_bits_4_31:28;
    };

    u_int32_t reg32;
};

void EmcDev::fill_pdex2rd_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const pdex2rd_u old_value_t = { .reg32 = value };
    const pdex2rd_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: pdex2rd:4",
              "specify the timing delay from exit of powerdown mode to a read command. Largest allowed value is 14 LPDDR2/DDR2: ceil(tXP/tCLK)+1",
              4, old_value_t.pdex2rd, new_value_t.pdex2rd };
    m_bit_details_model.bits.append(entry);
    entry = { "04: undefined_bits_4_31:28", "", 28, old_value_t.undefined_bits_4_31, new_value_t.undefined_bits_4_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "This register is shadowed.\nBoot requirements\n    * This register should be parameterized in the BCT and written by the BootROM during coldboot.\n    * This register should be saved in the scratch registers and restored by the BootROM during warmboot.\nDRAM Timing Parameter";
}

#define PCHG2PDEN_OFFSET 0x80
#define PCHG2PDEN_UNDEFMASK 0xFFFFFFE0
union pchg2pden_u {
    struct {
        unsigned int pchg2pden:5;           /* specify the timing delay from a precharge command to powerdown entry. LPDDR2/DDR2: ceil(tRP/tCK) */
        unsigned int undefined_bits_5_31:27;
    };

    u_int32_t reg32;
};

void EmcDev::fill_pchg2pden_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const pchg2pden_u old_value_t = { .reg32 = value };
    const pchg2pden_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: pchg2pden:5",
              "specify the timing delay from a precharge command to powerdown entry. LPDDR2/DDR2: ceil(tRP/tCK)",
              5, old_value_t.pchg2pden, new_value_t.pchg2pden };
    m_bit_details_model.bits.append(entry);
    entry = { "05: undefined_bits_5_31:27", "", 27, old_value_t.undefined_bits_5_31, new_value_t.undefined_bits_5_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "This register is shadowed.\nBoot requirements\n    * This register should be parameterized in the BCT and written by the BootROM during coldboot.\n    * This register should be saved in the scratch registers and restored by the BootROM during warmboot.\nDRAM Timing Parameter";
}

#define ACT2PDEN_OFFSET 0x84
#define ACT2PDEN_UNDEFMASK 0xFFFFFFE0
union act2pden_u {
    struct {
        unsigned int act2pden:5;            /* specify the timing delay from an activate, mrs or emrs command to powerdown entry. LPDDR2: ceilmax(8, ceil(tRCD/tCK)) DDR2: ceil(tRCD/tCLK) */
        unsigned int undefined_bits_5_31:27;
    };

    u_int32_t reg32;
};

void EmcDev::fill_act2pden_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const act2pden_u old_value_t = { .reg32 = value };
    const act2pden_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: act2pden:5",
              "specify the timing delay from an activate, mrs or emrs command to powerdown entry. LPDDR2: ceilmax(8, ceil(tRCD/tCK)) DDR2: ceil(tRCD/tCLK)",
              5, old_value_t.act2pden, new_value_t.act2pden };
    m_bit_details_model.bits.append(entry);
    entry = { "05: undefined_bits_5_31:27", "", 27, old_value_t.undefined_bits_5_31, new_value_t.undefined_bits_5_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "This register is shadowed.\nBoot requirements\n    * This register should be parameterized in the BCT and written by the BootROM during coldboot.\n    * This register should be saved in the scratch registers and restored by the BootROM during warmboot.\nDRAM Timing Parameter";
}

#define AR2PDEN_OFFSET 0x88
#define AR2PDEN_UNDEFMASK 0xFFFFFFE0
union ar2pden_u {
    struct {
        unsigned int ar2pden:5;             /* specify the timing delay from an autorefresh command to powerdown entry. LPDDR2/DDR2: 1 */
        unsigned int undefined_bits_5_31:27;
    };

    u_int32_t reg32;
};

void EmcDev::fill_ar2pden_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const ar2pden_u old_value_t = { .reg32 = value };
    const ar2pden_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: ar2pden:5",
              "specify the timing delay from an autorefresh command to powerdown entry. LPDDR2/DDR2: 1",
              5, old_value_t.ar2pden, new_value_t.ar2pden };
    m_bit_details_model.bits.append(entry);
    entry = { "05: undefined_bits_5_31:27", "", 27, old_value_t.undefined_bits_5_31, new_value_t.undefined_bits_5_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "This register is shadowed.\nBoot requirements\n    * This register should be parameterized in the BCT and written by the BootROM during coldboot.\n    * This register should be saved in the scratch registers and restored by the BootROM during warmboot.\nDRAM Timing Parameter";
}

#define RW2PDEN_OFFSET 0x8C
#define RW2PDEN_UNDEFMASK 0xFFFFFFC0
union rw2pden_u {
    struct {
        unsigned int rw2pden:6;             /* specify the timing delay from a read/write command to powerdown entry. Auto-precharge timing must be taken into account when programming this field. LPDDR2: ceilmax(RL+ceil((tDQSCKmax+tRP)/tCK)+1, WL+1+ceil((tWR+tRP)/tCK))  DDR2: max(RL+ceil((tDQSCKmax+tRP)/tCK)+1, WL+ceil((tWR+tRP)/tCK)) */
        unsigned int undefined_bits_6_31:26;
    };

    u_int32_t reg32;
};

void EmcDev::fill_rw2pden_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const rw2pden_u old_value_t = { .reg32 = value };
    const rw2pden_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: rw2pden:6",
              "specify the timing delay from a read/write command to powerdown entry. Auto-precharge timing must be taken into account when programming this field. LPDDR2: ceilmax(RL+ceil((tDQSCKmax+tRP)/tCK)+1, WL+1+ceil((tWR+tRP)/tCK))  DDR2: max(RL+ceil((tDQSCKmax+tRP)/tCK)+1, WL+ceil((tWR+tRP)/tCK))",
              6, old_value_t.rw2pden, new_value_t.rw2pden };
    m_bit_details_model.bits.append(entry);
    entry = { "06: undefined_bits_6_31:26", "", 26, old_value_t.undefined_bits_6_31, new_value_t.undefined_bits_6_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "This register is shadowed.\nBoot requirements\n    * This register should be parameterized in the BCT and written by the BootROM during coldboot.\n    * This register should be saved in the scratch registers and restored by the BootROM during warmboot.\nDRAM Timing Parameter";
}

#define TXSR_OFFSET 0x90
#define TXSR_UNDEFMASK 0xFFFFF000
union txsr_u {
    struct {
        unsigned int txsr:12;               /* cycles between self-refresh exit & first DRAM command Largest allowed value is 0xffe LPDDR2: ceilceil(tXSR/tCK); min = 2  DDR2: ceil(tXSR/tCK) */
        unsigned int undefined_bits_12_31:20;
    };

    u_int32_t reg32;
};

void EmcDev::fill_txsr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const txsr_u old_value_t = { .reg32 = value };
    const txsr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: txsr:12",
              "cycles between self-refresh exit & first DRAM command Largest allowed value is 0xffe LPDDR2: ceilceil(tXSR/tCK); min = 2  DDR2: ceil(tXSR/tCK)",
              12, old_value_t.txsr, new_value_t.txsr };
    m_bit_details_model.bits.append(entry);
    entry = { "12: undefined_bits_12_31:20", "", 20, old_value_t.undefined_bits_12_31, new_value_t.undefined_bits_12_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "This register is shadowed.\nBoot requirements\n    * This register should be parameterized in the BCT and written by the BootROM during coldboot.\n    * This register should be saved in the scratch registers and restored by the BootROM during warmboot.\nDRAM Timing Parameter";
}

#define TCKE_OFFSET 0x94
#define TCKE_UNDEFMASK 0xFFFFFFF0
union tcke_u {
    struct {
        unsigned int tcke:4;                /* specify minimum CKE pulse width. LPDDR2: ceilmax(tCKE, ceil(tXP/tCKmin)): tCKmin is the tCK of the max frequency of the DRAM parts used  DDR2: tCKE */
        unsigned int undefined_bits_4_31:28;
    };

    u_int32_t reg32;
};

void EmcDev::fill_tcke_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const tcke_u old_value_t = { .reg32 = value };
    const tcke_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: tcke:4",
              "specify minimum CKE pulse width. LPDDR2: ceilmax(tCKE, ceil(tXP/tCKmin)): tCKmin is the tCK of the max frequency of the DRAM parts used  DDR2: tCKE",
              4, old_value_t.tcke, new_value_t.tcke };
    m_bit_details_model.bits.append(entry);
    entry = { "04: undefined_bits_4_31:28", "", 28, old_value_t.undefined_bits_4_31, new_value_t.undefined_bits_4_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "This register is shadowed.\nBoot requirements\n    * This register should be parameterized in the BCT and written by the BootROM during coldboot.\n    * This register should be saved in the scratch registers and restored by the BootROM during warmboot.\nDRAM Timing Parameter";
}

#define TFAW_OFFSET 0x98
#define TFAW_UNDEFMASK 0xFFFFFFC0
union tfaw_u {
    struct {
        unsigned int tfaw:6;                /* specify the width of the FAW (four-activate window) for 8-bank devices. Set to 0 to disable this timing check. Only 4 activates may occur withing the rolling window.  LPDDR2: ceilceil(tFAW/tCK); min = 8  DDR2: ceil(tFAW/tCK) */
        unsigned int undefined_bits_6_31:26;
    };

    u_int32_t reg32;
};

void EmcDev::fill_tfaw_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const tfaw_u old_value_t = { .reg32 = value };
    const tfaw_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: tfaw:6",
              "specify the width of the FAW (four-activate window) for 8-bank devices. Set to 0 to disable this timing check. Only 4 activates may occur withing the rolling window.  LPDDR2: ceilceil(tFAW/tCK); min = 8  DDR2: ceil(tFAW/tCK)",
              6, old_value_t.tfaw, new_value_t.tfaw };
    m_bit_details_model.bits.append(entry);
    entry = { "06: undefined_bits_6_31:26", "", 26, old_value_t.undefined_bits_6_31, new_value_t.undefined_bits_6_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "This register is shadowed.\nBoot requirements\n    * This register should be parameterized in the BCT and written by the BootROM during coldboot.\n    * This register should be saved in the scratch registers and restored by the BootROM during warmboot.\nDRAM Timing Parameter";
}

#define TRPAB_OFFSET 0x9C
#define TRPAB_UNDEFMASK 0xFFFFFFC0
union trpab_u {
    struct {
        unsigned int trpab:6;               /* specify precharge-all tRP allowance for 8-bank devices. Setting this field to 0 will cause EMC to use TRP.TRP for precharge-all. LPDDR2: ceilceil((tRPpb+3)/tCK); min = 3  DDR2: ceil((tRP + tCK)/tCK) */
        unsigned int undefined_bits_6_31:26;
    };

    u_int32_t reg32;
};

void EmcDev::fill_trpab_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const trpab_u old_value_t = { .reg32 = value };
    const trpab_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: trpab:6",
              "specify precharge-all tRP allowance for 8-bank devices. Setting this field to 0 will cause EMC to use TRP.TRP for precharge-all. LPDDR2: ceilceil((tRPpb+3)/tCK); min = 3  DDR2: ceil((tRP + tCK)/tCK)",
              6, old_value_t.trpab, new_value_t.trpab };
    m_bit_details_model.bits.append(entry);
    entry = { "06: undefined_bits_6_31:26", "", 26, old_value_t.undefined_bits_6_31, new_value_t.undefined_bits_6_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "This register is shadowed.\nBoot requirements\n    * This register should be parameterized in the BCT and written by the BootROM during coldboot.\n    * This register should be saved in the scratch registers and restored by the BootROM during warmboot.\nDRAM Timing Parameter";
}

#define TCLKSTABLE_OFFSET 0xA0
#define TCLKSTABLE_UNDEFMASK 0xFFFFFFF0
union tclkstable_u {
    struct {
        unsigned int tclkstable:4;          /* specify minimum number of cycles of a stable clock period prior to exiting powerdown or self-refresh modes. LPDDR2: ceilmax(5, ceil(tRFC]/tCKmin/4) - 2): tCKmin is the tCK of the max frequency of the DRAM parts used  DDR2: 2 */
        unsigned int undefined_bits_4_31:28;
    };

    u_int32_t reg32;
};

void EmcDev::fill_tclkstable_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const tclkstable_u old_value_t = { .reg32 = value };
    const tclkstable_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: tclkstable:4",
              "specify minimum number of cycles of a stable clock period prior to exiting powerdown or self-refresh modes. LPDDR2: ceilmax(5, ceil(tRFC]/tCKmin/4) - 2): tCKmin is the tCK of the max frequency of the DRAM parts used  DDR2: 2",
              4, old_value_t.tclkstable, new_value_t.tclkstable };
    m_bit_details_model.bits.append(entry);
    entry = { "04: undefined_bits_4_31:28", "", 28, old_value_t.undefined_bits_4_31, new_value_t.undefined_bits_4_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "This register is shadowed.\nBoot requirements\n    * This register should be parameterized in the BCT and written by the BootROM during coldboot.\n    * This register should be saved in the scratch registers and restored by the BootROM during warmboot.\nDRAM Timing Parameter";
}

#define TCLKSTOP_OFFSET 0xA4
#define TCLKSTOP_UNDEFMASK 0xFFFFFFF0
union tclkstop_u {
    struct {
        unsigned int tclkstop:4;            /* delay from last command to stopping the external clock to DRAM devices. LPDDR2/DDR2: 2 */
        unsigned int undefined_bits_4_31:28;
    };

    u_int32_t reg32;
};

void EmcDev::fill_tclkstop_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const tclkstop_u old_value_t = { .reg32 = value };
    const tclkstop_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: tclkstop:4",
              "delay from last command to stopping the external clock to DRAM devices. LPDDR2/DDR2: 2",
              4, old_value_t.tclkstop, new_value_t.tclkstop };
    m_bit_details_model.bits.append(entry);
    entry = { "04: undefined_bits_4_31:28", "", 28, old_value_t.undefined_bits_4_31, new_value_t.undefined_bits_4_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "This register is shadowed.\nBoot requirements\n    * This register should be parameterized in the BCT and written by the BootROM during coldboot.\n    * This register should be saved in the scratch registers and restored by the BootROM during warmboot.\nDRAM Timing Parameter";
}

#define TREFBW_OFFSET 0xA8
#define TREFBW_UNDEFMASK 0xFFFFC000
union trefbw_u {
    struct {
        unsigned int trefbw:14;             /* specify the width of the burst-refresh window. If set to a non-zero value, only 8 refreshes will occur in this rolling window. Set to 0 to disable this timing check.  LPDDR2: ceilceil(32*tRFCab/tCK)  DDR2: 0 */
        unsigned int undefined_bits_14_31:18;
    };

    u_int32_t reg32;
};

void EmcDev::fill_trefbw_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const trefbw_u old_value_t = { .reg32 = value };
    const trefbw_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: trefbw:14",
              "specify the width of the burst-refresh window. If set to a non-zero value, only 8 refreshes will occur in this rolling window. Set to 0 to disable this timing check.  LPDDR2: ceilceil(32*tRFCab/tCK)  DDR2: 0",
              14, old_value_t.trefbw, new_value_t.trefbw };
    m_bit_details_model.bits.append(entry);
    entry = { "14: undefined_bits_14_31:18", "", 18, old_value_t.undefined_bits_14_31, new_value_t.undefined_bits_14_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "This register is shadowed.\nBoot requirements\n    * This register should be parameterized in the BCT and written by the BootROM during coldboot.\n    * This register should be saved in the scratch registers and restored by the BootROM during warmboot.\nDRAM Timing Parameter";
}

#define QUSE_EXTRA_OFFSET 0xAC
#define QUSE_EXTRA_UNDEFMASK 0xFFFFFFF0
union quse_extra_u {
    struct {
        unsigned int quse_extra:4;
        unsigned int undefined_bits_4_31:28;
    };

    u_int32_t reg32;
};

void EmcDev::fill_quse_extra_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const quse_extra_u old_value_t = { .reg32 = value };
    const quse_extra_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: quse_extra:4", "", 4, old_value_t.quse_extra, new_value_t.quse_extra };
    m_bit_details_model.bits.append(entry);
    entry = { "04: undefined_bits_4_31:28", "", 28, old_value_t.undefined_bits_4_31, new_value_t.undefined_bits_4_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "QUSE_EXTRA is combined with quse to add extra cycles to data return window. This is for use with dqs pulldowns in lpddr2 where start of read preamble could vary by more than 1 cycle\nExample: To extend end of QUSE window by 1 cycle, set QUSE_EXTRA = QUSE + 1. To start quse window earlier by 1 cycle, set QUSE_EXTRA = QUSE - 1. Disabled if QUSE_EXTRA = 0.\nThis register is shadowed.\nBoot requirements\n    * This register should be parameterized in the BCT and written by the BootROM during coldboot.\n    * This register should be saved in the scratch registers and restored by the BootROM during warmboot.";
}

#define ODT_WRITE_OFFSET 0xB0
#define ODT_WRITE_UNDEFMASK 0x3FFFFFF8
union odt_write_u {
    struct {
        unsigned int odt_wr_delay:3;        /* Set this field = ABS ( WL - ceiling(tAOND) - 2 ). The valid programming range is 0 <= ODT_WR_DELAY <= 2 if ODT_B4_WRITE=0, 0 <= ODT_WR_DELAY <= 1 if ODT_B4_WRITE=1 */
        unsigned int undefined_bits_3_29:27;
        unsigned int odt_b4_write:1;        /* If this field == 1, ODT is turned on ODT_WR_DELAY cycles prior to dram WRITE command. If this field == 0, ODT is turned on ODT_WR_DELAY cycles after dram WRITE command. Set ODT_B4_WRITE to 1 if ( WL - ceiling(tAOND) - 2 ) < 0 */
        unsigned int enable_odt_during_write:1;/* enables ODT to be turned on prior to issuing write to DRAM. If ENABLE_ODT_DURING_WRITE = 1 and DISABLE_ODT_DURING_READ = 0, ODT will always be enabled after 1st write */
    };

    u_int32_t reg32;
};

void EmcDev::fill_odt_write_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const odt_write_u old_value_t = { .reg32 = value };
    const odt_write_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: odt_wr_delay:3",
              "Set this field = ABS ( WL - ceiling(tAOND) - 2 ). The valid programming range is 0 <= ODT_WR_DELAY <= 2 if ODT_B4_WRITE=0, 0 <= ODT_WR_DELAY <= 1 if ODT_B4_WRITE=1",
              3, old_value_t.odt_wr_delay, new_value_t.odt_wr_delay };
    m_bit_details_model.bits.append(entry);
    entry = { "03: undefined_bits_3_29:27", "", 27, old_value_t.undefined_bits_3_29, new_value_t.undefined_bits_3_29 };
    m_bit_details_model.bits.append(entry);
    entry = { "30: odt_b4_write:1",
              "If this field == 1, ODT is turned on ODT_WR_DELAY cycles prior to dram WRITE command. If this field == 0, ODT is turned on ODT_WR_DELAY cycles after dram WRITE command. Set ODT_B4_WRITE to 1 if ( WL - ceiling(tAOND) - 2 ) < 0",
              1, old_value_t.odt_b4_write, new_value_t.odt_b4_write };
    m_bit_details_model.bits.append(entry);
    entry = { "31: enable_odt_during_write:1",
              "enables ODT to be turned on prior to issuing write to DRAM. If ENABLE_ODT_DURING_WRITE = 1 and DISABLE_ODT_DURING_READ = 0, ODT will always be enabled after 1st write",
              1, old_value_t.enable_odt_during_write, new_value_t.enable_odt_during_write };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = " For DDR2, ODT may be enabled during writes and disabled during reads via control of ODT pin.\nThis register is shadowed.\nBoot requirements\n    * This register should be parameterized in the BCT and written by the BootROM during coldboot.\n    * This register should be saved in the scratch registers and restored by the BootROM during warmboot.";
}

#define ODT_READ_OFFSET 0xB4
#define ODT_READ_UNDEFMASK 0x3FFFFFF8
union odt_read_u {
    struct {
        unsigned int odt_rd_delay:3;        /* Set this field = ABS ( RL - ceiling(tAOFD) - 2 ). The valid programming range is 0 <= ODT_RD_DELAY <= 2 if ODT_B4_READ=0, 0 <= ODT_RD_DELAY <= 1 if ODT_B4_READ=1 */
        unsigned int undefined_bits_3_29:27;
        unsigned int odt_b4_read:1;         /* If this field == 1, ODT is turned off ODT_RD_DELAY cycles prior to dram READ command. If this field == 0, ODT is turned off ODT_RD_DELAY cycles after dram READ command. Set ODT_B4_READ to 1 if ( RL - ceiling(tAOFD) - 2 ) < 0 */
        unsigned int disable_odt_during_read:1;/* enables ODT to be turned off prior to issuing read to DRAM. If this field == 0, ODT state will not be changed for reads. If this field == 1, Turn off ODT prior to READ command (has no effect if ODT ENABLE_ODT_DURING_WRITE == 0, as ODT will always be disabled) */
    };

    u_int32_t reg32;
};

void EmcDev::fill_odt_read_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const odt_read_u old_value_t = { .reg32 = value };
    const odt_read_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: odt_rd_delay:3",
              "Set this field = ABS ( RL - ceiling(tAOFD) - 2 ). The valid programming range is 0 <= ODT_RD_DELAY <= 2 if ODT_B4_READ=0, 0 <= ODT_RD_DELAY <= 1 if ODT_B4_READ=1",
              3, old_value_t.odt_rd_delay, new_value_t.odt_rd_delay };
    m_bit_details_model.bits.append(entry);
    entry = { "03: undefined_bits_3_29:27", "", 27, old_value_t.undefined_bits_3_29, new_value_t.undefined_bits_3_29 };
    m_bit_details_model.bits.append(entry);
    entry = { "30: odt_b4_read:1",
              "If this field == 1, ODT is turned off ODT_RD_DELAY cycles prior to dram READ command. If this field == 0, ODT is turned off ODT_RD_DELAY cycles after dram READ command. Set ODT_B4_READ to 1 if ( RL - ceiling(tAOFD) - 2 ) < 0",
              1, old_value_t.odt_b4_read, new_value_t.odt_b4_read };
    m_bit_details_model.bits.append(entry);
    entry = { "31: disable_odt_during_read:1",
              "enables ODT to be turned off prior to issuing read to DRAM. If this field == 0, ODT state will not be changed for reads. If this field == 1, Turn off ODT prior to READ command (has no effect if ODT ENABLE_ODT_DURING_WRITE == 0, as ODT will always be disabled)",
              1, old_value_t.disable_odt_during_read, new_value_t.disable_odt_during_read };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = " For DDR2, ODT may be enabled during writes and disabled during reads via control of ODT pin.\nThis register is shadowed.\nBoot requirements\n    * This register should be parameterized in the BCT and written by the BootROM during coldboot.\n    * This register should be saved in the scratch registers and restored by the BootROM during warmboot.";
}

#define MRS_OFFSET 0xCC
#define MRS_UNDEFMASK 0x3FCFC000
union mrs_u {
    struct {
        unsigned int mrs_adr:14;            /* mode-register data to be written */
        unsigned int undefined_bits_14_19:6;
        unsigned int mrs_ba:2;              /* Set to 0x0 for MRS */
        unsigned int undefined_bits_22_29:8;
        unsigned int mrs_dev_selectn:2;     /* active low chip-select, 0x0 applies command to both devices, 0x2 to for only dev0, 0x1 for only dev1 */
    };

    u_int32_t reg32;
};

void EmcDev::fill_mrs_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const mrs_u old_value_t = { .reg32 = value };
    const mrs_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: mrs_adr:14",
              "mode-register data to be written",
              14, old_value_t.mrs_adr, new_value_t.mrs_adr };
    m_bit_details_model.bits.append(entry);
    entry = { "14: undefined_bits_14_19:6", "", 6, old_value_t.undefined_bits_14_19, new_value_t.undefined_bits_14_19 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: mrs_ba:2",
              "Set to 0x0 for MRS",
              2, old_value_t.mrs_ba, new_value_t.mrs_ba };
    m_bit_details_model.bits.append(entry);
    entry = { "22: undefined_bits_22_29:8", "", 8, old_value_t.undefined_bits_22_29, new_value_t.undefined_bits_22_29 };
    m_bit_details_model.bits.append(entry);
    entry = { "30: mrs_dev_selectn:2",
              "active low chip-select, 0x0 applies command to both devices, 0x2 to for only dev0, 0x1 for only dev1",
              2, old_value_t.mrs_dev_selectn, new_value_t.mrs_dev_selectn };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "The MRS register allows SW to issue an MRS command.\nBA0, BA1 are used to address MRS or EMRS registers in DRAM. Although this register can also program EMRS, use the EMRS register so that the HW registers can shadow what is in the DRAM.\nBoot requirements\n    * This register should be parameterized in the BCT and written by the BootROM during coldboot.\nCommand trigger: MRS";
}

#define EMRS_OFFSET 0xD0
#define EMRS_UNDEFMASK 0x3FCFC000
union emrs_u {
    struct {
        unsigned int emrs_adr:14;           /* mode-register data to be written */
        unsigned int undefined_bits_14_19:6;
        unsigned int emrs_ba:2;             /* Set to 0x1 for EMRS (and where applicable, 0x2 for EMRS2, and 0x3 for EMRS3) */
        unsigned int undefined_bits_22_29:8;
        unsigned int emrs_dev_selectn:2;    /* active low chip-select, 0x0 applies command to both devices, 0x2 to for only dev0, 0x1 for only dev1 */
    };

    u_int32_t reg32;
};

void EmcDev::fill_emrs_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const emrs_u old_value_t = { .reg32 = value };
    const emrs_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: emrs_adr:14",
              "mode-register data to be written",
              14, old_value_t.emrs_adr, new_value_t.emrs_adr };
    m_bit_details_model.bits.append(entry);
    entry = { "14: undefined_bits_14_19:6", "", 6, old_value_t.undefined_bits_14_19, new_value_t.undefined_bits_14_19 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: emrs_ba:2",
              "Set to 0x1 for EMRS (and where applicable, 0x2 for EMRS2, and 0x3 for EMRS3)",
              2, old_value_t.emrs_ba, new_value_t.emrs_ba };
    m_bit_details_model.bits.append(entry);
    entry = { "22: undefined_bits_22_29:8", "", 8, old_value_t.undefined_bits_22_29, new_value_t.undefined_bits_22_29 };
    m_bit_details_model.bits.append(entry);
    entry = { "30: emrs_dev_selectn:2",
              "active low chip-select, 0x0 applies command to both devices, 0x2 to for only dev0, 0x1 for only dev1",
              2, old_value_t.emrs_dev_selectn, new_value_t.emrs_dev_selectn };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "The EMRS register allows SW to issue an EMRS command.\nBoot requirements\n    * This register should be parameterized in the BCT and written by the BootROM during coldboot.\nCommand trigger: EMRS";
}

#define REF_OFFSET 0xD4
#define REF_UNDEFMASK 0xFFFF00FE
union ref_u {
    struct {
        unsigned int ref_cmd:1;             /* causes the hardware to perform a REFRESH to all DRAM banks */
        unsigned int undefined_bits_1_7:7;
        unsigned int ref_num:8;             /* perform (REF_NUM + 1) refresh cycles */
        unsigned int undefined_bits_16_31:16;
    };

    u_int32_t reg32;
};

void EmcDev::fill_ref_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const ref_u old_value_t = { .reg32 = value };
    const ref_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: ref_cmd:1",
              "causes the hardware to perform a REFRESH to all DRAM banks",
              1, old_value_t.ref_cmd, new_value_t.ref_cmd };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_7:7", "", 7, old_value_t.undefined_bits_1_7, new_value_t.undefined_bits_1_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: ref_num:8",
              "perform (REF_NUM + 1) refresh cycles",
              8, old_value_t.ref_num, new_value_t.ref_num };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_31:16", "", 16, old_value_t.undefined_bits_16_31, new_value_t.undefined_bits_16_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "The REF register allows SW to issue refresh commands. This is done to ensure proper DRAM initialization.\n Boot requirements\n    * This register triggers a refresh command. REF_CMD should be written with 0x1 during coldboot to trigger refresh commands during DRAM initialization.\nCommand trigger: Refresh";
}

#define PRE_OFFSET 0xD8
#define PRE_UNDEFMASK 0x3FFFFFFE
union pre_u {
    struct {
        unsigned int pre_cmd:1;             /* causes the hardware to perform a PRECHARGE to all DRAM banks */
        unsigned int undefined_bits_1_29:29;
        unsigned int pre_dev_selectn:2;     /* active low chip-select, 0x0 applies command to both devices, 0x2 to for only dev0, 0x1 for only dev1 */
    };

    u_int32_t reg32;
};

void EmcDev::fill_pre_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const pre_u old_value_t = { .reg32 = value };
    const pre_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: pre_cmd:1",
              "causes the hardware to perform a PRECHARGE to all DRAM banks",
              1, old_value_t.pre_cmd, new_value_t.pre_cmd };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_29:29", "", 29, old_value_t.undefined_bits_1_29, new_value_t.undefined_bits_1_29 };
    m_bit_details_model.bits.append(entry);
    entry = { "30: pre_dev_selectn:2",
              "active low chip-select, 0x0 applies command to both devices, 0x2 to for only dev0, 0x1 for only dev1",
              2, old_value_t.pre_dev_selectn, new_value_t.pre_dev_selectn };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "The PRE register allows SW to issue a precharge all command. This command may be used to ensure proper DRAM initialization.\nBoot requirements\n    * This register triggers a precharge-all command. PRE_CMD should be written with 0x1 during coldboot to trigger refresh commands during DRAM initialization.\n    * If per-device DPD is used, the PRE_DEV_SELECTN field should be parameterized in the BCT and written by the BootROM during coldboot.\nCommand trigger: Precharge-All";
}

#define NOP_OFFSET 0xDC
#define NOP_UNDEFMASK 0xFFFFFFFE
union nop_u {
    struct {
        unsigned int nop_cmd:1;             /* causes the hardware to perform a NOP to all DRAM banks */
        unsigned int undefined_bits_1_31:31;
    };

    u_int32_t reg32;
};

void EmcDev::fill_nop_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const nop_u old_value_t = { .reg32 = value };
    const nop_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: nop_cmd:1",
              "causes the hardware to perform a NOP to all DRAM banks",
              1, old_value_t.nop_cmd, new_value_t.nop_cmd };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_31:31", "", 31, old_value_t.undefined_bits_1_31, new_value_t.undefined_bits_1_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "The NOP register allows SW to issue an explicit nop command. This command may be used to ensure proper DRAM initialization.\nBoot requirements\n    * This register triggers a no-operation command. NOP_CMD should be written with 0x1 during coldboot to trigger no-op commands during DRAM initialization.\nCommand trigger: NOP";
}

#define SELF_REF_OFFSET 0xE0
#define SELF_REF_UNDEFMASK 0x3FFFFFFE
union self_ref_u {
    struct {
        unsigned int self_ref_cmd:1;        /* causes the hardware to issue a SELF_REFRESH command. While CMD:ENABLED, the CKE pin is held deasserted. The CMD:ENABLED state will override the PIN:CKE setting. The DRAM will ignore all accesses until CMD:DISABLED. 0 = DISABLED 1 = ENABLED */
        unsigned int undefined_bits_1_29:29;
        unsigned int sref_dev_selectn:2;    /* active low chip-select, 0x0 applies command to both devices, 0x2 to for only dev0, 0x1 for only dev1, 0x3 for neither device */
    };

    u_int32_t reg32;
};

void EmcDev::fill_self_ref_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const self_ref_u old_value_t = { .reg32 = value };
    const self_ref_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: self_ref_cmd:1",
              "causes the hardware to issue a SELF_REFRESH command. While CMD:ENABLED, the CKE pin is held deasserted. The CMD:ENABLED state will override the PIN:CKE setting. The DRAM will ignore all accesses until CMD:DISABLED.\n0 = DISABLED\n1 = ENABLED",
              1, old_value_t.self_ref_cmd, new_value_t.self_ref_cmd };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_29:29", "", 29, old_value_t.undefined_bits_1_29, new_value_t.undefined_bits_1_29 };
    m_bit_details_model.bits.append(entry);
    entry = { "30: sref_dev_selectn:2",
              "active low chip-select, 0x0 applies command to both devices, 0x2 to for only dev0, 0x1 for only dev1, 0x3 for neither device",
              2, old_value_t.sref_dev_selectn, new_value_t.sref_dev_selectn };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "The SELF_REF register allows SW to issue self-refresh commands.\nCommand trigger: SELF REFRESH";
}

#define DPD_OFFSET 0xE4
#define DPD_UNDEFMASK 0x3FFFFFFE
union dpd_u {
    struct {
        unsigned int dpd_cmd:1;             /* causes the hardware to issue the deep power down command (Burst Terminate w/ cke low). While in DPD mode, the DRAM will not maintain data integrity. While CMD:ENABLED, the CKE pin is held deasserted. The CMD:ENABLED state will override the PIN:CKE setting. The DRAM will ignore all accesses until CMD:DISABLED. 0 = DISABLED 1 = ENABLED */
        unsigned int undefined_bits_1_29:29;
        unsigned int dpd_dev_selectn:2;     /* active low chip-select, 0x0 applies command to both devices, 0x2 to for only dev0, 0x1 for only dev1 */
    };

    u_int32_t reg32;
};

void EmcDev::fill_dpd_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const dpd_u old_value_t = { .reg32 = value };
    const dpd_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: dpd_cmd:1",
              "causes the hardware to issue the deep power down command (Burst Terminate w/ cke low). While in DPD mode, the DRAM will not maintain data integrity. While CMD:ENABLED, the CKE pin is held deasserted. The CMD:ENABLED state will override the PIN:CKE setting. The DRAM will ignore all accesses until CMD:DISABLED.\n0 = DISABLED\n1 = ENABLED",
              1, old_value_t.dpd_cmd, new_value_t.dpd_cmd };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_29:29", "", 29, old_value_t.undefined_bits_1_29, new_value_t.undefined_bits_1_29 };
    m_bit_details_model.bits.append(entry);
    entry = { "30: dpd_dev_selectn:2",
              "active low chip-select, 0x0 applies command to both devices, 0x2 to for only dev0, 0x1 for only dev1",
              2, old_value_t.dpd_dev_selectn, new_value_t.dpd_dev_selectn };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "The DPD register allows SW to issue a deep power down command.\nCommand trigger: Deep Power Down";
}

#define MRW_OFFSET 0xE8
#define MRW_UNDEFMASK 0x3F00FF00
union mrw_u {
    struct {
        unsigned int mrw_op:8;              /* data to be written */
        unsigned int undefined_bits_8_15:8;
        unsigned int mrw_ma:8;              /* register address */
        unsigned int undefined_bits_24_29:6;
        unsigned int mrw_dev_selectn:2;     /* active-low chip-select, 0x0 applies command to both devices, 0x2 to for only dev0, 0x1 for dev1 */
    };

    u_int32_t reg32;
};

void EmcDev::fill_mrw_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const mrw_u old_value_t = { .reg32 = value };
    const mrw_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: mrw_op:8",
              "data to be written",
              8, old_value_t.mrw_op, new_value_t.mrw_op };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_15:8", "", 8, old_value_t.undefined_bits_8_15, new_value_t.undefined_bits_8_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: mrw_ma:8",
              "register address",
              8, old_value_t.mrw_ma, new_value_t.mrw_ma };
    m_bit_details_model.bits.append(entry);
    entry = { "24: undefined_bits_24_29:6", "", 6, old_value_t.undefined_bits_24_29, new_value_t.undefined_bits_24_29 };
    m_bit_details_model.bits.append(entry);
    entry = { "30: mrw_dev_selectn:2",
              "active-low chip-select, 0x0 applies command to both devices, 0x2 to for only dev0, 0x1 for dev1",
              2, old_value_t.mrw_dev_selectn, new_value_t.mrw_dev_selectn };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Mode Register Write: LPDDR2-only version of MRS/EMRS\nBoot requirements\nThis register triggers a mode register write command. Multiple mode-register writes may be required by the coldboot sequence. Such commands should be parameterized in the BCT and written by the BootROM during coldboot.\nCommand trigger: MRW";
}

#define MRR_OFFSET 0xEC
#define MRR_UNDEFMASK 0x3F000000
union mrr_u {
    struct {
        unsigned int mrr_data:16;           /* data returned */
        unsigned int mrr_ma:8;              /* register address */
        unsigned int undefined_bits_24_29:6;
        unsigned int mrr_dev_selectn:2;     /* active-low chip-select, choose which device to send the command to. (enum for safety). 0 = ILLEGAL 1 = DEV1 2 = DEV0 3 = RESERVED */
    };

    u_int32_t reg32;
};

void EmcDev::fill_mrr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const mrr_u old_value_t = { .reg32 = value };
    const mrr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: mrr_data:16",
              "data returned",
              16, old_value_t.mrr_data, new_value_t.mrr_data };
    m_bit_details_model.bits.append(entry);
    entry = { "16: mrr_ma:8",
              "register address",
              8, old_value_t.mrr_ma, new_value_t.mrr_ma };
    m_bit_details_model.bits.append(entry);
    entry = { "24: undefined_bits_24_29:6", "", 6, old_value_t.undefined_bits_24_29, new_value_t.undefined_bits_24_29 };
    m_bit_details_model.bits.append(entry);
    entry = { "30: mrr_dev_selectn:2",
              "active-low chip-select, choose which device to send the command to. (enum for safety).\n0 = ILLEGAL\n1 = DEV1\n2 = DEV0\n3 = RESERVED",
              2, old_value_t.mrr_dev_selectn, new_value_t.mrr_dev_selectn };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Mode Register Read: LPDDR2 only\nSequence\n1. read MRR until EMC_STATUS.MRR_DIVLD=0 (ok to skip if it is sure there is no pending MRR reads)\n2. write this register with the desired addr (MA) and device (DEV_SELECTN), device needs to be either DEV0 or DEV1: writing to both is illegal\n3. poll EMC_STATUS.MRR_DIVLD=1, or if using interrupt, wait for MRR_DIVLD_INT\n4. read back MRR. The value is in MRR_DATA field.\nNote: New MRR requests may be issued while there are on-going requests. e.g. to issue 3 MRR, follow these steps: 1,2,2,2,3,4,3,4,3,4. Data read back in step 4 are in the same order requested in step 2.\nTo make sure EMC is available for new MRR requests, poll for EMC_STATUS.MRR_FIFO_SPACE > 0 before step 2.\n If using 2 x16 DRAM, MRR_DATA[15:8] can be used to store MRR from 2nd DRAM on same CS (configured via CFG_2.MRR_BYTESEL_X16)\nCommand trigger: MRR";
}

#define FBIO_CFG1_OFFSET 0xF4
#define FBIO_CFG1_UNDEFMASK 0xFFFEFFFF
union fbio_cfg1_u {
    struct {
        unsigned int undefined_bits_0_15:16;
        unsigned int cfg_den_early:1;       /* determines whether the output enable is the same width as data (DEN_EARLY=0) or 1/2 bit time wider on either end (DEN_EARLY=1). 0 = DISABLE 1 = ENABLE */
        unsigned int undefined_bits_17_31:15;
    };

    u_int32_t reg32;
};

void EmcDev::fill_fbio_cfg1_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const fbio_cfg1_u old_value_t = { .reg32 = value };
    const fbio_cfg1_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_15:16", "", 16, old_value_t.undefined_bits_0_15, new_value_t.undefined_bits_0_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: cfg_den_early:1",
              "determines whether the output enable is the same width as data (DEN_EARLY=0) or 1/2 bit time wider on either end (DEN_EARLY=1).\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.cfg_den_early, new_value_t.cfg_den_early };
    m_bit_details_model.bits.append(entry);
    entry = { "17: undefined_bits_17_31:15", "", 15, old_value_t.undefined_bits_17_31, new_value_t.undefined_bits_17_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "The FBIO_CFG1 register controls the width of the DQ enable window when driving write data.\nBoot requirements\n    * This register should be parameterized in the BCT and written by the BootROM during coldboot.\n    * This register should be saved in the scratch registers and restored by the BootROM during warmboot.\nFBIO Configuration Register";
}

#define FBIO_DQSIB_DLY_OFFSET 0xF8
#define FBIO_DQSIB_DLY_UNDEFMASK 0x00000000
union fbio_dqsib_dly_u {
    struct {
        unsigned int cfg_dqsib_dly_byte_0:8;
        unsigned int cfg_dqsib_dly_byte_1:8;
        unsigned int cfg_dqsib_dly_byte_2:8;
        unsigned int cfg_dqsib_dly_byte_3:8;
    };

    u_int32_t reg32;
};

void EmcDev::fill_fbio_dqsib_dly_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const fbio_dqsib_dly_u old_value_t = { .reg32 = value };
    const fbio_dqsib_dly_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: cfg_dqsib_dly_byte_0:8", "", 8, old_value_t.cfg_dqsib_dly_byte_0, new_value_t.cfg_dqsib_dly_byte_0 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: cfg_dqsib_dly_byte_1:8", "", 8, old_value_t.cfg_dqsib_dly_byte_1, new_value_t.cfg_dqsib_dly_byte_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: cfg_dqsib_dly_byte_2:8", "", 8, old_value_t.cfg_dqsib_dly_byte_2, new_value_t.cfg_dqsib_dly_byte_2 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: cfg_dqsib_dly_byte_3:8", "", 8, old_value_t.cfg_dqsib_dly_byte_3, new_value_t.cfg_dqsib_dly_byte_3 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "The FBIO_DQSIB_DELAY register sets the trimmers for inbound dqs delay on each of the inbound byte lanes.\n This register is shadowed.\nBoot requirements\n    * This register should be parameterized in the BCT and written by the BootROM during coldboot.\n    * This register should be saved in the scratch registers and restored by the BootROM during warmboot.\nFBIO Configuration Register";
}

#define FBIO_DQSIB_DLY_MSB_OFFSET 0xFC
#define FBIO_DQSIB_DLY_MSB_UNDEFMASK 0xFCFCFCFC
union fbio_dqsib_dly_msb_u {
    struct {
        unsigned int cfg_dqsib_dly_msb_byte_0:2;
        unsigned int undefined_bits_2_7:6;
        unsigned int cfg_dqsib_dly_msb_byte_1:2;
        unsigned int undefined_bits_10_15:6;
        unsigned int cfg_dqsib_dly_msb_byte_2:2;
        unsigned int undefined_bits_18_23:6;
        unsigned int cfg_dqsib_dly_msb_byte_3:2;
        unsigned int undefined_bits_26_31:6;
    };

    u_int32_t reg32;
};

void EmcDev::fill_fbio_dqsib_dly_msb_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const fbio_dqsib_dly_msb_u old_value_t = { .reg32 = value };
    const fbio_dqsib_dly_msb_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: cfg_dqsib_dly_msb_byte_0:2", "", 2, old_value_t.cfg_dqsib_dly_msb_byte_0, new_value_t.cfg_dqsib_dly_msb_byte_0 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: undefined_bits_2_7:6", "", 6, old_value_t.undefined_bits_2_7, new_value_t.undefined_bits_2_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: cfg_dqsib_dly_msb_byte_1:2", "", 2, old_value_t.cfg_dqsib_dly_msb_byte_1, new_value_t.cfg_dqsib_dly_msb_byte_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "10: undefined_bits_10_15:6", "", 6, old_value_t.undefined_bits_10_15, new_value_t.undefined_bits_10_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: cfg_dqsib_dly_msb_byte_2:2", "", 2, old_value_t.cfg_dqsib_dly_msb_byte_2, new_value_t.cfg_dqsib_dly_msb_byte_2 };
    m_bit_details_model.bits.append(entry);
    entry = { "18: undefined_bits_18_23:6", "", 6, old_value_t.undefined_bits_18_23, new_value_t.undefined_bits_18_23 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: cfg_dqsib_dly_msb_byte_3:2", "", 2, old_value_t.cfg_dqsib_dly_msb_byte_3, new_value_t.cfg_dqsib_dly_msb_byte_3 };
    m_bit_details_model.bits.append(entry);
    entry = { "26: undefined_bits_26_31:6", "", 6, old_value_t.undefined_bits_26_31, new_value_t.undefined_bits_26_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "FBIO_DQSIB_DLY_MSB contains the most-significant-bits of values in FBIO_DQSIB_DLY.\n This register is shadowed.\nBoot requirements\n    * This register should be parameterized in the BCT and written by the BootROM during coldboot.\n    * This register should be saved in the scratch registers and restored by the BootROM during warmboot.\nFBIO Configuration Register";
}

#define FBIO_CFG5_OFFSET 0x104
#define FBIO_CFG5_UNDEFMASK 0xFFFFF86C
union fbio_cfg5_u {
    struct {
        unsigned int dram_type:2;           /* specifies which DRAM protocol to use for the attached device(s). 0 = RESERVED 1 = DDR1 2 = LPDDR2 3 = DDR2 */
        unsigned int undefined_bits_2_3:2;
        unsigned int dram_width:1;          /* specifies whether the DRAM data-bus is 16-bits or 32-bits wide. 0 = X32 1 = X16 */
        unsigned int undefined_bits_5_6:2;
        unsigned int differential_dqs:1;    /* enables differential signalling on dqs strobes (lpddr2/ddr2 options) 0 = DISABLED 1 = ENABLED */
        unsigned int ctt_termination:1;     /* enables CTT_TERMINATION mode in pads (ddr2 support) 0 = DISABLED 1 = ENABLED */
        unsigned int dqs_pulld:1;           /* enables pulldowns on dqs lines (and pullups on DQS_N if DIFFERENTIAL_DQS). 0 = DISABLED 1 = ENABLED */
        unsigned int disable_concurrent_autopre:1;/* disables reads/writes to a device until the precharge command has been issued by the dram internally. 0 = DISABLED 1 = ENABLED */
        unsigned int undefined_bits_11_31:21;
    };

    u_int32_t reg32;
};

void EmcDev::fill_fbio_cfg5_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const fbio_cfg5_u old_value_t = { .reg32 = value };
    const fbio_cfg5_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: dram_type:2",
              "specifies which DRAM protocol to use for the attached device(s).\n0 = RESERVED\n1 = DDR1\n2 = LPDDR2\n3 = DDR2",
              2, old_value_t.dram_type, new_value_t.dram_type };
    m_bit_details_model.bits.append(entry);
    entry = { "02: undefined_bits_2_3:2", "", 2, old_value_t.undefined_bits_2_3, new_value_t.undefined_bits_2_3 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: dram_width:1",
              "specifies whether the DRAM data-bus is 16-bits or 32-bits wide.\n0 = X32\n1 = X16",
              1, old_value_t.dram_width, new_value_t.dram_width };
    m_bit_details_model.bits.append(entry);
    entry = { "05: undefined_bits_5_6:2", "", 2, old_value_t.undefined_bits_5_6, new_value_t.undefined_bits_5_6 };
    m_bit_details_model.bits.append(entry);
    entry = { "07: differential_dqs:1",
              "enables differential signalling on dqs strobes (lpddr2/ddr2 options)\n0 = DISABLED\n1 = ENABLED",
              1, old_value_t.differential_dqs, new_value_t.differential_dqs };
    m_bit_details_model.bits.append(entry);
    entry = { "08: ctt_termination:1",
              "enables CTT_TERMINATION mode in pads (ddr2 support)\n0 = DISABLED\n1 = ENABLED",
              1, old_value_t.ctt_termination, new_value_t.ctt_termination };
    m_bit_details_model.bits.append(entry);
    entry = { "09: dqs_pulld:1",
              "enables pulldowns on dqs lines (and pullups on DQS_N if DIFFERENTIAL_DQS).\n0 = DISABLED\n1 = ENABLED",
              1, old_value_t.dqs_pulld, new_value_t.dqs_pulld };
    m_bit_details_model.bits.append(entry);
    entry = { "10: disable_concurrent_autopre:1",
              "disables reads/writes to a device until the precharge command has been issued by the dram internally.\n0 = DISABLED\n1 = ENABLED",
              1, old_value_t.disable_concurrent_autopre, new_value_t.disable_concurrent_autopre };
    m_bit_details_model.bits.append(entry);
    entry = { "11: undefined_bits_11_31:21", "", 21, old_value_t.undefined_bits_11_31, new_value_t.undefined_bits_11_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "The FBIO_CFG5 register controls the FBIO I/O cells.\nThe following fields are shadowed: DIFFERENTIAL_DQS, CTT_TERMINATION, DQS_PULLD.\n Writes to these fields will not take effect until the active value is updated via TIMING_UPDATE or (if enabled) CLKCHANGE_REQ.\nBoot requirements\n    * This register (except for field DISABLE_CONCURRENT_AUTOPRE) should be parameterized in the BCT and written by the BootROM during coldboot.\n    * This register (except for field DISABLE_CONCURRENT_AUTOPRE) should be saved in the scratch registers and restored by the BootROM during warmboot.\nFBIO Configuration Register";
}

#define FBIO_QUSE_DLY_OFFSET 0x10C
#define FBIO_QUSE_DLY_UNDEFMASK 0x00000000
union fbio_quse_dly_u {
    struct {
        unsigned int cfg_quse_dly_byte_0:8;
        unsigned int cfg_quse_dly_byte_1:8;
        unsigned int cfg_quse_dly_byte_2:8;
        unsigned int cfg_quse_dly_byte_3:8;
    };

    u_int32_t reg32;
};

void EmcDev::fill_fbio_quse_dly_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const fbio_quse_dly_u old_value_t = { .reg32 = value };
    const fbio_quse_dly_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: cfg_quse_dly_byte_0:8", "", 8, old_value_t.cfg_quse_dly_byte_0, new_value_t.cfg_quse_dly_byte_0 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: cfg_quse_dly_byte_1:8", "", 8, old_value_t.cfg_quse_dly_byte_1, new_value_t.cfg_quse_dly_byte_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: cfg_quse_dly_byte_2:8", "", 8, old_value_t.cfg_quse_dly_byte_2, new_value_t.cfg_quse_dly_byte_2 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: cfg_quse_dly_byte_3:8", "", 8, old_value_t.cfg_quse_dly_byte_3, new_value_t.cfg_quse_dly_byte_3 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "QUSE_LATE and QUSE_DLY determine how much added delay fbio should add to the QUSE path. QUSE needs to align (approximately) with the incoming DQS (DDR1) in order to qualify it, since the incoming DQS/feedback clock is not always valid.\nDRAMC can position QUSE with m2clk granularity (2 bit times). For DDR1 only, QUSE_LATE provides finer granularity of 1/2 an m4clk cycle (1/2 bit time). The amount of delay we add will be primarily a function of the round trip wire delay to/from the DRAM. Other portions of the delay (driver and receiver delay) are compensated for by delay through a non-bonded QUSE pad cell.\nQUSE_DLY controls trimmers in each byte lane. This also allows for variation in the propagation delay from the \"common\" pad macro where the QUSE logic lives out to each of the 4 byte lanes.\nThis register is shadowed.\nBoot requirements\n    * This register should be parameterized in the BCT and written by the BootROM during coldboot.\n    * This register should be saved in the scratch registers and restored by the BootROM during warmboot.\nFBIO Configuration Register";
}

#define FBIO_QUSE_DLY_MSB_OFFSET 0x110
#define FBIO_QUSE_DLY_MSB_UNDEFMASK 0xFCFCFCFC
union fbio_quse_dly_msb_u {
    struct {
        unsigned int cfg_quse_dly_msb_byte_0:2;
        unsigned int undefined_bits_2_7:6;
        unsigned int cfg_quse_dly_msb_byte_1:2;
        unsigned int undefined_bits_10_15:6;
        unsigned int cfg_quse_dly_msb_byte_2:2;
        unsigned int undefined_bits_18_23:6;
        unsigned int cfg_quse_dly_msb_byte_3:2;
        unsigned int undefined_bits_26_31:6;
    };

    u_int32_t reg32;
};

void EmcDev::fill_fbio_quse_dly_msb_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const fbio_quse_dly_msb_u old_value_t = { .reg32 = value };
    const fbio_quse_dly_msb_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: cfg_quse_dly_msb_byte_0:2", "", 2, old_value_t.cfg_quse_dly_msb_byte_0, new_value_t.cfg_quse_dly_msb_byte_0 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: undefined_bits_2_7:6", "", 6, old_value_t.undefined_bits_2_7, new_value_t.undefined_bits_2_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: cfg_quse_dly_msb_byte_1:2", "", 2, old_value_t.cfg_quse_dly_msb_byte_1, new_value_t.cfg_quse_dly_msb_byte_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "10: undefined_bits_10_15:6", "", 6, old_value_t.undefined_bits_10_15, new_value_t.undefined_bits_10_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: cfg_quse_dly_msb_byte_2:2", "", 2, old_value_t.cfg_quse_dly_msb_byte_2, new_value_t.cfg_quse_dly_msb_byte_2 };
    m_bit_details_model.bits.append(entry);
    entry = { "18: undefined_bits_18_23:6", "", 6, old_value_t.undefined_bits_18_23, new_value_t.undefined_bits_18_23 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: cfg_quse_dly_msb_byte_3:2", "", 2, old_value_t.cfg_quse_dly_msb_byte_3, new_value_t.cfg_quse_dly_msb_byte_3 };
    m_bit_details_model.bits.append(entry);
    entry = { "26: undefined_bits_26_31:6", "", 6, old_value_t.undefined_bits_26_31, new_value_t.undefined_bits_26_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "FBIO_QUSE_DLY_MSB contains the most-significant-bits of values in FBIO_QUSE_DLY\nThis register is shadowed.\nBoot requirements\n    * This register should be parameterized in the BCT and written by the BootROM during coldboot.\n    * This register should be saved in the scratch registers and restored by the BootROM during warmboot.\nFBIO Configuration Register";
}

#define FBIO_CFG6_OFFSET 0x114
#define FBIO_CFG6_UNDEFMASK 0xFFFFFFF8
union fbio_cfg6_u {
    struct {
        unsigned int cfg_quse_late:3;
        unsigned int undefined_bits_3_31:29;
    };

    u_int32_t reg32;
};

void EmcDev::fill_fbio_cfg6_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const fbio_cfg6_u old_value_t = { .reg32 = value };
    const fbio_cfg6_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: cfg_quse_late:3", "", 3, old_value_t.cfg_quse_late, new_value_t.cfg_quse_late };
    m_bit_details_model.bits.append(entry);
    entry = { "03: undefined_bits_3_31:29", "", 29, old_value_t.undefined_bits_3_31, new_value_t.undefined_bits_3_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Boot requirements\n    * This register should be parameterized in the BCT and written by the BootROM during coldboot.\n    * This register should be saved in the scratch registers and restored by the BootROM during warmboot.\nFBIO Configuration Register";
}

#define DQS_TRIMMER_RD0_OFFSET 0x120
#define DQS_TRIMMER_RD0_UNDEFMASK 0xFC00FC00
union dqs_trimmer_rd0_u {
    struct {
        unsigned int quse_current_trim_val_byte_0:10;
        unsigned int undefined_bits_10_15:6;
        unsigned int dqs_current_trim_val_byte_0:10;
        unsigned int undefined_bits_26_31:6;
    };

    u_int32_t reg32;
};

void EmcDev::fill_dqs_trimmer_rd0_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const dqs_trimmer_rd0_u old_value_t = { .reg32 = value };
    const dqs_trimmer_rd0_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: quse_current_trim_val_byte_0:10", "", 10, old_value_t.quse_current_trim_val_byte_0, new_value_t.quse_current_trim_val_byte_0 };
    m_bit_details_model.bits.append(entry);
    entry = { "10: undefined_bits_10_15:6", "", 6, old_value_t.undefined_bits_10_15, new_value_t.undefined_bits_10_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: dqs_current_trim_val_byte_0:10", "", 10, old_value_t.dqs_current_trim_val_byte_0, new_value_t.dqs_current_trim_val_byte_0 };
    m_bit_details_model.bits.append(entry);
    entry = { "26: undefined_bits_26_31:6", "", 6, old_value_t.undefined_bits_26_31, new_value_t.undefined_bits_26_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "The DQS_TRIMMER_RD registers provide a way to observe the values being used by the trimmers";
}

#define DQS_TRIMMER_RD1_OFFSET 0x124
#define DQS_TRIMMER_RD1_UNDEFMASK 0xFC00FC00
union dqs_trimmer_rd1_u {
    struct {
        unsigned int quse_current_trim_val_byte_1:10;
        unsigned int undefined_bits_10_15:6;
        unsigned int dqs_current_trim_val_byte_1:10;
        unsigned int undefined_bits_26_31:6;
    };

    u_int32_t reg32;
};

void EmcDev::fill_dqs_trimmer_rd1_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const dqs_trimmer_rd1_u old_value_t = { .reg32 = value };
    const dqs_trimmer_rd1_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: quse_current_trim_val_byte_1:10", "", 10, old_value_t.quse_current_trim_val_byte_1, new_value_t.quse_current_trim_val_byte_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "10: undefined_bits_10_15:6", "", 6, old_value_t.undefined_bits_10_15, new_value_t.undefined_bits_10_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: dqs_current_trim_val_byte_1:10", "", 10, old_value_t.dqs_current_trim_val_byte_1, new_value_t.dqs_current_trim_val_byte_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "26: undefined_bits_26_31:6", "", 6, old_value_t.undefined_bits_26_31, new_value_t.undefined_bits_26_31 };
    m_bit_details_model.bits.append(entry);
}

#define DQS_TRIMMER_RD2_OFFSET 0x128
#define DQS_TRIMMER_RD2_UNDEFMASK 0xFC00FC00
union dqs_trimmer_rd2_u {
    struct {
        unsigned int quse_current_trim_val_byte_2:10;
        unsigned int undefined_bits_10_15:6;
        unsigned int dqs_current_trim_val_byte_2:10;
        unsigned int undefined_bits_26_31:6;
    };

    u_int32_t reg32;
};

void EmcDev::fill_dqs_trimmer_rd2_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const dqs_trimmer_rd2_u old_value_t = { .reg32 = value };
    const dqs_trimmer_rd2_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: quse_current_trim_val_byte_2:10", "", 10, old_value_t.quse_current_trim_val_byte_2, new_value_t.quse_current_trim_val_byte_2 };
    m_bit_details_model.bits.append(entry);
    entry = { "10: undefined_bits_10_15:6", "", 6, old_value_t.undefined_bits_10_15, new_value_t.undefined_bits_10_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: dqs_current_trim_val_byte_2:10", "", 10, old_value_t.dqs_current_trim_val_byte_2, new_value_t.dqs_current_trim_val_byte_2 };
    m_bit_details_model.bits.append(entry);
    entry = { "26: undefined_bits_26_31:6", "", 6, old_value_t.undefined_bits_26_31, new_value_t.undefined_bits_26_31 };
    m_bit_details_model.bits.append(entry);
}

#define DQS_TRIMMER_RD3_OFFSET 0x12C
#define DQS_TRIMMER_RD3_UNDEFMASK 0xFC00FC00
union dqs_trimmer_rd3_u {
    struct {
        unsigned int quse_current_trim_val_byte_3:10;
        unsigned int undefined_bits_10_15:6;
        unsigned int dqs_current_trim_val_byte_3:10;
        unsigned int undefined_bits_26_31:6;
    };

    u_int32_t reg32;
};

void EmcDev::fill_dqs_trimmer_rd3_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const dqs_trimmer_rd3_u old_value_t = { .reg32 = value };
    const dqs_trimmer_rd3_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: quse_current_trim_val_byte_3:10", "", 10, old_value_t.quse_current_trim_val_byte_3, new_value_t.quse_current_trim_val_byte_3 };
    m_bit_details_model.bits.append(entry);
    entry = { "10: undefined_bits_10_15:6", "", 6, old_value_t.undefined_bits_10_15, new_value_t.undefined_bits_10_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: dqs_current_trim_val_byte_3:10", "", 10, old_value_t.dqs_current_trim_val_byte_3, new_value_t.dqs_current_trim_val_byte_3 };
    m_bit_details_model.bits.append(entry);
    entry = { "26: undefined_bits_26_31:6", "", 6, old_value_t.undefined_bits_26_31, new_value_t.undefined_bits_26_31 };
    m_bit_details_model.bits.append(entry);
}

#define LL_ARB_CONFIG_OFFSET 0x144
#define LL_ARB_CONFIG_UNDEFMASK 0xC0FF0EF0
union ll_arb_config_u {
    struct {
        unsigned int die_off_exp:4;
        unsigned int undefined_bits_4_7:4;
        unsigned int allow_idle_insert:1;   /* 0 = DISABLED 1 = ENABLED */
        unsigned int undefined_bits_9_11:3;
        unsigned int max_ll_greed:4;
        unsigned int undefined_bits_16_23:8;
        unsigned int ll_greed_diff_bank_disable:1;/* set to one to get AP15 behavior */
        unsigned int ll_greed_diff_bank_after_disable:1;/* set to one to get AP15 behavior */
        unsigned int ll_force_insert_wr_disable:1;/* set to one to get AP15 behavior */
        unsigned int ll_insert_diff_bank_before_disable:1;/* set to one to get AP15 behavior */
        unsigned int ll_insert_diff_bank_after_toggle:1;/* set to one to get AP15 behavior */
        unsigned int ll_insert_diff_bank_after_remove:1;/* set to zero to get AP15 behavior */
        unsigned int undefined_bits_30_31:2;
    };

    u_int32_t reg32;
};

void EmcDev::fill_ll_arb_config_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const ll_arb_config_u old_value_t = { .reg32 = value };
    const ll_arb_config_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: die_off_exp:4", "", 4, old_value_t.die_off_exp, new_value_t.die_off_exp };
    m_bit_details_model.bits.append(entry);
    entry = { "04: undefined_bits_4_7:4", "", 4, old_value_t.undefined_bits_4_7, new_value_t.undefined_bits_4_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: allow_idle_insert:1",
              "0 = DISABLED\n1 = ENABLED",
              1, old_value_t.allow_idle_insert, new_value_t.allow_idle_insert };
    m_bit_details_model.bits.append(entry);
    entry = { "09: undefined_bits_9_11:3", "", 3, old_value_t.undefined_bits_9_11, new_value_t.undefined_bits_9_11 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: max_ll_greed:4", "", 4, old_value_t.max_ll_greed, new_value_t.max_ll_greed };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_23:8", "", 8, old_value_t.undefined_bits_16_23, new_value_t.undefined_bits_16_23 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: ll_greed_diff_bank_disable:1",
              "set to one to get AP15 behavior",
              1, old_value_t.ll_greed_diff_bank_disable, new_value_t.ll_greed_diff_bank_disable };
    m_bit_details_model.bits.append(entry);
    entry = { "25: ll_greed_diff_bank_after_disable:1",
              "set to one to get AP15 behavior",
              1, old_value_t.ll_greed_diff_bank_after_disable, new_value_t.ll_greed_diff_bank_after_disable };
    m_bit_details_model.bits.append(entry);
    entry = { "26: ll_force_insert_wr_disable:1",
              "set to one to get AP15 behavior",
              1, old_value_t.ll_force_insert_wr_disable, new_value_t.ll_force_insert_wr_disable };
    m_bit_details_model.bits.append(entry);
    entry = { "27: ll_insert_diff_bank_before_disable:1",
              "set to one to get AP15 behavior",
              1, old_value_t.ll_insert_diff_bank_before_disable, new_value_t.ll_insert_diff_bank_before_disable };
    m_bit_details_model.bits.append(entry);
    entry = { "28: ll_insert_diff_bank_after_toggle:1",
              "set to one to get AP15 behavior",
              1, old_value_t.ll_insert_diff_bank_after_toggle, new_value_t.ll_insert_diff_bank_after_toggle };
    m_bit_details_model.bits.append(entry);
    entry = { "29: ll_insert_diff_bank_after_remove:1",
              "set to zero to get AP15 behavior",
              1, old_value_t.ll_insert_diff_bank_after_remove, new_value_t.ll_insert_diff_bank_after_remove };
    m_bit_details_model.bits.append(entry);
    entry = { "30: undefined_bits_30_31:2", "", 2, old_value_t.undefined_bits_30_31, new_value_t.undefined_bits_30_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Configuration of arbiter between regular MC path and low-latency path.\nDIE_OFF_EXP: Exponent of the die-off factor, which is used to calculate the average load of the regular data transaction path. Valid values are from 0 to 8. The die-off factor is calculated as 1 / (2^DIE_OFF_EXP).\n0: Only the last transaction is used to calculated the load\n8: minimal exponential die-off factor of 1/256\nALLOW_IDLE_INSERT: If enabled, arbiter would allow a low-latency request when the MC<=>EMC path is idle. If disabled, the low-latency request would wait till the insertion delay programed.\nMAX_LL_GREED: Specify the maximum number of consecutive 256-bit transactions the low-latency path is allowed to perform. The amount of transactions is not only limited by this number: transactions also have to be in the same page and in the same direction as the previous one.\nFor streaming read and write operations, where this is the most useful, transactions will switch page every 64 bytes, due to the location of the bank bits in the address. The greed counter has a granularity of 32 bytes, so in practise, the only practically useful numbers are 1 and 2.\nIn addition to allowing scheduling a consecutive transaction, the greed counter also guarantees that autopc will be issued at the end of the programmed number of consecutive writes.\nPotential values:\n0: 1 transaction executed at a time. When the next transaction (already in FIFO) is to the same page, autopc will not be set.\n1: 1 transaction executed at a time. Autopc will always be issued.\n2: 2 transactions can be executed, if they go to the same page. Autopc is issued at the end of the 2nd transaction or after the first one if there is no second transaction.\n3 and higher: Same as 2, but for more transactions. In practice, this will not happen since the address mapping is such that bank changes after 2 transactions.\nBoot requirements\n    * This arbitration configuration register should be parameterized in the BCT and written by the OS during coldboot and warmboot.\nLOW-LATENCY Arbiter Configuration";
}

#define T_MIN_CRITICAL_HP_OFFSET 0x148
#define T_MIN_CRITICAL_HP_UNDEFMASK 0x00000000
union t_min_critical_hp_u {
    struct {
        unsigned int t_min_crit_hp_0:8;
        unsigned int t_min_crit_hp_1:8;
        unsigned int t_min_crit_hp_2:8;
        unsigned int t_min_crit_hp_3:8;
    };

    u_int32_t reg32;
};

void EmcDev::fill_t_min_critical_hp_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const t_min_critical_hp_u old_value_t = { .reg32 = value };
    const t_min_critical_hp_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: t_min_crit_hp_0:8", "", 8, old_value_t.t_min_crit_hp_0, new_value_t.t_min_crit_hp_0 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: t_min_crit_hp_1:8", "", 8, old_value_t.t_min_crit_hp_1, new_value_t.t_min_crit_hp_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: t_min_crit_hp_2:8", "", 8, old_value_t.t_min_crit_hp_2, new_value_t.t_min_crit_hp_2 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: t_min_crit_hp_3:8", "", 8, old_value_t.t_min_crit_hp_3, new_value_t.t_min_crit_hp_3 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Configuration table with low-latency insertion delay based on the criticality level inside the MC. Agents inside the MC that can indicate critical status. Depending on the number of agents that are currently in critical status, a minimum value can be programmed before which a low-latency transfer is allowed.\n There are 4 levels for high priority: 0, 1, 2, 3_or_more\nBoot requirements\n    * This arbitration configuration register should be parameterized in the BCT and written by the OS during coldboot and warmboot.\nLOW-LATENCY Arbiter Configuration";
}

#define T_MIN_CRITICAL_TIMEOUT_OFFSET 0x14C
#define T_MIN_CRITICAL_TIMEOUT_UNDEFMASK 0x00000000
union t_min_critical_timeout_u {
    struct {
        unsigned int t_min_crit_timeout_0:8;
        unsigned int t_min_crit_timeout_1:8;
        unsigned int t_min_crit_timeout_2:8;
        unsigned int t_min_crit_timeout_3:8;
    };

    u_int32_t reg32;
};

void EmcDev::fill_t_min_critical_timeout_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const t_min_critical_timeout_u old_value_t = { .reg32 = value };
    const t_min_critical_timeout_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: t_min_crit_timeout_0:8", "", 8, old_value_t.t_min_crit_timeout_0, new_value_t.t_min_crit_timeout_0 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: t_min_crit_timeout_1:8", "", 8, old_value_t.t_min_crit_timeout_1, new_value_t.t_min_crit_timeout_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: t_min_crit_timeout_2:8", "", 8, old_value_t.t_min_crit_timeout_2, new_value_t.t_min_crit_timeout_2 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: t_min_crit_timeout_3:8", "", 8, old_value_t.t_min_crit_timeout_3, new_value_t.t_min_crit_timeout_3 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "There are 4 levels for timeout: 0, 1, 2, 3_or_more\nBoot requirements\n    * This arbitration configuration register should be parameterized in the BCT and written by the OS during coldboot and warmboot.\nLOW-LATENCY Arbiter Configuration";
}

#define T_MIN_LOAD_OFFSET 0x150
#define T_MIN_LOAD_UNDEFMASK 0x00000000
union t_min_load_u {
    struct {
        unsigned int t_min_load_0:8;
        unsigned int t_min_load_1:8;
        unsigned int t_min_load_2:8;
        unsigned int t_min_load_3:8;
    };

    u_int32_t reg32;
};

void EmcDev::fill_t_min_load_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const t_min_load_u old_value_t = { .reg32 = value };
    const t_min_load_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: t_min_load_0:8", "", 8, old_value_t.t_min_load_0, new_value_t.t_min_load_0 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: t_min_load_1:8", "", 8, old_value_t.t_min_load_1, new_value_t.t_min_load_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: t_min_load_2:8", "", 8, old_value_t.t_min_load_2, new_value_t.t_min_load_2 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: t_min_load_3:8", "", 8, old_value_t.t_min_load_3, new_value_t.t_min_load_3 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "There are 4 level of (time averaged) load. For each of those levels, a different minimum low-latency hold-off value can be programmed.\nBoot requirements\n    * This arbitration configuration register should be parameterized in the BCT and written by the OS during coldboot and warmboot.\nLOW-LATENCY Arbiter Configuration";
}

#define T_MAX_CRITICAL_HP_OFFSET 0x154
#define T_MAX_CRITICAL_HP_UNDEFMASK 0x00000000
union t_max_critical_hp_u {
    struct {
        unsigned int t_max_crit_hp_0:8;
        unsigned int t_max_crit_hp_1:8;
        unsigned int t_max_crit_hp_2:8;
        unsigned int t_max_crit_hp_3:8;
    };

    u_int32_t reg32;
};

void EmcDev::fill_t_max_critical_hp_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const t_max_critical_hp_u old_value_t = { .reg32 = value };
    const t_max_critical_hp_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: t_max_crit_hp_0:8", "", 8, old_value_t.t_max_crit_hp_0, new_value_t.t_max_crit_hp_0 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: t_max_crit_hp_1:8", "", 8, old_value_t.t_max_crit_hp_1, new_value_t.t_max_crit_hp_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: t_max_crit_hp_2:8", "", 8, old_value_t.t_max_crit_hp_2, new_value_t.t_max_crit_hp_2 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: t_max_crit_hp_3:8", "", 8, old_value_t.t_max_crit_hp_3, new_value_t.t_max_crit_hp_3 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Maximum hold-off time for a given criticality in the MC.\nBoot requirements\n    * This arbitration configuration register should be parameterized in the BCT and written by the OS during coldboot and warmboot.\nLOW-LATENCY Arbiter Configuration";
}

#define T_MAX_CRITICAL_TIMEOUT_OFFSET 0x158
#define T_MAX_CRITICAL_TIMEOUT_UNDEFMASK 0x00000000
union t_max_critical_timeout_u {
    struct {
        unsigned int t_max_crit_timeout_0:8;
        unsigned int t_max_crit_timeout_1:8;
        unsigned int t_max_crit_timeout_2:8;
        unsigned int t_max_crit_timeout_3:8;
    };

    u_int32_t reg32;
};

void EmcDev::fill_t_max_critical_timeout_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const t_max_critical_timeout_u old_value_t = { .reg32 = value };
    const t_max_critical_timeout_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: t_max_crit_timeout_0:8", "", 8, old_value_t.t_max_crit_timeout_0, new_value_t.t_max_crit_timeout_0 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: t_max_crit_timeout_1:8", "", 8, old_value_t.t_max_crit_timeout_1, new_value_t.t_max_crit_timeout_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: t_max_crit_timeout_2:8", "", 8, old_value_t.t_max_crit_timeout_2, new_value_t.t_max_crit_timeout_2 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: t_max_crit_timeout_3:8", "", 8, old_value_t.t_max_crit_timeout_3, new_value_t.t_max_crit_timeout_3 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Boot requirements\n    * This arbitration configuration register should be parameterized in the BCT and written by the OS during coldboot and warmboot.\nLOW-LATENCY Arbiter Configuration";
}

#define T_MAX_LOAD_OFFSET 0x15C
#define T_MAX_LOAD_UNDEFMASK 0x00000000
union t_max_load_u {
    struct {
        unsigned int t_max_load_0:8;
        unsigned int t_max_load_1:8;
        unsigned int t_max_load_2:8;
        unsigned int t_max_load_3:8;
    };

    u_int32_t reg32;
};

void EmcDev::fill_t_max_load_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const t_max_load_u old_value_t = { .reg32 = value };
    const t_max_load_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: t_max_load_0:8", "", 8, old_value_t.t_max_load_0, new_value_t.t_max_load_0 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: t_max_load_1:8", "", 8, old_value_t.t_max_load_1, new_value_t.t_max_load_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: t_max_load_2:8", "", 8, old_value_t.t_max_load_2, new_value_t.t_max_load_2 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: t_max_load_3:8", "", 8, old_value_t.t_max_load_3, new_value_t.t_max_load_3 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Maximum load dependent hold-off time\nBoot requirements\n    * This arbitration configuration register should be parameterized in the BCT and written by the OS during coldboot and warmboot.\nLOW-LATENCY Arbiter Configuration";
}

#define AUTO_CAL_CONFIG_OFFSET 0x2A4
#define AUTO_CAL_CONFIG_UNDEFMASK 0x0C00E0E0
union auto_cal_config_u {
    struct {
        unsigned int auto_cal_pu_offset:5;  /* 2's complement offset for pull-up value */
        unsigned int undefined_bits_5_7:3;
        unsigned int auto_cal_pd_offset:5;  /* 2's complement offset for pull-down value */
        unsigned int undefined_bits_13_15:3;
        unsigned int auto_cal_step:10;      /* Auto Cal calibration step interval (in emc clocks) - the default is set for 1.0us calibration step at 166MHz */
        unsigned int undefined_bits_26_27:2;
        unsigned int autocal_slw_override:1;/* 0 (Normal operation) pad DRVDN/UP_SLWR/F tied to AUTO_CAL output DRDVDN/UP_SLWR/F[3:0] = AUTO_CAL_PULLDOWN/UP[4:1] 1 (override) use CFG2TMC_*_DRVDN/UP_SLWR/F pins to control pad slew inputs */
        unsigned int auto_cal_enable:1;     /* 1 (normal operation): use EMC generated pullup/dn (override or autocal) 0 (disabled): use cfg2tmc_xm2* register settings for pullup/dn 0 = DISABLED 1 = ENABLED */
        unsigned int auto_cal_override:1;   /* 0 (normal operation): use AUTO_CAL_PU/PD_OFFSET as an offset to the calibration tate machine setting 1 (override) : use AUTO_CAL_PU/PD_OFFSET register values directly */
        unsigned int auto_cal_start:1;      /* Writing a one to this bit starts the calibration state machine. This bit must be set even if the override is set in order to latch in the override value */
    };

    u_int32_t reg32;
};

void EmcDev::fill_auto_cal_config_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const auto_cal_config_u old_value_t = { .reg32 = value };
    const auto_cal_config_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: auto_cal_pu_offset:5",
              "2's complement offset for pull-up value",
              5, old_value_t.auto_cal_pu_offset, new_value_t.auto_cal_pu_offset };
    m_bit_details_model.bits.append(entry);
    entry = { "05: undefined_bits_5_7:3", "", 3, old_value_t.undefined_bits_5_7, new_value_t.undefined_bits_5_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: auto_cal_pd_offset:5",
              "2's complement offset for pull-down value",
              5, old_value_t.auto_cal_pd_offset, new_value_t.auto_cal_pd_offset };
    m_bit_details_model.bits.append(entry);
    entry = { "13: undefined_bits_13_15:3", "", 3, old_value_t.undefined_bits_13_15, new_value_t.undefined_bits_13_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: auto_cal_step:10",
              "Auto Cal calibration step interval (in emc clocks) - the default is set for 1.0us calibration step at 166MHz",
              10, old_value_t.auto_cal_step, new_value_t.auto_cal_step };
    m_bit_details_model.bits.append(entry);
    entry = { "26: undefined_bits_26_27:2", "", 2, old_value_t.undefined_bits_26_27, new_value_t.undefined_bits_26_27 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: autocal_slw_override:1",
              "0 (Normal operation) pad DRVDN/UP_SLWR/F tied to AUTO_CAL output DRDVDN/UP_SLWR/F[3:0] = AUTO_CAL_PULLDOWN/UP[4:1] 1 (override) use CFG2TMC_*_DRVDN/UP_SLWR/F pins to control pad slew inputs",
              1, old_value_t.autocal_slw_override, new_value_t.autocal_slw_override };
    m_bit_details_model.bits.append(entry);
    entry = { "29: auto_cal_enable:1",
              "1 (normal operation): use EMC generated pullup/dn (override or autocal) 0 (disabled): use cfg2tmc_xm2* register settings for pullup/dn\n0 = DISABLED\n1 = ENABLED",
              1, old_value_t.auto_cal_enable, new_value_t.auto_cal_enable };
    m_bit_details_model.bits.append(entry);
    entry = { "30: auto_cal_override:1",
              "0 (normal operation): use AUTO_CAL_PU/PD_OFFSET as an offset to the calibration tate machine setting 1 (override) : use AUTO_CAL_PU/PD_OFFSET register values directly",
              1, old_value_t.auto_cal_override, new_value_t.auto_cal_override };
    m_bit_details_model.bits.append(entry);
    entry = { "31: auto_cal_start:1",
              "Writing a one to this bit starts the calibration state machine. This bit must be set even if the override is set in order to latch in the override value",
              1, old_value_t.auto_cal_start, new_value_t.auto_cal_start };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Boot requirements\n    * This register (except for AUTOCAL_SLW_OVERRIDE and AUTO_CAL_START(trigger)) should be parameterized in the BCT and written by the BootROM during coldboot.\n    * This register (except for AUTOCAL_SLW_OVERRIDE and AUTO_CAL_START(trigger)) should be saved in the scratch registers and restored by the BootROM during warmboot.\nAuto-calibration Settings for EMC Pads";
}

#define AUTO_CAL_INTERVAL_OFFSET 0x2A8
#define AUTO_CAL_INTERVAL_UNDEFMASK 0xF0000000
union auto_cal_interval_u {
    struct {
        unsigned int auto_cal_interval:28;  /* 0: do calibration once Otherwise, auto-calibration occurs at intervals equivalent to the programmed number of cycles */
        unsigned int undefined_bits_28_31:4;
    };

    u_int32_t reg32;
};

void EmcDev::fill_auto_cal_interval_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const auto_cal_interval_u old_value_t = { .reg32 = value };
    const auto_cal_interval_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: auto_cal_interval:28",
              "0: do calibration once Otherwise, auto-calibration occurs at intervals equivalent to the programmed number of cycles",
              28, old_value_t.auto_cal_interval, new_value_t.auto_cal_interval };
    m_bit_details_model.bits.append(entry);
    entry = { "28: undefined_bits_28_31:4", "", 4, old_value_t.undefined_bits_28_31, new_value_t.undefined_bits_28_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Boot requirements\n    * This register should be parameterized in the BCT and written by the BootROM during coldboot.\n    * This register should be saved in the scratch registers and restored by the BootROM during warmboot.\nEMC Pad Calibration Interval";
}

#define AUTO_CAL_STATUS_OFFSET 0x2AC
#define AUTO_CAL_STATUS_UNDEFMASK 0x60E0E0E0
union auto_cal_status_u {
    struct {
        unsigned int auto_cal_pullup:5;     /* Pullup code generated by auto-calibration */
        unsigned int undefined_bits_5_7:3;
        unsigned int auto_cal_pulldown:5;   /* Pulldown code generated by auto-calibration */
        unsigned int undefined_bits_13_15:3;
        unsigned int auto_cal_pullup_adj:5; /* Pullup code sent to pads */
        unsigned int undefined_bits_21_23:3;
        unsigned int auto_cal_pulldown_adj:5;/* Pulldown code sent to pads */
        unsigned int undefined_bits_29_30:2;
        unsigned int auto_cal_active:1;     /* One when auto calibrate is active - valid only after auto calibrate sequence has completed (EMC_CAL_ACTIVE == 0) */
    };

    u_int32_t reg32;
};

void EmcDev::fill_auto_cal_status_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const auto_cal_status_u old_value_t = { .reg32 = value };
    const auto_cal_status_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: auto_cal_pullup:5",
              "Pullup code generated by auto-calibration",
              5, old_value_t.auto_cal_pullup, new_value_t.auto_cal_pullup };
    m_bit_details_model.bits.append(entry);
    entry = { "05: undefined_bits_5_7:3", "", 3, old_value_t.undefined_bits_5_7, new_value_t.undefined_bits_5_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: auto_cal_pulldown:5",
              "Pulldown code generated by auto-calibration",
              5, old_value_t.auto_cal_pulldown, new_value_t.auto_cal_pulldown };
    m_bit_details_model.bits.append(entry);
    entry = { "13: undefined_bits_13_15:3", "", 3, old_value_t.undefined_bits_13_15, new_value_t.undefined_bits_13_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: auto_cal_pullup_adj:5",
              "Pullup code sent to pads",
              5, old_value_t.auto_cal_pullup_adj, new_value_t.auto_cal_pullup_adj };
    m_bit_details_model.bits.append(entry);
    entry = { "21: undefined_bits_21_23:3", "", 3, old_value_t.undefined_bits_21_23, new_value_t.undefined_bits_21_23 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: auto_cal_pulldown_adj:5",
              "Pulldown code sent to pads",
              5, old_value_t.auto_cal_pulldown_adj, new_value_t.auto_cal_pulldown_adj };
    m_bit_details_model.bits.append(entry);
    entry = { "29: undefined_bits_29_30:2", "", 2, old_value_t.undefined_bits_29_30, new_value_t.undefined_bits_29_30 };
    m_bit_details_model.bits.append(entry);
    entry = { "31: auto_cal_active:1",
              "One when auto calibrate is active - valid only after auto calibrate sequence has completed (EMC_CAL_ACTIVE == 0)",
              1, old_value_t.auto_cal_active, new_value_t.auto_cal_active };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "EMC pad calibration status";
}

#define REQ_CTRL_OFFSET 0x2B0
#define REQ_CTRL_UNDEFMASK 0xFFFFFFFC
union req_ctrl_u {
    struct {
        unsigned int stall_all_reads:1;     /* Stall incoming read transactions (1st non-LL read will stall all transactions) */
        unsigned int stall_all_writes:1;    /* Stall incoming write transactions */
        unsigned int undefined_bits_2_31:30;
    };

    u_int32_t reg32;
};

void EmcDev::fill_req_ctrl_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const req_ctrl_u old_value_t = { .reg32 = value };
    const req_ctrl_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: stall_all_reads:1",
              "Stall incoming read transactions (1st non-LL read will stall all transactions)",
              1, old_value_t.stall_all_reads, new_value_t.stall_all_reads };
    m_bit_details_model.bits.append(entry);
    entry = { "01: stall_all_writes:1",
              "Stall incoming write transactions",
              1, old_value_t.stall_all_writes, new_value_t.stall_all_writes };
    m_bit_details_model.bits.append(entry);
    entry = { "02: undefined_bits_2_31:30", "", 30, old_value_t.undefined_bits_2_31, new_value_t.undefined_bits_2_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Request status/control";
}

#define EMC_STATUS_OFFSET 0x2B4
#define EMC_STATUS_UNDEFMASK 0xFFE0CCC8
union emc_status_u {
    struct {
        unsigned int emc_req_fifo_empty:1;  /* Request fifo is empty */
        unsigned int emc_ll_req_fifo_empty:1;/* LL Request fifo is empty */
        unsigned int no_outstanding_transactions:1;/* All non-stalled requests have completed */
        unsigned int undefined_bit_3:1;
        unsigned int dram_in_powerdown:2;   /* dev[n] has entered powerdown state (incoming req's will awaken if not stalled) */
        unsigned int undefined_bits_6_7:2;
        unsigned int dram_in_self_refresh:2;/* dev[n] has been put into self-refresh (will remain until SR exit cmd) */
        unsigned int undefined_bits_10_11:2;
        unsigned int dram_in_dpd:2;         /* dev[n] has been put into deep powerdown state */
        unsigned int undefined_bits_14_15:2;
        unsigned int mrr_fifo_space:4;      /* mrr fifospace available */
        unsigned int mrr_divld:1;           /* mrr data available for reading */
        unsigned int undefined_bits_21_31:11;
    };

    u_int32_t reg32;
};

void EmcDev::fill_emc_status_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const emc_status_u old_value_t = { .reg32 = value };
    const emc_status_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: emc_req_fifo_empty:1",
              "Request fifo is empty",
              1, old_value_t.emc_req_fifo_empty, new_value_t.emc_req_fifo_empty };
    m_bit_details_model.bits.append(entry);
    entry = { "01: emc_ll_req_fifo_empty:1",
              "LL Request fifo is empty",
              1, old_value_t.emc_ll_req_fifo_empty, new_value_t.emc_ll_req_fifo_empty };
    m_bit_details_model.bits.append(entry);
    entry = { "02: no_outstanding_transactions:1",
              "All non-stalled requests have completed",
              1, old_value_t.no_outstanding_transactions, new_value_t.no_outstanding_transactions };
    m_bit_details_model.bits.append(entry);
    entry = { "03: undefined_bit_3:1", "", 1, old_value_t.undefined_bit_3, new_value_t.undefined_bit_3 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: dram_in_powerdown:2",
              "dev[n] has entered powerdown state (incoming req's will awaken if not stalled)",
              2, old_value_t.dram_in_powerdown, new_value_t.dram_in_powerdown };
    m_bit_details_model.bits.append(entry);
    entry = { "06: undefined_bits_6_7:2", "", 2, old_value_t.undefined_bits_6_7, new_value_t.undefined_bits_6_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: dram_in_self_refresh:2",
              "dev[n] has been put into self-refresh (will remain until SR exit cmd)",
              2, old_value_t.dram_in_self_refresh, new_value_t.dram_in_self_refresh };
    m_bit_details_model.bits.append(entry);
    entry = { "10: undefined_bits_10_11:2", "", 2, old_value_t.undefined_bits_10_11, new_value_t.undefined_bits_10_11 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: dram_in_dpd:2",
              "dev[n] has been put into deep powerdown state",
              2, old_value_t.dram_in_dpd, new_value_t.dram_in_dpd };
    m_bit_details_model.bits.append(entry);
    entry = { "14: undefined_bits_14_15:2", "", 2, old_value_t.undefined_bits_14_15, new_value_t.undefined_bits_14_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: mrr_fifo_space:4",
              "mrr fifospace available",
              4, old_value_t.mrr_fifo_space, new_value_t.mrr_fifo_space };
    m_bit_details_model.bits.append(entry);
    entry = { "20: mrr_divld:1",
              "mrr data available for reading",
              1, old_value_t.mrr_divld, new_value_t.mrr_divld };
    m_bit_details_model.bits.append(entry);
    entry = { "21: undefined_bits_21_31:11", "", 11, old_value_t.undefined_bits_21_31, new_value_t.undefined_bits_21_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "DRAM_IN_POWERDOWN, DRAM_IN_SELF_REFRESH, DRAM_IN_DPD: active high signal indicating current DRAM status for each of these modes, w/ 1 status bit per device, bit[0] = dev0 status, bit[1] = dev1 status.\nExample: DRAM_IN_SELF_REFRESH = 0x3, both devices are in self-refresh, DRAM_IN_DPD= 0x2 would indicate only dev1 is in deep-power-down mode. NOTE: If EMC is reset or powered down, the actual DRAM state could be different than indicated by these status bits. These bits do not reflect manually entered/exited powerdown or self-refresh (via use of PIN_CKE).\nEMC State-Machine Status";
}

#define CFG_2_OFFSET 0x2B8
#define CFG_2_UNDEFMASK 0x7FCCF8F8
union cfg_2_u {
    struct {
        unsigned int clkchange_req_enable:1;/* allows EMC and CAR to handshake on PLL divider/source changes. 0 = DISABLED 1 = ENABLED */
        unsigned int clkchange_pd_enable:1; /* Forces dram into power-down during CLKCHANGE. 0 = DISABLED 1 = ENABLED */
        unsigned int clkchange_sr_enable:1; /* Forces dram into self-refresh during CLKCHANGE. Takes precedent over CLKCHANGE_PD_ENABLE if both are set. 0 = DISABLED 1 = ENABLED */
        unsigned int undefined_bits_3_7:5;
        unsigned int pin_config:2;          /* Remaps address/command pins for LPDDR_POP ball-out otherwise uses standard LPDDR2 pin configuration. 0 = LPDDR2; 1 = LPDDR_POP 2 = RESERVED */
        unsigned int use_addr_clk:1;        /* Used to select source for DRAM clock. If enabled, xm2_addr_mclk pins instead of xm2_mclk. the former is located adjacent to addr pins used in lpddr2 (for lower clk to addr skew). If disabled, xm2_addr_mclk will be disabled & xm2_mclk will output DRAM clock (required for LPDDR_POP). 0 = DISABLED 1 = ENABLED */
        unsigned int undefined_bits_11_15:5;
        unsigned int mrr_bytesel:2;         /* Indicates which AP bytelane is connected to DRAM byte 0 (over which MRR data is returned) */
        unsigned int undefined_bits_18_19:2;
        unsigned int mrr_bytesel_x16:2;     /* If using 2 X16 DRAM on a single CS to form 32-bit wide data, indicates which bytelane 2nd DRAM's byte 0 is connected to */
        unsigned int undefined_bits_22_30:9;
        unsigned int dramc_pre_b4_act:1;    /* CYA bit, gives priority to activates over precharges, determining which (precharge/activate) is processed first if both are pending and unblocked. 0 = DISABLED 1 = ENABLED */
    };

    u_int32_t reg32;
};

void EmcDev::fill_cfg_2_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const cfg_2_u old_value_t = { .reg32 = value };
    const cfg_2_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: clkchange_req_enable:1",
              "allows EMC and CAR to handshake on PLL divider/source changes.\n0 = DISABLED\n1 = ENABLED",
              1, old_value_t.clkchange_req_enable, new_value_t.clkchange_req_enable };
    m_bit_details_model.bits.append(entry);
    entry = { "01: clkchange_pd_enable:1",
              "Forces dram into power-down during CLKCHANGE.\n0 = DISABLED\n1 = ENABLED",
              1, old_value_t.clkchange_pd_enable, new_value_t.clkchange_pd_enable };
    m_bit_details_model.bits.append(entry);
    entry = { "02: clkchange_sr_enable:1",
              "Forces dram into self-refresh during CLKCHANGE. Takes precedent over CLKCHANGE_PD_ENABLE if both are set.\n0 = DISABLED\n1 = ENABLED",
              1, old_value_t.clkchange_sr_enable, new_value_t.clkchange_sr_enable };
    m_bit_details_model.bits.append(entry);
    entry = { "03: undefined_bits_3_7:5", "", 5, old_value_t.undefined_bits_3_7, new_value_t.undefined_bits_3_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: pin_config:2",
              "Remaps address/command pins for LPDDR_POP ball-out otherwise uses standard LPDDR2 pin configuration.\n0 = LPDDR2;\n1 = LPDDR_POP\n2 = RESERVED",
              2, old_value_t.pin_config, new_value_t.pin_config };
    m_bit_details_model.bits.append(entry);
    entry = { "10: use_addr_clk:1",
              "Used to select source for DRAM clock. If enabled, xm2_addr_mclk pins instead of xm2_mclk. the former is located adjacent to addr pins used in lpddr2 (for lower clk to addr skew). If disabled, xm2_addr_mclk will be disabled & xm2_mclk will output DRAM clock (required for LPDDR_POP).\n0 = DISABLED\n1 = ENABLED",
              1, old_value_t.use_addr_clk, new_value_t.use_addr_clk };
    m_bit_details_model.bits.append(entry);
    entry = { "11: undefined_bits_11_15:5", "", 5, old_value_t.undefined_bits_11_15, new_value_t.undefined_bits_11_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: mrr_bytesel:2",
              "Indicates which AP bytelane is connected to DRAM byte 0 (over which MRR data is returned)",
              2, old_value_t.mrr_bytesel, new_value_t.mrr_bytesel };
    m_bit_details_model.bits.append(entry);
    entry = { "18: undefined_bits_18_19:2", "", 2, old_value_t.undefined_bits_18_19, new_value_t.undefined_bits_18_19 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: mrr_bytesel_x16:2",
              "If using 2 X16 DRAM on a single CS to form 32-bit wide data, indicates which bytelane 2nd DRAM's byte 0 is connected to",
              2, old_value_t.mrr_bytesel_x16, new_value_t.mrr_bytesel_x16 };
    m_bit_details_model.bits.append(entry);
    entry = { "22: undefined_bits_22_30:9", "", 9, old_value_t.undefined_bits_22_30, new_value_t.undefined_bits_22_30 };
    m_bit_details_model.bits.append(entry);
    entry = { "31: dramc_pre_b4_act:1",
              "CYA bit, gives priority to activates over precharges, determining which (precharge/activate) is processed first if both are pending and unblocked.\n0 = DISABLED\n1 = ENABLED",
              1, old_value_t.dramc_pre_b4_act, new_value_t.dramc_pre_b4_act };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Clock change sequencing: Once the divider is reprogrammed, CAR signals to EMC that a clock change is pending. If enabled, EMC stalls incoming requests, drains outstanding requests, and, if CLKCHANGE_(PD|SR)_ENABLE is enabled, puts DRAM into powerdown (or self-refresh) before signalling to CAR that it is idle and ready for the change to happen.\nCAR will then change the divider/pll reprogramming. Once complete, EMC updates its shadow registers (assuming they may have been reprogrammed for new clock setting), unstalls requests, and resumes operation with new clock settings.\nBoot requirements\n    * This register (except for fields DRAMC_PRE_B4_ACT, MRR_BYTESEL_X16, MRR_BYTESEL) should be parameterized in the BCT and written by the BootROM during coldboot.\n    * This register (except for fields DRAMC_PRE_B4_ACT, MRR_BYTESEL_X16, MRR_BYTESEL) should be saved in the scratch registers and restored by the BootROM during warmboot.\n    * If the OS needs the MRR_BYTESEL* fields set to non-default values to perform a mode-register read, it needs to correctly program these values before performing the MRR.\nEMC Configuration";
}

#define CFG_DIG_DLL_OFFSET 0x2BC
#define CFG_DIG_DLL_UNDEFMASK 0x0400F000
union cfg_dig_dll_u {
    struct {
        unsigned int cfg_dll_en:1;          /* Enable digital DLL's. 0 = DISABLED 1 = ENABLED */
        unsigned int cfg_dli_trimmer_en:1;  /* Enable DL trimmer cells (embedded in pads). 0 = DISABLED 1 = ENABLED */
        unsigned int cfg_dll_override_en:1; /* Override DLL's DLI output w/ OVERRIDE_VAL (still uses mult/offset). 0 = DISABLED 1 = ENABLED */
        unsigned int cfg_use_single_dll:1;  /* Turn off upper DLL & use lower dll output to drive all trimmers. 0 = DISABLED 1 = ENABLED */
        unsigned int cfg_perbyte_trimmer_override:1;/* Set trimmer values directly for each byte via FBIO_QUSE_DLY/FBIO_DQS_DLY & FBIO_QUSE_DLY_MSB/FBIO_DQS_DLY_MSB. 0 = DISABLED 1 = ENABLED */
        unsigned int cfg_dll_lowspeed:1;    /* Enable DLL for use w/ lowspeed EMCCLK operation (<200MHz) */
        unsigned int cfg_dll_mode:2;        /* Controls how frequently DLL runs, as follows 0 = RUN_CONTINUOUS : DLL will run continuously (only disabled during reads). This option will consume the most power.  1 = RUN_TIL_LOCK : after DLL_RESET is set, DLL will run until it has locked, then be disabled  2 = RUN_PERIODIC : DLL will be re-enabled w/ each refresh to make sure LOCK is maintained; 3 = RESERVED */
        unsigned int cfg_dll_udset:4;       /* DLL Loop filter control (2^(udset+3)) */
        unsigned int undefined_bits_12_15:4;
        unsigned int cfg_dll_override_val:10;/* Value to use in place of DLI output if CFG_DLL_OVERRIDE_EN is set */
        unsigned int undefined_bit_26:1;
        unsigned int cfg_dll_alarm_disable:1;/* CYA bit -- disable override of DLL logic when DLL_ALM is set (otherwise overrides DLI to 0x3FF) */
        unsigned int cfg_dll_lock_limit:2;  /* CYA in case DLL has problems locking. DLL will be treated as locked after LIMIT emcclk cycles. Counter is reset w/ DLL_RESET (from above) or w/ each periodic update (if using RUN_PERIODIC). Settings are: 00: LIMIT = 2^12 01: LIMIT = 2^15 10: LIMIT = 2^16 11: LIMIT = 2^16 + 2^17 */
        unsigned int dll_reset:1;           /* Writing 1 to this register will send reset pulse to DLL's on next shadow update. Must reset DLL's when changing clock frequency by factor >= 2 */
        unsigned int cfg_dll_use_override_until_lock:1;/* Writing 1 to this register causes override_val to be used in place of DLL output until DLL_LOCK is obtained. Takes effect on next shadow update */
    };

    u_int32_t reg32;
};

void EmcDev::fill_cfg_dig_dll_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const cfg_dig_dll_u old_value_t = { .reg32 = value };
    const cfg_dig_dll_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: cfg_dll_en:1",
              "Enable digital DLL's.\n0 = DISABLED\n1 = ENABLED",
              1, old_value_t.cfg_dll_en, new_value_t.cfg_dll_en };
    m_bit_details_model.bits.append(entry);
    entry = { "01: cfg_dli_trimmer_en:1",
              "Enable DL trimmer cells (embedded in pads).\n0 = DISABLED\n1 = ENABLED",
              1, old_value_t.cfg_dli_trimmer_en, new_value_t.cfg_dli_trimmer_en };
    m_bit_details_model.bits.append(entry);
    entry = { "02: cfg_dll_override_en:1",
              "Override DLL's DLI output w/ OVERRIDE_VAL (still uses mult/offset).\n0 = DISABLED\n1 = ENABLED",
              1, old_value_t.cfg_dll_override_en, new_value_t.cfg_dll_override_en };
    m_bit_details_model.bits.append(entry);
    entry = { "03: cfg_use_single_dll:1",
              "Turn off upper DLL & use lower dll output to drive all trimmers.\n0 = DISABLED\n1 = ENABLED",
              1, old_value_t.cfg_use_single_dll, new_value_t.cfg_use_single_dll };
    m_bit_details_model.bits.append(entry);
    entry = { "04: cfg_perbyte_trimmer_override:1",
              "Set trimmer values directly for each byte via FBIO_QUSE_DLY/FBIO_DQS_DLY & FBIO_QUSE_DLY_MSB/FBIO_DQS_DLY_MSB.\n0 = DISABLED\n1 = ENABLED",
              1, old_value_t.cfg_perbyte_trimmer_override, new_value_t.cfg_perbyte_trimmer_override };
    m_bit_details_model.bits.append(entry);
    entry = { "05: cfg_dll_lowspeed:1",
              "Enable DLL for use w/ lowspeed EMCCLK operation (<200MHz)",
              1, old_value_t.cfg_dll_lowspeed, new_value_t.cfg_dll_lowspeed };
    m_bit_details_model.bits.append(entry);
    entry = { "06: cfg_dll_mode:2",
              "Controls how frequently DLL runs, as follows\n0 = RUN_CONTINUOUS : DLL will run continuously (only disabled during reads). This option will consume the most power.\n1 = RUN_TIL_LOCK : after DLL_RESET is set, DLL will run until it has locked, then be disabled \n2 = RUN_PERIODIC : DLL will be re-enabled w/ each refresh to make sure LOCK is maintained;\n3 = RESERVED",
              2, old_value_t.cfg_dll_mode, new_value_t.cfg_dll_mode };
    m_bit_details_model.bits.append(entry);
    entry = { "08: cfg_dll_udset:4",
              "DLL Loop filter control (2^(udset+3))",
              4, old_value_t.cfg_dll_udset, new_value_t.cfg_dll_udset };
    m_bit_details_model.bits.append(entry);
    entry = { "12: undefined_bits_12_15:4", "", 4, old_value_t.undefined_bits_12_15, new_value_t.undefined_bits_12_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: cfg_dll_override_val:10",
              "Value to use in place of DLI output if CFG_DLL_OVERRIDE_EN is set",
              10, old_value_t.cfg_dll_override_val, new_value_t.cfg_dll_override_val };
    m_bit_details_model.bits.append(entry);
    entry = { "26: undefined_bit_26:1", "", 1, old_value_t.undefined_bit_26, new_value_t.undefined_bit_26 };
    m_bit_details_model.bits.append(entry);
    entry = { "27: cfg_dll_alarm_disable:1",
              "CYA bit -- disable override of DLL logic when DLL_ALM is set (otherwise overrides DLI to 0x3FF)",
              1, old_value_t.cfg_dll_alarm_disable, new_value_t.cfg_dll_alarm_disable };
    m_bit_details_model.bits.append(entry);
    entry = { "28: cfg_dll_lock_limit:2",
              "CYA in case DLL has problems locking. DLL will be treated as locked after LIMIT emcclk cycles. Counter is reset w/ DLL_RESET (from above) or w/ each periodic update (if using RUN_PERIODIC). Settings are: 00: LIMIT = 2^12 01: LIMIT = 2^15 10: LIMIT = 2^16 11: LIMIT = 2^16 + 2^17",
              2, old_value_t.cfg_dll_lock_limit, new_value_t.cfg_dll_lock_limit };
    m_bit_details_model.bits.append(entry);
    entry = { "30: dll_reset:1",
              "Writing 1 to this register will send reset pulse to DLL's on next shadow update. Must reset DLL's when changing clock frequency by factor >= 2",
              1, old_value_t.dll_reset, new_value_t.dll_reset };
    m_bit_details_model.bits.append(entry);
    entry = { "31: cfg_dll_use_override_until_lock:1",
              "Writing 1 to this register causes override_val to be used in place of DLL output until DLL_LOCK is obtained. Takes effect on next shadow update",
              1, old_value_t.cfg_dll_use_override_until_lock, new_value_t.cfg_dll_use_override_until_lock };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Controls for digital DLL's, which used to measure and maintain 1/4 cycle phase adjustment for RDQS strobes.\nThis register is shadowed.\nBoot requirements\n    * This register (except for field CFG_DLL_ALARM_DISABLE and DLL_RESET(trigger) and CFG_DLL_USE_OVERRIDE_UNTIL_LOCK(trigger)) should be parameterized in the BCT and written by the BootROM during coldboot.\n    * This register (except for field CFG_DLL_ALARM_DISABLE and DLL_RESET(trigger) and CFG_DLL_USE_OVERRIDE_UNTIL_LOCK(trigger)) should be saved in the scratch registers and restored by the BootROM during warmboot.\nConfigure Digital DLL";
}

#define DLL_XFORM_DQS_OFFSET 0x2C0
#define DLL_XFORM_DQS_UNDEFMASK 0xFF8000E0
union dll_xform_dqs_u {
    struct {
        unsigned int xform_dqs_mult:5;
        unsigned int undefined_bits_5_7:3;
        unsigned int xform_dqs_offs:15;
        unsigned int undefined_bits_23_31:9;
    };

    u_int32_t reg32;
};

void EmcDev::fill_dll_xform_dqs_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const dll_xform_dqs_u old_value_t = { .reg32 = value };
    const dll_xform_dqs_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: xform_dqs_mult:5", "", 5, old_value_t.xform_dqs_mult, new_value_t.xform_dqs_mult };
    m_bit_details_model.bits.append(entry);
    entry = { "05: undefined_bits_5_7:3", "", 3, old_value_t.undefined_bits_5_7, new_value_t.undefined_bits_5_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: xform_dqs_offs:15", "", 15, old_value_t.xform_dqs_offs, new_value_t.xform_dqs_offs };
    m_bit_details_model.bits.append(entry);
    entry = { "23: undefined_bits_23_31:9", "", 9, old_value_t.undefined_bits_23_31, new_value_t.undefined_bits_23_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "XFORM_DQS_MULT and XFORM_DQS_OFFS are a multiplier and offset, respectively that can be used to modify the dll output.\n Final products may be read out in DQS_TRIMMER_RD register. Default is multiply by 1, to keep DLL's 1/4 cycle delay. Integer + fractional formats for multiplier & offset:\n OFFS is 2's complement format, w/ bit [4] representing integer\n The output of the XFORM is xform_out = (xform_in * MULT + OFFS)/ 16\n Largest allowed MULT = 0x17\n In the case of overflow, output is clamped according to these rules:\n out >= 0x600, xform_out = 0x000\n 0x600 > out >= 0x400, xform_out = 0x3ff\n That means clamping works within 50% above the maximum (0x3ff) dll output or 50% below the minimum (0) dll output.\nTo make sure that is always satisfied, conservatively program OFFS so that 0x6000 < OFFS < (0x5fff - MULT * 0x3ff)\nThis register is shadowed.\nBoot requirements\n    * This register should be parameterized in the BCT and written by the BootROM during coldboot.\n    * This register should be saved in the scratch registers and restored by the BootROM during warmboot.\nConfigure Digital DLL";
}

#define DLL_XFORM_QUSE_OFFSET 0x2C4
#define DLL_XFORM_QUSE_UNDEFMASK 0xFF8000E0
union dll_xform_quse_u {
    struct {
        unsigned int xform_quse_mult:5;
        unsigned int undefined_bits_5_7:3;
        unsigned int xform_quse_offs:15;
        unsigned int undefined_bits_23_31:9;
    };

    u_int32_t reg32;
};

void EmcDev::fill_dll_xform_quse_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const dll_xform_quse_u old_value_t = { .reg32 = value };
    const dll_xform_quse_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: xform_quse_mult:5", "", 5, old_value_t.xform_quse_mult, new_value_t.xform_quse_mult };
    m_bit_details_model.bits.append(entry);
    entry = { "05: undefined_bits_5_7:3", "", 3, old_value_t.undefined_bits_5_7, new_value_t.undefined_bits_5_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: xform_quse_offs:15", "", 15, old_value_t.xform_quse_offs, new_value_t.xform_quse_offs };
    m_bit_details_model.bits.append(entry);
    entry = { "23: undefined_bits_23_31:9", "", 9, old_value_t.undefined_bits_23_31, new_value_t.undefined_bits_23_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "XFORM_QUSE_MULT and XFORM_QUSE_OFFS are a multiplier and offset, respectively that can be used to modify the dll output. Final product may be read out in DQS_TRIMMER_RD register. Default is multiply by 1/2, to give 1/8 cycle delay.\n OFFS is 2's complement format, w/ bit [4] representing integer\n The output of the XFORM is xform_out = (xform_in * MULT + OFFS)/ 16\n Largest allowed MULT = 0x17\n In the case of overflow, output is clamped according to these rules:\n out >= 0x600, xform_out = 0x000\n 0x600 > out >= 0x400, xform_out = 0x3ff\nThat means clamping works within 50% above the maximum (0x3ff) dll output or 50% below the minimum (0) dll output.\nTo make sure that is always satisfied, conservatively program OFFS so that 0x6000 < OFFS < (0x5fff - MULT * 0x3ff)\nThis register is shadowed.\nBoot requirements\n    * This register should be parameterized in the BCT and written by the BootROM during coldboot.\n    * This register should be saved in the scratch registers and restored by the BootROM during warmboot.\nConfigure Digital DLL";
}

#define DIG_DLL_UPPER_STATUS_OFFSET 0x2C8
#define DIG_DLL_UPPER_STATUS_UNDEFMASK 0xFFFF1C00
union dig_dll_upper_status_u {
    struct {
        unsigned int dll_upper_out:10;
        unsigned int undefined_bits_10_12:3;
        unsigned int dll_upper_lock_timeout:1;
        unsigned int dll_upper_alarm:1;
        unsigned int dll_upper_lock:1;
        unsigned int undefined_bits_16_31:16;
    };

    u_int32_t reg32;
};

void EmcDev::fill_dig_dll_upper_status_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const dig_dll_upper_status_u old_value_t = { .reg32 = value };
    const dig_dll_upper_status_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: dll_upper_out:10", "", 10, old_value_t.dll_upper_out, new_value_t.dll_upper_out };
    m_bit_details_model.bits.append(entry);
    entry = { "10: undefined_bits_10_12:3", "", 3, old_value_t.undefined_bits_10_12, new_value_t.undefined_bits_10_12 };
    m_bit_details_model.bits.append(entry);
    entry = { "13: dll_upper_lock_timeout:1", "", 1, old_value_t.dll_upper_lock_timeout, new_value_t.dll_upper_lock_timeout };
    m_bit_details_model.bits.append(entry);
    entry = { "14: dll_upper_alarm:1", "", 1, old_value_t.dll_upper_alarm, new_value_t.dll_upper_alarm };
    m_bit_details_model.bits.append(entry);
    entry = { "15: dll_upper_lock:1", "", 1, old_value_t.dll_upper_lock, new_value_t.dll_upper_lock };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_31:16", "", 16, old_value_t.undefined_bits_16_31, new_value_t.undefined_bits_16_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Digital DLL Status bits directly from DLL\nDigital DLL Status";
}

#define DIG_DLL_LOWER_STATUS_OFFSET 0x2CC
#define DIG_DLL_LOWER_STATUS_UNDEFMASK 0xFFFF1C00
union dig_dll_lower_status_u {
    struct {
        unsigned int dll_lower_out:10;
        unsigned int undefined_bits_10_12:3;
        unsigned int dll_lower_lock_timeout:1;
        unsigned int dll_lower_alarm:1;
        unsigned int dll_lower_lock:1;
        unsigned int undefined_bits_16_31:16;
    };

    u_int32_t reg32;
};

void EmcDev::fill_dig_dll_lower_status_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const dig_dll_lower_status_u old_value_t = { .reg32 = value };
    const dig_dll_lower_status_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: dll_lower_out:10", "", 10, old_value_t.dll_lower_out, new_value_t.dll_lower_out };
    m_bit_details_model.bits.append(entry);
    entry = { "10: undefined_bits_10_12:3", "", 3, old_value_t.undefined_bits_10_12, new_value_t.undefined_bits_10_12 };
    m_bit_details_model.bits.append(entry);
    entry = { "13: dll_lower_lock_timeout:1", "", 1, old_value_t.dll_lower_lock_timeout, new_value_t.dll_lower_lock_timeout };
    m_bit_details_model.bits.append(entry);
    entry = { "14: dll_lower_alarm:1", "", 1, old_value_t.dll_lower_alarm, new_value_t.dll_lower_alarm };
    m_bit_details_model.bits.append(entry);
    entry = { "15: dll_lower_lock:1", "", 1, old_value_t.dll_lower_lock, new_value_t.dll_lower_lock };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_31:16", "", 16, old_value_t.undefined_bits_16_31, new_value_t.undefined_bits_16_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Digital DLL Status";
}

#define CTT_TERM_CTRL_OFFSET 0x2DC
#define CTT_TERM_CTRL_UNDEFMASK 0x60F060F8
union ctt_term_ctrl_u {
    struct {
        unsigned int term_slope:3;          /*  */
        unsigned int undefined_bits_3_7:5;
        unsigned int term_offset:5;         /*  */
        unsigned int undefined_bits_13_14:2;
        unsigned int term_drvdn:5;
        unsigned int undefined_bits_20_23:4;
        unsigned int term_drvup:5;
        unsigned int undefined_bits_29_30:2;
        unsigned int term_override:1;       /* 0 = DISABLED 1 = ENABLED */
    };

    u_int32_t reg32;
};

void EmcDev::fill_ctt_term_ctrl_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const ctt_term_ctrl_u old_value_t = { .reg32 = value };
    const ctt_term_ctrl_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: term_slope:3",
              "",
              3, old_value_t.term_slope, new_value_t.term_slope };
    m_bit_details_model.bits.append(entry);
    entry = { "03: undefined_bits_3_7:5", "", 5, old_value_t.undefined_bits_3_7, new_value_t.undefined_bits_3_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: term_offset:5",
              "",
              5, old_value_t.term_offset, new_value_t.term_offset };
    m_bit_details_model.bits.append(entry);
    entry = { "13: undefined_bits_13_14:2", "", 2, old_value_t.undefined_bits_13_14, new_value_t.undefined_bits_13_14 };
    m_bit_details_model.bits.append(entry);
    entry = { "15: term_drvdn:5", "", 5, old_value_t.term_drvdn, new_value_t.term_drvdn };
    m_bit_details_model.bits.append(entry);
    entry = { "20: undefined_bits_20_23:4", "", 4, old_value_t.undefined_bits_20_23, new_value_t.undefined_bits_20_23 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: term_drvup:5", "", 5, old_value_t.term_drvup, new_value_t.term_drvup };
    m_bit_details_model.bits.append(entry);
    entry = { "29: undefined_bits_29_30:2", "", 2, old_value_t.undefined_bits_29_30, new_value_t.undefined_bits_29_30 };
    m_bit_details_model.bits.append(entry);
    entry = { "31: term_override:1",
              "0 = DISABLED\n1 = ENABLED",
              1, old_value_t.term_override, new_value_t.term_override };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "If CTT_TERMINATION is enabled this controls the strength of the output drivers.\nTERM_OVERRIDE forces use of CFG2TMC_CFG*_DRVDN_TERM, CFG2TMC_CFG*_DRVUP_TERM instead (arapb_misc_gp register) of using of AUTO_CAL DRVDN/DRVUP values w/ the following equation applied:\n TERM_DRDN = (AUTO_CAL_DRVDN * TERM_SLOPE) / 4 + TERM_OFFSET\n TERM_DRUP = (AUTO_CAL_DRVUP * TERM_SLOPE) / 4 + TERM_OFFSET\nRecommended values for SLOPE/OFFSET\n 100ohm CTT: TERM_SLOPE = 0x1, TERM_OFFSET = 0x4\n 50ohm CTT: TERM_SLOPE = 0x2, TERM_OFFSET = 0x8\nNote: setting slope = 0 allows TERM_DRDN/DRVUP = TERM_OFFSET setting slope > 2 is not supported\nBoot requirements\n    * This register (except for fields TERM_DRVDN and TERM_DRVUP) should be parameterized in the BCT and written by the BootROM during coldboot.\n    * This register (except for fields TERM_DRVDN and TERM_DRVUP) should be saved in the scratch registers and restored by the BootROM during warmboot.\nConfigure CTT termination output drive strength";
}

#define ZCAL_REF_CNT_OFFSET 0x2E0
#define ZCAL_REF_CNT_UNDEFMASK 0xFF000000
union zcal_ref_cnt_u {
    struct {
        unsigned int zcal_ref_interval:24;  /* Number of refreshes to wait between issuance of ZCAL_MRW_CMD. If 0, ZCAL is disabled and internal counter will be reset */
        unsigned int undefined_bits_24_31:8;
    };

    u_int32_t reg32;
};

void EmcDev::fill_zcal_ref_cnt_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const zcal_ref_cnt_u old_value_t = { .reg32 = value };
    const zcal_ref_cnt_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: zcal_ref_interval:24",
              "Number of refreshes to wait between issuance of ZCAL_MRW_CMD. If 0, ZCAL is disabled and internal counter will be reset",
              24, old_value_t.zcal_ref_interval, new_value_t.zcal_ref_interval };
    m_bit_details_model.bits.append(entry);
    entry = { "24: undefined_bits_24_31:8", "", 8, old_value_t.undefined_bits_24_31, new_value_t.undefined_bits_24_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "This register is shadowed.\nBoot requirements\n    * This register should be parameterized in the BCT and written by the BootROM during coldboot.\n    * This register should be saved in the scratch registers and restored by the BootROM during warmboot.\nConfigure ZQ Calibration";
}

#define ZCAL_WAIT_CNT_OFFSET 0x2E4
#define ZCAL_WAIT_CNT_UNDEFMASK 0xFFFFFF00
union zcal_wait_cnt_u {
    struct {
        unsigned int zcal_wait_cnt:8;       /* Number of emc clocks to wait before issuing any commands after sending ZCAL_MRW_CMD */
        unsigned int undefined_bits_8_31:24;
    };

    u_int32_t reg32;
};

void EmcDev::fill_zcal_wait_cnt_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const zcal_wait_cnt_u old_value_t = { .reg32 = value };
    const zcal_wait_cnt_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: zcal_wait_cnt:8",
              "Number of emc clocks to wait before issuing any commands after sending ZCAL_MRW_CMD",
              8, old_value_t.zcal_wait_cnt, new_value_t.zcal_wait_cnt };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_31:24", "", 24, old_value_t.undefined_bits_8_31, new_value_t.undefined_bits_8_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "This register is shadowed.\nBoot requirements\n    * This register should be parameterized in the BCT and written by the BootROM during coldboot.\n    * This register should be saved in the scratch registers and restored by the BootROM during warmboot.\nConfigure ZQ Calibration";
}

#define ZCAL_MRW_CMD_OFFSET 0x2E8
#define ZCAL_MRW_CMD_UNDEFMASK 0x3F00FF00
union zcal_mrw_cmd_u {
    struct {
        unsigned int zq_mrw_op:8;           /* MRW OP field to be sent after ZCAL_REF_CNT */
        unsigned int undefined_bits_8_15:8;
        unsigned int zq_mrw_ma:8;           /* MRW MA field to be sent after ZCAL_REF_CNT */
        unsigned int undefined_bits_24_29:6;
        unsigned int zq_mrw_dev_selectn:2;  /* active-low chip-select, 0x0 applies command to both devices (will happen 1 at a time), 0x2 to for only dev0, 0x1 for dev1 */
    };

    u_int32_t reg32;
};

void EmcDev::fill_zcal_mrw_cmd_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const zcal_mrw_cmd_u old_value_t = { .reg32 = value };
    const zcal_mrw_cmd_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: zq_mrw_op:8",
              "MRW OP field to be sent after ZCAL_REF_CNT",
              8, old_value_t.zq_mrw_op, new_value_t.zq_mrw_op };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_15:8", "", 8, old_value_t.undefined_bits_8_15, new_value_t.undefined_bits_8_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: zq_mrw_ma:8",
              "MRW MA field to be sent after ZCAL_REF_CNT",
              8, old_value_t.zq_mrw_ma, new_value_t.zq_mrw_ma };
    m_bit_details_model.bits.append(entry);
    entry = { "24: undefined_bits_24_29:6", "", 6, old_value_t.undefined_bits_24_29, new_value_t.undefined_bits_24_29 };
    m_bit_details_model.bits.append(entry);
    entry = { "30: zq_mrw_dev_selectn:2",
              "active-low chip-select, 0x0 applies command to both devices (will happen 1 at a time), 0x2 to for only dev0, 0x1 for dev1",
              2, old_value_t.zq_mrw_dev_selectn, new_value_t.zq_mrw_dev_selectn };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "This register is shadowed.\nBoot requirements\n    * This register should be parameterized in the BCT and written by the BootROM during coldboot.\n    * This register should be saved in the scratch registers and restored by the BootROM during warmboot.\nConfigure ZQ Calibration";
}

#define CMDQ_OFFSET 0xF0
#define CMDQ_UNDEFMASK 0xE0FF88E0
union cmdq_u {
    struct {
        unsigned int rw_depth:5;
        unsigned int undefined_bits_5_7:3;
        unsigned int act_depth:3;
        unsigned int undefined_bit_11:1;
        unsigned int pre_depth:3;
        unsigned int undefined_bits_15_23:9;
        unsigned int rw_wd_depth:5;
        unsigned int undefined_bits_29_31:3;
    };

    u_int32_t reg32;
};

void EmcDev::fill_cmdq_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const cmdq_u old_value_t = { .reg32 = value };
    const cmdq_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: rw_depth:5", "", 5, old_value_t.rw_depth, new_value_t.rw_depth };
    m_bit_details_model.bits.append(entry);
    entry = { "05: undefined_bits_5_7:3", "", 3, old_value_t.undefined_bits_5_7, new_value_t.undefined_bits_5_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: act_depth:3", "", 3, old_value_t.act_depth, new_value_t.act_depth };
    m_bit_details_model.bits.append(entry);
    entry = { "11: undefined_bit_11:1", "", 1, old_value_t.undefined_bit_11, new_value_t.undefined_bit_11 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: pre_depth:3", "", 3, old_value_t.pre_depth, new_value_t.pre_depth };
    m_bit_details_model.bits.append(entry);
    entry = { "15: undefined_bits_15_23:9", "", 9, old_value_t.undefined_bits_15_23, new_value_t.undefined_bits_15_23 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: rw_wd_depth:5", "", 5, old_value_t.rw_wd_depth, new_value_t.rw_wd_depth };
    m_bit_details_model.bits.append(entry);
    entry = { "29: undefined_bits_29_31:3", "", 3, old_value_t.undefined_bits_29_31, new_value_t.undefined_bits_29_31 };
    m_bit_details_model.bits.append(entry);
}

#define FBIO_SPARE_OFFSET 0x100
#define FBIO_SPARE_UNDEFMASK 0x00000000
union fbio_spare_u {
    struct {
        unsigned int cfg_fbio_spare:32;
    };

    u_int32_t reg32;
};

void EmcDev::fill_fbio_spare_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const fbio_spare_u old_value_t = { .reg32 = value };
    const fbio_spare_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: cfg_fbio_spare:32", "", 32, old_value_t.cfg_fbio_spare, new_value_t.cfg_fbio_spare };
    m_bit_details_model.bits.append(entry);
}

#define FBIO_WRPTR_EQ_2_OFFSET 0x108
#define FBIO_WRPTR_EQ_2_UNDEFMASK 0xFFFFFFF0
union fbio_wrptr_eq_2_u {
    struct {
        unsigned int fb_wrptr_eq_2:4;
        unsigned int undefined_bits_4_31:28;
    };

    u_int32_t reg32;
};

void EmcDev::fill_fbio_wrptr_eq_2_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const fbio_wrptr_eq_2_u old_value_t = { .reg32 = value };
    const fbio_wrptr_eq_2_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: fb_wrptr_eq_2:4", "", 4, old_value_t.fb_wrptr_eq_2, new_value_t.fb_wrptr_eq_2 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: undefined_bits_4_31:28", "", 28, old_value_t.undefined_bits_4_31, new_value_t.undefined_bits_4_31 };
    m_bit_details_model.bits.append(entry);
}

#define CLKEN_OVERRIDE_OFFSET 0x140
#define CLKEN_OVERRIDE_UNDEFMASK 0xFFFFFF80
union emc_clken_override_u {
    struct {
        unsigned int arb_clken_ovr:1;
        unsigned int cmdq_clken_ovr:1;
        unsigned int dramc_clken_ovr:1;
        unsigned int rr_clken_ovr:1;
        unsigned int ll_clken_ovr:1;
        unsigned int llstats_clken_ovr:1;
        unsigned int stats_clken_ovr:1;
        unsigned int undefined_bits_7_31:25;
    };

    u_int32_t reg32;
};

void EmcDev::fill_clken_override_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const emc_clken_override_u old_value_t = { .reg32 = value };
    const emc_clken_override_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: arb_clken_ovr:1", "", 1, old_value_t.arb_clken_ovr, new_value_t.arb_clken_ovr };
    m_bit_details_model.bits.append(entry);
    entry = { "01: cmdq_clken_ovr:1", "", 1, old_value_t.cmdq_clken_ovr, new_value_t.cmdq_clken_ovr };
    m_bit_details_model.bits.append(entry);
    entry = { "02: dramc_clken_ovr:1", "", 1, old_value_t.dramc_clken_ovr, new_value_t.dramc_clken_ovr };
    m_bit_details_model.bits.append(entry);
    entry = { "03: rr_clken_ovr:1", "", 1, old_value_t.rr_clken_ovr, new_value_t.rr_clken_ovr };
    m_bit_details_model.bits.append(entry);
    entry = { "04: ll_clken_ovr:1", "", 1, old_value_t.ll_clken_ovr, new_value_t.ll_clken_ovr };
    m_bit_details_model.bits.append(entry);
    entry = { "05: llstats_clken_ovr:1", "", 1, old_value_t.llstats_clken_ovr, new_value_t.llstats_clken_ovr };
    m_bit_details_model.bits.append(entry);
    entry = { "06: stats_clken_ovr:1", "", 1, old_value_t.stats_clken_ovr, new_value_t.stats_clken_ovr };
    m_bit_details_model.bits.append(entry);
    entry = { "07: undefined_bits_7_31:25", "", 25, old_value_t.undefined_bits_7_31, new_value_t.undefined_bits_7_31 };
    m_bit_details_model.bits.append(entry);
}

#define STAT_CONTROL_OFFSET 0x160
#define STAT_CONTROL_UNDEFMASK 0xFFFCFCF8
union emc_stat_control_u {
    struct {
        unsigned int llmc_gather:3;
        unsigned int undefined_bits_3_7:5;
        unsigned int pwr_gather:2;
        unsigned int undefined_bits_10_15:6;
        unsigned int dram_gather:2;
        unsigned int undefined_bits_18_31:14;
    };

    u_int32_t reg32;
};

void EmcDev::fill_stat_control_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const emc_stat_control_u old_value_t = { .reg32 = value };
    const emc_stat_control_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: llmc_gather:3", "", 3, old_value_t.llmc_gather, new_value_t.llmc_gather };
    m_bit_details_model.bits.append(entry);
    entry = { "03: undefined_bits_3_7:5", "", 5, old_value_t.undefined_bits_3_7, new_value_t.undefined_bits_3_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: pwr_gather:2", "", 2, old_value_t.pwr_gather, new_value_t.pwr_gather };
    m_bit_details_model.bits.append(entry);
    entry = { "10: undefined_bits_10_15:6", "", 6, old_value_t.undefined_bits_10_15, new_value_t.undefined_bits_10_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: dram_gather:2", "", 2, old_value_t.dram_gather, new_value_t.dram_gather };
    m_bit_details_model.bits.append(entry);
    entry = { "18: undefined_bits_18_31:14", "", 14, old_value_t.undefined_bits_18_31, new_value_t.undefined_bits_18_31 };
    m_bit_details_model.bits.append(entry);
}

#define STAT_STATUS_OFFSET 0x164
#define STAT_STATUS_UNDEFMASK 0xFFFEFEFE
union emc_stat_status_u {
    struct {
        unsigned int llmc_limit:1;
        unsigned int undefined_bits_1_7:7;
        unsigned int pwr_limit:1;
        unsigned int undefined_bits_9_15:7;
        unsigned int dram_limit:1;
        unsigned int undefined_bits_17_31:15;
    };

    u_int32_t reg32;
};

void EmcDev::fill_stat_status_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const emc_stat_status_u old_value_t = { .reg32 = value };
    const emc_stat_status_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: llmc_limit:1", "", 1, old_value_t.llmc_limit, new_value_t.llmc_limit };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_7:7", "", 7, old_value_t.undefined_bits_1_7, new_value_t.undefined_bits_1_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: pwr_limit:1", "", 1, old_value_t.pwr_limit, new_value_t.pwr_limit };
    m_bit_details_model.bits.append(entry);
    entry = { "09: undefined_bits_9_15:7", "", 7, old_value_t.undefined_bits_9_15, new_value_t.undefined_bits_9_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: dram_limit:1", "", 1, old_value_t.dram_limit, new_value_t.dram_limit };
    m_bit_details_model.bits.append(entry);
    entry = { "17: undefined_bits_17_31:15", "", 15, old_value_t.undefined_bits_17_31, new_value_t.undefined_bits_17_31 };
    m_bit_details_model.bits.append(entry);
}

#define STAT_LLMC_ADDR_LOW_OFFSET 0x168
#define STAT_LLMC_ADDR_LOW_UNDEFMASK 0xC000000F
union stat_llmc_addr_low_u {
    struct {
        unsigned int undefined_bits_0_3:4;
        unsigned int llmc_addr_low:26;
        unsigned int undefined_bits_30_31:2;
    };

    u_int32_t reg32;
};

void EmcDev::fill_stat_llmc_addr_low_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const stat_llmc_addr_low_u old_value_t = { .reg32 = value };
    const stat_llmc_addr_low_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_3:4", "", 4, old_value_t.undefined_bits_0_3, new_value_t.undefined_bits_0_3 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: llmc_addr_low:26", "", 26, old_value_t.llmc_addr_low, new_value_t.llmc_addr_low };
    m_bit_details_model.bits.append(entry);
    entry = { "30: undefined_bits_30_31:2", "", 2, old_value_t.undefined_bits_30_31, new_value_t.undefined_bits_30_31 };
    m_bit_details_model.bits.append(entry);
}

#define STAT_LLMC_ADDR_HIGH_OFFSET 0x16C
#define STAT_LLMC_ADDR_HIGH_UNDEFMASK 0xC000000F
union stat_llmc_addr_high_u {
    struct {
        unsigned int undefined_bits_0_3:4;
        unsigned int llmc_addr_high:26;
        unsigned int undefined_bits_30_31:2;
    };

    u_int32_t reg32;
};

void EmcDev::fill_stat_llmc_addr_high_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const stat_llmc_addr_high_u old_value_t = { .reg32 = value };
    const stat_llmc_addr_high_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_3:4", "", 4, old_value_t.undefined_bits_0_3, new_value_t.undefined_bits_0_3 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: llmc_addr_high:26", "", 26, old_value_t.llmc_addr_high, new_value_t.llmc_addr_high };
    m_bit_details_model.bits.append(entry);
    entry = { "30: undefined_bits_30_31:2", "", 2, old_value_t.undefined_bits_30_31, new_value_t.undefined_bits_30_31 };
    m_bit_details_model.bits.append(entry);
}

#define STAT_LLMC_CLOCK_LIMIT_OFFSET 0x170
#define STAT_LLMC_CLOCK_LIMIT_UNDEFMASK 0x00000000
union stat_llmc_clock_limit_u {
    struct {
        unsigned int llmc_clock_limit:32;
    };

    u_int32_t reg32;
};

void EmcDev::fill_stat_llmc_clock_limit_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const stat_llmc_clock_limit_u old_value_t = { .reg32 = value };
    const stat_llmc_clock_limit_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: llmc_clock_limit:32", "", 32, old_value_t.llmc_clock_limit, new_value_t.llmc_clock_limit };
    m_bit_details_model.bits.append(entry);
}

#define STAT_LLMC_CLOCKS_OFFSET 0x174
#define STAT_LLMC_CLOCKS_UNDEFMASK 0x00000000
union stat_llmc_clocks_u {
    struct {
        unsigned int llmc_clocks:32;
    };

    u_int32_t reg32;
};

void EmcDev::fill_stat_llmc_clocks_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const stat_llmc_clocks_u old_value_t = { .reg32 = value };
    const stat_llmc_clocks_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: llmc_clocks:32", "", 32, old_value_t.llmc_clocks, new_value_t.llmc_clocks };
    m_bit_details_model.bits.append(entry);
}

#define STAT_LLMC_CONTROL_OFFSET 0x178
#define STAT_LLMC_CONTROL_UNDEFMASK 0x00000000
union stat_llmc_control_u {
    struct {
        unsigned int llmc_control_0:32;
    };

    u_int32_t reg32;
};

void EmcDev::fill_stat_llmc_control_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const stat_llmc_control_u old_value_t = { .reg32 = value };
    const stat_llmc_control_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: llmc_control_0:32", "", 32, old_value_t.llmc_control_0, new_value_t.llmc_control_0 };
    m_bit_details_model.bits.append(entry);
}

#define STAT_LLMC_HIST_LIMIT_OFFSET 0x180
#define STAT_LLMC_HIST_LIMIT_UNDEFMASK 0x00000000
union stat_llmc_hist_limit_u {
    struct {
        unsigned int llmc_hist_limit_0:32;
    };

    u_int32_t reg32;
};

void EmcDev::fill_stat_llmc_hist_limit_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const stat_llmc_hist_limit_u old_value_t = { .reg32 = value };
    const stat_llmc_hist_limit_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: llmc_hist_limit_0:32", "", 32, old_value_t.llmc_hist_limit_0, new_value_t.llmc_hist_limit_0 };
    m_bit_details_model.bits.append(entry);
}

#define STAT_LLMC_COUNT_OFFSET 0x188
#define STAT_LLMC_COUNT_UNDEFMASK 0x00000000
union stat_llmc_count_u {
    struct {
        unsigned int llmc_count_0:32;
    };

    u_int32_t reg32;
};

void EmcDev::fill_stat_llmc_count_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const stat_llmc_count_u old_value_t = { .reg32 = value };
    const stat_llmc_count_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: llmc_count_0:32", "", 32, old_value_t.llmc_count_0, new_value_t.llmc_count_0 };
    m_bit_details_model.bits.append(entry);
}

#define STAT_LLMC_HIST_OFFSET 0x190
#define STAT_LLMC_HIST_UNDEFMASK 0x00000000
union stat_llmc_hist_u {
    struct {
        unsigned int llmc_hist_0:32;
    };

    u_int32_t reg32;
};

void EmcDev::fill_stat_llmc_hist_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const stat_llmc_hist_u old_value_t = { .reg32 = value };
    const stat_llmc_hist_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: llmc_hist_0:32", "", 32, old_value_t.llmc_hist_0, new_value_t.llmc_hist_0 };
    m_bit_details_model.bits.append(entry);
}

#define STAT_PWR_CLOCK_LIMIT_OFFSET 0x198
#define STAT_PWR_CLOCK_LIMIT_UNDEFMASK 0x00000000
union stat_pwr_clock_limit_u {
    struct {
        unsigned int pwr_clock_limit:32;
    };

    u_int32_t reg32;
};

void EmcDev::fill_stat_pwr_clock_limit_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const stat_pwr_clock_limit_u old_value_t = { .reg32 = value };
    const stat_pwr_clock_limit_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: pwr_clock_limit:32", "", 32, old_value_t.pwr_clock_limit, new_value_t.pwr_clock_limit };
    m_bit_details_model.bits.append(entry);
}

#define STAT_PWR_CLOCKS_OFFSET 0x19C
#define STAT_PWR_CLOCKS_UNDEFMASK 0x00000000
union stat_pwr_clocks_u {
    struct {
        unsigned int pwr_clocks:32;
    };

    u_int32_t reg32;
};

void EmcDev::fill_stat_pwr_clocks_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const stat_pwr_clocks_u old_value_t = { .reg32 = value };
    const stat_pwr_clocks_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: pwr_clocks:32", "", 32, old_value_t.pwr_clocks, new_value_t.pwr_clocks };
    m_bit_details_model.bits.append(entry);
}

#define STAT_PWR_COUNT_OFFSET 0x1A0
#define STAT_PWR_COUNT_UNDEFMASK 0x00000000
union stat_pwr_count_u {
    struct {
        unsigned int pwr_count:32;
    };

    u_int32_t reg32;
};

void EmcDev::fill_stat_pwr_count_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const stat_pwr_count_u old_value_t = { .reg32 = value };
    const stat_pwr_count_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: pwr_count:32", "", 32, old_value_t.pwr_count, new_value_t.pwr_count };
    m_bit_details_model.bits.append(entry);
}

#define STAT_DRAM_CLOCK_LIMIT_LO_OFFSET 0x1A4
#define STAT_DRAM_CLOCK_LIMIT_LO_UNDEFMASK 0x00000000
union stat_dram_clock_limit_lo_u {
    struct {
        unsigned int dram_clock_limit_lo:32;
    };

    u_int32_t reg32;
};

void EmcDev::fill_stat_dram_clock_limit_lo_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const stat_dram_clock_limit_lo_u old_value_t = { .reg32 = value };
    const stat_dram_clock_limit_lo_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: dram_clock_limit_lo:32", "", 32, old_value_t.dram_clock_limit_lo, new_value_t.dram_clock_limit_lo };
    m_bit_details_model.bits.append(entry);
}

#define STAT_DRAM_CLOCK_LIMIT_HI_OFFSET 0x1A8
#define STAT_DRAM_CLOCK_LIMIT_HI_UNDEFMASK 0xFFFFFF00
union stat_dram_clock_limit_hi_u {
    struct {
        unsigned int dram_clock_limit_hi:8;
        unsigned int undefined_bits_8_31:24;
    };

    u_int32_t reg32;
};

void EmcDev::fill_stat_dram_clock_limit_hi_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const stat_dram_clock_limit_hi_u old_value_t = { .reg32 = value };
    const stat_dram_clock_limit_hi_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: dram_clock_limit_hi:8", "", 8, old_value_t.dram_clock_limit_hi, new_value_t.dram_clock_limit_hi };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_31:24", "", 24, old_value_t.undefined_bits_8_31, new_value_t.undefined_bits_8_31 };
    m_bit_details_model.bits.append(entry);
}

#define STAT_DRAM_CLOCKS_LO_OFFSET 0x1AC
#define STAT_DRAM_CLOCKS_LO_UNDEFMASK 0x00000000
union stat_dram_clocks_lo_u {
    struct {
        unsigned int dram_clocks_lo:32;
    };

    u_int32_t reg32;
};

void EmcDev::fill_stat_dram_clocks_lo_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const stat_dram_clocks_lo_u old_value_t = { .reg32 = value };
    const stat_dram_clocks_lo_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: dram_clocks_lo:32", "", 32, old_value_t.dram_clocks_lo, new_value_t.dram_clocks_lo };
    m_bit_details_model.bits.append(entry);
}

#define STAT_DRAM_CLOCKS_HI_OFFSET 0x1B0
#define STAT_DRAM_CLOCKS_HI_UNDEFMASK 0xFFFFFF00
union stat_dram_clocks_hi_u {
    struct {
        unsigned int dram_clocks_hi:8;
        unsigned int undefined_bits_8_31:24;
    };

    u_int32_t reg32;
};

void EmcDev::fill_stat_dram_clocks_hi_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const stat_dram_clocks_hi_u old_value_t = { .reg32 = value };
    const stat_dram_clocks_hi_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: dram_clocks_hi:8", "", 8, old_value_t.dram_clocks_hi, new_value_t.dram_clocks_hi };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_31:24", "", 24, old_value_t.undefined_bits_8_31, new_value_t.undefined_bits_8_31 };
    m_bit_details_model.bits.append(entry);
}

#define STAT_DRAM_DEV0_ACTIVATE_CNT_LO_OFFSET 0x1B4
#define STAT_DRAM_DEV0_ACTIVATE_CNT_LO_UNDEFMASK 0x00000000
union stat_dram_dev0_activate_cnt_lo_u {
    struct {
        unsigned int dev0_activate_cnt_lo:32;
    };

    u_int32_t reg32;
};

void EmcDev::fill_stat_dram_dev0_activate_cnt_lo_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const stat_dram_dev0_activate_cnt_lo_u old_value_t = { .reg32 = value };
    const stat_dram_dev0_activate_cnt_lo_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: dev0_activate_cnt_lo:32", "", 32, old_value_t.dev0_activate_cnt_lo, new_value_t.dev0_activate_cnt_lo };
    m_bit_details_model.bits.append(entry);
}

#define STAT_DRAM_DEV0_ACTIVATE_CNT_HI_OFFSET 0x1B8
#define STAT_DRAM_DEV0_ACTIVATE_CNT_HI_UNDEFMASK 0xFFFFFF00
union stat_dram_dev0_activate_cnt_hi_u {
    struct {
        unsigned int dev0_activate_cnt_hi:8;
        unsigned int undefined_bits_8_31:24;
    };

    u_int32_t reg32;
};

void EmcDev::fill_stat_dram_dev0_activate_cnt_hi_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const stat_dram_dev0_activate_cnt_hi_u old_value_t = { .reg32 = value };
    const stat_dram_dev0_activate_cnt_hi_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: dev0_activate_cnt_hi:8", "", 8, old_value_t.dev0_activate_cnt_hi, new_value_t.dev0_activate_cnt_hi };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_31:24", "", 24, old_value_t.undefined_bits_8_31, new_value_t.undefined_bits_8_31 };
    m_bit_details_model.bits.append(entry);
}

#define STAT_DRAM_DEV0_READ_CNT_LO_OFFSET 0x1BC
#define STAT_DRAM_DEV0_READ_CNT_LO_UNDEFMASK 0x00000000
union stat_dram_dev0_read_cnt_lo_u {
    struct {
        unsigned int dev0_read_cnt_lo:32;
    };

    u_int32_t reg32;
};

void EmcDev::fill_stat_dram_dev0_read_cnt_lo_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const stat_dram_dev0_read_cnt_lo_u old_value_t = { .reg32 = value };
    const stat_dram_dev0_read_cnt_lo_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: dev0_read_cnt_lo:32", "", 32, old_value_t.dev0_read_cnt_lo, new_value_t.dev0_read_cnt_lo };
    m_bit_details_model.bits.append(entry);
}

#define STAT_DRAM_DEV0_READ_CNT_HI_OFFSET 0x1C0
#define STAT_DRAM_DEV0_READ_CNT_HI_UNDEFMASK 0xFFFFFF00
union stat_dram_dev0_read_cnt_hi_u {
    struct {
        unsigned int dev0_read_cnt_hi:8;
        unsigned int undefined_bits_8_31:24;
    };

    u_int32_t reg32;
};

void EmcDev::fill_stat_dram_dev0_read_cnt_hi_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const stat_dram_dev0_read_cnt_hi_u old_value_t = { .reg32 = value };
    const stat_dram_dev0_read_cnt_hi_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: dev0_read_cnt_hi:8", "", 8, old_value_t.dev0_read_cnt_hi, new_value_t.dev0_read_cnt_hi };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_31:24", "", 24, old_value_t.undefined_bits_8_31, new_value_t.undefined_bits_8_31 };
    m_bit_details_model.bits.append(entry);
}

#define STAT_DRAM_DEV0_WRITE_CNT_LO_OFFSET 0x1C4
#define STAT_DRAM_DEV0_WRITE_CNT_LO_UNDEFMASK 0x00000000
union stat_dram_dev0_write_cnt_lo_u {
    struct {
        unsigned int dev0_write_cnt_lo:32;
    };

    u_int32_t reg32;
};

void EmcDev::fill_stat_dram_dev0_write_cnt_lo_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const stat_dram_dev0_write_cnt_lo_u old_value_t = { .reg32 = value };
    const stat_dram_dev0_write_cnt_lo_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: dev0_write_cnt_lo:32", "", 32, old_value_t.dev0_write_cnt_lo, new_value_t.dev0_write_cnt_lo };
    m_bit_details_model.bits.append(entry);
}

#define STAT_DRAM_DEV0_WRITE_CNT_HI_OFFSET 0x1C8
#define STAT_DRAM_DEV0_WRITE_CNT_HI_UNDEFMASK 0xFFFFFF00
union stat_dram_dev0_write_cnt_hi_u {
    struct {
        unsigned int dev0_write_cnt_hi:8;
        unsigned int undefined_bits_8_31:24;
    };

    u_int32_t reg32;
};

void EmcDev::fill_stat_dram_dev0_write_cnt_hi_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const stat_dram_dev0_write_cnt_hi_u old_value_t = { .reg32 = value };
    const stat_dram_dev0_write_cnt_hi_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: dev0_write_cnt_hi:8", "", 8, old_value_t.dev0_write_cnt_hi, new_value_t.dev0_write_cnt_hi };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_31:24", "", 24, old_value_t.undefined_bits_8_31, new_value_t.undefined_bits_8_31 };
    m_bit_details_model.bits.append(entry);
}

#define STAT_DRAM_DEV0_REF_CNT_LO_OFFSET 0x1CC
#define STAT_DRAM_DEV0_REF_CNT_LO_UNDEFMASK 0x00000000
union stat_dram_dev0_ref_cnt_lo_u {
    struct {
        unsigned int dev0_ref_cnt_lo:32;
    };

    u_int32_t reg32;
};

void EmcDev::fill_stat_dram_dev0_ref_cnt_lo_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const stat_dram_dev0_ref_cnt_lo_u old_value_t = { .reg32 = value };
    const stat_dram_dev0_ref_cnt_lo_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: dev0_ref_cnt_lo:32", "", 32, old_value_t.dev0_ref_cnt_lo, new_value_t.dev0_ref_cnt_lo };
    m_bit_details_model.bits.append(entry);
}

#define STAT_DRAM_DEV0_REF_CNT_HI_OFFSET 0x1D0
#define STAT_DRAM_DEV0_REF_CNT_HI_UNDEFMASK 0xFFFFFF00
union stat_dram_dev0_ref_cnt_hi_u {
    struct {
        unsigned int dev0_ref_cnt_hi:8;
        unsigned int undefined_bits_8_31:24;
    };

    u_int32_t reg32;
};

void EmcDev::fill_stat_dram_dev0_ref_cnt_hi_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const stat_dram_dev0_ref_cnt_hi_u old_value_t = { .reg32 = value };
    const stat_dram_dev0_ref_cnt_hi_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: dev0_ref_cnt_hi:8", "", 8, old_value_t.dev0_ref_cnt_hi, new_value_t.dev0_ref_cnt_hi };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_31:24", "", 24, old_value_t.undefined_bits_8_31, new_value_t.undefined_bits_8_31 };
    m_bit_details_model.bits.append(entry);
}

#define STAT_DRAM_DEV0_CUMM_BANKS_ACTIVE_CKE_EQ1_LO_OFFSET 0x1D4
#define STAT_DRAM_DEV0_CUMM_BANKS_ACTIVE_CKE_EQ1_LO_UNDEFMASK 0x00000000
union stat_dram_dev0_cumm_banks_active_cke_eq1_lo_u {
    struct {
        unsigned int dev0_cumm_banks_active_cke_eq1_lo:32;
    };

    u_int32_t reg32;
};

void EmcDev::fill_stat_dram_dev0_cumm_banks_active_cke_eq1_lo_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const stat_dram_dev0_cumm_banks_active_cke_eq1_lo_u old_value_t = { .reg32 = value };
    const stat_dram_dev0_cumm_banks_active_cke_eq1_lo_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: dev0_cumm_banks_active_cke_eq1_lo:32", "", 32, old_value_t.dev0_cumm_banks_active_cke_eq1_lo, new_value_t.dev0_cumm_banks_active_cke_eq1_lo };
    m_bit_details_model.bits.append(entry);
}

#define STAT_DRAM_DEV0_CUMM_BANKS_ACTIVE_CKE_EQ1_HI_OFFSET 0x1D8
#define STAT_DRAM_DEV0_CUMM_BANKS_ACTIVE_CKE_EQ1_HI_UNDEFMASK 0xFFFFFF00
union stat_dram_dev0_cumm_banks_active_cke_eq1_hi_u {
    struct {
        unsigned int dev0_cumm_banks_active_cke_eq1_hi:8;
        unsigned int undefined_bits_8_31:24;
    };

    u_int32_t reg32;
};

void EmcDev::fill_stat_dram_dev0_cumm_banks_active_cke_eq1_hi_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const stat_dram_dev0_cumm_banks_active_cke_eq1_hi_u old_value_t = { .reg32 = value };
    const stat_dram_dev0_cumm_banks_active_cke_eq1_hi_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: dev0_cumm_banks_active_cke_eq1_hi:8", "", 8, old_value_t.dev0_cumm_banks_active_cke_eq1_hi, new_value_t.dev0_cumm_banks_active_cke_eq1_hi };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_31:24", "", 24, old_value_t.undefined_bits_8_31, new_value_t.undefined_bits_8_31 };
    m_bit_details_model.bits.append(entry);
}

#define STAT_DRAM_DEV0_CUMM_BANKS_ACTIVE_CKE_EQ0_LO_OFFSET 0x1DC
#define STAT_DRAM_DEV0_CUMM_BANKS_ACTIVE_CKE_EQ0_LO_UNDEFMASK 0x00000000
union stat_dram_dev0_cumm_banks_active_cke_eq0_lo_u {
    struct {
        unsigned int dev0_cumm_banks_active_cke_eq0_lo:32;
    };

    u_int32_t reg32;
};

void EmcDev::fill_stat_dram_dev0_cumm_banks_active_cke_eq0_lo_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const stat_dram_dev0_cumm_banks_active_cke_eq0_lo_u old_value_t = { .reg32 = value };
    const stat_dram_dev0_cumm_banks_active_cke_eq0_lo_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: dev0_cumm_banks_active_cke_eq0_lo:32", "", 32, old_value_t.dev0_cumm_banks_active_cke_eq0_lo, new_value_t.dev0_cumm_banks_active_cke_eq0_lo };
    m_bit_details_model.bits.append(entry);
}

#define STAT_DRAM_DEV0_CUMM_BANKS_ACTIVE_CKE_EQ0_HI_OFFSET 0x1E0
#define STAT_DRAM_DEV0_CUMM_BANKS_ACTIVE_CKE_EQ0_HI_UNDEFMASK 0xFFFFFF00
union stat_dram_dev0_cumm_banks_active_cke_eq0_hi_u {
    struct {
        unsigned int dev0_cumm_banks_active_cke_eq0_hi:8;
        unsigned int undefined_bits_8_31:24;
    };

    u_int32_t reg32;
};

void EmcDev::fill_stat_dram_dev0_cumm_banks_active_cke_eq0_hi_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const stat_dram_dev0_cumm_banks_active_cke_eq0_hi_u old_value_t = { .reg32 = value };
    const stat_dram_dev0_cumm_banks_active_cke_eq0_hi_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: dev0_cumm_banks_active_cke_eq0_hi:8", "", 8, old_value_t.dev0_cumm_banks_active_cke_eq0_hi, new_value_t.dev0_cumm_banks_active_cke_eq0_hi };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_31:24", "", 24, old_value_t.undefined_bits_8_31, new_value_t.undefined_bits_8_31 };
    m_bit_details_model.bits.append(entry);
}

#define STAT_DRAM_DEV0_CKE_EQ1_CLKS_LO_OFFSET 0x1E4
#define STAT_DRAM_DEV0_CKE_EQ1_CLKS_LO_UNDEFMASK 0x00000000
union stat_dram_dev0_cke_eq1_clks_lo_u {
    struct {
        unsigned int dev0_cke_eq1_clks_lo:32;
    };

    u_int32_t reg32;
};

void EmcDev::fill_stat_dram_dev0_cke_eq1_clks_lo_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const stat_dram_dev0_cke_eq1_clks_lo_u old_value_t = { .reg32 = value };
    const stat_dram_dev0_cke_eq1_clks_lo_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: dev0_cke_eq1_clks_lo:32", "", 32, old_value_t.dev0_cke_eq1_clks_lo, new_value_t.dev0_cke_eq1_clks_lo };
    m_bit_details_model.bits.append(entry);
}

#define STAT_DRAM_DEV0_CKE_EQ1_CLKS_HI_OFFSET 0x1E8
#define STAT_DRAM_DEV0_CKE_EQ1_CLKS_HI_UNDEFMASK 0xFFFFFF00
union stat_dram_dev0_cke_eq1_clks_hi_u {
    struct {
        unsigned int dev0_cke_eq1_clks_hi:8;
        unsigned int undefined_bits_8_31:24;
    };

    u_int32_t reg32;
};

void EmcDev::fill_stat_dram_dev0_cke_eq1_clks_hi_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const stat_dram_dev0_cke_eq1_clks_hi_u old_value_t = { .reg32 = value };
    const stat_dram_dev0_cke_eq1_clks_hi_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: dev0_cke_eq1_clks_hi:8", "", 8, old_value_t.dev0_cke_eq1_clks_hi, new_value_t.dev0_cke_eq1_clks_hi };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_31:24", "", 24, old_value_t.undefined_bits_8_31, new_value_t.undefined_bits_8_31 };
    m_bit_details_model.bits.append(entry);
}

#define STAT_DRAM_DEV0_EXTCLKS_CKE_EQ1_LO_OFFSET 0x1EC
#define STAT_DRAM_DEV0_EXTCLKS_CKE_EQ1_LO_UNDEFMASK 0x00000000
union stat_dram_dev0_extclks_cke_eq1_lo_u {
    struct {
        unsigned int dev0_extclks_cke_eq1_lo:32;
    };

    u_int32_t reg32;
};

void EmcDev::fill_stat_dram_dev0_extclks_cke_eq1_lo_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const stat_dram_dev0_extclks_cke_eq1_lo_u old_value_t = { .reg32 = value };
    const stat_dram_dev0_extclks_cke_eq1_lo_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: dev0_extclks_cke_eq1_lo:32", "", 32, old_value_t.dev0_extclks_cke_eq1_lo, new_value_t.dev0_extclks_cke_eq1_lo };
    m_bit_details_model.bits.append(entry);
}

#define STAT_DRAM_DEV0_EXTCLKS_CKE_EQ1_HI_OFFSET 0x1F0
#define STAT_DRAM_DEV0_EXTCLKS_CKE_EQ1_HI_UNDEFMASK 0xFFFFFF00
union stat_dram_dev0_extclks_cke_eq1_hi_u {
    struct {
        unsigned int dev0_extclks_cke_eq1_hi:8;
        unsigned int undefined_bits_8_31:24;
    };

    u_int32_t reg32;
};

void EmcDev::fill_stat_dram_dev0_extclks_cke_eq1_hi_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const stat_dram_dev0_extclks_cke_eq1_hi_u old_value_t = { .reg32 = value };
    const stat_dram_dev0_extclks_cke_eq1_hi_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: dev0_extclks_cke_eq1_hi:8", "", 8, old_value_t.dev0_extclks_cke_eq1_hi, new_value_t.dev0_extclks_cke_eq1_hi };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_31:24", "", 24, old_value_t.undefined_bits_8_31, new_value_t.undefined_bits_8_31 };
    m_bit_details_model.bits.append(entry);
}

#define STAT_DRAM_DEV0_EXTCLKS_CKE_EQ0_LO_OFFSET 0x1F4
#define STAT_DRAM_DEV0_EXTCLKS_CKE_EQ0_LO_UNDEFMASK 0x00000000
union stat_dram_dev0_extclks_cke_eq0_lo_u {
    struct {
        unsigned int dev0_extclks_cke_eq0_lo:32;
    };

    u_int32_t reg32;
};

void EmcDev::fill_stat_dram_dev0_extclks_cke_eq0_lo_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const stat_dram_dev0_extclks_cke_eq0_lo_u old_value_t = { .reg32 = value };
    const stat_dram_dev0_extclks_cke_eq0_lo_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: dev0_extclks_cke_eq0_lo:32", "", 32, old_value_t.dev0_extclks_cke_eq0_lo, new_value_t.dev0_extclks_cke_eq0_lo };
    m_bit_details_model.bits.append(entry);
}

#define STAT_DRAM_DEV0_EXTCLKS_CKE_EQ0_HI_OFFSET 0x1F8
#define STAT_DRAM_DEV0_EXTCLKS_CKE_EQ0_HI_UNDEFMASK 0xFFFFFF00
union stat_dram_dev0_extclks_cke_eq0_hi_u {
    struct {
        unsigned int dev0_extclks_cke_eq0_hi:8;
        unsigned int undefined_bits_8_31:24;
    };

    u_int32_t reg32;
};

void EmcDev::fill_stat_dram_dev0_extclks_cke_eq0_hi_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const stat_dram_dev0_extclks_cke_eq0_hi_u old_value_t = { .reg32 = value };
    const stat_dram_dev0_extclks_cke_eq0_hi_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: dev0_extclks_cke_eq0_hi:8", "", 8, old_value_t.dev0_extclks_cke_eq0_hi, new_value_t.dev0_extclks_cke_eq0_hi };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_31:24", "", 24, old_value_t.undefined_bits_8_31, new_value_t.undefined_bits_8_31 };
    m_bit_details_model.bits.append(entry);
}

#define STAT_DRAM_DEV1_ACTIVATE_CNT_LO_OFFSET 0x1FC
#define STAT_DRAM_DEV1_ACTIVATE_CNT_LO_UNDEFMASK 0x00000000
union stat_dram_dev1_activate_cnt_lo_u {
    struct {
        unsigned int dev1_activate_cnt_lo:32;
    };

    u_int32_t reg32;
};

void EmcDev::fill_stat_dram_dev1_activate_cnt_lo_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const stat_dram_dev1_activate_cnt_lo_u old_value_t = { .reg32 = value };
    const stat_dram_dev1_activate_cnt_lo_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: dev1_activate_cnt_lo:32", "", 32, old_value_t.dev1_activate_cnt_lo, new_value_t.dev1_activate_cnt_lo };
    m_bit_details_model.bits.append(entry);
}

#define STAT_DRAM_DEV1_ACTIVATE_CNT_HI_OFFSET 0x200
#define STAT_DRAM_DEV1_ACTIVATE_CNT_HI_UNDEFMASK 0xFFFFFF00
union stat_dram_dev1_activate_cnt_hi_u {
    struct {
        unsigned int dev1_activate_cnt_hi:8;
        unsigned int undefined_bits_8_31:24;
    };

    u_int32_t reg32;
};

void EmcDev::fill_stat_dram_dev1_activate_cnt_hi_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const stat_dram_dev1_activate_cnt_hi_u old_value_t = { .reg32 = value };
    const stat_dram_dev1_activate_cnt_hi_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: dev1_activate_cnt_hi:8", "", 8, old_value_t.dev1_activate_cnt_hi, new_value_t.dev1_activate_cnt_hi };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_31:24", "", 24, old_value_t.undefined_bits_8_31, new_value_t.undefined_bits_8_31 };
    m_bit_details_model.bits.append(entry);
}

#define STAT_DRAM_DEV1_READ_CNT_LO_OFFSET 0x204
#define STAT_DRAM_DEV1_READ_CNT_LO_UNDEFMASK 0x00000000
union stat_dram_dev1_read_cnt_lo_u {
    struct {
        unsigned int dev1_read_cnt_lo:32;
    };

    u_int32_t reg32;
};

void EmcDev::fill_stat_dram_dev1_read_cnt_lo_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const stat_dram_dev1_read_cnt_lo_u old_value_t = { .reg32 = value };
    const stat_dram_dev1_read_cnt_lo_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: dev1_read_cnt_lo:32", "", 32, old_value_t.dev1_read_cnt_lo, new_value_t.dev1_read_cnt_lo };
    m_bit_details_model.bits.append(entry);
}

#define STAT_DRAM_DEV1_READ_CNT_HI_OFFSET 0x208
#define STAT_DRAM_DEV1_READ_CNT_HI_UNDEFMASK 0xFFFFFF00
union stat_dram_dev1_read_cnt_hi_u {
    struct {
        unsigned int dev1_read_cnt_hi:8;
        unsigned int undefined_bits_8_31:24;
    };

    u_int32_t reg32;
};

void EmcDev::fill_stat_dram_dev1_read_cnt_hi_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const stat_dram_dev1_read_cnt_hi_u old_value_t = { .reg32 = value };
    const stat_dram_dev1_read_cnt_hi_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: dev1_read_cnt_hi:8", "", 8, old_value_t.dev1_read_cnt_hi, new_value_t.dev1_read_cnt_hi };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_31:24", "", 24, old_value_t.undefined_bits_8_31, new_value_t.undefined_bits_8_31 };
    m_bit_details_model.bits.append(entry);
}

#define STAT_DRAM_DEV1_WRITE_CNT_LO_OFFSET 0x20C
#define STAT_DRAM_DEV1_WRITE_CNT_LO_UNDEFMASK 0x00000000
union stat_dram_dev1_write_cnt_lo_u {
    struct {
        unsigned int dev1_write_cnt_lo:32;
    };

    u_int32_t reg32;
};

void EmcDev::fill_stat_dram_dev1_write_cnt_lo_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const stat_dram_dev1_write_cnt_lo_u old_value_t = { .reg32 = value };
    const stat_dram_dev1_write_cnt_lo_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: dev1_write_cnt_lo:32", "", 32, old_value_t.dev1_write_cnt_lo, new_value_t.dev1_write_cnt_lo };
    m_bit_details_model.bits.append(entry);
}

#define STAT_DRAM_DEV1_WRITE_CNT_HI_OFFSET 0x210
#define STAT_DRAM_DEV1_WRITE_CNT_HI_UNDEFMASK 0xFFFFFF00
union stat_dram_dev1_write_cnt_hi_u {
    struct {
        unsigned int dev1_write_cnt_hi:8;
        unsigned int undefined_bits_8_31:24;
    };

    u_int32_t reg32;
};

void EmcDev::fill_stat_dram_dev1_write_cnt_hi_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const stat_dram_dev1_write_cnt_hi_u old_value_t = { .reg32 = value };
    const stat_dram_dev1_write_cnt_hi_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: dev1_write_cnt_hi:8", "", 8, old_value_t.dev1_write_cnt_hi, new_value_t.dev1_write_cnt_hi };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_31:24", "", 24, old_value_t.undefined_bits_8_31, new_value_t.undefined_bits_8_31 };
    m_bit_details_model.bits.append(entry);
}

#define STAT_DRAM_DEV1_REF_CNT_LO_OFFSET 0x214
#define STAT_DRAM_DEV1_REF_CNT_LO_UNDEFMASK 0x00000000
union stat_dram_dev1_ref_cnt_lo_u {
    struct {
        unsigned int dev1_ref_cnt_lo:32;
    };

    u_int32_t reg32;
};

void EmcDev::fill_stat_dram_dev1_ref_cnt_lo_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const stat_dram_dev1_ref_cnt_lo_u old_value_t = { .reg32 = value };
    const stat_dram_dev1_ref_cnt_lo_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: dev1_ref_cnt_lo:32", "", 32, old_value_t.dev1_ref_cnt_lo, new_value_t.dev1_ref_cnt_lo };
    m_bit_details_model.bits.append(entry);
}

#define STAT_DRAM_DEV1_REF_CNT_HI_OFFSET 0x218
#define STAT_DRAM_DEV1_REF_CNT_HI_UNDEFMASK 0xFFFFFF00
union stat_dram_dev1_ref_cnt_hi_u {
    struct {
        unsigned int dev1_ref_cnt_hi:8;
        unsigned int undefined_bits_8_31:24;
    };

    u_int32_t reg32;
};

void EmcDev::fill_stat_dram_dev1_ref_cnt_hi_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const stat_dram_dev1_ref_cnt_hi_u old_value_t = { .reg32 = value };
    const stat_dram_dev1_ref_cnt_hi_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: dev1_ref_cnt_hi:8", "", 8, old_value_t.dev1_ref_cnt_hi, new_value_t.dev1_ref_cnt_hi };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_31:24", "", 24, old_value_t.undefined_bits_8_31, new_value_t.undefined_bits_8_31 };
    m_bit_details_model.bits.append(entry);
}

#define STAT_DRAM_DEV1_CUMM_BANKS_ACTIVE_CKE_EQ1_LO_OFFSET 0x21C
#define STAT_DRAM_DEV1_CUMM_BANKS_ACTIVE_CKE_EQ1_LO_UNDEFMASK 0x00000000
union stat_dram_dev1_cumm_banks_active_cke_eq1_lo_u {
    struct {
        unsigned int dev1_cumm_banks_active_cke_eq1_lo:32;
    };

    u_int32_t reg32;
};

void EmcDev::fill_stat_dram_dev1_cumm_banks_active_cke_eq1_lo_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const stat_dram_dev1_cumm_banks_active_cke_eq1_lo_u old_value_t = { .reg32 = value };
    const stat_dram_dev1_cumm_banks_active_cke_eq1_lo_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: dev1_cumm_banks_active_cke_eq1_lo:32", "", 32, old_value_t.dev1_cumm_banks_active_cke_eq1_lo, new_value_t.dev1_cumm_banks_active_cke_eq1_lo };
    m_bit_details_model.bits.append(entry);
}

#define STAT_DRAM_DEV1_CUMM_BANKS_ACTIVE_CKE_EQ1_HI_OFFSET 0x220
#define STAT_DRAM_DEV1_CUMM_BANKS_ACTIVE_CKE_EQ1_HI_UNDEFMASK 0xFFFFFF00
union stat_dram_dev1_cumm_banks_active_cke_eq1_hi_u {
    struct {
        unsigned int dev1_cumm_banks_active_cke_eq1_hi:8;
        unsigned int undefined_bits_8_31:24;
    };

    u_int32_t reg32;
};

void EmcDev::fill_stat_dram_dev1_cumm_banks_active_cke_eq1_hi_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const stat_dram_dev1_cumm_banks_active_cke_eq1_hi_u old_value_t = { .reg32 = value };
    const stat_dram_dev1_cumm_banks_active_cke_eq1_hi_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: dev1_cumm_banks_active_cke_eq1_hi:8", "", 8, old_value_t.dev1_cumm_banks_active_cke_eq1_hi, new_value_t.dev1_cumm_banks_active_cke_eq1_hi };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_31:24", "", 24, old_value_t.undefined_bits_8_31, new_value_t.undefined_bits_8_31 };
    m_bit_details_model.bits.append(entry);
}

#define STAT_DRAM_DEV1_CUMM_BANKS_ACTIVE_CKE_EQ0_LO_OFFSET 0x224
#define STAT_DRAM_DEV1_CUMM_BANKS_ACTIVE_CKE_EQ0_LO_UNDEFMASK 0x00000000
union stat_dram_dev1_cumm_banks_active_cke_eq0_lo_u {
    struct {
        unsigned int dev1_cumm_banks_active_cke_eq0_lo:32;
    };

    u_int32_t reg32;
};

void EmcDev::fill_stat_dram_dev1_cumm_banks_active_cke_eq0_lo_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const stat_dram_dev1_cumm_banks_active_cke_eq0_lo_u old_value_t = { .reg32 = value };
    const stat_dram_dev1_cumm_banks_active_cke_eq0_lo_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: dev1_cumm_banks_active_cke_eq0_lo:32", "", 32, old_value_t.dev1_cumm_banks_active_cke_eq0_lo, new_value_t.dev1_cumm_banks_active_cke_eq0_lo };
    m_bit_details_model.bits.append(entry);
}

#define STAT_DRAM_DEV1_CUMM_BANKS_ACTIVE_CKE_EQ0_HI_OFFSET 0x228
#define STAT_DRAM_DEV1_CUMM_BANKS_ACTIVE_CKE_EQ0_HI_UNDEFMASK 0xFFFFFF00
union stat_dram_dev1_cumm_banks_active_cke_eq0_hi_u {
    struct {
        unsigned int dev1_cumm_banks_active_cke_eq0_hi:8;
        unsigned int undefined_bits_8_31:24;
    };

    u_int32_t reg32;
};

void EmcDev::fill_stat_dram_dev1_cumm_banks_active_cke_eq0_hi_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const stat_dram_dev1_cumm_banks_active_cke_eq0_hi_u old_value_t = { .reg32 = value };
    const stat_dram_dev1_cumm_banks_active_cke_eq0_hi_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: dev1_cumm_banks_active_cke_eq0_hi:8", "", 8, old_value_t.dev1_cumm_banks_active_cke_eq0_hi, new_value_t.dev1_cumm_banks_active_cke_eq0_hi };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_31:24", "", 24, old_value_t.undefined_bits_8_31, new_value_t.undefined_bits_8_31 };
    m_bit_details_model.bits.append(entry);
}

#define STAT_DRAM_DEV1_CKE_EQ1_CLKS_LO_OFFSET 0x22C
#define STAT_DRAM_DEV1_CKE_EQ1_CLKS_LO_UNDEFMASK 0x00000000
union stat_dram_dev1_cke_eq1_clks_lo_u {
    struct {
        unsigned int dev1_cke_eq1_clks_lo:32;
    };

    u_int32_t reg32;
};

void EmcDev::fill_stat_dram_dev1_cke_eq1_clks_lo_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const stat_dram_dev1_cke_eq1_clks_lo_u old_value_t = { .reg32 = value };
    const stat_dram_dev1_cke_eq1_clks_lo_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: dev1_cke_eq1_clks_lo:32", "", 32, old_value_t.dev1_cke_eq1_clks_lo, new_value_t.dev1_cke_eq1_clks_lo };
    m_bit_details_model.bits.append(entry);
}

#define STAT_DRAM_DEV1_CKE_EQ1_CLKS_HI_OFFSET 0x230
#define STAT_DRAM_DEV1_CKE_EQ1_CLKS_HI_UNDEFMASK 0xFFFFFF00
union stat_dram_dev1_cke_eq1_clks_hi_u {
    struct {
        unsigned int dev1_cke_eq1_clks_hi:8;
        unsigned int undefined_bits_8_31:24;
    };

    u_int32_t reg32;
};

void EmcDev::fill_stat_dram_dev1_cke_eq1_clks_hi_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const stat_dram_dev1_cke_eq1_clks_hi_u old_value_t = { .reg32 = value };
    const stat_dram_dev1_cke_eq1_clks_hi_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: dev1_cke_eq1_clks_hi:8", "", 8, old_value_t.dev1_cke_eq1_clks_hi, new_value_t.dev1_cke_eq1_clks_hi };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_31:24", "", 24, old_value_t.undefined_bits_8_31, new_value_t.undefined_bits_8_31 };
    m_bit_details_model.bits.append(entry);
}

#define STAT_DRAM_DEV1_EXTCLKS_CKE_EQ1_LO_OFFSET 0x234
#define STAT_DRAM_DEV1_EXTCLKS_CKE_EQ1_LO_UNDEFMASK 0x00000000
union stat_dram_dev1_extclks_cke_eq1_lo_u {
    struct {
        unsigned int dev1_extclks_cke_eq1_lo:32;
    };

    u_int32_t reg32;
};

void EmcDev::fill_stat_dram_dev1_extclks_cke_eq1_lo_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const stat_dram_dev1_extclks_cke_eq1_lo_u old_value_t = { .reg32 = value };
    const stat_dram_dev1_extclks_cke_eq1_lo_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: dev1_extclks_cke_eq1_lo:32", "", 32, old_value_t.dev1_extclks_cke_eq1_lo, new_value_t.dev1_extclks_cke_eq1_lo };
    m_bit_details_model.bits.append(entry);
}

#define STAT_DRAM_DEV1_EXTCLKS_CKE_EQ1_HI_OFFSET 0x238
#define STAT_DRAM_DEV1_EXTCLKS_CKE_EQ1_HI_UNDEFMASK 0xFFFFFF00
union stat_dram_dev1_extclks_cke_eq1_hi_u {
    struct {
        unsigned int dev1_extclks_cke_eq1_hi:8;
        unsigned int undefined_bits_8_31:24;
    };

    u_int32_t reg32;
};

void EmcDev::fill_stat_dram_dev1_extclks_cke_eq1_hi_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const stat_dram_dev1_extclks_cke_eq1_hi_u old_value_t = { .reg32 = value };
    const stat_dram_dev1_extclks_cke_eq1_hi_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: dev1_extclks_cke_eq1_hi:8", "", 8, old_value_t.dev1_extclks_cke_eq1_hi, new_value_t.dev1_extclks_cke_eq1_hi };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_31:24", "", 24, old_value_t.undefined_bits_8_31, new_value_t.undefined_bits_8_31 };
    m_bit_details_model.bits.append(entry);
}

#define STAT_DRAM_DEV1_EXTCLKS_CKE_EQ0_LO_OFFSET 0x23C
#define STAT_DRAM_DEV1_EXTCLKS_CKE_EQ0_LO_UNDEFMASK 0x00000000
union stat_dram_dev1_extclks_cke_eq0_lo_u {
    struct {
        unsigned int dev1_extclks_cke_eq0_lo:32;
    };

    u_int32_t reg32;
};

void EmcDev::fill_stat_dram_dev1_extclks_cke_eq0_lo_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const stat_dram_dev1_extclks_cke_eq0_lo_u old_value_t = { .reg32 = value };
    const stat_dram_dev1_extclks_cke_eq0_lo_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: dev1_extclks_cke_eq0_lo:32", "", 32, old_value_t.dev1_extclks_cke_eq0_lo, new_value_t.dev1_extclks_cke_eq0_lo };
    m_bit_details_model.bits.append(entry);
}

#define STAT_DRAM_DEV1_EXTCLKS_CKE_EQ0_HI_OFFSET 0x240
#define STAT_DRAM_DEV1_EXTCLKS_CKE_EQ0_HI_UNDEFMASK 0xFFFFFF00
union stat_dram_dev1_extclks_cke_eq0_hi_u {
    struct {
        unsigned int dev1_extclks_cke_eq0_hi:8;
        unsigned int undefined_bits_8_31:24;
    };

    u_int32_t reg32;
};

void EmcDev::fill_stat_dram_dev1_extclks_cke_eq0_hi_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const stat_dram_dev1_extclks_cke_eq0_hi_u old_value_t = { .reg32 = value };
    const stat_dram_dev1_extclks_cke_eq0_hi_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: dev1_extclks_cke_eq0_hi:8", "", 8, old_value_t.dev1_extclks_cke_eq0_hi, new_value_t.dev1_extclks_cke_eq0_hi };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_31:24", "", 24, old_value_t.undefined_bits_8_31, new_value_t.undefined_bits_8_31 };
    m_bit_details_model.bits.append(entry);
}

#define STAT_DRAM_DEV0_NO_BANKS_ACTIVE_CKE_EQ1_LO_OFFSET 0x244
#define STAT_DRAM_DEV0_NO_BANKS_ACTIVE_CKE_EQ1_LO_UNDEFMASK 0x00000000
union stat_dram_dev0_no_banks_active_cke_eq1_lo_u {
    struct {
        unsigned int dev0_no_banks_active_cke_eq1_lo:32;
    };

    u_int32_t reg32;
};

void EmcDev::fill_stat_dram_dev0_no_banks_active_cke_eq1_lo_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const stat_dram_dev0_no_banks_active_cke_eq1_lo_u old_value_t = { .reg32 = value };
    const stat_dram_dev0_no_banks_active_cke_eq1_lo_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: dev0_no_banks_active_cke_eq1_lo:32", "", 32, old_value_t.dev0_no_banks_active_cke_eq1_lo, new_value_t.dev0_no_banks_active_cke_eq1_lo };
    m_bit_details_model.bits.append(entry);
}

#define STAT_DRAM_DEV0_NO_BANKS_ACTIVE_CKE_EQ1_HI_OFFSET 0x248
#define STAT_DRAM_DEV0_NO_BANKS_ACTIVE_CKE_EQ1_HI_UNDEFMASK 0xFFFFFF00
union stat_dram_dev0_no_banks_active_cke_eq1_hi_u {
    struct {
        unsigned int dev0_no_banks_active_cke_eq1_hi:8;
        unsigned int undefined_bits_8_31:24;
    };

    u_int32_t reg32;
};

void EmcDev::fill_stat_dram_dev0_no_banks_active_cke_eq1_hi_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const stat_dram_dev0_no_banks_active_cke_eq1_hi_u old_value_t = { .reg32 = value };
    const stat_dram_dev0_no_banks_active_cke_eq1_hi_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: dev0_no_banks_active_cke_eq1_hi:8", "", 8, old_value_t.dev0_no_banks_active_cke_eq1_hi, new_value_t.dev0_no_banks_active_cke_eq1_hi };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_31:24", "", 24, old_value_t.undefined_bits_8_31, new_value_t.undefined_bits_8_31 };
    m_bit_details_model.bits.append(entry);
}

#define STAT_DRAM_DEV0_NO_BANKS_ACTIVE_CKE_EQ0_LO_OFFSET 0x24C
#define STAT_DRAM_DEV0_NO_BANKS_ACTIVE_CKE_EQ0_LO_UNDEFMASK 0x00000000
union stat_dram_dev0_no_banks_active_cke_eq0_lo_u {
    struct {
        unsigned int dev0_no_banks_active_cke_eq0_lo:32;
    };

    u_int32_t reg32;
};

void EmcDev::fill_stat_dram_dev0_no_banks_active_cke_eq0_lo_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const stat_dram_dev0_no_banks_active_cke_eq0_lo_u old_value_t = { .reg32 = value };
    const stat_dram_dev0_no_banks_active_cke_eq0_lo_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: dev0_no_banks_active_cke_eq0_lo:32", "", 32, old_value_t.dev0_no_banks_active_cke_eq0_lo, new_value_t.dev0_no_banks_active_cke_eq0_lo };
    m_bit_details_model.bits.append(entry);
}

#define STAT_DRAM_DEV0_NO_BANKS_ACTIVE_CKE_EQ0_HI_OFFSET 0x250
#define STAT_DRAM_DEV0_NO_BANKS_ACTIVE_CKE_EQ0_HI_UNDEFMASK 0xFFFFFF00
union stat_dram_dev0_no_banks_active_cke_eq0_hi_u {
    struct {
        unsigned int dev0_no_banks_active_cke_eq0_hi:8;
        unsigned int undefined_bits_8_31:24;
    };

    u_int32_t reg32;
};

void EmcDev::fill_stat_dram_dev0_no_banks_active_cke_eq0_hi_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const stat_dram_dev0_no_banks_active_cke_eq0_hi_u old_value_t = { .reg32 = value };
    const stat_dram_dev0_no_banks_active_cke_eq0_hi_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: dev0_no_banks_active_cke_eq0_hi:8", "", 8, old_value_t.dev0_no_banks_active_cke_eq0_hi, new_value_t.dev0_no_banks_active_cke_eq0_hi };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_31:24", "", 24, old_value_t.undefined_bits_8_31, new_value_t.undefined_bits_8_31 };
    m_bit_details_model.bits.append(entry);
}

#define STAT_DRAM_DEV1_NO_BANKS_ACTIVE_CKE_EQ1_LO_OFFSET 0x254
#define STAT_DRAM_DEV1_NO_BANKS_ACTIVE_CKE_EQ1_LO_UNDEFMASK 0x00000000
union stat_dram_dev1_no_banks_active_cke_eq1_lo_u {
    struct {
        unsigned int dev1_no_banks_active_cke_eq1_lo:32;
    };

    u_int32_t reg32;
};

void EmcDev::fill_stat_dram_dev1_no_banks_active_cke_eq1_lo_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const stat_dram_dev1_no_banks_active_cke_eq1_lo_u old_value_t = { .reg32 = value };
    const stat_dram_dev1_no_banks_active_cke_eq1_lo_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: dev1_no_banks_active_cke_eq1_lo:32", "", 32, old_value_t.dev1_no_banks_active_cke_eq1_lo, new_value_t.dev1_no_banks_active_cke_eq1_lo };
    m_bit_details_model.bits.append(entry);
}

#define STAT_DRAM_DEV1_NO_BANKS_ACTIVE_CKE_EQ1_HI_OFFSET 0x258
#define STAT_DRAM_DEV1_NO_BANKS_ACTIVE_CKE_EQ1_HI_UNDEFMASK 0xFFFFFF00
union stat_dram_dev1_no_banks_active_cke_eq1_hi_u {
    struct {
        unsigned int dev1_no_banks_active_cke_eq1_hi:8;
        unsigned int undefined_bits_8_31:24;
    };

    u_int32_t reg32;
};

void EmcDev::fill_stat_dram_dev1_no_banks_active_cke_eq1_hi_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const stat_dram_dev1_no_banks_active_cke_eq1_hi_u old_value_t = { .reg32 = value };
    const stat_dram_dev1_no_banks_active_cke_eq1_hi_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: dev1_no_banks_active_cke_eq1_hi:8", "", 8, old_value_t.dev1_no_banks_active_cke_eq1_hi, new_value_t.dev1_no_banks_active_cke_eq1_hi };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_31:24", "", 24, old_value_t.undefined_bits_8_31, new_value_t.undefined_bits_8_31 };
    m_bit_details_model.bits.append(entry);
}

#define STAT_DRAM_DEV1_NO_BANKS_ACTIVE_CKE_EQ0_LO_OFFSET 0x25C
#define STAT_DRAM_DEV1_NO_BANKS_ACTIVE_CKE_EQ0_LO_UNDEFMASK 0x00000000
union stat_dram_dev1_no_banks_active_cke_eq0_lo_u {
    struct {
        unsigned int dev1_no_banks_active_cke_eq0_lo:32;
    };

    u_int32_t reg32;
};

void EmcDev::fill_stat_dram_dev1_no_banks_active_cke_eq0_lo_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const stat_dram_dev1_no_banks_active_cke_eq0_lo_u old_value_t = { .reg32 = value };
    const stat_dram_dev1_no_banks_active_cke_eq0_lo_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: dev1_no_banks_active_cke_eq0_lo:32", "", 32, old_value_t.dev1_no_banks_active_cke_eq0_lo, new_value_t.dev1_no_banks_active_cke_eq0_lo };
    m_bit_details_model.bits.append(entry);
}

#define STAT_DRAM_DEV1_NO_BANKS_ACTIVE_CKE_EQ0_HI_OFFSET 0x260
#define STAT_DRAM_DEV1_NO_BANKS_ACTIVE_CKE_EQ0_HI_UNDEFMASK 0xFFFFFF00
union stat_dram_dev1_no_banks_active_cke_eq0_hi_u {
    struct {
        unsigned int dev1_no_banks_active_cke_eq0_hi:8;
        unsigned int undefined_bits_8_31:24;
    };

    u_int32_t reg32;
};

void EmcDev::fill_stat_dram_dev1_no_banks_active_cke_eq0_hi_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const stat_dram_dev1_no_banks_active_cke_eq0_hi_u old_value_t = { .reg32 = value };
    const stat_dram_dev1_no_banks_active_cke_eq0_hi_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: dev1_no_banks_active_cke_eq0_hi:8", "", 8, old_value_t.dev1_no_banks_active_cke_eq0_hi, new_value_t.dev1_no_banks_active_cke_eq0_hi };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_31:24", "", 24, old_value_t.undefined_bits_8_31, new_value_t.undefined_bits_8_31 };
    m_bit_details_model.bits.append(entry);
}

#define CFG_CLKTRIM_OFFSET 0x2D0
#define CFG_CLKTRIM_UNDEFMASK 0xC0000000
union cfg_clktrim_u {
    struct {
        unsigned int cfg_data0_clktrim:6;
        unsigned int cfg_data1_clktrim:6;
        unsigned int cfg_data2_clktrim:6;
        unsigned int cfg_data3_clktrim:6;
        unsigned int cfg_mclk_addr_clktrim:6;
        unsigned int undefined_bits_30_31:2;
    };

    u_int32_t reg32;
};

void EmcDev::fill_cfg_clktrim_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const cfg_clktrim_u old_value_t = { .reg32 = value };
    const cfg_clktrim_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: cfg_data0_clktrim:6", "", 6, old_value_t.cfg_data0_clktrim, new_value_t.cfg_data0_clktrim };
    m_bit_details_model.bits.append(entry);
    entry = { "06: cfg_data1_clktrim:6", "", 6, old_value_t.cfg_data1_clktrim, new_value_t.cfg_data1_clktrim };
    m_bit_details_model.bits.append(entry);
    entry = { "12: cfg_data2_clktrim:6", "", 6, old_value_t.cfg_data2_clktrim, new_value_t.cfg_data2_clktrim };
    m_bit_details_model.bits.append(entry);
    entry = { "18: cfg_data3_clktrim:6", "", 6, old_value_t.cfg_data3_clktrim, new_value_t.cfg_data3_clktrim };
    m_bit_details_model.bits.append(entry);
    entry = { "24: cfg_mclk_addr_clktrim:6", "", 6, old_value_t.cfg_mclk_addr_clktrim, new_value_t.cfg_mclk_addr_clktrim };
    m_bit_details_model.bits.append(entry);
    entry = { "30: undefined_bits_30_31:2", "", 2, old_value_t.undefined_bits_30_31, new_value_t.undefined_bits_30_31 };
    m_bit_details_model.bits.append(entry);
}

#define CFG_CLKTRIM_1_OFFSET 0x2D4
#define CFG_CLKTRIM_1_UNDEFMASK 0xC0000000
union cfg_clktrim_1_u {
    struct {
        unsigned int cfg_dqs0_clktrim:6;
        unsigned int cfg_dqs1_clktrim:6;
        unsigned int cfg_dqs2_clktrim:6;
        unsigned int cfg_dqs3_clktrim:6;
        unsigned int cfg_mclk_clktrim:6;
        unsigned int undefined_bits_30_31:2;
    };

    u_int32_t reg32;
};

void EmcDev::fill_cfg_clktrim_1_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const cfg_clktrim_1_u old_value_t = { .reg32 = value };
    const cfg_clktrim_1_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: cfg_dqs0_clktrim:6", "", 6, old_value_t.cfg_dqs0_clktrim, new_value_t.cfg_dqs0_clktrim };
    m_bit_details_model.bits.append(entry);
    entry = { "06: cfg_dqs1_clktrim:6", "", 6, old_value_t.cfg_dqs1_clktrim, new_value_t.cfg_dqs1_clktrim };
    m_bit_details_model.bits.append(entry);
    entry = { "12: cfg_dqs2_clktrim:6", "", 6, old_value_t.cfg_dqs2_clktrim, new_value_t.cfg_dqs2_clktrim };
    m_bit_details_model.bits.append(entry);
    entry = { "18: cfg_dqs3_clktrim:6", "", 6, old_value_t.cfg_dqs3_clktrim, new_value_t.cfg_dqs3_clktrim };
    m_bit_details_model.bits.append(entry);
    entry = { "24: cfg_mclk_clktrim:6", "", 6, old_value_t.cfg_mclk_clktrim, new_value_t.cfg_mclk_clktrim };
    m_bit_details_model.bits.append(entry);
    entry = { "30: undefined_bits_30_31:2", "", 2, old_value_t.undefined_bits_30_31, new_value_t.undefined_bits_30_31 };
    m_bit_details_model.bits.append(entry);
}

#define CFG_CLKTRIM_2_OFFSET 0x2D8
#define CFG_CLKTRIM_2_UNDEFMASK 0xC0000000
union cfg_clktrim_2_u {
    struct {
        unsigned int cfg_dq0_clktrim:6;
        unsigned int cfg_dq1_clktrim:6;
        unsigned int cfg_dq2_clktrim:6;
        unsigned int cfg_dq3_clktrim:6;
        unsigned int cfg_cmd_clktrim:6;
        unsigned int undefined_bits_30_31:2;
    };

    u_int32_t reg32;
};

void EmcDev::fill_cfg_clktrim_2_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const cfg_clktrim_2_u old_value_t = { .reg32 = value };
    const cfg_clktrim_2_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: cfg_dq0_clktrim:6", "", 6, old_value_t.cfg_dq0_clktrim, new_value_t.cfg_dq0_clktrim };
    m_bit_details_model.bits.append(entry);
    entry = { "06: cfg_dq1_clktrim:6", "", 6, old_value_t.cfg_dq1_clktrim, new_value_t.cfg_dq1_clktrim };
    m_bit_details_model.bits.append(entry);
    entry = { "12: cfg_dq2_clktrim:6", "", 6, old_value_t.cfg_dq2_clktrim, new_value_t.cfg_dq2_clktrim };
    m_bit_details_model.bits.append(entry);
    entry = { "18: cfg_dq3_clktrim:6", "", 6, old_value_t.cfg_dq3_clktrim, new_value_t.cfg_dq3_clktrim };
    m_bit_details_model.bits.append(entry);
    entry = { "24: cfg_cmd_clktrim:6", "", 6, old_value_t.cfg_cmd_clktrim, new_value_t.cfg_cmd_clktrim };
    m_bit_details_model.bits.append(entry);
    entry = { "30: undefined_bits_30_31:2", "", 2, old_value_t.undefined_bits_30_31, new_value_t.undefined_bits_30_31 };
    m_bit_details_model.bits.append(entry);
}

bool EmcDev::is_offset_valid(const u_int32_t &offset) const
{
    switch (offset) {
    case INTSTATUS_OFFSET:
    case INTMASK_OFFSET:
    case DBG_OFFSET:
    case CFG_OFFSET:
    case ADR_CFG_OFFSET:
    case ADR_CFG_1_OFFSET:
    case REFCTRL_OFFSET:
    case PIN_OFFSET:
    case TIMING_CONTROL_OFFSET:
    case RC_OFFSET:
    case RFC_OFFSET:
    case RAS_OFFSET:
    case RP_OFFSET:
    case R2W_OFFSET:
    case W2R_OFFSET:
    case R2P_OFFSET:
    case W2P_OFFSET:
    case RD_RCD_OFFSET:
    case WR_RCD_OFFSET:
    case RRD_OFFSET:
    case REXT_OFFSET:
    case WDV_OFFSET:
    case QUSE_OFFSET:
    case QRST_OFFSET:
    case QSAFE_OFFSET:
    case RDV_OFFSET:
    case REFRESH_OFFSET:
    case BURST_REFRESH_NUM_OFFSET:
    case PDEX2WR_OFFSET:
    case PDEX2RD_OFFSET:
    case PCHG2PDEN_OFFSET:
    case ACT2PDEN_OFFSET:
    case AR2PDEN_OFFSET:
    case RW2PDEN_OFFSET:
    case TXSR_OFFSET:
    case TCKE_OFFSET:
    case TFAW_OFFSET:
    case TRPAB_OFFSET:
    case TCLKSTABLE_OFFSET:
    case TCLKSTOP_OFFSET:
    case TREFBW_OFFSET:
    case QUSE_EXTRA_OFFSET:
    case ODT_WRITE_OFFSET:
    case ODT_READ_OFFSET:
    case MRS_OFFSET:
    case EMRS_OFFSET:
    case REF_OFFSET:
    case PRE_OFFSET:
    case NOP_OFFSET:
    case SELF_REF_OFFSET:
    case DPD_OFFSET:
    case MRW_OFFSET:
    case MRR_OFFSET:
    case FBIO_CFG1_OFFSET:
    case FBIO_DQSIB_DLY_OFFSET:
    case FBIO_DQSIB_DLY_MSB_OFFSET:
    case FBIO_CFG5_OFFSET:
    case FBIO_QUSE_DLY_OFFSET:
    case FBIO_QUSE_DLY_MSB_OFFSET:
    case FBIO_CFG6_OFFSET:
    case DQS_TRIMMER_RD0_OFFSET:
    case DQS_TRIMMER_RD1_OFFSET:
    case DQS_TRIMMER_RD2_OFFSET:
    case DQS_TRIMMER_RD3_OFFSET:
    case LL_ARB_CONFIG_OFFSET:
    case T_MIN_CRITICAL_HP_OFFSET:
    case T_MIN_CRITICAL_TIMEOUT_OFFSET:
    case T_MIN_LOAD_OFFSET:
    case T_MAX_CRITICAL_HP_OFFSET:
    case T_MAX_CRITICAL_TIMEOUT_OFFSET:
    case T_MAX_LOAD_OFFSET:
    case AUTO_CAL_CONFIG_OFFSET:
    case AUTO_CAL_INTERVAL_OFFSET:
    case AUTO_CAL_STATUS_OFFSET:
    case REQ_CTRL_OFFSET:
    case EMC_STATUS_OFFSET:
    case CFG_2_OFFSET:
    case CFG_DIG_DLL_OFFSET:
    case DLL_XFORM_DQS_OFFSET:
    case DLL_XFORM_QUSE_OFFSET:
    case DIG_DLL_UPPER_STATUS_OFFSET:
    case DIG_DLL_LOWER_STATUS_OFFSET:
    case CTT_TERM_CTRL_OFFSET:
    case ZCAL_REF_CNT_OFFSET:
    case ZCAL_WAIT_CNT_OFFSET:
    case ZCAL_MRW_CMD_OFFSET:
    case CMDQ_OFFSET:
    case FBIO_SPARE_OFFSET:
    case FBIO_WRPTR_EQ_2_OFFSET:
    case CLKEN_OVERRIDE_OFFSET:
    case STAT_CONTROL_OFFSET:
    case STAT_STATUS_OFFSET:
    case STAT_LLMC_ADDR_LOW_OFFSET:
    case STAT_LLMC_ADDR_HIGH_OFFSET:
    case STAT_LLMC_CLOCK_LIMIT_OFFSET:
    case STAT_LLMC_CLOCKS_OFFSET:
    case STAT_LLMC_CONTROL_OFFSET:
    case STAT_LLMC_HIST_LIMIT_OFFSET:
    case STAT_LLMC_COUNT_OFFSET:
    case STAT_LLMC_HIST_OFFSET:
    case STAT_PWR_CLOCK_LIMIT_OFFSET:
    case STAT_PWR_CLOCKS_OFFSET:
    case STAT_PWR_COUNT_OFFSET:
    case STAT_DRAM_CLOCK_LIMIT_LO_OFFSET:
    case STAT_DRAM_CLOCK_LIMIT_HI_OFFSET:
    case STAT_DRAM_CLOCKS_LO_OFFSET:
    case STAT_DRAM_CLOCKS_HI_OFFSET:
    case STAT_DRAM_DEV0_ACTIVATE_CNT_LO_OFFSET:
    case STAT_DRAM_DEV0_ACTIVATE_CNT_HI_OFFSET:
    case STAT_DRAM_DEV0_READ_CNT_LO_OFFSET:
    case STAT_DRAM_DEV0_READ_CNT_HI_OFFSET:
    case STAT_DRAM_DEV0_WRITE_CNT_LO_OFFSET:
    case STAT_DRAM_DEV0_WRITE_CNT_HI_OFFSET:
    case STAT_DRAM_DEV0_REF_CNT_LO_OFFSET:
    case STAT_DRAM_DEV0_REF_CNT_HI_OFFSET:
    case STAT_DRAM_DEV0_CUMM_BANKS_ACTIVE_CKE_EQ1_LO_OFFSET:
    case STAT_DRAM_DEV0_CUMM_BANKS_ACTIVE_CKE_EQ1_HI_OFFSET:
    case STAT_DRAM_DEV0_CUMM_BANKS_ACTIVE_CKE_EQ0_LO_OFFSET:
    case STAT_DRAM_DEV0_CUMM_BANKS_ACTIVE_CKE_EQ0_HI_OFFSET:
    case STAT_DRAM_DEV0_CKE_EQ1_CLKS_LO_OFFSET:
    case STAT_DRAM_DEV0_CKE_EQ1_CLKS_HI_OFFSET:
    case STAT_DRAM_DEV0_EXTCLKS_CKE_EQ1_LO_OFFSET:
    case STAT_DRAM_DEV0_EXTCLKS_CKE_EQ1_HI_OFFSET:
    case STAT_DRAM_DEV0_EXTCLKS_CKE_EQ0_LO_OFFSET:
    case STAT_DRAM_DEV0_EXTCLKS_CKE_EQ0_HI_OFFSET:
    case STAT_DRAM_DEV1_ACTIVATE_CNT_LO_OFFSET:
    case STAT_DRAM_DEV1_ACTIVATE_CNT_HI_OFFSET:
    case STAT_DRAM_DEV1_READ_CNT_LO_OFFSET:
    case STAT_DRAM_DEV1_READ_CNT_HI_OFFSET:
    case STAT_DRAM_DEV1_WRITE_CNT_LO_OFFSET:
    case STAT_DRAM_DEV1_WRITE_CNT_HI_OFFSET:
    case STAT_DRAM_DEV1_REF_CNT_LO_OFFSET:
    case STAT_DRAM_DEV1_REF_CNT_HI_OFFSET:
    case STAT_DRAM_DEV1_CUMM_BANKS_ACTIVE_CKE_EQ1_LO_OFFSET:
    case STAT_DRAM_DEV1_CUMM_BANKS_ACTIVE_CKE_EQ1_HI_OFFSET:
    case STAT_DRAM_DEV1_CUMM_BANKS_ACTIVE_CKE_EQ0_LO_OFFSET:
    case STAT_DRAM_DEV1_CUMM_BANKS_ACTIVE_CKE_EQ0_HI_OFFSET:
    case STAT_DRAM_DEV1_CKE_EQ1_CLKS_LO_OFFSET:
    case STAT_DRAM_DEV1_CKE_EQ1_CLKS_HI_OFFSET:
    case STAT_DRAM_DEV1_EXTCLKS_CKE_EQ1_LO_OFFSET:
    case STAT_DRAM_DEV1_EXTCLKS_CKE_EQ1_HI_OFFSET:
    case STAT_DRAM_DEV1_EXTCLKS_CKE_EQ0_LO_OFFSET:
    case STAT_DRAM_DEV1_EXTCLKS_CKE_EQ0_HI_OFFSET:
    case STAT_DRAM_DEV0_NO_BANKS_ACTIVE_CKE_EQ1_LO_OFFSET:
    case STAT_DRAM_DEV0_NO_BANKS_ACTIVE_CKE_EQ1_HI_OFFSET:
    case STAT_DRAM_DEV0_NO_BANKS_ACTIVE_CKE_EQ0_LO_OFFSET:
    case STAT_DRAM_DEV0_NO_BANKS_ACTIVE_CKE_EQ0_HI_OFFSET:
    case STAT_DRAM_DEV1_NO_BANKS_ACTIVE_CKE_EQ1_LO_OFFSET:
    case STAT_DRAM_DEV1_NO_BANKS_ACTIVE_CKE_EQ1_HI_OFFSET:
    case STAT_DRAM_DEV1_NO_BANKS_ACTIVE_CKE_EQ0_LO_OFFSET:
    case STAT_DRAM_DEV1_NO_BANKS_ACTIVE_CKE_EQ0_HI_OFFSET:
    case CFG_CLKTRIM_OFFSET:
    case CFG_CLKTRIM_1_OFFSET:
    case CFG_CLKTRIM_2_OFFSET:
        return true;
    default:
        break;
    }

    return false;
}

bool EmcDev::is_undef_changed(const u_int32_t &offset,
                                           const u_int32_t &value,
                                           const u_int32_t &new_value) const
{
    switch (offset) {
    case INTSTATUS_OFFSET:
        if ((value ^ new_value) & INTSTATUS_UNDEFMASK)
            return true;
        break;
    case INTMASK_OFFSET:
        if ((value ^ new_value) & INTMASK_UNDEFMASK)
            return true;
        break;
    case DBG_OFFSET:
        if ((value ^ new_value) & DBG_UNDEFMASK)
            return true;
        break;
    case CFG_OFFSET:
        if ((value ^ new_value) & CFG_UNDEFMASK)
            return true;
        break;
    case ADR_CFG_OFFSET:
        if ((value ^ new_value) & ADR_CFG_UNDEFMASK)
            return true;
        break;
    case ADR_CFG_1_OFFSET:
        if ((value ^ new_value) & ADR_CFG_1_UNDEFMASK)
            return true;
        break;
    case REFCTRL_OFFSET:
        if ((value ^ new_value) & REFCTRL_UNDEFMASK)
            return true;
        break;
    case PIN_OFFSET:
        if ((value ^ new_value) & PIN_UNDEFMASK)
            return true;
        break;
    case TIMING_CONTROL_OFFSET:
        if ((value ^ new_value) & TIMING_CONTROL_UNDEFMASK)
            return true;
        break;
    case RC_OFFSET:
        if ((value ^ new_value) & RC_UNDEFMASK)
            return true;
        break;
    case RFC_OFFSET:
        if ((value ^ new_value) & RFC_UNDEFMASK)
            return true;
        break;
    case RAS_OFFSET:
        if ((value ^ new_value) & RAS_UNDEFMASK)
            return true;
        break;
    case RP_OFFSET:
        if ((value ^ new_value) & RP_UNDEFMASK)
            return true;
        break;
    case R2W_OFFSET:
        if ((value ^ new_value) & R2W_UNDEFMASK)
            return true;
        break;
    case W2R_OFFSET:
        if ((value ^ new_value) & W2R_UNDEFMASK)
            return true;
        break;
    case R2P_OFFSET:
        if ((value ^ new_value) & R2P_UNDEFMASK)
            return true;
        break;
    case W2P_OFFSET:
        if ((value ^ new_value) & W2P_UNDEFMASK)
            return true;
        break;
    case RD_RCD_OFFSET:
        if ((value ^ new_value) & RD_RCD_UNDEFMASK)
            return true;
        break;
    case WR_RCD_OFFSET:
        if ((value ^ new_value) & WR_RCD_UNDEFMASK)
            return true;
        break;
    case RRD_OFFSET:
        if ((value ^ new_value) & RRD_UNDEFMASK)
            return true;
        break;
    case REXT_OFFSET:
        if ((value ^ new_value) & REXT_UNDEFMASK)
            return true;
        break;
    case WDV_OFFSET:
        if ((value ^ new_value) & WDV_UNDEFMASK)
            return true;
        break;
    case QUSE_OFFSET:
        if ((value ^ new_value) & QUSE_UNDEFMASK)
            return true;
        break;
    case QRST_OFFSET:
        if ((value ^ new_value) & QRST_UNDEFMASK)
            return true;
        break;
    case QSAFE_OFFSET:
        if ((value ^ new_value) & QSAFE_UNDEFMASK)
            return true;
        break;
    case RDV_OFFSET:
        if ((value ^ new_value) & RDV_UNDEFMASK)
            return true;
        break;
    case REFRESH_OFFSET:
        if ((value ^ new_value) & REFRESH_UNDEFMASK)
            return true;
        break;
    case BURST_REFRESH_NUM_OFFSET:
        if ((value ^ new_value) & BURST_REFRESH_NUM_UNDEFMASK)
            return true;
        break;
    case PDEX2WR_OFFSET:
        if ((value ^ new_value) & PDEX2WR_UNDEFMASK)
            return true;
        break;
    case PDEX2RD_OFFSET:
        if ((value ^ new_value) & PDEX2RD_UNDEFMASK)
            return true;
        break;
    case PCHG2PDEN_OFFSET:
        if ((value ^ new_value) & PCHG2PDEN_UNDEFMASK)
            return true;
        break;
    case ACT2PDEN_OFFSET:
        if ((value ^ new_value) & ACT2PDEN_UNDEFMASK)
            return true;
        break;
    case AR2PDEN_OFFSET:
        if ((value ^ new_value) & AR2PDEN_UNDEFMASK)
            return true;
        break;
    case RW2PDEN_OFFSET:
        if ((value ^ new_value) & RW2PDEN_UNDEFMASK)
            return true;
        break;
    case TXSR_OFFSET:
        if ((value ^ new_value) & TXSR_UNDEFMASK)
            return true;
        break;
    case TCKE_OFFSET:
        if ((value ^ new_value) & TCKE_UNDEFMASK)
            return true;
        break;
    case TFAW_OFFSET:
        if ((value ^ new_value) & TFAW_UNDEFMASK)
            return true;
        break;
    case TRPAB_OFFSET:
        if ((value ^ new_value) & TRPAB_UNDEFMASK)
            return true;
        break;
    case TCLKSTABLE_OFFSET:
        if ((value ^ new_value) & TCLKSTABLE_UNDEFMASK)
            return true;
        break;
    case TCLKSTOP_OFFSET:
        if ((value ^ new_value) & TCLKSTOP_UNDEFMASK)
            return true;
        break;
    case TREFBW_OFFSET:
        if ((value ^ new_value) & TREFBW_UNDEFMASK)
            return true;
        break;
    case QUSE_EXTRA_OFFSET:
        if ((value ^ new_value) & QUSE_EXTRA_UNDEFMASK)
            return true;
        break;
    case ODT_WRITE_OFFSET:
        if ((value ^ new_value) & ODT_WRITE_UNDEFMASK)
            return true;
        break;
    case ODT_READ_OFFSET:
        if ((value ^ new_value) & ODT_READ_UNDEFMASK)
            return true;
        break;
    case MRS_OFFSET:
        if ((value ^ new_value) & MRS_UNDEFMASK)
            return true;
        break;
    case EMRS_OFFSET:
        if ((value ^ new_value) & EMRS_UNDEFMASK)
            return true;
        break;
    case REF_OFFSET:
        if ((value ^ new_value) & REF_UNDEFMASK)
            return true;
        break;
    case PRE_OFFSET:
        if ((value ^ new_value) & PRE_UNDEFMASK)
            return true;
        break;
    case NOP_OFFSET:
        if ((value ^ new_value) & NOP_UNDEFMASK)
            return true;
        break;
    case SELF_REF_OFFSET:
        if ((value ^ new_value) & SELF_REF_UNDEFMASK)
            return true;
        break;
    case DPD_OFFSET:
        if ((value ^ new_value) & DPD_UNDEFMASK)
            return true;
        break;
    case MRW_OFFSET:
        if ((value ^ new_value) & MRW_UNDEFMASK)
            return true;
        break;
    case MRR_OFFSET:
        if ((value ^ new_value) & MRR_UNDEFMASK)
            return true;
        break;
    case FBIO_CFG1_OFFSET:
        if ((value ^ new_value) & FBIO_CFG1_UNDEFMASK)
            return true;
        break;
    case FBIO_DQSIB_DLY_OFFSET:
        if ((value ^ new_value) & FBIO_DQSIB_DLY_UNDEFMASK)
            return true;
        break;
    case FBIO_DQSIB_DLY_MSB_OFFSET:
        if ((value ^ new_value) & FBIO_DQSIB_DLY_MSB_UNDEFMASK)
            return true;
        break;
    case FBIO_CFG5_OFFSET:
        if ((value ^ new_value) & FBIO_CFG5_UNDEFMASK)
            return true;
        break;
    case FBIO_QUSE_DLY_OFFSET:
        if ((value ^ new_value) & FBIO_QUSE_DLY_UNDEFMASK)
            return true;
        break;
    case FBIO_QUSE_DLY_MSB_OFFSET:
        if ((value ^ new_value) & FBIO_QUSE_DLY_MSB_UNDEFMASK)
            return true;
        break;
    case FBIO_CFG6_OFFSET:
        if ((value ^ new_value) & FBIO_CFG6_UNDEFMASK)
            return true;
        break;
    case DQS_TRIMMER_RD0_OFFSET:
        if ((value ^ new_value) & DQS_TRIMMER_RD0_UNDEFMASK)
            return true;
        break;
    case DQS_TRIMMER_RD1_OFFSET:
        if ((value ^ new_value) & DQS_TRIMMER_RD1_UNDEFMASK)
            return true;
        break;
    case DQS_TRIMMER_RD2_OFFSET:
        if ((value ^ new_value) & DQS_TRIMMER_RD2_UNDEFMASK)
            return true;
        break;
    case DQS_TRIMMER_RD3_OFFSET:
        if ((value ^ new_value) & DQS_TRIMMER_RD3_UNDEFMASK)
            return true;
        break;
    case LL_ARB_CONFIG_OFFSET:
        if ((value ^ new_value) & LL_ARB_CONFIG_UNDEFMASK)
            return true;
        break;
    case T_MIN_CRITICAL_HP_OFFSET:
        if ((value ^ new_value) & T_MIN_CRITICAL_HP_UNDEFMASK)
            return true;
        break;
    case T_MIN_CRITICAL_TIMEOUT_OFFSET:
        if ((value ^ new_value) & T_MIN_CRITICAL_TIMEOUT_UNDEFMASK)
            return true;
        break;
    case T_MIN_LOAD_OFFSET:
        if ((value ^ new_value) & T_MIN_LOAD_UNDEFMASK)
            return true;
        break;
    case T_MAX_CRITICAL_HP_OFFSET:
        if ((value ^ new_value) & T_MAX_CRITICAL_HP_UNDEFMASK)
            return true;
        break;
    case T_MAX_CRITICAL_TIMEOUT_OFFSET:
        if ((value ^ new_value) & T_MAX_CRITICAL_TIMEOUT_UNDEFMASK)
            return true;
        break;
    case T_MAX_LOAD_OFFSET:
        if ((value ^ new_value) & T_MAX_LOAD_UNDEFMASK)
            return true;
        break;
    case AUTO_CAL_CONFIG_OFFSET:
        if ((value ^ new_value) & AUTO_CAL_CONFIG_UNDEFMASK)
            return true;
        break;
    case AUTO_CAL_INTERVAL_OFFSET:
        if ((value ^ new_value) & AUTO_CAL_INTERVAL_UNDEFMASK)
            return true;
        break;
    case AUTO_CAL_STATUS_OFFSET:
        if ((value ^ new_value) & AUTO_CAL_STATUS_UNDEFMASK)
            return true;
        break;
    case REQ_CTRL_OFFSET:
        if ((value ^ new_value) & REQ_CTRL_UNDEFMASK)
            return true;
        break;
    case EMC_STATUS_OFFSET:
        if ((value ^ new_value) & EMC_STATUS_UNDEFMASK)
            return true;
        break;
    case CFG_2_OFFSET:
        if ((value ^ new_value) & CFG_2_UNDEFMASK)
            return true;
        break;
    case CFG_DIG_DLL_OFFSET:
        if ((value ^ new_value) & CFG_DIG_DLL_UNDEFMASK)
            return true;
        break;
    case DLL_XFORM_DQS_OFFSET:
        if ((value ^ new_value) & DLL_XFORM_DQS_UNDEFMASK)
            return true;
        break;
    case DLL_XFORM_QUSE_OFFSET:
        if ((value ^ new_value) & DLL_XFORM_QUSE_UNDEFMASK)
            return true;
        break;
    case DIG_DLL_UPPER_STATUS_OFFSET:
        if ((value ^ new_value) & DIG_DLL_UPPER_STATUS_UNDEFMASK)
            return true;
        break;
    case DIG_DLL_LOWER_STATUS_OFFSET:
        if ((value ^ new_value) & DIG_DLL_LOWER_STATUS_UNDEFMASK)
            return true;
        break;
    case CTT_TERM_CTRL_OFFSET:
        if ((value ^ new_value) & CTT_TERM_CTRL_UNDEFMASK)
            return true;
        break;
    case ZCAL_REF_CNT_OFFSET:
        if ((value ^ new_value) & ZCAL_REF_CNT_UNDEFMASK)
            return true;
        break;
    case ZCAL_WAIT_CNT_OFFSET:
        if ((value ^ new_value) & ZCAL_WAIT_CNT_UNDEFMASK)
            return true;
        break;
    case ZCAL_MRW_CMD_OFFSET:
        if ((value ^ new_value) & ZCAL_MRW_CMD_UNDEFMASK)
            return true;
        break;
    case CMDQ_OFFSET:
        if ((value ^ new_value) & CMDQ_UNDEFMASK)
            return true;
        break;
    case FBIO_SPARE_OFFSET:
        if ((value ^ new_value) & FBIO_SPARE_UNDEFMASK)
            return true;
        break;
    case FBIO_WRPTR_EQ_2_OFFSET:
        if ((value ^ new_value) & FBIO_WRPTR_EQ_2_UNDEFMASK)
            return true;
        break;
    case CLKEN_OVERRIDE_OFFSET:
        if ((value ^ new_value) & CLKEN_OVERRIDE_UNDEFMASK)
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
    case STAT_LLMC_ADDR_LOW_OFFSET:
        if ((value ^ new_value) & STAT_LLMC_ADDR_LOW_UNDEFMASK)
            return true;
        break;
    case STAT_LLMC_ADDR_HIGH_OFFSET:
        if ((value ^ new_value) & STAT_LLMC_ADDR_HIGH_UNDEFMASK)
            return true;
        break;
    case STAT_LLMC_CLOCK_LIMIT_OFFSET:
        if ((value ^ new_value) & STAT_LLMC_CLOCK_LIMIT_UNDEFMASK)
            return true;
        break;
    case STAT_LLMC_CLOCKS_OFFSET:
        if ((value ^ new_value) & STAT_LLMC_CLOCKS_UNDEFMASK)
            return true;
        break;
    case STAT_LLMC_CONTROL_OFFSET:
        if ((value ^ new_value) & STAT_LLMC_CONTROL_UNDEFMASK)
            return true;
        break;
    case STAT_LLMC_HIST_LIMIT_OFFSET:
        if ((value ^ new_value) & STAT_LLMC_HIST_LIMIT_UNDEFMASK)
            return true;
        break;
    case STAT_LLMC_COUNT_OFFSET:
        if ((value ^ new_value) & STAT_LLMC_COUNT_UNDEFMASK)
            return true;
        break;
    case STAT_LLMC_HIST_OFFSET:
        if ((value ^ new_value) & STAT_LLMC_HIST_UNDEFMASK)
            return true;
        break;
    case STAT_PWR_CLOCK_LIMIT_OFFSET:
        if ((value ^ new_value) & STAT_PWR_CLOCK_LIMIT_UNDEFMASK)
            return true;
        break;
    case STAT_PWR_CLOCKS_OFFSET:
        if ((value ^ new_value) & STAT_PWR_CLOCKS_UNDEFMASK)
            return true;
        break;
    case STAT_PWR_COUNT_OFFSET:
        if ((value ^ new_value) & STAT_PWR_COUNT_UNDEFMASK)
            return true;
        break;
    case STAT_DRAM_CLOCK_LIMIT_LO_OFFSET:
        if ((value ^ new_value) & STAT_DRAM_CLOCK_LIMIT_LO_UNDEFMASK)
            return true;
        break;
    case STAT_DRAM_CLOCK_LIMIT_HI_OFFSET:
        if ((value ^ new_value) & STAT_DRAM_CLOCK_LIMIT_HI_UNDEFMASK)
            return true;
        break;
    case STAT_DRAM_CLOCKS_LO_OFFSET:
        if ((value ^ new_value) & STAT_DRAM_CLOCKS_LO_UNDEFMASK)
            return true;
        break;
    case STAT_DRAM_CLOCKS_HI_OFFSET:
        if ((value ^ new_value) & STAT_DRAM_CLOCKS_HI_UNDEFMASK)
            return true;
        break;
    case STAT_DRAM_DEV0_ACTIVATE_CNT_LO_OFFSET:
        if ((value ^ new_value) & STAT_DRAM_DEV0_ACTIVATE_CNT_LO_UNDEFMASK)
            return true;
        break;
    case STAT_DRAM_DEV0_ACTIVATE_CNT_HI_OFFSET:
        if ((value ^ new_value) & STAT_DRAM_DEV0_ACTIVATE_CNT_HI_UNDEFMASK)
            return true;
        break;
    case STAT_DRAM_DEV0_READ_CNT_LO_OFFSET:
        if ((value ^ new_value) & STAT_DRAM_DEV0_READ_CNT_LO_UNDEFMASK)
            return true;
        break;
    case STAT_DRAM_DEV0_READ_CNT_HI_OFFSET:
        if ((value ^ new_value) & STAT_DRAM_DEV0_READ_CNT_HI_UNDEFMASK)
            return true;
        break;
    case STAT_DRAM_DEV0_WRITE_CNT_LO_OFFSET:
        if ((value ^ new_value) & STAT_DRAM_DEV0_WRITE_CNT_LO_UNDEFMASK)
            return true;
        break;
    case STAT_DRAM_DEV0_WRITE_CNT_HI_OFFSET:
        if ((value ^ new_value) & STAT_DRAM_DEV0_WRITE_CNT_HI_UNDEFMASK)
            return true;
        break;
    case STAT_DRAM_DEV0_REF_CNT_LO_OFFSET:
        if ((value ^ new_value) & STAT_DRAM_DEV0_REF_CNT_LO_UNDEFMASK)
            return true;
        break;
    case STAT_DRAM_DEV0_REF_CNT_HI_OFFSET:
        if ((value ^ new_value) & STAT_DRAM_DEV0_REF_CNT_HI_UNDEFMASK)
            return true;
        break;
    case STAT_DRAM_DEV0_CUMM_BANKS_ACTIVE_CKE_EQ1_LO_OFFSET:
        if ((value ^ new_value) & STAT_DRAM_DEV0_CUMM_BANKS_ACTIVE_CKE_EQ1_LO_UNDEFMASK)
            return true;
        break;
    case STAT_DRAM_DEV0_CUMM_BANKS_ACTIVE_CKE_EQ1_HI_OFFSET:
        if ((value ^ new_value) & STAT_DRAM_DEV0_CUMM_BANKS_ACTIVE_CKE_EQ1_HI_UNDEFMASK)
            return true;
        break;
    case STAT_DRAM_DEV0_CUMM_BANKS_ACTIVE_CKE_EQ0_LO_OFFSET:
        if ((value ^ new_value) & STAT_DRAM_DEV0_CUMM_BANKS_ACTIVE_CKE_EQ0_LO_UNDEFMASK)
            return true;
        break;
    case STAT_DRAM_DEV0_CUMM_BANKS_ACTIVE_CKE_EQ0_HI_OFFSET:
        if ((value ^ new_value) & STAT_DRAM_DEV0_CUMM_BANKS_ACTIVE_CKE_EQ0_HI_UNDEFMASK)
            return true;
        break;
    case STAT_DRAM_DEV0_CKE_EQ1_CLKS_LO_OFFSET:
        if ((value ^ new_value) & STAT_DRAM_DEV0_CKE_EQ1_CLKS_LO_UNDEFMASK)
            return true;
        break;
    case STAT_DRAM_DEV0_CKE_EQ1_CLKS_HI_OFFSET:
        if ((value ^ new_value) & STAT_DRAM_DEV0_CKE_EQ1_CLKS_HI_UNDEFMASK)
            return true;
        break;
    case STAT_DRAM_DEV0_EXTCLKS_CKE_EQ1_LO_OFFSET:
        if ((value ^ new_value) & STAT_DRAM_DEV0_EXTCLKS_CKE_EQ1_LO_UNDEFMASK)
            return true;
        break;
    case STAT_DRAM_DEV0_EXTCLKS_CKE_EQ1_HI_OFFSET:
        if ((value ^ new_value) & STAT_DRAM_DEV0_EXTCLKS_CKE_EQ1_HI_UNDEFMASK)
            return true;
        break;
    case STAT_DRAM_DEV0_EXTCLKS_CKE_EQ0_LO_OFFSET:
        if ((value ^ new_value) & STAT_DRAM_DEV0_EXTCLKS_CKE_EQ0_LO_UNDEFMASK)
            return true;
        break;
    case STAT_DRAM_DEV0_EXTCLKS_CKE_EQ0_HI_OFFSET:
        if ((value ^ new_value) & STAT_DRAM_DEV0_EXTCLKS_CKE_EQ0_HI_UNDEFMASK)
            return true;
        break;
    case STAT_DRAM_DEV1_ACTIVATE_CNT_LO_OFFSET:
        if ((value ^ new_value) & STAT_DRAM_DEV1_ACTIVATE_CNT_LO_UNDEFMASK)
            return true;
        break;
    case STAT_DRAM_DEV1_ACTIVATE_CNT_HI_OFFSET:
        if ((value ^ new_value) & STAT_DRAM_DEV1_ACTIVATE_CNT_HI_UNDEFMASK)
            return true;
        break;
    case STAT_DRAM_DEV1_READ_CNT_LO_OFFSET:
        if ((value ^ new_value) & STAT_DRAM_DEV1_READ_CNT_LO_UNDEFMASK)
            return true;
        break;
    case STAT_DRAM_DEV1_READ_CNT_HI_OFFSET:
        if ((value ^ new_value) & STAT_DRAM_DEV1_READ_CNT_HI_UNDEFMASK)
            return true;
        break;
    case STAT_DRAM_DEV1_WRITE_CNT_LO_OFFSET:
        if ((value ^ new_value) & STAT_DRAM_DEV1_WRITE_CNT_LO_UNDEFMASK)
            return true;
        break;
    case STAT_DRAM_DEV1_WRITE_CNT_HI_OFFSET:
        if ((value ^ new_value) & STAT_DRAM_DEV1_WRITE_CNT_HI_UNDEFMASK)
            return true;
        break;
    case STAT_DRAM_DEV1_REF_CNT_LO_OFFSET:
        if ((value ^ new_value) & STAT_DRAM_DEV1_REF_CNT_LO_UNDEFMASK)
            return true;
        break;
    case STAT_DRAM_DEV1_REF_CNT_HI_OFFSET:
        if ((value ^ new_value) & STAT_DRAM_DEV1_REF_CNT_HI_UNDEFMASK)
            return true;
        break;
    case STAT_DRAM_DEV1_CUMM_BANKS_ACTIVE_CKE_EQ1_LO_OFFSET:
        if ((value ^ new_value) & STAT_DRAM_DEV1_CUMM_BANKS_ACTIVE_CKE_EQ1_LO_UNDEFMASK)
            return true;
        break;
    case STAT_DRAM_DEV1_CUMM_BANKS_ACTIVE_CKE_EQ1_HI_OFFSET:
        if ((value ^ new_value) & STAT_DRAM_DEV1_CUMM_BANKS_ACTIVE_CKE_EQ1_HI_UNDEFMASK)
            return true;
        break;
    case STAT_DRAM_DEV1_CUMM_BANKS_ACTIVE_CKE_EQ0_LO_OFFSET:
        if ((value ^ new_value) & STAT_DRAM_DEV1_CUMM_BANKS_ACTIVE_CKE_EQ0_LO_UNDEFMASK)
            return true;
        break;
    case STAT_DRAM_DEV1_CUMM_BANKS_ACTIVE_CKE_EQ0_HI_OFFSET:
        if ((value ^ new_value) & STAT_DRAM_DEV1_CUMM_BANKS_ACTIVE_CKE_EQ0_HI_UNDEFMASK)
            return true;
        break;
    case STAT_DRAM_DEV1_CKE_EQ1_CLKS_LO_OFFSET:
        if ((value ^ new_value) & STAT_DRAM_DEV1_CKE_EQ1_CLKS_LO_UNDEFMASK)
            return true;
        break;
    case STAT_DRAM_DEV1_CKE_EQ1_CLKS_HI_OFFSET:
        if ((value ^ new_value) & STAT_DRAM_DEV1_CKE_EQ1_CLKS_HI_UNDEFMASK)
            return true;
        break;
    case STAT_DRAM_DEV1_EXTCLKS_CKE_EQ1_LO_OFFSET:
        if ((value ^ new_value) & STAT_DRAM_DEV1_EXTCLKS_CKE_EQ1_LO_UNDEFMASK)
            return true;
        break;
    case STAT_DRAM_DEV1_EXTCLKS_CKE_EQ1_HI_OFFSET:
        if ((value ^ new_value) & STAT_DRAM_DEV1_EXTCLKS_CKE_EQ1_HI_UNDEFMASK)
            return true;
        break;
    case STAT_DRAM_DEV1_EXTCLKS_CKE_EQ0_LO_OFFSET:
        if ((value ^ new_value) & STAT_DRAM_DEV1_EXTCLKS_CKE_EQ0_LO_UNDEFMASK)
            return true;
        break;
    case STAT_DRAM_DEV1_EXTCLKS_CKE_EQ0_HI_OFFSET:
        if ((value ^ new_value) & STAT_DRAM_DEV1_EXTCLKS_CKE_EQ0_HI_UNDEFMASK)
            return true;
        break;
    case STAT_DRAM_DEV0_NO_BANKS_ACTIVE_CKE_EQ1_LO_OFFSET:
        if ((value ^ new_value) & STAT_DRAM_DEV0_NO_BANKS_ACTIVE_CKE_EQ1_LO_UNDEFMASK)
            return true;
        break;
    case STAT_DRAM_DEV0_NO_BANKS_ACTIVE_CKE_EQ1_HI_OFFSET:
        if ((value ^ new_value) & STAT_DRAM_DEV0_NO_BANKS_ACTIVE_CKE_EQ1_HI_UNDEFMASK)
            return true;
        break;
    case STAT_DRAM_DEV0_NO_BANKS_ACTIVE_CKE_EQ0_LO_OFFSET:
        if ((value ^ new_value) & STAT_DRAM_DEV0_NO_BANKS_ACTIVE_CKE_EQ0_LO_UNDEFMASK)
            return true;
        break;
    case STAT_DRAM_DEV0_NO_BANKS_ACTIVE_CKE_EQ0_HI_OFFSET:
        if ((value ^ new_value) & STAT_DRAM_DEV0_NO_BANKS_ACTIVE_CKE_EQ0_HI_UNDEFMASK)
            return true;
        break;
    case STAT_DRAM_DEV1_NO_BANKS_ACTIVE_CKE_EQ1_LO_OFFSET:
        if ((value ^ new_value) & STAT_DRAM_DEV1_NO_BANKS_ACTIVE_CKE_EQ1_LO_UNDEFMASK)
            return true;
        break;
    case STAT_DRAM_DEV1_NO_BANKS_ACTIVE_CKE_EQ1_HI_OFFSET:
        if ((value ^ new_value) & STAT_DRAM_DEV1_NO_BANKS_ACTIVE_CKE_EQ1_HI_UNDEFMASK)
            return true;
        break;
    case STAT_DRAM_DEV1_NO_BANKS_ACTIVE_CKE_EQ0_LO_OFFSET:
        if ((value ^ new_value) & STAT_DRAM_DEV1_NO_BANKS_ACTIVE_CKE_EQ0_LO_UNDEFMASK)
            return true;
        break;
    case STAT_DRAM_DEV1_NO_BANKS_ACTIVE_CKE_EQ0_HI_OFFSET:
        if ((value ^ new_value) & STAT_DRAM_DEV1_NO_BANKS_ACTIVE_CKE_EQ0_HI_UNDEFMASK)
            return true;
        break;
    case CFG_CLKTRIM_OFFSET:
        if ((value ^ new_value) & CFG_CLKTRIM_UNDEFMASK)
            return true;
        break;
    case CFG_CLKTRIM_1_OFFSET:
        if ((value ^ new_value) & CFG_CLKTRIM_1_UNDEFMASK)
            return true;
        break;
    case CFG_CLKTRIM_2_OFFSET:
        if ((value ^ new_value) & CFG_CLKTRIM_2_UNDEFMASK)
            return true;
        break;

    default:
        break;
    }

    return false;
}

QString EmcDev::get_register_name(const log_entry &entry) const
{
    switch (entry.offset) {
    case INTSTATUS_OFFSET:
        return QString("INTSTATUS");
    case INTMASK_OFFSET:
        return QString("INTMASK");
    case DBG_OFFSET:
        return QString("DBG");
    case CFG_OFFSET:
        return QString("CFG");
    case ADR_CFG_OFFSET:
        return QString("ADR_CFG");
    case ADR_CFG_1_OFFSET:
        return QString("ADR_CFG_1");
    case REFCTRL_OFFSET:
        return QString("REFCTRL");
    case PIN_OFFSET:
        return QString("PIN");
    case TIMING_CONTROL_OFFSET:
        return QString("TIMING_CONTROL");
    case RC_OFFSET:
        return QString("RC");
    case RFC_OFFSET:
        return QString("RFC");
    case RAS_OFFSET:
        return QString("RAS");
    case RP_OFFSET:
        return QString("RP");
    case R2W_OFFSET:
        return QString("R2W");
    case W2R_OFFSET:
        return QString("W2R");
    case R2P_OFFSET:
        return QString("R2P");
    case W2P_OFFSET:
        return QString("W2P");
    case RD_RCD_OFFSET:
        return QString("RD_RCD");
    case WR_RCD_OFFSET:
        return QString("WR_RCD");
    case RRD_OFFSET:
        return QString("RRD");
    case REXT_OFFSET:
        return QString("REXT");
    case WDV_OFFSET:
        return QString("WDV");
    case QUSE_OFFSET:
        return QString("QUSE");
    case QRST_OFFSET:
        return QString("QRST");
    case QSAFE_OFFSET:
        return QString("QSAFE");
    case RDV_OFFSET:
        return QString("RDV");
    case REFRESH_OFFSET:
        return QString("REFRESH");
    case BURST_REFRESH_NUM_OFFSET:
        return QString("BURST_REFRESH_NUM");
    case PDEX2WR_OFFSET:
        return QString("PDEX2WR");
    case PDEX2RD_OFFSET:
        return QString("PDEX2RD");
    case PCHG2PDEN_OFFSET:
        return QString("PCHG2PDEN");
    case ACT2PDEN_OFFSET:
        return QString("ACT2PDEN");
    case AR2PDEN_OFFSET:
        return QString("AR2PDEN");
    case RW2PDEN_OFFSET:
        return QString("RW2PDEN");
    case TXSR_OFFSET:
        return QString("TXSR");
    case TCKE_OFFSET:
        return QString("TCKE");
    case TFAW_OFFSET:
        return QString("TFAW");
    case TRPAB_OFFSET:
        return QString("TRPAB");
    case TCLKSTABLE_OFFSET:
        return QString("TCLKSTABLE");
    case TCLKSTOP_OFFSET:
        return QString("TCLKSTOP");
    case TREFBW_OFFSET:
        return QString("TREFBW");
    case QUSE_EXTRA_OFFSET:
        return QString("QUSE_EXTRA");
    case ODT_WRITE_OFFSET:
        return QString("ODT_WRITE");
    case ODT_READ_OFFSET:
        return QString("ODT_READ");
    case MRS_OFFSET:
        return QString("MRS");
    case EMRS_OFFSET:
        return QString("EMRS");
    case REF_OFFSET:
        return QString("REF");
    case PRE_OFFSET:
        return QString("PRE");
    case NOP_OFFSET:
        return QString("NOP");
    case SELF_REF_OFFSET:
        return QString("SELF_REF");
    case DPD_OFFSET:
        return QString("DPD");
    case MRW_OFFSET:
        return QString("MRW");
    case MRR_OFFSET:
        return QString("MRR");
    case FBIO_CFG1_OFFSET:
        return QString("FBIO_CFG1");
    case FBIO_DQSIB_DLY_OFFSET:
        return QString("FBIO_DQSIB_DLY");
    case FBIO_DQSIB_DLY_MSB_OFFSET:
        return QString("FBIO_DQSIB_DLY_MSB");
    case FBIO_CFG5_OFFSET:
        return QString("FBIO_CFG5");
    case FBIO_QUSE_DLY_OFFSET:
        return QString("FBIO_QUSE_DLY");
    case FBIO_QUSE_DLY_MSB_OFFSET:
        return QString("FBIO_QUSE_DLY_MSB");
    case FBIO_CFG6_OFFSET:
        return QString("FBIO_CFG6");
    case DQS_TRIMMER_RD0_OFFSET:
        return QString("DQS_TRIMMER_RD0");
    case DQS_TRIMMER_RD1_OFFSET:
        return QString("DQS_TRIMMER_RD1");
    case DQS_TRIMMER_RD2_OFFSET:
        return QString("DQS_TRIMMER_RD2");
    case DQS_TRIMMER_RD3_OFFSET:
        return QString("DQS_TRIMMER_RD3");
    case LL_ARB_CONFIG_OFFSET:
        return QString("LL_ARB_CONFIG");
    case T_MIN_CRITICAL_HP_OFFSET:
        return QString("T_MIN_CRITICAL_HP");
    case T_MIN_CRITICAL_TIMEOUT_OFFSET:
        return QString("T_MIN_CRITICAL_TIMEOUT");
    case T_MIN_LOAD_OFFSET:
        return QString("T_MIN_LOAD");
    case T_MAX_CRITICAL_HP_OFFSET:
        return QString("T_MAX_CRITICAL_HP");
    case T_MAX_CRITICAL_TIMEOUT_OFFSET:
        return QString("T_MAX_CRITICAL_TIMEOUT");
    case T_MAX_LOAD_OFFSET:
        return QString("T_MAX_LOAD");
    case AUTO_CAL_CONFIG_OFFSET:
        return QString("AUTO_CAL_CONFIG");
    case AUTO_CAL_INTERVAL_OFFSET:
        return QString("AUTO_CAL_INTERVAL");
    case AUTO_CAL_STATUS_OFFSET:
        return QString("AUTO_CAL_STATUS");
    case REQ_CTRL_OFFSET:
        return QString("REQ_CTRL");
    case EMC_STATUS_OFFSET:
        return QString("EMC_STATUS");
    case CFG_2_OFFSET:
        return QString("CFG_2");
    case CFG_DIG_DLL_OFFSET:
        return QString("CFG_DIG_DLL");
    case DLL_XFORM_DQS_OFFSET:
        return QString("DLL_XFORM_DQS");
    case DLL_XFORM_QUSE_OFFSET:
        return QString("DLL_XFORM_QUSE");
    case DIG_DLL_UPPER_STATUS_OFFSET:
        return QString("DIG_DLL_UPPER_STATUS");
    case DIG_DLL_LOWER_STATUS_OFFSET:
        return QString("DIG_DLL_LOWER_STATUS");
    case CTT_TERM_CTRL_OFFSET:
        return QString("CTT_TERM_CTRL");
    case ZCAL_REF_CNT_OFFSET:
        return QString("ZCAL_REF_CNT");
    case ZCAL_WAIT_CNT_OFFSET:
        return QString("ZCAL_WAIT_CNT");
    case ZCAL_MRW_CMD_OFFSET:
        return QString("ZCAL_MRW_CMD");
    case CMDQ_OFFSET:
        return QString("CMDQ");
    case FBIO_SPARE_OFFSET:
        return QString("FBIO_SPARE");
    case FBIO_WRPTR_EQ_2_OFFSET:
        return QString("FBIO_WRPTR_EQ_2");
    case CLKEN_OVERRIDE_OFFSET:
        return QString("CLKEN_OVERRIDE");
    case STAT_CONTROL_OFFSET:
        return QString("STAT_CONTROL");
    case STAT_STATUS_OFFSET:
        return QString("STAT_STATUS");
    case STAT_LLMC_ADDR_LOW_OFFSET:
        return QString("STAT_LLMC_ADDR_LOW");
    case STAT_LLMC_ADDR_HIGH_OFFSET:
        return QString("STAT_LLMC_ADDR_HIGH");
    case STAT_LLMC_CLOCK_LIMIT_OFFSET:
        return QString("STAT_LLMC_CLOCK_LIMIT");
    case STAT_LLMC_CLOCKS_OFFSET:
        return QString("STAT_LLMC_CLOCKS");
    case STAT_LLMC_CONTROL_OFFSET:
        return QString("STAT_LLMC_CONTROL");
    case STAT_LLMC_HIST_LIMIT_OFFSET:
        return QString("STAT_LLMC_HIST_LIMIT");
    case STAT_LLMC_COUNT_OFFSET:
        return QString("STAT_LLMC_COUNT");
    case STAT_LLMC_HIST_OFFSET:
        return QString("STAT_LLMC_HIST");
    case STAT_PWR_CLOCK_LIMIT_OFFSET:
        return QString("STAT_PWR_CLOCK_LIMIT");
    case STAT_PWR_CLOCKS_OFFSET:
        return QString("STAT_PWR_CLOCKS");
    case STAT_PWR_COUNT_OFFSET:
        return QString("STAT_PWR_COUNT");
    case STAT_DRAM_CLOCK_LIMIT_LO_OFFSET:
        return QString("STAT_DRAM_CLOCK_LIMIT_LO");
    case STAT_DRAM_CLOCK_LIMIT_HI_OFFSET:
        return QString("STAT_DRAM_CLOCK_LIMIT_HI");
    case STAT_DRAM_CLOCKS_LO_OFFSET:
        return QString("STAT_DRAM_CLOCKS_LO");
    case STAT_DRAM_CLOCKS_HI_OFFSET:
        return QString("STAT_DRAM_CLOCKS_HI");
    case STAT_DRAM_DEV0_ACTIVATE_CNT_LO_OFFSET:
        return QString("STAT_DRAM_DEV0_ACTIVATE_CNT_LO");
    case STAT_DRAM_DEV0_ACTIVATE_CNT_HI_OFFSET:
        return QString("STAT_DRAM_DEV0_ACTIVATE_CNT_HI");
    case STAT_DRAM_DEV0_READ_CNT_LO_OFFSET:
        return QString("STAT_DRAM_DEV0_READ_CNT_LO");
    case STAT_DRAM_DEV0_READ_CNT_HI_OFFSET:
        return QString("STAT_DRAM_DEV0_READ_CNT_HI");
    case STAT_DRAM_DEV0_WRITE_CNT_LO_OFFSET:
        return QString("STAT_DRAM_DEV0_WRITE_CNT_LO");
    case STAT_DRAM_DEV0_WRITE_CNT_HI_OFFSET:
        return QString("STAT_DRAM_DEV0_WRITE_CNT_HI");
    case STAT_DRAM_DEV0_REF_CNT_LO_OFFSET:
        return QString("STAT_DRAM_DEV0_REF_CNT_LO");
    case STAT_DRAM_DEV0_REF_CNT_HI_OFFSET:
        return QString("STAT_DRAM_DEV0_REF_CNT_HI");
    case STAT_DRAM_DEV0_CUMM_BANKS_ACTIVE_CKE_EQ1_LO_OFFSET:
        return QString("STAT_DRAM_DEV0_CUMM_BANKS_ACTIVE_CKE_EQ1_LO");
    case STAT_DRAM_DEV0_CUMM_BANKS_ACTIVE_CKE_EQ1_HI_OFFSET:
        return QString("STAT_DRAM_DEV0_CUMM_BANKS_ACTIVE_CKE_EQ1_HI");
    case STAT_DRAM_DEV0_CUMM_BANKS_ACTIVE_CKE_EQ0_LO_OFFSET:
        return QString("STAT_DRAM_DEV0_CUMM_BANKS_ACTIVE_CKE_EQ0_LO");
    case STAT_DRAM_DEV0_CUMM_BANKS_ACTIVE_CKE_EQ0_HI_OFFSET:
        return QString("STAT_DRAM_DEV0_CUMM_BANKS_ACTIVE_CKE_EQ0_HI");
    case STAT_DRAM_DEV0_CKE_EQ1_CLKS_LO_OFFSET:
        return QString("STAT_DRAM_DEV0_CKE_EQ1_CLKS_LO");
    case STAT_DRAM_DEV0_CKE_EQ1_CLKS_HI_OFFSET:
        return QString("STAT_DRAM_DEV0_CKE_EQ1_CLKS_HI");
    case STAT_DRAM_DEV0_EXTCLKS_CKE_EQ1_LO_OFFSET:
        return QString("STAT_DRAM_DEV0_EXTCLKS_CKE_EQ1_LO");
    case STAT_DRAM_DEV0_EXTCLKS_CKE_EQ1_HI_OFFSET:
        return QString("STAT_DRAM_DEV0_EXTCLKS_CKE_EQ1_HI");
    case STAT_DRAM_DEV0_EXTCLKS_CKE_EQ0_LO_OFFSET:
        return QString("STAT_DRAM_DEV0_EXTCLKS_CKE_EQ0_LO");
    case STAT_DRAM_DEV0_EXTCLKS_CKE_EQ0_HI_OFFSET:
        return QString("STAT_DRAM_DEV0_EXTCLKS_CKE_EQ0_HI");
    case STAT_DRAM_DEV1_ACTIVATE_CNT_LO_OFFSET:
        return QString("STAT_DRAM_DEV1_ACTIVATE_CNT_LO");
    case STAT_DRAM_DEV1_ACTIVATE_CNT_HI_OFFSET:
        return QString("STAT_DRAM_DEV1_ACTIVATE_CNT_HI");
    case STAT_DRAM_DEV1_READ_CNT_LO_OFFSET:
        return QString("STAT_DRAM_DEV1_READ_CNT_LO");
    case STAT_DRAM_DEV1_READ_CNT_HI_OFFSET:
        return QString("STAT_DRAM_DEV1_READ_CNT_HI");
    case STAT_DRAM_DEV1_WRITE_CNT_LO_OFFSET:
        return QString("STAT_DRAM_DEV1_WRITE_CNT_LO");
    case STAT_DRAM_DEV1_WRITE_CNT_HI_OFFSET:
        return QString("STAT_DRAM_DEV1_WRITE_CNT_HI");
    case STAT_DRAM_DEV1_REF_CNT_LO_OFFSET:
        return QString("STAT_DRAM_DEV1_REF_CNT_LO");
    case STAT_DRAM_DEV1_REF_CNT_HI_OFFSET:
        return QString("STAT_DRAM_DEV1_REF_CNT_HI");
    case STAT_DRAM_DEV1_CUMM_BANKS_ACTIVE_CKE_EQ1_LO_OFFSET:
        return QString("STAT_DRAM_DEV1_CUMM_BANKS_ACTIVE_CKE_EQ1_LO");
    case STAT_DRAM_DEV1_CUMM_BANKS_ACTIVE_CKE_EQ1_HI_OFFSET:
        return QString("STAT_DRAM_DEV1_CUMM_BANKS_ACTIVE_CKE_EQ1_HI");
    case STAT_DRAM_DEV1_CUMM_BANKS_ACTIVE_CKE_EQ0_LO_OFFSET:
        return QString("STAT_DRAM_DEV1_CUMM_BANKS_ACTIVE_CKE_EQ0_LO");
    case STAT_DRAM_DEV1_CUMM_BANKS_ACTIVE_CKE_EQ0_HI_OFFSET:
        return QString("STAT_DRAM_DEV1_CUMM_BANKS_ACTIVE_CKE_EQ0_HI");
    case STAT_DRAM_DEV1_CKE_EQ1_CLKS_LO_OFFSET:
        return QString("STAT_DRAM_DEV1_CKE_EQ1_CLKS_LO");
    case STAT_DRAM_DEV1_CKE_EQ1_CLKS_HI_OFFSET:
        return QString("STAT_DRAM_DEV1_CKE_EQ1_CLKS_HI");
    case STAT_DRAM_DEV1_EXTCLKS_CKE_EQ1_LO_OFFSET:
        return QString("STAT_DRAM_DEV1_EXTCLKS_CKE_EQ1_LO");
    case STAT_DRAM_DEV1_EXTCLKS_CKE_EQ1_HI_OFFSET:
        return QString("STAT_DRAM_DEV1_EXTCLKS_CKE_EQ1_HI");
    case STAT_DRAM_DEV1_EXTCLKS_CKE_EQ0_LO_OFFSET:
        return QString("STAT_DRAM_DEV1_EXTCLKS_CKE_EQ0_LO");
    case STAT_DRAM_DEV1_EXTCLKS_CKE_EQ0_HI_OFFSET:
        return QString("STAT_DRAM_DEV1_EXTCLKS_CKE_EQ0_HI");
    case STAT_DRAM_DEV0_NO_BANKS_ACTIVE_CKE_EQ1_LO_OFFSET:
        return QString("STAT_DRAM_DEV0_NO_BANKS_ACTIVE_CKE_EQ1_LO");
    case STAT_DRAM_DEV0_NO_BANKS_ACTIVE_CKE_EQ1_HI_OFFSET:
        return QString("STAT_DRAM_DEV0_NO_BANKS_ACTIVE_CKE_EQ1_HI");
    case STAT_DRAM_DEV0_NO_BANKS_ACTIVE_CKE_EQ0_LO_OFFSET:
        return QString("STAT_DRAM_DEV0_NO_BANKS_ACTIVE_CKE_EQ0_LO");
    case STAT_DRAM_DEV0_NO_BANKS_ACTIVE_CKE_EQ0_HI_OFFSET:
        return QString("STAT_DRAM_DEV0_NO_BANKS_ACTIVE_CKE_EQ0_HI");
    case STAT_DRAM_DEV1_NO_BANKS_ACTIVE_CKE_EQ1_LO_OFFSET:
        return QString("STAT_DRAM_DEV1_NO_BANKS_ACTIVE_CKE_EQ1_LO");
    case STAT_DRAM_DEV1_NO_BANKS_ACTIVE_CKE_EQ1_HI_OFFSET:
        return QString("STAT_DRAM_DEV1_NO_BANKS_ACTIVE_CKE_EQ1_HI");
    case STAT_DRAM_DEV1_NO_BANKS_ACTIVE_CKE_EQ0_LO_OFFSET:
        return QString("STAT_DRAM_DEV1_NO_BANKS_ACTIVE_CKE_EQ0_LO");
    case STAT_DRAM_DEV1_NO_BANKS_ACTIVE_CKE_EQ0_HI_OFFSET:
        return QString("STAT_DRAM_DEV1_NO_BANKS_ACTIVE_CKE_EQ0_HI");
    case CFG_CLKTRIM_OFFSET:
        return QString("CFG_CLKTRIM");
    case CFG_CLKTRIM_1_OFFSET:
        return QString("CFG_CLKTRIM_1");
    case CFG_CLKTRIM_2_OFFSET:
        return QString("CFG_CLKTRIM_2");

    default:
        break;
    }

    qDebug() << QString().sprintf("EMC: %s: Ooops... 0x%x", __func__, entry.offset);

    return QString().sprintf("Ooops... @0x%X", entry.offset);
}

void EmcDev::fill_bits_details(const u_int32_t &offset,
                                      const u_int32_t &value, const u_int32_t &new_value)
{
    switch (offset) {
    case INTSTATUS_OFFSET:
        fill_intstatus_details(value, new_value);
        break;
    case INTMASK_OFFSET:
        fill_intmask_details(value, new_value);
        break;
    case DBG_OFFSET:
        fill_dbg_details(value, new_value);
        break;
    case CFG_OFFSET:
        fill_cfg_details(value, new_value);
        break;
    case ADR_CFG_OFFSET:
        fill_adr_cfg_details(value, new_value);
        break;
    case ADR_CFG_1_OFFSET:
        fill_adr_cfg_1_details(value, new_value);
        break;
    case REFCTRL_OFFSET:
        fill_refctrl_details(value, new_value);
        break;
    case PIN_OFFSET:
        fill_pin_details(value, new_value);
        break;
    case TIMING_CONTROL_OFFSET:
        fill_timing_control_details(value, new_value);
        break;
    case RC_OFFSET:
        fill_rc_details(value, new_value);
        break;
    case RFC_OFFSET:
        fill_rfc_details(value, new_value);
        break;
    case RAS_OFFSET:
        fill_ras_details(value, new_value);
        break;
    case RP_OFFSET:
        fill_rp_details(value, new_value);
        break;
    case R2W_OFFSET:
        fill_r2w_details(value, new_value);
        break;
    case W2R_OFFSET:
        fill_w2r_details(value, new_value);
        break;
    case R2P_OFFSET:
        fill_r2p_details(value, new_value);
        break;
    case W2P_OFFSET:
        fill_w2p_details(value, new_value);
        break;
    case RD_RCD_OFFSET:
        fill_rd_rcd_details(value, new_value);
        break;
    case WR_RCD_OFFSET:
        fill_wr_rcd_details(value, new_value);
        break;
    case RRD_OFFSET:
        fill_rrd_details(value, new_value);
        break;
    case REXT_OFFSET:
        fill_rext_details(value, new_value);
        break;
    case WDV_OFFSET:
        fill_wdv_details(value, new_value);
        break;
    case QUSE_OFFSET:
        fill_quse_details(value, new_value);
        break;
    case QRST_OFFSET:
        fill_qrst_details(value, new_value);
        break;
    case QSAFE_OFFSET:
        fill_qsafe_details(value, new_value);
        break;
    case RDV_OFFSET:
        fill_rdv_details(value, new_value);
        break;
    case REFRESH_OFFSET:
        fill_refresh_details(value, new_value);
        break;
    case BURST_REFRESH_NUM_OFFSET:
        fill_burst_refresh_num_details(value, new_value);
        break;
    case PDEX2WR_OFFSET:
        fill_pdex2wr_details(value, new_value);
        break;
    case PDEX2RD_OFFSET:
        fill_pdex2rd_details(value, new_value);
        break;
    case PCHG2PDEN_OFFSET:
        fill_pchg2pden_details(value, new_value);
        break;
    case ACT2PDEN_OFFSET:
        fill_act2pden_details(value, new_value);
        break;
    case AR2PDEN_OFFSET:
        fill_ar2pden_details(value, new_value);
        break;
    case RW2PDEN_OFFSET:
        fill_rw2pden_details(value, new_value);
        break;
    case TXSR_OFFSET:
        fill_txsr_details(value, new_value);
        break;
    case TCKE_OFFSET:
        fill_tcke_details(value, new_value);
        break;
    case TFAW_OFFSET:
        fill_tfaw_details(value, new_value);
        break;
    case TRPAB_OFFSET:
        fill_trpab_details(value, new_value);
        break;
    case TCLKSTABLE_OFFSET:
        fill_tclkstable_details(value, new_value);
        break;
    case TCLKSTOP_OFFSET:
        fill_tclkstop_details(value, new_value);
        break;
    case TREFBW_OFFSET:
        fill_trefbw_details(value, new_value);
        break;
    case QUSE_EXTRA_OFFSET:
        fill_quse_extra_details(value, new_value);
        break;
    case ODT_WRITE_OFFSET:
        fill_odt_write_details(value, new_value);
        break;
    case ODT_READ_OFFSET:
        fill_odt_read_details(value, new_value);
        break;
    case MRS_OFFSET:
        fill_mrs_details(value, new_value);
        break;
    case EMRS_OFFSET:
        fill_emrs_details(value, new_value);
        break;
    case REF_OFFSET:
        fill_ref_details(value, new_value);
        break;
    case PRE_OFFSET:
        fill_pre_details(value, new_value);
        break;
    case NOP_OFFSET:
        fill_nop_details(value, new_value);
        break;
    case SELF_REF_OFFSET:
        fill_self_ref_details(value, new_value);
        break;
    case DPD_OFFSET:
        fill_dpd_details(value, new_value);
        break;
    case MRW_OFFSET:
        fill_mrw_details(value, new_value);
        break;
    case MRR_OFFSET:
        fill_mrr_details(value, new_value);
        break;
    case FBIO_CFG1_OFFSET:
        fill_fbio_cfg1_details(value, new_value);
        break;
    case FBIO_DQSIB_DLY_OFFSET:
        fill_fbio_dqsib_dly_details(value, new_value);
        break;
    case FBIO_DQSIB_DLY_MSB_OFFSET:
        fill_fbio_dqsib_dly_msb_details(value, new_value);
        break;
    case FBIO_CFG5_OFFSET:
        fill_fbio_cfg5_details(value, new_value);
        break;
    case FBIO_QUSE_DLY_OFFSET:
        fill_fbio_quse_dly_details(value, new_value);
        break;
    case FBIO_QUSE_DLY_MSB_OFFSET:
        fill_fbio_quse_dly_msb_details(value, new_value);
        break;
    case FBIO_CFG6_OFFSET:
        fill_fbio_cfg6_details(value, new_value);
        break;
    case DQS_TRIMMER_RD0_OFFSET:
        fill_dqs_trimmer_rd0_details(value, new_value);
        break;
    case DQS_TRIMMER_RD1_OFFSET:
        fill_dqs_trimmer_rd1_details(value, new_value);
        break;
    case DQS_TRIMMER_RD2_OFFSET:
        fill_dqs_trimmer_rd2_details(value, new_value);
        break;
    case DQS_TRIMMER_RD3_OFFSET:
        fill_dqs_trimmer_rd3_details(value, new_value);
        break;
    case LL_ARB_CONFIG_OFFSET:
        fill_ll_arb_config_details(value, new_value);
        break;
    case T_MIN_CRITICAL_HP_OFFSET:
        fill_t_min_critical_hp_details(value, new_value);
        break;
    case T_MIN_CRITICAL_TIMEOUT_OFFSET:
        fill_t_min_critical_timeout_details(value, new_value);
        break;
    case T_MIN_LOAD_OFFSET:
        fill_t_min_load_details(value, new_value);
        break;
    case T_MAX_CRITICAL_HP_OFFSET:
        fill_t_max_critical_hp_details(value, new_value);
        break;
    case T_MAX_CRITICAL_TIMEOUT_OFFSET:
        fill_t_max_critical_timeout_details(value, new_value);
        break;
    case T_MAX_LOAD_OFFSET:
        fill_t_max_load_details(value, new_value);
        break;
    case AUTO_CAL_CONFIG_OFFSET:
        fill_auto_cal_config_details(value, new_value);
        break;
    case AUTO_CAL_INTERVAL_OFFSET:
        fill_auto_cal_interval_details(value, new_value);
        break;
    case AUTO_CAL_STATUS_OFFSET:
        fill_auto_cal_status_details(value, new_value);
        break;
    case REQ_CTRL_OFFSET:
        fill_req_ctrl_details(value, new_value);
        break;
    case EMC_STATUS_OFFSET:
        fill_emc_status_details(value, new_value);
        break;
    case CFG_2_OFFSET:
        fill_cfg_2_details(value, new_value);
        break;
    case CFG_DIG_DLL_OFFSET:
        fill_cfg_dig_dll_details(value, new_value);
        break;
    case DLL_XFORM_DQS_OFFSET:
        fill_dll_xform_dqs_details(value, new_value);
        break;
    case DLL_XFORM_QUSE_OFFSET:
        fill_dll_xform_quse_details(value, new_value);
        break;
    case DIG_DLL_UPPER_STATUS_OFFSET:
        fill_dig_dll_upper_status_details(value, new_value);
        break;
    case DIG_DLL_LOWER_STATUS_OFFSET:
        fill_dig_dll_lower_status_details(value, new_value);
        break;
    case CTT_TERM_CTRL_OFFSET:
        fill_ctt_term_ctrl_details(value, new_value);
        break;
    case ZCAL_REF_CNT_OFFSET:
        fill_zcal_ref_cnt_details(value, new_value);
        break;
    case ZCAL_WAIT_CNT_OFFSET:
        fill_zcal_wait_cnt_details(value, new_value);
        break;
    case ZCAL_MRW_CMD_OFFSET:
        fill_zcal_mrw_cmd_details(value, new_value);
        break;
    case CMDQ_OFFSET:
        fill_cmdq_details(value, new_value);
        break;
    case FBIO_SPARE_OFFSET:
        fill_fbio_spare_details(value, new_value);
        break;
    case FBIO_WRPTR_EQ_2_OFFSET:
        fill_fbio_wrptr_eq_2_details(value, new_value);
        break;
    case CLKEN_OVERRIDE_OFFSET:
        fill_clken_override_details(value, new_value);
        break;
    case STAT_CONTROL_OFFSET:
        fill_stat_control_details(value, new_value);
        break;
    case STAT_STATUS_OFFSET:
        fill_stat_status_details(value, new_value);
        break;
    case STAT_LLMC_ADDR_LOW_OFFSET:
        fill_stat_llmc_addr_low_details(value, new_value);
        break;
    case STAT_LLMC_ADDR_HIGH_OFFSET:
        fill_stat_llmc_addr_high_details(value, new_value);
        break;
    case STAT_LLMC_CLOCK_LIMIT_OFFSET:
        fill_stat_llmc_clock_limit_details(value, new_value);
        break;
    case STAT_LLMC_CLOCKS_OFFSET:
        fill_stat_llmc_clocks_details(value, new_value);
        break;
    case STAT_LLMC_CONTROL_OFFSET:
        fill_stat_llmc_control_details(value, new_value);
        break;
    case STAT_LLMC_HIST_LIMIT_OFFSET:
        fill_stat_llmc_hist_limit_details(value, new_value);
        break;
    case STAT_LLMC_COUNT_OFFSET:
        fill_stat_llmc_count_details(value, new_value);
        break;
    case STAT_LLMC_HIST_OFFSET:
        fill_stat_llmc_hist_details(value, new_value);
        break;
    case STAT_PWR_CLOCK_LIMIT_OFFSET:
        fill_stat_pwr_clock_limit_details(value, new_value);
        break;
    case STAT_PWR_CLOCKS_OFFSET:
        fill_stat_pwr_clocks_details(value, new_value);
        break;
    case STAT_PWR_COUNT_OFFSET:
        fill_stat_pwr_count_details(value, new_value);
        break;
    case STAT_DRAM_CLOCK_LIMIT_LO_OFFSET:
        fill_stat_dram_clock_limit_lo_details(value, new_value);
        break;
    case STAT_DRAM_CLOCK_LIMIT_HI_OFFSET:
        fill_stat_dram_clock_limit_hi_details(value, new_value);
        break;
    case STAT_DRAM_CLOCKS_LO_OFFSET:
        fill_stat_dram_clocks_lo_details(value, new_value);
        break;
    case STAT_DRAM_CLOCKS_HI_OFFSET:
        fill_stat_dram_clocks_hi_details(value, new_value);
        break;
    case STAT_DRAM_DEV0_ACTIVATE_CNT_LO_OFFSET:
        fill_stat_dram_dev0_activate_cnt_lo_details(value, new_value);
        break;
    case STAT_DRAM_DEV0_ACTIVATE_CNT_HI_OFFSET:
        fill_stat_dram_dev0_activate_cnt_hi_details(value, new_value);
        break;
    case STAT_DRAM_DEV0_READ_CNT_LO_OFFSET:
        fill_stat_dram_dev0_read_cnt_lo_details(value, new_value);
        break;
    case STAT_DRAM_DEV0_READ_CNT_HI_OFFSET:
        fill_stat_dram_dev0_read_cnt_hi_details(value, new_value);
        break;
    case STAT_DRAM_DEV0_WRITE_CNT_LO_OFFSET:
        fill_stat_dram_dev0_write_cnt_lo_details(value, new_value);
        break;
    case STAT_DRAM_DEV0_WRITE_CNT_HI_OFFSET:
        fill_stat_dram_dev0_write_cnt_hi_details(value, new_value);
        break;
    case STAT_DRAM_DEV0_REF_CNT_LO_OFFSET:
        fill_stat_dram_dev0_ref_cnt_lo_details(value, new_value);
        break;
    case STAT_DRAM_DEV0_REF_CNT_HI_OFFSET:
        fill_stat_dram_dev0_ref_cnt_hi_details(value, new_value);
        break;
    case STAT_DRAM_DEV0_CUMM_BANKS_ACTIVE_CKE_EQ1_LO_OFFSET:
        fill_stat_dram_dev0_cumm_banks_active_cke_eq1_lo_details(value, new_value);
        break;
    case STAT_DRAM_DEV0_CUMM_BANKS_ACTIVE_CKE_EQ1_HI_OFFSET:
        fill_stat_dram_dev0_cumm_banks_active_cke_eq1_hi_details(value, new_value);
        break;
    case STAT_DRAM_DEV0_CUMM_BANKS_ACTIVE_CKE_EQ0_LO_OFFSET:
        fill_stat_dram_dev0_cumm_banks_active_cke_eq0_lo_details(value, new_value);
        break;
    case STAT_DRAM_DEV0_CUMM_BANKS_ACTIVE_CKE_EQ0_HI_OFFSET:
        fill_stat_dram_dev0_cumm_banks_active_cke_eq0_hi_details(value, new_value);
        break;
    case STAT_DRAM_DEV0_CKE_EQ1_CLKS_LO_OFFSET:
        fill_stat_dram_dev0_cke_eq1_clks_lo_details(value, new_value);
        break;
    case STAT_DRAM_DEV0_CKE_EQ1_CLKS_HI_OFFSET:
        fill_stat_dram_dev0_cke_eq1_clks_hi_details(value, new_value);
        break;
    case STAT_DRAM_DEV0_EXTCLKS_CKE_EQ1_LO_OFFSET:
        fill_stat_dram_dev0_extclks_cke_eq1_lo_details(value, new_value);
        break;
    case STAT_DRAM_DEV0_EXTCLKS_CKE_EQ1_HI_OFFSET:
        fill_stat_dram_dev0_extclks_cke_eq1_hi_details(value, new_value);
        break;
    case STAT_DRAM_DEV0_EXTCLKS_CKE_EQ0_LO_OFFSET:
        fill_stat_dram_dev0_extclks_cke_eq0_lo_details(value, new_value);
        break;
    case STAT_DRAM_DEV0_EXTCLKS_CKE_EQ0_HI_OFFSET:
        fill_stat_dram_dev0_extclks_cke_eq0_hi_details(value, new_value);
        break;
    case STAT_DRAM_DEV1_ACTIVATE_CNT_LO_OFFSET:
        fill_stat_dram_dev1_activate_cnt_lo_details(value, new_value);
        break;
    case STAT_DRAM_DEV1_ACTIVATE_CNT_HI_OFFSET:
        fill_stat_dram_dev1_activate_cnt_hi_details(value, new_value);
        break;
    case STAT_DRAM_DEV1_READ_CNT_LO_OFFSET:
        fill_stat_dram_dev1_read_cnt_lo_details(value, new_value);
        break;
    case STAT_DRAM_DEV1_READ_CNT_HI_OFFSET:
        fill_stat_dram_dev1_read_cnt_hi_details(value, new_value);
        break;
    case STAT_DRAM_DEV1_WRITE_CNT_LO_OFFSET:
        fill_stat_dram_dev1_write_cnt_lo_details(value, new_value);
        break;
    case STAT_DRAM_DEV1_WRITE_CNT_HI_OFFSET:
        fill_stat_dram_dev1_write_cnt_hi_details(value, new_value);
        break;
    case STAT_DRAM_DEV1_REF_CNT_LO_OFFSET:
        fill_stat_dram_dev1_ref_cnt_lo_details(value, new_value);
        break;
    case STAT_DRAM_DEV1_REF_CNT_HI_OFFSET:
        fill_stat_dram_dev1_ref_cnt_hi_details(value, new_value);
        break;
    case STAT_DRAM_DEV1_CUMM_BANKS_ACTIVE_CKE_EQ1_LO_OFFSET:
        fill_stat_dram_dev1_cumm_banks_active_cke_eq1_lo_details(value, new_value);
        break;
    case STAT_DRAM_DEV1_CUMM_BANKS_ACTIVE_CKE_EQ1_HI_OFFSET:
        fill_stat_dram_dev1_cumm_banks_active_cke_eq1_hi_details(value, new_value);
        break;
    case STAT_DRAM_DEV1_CUMM_BANKS_ACTIVE_CKE_EQ0_LO_OFFSET:
        fill_stat_dram_dev1_cumm_banks_active_cke_eq0_lo_details(value, new_value);
        break;
    case STAT_DRAM_DEV1_CUMM_BANKS_ACTIVE_CKE_EQ0_HI_OFFSET:
        fill_stat_dram_dev1_cumm_banks_active_cke_eq0_hi_details(value, new_value);
        break;
    case STAT_DRAM_DEV1_CKE_EQ1_CLKS_LO_OFFSET:
        fill_stat_dram_dev1_cke_eq1_clks_lo_details(value, new_value);
        break;
    case STAT_DRAM_DEV1_CKE_EQ1_CLKS_HI_OFFSET:
        fill_stat_dram_dev1_cke_eq1_clks_hi_details(value, new_value);
        break;
    case STAT_DRAM_DEV1_EXTCLKS_CKE_EQ1_LO_OFFSET:
        fill_stat_dram_dev1_extclks_cke_eq1_lo_details(value, new_value);
        break;
    case STAT_DRAM_DEV1_EXTCLKS_CKE_EQ1_HI_OFFSET:
        fill_stat_dram_dev1_extclks_cke_eq1_hi_details(value, new_value);
        break;
    case STAT_DRAM_DEV1_EXTCLKS_CKE_EQ0_LO_OFFSET:
        fill_stat_dram_dev1_extclks_cke_eq0_lo_details(value, new_value);
        break;
    case STAT_DRAM_DEV1_EXTCLKS_CKE_EQ0_HI_OFFSET:
        fill_stat_dram_dev1_extclks_cke_eq0_hi_details(value, new_value);
        break;
    case STAT_DRAM_DEV0_NO_BANKS_ACTIVE_CKE_EQ1_LO_OFFSET:
        fill_stat_dram_dev0_no_banks_active_cke_eq1_lo_details(value, new_value);
        break;
    case STAT_DRAM_DEV0_NO_BANKS_ACTIVE_CKE_EQ1_HI_OFFSET:
        fill_stat_dram_dev0_no_banks_active_cke_eq1_hi_details(value, new_value);
        break;
    case STAT_DRAM_DEV0_NO_BANKS_ACTIVE_CKE_EQ0_LO_OFFSET:
        fill_stat_dram_dev0_no_banks_active_cke_eq0_lo_details(value, new_value);
        break;
    case STAT_DRAM_DEV0_NO_BANKS_ACTIVE_CKE_EQ0_HI_OFFSET:
        fill_stat_dram_dev0_no_banks_active_cke_eq0_hi_details(value, new_value);
        break;
    case STAT_DRAM_DEV1_NO_BANKS_ACTIVE_CKE_EQ1_LO_OFFSET:
        fill_stat_dram_dev1_no_banks_active_cke_eq1_lo_details(value, new_value);
        break;
    case STAT_DRAM_DEV1_NO_BANKS_ACTIVE_CKE_EQ1_HI_OFFSET:
        fill_stat_dram_dev1_no_banks_active_cke_eq1_hi_details(value, new_value);
        break;
    case STAT_DRAM_DEV1_NO_BANKS_ACTIVE_CKE_EQ0_LO_OFFSET:
        fill_stat_dram_dev1_no_banks_active_cke_eq0_lo_details(value, new_value);
        break;
    case STAT_DRAM_DEV1_NO_BANKS_ACTIVE_CKE_EQ0_HI_OFFSET:
        fill_stat_dram_dev1_no_banks_active_cke_eq0_hi_details(value, new_value);
        break;
    case CFG_CLKTRIM_OFFSET:
        fill_cfg_clktrim_details(value, new_value);
        break;
    case CFG_CLKTRIM_1_OFFSET:
        fill_cfg_clktrim_1_details(value, new_value);
        break;
    case CFG_CLKTRIM_2_OFFSET:
        fill_cfg_clktrim_2_details(value, new_value);
        break;

    default:
        m_bit_details_model.bits.clear();
        break;
    }
}
