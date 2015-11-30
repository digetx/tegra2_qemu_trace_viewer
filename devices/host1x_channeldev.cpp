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

#include "host1x_channeldev.h"

#include <QDebug>

#define FIFOSTAT_OFFSET 0x0
#define FIFOSTAT_UNDEFMASK 0x60E0E000
union fifostat_u {
    struct {
        unsigned int cfnumempty:10;         /* Command FIFO free count */
        unsigned int cfempty:1;             /* Indicates whether the command FIFO is empty or not 0 = NOTEMPTY 1 = EMPTY */
        unsigned int cfgather:1;            /* Indicates whether GATHER is active. If a GATHER command issued via PIO, software must wait for the GATHER to be IDLE before issuing another command. 0 = IDLE 1 = BUSY */
        unsigned int cfgather3d:1;          /* Indicates whether GATHER is active. If a GATHER command issued via PIO, software must wait for the GATHER to be IDLE before issuing another command. 0 = IDLE 1 = BUSY */
        unsigned int undefined_bits_13_15:3;
        unsigned int regfnumempty:5;        /* Register write/read FIFO free count */
        unsigned int undefined_bits_21_23:3;
        unsigned int outfentries:5;         /* Number of entries available for reading in this channel's output FIFO */
        unsigned int undefined_bits_29_30:2;
        unsigned int indrdy:1;              /* Indicates that INDCOUNT==0, so it should be OK to issue another read */
    };

    u_int32_t reg32;
};

void Host1x_channelDev::fill_fifostat_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const fifostat_u old_value_t = { .reg32 = value };
    const fifostat_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: cfnumempty:10",
              "Command FIFO free count",
              10, old_value_t.cfnumempty, new_value_t.cfnumempty };
    m_bit_details_model.bits.append(entry);
    entry = { "10: cfempty:1",
              "Indicates whether the command FIFO is empty or not\n0 = NOTEMPTY\n1 = EMPTY",
              1, old_value_t.cfempty, new_value_t.cfempty };
    m_bit_details_model.bits.append(entry);
    entry = { "11: cfgather:1",
              "Indicates whether GATHER is active. If a GATHER command issued via PIO, software must wait for the GATHER to be IDLE before issuing another command.\n0 = IDLE\n1 = BUSY",
              1, old_value_t.cfgather, new_value_t.cfgather };
    m_bit_details_model.bits.append(entry);
    entry = { "12: cfgather3d:1",
              "Indicates whether GATHER is active. If a GATHER command issued via PIO, software must wait for the GATHER to be IDLE before issuing another command.\n0 = IDLE\n1 = BUSY",
              1, old_value_t.cfgather3d, new_value_t.cfgather3d };
    m_bit_details_model.bits.append(entry);
    entry = { "13: undefined_bits_13_15:3", "", 3, old_value_t.undefined_bits_13_15, new_value_t.undefined_bits_13_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: regfnumempty:5",
              "Register write/read FIFO free count",
              5, old_value_t.regfnumempty, new_value_t.regfnumempty };
    m_bit_details_model.bits.append(entry);
    entry = { "21: undefined_bits_21_23:3", "", 3, old_value_t.undefined_bits_21_23, new_value_t.undefined_bits_21_23 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: outfentries:5",
              "Number of entries available for reading in this channel's output FIFO",
              5, old_value_t.outfentries, new_value_t.outfentries };
    m_bit_details_model.bits.append(entry);
    entry = { "29: undefined_bits_29_30:2", "", 2, old_value_t.undefined_bits_29_30, new_value_t.undefined_bits_29_30 };
    m_bit_details_model.bits.append(entry);
    entry = { "31: indrdy:1",
              "Indicates that INDCOUNT==0, so it should be OK to issue another read",
              1, old_value_t.indrdy, new_value_t.indrdy };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "All channels have the common registers. CFNUMEMPTY is the number of free slots available in the per-channel command. FIFO is needed for PIO or polling for completion of a wait.";
}

#define INDOFF_OFFSET 0x4
#define INDOFF_UNDEFMASK 0x04000002
union indoff_u {
    struct {
        unsigned int indoffupd:1;           /* Optionally disable the update of INDOFFSET when writing this register 0 = UPDATE 1 = NO_UPDATE */
        unsigned int undefined_bit_1:1;
        unsigned int indcustom:24;
        unsigned int undefined_bit_26:1;
        unsigned int indswap:2;             /* Indirect framebuffer access swap control. 00 = No byte swap 01 = 16-bit byte swap ([31:0] -> {[23:16],[31:24],[7:0],[15:8]}) 10 = 32-bit byte swap ([31:0] -> {[7:0],[15:8],[23:16],[31:24]}) 11 = 32-bit word swap ([31:0] -> {[15:8],[7:0],[31:24],[23:16]}) 0 = NONE 1 = BYTE16 2 = BYTE32 3 = WORD32 */
        unsigned int buf32b:1;              /* buffer up 32 bits of register data before sending it. Otherwise, register writes will be sent as soon as they are received. Does not support byte writes in 16-bit host. Does not affect framebuffer writes. 0 = NOBUF 1 = BUF */
        unsigned int acctype:1;             /* access type: indirect register or indirect framebuffer 0 = REG 1 = FB */
        unsigned int autoinc:1;             /* auto increment of read/write address 0 = DISABLE 1 = ENABLE */
    };

    u_int32_t reg32;
};

void Host1x_channelDev::fill_indoff_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const indoff_u old_value_t = { .reg32 = value };
    const indoff_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: indoffupd:1",
              "Optionally disable the update of INDOFFSET when writing this register\n0 = UPDATE\n1 = NO_UPDATE",
              1, old_value_t.indoffupd, new_value_t.indoffupd };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bit_1:1", "", 1, old_value_t.undefined_bit_1, new_value_t.undefined_bit_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: indcustom:24", "", 24, old_value_t.indcustom, new_value_t.indcustom };
    m_bit_details_model.bits.append(entry);
    entry = { "26: undefined_bit_26:1", "", 1, old_value_t.undefined_bit_26, new_value_t.undefined_bit_26 };
    m_bit_details_model.bits.append(entry);
    entry = { "27: indswap:2",
              "Indirect framebuffer access swap control.\n00 = No byte swap\n01 = 16-bit byte swap ([31:0] -> {[23:16],[31:24],[7:0],[15:8]})\n10 = 32-bit byte swap ([31:0] -> {[7:0],[15:8],[23:16],[31:24]})\n11 = 32-bit word swap ([31:0] -> {[15:8],[7:0],[31:24],[23:16]})\n0 = NONE\n1 = BYTE16\n2 = BYTE32\n3 = WORD32",
              2, old_value_t.indswap, new_value_t.indswap };
    m_bit_details_model.bits.append(entry);
    entry = { "29: buf32b:1",
              "buffer up 32 bits of register data before sending it. Otherwise, register writes will be sent as soon as they are received. Does not support byte writes in 16-bit host. Does not affect framebuffer writes.\n0 = NOBUF\n1 = BUF",
              1, old_value_t.buf32b, new_value_t.buf32b };
    m_bit_details_model.bits.append(entry);
    entry = { "30: acctype:1",
              "access type: indirect register or indirect framebuffer\n0 = REG\n1 = FB",
              1, old_value_t.acctype, new_value_t.acctype };
    m_bit_details_model.bits.append(entry);
    entry = { "31: autoinc:1",
              "auto increment of read/write address\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.autoinc, new_value_t.autoinc };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "The INDOFF and INDOFF2 registers (along with INDCNT and INDDATA) are used to indirectly read/write modules outside the host. If AUTOINC is set, INDOFFSET increments by 4 on every access of INDDATA.  REGFNUMEMPTY is polled to determine when valid data can be read from INDDATA.\nThe INDOFF register has limited capability on chips with large memory maps. If the top bit of the memory address is >= 27, all of memory cannot be addressed with INDOFF.  In these cases, use INDOFF2 to set the offset while still using INDOFF to set the other parameters.  Always have INDOFFUPD set to NO_UPDATE in these cases.  For register accesses, using INDOFF (with INDOFFUPD set to UPDATE) is always more efficient, since it only requires one write.\nIndirect framebuffer write is STRONGLY DISCOURAGED.  There are better ways to write to memory (direct and through the channel memory map) and there is limited flow control in the host.  It's very easy to get into trouble with indirect framebuffer write.";
}

#define INDCNT_OFFSET 0x8
#define INDCNT_UNDEFMASK 0xFFFF0000
union indcnt_u {
    struct {
        unsigned int indcount:16;
        unsigned int undefined_bits_16_31:16;
    };

    u_int32_t reg32;
};

void Host1x_channelDev::fill_indcnt_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const indcnt_u old_value_t = { .reg32 = value };
    const indcnt_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: indcount:16", "", 16, old_value_t.indcount, new_value_t.indcount };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_31:16", "", 16, old_value_t.undefined_bits_16_31, new_value_t.undefined_bits_16_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Indirect register access count Used to trigger indirect reads.  Holds the number of registers/memory locations that will be read out.  Channels should not request more than there is space available in their output FIFO. Only the protected channel should make liberal use of this feature for speeding up context switching.\nFor indirect framebuffer reads, each channel cannot issue more than NV_HOST1X_MAX_IND_FB_READS at once.  The read data must return and be written into the per-channel output FIFO before any additional reads can be issued.";
}

#define INDDATA_OFFSET 0xC
#define INDDATA_UNDEFMASK 0x00000000
union inddata_u {
    struct {
        unsigned int inddata:32;            /* read or write data */
    };

    u_int32_t reg32;
};

void Host1x_channelDev::fill_inddata_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const inddata_u old_value_t = { .reg32 = value };
    const inddata_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: inddata:32",
              "read or write data",
              32, old_value_t.inddata, new_value_t.inddata };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "This register, when written, writes to the data to the INDOFFSET in INDOFF. For reads, a REGFNUMEMPTY number of 32-bit values can be read before needing to poll FIFOSTAT again. The per-channel output FIFO (OUTFENTRIES) is readable via this offset.  A read of INDDATA will pop an entry off of the per-channel output FIFO.";
}

#define DMASTART_OFFSET 0x14
#define DMASTART_UNDEFMASK 0x00000003
union dmastart_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int dmastart:30;           /* cmdbuf FB offset */
    };

    u_int32_t reg32;
};

void Host1x_channelDev::fill_dmastart_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const dmastart_u old_value_t = { .reg32 = value };
    const dmastart_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: dmastart:30",
              "cmdbuf FB offset",
              30, old_value_t.dmastart, new_value_t.dmastart };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "This register triggers a DMA fetch from the FB for this channel, if the Put register doesn't equal the DMA Get register.";
}

#define DMAPUT_OFFSET 0x18
#define DMAPUT_UNDEFMASK 0x00000003
union dmaput_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int dmaput:30;             /* cmdbuf FB offset */
    };

    u_int32_t reg32;
};

void Host1x_channelDev::fill_dmaput_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const dmaput_u old_value_t = { .reg32 = value };
    const dmaput_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: dmaput:30",
              "cmdbuf FB offset",
              30, old_value_t.dmaput, new_value_t.dmaput };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "This register triggers a DMA fetch from the FB for this channel, if the PUT register doesn't equal the GET register.  This address is relative to the DMASTART base address. Does not support byte writes. All 4-byte data need to be programmed.";
}

#define DMAGET_OFFSET 0x1C
#define DMAGET_UNDEFMASK 0x00000003
union dmaget_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int dmaget:30;             /* cmdbuf FB offset */
    };

    u_int32_t reg32;
};

void Host1x_channelDev::fill_dmaget_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const dmaget_u old_value_t = { .reg32 = value };
    const dmaget_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: dmaget:30",
              "cmdbuf FB offset",
              30, old_value_t.dmaget, new_value_t.dmaget };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "This register tracks the FB offset the DMA engine has read up to (incremented as entries are loaded from the channels command buffer into the FIFO). This addresses is relative to the DMASTART base address.";
}

#define DMAEND_OFFSET 0x20
#define DMAEND_UNDEFMASK 0x00000003
union dmaend_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int dmaend:30;             /* cmdbuf FB offset */
    };

    u_int32_t reg32;
};

void Host1x_channelDev::fill_dmaend_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const dmaend_u old_value_t = { .reg32 = value };
    const dmaend_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: dmaend:30",
              "cmdbuf FB offset",
              30, old_value_t.dmaend, new_value_t.dmaend };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "The boundary of illegal addresses (either end of pushbuffer or end of physical memory). This is designed to prevent DMA from prefetching illegal addresses.  If DMA reaches this address before seeing a RESTART, it will stop. This would be a software error condition.";
}

#define DMACTRL_OFFSET 0x24
#define DMACTRL_UNDEFMASK 0xFFFFFFF8
union dmactrl_u {
    struct {
        unsigned int dmastop:1;             /* Stop DMA from fetching on this channel. NOTE: a Command DMA channel needs to be enabled for PIO-gather to work!! 0 = RUN 1 = STOP */
        unsigned int dmagetrst:1;           /* Reset GET pointer to '0'. Useful for cleaning up crashed channels. 0 = DISABLE 1 = ENABLE */
        unsigned int dmainitget:1;          /* Reset GET pointer to the value of DMAPUT when DMAGETRST is asserted. 0 = DISABLE 1 = ENABLE */
        unsigned int undefined_bits_3_31:29;
    };

    u_int32_t reg32;
};

void Host1x_channelDev::fill_dmactrl_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const dmactrl_u old_value_t = { .reg32 = value };
    const dmactrl_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: dmastop:1",
              "Stop DMA from fetching on this channel. NOTE: a Command DMA channel needs to be enabled for PIO-gather to work!!\n0 = RUN\n1 = STOP",
              1, old_value_t.dmastop, new_value_t.dmastop };
    m_bit_details_model.bits.append(entry);
    entry = { "01: dmagetrst:1",
              "Reset GET pointer to '0'. Useful for cleaning up crashed channels.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.dmagetrst, new_value_t.dmagetrst };
    m_bit_details_model.bits.append(entry);
    entry = { "02: dmainitget:1",
              "Reset GET pointer to the value of DMAPUT when DMAGETRST is asserted.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.dmainitget, new_value_t.dmainitget };
    m_bit_details_model.bits.append(entry);
    entry = { "03: undefined_bits_3_31:29", "", 29, old_value_t.undefined_bits_3_31, new_value_t.undefined_bits_3_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "DMA control register";
}

#define INDOFF2_OFFSET 0x8C
#define INDOFF2_UNDEFMASK 0x00000003
union indoff2_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int custom:30;
    };

    u_int32_t reg32;
};

void Host1x_channelDev::fill_indoff2_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const indoff2_u old_value_t = { .reg32 = value };
    const indoff2_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: custom:30", "", 30, old_value_t.custom, new_value_t.custom };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "The INDOFF and INDOFF2 registers (along with INDCNT and INDDATA) are used to indirectly read/write modules outside the host. If AUTOINC is set, INDOFFSET increments by 4 on every access of INDDATA.  REGFNUMEMPTY is polled to determine when valid data can be read from INDDATA.\nThe INDOFF register has limited capability on chips with large memory maps. If the top bit of the memory address is >= 27, all of memory cannot be addressed with INDOFF.  In these cases, use INDOFF2 to set the offset while still using INDOFF to set the other parameters.  Always have INDOFFUPD set to NO_UPDATE in these cases.  For register accesses, using INDOFF (with INDOFFUPD set to UPDATE) is always more efficient, since it only requires one write.\nIndirect framebuffer write is STRONGLY DISCOURAGED. There are better ways to write to memory (direct and through the channel memory map) and there is limited flow control in the host.  It's very easy to get into trouble with indirect framebuffer write.";
}

#define TICKCOUNT_HI_OFFSET 0x90
#define TICKCOUNT_HI_UNDEFMASK 0x00000000
union tickcount_hi_u {
    struct {
        unsigned int ticks_hi:32;
    };

    u_int32_t reg32;
};

void Host1x_channelDev::fill_tickcount_hi_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const tickcount_hi_u old_value_t = { .reg32 = value };
    const tickcount_hi_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: ticks_hi:32", "", 32, old_value_t.ticks_hi, new_value_t.ticks_hi };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "This register holds the high 32 bits of tick count value.";
}

#define TICKCOUNT_LO_OFFSET 0x94
#define TICKCOUNT_LO_UNDEFMASK 0x00000000
union tickcount_lo_u {
    struct {
        unsigned int ticks_lo:32;
    };

    u_int32_t reg32;
};

void Host1x_channelDev::fill_tickcount_lo_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const tickcount_lo_u old_value_t = { .reg32 = value };
    const tickcount_lo_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: ticks_lo:32", "", 32, old_value_t.ticks_lo, new_value_t.ticks_lo };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "This register holds the low 32 bits of tick count value.";
}

#define CHANNELCTRL_OFFSET 0x98
#define CHANNELCTRL_UNDEFMASK 0xFFFFFFFE
union channelctrl_u {
    struct {
        unsigned int enabletickcnt:1;       /* enable or disable tick counter 0 = DISABLE 1 = ENABLE */
        unsigned int undefined_bits_1_31:31;
    };

    u_int32_t reg32;
};

void Host1x_channelDev::fill_channelctrl_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const channelctrl_u old_value_t = { .reg32 = value };
    const channelctrl_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: enabletickcnt:1",
              "enable or disable tick counter\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.enabletickcnt, new_value_t.enabletickcnt };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_31:31", "", 31, old_value_t.undefined_bits_1_31, new_value_t.undefined_bits_1_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "This register will be used for controlling some channel related commands including enabling/disabling of tick counter.";
}

#define RAISE_OFFSET 0x10
#define RAISE_UNDEFMASK 0x00000000
union raise_u {
    struct {
        unsigned int raise:32;              /* This channel's RAISE vector */
    };

    u_int32_t reg32;
};

void Host1x_channelDev::fill_raise_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const raise_u old_value_t = { .reg32 = value };
    const raise_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: raise:32",
              "This channel's RAISE vector",
              32, old_value_t.raise, new_value_t.raise };
    m_bit_details_model.bits.append(entry);
}

#define FBBUFBASE_OFFSET 0x28
#define FBBUFBASE_UNDEFMASK 0x00000003
union fbbufbase_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int fbbufbase:30;
    };

    u_int32_t reg32;
};

void Host1x_channelDev::fill_fbbufbase_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const fbbufbase_u old_value_t = { .reg32 = value };
    const fbbufbase_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_1:2", "", 2, old_value_t.undefined_bits_0_1, new_value_t.undefined_bits_0_1 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: fbbufbase:30", "", 30, old_value_t.fbbufbase, new_value_t.fbbufbase };
    m_bit_details_model.bits.append(entry);
}

#define CMDSWAP_OFFSET 0x2C
#define CMDSWAP_UNDEFMASK 0xFFFFFFFC
union cmdswap_u {
    struct {
        unsigned int cmdswap:2;             /* Indirect framebuffer access swap control. 00 = No byte swap 01 = 16-bit byte swap ([31:0] -> {[23:16],[31:24],[7:0],[15:8]}) 10 = 32-bit byte swap ([31:0] -> {[7:0],[15:8],[23:16],[31:24]}) 11 = 32-bit word swap ([31:0] -> {[15:8],[7:0],[31:24],[23:16]}) */
        unsigned int undefined_bits_2_31:30;
    };

    u_int32_t reg32;
};

void Host1x_channelDev::fill_cmdswap_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const cmdswap_u old_value_t = { .reg32 = value };
    const cmdswap_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: cmdswap:2",
              "Indirect framebuffer access swap control.\n00 = No byte swap\n01 = 16-bit byte swap ([31:0] -> {[23:16],[31:24],[7:0],[15:8]})\n10 = 32-bit byte swap ([31:0] -> {[7:0],[15:8],[23:16],[31:24]})\n11 = 32-bit word swap ([31:0] -> {[15:8],[7:0],[31:24],[23:16]})",
              2, old_value_t.cmdswap, new_value_t.cmdswap };
    m_bit_details_model.bits.append(entry);
    entry = { "02: undefined_bits_2_31:30", "", 30, old_value_t.undefined_bits_2_31, new_value_t.undefined_bits_2_31 };
    m_bit_details_model.bits.append(entry);
}

bool Host1x_channelDev::is_offset_valid(const u_int32_t &offset) const
{
    switch (offset) {
    case FIFOSTAT_OFFSET:
    case INDOFF_OFFSET:
    case INDCNT_OFFSET:
    case INDDATA_OFFSET:
    case DMASTART_OFFSET:
    case DMAPUT_OFFSET:
    case DMAGET_OFFSET:
    case DMAEND_OFFSET:
    case DMACTRL_OFFSET:
    case INDOFF2_OFFSET:
    case TICKCOUNT_HI_OFFSET:
    case TICKCOUNT_LO_OFFSET:
    case CHANNELCTRL_OFFSET:
    case RAISE_OFFSET:
    case FBBUFBASE_OFFSET:
    case CMDSWAP_OFFSET:
        return true;
    default:
        break;
    }

    return false;
}

bool Host1x_channelDev::is_undef_changed(const u_int32_t &offset,
                                           const u_int32_t &value,
                                           const u_int32_t &new_value) const
{
    switch (offset) {
    case FIFOSTAT_OFFSET:
        if ((value ^ new_value) & FIFOSTAT_UNDEFMASK)
            return true;
        break;
    case INDOFF_OFFSET:
        if ((value ^ new_value) & INDOFF_UNDEFMASK)
            return true;
        break;
    case INDCNT_OFFSET:
        if ((value ^ new_value) & INDCNT_UNDEFMASK)
            return true;
        break;
    case INDDATA_OFFSET:
        if ((value ^ new_value) & INDDATA_UNDEFMASK)
            return true;
        break;
    case DMASTART_OFFSET:
        if ((value ^ new_value) & DMASTART_UNDEFMASK)
            return true;
        break;
    case DMAPUT_OFFSET:
        if ((value ^ new_value) & DMAPUT_UNDEFMASK)
            return true;
        break;
    case DMAGET_OFFSET:
        if ((value ^ new_value) & DMAGET_UNDEFMASK)
            return true;
        break;
    case DMAEND_OFFSET:
        if ((value ^ new_value) & DMAEND_UNDEFMASK)
            return true;
        break;
    case DMACTRL_OFFSET:
        if ((value ^ new_value) & DMACTRL_UNDEFMASK)
            return true;
        break;
    case INDOFF2_OFFSET:
        if ((value ^ new_value) & INDOFF2_UNDEFMASK)
            return true;
        break;
    case TICKCOUNT_HI_OFFSET:
        if ((value ^ new_value) & TICKCOUNT_HI_UNDEFMASK)
            return true;
        break;
    case TICKCOUNT_LO_OFFSET:
        if ((value ^ new_value) & TICKCOUNT_LO_UNDEFMASK)
            return true;
        break;
    case CHANNELCTRL_OFFSET:
        if ((value ^ new_value) & CHANNELCTRL_UNDEFMASK)
            return true;
        break;
    case RAISE_OFFSET:
        if ((value ^ new_value) & RAISE_UNDEFMASK)
            return true;
        break;
    case FBBUFBASE_OFFSET:
        if ((value ^ new_value) & FBBUFBASE_UNDEFMASK)
            return true;
        break;
    case CMDSWAP_OFFSET:
        if ((value ^ new_value) & CMDSWAP_UNDEFMASK)
            return true;
        break;

    default:
        break;
    }

    return false;
}

QString Host1x_channelDev::get_register_name(const log_entry &entry) const
{
    switch (entry.offset) {
    case FIFOSTAT_OFFSET:
        return QString("FIFOSTAT");
    case INDOFF_OFFSET:
        return QString("INDOFF");
    case INDCNT_OFFSET:
        return QString("INDCNT");
    case INDDATA_OFFSET:
        return QString("INDDATA");
    case DMASTART_OFFSET:
        return QString("DMASTART");
    case DMAPUT_OFFSET:
        return QString("DMAPUT");
    case DMAGET_OFFSET:
        return QString("DMAGET");
    case DMAEND_OFFSET:
        return QString("DMAEND");
    case DMACTRL_OFFSET:
        return QString("DMACTRL");
    case INDOFF2_OFFSET:
        return QString("INDOFF2");
    case TICKCOUNT_HI_OFFSET:
        return QString("TICKCOUNT_HI");
    case TICKCOUNT_LO_OFFSET:
        return QString("TICKCOUNT_LO");
    case CHANNELCTRL_OFFSET:
        return QString("CHANNELCTRL");
    case RAISE_OFFSET:
        return QString("RAISE");
    case FBBUFBASE_OFFSET:
        return QString("FBBUFBASE");
    case CMDSWAP_OFFSET:
        return QString("CMDSWAP");

    default:
        break;
    }

    qDebug() << QString().sprintf("HOST1X_CHANNEL: %s: Ooops... 0x%x", __func__, entry.offset);

    return QString().sprintf("Ooops... @0x%X", entry.offset);
}

void Host1x_channelDev::fill_bits_details(const u_int32_t &offset,
                                      const u_int32_t &value, const u_int32_t &new_value)
{
    switch (offset) {
    case FIFOSTAT_OFFSET:
        fill_fifostat_details(value, new_value);
        break;
    case INDOFF_OFFSET:
        fill_indoff_details(value, new_value);
        break;
    case INDCNT_OFFSET:
        fill_indcnt_details(value, new_value);
        break;
    case INDDATA_OFFSET:
        fill_inddata_details(value, new_value);
        break;
    case DMASTART_OFFSET:
        fill_dmastart_details(value, new_value);
        break;
    case DMAPUT_OFFSET:
        fill_dmaput_details(value, new_value);
        break;
    case DMAGET_OFFSET:
        fill_dmaget_details(value, new_value);
        break;
    case DMAEND_OFFSET:
        fill_dmaend_details(value, new_value);
        break;
    case DMACTRL_OFFSET:
        fill_dmactrl_details(value, new_value);
        break;
    case INDOFF2_OFFSET:
        fill_indoff2_details(value, new_value);
        break;
    case TICKCOUNT_HI_OFFSET:
        fill_tickcount_hi_details(value, new_value);
        break;
    case TICKCOUNT_LO_OFFSET:
        fill_tickcount_lo_details(value, new_value);
        break;
    case CHANNELCTRL_OFFSET:
        fill_channelctrl_details(value, new_value);
        break;
    case RAISE_OFFSET:
        fill_raise_details(value, new_value);
        break;
    case FBBUFBASE_OFFSET:
        fill_fbbufbase_details(value, new_value);
        break;
    case CMDSWAP_OFFSET:
        fill_cmdswap_details(value, new_value);
        break;

    default:
        m_bit_details_model.bits.clear();
        break;
    }
}
