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

#include "host1x_dev.h"

#include <QDebug>

#define NV_CLASS_HOST_INCR_SYNCPT_OFFSET 0x0
#define NV_CLASS_HOST_INCR_SYNCPT_UNDEFMASK 0xFFFF0000
union nv_class_host_incr_syncpt_u {
    struct {
        unsigned int indx:8;                /* syncpt index value */
        unsigned int cond:8;                /* Condition mapped from raise/wait 0 = IMMEDIATE 1 = OP_DONE 2 = RD_DONE 3 = REG_WR_SAFE 4 = COND_4 5 = COND_5 6 = COND_6 7 = COND_7 8 = COND_8 9 = COND_9 10 = COND_10 11 = COND_11 12 = COND_12 13 = COND_13 14 = COND_14 15 = COND_15 */
        unsigned int undefined_bits_16_31:16;
    };

    u_int32_t reg32;
};

void Host1xDev::fill_nv_class_host_incr_syncpt_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const nv_class_host_incr_syncpt_u old_value_t = { .reg32 = value };
    const nv_class_host_incr_syncpt_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: indx:8",
              "syncpt index value",
              8, old_value_t.indx, new_value_t.indx };
    m_bit_details_model.bits.append(entry);
    entry = { "08: cond:8",
              "Condition mapped from raise/wait\n0 = IMMEDIATE\n1 = OP_DONE\n2 = RD_DONE\n3 = REG_WR_SAFE\n4 = COND_4\n5 = COND_5\n6 = COND_6\n7 = COND_7\n8 = COND_8\n9 = COND_9\n10 = COND_10\n11 = COND_11\n12 = COND_12\n13 = COND_13\n14 = COND_14\n15 = COND_15",
              8, old_value_t.cond, new_value_t.cond };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_31:16", "", 16, old_value_t.undefined_bits_16_31, new_value_t.undefined_bits_16_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "All Classes have the INCR_SYNCPT method For host, this method, immediately increments SYNCPT[indx], irrespective of the cond. Note that INCR_SYNCPT_CNTRL and INCR_SYNCPT_ERROR are included for consistency with host clients, but writes to INCR_SYNCPT_CNTRL have no effect on the operation of host1x, and because there are no condition FIFOs to overflow, INCR_SYNCPT_ERROR will never be set.";
}

#define NV_CLASS_HOST_INCR_SYNCPT_CNTRL_OFFSET 0x1
#define NV_CLASS_HOST_INCR_SYNCPT_CNTRL_UNDEFMASK 0xFFFFFEFE
union nv_class_host_incr_syncpt_cntrl_u {
    struct {
        unsigned int incr_syncpt_soft_reset:1;/* If SOFT_RESET is set, then all internal state of the client syncpt block will be reset. To do soft reset, first set SOFT_RESET of all host1x clients affected, then clear all SOFT_RESETs */
        unsigned int undefined_bits_1_7:7;
        unsigned int incr_syncpt_no_stall:1;/* If NO_STALL is 1, then when FIFOs are full, INCR_SYNCPT methods will be dropped and the INCR_SYNCPT_ERROR[COND] bit will be set. If NO_STALL is 0, then when FIFOs are full, the client host interface will be stalled */
        unsigned int undefined_bits_9_31:23;
    };

    u_int32_t reg32;
};

void Host1xDev::fill_nv_class_host_incr_syncpt_cntrl_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const nv_class_host_incr_syncpt_cntrl_u old_value_t = { .reg32 = value };
    const nv_class_host_incr_syncpt_cntrl_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: incr_syncpt_soft_reset:1",
              "If SOFT_RESET is set, then all internal state of the client syncpt block will be reset. To do soft reset, first set SOFT_RESET of all host1x clients affected, then clear all SOFT_RESETs",
              1, old_value_t.incr_syncpt_soft_reset, new_value_t.incr_syncpt_soft_reset };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_7:7", "", 7, old_value_t.undefined_bits_1_7, new_value_t.undefined_bits_1_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: incr_syncpt_no_stall:1",
              "If NO_STALL is 1, then when FIFOs are full, INCR_SYNCPT methods will be dropped and the INCR_SYNCPT_ERROR[COND] bit will be set. If NO_STALL is 0, then when FIFOs are full, the client host interface will be stalled",
              1, old_value_t.incr_syncpt_no_stall, new_value_t.incr_syncpt_no_stall };
    m_bit_details_model.bits.append(entry);
    entry = { "09: undefined_bits_9_31:23", "", 23, old_value_t.undefined_bits_9_31, new_value_t.undefined_bits_9_31 };
    m_bit_details_model.bits.append(entry);
}

#define NV_CLASS_HOST_INCR_SYNCPT_ERROR_OFFSET 0x2
#define NV_CLASS_HOST_INCR_SYNCPT_ERROR_UNDEFMASK 0x00000000
union nv_class_host_incr_syncpt_error_u {
    struct {
        unsigned int cond_status:32;        /* COND_STATUS[COND] is set if the FIFO for COND overflows. This bit is sticky and will remain set until cleared. Cleared by writing 1 */
    };

    u_int32_t reg32;
};

void Host1xDev::fill_nv_class_host_incr_syncpt_error_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const nv_class_host_incr_syncpt_error_u old_value_t = { .reg32 = value };
    const nv_class_host_incr_syncpt_error_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: cond_status:32",
              "COND_STATUS[COND] is set if the FIFO for COND overflows. This bit is sticky and will remain set until cleared. Cleared by writing 1",
              32, old_value_t.cond_status, new_value_t.cond_status };
    m_bit_details_model.bits.append(entry);
}

#define NV_CLASS_HOST_WAIT_SYNCPT_OFFSET 0x8
#define NV_CLASS_HOST_WAIT_SYNCPT_UNDEFMASK 0x00000000
union nv_class_host_wait_syncpt_u {
    struct {
        unsigned int thresh:24;
        unsigned int indx:8;
    };

    u_int32_t reg32;
};

void Host1xDev::fill_nv_class_host_wait_syncpt_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const nv_class_host_wait_syncpt_u old_value_t = { .reg32 = value };
    const nv_class_host_wait_syncpt_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: thresh:24", "", 24, old_value_t.thresh, new_value_t.thresh };
    m_bit_details_model.bits.append(entry);
    entry = { "24: indx:8", "", 8, old_value_t.indx, new_value_t.indx };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Wait on syncpt method.\nCommand dispatch will stall until:\nSYNCPT[indx][NV_HOST1X_SYNCPT_THRESH_WIDTH-1:0] >= threshold[NV_HOST1X_SYNCPT_THRESH_WIDTH-1:0]\nThe comparison takes into account the possibility of wrapping. Note that more bits are allocated for indx and threshold than may be used in an implementation Use NV_HOST1X_SYNCPT_NB_PTS for the number of syncpts, and NV_HOST1X_SYNCPT_THESH_WIDTH for the number of bits used by the comparison.";
}

#define NV_CLASS_HOST_WAIT_SYNCPT_BASE_OFFSET 0x9
#define NV_CLASS_HOST_WAIT_SYNCPT_BASE_UNDEFMASK 0x00000000
union nv_class_host_wait_syncpt_base_u {
    struct {
        unsigned int offset:16;
        unsigned int base_indx:8;
        unsigned int indx:8;
    };

    u_int32_t reg32;
};

void Host1xDev::fill_nv_class_host_wait_syncpt_base_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const nv_class_host_wait_syncpt_base_u old_value_t = { .reg32 = value };
    const nv_class_host_wait_syncpt_base_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: offset:16", "", 16, old_value_t.offset, new_value_t.offset };
    m_bit_details_model.bits.append(entry);
    entry = { "16: base_indx:8", "", 8, old_value_t.base_indx, new_value_t.base_indx };
    m_bit_details_model.bits.append(entry);
    entry = { "24: indx:8", "", 8, old_value_t.indx, new_value_t.indx };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Wait on syncpt method using base register.\nCommand dispatch will stall until:\nSYNCPT[indx][NV_HOST1X_SYNCPT_THRESH_WIDTH-1:0] >= (SYNCPT_BASE[base_indx]+offset)\nThe comparison here is of 16 bit value and takes into account the possibility of wrapping. Note that more bits are allocated for indx and base_indx than may be used in an implementation. Use NV_HOST1X_SYNCPT_NB_PTS for the number of syncpts, Use NV_HOST1X_SYNCPT_NB_BASES for the number of syncpt_bases, and NV_HOST1X_SYNCPT_THRESH_WIDTH for the number of bits used by the comparison If NV_HOST1X_SYNCPT_THESH_WIDTH is greater than 16, offset is sign-extended before it is added to SYNCPT_BASE.";
}

#define NV_CLASS_HOST_WAIT_SYNCPT_INCR_OFFSET 0xA
#define NV_CLASS_HOST_WAIT_SYNCPT_INCR_UNDEFMASK 0x00FFFFFF
union nv_class_host_wait_syncpt_incr_u {
    struct {
        unsigned int undefined_bits_0_23:24;
        unsigned int indx:8;
    };

    u_int32_t reg32;
};

void Host1xDev::fill_nv_class_host_wait_syncpt_incr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const nv_class_host_wait_syncpt_incr_u old_value_t = { .reg32 = value };
    const nv_class_host_wait_syncpt_incr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_23:24", "", 24, old_value_t.undefined_bits_0_23, new_value_t.undefined_bits_0_23 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: indx:8", "", 8, old_value_t.indx, new_value_t.indx };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Wait on syncpt increment method.\nCommand dispatch will stall until the next time that SYNCPT[indx] is incremented.\nNote that more bits are allocated for indx than may be used in an implementation. Use NV_HOST1X_SYNCPT_NB_PTS for the number of syncpts.";
}

#define NV_CLASS_HOST_LOAD_SYNCPT_BASE_OFFSET 0xB
#define NV_CLASS_HOST_LOAD_SYNCPT_BASE_UNDEFMASK 0x00000000
union nv_class_host_load_syncpt_base_u {
    struct {
        unsigned int value:24;
        unsigned int base_indx:8;
    };

    u_int32_t reg32;
};

void Host1xDev::fill_nv_class_host_load_syncpt_base_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const nv_class_host_load_syncpt_base_u old_value_t = { .reg32 = value };
    const nv_class_host_load_syncpt_base_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: value:24", "", 24, old_value_t.value, new_value_t.value };
    m_bit_details_model.bits.append(entry);
    entry = { "24: base_indx:8", "", 8, old_value_t.base_indx, new_value_t.base_indx };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Load syncpt base method.\nSYNCPT_BASE[indx] = value";
}

#define NV_CLASS_HOST_INCR_SYNCPT_BASE_OFFSET 0xC
#define NV_CLASS_HOST_INCR_SYNCPT_BASE_UNDEFMASK 0x00000000
union nv_class_host_incr_syncpt_base_u {
    struct {
        unsigned int offset:24;
        unsigned int base_indx:8;
    };

    u_int32_t reg32;
};

void Host1xDev::fill_nv_class_host_incr_syncpt_base_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const nv_class_host_incr_syncpt_base_u old_value_t = { .reg32 = value };
    const nv_class_host_incr_syncpt_base_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: offset:24", "", 24, old_value_t.offset, new_value_t.offset };
    m_bit_details_model.bits.append(entry);
    entry = { "24: base_indx:8", "", 8, old_value_t.base_indx, new_value_t.base_indx };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Increment syncpt base method.\nSYNCPT_BASE[indx] += offset";
}

#define NV_CLASS_HOST_DELAY_USEC_OFFSET 0x10
#define NV_CLASS_HOST_DELAY_USEC_UNDEFMASK 0xFFF00000
union nv_class_host_delay_usec_u {
    struct {
        unsigned int nusec:20;              /* Enough for 1.05 seconds */
        unsigned int undefined_bits_20_31:12;
    };

    u_int32_t reg32;
};

void Host1xDev::fill_nv_class_host_delay_usec_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const nv_class_host_delay_usec_u old_value_t = { .reg32 = value };
    const nv_class_host_delay_usec_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: nusec:20",
              "Enough for 1.05 seconds",
              20, old_value_t.nusec, new_value_t.nusec };
    m_bit_details_model.bits.append(entry);
    entry = { "20: undefined_bits_20_31:12", "", 12, old_value_t.undefined_bits_20_31, new_value_t.undefined_bits_20_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Delay number of microseconds.  Command dispatch will stall until the number of microseconds indicated in NUSEC has passed.  The timing of microseconds is controlled by the USEC_CLK register.";
}

#define NV_CLASS_HOST_TICKCOUNT_HI_OFFSET 0x11
#define NV_CLASS_HOST_TICKCOUNT_HI_UNDEFMASK 0x00000000
union nv_class_host_tickcount_hi_u {
    struct {
        unsigned int ticks_hi:32;           /* read or write tick count */
    };

    u_int32_t reg32;
};

void Host1xDev::fill_nv_class_host_tickcount_hi_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const nv_class_host_tickcount_hi_u old_value_t = { .reg32 = value };
    const nv_class_host_tickcount_hi_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: ticks_hi:32",
              "read or write tick count",
              32, old_value_t.ticks_hi, new_value_t.ticks_hi };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "This register value will initialize the high 32 bits of tick count value in the host clock counter.";
}

#define NV_CLASS_HOST_TICKCOUNT_LO_OFFSET 0x12
#define NV_CLASS_HOST_TICKCOUNT_LO_UNDEFMASK 0x00000000
union nv_class_host_tickcount_lo_u {
    struct {
        unsigned int ticks_lo:32;           /* read or write tick count */
    };

    u_int32_t reg32;
};

void Host1xDev::fill_nv_class_host_tickcount_lo_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const nv_class_host_tickcount_lo_u old_value_t = { .reg32 = value };
    const nv_class_host_tickcount_lo_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: ticks_lo:32",
              "read or write tick count",
              32, old_value_t.ticks_lo, new_value_t.ticks_lo };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "This register value will initialize the low 32 bits of tick count value in the host clock counter.";
}

#define NV_CLASS_HOST_TICKCTRL_OFFSET 0x13
#define NV_CLASS_HOST_TICKCTRL_UNDEFMASK 0xFFFFFFFE
union nv_class_host_tickctrl_u {
    struct {
        unsigned int tickcnt_enable:1;      /* Enable or Disable tick counter 0 = DISABLE 1 = ENABLE */
        unsigned int undefined_bits_1_31:31;
    };

    u_int32_t reg32;
};

void Host1xDev::fill_nv_class_host_tickctrl_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const nv_class_host_tickctrl_u old_value_t = { .reg32 = value };
    const nv_class_host_tickctrl_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: tickcnt_enable:1",
              "Enable or Disable tick counter\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.tickcnt_enable, new_value_t.tickcnt_enable };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_31:31", "", 31, old_value_t.undefined_bits_1_31, new_value_t.undefined_bits_1_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "This register write enables the tick counter on the host clock to start counting.";
}

#define NV_CLASS_HOST_INDCTRL_OFFSET 0x2B
#define NV_CLASS_HOST_INDCTRL_UNDEFMASK 0x03FFFFFC
union nv_class_host_indctrl_u {
    struct {
        unsigned int rwn:1;                 /* Read/write 0 = WRITE 1 = READ */
        unsigned int acctype:1;             /* Access type: indirect register or indirect framebuffer 0 = REG 1 = FB */
        unsigned int undefined_bits_2_25:24;
        unsigned int spool:1;               /* Route return data to spool FIFO, only applicable to reads 0 = DISABLE 1 = ENABLE */
        unsigned int autoinc:1;             /* Auto increment of read/write address 0 = DISABLE 1 = ENABLE */
        unsigned int indbe:4;               /* Byte enables. Will apply to all subsequent data transactions. Not applicable for reads */
    };

    u_int32_t reg32;
};

void Host1xDev::fill_nv_class_host_indctrl_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const nv_class_host_indctrl_u old_value_t = { .reg32 = value };
    const nv_class_host_indctrl_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: rwn:1",
              "Read/write\n0 = WRITE\n1 = READ",
              1, old_value_t.rwn, new_value_t.rwn };
    m_bit_details_model.bits.append(entry);
    entry = { "01: acctype:1",
              "Access type: indirect register or indirect framebuffer\n0 = REG\n1 = FB",
              1, old_value_t.acctype, new_value_t.acctype };
    m_bit_details_model.bits.append(entry);
    entry = { "02: undefined_bits_2_25:24", "", 24, old_value_t.undefined_bits_2_25, new_value_t.undefined_bits_2_25 };
    m_bit_details_model.bits.append(entry);
    entry = { "26: spool:1",
              "Route return data to spool FIFO, only applicable to reads\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.spool, new_value_t.spool };
    m_bit_details_model.bits.append(entry);
    entry = { "27: autoinc:1",
              "Auto increment of read/write address\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.autoinc, new_value_t.autoinc };
    m_bit_details_model.bits.append(entry);
    entry = { "28: indbe:4",
              "Byte enables. Will apply to all subsequent data transactions. Not applicable for reads",
              4, old_value_t.indbe, new_value_t.indbe };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Note:\n Indirect Addressing.\nThese registers (along with INDDATA) are used to indirectly read/write either register or memory.  Host registers are not accessible using this interface. If AUTOINC is set, INDOFFSET increments by 4 on every access of INDDATA.\nEither INDCTRL/INDOFF2 or INDOFF can be used, but INDOFF may not be able to address all memory in chips with large memory maps.  The rundundant bits in INDCTRL and INDOFF are shared, so writing either offset sets those bits.\nThe following restrictions apply to the use of indirect memory writes:\n    * At initialization time, do a dummy indirect write (with all byte enables set to zero)\n    * Dedicate an MLOCK for indirect memory writes, then before a channel issues a set of indirect memory writes it must acquire this MLOCK; after the writes have been issued, the MLOCK is released -- this will restrict the use of indirect memory writes to a single channel at a time.";
}

#define NV_CLASS_HOST_INDOFF2_OFFSET 0x2C
#define NV_CLASS_HOST_INDOFF2_UNDEFMASK 0xFC000003
union nv_class_host_indoff2_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int indroffset:16;         /* ACCTYPE=REG: register offset ([15:0]) */
        unsigned int indmodid:8;            /* ACCTYPE=REG: register module ID 0 = HOST1X 1 = MPE 2 = VI 3 = EPP 4 = ISP 5 = GR2D 6 = GR3D 8 = DISPLAY 11 = TVO 9 = DISPLAYB 12 = DSI 10 = HDMI */
        unsigned int undefined_bits_26_31:6;
    };

    u_int32_t reg32;
};

void Host1xDev::fill_nv_class_host_indoff2_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const nv_class_host_indoff2_u old_value_t = { .reg32 = value };
    const nv_class_host_indoff2_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: indroffset:16",
              "ACCTYPE=REG: register offset ([15:0])",
              16, old_value_t.indroffset, new_value_t.indroffset };
    m_bit_details_model.bits.append(entry);
    entry = { "18: indmodid:8",
              "ACCTYPE=REG: register module ID\n0 = HOST1X\n1 = MPE\n2 = VI\n3 = EPP\n4 = ISP\n5 = GR2D\n6 = GR3D\n8 = DISPLAY\n11 = TVO\n9 = DISPLAYB\n12 = DSI\n10 = HDMI",
              8, old_value_t.indmodid, new_value_t.indmodid };
    m_bit_details_model.bits.append(entry);
    entry = { "26: undefined_bits_26_31:6", "", 6, old_value_t.undefined_bits_26_31, new_value_t.undefined_bits_26_31 };
    m_bit_details_model.bits.append(entry);
}

#define NV_CLASS_HOST_INDOFF2FB_OFFSET 0x2C
#define NV_CLASS_HOST_INDOFF2FB_UNDEFMASK 0x00000003
union nv_class_host_indoff2fb_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int indoffset:30;          /* ACCTYPE=FB: framebuffer address */
    };

    u_int32_t reg32;
};

void Host1xDev::fill_nv_class_host_indoff2fb_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const nv_class_host_indoff2fb_u old_value_t = { .reg32 = value };
    const nv_class_host_indoff2fb_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: indoffset:30",
              "ACCTYPE=FB: framebuffer address",
              30, old_value_t.indoffset, new_value_t.indoffset };
    m_bit_details_model.bits.append(entry);
}

#define NV_CLASS_HOST_INDOFF_OFFSET 0x2D
#define NV_CLASS_HOST_INDOFF_UNDEFMASK 0x00000000
union nv_class_host_indoff_u {
    struct {
        unsigned int rwn:1;                 /* Read/write 0 = WRITE 1 = READ */
        unsigned int acctype:1;             /* Access type: indirect register or indirect framebuffer 0 = REG 1 = FB */
        unsigned int indroffset:16;         /* ACCTYPE=REG: register offset ([15:0]) */
        unsigned int indmodid:8;            /* ACCTYPE=REG: register module ID 0 = HOST1X 1 = MPE 2 = VI 3 = EPP 4 = ISP 5 = GR2D 6 = GR3D 8 = DISPLAY 11 = TVO 9 = DISPLAYB 12 = DSI 10 = HDMI */
        unsigned int spool:1;               /* Route return data to spool FIFO, only applicable to reads 0 = DISABLE 1 = ENABLE */
        unsigned int autoinc:1;             /* Auto increment of read/write address 0 = DISABLE 1 = ENABLE */
        unsigned int indbe:4;               /* Byte enables. Will apply to all subsequent data transactions. Not applicable for reads */
    };

    u_int32_t reg32;
};

void Host1xDev::fill_nv_class_host_indoff_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const nv_class_host_indoff_u old_value_t = { .reg32 = value };
    const nv_class_host_indoff_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: rwn:1",
              "Read/write\n0 = WRITE\n1 = READ",
              1, old_value_t.rwn, new_value_t.rwn };
    m_bit_details_model.bits.append(entry);
    entry = { "01: acctype:1",
              "Access type: indirect register or indirect framebuffer\n0 = REG\n1 = FB",
              1, old_value_t.acctype, new_value_t.acctype };
    m_bit_details_model.bits.append(entry);
    entry = { "02: indroffset:16",
              "ACCTYPE=REG: register offset ([15:0])",
              16, old_value_t.indroffset, new_value_t.indroffset };
    m_bit_details_model.bits.append(entry);
    entry = { "18: indmodid:8",
              "ACCTYPE=REG: register module ID\n0 = HOST1X\n1 = MPE\n2 = VI\n3 = EPP\n4 = ISP\n5 = GR2D\n6 = GR3D\n8 = DISPLAY\n11 = TVO\n9 = DISPLAYB\n12 = DSI\n10 = HDMI",
              8, old_value_t.indmodid, new_value_t.indmodid };
    m_bit_details_model.bits.append(entry);
    entry = { "26: spool:1",
              "Route return data to spool FIFO, only applicable to reads\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.spool, new_value_t.spool };
    m_bit_details_model.bits.append(entry);
    entry = { "27: autoinc:1",
              "Auto increment of read/write address\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.autoinc, new_value_t.autoinc };
    m_bit_details_model.bits.append(entry);
    entry = { "28: indbe:4",
              "Byte enables. Will apply to all subsequent data transactions. Not applicable for reads",
              4, old_value_t.indbe, new_value_t.indbe };
    m_bit_details_model.bits.append(entry);
}

#define NV_CLASS_HOST_INDOFFFB_OFFSET 0x2D
#define NV_CLASS_HOST_INDOFFFB_UNDEFMASK 0x00000000
union nv_class_host_indofffb_u {
    struct {
        unsigned int rwn:1;                 /* Read/write 0 = WRITE 1 = READ */
        unsigned int acctype:1;             /* Access type: indirect register or indirect framebuffer 0 = REG 1 = FB */
        unsigned int indoffset:24;          /* ACCTYPE=FB: framebuffer address */
        unsigned int spool:1;               /* Route return data to spool FIFO, only applicable to reads 0 = DISABLE 1 = ENABLE */
        unsigned int autoinc:1;             /* Auto increment of read/write address 0 = DISABLE 1 = ENABLE */
        unsigned int indbe:4;               /* Byte enables. Will apply to all subsequent data transactions. Not applicable for reads */
    };

    u_int32_t reg32;
};

void Host1xDev::fill_nv_class_host_indofffb_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const nv_class_host_indofffb_u old_value_t = { .reg32 = value };
    const nv_class_host_indofffb_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: rwn:1",
              "Read/write\n0 = WRITE\n1 = READ",
              1, old_value_t.rwn, new_value_t.rwn };
    m_bit_details_model.bits.append(entry);
    entry = { "01: acctype:1",
              "Access type: indirect register or indirect framebuffer\n0 = REG\n1 = FB",
              1, old_value_t.acctype, new_value_t.acctype };
    m_bit_details_model.bits.append(entry);
    entry = { "02: indoffset:24",
              "ACCTYPE=FB: framebuffer address",
              24, old_value_t.indoffset, new_value_t.indoffset };
    m_bit_details_model.bits.append(entry);
    entry = { "26: spool:1",
              "Route return data to spool FIFO, only applicable to reads\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.spool, new_value_t.spool };
    m_bit_details_model.bits.append(entry);
    entry = { "27: autoinc:1",
              "Auto increment of read/write address\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.autoinc, new_value_t.autoinc };
    m_bit_details_model.bits.append(entry);
    entry = { "28: indbe:4",
              "Byte enables. Will apply to all subsequent data transactions. Not applicable for reads",
              4, old_value_t.indbe, new_value_t.indbe };
    m_bit_details_model.bits.append(entry);
}

#define NV_CLASS_HOST_INDDATA_OFFSET 0x2E
#define NV_CLASS_HOST_INDDATA_UNDEFMASK 0x00000000
union nv_class_host_inddata_u {
    struct {
        unsigned int inddata:32;            /* read or write data */
    };

    u_int32_t reg32;
};

void Host1xDev::fill_nv_class_host_inddata_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const nv_class_host_inddata_u old_value_t = { .reg32 = value };
    const nv_class_host_inddata_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: inddata:32",
              "read or write data",
              32, old_value_t.inddata, new_value_t.inddata };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "These registers, when written, either writes to the data to the INDOFFSET in INDOFF or triggers a read of the offset at INDOFFSET. This is an array of 31 identical register entries; the register fields below apply to each entry.";
}



bool Host1xDev::is_offset_valid(const u_int32_t &offset) const
{
    switch (offset) {
    case NV_CLASS_HOST_INCR_SYNCPT_OFFSET:
    case NV_CLASS_HOST_INCR_SYNCPT_CNTRL_OFFSET:
    case NV_CLASS_HOST_INCR_SYNCPT_ERROR_OFFSET:
    case NV_CLASS_HOST_WAIT_SYNCPT_OFFSET:
    case NV_CLASS_HOST_WAIT_SYNCPT_BASE_OFFSET:
    case NV_CLASS_HOST_WAIT_SYNCPT_INCR_OFFSET:
    case NV_CLASS_HOST_LOAD_SYNCPT_BASE_OFFSET:
    case NV_CLASS_HOST_INCR_SYNCPT_BASE_OFFSET:
    case NV_CLASS_HOST_DELAY_USEC_OFFSET:
    case NV_CLASS_HOST_TICKCOUNT_HI_OFFSET:
    case NV_CLASS_HOST_TICKCOUNT_LO_OFFSET:
    case NV_CLASS_HOST_TICKCTRL_OFFSET:
    case NV_CLASS_HOST_INDCTRL_OFFSET:
    case NV_CLASS_HOST_INDOFF2_OFFSET:
    case NV_CLASS_HOST_INDOFF_OFFSET:
    case NV_CLASS_HOST_INDDATA_OFFSET:
        return true;
    default:
        break;
    }

    return false;
}

bool Host1xDev::is_undef_changed(const u_int32_t &offset,
                                           const u_int32_t &value,
                                           const u_int32_t &new_value) const
{
    switch (offset) {
    case NV_CLASS_HOST_INCR_SYNCPT_OFFSET:
        if ((value ^ new_value) & NV_CLASS_HOST_INCR_SYNCPT_UNDEFMASK)
            return true;
        break;
    case NV_CLASS_HOST_INCR_SYNCPT_CNTRL_OFFSET:
        if ((value ^ new_value) & NV_CLASS_HOST_INCR_SYNCPT_CNTRL_UNDEFMASK)
            return true;
        break;
    case NV_CLASS_HOST_INCR_SYNCPT_ERROR_OFFSET:
        if ((value ^ new_value) & NV_CLASS_HOST_INCR_SYNCPT_ERROR_UNDEFMASK)
            return true;
        break;
    case NV_CLASS_HOST_WAIT_SYNCPT_OFFSET:
        if ((value ^ new_value) & NV_CLASS_HOST_WAIT_SYNCPT_UNDEFMASK)
            return true;
        break;
    case NV_CLASS_HOST_WAIT_SYNCPT_BASE_OFFSET:
        if ((value ^ new_value) & NV_CLASS_HOST_WAIT_SYNCPT_BASE_UNDEFMASK)
            return true;
        break;
    case NV_CLASS_HOST_WAIT_SYNCPT_INCR_OFFSET:
        if ((value ^ new_value) & NV_CLASS_HOST_WAIT_SYNCPT_INCR_UNDEFMASK)
            return true;
        break;
    case NV_CLASS_HOST_LOAD_SYNCPT_BASE_OFFSET:
        if ((value ^ new_value) & NV_CLASS_HOST_LOAD_SYNCPT_BASE_UNDEFMASK)
            return true;
        break;
    case NV_CLASS_HOST_INCR_SYNCPT_BASE_OFFSET:
        if ((value ^ new_value) & NV_CLASS_HOST_INCR_SYNCPT_BASE_UNDEFMASK)
            return true;
        break;
    case NV_CLASS_HOST_DELAY_USEC_OFFSET:
        if ((value ^ new_value) & NV_CLASS_HOST_DELAY_USEC_UNDEFMASK)
            return true;
        break;
    case NV_CLASS_HOST_TICKCOUNT_HI_OFFSET:
        if ((value ^ new_value) & NV_CLASS_HOST_TICKCOUNT_HI_UNDEFMASK)
            return true;
        break;
    case NV_CLASS_HOST_TICKCOUNT_LO_OFFSET:
        if ((value ^ new_value) & NV_CLASS_HOST_TICKCOUNT_LO_UNDEFMASK)
            return true;
        break;
    case NV_CLASS_HOST_TICKCTRL_OFFSET:
        if ((value ^ new_value) & NV_CLASS_HOST_TICKCTRL_UNDEFMASK)
            return true;
        break;
    case NV_CLASS_HOST_INDCTRL_OFFSET:
        if ((value ^ new_value) & NV_CLASS_HOST_INDCTRL_UNDEFMASK)
            return true;
        break;
    case NV_CLASS_HOST_INDOFF2_OFFSET:
        if ((value ^ new_value) & NV_CLASS_HOST_INDOFF2_UNDEFMASK)
            return true;
        break;
    case NV_CLASS_HOST_INDOFF_OFFSET:
        if ((value ^ new_value) & NV_CLASS_HOST_INDOFF_UNDEFMASK)
            return true;
        break;
    case NV_CLASS_HOST_INDDATA_OFFSET:
        if ((value ^ new_value) & NV_CLASS_HOST_INDDATA_UNDEFMASK)
            return true;
        break;

    default:
        break;
    }

    return false;
}


QString Host1xDev::get_register_name(const log_entry &entry) const
{
    switch (entry.offset) {
    case NV_CLASS_HOST_INCR_SYNCPT_OFFSET:
        return QString("NV_CLASS_HOST_INCR_SYNCPT");
    case NV_CLASS_HOST_INCR_SYNCPT_CNTRL_OFFSET:
        return QString("NV_CLASS_HOST_INCR_SYNCPT_CNTRL");
    case NV_CLASS_HOST_INCR_SYNCPT_ERROR_OFFSET:
        return QString("NV_CLASS_HOST_INCR_SYNCPT_ERROR");
    case NV_CLASS_HOST_WAIT_SYNCPT_OFFSET:
        return QString("NV_CLASS_HOST_WAIT_SYNCPT");
    case NV_CLASS_HOST_WAIT_SYNCPT_BASE_OFFSET:
        return QString("NV_CLASS_HOST_WAIT_SYNCPT_BASE");
    case NV_CLASS_HOST_WAIT_SYNCPT_INCR_OFFSET:
        return QString("NV_CLASS_HOST_WAIT_SYNCPT_INCR");
    case NV_CLASS_HOST_LOAD_SYNCPT_BASE_OFFSET:
        return QString("NV_CLASS_HOST_LOAD_SYNCPT_BASE");
    case NV_CLASS_HOST_INCR_SYNCPT_BASE_OFFSET:
        return QString("NV_CLASS_HOST_INCR_SYNCPT_BASE");
    case NV_CLASS_HOST_DELAY_USEC_OFFSET:
        return QString("NV_CLASS_HOST_DELAY_USEC");
    case NV_CLASS_HOST_TICKCOUNT_HI_OFFSET:
        return QString("NV_CLASS_HOST_TICKCOUNT_HI");
    case NV_CLASS_HOST_TICKCOUNT_LO_OFFSET:
        return QString("NV_CLASS_HOST_TICKCOUNT_LO");
    case NV_CLASS_HOST_TICKCTRL_OFFSET:
        return QString("NV_CLASS_HOST_TICKCTRL");
    case NV_CLASS_HOST_INDCTRL_OFFSET:
        return QString("NV_CLASS_HOST_INDCTRL");
    case NV_CLASS_HOST_INDOFF2_OFFSET:
        return QString("NV_CLASS_HOST_INDOFF2");
    case NV_CLASS_HOST_INDOFF_OFFSET:
        return QString("NV_CLASS_HOST_INDOFF");
    case NV_CLASS_HOST_INDDATA_OFFSET:
        return QString("NV_CLASS_HOST_INDDATA");

    default:
        break;
    }

    qDebug() << QString().sprintf("HOST1X: %s: Ooops... 0x%x", __func__, entry.offset);

    return QString().sprintf("Ooops... @0x%X", entry.offset);
}

void Host1xDev::fill_bits_details(const u_int32_t &offset,
                                      const u_int32_t &value, const u_int32_t &new_value)
{
    static int acctype = 0;

    switch (offset) {
    case NV_CLASS_HOST_INCR_SYNCPT_OFFSET:
        fill_nv_class_host_incr_syncpt_details(value, new_value);
        break;
    case NV_CLASS_HOST_INCR_SYNCPT_CNTRL_OFFSET:
        fill_nv_class_host_incr_syncpt_cntrl_details(value, new_value);
        break;
    case NV_CLASS_HOST_INCR_SYNCPT_ERROR_OFFSET:
        fill_nv_class_host_incr_syncpt_error_details(value, new_value);
        break;
    case NV_CLASS_HOST_WAIT_SYNCPT_OFFSET:
        fill_nv_class_host_wait_syncpt_details(value, new_value);
        break;
    case NV_CLASS_HOST_WAIT_SYNCPT_BASE_OFFSET:
        fill_nv_class_host_wait_syncpt_base_details(value, new_value);
        break;
    case NV_CLASS_HOST_WAIT_SYNCPT_INCR_OFFSET:
        fill_nv_class_host_wait_syncpt_incr_details(value, new_value);
        break;
    case NV_CLASS_HOST_LOAD_SYNCPT_BASE_OFFSET:
        fill_nv_class_host_load_syncpt_base_details(value, new_value);
        break;
    case NV_CLASS_HOST_INCR_SYNCPT_BASE_OFFSET:
        fill_nv_class_host_incr_syncpt_base_details(value, new_value);
        break;
    case NV_CLASS_HOST_DELAY_USEC_OFFSET:
        fill_nv_class_host_delay_usec_details(value, new_value);
        break;
    case NV_CLASS_HOST_TICKCOUNT_HI_OFFSET:
        fill_nv_class_host_tickcount_hi_details(value, new_value);
        break;
    case NV_CLASS_HOST_TICKCOUNT_LO_OFFSET:
        fill_nv_class_host_tickcount_lo_details(value, new_value);
        break;
    case NV_CLASS_HOST_TICKCTRL_OFFSET:
        fill_nv_class_host_tickctrl_details(value, new_value);
        break;
    case NV_CLASS_HOST_INDCTRL_OFFSET:
        fill_nv_class_host_indctrl_details(value, new_value);
        break;
    case NV_CLASS_HOST_INDOFF2_OFFSET:
        if (acctype)
            fill_nv_class_host_indoff2fb_details(value, new_value);
        else
            fill_nv_class_host_indoff2_details(value, new_value);
        break;
    case NV_CLASS_HOST_INDOFF_OFFSET:
        if (new_value & 2) {
            acctype = 1;
            fill_nv_class_host_indofffb_details(value, new_value);
        } else {
            acctype = 0;
            fill_nv_class_host_indoff_details(value, new_value);
        }
        break;
    case NV_CLASS_HOST_INDDATA_OFFSET:
        fill_nv_class_host_inddata_details(value, new_value);
        break;

    default:
        m_bit_details_model.bits.clear();
        break;
    }
}
