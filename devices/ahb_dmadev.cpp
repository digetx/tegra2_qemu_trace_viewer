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

#include "ahb_dmadev.h"

#include <QDebug>

#define CMD_OFFSET 0x0
#define CMD_UNDEFMASK 0x7FFFFFFF
union cmd_u {
    struct {
        unsigned int undefined_bits_0_30:31;
        unsigned int gen:1;                 /* 0 = Disable AHB-DMA; 0 = DISABLE; 1 = ENABLE */
    };

    u_int32_t reg32;
};

void Ahb_dmaDev::fill_cmd_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const cmd_u old_value_t = { .reg32 = value };
    const cmd_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_30:31", "", 31, old_value_t.undefined_bits_0_30, new_value_t.undefined_bits_0_30 };
    m_bit_details_model.bits.append(entry);
    entry = { "31: gen:1",
              "0 = Disable AHB-DMA;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.gen, new_value_t.gen };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "AHB-DMA Command Register\nThe Global Enable bit in the command register enables the AHB DMA. Clearing this bit causes active DMA transfers to be paused. Pending bus transactions (ongoing burst) are completed and no new transactions are generated. Set this bit again to resume transfers.";
}

#define STA_OFFSET 0x4
#define STA_UNDEFMASK 0xF0FFFFFF
union sta_u {
    struct {
        unsigned int undefined_bits_0_23:24;
        unsigned int ch0:1;                 /* AHB DMA channel busy status flags set/cleared by HW; 0 = NOT_BUSY; 1 = BUSY */
        unsigned int ch1:1;                 /* AHB DMA channel busy status flags set/cleared by HW; 0 = NOT_BUSY; 1 = BUSY */
        unsigned int ch2:1;                 /* AHB DMA channel busy status flags set/cleared by HW; 0 = NOT_BUSY; 1 = BUSY */
        unsigned int ch3:1;                 /* AHB DMA channel busy status flags set/cleared by HW; 0 = NOT_BUSY; 1 = BUSY */
        unsigned int undefined_bits_28_31:4;
    };

    u_int32_t reg32;
};

void Ahb_dmaDev::fill_sta_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const sta_u old_value_t = { .reg32 = value };
    const sta_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_23:24", "", 24, old_value_t.undefined_bits_0_23, new_value_t.undefined_bits_0_23 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: ch0:1",
              "AHB DMA channel busy status flags set/cleared by HW;\n0 = NOT_BUSY;\n1 = BUSY",
              1, old_value_t.ch0, new_value_t.ch0 };
    m_bit_details_model.bits.append(entry);
    entry = { "25: ch1:1",
              "AHB DMA channel busy status flags set/cleared by HW;\n0 = NOT_BUSY;\n1 = BUSY",
              1, old_value_t.ch1, new_value_t.ch1 };
    m_bit_details_model.bits.append(entry);
    entry = { "26: ch2:1",
              "AHB DMA channel busy status flags set/cleared by HW;\n0 = NOT_BUSY;\n1 = BUSY",
              1, old_value_t.ch2, new_value_t.ch2 };
    m_bit_details_model.bits.append(entry);
    entry = { "27: ch3:1",
              "AHB DMA channel busy status flags set/cleared by HW;\n0 = NOT_BUSY;\n1 = BUSY",
              1, old_value_t.ch3, new_value_t.ch3 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: undefined_bits_28_31:4", "", 4, old_value_t.undefined_bits_28_31, new_value_t.undefined_bits_28_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "AHB-DMA Status Register\nBusy bits in the status register indicate which (if any) of the AHB DMA channels have active pending AHB DMA transfers.\nAHB DMA transfers that are started in continuous (repetitive) mode have their busy bits active until the enable bit for the AHB DMA channel is cleared to 0.";
}

#define TX_REQ_OFFSET 0x8
#define TX_REQ_UNDEFMASK 0x00303000
union tx_req_u {
    struct {
        unsigned int cntr_req:1;            /* Enable Counter requestor; 0 = DISABLE; 1 = ENABLE */
        unsigned int smp_17:1;              /* Enable software requestor SMP17 from the SHRD_SMP.STA register; 0 = DISABLE; 1 = ENABLE */
        unsigned int smp_18:1;              /* Enable software requestor SMP18 from the SHRD_SMP.STA register; 0 = DISABLE; 1 = ENABLE */
        unsigned int smp_19:1;              /* Enable software requestor SMP19 from the SHRD_SMP.STA register; 0 = DISABLE; 1 = ENABLE */
        unsigned int smp_20:1;              /* Enable software requestor SMP20 from the SHRD_SMP.STA register; 0 = DISABLE; 1 = ENABLE */
        unsigned int smp_21:1;              /* Enable software requestor SMP21 from the SHRD_SMP.STA register; 0 = DISABLE; 1 = ENABLE */
        unsigned int smp_22:1;              /* Enable software requestor SMP22 from the SHRD_SMP.STA register; 0 = DISABLE; 1 = ENABLE */
        unsigned int smp_23:1;              /* Enable software requestor SMP23 from the SHRD_SMP.STA register; 0 = DISABLE; 1 = ENABLE */
        unsigned int smp_24:1;              /* Enable software requestor SMP24 from the SHRD_SMP.STA register; 0 = DISABLE; 1 = ENABLE */
        unsigned int smp_25:1;              /* Enable software requestor SMP25 from the SHRD_SMP.STA register; 0 = DISABLE; 1 = ENABLE */
        unsigned int smp_26:1;              /* Enable software requestor SMP26 from the SHRD_SMP.STA register; 0 = DISABLE; 1 = ENABLE */
        unsigned int host1x:1;              /* 0 = NOP; 0 = DISABLE; 1 = ENABLE */
        unsigned int undefined_bits_12_13:2;
        unsigned int srq0_xrq_a:1;          /* 0 = NOP; 0 = DISABLE; 1 = ENABLE */
        unsigned int srq1_xrq_b:1;          /* 0 = NOP; 0 = DISABLE; 1 = ENABLE */
        unsigned int smp_30_same_as_30_bit:1; /* Software requestor SMP30 from the SHRD_SMP.STA register.(same as bit[30]); 0 = DISABLE; 1 = ENABLE */
        unsigned int smp_31_same_as_31_bit:1; /* Software requestor SMP31 from the SHRD_SMP.STA register (same as bit[31]); 0 = DISABLE; 1 = ENABLE */
        unsigned int hrq2_xrq_c:1;          /* 0 = NOP; 0 = DISABLE; 1 = ENABLE */
        unsigned int hrq3_xrq_d:1;          /* 0 = NOP; 0 = DISABLE; 1 = ENABLE */
        unsigned int undefined_bits_20_21:2;
        unsigned int hrq6_tmr1:1;           /* Timer 1 Interrupt; 0 = DISABLE; 1 = ENABLE */
        unsigned int hrq7_tmr2:1;           /* Timer 2 Interrupt; 0 = DISABLE; 1 = ENABLE */
        unsigned int ahb_0:1;               /* End of AHB-DMA Transfer on Channel 0; 0 = DISABLE; 1 = ENABLE */
        unsigned int ahb_1:1;               /* End of AHB-DMA Transfer on Channel 1; 0 = DISABLE; 1 = ENABLE */
        unsigned int ahb_2:1;               /* End of AHB-DMA Transfer on Channel 2; 0 = DISABLE; 1 = ENABLE */
        unsigned int ahb_3:1;               /* End of AHB-DMA Transfer on Channel 3; 0 = DISABLE; 1 = ENABLE */
        unsigned int smp_28:1;              /* Software requestor SMP28 from the SHRD_SMP.STA register; 0 = DISABLE; 1 = ENABLE */
        unsigned int smp_29:1;              /* Software requestor SMP29 from the SHRD_SMP.STA register; 0 = DISABLE; 1 = ENABLE */
        unsigned int smp_30:1;              /* Software requestor SMP30 from the SHRD_SMP.STA register; 0 = DISABLE; 1 = ENABLE */
        unsigned int smp_31:1;              /* Software requestor SMP31 from the SHRD_SMP.STA register; 0 = DISABLE; 1 = ENABLE */
    };

    u_int32_t reg32;
};

void Ahb_dmaDev::fill_tx_req_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const tx_req_u old_value_t = { .reg32 = value };
    const tx_req_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: cntr_req:1",
              "Enable Counter requestor;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.cntr_req, new_value_t.cntr_req };
    m_bit_details_model.bits.append(entry);
    entry = { "01: smp_17:1",
              "Enable software requestor SMP17 from the SHRD_SMP.STA register;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.smp_17, new_value_t.smp_17 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: smp_18:1",
              "Enable software requestor SMP18 from the SHRD_SMP.STA register;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.smp_18, new_value_t.smp_18 };
    m_bit_details_model.bits.append(entry);
    entry = { "03: smp_19:1",
              "Enable software requestor SMP19 from the SHRD_SMP.STA register;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.smp_19, new_value_t.smp_19 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: smp_20:1",
              "Enable software requestor SMP20 from the SHRD_SMP.STA register;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.smp_20, new_value_t.smp_20 };
    m_bit_details_model.bits.append(entry);
    entry = { "05: smp_21:1",
              "Enable software requestor SMP21 from the SHRD_SMP.STA register;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.smp_21, new_value_t.smp_21 };
    m_bit_details_model.bits.append(entry);
    entry = { "06: smp_22:1",
              "Enable software requestor SMP22 from the SHRD_SMP.STA register;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.smp_22, new_value_t.smp_22 };
    m_bit_details_model.bits.append(entry);
    entry = { "07: smp_23:1",
              "Enable software requestor SMP23 from the SHRD_SMP.STA register;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.smp_23, new_value_t.smp_23 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: smp_24:1",
              "Enable software requestor SMP24 from the SHRD_SMP.STA register;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.smp_24, new_value_t.smp_24 };
    m_bit_details_model.bits.append(entry);
    entry = { "09: smp_25:1",
              "Enable software requestor SMP25 from the SHRD_SMP.STA register;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.smp_25, new_value_t.smp_25 };
    m_bit_details_model.bits.append(entry);
    entry = { "10: smp_26:1",
              "Enable software requestor SMP26 from the SHRD_SMP.STA register;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.smp_26, new_value_t.smp_26 };
    m_bit_details_model.bits.append(entry);
    entry = { "11: host1x:1",
              "0 = NOP;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.host1x, new_value_t.host1x };
    m_bit_details_model.bits.append(entry);
    entry = { "12: undefined_bits_12_13:2", "", 2, old_value_t.undefined_bits_12_13, new_value_t.undefined_bits_12_13 };
    m_bit_details_model.bits.append(entry);
    entry = { "14: srq0_xrq_a:1",
              "0 = NOP;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.srq0_xrq_a, new_value_t.srq0_xrq_a };
    m_bit_details_model.bits.append(entry);
    entry = { "15: srq1_xrq_b:1",
              "0 = NOP;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.srq1_xrq_b, new_value_t.srq1_xrq_b };
    m_bit_details_model.bits.append(entry);
    entry = { "16: smp_30_same_as_30_bit:1",
              "Software requestor SMP30 from the SHRD_SMP.STA register.(same as bit[30]);\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.smp_30_same_as_30_bit, new_value_t.smp_30_same_as_30_bit };
    m_bit_details_model.bits.append(entry);
    entry = { "17: smp_31_same_as_31_bit:1",
              "Software requestor SMP31 from the SHRD_SMP.STA register (same as bit[31]);\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.smp_31_same_as_31_bit, new_value_t.smp_31_same_as_31_bit };
    m_bit_details_model.bits.append(entry);
    entry = { "18: hrq2_xrq_c:1",
              "0 = NOP;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.hrq2_xrq_c, new_value_t.hrq2_xrq_c };
    m_bit_details_model.bits.append(entry);
    entry = { "19: hrq3_xrq_d:1",
              "0 = NOP;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.hrq3_xrq_d, new_value_t.hrq3_xrq_d };
    m_bit_details_model.bits.append(entry);
    entry = { "20: undefined_bits_20_21:2", "", 2, old_value_t.undefined_bits_20_21, new_value_t.undefined_bits_20_21 };
    m_bit_details_model.bits.append(entry);
    entry = { "22: hrq6_tmr1:1",
              "Timer 1 Interrupt;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.hrq6_tmr1, new_value_t.hrq6_tmr1 };
    m_bit_details_model.bits.append(entry);
    entry = { "23: hrq7_tmr2:1",
              "Timer 2 Interrupt;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.hrq7_tmr2, new_value_t.hrq7_tmr2 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: ahb_0:1",
              "End of AHB-DMA Transfer on Channel 0;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ahb_0, new_value_t.ahb_0 };
    m_bit_details_model.bits.append(entry);
    entry = { "25: ahb_1:1",
              "End of AHB-DMA Transfer on Channel 1;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ahb_1, new_value_t.ahb_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "26: ahb_2:1",
              "End of AHB-DMA Transfer on Channel 2;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ahb_2, new_value_t.ahb_2 };
    m_bit_details_model.bits.append(entry);
    entry = { "27: ahb_3:1",
              "End of AHB-DMA Transfer on Channel 3;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ahb_3, new_value_t.ahb_3 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: smp_28:1",
              "Software requestor SMP28 from the SHRD_SMP.STA register;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.smp_28, new_value_t.smp_28 };
    m_bit_details_model.bits.append(entry);
    entry = { "29: smp_29:1",
              "Software requestor SMP29 from the SHRD_SMP.STA register;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.smp_29, new_value_t.smp_29 };
    m_bit_details_model.bits.append(entry);
    entry = { "30: smp_30:1",
              "Software requestor SMP30 from the SHRD_SMP.STA register;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.smp_30, new_value_t.smp_30 };
    m_bit_details_model.bits.append(entry);
    entry = { "31: smp_31:1",
              "Software requestor SMP31 from the SHRD_SMP.STA register;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.smp_31, new_value_t.smp_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "AHB-DMA Requestor Assignments\nThe Tx Requestors are values used as triggers or flow controls for AHB DMA transfers.";
}

#define COUNTER_OFFSET 0x10
#define COUNTER_UNDEFMASK 0xFFC00000
union counter_u {
    struct {
        unsigned int count_value:16;        /* DMA COUNT Init/Reload Value */
        unsigned int prd_en:1;              /* Normally, AHB DMA current count value is reloaded to the programmed init/reload value whenever the current count reaches 0. If this bit is set, the reload is additionally qualified with the condition that the last word of the burst is being sent. This will delay the reload of the counter by only a few cycles from when the counter value reaches 0; 0 = DISABLE; 1 = ENABLE */
        unsigned int cntr_en:1;             /* When this bit is set Counter is enabled; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch0_fl_cnt:1;          /* Controls AHB DMA channel0 self-throttle based on the AHB DMA Counter Value. If this bit field is active, then AHB DMA counter value will be enabled for decrement and reload (just as if CNTR.EN is set); 0 = DISABLE; 1 = ENABLE */
        unsigned int ch1_fl_cnt:1;          /* Controls AHB DMA channel1 self-throttle based on the AHB DMA Counter Value. If this bit field is active, then AHB DMA counter value will be enabled for decrement and reload (just as if CNTR.EN is set); 0 = DISABLE; 1 = ENABLE */
        unsigned int ch2_fl_cnt:1;          /* Controls AHB DMA channel2 self-throttle based on the AHB DMA Counter Value. If this bit field is active, then AHB DMA counter value will be enabled for decrement and reload (just as if CNTR.EN is set); 0 = DISABLE; 1 = ENABLE */
        unsigned int ch3_fl_cnt:1;          /* Controls AHB DMA channel3 self-throttle based on the AHB DMA Counter Value. If this bit field is active, then AHB DMA counter value will be enabled for decrement and reload (just as if CNTR.EN is set); 0 = DISABLE; 1 = ENABLE */
        unsigned int undefined_bits_22_31:10;
    };

    u_int32_t reg32;
};

void Ahb_dmaDev::fill_counter_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const counter_u old_value_t = { .reg32 = value };
    const counter_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: count_value:16",
              "DMA COUNT Init/Reload Value",
              16, old_value_t.count_value, new_value_t.count_value };
    m_bit_details_model.bits.append(entry);
    entry = { "16: prd_en:1",
              "Normally, AHB DMA current count value is reloaded to the programmed init/reload value whenever the current count reaches 0. If this bit is set, the reload is additionally qualified with the condition that the last word of the burst is being sent. This will delay the reload of the counter by only a few cycles from when the counter value reaches 0;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.prd_en, new_value_t.prd_en };
    m_bit_details_model.bits.append(entry);
    entry = { "17: cntr_en:1",
              "When this bit is set Counter is enabled;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.cntr_en, new_value_t.cntr_en };
    m_bit_details_model.bits.append(entry);
    entry = { "18: ch0_fl_cnt:1",
              "Controls AHB DMA channel0 self-throttle based on the AHB DMA Counter Value. If this bit field is active, then AHB DMA counter value will be enabled for decrement and reload (just as if CNTR.EN is set);\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch0_fl_cnt, new_value_t.ch0_fl_cnt };
    m_bit_details_model.bits.append(entry);
    entry = { "19: ch1_fl_cnt:1",
              "Controls AHB DMA channel1 self-throttle based on the AHB DMA Counter Value. If this bit field is active, then AHB DMA counter value will be enabled for decrement and reload (just as if CNTR.EN is set);\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch1_fl_cnt, new_value_t.ch1_fl_cnt };
    m_bit_details_model.bits.append(entry);
    entry = { "20: ch2_fl_cnt:1",
              "Controls AHB DMA channel2 self-throttle based on the AHB DMA Counter Value. If this bit field is active, then AHB DMA counter value will be enabled for decrement and reload (just as if CNTR.EN is set);\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch2_fl_cnt, new_value_t.ch2_fl_cnt };
    m_bit_details_model.bits.append(entry);
    entry = { "21: ch3_fl_cnt:1",
              "Controls AHB DMA channel3 self-throttle based on the AHB DMA Counter Value. If this bit field is active, then AHB DMA counter value will be enabled for decrement and reload (just as if CNTR.EN is set);\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch3_fl_cnt, new_value_t.ch3_fl_cnt };
    m_bit_details_model.bits.append(entry);
    entry = { "22: undefined_bits_22_31:10", "", 10, old_value_t.undefined_bits_22_31, new_value_t.undefined_bits_22_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Controls which (if any) AHB DMA channel(s) will self-throttle based on the AHB DMA Counter Value. If any bit in [21:18] 4-bit  field is active, then AHB DMA counter value will be enabled for decrement and  reload (just as if CNTR.EN is set).\nAHB-DMA Counter Usage\nThe AHB DMA Counter is used to slow down the request rates on some AHB DMA channels. It stores bits that configure which (if any) channel(s) should be throttled.";
}

#define IRQ_STA_CPU_OFFSET 0x14
#define IRQ_STA_CPU_UNDEFMASK 0xFFFFFFF0
union irq_sta_cpu_u {
    struct {
        unsigned int ch0:1;                 /* Gathers all the after-masking CPU directed IRQ status bits from channel0; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch1:1;                 /* Gathers all the after-masking CPU directed IRQ status bits from channel1; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch2:1;                 /* Gathers all the after-masking CPU directed IRQ status bits from channel2; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch3:1;                 /* Gathers all the after-masking CPU directed IRQ status bits from channel3; 0 = DISABLE; 1 = ENABLE */
        unsigned int undefined_bits_4_31:28;
    };

    u_int32_t reg32;
};

void Ahb_dmaDev::fill_irq_sta_cpu_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const irq_sta_cpu_u old_value_t = { .reg32 = value };
    const irq_sta_cpu_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: ch0:1",
              "Gathers all the after-masking CPU directed IRQ status bits from channel0;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch0, new_value_t.ch0 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: ch1:1",
              "Gathers all the after-masking CPU directed IRQ status bits from channel1;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch1, new_value_t.ch1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: ch2:1",
              "Gathers all the after-masking CPU directed IRQ status bits from channel2;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch2, new_value_t.ch2 };
    m_bit_details_model.bits.append(entry);
    entry = { "03: ch3:1",
              "Gathers all the after-masking CPU directed IRQ status bits from channel3;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch3, new_value_t.ch3 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: undefined_bits_4_31:28", "", 28, old_value_t.undefined_bits_4_31, new_value_t.undefined_bits_4_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "AHB-DMA MASK_CPU Register Usage\nGathers all the after-masking CPU directed IRQ status bits.";
}

#define IRQ_STA_COP_OFFSET 0x18
#define IRQ_STA_COP_UNDEFMASK 0xFFFFFFF0
union irq_sta_cop_u {
    struct {
        unsigned int ch0:1;                 /* Gathers all the after-masking COP directed IRQ status bits from channel0; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch1:1;                 /* Gathers all the after-masking COP directed IRQ status bits from channel1; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch2:1;                 /* Gathers all the after-masking COP directed IRQ status bits from channel2; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch3:1;                 /* Gathers all the after-masking COP directed IRQ status bits from channel3; 0 = DISABLE; 1 = ENABLE */
        unsigned int undefined_bits_4_31:28;
    };

    u_int32_t reg32;
};

void Ahb_dmaDev::fill_irq_sta_cop_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const irq_sta_cop_u old_value_t = { .reg32 = value };
    const irq_sta_cop_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: ch0:1",
              "Gathers all the after-masking COP directed IRQ status bits from channel0;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch0, new_value_t.ch0 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: ch1:1",
              "Gathers all the after-masking COP directed IRQ status bits from channel1;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch1, new_value_t.ch1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: ch2:1",
              "Gathers all the after-masking COP directed IRQ status bits from channel2;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch2, new_value_t.ch2 };
    m_bit_details_model.bits.append(entry);
    entry = { "03: ch3:1",
              "Gathers all the after-masking COP directed IRQ status bits from channel3;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch3, new_value_t.ch3 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: undefined_bits_4_31:28", "", 28, old_value_t.undefined_bits_4_31, new_value_t.undefined_bits_4_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "AHB-DMA MASK_COP Register Usage\nGathers all the after-masking COP directed IRQ status bits.";
}

#define IRQ_MASK_OFFSET 0x1C
#define IRQ_MASK_UNDEFMASK 0xFFFFFFF0
union irq_mask_u {
    struct {
        unsigned int ch0:1;                 /* Each bit allows the associated channel0 IRQ to propagate when '1'; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch1:1;                 /* Each bit allows the associated channel1 IRQ to propagate when '1'; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch2:1;                 /* Each bit allows the associated channel2 IRQ to propagate when '1'; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch3:1;                 /* Each bit allows the associated channel3 IRQ to propagate when '1'; 0 = DISABLE; 1 = ENABLE */
        unsigned int undefined_bits_4_31:28;
    };

    u_int32_t reg32;
};

void Ahb_dmaDev::fill_irq_mask_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const irq_mask_u old_value_t = { .reg32 = value };
    const irq_mask_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: ch0:1",
              "Each bit allows the associated channel0 IRQ to propagate when '1';\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch0, new_value_t.ch0 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: ch1:1",
              "Each bit allows the associated channel1 IRQ to propagate when '1';\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch1, new_value_t.ch1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: ch2:1",
              "Each bit allows the associated channel2 IRQ to propagate when '1';\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch2, new_value_t.ch2 };
    m_bit_details_model.bits.append(entry);
    entry = { "03: ch3:1",
              "Each bit allows the associated channel3 IRQ to propagate when '1';\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch3, new_value_t.ch3 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: undefined_bits_4_31:28", "", 28, old_value_t.undefined_bits_4_31, new_value_t.undefined_bits_4_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "AHB-DMA SET_MASK Register Usage\nAllows the IRQ to propagate when enabled, this is the ANDed result of set and clear mask bits.";
}

#define IRQ_MASK_SET_OFFSET 0x20
#define IRQ_MASK_SET_UNDEFMASK 0xFFFFFFF0
union irq_mask_set_u {
    struct {
        unsigned int ch0:1;                 /* Writing  1 Sets the Mask Register for CH0; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch1:1;                 /* Writing  1 Sets the Mask Register for CH1; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch2:1;                 /* Writing  1 Sets the Mask Register for CH2; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch3:1;                 /* Writing  1 Sets the Mask Register for CH3; 0 = DISABLE; 1 = ENABLE */
        unsigned int undefined_bits_4_31:28;
    };

    u_int32_t reg32;
};

void Ahb_dmaDev::fill_irq_mask_set_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const irq_mask_set_u old_value_t = { .reg32 = value };
    const irq_mask_set_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: ch0:1",
              "Writing  1 Sets the Mask Register for CH0;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch0, new_value_t.ch0 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: ch1:1",
              "Writing  1 Sets the Mask Register for CH1;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch1, new_value_t.ch1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: ch2:1",
              "Writing  1 Sets the Mask Register for CH2;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch2, new_value_t.ch2 };
    m_bit_details_model.bits.append(entry);
    entry = { "03: ch3:1",
              "Writing  1 Sets the Mask Register for CH3;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch3, new_value_t.ch3 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: undefined_bits_4_31:28", "", 28, old_value_t.undefined_bits_4_31, new_value_t.undefined_bits_4_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "AHB-DMA CLR_MASK Register Usage\nThis register sets the Mask for the IRQs.";
}

#define IRQ_MASK_CLR_OFFSET 0x24
#define IRQ_MASK_CLR_UNDEFMASK 0xFFFFFFF0
union irq_mask_clr_u {
    struct {
        unsigned int ch0:1;                 /* Writing  1 Clears the Mask Register for CH0; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch1:1;                 /* Writing  1 Clears the Mask Register for CH1; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch2:1;                 /* Writing  1 Clears the Mask Register for CH2; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch3:1;                 /* Writing  1 Clears the Mask Register for CH3; 0 = DISABLE; 1 = ENABLE */
        unsigned int undefined_bits_4_31:28;
    };

    u_int32_t reg32;
};

void Ahb_dmaDev::fill_irq_mask_clr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const irq_mask_clr_u old_value_t = { .reg32 = value };
    const irq_mask_clr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: ch0:1",
              "Writing  1 Clears the Mask Register for CH0;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch0, new_value_t.ch0 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: ch1:1",
              "Writing  1 Clears the Mask Register for CH1;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch1, new_value_t.ch1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: ch2:1",
              "Writing  1 Clears the Mask Register for CH2;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch2, new_value_t.ch2 };
    m_bit_details_model.bits.append(entry);
    entry = { "03: ch3:1",
              "Writing  1 Clears the Mask Register for CH3;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ch3, new_value_t.ch3 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: undefined_bits_4_31:28", "", 28, old_value_t.undefined_bits_4_31, new_value_t.undefined_bits_4_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "AHB-DMA Requestor Usage\nThis register clears the IRQs.";
}

#define RDWR_COHERENCY_OFFSET 0x28
#define RDWR_COHERENCY_UNDEFMASK 0x7FF0FFF0
union rdwr_coherency_u {
    struct {
        unsigned int ch0_wrs_active:1;
        unsigned int ch1_wrs_active:1;
        unsigned int ch2_wrs_active:1;
        unsigned int ch3_wrs_active:1;      /* 1=ahbdma channel 3 has write transaction(s) outstanding */
        unsigned int undefined_bits_4_15:12;
        unsigned int ch0_rds_active:1;
        unsigned int ch1_rds_active:1;
        unsigned int ch2_rds_active:1;
        unsigned int ch3_rds_active:1;      /* 1=ahbdma channel 3 has read transaction(s) outstanding */
        unsigned int undefined_bits_20_30:11;
        unsigned int mst_gizmo_wrque_empty:1;
    };

    u_int32_t reg32;
};

void Ahb_dmaDev::fill_rdwr_coherency_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const rdwr_coherency_u old_value_t = { .reg32 = value };
    const rdwr_coherency_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: ch0_wrs_active:1", "", 1, old_value_t.ch0_wrs_active, new_value_t.ch0_wrs_active };
    m_bit_details_model.bits.append(entry);
    entry = { "01: ch1_wrs_active:1", "", 1, old_value_t.ch1_wrs_active, new_value_t.ch1_wrs_active };
    m_bit_details_model.bits.append(entry);
    entry = { "02: ch2_wrs_active:1", "", 1, old_value_t.ch2_wrs_active, new_value_t.ch2_wrs_active };
    m_bit_details_model.bits.append(entry);
    entry = { "03: ch3_wrs_active:1",
              "1=ahbdma channel 3 has write transaction(s) outstanding",
              1, old_value_t.ch3_wrs_active, new_value_t.ch3_wrs_active };
    m_bit_details_model.bits.append(entry);
    entry = { "04: undefined_bits_4_15:12", "", 12, old_value_t.undefined_bits_4_15, new_value_t.undefined_bits_4_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: ch0_rds_active:1", "", 1, old_value_t.ch0_rds_active, new_value_t.ch0_rds_active };
    m_bit_details_model.bits.append(entry);
    entry = { "17: ch1_rds_active:1", "", 1, old_value_t.ch1_rds_active, new_value_t.ch1_rds_active };
    m_bit_details_model.bits.append(entry);
    entry = { "18: ch2_rds_active:1", "", 1, old_value_t.ch2_rds_active, new_value_t.ch2_rds_active };
    m_bit_details_model.bits.append(entry);
    entry = { "19: ch3_rds_active:1",
              "1=ahbdma channel 3 has read transaction(s) outstanding",
              1, old_value_t.ch3_rds_active, new_value_t.ch3_rds_active };
    m_bit_details_model.bits.append(entry);
    entry = { "20: undefined_bits_20_30:11", "", 11, old_value_t.undefined_bits_20_30, new_value_t.undefined_bits_20_30 };
    m_bit_details_model.bits.append(entry);
    entry = { "31: mst_gizmo_wrque_empty:1", "", 1, old_value_t.mst_gizmo_wrque_empty, new_value_t.mst_gizmo_wrque_empty };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "0x6000_8028: AHBDMA outstanding R/W per channel\nbit[31] is the coherency status on the AHB-side of the AHBDMA.\nWhen MST_GIZMO_WRQUE_EMPTY is active, there are no writeAHB transactions from any AHBDMA channel on their way out.\nbits[19:16] and [3:0] check the status of WriteXMB and ReadXMB transactions on the direct-to-memory CIF side of the AHBDMA.";
}

#define TEST_BUS_OFFSET 0x2C
#define TEST_BUS_UNDEFMASK 0xFFFFFF00
union test_bus_u {
    struct {
        unsigned int mstgizmo_wrque_ch0_ping_status:1;
        unsigned int mstgizmo_wrque_ch0_pong_status:1;
        unsigned int mstgizmo_wrque_ch1_ping_status:1;
        unsigned int mstgizmo_wrque_ch1_pong_status:1;
        unsigned int mstgizmo_wrque_ch2_ping_status:1;
        unsigned int mstgizmo_wrque_ch2_pong_status:1;
        unsigned int mstgizmo_wrque_ch3_ping_status:1;
        unsigned int mstgizmo_wrque_ch3_pong_status:1;
        unsigned int undefined_bits_8_31:24;
    };

    u_int32_t reg32;
};

void Ahb_dmaDev::fill_test_bus_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const test_bus_u old_value_t = { .reg32 = value };
    const test_bus_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: mstgizmo_wrque_ch0_ping_status:1", "", 1, old_value_t.mstgizmo_wrque_ch0_ping_status, new_value_t.mstgizmo_wrque_ch0_ping_status };
    m_bit_details_model.bits.append(entry);
    entry = { "01: mstgizmo_wrque_ch0_pong_status:1", "", 1, old_value_t.mstgizmo_wrque_ch0_pong_status, new_value_t.mstgizmo_wrque_ch0_pong_status };
    m_bit_details_model.bits.append(entry);
    entry = { "02: mstgizmo_wrque_ch1_ping_status:1", "", 1, old_value_t.mstgizmo_wrque_ch1_ping_status, new_value_t.mstgizmo_wrque_ch1_ping_status };
    m_bit_details_model.bits.append(entry);
    entry = { "03: mstgizmo_wrque_ch1_pong_status:1", "", 1, old_value_t.mstgizmo_wrque_ch1_pong_status, new_value_t.mstgizmo_wrque_ch1_pong_status };
    m_bit_details_model.bits.append(entry);
    entry = { "04: mstgizmo_wrque_ch2_ping_status:1", "", 1, old_value_t.mstgizmo_wrque_ch2_ping_status, new_value_t.mstgizmo_wrque_ch2_ping_status };
    m_bit_details_model.bits.append(entry);
    entry = { "05: mstgizmo_wrque_ch2_pong_status:1", "", 1, old_value_t.mstgizmo_wrque_ch2_pong_status, new_value_t.mstgizmo_wrque_ch2_pong_status };
    m_bit_details_model.bits.append(entry);
    entry = { "06: mstgizmo_wrque_ch3_ping_status:1", "", 1, old_value_t.mstgizmo_wrque_ch3_ping_status, new_value_t.mstgizmo_wrque_ch3_ping_status };
    m_bit_details_model.bits.append(entry);
    entry = { "07: mstgizmo_wrque_ch3_pong_status:1", "", 1, old_value_t.mstgizmo_wrque_ch3_pong_status, new_value_t.mstgizmo_wrque_ch3_pong_status };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_31:24", "", 24, old_value_t.undefined_bits_8_31, new_value_t.undefined_bits_8_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "0x6000_802C: AHBDMA_TEST_BUS. This is a legacy observability bus.";
}

#define PPCS_MCCIF_FIFOCTRL_OFFSET 0x40
#define PPCS_MCCIF_FIFOCTRL_UNDEFMASK 0xFFFFFFF0
union ppcs_mccif_fifoctrl_u {
    struct {
        unsigned int ppcs_mccif_wrcl_mcle2x:1; /* 0 = DISABLE; 1 = ENABLE */
        unsigned int ppcs_mccif_rdmc_rdfast:1; /* 0 = DISABLE; 1 = ENABLE */
        unsigned int ppcs_mccif_wrmc_clle2x:1; /* 0 = DISABLE; 1 = ENABLE */
        unsigned int ppcs_mccif_rdcl_rdfast:1; /* 0 = DISABLE; 1 = ENABLE */
        unsigned int undefined_bits_4_31:28;
    };

    u_int32_t reg32;
};

void Ahb_dmaDev::fill_ppcs_mccif_fifoctrl_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const ppcs_mccif_fifoctrl_u old_value_t = { .reg32 = value };
    const ppcs_mccif_fifoctrl_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: ppcs_mccif_wrcl_mcle2x:1",
              "0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ppcs_mccif_wrcl_mcle2x, new_value_t.ppcs_mccif_wrcl_mcle2x };
    m_bit_details_model.bits.append(entry);
    entry = { "01: ppcs_mccif_rdmc_rdfast:1",
              "0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ppcs_mccif_rdmc_rdfast, new_value_t.ppcs_mccif_rdmc_rdfast };
    m_bit_details_model.bits.append(entry);
    entry = { "02: ppcs_mccif_wrmc_clle2x:1",
              "0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ppcs_mccif_wrmc_clle2x, new_value_t.ppcs_mccif_wrmc_clle2x };
    m_bit_details_model.bits.append(entry);
    entry = { "03: ppcs_mccif_rdcl_rdfast:1",
              "0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ppcs_mccif_rdcl_rdfast, new_value_t.ppcs_mccif_rdcl_rdfast };
    m_bit_details_model.bits.append(entry);
    entry = { "04: undefined_bits_4_31:28", "", 28, old_value_t.undefined_bits_4_31, new_value_t.undefined_bits_4_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Memory Client Interface FIFO Control Register\nThe registers below allow optimizing the synchronization timing in the memory client asynchronous FIFOs. When they can be used depend on the client and memory controller clock ratio.\nAdditionally, the RDMC_RDFAST/RDCL_RDFAST fields can increase power consumption if the asynchronous FIFO is implemented as a real ram.\nThere is no power impact on latch-based FIFOs. Flip-flop-based FIFOs do not use these fields.\nRecommended Settings\nClient writing to FIFO, memory controller reading from FIFO\nmcclk_freq <= clientclk_freq\nYou can enable both RDMC_RDFAST and WRCL_CLLE2X. If one of the FIFOs is a real ram and power is a concern, you should avoid enabling RDMC_RDFAST.\nclientclk_freq < mcclk_freq <= 2 * clientclk_freq\nYou can enable RDMC_RDFAST or WRCL_MCLE2X, but because the client clock is slower, you should enable only WRCL_MCLE2X.\n2 * clientclk_freq < mcclk_freq\nYou can only enable RDMC_RDFAST. If one of the FIFOs is a real ram and power is a concern, you should avoid enabling RDMC_RDFAST.\nMemory controller writing to fifo, client reading from fifo\nclientclk_freq <= mcclk_freq\nYou can enable both RDCL_RDFAST and WRMC_CLLE2X. If one of the FIFOs is a real ram and power is a concern, you should avoid enabling RDCL_RDFAST.\nmcclk_freq < clientclk_freq <= 2 * mcclk_freq\nYou can enable RDCL_RDFAST or WRMC_CLLE2X, but because the memory controller clock is slower, you should enable only WRMC_CLLE2X.\n2 * mcclk_freq < clientclk_freq\nYou can only enable RDCL_RDFAST. If one of the FIFOs is a real ram and power is a concern, you should avoid enabling RDCL_RDFAST.";
}

#define TIMEOUT_WCOAL_PPCS_OFFSET 0x44
#define TIMEOUT_WCOAL_PPCS_UNDEFMASK 0xFFFF0000
union timeout_wcoal_ppcs_u {
    struct {
        unsigned int ppcsahbslvw_wcoal_tmval:8;
        unsigned int ppcsahbdmaw_wcoal_tmval:8;
        unsigned int undefined_bits_16_31:16;
    };

    u_int32_t reg32;
};

void Ahb_dmaDev::fill_timeout_wcoal_ppcs_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const timeout_wcoal_ppcs_u old_value_t = { .reg32 = value };
    const timeout_wcoal_ppcs_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: ppcsahbslvw_wcoal_tmval:8", "", 8, old_value_t.ppcsahbslvw_wcoal_tmval, new_value_t.ppcsahbslvw_wcoal_tmval };
    m_bit_details_model.bits.append(entry);
    entry = { "08: ppcsahbdmaw_wcoal_tmval:8", "", 8, old_value_t.ppcsahbdmaw_wcoal_tmval, new_value_t.ppcsahbdmaw_wcoal_tmval };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_31:16", "", 16, old_value_t.undefined_bits_16_31, new_value_t.undefined_bits_16_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Write Coalescing Time-Out Register\nThis register exists only for write clients. Reset value defaults to 50 for most clients, but may be different for certain clients.\nWrite coalescing happens inside the memory client.\nCoalescing means two (NV_MC_MW/2)-bit requests are grouped together in one NV_MC_MW-bit request.\nThe register value indicates how many cycles a first write request is going to wait for a subsequent one for possible coalescing. The coalescing can only happen if the request addresses are compatible. A value of zero means that coalescing is off and requests are sent right away to the memory controller.\nWrite coalescing can have a very significant impact performance when accessing the internal memory, because its memory word is NV_MC_WM-bit wide. Grouping two half-word accesses is much more efficient, because the two accesses would actually have taken three cycles, due to a stall when accessing the same memory bank. It also reduces the number of accessing (one instead of two), freeing up internal memory bandwidth for other accesses.\nThe impact on external memory accesses is not as significant as the burst access is for NV_MC_MW/2 bits. But a coalesced write guarantees two consecutive same page accesses which is good for external memory bandwidth utilization.\nThe write coalescing time-out should be programmed depending on the client behavior. The first write is obviously delayed by an amount of client cycles equal to the time-out value.\nNote that writes tagged by the client (i.e. the client expects a write response, usually for coherency), and the last write of a block transfer are not delayed. They only have a one-cycle opportunity to get coalesced.";
}

#define AHBDMACHAN_CHANNEL_0_CSR_OFFSET 0x0 + 0x1000
#define AHBDMACHAN_CHANNEL_0_CSR_UNDEFMASK 0x00000003
union ahbdmachan_channel_0_csr_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int wcount:14;             /* Number of 32 bit word cycles. This is encoded as N+1, so that if a value of 0 is programmed here, 1 32-bit word will be transferred */
        unsigned int req_sel:4;             /* 0 = CNTR_REQ; 1 = SMP_17; 2 = SMP_18; 3 = SMP_19; 4 = SMP_20; 5 = SMP_21; 6 = SMP_22; 7 = SMP_23; 8 = SMP_24; 9 = SMP_25; 10 = SMP_26; 11 = Host1x; 12 = SRQ0_N_A; 13 = SRQ1_N_A; 14 = SRQ0_XRQ_A; 15 = SRQ1_XRQ_B */
        unsigned int trig_sel:4;            /* 0 = SMP_30_same_as_bit_14; 1 = SMP_31_same_as_bit_15; 2 = HRQ2_XRQ_C; 3 = HRQ3_XRQ_D; 4 = HRQ4_N_A; 5 = HRQ5_N_A; 6 = HRQ6_TMR1; 7 = HRQ7_TMR2; 8 = AHB_0; 9 = AHB_1; 10 = AHB_2; 11 = AHB_3; 12 = SMP_28; 13 = SMP_29; 14 = SMP_30; 15 = SMP_31 */
        unsigned int flow:1;                /* 0 = Independent of DRQ request (no flow set); 0 = DISABLE; 1 = ENABLE */
        unsigned int trig:1;                /* 0 = Independent of Trigger (no trigger set); 0 = DISABLE; 1 = ENABLE */
        unsigned int once:1;                /* 0 = Run for Multiple Block Transfer; 0 = DISABLE; 1 = ENABLE */
        unsigned int dir:1;                 /* 0 = XMB read to AHB write; 0 = DISABLE; 1 = ENABLE */
        unsigned int hold:1;                /* 0 = Disable; 0 = DISABLE; 1 = ENABLE */
        unsigned int fl_btwn:1;             /* 0 = do not flush; 0 = DISABLE; 1 = ENABLE */
        unsigned int ie_eoc:1;              /* 0 = NOP or waiting; 0 = DISABLE; 1 = ENABLE */
        unsigned int enb:1;                 /* 0 = Disable the DMA Channel; 0 = DISABLE; 1 = ENABLE */
    };

    u_int32_t reg32;
};

void Ahb_dmaDev::fill_ahbdmachan_channel_0_csr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const ahbdmachan_channel_0_csr_u old_value_t = { .reg32 = value };
    const ahbdmachan_channel_0_csr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: wcount:14",
              "Number of 32 bit word cycles. This is encoded as N+1, so that if a value of 0 is programmed here, 1 32-bit word will be transferred",
              14, old_value_t.wcount, new_value_t.wcount };
    m_bit_details_model.bits.append(entry);
    entry = { "16: req_sel:4",
              "0 = CNTR_REQ;\n1 = SMP_17;\n2 = SMP_18;\n3 = SMP_19;\n4 = SMP_20;\n5 = SMP_21;\n6 = SMP_22;\n7 = SMP_23;\n8 = SMP_24;\n9 = SMP_25;\n10 = SMP_26;\n11 = Host1x;\n12 = SRQ0_N_A;\n13 = SRQ1_N_A;\n14 = SRQ0_XRQ_A;\n15 = SRQ1_XRQ_B",
              4, old_value_t.req_sel, new_value_t.req_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "20: trig_sel:4",
              "0 = SMP_30_same_as_bit_14;\n1 = SMP_31_same_as_bit_15;\n2 = HRQ2_XRQ_C;\n3 = HRQ3_XRQ_D;\n4 = HRQ4_N_A;\n5 = HRQ5_N_A;\n6 = HRQ6_TMR1;\n7 = HRQ7_TMR2;\n8 = AHB_0;\n9 = AHB_1;\n10 = AHB_2;\n11 = AHB_3;\n12 = SMP_28;\n13 = SMP_29;\n14 = SMP_30;\n15 = SMP_31",
              4, old_value_t.trig_sel, new_value_t.trig_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "24: flow:1",
              "0 = Independent of DRQ request (no flow set);\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.flow, new_value_t.flow };
    m_bit_details_model.bits.append(entry);
    entry = { "25: trig:1",
              "0 = Independent of Trigger (no trigger set);\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.trig, new_value_t.trig };
    m_bit_details_model.bits.append(entry);
    entry = { "26: once:1",
              "0 = Run for Multiple Block Transfer;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.once, new_value_t.once };
    m_bit_details_model.bits.append(entry);
    entry = { "27: dir:1",
              "0 = XMB read to AHB write;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.dir, new_value_t.dir };
    m_bit_details_model.bits.append(entry);
    entry = { "28: hold:1",
              "0 = Disable;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.hold, new_value_t.hold };
    m_bit_details_model.bits.append(entry);
    entry = { "29: fl_btwn:1",
              "0 = do not flush;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.fl_btwn, new_value_t.fl_btwn };
    m_bit_details_model.bits.append(entry);
    entry = { "30: ie_eoc:1",
              "0 = NOP or waiting;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ie_eoc, new_value_t.ie_eoc };
    m_bit_details_model.bits.append(entry);
    entry = { "31: enb:1",
              "0 = Disable the DMA Channel;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.enb, new_value_t.enb };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = " AHB-DMA-CHANNEL-0 Control Register\nWriting a 1 to bit [31] of an AHB DMA Channel Control Register will initiate the AHB DMA Transfer. Because this action will depend on some values programmed in the other registers, it is recommended that the registers in the address space in the required AHB DMA channel be programmed before writing into control register.\nIn \"Once\" mode, the channel is disabled after the AHB DMA Transfer has completed. When the channel's Transfer completes, an interrupt will be sent if the IE.EOC bit is set\nIf the transfer requires a trigger or flow, then the corresponding trigger selected by the \"TRIG_SEL\" or \"REQ_SEL\" field must become active respectively before the channel can starts its transfer. If both Trigger and Flow bits are set, both conditions must be met before the channel starts each DMA Burst.";
}

#define AHBDMACHAN_CHANNEL_0_STA_OFFSET 0x4 + 0x1000
#define AHBDMACHAN_CHANNEL_0_STA_UNDEFMASK 0x2FFF0003
union ahbdmachan_channel_0_sta_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int count:14;              /* Remaining transfer count in 32bit word cycles Flags set / cleared by HW */
        unsigned int undefined_bits_16_27:12;
        unsigned int halt:1;                /* 0 = NOP (holding status) Read-only 0 = DISABLE 1 = ENABLE */
        unsigned int undefined_bit_29:1;
        unsigned int is_eoc:1;              /* Write '1' to clear the flag 0 = NO_INTR 1 = INTR */
        unsigned int bsy:1;                 /* 0 = NOP Read-only 0 = DISABLE 1 = ENABLE */
    };

    u_int32_t reg32;
};

void Ahb_dmaDev::fill_ahbdmachan_channel_0_sta_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const ahbdmachan_channel_0_sta_u old_value_t = { .reg32 = value };
    const ahbdmachan_channel_0_sta_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: count:14",
              "Remaining transfer count in 32bit word cycles Flags set / cleared by HW",
              14, old_value_t.count, new_value_t.count };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_27:12", "", 12, old_value_t.undefined_bits_16_27, new_value_t.undefined_bits_16_27 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: halt:1",
              "0 = NOP (holding status) Read-only\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.halt, new_value_t.halt };
    m_bit_details_model.bits.append(entry);
    entry = { "29: undefined_bit_29:1", "", 1, old_value_t.undefined_bit_29, new_value_t.undefined_bit_29 };
    m_bit_details_model.bits.append(entry);
    entry = { "30: is_eoc:1",
              "Write '1' to clear the flag\n0 = NO_INTR\n1 = INTR",
              1, old_value_t.is_eoc, new_value_t.is_eoc };
    m_bit_details_model.bits.append(entry);
    entry = { "31: bsy:1",
              "0 = NOP Read-only\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.bsy, new_value_t.bsy };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "AHB-DMA-CHANNEL-0 Status Register";
}

#define AHBDMACHAN_CHANNEL_0_AHB_PTR_OFFSET 0x10 + 0x1000
#define AHBDMACHAN_CHANNEL_0_AHB_PTR_UNDEFMASK 0x00000003
union ahbdmachan_channel_0_ahb_ptr_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int ahb_base:30;           /* AHB-DMA starting address for internal AHB Bus */
    };

    u_int32_t reg32;
};

void Ahb_dmaDev::fill_ahbdmachan_channel_0_ahb_ptr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const ahbdmachan_channel_0_ahb_ptr_u old_value_t = { .reg32 = value };
    const ahbdmachan_channel_0_ahb_ptr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: ahb_base:30",
              "AHB-DMA starting address for internal AHB Bus",
              30, old_value_t.ahb_base, new_value_t.ahb_base };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "AHB-DMA-CHANNEL-0 AHB Starting Address Pointer Register\nIf stride is enabled, the AHB address should be aligned to burst size.";
}

#define AHBDMACHAN_CHANNEL_0_AHB_SEQ_OFFSET 0x14 + 0x1000
#define AHBDMACHAN_CHANNEL_0_AHB_SEQ_UNDEFMASK 0x70100003
union ahbdmachan_channel_0_ahb_seq_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int ahb_stride:16;         /* This field tells us number of words that are supposed to be skipped on AHB side */
        unsigned int ahb_addr_wrap:1;       /* 0 = disable  0 = DISABLE 1 = ENABLE */
        unsigned int dbl_buf:1;             /* 0 = Reload Base Address for 1X blocks (default), reload each time 0 = DISABLE 1 = ENABLE */
        unsigned int undefined_bit_20:1;
        unsigned int ahb_stride_size:3;     /* 0 = disabled, otherwise stride is enabled 0 = DISABLE 1 = WORDS_4 2 = WORDS_8 3 = WORDS_16 4 = WORDS_32 5 = WORDS_64 6 = WORDS_128 7 = WORDS_256 */
        unsigned int ahb_burst:3;           /* 0,1,5-7 = rsvd 2 = WORD 3 = FOUR_WORD 4 = EIGHT_WORD */
        unsigned int ahb_data_swap:1;       /* 0 = no data conversion, when 1 and writeAhb: [31:0]->{[7:0],[15:8],[23:16],[31:24]}  0 = DISABLE 1 = ENABLE */
        unsigned int undefined_bits_28_30:3;
        unsigned int intr_enb:1;            /* 0 = send interrupt to COP 1 = CPU 0 = COP */
    };

    u_int32_t reg32;
};

void Ahb_dmaDev::fill_ahbdmachan_channel_0_ahb_seq_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const ahbdmachan_channel_0_ahb_seq_u old_value_t = { .reg32 = value };
    const ahbdmachan_channel_0_ahb_seq_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: ahb_stride:16",
              "This field tells us number of words that are supposed to be skipped on AHB side",
              16, old_value_t.ahb_stride, new_value_t.ahb_stride };
    m_bit_details_model.bits.append(entry);
    entry = { "18: ahb_addr_wrap:1",
              "0 = disable \n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.ahb_addr_wrap, new_value_t.ahb_addr_wrap };
    m_bit_details_model.bits.append(entry);
    entry = { "19: dbl_buf:1",
              "0 = Reload Base Address for 1X blocks (default), reload each time\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.dbl_buf, new_value_t.dbl_buf };
    m_bit_details_model.bits.append(entry);
    entry = { "20: undefined_bit_20:1", "", 1, old_value_t.undefined_bit_20, new_value_t.undefined_bit_20 };
    m_bit_details_model.bits.append(entry);
    entry = { "21: ahb_stride_size:3",
              "0 = disabled, otherwise stride is enabled\n0 = DISABLE\n1 = WORDS_4\n2 = WORDS_8\n3 = WORDS_16\n4 = WORDS_32\n5 = WORDS_64\n6 = WORDS_128\n7 = WORDS_256",
              3, old_value_t.ahb_stride_size, new_value_t.ahb_stride_size };
    m_bit_details_model.bits.append(entry);
    entry = { "24: ahb_burst:3",
              "0,1,5-7 = rsvd\n2 = WORD\n3 = FOUR_WORD\n4 = EIGHT_WORD",
              3, old_value_t.ahb_burst, new_value_t.ahb_burst };
    m_bit_details_model.bits.append(entry);
    entry = { "27: ahb_data_swap:1",
              "0 = no data conversion, when 1 and writeAhb: [31:0]->{[7:0],[15:8],[23:16],[31:24]} \n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.ahb_data_swap, new_value_t.ahb_data_swap };
    m_bit_details_model.bits.append(entry);
    entry = { "28: undefined_bits_28_30:3", "", 3, old_value_t.undefined_bits_28_30, new_value_t.undefined_bits_28_30 };
    m_bit_details_model.bits.append(entry);
    entry = { "31: intr_enb:1",
              "0 = send interrupt to COP\n1 = CPU\n0 = COP",
              1, old_value_t.intr_enb, new_value_t.intr_enb };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "AHB-DMA-CHANNEL-0 AHB Address Sequencer Register\nAn AHB DMA stride is a sub-section of an AHB DMA transfer, can be used in once mode, and is composed of one or more AHB DMA bursts.\nWhen stride is enabled, wrap should not be enabled. The size of a stride is programmable, but is always an integer multiple of 4 words.\nThe size of the AHB DMA stride must always be an integer multiple of the AHB DMA burst size.\nThe size of the AHB DMA transfer count (total words in the transfer) must also be a multiple of both the burst size and the stride size.\nIf stride is enabled, the AHB_STRIDE should be aligned to burst size.";
}

#define AHBDMACHAN_CHANNEL_0_XMB_PTR_OFFSET 0x18 + 0x1000
#define AHBDMACHAN_CHANNEL_0_XMB_PTR_UNDEFMASK 0x00000003
union ahbdmachan_channel_0_xmb_ptr_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int xmb_base:30;           /* AHB-DMA Starting address for internal AHB Bus */
    };

    u_int32_t reg32;
};

void Ahb_dmaDev::fill_ahbdmachan_channel_0_xmb_ptr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const ahbdmachan_channel_0_xmb_ptr_u old_value_t = { .reg32 = value };
    const ahbdmachan_channel_0_xmb_ptr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: xmb_base:30",
              "AHB-DMA Starting address for internal AHB Bus",
              30, old_value_t.xmb_base, new_value_t.xmb_base };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "AHB-DMA-CHANNEL-0 XMB Starting Address Pointer Register\nThe starting XMB address for the AHB DMA transfer must be aligned to an address boundary that is a multiple of the burst size.";
}

#define AHBDMACHAN_CHANNEL_0_XMB_SEQ_OFFSET 0x1C + 0x1000
#define AHBDMACHAN_CHANNEL_0_XMB_SEQ_UNDEFMASK 0xF7F00003
union ahbdmachan_channel_0_xmb_seq_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int xmb_stride:16;         /* This field tells us number of words that are supposed to be skipped on XMB side */
        unsigned int xmb_addr_wrap:1;       /* 0 disable 0 = DISABLE 1 = ENABLE */
        unsigned int dbl_buf:1;             /* 0 = Reload Base Address for 1X blocks (default) (reload each time) 0 = DISABLE 1 = ENABLE */
        unsigned int undefined_bits_20_26:7;
        unsigned int xmb_data_swap:1;       /* 0 = no data conversion, when 1 and writeXmb: [31:0]->{[7:0],[15:8],[23:16],[31:24]} 0 = DISABLE 1 = ENABLE */
        unsigned int undefined_bits_28_31:4;
    };

    u_int32_t reg32;
};

void Ahb_dmaDev::fill_ahbdmachan_channel_0_xmb_seq_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const ahbdmachan_channel_0_xmb_seq_u old_value_t = { .reg32 = value };
    const ahbdmachan_channel_0_xmb_seq_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: xmb_stride:16",
              "This field tells us number of words that are supposed to be skipped on XMB side",
              16, old_value_t.xmb_stride, new_value_t.xmb_stride };
    m_bit_details_model.bits.append(entry);
    entry = { "18: xmb_addr_wrap:1",
              "0 disable\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.xmb_addr_wrap, new_value_t.xmb_addr_wrap };
    m_bit_details_model.bits.append(entry);
    entry = { "19: dbl_buf:1",
              "0 = Reload Base Address for 1X blocks (default) (reload each time)\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.dbl_buf, new_value_t.dbl_buf };
    m_bit_details_model.bits.append(entry);
    entry = { "20: undefined_bits_20_26:7", "", 7, old_value_t.undefined_bits_20_26, new_value_t.undefined_bits_20_26 };
    m_bit_details_model.bits.append(entry);
    entry = { "27: xmb_data_swap:1",
              "0 = no data conversion, when 1 and writeXmb: [31:0]->{[7:0],[15:8],[23:16],[31:24]}\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.xmb_data_swap, new_value_t.xmb_data_swap };
    m_bit_details_model.bits.append(entry);
    entry = { "28: undefined_bits_28_31:4", "", 4, old_value_t.undefined_bits_28_31, new_value_t.undefined_bits_28_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "AHB-DMA-CHANNEL-0 XMB Address Sequencer Register\nIf the stride is enabled, then the XMB_STRIDE must also be a multiple of the burst size.";
}

#define AHBDMACHAN_CHANNEL_1_CSR_OFFSET 0x20 + 0x1000
#define AHBDMACHAN_CHANNEL_1_CSR_UNDEFMASK 0x00000003
union ahbdmachan_channel_1_csr_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int wcount:14;             /* Number of 32 bit word cycles. This is encoded as N+1, so that if a value of 0 is programmed here, 1 32-bit word will be transferred */
        unsigned int req_sel:4;             /* 0 = CNTR_REQ 1 = SMP_17 2 = SMP_18 3 = SMP_19 4 = SMP_20 5 = SMP_21 6 = SMP_22 7 = SMP_23 8 = SMP_24 9 = SMP_25 10 = SMP_26 11 = Host1x 12 = SRQ0_N_A 13 = SRQ1_N_A 14 = SRQ0_XRQ_A 15 = SRQ1_XRQ_B */
        unsigned int trig_sel:4;            /* 0 = SMP_30_same_as_bit_14 1 = SMP_31_same_as_bit_15 2 = HRQ2_XRQ_C 3 = HRQ3_XRQ_D 4 = HRQ4_N_A 5 = HRQ5_N_A 6 = HRQ6_TMR1 7 = HRQ7_TMR2 8 = AHB_0 9 = AHB_1 10 = AHB_2 11 = AHB_3 12 = SMP_28 13 = SMP_29 14 = SMP_30 15 = SMP_31 */
        unsigned int flow:1;                /* 0 = Independent of DRQ request 0 = DISABLE 1 = ENABLE */
        unsigned int trig:1;                /* 0 = Independent of Trigger 0 = DISABLE 1 = ENABLE */
        unsigned int once:1;                /* 0 = Run for Multiple Block Transfer 0 = DISABLE 1 = ENABLE */
        unsigned int dir:1;                 /* 0 = XMB read to AHB write 0 = DISABLE 1 = ENABLE */
        unsigned int hold:1;                /* 0 = Disable 0 = DISABLE 1 = ENABLE */
        unsigned int fl_btwn:1;             /* 0 = do not flush 0 = DISABLE 1 = ENABLE */
        unsigned int ie_eoc:1;              /* 0 = NOP 0 = DISABLE 1 = ENABLE */
        unsigned int enb:1;                 /* 0 = Disable the DMA Channel 0 = DISABLE 1 = ENABLE */
    };

    u_int32_t reg32;
};

void Ahb_dmaDev::fill_ahbdmachan_channel_1_csr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const ahbdmachan_channel_1_csr_u old_value_t = { .reg32 = value };
    const ahbdmachan_channel_1_csr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: wcount:14",
              "Number of 32 bit word cycles. This is encoded as N+1, so that if a value of 0 is programmed here, 1 32-bit word will be transferred",
              14, old_value_t.wcount, new_value_t.wcount };
    m_bit_details_model.bits.append(entry);
    entry = { "16: req_sel:4",
              "0 = CNTR_REQ\n1 = SMP_17\n2 = SMP_18\n3 = SMP_19\n4 = SMP_20\n5 = SMP_21\n6 = SMP_22\n7 = SMP_23\n8 = SMP_24\n9 = SMP_25\n10 = SMP_26\n11 = Host1x\n12 = SRQ0_N_A\n13 = SRQ1_N_A\n14 = SRQ0_XRQ_A\n15 = SRQ1_XRQ_B",
              4, old_value_t.req_sel, new_value_t.req_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "20: trig_sel:4",
              "0 = SMP_30_same_as_bit_14\n1 = SMP_31_same_as_bit_15\n2 = HRQ2_XRQ_C\n3 = HRQ3_XRQ_D\n4 = HRQ4_N_A\n5 = HRQ5_N_A\n6 = HRQ6_TMR1\n7 = HRQ7_TMR2\n8 = AHB_0\n9 = AHB_1\n10 = AHB_2\n11 = AHB_3\n12 = SMP_28\n13 = SMP_29\n14 = SMP_30\n15 = SMP_31",
              4, old_value_t.trig_sel, new_value_t.trig_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "24: flow:1",
              "0 = Independent of DRQ request\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.flow, new_value_t.flow };
    m_bit_details_model.bits.append(entry);
    entry = { "25: trig:1",
              "0 = Independent of Trigger\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.trig, new_value_t.trig };
    m_bit_details_model.bits.append(entry);
    entry = { "26: once:1",
              "0 = Run for Multiple Block Transfer\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.once, new_value_t.once };
    m_bit_details_model.bits.append(entry);
    entry = { "27: dir:1",
              "0 = XMB read to AHB write\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.dir, new_value_t.dir };
    m_bit_details_model.bits.append(entry);
    entry = { "28: hold:1",
              "0 = Disable\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.hold, new_value_t.hold };
    m_bit_details_model.bits.append(entry);
    entry = { "29: fl_btwn:1",
              "0 = do not flush\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.fl_btwn, new_value_t.fl_btwn };
    m_bit_details_model.bits.append(entry);
    entry = { "30: ie_eoc:1",
              "0 = NOP\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.ie_eoc, new_value_t.ie_eoc };
    m_bit_details_model.bits.append(entry);
    entry = { "31: enb:1",
              "0 = Disable the DMA Channel\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.enb, new_value_t.enb };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "AHB-DMA-CHANNEL-1 Control Register";
}

#define AHBDMACHAN_CHANNEL_1_STA_OFFSET 0x24 + 0x1000
#define AHBDMACHAN_CHANNEL_1_STA_UNDEFMASK 0x2FFF0003
union ahbdmachan_channel_1_sta_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int count:14;              /* Remaining transfer count in 32bit word cycles Flags set / cleared by HW */
        unsigned int undefined_bits_16_27:12;
        unsigned int halt:1;                /* 0 = NOP  0 = DISABLE 1 = ENABLE */
        unsigned int undefined_bit_29:1;
        unsigned int is_eoc:1;              /* Write '1' to clear the flag  0 = NO_INTR 1 = INTR */
        unsigned int bsy:1;                 /* 0 = NOP Read-only 0 = DISABLE 1 = ENABLE */
    };

    u_int32_t reg32;
};

void Ahb_dmaDev::fill_ahbdmachan_channel_1_sta_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const ahbdmachan_channel_1_sta_u old_value_t = { .reg32 = value };
    const ahbdmachan_channel_1_sta_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: count:14",
              "Remaining transfer count in 32bit word cycles Flags set / cleared by HW",
              14, old_value_t.count, new_value_t.count };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_27:12", "", 12, old_value_t.undefined_bits_16_27, new_value_t.undefined_bits_16_27 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: halt:1",
              "0 = NOP \n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.halt, new_value_t.halt };
    m_bit_details_model.bits.append(entry);
    entry = { "29: undefined_bit_29:1", "", 1, old_value_t.undefined_bit_29, new_value_t.undefined_bit_29 };
    m_bit_details_model.bits.append(entry);
    entry = { "30: is_eoc:1",
              "Write '1' to clear the flag \n0 = NO_INTR\n1 = INTR",
              1, old_value_t.is_eoc, new_value_t.is_eoc };
    m_bit_details_model.bits.append(entry);
    entry = { "31: bsy:1",
              "0 = NOP Read-only\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.bsy, new_value_t.bsy };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "AHB-DMA-CHANNEL-1 Status Register";
}

#define AHBDMACHAN_CHANNEL_1_AHB_PTR_OFFSET 0x30 + 0x1000
#define AHBDMACHAN_CHANNEL_1_AHB_PTR_UNDEFMASK 0x00000003
union ahbdmachan_channel_1_ahb_ptr_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int ahb_base:30;           /* AHB-DMA starting address pointer for internal AHB Bus */
    };

    u_int32_t reg32;
};

void Ahb_dmaDev::fill_ahbdmachan_channel_1_ahb_ptr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const ahbdmachan_channel_1_ahb_ptr_u old_value_t = { .reg32 = value };
    const ahbdmachan_channel_1_ahb_ptr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: ahb_base:30",
              "AHB-DMA starting address pointer for internal AHB Bus",
              30, old_value_t.ahb_base, new_value_t.ahb_base };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "AHB-DMA-CHANNEL-1 AHB Starting Address Pointer Register";
}

#define AHBDMACHAN_CHANNEL_1_AHB_SEQ_OFFSET 0x34 + 0x1000
#define AHBDMACHAN_CHANNEL_1_AHB_SEQ_UNDEFMASK 0x70100003
union ahbdmachan_channel_1_ahb_seq_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int ahb_stride:16;         /* This field tells us number of words that are supposed to be skipped on AHB side */
        unsigned int ahb_addr_wrap:1;       /* 0 = disable  0 = DISABLE 1 = ENABLE */
        unsigned int dbl_buf:1;             /* 0 = Reload Base Address for 1X blocks (default), reload each time 0 = DISABLE 1 = ENABLE */
        unsigned int undefined_bit_20:1;
        unsigned int ahb_stride_size:3;     /* 0 = disabled, otherwise stride is enabled 0 = DISABLE 1 = WORDS_4 2 = WORDS_8 3 = WORDS_16 4 = WORDS_32 5 = WORDS_64 6 = WORDS_128 7 = WORDS_256 */
        unsigned int ahb_burst:3;           /* 0,1,5-7 = rsvd 2 = WORD 3 = FOUR_WORD 4 = EIGHT_WORD */
        unsigned int ahb_data_swap:1;       /* 0 = no data conversion, when 1 and writeAhb: [31:0]->{[7:0],[15:8],[23:16],[31:24]} enum (DISABLE=0x0,ENABLE=0x1) */
        unsigned int undefined_bits_28_30:3;
        unsigned int intr_enb:1;            /* 0 = send interrupt to COP 1 = CPU 0 = COP */
    };

    u_int32_t reg32;
};

void Ahb_dmaDev::fill_ahbdmachan_channel_1_ahb_seq_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const ahbdmachan_channel_1_ahb_seq_u old_value_t = { .reg32 = value };
    const ahbdmachan_channel_1_ahb_seq_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: ahb_stride:16",
              "This field tells us number of words that are supposed to be skipped on AHB side",
              16, old_value_t.ahb_stride, new_value_t.ahb_stride };
    m_bit_details_model.bits.append(entry);
    entry = { "18: ahb_addr_wrap:1",
              "0 = disable \n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.ahb_addr_wrap, new_value_t.ahb_addr_wrap };
    m_bit_details_model.bits.append(entry);
    entry = { "19: dbl_buf:1",
              "0 = Reload Base Address for 1X blocks (default), reload each time\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.dbl_buf, new_value_t.dbl_buf };
    m_bit_details_model.bits.append(entry);
    entry = { "20: undefined_bit_20:1", "", 1, old_value_t.undefined_bit_20, new_value_t.undefined_bit_20 };
    m_bit_details_model.bits.append(entry);
    entry = { "21: ahb_stride_size:3",
              "0 = disabled, otherwise stride is enabled\n0 = DISABLE\n1 = WORDS_4\n2 = WORDS_8\n3 = WORDS_16\n4 = WORDS_32\n5 = WORDS_64\n6 = WORDS_128\n7 = WORDS_256",
              3, old_value_t.ahb_stride_size, new_value_t.ahb_stride_size };
    m_bit_details_model.bits.append(entry);
    entry = { "24: ahb_burst:3",
              "0,1,5-7 = rsvd\n2 = WORD\n3 = FOUR_WORD\n4 = EIGHT_WORD",
              3, old_value_t.ahb_burst, new_value_t.ahb_burst };
    m_bit_details_model.bits.append(entry);
    entry = { "27: ahb_data_swap:1",
              "0 = no data conversion, when 1 and writeAhb: [31:0]->{[7:0],[15:8],[23:16],[31:24]} enum (DISABLE=0x0,ENABLE=0x1)",
              1, old_value_t.ahb_data_swap, new_value_t.ahb_data_swap };
    m_bit_details_model.bits.append(entry);
    entry = { "28: undefined_bits_28_30:3", "", 3, old_value_t.undefined_bits_28_30, new_value_t.undefined_bits_28_30 };
    m_bit_details_model.bits.append(entry);
    entry = { "31: intr_enb:1",
              "0 = send interrupt to COP\n1 = CPU\n0 = COP",
              1, old_value_t.intr_enb, new_value_t.intr_enb };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "AHB-DMA-CHANNEL-1 AHB Address Sequencer Register";
}

#define AHBDMACHAN_CHANNEL_1_XMB_PTR_OFFSET 0x38 + 0x1000
#define AHBDMACHAN_CHANNEL_1_XMB_PTR_UNDEFMASK 0x00000003
union ahbdmachan_channel_1_xmb_ptr_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int xmb_base:30;           /* AHB-DMA Starting address pointer for internal AHB Bus */
    };

    u_int32_t reg32;
};

void Ahb_dmaDev::fill_ahbdmachan_channel_1_xmb_ptr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const ahbdmachan_channel_1_xmb_ptr_u old_value_t = { .reg32 = value };
    const ahbdmachan_channel_1_xmb_ptr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: xmb_base:30",
              "AHB-DMA Starting address pointer for internal AHB Bus",
              30, old_value_t.xmb_base, new_value_t.xmb_base };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "AHB-DMA-CHANNEL-1 XMB Starting Address Pointer Register";
}

#define AHBDMACHAN_CHANNEL_1_XMB_SEQ_OFFSET 0x3C + 0x1000
#define AHBDMACHAN_CHANNEL_1_XMB_SEQ_UNDEFMASK 0xF7F00003
union ahbdmachan_channel_1_xmb_seq_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int xmb_stride:16;         /* This field tells us number of words that are supposed to be skipped on XMB side */
        unsigned int xmb_addr_wrap:1;       /* 1 enable: 0 disable ; When enabled the Address on XMB gets wrapped to same address.  0 = DISABLE 1 = ENABLE */
        unsigned int dbl_buf:1;             /* 0 = Reload Base Address for 1X blocks (default), reload each time 0 = DISABLE 1 = ENABLE */
        unsigned int undefined_bits_20_26:7;
        unsigned int xmb_data_swap:1;       /* 0 = no data conversion, when 1 and writeXmb: [31:0]->{[7:0],[15:8],[23:16],[31:24]} 0 = DISABLE 1 = ENABLE */
        unsigned int undefined_bits_28_31:4;
    };

    u_int32_t reg32;
};

void Ahb_dmaDev::fill_ahbdmachan_channel_1_xmb_seq_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const ahbdmachan_channel_1_xmb_seq_u old_value_t = { .reg32 = value };
    const ahbdmachan_channel_1_xmb_seq_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: xmb_stride:16",
              "This field tells us number of words that are supposed to be skipped on XMB side",
              16, old_value_t.xmb_stride, new_value_t.xmb_stride };
    m_bit_details_model.bits.append(entry);
    entry = { "18: xmb_addr_wrap:1",
              "1 enable: 0 disable ; When enabled the Address on XMB gets wrapped to same address.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.xmb_addr_wrap, new_value_t.xmb_addr_wrap };
    m_bit_details_model.bits.append(entry);
    entry = { "19: dbl_buf:1",
              "0 = Reload Base Address for 1X blocks (default), reload each time\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.dbl_buf, new_value_t.dbl_buf };
    m_bit_details_model.bits.append(entry);
    entry = { "20: undefined_bits_20_26:7", "", 7, old_value_t.undefined_bits_20_26, new_value_t.undefined_bits_20_26 };
    m_bit_details_model.bits.append(entry);
    entry = { "27: xmb_data_swap:1",
              "0 = no data conversion, when 1 and writeXmb: [31:0]->{[7:0],[15:8],[23:16],[31:24]}\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.xmb_data_swap, new_value_t.xmb_data_swap };
    m_bit_details_model.bits.append(entry);
    entry = { "28: undefined_bits_28_31:4", "", 4, old_value_t.undefined_bits_28_31, new_value_t.undefined_bits_28_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "AHB-DMA-CHANNEL-1 XMB Address Sequencer Register";
}

#define AHBDMACHAN_CHANNEL_2_CSR_OFFSET 0x40 + 0x1000
#define AHBDMACHAN_CHANNEL_2_CSR_UNDEFMASK 0x00000003
union ahbdmachan_channel_2_csr_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int wcount:14;             /* Number of 32 bit word cycles. This is encoded as N+1, so that if a value of 0 is programmed here, 1 32-bit word will be transferred */
        unsigned int req_sel:4;             /* 0 = CNTR_REQ 1 = SMP_17 2 = SMP_18 3 = SMP_19 4 = SMP_20 5 = SMP_21 6 = SMP_22 7 = SMP_23 8 = SMP_24 9 = SMP_25 10 = SMP_26 11 = Host1x 12 = SRQ0_N_A 13 = SRQ1_N_A 14 = SRQ0_XRQ_A 15 = SRQ1_XRQ_B */
        unsigned int trig_sel:4;            /* 0 = SMP_30_same_as_bit_14 1 = SMP_31_same_as_bit_15 2 = HRQ2_XRQ_C 3 = HRQ3_XRQ_D 4 = HRQ4_N_A 5 = HRQ5_N_A 6 = HRQ6_TMR1 7 = HRQ7_TMR2 8 = AHB_0 9 = AHB_1 10 = AHB_2 11 = AHB_3 12 = SMP_28 13 = SMP_29 14 = SMP_30 15 = SMP_31 */
        unsigned int flow:1;                /* 0 = Independent of DRQ request (no flow set) 0 = DISABLE 1 = ENABLE */
        unsigned int trig:1;                /* 0 = Independent of Trigger (no trigger set) 0 = DISABLE 1 = ENABLE */
        unsigned int once:1;                /* 0 = Run for Multiple Block Transfer 0 = DISABLE 1 = ENABLE */
        unsigned int dir:1;                 /* 0 = XMB read to AHB write 0 = DISABLE 1 = ENABLE */
        unsigned int hold:1;                /* 0 = Disable 0 = DISABLE 1 = ENABLE */
        unsigned int fl_btwn:1;             /* 0 = do not flush 0 = DISABLE 1 = ENABLE */
        unsigned int ie_eoc:1;              /* 0 = NOP or waiting 0 = DISABLE 1 = ENABLE */
        unsigned int enb:1;                 /* 0 = Disable the DMA Channel 0 = DISABLE 1 = ENABLE */
    };

    u_int32_t reg32;
};

void Ahb_dmaDev::fill_ahbdmachan_channel_2_csr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const ahbdmachan_channel_2_csr_u old_value_t = { .reg32 = value };
    const ahbdmachan_channel_2_csr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: wcount:14",
              "Number of 32 bit word cycles. This is encoded as N+1, so that if a value of 0 is programmed here, 1 32-bit word will be transferred",
              14, old_value_t.wcount, new_value_t.wcount };
    m_bit_details_model.bits.append(entry);
    entry = { "16: req_sel:4",
              "0 = CNTR_REQ\n1 = SMP_17\n2 = SMP_18\n3 = SMP_19\n4 = SMP_20\n5 = SMP_21\n6 = SMP_22\n7 = SMP_23\n8 = SMP_24\n9 = SMP_25\n10 = SMP_26\n11 = Host1x\n12 = SRQ0_N_A\n13 = SRQ1_N_A\n14 = SRQ0_XRQ_A\n15 = SRQ1_XRQ_B",
              4, old_value_t.req_sel, new_value_t.req_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "20: trig_sel:4",
              "0 = SMP_30_same_as_bit_14\n1 = SMP_31_same_as_bit_15\n2 = HRQ2_XRQ_C\n3 = HRQ3_XRQ_D\n4 = HRQ4_N_A\n5 = HRQ5_N_A\n6 = HRQ6_TMR1\n7 = HRQ7_TMR2\n8 = AHB_0\n9 = AHB_1\n10 = AHB_2\n11 = AHB_3\n12 = SMP_28\n13 = SMP_29\n14 = SMP_30\n15 = SMP_31",
              4, old_value_t.trig_sel, new_value_t.trig_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "24: flow:1",
              "0 = Independent of DRQ request (no flow set)\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.flow, new_value_t.flow };
    m_bit_details_model.bits.append(entry);
    entry = { "25: trig:1",
              "0 = Independent of Trigger (no trigger set)\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.trig, new_value_t.trig };
    m_bit_details_model.bits.append(entry);
    entry = { "26: once:1",
              "0 = Run for Multiple Block Transfer\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.once, new_value_t.once };
    m_bit_details_model.bits.append(entry);
    entry = { "27: dir:1",
              "0 = XMB read to AHB write\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.dir, new_value_t.dir };
    m_bit_details_model.bits.append(entry);
    entry = { "28: hold:1",
              "0 = Disable\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.hold, new_value_t.hold };
    m_bit_details_model.bits.append(entry);
    entry = { "29: fl_btwn:1",
              "0 = do not flush\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.fl_btwn, new_value_t.fl_btwn };
    m_bit_details_model.bits.append(entry);
    entry = { "30: ie_eoc:1",
              "0 = NOP or waiting\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.ie_eoc, new_value_t.ie_eoc };
    m_bit_details_model.bits.append(entry);
    entry = { "31: enb:1",
              "0 = Disable the DMA Channel\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.enb, new_value_t.enb };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "AHB-DMA-CHANNEL-2 Control Register";
}

#define AHBDMACHAN_CHANNEL_2_STA_OFFSET 0x44 + 0x1000
#define AHBDMACHAN_CHANNEL_2_STA_UNDEFMASK 0x2FFF0003
union ahbdmachan_channel_2_sta_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int count:14;              /* Remaining transfer count in 32bit word cycles Flags set / cleared by HW */
        unsigned int undefined_bits_16_27:12;
        unsigned int halt:1;                /* 0 = NOP (holding status) Read-only 0 = DISABLE 1 = ENABLE */
        unsigned int undefined_bit_29:1;
        unsigned int is_eoc:1;              /* Write '1' to clear the flag  0 = NO_INTR 1 = INTR */
        unsigned int bsy:1;                 /* 0 = NOP Read-only 0 = DISABLE 1 = ENABLE */
    };

    u_int32_t reg32;
};

void Ahb_dmaDev::fill_ahbdmachan_channel_2_sta_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const ahbdmachan_channel_2_sta_u old_value_t = { .reg32 = value };
    const ahbdmachan_channel_2_sta_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: count:14",
              "Remaining transfer count in 32bit word cycles Flags set / cleared by HW",
              14, old_value_t.count, new_value_t.count };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_27:12", "", 12, old_value_t.undefined_bits_16_27, new_value_t.undefined_bits_16_27 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: halt:1",
              "0 = NOP (holding status) Read-only\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.halt, new_value_t.halt };
    m_bit_details_model.bits.append(entry);
    entry = { "29: undefined_bit_29:1", "", 1, old_value_t.undefined_bit_29, new_value_t.undefined_bit_29 };
    m_bit_details_model.bits.append(entry);
    entry = { "30: is_eoc:1",
              "Write '1' to clear the flag \n0 = NO_INTR\n1 = INTR",
              1, old_value_t.is_eoc, new_value_t.is_eoc };
    m_bit_details_model.bits.append(entry);
    entry = { "31: bsy:1",
              "0 = NOP Read-only\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.bsy, new_value_t.bsy };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "AHB-DMA-CHANNEL-2 Status Register";
}

#define AHBDMACHAN_CHANNEL_2_AHB_PTR_OFFSET 0x50 + 0x1000
#define AHBDMACHAN_CHANNEL_2_AHB_PTR_UNDEFMASK 0x00000003
union ahbdmachan_channel_2_ahb_ptr_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int ahb_base:30;           /* AHB-DMA starting address for internal AHB Bus */
    };

    u_int32_t reg32;
};

void Ahb_dmaDev::fill_ahbdmachan_channel_2_ahb_ptr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const ahbdmachan_channel_2_ahb_ptr_u old_value_t = { .reg32 = value };
    const ahbdmachan_channel_2_ahb_ptr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: ahb_base:30",
              "AHB-DMA starting address for internal AHB Bus",
              30, old_value_t.ahb_base, new_value_t.ahb_base };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "AHB-DMA-CHANNEL-2 AHB Starting Address Pointer Register";
}

#define AHBDMACHAN_CHANNEL_2_AHB_SEQ_OFFSET 0x54 + 0x1000
#define AHBDMACHAN_CHANNEL_2_AHB_SEQ_UNDEFMASK 0x70100003
union ahbdmachan_channel_2_ahb_seq_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int ahb_stride:16;         /* This field tells us number of words that are supposed to be skipped on AHB side */
        unsigned int ahb_addr_wrap:1;       /* 0 = disable  0 = DISABLE 1 = ENABLE */
        unsigned int dbl_buf:1;             /* 0 = Reload Base Address for 1X blocks (default), reload each time 0 = DISABLE 1 = ENABLE */
        unsigned int undefined_bit_20:1;
        unsigned int ahb_stride_size:3;     /* 0 = disabled, otherwise stride is enabled 0 = DISABLE 1 = WORDS_4 2 = WORDS_8 3 = WORDS_16 4 = WORDS_32 5 = WORDS_64 6 = WORDS_128 7 = WORDS_256 */
        unsigned int ahb_burst:3;           /* 0,1,5-7 = rsvd 2 = WORD 3 = FOUR_WORD 4 = EIGHT_WORD */
        unsigned int ahb_data_swap:1;       /* 0 = no data conversion, when 1 and writeAhb: [31:0]->{[7:0],[15:8],[23:16],[31:24]}  0 = DISABLE 1 = ENABLE */
        unsigned int undefined_bits_28_30:3;
        unsigned int intr_enb:1;            /* 0 = send interrupt to COP 1 = CPU 0 = COP */
    };

    u_int32_t reg32;
};

void Ahb_dmaDev::fill_ahbdmachan_channel_2_ahb_seq_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const ahbdmachan_channel_2_ahb_seq_u old_value_t = { .reg32 = value };
    const ahbdmachan_channel_2_ahb_seq_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: ahb_stride:16",
              "This field tells us number of words that are supposed to be skipped on AHB side",
              16, old_value_t.ahb_stride, new_value_t.ahb_stride };
    m_bit_details_model.bits.append(entry);
    entry = { "18: ahb_addr_wrap:1",
              "0 = disable \n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.ahb_addr_wrap, new_value_t.ahb_addr_wrap };
    m_bit_details_model.bits.append(entry);
    entry = { "19: dbl_buf:1",
              "0 = Reload Base Address for 1X blocks (default), reload each time\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.dbl_buf, new_value_t.dbl_buf };
    m_bit_details_model.bits.append(entry);
    entry = { "20: undefined_bit_20:1", "", 1, old_value_t.undefined_bit_20, new_value_t.undefined_bit_20 };
    m_bit_details_model.bits.append(entry);
    entry = { "21: ahb_stride_size:3",
              "0 = disabled, otherwise stride is enabled\n0 = DISABLE\n1 = WORDS_4\n2 = WORDS_8\n3 = WORDS_16\n4 = WORDS_32\n5 = WORDS_64\n6 = WORDS_128\n7 = WORDS_256",
              3, old_value_t.ahb_stride_size, new_value_t.ahb_stride_size };
    m_bit_details_model.bits.append(entry);
    entry = { "24: ahb_burst:3",
              "0,1,5-7 = rsvd\n2 = WORD\n3 = FOUR_WORD\n4 = EIGHT_WORD",
              3, old_value_t.ahb_burst, new_value_t.ahb_burst };
    m_bit_details_model.bits.append(entry);
    entry = { "27: ahb_data_swap:1",
              "0 = no data conversion, when 1 and writeAhb: [31:0]->{[7:0],[15:8],[23:16],[31:24]} \n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.ahb_data_swap, new_value_t.ahb_data_swap };
    m_bit_details_model.bits.append(entry);
    entry = { "28: undefined_bits_28_30:3", "", 3, old_value_t.undefined_bits_28_30, new_value_t.undefined_bits_28_30 };
    m_bit_details_model.bits.append(entry);
    entry = { "31: intr_enb:1",
              "0 = send interrupt to COP\n1 = CPU\n0 = COP",
              1, old_value_t.intr_enb, new_value_t.intr_enb };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "AHB-DMA-CHANNEL-2 AHB Address Sequencer Register";
}

#define AHBDMACHAN_CHANNEL_2_XMB_PTR_OFFSET 0x58 + 0x1000
#define AHBDMACHAN_CHANNEL_2_XMB_PTR_UNDEFMASK 0x00000003
union ahbdmachan_channel_2_xmb_ptr_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int xmb_base:30;           /* AHB-DMA Starting address for internal AHB Bus */
    };

    u_int32_t reg32;
};

void Ahb_dmaDev::fill_ahbdmachan_channel_2_xmb_ptr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const ahbdmachan_channel_2_xmb_ptr_u old_value_t = { .reg32 = value };
    const ahbdmachan_channel_2_xmb_ptr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: xmb_base:30",
              "AHB-DMA Starting address for internal AHB Bus",
              30, old_value_t.xmb_base, new_value_t.xmb_base };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "AHB-DMA-CHANNEL-2 XMB Starting Address Pointer Register";
}

#define AHBDMACHAN_CHANNEL_2_XMB_SEQ_OFFSET 0x5C + 0x1000
#define AHBDMACHAN_CHANNEL_2_XMB_SEQ_UNDEFMASK 0xF7F00003
union ahbdmachan_channel_2_xmb_seq_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int xmb_stride:16;         /* This field tells us number of words that are supposed to be skipped on XMB side */
        unsigned int xmb_addr_wrap:1;       /* 1 enable: 0 disable ; When enabled the Address on XMB gets wrapped to same address.  0 = DISABLE 1 = ENABLE */
        unsigned int dbl_buf:1;             /* 0 = Reload Base Address for 1X blocks (def) eload each time) 0 = DISABLE 1 = ENABLE */
        unsigned int undefined_bits_20_26:7;
        unsigned int xmb_data_swap:1;       /* 0 = no data conversion, when 1 and writeXmb: [31:0]->{[7:0],[15:8],[23:16],[31:24]} 0 = DISABLE 1 = ENABLE */
        unsigned int undefined_bits_28_31:4;
    };

    u_int32_t reg32;
};

void Ahb_dmaDev::fill_ahbdmachan_channel_2_xmb_seq_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const ahbdmachan_channel_2_xmb_seq_u old_value_t = { .reg32 = value };
    const ahbdmachan_channel_2_xmb_seq_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: xmb_stride:16",
              "This field tells us number of words that are supposed to be skipped on XMB side",
              16, old_value_t.xmb_stride, new_value_t.xmb_stride };
    m_bit_details_model.bits.append(entry);
    entry = { "18: xmb_addr_wrap:1",
              "1 enable: 0 disable ; When enabled the Address on XMB gets wrapped to same address.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.xmb_addr_wrap, new_value_t.xmb_addr_wrap };
    m_bit_details_model.bits.append(entry);
    entry = { "19: dbl_buf:1",
              "0 = Reload Base Address for 1X blocks (def) eload each time)\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.dbl_buf, new_value_t.dbl_buf };
    m_bit_details_model.bits.append(entry);
    entry = { "20: undefined_bits_20_26:7", "", 7, old_value_t.undefined_bits_20_26, new_value_t.undefined_bits_20_26 };
    m_bit_details_model.bits.append(entry);
    entry = { "27: xmb_data_swap:1",
              "0 = no data conversion, when 1 and writeXmb: [31:0]->{[7:0],[15:8],[23:16],[31:24]}\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.xmb_data_swap, new_value_t.xmb_data_swap };
    m_bit_details_model.bits.append(entry);
    entry = { "28: undefined_bits_28_31:4", "", 4, old_value_t.undefined_bits_28_31, new_value_t.undefined_bits_28_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "AHB-DMA-CHANNEL-2 XMB Address Sequencer Register";
}

#define AHBDMACHAN_CHANNEL_3_CSR_OFFSET 0x60 + 0x1000
#define AHBDMACHAN_CHANNEL_3_CSR_UNDEFMASK 0x00000003
union ahbdmachan_channel_3_csr_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int wcount:14;             /* Number of 32 bit word cycles. This is encoded as N+1, so that if a value of 0 is programmed here, 1 32-bit word will be transferred */
        unsigned int req_sel_req_sel:4;     /* 0 = CNTR_REQ 1 = SMP_17 2 = SMP_18 3 = SMP_19 4 = SMP_20 5 = SMP_21 6 = SMP_22 7 = SMP_23 8 = SMP_24 9 = SMP_25 10 = SMP_26 11 = Host1x 12 = SRQ0_N_A 13 = SRQ1_N_A 14 = SRQ0_XRQ_A 15 = SRQ1_XRQ_B; Lower 16 Requestors (15-0) */
        unsigned int trig_sel:4;            /* 0 = SMP_30_same_as_bit_14 1 = SMP_31_same_as_bit_15 2 = HRQ2_XRQ_C 3 = HRQ3_XRQ_D 4 = HRQ4_N_A 5 = HRQ5_N_A 6 = HRQ6_TMR1 7 = HRQ7_TMR2 8 = AHB_0 9 = AHB_1 10 = AHB_2 11 = AHB_3 12 = SMP_28 13 = SMP_29 14 = SMP_30 15 = SMP_31 */
        unsigned int flow:1;                /* 0 = Independent of DRQ request 0 = DISABLE 1 = ENABLE */
        unsigned int trig:1;                /* 0 = Independent of Trigger 0 = DISABLE 1 = ENABLE */
        unsigned int once:1;                /* 0 = Run for Multiple Block Transfer 0 = DISABLE 1 = ENABLE */
        unsigned int dir:1;                 /* 0 = XMB read to AHB write 0 = DISABLE 1 = ENABLE */
        unsigned int hold:1;                /* 0 = Disable 0 = DISABLE 1 = ENABLE */
        unsigned int fl_btwn:1;             /* 0 = do not flush 0 = DISABLE 1 = ENABLE */
        unsigned int ie_eoc:1;              /* 0 = NOP 0 = DISABLE 1 = ENABLE */
        unsigned int enb:1;                 /* 0 = Disable the DMA Channel 0 = DISABLE 1 = ENABLE */
    };

    u_int32_t reg32;
};

void Ahb_dmaDev::fill_ahbdmachan_channel_3_csr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const ahbdmachan_channel_3_csr_u old_value_t = { .reg32 = value };
    const ahbdmachan_channel_3_csr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: wcount:14",
              "Number of 32 bit word cycles. This is encoded as N+1, so that if a value of 0 is programmed here, 1 32-bit word will be transferred",
              14, old_value_t.wcount, new_value_t.wcount };
    m_bit_details_model.bits.append(entry);
    entry = { "16: req_sel_req_sel:4",
              "0 = CNTR_REQ\n1 = SMP_17\n2 = SMP_18\n3 = SMP_19\n4 = SMP_20\n5 = SMP_21\n6 = SMP_22\n7 = SMP_23\n8 = SMP_24\n9 = SMP_25\n10 = SMP_26\n11 = Host1x\n12 = SRQ0_N_A\n13 = SRQ1_N_A\n14 = SRQ0_XRQ_A\n15 = SRQ1_XRQ_B; Lower 16 Requestors (15-0)",
              4, old_value_t.req_sel_req_sel, new_value_t.req_sel_req_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "20: trig_sel:4",
              "0 = SMP_30_same_as_bit_14\n1 = SMP_31_same_as_bit_15\n2 = HRQ2_XRQ_C\n3 = HRQ3_XRQ_D\n4 = HRQ4_N_A\n5 = HRQ5_N_A\n6 = HRQ6_TMR1\n7 = HRQ7_TMR2\n8 = AHB_0\n9 = AHB_1\n10 = AHB_2\n11 = AHB_3\n12 = SMP_28\n13 = SMP_29\n14 = SMP_30\n15 = SMP_31",
              4, old_value_t.trig_sel, new_value_t.trig_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "24: flow:1",
              "0 = Independent of DRQ request\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.flow, new_value_t.flow };
    m_bit_details_model.bits.append(entry);
    entry = { "25: trig:1",
              "0 = Independent of Trigger\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.trig, new_value_t.trig };
    m_bit_details_model.bits.append(entry);
    entry = { "26: once:1",
              "0 = Run for Multiple Block Transfer\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.once, new_value_t.once };
    m_bit_details_model.bits.append(entry);
    entry = { "27: dir:1",
              "0 = XMB read to AHB write\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.dir, new_value_t.dir };
    m_bit_details_model.bits.append(entry);
    entry = { "28: hold:1",
              "0 = Disable\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.hold, new_value_t.hold };
    m_bit_details_model.bits.append(entry);
    entry = { "29: fl_btwn:1",
              "0 = do not flush\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.fl_btwn, new_value_t.fl_btwn };
    m_bit_details_model.bits.append(entry);
    entry = { "30: ie_eoc:1",
              "0 = NOP\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.ie_eoc, new_value_t.ie_eoc };
    m_bit_details_model.bits.append(entry);
    entry = { "31: enb:1",
              "0 = Disable the DMA Channel\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.enb, new_value_t.enb };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "AHB-DMA-CHANNEL-3 Control Register";
}

#define AHBDMACHAN_CHANNEL_3_STA_OFFSET 0x64 + 0x1000
#define AHBDMACHAN_CHANNEL_3_STA_UNDEFMASK 0x2FFF0003
union ahbdmachan_channel_3_sta_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int count:14;              /* Remaining transfer count in 32bit word cycles Flags set / cleared by HW */
        unsigned int undefined_bits_16_27:12;
        unsigned int halt:1;                /* 0 = NOP  0 = DISABLE 1 = ENABLE */
        unsigned int undefined_bit_29:1;
        unsigned int is_eoc:1;              /* Write '1' to clear the flag  0 = NO_INTR 1 = INTR */
        unsigned int bsy:1;                 /* 0 = NOP Read-only 0 = DISABLE 1 = ENABLE */
    };

    u_int32_t reg32;
};

void Ahb_dmaDev::fill_ahbdmachan_channel_3_sta_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const ahbdmachan_channel_3_sta_u old_value_t = { .reg32 = value };
    const ahbdmachan_channel_3_sta_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: count:14",
              "Remaining transfer count in 32bit word cycles Flags set / cleared by HW",
              14, old_value_t.count, new_value_t.count };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_27:12", "", 12, old_value_t.undefined_bits_16_27, new_value_t.undefined_bits_16_27 };
    m_bit_details_model.bits.append(entry);
    entry = { "28: halt:1",
              "0 = NOP \n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.halt, new_value_t.halt };
    m_bit_details_model.bits.append(entry);
    entry = { "29: undefined_bit_29:1", "", 1, old_value_t.undefined_bit_29, new_value_t.undefined_bit_29 };
    m_bit_details_model.bits.append(entry);
    entry = { "30: is_eoc:1",
              "Write '1' to clear the flag \n0 = NO_INTR\n1 = INTR",
              1, old_value_t.is_eoc, new_value_t.is_eoc };
    m_bit_details_model.bits.append(entry);
    entry = { "31: bsy:1",
              "0 = NOP Read-only\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.bsy, new_value_t.bsy };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "AHB-DMA-CHANNEL-3 Status Register";
}

#define AHBDMACHAN_CHANNEL_3_AHB_PTR_OFFSET 0x70 + 0x1000
#define AHBDMACHAN_CHANNEL_3_AHB_PTR_UNDEFMASK 0x00000003
union ahbdmachan_channel_3_ahb_ptr_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int ahb_base:30;           /* AHB-DMA starting address pointer for internal AHB Bus */
    };

    u_int32_t reg32;
};

void Ahb_dmaDev::fill_ahbdmachan_channel_3_ahb_ptr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const ahbdmachan_channel_3_ahb_ptr_u old_value_t = { .reg32 = value };
    const ahbdmachan_channel_3_ahb_ptr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: ahb_base:30",
              "AHB-DMA starting address pointer for internal AHB Bus",
              30, old_value_t.ahb_base, new_value_t.ahb_base };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "AHB-DMA-CHANNEL-3 AHB Starting Address Pointer Register";
}

#define AHBDMACHAN_CHANNEL_3_AHB_SEQ_OFFSET 0x74 + 0x1000
#define AHBDMACHAN_CHANNEL_3_AHB_SEQ_UNDEFMASK 0x70100003
union ahbdmachan_channel_3_ahb_seq_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int ahb_stride:16;         /* This field tells us number of words that are supposed to be skipped on AHB side */
        unsigned int ahb_addr_wrap:1;       /* 0 = disable  0 = DISABLE 1 = ENABLE */
        unsigned int dbl_buf:1;             /* 0 = Reload Base Address for 1X blocks (default), reload each time 0 = DISABLE 1 = ENABLE */
        unsigned int undefined_bit_20:1;
        unsigned int ahb_stride_size:3;     /* 0 = disabled, otherwise stride is enabled 0 = DISABLE 1 = WORDS_4 2 = WORDS_8 3 = WORDS_16 4 = WORDS_32 5 = WORDS_64 6 = WORDS_128 7 = WORDS_256 */
        unsigned int ahb_burst:3;           /* 0,1,5-7 = rsvd 2 = WORD 3 = FOUR_WORD 4 = EIGHT_WORD */
        unsigned int ahb_data_swap:1;       /* 0 = no data conversion, when 1 and writeAhb: [31:0]->{[7:0],[15:8],[23:16],[31:24]}  0 = DISABLE 1 = ENABLE */
        unsigned int undefined_bits_28_30:3;
        unsigned int intr_enb:1;            /* 0 = send interrupt to COP 1 = CPU 0 = COP */
    };

    u_int32_t reg32;
};

void Ahb_dmaDev::fill_ahbdmachan_channel_3_ahb_seq_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const ahbdmachan_channel_3_ahb_seq_u old_value_t = { .reg32 = value };
    const ahbdmachan_channel_3_ahb_seq_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: ahb_stride:16",
              "This field tells us number of words that are supposed to be skipped on AHB side",
              16, old_value_t.ahb_stride, new_value_t.ahb_stride };
    m_bit_details_model.bits.append(entry);
    entry = { "18: ahb_addr_wrap:1",
              "0 = disable \n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.ahb_addr_wrap, new_value_t.ahb_addr_wrap };
    m_bit_details_model.bits.append(entry);
    entry = { "19: dbl_buf:1",
              "0 = Reload Base Address for 1X blocks (default), reload each time\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.dbl_buf, new_value_t.dbl_buf };
    m_bit_details_model.bits.append(entry);
    entry = { "20: undefined_bit_20:1", "", 1, old_value_t.undefined_bit_20, new_value_t.undefined_bit_20 };
    m_bit_details_model.bits.append(entry);
    entry = { "21: ahb_stride_size:3",
              "0 = disabled, otherwise stride is enabled\n0 = DISABLE\n1 = WORDS_4\n2 = WORDS_8\n3 = WORDS_16\n4 = WORDS_32\n5 = WORDS_64\n6 = WORDS_128\n7 = WORDS_256",
              3, old_value_t.ahb_stride_size, new_value_t.ahb_stride_size };
    m_bit_details_model.bits.append(entry);
    entry = { "24: ahb_burst:3",
              "0,1,5-7 = rsvd\n2 = WORD\n3 = FOUR_WORD\n4 = EIGHT_WORD",
              3, old_value_t.ahb_burst, new_value_t.ahb_burst };
    m_bit_details_model.bits.append(entry);
    entry = { "27: ahb_data_swap:1",
              "0 = no data conversion, when 1 and writeAhb: [31:0]->{[7:0],[15:8],[23:16],[31:24]} \n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.ahb_data_swap, new_value_t.ahb_data_swap };
    m_bit_details_model.bits.append(entry);
    entry = { "28: undefined_bits_28_30:3", "", 3, old_value_t.undefined_bits_28_30, new_value_t.undefined_bits_28_30 };
    m_bit_details_model.bits.append(entry);
    entry = { "31: intr_enb:1",
              "0 = send interrupt to COP\n1 = CPU\n0 = COP",
              1, old_value_t.intr_enb, new_value_t.intr_enb };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "AHB-DMA-CHANNEL-3 AHB Address Sequencer Register";
}

#define AHBDMACHAN_CHANNEL_3_XMB_PTR_OFFSET 0x78 + 0x1000
#define AHBDMACHAN_CHANNEL_3_XMB_PTR_UNDEFMASK 0x00000003
union ahbdmachan_channel_3_xmb_ptr_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int xmb_base:30;           /* AHB-DMA Starting address pointer for internal AHB Bus */
    };

    u_int32_t reg32;
};

void Ahb_dmaDev::fill_ahbdmachan_channel_3_xmb_ptr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const ahbdmachan_channel_3_xmb_ptr_u old_value_t = { .reg32 = value };
    const ahbdmachan_channel_3_xmb_ptr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: xmb_base:30",
              "AHB-DMA Starting address pointer for internal AHB Bus",
              30, old_value_t.xmb_base, new_value_t.xmb_base };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "AHB-DMA-CHANNEL-3 XMB Starting Address Pointer Register";
}

#define AHBDMACHAN_CHANNEL_3_XMB_SEQ_OFFSET 0x7C + 0x1000
#define AHBDMACHAN_CHANNEL_3_XMB_SEQ_UNDEFMASK 0xF7F00003
union ahbdmachan_channel_3_xmb_seq_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int xmb_stride:16;         /* This field tells us number of words that are supposed to be skipped on XMB side */
        unsigned int xmb_addr_wrap:1;       /* 0 = disable  0 = DISABLE 1 = ENABLE */
        unsigned int dbl_buf:1;             /* 0 = Reload Base Address for 1X blocks (default), reload each time 0 = DISABLE 1 = ENABLE */
        unsigned int undefined_bits_20_26:7;
        unsigned int xmb_data_swap:1;       /* 0 = no data conversion, when 1 and writeXmb: [31:0]->{[7:0],[15:8],[23:16],[31:24]} 0 = DISABLE 1 = ENABLE */
        unsigned int undefined_bits_28_31:4;
    };

    u_int32_t reg32;
};

void Ahb_dmaDev::fill_ahbdmachan_channel_3_xmb_seq_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const ahbdmachan_channel_3_xmb_seq_u old_value_t = { .reg32 = value };
    const ahbdmachan_channel_3_xmb_seq_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: xmb_stride:16",
              "This field tells us number of words that are supposed to be skipped on XMB side",
              16, old_value_t.xmb_stride, new_value_t.xmb_stride };
    m_bit_details_model.bits.append(entry);
    entry = { "18: xmb_addr_wrap:1",
              "0 = disable \n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.xmb_addr_wrap, new_value_t.xmb_addr_wrap };
    m_bit_details_model.bits.append(entry);
    entry = { "19: dbl_buf:1",
              "0 = Reload Base Address for 1X blocks (default), reload each time\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.dbl_buf, new_value_t.dbl_buf };
    m_bit_details_model.bits.append(entry);
    entry = { "20: undefined_bits_20_26:7", "", 7, old_value_t.undefined_bits_20_26, new_value_t.undefined_bits_20_26 };
    m_bit_details_model.bits.append(entry);
    entry = { "27: xmb_data_swap:1",
              "0 = no data conversion, when 1 and writeXmb: [31:0]->{[7:0],[15:8],[23:16],[31:24]}\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.xmb_data_swap, new_value_t.xmb_data_swap };
    m_bit_details_model.bits.append(entry);
    entry = { "28: undefined_bits_28_31:4", "", 4, old_value_t.undefined_bits_28_31, new_value_t.undefined_bits_28_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "AHB-DMA-CHANNEL-3 XMB Address Sequencer Register";
}



bool Ahb_dmaDev::is_offset_valid(const u_int32_t &offset) const
{
    switch (offset) {
    case CMD_OFFSET:
    case STA_OFFSET:
    case TX_REQ_OFFSET:
    case COUNTER_OFFSET:
    case IRQ_STA_CPU_OFFSET:
    case IRQ_STA_COP_OFFSET:
    case IRQ_MASK_OFFSET:
    case IRQ_MASK_SET_OFFSET:
    case IRQ_MASK_CLR_OFFSET:
    case RDWR_COHERENCY_OFFSET:
    case TEST_BUS_OFFSET:
    case PPCS_MCCIF_FIFOCTRL_OFFSET:
    case TIMEOUT_WCOAL_PPCS_OFFSET:
    case AHBDMACHAN_CHANNEL_0_CSR_OFFSET:
    case AHBDMACHAN_CHANNEL_0_STA_OFFSET:
    case AHBDMACHAN_CHANNEL_0_AHB_PTR_OFFSET:
    case AHBDMACHAN_CHANNEL_0_AHB_SEQ_OFFSET:
    case AHBDMACHAN_CHANNEL_0_XMB_PTR_OFFSET:
    case AHBDMACHAN_CHANNEL_0_XMB_SEQ_OFFSET:
    case AHBDMACHAN_CHANNEL_1_CSR_OFFSET:
    case AHBDMACHAN_CHANNEL_1_STA_OFFSET:
    case AHBDMACHAN_CHANNEL_1_AHB_PTR_OFFSET:
    case AHBDMACHAN_CHANNEL_1_AHB_SEQ_OFFSET:
    case AHBDMACHAN_CHANNEL_1_XMB_PTR_OFFSET:
    case AHBDMACHAN_CHANNEL_1_XMB_SEQ_OFFSET:
    case AHBDMACHAN_CHANNEL_2_CSR_OFFSET:
    case AHBDMACHAN_CHANNEL_2_STA_OFFSET:
    case AHBDMACHAN_CHANNEL_2_AHB_PTR_OFFSET:
    case AHBDMACHAN_CHANNEL_2_AHB_SEQ_OFFSET:
    case AHBDMACHAN_CHANNEL_2_XMB_PTR_OFFSET:
    case AHBDMACHAN_CHANNEL_2_XMB_SEQ_OFFSET:
    case AHBDMACHAN_CHANNEL_3_CSR_OFFSET:
    case AHBDMACHAN_CHANNEL_3_STA_OFFSET:
    case AHBDMACHAN_CHANNEL_3_AHB_PTR_OFFSET:
    case AHBDMACHAN_CHANNEL_3_AHB_SEQ_OFFSET:
    case AHBDMACHAN_CHANNEL_3_XMB_PTR_OFFSET:
    case AHBDMACHAN_CHANNEL_3_XMB_SEQ_OFFSET:
        return true;
    default:
        break;
    }

    return false;
}

bool Ahb_dmaDev::is_undef_changed(const u_int32_t &offset,
                                           const u_int32_t &value,
                                           const u_int32_t &new_value) const
{
    switch (offset) {
    case CMD_OFFSET:
        if ((value ^ new_value) & CMD_UNDEFMASK)
            return true;
        break;
    case STA_OFFSET:
        if ((value ^ new_value) & STA_UNDEFMASK)
            return true;
        break;
    case TX_REQ_OFFSET:
        if ((value ^ new_value) & TX_REQ_UNDEFMASK)
            return true;
        break;
    case COUNTER_OFFSET:
        if ((value ^ new_value) & COUNTER_UNDEFMASK)
            return true;
        break;
    case IRQ_STA_CPU_OFFSET:
        if ((value ^ new_value) & IRQ_STA_CPU_UNDEFMASK)
            return true;
        break;
    case IRQ_STA_COP_OFFSET:
        if ((value ^ new_value) & IRQ_STA_COP_UNDEFMASK)
            return true;
        break;
    case IRQ_MASK_OFFSET:
        if ((value ^ new_value) & IRQ_MASK_UNDEFMASK)
            return true;
        break;
    case IRQ_MASK_SET_OFFSET:
        if ((value ^ new_value) & IRQ_MASK_SET_UNDEFMASK)
            return true;
        break;
    case IRQ_MASK_CLR_OFFSET:
        if ((value ^ new_value) & IRQ_MASK_CLR_UNDEFMASK)
            return true;
        break;
    case RDWR_COHERENCY_OFFSET:
        if ((value ^ new_value) & RDWR_COHERENCY_UNDEFMASK)
            return true;
        break;
    case TEST_BUS_OFFSET:
        if ((value ^ new_value) & TEST_BUS_UNDEFMASK)
            return true;
        break;
    case PPCS_MCCIF_FIFOCTRL_OFFSET:
        if ((value ^ new_value) & PPCS_MCCIF_FIFOCTRL_UNDEFMASK)
            return true;
        break;
    case TIMEOUT_WCOAL_PPCS_OFFSET:
        if ((value ^ new_value) & TIMEOUT_WCOAL_PPCS_UNDEFMASK)
            return true;
        break;
    case AHBDMACHAN_CHANNEL_0_CSR_OFFSET:
        if ((value ^ new_value) & AHBDMACHAN_CHANNEL_0_CSR_UNDEFMASK)
            return true;
        break;
    case AHBDMACHAN_CHANNEL_0_STA_OFFSET:
        if ((value ^ new_value) & AHBDMACHAN_CHANNEL_0_STA_UNDEFMASK)
            return true;
        break;
    case AHBDMACHAN_CHANNEL_0_AHB_PTR_OFFSET:
        if ((value ^ new_value) & AHBDMACHAN_CHANNEL_0_AHB_PTR_UNDEFMASK)
            return true;
        break;
    case AHBDMACHAN_CHANNEL_0_AHB_SEQ_OFFSET:
        if ((value ^ new_value) & AHBDMACHAN_CHANNEL_0_AHB_SEQ_UNDEFMASK)
            return true;
        break;
    case AHBDMACHAN_CHANNEL_0_XMB_PTR_OFFSET:
        if ((value ^ new_value) & AHBDMACHAN_CHANNEL_0_XMB_PTR_UNDEFMASK)
            return true;
        break;
    case AHBDMACHAN_CHANNEL_0_XMB_SEQ_OFFSET:
        if ((value ^ new_value) & AHBDMACHAN_CHANNEL_0_XMB_SEQ_UNDEFMASK)
            return true;
        break;
    case AHBDMACHAN_CHANNEL_1_CSR_OFFSET:
        if ((value ^ new_value) & AHBDMACHAN_CHANNEL_1_CSR_UNDEFMASK)
            return true;
        break;
    case AHBDMACHAN_CHANNEL_1_STA_OFFSET:
        if ((value ^ new_value) & AHBDMACHAN_CHANNEL_1_STA_UNDEFMASK)
            return true;
        break;
    case AHBDMACHAN_CHANNEL_1_AHB_PTR_OFFSET:
        if ((value ^ new_value) & AHBDMACHAN_CHANNEL_1_AHB_PTR_UNDEFMASK)
            return true;
        break;
    case AHBDMACHAN_CHANNEL_1_AHB_SEQ_OFFSET:
        if ((value ^ new_value) & AHBDMACHAN_CHANNEL_1_AHB_SEQ_UNDEFMASK)
            return true;
        break;
    case AHBDMACHAN_CHANNEL_1_XMB_PTR_OFFSET:
        if ((value ^ new_value) & AHBDMACHAN_CHANNEL_1_XMB_PTR_UNDEFMASK)
            return true;
        break;
    case AHBDMACHAN_CHANNEL_1_XMB_SEQ_OFFSET:
        if ((value ^ new_value) & AHBDMACHAN_CHANNEL_1_XMB_SEQ_UNDEFMASK)
            return true;
        break;
    case AHBDMACHAN_CHANNEL_2_CSR_OFFSET:
        if ((value ^ new_value) & AHBDMACHAN_CHANNEL_2_CSR_UNDEFMASK)
            return true;
        break;
    case AHBDMACHAN_CHANNEL_2_STA_OFFSET:
        if ((value ^ new_value) & AHBDMACHAN_CHANNEL_2_STA_UNDEFMASK)
            return true;
        break;
    case AHBDMACHAN_CHANNEL_2_AHB_PTR_OFFSET:
        if ((value ^ new_value) & AHBDMACHAN_CHANNEL_2_AHB_PTR_UNDEFMASK)
            return true;
        break;
    case AHBDMACHAN_CHANNEL_2_AHB_SEQ_OFFSET:
        if ((value ^ new_value) & AHBDMACHAN_CHANNEL_2_AHB_SEQ_UNDEFMASK)
            return true;
        break;
    case AHBDMACHAN_CHANNEL_2_XMB_PTR_OFFSET:
        if ((value ^ new_value) & AHBDMACHAN_CHANNEL_2_XMB_PTR_UNDEFMASK)
            return true;
        break;
    case AHBDMACHAN_CHANNEL_2_XMB_SEQ_OFFSET:
        if ((value ^ new_value) & AHBDMACHAN_CHANNEL_2_XMB_SEQ_UNDEFMASK)
            return true;
        break;
    case AHBDMACHAN_CHANNEL_3_CSR_OFFSET:
        if ((value ^ new_value) & AHBDMACHAN_CHANNEL_3_CSR_UNDEFMASK)
            return true;
        break;
    case AHBDMACHAN_CHANNEL_3_STA_OFFSET:
        if ((value ^ new_value) & AHBDMACHAN_CHANNEL_3_STA_UNDEFMASK)
            return true;
        break;
    case AHBDMACHAN_CHANNEL_3_AHB_PTR_OFFSET:
        if ((value ^ new_value) & AHBDMACHAN_CHANNEL_3_AHB_PTR_UNDEFMASK)
            return true;
        break;
    case AHBDMACHAN_CHANNEL_3_AHB_SEQ_OFFSET:
        if ((value ^ new_value) & AHBDMACHAN_CHANNEL_3_AHB_SEQ_UNDEFMASK)
            return true;
        break;
    case AHBDMACHAN_CHANNEL_3_XMB_PTR_OFFSET:
        if ((value ^ new_value) & AHBDMACHAN_CHANNEL_3_XMB_PTR_UNDEFMASK)
            return true;
        break;
    case AHBDMACHAN_CHANNEL_3_XMB_SEQ_OFFSET:
        if ((value ^ new_value) & AHBDMACHAN_CHANNEL_3_XMB_SEQ_UNDEFMASK)
            return true;
        break;

    default:
        break;
    }

    return false;
}


QString Ahb_dmaDev::get_register_name(const log_entry &entry) const
{
    switch (entry.offset) {
    case CMD_OFFSET:
        return QString("CMD");
    case STA_OFFSET:
        return QString("STA");
    case TX_REQ_OFFSET:
        return QString("TX_REQ");
    case COUNTER_OFFSET:
        return QString("COUNTER");
    case IRQ_STA_CPU_OFFSET:
        return QString("IRQ_STA_CPU");
    case IRQ_STA_COP_OFFSET:
        return QString("IRQ_STA_COP");
    case IRQ_MASK_OFFSET:
        return QString("IRQ_MASK");
    case IRQ_MASK_SET_OFFSET:
        return QString("IRQ_MASK_SET");
    case IRQ_MASK_CLR_OFFSET:
        return QString("IRQ_MASK_CLR");
    case RDWR_COHERENCY_OFFSET:
        return QString("RDWR_COHERENCY");
    case TEST_BUS_OFFSET:
        return QString("TEST_BUS");
    case PPCS_MCCIF_FIFOCTRL_OFFSET:
        return QString("PPCS_MCCIF_FIFOCTRL");
    case TIMEOUT_WCOAL_PPCS_OFFSET:
        return QString("TIMEOUT_WCOAL_PPCS");
    case AHBDMACHAN_CHANNEL_0_CSR_OFFSET:
        return QString("AHBDMACHAN_CHANNEL_0_CSR");
    case AHBDMACHAN_CHANNEL_0_STA_OFFSET:
        return QString("AHBDMACHAN_CHANNEL_0_STA");
    case AHBDMACHAN_CHANNEL_0_AHB_PTR_OFFSET:
        return QString("AHBDMACHAN_CHANNEL_0_AHB_PTR");
    case AHBDMACHAN_CHANNEL_0_AHB_SEQ_OFFSET:
        return QString("AHBDMACHAN_CHANNEL_0_AHB_SEQ");
    case AHBDMACHAN_CHANNEL_0_XMB_PTR_OFFSET:
        return QString("AHBDMACHAN_CHANNEL_0_XMB_PTR");
    case AHBDMACHAN_CHANNEL_0_XMB_SEQ_OFFSET:
        return QString("AHBDMACHAN_CHANNEL_0_XMB_SEQ");
    case AHBDMACHAN_CHANNEL_1_CSR_OFFSET:
        return QString("AHBDMACHAN_CHANNEL_1_CSR");
    case AHBDMACHAN_CHANNEL_1_STA_OFFSET:
        return QString("AHBDMACHAN_CHANNEL_1_STA");
    case AHBDMACHAN_CHANNEL_1_AHB_PTR_OFFSET:
        return QString("AHBDMACHAN_CHANNEL_1_AHB_PTR");
    case AHBDMACHAN_CHANNEL_1_AHB_SEQ_OFFSET:
        return QString("AHBDMACHAN_CHANNEL_1_AHB_SEQ");
    case AHBDMACHAN_CHANNEL_1_XMB_PTR_OFFSET:
        return QString("AHBDMACHAN_CHANNEL_1_XMB_PTR");
    case AHBDMACHAN_CHANNEL_1_XMB_SEQ_OFFSET:
        return QString("AHBDMACHAN_CHANNEL_1_XMB_SEQ");
    case AHBDMACHAN_CHANNEL_2_CSR_OFFSET:
        return QString("AHBDMACHAN_CHANNEL_2_CSR");
    case AHBDMACHAN_CHANNEL_2_STA_OFFSET:
        return QString("AHBDMACHAN_CHANNEL_2_STA");
    case AHBDMACHAN_CHANNEL_2_AHB_PTR_OFFSET:
        return QString("AHBDMACHAN_CHANNEL_2_AHB_PTR");
    case AHBDMACHAN_CHANNEL_2_AHB_SEQ_OFFSET:
        return QString("AHBDMACHAN_CHANNEL_2_AHB_SEQ");
    case AHBDMACHAN_CHANNEL_2_XMB_PTR_OFFSET:
        return QString("AHBDMACHAN_CHANNEL_2_XMB_PTR");
    case AHBDMACHAN_CHANNEL_2_XMB_SEQ_OFFSET:
        return QString("AHBDMACHAN_CHANNEL_2_XMB_SEQ");
    case AHBDMACHAN_CHANNEL_3_CSR_OFFSET:
        return QString("AHBDMACHAN_CHANNEL_3_CSR");
    case AHBDMACHAN_CHANNEL_3_STA_OFFSET:
        return QString("AHBDMACHAN_CHANNEL_3_STA");
    case AHBDMACHAN_CHANNEL_3_AHB_PTR_OFFSET:
        return QString("AHBDMACHAN_CHANNEL_3_AHB_PTR");
    case AHBDMACHAN_CHANNEL_3_AHB_SEQ_OFFSET:
        return QString("AHBDMACHAN_CHANNEL_3_AHB_SEQ");
    case AHBDMACHAN_CHANNEL_3_XMB_PTR_OFFSET:
        return QString("AHBDMACHAN_CHANNEL_3_XMB_PTR");
    case AHBDMACHAN_CHANNEL_3_XMB_SEQ_OFFSET:
        return QString("AHBDMACHAN_CHANNEL_3_XMB_SEQ");

    default:
        break;
    }

    qDebug() << QString().sprintf("AHB_DMA: %s: Ooops... 0x%x", __func__, entry.offset);

    return QString().sprintf("Ooops... @0x%X", entry.offset);
}

void Ahb_dmaDev::fill_bits_details(const u_int32_t &offset,
                                      const u_int32_t &value, const u_int32_t &new_value)
{
    switch (offset) {
    case CMD_OFFSET:
        fill_cmd_details(value, new_value);
        break;
    case STA_OFFSET:
        fill_sta_details(value, new_value);
        break;
    case TX_REQ_OFFSET:
        fill_tx_req_details(value, new_value);
        break;
    case COUNTER_OFFSET:
        fill_counter_details(value, new_value);
        break;
    case IRQ_STA_CPU_OFFSET:
        fill_irq_sta_cpu_details(value, new_value);
        break;
    case IRQ_STA_COP_OFFSET:
        fill_irq_sta_cop_details(value, new_value);
        break;
    case IRQ_MASK_OFFSET:
        fill_irq_mask_details(value, new_value);
        break;
    case IRQ_MASK_SET_OFFSET:
        fill_irq_mask_set_details(value, new_value);
        break;
    case IRQ_MASK_CLR_OFFSET:
        fill_irq_mask_clr_details(value, new_value);
        break;
    case RDWR_COHERENCY_OFFSET:
        fill_rdwr_coherency_details(value, new_value);
        break;
    case TEST_BUS_OFFSET:
        fill_test_bus_details(value, new_value);
        break;
    case PPCS_MCCIF_FIFOCTRL_OFFSET:
        fill_ppcs_mccif_fifoctrl_details(value, new_value);
        break;
    case TIMEOUT_WCOAL_PPCS_OFFSET:
        fill_timeout_wcoal_ppcs_details(value, new_value);
        break;
    case AHBDMACHAN_CHANNEL_0_CSR_OFFSET:
        fill_ahbdmachan_channel_0_csr_details(value, new_value);
        break;
    case AHBDMACHAN_CHANNEL_0_STA_OFFSET:
        fill_ahbdmachan_channel_0_sta_details(value, new_value);
        break;
    case AHBDMACHAN_CHANNEL_0_AHB_PTR_OFFSET:
        fill_ahbdmachan_channel_0_ahb_ptr_details(value, new_value);
        break;
    case AHBDMACHAN_CHANNEL_0_AHB_SEQ_OFFSET:
        fill_ahbdmachan_channel_0_ahb_seq_details(value, new_value);
        break;
    case AHBDMACHAN_CHANNEL_0_XMB_PTR_OFFSET:
        fill_ahbdmachan_channel_0_xmb_ptr_details(value, new_value);
        break;
    case AHBDMACHAN_CHANNEL_0_XMB_SEQ_OFFSET:
        fill_ahbdmachan_channel_0_xmb_seq_details(value, new_value);
        break;
    case AHBDMACHAN_CHANNEL_1_CSR_OFFSET:
        fill_ahbdmachan_channel_1_csr_details(value, new_value);
        break;
    case AHBDMACHAN_CHANNEL_1_STA_OFFSET:
        fill_ahbdmachan_channel_1_sta_details(value, new_value);
        break;
    case AHBDMACHAN_CHANNEL_1_AHB_PTR_OFFSET:
        fill_ahbdmachan_channel_1_ahb_ptr_details(value, new_value);
        break;
    case AHBDMACHAN_CHANNEL_1_AHB_SEQ_OFFSET:
        fill_ahbdmachan_channel_1_ahb_seq_details(value, new_value);
        break;
    case AHBDMACHAN_CHANNEL_1_XMB_PTR_OFFSET:
        fill_ahbdmachan_channel_1_xmb_ptr_details(value, new_value);
        break;
    case AHBDMACHAN_CHANNEL_1_XMB_SEQ_OFFSET:
        fill_ahbdmachan_channel_1_xmb_seq_details(value, new_value);
        break;
    case AHBDMACHAN_CHANNEL_2_CSR_OFFSET:
        fill_ahbdmachan_channel_2_csr_details(value, new_value);
        break;
    case AHBDMACHAN_CHANNEL_2_STA_OFFSET:
        fill_ahbdmachan_channel_2_sta_details(value, new_value);
        break;
    case AHBDMACHAN_CHANNEL_2_AHB_PTR_OFFSET:
        fill_ahbdmachan_channel_2_ahb_ptr_details(value, new_value);
        break;
    case AHBDMACHAN_CHANNEL_2_AHB_SEQ_OFFSET:
        fill_ahbdmachan_channel_2_ahb_seq_details(value, new_value);
        break;
    case AHBDMACHAN_CHANNEL_2_XMB_PTR_OFFSET:
        fill_ahbdmachan_channel_2_xmb_ptr_details(value, new_value);
        break;
    case AHBDMACHAN_CHANNEL_2_XMB_SEQ_OFFSET:
        fill_ahbdmachan_channel_2_xmb_seq_details(value, new_value);
        break;
    case AHBDMACHAN_CHANNEL_3_CSR_OFFSET:
        fill_ahbdmachan_channel_3_csr_details(value, new_value);
        break;
    case AHBDMACHAN_CHANNEL_3_STA_OFFSET:
        fill_ahbdmachan_channel_3_sta_details(value, new_value);
        break;
    case AHBDMACHAN_CHANNEL_3_AHB_PTR_OFFSET:
        fill_ahbdmachan_channel_3_ahb_ptr_details(value, new_value);
        break;
    case AHBDMACHAN_CHANNEL_3_AHB_SEQ_OFFSET:
        fill_ahbdmachan_channel_3_ahb_seq_details(value, new_value);
        break;
    case AHBDMACHAN_CHANNEL_3_XMB_PTR_OFFSET:
        fill_ahbdmachan_channel_3_xmb_ptr_details(value, new_value);
        break;
    case AHBDMACHAN_CHANNEL_3_XMB_SEQ_OFFSET:
        fill_ahbdmachan_channel_3_xmb_seq_details(value, new_value);
        break;

    default:
        m_bit_details_model.bits.clear();
        break;
    }
}
