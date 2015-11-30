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

#include "fusedev.h"

#include <QDebug>

#define FUSE_FUSEBYPASS_OFFSET 0x24
#define FUSE_FUSEBYPASS_UNDEFMASK 0xFFFFFFFE
union fuse_fusebypass_u {
    struct {
        unsigned int fusebypass_val:1;
        unsigned int undefined_bits_1_31:31;
    };

    u_int32_t reg32;
};

void FuseDev::fill_fuse_fusebypass_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const fuse_fusebypass_u old_value_t = { .reg32 = value };
    const fuse_fusebypass_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: fusebypass_val:1", "", 1, old_value_t.fusebypass_val, new_value_t.fusebypass_val };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_31:31", "", 31, old_value_t.undefined_bits_1_31, new_value_t.undefined_bits_1_31 };
    m_bit_details_model.bits.append(entry);
}

#define FUSE_WRITE_ACCESS_SW_OFFSET 0x30
#define FUSE_WRITE_ACCESS_SW_UNDEFMASK 0xFFFEFFFE
union fuse_write_access_sw_u {
    struct {
        unsigned int write_access_sw_ctrl:1;
        unsigned int undefined_bits_1_15:15;
        unsigned int write_access_sw_status:1;
        unsigned int undefined_bits_17_31:15;
    };

    u_int32_t reg32;
};

void FuseDev::fill_fuse_write_access_sw_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const fuse_write_access_sw_u old_value_t = { .reg32 = value };
    const fuse_write_access_sw_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: write_access_sw_ctrl:1", "", 1, old_value_t.write_access_sw_ctrl, new_value_t.write_access_sw_ctrl };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_15:15", "", 15, old_value_t.undefined_bits_1_15, new_value_t.undefined_bits_1_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: write_access_sw_status:1", "", 1, old_value_t.write_access_sw_status, new_value_t.write_access_sw_status };
    m_bit_details_model.bits.append(entry);
    entry = { "17: undefined_bits_17_31:15", "", 15, old_value_t.undefined_bits_17_31, new_value_t.undefined_bits_17_31 };
    m_bit_details_model.bits.append(entry);
}

#define FUSE_JTAG_SECUREID_OFFSET 0x108
#define FUSE_JTAG_SECUREID_UNDEFMASK 0x00000000
union fuse_jtag_secureid_u {
    struct {
        unsigned int jtag_secureid_0:32;
    };

    u_int32_t reg32;
};

void FuseDev::fill_fuse_jtag_secureid_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const fuse_jtag_secureid_u old_value_t = { .reg32 = value };
    const fuse_jtag_secureid_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: jtag_secureid_0:32", "", 32, old_value_t.jtag_secureid_0, new_value_t.jtag_secureid_0 };
    m_bit_details_model.bits.append(entry);
}

#define FUSE_JTAG_SECUREID_1_OFFSET 0x10C
#define FUSE_JTAG_SECUREID_1_UNDEFMASK 0x00000000
union fuse_jtag_secureid_1_u {
    struct {
        unsigned int jtag_secureid_1:32;
    };

    u_int32_t reg32;
};

void FuseDev::fill_fuse_jtag_secureid_1_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const fuse_jtag_secureid_1_u old_value_t = { .reg32 = value };
    const fuse_jtag_secureid_1_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: jtag_secureid_1:32", "", 32, old_value_t.jtag_secureid_1, new_value_t.jtag_secureid_1 };
    m_bit_details_model.bits.append(entry);
}

#define FUSE_SKU_INFO_OFFSET 0x110
#define FUSE_SKU_INFO_UNDEFMASK 0xFFFFFF00
union fuse_sku_info_u {
    struct {
        unsigned int sku_info:8;
        unsigned int undefined_bits_8_31:24;
    };

    u_int32_t reg32;
};

void FuseDev::fill_fuse_sku_info_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const fuse_sku_info_u old_value_t = { .reg32 = value };
    const fuse_sku_info_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: sku_info:8", "", 8, old_value_t.sku_info, new_value_t.sku_info };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_31:24", "", 24, old_value_t.undefined_bits_8_31, new_value_t.undefined_bits_8_31 };
    m_bit_details_model.bits.append(entry);
}

#define FUSE_PROCESS_CALIB_OFFSET 0x114
#define FUSE_PROCESS_CALIB_UNDEFMASK 0xFFFFFFFC
union fuse_process_calib_u {
    struct {
        unsigned int process_calib:2;
        unsigned int undefined_bits_2_31:30;
    };

    u_int32_t reg32;
};

void FuseDev::fill_fuse_process_calib_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const fuse_process_calib_u old_value_t = { .reg32 = value };
    const fuse_process_calib_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: process_calib:2", "", 2, old_value_t.process_calib, new_value_t.process_calib };
    m_bit_details_model.bits.append(entry);
    entry = { "02: undefined_bits_2_31:30", "", 30, old_value_t.undefined_bits_2_31, new_value_t.undefined_bits_2_31 };
    m_bit_details_model.bits.append(entry);
}

#define FUSE_IO_CALIB_OFFSET 0x118
#define FUSE_IO_CALIB_UNDEFMASK 0xFFFFFC00
union fuse_io_calib_u {
    struct {
        unsigned int io_calib:10;
        unsigned int undefined_bits_10_31:22;
    };

    u_int32_t reg32;
};

void FuseDev::fill_fuse_io_calib_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const fuse_io_calib_u old_value_t = { .reg32 = value };
    const fuse_io_calib_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: io_calib:10", "", 10, old_value_t.io_calib, new_value_t.io_calib };
    m_bit_details_model.bits.append(entry);
    entry = { "10: undefined_bits_10_31:22", "", 22, old_value_t.undefined_bits_10_31, new_value_t.undefined_bits_10_31 };
    m_bit_details_model.bits.append(entry);
}

#define FUSE_DAC_CRT_CALIB_OFFSET 0x11C
#define FUSE_DAC_CRT_CALIB_UNDEFMASK 0xFFFFFF00
union fuse_dac_crt_calib_u {
    struct {
        unsigned int dac_crt_calib:8;
        unsigned int undefined_bits_8_31:24;
    };

    u_int32_t reg32;
};

void FuseDev::fill_fuse_dac_crt_calib_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const fuse_dac_crt_calib_u old_value_t = { .reg32 = value };
    const fuse_dac_crt_calib_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: dac_crt_calib:8", "", 8, old_value_t.dac_crt_calib, new_value_t.dac_crt_calib };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_31:24", "", 24, old_value_t.undefined_bits_8_31, new_value_t.undefined_bits_8_31 };
    m_bit_details_model.bits.append(entry);
}

#define FUSE_DAC_HDTV_CALIB_OFFSET 0x120
#define FUSE_DAC_HDTV_CALIB_UNDEFMASK 0xFFFFFF00
union fuse_dac_hdtv_calib_u {
    struct {
        unsigned int dac_hdtv_calib:8;
        unsigned int undefined_bits_8_31:24;
    };

    u_int32_t reg32;
};

void FuseDev::fill_fuse_dac_hdtv_calib_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const fuse_dac_hdtv_calib_u old_value_t = { .reg32 = value };
    const fuse_dac_hdtv_calib_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: dac_hdtv_calib:8", "", 8, old_value_t.dac_hdtv_calib, new_value_t.dac_hdtv_calib };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_31:24", "", 24, old_value_t.undefined_bits_8_31, new_value_t.undefined_bits_8_31 };
    m_bit_details_model.bits.append(entry);
}

#define FUSE_DAC_SDTV_CALIB_OFFSET 0x124
#define FUSE_DAC_SDTV_CALIB_UNDEFMASK 0xFFFFFF00
union fuse_dac_sdtv_calib_u {
    struct {
        unsigned int dac_sdtv_calib:8;
        unsigned int undefined_bits_8_31:24;
    };

    u_int32_t reg32;
};

void FuseDev::fill_fuse_dac_sdtv_calib_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const fuse_dac_sdtv_calib_u old_value_t = { .reg32 = value };
    const fuse_dac_sdtv_calib_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: dac_sdtv_calib:8", "", 8, old_value_t.dac_sdtv_calib, new_value_t.dac_sdtv_calib };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_31:24", "", 24, old_value_t.undefined_bits_8_31, new_value_t.undefined_bits_8_31 };
    m_bit_details_model.bits.append(entry);
}

#define FUSE_RESERVED_PRODUCTION_OFFSET 0x14C
#define FUSE_RESERVED_PRODUCTION_UNDEFMASK 0xFFFFFFF0
union fuse_reserved_production_u {
    struct {
        unsigned int reserved_production:4;
        unsigned int undefined_bits_4_31:28;
    };

    u_int32_t reg32;
};

void FuseDev::fill_fuse_reserved_production_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const fuse_reserved_production_u old_value_t = { .reg32 = value };
    const fuse_reserved_production_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: reserved_production:4", "", 4, old_value_t.reserved_production, new_value_t.reserved_production };
    m_bit_details_model.bits.append(entry);
    entry = { "04: undefined_bits_4_31:28", "", 28, old_value_t.undefined_bits_4_31, new_value_t.undefined_bits_4_31 };
    m_bit_details_model.bits.append(entry);
}

#define FUSE_SPARE_BIT_OFFSET 0x200
#define FUSE_SPARE_BIT_UNDEFMASK 0xFFFFFFFE
union fuse_spare_bit_u {
    struct {
        unsigned int spare_bit_0:1;
        unsigned int undefined_bits_1_31:31;
    };

    u_int32_t reg32;
};

void FuseDev::fill_fuse_spare_bit_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const fuse_spare_bit_u old_value_t = { .reg32 = value };
    const fuse_spare_bit_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: spare_bit_0:1", "", 1, old_value_t.spare_bit_0, new_value_t.spare_bit_0 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_31:31", "", 31, old_value_t.undefined_bits_1_31, new_value_t.undefined_bits_1_31 };
    m_bit_details_model.bits.append(entry);
}

#define FUSE_SPARE_BIT_1_OFFSET 0x204
#define FUSE_SPARE_BIT_1_UNDEFMASK 0xFFFFFFFE
union fuse_spare_bit_1_u {
    struct {
        unsigned int spare_bit_1:1;
        unsigned int undefined_bits_1_31:31;
    };

    u_int32_t reg32;
};

void FuseDev::fill_fuse_spare_bit_1_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const fuse_spare_bit_1_u old_value_t = { .reg32 = value };
    const fuse_spare_bit_1_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: spare_bit_1:1", "", 1, old_value_t.spare_bit_1, new_value_t.spare_bit_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_31:31", "", 31, old_value_t.undefined_bits_1_31, new_value_t.undefined_bits_1_31 };
    m_bit_details_model.bits.append(entry);
}

#define FUSE_SPARE_BIT_2_OFFSET 0x208
#define FUSE_SPARE_BIT_2_UNDEFMASK 0xFFFFFFFE
union fuse_spare_bit_2_u {
    struct {
        unsigned int spare_bit_2:1;
        unsigned int undefined_bits_1_31:31;
    };

    u_int32_t reg32;
};

void FuseDev::fill_fuse_spare_bit_2_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const fuse_spare_bit_2_u old_value_t = { .reg32 = value };
    const fuse_spare_bit_2_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: spare_bit_2:1", "", 1, old_value_t.spare_bit_2, new_value_t.spare_bit_2 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_31:31", "", 31, old_value_t.undefined_bits_1_31, new_value_t.undefined_bits_1_31 };
    m_bit_details_model.bits.append(entry);
}

#define FUSE_SPARE_BIT_3_OFFSET 0x20C
#define FUSE_SPARE_BIT_3_UNDEFMASK 0xFFFFFFFE
union fuse_spare_bit_3_u {
    struct {
        unsigned int spare_bit_3:1;
        unsigned int undefined_bits_1_31:31;
    };

    u_int32_t reg32;
};

void FuseDev::fill_fuse_spare_bit_3_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const fuse_spare_bit_3_u old_value_t = { .reg32 = value };
    const fuse_spare_bit_3_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: spare_bit_3:1", "", 1, old_value_t.spare_bit_3, new_value_t.spare_bit_3 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_31:31", "", 31, old_value_t.undefined_bits_1_31, new_value_t.undefined_bits_1_31 };
    m_bit_details_model.bits.append(entry);
}

#define FUSE_SPARE_BIT_4_OFFSET 0x210
#define FUSE_SPARE_BIT_4_UNDEFMASK 0xFFFFFFFE
union fuse_spare_bit_4_u {
    struct {
        unsigned int spare_bit_4:1;
        unsigned int undefined_bits_1_31:31;
    };

    u_int32_t reg32;
};

void FuseDev::fill_fuse_spare_bit_4_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const fuse_spare_bit_4_u old_value_t = { .reg32 = value };
    const fuse_spare_bit_4_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: spare_bit_4:1", "", 1, old_value_t.spare_bit_4, new_value_t.spare_bit_4 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_31:31", "", 31, old_value_t.undefined_bits_1_31, new_value_t.undefined_bits_1_31 };
    m_bit_details_model.bits.append(entry);
}

#define FUSE_SPARE_BIT_5_OFFSET 0x214
#define FUSE_SPARE_BIT_5_UNDEFMASK 0xFFFFFFFE
union fuse_spare_bit_5_u {
    struct {
        unsigned int spare_bit_5:1;
        unsigned int undefined_bits_1_31:31;
    };

    u_int32_t reg32;
};

void FuseDev::fill_fuse_spare_bit_5_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const fuse_spare_bit_5_u old_value_t = { .reg32 = value };
    const fuse_spare_bit_5_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: spare_bit_5:1", "", 1, old_value_t.spare_bit_5, new_value_t.spare_bit_5 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_31:31", "", 31, old_value_t.undefined_bits_1_31, new_value_t.undefined_bits_1_31 };
    m_bit_details_model.bits.append(entry);
}

#define FUSE_SPARE_BIT_6_OFFSET 0x218
#define FUSE_SPARE_BIT_6_UNDEFMASK 0xFFFFFFFE
union fuse_spare_bit_6_u {
    struct {
        unsigned int spare_bit_6:1;
        unsigned int undefined_bits_1_31:31;
    };

    u_int32_t reg32;
};

void FuseDev::fill_fuse_spare_bit_6_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const fuse_spare_bit_6_u old_value_t = { .reg32 = value };
    const fuse_spare_bit_6_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: spare_bit_6:1", "", 1, old_value_t.spare_bit_6, new_value_t.spare_bit_6 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_31:31", "", 31, old_value_t.undefined_bits_1_31, new_value_t.undefined_bits_1_31 };
    m_bit_details_model.bits.append(entry);
}

#define FUSE_SPARE_BIT_7_OFFSET 0x21C
#define FUSE_SPARE_BIT_7_UNDEFMASK 0xFFFFFFFE
union fuse_spare_bit_7_u {
    struct {
        unsigned int spare_bit_7:1;
        unsigned int undefined_bits_1_31:31;
    };

    u_int32_t reg32;
};

void FuseDev::fill_fuse_spare_bit_7_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const fuse_spare_bit_7_u old_value_t = { .reg32 = value };
    const fuse_spare_bit_7_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: spare_bit_7:1", "", 1, old_value_t.spare_bit_7, new_value_t.spare_bit_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_31:31", "", 31, old_value_t.undefined_bits_1_31, new_value_t.undefined_bits_1_31 };
    m_bit_details_model.bits.append(entry);
}

#define FUSE_SPARE_BIT_8_OFFSET 0x220
#define FUSE_SPARE_BIT_8_UNDEFMASK 0xFFFFFFFE
union fuse_spare_bit_8_u {
    struct {
        unsigned int spare_bit_8:1;
        unsigned int undefined_bits_1_31:31;
    };

    u_int32_t reg32;
};

void FuseDev::fill_fuse_spare_bit_8_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const fuse_spare_bit_8_u old_value_t = { .reg32 = value };
    const fuse_spare_bit_8_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: spare_bit_8:1", "", 1, old_value_t.spare_bit_8, new_value_t.spare_bit_8 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_31:31", "", 31, old_value_t.undefined_bits_1_31, new_value_t.undefined_bits_1_31 };
    m_bit_details_model.bits.append(entry);
}

#define FUSE_SPARE_BIT_9_OFFSET 0x224
#define FUSE_SPARE_BIT_9_UNDEFMASK 0xFFFFFFFE
union fuse_spare_bit_9_u {
    struct {
        unsigned int spare_bit_9:1;
        unsigned int undefined_bits_1_31:31;
    };

    u_int32_t reg32;
};

void FuseDev::fill_fuse_spare_bit_9_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const fuse_spare_bit_9_u old_value_t = { .reg32 = value };
    const fuse_spare_bit_9_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: spare_bit_9:1", "", 1, old_value_t.spare_bit_9, new_value_t.spare_bit_9 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_31:31", "", 31, old_value_t.undefined_bits_1_31, new_value_t.undefined_bits_1_31 };
    m_bit_details_model.bits.append(entry);
}

#define FUSE_SPARE_BIT_10_OFFSET 0x228
#define FUSE_SPARE_BIT_10_UNDEFMASK 0xFFFFFFFE
union fuse_spare_bit_10_u {
    struct {
        unsigned int spare_bit_10:1;
        unsigned int undefined_bits_1_31:31;
    };

    u_int32_t reg32;
};

void FuseDev::fill_fuse_spare_bit_10_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const fuse_spare_bit_10_u old_value_t = { .reg32 = value };
    const fuse_spare_bit_10_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: spare_bit_10:1", "", 1, old_value_t.spare_bit_10, new_value_t.spare_bit_10 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_31:31", "", 31, old_value_t.undefined_bits_1_31, new_value_t.undefined_bits_1_31 };
    m_bit_details_model.bits.append(entry);
}

#define FUSE_SPARE_BIT_11_OFFSET 0x22C
#define FUSE_SPARE_BIT_11_UNDEFMASK 0xFFFFFFFE
union fuse_spare_bit_11_u {
    struct {
        unsigned int spare_bit_11:1;
        unsigned int undefined_bits_1_31:31;
    };

    u_int32_t reg32;
};

void FuseDev::fill_fuse_spare_bit_11_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const fuse_spare_bit_11_u old_value_t = { .reg32 = value };
    const fuse_spare_bit_11_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: spare_bit_11:1", "", 1, old_value_t.spare_bit_11, new_value_t.spare_bit_11 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_31:31", "", 31, old_value_t.undefined_bits_1_31, new_value_t.undefined_bits_1_31 };
    m_bit_details_model.bits.append(entry);
}

#define FUSE_SPARE_BIT_12_OFFSET 0x230
#define FUSE_SPARE_BIT_12_UNDEFMASK 0xFFFFFFFE
union fuse_spare_bit_12_u {
    struct {
        unsigned int spare_bit_12:1;
        unsigned int undefined_bits_1_31:31;
    };

    u_int32_t reg32;
};

void FuseDev::fill_fuse_spare_bit_12_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const fuse_spare_bit_12_u old_value_t = { .reg32 = value };
    const fuse_spare_bit_12_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: spare_bit_12:1", "", 1, old_value_t.spare_bit_12, new_value_t.spare_bit_12 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_31:31", "", 31, old_value_t.undefined_bits_1_31, new_value_t.undefined_bits_1_31 };
    m_bit_details_model.bits.append(entry);
}

#define FUSE_SPARE_BIT_13_OFFSET 0x234
#define FUSE_SPARE_BIT_13_UNDEFMASK 0xFFFFFFFE
union fuse_spare_bit_13_u {
    struct {
        unsigned int spare_bit_13:1;
        unsigned int undefined_bits_1_31:31;
    };

    u_int32_t reg32;
};

void FuseDev::fill_fuse_spare_bit_13_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const fuse_spare_bit_13_u old_value_t = { .reg32 = value };
    const fuse_spare_bit_13_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: spare_bit_13:1", "", 1, old_value_t.spare_bit_13, new_value_t.spare_bit_13 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_31:31", "", 31, old_value_t.undefined_bits_1_31, new_value_t.undefined_bits_1_31 };
    m_bit_details_model.bits.append(entry);
}

#define FUSE_SPARE_BIT_14_OFFSET 0x238
#define FUSE_SPARE_BIT_14_UNDEFMASK 0xFFFFFFFE
union fuse_spare_bit_14_u {
    struct {
        unsigned int spare_bit_14:1;
        unsigned int undefined_bits_1_31:31;
    };

    u_int32_t reg32;
};

void FuseDev::fill_fuse_spare_bit_14_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const fuse_spare_bit_14_u old_value_t = { .reg32 = value };
    const fuse_spare_bit_14_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: spare_bit_14:1", "", 1, old_value_t.spare_bit_14, new_value_t.spare_bit_14 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_31:31", "", 31, old_value_t.undefined_bits_1_31, new_value_t.undefined_bits_1_31 };
    m_bit_details_model.bits.append(entry);
}

#define FUSE_SPARE_BIT_15_OFFSET 0x23C
#define FUSE_SPARE_BIT_15_UNDEFMASK 0xFFFFFFFE
union fuse_spare_bit_15_u {
    struct {
        unsigned int spare_bit_15:1;
        unsigned int undefined_bits_1_31:31;
    };

    u_int32_t reg32;
};

void FuseDev::fill_fuse_spare_bit_15_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const fuse_spare_bit_15_u old_value_t = { .reg32 = value };
    const fuse_spare_bit_15_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: spare_bit_15:1", "", 1, old_value_t.spare_bit_15, new_value_t.spare_bit_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_31:31", "", 31, old_value_t.undefined_bits_1_31, new_value_t.undefined_bits_1_31 };
    m_bit_details_model.bits.append(entry);
}

#define FUSE_SPARE_BIT_16_OFFSET 0x240
#define FUSE_SPARE_BIT_16_UNDEFMASK 0xFFFFFFFE
union fuse_spare_bit_16_u {
    struct {
        unsigned int spare_bit_16:1;
        unsigned int undefined_bits_1_31:31;
    };

    u_int32_t reg32;
};

void FuseDev::fill_fuse_spare_bit_16_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const fuse_spare_bit_16_u old_value_t = { .reg32 = value };
    const fuse_spare_bit_16_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: spare_bit_16:1", "", 1, old_value_t.spare_bit_16, new_value_t.spare_bit_16 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_31:31", "", 31, old_value_t.undefined_bits_1_31, new_value_t.undefined_bits_1_31 };
    m_bit_details_model.bits.append(entry);
}

#define FUSE_SPARE_BIT_17_OFFSET 0x244
#define FUSE_SPARE_BIT_17_UNDEFMASK 0xFFFFFFFE
union fuse_spare_bit_17_u {
    struct {
        unsigned int spare_bit_17:1;
        unsigned int undefined_bits_1_31:31;
    };

    u_int32_t reg32;
};

void FuseDev::fill_fuse_spare_bit_17_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const fuse_spare_bit_17_u old_value_t = { .reg32 = value };
    const fuse_spare_bit_17_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: spare_bit_17:1", "", 1, old_value_t.spare_bit_17, new_value_t.spare_bit_17 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_31:31", "", 31, old_value_t.undefined_bits_1_31, new_value_t.undefined_bits_1_31 };
    m_bit_details_model.bits.append(entry);
}

#define FUSE_SPARE_BIT_18_OFFSET 0x248
#define FUSE_SPARE_BIT_18_UNDEFMASK 0xFFFFFFFE
union fuse_spare_bit_18_u {
    struct {
        unsigned int spare_bit_18:1;
        unsigned int undefined_bits_1_31:31;
    };

    u_int32_t reg32;
};

void FuseDev::fill_fuse_spare_bit_18_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const fuse_spare_bit_18_u old_value_t = { .reg32 = value };
    const fuse_spare_bit_18_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: spare_bit_18:1", "", 1, old_value_t.spare_bit_18, new_value_t.spare_bit_18 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_31:31", "", 31, old_value_t.undefined_bits_1_31, new_value_t.undefined_bits_1_31 };
    m_bit_details_model.bits.append(entry);
}

#define FUSE_SPARE_BIT_19_OFFSET 0x24C
#define FUSE_SPARE_BIT_19_UNDEFMASK 0xFFFFFFFE
union fuse_spare_bit_19_u {
    struct {
        unsigned int spare_bit_19:1;
        unsigned int undefined_bits_1_31:31;
    };

    u_int32_t reg32;
};

void FuseDev::fill_fuse_spare_bit_19_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const fuse_spare_bit_19_u old_value_t = { .reg32 = value };
    const fuse_spare_bit_19_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: spare_bit_19:1", "", 1, old_value_t.spare_bit_19, new_value_t.spare_bit_19 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_31:31", "", 31, old_value_t.undefined_bits_1_31, new_value_t.undefined_bits_1_31 };
    m_bit_details_model.bits.append(entry);
}

#define FUSE_SPARE_BIT_20_OFFSET 0x250
#define FUSE_SPARE_BIT_20_UNDEFMASK 0xFFFFFFFE
union fuse_spare_bit_20_u {
    struct {
        unsigned int spare_bit_20:1;
        unsigned int undefined_bits_1_31:31;
    };

    u_int32_t reg32;
};

void FuseDev::fill_fuse_spare_bit_20_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const fuse_spare_bit_20_u old_value_t = { .reg32 = value };
    const fuse_spare_bit_20_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: spare_bit_20:1", "", 1, old_value_t.spare_bit_20, new_value_t.spare_bit_20 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_31:31", "", 31, old_value_t.undefined_bits_1_31, new_value_t.undefined_bits_1_31 };
    m_bit_details_model.bits.append(entry);
}

#define FUSE_SPARE_BIT_21_OFFSET 0x254
#define FUSE_SPARE_BIT_21_UNDEFMASK 0xFFFFFFFE
union fuse_spare_bit_21_u {
    struct {
        unsigned int spare_bit_21:1;
        unsigned int undefined_bits_1_31:31;
    };

    u_int32_t reg32;
};

void FuseDev::fill_fuse_spare_bit_21_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const fuse_spare_bit_21_u old_value_t = { .reg32 = value };
    const fuse_spare_bit_21_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: spare_bit_21:1", "", 1, old_value_t.spare_bit_21, new_value_t.spare_bit_21 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_31:31", "", 31, old_value_t.undefined_bits_1_31, new_value_t.undefined_bits_1_31 };
    m_bit_details_model.bits.append(entry);
}

#define FUSE_SPARE_BIT_22_OFFSET 0x258
#define FUSE_SPARE_BIT_22_UNDEFMASK 0xFFFFFFFE
union fuse_spare_bit_22_u {
    struct {
        unsigned int spare_bit_22:1;
        unsigned int undefined_bits_1_31:31;
    };

    u_int32_t reg32;
};

void FuseDev::fill_fuse_spare_bit_22_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const fuse_spare_bit_22_u old_value_t = { .reg32 = value };
    const fuse_spare_bit_22_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: spare_bit_22:1", "", 1, old_value_t.spare_bit_22, new_value_t.spare_bit_22 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_31:31", "", 31, old_value_t.undefined_bits_1_31, new_value_t.undefined_bits_1_31 };
    m_bit_details_model.bits.append(entry);
}

#define FUSE_SPARE_BIT_23_OFFSET 0x25C
#define FUSE_SPARE_BIT_23_UNDEFMASK 0xFFFFFFFE
union fuse_spare_bit_23_u {
    struct {
        unsigned int spare_bit_23:1;
        unsigned int undefined_bits_1_31:31;
    };

    u_int32_t reg32;
};

void FuseDev::fill_fuse_spare_bit_23_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const fuse_spare_bit_23_u old_value_t = { .reg32 = value };
    const fuse_spare_bit_23_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: spare_bit_23:1", "", 1, old_value_t.spare_bit_23, new_value_t.spare_bit_23 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_31:31", "", 31, old_value_t.undefined_bits_1_31, new_value_t.undefined_bits_1_31 };
    m_bit_details_model.bits.append(entry);
}

#define FUSE_SPARE_BIT_24_OFFSET 0x260
#define FUSE_SPARE_BIT_24_UNDEFMASK 0xFFFFFFFE
union fuse_spare_bit_24_u {
    struct {
        unsigned int spare_bit_24:1;
        unsigned int undefined_bits_1_31:31;
    };

    u_int32_t reg32;
};

void FuseDev::fill_fuse_spare_bit_24_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const fuse_spare_bit_24_u old_value_t = { .reg32 = value };
    const fuse_spare_bit_24_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: spare_bit_24:1", "", 1, old_value_t.spare_bit_24, new_value_t.spare_bit_24 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_31:31", "", 31, old_value_t.undefined_bits_1_31, new_value_t.undefined_bits_1_31 };
    m_bit_details_model.bits.append(entry);
}

#define FUSE_SPARE_BIT_25_OFFSET 0x264
#define FUSE_SPARE_BIT_25_UNDEFMASK 0xFFFFFFFE
union fuse_spare_bit_25_u {
    struct {
        unsigned int spare_bit_25:1;
        unsigned int undefined_bits_1_31:31;
    };

    u_int32_t reg32;
};

void FuseDev::fill_fuse_spare_bit_25_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const fuse_spare_bit_25_u old_value_t = { .reg32 = value };
    const fuse_spare_bit_25_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: spare_bit_25:1", "", 1, old_value_t.spare_bit_25, new_value_t.spare_bit_25 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_31:31", "", 31, old_value_t.undefined_bits_1_31, new_value_t.undefined_bits_1_31 };
    m_bit_details_model.bits.append(entry);
}

#define FUSE_SPARE_BIT_26_OFFSET 0x268
#define FUSE_SPARE_BIT_26_UNDEFMASK 0xFFFFFFFE
union fuse_spare_bit_26_u {
    struct {
        unsigned int spare_bit_26:1;
        unsigned int undefined_bits_1_31:31;
    };

    u_int32_t reg32;
};

void FuseDev::fill_fuse_spare_bit_26_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const fuse_spare_bit_26_u old_value_t = { .reg32 = value };
    const fuse_spare_bit_26_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: spare_bit_26:1", "", 1, old_value_t.spare_bit_26, new_value_t.spare_bit_26 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_31:31", "", 31, old_value_t.undefined_bits_1_31, new_value_t.undefined_bits_1_31 };
    m_bit_details_model.bits.append(entry);
}

#define FUSE_SPARE_BIT_27_OFFSET 0x26C
#define FUSE_SPARE_BIT_27_UNDEFMASK 0xFFFFFFFE
union fuse_spare_bit_27_u {
    struct {
        unsigned int spare_bit_27:1;
        unsigned int undefined_bits_1_31:31;
    };

    u_int32_t reg32;
};

void FuseDev::fill_fuse_spare_bit_27_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const fuse_spare_bit_27_u old_value_t = { .reg32 = value };
    const fuse_spare_bit_27_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: spare_bit_27:1", "", 1, old_value_t.spare_bit_27, new_value_t.spare_bit_27 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_31:31", "", 31, old_value_t.undefined_bits_1_31, new_value_t.undefined_bits_1_31 };
    m_bit_details_model.bits.append(entry);
}

#define FUSE_SPARE_BIT_28_OFFSET 0x270
#define FUSE_SPARE_BIT_28_UNDEFMASK 0xFFFFFFFE
union fuse_spare_bit_28_u {
    struct {
        unsigned int spare_bit_28:1;
        unsigned int undefined_bits_1_31:31;
    };

    u_int32_t reg32;
};

void FuseDev::fill_fuse_spare_bit_28_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const fuse_spare_bit_28_u old_value_t = { .reg32 = value };
    const fuse_spare_bit_28_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: spare_bit_28:1", "", 1, old_value_t.spare_bit_28, new_value_t.spare_bit_28 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_31:31", "", 31, old_value_t.undefined_bits_1_31, new_value_t.undefined_bits_1_31 };
    m_bit_details_model.bits.append(entry);
}

#define FUSE_SPARE_BIT_29_OFFSET 0x274
#define FUSE_SPARE_BIT_29_UNDEFMASK 0xFFFFFFFE
union fuse_spare_bit_29_u {
    struct {
        unsigned int spare_bit_29:1;
        unsigned int undefined_bits_1_31:31;
    };

    u_int32_t reg32;
};

void FuseDev::fill_fuse_spare_bit_29_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const fuse_spare_bit_29_u old_value_t = { .reg32 = value };
    const fuse_spare_bit_29_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: spare_bit_29:1", "", 1, old_value_t.spare_bit_29, new_value_t.spare_bit_29 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_31:31", "", 31, old_value_t.undefined_bits_1_31, new_value_t.undefined_bits_1_31 };
    m_bit_details_model.bits.append(entry);
}

#define FUSE_SPARE_BIT_30_OFFSET 0x278
#define FUSE_SPARE_BIT_30_UNDEFMASK 0xFFFFFFFE
union fuse_spare_bit_30_u {
    struct {
        unsigned int spare_bit_30:1;
        unsigned int undefined_bits_1_31:31;
    };

    u_int32_t reg32;
};

void FuseDev::fill_fuse_spare_bit_30_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const fuse_spare_bit_30_u old_value_t = { .reg32 = value };
    const fuse_spare_bit_30_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: spare_bit_30:1", "", 1, old_value_t.spare_bit_30, new_value_t.spare_bit_30 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_31:31", "", 31, old_value_t.undefined_bits_1_31, new_value_t.undefined_bits_1_31 };
    m_bit_details_model.bits.append(entry);
}

#define FUSE_SPARE_BIT_31_OFFSET 0x27C
#define FUSE_SPARE_BIT_31_UNDEFMASK 0xFFFFFFFE
union fuse_spare_bit_31_u {
    struct {
        unsigned int spare_bit_31:1;
        unsigned int undefined_bits_1_31:31;
    };

    u_int32_t reg32;
};

void FuseDev::fill_fuse_spare_bit_31_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const fuse_spare_bit_31_u old_value_t = { .reg32 = value };
    const fuse_spare_bit_31_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: spare_bit_31:1", "", 1, old_value_t.spare_bit_31, new_value_t.spare_bit_31 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_31:31", "", 31, old_value_t.undefined_bits_1_31, new_value_t.undefined_bits_1_31 };
    m_bit_details_model.bits.append(entry);
}

#define FUSE_SPARE_BIT_32_OFFSET 0x280
#define FUSE_SPARE_BIT_32_UNDEFMASK 0xFFFFFFFE
union fuse_spare_bit_32_u {
    struct {
        unsigned int spare_bit_32:1;
        unsigned int undefined_bits_1_31:31;
    };

    u_int32_t reg32;
};

void FuseDev::fill_fuse_spare_bit_32_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const fuse_spare_bit_32_u old_value_t = { .reg32 = value };
    const fuse_spare_bit_32_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: spare_bit_32:1", "", 1, old_value_t.spare_bit_32, new_value_t.spare_bit_32 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_31:31", "", 31, old_value_t.undefined_bits_1_31, new_value_t.undefined_bits_1_31 };
    m_bit_details_model.bits.append(entry);
}

#define FUSE_SPARE_BIT_33_OFFSET 0x284
#define FUSE_SPARE_BIT_33_UNDEFMASK 0xFFFFFFFE
union fuse_spare_bit_33_u {
    struct {
        unsigned int spare_bit_33:1;
        unsigned int undefined_bits_1_31:31;
    };

    u_int32_t reg32;
};

void FuseDev::fill_fuse_spare_bit_33_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const fuse_spare_bit_33_u old_value_t = { .reg32 = value };
    const fuse_spare_bit_33_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: spare_bit_33:1", "", 1, old_value_t.spare_bit_33, new_value_t.spare_bit_33 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_31:31", "", 31, old_value_t.undefined_bits_1_31, new_value_t.undefined_bits_1_31 };
    m_bit_details_model.bits.append(entry);
}

#define FUSE_SPARE_BIT_34_OFFSET 0x288
#define FUSE_SPARE_BIT_34_UNDEFMASK 0xFFFFFFFE
union fuse_spare_bit_34_u {
    struct {
        unsigned int spare_bit_34:1;
        unsigned int undefined_bits_1_31:31;
    };

    u_int32_t reg32;
};

void FuseDev::fill_fuse_spare_bit_34_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const fuse_spare_bit_34_u old_value_t = { .reg32 = value };
    const fuse_spare_bit_34_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: spare_bit_34:1", "", 1, old_value_t.spare_bit_34, new_value_t.spare_bit_34 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_31:31", "", 31, old_value_t.undefined_bits_1_31, new_value_t.undefined_bits_1_31 };
    m_bit_details_model.bits.append(entry);
}

#define FUSE_SPARE_BIT_35_OFFSET 0x28C
#define FUSE_SPARE_BIT_35_UNDEFMASK 0xFFFFFFFE
union fuse_spare_bit_35_u {
    struct {
        unsigned int spare_bit_35:1;
        unsigned int undefined_bits_1_31:31;
    };

    u_int32_t reg32;
};

void FuseDev::fill_fuse_spare_bit_35_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const fuse_spare_bit_35_u old_value_t = { .reg32 = value };
    const fuse_spare_bit_35_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: spare_bit_35:1", "", 1, old_value_t.spare_bit_35, new_value_t.spare_bit_35 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_31:31", "", 31, old_value_t.undefined_bits_1_31, new_value_t.undefined_bits_1_31 };
    m_bit_details_model.bits.append(entry);
}

#define FUSE_SPARE_BIT_36_OFFSET 0x290
#define FUSE_SPARE_BIT_36_UNDEFMASK 0xFFFFFFFE
union fuse_spare_bit_36_u {
    struct {
        unsigned int spare_bit_36:1;
        unsigned int undefined_bits_1_31:31;
    };

    u_int32_t reg32;
};

void FuseDev::fill_fuse_spare_bit_36_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const fuse_spare_bit_36_u old_value_t = { .reg32 = value };
    const fuse_spare_bit_36_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: spare_bit_36:1", "", 1, old_value_t.spare_bit_36, new_value_t.spare_bit_36 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_31:31", "", 31, old_value_t.undefined_bits_1_31, new_value_t.undefined_bits_1_31 };
    m_bit_details_model.bits.append(entry);
}

#define FUSE_SPARE_BIT_37_OFFSET 0x294
#define FUSE_SPARE_BIT_37_UNDEFMASK 0xFFFFFFFE
union fuse_spare_bit_37_u {
    struct {
        unsigned int spare_bit_37:1;
        unsigned int undefined_bits_1_31:31;
    };

    u_int32_t reg32;
};

void FuseDev::fill_fuse_spare_bit_37_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const fuse_spare_bit_37_u old_value_t = { .reg32 = value };
    const fuse_spare_bit_37_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: spare_bit_37:1", "", 1, old_value_t.spare_bit_37, new_value_t.spare_bit_37 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_31:31", "", 31, old_value_t.undefined_bits_1_31, new_value_t.undefined_bits_1_31 };
    m_bit_details_model.bits.append(entry);
}

#define FUSE_SPARE_BIT_38_OFFSET 0x298
#define FUSE_SPARE_BIT_38_UNDEFMASK 0xFFFFFFFE
union fuse_spare_bit_38_u {
    struct {
        unsigned int spare_bit_38:1;
        unsigned int undefined_bits_1_31:31;
    };

    u_int32_t reg32;
};

void FuseDev::fill_fuse_spare_bit_38_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const fuse_spare_bit_38_u old_value_t = { .reg32 = value };
    const fuse_spare_bit_38_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: spare_bit_38:1", "", 1, old_value_t.spare_bit_38, new_value_t.spare_bit_38 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_31:31", "", 31, old_value_t.undefined_bits_1_31, new_value_t.undefined_bits_1_31 };
    m_bit_details_model.bits.append(entry);
}

#define FUSE_SPARE_BIT_39_OFFSET 0x29C
#define FUSE_SPARE_BIT_39_UNDEFMASK 0xFFFFFFFE
union fuse_spare_bit_39_u {
    struct {
        unsigned int spare_bit_39:1;
        unsigned int undefined_bits_1_31:31;
    };

    u_int32_t reg32;
};

void FuseDev::fill_fuse_spare_bit_39_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const fuse_spare_bit_39_u old_value_t = { .reg32 = value };
    const fuse_spare_bit_39_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: spare_bit_39:1", "", 1, old_value_t.spare_bit_39, new_value_t.spare_bit_39 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_31:31", "", 31, old_value_t.undefined_bits_1_31, new_value_t.undefined_bits_1_31 };
    m_bit_details_model.bits.append(entry);
}

#define FUSE_SPARE_BIT_40_OFFSET 0x2A0
#define FUSE_SPARE_BIT_40_UNDEFMASK 0xFFFFFFFE
union fuse_spare_bit_40_u {
    struct {
        unsigned int spare_bit_40:1;
        unsigned int undefined_bits_1_31:31;
    };

    u_int32_t reg32;
};

void FuseDev::fill_fuse_spare_bit_40_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const fuse_spare_bit_40_u old_value_t = { .reg32 = value };
    const fuse_spare_bit_40_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: spare_bit_40:1", "", 1, old_value_t.spare_bit_40, new_value_t.spare_bit_40 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_31:31", "", 31, old_value_t.undefined_bits_1_31, new_value_t.undefined_bits_1_31 };
    m_bit_details_model.bits.append(entry);
}

#define FUSE_SPARE_BIT_41_OFFSET 0x2A4
#define FUSE_SPARE_BIT_41_UNDEFMASK 0xFFFFFFFE
union fuse_spare_bit_41_u {
    struct {
        unsigned int spare_bit_41:1;
        unsigned int undefined_bits_1_31:31;
    };

    u_int32_t reg32;
};

void FuseDev::fill_fuse_spare_bit_41_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const fuse_spare_bit_41_u old_value_t = { .reg32 = value };
    const fuse_spare_bit_41_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: spare_bit_41:1", "", 1, old_value_t.spare_bit_41, new_value_t.spare_bit_41 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_31:31", "", 31, old_value_t.undefined_bits_1_31, new_value_t.undefined_bits_1_31 };
    m_bit_details_model.bits.append(entry);
}

#define FUSE_SPARE_BIT_42_OFFSET 0x2A8
#define FUSE_SPARE_BIT_42_UNDEFMASK 0xFFFFFFFE
union fuse_spare_bit_42_u {
    struct {
        unsigned int spare_bit_42:1;
        unsigned int undefined_bits_1_31:31;
    };

    u_int32_t reg32;
};

void FuseDev::fill_fuse_spare_bit_42_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const fuse_spare_bit_42_u old_value_t = { .reg32 = value };
    const fuse_spare_bit_42_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: spare_bit_42:1", "", 1, old_value_t.spare_bit_42, new_value_t.spare_bit_42 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_31:31", "", 31, old_value_t.undefined_bits_1_31, new_value_t.undefined_bits_1_31 };
    m_bit_details_model.bits.append(entry);
}

#define FUSE_SPARE_BIT_43_OFFSET 0x2AC
#define FUSE_SPARE_BIT_43_UNDEFMASK 0xFFFFFFFE
union fuse_spare_bit_43_u {
    struct {
        unsigned int spare_bit_43:1;
        unsigned int undefined_bits_1_31:31;
    };

    u_int32_t reg32;
};

void FuseDev::fill_fuse_spare_bit_43_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const fuse_spare_bit_43_u old_value_t = { .reg32 = value };
    const fuse_spare_bit_43_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: spare_bit_43:1", "", 1, old_value_t.spare_bit_43, new_value_t.spare_bit_43 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_31:31", "", 31, old_value_t.undefined_bits_1_31, new_value_t.undefined_bits_1_31 };
    m_bit_details_model.bits.append(entry);
}

#define FUSE_SPARE_BIT_44_OFFSET 0x2B0
#define FUSE_SPARE_BIT_44_UNDEFMASK 0xFFFFFFFE
union fuse_spare_bit_44_u {
    struct {
        unsigned int spare_bit_44:1;
        unsigned int undefined_bits_1_31:31;
    };

    u_int32_t reg32;
};

void FuseDev::fill_fuse_spare_bit_44_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const fuse_spare_bit_44_u old_value_t = { .reg32 = value };
    const fuse_spare_bit_44_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: spare_bit_44:1", "", 1, old_value_t.spare_bit_44, new_value_t.spare_bit_44 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_31:31", "", 31, old_value_t.undefined_bits_1_31, new_value_t.undefined_bits_1_31 };
    m_bit_details_model.bits.append(entry);
}

#define FUSE_SPARE_BIT_45_OFFSET 0x2B4
#define FUSE_SPARE_BIT_45_UNDEFMASK 0xFFFFFFFE
union fuse_spare_bit_45_u {
    struct {
        unsigned int spare_bit_45:1;
        unsigned int undefined_bits_1_31:31;
    };

    u_int32_t reg32;
};

void FuseDev::fill_fuse_spare_bit_45_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const fuse_spare_bit_45_u old_value_t = { .reg32 = value };
    const fuse_spare_bit_45_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: spare_bit_45:1", "", 1, old_value_t.spare_bit_45, new_value_t.spare_bit_45 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_31:31", "", 31, old_value_t.undefined_bits_1_31, new_value_t.undefined_bits_1_31 };
    m_bit_details_model.bits.append(entry);
}

#define FUSE_SPARE_BIT_46_OFFSET 0x2B8
#define FUSE_SPARE_BIT_46_UNDEFMASK 0xFFFFFFFE
union fuse_spare_bit_46_u {
    struct {
        unsigned int spare_bit_46:1;
        unsigned int undefined_bits_1_31:31;
    };

    u_int32_t reg32;
};

void FuseDev::fill_fuse_spare_bit_46_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const fuse_spare_bit_46_u old_value_t = { .reg32 = value };
    const fuse_spare_bit_46_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: spare_bit_46:1", "", 1, old_value_t.spare_bit_46, new_value_t.spare_bit_46 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_31:31", "", 31, old_value_t.undefined_bits_1_31, new_value_t.undefined_bits_1_31 };
    m_bit_details_model.bits.append(entry);
}

#define FUSE_SPARE_BIT_47_OFFSET 0x2BC
#define FUSE_SPARE_BIT_47_UNDEFMASK 0xFFFFFFFE
union fuse_spare_bit_47_u {
    struct {
        unsigned int spare_bit_47:1;
        unsigned int undefined_bits_1_31:31;
    };

    u_int32_t reg32;
};

void FuseDev::fill_fuse_spare_bit_47_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const fuse_spare_bit_47_u old_value_t = { .reg32 = value };
    const fuse_spare_bit_47_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: spare_bit_47:1", "", 1, old_value_t.spare_bit_47, new_value_t.spare_bit_47 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_31:31", "", 31, old_value_t.undefined_bits_1_31, new_value_t.undefined_bits_1_31 };
    m_bit_details_model.bits.append(entry);
}

#define FUSE_SPARE_BIT_48_OFFSET 0x2C0
#define FUSE_SPARE_BIT_48_UNDEFMASK 0xFFFFFFFE
union fuse_spare_bit_48_u {
    struct {
        unsigned int spare_bit_48:1;
        unsigned int undefined_bits_1_31:31;
    };

    u_int32_t reg32;
};

void FuseDev::fill_fuse_spare_bit_48_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const fuse_spare_bit_48_u old_value_t = { .reg32 = value };
    const fuse_spare_bit_48_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: spare_bit_48:1", "", 1, old_value_t.spare_bit_48, new_value_t.spare_bit_48 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_31:31", "", 31, old_value_t.undefined_bits_1_31, new_value_t.undefined_bits_1_31 };
    m_bit_details_model.bits.append(entry);
}

#define FUSE_SPARE_BIT_49_OFFSET 0x2C4
#define FUSE_SPARE_BIT_49_UNDEFMASK 0xFFFFFFFE
union fuse_spare_bit_49_u {
    struct {
        unsigned int spare_bit_49:1;
        unsigned int undefined_bits_1_31:31;
    };

    u_int32_t reg32;
};

void FuseDev::fill_fuse_spare_bit_49_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const fuse_spare_bit_49_u old_value_t = { .reg32 = value };
    const fuse_spare_bit_49_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: spare_bit_49:1", "", 1, old_value_t.spare_bit_49, new_value_t.spare_bit_49 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_31:31", "", 31, old_value_t.undefined_bits_1_31, new_value_t.undefined_bits_1_31 };
    m_bit_details_model.bits.append(entry);
}

#define FUSE_SPARE_BIT_50_OFFSET 0x2C8
#define FUSE_SPARE_BIT_50_UNDEFMASK 0xFFFFFFFE
union fuse_spare_bit_50_u {
    struct {
        unsigned int spare_bit_50:1;
        unsigned int undefined_bits_1_31:31;
    };

    u_int32_t reg32;
};

void FuseDev::fill_fuse_spare_bit_50_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const fuse_spare_bit_50_u old_value_t = { .reg32 = value };
    const fuse_spare_bit_50_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: spare_bit_50:1", "", 1, old_value_t.spare_bit_50, new_value_t.spare_bit_50 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_31:31", "", 31, old_value_t.undefined_bits_1_31, new_value_t.undefined_bits_1_31 };
    m_bit_details_model.bits.append(entry);
}

#define FUSE_SPARE_BIT_51_OFFSET 0x2CC
#define FUSE_SPARE_BIT_51_UNDEFMASK 0xFFFFFFFE
union fuse_spare_bit_51_u {
    struct {
        unsigned int spare_bit_51:1;
        unsigned int undefined_bits_1_31:31;
    };

    u_int32_t reg32;
};

void FuseDev::fill_fuse_spare_bit_51_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const fuse_spare_bit_51_u old_value_t = { .reg32 = value };
    const fuse_spare_bit_51_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: spare_bit_51:1", "", 1, old_value_t.spare_bit_51, new_value_t.spare_bit_51 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_31:31", "", 31, old_value_t.undefined_bits_1_31, new_value_t.undefined_bits_1_31 };
    m_bit_details_model.bits.append(entry);
}

#define FUSE_SPARE_BIT_52_OFFSET 0x2D0
#define FUSE_SPARE_BIT_52_UNDEFMASK 0xFFFFFFFE
union fuse_spare_bit_52_u {
    struct {
        unsigned int spare_bit_52:1;
        unsigned int undefined_bits_1_31:31;
    };

    u_int32_t reg32;
};

void FuseDev::fill_fuse_spare_bit_52_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const fuse_spare_bit_52_u old_value_t = { .reg32 = value };
    const fuse_spare_bit_52_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: spare_bit_52:1", "", 1, old_value_t.spare_bit_52, new_value_t.spare_bit_52 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_31:31", "", 31, old_value_t.undefined_bits_1_31, new_value_t.undefined_bits_1_31 };
    m_bit_details_model.bits.append(entry);
}

#define FUSE_SPARE_BIT_53_OFFSET 0x2D4
#define FUSE_SPARE_BIT_53_UNDEFMASK 0xFFFFFFFE
union fuse_spare_bit_53_u {
    struct {
        unsigned int spare_bit_53:1;
        unsigned int undefined_bits_1_31:31;
    };

    u_int32_t reg32;
};

void FuseDev::fill_fuse_spare_bit_53_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const fuse_spare_bit_53_u old_value_t = { .reg32 = value };
    const fuse_spare_bit_53_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: spare_bit_53:1", "", 1, old_value_t.spare_bit_53, new_value_t.spare_bit_53 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_31:31", "", 31, old_value_t.undefined_bits_1_31, new_value_t.undefined_bits_1_31 };
    m_bit_details_model.bits.append(entry);
}

#define FUSE_SPARE_BIT_54_OFFSET 0x2D8
#define FUSE_SPARE_BIT_54_UNDEFMASK 0xFFFFFFFE
union fuse_spare_bit_54_u {
    struct {
        unsigned int spare_bit_54:1;
        unsigned int undefined_bits_1_31:31;
    };

    u_int32_t reg32;
};

void FuseDev::fill_fuse_spare_bit_54_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const fuse_spare_bit_54_u old_value_t = { .reg32 = value };
    const fuse_spare_bit_54_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: spare_bit_54:1", "", 1, old_value_t.spare_bit_54, new_value_t.spare_bit_54 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_31:31", "", 31, old_value_t.undefined_bits_1_31, new_value_t.undefined_bits_1_31 };
    m_bit_details_model.bits.append(entry);
}

#define FUSE_SPARE_BIT_55_OFFSET 0x2DC
#define FUSE_SPARE_BIT_55_UNDEFMASK 0xFFFFFFFE
union fuse_spare_bit_55_u {
    struct {
        unsigned int spare_bit_55:1;
        unsigned int undefined_bits_1_31:31;
    };

    u_int32_t reg32;
};

void FuseDev::fill_fuse_spare_bit_55_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const fuse_spare_bit_55_u old_value_t = { .reg32 = value };
    const fuse_spare_bit_55_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: spare_bit_55:1", "", 1, old_value_t.spare_bit_55, new_value_t.spare_bit_55 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_31:31", "", 31, old_value_t.undefined_bits_1_31, new_value_t.undefined_bits_1_31 };
    m_bit_details_model.bits.append(entry);
}

#define FUSE_SPARE_BIT_56_OFFSET 0x2E0
#define FUSE_SPARE_BIT_56_UNDEFMASK 0xFFFFFFFE
union fuse_spare_bit_56_u {
    struct {
        unsigned int spare_bit_56:1;
        unsigned int undefined_bits_1_31:31;
    };

    u_int32_t reg32;
};

void FuseDev::fill_fuse_spare_bit_56_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const fuse_spare_bit_56_u old_value_t = { .reg32 = value };
    const fuse_spare_bit_56_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: spare_bit_56:1", "", 1, old_value_t.spare_bit_56, new_value_t.spare_bit_56 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_31:31", "", 31, old_value_t.undefined_bits_1_31, new_value_t.undefined_bits_1_31 };
    m_bit_details_model.bits.append(entry);
}

#define FUSE_SPARE_BIT_57_OFFSET 0x2E4
#define FUSE_SPARE_BIT_57_UNDEFMASK 0xFFFFFFFE
union fuse_spare_bit_57_u {
    struct {
        unsigned int spare_bit_57:1;
        unsigned int undefined_bits_1_31:31;
    };

    u_int32_t reg32;
};

void FuseDev::fill_fuse_spare_bit_57_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const fuse_spare_bit_57_u old_value_t = { .reg32 = value };
    const fuse_spare_bit_57_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: spare_bit_57:1", "", 1, old_value_t.spare_bit_57, new_value_t.spare_bit_57 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_31:31", "", 31, old_value_t.undefined_bits_1_31, new_value_t.undefined_bits_1_31 };
    m_bit_details_model.bits.append(entry);
}

#define FUSE_SPARE_BIT_58_OFFSET 0x2E8
#define FUSE_SPARE_BIT_58_UNDEFMASK 0xFFFFFFFE
union fuse_spare_bit_58_u {
    struct {
        unsigned int spare_bit_58:1;
        unsigned int undefined_bits_1_31:31;
    };

    u_int32_t reg32;
};

void FuseDev::fill_fuse_spare_bit_58_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const fuse_spare_bit_58_u old_value_t = { .reg32 = value };
    const fuse_spare_bit_58_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: spare_bit_58:1", "", 1, old_value_t.spare_bit_58, new_value_t.spare_bit_58 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_31:31", "", 31, old_value_t.undefined_bits_1_31, new_value_t.undefined_bits_1_31 };
    m_bit_details_model.bits.append(entry);
}

#define FUSE_SPARE_BIT_59_OFFSET 0x2EC
#define FUSE_SPARE_BIT_59_UNDEFMASK 0xFFFFFFFE
union fuse_spare_bit_59_u {
    struct {
        unsigned int spare_bit_59:1;
        unsigned int undefined_bits_1_31:31;
    };

    u_int32_t reg32;
};

void FuseDev::fill_fuse_spare_bit_59_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const fuse_spare_bit_59_u old_value_t = { .reg32 = value };
    const fuse_spare_bit_59_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: spare_bit_59:1", "", 1, old_value_t.spare_bit_59, new_value_t.spare_bit_59 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_31:31", "", 31, old_value_t.undefined_bits_1_31, new_value_t.undefined_bits_1_31 };
    m_bit_details_model.bits.append(entry);
}

#define FUSE_SPARE_BIT_60_OFFSET 0x2F0
#define FUSE_SPARE_BIT_60_UNDEFMASK 0xFFFFFFFE
union fuse_spare_bit_60_u {
    struct {
        unsigned int spare_bit_60:1;
        unsigned int undefined_bits_1_31:31;
    };

    u_int32_t reg32;
};

void FuseDev::fill_fuse_spare_bit_60_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const fuse_spare_bit_60_u old_value_t = { .reg32 = value };
    const fuse_spare_bit_60_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: spare_bit_60:1", "", 1, old_value_t.spare_bit_60, new_value_t.spare_bit_60 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_31:31", "", 31, old_value_t.undefined_bits_1_31, new_value_t.undefined_bits_1_31 };
    m_bit_details_model.bits.append(entry);
}

#define FUSE_SPARE_BIT_61_OFFSET 0x2F4
#define FUSE_SPARE_BIT_61_UNDEFMASK 0xFFFFFFFE
union fuse_spare_bit_61_u {
    struct {
        unsigned int spare_bit_61:1;
        unsigned int undefined_bits_1_31:31;
    };

    u_int32_t reg32;
};

void FuseDev::fill_fuse_spare_bit_61_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const fuse_spare_bit_61_u old_value_t = { .reg32 = value };
    const fuse_spare_bit_61_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: spare_bit_61:1", "", 1, old_value_t.spare_bit_61, new_value_t.spare_bit_61 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_31:31", "", 31, old_value_t.undefined_bits_1_31, new_value_t.undefined_bits_1_31 };
    m_bit_details_model.bits.append(entry);
}

bool FuseDev::is_offset_valid(const u_int32_t &offset) const
{
    switch (offset) {
    case FUSE_FUSEBYPASS_OFFSET:
    case FUSE_WRITE_ACCESS_SW_OFFSET:
    case FUSE_JTAG_SECUREID_OFFSET:
    case FUSE_JTAG_SECUREID_1_OFFSET:
    case FUSE_SKU_INFO_OFFSET:
    case FUSE_PROCESS_CALIB_OFFSET:
    case FUSE_IO_CALIB_OFFSET:
    case FUSE_DAC_CRT_CALIB_OFFSET:
    case FUSE_DAC_HDTV_CALIB_OFFSET:
    case FUSE_DAC_SDTV_CALIB_OFFSET:
    case FUSE_RESERVED_PRODUCTION_OFFSET:
    case FUSE_SPARE_BIT_OFFSET:
    case FUSE_SPARE_BIT_1_OFFSET:
    case FUSE_SPARE_BIT_2_OFFSET:
    case FUSE_SPARE_BIT_3_OFFSET:
    case FUSE_SPARE_BIT_4_OFFSET:
    case FUSE_SPARE_BIT_5_OFFSET:
    case FUSE_SPARE_BIT_6_OFFSET:
    case FUSE_SPARE_BIT_7_OFFSET:
    case FUSE_SPARE_BIT_8_OFFSET:
    case FUSE_SPARE_BIT_9_OFFSET:
    case FUSE_SPARE_BIT_10_OFFSET:
    case FUSE_SPARE_BIT_11_OFFSET:
    case FUSE_SPARE_BIT_12_OFFSET:
    case FUSE_SPARE_BIT_13_OFFSET:
    case FUSE_SPARE_BIT_14_OFFSET:
    case FUSE_SPARE_BIT_15_OFFSET:
    case FUSE_SPARE_BIT_16_OFFSET:
    case FUSE_SPARE_BIT_17_OFFSET:
    case FUSE_SPARE_BIT_18_OFFSET:
    case FUSE_SPARE_BIT_19_OFFSET:
    case FUSE_SPARE_BIT_20_OFFSET:
    case FUSE_SPARE_BIT_21_OFFSET:
    case FUSE_SPARE_BIT_22_OFFSET:
    case FUSE_SPARE_BIT_23_OFFSET:
    case FUSE_SPARE_BIT_24_OFFSET:
    case FUSE_SPARE_BIT_25_OFFSET:
    case FUSE_SPARE_BIT_26_OFFSET:
    case FUSE_SPARE_BIT_27_OFFSET:
    case FUSE_SPARE_BIT_28_OFFSET:
    case FUSE_SPARE_BIT_29_OFFSET:
    case FUSE_SPARE_BIT_30_OFFSET:
    case FUSE_SPARE_BIT_31_OFFSET:
    case FUSE_SPARE_BIT_32_OFFSET:
    case FUSE_SPARE_BIT_33_OFFSET:
    case FUSE_SPARE_BIT_34_OFFSET:
    case FUSE_SPARE_BIT_35_OFFSET:
    case FUSE_SPARE_BIT_36_OFFSET:
    case FUSE_SPARE_BIT_37_OFFSET:
    case FUSE_SPARE_BIT_38_OFFSET:
    case FUSE_SPARE_BIT_39_OFFSET:
    case FUSE_SPARE_BIT_40_OFFSET:
    case FUSE_SPARE_BIT_41_OFFSET:
    case FUSE_SPARE_BIT_42_OFFSET:
    case FUSE_SPARE_BIT_43_OFFSET:
    case FUSE_SPARE_BIT_44_OFFSET:
    case FUSE_SPARE_BIT_45_OFFSET:
    case FUSE_SPARE_BIT_46_OFFSET:
    case FUSE_SPARE_BIT_47_OFFSET:
    case FUSE_SPARE_BIT_48_OFFSET:
    case FUSE_SPARE_BIT_49_OFFSET:
    case FUSE_SPARE_BIT_50_OFFSET:
    case FUSE_SPARE_BIT_51_OFFSET:
    case FUSE_SPARE_BIT_52_OFFSET:
    case FUSE_SPARE_BIT_53_OFFSET:
    case FUSE_SPARE_BIT_54_OFFSET:
    case FUSE_SPARE_BIT_55_OFFSET:
    case FUSE_SPARE_BIT_56_OFFSET:
    case FUSE_SPARE_BIT_57_OFFSET:
    case FUSE_SPARE_BIT_58_OFFSET:
    case FUSE_SPARE_BIT_59_OFFSET:
    case FUSE_SPARE_BIT_60_OFFSET:
    case FUSE_SPARE_BIT_61_OFFSET:
        return true;
    default:
        break;
    }

    return false;
}

bool FuseDev::is_undef_changed(const u_int32_t &offset,
                                           const u_int32_t &value,
                                           const u_int32_t &new_value) const
{
    switch (offset) {
    case FUSE_FUSEBYPASS_OFFSET:
        if ((value ^ new_value) & FUSE_FUSEBYPASS_UNDEFMASK)
            return true;
        break;
    case FUSE_WRITE_ACCESS_SW_OFFSET:
        if ((value ^ new_value) & FUSE_WRITE_ACCESS_SW_UNDEFMASK)
            return true;
        break;
    case FUSE_JTAG_SECUREID_OFFSET:
        if ((value ^ new_value) & FUSE_JTAG_SECUREID_UNDEFMASK)
            return true;
        break;
    case FUSE_JTAG_SECUREID_1_OFFSET:
        if ((value ^ new_value) & FUSE_JTAG_SECUREID_1_UNDEFMASK)
            return true;
        break;
    case FUSE_SKU_INFO_OFFSET:
        if ((value ^ new_value) & FUSE_SKU_INFO_UNDEFMASK)
            return true;
        break;
    case FUSE_PROCESS_CALIB_OFFSET:
        if ((value ^ new_value) & FUSE_PROCESS_CALIB_UNDEFMASK)
            return true;
        break;
    case FUSE_IO_CALIB_OFFSET:
        if ((value ^ new_value) & FUSE_IO_CALIB_UNDEFMASK)
            return true;
        break;
    case FUSE_DAC_CRT_CALIB_OFFSET:
        if ((value ^ new_value) & FUSE_DAC_CRT_CALIB_UNDEFMASK)
            return true;
        break;
    case FUSE_DAC_HDTV_CALIB_OFFSET:
        if ((value ^ new_value) & FUSE_DAC_HDTV_CALIB_UNDEFMASK)
            return true;
        break;
    case FUSE_DAC_SDTV_CALIB_OFFSET:
        if ((value ^ new_value) & FUSE_DAC_SDTV_CALIB_UNDEFMASK)
            return true;
        break;
    case FUSE_RESERVED_PRODUCTION_OFFSET:
        if ((value ^ new_value) & FUSE_RESERVED_PRODUCTION_UNDEFMASK)
            return true;
        break;
    case FUSE_SPARE_BIT_OFFSET:
        if ((value ^ new_value) & FUSE_SPARE_BIT_UNDEFMASK)
            return true;
        break;
    case FUSE_SPARE_BIT_1_OFFSET:
        if ((value ^ new_value) & FUSE_SPARE_BIT_1_UNDEFMASK)
            return true;
        break;
    case FUSE_SPARE_BIT_2_OFFSET:
        if ((value ^ new_value) & FUSE_SPARE_BIT_2_UNDEFMASK)
            return true;
        break;
    case FUSE_SPARE_BIT_3_OFFSET:
        if ((value ^ new_value) & FUSE_SPARE_BIT_3_UNDEFMASK)
            return true;
        break;
    case FUSE_SPARE_BIT_4_OFFSET:
        if ((value ^ new_value) & FUSE_SPARE_BIT_4_UNDEFMASK)
            return true;
        break;
    case FUSE_SPARE_BIT_5_OFFSET:
        if ((value ^ new_value) & FUSE_SPARE_BIT_5_UNDEFMASK)
            return true;
        break;
    case FUSE_SPARE_BIT_6_OFFSET:
        if ((value ^ new_value) & FUSE_SPARE_BIT_6_UNDEFMASK)
            return true;
        break;
    case FUSE_SPARE_BIT_7_OFFSET:
        if ((value ^ new_value) & FUSE_SPARE_BIT_7_UNDEFMASK)
            return true;
        break;
    case FUSE_SPARE_BIT_8_OFFSET:
        if ((value ^ new_value) & FUSE_SPARE_BIT_8_UNDEFMASK)
            return true;
        break;
    case FUSE_SPARE_BIT_9_OFFSET:
        if ((value ^ new_value) & FUSE_SPARE_BIT_9_UNDEFMASK)
            return true;
        break;
    case FUSE_SPARE_BIT_10_OFFSET:
        if ((value ^ new_value) & FUSE_SPARE_BIT_10_UNDEFMASK)
            return true;
        break;
    case FUSE_SPARE_BIT_11_OFFSET:
        if ((value ^ new_value) & FUSE_SPARE_BIT_11_UNDEFMASK)
            return true;
        break;
    case FUSE_SPARE_BIT_12_OFFSET:
        if ((value ^ new_value) & FUSE_SPARE_BIT_12_UNDEFMASK)
            return true;
        break;
    case FUSE_SPARE_BIT_13_OFFSET:
        if ((value ^ new_value) & FUSE_SPARE_BIT_13_UNDEFMASK)
            return true;
        break;
    case FUSE_SPARE_BIT_14_OFFSET:
        if ((value ^ new_value) & FUSE_SPARE_BIT_14_UNDEFMASK)
            return true;
        break;
    case FUSE_SPARE_BIT_15_OFFSET:
        if ((value ^ new_value) & FUSE_SPARE_BIT_15_UNDEFMASK)
            return true;
        break;
    case FUSE_SPARE_BIT_16_OFFSET:
        if ((value ^ new_value) & FUSE_SPARE_BIT_16_UNDEFMASK)
            return true;
        break;
    case FUSE_SPARE_BIT_17_OFFSET:
        if ((value ^ new_value) & FUSE_SPARE_BIT_17_UNDEFMASK)
            return true;
        break;
    case FUSE_SPARE_BIT_18_OFFSET:
        if ((value ^ new_value) & FUSE_SPARE_BIT_18_UNDEFMASK)
            return true;
        break;
    case FUSE_SPARE_BIT_19_OFFSET:
        if ((value ^ new_value) & FUSE_SPARE_BIT_19_UNDEFMASK)
            return true;
        break;
    case FUSE_SPARE_BIT_20_OFFSET:
        if ((value ^ new_value) & FUSE_SPARE_BIT_20_UNDEFMASK)
            return true;
        break;
    case FUSE_SPARE_BIT_21_OFFSET:
        if ((value ^ new_value) & FUSE_SPARE_BIT_21_UNDEFMASK)
            return true;
        break;
    case FUSE_SPARE_BIT_22_OFFSET:
        if ((value ^ new_value) & FUSE_SPARE_BIT_22_UNDEFMASK)
            return true;
        break;
    case FUSE_SPARE_BIT_23_OFFSET:
        if ((value ^ new_value) & FUSE_SPARE_BIT_23_UNDEFMASK)
            return true;
        break;
    case FUSE_SPARE_BIT_24_OFFSET:
        if ((value ^ new_value) & FUSE_SPARE_BIT_24_UNDEFMASK)
            return true;
        break;
    case FUSE_SPARE_BIT_25_OFFSET:
        if ((value ^ new_value) & FUSE_SPARE_BIT_25_UNDEFMASK)
            return true;
        break;
    case FUSE_SPARE_BIT_26_OFFSET:
        if ((value ^ new_value) & FUSE_SPARE_BIT_26_UNDEFMASK)
            return true;
        break;
    case FUSE_SPARE_BIT_27_OFFSET:
        if ((value ^ new_value) & FUSE_SPARE_BIT_27_UNDEFMASK)
            return true;
        break;
    case FUSE_SPARE_BIT_28_OFFSET:
        if ((value ^ new_value) & FUSE_SPARE_BIT_28_UNDEFMASK)
            return true;
        break;
    case FUSE_SPARE_BIT_29_OFFSET:
        if ((value ^ new_value) & FUSE_SPARE_BIT_29_UNDEFMASK)
            return true;
        break;
    case FUSE_SPARE_BIT_30_OFFSET:
        if ((value ^ new_value) & FUSE_SPARE_BIT_30_UNDEFMASK)
            return true;
        break;
    case FUSE_SPARE_BIT_31_OFFSET:
        if ((value ^ new_value) & FUSE_SPARE_BIT_31_UNDEFMASK)
            return true;
        break;
    case FUSE_SPARE_BIT_32_OFFSET:
        if ((value ^ new_value) & FUSE_SPARE_BIT_32_UNDEFMASK)
            return true;
        break;
    case FUSE_SPARE_BIT_33_OFFSET:
        if ((value ^ new_value) & FUSE_SPARE_BIT_33_UNDEFMASK)
            return true;
        break;
    case FUSE_SPARE_BIT_34_OFFSET:
        if ((value ^ new_value) & FUSE_SPARE_BIT_34_UNDEFMASK)
            return true;
        break;
    case FUSE_SPARE_BIT_35_OFFSET:
        if ((value ^ new_value) & FUSE_SPARE_BIT_35_UNDEFMASK)
            return true;
        break;
    case FUSE_SPARE_BIT_36_OFFSET:
        if ((value ^ new_value) & FUSE_SPARE_BIT_36_UNDEFMASK)
            return true;
        break;
    case FUSE_SPARE_BIT_37_OFFSET:
        if ((value ^ new_value) & FUSE_SPARE_BIT_37_UNDEFMASK)
            return true;
        break;
    case FUSE_SPARE_BIT_38_OFFSET:
        if ((value ^ new_value) & FUSE_SPARE_BIT_38_UNDEFMASK)
            return true;
        break;
    case FUSE_SPARE_BIT_39_OFFSET:
        if ((value ^ new_value) & FUSE_SPARE_BIT_39_UNDEFMASK)
            return true;
        break;
    case FUSE_SPARE_BIT_40_OFFSET:
        if ((value ^ new_value) & FUSE_SPARE_BIT_40_UNDEFMASK)
            return true;
        break;
    case FUSE_SPARE_BIT_41_OFFSET:
        if ((value ^ new_value) & FUSE_SPARE_BIT_41_UNDEFMASK)
            return true;
        break;
    case FUSE_SPARE_BIT_42_OFFSET:
        if ((value ^ new_value) & FUSE_SPARE_BIT_42_UNDEFMASK)
            return true;
        break;
    case FUSE_SPARE_BIT_43_OFFSET:
        if ((value ^ new_value) & FUSE_SPARE_BIT_43_UNDEFMASK)
            return true;
        break;
    case FUSE_SPARE_BIT_44_OFFSET:
        if ((value ^ new_value) & FUSE_SPARE_BIT_44_UNDEFMASK)
            return true;
        break;
    case FUSE_SPARE_BIT_45_OFFSET:
        if ((value ^ new_value) & FUSE_SPARE_BIT_45_UNDEFMASK)
            return true;
        break;
    case FUSE_SPARE_BIT_46_OFFSET:
        if ((value ^ new_value) & FUSE_SPARE_BIT_46_UNDEFMASK)
            return true;
        break;
    case FUSE_SPARE_BIT_47_OFFSET:
        if ((value ^ new_value) & FUSE_SPARE_BIT_47_UNDEFMASK)
            return true;
        break;
    case FUSE_SPARE_BIT_48_OFFSET:
        if ((value ^ new_value) & FUSE_SPARE_BIT_48_UNDEFMASK)
            return true;
        break;
    case FUSE_SPARE_BIT_49_OFFSET:
        if ((value ^ new_value) & FUSE_SPARE_BIT_49_UNDEFMASK)
            return true;
        break;
    case FUSE_SPARE_BIT_50_OFFSET:
        if ((value ^ new_value) & FUSE_SPARE_BIT_50_UNDEFMASK)
            return true;
        break;
    case FUSE_SPARE_BIT_51_OFFSET:
        if ((value ^ new_value) & FUSE_SPARE_BIT_51_UNDEFMASK)
            return true;
        break;
    case FUSE_SPARE_BIT_52_OFFSET:
        if ((value ^ new_value) & FUSE_SPARE_BIT_52_UNDEFMASK)
            return true;
        break;
    case FUSE_SPARE_BIT_53_OFFSET:
        if ((value ^ new_value) & FUSE_SPARE_BIT_53_UNDEFMASK)
            return true;
        break;
    case FUSE_SPARE_BIT_54_OFFSET:
        if ((value ^ new_value) & FUSE_SPARE_BIT_54_UNDEFMASK)
            return true;
        break;
    case FUSE_SPARE_BIT_55_OFFSET:
        if ((value ^ new_value) & FUSE_SPARE_BIT_55_UNDEFMASK)
            return true;
        break;
    case FUSE_SPARE_BIT_56_OFFSET:
        if ((value ^ new_value) & FUSE_SPARE_BIT_56_UNDEFMASK)
            return true;
        break;
    case FUSE_SPARE_BIT_57_OFFSET:
        if ((value ^ new_value) & FUSE_SPARE_BIT_57_UNDEFMASK)
            return true;
        break;
    case FUSE_SPARE_BIT_58_OFFSET:
        if ((value ^ new_value) & FUSE_SPARE_BIT_58_UNDEFMASK)
            return true;
        break;
    case FUSE_SPARE_BIT_59_OFFSET:
        if ((value ^ new_value) & FUSE_SPARE_BIT_59_UNDEFMASK)
            return true;
        break;
    case FUSE_SPARE_BIT_60_OFFSET:
        if ((value ^ new_value) & FUSE_SPARE_BIT_60_UNDEFMASK)
            return true;
        break;
    case FUSE_SPARE_BIT_61_OFFSET:
        if ((value ^ new_value) & FUSE_SPARE_BIT_61_UNDEFMASK)
            return true;
        break;

    default:
        break;
    }

    return false;
}

QString FuseDev::get_register_name(const log_entry &entry) const
{
    switch (entry.offset) {
    case FUSE_FUSEBYPASS_OFFSET:
        return QString("FUSE_FUSEBYPASS");
    case FUSE_WRITE_ACCESS_SW_OFFSET:
        return QString("FUSE_WRITE_ACCESS_SW");
    case FUSE_JTAG_SECUREID_OFFSET:
        return QString("FUSE_JTAG_SECUREID");
    case FUSE_JTAG_SECUREID_1_OFFSET:
        return QString("FUSE_JTAG_SECUREID_1");
    case FUSE_SKU_INFO_OFFSET:
        return QString("FUSE_SKU_INFO");
    case FUSE_PROCESS_CALIB_OFFSET:
        return QString("FUSE_PROCESS_CALIB");
    case FUSE_IO_CALIB_OFFSET:
        return QString("FUSE_IO_CALIB");
    case FUSE_DAC_CRT_CALIB_OFFSET:
        return QString("FUSE_DAC_CRT_CALIB");
    case FUSE_DAC_HDTV_CALIB_OFFSET:
        return QString("FUSE_DAC_HDTV_CALIB");
    case FUSE_DAC_SDTV_CALIB_OFFSET:
        return QString("FUSE_DAC_SDTV_CALIB");
    case FUSE_RESERVED_PRODUCTION_OFFSET:
        return QString("FUSE_RESERVED_PRODUCTION");
    case FUSE_SPARE_BIT_OFFSET:
        return QString("FUSE_SPARE_BIT");
    case FUSE_SPARE_BIT_1_OFFSET:
        return QString("FUSE_SPARE_BIT_1");
    case FUSE_SPARE_BIT_2_OFFSET:
        return QString("FUSE_SPARE_BIT_2");
    case FUSE_SPARE_BIT_3_OFFSET:
        return QString("FUSE_SPARE_BIT_3");
    case FUSE_SPARE_BIT_4_OFFSET:
        return QString("FUSE_SPARE_BIT_4");
    case FUSE_SPARE_BIT_5_OFFSET:
        return QString("FUSE_SPARE_BIT_5");
    case FUSE_SPARE_BIT_6_OFFSET:
        return QString("FUSE_SPARE_BIT_6");
    case FUSE_SPARE_BIT_7_OFFSET:
        return QString("FUSE_SPARE_BIT_7");
    case FUSE_SPARE_BIT_8_OFFSET:
        return QString("FUSE_SPARE_BIT_8");
    case FUSE_SPARE_BIT_9_OFFSET:
        return QString("FUSE_SPARE_BIT_9");
    case FUSE_SPARE_BIT_10_OFFSET:
        return QString("FUSE_SPARE_BIT_10");
    case FUSE_SPARE_BIT_11_OFFSET:
        return QString("FUSE_SPARE_BIT_11");
    case FUSE_SPARE_BIT_12_OFFSET:
        return QString("FUSE_SPARE_BIT_12");
    case FUSE_SPARE_BIT_13_OFFSET:
        return QString("FUSE_SPARE_BIT_13");
    case FUSE_SPARE_BIT_14_OFFSET:
        return QString("FUSE_SPARE_BIT_14");
    case FUSE_SPARE_BIT_15_OFFSET:
        return QString("FUSE_SPARE_BIT_15");
    case FUSE_SPARE_BIT_16_OFFSET:
        return QString("FUSE_SPARE_BIT_16");
    case FUSE_SPARE_BIT_17_OFFSET:
        return QString("FUSE_SPARE_BIT_17");
    case FUSE_SPARE_BIT_18_OFFSET:
        return QString("FUSE_SPARE_BIT_18");
    case FUSE_SPARE_BIT_19_OFFSET:
        return QString("FUSE_SPARE_BIT_19");
    case FUSE_SPARE_BIT_20_OFFSET:
        return QString("FUSE_SPARE_BIT_20");
    case FUSE_SPARE_BIT_21_OFFSET:
        return QString("FUSE_SPARE_BIT_21");
    case FUSE_SPARE_BIT_22_OFFSET:
        return QString("FUSE_SPARE_BIT_22");
    case FUSE_SPARE_BIT_23_OFFSET:
        return QString("FUSE_SPARE_BIT_23");
    case FUSE_SPARE_BIT_24_OFFSET:
        return QString("FUSE_SPARE_BIT_24");
    case FUSE_SPARE_BIT_25_OFFSET:
        return QString("FUSE_SPARE_BIT_25");
    case FUSE_SPARE_BIT_26_OFFSET:
        return QString("FUSE_SPARE_BIT_26");
    case FUSE_SPARE_BIT_27_OFFSET:
        return QString("FUSE_SPARE_BIT_27");
    case FUSE_SPARE_BIT_28_OFFSET:
        return QString("FUSE_SPARE_BIT_28");
    case FUSE_SPARE_BIT_29_OFFSET:
        return QString("FUSE_SPARE_BIT_29");
    case FUSE_SPARE_BIT_30_OFFSET:
        return QString("FUSE_SPARE_BIT_30");
    case FUSE_SPARE_BIT_31_OFFSET:
        return QString("FUSE_SPARE_BIT_31");
    case FUSE_SPARE_BIT_32_OFFSET:
        return QString("FUSE_SPARE_BIT_32");
    case FUSE_SPARE_BIT_33_OFFSET:
        return QString("FUSE_SPARE_BIT_33");
    case FUSE_SPARE_BIT_34_OFFSET:
        return QString("FUSE_SPARE_BIT_34");
    case FUSE_SPARE_BIT_35_OFFSET:
        return QString("FUSE_SPARE_BIT_35");
    case FUSE_SPARE_BIT_36_OFFSET:
        return QString("FUSE_SPARE_BIT_36");
    case FUSE_SPARE_BIT_37_OFFSET:
        return QString("FUSE_SPARE_BIT_37");
    case FUSE_SPARE_BIT_38_OFFSET:
        return QString("FUSE_SPARE_BIT_38");
    case FUSE_SPARE_BIT_39_OFFSET:
        return QString("FUSE_SPARE_BIT_39");
    case FUSE_SPARE_BIT_40_OFFSET:
        return QString("FUSE_SPARE_BIT_40");
    case FUSE_SPARE_BIT_41_OFFSET:
        return QString("FUSE_SPARE_BIT_41");
    case FUSE_SPARE_BIT_42_OFFSET:
        return QString("FUSE_SPARE_BIT_42");
    case FUSE_SPARE_BIT_43_OFFSET:
        return QString("FUSE_SPARE_BIT_43");
    case FUSE_SPARE_BIT_44_OFFSET:
        return QString("FUSE_SPARE_BIT_44");
    case FUSE_SPARE_BIT_45_OFFSET:
        return QString("FUSE_SPARE_BIT_45");
    case FUSE_SPARE_BIT_46_OFFSET:
        return QString("FUSE_SPARE_BIT_46");
    case FUSE_SPARE_BIT_47_OFFSET:
        return QString("FUSE_SPARE_BIT_47");
    case FUSE_SPARE_BIT_48_OFFSET:
        return QString("FUSE_SPARE_BIT_48");
    case FUSE_SPARE_BIT_49_OFFSET:
        return QString("FUSE_SPARE_BIT_49");
    case FUSE_SPARE_BIT_50_OFFSET:
        return QString("FUSE_SPARE_BIT_50");
    case FUSE_SPARE_BIT_51_OFFSET:
        return QString("FUSE_SPARE_BIT_51");
    case FUSE_SPARE_BIT_52_OFFSET:
        return QString("FUSE_SPARE_BIT_52");
    case FUSE_SPARE_BIT_53_OFFSET:
        return QString("FUSE_SPARE_BIT_53");
    case FUSE_SPARE_BIT_54_OFFSET:
        return QString("FUSE_SPARE_BIT_54");
    case FUSE_SPARE_BIT_55_OFFSET:
        return QString("FUSE_SPARE_BIT_55");
    case FUSE_SPARE_BIT_56_OFFSET:
        return QString("FUSE_SPARE_BIT_56");
    case FUSE_SPARE_BIT_57_OFFSET:
        return QString("FUSE_SPARE_BIT_57");
    case FUSE_SPARE_BIT_58_OFFSET:
        return QString("FUSE_SPARE_BIT_58");
    case FUSE_SPARE_BIT_59_OFFSET:
        return QString("FUSE_SPARE_BIT_59");
    case FUSE_SPARE_BIT_60_OFFSET:
        return QString("FUSE_SPARE_BIT_60");
    case FUSE_SPARE_BIT_61_OFFSET:
        return QString("FUSE_SPARE_BIT_61");

    default:
        break;
    }

    qDebug() << QString().sprintf("FUSE: %s: Ooops... 0x%x", __func__, entry.offset);

    return QString().sprintf("Ooops... @0x%X", entry.offset);
}

void FuseDev::fill_bits_details(const u_int32_t &offset,
                                      const u_int32_t &value, const u_int32_t &new_value)
{
    switch (offset) {
    case FUSE_FUSEBYPASS_OFFSET:
        fill_fuse_fusebypass_details(value, new_value);
        break;
    case FUSE_WRITE_ACCESS_SW_OFFSET:
        fill_fuse_write_access_sw_details(value, new_value);
        break;
    case FUSE_JTAG_SECUREID_OFFSET:
        fill_fuse_jtag_secureid_details(value, new_value);
        break;
    case FUSE_JTAG_SECUREID_1_OFFSET:
        fill_fuse_jtag_secureid_1_details(value, new_value);
        break;
    case FUSE_SKU_INFO_OFFSET:
        fill_fuse_sku_info_details(value, new_value);
        break;
    case FUSE_PROCESS_CALIB_OFFSET:
        fill_fuse_process_calib_details(value, new_value);
        break;
    case FUSE_IO_CALIB_OFFSET:
        fill_fuse_io_calib_details(value, new_value);
        break;
    case FUSE_DAC_CRT_CALIB_OFFSET:
        fill_fuse_dac_crt_calib_details(value, new_value);
        break;
    case FUSE_DAC_HDTV_CALIB_OFFSET:
        fill_fuse_dac_hdtv_calib_details(value, new_value);
        break;
    case FUSE_DAC_SDTV_CALIB_OFFSET:
        fill_fuse_dac_sdtv_calib_details(value, new_value);
        break;
    case FUSE_RESERVED_PRODUCTION_OFFSET:
        fill_fuse_reserved_production_details(value, new_value);
        break;
    case FUSE_SPARE_BIT_OFFSET:
        fill_fuse_spare_bit_details(value, new_value);
        break;
    case FUSE_SPARE_BIT_1_OFFSET:
        fill_fuse_spare_bit_1_details(value, new_value);
        break;
    case FUSE_SPARE_BIT_2_OFFSET:
        fill_fuse_spare_bit_2_details(value, new_value);
        break;
    case FUSE_SPARE_BIT_3_OFFSET:
        fill_fuse_spare_bit_3_details(value, new_value);
        break;
    case FUSE_SPARE_BIT_4_OFFSET:
        fill_fuse_spare_bit_4_details(value, new_value);
        break;
    case FUSE_SPARE_BIT_5_OFFSET:
        fill_fuse_spare_bit_5_details(value, new_value);
        break;
    case FUSE_SPARE_BIT_6_OFFSET:
        fill_fuse_spare_bit_6_details(value, new_value);
        break;
    case FUSE_SPARE_BIT_7_OFFSET:
        fill_fuse_spare_bit_7_details(value, new_value);
        break;
    case FUSE_SPARE_BIT_8_OFFSET:
        fill_fuse_spare_bit_8_details(value, new_value);
        break;
    case FUSE_SPARE_BIT_9_OFFSET:
        fill_fuse_spare_bit_9_details(value, new_value);
        break;
    case FUSE_SPARE_BIT_10_OFFSET:
        fill_fuse_spare_bit_10_details(value, new_value);
        break;
    case FUSE_SPARE_BIT_11_OFFSET:
        fill_fuse_spare_bit_11_details(value, new_value);
        break;
    case FUSE_SPARE_BIT_12_OFFSET:
        fill_fuse_spare_bit_12_details(value, new_value);
        break;
    case FUSE_SPARE_BIT_13_OFFSET:
        fill_fuse_spare_bit_13_details(value, new_value);
        break;
    case FUSE_SPARE_BIT_14_OFFSET:
        fill_fuse_spare_bit_14_details(value, new_value);
        break;
    case FUSE_SPARE_BIT_15_OFFSET:
        fill_fuse_spare_bit_15_details(value, new_value);
        break;
    case FUSE_SPARE_BIT_16_OFFSET:
        fill_fuse_spare_bit_16_details(value, new_value);
        break;
    case FUSE_SPARE_BIT_17_OFFSET:
        fill_fuse_spare_bit_17_details(value, new_value);
        break;
    case FUSE_SPARE_BIT_18_OFFSET:
        fill_fuse_spare_bit_18_details(value, new_value);
        break;
    case FUSE_SPARE_BIT_19_OFFSET:
        fill_fuse_spare_bit_19_details(value, new_value);
        break;
    case FUSE_SPARE_BIT_20_OFFSET:
        fill_fuse_spare_bit_20_details(value, new_value);
        break;
    case FUSE_SPARE_BIT_21_OFFSET:
        fill_fuse_spare_bit_21_details(value, new_value);
        break;
    case FUSE_SPARE_BIT_22_OFFSET:
        fill_fuse_spare_bit_22_details(value, new_value);
        break;
    case FUSE_SPARE_BIT_23_OFFSET:
        fill_fuse_spare_bit_23_details(value, new_value);
        break;
    case FUSE_SPARE_BIT_24_OFFSET:
        fill_fuse_spare_bit_24_details(value, new_value);
        break;
    case FUSE_SPARE_BIT_25_OFFSET:
        fill_fuse_spare_bit_25_details(value, new_value);
        break;
    case FUSE_SPARE_BIT_26_OFFSET:
        fill_fuse_spare_bit_26_details(value, new_value);
        break;
    case FUSE_SPARE_BIT_27_OFFSET:
        fill_fuse_spare_bit_27_details(value, new_value);
        break;
    case FUSE_SPARE_BIT_28_OFFSET:
        fill_fuse_spare_bit_28_details(value, new_value);
        break;
    case FUSE_SPARE_BIT_29_OFFSET:
        fill_fuse_spare_bit_29_details(value, new_value);
        break;
    case FUSE_SPARE_BIT_30_OFFSET:
        fill_fuse_spare_bit_30_details(value, new_value);
        break;
    case FUSE_SPARE_BIT_31_OFFSET:
        fill_fuse_spare_bit_31_details(value, new_value);
        break;
    case FUSE_SPARE_BIT_32_OFFSET:
        fill_fuse_spare_bit_32_details(value, new_value);
        break;
    case FUSE_SPARE_BIT_33_OFFSET:
        fill_fuse_spare_bit_33_details(value, new_value);
        break;
    case FUSE_SPARE_BIT_34_OFFSET:
        fill_fuse_spare_bit_34_details(value, new_value);
        break;
    case FUSE_SPARE_BIT_35_OFFSET:
        fill_fuse_spare_bit_35_details(value, new_value);
        break;
    case FUSE_SPARE_BIT_36_OFFSET:
        fill_fuse_spare_bit_36_details(value, new_value);
        break;
    case FUSE_SPARE_BIT_37_OFFSET:
        fill_fuse_spare_bit_37_details(value, new_value);
        break;
    case FUSE_SPARE_BIT_38_OFFSET:
        fill_fuse_spare_bit_38_details(value, new_value);
        break;
    case FUSE_SPARE_BIT_39_OFFSET:
        fill_fuse_spare_bit_39_details(value, new_value);
        break;
    case FUSE_SPARE_BIT_40_OFFSET:
        fill_fuse_spare_bit_40_details(value, new_value);
        break;
    case FUSE_SPARE_BIT_41_OFFSET:
        fill_fuse_spare_bit_41_details(value, new_value);
        break;
    case FUSE_SPARE_BIT_42_OFFSET:
        fill_fuse_spare_bit_42_details(value, new_value);
        break;
    case FUSE_SPARE_BIT_43_OFFSET:
        fill_fuse_spare_bit_43_details(value, new_value);
        break;
    case FUSE_SPARE_BIT_44_OFFSET:
        fill_fuse_spare_bit_44_details(value, new_value);
        break;
    case FUSE_SPARE_BIT_45_OFFSET:
        fill_fuse_spare_bit_45_details(value, new_value);
        break;
    case FUSE_SPARE_BIT_46_OFFSET:
        fill_fuse_spare_bit_46_details(value, new_value);
        break;
    case FUSE_SPARE_BIT_47_OFFSET:
        fill_fuse_spare_bit_47_details(value, new_value);
        break;
    case FUSE_SPARE_BIT_48_OFFSET:
        fill_fuse_spare_bit_48_details(value, new_value);
        break;
    case FUSE_SPARE_BIT_49_OFFSET:
        fill_fuse_spare_bit_49_details(value, new_value);
        break;
    case FUSE_SPARE_BIT_50_OFFSET:
        fill_fuse_spare_bit_50_details(value, new_value);
        break;
    case FUSE_SPARE_BIT_51_OFFSET:
        fill_fuse_spare_bit_51_details(value, new_value);
        break;
    case FUSE_SPARE_BIT_52_OFFSET:
        fill_fuse_spare_bit_52_details(value, new_value);
        break;
    case FUSE_SPARE_BIT_53_OFFSET:
        fill_fuse_spare_bit_53_details(value, new_value);
        break;
    case FUSE_SPARE_BIT_54_OFFSET:
        fill_fuse_spare_bit_54_details(value, new_value);
        break;
    case FUSE_SPARE_BIT_55_OFFSET:
        fill_fuse_spare_bit_55_details(value, new_value);
        break;
    case FUSE_SPARE_BIT_56_OFFSET:
        fill_fuse_spare_bit_56_details(value, new_value);
        break;
    case FUSE_SPARE_BIT_57_OFFSET:
        fill_fuse_spare_bit_57_details(value, new_value);
        break;
    case FUSE_SPARE_BIT_58_OFFSET:
        fill_fuse_spare_bit_58_details(value, new_value);
        break;
    case FUSE_SPARE_BIT_59_OFFSET:
        fill_fuse_spare_bit_59_details(value, new_value);
        break;
    case FUSE_SPARE_BIT_60_OFFSET:
        fill_fuse_spare_bit_60_details(value, new_value);
        break;
    case FUSE_SPARE_BIT_61_OFFSET:
        fill_fuse_spare_bit_61_details(value, new_value);
        break;

    default:
        m_bit_details_model.bits.clear();
        break;
    }
}
