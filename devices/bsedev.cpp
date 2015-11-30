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

#include "bsedev.h"

#include <QDebug>

#define CMD_BLKSTARTENGINE  0x0E
#define CMD_DMASETUP        0x10
#define CMD_DMACOMPLETE     0x11
#define CMD_SETTABLE        0x15
#define CMD_MEMDMAVD        0x22

typedef union bse_cmd_setup_table {
    struct {
        unsigned int key_table_phy_addr:17;
        unsigned int key_table_id:7;
        unsigned int table_select:2;
        unsigned int opcode:6;
    };

    u_int32_t reg32;
} bse_cmd_setup_table_t;

typedef union bse_cmd_block_count {
    struct {
        unsigned int block_count:26;
        unsigned int opcode:6;
    };

    u_int32_t reg32;
} bse_cmd_block_count_t;

#define ICMDQUE_WR_OFFSET 0x0
#define ICMDQUE_WR_UNDEFMASK 0x00000000
union icmdque_wr_u {
    struct {
        unsigned int icmdque_wdata:32;
    };

    u_int32_t reg32;
};

void BseDev::fill_icmdque_wr_details(const u_int32_t &, const u_int32_t &new_value)
{
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = false;

    switch (new_value >> 26) {
    case CMD_SETTABLE: {
        const bse_cmd_setup_table_t st = { .reg32 = new_value };
        entry = { "00: key_table_phy_addr:17", "", 17, st.key_table_phy_addr, st.key_table_phy_addr };
        m_bit_details_model.bits.append(entry);
        entry = { "17: key_table_id:7", "", 7, st.key_table_id, st.key_table_id };
        m_bit_details_model.bits.append(entry);
        entry = { "24: table_select:2", "", 2, st.table_select, st.table_select };
        m_bit_details_model.bits.append(entry);
        entry = { "26: opcode:6", "", 6, st.opcode, st.opcode };
        m_bit_details_model.bits.append(entry);
        break;
    }
    case CMD_BLKSTARTENGINE: {
        const bse_cmd_block_count_t bc = { .reg32 = new_value };
        entry = { "00: block_count:26", "", 26, bc.block_count, bc.block_count };
        m_bit_details_model.bits.append(entry);
        entry = { "26: opcode:6", "", 6, bc.opcode, bc.opcode };
        m_bit_details_model.bits.append(entry);
        break;
    }
    case CMD_DMASETUP:
    case CMD_DMACOMPLETE:
        entry = { "26: opcode:6", "", 6, new_value >> 26, new_value >> 26 };
        m_bit_details_model.bits.append(entry);
        break;
    case CMD_MEMDMAVD:
    default: {
        const icmdque_wr_u new_value_t = { .reg32 = new_value };
        entry = { "00: icmdque_wdata:32", "", 32, new_value_t.icmdque_wdata, new_value_t.icmdque_wdata };
        m_bit_details_model.bits.append(entry);
    }
    }
}

#define CMDQUE_CONTROL_OFFSET 0x8
#define CMDQUE_CONTROL_UNDEFMASK 0xFFFFFFCF
union cmdque_control_u {
    struct {
        unsigned int undefined_bits_0_3:4;
        unsigned int src_stm_sel:1;         /* Source Stream interface select 0: through CIF (SDRAM only), 1: through AHB (SDRAM/IRAM) */
        unsigned int dst_stm_sel:1;         /* Destination Stream interface select 0: through CIF (SDRAM only), 1: through AHB (SDRAM/IRAM) */
        unsigned int undefined_bits_6_31:26;
    };

    u_int32_t reg32;
};

void BseDev::fill_cmdque_control_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const cmdque_control_u old_value_t = { .reg32 = value };
    const cmdque_control_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_3:4", "", 4, old_value_t.undefined_bits_0_3, new_value_t.undefined_bits_0_3 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: src_stm_sel:1",
              "Source Stream interface select 0: through CIF (SDRAM only), 1: through AHB (SDRAM/IRAM)",
              1, old_value_t.src_stm_sel, new_value_t.src_stm_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "05: dst_stm_sel:1",
              "Destination Stream interface select 0: through CIF (SDRAM only), 1: through AHB (SDRAM/IRAM)",
              1, old_value_t.dst_stm_sel, new_value_t.dst_stm_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "06: undefined_bits_6_31:26", "", 26, old_value_t.undefined_bits_6_31, new_value_t.undefined_bits_6_31 };
    m_bit_details_model.bits.append(entry);
}

#define INTR_STATUS_OFFSET 0x18
#define INTR_STATUS_UNDEFMASK 0xFFFFFDF6
union intr_status_u {
    struct {
        unsigned int engine_busy:1;         /* AES busy (RO) */
        unsigned int undefined_bits_1_2:2;
        unsigned int icq_empty:1;           /* Interactive command queue is empty (RO) */
        unsigned int undefined_bits_4_8:5;
        unsigned int dma_busy:1;            /* DMA engine is still busy (asserted by DMASetup and de-asserted by DMAFinish) (RO) */
        unsigned int undefined_bits_10_31:22;
    };

    u_int32_t reg32;
};

void BseDev::fill_intr_status_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const intr_status_u old_value_t = { .reg32 = value };
    const intr_status_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: engine_busy:1",
              "AES busy (RO)",
              1, old_value_t.engine_busy, new_value_t.engine_busy };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_2:2", "", 2, old_value_t.undefined_bits_1_2, new_value_t.undefined_bits_1_2 };
    m_bit_details_model.bits.append(entry);
    entry = { "03: icq_empty:1",
              "Interactive command queue is empty (RO)",
              1, old_value_t.icq_empty, new_value_t.icq_empty };
    m_bit_details_model.bits.append(entry);
    entry = { "04: undefined_bits_4_8:5", "", 5, old_value_t.undefined_bits_4_8, new_value_t.undefined_bits_4_8 };
    m_bit_details_model.bits.append(entry);
    entry = { "09: dma_busy:1",
              "DMA engine is still busy (asserted by DMASetup and de-asserted by DMAFinish) (RO)",
              1, old_value_t.dma_busy, new_value_t.dma_busy };
    m_bit_details_model.bits.append(entry);
    entry = { "10: undefined_bits_10_31:22", "", 22, old_value_t.undefined_bits_10_31, new_value_t.undefined_bits_10_31 };
    m_bit_details_model.bits.append(entry);
}

#define BSE_CONFIG_OFFSET 0x44
#define BSE_CONFIG_UNDEFMASK 0xFFFFFBE0
union bse_config_u {
    struct {
        unsigned int bse_mode_sel:5;        /* 00000: CRYPTO mode */
        unsigned int undefined_bits_5_9:5;
        unsigned int endian_enb:1;          /* Must be set to 1. */
        unsigned int undefined_bits_11_31:21;
    };

    u_int32_t reg32;
};

void BseDev::fill_bse_config_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const bse_config_u old_value_t = { .reg32 = value };
    const bse_config_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: bse_mode_sel:5",
              "00000: CRYPTO mode",
              5, old_value_t.bse_mode_sel, new_value_t.bse_mode_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "05: undefined_bits_5_9:5", "", 5, old_value_t.undefined_bits_5_9, new_value_t.undefined_bits_5_9 };
    m_bit_details_model.bits.append(entry);
    entry = { "10: endian_enb:1",
              "Must be set to 1.",
              1, old_value_t.endian_enb, new_value_t.endian_enb };
    m_bit_details_model.bits.append(entry);
    entry = { "11: undefined_bits_11_31:21", "", 21, old_value_t.undefined_bits_11_31, new_value_t.undefined_bits_11_31 };
    m_bit_details_model.bits.append(entry);
}

#define SECURE_DEST_ADDR_OFFSET 0x100
#define SECURE_DEST_ADDR_UNDEFMASK 0x00000000
union secure_dest_addr_u {
    struct {
        unsigned int secure_dest_addr:32;   /* SECURE engine: write back destination write address */
    };

    u_int32_t reg32;
};

void BseDev::fill_secure_dest_addr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const secure_dest_addr_u old_value_t = { .reg32 = value };
    const secure_dest_addr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: secure_dest_addr:32",
              "SECURE engine: write back destination write address",
              32, old_value_t.secure_dest_addr, new_value_t.secure_dest_addr };
    m_bit_details_model.bits.append(entry);
}

#define SECURE_INPUT_SELECT_OFFSET 0x104
#define SECURE_INPUT_SELECT_UNDEFMASK 0xFFFFF001
union secure_input_select_u {
    struct {
        unsigned int undefined_bit_0:1;
        unsigned int secure_hash_dest:1;    /* CYRPTO hash destination, this is valid only when SECURE_HASH_ENB = 1 0: Do not write output to memory pointed by destination address.    Data can be read from HASH_RESULT 1: Write final 128-bit output to memory pointed by destination address */
        unsigned int secure_hash_enb:1;     /* CYRPTO hash enable */
        unsigned int secure_xor_pos:2;      /* CRYPTO XOR position 0x: Bypass 10: top, before CRYPTO 11: bottom, after CRYPTO */
        unsigned int secure_input_sel:2;    /* CRYPTO input select 00: From AHB input vector 01: reserved 10: Init Vector for first round and CRYPTO output for the rest rounds 11: Counter */
        unsigned int secure_vctram_sel:2;   /* Vector RAM select 00: From AHB input vector 01: reserved 10: Init Vector for first round and CRYPTO output for the rest rounds 11: Init Vector for the first round and previous AHB input for the rest rounds */
        unsigned int secure_core_sel:1;     /* CRYPTO/inv-CRYPTO core selection (use for shiftrow direction) */
        unsigned int secure_iv_select:1;    /* SECURE engine: Init vector select */
        unsigned int secure_rng_enb:1;      /* SECURE engine: random number generator enable */
        unsigned int undefined_bits_12_31:20;
    };

    u_int32_t reg32;
};

void BseDev::fill_secure_input_select_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const secure_input_select_u old_value_t = { .reg32 = value };
    const secure_input_select_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bit_0:1", "", 1, old_value_t.undefined_bit_0, new_value_t.undefined_bit_0 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: secure_hash_dest:1",
              "CYRPTO hash destination, this is valid only when SECURE_HASH_ENB = 1 0: Do not write output to memory pointed by destination address.    Data can be read from HASH_RESULT 1: Write final 128-bit output to memory pointed by destination address",
              1, old_value_t.secure_hash_dest, new_value_t.secure_hash_dest };
    m_bit_details_model.bits.append(entry);
    entry = { "02: secure_hash_enb:1",
              "CYRPTO hash enable",
              1, old_value_t.secure_hash_enb, new_value_t.secure_hash_enb };
    m_bit_details_model.bits.append(entry);
    entry = { "03: secure_xor_pos:2",
              "CRYPTO XOR position 0x: Bypass 10: top, before CRYPTO 11: bottom, after CRYPTO",
              2, old_value_t.secure_xor_pos, new_value_t.secure_xor_pos };
    m_bit_details_model.bits.append(entry);
    entry = { "05: secure_input_sel:2",
              "CRYPTO input select 00: From AHB input vector 01: reserved 10: Init Vector for first round and CRYPTO output for the rest rounds 11: Counter",
              2, old_value_t.secure_input_sel, new_value_t.secure_input_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "07: secure_vctram_sel:2",
              "Vector RAM select 00: From AHB input vector 01: reserved 10: Init Vector for first round and CRYPTO output for the rest rounds 11: Init Vector for the first round and previous AHB input for the rest rounds",
              2, old_value_t.secure_vctram_sel, new_value_t.secure_vctram_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "09: secure_core_sel:1",
              "CRYPTO/inv-CRYPTO core selection (use for shiftrow direction)",
              1, old_value_t.secure_core_sel, new_value_t.secure_core_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "10: secure_iv_select:1",
              "SECURE engine: Init vector select",
              1, old_value_t.secure_iv_select, new_value_t.secure_iv_select };
    m_bit_details_model.bits.append(entry);
    entry = { "11: secure_rng_enb:1",
              "SECURE engine: random number generator enable",
              1, old_value_t.secure_rng_enb, new_value_t.secure_rng_enb };
    m_bit_details_model.bits.append(entry);
    entry = { "12: undefined_bits_12_31:20", "", 20, old_value_t.undefined_bits_12_31, new_value_t.undefined_bits_12_31 };
    m_bit_details_model.bits.append(entry);
}

#define SECURE_CONFIG_OFFSET 0x108
#define SECURE_CONFIG_UNDEFMASK 0xFE0FFFFF
union secure_config_u {
    struct {
        unsigned int undefined_bits_0_19:20;
        unsigned int secure_key_index:5;    /* 5-bit index to select between the 8-keys(value greater than 7 is reserved) */
        unsigned int undefined_bits_25_31:7;
    };

    u_int32_t reg32;
};

void BseDev::fill_secure_config_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const secure_config_u old_value_t = { .reg32 = value };
    const secure_config_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_19:20", "", 20, old_value_t.undefined_bits_0_19, new_value_t.undefined_bits_0_19 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: secure_key_index:5",
              "5-bit index to select between the 8-keys(value greater than 7 is reserved)",
              5, old_value_t.secure_key_index, new_value_t.secure_key_index };
    m_bit_details_model.bits.append(entry);
    entry = { "25: undefined_bits_25_31:7", "", 7, old_value_t.undefined_bits_25_31, new_value_t.undefined_bits_25_31 };
    m_bit_details_model.bits.append(entry);
}

#define SECURE_CONFIG_EXT_OFFSET 0x10C
#define SECURE_CONFIG_EXT_UNDEFMASK 0x00FF7FFF
union secure_config_ext_u {
    struct {
        unsigned int undefined_bits_0_14:15;
        unsigned int secure_key_sch_dis:1;  /* Must be set to 0. Anything else is illegal. */
        unsigned int undefined_bits_16_23:8;
        unsigned int secure_offset_cnt:8;   /* CRYPTO encryption/decryption with 16B*N offset. 0: every 16B is encrypted/decrypted N: first 16B is encrypted/decrypted and N*16B is not */
    };

    u_int32_t reg32;
};

void BseDev::fill_secure_config_ext_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const secure_config_ext_u old_value_t = { .reg32 = value };
    const secure_config_ext_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_14:15", "", 15, old_value_t.undefined_bits_0_14, new_value_t.undefined_bits_0_14 };
    m_bit_details_model.bits.append(entry);
    entry = { "15: secure_key_sch_dis:1",
              "Must be set to 0. Anything else is illegal.",
              1, old_value_t.secure_key_sch_dis, new_value_t.secure_key_sch_dis };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_23:8", "", 8, old_value_t.undefined_bits_16_23, new_value_t.undefined_bits_16_23 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: secure_offset_cnt:8",
              "CRYPTO encryption/decryption with 16B*N offset. 0: every 16B is encrypted/decrypted N: first 16B is encrypted/decrypted and N*16B is not",
              8, old_value_t.secure_offset_cnt, new_value_t.secure_offset_cnt };
    m_bit_details_model.bits.append(entry);
}

#define SECURE_SECURITY_OFFSET 0x110
#define SECURE_SECURITY_UNDEFMASK 0xFFFFFFFC
union secure_security_u {
    struct {
        unsigned int secure_eng_dis:1;      /* Sticky bit. When this value is "1", crypto engine will be disabled. Software will not be able to use the crypto engine until the next system reset. */
        unsigned int key_sched_read:1;      /* Sticky bit. Must be set to 0. */
        unsigned int undefined_bits_2_31:30;
    };

    u_int32_t reg32;
};

void BseDev::fill_secure_security_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const secure_security_u old_value_t = { .reg32 = value };
    const secure_security_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: secure_eng_dis:1",
              "Sticky bit. When this value is \"1\", crypto engine will be disabled. Software will not be able to use the crypto engine until the next system reset.",
              1, old_value_t.secure_eng_dis, new_value_t.secure_eng_dis };
    m_bit_details_model.bits.append(entry);
    entry = { "01: key_sched_read:1",
              "Sticky bit. Must be set to 0.",
              1, old_value_t.key_sched_read, new_value_t.key_sched_read };
    m_bit_details_model.bits.append(entry);
    entry = { "02: undefined_bits_2_31:30", "", 30, old_value_t.undefined_bits_2_31, new_value_t.undefined_bits_2_31 };
    m_bit_details_model.bits.append(entry);
}

#define SECURE_HASH_RESULT0_OFFSET 0x120
#define SECURE_HASH_RESULT0_UNDEFMASK 0x00000000
union secure_hash_result0_u {
    struct {
        unsigned int secure_hash_result0:32;/* CRYPTO Hash result [31:0] */
    };

    u_int32_t reg32;
};

void BseDev::fill_secure_hash_result0_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const secure_hash_result0_u old_value_t = { .reg32 = value };
    const secure_hash_result0_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: secure_hash_result0:32",
              "CRYPTO Hash result [31:0]",
              32, old_value_t.secure_hash_result0, new_value_t.secure_hash_result0 };
    m_bit_details_model.bits.append(entry);
}

#define SECURE_HASH_RESULT1_OFFSET 0x124
#define SECURE_HASH_RESULT1_UNDEFMASK 0x00000000
union secure_hash_result1_u {
    struct {
        unsigned int secure_hash_result1:32;/* CRYPTO Hash result [63:32] */
    };

    u_int32_t reg32;
};

void BseDev::fill_secure_hash_result1_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const secure_hash_result1_u old_value_t = { .reg32 = value };
    const secure_hash_result1_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: secure_hash_result1:32",
              "CRYPTO Hash result [63:32]",
              32, old_value_t.secure_hash_result1, new_value_t.secure_hash_result1 };
    m_bit_details_model.bits.append(entry);
}

#define SECURE_HASH_RESULT2_OFFSET 0x128
#define SECURE_HASH_RESULT2_UNDEFMASK 0x00000000
union secure_hash_result2_u {
    struct {
        unsigned int secure_hash_result2:32;/* CRYPTO Hash result [95:64] */
    };

    u_int32_t reg32;
};

void BseDev::fill_secure_hash_result2_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const secure_hash_result2_u old_value_t = { .reg32 = value };
    const secure_hash_result2_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: secure_hash_result2:32",
              "CRYPTO Hash result [95:64]",
              32, old_value_t.secure_hash_result2, new_value_t.secure_hash_result2 };
    m_bit_details_model.bits.append(entry);
}

#define SECURE_HASH_RESULT3_OFFSET 0x12C
#define SECURE_HASH_RESULT3_UNDEFMASK 0x00000000
union secure_hash_result3_u {
    struct {
        unsigned int secure_hash_result3:32;/* CRYPTO Hash result [127:96] */
    };

    u_int32_t reg32;
};

void BseDev::fill_secure_hash_result3_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const secure_hash_result3_u old_value_t = { .reg32 = value };
    const secure_hash_result3_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: secure_hash_result3:32",
              "CRYPTO Hash result [127:96]",
              32, old_value_t.secure_hash_result3, new_value_t.secure_hash_result3 };
    m_bit_details_model.bits.append(entry);
}

#define SECURE_SEC_SEL0_OFFSET 0x140
#define SECURE_SEC_SEL0_UNDEFMASK 0xFFFFFFF8
union secure_sec_sel0_u {
    struct {
        unsigned int keyread_enb0:1;        /* Sticky bit, When set to "0", it will not be possible to change the value of this bit until the next system reset. When this value is "0", software will not be able to read back key 0 and original initialization vector 0 */
        unsigned int keyupdate_enb0:1;      /* Sticky bit, When set to "0", it will not be possible to change the value of this bit until the next system reset. When this value is "0", software will not be able to update key 0 and original initialization vector 0. */
        unsigned int ivread_enb0:1;         /* Sticky bit, When set to "0", it will not be possible to change the value of this bit until the next system reset. When this value is "0", software will not be able to read back the current and updated initialization vector 0. */
        unsigned int undefined_bits_3_31:29;
    };

    u_int32_t reg32;
};

void BseDev::fill_secure_sec_sel0_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const secure_sec_sel0_u old_value_t = { .reg32 = value };
    const secure_sec_sel0_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: keyread_enb0:1",
              "Sticky bit, When set to \"0\", it will not be possible to change the value of this bit until the next system reset. When this value is \"0\", software will not be able to read back key 0 and original initialization vector 0",
              1, old_value_t.keyread_enb0, new_value_t.keyread_enb0 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: keyupdate_enb0:1",
              "Sticky bit, When set to \"0\", it will not be possible to change the value of this bit until the next system reset. When this value is \"0\", software will not be able to update key 0 and original initialization vector 0.",
              1, old_value_t.keyupdate_enb0, new_value_t.keyupdate_enb0 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: ivread_enb0:1",
              "Sticky bit, When set to \"0\", it will not be possible to change the value of this bit until the next system reset. When this value is \"0\", software will not be able to read back the current and updated initialization vector 0.",
              1, old_value_t.ivread_enb0, new_value_t.ivread_enb0 };
    m_bit_details_model.bits.append(entry);
    entry = { "03: undefined_bits_3_31:29", "", 29, old_value_t.undefined_bits_3_31, new_value_t.undefined_bits_3_31 };
    m_bit_details_model.bits.append(entry);
}

#define SECURE_SEC_SEL1_OFFSET 0x144
#define SECURE_SEC_SEL1_UNDEFMASK 0xFFFFFFF8
union secure_sec_sel1_u {
    struct {
        unsigned int keyread_enb1:1;        /* Sticky bit, When set to "0", it will not be possible to change the value of this bit until the next system reset. When this value is "0", software will not be able to read back key 1 and original initialization vector 1 */
        unsigned int keyupdate_enb1:1;      /* Sticky bit, When set to "0", it will not be possible to change the value of this bit until the next system reset. When this value is "0", software will not be able to update key 1 and original initialization vector 1. */
        unsigned int ivread_enb1:1;         /* Sticky bit, When set to "0", it will not be possible to change the value of this bit until the next system reset. When this value is "0", software will not be able to read back the current and updated initialization vector 1. */
        unsigned int undefined_bits_3_31:29;
    };

    u_int32_t reg32;
};

void BseDev::fill_secure_sec_sel1_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const secure_sec_sel1_u old_value_t = { .reg32 = value };
    const secure_sec_sel1_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: keyread_enb1:1",
              "Sticky bit, When set to \"0\", it will not be possible to change the value of this bit until the next system reset. When this value is \"0\", software will not be able to read back key 1 and original initialization vector 1",
              1, old_value_t.keyread_enb1, new_value_t.keyread_enb1 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: keyupdate_enb1:1",
              "Sticky bit, When set to \"0\", it will not be possible to change the value of this bit until the next system reset. When this value is \"0\", software will not be able to update key 1 and original initialization vector 1.",
              1, old_value_t.keyupdate_enb1, new_value_t.keyupdate_enb1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: ivread_enb1:1",
              "Sticky bit, When set to \"0\", it will not be possible to change the value of this bit until the next system reset. When this value is \"0\", software will not be able to read back the current and updated initialization vector 1.",
              1, old_value_t.ivread_enb1, new_value_t.ivread_enb1 };
    m_bit_details_model.bits.append(entry);
    entry = { "03: undefined_bits_3_31:29", "", 29, old_value_t.undefined_bits_3_31, new_value_t.undefined_bits_3_31 };
    m_bit_details_model.bits.append(entry);
}

#define SECURE_SEC_SEL2_OFFSET 0x148
#define SECURE_SEC_SEL2_UNDEFMASK 0xFFFFFFF8
union secure_sec_sel2_u {
    struct {
        unsigned int keyread_enb2:1;        /* Sticky bit, When set to "0", it will not be possible to change the value of this bit until the next system reset. When this value is "0", software will not be able to read back key 2 and original initialization vector 2 */
        unsigned int keyupdate_enb2:1;      /* Sticky bit, When set to "0", it will not be possible to change the value of this bit until the next system reset. When this value is "0", software will not be able to update key 2 and original initialization vector 2. */
        unsigned int ivread_enb2:1;         /* Sticky bit, When set to "0", it will not be possible to change the value of this bit until the next system reset. When this value is "0", software will not be able to read back the current and updated initialization vector 2. */
        unsigned int undefined_bits_3_31:29;
    };

    u_int32_t reg32;
};

void BseDev::fill_secure_sec_sel2_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const secure_sec_sel2_u old_value_t = { .reg32 = value };
    const secure_sec_sel2_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: keyread_enb2:1",
              "Sticky bit, When set to \"0\", it will not be possible to change the value of this bit until the next system reset. When this value is \"0\", software will not be able to read back key 2 and original initialization vector 2",
              1, old_value_t.keyread_enb2, new_value_t.keyread_enb2 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: keyupdate_enb2:1",
              "Sticky bit, When set to \"0\", it will not be possible to change the value of this bit until the next system reset. When this value is \"0\", software will not be able to update key 2 and original initialization vector 2.",
              1, old_value_t.keyupdate_enb2, new_value_t.keyupdate_enb2 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: ivread_enb2:1",
              "Sticky bit, When set to \"0\", it will not be possible to change the value of this bit until the next system reset. When this value is \"0\", software will not be able to read back the current and updated initialization vector 2.",
              1, old_value_t.ivread_enb2, new_value_t.ivread_enb2 };
    m_bit_details_model.bits.append(entry);
    entry = { "03: undefined_bits_3_31:29", "", 29, old_value_t.undefined_bits_3_31, new_value_t.undefined_bits_3_31 };
    m_bit_details_model.bits.append(entry);
}

#define SECURE_SEC_SEL3_OFFSET 0x14C
#define SECURE_SEC_SEL3_UNDEFMASK 0xFFFFFFF8
union secure_sec_sel3_u {
    struct {
        unsigned int keyread_enb3:1;        /* Sticky bit, When set to "0", it will not be possible to change the value of this bit until the next system reset. When this value is "0", software will not be able to read back key 3 and original initialization vector 3 */
        unsigned int keyupdate_enb3:1;      /* Sticky bit, When set to "0", it will not be possible to change the value of this bit until the next system reset. When this value is "0", software will not be able to update key 3 and original initialization vector 3. */
        unsigned int ivread_enb3:1;         /* Sticky bit, When set to "0", it will not be possible to change the value of this bit until the next system reset. When this value is "0", software will not be able to read back the current and updated initialization vector 3. */
        unsigned int undefined_bits_3_31:29;
    };

    u_int32_t reg32;
};

void BseDev::fill_secure_sec_sel3_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const secure_sec_sel3_u old_value_t = { .reg32 = value };
    const secure_sec_sel3_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: keyread_enb3:1",
              "Sticky bit, When set to \"0\", it will not be possible to change the value of this bit until the next system reset. When this value is \"0\", software will not be able to read back key 3 and original initialization vector 3",
              1, old_value_t.keyread_enb3, new_value_t.keyread_enb3 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: keyupdate_enb3:1",
              "Sticky bit, When set to \"0\", it will not be possible to change the value of this bit until the next system reset. When this value is \"0\", software will not be able to update key 3 and original initialization vector 3.",
              1, old_value_t.keyupdate_enb3, new_value_t.keyupdate_enb3 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: ivread_enb3:1",
              "Sticky bit, When set to \"0\", it will not be possible to change the value of this bit until the next system reset. When this value is \"0\", software will not be able to read back the current and updated initialization vector 3.",
              1, old_value_t.ivread_enb3, new_value_t.ivread_enb3 };
    m_bit_details_model.bits.append(entry);
    entry = { "03: undefined_bits_3_31:29", "", 29, old_value_t.undefined_bits_3_31, new_value_t.undefined_bits_3_31 };
    m_bit_details_model.bits.append(entry);
}

#define SECURE_SEC_SEL4_OFFSET 0x150
#define SECURE_SEC_SEL4_UNDEFMASK 0xFFFFFFF8
union secure_sec_sel4_u {
    struct {
        unsigned int keyread_enb4:1;        /* Sticky bit, When set to "0", it will not be possible to change the value of this bit until the next system reset. When this value is "0", software will not be able to read back key 4 and original initialization vector 4 */
        unsigned int keyupdate_enb4:1;      /* Sticky bit, When set to "0", it will not be possible to change the value of this bit until the next system reset. When this value is "0", software will not be able to update key 4 and original initialization vector 4. */
        unsigned int ivread_enb4:1;         /* Sticky bit, When set to "0", it will not be possible to change the value of this bit until the next system reset. When this value is "0", software will not be able to read back the current and updated initialization vector 4. */
        unsigned int undefined_bits_3_31:29;
    };

    u_int32_t reg32;
};

void BseDev::fill_secure_sec_sel4_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const secure_sec_sel4_u old_value_t = { .reg32 = value };
    const secure_sec_sel4_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: keyread_enb4:1",
              "Sticky bit, When set to \"0\", it will not be possible to change the value of this bit until the next system reset. When this value is \"0\", software will not be able to read back key 4 and original initialization vector 4",
              1, old_value_t.keyread_enb4, new_value_t.keyread_enb4 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: keyupdate_enb4:1",
              "Sticky bit, When set to \"0\", it will not be possible to change the value of this bit until the next system reset. When this value is \"0\", software will not be able to update key 4 and original initialization vector 4.",
              1, old_value_t.keyupdate_enb4, new_value_t.keyupdate_enb4 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: ivread_enb4:1",
              "Sticky bit, When set to \"0\", it will not be possible to change the value of this bit until the next system reset. When this value is \"0\", software will not be able to read back the current and updated initialization vector 4.",
              1, old_value_t.ivread_enb4, new_value_t.ivread_enb4 };
    m_bit_details_model.bits.append(entry);
    entry = { "03: undefined_bits_3_31:29", "", 29, old_value_t.undefined_bits_3_31, new_value_t.undefined_bits_3_31 };
    m_bit_details_model.bits.append(entry);
}

#define SECURE_SEC_SEL5_OFFSET 0x154
#define SECURE_SEC_SEL5_UNDEFMASK 0xFFFFFFF8
union secure_sec_sel5_u {
    struct {
        unsigned int keyread_enb5:1;        /* Sticky bit, When set to "0", it will not be possible to change the value of this bit until the next system reset. When this value is "0", software will not be able to read back key 5 and original initialization vector 5 */
        unsigned int keyupdate_enb5:1;      /* Sticky bit, When set to "0", it will not be possible to change the value of this bit until the next system reset. When this value is "0", software will not be able to update key 5 and original initialization vector 5. */
        unsigned int ivread_enb5:1;         /* Sticky bit, When set to "0", it will not be possible to change the value of this bit until the next system reset. When this value is "0", software will not be able to read back the current and updated initialization vector 5. */
        unsigned int undefined_bits_3_31:29;
    };

    u_int32_t reg32;
};

void BseDev::fill_secure_sec_sel5_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const secure_sec_sel5_u old_value_t = { .reg32 = value };
    const secure_sec_sel5_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: keyread_enb5:1",
              "Sticky bit, When set to \"0\", it will not be possible to change the value of this bit until the next system reset. When this value is \"0\", software will not be able to read back key 5 and original initialization vector 5",
              1, old_value_t.keyread_enb5, new_value_t.keyread_enb5 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: keyupdate_enb5:1",
              "Sticky bit, When set to \"0\", it will not be possible to change the value of this bit until the next system reset. When this value is \"0\", software will not be able to update key 5 and original initialization vector 5.",
              1, old_value_t.keyupdate_enb5, new_value_t.keyupdate_enb5 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: ivread_enb5:1",
              "Sticky bit, When set to \"0\", it will not be possible to change the value of this bit until the next system reset. When this value is \"0\", software will not be able to read back the current and updated initialization vector 5.",
              1, old_value_t.ivread_enb5, new_value_t.ivread_enb5 };
    m_bit_details_model.bits.append(entry);
    entry = { "03: undefined_bits_3_31:29", "", 29, old_value_t.undefined_bits_3_31, new_value_t.undefined_bits_3_31 };
    m_bit_details_model.bits.append(entry);
}

#define SECURE_SEC_SEL6_OFFSET 0x158
#define SECURE_SEC_SEL6_UNDEFMASK 0xFFFFFFF8
union secure_sec_sel6_u {
    struct {
        unsigned int keyread_enb6:1;        /* Sticky bit, When set to "0", it will not be possible to change the value of this bit until the next system reset. When this value is "0", software will not be able to read back key 6 and original initialization vector 6 */
        unsigned int keyupdate_enb6:1;      /* Sticky bit, When set to "0", it will not be possible to change the value of this bit until the next system reset. When this value is "0", software will not be able to update key 6 and original initialization vector 6. */
        unsigned int ivread_enb6:1;         /* Sticky bit, When set to "0", it will not be possible to change the value of this bit until the next system reset. When this value is "0", software will not be able to read back the current and updated initialization vector 6. */
        unsigned int undefined_bits_3_31:29;
    };

    u_int32_t reg32;
};

void BseDev::fill_secure_sec_sel6_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const secure_sec_sel6_u old_value_t = { .reg32 = value };
    const secure_sec_sel6_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: keyread_enb6:1",
              "Sticky bit, When set to \"0\", it will not be possible to change the value of this bit until the next system reset. When this value is \"0\", software will not be able to read back key 6 and original initialization vector 6",
              1, old_value_t.keyread_enb6, new_value_t.keyread_enb6 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: keyupdate_enb6:1",
              "Sticky bit, When set to \"0\", it will not be possible to change the value of this bit until the next system reset. When this value is \"0\", software will not be able to update key 6 and original initialization vector 6.",
              1, old_value_t.keyupdate_enb6, new_value_t.keyupdate_enb6 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: ivread_enb6:1",
              "Sticky bit, When set to \"0\", it will not be possible to change the value of this bit until the next system reset. When this value is \"0\", software will not be able to read back the current and updated initialization vector 6.",
              1, old_value_t.ivread_enb6, new_value_t.ivread_enb6 };
    m_bit_details_model.bits.append(entry);
    entry = { "03: undefined_bits_3_31:29", "", 29, old_value_t.undefined_bits_3_31, new_value_t.undefined_bits_3_31 };
    m_bit_details_model.bits.append(entry);
}

#define SECURE_SEC_SEL7_OFFSET 0x15C
#define SECURE_SEC_SEL7_UNDEFMASK 0xFFFFFFF8
union secure_sec_sel7_u {
    struct {
        unsigned int keyread_enb7:1;        /* Sticky bit, When set to "0", it will not be possible to change the value of this bit until the next system reset. When this value is "0", software will not be able to read back key 7 and original initialization vector 7 */
        unsigned int keyupdate_enb7:1;      /* Sticky bit, When set to "0", it will not be possible to change the value of this bit until the next system reset. When this value is "0", software will not be able to update key 7 and original initialization vector 7. */
        unsigned int ivread_enb7:1;         /* Sticky bit, When set to "0", it will not be possible to change the value of this bit until the next system reset. When this value is "0", software will not be able to read back the current and updated initialization vector 7. */
        unsigned int undefined_bits_3_31:29;
    };

    u_int32_t reg32;
};

void BseDev::fill_secure_sec_sel7_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const secure_sec_sel7_u old_value_t = { .reg32 = value };
    const secure_sec_sel7_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: keyread_enb7:1",
              "Sticky bit, When set to \"0\", it will not be possible to change the value of this bit until the next system reset. When this value is \"0\", software will not be able to read back key 7 and original initialization vector 7",
              1, old_value_t.keyread_enb7, new_value_t.keyread_enb7 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: keyupdate_enb7:1",
              "Sticky bit, When set to \"0\", it will not be possible to change the value of this bit until the next system reset. When this value is \"0\", software will not be able to update key 7 and original initialization vector 7.",
              1, old_value_t.keyupdate_enb7, new_value_t.keyupdate_enb7 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: ivread_enb7:1",
              "Sticky bit, When set to \"0\", it will not be possible to change the value of this bit until the next system reset. When this value is \"0\", software will not be able to read back the current and updated initialization vector 7.",
              1, old_value_t.ivread_enb7, new_value_t.ivread_enb7 };
    m_bit_details_model.bits.append(entry);
    entry = { "03: undefined_bits_3_31:29", "", 29, old_value_t.undefined_bits_3_31, new_value_t.undefined_bits_3_31 };
    m_bit_details_model.bits.append(entry);
}

bool BseDev::is_offset_valid(const u_int32_t &offset) const
{
    switch (offset) {
    case ICMDQUE_WR_OFFSET:
    case CMDQUE_CONTROL_OFFSET:
    case INTR_STATUS_OFFSET:
    case BSE_CONFIG_OFFSET:
    case SECURE_DEST_ADDR_OFFSET:
    case SECURE_INPUT_SELECT_OFFSET:
    case SECURE_CONFIG_OFFSET:
    case SECURE_CONFIG_EXT_OFFSET:
    case SECURE_SECURITY_OFFSET:
    case SECURE_HASH_RESULT0_OFFSET:
    case SECURE_HASH_RESULT1_OFFSET:
    case SECURE_HASH_RESULT2_OFFSET:
    case SECURE_HASH_RESULT3_OFFSET:
    case SECURE_SEC_SEL0_OFFSET:
    case SECURE_SEC_SEL1_OFFSET:
    case SECURE_SEC_SEL2_OFFSET:
    case SECURE_SEC_SEL3_OFFSET:
    case SECURE_SEC_SEL4_OFFSET:
    case SECURE_SEC_SEL5_OFFSET:
    case SECURE_SEC_SEL6_OFFSET:
    case SECURE_SEC_SEL7_OFFSET:
        return true;
    default:
        break;
    }

    return false;
}

bool BseDev::is_undef_changed(const u_int32_t &offset,
                                           const u_int32_t &value,
                                           const u_int32_t &new_value) const
{
    switch (offset) {
    case ICMDQUE_WR_OFFSET:
        if ((value ^ new_value) & ICMDQUE_WR_UNDEFMASK)
            return true;
        break;
    case CMDQUE_CONTROL_OFFSET:
        if ((value ^ new_value) & CMDQUE_CONTROL_UNDEFMASK)
            return true;
        break;
    case INTR_STATUS_OFFSET:
        if ((value ^ new_value) & INTR_STATUS_UNDEFMASK)
            return true;
        break;
    case BSE_CONFIG_OFFSET:
        if ((value ^ new_value) & BSE_CONFIG_UNDEFMASK)
            return true;
        break;
    case SECURE_DEST_ADDR_OFFSET:
        if ((value ^ new_value) & SECURE_DEST_ADDR_UNDEFMASK)
            return true;
        break;
    case SECURE_INPUT_SELECT_OFFSET:
        if ((value ^ new_value) & SECURE_INPUT_SELECT_UNDEFMASK)
            return true;
        break;
    case SECURE_CONFIG_OFFSET:
        if ((value ^ new_value) & SECURE_CONFIG_UNDEFMASK)
            return true;
        break;
    case SECURE_CONFIG_EXT_OFFSET:
        if ((value ^ new_value) & SECURE_CONFIG_EXT_UNDEFMASK)
            return true;
        break;
    case SECURE_SECURITY_OFFSET:
        if ((value ^ new_value) & SECURE_SECURITY_UNDEFMASK)
            return true;
        break;
    case SECURE_HASH_RESULT0_OFFSET:
        if ((value ^ new_value) & SECURE_HASH_RESULT0_UNDEFMASK)
            return true;
        break;
    case SECURE_HASH_RESULT1_OFFSET:
        if ((value ^ new_value) & SECURE_HASH_RESULT1_UNDEFMASK)
            return true;
        break;
    case SECURE_HASH_RESULT2_OFFSET:
        if ((value ^ new_value) & SECURE_HASH_RESULT2_UNDEFMASK)
            return true;
        break;
    case SECURE_HASH_RESULT3_OFFSET:
        if ((value ^ new_value) & SECURE_HASH_RESULT3_UNDEFMASK)
            return true;
        break;
    case SECURE_SEC_SEL0_OFFSET:
        if ((value ^ new_value) & SECURE_SEC_SEL0_UNDEFMASK)
            return true;
        break;
    case SECURE_SEC_SEL1_OFFSET:
        if ((value ^ new_value) & SECURE_SEC_SEL1_UNDEFMASK)
            return true;
        break;
    case SECURE_SEC_SEL2_OFFSET:
        if ((value ^ new_value) & SECURE_SEC_SEL2_UNDEFMASK)
            return true;
        break;
    case SECURE_SEC_SEL3_OFFSET:
        if ((value ^ new_value) & SECURE_SEC_SEL3_UNDEFMASK)
            return true;
        break;
    case SECURE_SEC_SEL4_OFFSET:
        if ((value ^ new_value) & SECURE_SEC_SEL4_UNDEFMASK)
            return true;
        break;
    case SECURE_SEC_SEL5_OFFSET:
        if ((value ^ new_value) & SECURE_SEC_SEL5_UNDEFMASK)
            return true;
        break;
    case SECURE_SEC_SEL6_OFFSET:
        if ((value ^ new_value) & SECURE_SEC_SEL6_UNDEFMASK)
            return true;
        break;
    case SECURE_SEC_SEL7_OFFSET:
        if ((value ^ new_value) & SECURE_SEC_SEL7_UNDEFMASK)
            return true;
        break;

    default:
        break;
    }

    return false;
}

void BseDev::update_internal(log_entry &entry)
{
    switch (entry.offset) {
    case ICMDQUE_WR_OFFSET:
        if (m_state == BseDev::DMA_SETUP) {
            m_state = BseDev::IDLE;
            entry.custom = BseDev::DMA_SETUP;
            break;
        }

        switch (entry.new_value >> 26) {
        case CMD_DMASETUP:
            m_state = BseDev::DMA_SETUP;
            break;
        case CMD_SETTABLE:
        case CMD_DMACOMPLETE:
        case CMD_BLKSTARTENGINE:
        case CMD_MEMDMAVD:
            break;
        default:
            entry.is_error = true;
            break;
        }
    default:
        break;
    }
}

QString BseDev::get_register_name(const log_entry &entry) const
{
    switch (entry.offset) {
    case ICMDQUE_WR_OFFSET:
        if (entry.custom == BseDev::DMA_SETUP)
            return QString().sprintf("ICMD: DMA set to 0x%08X", entry.new_value);

        switch (entry.new_value >> 26) {
        case CMD_SETTABLE:
            return QString("ICMD: CMD_SETTABLE");
        case CMD_DMASETUP:
            return QString("ICMD: CMD_DMASETUP");
        case CMD_DMACOMPLETE:
            return QString("ICMD: CMD_DMACOMPLETE");
        case CMD_BLKSTARTENGINE:
            return QString("ICMD: CMD_BLKSTARTENGINE");
        case CMD_MEMDMAVD:
            return QString("ICMD: CMD_MEMDMAVD");
        default:
            return QString().sprintf("ICMD: Unknown opcode=0x%02X",
                                     (u_int8_t) (entry.new_value >> 26));
        }
    case CMDQUE_CONTROL_OFFSET:
        return QString("CMDQUE_CONTROL");
    case INTR_STATUS_OFFSET:
        return QString("INTR_STATUS");
    case BSE_CONFIG_OFFSET:
        return QString("BSE_CONFIG");
    case SECURE_DEST_ADDR_OFFSET:
        return QString("SECURE_DEST_ADDR");
    case SECURE_INPUT_SELECT_OFFSET:
        return QString("SECURE_INPUT_SELECT");
    case SECURE_CONFIG_OFFSET:
        return QString("SECURE_CONFIG");
    case SECURE_CONFIG_EXT_OFFSET:
        return QString("SECURE_CONFIG_EXT");
    case SECURE_SECURITY_OFFSET:
        return QString("SECURE_SECURITY");
    case SECURE_HASH_RESULT0_OFFSET:
        return QString("SECURE_HASH_RESULT0");
    case SECURE_HASH_RESULT1_OFFSET:
        return QString("SECURE_HASH_RESULT1");
    case SECURE_HASH_RESULT2_OFFSET:
        return QString("SECURE_HASH_RESULT2");
    case SECURE_HASH_RESULT3_OFFSET:
        return QString("SECURE_HASH_RESULT3");
    case SECURE_SEC_SEL0_OFFSET:
        return QString("SECURE_SEC_SEL0");
    case SECURE_SEC_SEL1_OFFSET:
        return QString("SECURE_SEC_SEL1");
    case SECURE_SEC_SEL2_OFFSET:
        return QString("SECURE_SEC_SEL2");
    case SECURE_SEC_SEL3_OFFSET:
        return QString("SECURE_SEC_SEL3");
    case SECURE_SEC_SEL4_OFFSET:
        return QString("SECURE_SEC_SEL4");
    case SECURE_SEC_SEL5_OFFSET:
        return QString("SECURE_SEC_SEL5");
    case SECURE_SEC_SEL6_OFFSET:
        return QString("SECURE_SEC_SEL6");
    case SECURE_SEC_SEL7_OFFSET:
        return QString("SECURE_SEC_SEL7");

    default:
        break;
    }

    qDebug() << QString().sprintf("BSE: %s: Ooops... 0x%x", __func__, entry.offset);

    return QString().sprintf("Ooops... @0x%X", entry.offset);
}

void BseDev::fill_bits_details(const u_int32_t &offset,
                                      const u_int32_t &value, const u_int32_t &new_value)
{
    switch (offset) {
    case ICMDQUE_WR_OFFSET:
        fill_icmdque_wr_details(value, new_value);
        break;
    case CMDQUE_CONTROL_OFFSET:
        fill_cmdque_control_details(value, new_value);
        break;
    case INTR_STATUS_OFFSET:
        fill_intr_status_details(value, new_value);
        break;
    case BSE_CONFIG_OFFSET:
        fill_bse_config_details(value, new_value);
        break;
    case SECURE_DEST_ADDR_OFFSET:
        fill_secure_dest_addr_details(value, new_value);
        break;
    case SECURE_INPUT_SELECT_OFFSET:
        fill_secure_input_select_details(value, new_value);
        break;
    case SECURE_CONFIG_OFFSET:
        fill_secure_config_details(value, new_value);
        break;
    case SECURE_CONFIG_EXT_OFFSET:
        fill_secure_config_ext_details(value, new_value);
        break;
    case SECURE_SECURITY_OFFSET:
        fill_secure_security_details(value, new_value);
        break;
    case SECURE_HASH_RESULT0_OFFSET:
        fill_secure_hash_result0_details(value, new_value);
        break;
    case SECURE_HASH_RESULT1_OFFSET:
        fill_secure_hash_result1_details(value, new_value);
        break;
    case SECURE_HASH_RESULT2_OFFSET:
        fill_secure_hash_result2_details(value, new_value);
        break;
    case SECURE_HASH_RESULT3_OFFSET:
        fill_secure_hash_result3_details(value, new_value);
        break;
    case SECURE_SEC_SEL0_OFFSET:
        fill_secure_sec_sel0_details(value, new_value);
        break;
    case SECURE_SEC_SEL1_OFFSET:
        fill_secure_sec_sel1_details(value, new_value);
        break;
    case SECURE_SEC_SEL2_OFFSET:
        fill_secure_sec_sel2_details(value, new_value);
        break;
    case SECURE_SEC_SEL3_OFFSET:
        fill_secure_sec_sel3_details(value, new_value);
        break;
    case SECURE_SEC_SEL4_OFFSET:
        fill_secure_sec_sel4_details(value, new_value);
        break;
    case SECURE_SEC_SEL5_OFFSET:
        fill_secure_sec_sel5_details(value, new_value);
        break;
    case SECURE_SEC_SEL6_OFFSET:
        fill_secure_sec_sel6_details(value, new_value);
        break;
    case SECURE_SEC_SEL7_OFFSET:
        fill_secure_sec_sel7_details(value, new_value);
        break;

    default:
        m_bit_details_model.bits.clear();
        break;
    }
}
