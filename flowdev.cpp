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

#include "flowdev.h"

#include <QDebug>

FlowDev::FlowDev(QObject *parent) :
    Device(parent)
{
}

#define HALT_CPU_EVENTS_OFFSET 0x0
#define HALT_CPU_EVENTS_UNDEFMASK 0x00000000
union halt_cpu_events_u {
    struct {
        unsigned int zero:8;
        unsigned int fiq_0:1;
        unsigned int fiq_1:1;
        unsigned int irq_0:1;
        unsigned int irq_1:1;
        unsigned int ibf:1;
        unsigned int ibe:1;
        unsigned int obf:1;
        unsigned int obe:1;
        unsigned int xrq_a:1;
        unsigned int xrq_b:1;
        unsigned int xrq_c:1;
        unsigned int xrq_d:1;
        unsigned int smp30:1;
        unsigned int smp31:1;
        unsigned int x_rdy:1;
        unsigned int sec:1;
        unsigned int msec:1;
        unsigned int usec:1;
        unsigned int x32k:1;
        unsigned int sclk:1;
        unsigned int jtag:1;
        unsigned int mode:3;                /* 0 = FLOW_MODE_NONE 1 = FLOW_MODE_RUN_AND_INT 2 = FLOW_MODE_WAITEVENT 3 = FLOW_MODE_WAITEVENT_AND_INT 4 = FLOW_MODE_STOP_UNTIL_IRQ 5 = FLOW_MODE_STOP_UNTIL_IRQ_AND_INT 6 = FLOW_MODE_STOP_UNTIL_EVENT_AND_IRQ 2 = FLOW_MODE_STOP 3 = FLOW_MODE_STOP_AND_INT 4 = FLOW_MODE_STOP_UNTIL_INT 5 = FLOW_MODE_STOP_UNTIL_INT_AND_INT 6 = FLOW_MODE_STOP_OR_INT */
    };

    u_int32_t reg32;
};

void FlowDev::fill_halt_cpu_events_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const halt_cpu_events_u old_value_t = { .reg32 = value };
    const halt_cpu_events_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: zero:8", "", 8, old_value_t.zero, new_value_t.zero };
    m_bit_details_model.bits.append(entry);
    entry = { "08: fiq_0:1", "", 1, old_value_t.fiq_0, new_value_t.fiq_0 };
    m_bit_details_model.bits.append(entry);
    entry = { "09: fiq_1:1", "", 1, old_value_t.fiq_1, new_value_t.fiq_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "10: irq_0:1", "", 1, old_value_t.irq_0, new_value_t.irq_0 };
    m_bit_details_model.bits.append(entry);
    entry = { "11: irq_1:1", "", 1, old_value_t.irq_1, new_value_t.irq_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: ibf:1", "", 1, old_value_t.ibf, new_value_t.ibf };
    m_bit_details_model.bits.append(entry);
    entry = { "13: ibe:1", "", 1, old_value_t.ibe, new_value_t.ibe };
    m_bit_details_model.bits.append(entry);
    entry = { "14: obf:1", "", 1, old_value_t.obf, new_value_t.obf };
    m_bit_details_model.bits.append(entry);
    entry = { "15: obe:1", "", 1, old_value_t.obe, new_value_t.obe };
    m_bit_details_model.bits.append(entry);
    entry = { "16: xrq_a:1", "", 1, old_value_t.xrq_a, new_value_t.xrq_a };
    m_bit_details_model.bits.append(entry);
    entry = { "17: xrq_b:1", "", 1, old_value_t.xrq_b, new_value_t.xrq_b };
    m_bit_details_model.bits.append(entry);
    entry = { "18: xrq_c:1", "", 1, old_value_t.xrq_c, new_value_t.xrq_c };
    m_bit_details_model.bits.append(entry);
    entry = { "19: xrq_d:1", "", 1, old_value_t.xrq_d, new_value_t.xrq_d };
    m_bit_details_model.bits.append(entry);
    entry = { "20: smp30:1", "", 1, old_value_t.smp30, new_value_t.smp30 };
    m_bit_details_model.bits.append(entry);
    entry = { "21: smp31:1", "", 1, old_value_t.smp31, new_value_t.smp31 };
    m_bit_details_model.bits.append(entry);
    entry = { "22: x_rdy:1", "", 1, old_value_t.x_rdy, new_value_t.x_rdy };
    m_bit_details_model.bits.append(entry);
    entry = { "23: sec:1", "", 1, old_value_t.sec, new_value_t.sec };
    m_bit_details_model.bits.append(entry);
    entry = { "24: msec:1", "", 1, old_value_t.msec, new_value_t.msec };
    m_bit_details_model.bits.append(entry);
    entry = { "25: usec:1", "", 1, old_value_t.usec, new_value_t.usec };
    m_bit_details_model.bits.append(entry);
    entry = { "26: x32k:1", "", 1, old_value_t.x32k, new_value_t.x32k };
    m_bit_details_model.bits.append(entry);
    entry = { "27: sclk:1", "", 1, old_value_t.sclk, new_value_t.sclk };
    m_bit_details_model.bits.append(entry);
    entry = { "28: jtag:1", "", 1, old_value_t.jtag, new_value_t.jtag };
    m_bit_details_model.bits.append(entry);
    entry = { "29: mode:3",
              "0 = FLOW_MODE_NONE\n1 = FLOW_MODE_RUN_AND_INT\n2 = FLOW_MODE_WAITEVENT\n3 = FLOW_MODE_WAITEVENT_AND_INT\n4 = FLOW_MODE_STOP_UNTIL_IRQ\n5 = FLOW_MODE_STOP_UNTIL_IRQ_AND_INT\n6 = FLOW_MODE_STOP_UNTIL_EVENT_AND_IRQ\n2 = FLOW_MODE_STOP\n3 = FLOW_MODE_STOP_AND_INT\n4 = FLOW_MODE_STOP_UNTIL_INT\n5 = FLOW_MODE_STOP_UNTIL_INT_AND_INT\n6 = FLOW_MODE_STOP_OR_INT",
              3, old_value_t.mode, new_value_t.mode };
    m_bit_details_model.bits.append(entry);
}

#define HALT_COP_EVENTS_OFFSET 0x4
#define HALT_COP_EVENTS_UNDEFMASK 0x00000000
union halt_cop_events_u {
    struct {
        unsigned int zero:8;
        unsigned int fiq_0:1;
        unsigned int fiq_1:1;
        unsigned int irq_0:1;
        unsigned int irq_1:1;
        unsigned int ibf:1;
        unsigned int ibe:1;
        unsigned int obf:1;
        unsigned int obe:1;
        unsigned int xrq_a:1;
        unsigned int xrq_b:1;
        unsigned int xrq_c:1;
        unsigned int xrq_d:1;
        unsigned int smp30:1;
        unsigned int smp31:1;
        unsigned int x_rdy:1;
        unsigned int sec:1;
        unsigned int msec:1;
        unsigned int usec:1;
        unsigned int x32k:1;
        unsigned int sclk:1;
        unsigned int jtag:1;
        unsigned int mode:3;                /* 0 = FLOW_MODE_NONE 1 = FLOW_MODE_RUN_AND_INT 2 = FLOW_MODE_WAITEVENT 3 = FLOW_MODE_WAITEVENT_AND_INT 4 = FLOW_MODE_STOP_UNTIL_IRQ 5 = FLOW_MODE_STOP_UNTIL_IRQ_AND_INT 6 = FLOW_MODE_STOP_UNTIL_EVENT_AND_IRQ 2 = FLOW_MODE_STOP 3 = FLOW_MODE_STOP_AND_INT 4 = FLOW_MODE_STOP_UNTIL_INT 5 = FLOW_MODE_STOP_UNTIL_INT_AND_INT 6 = FLOW_MODE_STOP_OR_INT */
    };

    u_int32_t reg32;
};

void FlowDev::fill_halt_cop_events_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const halt_cop_events_u old_value_t = { .reg32 = value };
    const halt_cop_events_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: zero:8", "", 8, old_value_t.zero, new_value_t.zero };
    m_bit_details_model.bits.append(entry);
    entry = { "08: fiq_0:1", "", 1, old_value_t.fiq_0, new_value_t.fiq_0 };
    m_bit_details_model.bits.append(entry);
    entry = { "09: fiq_1:1", "", 1, old_value_t.fiq_1, new_value_t.fiq_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "10: irq_0:1", "", 1, old_value_t.irq_0, new_value_t.irq_0 };
    m_bit_details_model.bits.append(entry);
    entry = { "11: irq_1:1", "", 1, old_value_t.irq_1, new_value_t.irq_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: ibf:1", "", 1, old_value_t.ibf, new_value_t.ibf };
    m_bit_details_model.bits.append(entry);
    entry = { "13: ibe:1", "", 1, old_value_t.ibe, new_value_t.ibe };
    m_bit_details_model.bits.append(entry);
    entry = { "14: obf:1", "", 1, old_value_t.obf, new_value_t.obf };
    m_bit_details_model.bits.append(entry);
    entry = { "15: obe:1", "", 1, old_value_t.obe, new_value_t.obe };
    m_bit_details_model.bits.append(entry);
    entry = { "16: xrq_a:1", "", 1, old_value_t.xrq_a, new_value_t.xrq_a };
    m_bit_details_model.bits.append(entry);
    entry = { "17: xrq_b:1", "", 1, old_value_t.xrq_b, new_value_t.xrq_b };
    m_bit_details_model.bits.append(entry);
    entry = { "18: xrq_c:1", "", 1, old_value_t.xrq_c, new_value_t.xrq_c };
    m_bit_details_model.bits.append(entry);
    entry = { "19: xrq_d:1", "", 1, old_value_t.xrq_d, new_value_t.xrq_d };
    m_bit_details_model.bits.append(entry);
    entry = { "20: smp30:1", "", 1, old_value_t.smp30, new_value_t.smp30 };
    m_bit_details_model.bits.append(entry);
    entry = { "21: smp31:1", "", 1, old_value_t.smp31, new_value_t.smp31 };
    m_bit_details_model.bits.append(entry);
    entry = { "22: x_rdy:1", "", 1, old_value_t.x_rdy, new_value_t.x_rdy };
    m_bit_details_model.bits.append(entry);
    entry = { "23: sec:1", "", 1, old_value_t.sec, new_value_t.sec };
    m_bit_details_model.bits.append(entry);
    entry = { "24: msec:1", "", 1, old_value_t.msec, new_value_t.msec };
    m_bit_details_model.bits.append(entry);
    entry = { "25: usec:1", "", 1, old_value_t.usec, new_value_t.usec };
    m_bit_details_model.bits.append(entry);
    entry = { "26: x32k:1", "", 1, old_value_t.x32k, new_value_t.x32k };
    m_bit_details_model.bits.append(entry);
    entry = { "27: sclk:1", "", 1, old_value_t.sclk, new_value_t.sclk };
    m_bit_details_model.bits.append(entry);
    entry = { "28: jtag:1", "", 1, old_value_t.jtag, new_value_t.jtag };
    m_bit_details_model.bits.append(entry);
    entry = { "29: mode:3",
              "0 = FLOW_MODE_NONE\n1 = FLOW_MODE_RUN_AND_INT\n2 = FLOW_MODE_WAITEVENT\n3 = FLOW_MODE_WAITEVENT_AND_INT\n4 = FLOW_MODE_STOP_UNTIL_IRQ\n5 = FLOW_MODE_STOP_UNTIL_IRQ_AND_INT\n6 = FLOW_MODE_STOP_UNTIL_EVENT_AND_IRQ\n2 = FLOW_MODE_STOP\n3 = FLOW_MODE_STOP_AND_INT\n4 = FLOW_MODE_STOP_UNTIL_INT\n5 = FLOW_MODE_STOP_UNTIL_INT_AND_INT\n6 = FLOW_MODE_STOP_OR_INT",
              3, old_value_t.mode, new_value_t.mode };
    m_bit_details_model.bits.append(entry);
}

#define CPU_CSR_OFFSET 0x8
#define CPU_CSR_UNDEFMASK 0xF0043FCC
union cpu_csr_u {
    struct {
        unsigned int enable:1;
        unsigned int event_enable:1;
        unsigned int undefined_bits_2_3:2;
        unsigned int wait_wfe_bitmap:2;
        unsigned int undefined_bits_6_13:8;
        unsigned int event_flag:1;
        unsigned int intr_flag:1;
        unsigned int pwr_off_sts:1;
        unsigned int f2c_mpcore_rst:1;
        unsigned int undefined_bit_18:1;
        unsigned int f2p_req:1;
        unsigned int f2p_pwrup:1;
        unsigned int p2f_ack:1;
        unsigned int halt:1;
        unsigned int wait_event:1;
        unsigned int pwr_state:4;
        unsigned int undefined_bits_28_31:4;
    };

    u_int32_t reg32;
};

void FlowDev::fill_cpu_csr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const cpu_csr_u old_value_t = { .reg32 = value };
    const cpu_csr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: enable:1", "", 1, old_value_t.enable, new_value_t.enable };
    m_bit_details_model.bits.append(entry);
    entry = { "01: event_enable:1", "", 1, old_value_t.event_enable, new_value_t.event_enable };
    m_bit_details_model.bits.append(entry);
    entry = { "02: undefined_bits_2_3:2", "", 2, old_value_t.undefined_bits_2_3, new_value_t.undefined_bits_2_3 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: wait_wfe_bitmap:2", "", 2, old_value_t.wait_wfe_bitmap, new_value_t.wait_wfe_bitmap };
    m_bit_details_model.bits.append(entry);
    entry = { "06: undefined_bits_6_13:8", "", 8, old_value_t.undefined_bits_6_13, new_value_t.undefined_bits_6_13 };
    m_bit_details_model.bits.append(entry);
    entry = { "14: event_flag:1", "", 1, old_value_t.event_flag, new_value_t.event_flag };
    m_bit_details_model.bits.append(entry);
    entry = { "15: intr_flag:1", "", 1, old_value_t.intr_flag, new_value_t.intr_flag };
    m_bit_details_model.bits.append(entry);
    entry = { "16: pwr_off_sts:1", "", 1, old_value_t.pwr_off_sts, new_value_t.pwr_off_sts };
    m_bit_details_model.bits.append(entry);
    entry = { "17: f2c_mpcore_rst:1", "", 1, old_value_t.f2c_mpcore_rst, new_value_t.f2c_mpcore_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "18: undefined_bit_18:1", "", 1, old_value_t.undefined_bit_18, new_value_t.undefined_bit_18 };
    m_bit_details_model.bits.append(entry);
    entry = { "19: f2p_req:1", "", 1, old_value_t.f2p_req, new_value_t.f2p_req };
    m_bit_details_model.bits.append(entry);
    entry = { "20: f2p_pwrup:1", "", 1, old_value_t.f2p_pwrup, new_value_t.f2p_pwrup };
    m_bit_details_model.bits.append(entry);
    entry = { "21: p2f_ack:1", "", 1, old_value_t.p2f_ack, new_value_t.p2f_ack };
    m_bit_details_model.bits.append(entry);
    entry = { "22: halt:1", "", 1, old_value_t.halt, new_value_t.halt };
    m_bit_details_model.bits.append(entry);
    entry = { "23: wait_event:1", "", 1, old_value_t.wait_event, new_value_t.wait_event };
    m_bit_details_model.bits.append(entry);
    entry = { "24: pwr_state:4", "", 4, old_value_t.pwr_state, new_value_t.pwr_state };
    m_bit_details_model.bits.append(entry);
    entry = { "28: undefined_bits_28_31:4", "", 4, old_value_t.undefined_bits_28_31, new_value_t.undefined_bits_28_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "The CPU_CSR registers are replicated for CPU0 and CPU1. They define additional characteristics of the flow controller linked to CPU cores, especially the interaction of the flow controller with power management functions. The LP1 state is normally entered and exited via side effects of the flow controller operation.\nNote:\n The difference between LP1 and LP0 is not visible at the flow controller, but is defined by a configuration bit in PMC (LP1 entry triggers LP0 entry).\nAll fields of the CPU_CSR register have an initial value of 0.  The different fields are:\n    * PWR_STATE : Current state of the powerGate State Machine\n    * WAIT_EVENT: CPU is waiting, wake up is via an event\n    *  HALT: CPU is halted\n    *  P2F_ACK: pmc2flow_ack signal, this is the same signal for both CPU cores\n    *  F2P_PWRUP : flow2pmc_pwrup, this is the same signal for both CPU cores\n    *  F2P_REQ : flow2pmc_req valid, this is the same signal for both CPU cores\n    *  F2C_MPCORE_RST : TRUE when Requesting Reset of MPCore\n    *  PWR_OFF_STS : TRUE when CPU PowerGated OFF by Flow Controller\n    *  INTR_FLAG : TRUE when Interrupt is Active -- Write-1-to-Clear\n    *  EVENT_FLAG : TRUE when Event is Active -- Write-1-to Clear\n    *  WAIT_WFE_BITMAP : All cores indicated in bitmap must be in STANDBY_WFE before CPU PowerGating\n    *  EVENT_ENABLE : Generates an event when the flow controller exits the halted state\n    *  ENABLE: PowerGate Enable - Halt or Event-wait causes CPU PowerGating";
}

#define COP_CSR_OFFSET 0xC
#define COP_CSR_UNDEFMASK 0xFFFF7FFF
union cop_csr_u {
    struct {
        unsigned int undefined_bits_0_14:15;
        unsigned int intr_flag:1;           /* TRUE when Interrupt is Active -- Write-1-to-Clear */
        unsigned int undefined_bits_16_31:16;
    };

    u_int32_t reg32;
};

void FlowDev::fill_cop_csr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const cop_csr_u old_value_t = { .reg32 = value };
    const cop_csr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_14:15", "", 15, old_value_t.undefined_bits_0_14, new_value_t.undefined_bits_0_14 };
    m_bit_details_model.bits.append(entry);
    entry = { "15: intr_flag:1",
              "TRUE when Interrupt is Active -- Write-1-to-Clear",
              1, old_value_t.intr_flag, new_value_t.intr_flag };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_31:16", "", 16, old_value_t.undefined_bits_16_31, new_value_t.undefined_bits_16_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "COP Control/Status for Interrupts\nR/W addr=6000:700c";
}

#define XRQ_EVENTS_OFFSET 0x10
#define XRQ_EVENTS_UNDEFMASK 0x00000000
union xrq_events_u {
    struct {
        unsigned int xrq_a7_xrq_a0:8;       /* Setting a bit to 1 enables event triggering for the corresponding bit in GPIO port A. The assertion level is determined by GPIO_INT.LVL.A. If more than one XRQ.A bit is set, the events are ORed together. The resultant event is enabled by setting the XRQ.A bit in the HALT_CPU.EVENTS or HALT_COP.EVENTS registers */
        unsigned int xrq_b7_xrq_b0:8;       /* Setting a bit to 1 enables event triggering for the corresponding bit in GPIO port B. The assertion level is determined by GPIO_INT.LVL.B. If more than one XRQ.B bit is set, the events are ORed together. The resultant event is enabled by setting the XRQ.B bit in the HALT_CPU.EVENTS or HALT_COP.EVENTS registers */
        unsigned int xrq_c7_xrq_c0:8;       /* Setting a bit to 1 enables event triggering for the corresponding bit in GPIO port C. The assertion level is determined by GPIO_INT.LVL.C. If more than one XRQ.C bit is set, the events are ORed together. The resultant event is enabled by setting the XRQ.C bit in the HALT_CPU.EVENTS or HALT_COP.EVENTS registers */
        unsigned int xrq_d7_xrq_d0:8;       /* Setting a bit to 1 enables event triggering for the corresponding bit in GPIO port D. The assertion level is determined by GPIO_INT.LVL.D. If more than one XRQ.D bit is set, the events are ORed together. The resultant event is enabled by setting the XRQ.D bit in the HALT_CPU.EVENTS or HALT_COP.EVENTS registers */
    };

    u_int32_t reg32;
};

void FlowDev::fill_xrq_events_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const xrq_events_u old_value_t = { .reg32 = value };
    const xrq_events_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: xrq_a7_xrq_a0:8",
              "Setting a bit to 1 enables event triggering for the corresponding bit in GPIO port A. The assertion level is determined by GPIO_INT.LVL.A. If more than one XRQ.A bit is set, the events are ORed together. The resultant event is enabled by setting the XRQ.A bit in the HALT_CPU.EVENTS or HALT_COP.EVENTS registers",
              8, old_value_t.xrq_a7_xrq_a0, new_value_t.xrq_a7_xrq_a0 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: xrq_b7_xrq_b0:8",
              "Setting a bit to 1 enables event triggering for the corresponding bit in GPIO port B. The assertion level is determined by GPIO_INT.LVL.B. If more than one XRQ.B bit is set, the events are ORed together. The resultant event is enabled by setting the XRQ.B bit in the HALT_CPU.EVENTS or HALT_COP.EVENTS registers",
              8, old_value_t.xrq_b7_xrq_b0, new_value_t.xrq_b7_xrq_b0 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: xrq_c7_xrq_c0:8",
              "Setting a bit to 1 enables event triggering for the corresponding bit in GPIO port C. The assertion level is determined by GPIO_INT.LVL.C. If more than one XRQ.C bit is set, the events are ORed together. The resultant event is enabled by setting the XRQ.C bit in the HALT_CPU.EVENTS or HALT_COP.EVENTS registers",
              8, old_value_t.xrq_c7_xrq_c0, new_value_t.xrq_c7_xrq_c0 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: xrq_d7_xrq_d0:8",
              "Setting a bit to 1 enables event triggering for the corresponding bit in GPIO port D. The assertion level is determined by GPIO_INT.LVL.D. If more than one XRQ.D bit is set, the events are ORed together. The resultant event is enabled by setting the XRQ.D bit in the HALT_CPU.EVENTS or HALT_COP.EVENTS registers",
              8, old_value_t.xrq_d7_xrq_d0, new_value_t.xrq_d7_xrq_d0 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "XRQ Event Detect Selector Register";
}

#define HALT_CPU1_EVENTS_OFFSET 0x14
#define HALT_CPU1_EVENTS_UNDEFMASK 0x00000000
union halt_cpu1_events_u {
    struct {
        unsigned int zero:8;
        unsigned int fiq_0:1;
        unsigned int fiq_1:1;
        unsigned int irq_0:1;
        unsigned int irq_1:1;
        unsigned int ibf:1;
        unsigned int ibe:1;
        unsigned int obf:1;
        unsigned int obe:1;
        unsigned int xrq_a:1;
        unsigned int xrq_b:1;
        unsigned int xrq_c:1;
        unsigned int xrq_d:1;
        unsigned int smp30:1;
        unsigned int smp31:1;
        unsigned int x_rdy:1;
        unsigned int sec:1;
        unsigned int msec:1;
        unsigned int usec:1;
        unsigned int x32k:1;
        unsigned int sclk:1;
        unsigned int jtag:1;
        unsigned int mode:3;                /* 0 = FLOW_MODE_NONE 1 = FLOW_MODE_RUN_AND_INT 2 = FLOW_MODE_WAITEVENT 3 = FLOW_MODE_WAITEVENT_AND_INT 4 = FLOW_MODE_STOP_UNTIL_IRQ 5 = FLOW_MODE_STOP_UNTIL_IRQ_AND_INT 6 = FLOW_MODE_STOP_UNTIL_EVENT_AND_IRQ 2 = FLOW_MODE_STOP 3 = FLOW_MODE_STOP_AND_INT 4 = FLOW_MODE_STOP_UNTIL_INT 5 = FLOW_MODE_STOP_UNTIL_INT_AND_INT 6 = FLOW_MODE_STOP_OR_INT */
    };

    u_int32_t reg32;
};

void FlowDev::fill_halt_cpu1_events_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const halt_cpu1_events_u old_value_t = { .reg32 = value };
    const halt_cpu1_events_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: zero:8", "", 8, old_value_t.zero, new_value_t.zero };
    m_bit_details_model.bits.append(entry);
    entry = { "08: fiq_0:1", "", 1, old_value_t.fiq_0, new_value_t.fiq_0 };
    m_bit_details_model.bits.append(entry);
    entry = { "09: fiq_1:1", "", 1, old_value_t.fiq_1, new_value_t.fiq_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "10: irq_0:1", "", 1, old_value_t.irq_0, new_value_t.irq_0 };
    m_bit_details_model.bits.append(entry);
    entry = { "11: irq_1:1", "", 1, old_value_t.irq_1, new_value_t.irq_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: ibf:1", "", 1, old_value_t.ibf, new_value_t.ibf };
    m_bit_details_model.bits.append(entry);
    entry = { "13: ibe:1", "", 1, old_value_t.ibe, new_value_t.ibe };
    m_bit_details_model.bits.append(entry);
    entry = { "14: obf:1", "", 1, old_value_t.obf, new_value_t.obf };
    m_bit_details_model.bits.append(entry);
    entry = { "15: obe:1", "", 1, old_value_t.obe, new_value_t.obe };
    m_bit_details_model.bits.append(entry);
    entry = { "16: xrq_a:1", "", 1, old_value_t.xrq_a, new_value_t.xrq_a };
    m_bit_details_model.bits.append(entry);
    entry = { "17: xrq_b:1", "", 1, old_value_t.xrq_b, new_value_t.xrq_b };
    m_bit_details_model.bits.append(entry);
    entry = { "18: xrq_c:1", "", 1, old_value_t.xrq_c, new_value_t.xrq_c };
    m_bit_details_model.bits.append(entry);
    entry = { "19: xrq_d:1", "", 1, old_value_t.xrq_d, new_value_t.xrq_d };
    m_bit_details_model.bits.append(entry);
    entry = { "20: smp30:1", "", 1, old_value_t.smp30, new_value_t.smp30 };
    m_bit_details_model.bits.append(entry);
    entry = { "21: smp31:1", "", 1, old_value_t.smp31, new_value_t.smp31 };
    m_bit_details_model.bits.append(entry);
    entry = { "22: x_rdy:1", "", 1, old_value_t.x_rdy, new_value_t.x_rdy };
    m_bit_details_model.bits.append(entry);
    entry = { "23: sec:1", "", 1, old_value_t.sec, new_value_t.sec };
    m_bit_details_model.bits.append(entry);
    entry = { "24: msec:1", "", 1, old_value_t.msec, new_value_t.msec };
    m_bit_details_model.bits.append(entry);
    entry = { "25: usec:1", "", 1, old_value_t.usec, new_value_t.usec };
    m_bit_details_model.bits.append(entry);
    entry = { "26: x32k:1", "", 1, old_value_t.x32k, new_value_t.x32k };
    m_bit_details_model.bits.append(entry);
    entry = { "27: sclk:1", "", 1, old_value_t.sclk, new_value_t.sclk };
    m_bit_details_model.bits.append(entry);
    entry = { "28: jtag:1", "", 1, old_value_t.jtag, new_value_t.jtag };
    m_bit_details_model.bits.append(entry);
    entry = { "29: mode:3",
              "0 = FLOW_MODE_NONE\n1 = FLOW_MODE_RUN_AND_INT\n2 = FLOW_MODE_WAITEVENT\n3 = FLOW_MODE_WAITEVENT_AND_INT\n4 = FLOW_MODE_STOP_UNTIL_IRQ\n5 = FLOW_MODE_STOP_UNTIL_IRQ_AND_INT\n6 = FLOW_MODE_STOP_UNTIL_EVENT_AND_IRQ\n2 = FLOW_MODE_STOP\n3 = FLOW_MODE_STOP_AND_INT\n4 = FLOW_MODE_STOP_UNTIL_INT\n5 = FLOW_MODE_STOP_UNTIL_INT_AND_INT\n6 = FLOW_MODE_STOP_OR_INT",
              3, old_value_t.mode, new_value_t.mode };
    m_bit_details_model.bits.append(entry);
}

#define CPU1_CSR_OFFSET 0x18
#define CPU1_CSR_UNDEFMASK 0xF0043FCC
union cpu1_csr_u {
    struct {
        unsigned int enable:1;
        unsigned int event_enable:1;
        unsigned int undefined_bits_2_3:2;
        unsigned int wait_wfe_bitmap:2;
        unsigned int undefined_bits_6_13:8;
        unsigned int event_flag:1;
        unsigned int intr_flag:1;
        unsigned int pwr_off_sts:1;
        unsigned int f2c_mpcore_rst:1;
        unsigned int undefined_bit_18:1;
        unsigned int f2p_req:1;
        unsigned int f2p_pwrup:1;
        unsigned int p2f_ack:1;
        unsigned int halt:1;
        unsigned int wait_event:1;
        unsigned int pwr_state:4;
        unsigned int undefined_bits_28_31:4;
    };

    u_int32_t reg32;
};

void FlowDev::fill_cpu1_csr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const cpu1_csr_u old_value_t = { .reg32 = value };
    const cpu1_csr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: enable:1", "", 1, old_value_t.enable, new_value_t.enable };
    m_bit_details_model.bits.append(entry);
    entry = { "01: event_enable:1", "", 1, old_value_t.event_enable, new_value_t.event_enable };
    m_bit_details_model.bits.append(entry);
    entry = { "02: undefined_bits_2_3:2", "", 2, old_value_t.undefined_bits_2_3, new_value_t.undefined_bits_2_3 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: wait_wfe_bitmap:2", "", 2, old_value_t.wait_wfe_bitmap, new_value_t.wait_wfe_bitmap };
    m_bit_details_model.bits.append(entry);
    entry = { "06: undefined_bits_6_13:8", "", 8, old_value_t.undefined_bits_6_13, new_value_t.undefined_bits_6_13 };
    m_bit_details_model.bits.append(entry);
    entry = { "14: event_flag:1", "", 1, old_value_t.event_flag, new_value_t.event_flag };
    m_bit_details_model.bits.append(entry);
    entry = { "15: intr_flag:1", "", 1, old_value_t.intr_flag, new_value_t.intr_flag };
    m_bit_details_model.bits.append(entry);
    entry = { "16: pwr_off_sts:1", "", 1, old_value_t.pwr_off_sts, new_value_t.pwr_off_sts };
    m_bit_details_model.bits.append(entry);
    entry = { "17: f2c_mpcore_rst:1", "", 1, old_value_t.f2c_mpcore_rst, new_value_t.f2c_mpcore_rst };
    m_bit_details_model.bits.append(entry);
    entry = { "18: undefined_bit_18:1", "", 1, old_value_t.undefined_bit_18, new_value_t.undefined_bit_18 };
    m_bit_details_model.bits.append(entry);
    entry = { "19: f2p_req:1", "", 1, old_value_t.f2p_req, new_value_t.f2p_req };
    m_bit_details_model.bits.append(entry);
    entry = { "20: f2p_pwrup:1", "", 1, old_value_t.f2p_pwrup, new_value_t.f2p_pwrup };
    m_bit_details_model.bits.append(entry);
    entry = { "21: p2f_ack:1", "", 1, old_value_t.p2f_ack, new_value_t.p2f_ack };
    m_bit_details_model.bits.append(entry);
    entry = { "22: halt:1", "", 1, old_value_t.halt, new_value_t.halt };
    m_bit_details_model.bits.append(entry);
    entry = { "23: wait_event:1", "", 1, old_value_t.wait_event, new_value_t.wait_event };
    m_bit_details_model.bits.append(entry);
    entry = { "24: pwr_state:4", "", 4, old_value_t.pwr_state, new_value_t.pwr_state };
    m_bit_details_model.bits.append(entry);
    entry = { "28: undefined_bits_28_31:4", "", 4, old_value_t.undefined_bits_28_31, new_value_t.undefined_bits_28_31 };
    m_bit_details_model.bits.append(entry);
}

bool FlowDev::is_offset_valid(const u_int32_t &offset) const
{
    switch (offset) {
    case HALT_CPU_EVENTS_OFFSET:
    case HALT_COP_EVENTS_OFFSET:
    case CPU_CSR_OFFSET:
    case COP_CSR_OFFSET:
    case XRQ_EVENTS_OFFSET:
    case HALT_CPU1_EVENTS_OFFSET:
    case CPU1_CSR_OFFSET:
        return true;
    default:
        break;
    }

    return false;
}

bool FlowDev::is_undef_changed(const u_int32_t &offset,
                                           const u_int32_t &value,
                                           const u_int32_t &new_value) const
{
    switch (offset) {
    case HALT_CPU_EVENTS_OFFSET:
        if ((value ^ new_value) & HALT_CPU_EVENTS_UNDEFMASK)
            return true;
        break;
    case HALT_COP_EVENTS_OFFSET:
        if ((value ^ new_value) & HALT_COP_EVENTS_UNDEFMASK)
            return true;
        break;
    case CPU_CSR_OFFSET:
        if ((value ^ new_value) & CPU_CSR_UNDEFMASK)
            return true;
        break;
    case COP_CSR_OFFSET:
        if ((value ^ new_value) & COP_CSR_UNDEFMASK)
            return true;
        break;
    case XRQ_EVENTS_OFFSET:
        if ((value ^ new_value) & XRQ_EVENTS_UNDEFMASK)
            return true;
        break;
    case HALT_CPU1_EVENTS_OFFSET:
        if ((value ^ new_value) & HALT_CPU1_EVENTS_UNDEFMASK)
            return true;
        break;
    case CPU1_CSR_OFFSET:
        if ((value ^ new_value) & CPU1_CSR_UNDEFMASK)
            return true;
        break;

    default:
        break;
    }

    return false;
}

QString FlowDev::get_register_name(const log_entry &entry) const
{
    switch (entry.offset) {
    case HALT_CPU_EVENTS_OFFSET:
        return QString("HALT_CPU_EVENTS");
    case HALT_COP_EVENTS_OFFSET:
        return QString("HALT_COP_EVENTS");
    case CPU_CSR_OFFSET:
        return QString("CPU_CSR");
    case COP_CSR_OFFSET:
        return QString("COP_CSR");
    case XRQ_EVENTS_OFFSET:
        return QString("XRQ_EVENTS");
    case HALT_CPU1_EVENTS_OFFSET:
        return QString("HALT_CPU1_EVENTS");
    case CPU1_CSR_OFFSET:
        return QString("CPU1_CSR");

    default:
        break;
    }

    qDebug() << QString().sprintf("FLOW: %s: Ooops... 0x%x", __func__, entry.offset);

    return QString().sprintf("Ooops... @0x%X", entry.offset);
}

void FlowDev::fill_bits_details(const u_int32_t &offset,
                                      const u_int32_t &value, const u_int32_t &new_value)
{
    switch (offset) {
    case HALT_CPU_EVENTS_OFFSET:
        fill_halt_cpu_events_details(value, new_value);
        break;
    case HALT_COP_EVENTS_OFFSET:
        fill_halt_cop_events_details(value, new_value);
        break;
    case CPU_CSR_OFFSET:
        fill_cpu_csr_details(value, new_value);
        break;
    case COP_CSR_OFFSET:
        fill_cop_csr_details(value, new_value);
        break;
    case XRQ_EVENTS_OFFSET:
        fill_xrq_events_details(value, new_value);
        break;
    case HALT_CPU1_EVENTS_OFFSET:
        fill_halt_cpu1_events_details(value, new_value);
        break;
    case CPU1_CSR_OFFSET:
        fill_cpu1_csr_details(value, new_value);
        break;

    default:
        m_bit_details_model.bits.clear();
        break;
    }
}
