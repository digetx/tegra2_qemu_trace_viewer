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

#include "timer_usdev.h"

#include <QDebug>

#define CNTR_1US_OFFSET 0x0
#define CNTR_1US_UNDEFMASK 0x00000000
union cntr_1us_u {
    struct {
        unsigned int low_value:16;          /* Elapsed time in micro-second */
        unsigned int high_value:16;         /* Elapsed time in micro-second */
    };

    u_int32_t reg32;
};

void Timer_usDev::fill_cntr_1us_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const cntr_1us_u old_value_t = { .reg32 = value };
    const cntr_1us_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: low_value:16",
              "Elapsed time in micro-second",
              16, old_value_t.low_value, new_value_t.low_value };
    m_bit_details_model.bits.append(entry);
    entry = { "16: high_value:16",
              "Elapsed time in micro-second",
              16, old_value_t.high_value, new_value_t.high_value };
    m_bit_details_model.bits.append(entry);
}

#define USEC_CFG_OFFSET 0x4
#define USEC_CFG_UNDEFMASK 0xFFFF0000
union usec_cfg_u {
    struct {
        unsigned int usec_divisor:8;        /* usec divisor */
        unsigned int usec_dividend:8;       /* usec dividend */
        unsigned int undefined_bits_16_31:16;
    };

    u_int32_t reg32;
};

void Timer_usDev::fill_usec_cfg_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const usec_cfg_u old_value_t = { .reg32 = value };
    const usec_cfg_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: usec_divisor:8",
              "usec divisor",
              8, old_value_t.usec_divisor, new_value_t.usec_divisor };
    m_bit_details_model.bits.append(entry);
    entry = { "08: usec_dividend:8",
              "usec dividend",
              8, old_value_t.usec_dividend, new_value_t.usec_dividend };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_31:16", "", 16, old_value_t.undefined_bits_16_31, new_value_t.undefined_bits_16_31 };
    m_bit_details_model.bits.append(entry);
}

#define CNTR_FREEZE_OFFSET 0x3C
#define CNTR_FREEZE_UNDEFMASK 0xFFFFFFEC
union cntr_freeze_u {
    struct {
        unsigned int dbg_freeze_cpu0:1;     /* 1 = freeze timers when CPU0 is in debug state, 0 = no freeze */
        unsigned int dbg_freeze_cpu1:1;     /* 1 = freeze timers when CPU1 is in debug state, 0 = no freeze */
        unsigned int undefined_bits_2_3:2;
        unsigned int dbg_freeze_cop:1;      /* 1 = freeze timers when COP is in debug state, 0 = no freeze */
        unsigned int undefined_bits_5_31:27;
    };

    u_int32_t reg32;
};

void Timer_usDev::fill_cntr_freeze_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const cntr_freeze_u old_value_t = { .reg32 = value };
    const cntr_freeze_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: dbg_freeze_cpu0:1",
              "1 = freeze timers when CPU0 is in debug state,\n0 = no freeze",
              1, old_value_t.dbg_freeze_cpu0, new_value_t.dbg_freeze_cpu0 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: dbg_freeze_cpu1:1",
              "1 = freeze timers when CPU1 is in debug state,\n0 = no freeze",
              1, old_value_t.dbg_freeze_cpu1, new_value_t.dbg_freeze_cpu1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: undefined_bits_2_3:2", "", 2, old_value_t.undefined_bits_2_3, new_value_t.undefined_bits_2_3 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: dbg_freeze_cop:1",
              "1 = freeze timers when COP is in debug state,\n0 = no freeze",
              1, old_value_t.dbg_freeze_cop, new_value_t.dbg_freeze_cop };
    m_bit_details_model.bits.append(entry);
    entry = { "05: undefined_bits_5_31:27", "", 27, old_value_t.undefined_bits_5_31, new_value_t.undefined_bits_5_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "The timer disable logic freezes (stops incrementing or decrementing) the timer counters when one or both of the ARM cores enters debug state. The timers remain frozen while either core is in debug state or its freeze enable bit is asserted:\nfreeze = (cpu_timer_freeze && cpu_debug_state) || (cop_timer_freeze && cop_debug_state)";
}

bool Timer_usDev::is_offset_valid(const u_int32_t &offset) const
{
    switch (offset) {
    case CNTR_1US_OFFSET:
    case USEC_CFG_OFFSET:
    case CNTR_FREEZE_OFFSET:
        return true;
    default:
        break;
    }

    return false;
}

bool Timer_usDev::is_undef_changed(const u_int32_t &offset,
                                           const u_int32_t &value,
                                           const u_int32_t &new_value) const
{
    switch (offset) {
    case CNTR_1US_OFFSET:
        if ((value ^ new_value) & CNTR_1US_UNDEFMASK)
            return true;
        break;
    case USEC_CFG_OFFSET:
        if ((value ^ new_value) & USEC_CFG_UNDEFMASK)
            return true;
        break;
    case CNTR_FREEZE_OFFSET:
        if ((value ^ new_value) & CNTR_FREEZE_UNDEFMASK)
            return true;
        break;

    default:
        break;
    }

    return false;
}

QString Timer_usDev::get_register_name(const log_entry &entry) const
{
    switch (entry.offset) {
    case CNTR_1US_OFFSET:
        return QString("CNTR_1US");
    case USEC_CFG_OFFSET:
        return QString("USEC_CFG");
    case CNTR_FREEZE_OFFSET:
        return QString("CNTR_FREEZE");

    default:
        break;
    }

    qDebug() << QString().sprintf("TIMER_US: %s: Ooops... 0x%x", __func__, entry.offset);

    return QString().sprintf("Ooops... @0x%X", entry.offset);
}

void Timer_usDev::fill_bits_details(const u_int32_t &offset,
                                      const u_int32_t &value, const u_int32_t &new_value)
{
    switch (offset) {
    case CNTR_1US_OFFSET:
        fill_cntr_1us_details(value, new_value);
        break;
    case USEC_CFG_OFFSET:
        fill_usec_cfg_details(value, new_value);
        break;
    case CNTR_FREEZE_OFFSET:
        fill_cntr_freeze_details(value, new_value);
        break;

    default:
        m_bit_details_model.bits.clear();
        break;
    }
}
