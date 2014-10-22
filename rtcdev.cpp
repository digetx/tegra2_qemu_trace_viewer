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

#include "rtcdev.h"

#include <QDebug>

RtcDev::RtcDev(QObject *parent) :
    Device(parent)
{
}

#define CONTROL_OFFSET 0x0
#define CONTROL_UNDEFMASK 0xFFFFFFFE
union control_u {
    struct {
        unsigned int wr_sec_cnt:1;          /* When set, writes to SECONDS counter are disabled. can only cleared by resetting the RTC module  0 = DISABLE 1 = ENABLE */
        unsigned int undefined_bits_1_31:31;
    };

    u_int32_t reg32;
};

void RtcDev::fill_control_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const control_u old_value_t = { .reg32 = value };
    const control_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: wr_sec_cnt:1",
              "When set, writes to SECONDS counter are disabled. can only cleared by resetting the RTC module \n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.wr_sec_cnt, new_value_t.wr_sec_cnt };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_31:31", "", 31, old_value_t.undefined_bits_1_31, new_value_t.undefined_bits_1_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Control register.";
}

#define BUSY_OFFSET 0x4
#define BUSY_UNDEFMASK 0xFFFFFFFE
union busy_u {
    struct {
        unsigned int status:1;              /* This bit is set when a write is initiated on the APB side. It is cleared once the write completes in RTC 32KHz clock domain which could be several thousands of APB clocks. This must be IDLE before a write is initiated. Note that this bit is only for writes. 0 = IDLE 1 = BUSY */
        unsigned int undefined_bits_1_31:31;
    };

    u_int32_t reg32;
};

void RtcDev::fill_busy_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const busy_u old_value_t = { .reg32 = value };
    const busy_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: status:1",
              "This bit is set when a write is initiated on the APB side. It is cleared once the write completes in RTC 32KHz clock domain which could be several thousands of APB clocks. This must be IDLE before a write is initiated. Note that this bit is only for writes.\n0 = IDLE\n1 = BUSY",
              1, old_value_t.status, new_value_t.status };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_31:31", "", 31, old_value_t.undefined_bits_1_31, new_value_t.undefined_bits_1_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Busy register.";
}

#define SECONDS_OFFSET 0x8
#define SECONDS_UNDEFMASK 0x00000000
union seconds_u {
    struct {
        unsigned int seconds:32;            /* seconds counter is incremented for every 1000 milli-seconds */
    };

    u_int32_t reg32;
};

void RtcDev::fill_seconds_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const seconds_u old_value_t = { .reg32 = value };
    const seconds_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: seconds:32",
              "seconds counter is incremented for every 1000 milli-seconds",
              32, old_value_t.seconds, new_value_t.seconds };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Seconds counter register. SECONDS register is copied over to APB side every eight 32KHz clocks (~250uS). Because of this, performing a read immediately after a write might return old value. This covers 49710.26 Days (or) 136.192 Years of 365 days each";
}

#define SHADOW_SECONDS_OFFSET 0xC
#define SHADOW_SECONDS_UNDEFMASK 0x00000000
union shadow_seconds_u {
    struct {
        unsigned int shadow_seconds:32;     /* A snapshot of the SECONDS counter is taken whenever there is a read to MILLI_SECONDS Register */
    };

    u_int32_t reg32;
};

void RtcDev::fill_shadow_seconds_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const shadow_seconds_u old_value_t = { .reg32 = value };
    const shadow_seconds_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: shadow_seconds:32",
              "A snapshot of the SECONDS counter is taken whenever there is a read to MILLI_SECONDS Register",
              32, old_value_t.shadow_seconds, new_value_t.shadow_seconds };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Shadowed seconds counter register. Shadow SECONDS register is updated over to APB side whenever there is a read to milliseconds counter. Since the software cannot read both registers at any given point of time, the Seconds register is snapshotted in this Register. If the software needs to read two registers, then it should read MILLI_SECONDS Register and then this Register. It should not read the SECONDS register, as it contains the updated value.";
}

#define MILLI_SECONDS_OFFSET 0x10
#define MILLI_SECONDS_UNDEFMASK 0xFFFFFC00
union milli_seconds_u {
    struct {
        unsigned int milli_seconds:10;      /* milliseconds counter is incremented using Bresenham algorithm */
        unsigned int undefined_bits_10_31:22;
    };

    u_int32_t reg32;
};

void RtcDev::fill_milli_seconds_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const milli_seconds_u old_value_t = { .reg32 = value };
    const milli_seconds_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: milli_seconds:10",
              "milliseconds counter is incremented using Bresenham algorithm",
              10, old_value_t.milli_seconds, new_value_t.milli_seconds };
    m_bit_details_model.bits.append(entry);
    entry = { "10: undefined_bits_10_31:22", "", 22, old_value_t.undefined_bits_10_31, new_value_t.undefined_bits_10_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Milliseconds counter register. Milli SECONDS register is copied over to APB side every eight 32KHz clocks (~250uS). Because of this, performing a read immediately after a write might return old value.";
}

#define SECONDS_ALARM0_OFFSET 0x14
#define SECONDS_ALARM0_UNDEFMASK 0x00000000
union seconds_alarm0_u {
    struct {
        unsigned int secs_match_value:32;   /* match value to trigger the alarm */
    };

    u_int32_t reg32;
};

void RtcDev::fill_seconds_alarm0_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const seconds_alarm0_u old_value_t = { .reg32 = value };
    const seconds_alarm0_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: secs_match_value:32",
              "match value to trigger the alarm",
              32, old_value_t.secs_match_value, new_value_t.secs_match_value };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Seconds alarm0 register. When the value in this register matches the seconds counter, corresponding interrupt status bit is set.\nIf enabled, the interrupt line is asserted. A value of zero disables the alarm.";
}

#define SECONDS_ALARM1_OFFSET 0x18
#define SECONDS_ALARM1_UNDEFMASK 0x00000000
union seconds_alarm1_u {
    struct {
        unsigned int secs_match_value:32;   /* match value to trigger the alarm */
    };

    u_int32_t reg32;
};

void RtcDev::fill_seconds_alarm1_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const seconds_alarm1_u old_value_t = { .reg32 = value };
    const seconds_alarm1_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: secs_match_value:32",
              "match value to trigger the alarm",
              32, old_value_t.secs_match_value, new_value_t.secs_match_value };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Seconds alarm1 register. When the value in this register matches the seconds counter, corresponding interrupt status bit is set.\nIf enabled, the interrupt line is asserted. A value of zero disables the alarm.";
}

#define MILLI_SECONDS_ALARM_OFFSET 0x1C
#define MILLI_SECONDS_ALARM_UNDEFMASK 0xFFFFFC00
union milli_seconds_alarm_u {
    struct {
        unsigned int msec_match_value:10;   /* milliseconds match value */
        unsigned int undefined_bits_10_31:22;
    };

    u_int32_t reg32;
};

void RtcDev::fill_milli_seconds_alarm_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const milli_seconds_alarm_u old_value_t = { .reg32 = value };
    const milli_seconds_alarm_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: msec_match_value:10",
              "milliseconds match value",
              10, old_value_t.msec_match_value, new_value_t.msec_match_value };
    m_bit_details_model.bits.append(entry);
    entry = { "10: undefined_bits_10_31:22", "", 22, old_value_t.undefined_bits_10_31, new_value_t.undefined_bits_10_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Milliseconds alarm register. When the value in this register matches the milliseconds counter, corresponding interrupt status bit is set.\nIf enabled, the interrupt line is asserted. A value of zero disables the alarm.";
}

#define SECONDS_COUNTDOWN_ALARM_OFFSET 0x20
#define SECONDS_COUNTDOWN_ALARM_UNDEFMASK 0x00000000
union seconds_countdown_alarm_u {
    struct {
        unsigned int value:30;              /* number of milliseconds to countdown */
        unsigned int repeat:1;              /* repeat bit for the countdown operation  0 = DISABLED 1 = ENABLED */
        unsigned int enable:1;              /* enable bit for the countdown operation. If repeat is not set, this bit is cleared once the internal counters counts down to specified value. 0 = DISABLED 1 = ENABLED */
    };

    u_int32_t reg32;
};

void RtcDev::fill_seconds_countdown_alarm_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const seconds_countdown_alarm_u old_value_t = { .reg32 = value };
    const seconds_countdown_alarm_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: value:30",
              "number of milliseconds to countdown",
              30, old_value_t.value, new_value_t.value };
    m_bit_details_model.bits.append(entry);
    entry = { "30: repeat:1",
              "repeat bit for the countdown operation \n0 = DISABLED\n1 = ENABLED",
              1, old_value_t.repeat, new_value_t.repeat };
    m_bit_details_model.bits.append(entry);
    entry = { "31: enable:1",
              "enable bit for the countdown operation. If repeat is not set, this bit is cleared once the internal counters counts down to specified value.\n0 = DISABLED\n1 = ENABLED",
              1, old_value_t.enable, new_value_t.enable };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Countdown alarm registers. If ENABLE_ENABLED, an internal counter is loaded with VALUE and counted down. The interrupt bit corresponding to the countdown_alarm_0 is set after the specified number of seconds have elapsed.\nThe interrupt bit corresponding to the countdown_alarm_1 is set after the specified number of milliseconds have elapsed. If REPEAT is ENABLED, the countdown operation is performed repeatedly.";
}

#define MILLI_SECONDS_COUNTDOWN_ALARM_OFFSET 0x24
#define MILLI_SECONDS_COUNTDOWN_ALARM_UNDEFMASK 0x00000000
union milli_seconds_countdown_alarm_u {
    struct {
        unsigned int value:30;              /* number of milliseconds to countdown */
        unsigned int repeat:1;              /* repeat bit for the countdown operation  0 = DISABLED 1 = ENABLED */
        unsigned int enable:1;              /* enable bit for the countdown operation. If repeat is not set, this bit is cleared once the internal counters counts down to specified value. 0 = DISABLED 1 = ENABLED */
    };

    u_int32_t reg32;
};

void RtcDev::fill_milli_seconds_countdown_alarm_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const milli_seconds_countdown_alarm_u old_value_t = { .reg32 = value };
    const milli_seconds_countdown_alarm_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: value:30",
              "number of milliseconds to countdown",
              30, old_value_t.value, new_value_t.value };
    m_bit_details_model.bits.append(entry);
    entry = { "30: repeat:1",
              "repeat bit for the countdown operation \n0 = DISABLED\n1 = ENABLED",
              1, old_value_t.repeat, new_value_t.repeat };
    m_bit_details_model.bits.append(entry);
    entry = { "31: enable:1",
              "enable bit for the countdown operation. If repeat is not set, this bit is cleared once the internal counters counts down to specified value.\n0 = DISABLED\n1 = ENABLED",
              1, old_value_t.enable, new_value_t.enable };
    m_bit_details_model.bits.append(entry);
}

#define INTR_MASK_OFFSET 0x28
#define INTR_MASK_UNDEFMASK 0xFFFFFFE0
union intr_mask_u {
    struct {
        unsigned int sec_alarm0:1;
        unsigned int sec_alarm1:1;
        unsigned int msec_alarm:1;
        unsigned int sec_cdn_alarm:1;
        unsigned int msec_cdn_alarm:1;
        unsigned int undefined_bits_5_31:27;
    };

    u_int32_t reg32;
};

void RtcDev::fill_intr_mask_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const intr_mask_u old_value_t = { .reg32 = value };
    const intr_mask_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: sec_alarm0:1", "", 1, old_value_t.sec_alarm0, new_value_t.sec_alarm0 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: sec_alarm1:1", "", 1, old_value_t.sec_alarm1, new_value_t.sec_alarm1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: msec_alarm:1", "", 1, old_value_t.msec_alarm, new_value_t.msec_alarm };
    m_bit_details_model.bits.append(entry);
    entry = { "03: sec_cdn_alarm:1", "", 1, old_value_t.sec_cdn_alarm, new_value_t.sec_cdn_alarm };
    m_bit_details_model.bits.append(entry);
    entry = { "04: msec_cdn_alarm:1", "", 1, old_value_t.msec_cdn_alarm, new_value_t.msec_cdn_alarm };
    m_bit_details_model.bits.append(entry);
    entry = { "05: undefined_bits_5_31:27", "", 27, old_value_t.undefined_bits_5_31, new_value_t.undefined_bits_5_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Interrupt mask register. This register stores the masks for the interrupts. If a bit is set 1 and the corresponding interrupt condition is satisfied, interrupt line to system interrupt controller is asserted.";
}

#define INTR_STATUS_OFFSET 0x2C
#define INTR_STATUS_UNDEFMASK 0xFFFFFFE0
union intr_status_u {
    struct {
        unsigned int sec_alarm0:1;
        unsigned int sec_alarm1:1;
        unsigned int msec_alarm:1;
        unsigned int sec_cdn_alarm:1;
        unsigned int msec_cdn_alarm:1;
        unsigned int undefined_bits_5_31:27;
    };

    u_int32_t reg32;
};

void RtcDev::fill_intr_status_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const intr_status_u old_value_t = { .reg32 = value };
    const intr_status_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: sec_alarm0:1", "", 1, old_value_t.sec_alarm0, new_value_t.sec_alarm0 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: sec_alarm1:1", "", 1, old_value_t.sec_alarm1, new_value_t.sec_alarm1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: msec_alarm:1", "", 1, old_value_t.msec_alarm, new_value_t.msec_alarm };
    m_bit_details_model.bits.append(entry);
    entry = { "03: sec_cdn_alarm:1", "", 1, old_value_t.sec_cdn_alarm, new_value_t.sec_cdn_alarm };
    m_bit_details_model.bits.append(entry);
    entry = { "04: msec_cdn_alarm:1", "", 1, old_value_t.msec_cdn_alarm, new_value_t.msec_cdn_alarm };
    m_bit_details_model.bits.append(entry);
    entry = { "05: undefined_bits_5_31:27", "", 27, old_value_t.undefined_bits_5_31, new_value_t.undefined_bits_5_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Interrupt status register. Bits in this register are high after the interrupt condition is satisfied.\n A write to this register clears the bits corresponding to the data bits that are high in the write data.";
}

#define INTR_SOURCE_OFFSET 0x30
#define INTR_SOURCE_UNDEFMASK 0xFFFFFFE0
union intr_source_u {
    struct {
        unsigned int sec_alarm0:1;
        unsigned int sec_alarm1:1;
        unsigned int msec_alarm:1;
        unsigned int sec_cdn_alarm:1;
        unsigned int msec_cdn_alarm:1;
        unsigned int undefined_bits_5_31:27;
    };

    u_int32_t reg32;
};

void RtcDev::fill_intr_source_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const intr_source_u old_value_t = { .reg32 = value };
    const intr_source_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: sec_alarm0:1", "", 1, old_value_t.sec_alarm0, new_value_t.sec_alarm0 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: sec_alarm1:1", "", 1, old_value_t.sec_alarm1, new_value_t.sec_alarm1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: msec_alarm:1", "", 1, old_value_t.msec_alarm, new_value_t.msec_alarm };
    m_bit_details_model.bits.append(entry);
    entry = { "03: sec_cdn_alarm:1", "", 1, old_value_t.sec_cdn_alarm, new_value_t.sec_cdn_alarm };
    m_bit_details_model.bits.append(entry);
    entry = { "04: msec_cdn_alarm:1", "", 1, old_value_t.msec_cdn_alarm, new_value_t.msec_cdn_alarm };
    m_bit_details_model.bits.append(entry);
    entry = { "05: undefined_bits_5_31:27", "", 27, old_value_t.undefined_bits_5_31, new_value_t.undefined_bits_5_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Interrupt source register. This is a read-only register which returns the AND of interrupt source and interrupt mask registers.";
}

#define INTR_SET_OFFSET 0x34
#define INTR_SET_UNDEFMASK 0xFFFFFFE0
union intr_set_u {
    struct {
        unsigned int sec_alarm0:1;
        unsigned int sec_alarm1:1;
        unsigned int msec_alarm:1;
        unsigned int sec_cdn_alarm:1;
        unsigned int msec_cdn_alarm:1;
        unsigned int undefined_bits_5_31:27;
    };

    u_int32_t reg32;
};

void RtcDev::fill_intr_set_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const intr_set_u old_value_t = { .reg32 = value };
    const intr_set_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: sec_alarm0:1", "", 1, old_value_t.sec_alarm0, new_value_t.sec_alarm0 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: sec_alarm1:1", "", 1, old_value_t.sec_alarm1, new_value_t.sec_alarm1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: msec_alarm:1", "", 1, old_value_t.msec_alarm, new_value_t.msec_alarm };
    m_bit_details_model.bits.append(entry);
    entry = { "03: sec_cdn_alarm:1", "", 1, old_value_t.sec_cdn_alarm, new_value_t.sec_cdn_alarm };
    m_bit_details_model.bits.append(entry);
    entry = { "04: msec_cdn_alarm:1", "", 1, old_value_t.msec_cdn_alarm, new_value_t.msec_cdn_alarm };
    m_bit_details_model.bits.append(entry);
    entry = { "05: undefined_bits_5_31:27", "", 27, old_value_t.undefined_bits_5_31, new_value_t.undefined_bits_5_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Interrupt set register. This is a write-only register which can be used to set the interrupt status bit.\nA write to this register causes the bits in status register to be set if the corresponding bit in write data is 1'b1. Read always returns 'h0.";
}

#define CORRECTION_FACTOR_OFFSET 0x38
#define CORRECTION_FACTOR_UNDEFMASK 0xFFFFFC00
union correction_factor_u {
    struct {
        unsigned int ppm:9;
        unsigned int direction:1;           /* 0 = DECREMENT 1 = INCREMENT */
        unsigned int undefined_bits_10_31:22;
    };

    u_int32_t reg32;
};

void RtcDev::fill_correction_factor_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const correction_factor_u old_value_t = { .reg32 = value };
    const correction_factor_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: ppm:9", "", 9, old_value_t.ppm, new_value_t.ppm };
    m_bit_details_model.bits.append(entry);
    entry = { "09: direction:1",
              "0 = DECREMENT\n1 = INCREMENT",
              1, old_value_t.direction, new_value_t.direction };
    m_bit_details_model.bits.append(entry);
    entry = { "10: undefined_bits_10_31:22", "", 22, old_value_t.undefined_bits_10_31, new_value_t.undefined_bits_10_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Correction factor (digital trimming) register. Support is for +/- 500ppm (+/- 50 ppm is maximum)";
}

bool RtcDev::is_offset_valid(const u_int32_t &offset) const
{
    switch (offset) {
    case CONTROL_OFFSET:
    case BUSY_OFFSET:
    case SECONDS_OFFSET:
    case SHADOW_SECONDS_OFFSET:
    case MILLI_SECONDS_OFFSET:
    case SECONDS_ALARM0_OFFSET:
    case SECONDS_ALARM1_OFFSET:
    case MILLI_SECONDS_ALARM_OFFSET:
    case SECONDS_COUNTDOWN_ALARM_OFFSET:
    case MILLI_SECONDS_COUNTDOWN_ALARM_OFFSET:
    case INTR_MASK_OFFSET:
    case INTR_STATUS_OFFSET:
    case INTR_SOURCE_OFFSET:
    case INTR_SET_OFFSET:
    case CORRECTION_FACTOR_OFFSET:
        return true;
    default:
        break;
    }

    return false;
}

bool RtcDev::is_undef_changed(const u_int32_t &offset,
                                           const u_int32_t &value,
                                           const u_int32_t &new_value) const
{
    switch (offset) {
    case CONTROL_OFFSET:
        if ((value ^ new_value) & CONTROL_UNDEFMASK)
            return true;
        break;
    case BUSY_OFFSET:
        if ((value ^ new_value) & BUSY_UNDEFMASK)
            return true;
        break;
    case SECONDS_OFFSET:
        if ((value ^ new_value) & SECONDS_UNDEFMASK)
            return true;
        break;
    case SHADOW_SECONDS_OFFSET:
        if ((value ^ new_value) & SHADOW_SECONDS_UNDEFMASK)
            return true;
        break;
    case MILLI_SECONDS_OFFSET:
        if ((value ^ new_value) & MILLI_SECONDS_UNDEFMASK)
            return true;
        break;
    case SECONDS_ALARM0_OFFSET:
        if ((value ^ new_value) & SECONDS_ALARM0_UNDEFMASK)
            return true;
        break;
    case SECONDS_ALARM1_OFFSET:
        if ((value ^ new_value) & SECONDS_ALARM1_UNDEFMASK)
            return true;
        break;
    case MILLI_SECONDS_ALARM_OFFSET:
        if ((value ^ new_value) & MILLI_SECONDS_ALARM_UNDEFMASK)
            return true;
        break;
    case SECONDS_COUNTDOWN_ALARM_OFFSET:
        if ((value ^ new_value) & SECONDS_COUNTDOWN_ALARM_UNDEFMASK)
            return true;
        break;
    case MILLI_SECONDS_COUNTDOWN_ALARM_OFFSET:
        if ((value ^ new_value) & MILLI_SECONDS_COUNTDOWN_ALARM_UNDEFMASK)
            return true;
        break;
    case INTR_MASK_OFFSET:
        if ((value ^ new_value) & INTR_MASK_UNDEFMASK)
            return true;
        break;
    case INTR_STATUS_OFFSET:
        if ((value ^ new_value) & INTR_STATUS_UNDEFMASK)
            return true;
        break;
    case INTR_SOURCE_OFFSET:
        if ((value ^ new_value) & INTR_SOURCE_UNDEFMASK)
            return true;
        break;
    case INTR_SET_OFFSET:
        if ((value ^ new_value) & INTR_SET_UNDEFMASK)
            return true;
        break;
    case CORRECTION_FACTOR_OFFSET:
        if ((value ^ new_value) & CORRECTION_FACTOR_UNDEFMASK)
            return true;
        break;

    default:
        break;
    }

    return false;
}

QString RtcDev::get_register_name(const log_entry &entry) const
{
    switch (entry.offset) {
    case CONTROL_OFFSET:
        return QString("CONTROL");
    case BUSY_OFFSET:
        return QString("BUSY");
    case SECONDS_OFFSET:
        return QString("SECONDS");
    case SHADOW_SECONDS_OFFSET:
        return QString("SHADOW_SECONDS");
    case MILLI_SECONDS_OFFSET:
        return QString("MILLI_SECONDS");
    case SECONDS_ALARM0_OFFSET:
        return QString("SECONDS_ALARM0");
    case SECONDS_ALARM1_OFFSET:
        return QString("SECONDS_ALARM1");
    case MILLI_SECONDS_ALARM_OFFSET:
        return QString("MILLI_SECONDS_ALARM");
    case SECONDS_COUNTDOWN_ALARM_OFFSET:
        return QString("SECONDS_COUNTDOWN_ALARM");
    case MILLI_SECONDS_COUNTDOWN_ALARM_OFFSET:
        return QString("MILLI_SECONDS_COUNTDOWN_ALARM");
    case INTR_MASK_OFFSET:
        return QString("INTR_MASK");
    case INTR_STATUS_OFFSET:
        return QString("INTR_STATUS");
    case INTR_SOURCE_OFFSET:
        return QString("INTR_SOURCE");
    case INTR_SET_OFFSET:
        return QString("INTR_SET");
    case CORRECTION_FACTOR_OFFSET:
        return QString("CORRECTION_FACTOR");

    default:
        break;
    }

    qDebug() << QString().sprintf("RTC: %s: Ooops... 0x%x", __func__, entry.offset);

    return QString().sprintf("Ooops... @0x%X", entry.offset);
}

void RtcDev::fill_bits_details(const u_int32_t &offset,
                                      const u_int32_t &value, const u_int32_t &new_value)
{
    switch (offset) {
    case CONTROL_OFFSET:
        fill_control_details(value, new_value);
        break;
    case BUSY_OFFSET:
        fill_busy_details(value, new_value);
        break;
    case SECONDS_OFFSET:
        fill_seconds_details(value, new_value);
        break;
    case SHADOW_SECONDS_OFFSET:
        fill_shadow_seconds_details(value, new_value);
        break;
    case MILLI_SECONDS_OFFSET:
        fill_milli_seconds_details(value, new_value);
        break;
    case SECONDS_ALARM0_OFFSET:
        fill_seconds_alarm0_details(value, new_value);
        break;
    case SECONDS_ALARM1_OFFSET:
        fill_seconds_alarm1_details(value, new_value);
        break;
    case MILLI_SECONDS_ALARM_OFFSET:
        fill_milli_seconds_alarm_details(value, new_value);
        break;
    case SECONDS_COUNTDOWN_ALARM_OFFSET:
        fill_seconds_countdown_alarm_details(value, new_value);
        break;
    case MILLI_SECONDS_COUNTDOWN_ALARM_OFFSET:
        fill_milli_seconds_countdown_alarm_details(value, new_value);
        break;
    case INTR_MASK_OFFSET:
        fill_intr_mask_details(value, new_value);
        break;
    case INTR_STATUS_OFFSET:
        fill_intr_status_details(value, new_value);
        break;
    case INTR_SOURCE_OFFSET:
        fill_intr_source_details(value, new_value);
        break;
    case INTR_SET_OFFSET:
        fill_intr_set_details(value, new_value);
        break;
    case CORRECTION_FACTOR_OFFSET:
        fill_correction_factor_details(value, new_value);
        break;

    default:
        m_bit_details_model.bits.clear();
        break;
    }
}
