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

#include "sdhcidev.h"

#include <QDebug>

SdhciDev::SdhciDev(QObject *parent) :
    Device(parent)
{
}

#define SYSTEM_ADDRESS_OFFSET 0x0
#define SYSTEM_ADDRESS_UNDEFMASK 0x00000000
union system_address_u {
    struct {
        unsigned int address:32;
    };

    u_int32_t reg32;
};

void SdhciDev::fill_system_address_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const system_address_u old_value_t = { .reg32 = value };
    const system_address_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: address:32", "", 32, old_value_t.address, new_value_t.address };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "ADDRESS\nThis register contains the system memory address for a SDMA transfer. When the Host Controller stops a SDMA transfer, this register shall point to the system address of the next contiguous data position. It can be accessed only if no transaction is executing (i.e., after a transaction has stopped). Read operations during transfers may return an invalid value.\nThe Host Driver shall initialize this register before starting a SDMA transaction. After SDMA has stopped, the next system address of the next contiguous data position can be read from this register. The SDMA transfer waits at the every boundary specified by the Host SDMA Buffer Boundary in the Block Size register. The Host Controller generates DMA Interrupt to request the Host Driver to update this register. The Host Driver sets the next system address of the next data position to this register. When the most upper byte of this register (003h) is written, the Host Controller restarts the SDMA transfer.\nWhen restarting SDMA by the Resume command or by setting Continue Request in the Block Gap Control register, the Host Controller shall start at the next contiguous address stored here in the SDMA System Address register. ADMA does not use this register.\nSDMA System Address Register";
}

#define BLOCK_SIZE_BLOCK_COUNT_OFFSET 0x4
#define BLOCK_SIZE_BLOCK_COUNT_UNDEFMASK 0x00000000
union block_size_block_count_u {
    struct {
        unsigned int xfer_block_size_11_0:12;
        unsigned int host_dma_buffer_size:3;/* 0 = DMA4K 1 = DMA8K 2 = DMA16K 3 = DMA32K 4 = DMA64K 5 = DMA128K 6 = DMA256K; 7 = DMA512K */
        unsigned int xfer_block_size_12:1;
        unsigned int blocks_count:16;
    };

    u_int32_t reg32;
};

void SdhciDev::fill_block_size_block_count_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const block_size_block_count_u old_value_t = { .reg32 = value };
    const block_size_block_count_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: xfer_block_size_11_0:12", "", 12, old_value_t.xfer_block_size_11_0, new_value_t.xfer_block_size_11_0 };
    m_bit_details_model.bits.append(entry);
    entry = { "12: host_dma_buffer_size:3",
              "0 = DMA4K\n1 = DMA8K\n2 = DMA16K\n3 = DMA32K\n4 = DMA64K\n5 = DMA128K\n6 = DMA256K;\n7 = DMA512K",
              3, old_value_t.host_dma_buffer_size, new_value_t.host_dma_buffer_size };
    m_bit_details_model.bits.append(entry);
    entry = { "15: xfer_block_size_12:1", "", 1, old_value_t.xfer_block_size_12, new_value_t.xfer_block_size_12 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: blocks_count:16", "", 16, old_value_t.blocks_count, new_value_t.blocks_count };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "HOST_DMA_BUFFER_SIZE\nThe large contiguous memory space may not be available in the virtual memory system. To perform long SDMA transfer, SDMA System Address register shall be updated at every system memory boundary during SDMA transfer.\nThese bits specify the size of contiguous buffer in the system memory. The SDMA transfer shall wait at the every boundary specified by these fields and the Host Controller generates the DMA Interrupt to request the Host Driver to update the SDMA System Address register. At the end of transfer, the Host Controller may issue or may not issue DMA Interrupt. In particular, DMA Interrupt shall not be issued after Transfer Complete Interrupt is issued. In case of this register is set to 0 (buffer size = 4K bytes), lower 12-bit of byte address points data in the contiguous buffer and the upper 20-bit points the location of the buffer in the system memory. The SDMA transfer stops when the Host Controller detects carry out of the address from bit 11 to 12.\nThese bits shall be supported when the SDMA Support in the Capabilities register is set to 1 and this function is active when the DMA Enable in the Transfer Mode register is set to 1.\nADMA does not use this register.\n000b 4K bytes (Detects A11 carry out)\n001b 8K bytes (Detects A12 carry out)\n010b 16K Bytes (Detects A13 carry out)\n011b 32K Bytes (Detects A14 carry out)\n100b 64K bytes (Detects A15 carry out)\n101b 128K Bytes (Detects A16 carry out)\n110b 256K Bytes (Detects A17 carry out)\n111b 512K Bytes (Detects A18 carry out)\nXFER_BLOCK_SIZE_11_0\nThis register specifies the block size of data transfers for CMD17, CMD18, CMD24, CMD25, and CMD53. Values ranging from 1 up to the maximum buffer size can be set. In case of memory, it shall be set up to 512 bytes (Refer to Implementation Note in Section 1.7.2). It can be accessed only if no transaction is executing (i.e., after a transaction has stopped). Read operations during transfers may return an invalid value, and write operations shall be ignored.\n0800h 2048 Bytes\n 0200h 512 Bytes\n01FFh 511 Bytes\n 0004h 4 Bytes\n0003h 3 Bytes\n0002h 2 Bytes\n0001h 1 Byte\n0000h No data transfer\nBLOCKS_COUNT\nThis register is enabled when Block Count Enable in the Transfer Mode register is set to 1 and is valid only for multiple block transfers. The Host Driver shall set this register to a value between 1 and the maximum block count. The Host Controller decrements the block count after each block transfer and stops when the count reaches zero. Setting the block count to 0 results in no data blocks is transferred.\nThis register should be accessed only when no transaction is executing (i.e., after transactions are stopped). During data transfer, read operations on this register may return an invalid value and write operations are ignored. When a suspend command is completed, the number of blocks yet to be transferred can be determined by reading this register. Before issuing a resume command, the Host Driver shall restore the previously saved block count.\nFFFFh 65535 blocks\n0002h 2 blocks\n0001h 1 block\n0000h Stop Count\nXFER_BLOCK_SIZE_12\nTransfer Block Size 12th bit. This bit is added to support 4Kb Data block transfer.\nBlock Size Register";
}

#define ARGUMENT_OFFSET 0x8
#define ARGUMENT_UNDEFMASK 0x00000000
union argument_u {
    struct {
        unsigned int command_argument:32;
    };

    u_int32_t reg32;
};

void SdhciDev::fill_argument_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const argument_u old_value_t = { .reg32 = value };
    const argument_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: command_argument:32", "", 32, old_value_t.command_argument, new_value_t.command_argument };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "COMMAND_ARGUMENT\nThe SD Command Argument is specified as bit39-8 of Command-Format in the Physical Layer Specification.\nCommand Argument Register";
}

#define CMD_XFER_MODE_OFFSET 0xC
#define CMD_XFER_MODE_UNDEFMASK 0xC004FF08
union cmd_xfer_mode_u {
    struct {
        unsigned int dma_en:1;              /* 0 = DISABLE 1 = ENABLE */
        unsigned int block_count_en:1;      /* 0 = DISABLE 1 = ENABLE */
        unsigned int auto_cmd12_en:1;       /* 0 = DISABLE 1 = ENABLE */
        unsigned int undefined_bit_3:1;
        unsigned int data_xfer_dir_sel:1;   /* 0 = WRITE 1 = READ */
        unsigned int multi_block_select:1;  /* 0 = DISABLE 1 = ENABLE */
        unsigned int cmd_comp_ata:1;        /* 0 = DISABLE 1 = ENABLE */
        unsigned int spi_mode:1;            /* 0 = DISABLE 1 = ENABLE */
        unsigned int undefined_bits_8_15:8;
        unsigned int resp_type_select:2;    /* 0 = NO_RESPONSE 1 = RESP_LENGTH_136 2 = RESP_LENGTH_48 3 = RESP_LENGTH_48BUSY 0 = SPI_R1_RESPONSE 1 = SPI_R2_RESPONSE 2 = SPI_R3_RESPONSE 3 = SPI_R1b_RESPONSE */
        unsigned int undefined_bit_18:1;
        unsigned int cmd_crc_check_en:1;    /* 0 = DISABLE 1 = ENABLE */
        unsigned int cmd_index_check_en:1;  /* 0 = DISABLE 1 = ENABLE */
        unsigned int data_present_select:1; /* 0 = NO_DATA_TRANSFER 1 = DATA_TRANSFER */
        unsigned int command_type:2;        /* 0 = NORMAL 1 = SUSPEND 2 = RESUME 3 = ABORT */
        unsigned int command_index:6;
        unsigned int undefined_bits_30_31:2;
    };

    u_int32_t reg32;
};

void SdhciDev::fill_cmd_xfer_mode_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const cmd_xfer_mode_u old_value_t = { .reg32 = value };
    const cmd_xfer_mode_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: dma_en:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.dma_en, new_value_t.dma_en };
    m_bit_details_model.bits.append(entry);
    entry = { "01: block_count_en:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.block_count_en, new_value_t.block_count_en };
    m_bit_details_model.bits.append(entry);
    entry = { "02: auto_cmd12_en:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.auto_cmd12_en, new_value_t.auto_cmd12_en };
    m_bit_details_model.bits.append(entry);
    entry = { "03: undefined_bit_3:1", "", 1, old_value_t.undefined_bit_3, new_value_t.undefined_bit_3 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: data_xfer_dir_sel:1",
              "0 = WRITE\n1 = READ",
              1, old_value_t.data_xfer_dir_sel, new_value_t.data_xfer_dir_sel };
    m_bit_details_model.bits.append(entry);
    entry = { "05: multi_block_select:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.multi_block_select, new_value_t.multi_block_select };
    m_bit_details_model.bits.append(entry);
    entry = { "06: cmd_comp_ata:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.cmd_comp_ata, new_value_t.cmd_comp_ata };
    m_bit_details_model.bits.append(entry);
    entry = { "07: spi_mode:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.spi_mode, new_value_t.spi_mode };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_15:8", "", 8, old_value_t.undefined_bits_8_15, new_value_t.undefined_bits_8_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: resp_type_select:2",
              "0 = NO_RESPONSE\n1 = RESP_LENGTH_136\n2 = RESP_LENGTH_48\n3 = RESP_LENGTH_48BUSY\n0 = SPI_R1_RESPONSE\n1 = SPI_R2_RESPONSE\n2 = SPI_R3_RESPONSE\n3 = SPI_R1b_RESPONSE",
              2, old_value_t.resp_type_select, new_value_t.resp_type_select };
    m_bit_details_model.bits.append(entry);
    entry = { "18: undefined_bit_18:1", "", 1, old_value_t.undefined_bit_18, new_value_t.undefined_bit_18 };
    m_bit_details_model.bits.append(entry);
    entry = { "19: cmd_crc_check_en:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.cmd_crc_check_en, new_value_t.cmd_crc_check_en };
    m_bit_details_model.bits.append(entry);
    entry = { "20: cmd_index_check_en:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.cmd_index_check_en, new_value_t.cmd_index_check_en };
    m_bit_details_model.bits.append(entry);
    entry = { "21: data_present_select:1",
              "0 = NO_DATA_TRANSFER\n1 = DATA_TRANSFER",
              1, old_value_t.data_present_select, new_value_t.data_present_select };
    m_bit_details_model.bits.append(entry);
    entry = { "22: command_type:2",
              "0 = NORMAL\n1 = SUSPEND\n2 = RESUME\n3 = ABORT",
              2, old_value_t.command_type, new_value_t.command_type };
    m_bit_details_model.bits.append(entry);
    entry = { "24: command_index:6", "", 6, old_value_t.command_index, new_value_t.command_index };
    m_bit_details_model.bits.append(entry);
    entry = { "30: undefined_bits_30_31:2", "", 2, old_value_t.undefined_bits_30_31, new_value_t.undefined_bits_30_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "COMMAND_INDEX\nThese bits shall be set to the command number (CMD0-63, ACMD0-63) that is specified in bits 45-40 of the Command-Format in the Physical Layer Specification and SDIO Card Specification.\nCOMMAND_TYPE\nThere are three types of special commands: Suspend, Resume and Abort. These bits shall be set to 00b for all other commands.\n- Suspend Command\nIf the Suspend command succeeds, the Host Controller shall assume the SD Bus has been released and that it is possible to issue the next command, which uses the DAT line. The Host Controller shall de-assert Read Wait for read transactions and stop checking busy for write transactions. The interrupt cycle shall start, in 4-bit mode. If the Suspend command fails, the Host Controller shall maintain its current state, and the Host Driver shall restart the transfer by setting Continue Request in the Block Gap Control register.\n- Resume Command\nThe Host Driver re-starts the data transfer by restoring the registers in the range of 000-00Dh. The Host Controller shall check for busy before starting write transfers.\n- Abort Command\nIf this command is set when executing a read transfer, the Host Controller shall stop reads to the buffer. If this command is set when executing a write transfer, the Host Controller shall stop driving the DAT line. After issuing the Abort command, the Host Driver should issue a software reset.\n11b Abort CMD12, CMD52 for writing \"I/O Abort\" in CCCR\n10b Resume CMD52 for writing \"Function Select\" in CCCR\n01b Suspend CMD52 for writing \"Bus Suspend\" in CCCR\n00b Normal Other commands\nDATA_PRESENT_SELECT\nThis bit is set to 1 to indicate that data is present and shall be transferred using the DAT line. It is set to 0 for the following:\n- Commands using only CMD line (ex. CMD52).\n- Commands with no data transfer but using busy signal on DAT[0] line (R1b or R5b ex. CMD38)\n- Resume command\nCMD_INDEX_CHECK_EN\nIf this bit is set to 1, the Host Controller shall check the Index field in the response to see if it has the same value as the command index. If it is not, it is reported as a Command Index Error. If this bit is set to 0, the Index field is not checked.\nCMD_CRC_CHECK_EN\nIf this bit is set to 1, the Host Controller shall check the CRC field in the response. If an error is detected, it is reported as a Command CRC Error. If this bit is set to 0, the CRC field is not checked. The position of CRC field is determined according to the length of the response.\nRESP_TYPE_SELECT\nNormal Mode:\n- 00 No Response\n- 01 Response Length 136\n- 10 Response Length 48\n- 11 Response Length 48 check Busy after response\nSPI Mode:(VENDOR Definition)\n- 00 R1 Response Length 8\n- 01 R2 Response Length 16\n- 10 R3 Response Length 40\n- 11 R1b Response Length 8\nSPI_MODE(VENDOR Bit)\nSPI Mode is enabled. The Response types definitions are different. Refer to Response type field.\nCMD_COMP_ATA- CEATA Command Completion Signal Enable.(VENDOR Bit)\nEnabled to wait for CCS Signal. After this has been received the Transfer complete occurs.\nMULTI_BLOCK_SELECT - Multi / Single Block Select\nThis bit is set when issuing multiple-block transfer commands using DAT line. For any other commands, this bit shall be set to 0. If this bit is 0, it is not necessary to set the Block Count register.\n1 Multiple Block\n0 Single Block\nDATA_XFER_DIR_SEL - Data Transfer Direction Select\nThis bit defines the direction of DAT line data transfers. The bit is set to 1 by the Host Driver to transfer data from the SD card to the SD Host Controller and it is set to 0 for all other commands.\n1 Read (Card to Host)\n0 Write (Host to Card)\nAUTO_CMD12_EN - Auto CMD12 Enable\nMultiple block transfers for memory require CMD12 to stop the transaction. When this bit is set to 1, the Host Controller shall issue CMD12 automatically when last block transfer is completed. The Host Driver shall not set this bit to issue commands that do not require CMD12 to stop data transfer. In particular, secure commands defined in the Part 3 File Security specification do not require CMD12.\nBLOCK_COUNT_EN - Block Count Enable\nThis bit is used to enable the Block Count register, which is only relevant for multiple block transfers. When this bit is 0, the Block Count register is disabled, which is useful in executing an infinite transfer. (Refer to Table 2-8) If ADMA2 data transfer is more than 65535 blocks, this bit shall be set to 0. In this case, data transfer length is designated by Descriptor Table.\nDMA_EN - DMA Enable\nThis bit enables DMA functionality as described in section 1.4. DMA can be enabled only if it is supported as indicated in the Capabilities register. One of the DMA modes can be selected by DMA Select in the Host Control register. If DMA is not supported, this bit is meaningless and shall always read 0. If this bit is set to 1, a DMA operation shall begin when the Host Driver writes to the upper byte of Command register (00Fh).\nCommand and Transfer Mode Register";
}

#define RESPONSE_R0_R1_OFFSET 0x10
#define RESPONSE_R0_R1_UNDEFMASK 0x00000000
union response_r0_r1_u {
    struct {
        unsigned int cmd_resp_15_0:16;
        unsigned int cmd_resp_31_16:16;
    };

    u_int32_t reg32;
};

void SdhciDev::fill_response_r0_r1_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const response_r0_r1_u old_value_t = { .reg32 = value };
    const response_r0_r1_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: cmd_resp_15_0:16", "", 16, old_value_t.cmd_resp_15_0, new_value_t.cmd_resp_15_0 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: cmd_resp_31_16:16", "", 16, old_value_t.cmd_resp_31_16, new_value_t.cmd_resp_31_16 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Command Response Registers\nThe Table below describes the mapping of command responses from the SD Bus to this register for each response type. In the table, R[…] refers to a bit range within the response data as transmitted on the SD Bus, REP[] refers to a bit range within the Response register.\nKind of Response\n Meaning of Response\n Response Field\n Response Register\nR1, R1b (normal response)\n Card Status\n R [39:8]\n REP [31:0]\nR1b (Auto CMD12 response)\n Card Status for Auto CMD12\n R [39:8]\n REP [127:96]\nR2 (CID, CSD register)\n CID or CSD reg. incl.\n R [127:8]\n REP [119:0]\nR3 (OCR register)\n OCR register for memory\n R [39:8]\n REP [31:0]\nR4 (OCR register)\n OCR register for I/O etc\n R [39:8]\n REP [31:0]\nR5,R5b\n SDIO response\n R [39:8]\n REP [31:0]\nR6 (Published RCA response)\n New published RCA[31:16] etc\n R [39:8]\n REP [31:0]\nResponse Bit Definition for Each Response Type\nCommand Response [31:0] (R0) Register";
}

#define RESPONSE_R2_R3_OFFSET 0x14
#define RESPONSE_R2_R3_UNDEFMASK 0x00000000
union response_r2_r3_u {
    struct {
        unsigned int cmd_resp_47_32:16;
        unsigned int cmd_resp_63_48:16;
    };

    u_int32_t reg32;
};

void SdhciDev::fill_response_r2_r3_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const response_r2_r3_u old_value_t = { .reg32 = value };
    const response_r2_r3_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: cmd_resp_47_32:16", "", 16, old_value_t.cmd_resp_47_32, new_value_t.cmd_resp_47_32 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: cmd_resp_63_48:16", "", 16, old_value_t.cmd_resp_63_48, new_value_t.cmd_resp_63_48 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Command Response [63:32] (R2) Register";
}

#define RESPONSE_R4_R5_OFFSET 0x18
#define RESPONSE_R4_R5_UNDEFMASK 0x00000000
union response_r4_r5_u {
    struct {
        unsigned int cmd_resp_79_64:16;
        unsigned int cmd_resp_95_80:16;
    };

    u_int32_t reg32;
};

void SdhciDev::fill_response_r4_r5_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const response_r4_r5_u old_value_t = { .reg32 = value };
    const response_r4_r5_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: cmd_resp_79_64:16", "", 16, old_value_t.cmd_resp_79_64, new_value_t.cmd_resp_79_64 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: cmd_resp_95_80:16", "", 16, old_value_t.cmd_resp_95_80, new_value_t.cmd_resp_95_80 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Command Response [95:64] (R4) Register";
}

#define RESPONSE_R6_R7_OFFSET 0x1C
#define RESPONSE_R6_R7_UNDEFMASK 0x00000000
union response_r6_r7_u {
    struct {
        unsigned int cmd_resp_111_96:16;
        unsigned int cmd_resp_127_112:16;
    };

    u_int32_t reg32;
};

void SdhciDev::fill_response_r6_r7_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const response_r6_r7_u old_value_t = { .reg32 = value };
    const response_r6_r7_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: cmd_resp_111_96:16", "", 16, old_value_t.cmd_resp_111_96, new_value_t.cmd_resp_111_96 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: cmd_resp_127_112:16", "", 16, old_value_t.cmd_resp_127_112, new_value_t.cmd_resp_127_112 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = " Command Response [127:96] (R6) Register";
}

#define BUFFER_DATA_PORT_OFFSET 0x20
#define BUFFER_DATA_PORT_UNDEFMASK 0x00000000
union buffer_data_port_u {
    struct {
        unsigned int buffer_data:32;        /*  */
    };

    u_int32_t reg32;
};

void SdhciDev::fill_buffer_data_port_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const buffer_data_port_u old_value_t = { .reg32 = value };
    const buffer_data_port_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: buffer_data:32",
              "",
              32, old_value_t.buffer_data, new_value_t.buffer_data };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "The Host Controller Buffer can be accessed through  this 32-bit Data Port Register.\nBuffer Data Port Register";
}

#define PRESENT_STATE_OFFSET 0x24
#define PRESENT_STATE_UNDEFMASK 0xE000F0F8
union present_state_u {
    struct {
        unsigned int cmd_inhibit_cmd:1;     /* 0 = INACTIVE 1 = ACTIVE */
        unsigned int cmd_inhibit_dat:1;     /* 0 = INACTIVE 1 = ACTIVE */
        unsigned int dat_line_active:1;     /* 0 = INACTIVE 1 = ACTIVE */
        unsigned int undefined_bits_3_7:5;
        unsigned int write_xfer_active:1;   /* 0 = NO_DATA 1 = TRANSFERING */
        unsigned int read_xfer_active:1;    /* 0 = NO_DATA 1 = TRANSFERING */
        unsigned int buffer_write_en:1;     /* 0 = DISABLE 1 = ENABLE */
        unsigned int buffer_read_en:1;      /* 0 = DISABLE 1 = ENABLE */
        unsigned int undefined_bits_12_15:4;
        unsigned int card_inserted:1;       /* 0 = DEBOUNCE 1 = INSERTED */
        unsigned int card_state_stable:1;   /* 0 = DEBOUNCE 1 = INSERTED */
        unsigned int card_detect_pin_level:1;/* 0 = NO_CARD 1 = CARD */
        unsigned int write_protect_level:1; /* 0 = PROTECTED 1 = ENABLED */
        unsigned int dat_3_0_line_level:4;
        unsigned int cmd_line_level:1;      /* 0 = LOW 1 = HIGH */
        unsigned int dat_7_4_line_level:4;
        unsigned int undefined_bits_29_31:3;
    };

    u_int32_t reg32;
};

void SdhciDev::fill_present_state_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const present_state_u old_value_t = { .reg32 = value };
    const present_state_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: cmd_inhibit_cmd:1",
              "0 = INACTIVE\n1 = ACTIVE",
              1, old_value_t.cmd_inhibit_cmd, new_value_t.cmd_inhibit_cmd };
    m_bit_details_model.bits.append(entry);
    entry = { "01: cmd_inhibit_dat:1",
              "0 = INACTIVE\n1 = ACTIVE",
              1, old_value_t.cmd_inhibit_dat, new_value_t.cmd_inhibit_dat };
    m_bit_details_model.bits.append(entry);
    entry = { "02: dat_line_active:1",
              "0 = INACTIVE\n1 = ACTIVE",
              1, old_value_t.dat_line_active, new_value_t.dat_line_active };
    m_bit_details_model.bits.append(entry);
    entry = { "03: undefined_bits_3_7:5", "", 5, old_value_t.undefined_bits_3_7, new_value_t.undefined_bits_3_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: write_xfer_active:1",
              "0 = NO_DATA\n1 = TRANSFERING",
              1, old_value_t.write_xfer_active, new_value_t.write_xfer_active };
    m_bit_details_model.bits.append(entry);
    entry = { "09: read_xfer_active:1",
              "0 = NO_DATA\n1 = TRANSFERING",
              1, old_value_t.read_xfer_active, new_value_t.read_xfer_active };
    m_bit_details_model.bits.append(entry);
    entry = { "10: buffer_write_en:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.buffer_write_en, new_value_t.buffer_write_en };
    m_bit_details_model.bits.append(entry);
    entry = { "11: buffer_read_en:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.buffer_read_en, new_value_t.buffer_read_en };
    m_bit_details_model.bits.append(entry);
    entry = { "12: undefined_bits_12_15:4", "", 4, old_value_t.undefined_bits_12_15, new_value_t.undefined_bits_12_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: card_inserted:1",
              "0 = DEBOUNCE\n1 = INSERTED",
              1, old_value_t.card_inserted, new_value_t.card_inserted };
    m_bit_details_model.bits.append(entry);
    entry = { "17: card_state_stable:1",
              "0 = DEBOUNCE\n1 = INSERTED",
              1, old_value_t.card_state_stable, new_value_t.card_state_stable };
    m_bit_details_model.bits.append(entry);
    entry = { "18: card_detect_pin_level:1",
              "0 = NO_CARD\n1 = CARD",
              1, old_value_t.card_detect_pin_level, new_value_t.card_detect_pin_level };
    m_bit_details_model.bits.append(entry);
    entry = { "19: write_protect_level:1",
              "0 = PROTECTED\n1 = ENABLED",
              1, old_value_t.write_protect_level, new_value_t.write_protect_level };
    m_bit_details_model.bits.append(entry);
    entry = { "20: dat_3_0_line_level:4", "", 4, old_value_t.dat_3_0_line_level, new_value_t.dat_3_0_line_level };
    m_bit_details_model.bits.append(entry);
    entry = { "24: cmd_line_level:1",
              "0 = LOW\n1 = HIGH",
              1, old_value_t.cmd_line_level, new_value_t.cmd_line_level };
    m_bit_details_model.bits.append(entry);
    entry = { "25: dat_7_4_line_level:4", "", 4, old_value_t.dat_7_4_line_level, new_value_t.dat_7_4_line_level };
    m_bit_details_model.bits.append(entry);
    entry = { "29: undefined_bits_29_31:3", "", 3, old_value_t.undefined_bits_29_31, new_value_t.undefined_bits_29_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "DAT_7_4_LINE_LEVEL - DAT[7:4] Line Signal Level(VENDOR Bit)\nThis status is used to check the DAT line level to recover from errors, and for debugging.\nCMD_LINE_LEVEL - CMD Line Signal Level\nThis status is used to check the CMD line level to recover from errors, and for debugging.\nDAT_3_0_LINE_LEVEL - DAT[3:0] Line Signal Level\nThis status is used to check the DAT line level to recover from errors, and for debugging. This is especially useful in detecting the busy signal level from DAT[0].\nWRITE_PROTECT_LEVEL - Write Protect Switch Pin Level\nCARD_DETECT_PIN_LEVEL - Card Detect Pin Level\nCARD_STATE_STABLE - Card State Stable\nCARD_INSERTED - Card Inserted\nBUFFER_READ_EN - Buffer Read Enable\nThis status is used for non-DMA read transfers.\nBUFFER_WRITE_EN - Buffer Write Enable\nThis status is used for non-DMA write transfers.\nREAD_XFER_ACTIVE - Read Transfer Active\nWRITE_XFER_ACTIVE - Write Transfer Active\nDAT_LINE_ACTIVE - DAT Line Active\nCMD_INHIBIT_DAT - Command Inhibit (DAT)\nCMD_INHIBIT_CMD - Command Inhibit (CMD)\nPresent State Register";
}

#define POWER_CONTROL_HOST_OFFSET 0x28
#define POWER_CONTROL_HOST_UNDEFMASK 0xF8F0F000
union power_control_host_u {
    struct {
        unsigned int led_control:1;         /* 0 = OFF 1 = ON */
        unsigned int data_xfer_width:1;     /* 0 = BIT_1 1 = BIT_4 */
        unsigned int high_speed_en:1;       /* 0 = NORMAL_SPEED 1 = HIGH_SPEED */
        unsigned int dma_select:2;          /* 0 = SDMA 1 = ADMA1_32BIT 2 = ADMA2_32BIT 3 = ADMA2_64BIT */
        unsigned int extended_data_transfer_width:1;/* 0 = NOBIT_8 1 = BIT_8 */
        unsigned int card_detect_test_lvl:1;/* 0 = NO_CARD 1 = CARD_INSERTED */
        unsigned int card_detect_signal_detect:1;/* 0 = SDCD 1 = CARD_DTECT_TST_LVL */
        unsigned int sd_bus_power:1;        /* 0 = POWER_OFF 1 = POWER_ON */
        unsigned int sd_bus_voltage_select:3;/* 5 = V1_8 6 = V3_0 7 = V3_3 */
        unsigned int undefined_bits_12_15:4;
        unsigned int stop_at_block_gap_request:1;/* 0 = STOP 1 = TRANSFER */
        unsigned int continue_request:1;    /* 0 = IGNORED 1 = RESTART */
        unsigned int read_wait_control:1;   /* 0 = DISABLE 1 = ENABLE */
        unsigned int interrupt_at_block_gap:1;/* 0 = DISABLE 1 = ENABLE */
        unsigned int undefined_bits_20_23:4;
        unsigned int wakeup_on_card_interrupt:1;/* 0 = DISABLE 1 = ENABLE */
        unsigned int wakeup_on_card_insertion:1;/* 0 = DISABLE 1 = ENABLE */
        unsigned int wakeup_on_card_removal:1;/* 0 = DISABLE 1 = ENABLE */
        unsigned int undefined_bits_27_31:5;
    };

    u_int32_t reg32;
};

void SdhciDev::fill_power_control_host_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const power_control_host_u old_value_t = { .reg32 = value };
    const power_control_host_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: led_control:1",
              "0 = OFF\n1 = ON",
              1, old_value_t.led_control, new_value_t.led_control };
    m_bit_details_model.bits.append(entry);
    entry = { "01: data_xfer_width:1",
              "0 = BIT_1\n1 = BIT_4",
              1, old_value_t.data_xfer_width, new_value_t.data_xfer_width };
    m_bit_details_model.bits.append(entry);
    entry = { "02: high_speed_en:1",
              "0 = NORMAL_SPEED\n1 = HIGH_SPEED",
              1, old_value_t.high_speed_en, new_value_t.high_speed_en };
    m_bit_details_model.bits.append(entry);
    entry = { "03: dma_select:2",
              "0 = SDMA\n1 = ADMA1_32BIT\n2 = ADMA2_32BIT\n3 = ADMA2_64BIT",
              2, old_value_t.dma_select, new_value_t.dma_select };
    m_bit_details_model.bits.append(entry);
    entry = { "05: extended_data_transfer_width:1",
              "0 = NOBIT_8\n1 = BIT_8",
              1, old_value_t.extended_data_transfer_width, new_value_t.extended_data_transfer_width };
    m_bit_details_model.bits.append(entry);
    entry = { "06: card_detect_test_lvl:1",
              "0 = NO_CARD\n1 = CARD_INSERTED",
              1, old_value_t.card_detect_test_lvl, new_value_t.card_detect_test_lvl };
    m_bit_details_model.bits.append(entry);
    entry = { "07: card_detect_signal_detect:1",
              "0 = SDCD\n1 = CARD_DTECT_TST_LVL",
              1, old_value_t.card_detect_signal_detect, new_value_t.card_detect_signal_detect };
    m_bit_details_model.bits.append(entry);
    entry = { "08: sd_bus_power:1",
              "0 = POWER_OFF\n1 = POWER_ON",
              1, old_value_t.sd_bus_power, new_value_t.sd_bus_power };
    m_bit_details_model.bits.append(entry);
    entry = { "09: sd_bus_voltage_select:3",
              "5 = V1_8\n6 = V3_0\n7 = V3_3",
              3, old_value_t.sd_bus_voltage_select, new_value_t.sd_bus_voltage_select };
    m_bit_details_model.bits.append(entry);
    entry = { "12: undefined_bits_12_15:4", "", 4, old_value_t.undefined_bits_12_15, new_value_t.undefined_bits_12_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: stop_at_block_gap_request:1",
              "0 = STOP\n1 = TRANSFER",
              1, old_value_t.stop_at_block_gap_request, new_value_t.stop_at_block_gap_request };
    m_bit_details_model.bits.append(entry);
    entry = { "17: continue_request:1",
              "0 = IGNORED\n1 = RESTART",
              1, old_value_t.continue_request, new_value_t.continue_request };
    m_bit_details_model.bits.append(entry);
    entry = { "18: read_wait_control:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.read_wait_control, new_value_t.read_wait_control };
    m_bit_details_model.bits.append(entry);
    entry = { "19: interrupt_at_block_gap:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.interrupt_at_block_gap, new_value_t.interrupt_at_block_gap };
    m_bit_details_model.bits.append(entry);
    entry = { "20: undefined_bits_20_23:4", "", 4, old_value_t.undefined_bits_20_23, new_value_t.undefined_bits_20_23 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: wakeup_on_card_interrupt:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.wakeup_on_card_interrupt, new_value_t.wakeup_on_card_interrupt };
    m_bit_details_model.bits.append(entry);
    entry = { "25: wakeup_on_card_insertion:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.wakeup_on_card_insertion, new_value_t.wakeup_on_card_insertion };
    m_bit_details_model.bits.append(entry);
    entry = { "26: wakeup_on_card_removal:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.wakeup_on_card_removal, new_value_t.wakeup_on_card_removal };
    m_bit_details_model.bits.append(entry);
    entry = { "27: undefined_bits_27_31:5", "", 5, old_value_t.undefined_bits_27_31, new_value_t.undefined_bits_27_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "WAKEUP_ON_CARD_REMOVAL - Wakeup Event Enable On SD Card Removal\nThis bit enables wakeup event via Card Removal assertion in the Normal Interrupt Status register. FN_WUS (Wake Up Support) in CIS does not affect this bit.\nWAKEUP_ON_CARD_INSERTION - Wakeup Event Enable On SD Card Insertion\nThis bit enables wakeup event via Card Insertion assertion in the Normal Interrupt Status register. FN_WUS (Wake Up Support) in CIS does not affect this bit.\nWAKEUP_ON_CARD_INTERRUPT - Wakeup Event Enable On Card Interrupt\nThis bit enables wakeup event via Card Interrupt assertion in the Normal Interrupt Status register. This bit can be set to 1 if FN_WUS (Wake Up Support) in CIS is set to 1.\nINTERRUPT_AT_BLOCK_GAP - Interrupt At Block Gap\nThis bit is valid only in 4-bit mode of the SDIO card and selects a sample point in the interrupt cycle. Setting to 1 enables interrupt detection at the block gap for a multiple block transfer. Setting to 0 disables interrupt detection during a multiple block transfer. If the SD card cannot signal an interrupt during a multiple block transfer, this bit should be set to 0. When the Host Driver detects an SD card insertion, it shall set this bit according to the CCCR of the SDIO card.\nREAD_WAIT_CONTROL - Read Wait Control\nThe read wait function is optional for SDIO cards. If the card supports read wait, set this bit to enable use of the read wait protocol to stop read data using the DAT[2] line. Otherwise, the Host Controller has to stop the SD Clock to hold read data, which restricts commands generation. When the Host Driver detects an SD card insertion, it shall set this bit according to the CCCR of the SDIO card. If the card does not support read wait, this bit shall never be set to 1 otherwise DAT line conflict may occur. If this bit is set to 0, Suspend/Resume cannot be supported.\nCONTINUE_REQUEST - Continue Request\nThis bit is used to restart a transaction, which was stopped using the Stop At Block Gap Request. To cancel stop at the block gap, set Stop At Block Gap Request to 0 and set this bit 1 to restart the transfer. The Host Controller automatically clears this bit in either of the following cases:\n- In the case of a read transaction, the DAT Line Active changes from 0 to 1 as a read transaction restarts.\n- In the case of a write transaction, the Write Transfer Active changes from 0 to 1 as the write transaction restarts. Therefore, it is not necessary for Host Driver to set this bit to 0. If Stop At Block Gap Request is set to 1, any write to this bit is ignored.\nSTOP_AT_BLOCK_GAP_REQUEST - Stop At Block Gap Request\nThis bit is used to stop executing read and write transaction at the next block gap for non-DMA, SDMA and ADMA transfers. The Host Driver shall leave this bit set to 1 until the Transfer Complete is set to 1. Clearing both Stop At Block Gap Request and Continue Request shall not cause the transaction to restart. When Host Controller version is 1.00, the Host Driver can set this bit if the card supports Read Wait Control. When Host Controller version is 2.00 or higher, the Host Driver can set this bit regardless of the card supports Read Wait Control. The Host Controller shall stop read transfer by using Read Wait or stopping SD clock.\nIn case of write transfers in which the Host Driver writes data to the Buffer Data Port register, the Host Driver shall set this bit after all block data is written. If this bit is set to 1, the Host Driver shall not write data to Buffer Data Port register. This bit affects Read Transfer Active, Write Transfer Active, DAT Line Active and Command Inhibit (DAT) in the Present State register. Regarding detailed control of bits D01 and D00.\nSD_BUS_VOLTAGE_SELECT - SD Bus Voltage Select\nBy setting these bits, the Host Driver selects the voltage level for the SD card. Before setting this register, the Host Driver shall check the Voltage Support bits in the Capabilities register. If an unsupported voltage is selected, the Host System shall not supply SD Bus voltage.\n111b 3.3V (Typ.)\n110b 3.0V (Typ.)\n101b 1.8V (Typ.)\n100b  000b Reserved\nSD_BUS_POWER - SD Bus Power\nBefore setting this bit, the SD Host Driver shall set SD Bus Voltage Select. If the Host Controller detects the No Card state, this bit shall be cleared. If this bit is cleared, the Host Controller shall immediately stop driving CMD and DAT[3:0] (tri-state) and drive SDCLK to low level.\nCARD_DETECT_SIGNAL_DETECT - Card Detect Signal Selection\nThis bit selects source for the card detection. When the source for the card detection is switched, the interrupt should be disabled during the switching period by clearing the Interrupt Status/Signal Enable register in order to mask unexpected interrupt being caused by the glitch. The Interrupt Status/Signal Enable should be disabled during over the period of debouncing.\nCARD_DETECT_TEST_LVL - Card Detect Test Level\nThis bit is enabled while the Card Detect Signal Selection is set to 1 and it indicates card inserted or not.\nEXTENDED_DATA_TRANSFER_WIDTH (VENDOR Bit)\n1:8-bit Mode,DATA_XFER_WIDTH is ignored.\n0:Card Bust is as per DATA_XFER_WIDTH value\nDMA_SELECT - DMA Select\nOne of supported DMA modes can be selected. The host driver shall check support of DMA modes by referring the Capabilities register. Use of selected DMA is determined by DMA Enable of the Transfer Mode register.\n00 SDMA is selected\n01 32-bit Address ADMA1 is selected(VENDOR Definition)\n10 32-bit Address ADMA2 is selected\n11 64-bit Address ADMA2 is selected (VENDOR Definition: 1xh is considered as ADMA2.)\nHIGH_SPEED_EN - High Speed Enable\nThis bit is optional. Before setting this bit, the Host Driver shall check the High Speed Support in the Capabilities register. If this bit is set to 0 (default), the Host Controller outputs CMD line and DAT lines at the falling edge of the SD Clock (up to 25MHz). If this bit is set to 1, the Host Controller outputs CMD line and DAT lines at the rising edge of the SD Clock (up to 50MHz).\nDATA_XFER_WIDTH - Data Transfer Width\nThis bit selects the data width of the Host Controller. The Host Driver shall set it to match the data width of the SD card.\nLED_CONTROL - LED Control\nThis bit is used to caution the user not to remove the card while the SD card is being accessed. If the software is going to issue multiple SD commands, this bit can be set during all these transactions. It is not necessary to change for each transaction.\nPower Control / Host Control Register";
}

#define SW_RESET_TIMEOUT_CTRL_CLOCK_CONTROL_OFFSET 0x2C
#define SW_RESET_TIMEOUT_CTRL_CLOCK_CONTROL_UNDEFMASK 0xF8F000F8
union sw_reset_timeout_ctrl_clock_control_u {
    struct {
        unsigned int internal_clock_en:1;   /* 0 = STOP 1 = OSCILLATE */
        unsigned int internal_clock_stable:1;/* 0 = NOT_READY 1 = READY */
        unsigned int sd_clock_en:1;         /* 0 = DISABLE 1 = ENABLE */
        unsigned int undefined_bits_3_7:5;
        unsigned int sdclk_frequencyselect:8;/* 128 = DIV256 64 = DIV128 32 = DIV64 16 = DIV32 8 = DIV16 4 = DIV8 2 = DIV4 1 = DIV2 0 = BASE */
        unsigned int data_timeout_counter_value:4;
        unsigned int undefined_bits_20_23:4;
        unsigned int sw_reset_for_all:1;    /* 0 = WORK 1 = RESETED */
        unsigned int sw_reset_for_cmd_line:1;/* 0 = WORK 1 = RESETED */
        unsigned int sw_reset_for_dat_line:1;/* 0 = WORK 1 = RESETED */
        unsigned int undefined_bits_27_31:5;
    };

    u_int32_t reg32;
};

void SdhciDev::fill_sw_reset_timeout_ctrl_clock_control_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const sw_reset_timeout_ctrl_clock_control_u old_value_t = { .reg32 = value };
    const sw_reset_timeout_ctrl_clock_control_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: internal_clock_en:1",
              "0 = STOP\n1 = OSCILLATE",
              1, old_value_t.internal_clock_en, new_value_t.internal_clock_en };
    m_bit_details_model.bits.append(entry);
    entry = { "01: internal_clock_stable:1",
              "0 = NOT_READY\n1 = READY",
              1, old_value_t.internal_clock_stable, new_value_t.internal_clock_stable };
    m_bit_details_model.bits.append(entry);
    entry = { "02: sd_clock_en:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.sd_clock_en, new_value_t.sd_clock_en };
    m_bit_details_model.bits.append(entry);
    entry = { "03: undefined_bits_3_7:5", "", 5, old_value_t.undefined_bits_3_7, new_value_t.undefined_bits_3_7 };
    m_bit_details_model.bits.append(entry);
    entry = { "08: sdclk_frequencyselect:8",
              "128 = DIV256\n64 = DIV128\n32 = DIV64\n16 = DIV32\n8 = DIV16\n4 = DIV8\n2 = DIV4\n1 = DIV2\n0 = BASE",
              8, old_value_t.sdclk_frequencyselect, new_value_t.sdclk_frequencyselect };
    m_bit_details_model.bits.append(entry);
    entry = { "16: data_timeout_counter_value:4", "", 4, old_value_t.data_timeout_counter_value, new_value_t.data_timeout_counter_value };
    m_bit_details_model.bits.append(entry);
    entry = { "20: undefined_bits_20_23:4", "", 4, old_value_t.undefined_bits_20_23, new_value_t.undefined_bits_20_23 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: sw_reset_for_all:1",
              "0 = WORK\n1 = RESETED",
              1, old_value_t.sw_reset_for_all, new_value_t.sw_reset_for_all };
    m_bit_details_model.bits.append(entry);
    entry = { "25: sw_reset_for_cmd_line:1",
              "0 = WORK\n1 = RESETED",
              1, old_value_t.sw_reset_for_cmd_line, new_value_t.sw_reset_for_cmd_line };
    m_bit_details_model.bits.append(entry);
    entry = { "26: sw_reset_for_dat_line:1",
              "0 = WORK\n1 = RESETED",
              1, old_value_t.sw_reset_for_dat_line, new_value_t.sw_reset_for_dat_line };
    m_bit_details_model.bits.append(entry);
    entry = { "27: undefined_bits_27_31:5", "", 5, old_value_t.undefined_bits_27_31, new_value_t.undefined_bits_27_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "SW_RESET_FOR_DAT_LINE - Software Reset For DAT Line\nOnly part of data circuit is reset. DMA circuit is also reset. The following registers and bits are cleared by this bit:\n    * Buffer Data Port register\n- Buffer is cleared and initialized.\n    * Present State register\n- Buffer Read Enable\n- Buffer Write Enable\n- Read Transfer Active\n- Write Transfer Active\n- DAT Line Active\n- Command Inhibit (DAT)\n    * Block Gap Control register\n- Continue Request\n- Stop At Block Gap Request\n    * Normal Interrupt Status register\n- Buffer Read Ready\n-  Buffer Write Ready\n- DMA Interrupt\n- Block Gap Event\n- Transfer Complete\nSW_RESET_FOR_CMD_LINE - Software Reset For CMD Line\nOnly part of command circuit is reset. The following registers and bits are cleared by this bit:\n    * Present State register\n- Command Inhibit (CMD)\n    * Normal Interrupt Status register\n- Command Complete\nSW_RESET_FOR_ALL - Software Reset For All\nThis reset affects the entire Host Controller except for the card detection circuit. Register bits of type ROC, RW, RW1C, RWAC are cleared to 0. During its initialization, the Host Driver shall set this bit to 1 to reset the Host Controller. The Host Controller shall reset this bit to 0 when Capabilities registers are valid and the Host Driver can read them. Additional use of Software Reset for All may not affect the value of the Capabilities registers. If this bit is set to 1, the host driver should issue reset command and reinitialize the SD card.\nDATA_TIMEOUT_COUNTER_VALUE - Data Timeout Counter Value\nThis value determines the interval by which DAT line timeouts are detected. For more information about timeout generation, refer to the Data Timeout Error in the Error Interrupt Status register. Timeout clock frequency will be generated by dividing the base clock TMCLK value by this value. When setting this register, prevent inadvertent timeout events by clearing the Data Timeout Error Status Enable (in the Error Interrupt Status Enable register)\n- 1111b Reserved\n- 1110b TMCLK x pow(2,27)\n-  0001b TMCLK x  pow(2,14)\n-  0000b TMCLK x  pow(2,13)\nSDCLK_FREQUENCYSELECT - SDCLK Frequency Select\nThis register is used to select the frequency of SDCLK pin. The frequency is not programmed directly; rather this register holds the divisor of the Base Clock Frequency For SD Clock in the Capabilities register. Only the following settings are allowed.\n- SD_CLOCK_EN - SD Clock Enable\nThe Host Controller shall stop SDCLK when writing this bit to 0. SDCLK Frequency Select can be changed when this bit is 0. Then, the Host Controller shall maintain the same clock frequency until SDCLK is stopped (Stop at SDCLK=0). If the Card Inserted in the Present State register is cleared, this bit shall be cleared.\n- INTERNAL_CLOCK_STABLE - Internal Clock Stable\nThis bit is set to 1 when SD Clock is stable after writing to Internal Clock Enable in this register to 1. The SD Host Driver shall wait to set SD Clock Enable until this bit is set to 1.\nNote:\n This is useful when using PLL for a clock oscillator that requires setup time.\n- INTERNAL_CLOCK_EN - Internal Clock Enable\nThis bit is set to 0 when the Host Driver is not using the Host Controller or the Host Controller awaits a wakeup interrupt. The Host Controller should stop its internal clock to go very low power state. Still, registers shall be able to be read and written. Clock starts to oscillate when this bit is set to 1. When clock oscillation is stable, the Host Controller shall set Internal Clock Stable in this register to 1. This bit shall not affect card detection.\nClock Control Register";
}

#define INTERRUPT_STATUS_OFFSET 0x30
#define INTERRUPT_STATUS_UNDEFMASK 0x04007E00
union interrupt_status_u {
    struct {
        unsigned int cmd_complete:1;        /* 0 = NO_INT 1 = GEN_INT */
        unsigned int xfer_complete:1;       /* 0 = NO_INT 1 = GEN_INT */
        unsigned int block_gap_event:1;     /* 0 = NO_INT 1 = GEN_INT */
        unsigned int dma_interrupt:1;       /* 0 = NO_INT 1 = GEN_INT */
        unsigned int buffer_write_ready:1;  /* 0 = NO_INT 1 = GEN_INT */
        unsigned int buffer_read_ready:1;   /* 0 = NO_INT 1 = GEN_INT */
        unsigned int card_insertion:1;      /* 0 = NO_INT 1 = GEN_INT */
        unsigned int card_removal:1;        /* 0 = NO_INT 1 = GEN_INT */
        unsigned int card_interrupt:1;      /* 0 = NO_INT 1 = GEN_INT */
        unsigned int undefined_bits_9_14:6;
        unsigned int err_interrupt:1;       /* 0 = NO_ERR 1 = ERR */
        unsigned int command_timeout_err:1; /* 0 = NO_ERR 1 = TIMEOUT */
        unsigned int command_crc_err:1;     /* 0 = NO_ERR 1 = CRC_ERR_GENERATED */
        unsigned int command_end_bit_err:1; /* 0 = NO_ERR 1 = END_BIT_ERR_GENERATED */
        unsigned int command_index_err:1;   /* 0 = NO_ERR 1 = ERR */
        unsigned int data_timeout_err:1;    /* 0 = NO_ERR 1 = TIMEOUT */
        unsigned int data_crc_err:1;        /* 0 = NO_ERR 1 = ERR */
        unsigned int data_end_bit_err:1;    /* 0 = NO_ERR 1 = ERR */
        unsigned int current_limit_err:1;   /* 0 = NO_ERR 1 = POWER_FAIL */
        unsigned int auto_cmd12_err:1;      /* 0 = NO_ERR 1 = ERR */
        unsigned int adma_err:1;            /* 0 = NO_ERR 1 = ERR */
        unsigned int undefined_bit_26:1;
        unsigned int spi_err:1;             /* 0 = NO_ERR 1 = ERR */
        unsigned int target_resp_error:1;   /* 0 = NO_ERROR 1 = ERROR */
        unsigned int ceata_error:1;         /* 0 = NO_ERROR 1 = ERROR */
        unsigned int vend_spec_err:2;       /* 0 = DISABLE 3 = ENABLE */
    };

    u_int32_t reg32;
};

void SdhciDev::fill_interrupt_status_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const interrupt_status_u old_value_t = { .reg32 = value };
    const interrupt_status_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: cmd_complete:1",
              "0 = NO_INT\n1 = GEN_INT",
              1, old_value_t.cmd_complete, new_value_t.cmd_complete };
    m_bit_details_model.bits.append(entry);
    entry = { "01: xfer_complete:1",
              "0 = NO_INT\n1 = GEN_INT",
              1, old_value_t.xfer_complete, new_value_t.xfer_complete };
    m_bit_details_model.bits.append(entry);
    entry = { "02: block_gap_event:1",
              "0 = NO_INT\n1 = GEN_INT",
              1, old_value_t.block_gap_event, new_value_t.block_gap_event };
    m_bit_details_model.bits.append(entry);
    entry = { "03: dma_interrupt:1",
              "0 = NO_INT\n1 = GEN_INT",
              1, old_value_t.dma_interrupt, new_value_t.dma_interrupt };
    m_bit_details_model.bits.append(entry);
    entry = { "04: buffer_write_ready:1",
              "0 = NO_INT\n1 = GEN_INT",
              1, old_value_t.buffer_write_ready, new_value_t.buffer_write_ready };
    m_bit_details_model.bits.append(entry);
    entry = { "05: buffer_read_ready:1",
              "0 = NO_INT\n1 = GEN_INT",
              1, old_value_t.buffer_read_ready, new_value_t.buffer_read_ready };
    m_bit_details_model.bits.append(entry);
    entry = { "06: card_insertion:1",
              "0 = NO_INT\n1 = GEN_INT",
              1, old_value_t.card_insertion, new_value_t.card_insertion };
    m_bit_details_model.bits.append(entry);
    entry = { "07: card_removal:1",
              "0 = NO_INT\n1 = GEN_INT",
              1, old_value_t.card_removal, new_value_t.card_removal };
    m_bit_details_model.bits.append(entry);
    entry = { "08: card_interrupt:1",
              "0 = NO_INT\n1 = GEN_INT",
              1, old_value_t.card_interrupt, new_value_t.card_interrupt };
    m_bit_details_model.bits.append(entry);
    entry = { "09: undefined_bits_9_14:6", "", 6, old_value_t.undefined_bits_9_14, new_value_t.undefined_bits_9_14 };
    m_bit_details_model.bits.append(entry);
    entry = { "15: err_interrupt:1",
              "0 = NO_ERR\n1 = ERR",
              1, old_value_t.err_interrupt, new_value_t.err_interrupt };
    m_bit_details_model.bits.append(entry);
    entry = { "16: command_timeout_err:1",
              "0 = NO_ERR\n1 = TIMEOUT",
              1, old_value_t.command_timeout_err, new_value_t.command_timeout_err };
    m_bit_details_model.bits.append(entry);
    entry = { "17: command_crc_err:1",
              "0 = NO_ERR\n1 = CRC_ERR_GENERATED",
              1, old_value_t.command_crc_err, new_value_t.command_crc_err };
    m_bit_details_model.bits.append(entry);
    entry = { "18: command_end_bit_err:1",
              "0 = NO_ERR\n1 = END_BIT_ERR_GENERATED",
              1, old_value_t.command_end_bit_err, new_value_t.command_end_bit_err };
    m_bit_details_model.bits.append(entry);
    entry = { "19: command_index_err:1",
              "0 = NO_ERR\n1 = ERR",
              1, old_value_t.command_index_err, new_value_t.command_index_err };
    m_bit_details_model.bits.append(entry);
    entry = { "20: data_timeout_err:1",
              "0 = NO_ERR\n1 = TIMEOUT",
              1, old_value_t.data_timeout_err, new_value_t.data_timeout_err };
    m_bit_details_model.bits.append(entry);
    entry = { "21: data_crc_err:1",
              "0 = NO_ERR\n1 = ERR",
              1, old_value_t.data_crc_err, new_value_t.data_crc_err };
    m_bit_details_model.bits.append(entry);
    entry = { "22: data_end_bit_err:1",
              "0 = NO_ERR\n1 = ERR",
              1, old_value_t.data_end_bit_err, new_value_t.data_end_bit_err };
    m_bit_details_model.bits.append(entry);
    entry = { "23: current_limit_err:1",
              "0 = NO_ERR\n1 = POWER_FAIL",
              1, old_value_t.current_limit_err, new_value_t.current_limit_err };
    m_bit_details_model.bits.append(entry);
    entry = { "24: auto_cmd12_err:1",
              "0 = NO_ERR\n1 = ERR",
              1, old_value_t.auto_cmd12_err, new_value_t.auto_cmd12_err };
    m_bit_details_model.bits.append(entry);
    entry = { "25: adma_err:1",
              "0 = NO_ERR\n1 = ERR",
              1, old_value_t.adma_err, new_value_t.adma_err };
    m_bit_details_model.bits.append(entry);
    entry = { "26: undefined_bit_26:1", "", 1, old_value_t.undefined_bit_26, new_value_t.undefined_bit_26 };
    m_bit_details_model.bits.append(entry);
    entry = { "27: spi_err:1",
              "0 = NO_ERR\n1 = ERR",
              1, old_value_t.spi_err, new_value_t.spi_err };
    m_bit_details_model.bits.append(entry);
    entry = { "28: target_resp_error:1",
              "0 = NO_ERROR\n1 = ERROR",
              1, old_value_t.target_resp_error, new_value_t.target_resp_error };
    m_bit_details_model.bits.append(entry);
    entry = { "29: ceata_error:1",
              "0 = NO_ERROR\n1 = ERROR",
              1, old_value_t.ceata_error, new_value_t.ceata_error };
    m_bit_details_model.bits.append(entry);
    entry = { "30: vend_spec_err:2",
              "0 = DISABLE\n3 = ENABLE",
              2, old_value_t.vend_spec_err, new_value_t.vend_spec_err };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "VEND_SPEC_ERR[1:0]\n1:BOOT_ACK_ERR - Occurs When Boot Ack Status is not equal to '010'\n0:BOOT_ACK_TIMEOUT_ERR - Occurs When Boot Ack is not received within the programmed number of cycles.\nCEATA_ERROR\nOccurs when the ATA command termination has occurred.\nTARGET_RESP_ERROR - Not supported for Tegra 2 Processor\nSPI_ERR\nIndicate when SPI Error has occurred. The SPI Errors are registered in SPI_INTERRUPT_STATUS register.\nADMA_ERR\nOccurs when detecting that one of the bits in Auto CMD12 Error Status register has changed from 0 to 1. This bit is set to 1,not only when the errors in Auto CMD12 occur but also when Auto CMD12 is not executed due to the previous command error.\nAUTO_CMD12_ERR\nOccurs when detecting that one of the bits in Auto CMD12 Error Status register has changed from 0 to 1. This bit is set to 1,not only when the errors in Auto CMD12 occur but also when Auto CMD12 is not executed due to the previous command error.\nCURRENT_LIMIT_ERR\nBy setting the SD Bus Power bit in the Power Control register, the Host Controller is requested to supply power for the SD Bus. If the Host Controller supports the Current Limit function, it can be protected from an illegal card by stopping power supply to the card in which case this bit indicates a failure status. Reading 1 means the Host Controller is not supplying power to SD card due to some failure. Reading 0 means that the Host Controller is supplying power and no error has occurred.\nThe Host Controller may require some sampling time to detect the current limit. If the Host Controller does not support this function, this bit shall always be set to 0.\nDATA_END_BIT_ERR\nOccurs either when detecting 0 at the end bit position of read data which uses the DAT line or at the end bit position of the CRC Status.\nDATA_CRC_ERR\nOccurs when detecting CRC error when transferring read data which uses the DAT line or when detecting the Write CRC status having a value of other than \"010\".\nDATA_TIMEOUT_ERR\nOccurs when detecting one of following timeout conditions.\n- Busy timeout for R1b,R5b type\n- Busy timeout after Write CRC status\n- Write CRC Status timeout\n- Read Data timeout.\nCOMMAND_INDEX_ERR\nOccurs if a Command Index error occurs in the command response.\nCOMMAND_END_BIT_ERR\nOccurs when detecting that the end bit of a command response is 0.\nCOMMAND_CRC_ERR\nCommand CRC Error is generated in two cases.\n- If a response is returned and the Command Timeout Error is set to 0 (indicating no timeout), this bit is set to 1 when detecting a CRC error in the command response.\n- The Host Controller detects a CMD line conflict by monitoring the CMD line when a command is issued. If the Host Controller drives the CMD line to 1 level, but detects 0 level on the CMD line at the next SDCLK edge, then the Host Controller shall abort the command (Stop driving CMD line) and set this bit to 1. The Command Timeout Error shall also be set to 1 to distinguish CMD line conflict\nCOMMAND_TIMEOUT_ERR\nOccurs only if no response is returned within 64 SDCLK cycles from the end bit of the command. If the Host Controller detects a CMD line conflict, in which case Command CRC Error shall also be set as shown in Table 2-25, this bit shall be set without waiting for 64 SDCLK cycles because the command will be aborted by the Host Controller.\nERR_INTERRUPT\nIf any of the bits in the Error Interrupt Status register are set, then this bit is set. Therefore the Host Driver can efficiently test for an error by checking this bit first. This bit is read only.\nCARD_INTERRUPT\nWriting this bit to 1 does not clear this bit. It is cleared by resetting the SD card interrupt factor. In 1-bit mode, the Host Controller shall detect the Card Interrupt without SD Clock to support wakeup. In 4-bit mode, the card interrupt signal is sampled during the interrupt cycle, so there are some sample delays between the interrupt signal from the SD card and the interrupt to the Host System. It is necessary to define how to handle this delay.\nCARD_REMOVAL\nThis status is set if the Card Inserted in the Present State register changes from 1 to 0. When the Host Driver writes this bit to 1 to clear this status, the status of the Card Inserted in the Present State register should be confirmed. Because the card detect state may possibly be changed when the Host Driver clear this bit and interrupt event may not be generated.\nCARD_INSERTION\nThis status is set if the Card Inserted in the Present State register changes from 0 to 1. When the Host Driver writes this bit to 1 to clear this status, the status of the Card Inserted in the Present State register should be confirmed. Because the card detect state may possibly be changed when the Host Driver clear this bit and interrupt event may not be generated.\nBUFFER_READ_READY\nThis status is set if the Buffer Read Enable changes from 0 to 1. Refer to the Buffer Read Enable in the Present State register.\nBUFFER_WRITE_READY\nThis status is set if the Buffer Write Enable changes from 0 to 1. Refer to the Buffer Write Enable in the Present State register.\nDMA_INTERRUPT\nThis status is set if the Host Controller detects the Host DMA Buffer boundary during transfer. Refer to the Host DMA Buffer Boundary in the Block Size register. Other DMA interrupt factors may be added in the future. This interrupt shall not be generated after the Transfer Complete.\nBLOCK_GAP_EVENT\nIf the Stop At Block Gap Request in the Block Gap Control register is set, this bit is set when both a read / write transaction is stopped at a block gap. If Stop At Block Gap Request is not set to 1, this bit is not set to 1.\nXFER_COMPLETE\nThis bit is set when a read / write transfer is completed.\n- In the case of a Read Transaction\n- In the case of a Write Transaction\nCMD_COMPLETE\nThis bit is set when get the end bit of the command response. (Except Auto CMD12) Refer to Command Inhibit (CMD) in the Present State register.\nNormal Interrupt Status Register";
}

#define INTERRUPT_STATUS_ENABLE_OFFSET 0x34
#define INTERRUPT_STATUS_ENABLE_UNDEFMASK 0x0400FE00
union interrupt_status_enable_u {
    struct {
        unsigned int command_complete:1;    /* 0 = DISABLE 1 = ENABLE */
        unsigned int transfer_complete:1;   /* 0 = DISABLE 1 = ENABLE */
        unsigned int block_gap_event:1;     /* 0 = DISABLE 1 = ENABLE */
        unsigned int dma_interrupt:1;       /* 0 = DISABLE 1 = ENABLE */
        unsigned int buffer_write_ready:1;  /* 0 = DISABLE; 1 = ENABLE */
        unsigned int buffer_read_ready:1;   /* 0 = DISABLE 1 = ENABLE */
        unsigned int card_insertion:1;      /* 0 = DISABLE 1 = ENABLE */
        unsigned int card_removal:1;        /* 0 = DISABLE 1 = ENABLE */
        unsigned int card_interrupt:1;      /* 0 = DISABLE 1 = ENABLE */
        unsigned int undefined_bits_9_15:7;
        unsigned int command_timeout_err:1; /* 0 = DISABLE 1 = ENABLE */
        unsigned int command_crc_err:1;     /* 0 = DISABLE 1 = ENABLE */
        unsigned int command_end_bit_err:1; /* 0 = DISABLE 1 = ENABLE */
        unsigned int command_index_err:1;   /* 0 = DISABLE 1 = ENABLE */
        unsigned int data_timeout_err:1;    /* 0 = DISABLE 1 = ENABLE */
        unsigned int data_crc_err:1;        /* 0 = DISABLE 1 = ENABLE */
        unsigned int data_end_bit_err:1;    /* 0 = DISABLE 1 = ENABLE */
        unsigned int current_limit_err:1;   /* 0 = DISABLE 1 = ENABLE */
        unsigned int auto_cmd12_err:1;      /* 0 = DISABLE 1 = ENABLE */
        unsigned int adma_err:1;            /* 0 = DISABLE 1 = ENABLE */
        unsigned int undefined_bit_26:1;
        unsigned int spi_err:1;             /* 0 = DISABLE 1 = ENABLE */
        unsigned int target_resp_error:1;   /* 0 = NO_ERROR 1 = ERROR */
        unsigned int ceata_error:1;         /* 0 = NO_ERROR 1 = ERROR */
        unsigned int vendor_specific_err:2; /* 0 = DISABLE; 3 = ENABLE */
    };

    u_int32_t reg32;
};

void SdhciDev::fill_interrupt_status_enable_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const interrupt_status_enable_u old_value_t = { .reg32 = value };
    const interrupt_status_enable_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: command_complete:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.command_complete, new_value_t.command_complete };
    m_bit_details_model.bits.append(entry);
    entry = { "01: transfer_complete:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.transfer_complete, new_value_t.transfer_complete };
    m_bit_details_model.bits.append(entry);
    entry = { "02: block_gap_event:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.block_gap_event, new_value_t.block_gap_event };
    m_bit_details_model.bits.append(entry);
    entry = { "03: dma_interrupt:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.dma_interrupt, new_value_t.dma_interrupt };
    m_bit_details_model.bits.append(entry);
    entry = { "04: buffer_write_ready:1",
              "0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.buffer_write_ready, new_value_t.buffer_write_ready };
    m_bit_details_model.bits.append(entry);
    entry = { "05: buffer_read_ready:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.buffer_read_ready, new_value_t.buffer_read_ready };
    m_bit_details_model.bits.append(entry);
    entry = { "06: card_insertion:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.card_insertion, new_value_t.card_insertion };
    m_bit_details_model.bits.append(entry);
    entry = { "07: card_removal:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.card_removal, new_value_t.card_removal };
    m_bit_details_model.bits.append(entry);
    entry = { "08: card_interrupt:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.card_interrupt, new_value_t.card_interrupt };
    m_bit_details_model.bits.append(entry);
    entry = { "09: undefined_bits_9_15:7", "", 7, old_value_t.undefined_bits_9_15, new_value_t.undefined_bits_9_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: command_timeout_err:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.command_timeout_err, new_value_t.command_timeout_err };
    m_bit_details_model.bits.append(entry);
    entry = { "17: command_crc_err:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.command_crc_err, new_value_t.command_crc_err };
    m_bit_details_model.bits.append(entry);
    entry = { "18: command_end_bit_err:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.command_end_bit_err, new_value_t.command_end_bit_err };
    m_bit_details_model.bits.append(entry);
    entry = { "19: command_index_err:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.command_index_err, new_value_t.command_index_err };
    m_bit_details_model.bits.append(entry);
    entry = { "20: data_timeout_err:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.data_timeout_err, new_value_t.data_timeout_err };
    m_bit_details_model.bits.append(entry);
    entry = { "21: data_crc_err:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.data_crc_err, new_value_t.data_crc_err };
    m_bit_details_model.bits.append(entry);
    entry = { "22: data_end_bit_err:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.data_end_bit_err, new_value_t.data_end_bit_err };
    m_bit_details_model.bits.append(entry);
    entry = { "23: current_limit_err:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.current_limit_err, new_value_t.current_limit_err };
    m_bit_details_model.bits.append(entry);
    entry = { "24: auto_cmd12_err:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.auto_cmd12_err, new_value_t.auto_cmd12_err };
    m_bit_details_model.bits.append(entry);
    entry = { "25: adma_err:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.adma_err, new_value_t.adma_err };
    m_bit_details_model.bits.append(entry);
    entry = { "26: undefined_bit_26:1", "", 1, old_value_t.undefined_bit_26, new_value_t.undefined_bit_26 };
    m_bit_details_model.bits.append(entry);
    entry = { "27: spi_err:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.spi_err, new_value_t.spi_err };
    m_bit_details_model.bits.append(entry);
    entry = { "28: target_resp_error:1",
              "0 = NO_ERROR\n1 = ERROR",
              1, old_value_t.target_resp_error, new_value_t.target_resp_error };
    m_bit_details_model.bits.append(entry);
    entry = { "29: ceata_error:1",
              "0 = NO_ERROR\n1 = ERROR",
              1, old_value_t.ceata_error, new_value_t.ceata_error };
    m_bit_details_model.bits.append(entry);
    entry = { "30: vendor_specific_err:2",
              "0 = DISABLE;\n3 = ENABLE",
              2, old_value_t.vendor_specific_err, new_value_t.vendor_specific_err };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "This register is used to select which interrupt status is indicated to the Host System as the interrupt. These status bits all share the same1 bit interrupt line. Setting any of these bits to 1 enables interrupt generation.\nNormal Interrupt Status Enable Register";
}

#define INTERRUPT_SIGNAL_ENABLE_OFFSET 0x38
#define INTERRUPT_SIGNAL_ENABLE_UNDEFMASK 0x0400FE00
union interrupt_signal_enable_u {
    struct {
        unsigned int command_complete:1;    /* 0 = DISABLE 1 = ENABLE */
        unsigned int transfer_complete:1;   /* 0 = DISABLE 1 = ENABLE */
        unsigned int block_gap_event:1;     /* 0 = DISABLE 1 = ENABLE */
        unsigned int dma_interrupt:1;       /* 0 = DISABLE 1 = ENABLE */
        unsigned int buffer_write_ready:1;  /* 0 = DISABLE 1 = ENABLE */
        unsigned int buffer_read_ready:1;   /* 0 = DISABLE 1 = ENABLE */
        unsigned int card_insertion:1;      /* 0 = DISABLE 1 = ENABLE */
        unsigned int card_removal:1;        /* 0 = DISABLE 1 = ENABLE */
        unsigned int card_interrupt:1;      /* 0 = DISABLE 1 = ENABLE */
        unsigned int undefined_bits_9_15:7;
        unsigned int command_timeout_err:1; /* 0 = DISABLE 1 = ENABLE */
        unsigned int command_crc_err:1;     /* 0 = DISABLE 1 = ENABLE */
        unsigned int command_end_bit_err:1; /* 0 = DISABLE 1 = ENABLE */
        unsigned int command_index_err:1;   /* 0 = DISABLE 1 = ENABLE */
        unsigned int data_timeout_err:1;    /* 0 = DISABLE 1 = ENABLE */
        unsigned int data_crc_err:1;        /* 0 = DISABLE 1 = ENABLE */
        unsigned int data_end_bit_err:1;    /* 0 = DISABLE 1 = ENABLE */
        unsigned int current_limit_err:1;   /* 0 = DISABLE 1 = ENABLE */
        unsigned int auto_cmd12_err:1;      /* 0 = DISABLE 1 = ENABLE */
        unsigned int adma_err:1;            /* 0 = DISABLE 1 = ENABLE */
        unsigned int undefined_bit_26:1;
        unsigned int spi_err:1;             /* 0 = DISABLE 1 = ENABLE */
        unsigned int target_resp_error:1;   /* 0 = NO_ERROR 1 = ERROR */
        unsigned int ceata_error:1;         /* 0 = NO_ERROR 1 = ERROR */
        unsigned int vendor_specific_err:2; /* 0 = DISABLE 3 = ENABLE */
    };

    u_int32_t reg32;
};

void SdhciDev::fill_interrupt_signal_enable_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const interrupt_signal_enable_u old_value_t = { .reg32 = value };
    const interrupt_signal_enable_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: command_complete:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.command_complete, new_value_t.command_complete };
    m_bit_details_model.bits.append(entry);
    entry = { "01: transfer_complete:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.transfer_complete, new_value_t.transfer_complete };
    m_bit_details_model.bits.append(entry);
    entry = { "02: block_gap_event:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.block_gap_event, new_value_t.block_gap_event };
    m_bit_details_model.bits.append(entry);
    entry = { "03: dma_interrupt:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.dma_interrupt, new_value_t.dma_interrupt };
    m_bit_details_model.bits.append(entry);
    entry = { "04: buffer_write_ready:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.buffer_write_ready, new_value_t.buffer_write_ready };
    m_bit_details_model.bits.append(entry);
    entry = { "05: buffer_read_ready:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.buffer_read_ready, new_value_t.buffer_read_ready };
    m_bit_details_model.bits.append(entry);
    entry = { "06: card_insertion:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.card_insertion, new_value_t.card_insertion };
    m_bit_details_model.bits.append(entry);
    entry = { "07: card_removal:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.card_removal, new_value_t.card_removal };
    m_bit_details_model.bits.append(entry);
    entry = { "08: card_interrupt:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.card_interrupt, new_value_t.card_interrupt };
    m_bit_details_model.bits.append(entry);
    entry = { "09: undefined_bits_9_15:7", "", 7, old_value_t.undefined_bits_9_15, new_value_t.undefined_bits_9_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: command_timeout_err:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.command_timeout_err, new_value_t.command_timeout_err };
    m_bit_details_model.bits.append(entry);
    entry = { "17: command_crc_err:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.command_crc_err, new_value_t.command_crc_err };
    m_bit_details_model.bits.append(entry);
    entry = { "18: command_end_bit_err:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.command_end_bit_err, new_value_t.command_end_bit_err };
    m_bit_details_model.bits.append(entry);
    entry = { "19: command_index_err:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.command_index_err, new_value_t.command_index_err };
    m_bit_details_model.bits.append(entry);
    entry = { "20: data_timeout_err:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.data_timeout_err, new_value_t.data_timeout_err };
    m_bit_details_model.bits.append(entry);
    entry = { "21: data_crc_err:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.data_crc_err, new_value_t.data_crc_err };
    m_bit_details_model.bits.append(entry);
    entry = { "22: data_end_bit_err:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.data_end_bit_err, new_value_t.data_end_bit_err };
    m_bit_details_model.bits.append(entry);
    entry = { "23: current_limit_err:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.current_limit_err, new_value_t.current_limit_err };
    m_bit_details_model.bits.append(entry);
    entry = { "24: auto_cmd12_err:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.auto_cmd12_err, new_value_t.auto_cmd12_err };
    m_bit_details_model.bits.append(entry);
    entry = { "25: adma_err:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.adma_err, new_value_t.adma_err };
    m_bit_details_model.bits.append(entry);
    entry = { "26: undefined_bit_26:1", "", 1, old_value_t.undefined_bit_26, new_value_t.undefined_bit_26 };
    m_bit_details_model.bits.append(entry);
    entry = { "27: spi_err:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.spi_err, new_value_t.spi_err };
    m_bit_details_model.bits.append(entry);
    entry = { "28: target_resp_error:1",
              "0 = NO_ERROR\n1 = ERROR",
              1, old_value_t.target_resp_error, new_value_t.target_resp_error };
    m_bit_details_model.bits.append(entry);
    entry = { "29: ceata_error:1",
              "0 = NO_ERROR\n1 = ERROR",
              1, old_value_t.ceata_error, new_value_t.ceata_error };
    m_bit_details_model.bits.append(entry);
    entry = { "30: vendor_specific_err:2",
              "0 = DISABLE\n3 = ENABLE",
              2, old_value_t.vendor_specific_err, new_value_t.vendor_specific_err };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "This register is used to select which interrupt status is notified to the Host System as the interrupt. These status bits all share the same 1 bit interrupt line. Setting any of these bits to 1 enables interrupt generation.\nNormal Interrupt Signal Enable Register";
}

#define AUTO_CMD12_ERR_STATUS_OFFSET 0x3C
#define AUTO_CMD12_ERR_STATUS_UNDEFMASK 0xFFFFFF60
union auto_cmd12_err_status_u {
    struct {
        unsigned int not_executed:1;        /* 0 = EXECUTED 1 = NOT_EXECUTED */
        unsigned int timeout_err:1;         /* 0 = NO_ERR 1 = TIMEOUT */
        unsigned int crc_err:1;             /* 0 = NO_ERR 1 = CRC_ERR_GENERATED */
        unsigned int end_bit_err:1;         /* 0 = NO_ERR 1 = END_BIT_ERR_GENERATED */
        unsigned int index_err:1;           /* 0 = NO_ERR 1 = ERR */
        unsigned int undefined_bits_5_6:2;
        unsigned int command_not_issued:1;  /* 0 = NO_ERR 1 = NOT_ISSUED */
        unsigned int undefined_bits_8_31:24;
    };

    u_int32_t reg32;
};

void SdhciDev::fill_auto_cmd12_err_status_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const auto_cmd12_err_status_u old_value_t = { .reg32 = value };
    const auto_cmd12_err_status_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: not_executed:1",
              "0 = EXECUTED\n1 = NOT_EXECUTED",
              1, old_value_t.not_executed, new_value_t.not_executed };
    m_bit_details_model.bits.append(entry);
    entry = { "01: timeout_err:1",
              "0 = NO_ERR\n1 = TIMEOUT",
              1, old_value_t.timeout_err, new_value_t.timeout_err };
    m_bit_details_model.bits.append(entry);
    entry = { "02: crc_err:1",
              "0 = NO_ERR\n1 = CRC_ERR_GENERATED",
              1, old_value_t.crc_err, new_value_t.crc_err };
    m_bit_details_model.bits.append(entry);
    entry = { "03: end_bit_err:1",
              "0 = NO_ERR\n1 = END_BIT_ERR_GENERATED",
              1, old_value_t.end_bit_err, new_value_t.end_bit_err };
    m_bit_details_model.bits.append(entry);
    entry = { "04: index_err:1",
              "0 = NO_ERR\n1 = ERR",
              1, old_value_t.index_err, new_value_t.index_err };
    m_bit_details_model.bits.append(entry);
    entry = { "05: undefined_bits_5_6:2", "", 2, old_value_t.undefined_bits_5_6, new_value_t.undefined_bits_5_6 };
    m_bit_details_model.bits.append(entry);
    entry = { "07: command_not_issued:1",
              "0 = NO_ERR\n1 = NOT_ISSUED",
              1, old_value_t.command_not_issued, new_value_t.command_not_issued };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_31:24", "", 24, old_value_t.undefined_bits_8_31, new_value_t.undefined_bits_8_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "COMMAND_NOT_ISSUED - Command Not Issued By Auto CMD12 Error\nSetting this bit to 1 means CMD_wo_DAT is not executed due to an Auto CMD12 Error (D04-D01) in this register.\nINDEX_ERR - Auto CMD12 Index Error\nThis bit is set if the Command Index error occurs in response to a command.\nEND_BIT_ERR - Auto CMD12 End Bit Error\nThis bit is set when detecting that the end bit of command response is 0.\nCRC_ERR - Auto CMD12 CRC Error\nThis bit is set when detecting a CRC error in the command response.\nTIMEOUT_ERR - Auto CMD12 Timeout Error\nThis bit is set if no response is returned within 64 SDCLK cycles from the end bit of command. If this bit is set to1, the other error status bits (D04-D02) are meaningless.\nNOT_EXECUTED - Auto CMD12 Not Executed\nIf memory multiple block data transfer is not started due to command error, this bit is not set because it is not necessary to issue Auto CMD12. Setting this bit to 1 means the Host Controller cannot issue Auto CMD12 to stop memory multiple block data transfer due to some error. If this bit is set to 1, other error status bits (D04-D01) are meaningless.\nThe relation between Auto CMD12 CRC Error and Auto CMD12 Timeout Error is shown below\nAuto CMD12 CRC Error\n Auto CMD12 Timeout Error\n Kinds of error\n0\n 0\n No Error\n0\n 1\n Response Timeout Error\n1\n 0\n Response CRC Error\n1\n 1\n CMD line conflict\nAuto CMD12 Error Status Register";
}

#define CAPABILITIES_OFFSET 0x40
#define CAPABILITIES_UNDEFMASK 0x8000C040
union capabilities_u {
    struct {
        unsigned int timeout_clock_frequency:6;
        unsigned int undefined_bit_6:1;
        unsigned int timeout_clock_unit:1;  /* 0 = KHZ 1 = MHZ */
        unsigned int base_clock_frequency:6;
        unsigned int undefined_bits_14_15:2;
        unsigned int max_block_length:2;    /* 0 = BYTE512; 1 = BYTE1024 2 = BYTE2048 3 = RESERVED */
        unsigned int extended_media_bus_support:1;/* 0 = NOT_SUPPORTED 1 = SUPPORTED */
        unsigned int adma2_support:1;       /* 0 = NOT_SUPPORTED 1 = SUPPORTED */
        unsigned int adma1_support:1;       /* 0 = NOT_SUPPORTED 1 = SUPPORTED */
        unsigned int high_speed_support:1;  /* 0 = NOT_SUPPORTED 1 = SUPPORTED */
        unsigned int dma_support:1;         /* 0 = NOT_SUPPORTED 1 = SUPPORTED */
        unsigned int suspend_resume_support:1;/* 0 = NOT_SUPPORTED 1 = SUPPORTED */
        unsigned int voltage_support_3_3_v:1;/* 0 = NOT_SUPPORTED 1 = SUPPORTED */
        unsigned int voltage_support_3_0_v:1;/* 0 = NOT_SUPPORTED 1 = SUPPORTED */
        unsigned int voltage_support_1_8_v:1;/* 0 = NOT_SUPPORTED 1 = SUPPORTED */
        unsigned int interrupt_mode:1;      /* 0 = NOT_SUPPORTED 1 = SUPPORTED */
        unsigned int system_bus_64bit_support:1;/* 0 = NOT_SUPPORTED 1 = SUPPORTED */
        unsigned int spi_mode:1;            /* 0 = NOT_SUPPORTED 1 = SUPPORTED */
        unsigned int spi_block_mode:1;      /* 0 = NOT_SUPPORTED 1 = SUPPORTED */
        unsigned int undefined_bit_31:1;
    };

    u_int32_t reg32;
};

void SdhciDev::fill_capabilities_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const capabilities_u old_value_t = { .reg32 = value };
    const capabilities_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: timeout_clock_frequency:6", "", 6, old_value_t.timeout_clock_frequency, new_value_t.timeout_clock_frequency };
    m_bit_details_model.bits.append(entry);
    entry = { "06: undefined_bit_6:1", "", 1, old_value_t.undefined_bit_6, new_value_t.undefined_bit_6 };
    m_bit_details_model.bits.append(entry);
    entry = { "07: timeout_clock_unit:1",
              "0 = KHZ\n1 = MHZ",
              1, old_value_t.timeout_clock_unit, new_value_t.timeout_clock_unit };
    m_bit_details_model.bits.append(entry);
    entry = { "08: base_clock_frequency:6", "", 6, old_value_t.base_clock_frequency, new_value_t.base_clock_frequency };
    m_bit_details_model.bits.append(entry);
    entry = { "14: undefined_bits_14_15:2", "", 2, old_value_t.undefined_bits_14_15, new_value_t.undefined_bits_14_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: max_block_length:2",
              "0 = BYTE512;\n1 = BYTE1024\n2 = BYTE2048\n3 = RESERVED",
              2, old_value_t.max_block_length, new_value_t.max_block_length };
    m_bit_details_model.bits.append(entry);
    entry = { "18: extended_media_bus_support:1",
              "0 = NOT_SUPPORTED\n1 = SUPPORTED",
              1, old_value_t.extended_media_bus_support, new_value_t.extended_media_bus_support };
    m_bit_details_model.bits.append(entry);
    entry = { "19: adma2_support:1",
              "0 = NOT_SUPPORTED\n1 = SUPPORTED",
              1, old_value_t.adma2_support, new_value_t.adma2_support };
    m_bit_details_model.bits.append(entry);
    entry = { "20: adma1_support:1",
              "0 = NOT_SUPPORTED\n1 = SUPPORTED",
              1, old_value_t.adma1_support, new_value_t.adma1_support };
    m_bit_details_model.bits.append(entry);
    entry = { "21: high_speed_support:1",
              "0 = NOT_SUPPORTED\n1 = SUPPORTED",
              1, old_value_t.high_speed_support, new_value_t.high_speed_support };
    m_bit_details_model.bits.append(entry);
    entry = { "22: dma_support:1",
              "0 = NOT_SUPPORTED\n1 = SUPPORTED",
              1, old_value_t.dma_support, new_value_t.dma_support };
    m_bit_details_model.bits.append(entry);
    entry = { "23: suspend_resume_support:1",
              "0 = NOT_SUPPORTED\n1 = SUPPORTED",
              1, old_value_t.suspend_resume_support, new_value_t.suspend_resume_support };
    m_bit_details_model.bits.append(entry);
    entry = { "24: voltage_support_3_3_v:1",
              "0 = NOT_SUPPORTED\n1 = SUPPORTED",
              1, old_value_t.voltage_support_3_3_v, new_value_t.voltage_support_3_3_v };
    m_bit_details_model.bits.append(entry);
    entry = { "25: voltage_support_3_0_v:1",
              "0 = NOT_SUPPORTED\n1 = SUPPORTED",
              1, old_value_t.voltage_support_3_0_v, new_value_t.voltage_support_3_0_v };
    m_bit_details_model.bits.append(entry);
    entry = { "26: voltage_support_1_8_v:1",
              "0 = NOT_SUPPORTED\n1 = SUPPORTED",
              1, old_value_t.voltage_support_1_8_v, new_value_t.voltage_support_1_8_v };
    m_bit_details_model.bits.append(entry);
    entry = { "27: interrupt_mode:1",
              "0 = NOT_SUPPORTED\n1 = SUPPORTED",
              1, old_value_t.interrupt_mode, new_value_t.interrupt_mode };
    m_bit_details_model.bits.append(entry);
    entry = { "28: system_bus_64bit_support:1",
              "0 = NOT_SUPPORTED\n1 = SUPPORTED",
              1, old_value_t.system_bus_64bit_support, new_value_t.system_bus_64bit_support };
    m_bit_details_model.bits.append(entry);
    entry = { "29: spi_mode:1",
              "0 = NOT_SUPPORTED\n1 = SUPPORTED",
              1, old_value_t.spi_mode, new_value_t.spi_mode };
    m_bit_details_model.bits.append(entry);
    entry = { "30: spi_block_mode:1",
              "0 = NOT_SUPPORTED\n1 = SUPPORTED",
              1, old_value_t.spi_block_mode, new_value_t.spi_block_mode };
    m_bit_details_model.bits.append(entry);
    entry = { "31: undefined_bit_31:1", "", 1, old_value_t.undefined_bit_31, new_value_t.undefined_bit_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "SPI_BLOCK_MODE\nSetting 1 indicates spi block mode is supported\nSPI_MODE\nSetting 1 indicates spi mode is supported\nSYSTEM_BUS_64BIT_SUPPORT - 64-bit System Bus Support\nSetting 1 to this bit indicates that the Host Controller supports 64-bit address descriptor mode and is connected to 64-bit address system bus.\nINTERRUPT_MODE\nSetting 1 indicates interrupt mode is supported\nVOLTAGE_SUPPORT_1_8_V - Voltage Support 1.8V\nVOLTAGE_SUPPORT_3_0_V - Voltage Support 3.0V\nVOLTAGE_SUPPORT_3_3_V - Voltage Support 3.3V\nSUSPEND_RESUME_SUPPORT - Suspend/Resume Support\nThis bit indicates whether the Host Controller supports Suspend / Resume functionality. If this bit is 0, the Host Driver shall not issue either Suspend or Resume commands because the Suspend and Resume mechanism is not supported.\nDMA_SUPPORT - SDMA Support\nThis bit indicates whether the Host Controller is capable of using SDMA to transfer data between system memory and the Host Controller directly.\nHIGH_SPEED_SUPPORT - High Speed Support\nThis bit indicates whether the Host Controller and the Host System support High Speed mode and they can supply SD Clock frequency from 25MHz to 50MHz.\nADMA1_SUPPORT - ADMA1 Support\nThis bit indicates whether the Host Controller is capable of using ADMA1.\nADMA2_SUPPORT - ADMA2 Support\nThis bit indicates whether the Host Controller is capable of using ADMA2.\nEXTENDED_MEDIA_BUS_SUPPORT\nSetting to 1, indicates 8-bit data bus is supported.\nMAX_BLOCK_LENGTH - Max Block Length\nThis value indicates the maximum block size that the Host Driver can read and write to the buffer in the Host Controller. The buffer shall transfer this block size without wait cycles. Three sizes can be defined as indicated below. It is noted that transfer block length shall be always 512 bytes for SD Memory Cards regardless this field.\nBASE_CLOCK_FREQUENCY - Base Clock Frequency for SD Clock\nThis value indicates the base (maximum) clock frequency for the SD Clock. Unit values are 1MHz. If the real frequency is 16.5MHz, the lager value shall be set 01 0001b (17MHz) because the Host Driver use this value to calculate the clock divider value (Refer to the SDCLK Frequency Select in the Clock Control register.) and it shall not exceed upper limit of the SD Clock frequency. The supported clock range is 10MHz to 63MHz. If these bits are all 0, the Host System has to get information via another method.\n- Not 0  -  1MHz to 63MHz\n- 000000b- Get information via another method\nTIMEOUT_CLOCK_UNIT - Timeout Clock Unit\nThis bit shows the unit of base clock frequency used to detect Data Timeout Error.\n- 0 KHz\n- 1 MHz\nTIMEOUT_CLOCK_FREQUENCY - Timeout Clock Frequency\nThis bit shows the base clock frequency used to detect Data Timeout Error. The Timeout Clock Unit defines the unit of this field's value.\n- Timeout Clock Unit =0 [KHz] unit: 1KHz to 63KHz\n- Timeout Clock Unit =1 [MHz] unit: 1MHz to 63MHz\n- Not 0   - 1KHz to 63KHz or 1MHz to 63MHz\n- 000000b - Get information via another method\nCapabilities Register";
}

#define MAXIMUM_CURRENT_OFFSET 0x48
#define MAXIMUM_CURRENT_UNDEFMASK 0xFF000000
union maximum_current_u {
    struct {
        unsigned int maximum_current_for_3_3v:8;/* Maximum Current for 3.3V */
        unsigned int maximum_current_for_3_0v:8;/* Maximum Current for 3.0V */
        unsigned int maximum_current_for_1_8v:8;/* Maximum Current for 1.8V */
        unsigned int undefined_bits_24_31:8;
    };

    u_int32_t reg32;
};

void SdhciDev::fill_maximum_current_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const maximum_current_u old_value_t = { .reg32 = value };
    const maximum_current_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: maximum_current_for_3_3v:8",
              "Maximum Current for 3.3V",
              8, old_value_t.maximum_current_for_3_3v, new_value_t.maximum_current_for_3_3v };
    m_bit_details_model.bits.append(entry);
    entry = { "08: maximum_current_for_3_0v:8",
              "Maximum Current for 3.0V",
              8, old_value_t.maximum_current_for_3_0v, new_value_t.maximum_current_for_3_0v };
    m_bit_details_model.bits.append(entry);
    entry = { "16: maximum_current_for_1_8v:8",
              "Maximum Current for 1.8V",
              8, old_value_t.maximum_current_for_1_8v, new_value_t.maximum_current_for_1_8v };
    m_bit_details_model.bits.append(entry);
    entry = { "24: undefined_bits_24_31:8", "", 8, old_value_t.undefined_bits_24_31, new_value_t.undefined_bits_24_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = " Maximum Current Capabilities Register";
}

#define FORCE_EVENT_OFFSET 0x50
#define FORCE_EVENT_UNDEFMASK 0x0400FF60
union force_event_u {
    struct {
        unsigned int auto_cmd12_not_executed:1;/* 0 = NO_INTERRUPT 1 = INTERRUPT */
        unsigned int auto_cmd12_timeout_err:1;/* 0 = NO_INTERRUPT 1 = INTERRUPT */
        unsigned int auto_cmd12_crc_err:1;  /* 0 = NO_INTERRUPT 1 = INTERRUPT */
        unsigned int auto_cmd12_end_bit_err:1;/* 0 = NO_INTERRUPT 1 = INTERRUPT */
        unsigned int auto_cmd12_index_err:1;/* 0 = NO_INTERRUPT 1 = INTERRUPT */
        unsigned int undefined_bits_5_6:2;
        unsigned int auto_cmd12_not_issued:1;/* 0 = NO_INTERRUPT 1 = INTERRUPT */
        unsigned int undefined_bits_8_15:8;
        unsigned int command_timeout_err:1; /* 0 = NO_INTERRUPT 1 = INTERRUPT */
        unsigned int command_crc_err:1;     /* 0 = NO_INTERRUPT 1 = INTERRUPT */
        unsigned int command_end_bit_err:1; /* 0 = NO_INTERRUPT 1 = INTERRUPT */
        unsigned int command_index_err:1;   /* 0 = NO_INTERRUPT 1 = INTERRUPT */
        unsigned int datatimeout_err:1;     /* 0 = NO_INTERRUPT 1 = INTERRUPT */
        unsigned int datacrc_err:1;         /* 0 = NO_INTERRUPT 1 = INTERRUPT */
        unsigned int data_end_bit_err:1;    /* 0 = NO_INTERRUPT 1 = INTERRUPT */
        unsigned int currentlimit_err:1;    /* 0 = NO_INTERRUPT; 1 = INTERRUPT */
        unsigned int autocmd12_err:1;       /* 0 = NO_INTERRUPT 1 = INTERRUPT */
        unsigned int adma_err:1;            /* 0 = NO_INTERRUPT 1 = INTERRUPT */
        unsigned int undefined_bit_26:1;
        unsigned int spi_err:1;             /* 0 = DISABLE 1 = ENABLE */
        unsigned int target_resp_error:1;   /* 0 = NO_ERROR 1 = ERROR */
        unsigned int ceata_error:1;         /* 0 = NO_ERROR 1 = ERROR */
        unsigned int vendor_specific_err_status:2;/* 0 = DISABLE 3 = ENABLE */
    };

    u_int32_t reg32;
};

void SdhciDev::fill_force_event_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const force_event_u old_value_t = { .reg32 = value };
    const force_event_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: auto_cmd12_not_executed:1",
              "0 = NO_INTERRUPT\n1 = INTERRUPT",
              1, old_value_t.auto_cmd12_not_executed, new_value_t.auto_cmd12_not_executed };
    m_bit_details_model.bits.append(entry);
    entry = { "01: auto_cmd12_timeout_err:1",
              "0 = NO_INTERRUPT\n1 = INTERRUPT",
              1, old_value_t.auto_cmd12_timeout_err, new_value_t.auto_cmd12_timeout_err };
    m_bit_details_model.bits.append(entry);
    entry = { "02: auto_cmd12_crc_err:1",
              "0 = NO_INTERRUPT\n1 = INTERRUPT",
              1, old_value_t.auto_cmd12_crc_err, new_value_t.auto_cmd12_crc_err };
    m_bit_details_model.bits.append(entry);
    entry = { "03: auto_cmd12_end_bit_err:1",
              "0 = NO_INTERRUPT\n1 = INTERRUPT",
              1, old_value_t.auto_cmd12_end_bit_err, new_value_t.auto_cmd12_end_bit_err };
    m_bit_details_model.bits.append(entry);
    entry = { "04: auto_cmd12_index_err:1",
              "0 = NO_INTERRUPT\n1 = INTERRUPT",
              1, old_value_t.auto_cmd12_index_err, new_value_t.auto_cmd12_index_err };
    m_bit_details_model.bits.append(entry);
    entry = { "05: undefined_bits_5_6:2", "", 2, old_value_t.undefined_bits_5_6, new_value_t.undefined_bits_5_6 };
    m_bit_details_model.bits.append(entry);
    entry = { "07: auto_cmd12_not_issued:1",
              "0 = NO_INTERRUPT\n1 = INTERRUPT",
              1, old_value_t.auto_cmd12_not_issued, new_value_t.auto_cmd12_not_issued };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_15:8", "", 8, old_value_t.undefined_bits_8_15, new_value_t.undefined_bits_8_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: command_timeout_err:1",
              "0 = NO_INTERRUPT\n1 = INTERRUPT",
              1, old_value_t.command_timeout_err, new_value_t.command_timeout_err };
    m_bit_details_model.bits.append(entry);
    entry = { "17: command_crc_err:1",
              "0 = NO_INTERRUPT\n1 = INTERRUPT",
              1, old_value_t.command_crc_err, new_value_t.command_crc_err };
    m_bit_details_model.bits.append(entry);
    entry = { "18: command_end_bit_err:1",
              "0 = NO_INTERRUPT\n1 = INTERRUPT",
              1, old_value_t.command_end_bit_err, new_value_t.command_end_bit_err };
    m_bit_details_model.bits.append(entry);
    entry = { "19: command_index_err:1",
              "0 = NO_INTERRUPT\n1 = INTERRUPT",
              1, old_value_t.command_index_err, new_value_t.command_index_err };
    m_bit_details_model.bits.append(entry);
    entry = { "20: datatimeout_err:1",
              "0 = NO_INTERRUPT\n1 = INTERRUPT",
              1, old_value_t.datatimeout_err, new_value_t.datatimeout_err };
    m_bit_details_model.bits.append(entry);
    entry = { "21: datacrc_err:1",
              "0 = NO_INTERRUPT\n1 = INTERRUPT",
              1, old_value_t.datacrc_err, new_value_t.datacrc_err };
    m_bit_details_model.bits.append(entry);
    entry = { "22: data_end_bit_err:1",
              "0 = NO_INTERRUPT\n1 = INTERRUPT",
              1, old_value_t.data_end_bit_err, new_value_t.data_end_bit_err };
    m_bit_details_model.bits.append(entry);
    entry = { "23: currentlimit_err:1",
              "0 = NO_INTERRUPT;\n1 = INTERRUPT",
              1, old_value_t.currentlimit_err, new_value_t.currentlimit_err };
    m_bit_details_model.bits.append(entry);
    entry = { "24: autocmd12_err:1",
              "0 = NO_INTERRUPT\n1 = INTERRUPT",
              1, old_value_t.autocmd12_err, new_value_t.autocmd12_err };
    m_bit_details_model.bits.append(entry);
    entry = { "25: adma_err:1",
              "0 = NO_INTERRUPT\n1 = INTERRUPT",
              1, old_value_t.adma_err, new_value_t.adma_err };
    m_bit_details_model.bits.append(entry);
    entry = { "26: undefined_bit_26:1", "", 1, old_value_t.undefined_bit_26, new_value_t.undefined_bit_26 };
    m_bit_details_model.bits.append(entry);
    entry = { "27: spi_err:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.spi_err, new_value_t.spi_err };
    m_bit_details_model.bits.append(entry);
    entry = { "28: target_resp_error:1",
              "0 = NO_ERROR\n1 = ERROR",
              1, old_value_t.target_resp_error, new_value_t.target_resp_error };
    m_bit_details_model.bits.append(entry);
    entry = { "29: ceata_error:1",
              "0 = NO_ERROR\n1 = ERROR",
              1, old_value_t.ceata_error, new_value_t.ceata_error };
    m_bit_details_model.bits.append(entry);
    entry = { "30: vendor_specific_err_status:2",
              "0 = DISABLE\n3 = ENABLE",
              2, old_value_t.vendor_specific_err_status, new_value_t.vendor_specific_err_status };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "The Force Event Register is not a physically implemented register. Rather, it is an address at which the Auto CMD12 Error Status Register can be written.\nWriting 1 : set each bit of the Auto CMD12 Error Status Register\nWriting 0 : no effect\nForce Event for Auto CMD12 Error Status Register";
}

#define ADMA_ERR_STATUS_OFFSET 0x54
#define ADMA_ERR_STATUS_UNDEFMASK 0xFFFFFFF8
union adma_err_status_u {
    struct {
        unsigned int adma_err_state:2;
        unsigned int adma_length_mismatch_err:1;/* 0 = NO_ERR 1 = ERR */
        unsigned int undefined_bits_3_31:29;
    };

    u_int32_t reg32;
};

void SdhciDev::fill_adma_err_status_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const adma_err_status_u old_value_t = { .reg32 = value };
    const adma_err_status_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: adma_err_state:2", "", 2, old_value_t.adma_err_state, new_value_t.adma_err_state };
    m_bit_details_model.bits.append(entry);
    entry = { "02: adma_length_mismatch_err:1",
              "0 = NO_ERR\n1 = ERR",
              1, old_value_t.adma_length_mismatch_err, new_value_t.adma_length_mismatch_err };
    m_bit_details_model.bits.append(entry);
    entry = { "03: undefined_bits_3_31:29", "", 29, old_value_t.undefined_bits_3_31, new_value_t.undefined_bits_3_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "ADMA_LENGTH_MISMATCH_ERR - ADMA Length Mismatch Error. This error occurs in the following 2 cases.\n    * While Block Count Enable being set, the total data length specified by the Descriptor table is different from that specified by the Block Count and Block Length.\n    * Total data length cannot be divided by the block length.\nADMA_ERR_STATE - ADMA Error State. This field indicates the state of ADMA when error is occurred during ADMA data transfer. This field never indicates \"10\" because ADMA never stops in this state.\nD01 - D00\n ADMA Error State when error is occurred\n Contents of SYS_SDR register\n00\n ST_STOP (Stop DMA)\n Points next of the error descriptor\nD01 - D00\n ADMA Error State when error is occurred\n Contents of SYS_SDR register\n01\n ST_FDS (Fetch Descriptor)\n Points the error descriptor\n10\n Never set this state\n (Not used)\n11\n ST_TFR (Transfer Data)\n Points the next of the error descriptor\nADMA Error Status Register";
}

#define ADMA_SYSTEM_ADDRESS_OFFSET 0x58
#define ADMA_SYSTEM_ADDRESS_UNDEFMASK 0x00000000
union adma_system_address_u {
    struct {
        unsigned int adma_system_address:32;
    };

    u_int32_t reg32;
};

void SdhciDev::fill_adma_system_address_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const adma_system_address_u old_value_t = { .reg32 = value };
    const adma_system_address_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: adma_system_address:32", "", 32, old_value_t.adma_system_address, new_value_t.adma_system_address };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "This register holds byte address of executing command of the Descriptor table. 32-bit Address Descriptor uses lower 32-bit of this register. At the start of ADMA, the Host Driver shall set start address of the Descriptor table. The ADMA increments this register address, which points to next line, when every fetching a Descriptor line. When the ADMA Error Interrupt is generated, this register shall hold valid Descriptor address depending on the ADMA state. The Host Driver programs Descriptor Table on 32-bit boundary and set 32-bit boundary address to this register. ADMA2 ignores lower 2-bit of this register and assumes it to be 00b.\nADMA System Address Register";
}

#define SPI_INTERRUPT_SUPPORT_OFFSET 0xF0
#define SPI_INTERRUPT_SUPPORT_UNDEFMASK 0xFFFFFF00
union spi_interrupt_support_u {
    struct {
        unsigned int spi_int_support:8;     /* This bit is set to indicate the assertion of interrupts in SPI MODE at any time Irrespective on the status of card select */
        unsigned int undefined_bits_8_31:24;
    };

    u_int32_t reg32;
};

void SdhciDev::fill_spi_interrupt_support_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const spi_interrupt_support_u old_value_t = { .reg32 = value };
    const spi_interrupt_support_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: spi_int_support:8",
              "This bit is set to indicate the assertion of interrupts in SPI MODE at any time Irrespective on the status of card select",
              8, old_value_t.spi_int_support, new_value_t.spi_int_support };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_31:24", "", 24, old_value_t.undefined_bits_8_31, new_value_t.undefined_bits_8_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "SPI Interrupt Support Register";
}

#define SLOT_INTERRUPT_STATUS_OFFSET 0xFC
#define SLOT_INTERRUPT_STATUS_UNDEFMASK 0x0000FF00
union slot_interrupt_status_u {
    struct {
        unsigned int interrupt_signal_for_each_slot:8;
        unsigned int undefined_bits_8_15:8;
        unsigned int specification_version_number:8;
        unsigned int vendor_version_number:8;
    };

    u_int32_t reg32;
};

void SdhciDev::fill_slot_interrupt_status_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const slot_interrupt_status_u old_value_t = { .reg32 = value };
    const slot_interrupt_status_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: interrupt_signal_for_each_slot:8", "", 8, old_value_t.interrupt_signal_for_each_slot, new_value_t.interrupt_signal_for_each_slot };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_15:8", "", 8, old_value_t.undefined_bits_8_15, new_value_t.undefined_bits_8_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: specification_version_number:8", "", 8, old_value_t.specification_version_number, new_value_t.specification_version_number };
    m_bit_details_model.bits.append(entry);
    entry = { "24: vendor_version_number:8", "", 8, old_value_t.vendor_version_number, new_value_t.vendor_version_number };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = ". VENDOR_VERSION_NUMBER - Vendor Version Number\nThis status is reserved for the vendor version number. The Host Driver should not use this status.\n    * SPECIFICATION_VERSION_NUMBER - Specification Version Number\nThis status indicates the Host Controller Spec. Version. The upper and lower 4-bits indicate the version.\n- 00 SD Host Specification Version 1.00\n- 01 SD Host Specification Version 2.00\nIncluding the feature of the ADMA and Test Register, others Reserved\n    * INTERRUPT_SIGNAL_FOR_EACH_SLOT - Interrupt Signal For Each Slot\nThese status bits indicate the logical OR of Interrupt Signal and Wakeup Signal for each slot. A maximum of 8 slots can be defined. If one interrupt signal is associated with multiple slots, the Host Driver can know which interrupt is generated by reading these status bits. By a power on reset or by setting Software Reset For All, the interrupt signal shall be de-asserted and this status shall read 00h.\n- Bit 00 Slot 1\n- Bit 01 Slot 2\n- Bit 02 Slot 3\n- Bit 07 Slot 8\nSlot Interrupt Status Register";
}

#define VENDOR_CLOCK_CNTRL_OFFSET 0x100
#define VENDOR_CLOCK_CNTRL_UNDEFMASK 0xFFFFFFFE
union vendor_clock_cntrl_u {
    struct {
        unsigned int sdmmc_clk:1;           /* This is set when sdmmc_clk is supplied by the CAR module.Prior to sdmmc_clk switch OFF. This bit should be written '0'. Prior to sdmmc_clk switch OFF. This bit should be written '0'. By writing zero, the asynchronous card interrupt is routed to the Interrupt controller. 0 = DISABLE 1 = ENABLE */
        unsigned int undefined_bits_1_31:31;
    };

    u_int32_t reg32;
};

void SdhciDev::fill_vendor_clock_cntrl_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const vendor_clock_cntrl_u old_value_t = { .reg32 = value };
    const vendor_clock_cntrl_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: sdmmc_clk:1",
              "This is set when sdmmc_clk is supplied by the CAR module.Prior to sdmmc_clk switch OFF. This bit should be written '0'. Prior to sdmmc_clk switch OFF. This bit should be written '0'. By writing zero, the asynchronous card interrupt is routed to the Interrupt controller.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.sdmmc_clk, new_value_t.sdmmc_clk };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_31:31", "", 31, old_value_t.undefined_bits_1_31, new_value_t.undefined_bits_1_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Vendor Clock Control Register";
}

#define VENDOR_SPI_CNTRL_OFFSET 0x104
#define VENDOR_SPI_CNTRL_UNDEFMASK 0xFFFFFFFE
union vendor_spi_cntrl_u {
    struct {
        unsigned int spi_mode:1;            /* This is a mirror bit. The SPI mode is set if this bit is set or CMD_XFER_MODE[7] is set Writing 1 will drive the CS Low and writing zero will de-assert the CS Signal 0 = DISABLE 1 = ENABLE */
        unsigned int undefined_bits_1_31:31;
    };

    u_int32_t reg32;
};

void SdhciDev::fill_vendor_spi_cntrl_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const vendor_spi_cntrl_u old_value_t = { .reg32 = value };
    const vendor_spi_cntrl_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: spi_mode:1",
              "This is a mirror bit. The SPI mode is set if this bit is set or CMD_XFER_MODE[7] is set Writing 1 will drive the CS Low and writing zero will de-assert the CS Signal\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.spi_mode, new_value_t.spi_mode };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_31:31", "", 31, old_value_t.undefined_bits_1_31, new_value_t.undefined_bits_1_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Vendor SPI Control Register";
}

#define VENDOR_SPI_INTR_STATUS_OFFSET 0x108
#define VENDOR_SPI_INTR_STATUS_UNDEFMASK 0xFFFFFE00
union vendor_spi_intr_status_u {
    struct {
        unsigned int dat_response:5;        /* Data Response while write to card  5 = DATA_ACCEPTED 11 = CRC_ERR 13 = WRITE_ERR */
        unsigned int dat_err_token:4;       /* Data Error Token, while read from card */
        unsigned int undefined_bits_9_31:23;
    };

    u_int32_t reg32;
};

void SdhciDev::fill_vendor_spi_intr_status_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const vendor_spi_intr_status_u old_value_t = { .reg32 = value };
    const vendor_spi_intr_status_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: dat_response:5",
              "Data Response while write to card \n5 = DATA_ACCEPTED\n11 = CRC_ERR\n13 = WRITE_ERR",
              5, old_value_t.dat_response, new_value_t.dat_response };
    m_bit_details_model.bits.append(entry);
    entry = { "05: dat_err_token:4",
              "Data Error Token, while read from card",
              4, old_value_t.dat_err_token, new_value_t.dat_err_token };
    m_bit_details_model.bits.append(entry);
    entry = { "09: undefined_bits_9_31:23", "", 23, old_value_t.undefined_bits_9_31, new_value_t.undefined_bits_9_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "The fields are valid when an SPI error has occurred.\nSPI Interrupt Status Register";
}

#define VENDOR_CEATA_CNTRL_OFFSET 0x10C
#define VENDOR_CEATA_CNTRL_UNDEFMASK 0xFFFFFFFE
union vendor_ceata_cntrl_u {
    struct {
        unsigned int ccs_signal:1;          /* If this bit is set to 1,the controller expects a Command completion signal from the card after the transfer. If the CCS Signal doesn’t come within Data Timeout Value the CEATA Error is flagged. 0 = DISABLE 1 = ENABLE */
        unsigned int undefined_bits_1_31:31;
    };

    u_int32_t reg32;
};

void SdhciDev::fill_vendor_ceata_cntrl_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const vendor_ceata_cntrl_u old_value_t = { .reg32 = value };
    const vendor_ceata_cntrl_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: ccs_signal:1",
              "If this bit is set to 1,the controller expects a Command completion signal from the card after the transfer. If the CCS Signal doesn’t come within Data Timeout Value the CEATA Error is flagged.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.ccs_signal, new_value_t.ccs_signal };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_31:31", "", 31, old_value_t.undefined_bits_1_31, new_value_t.undefined_bits_1_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Vendor CEATA Control Register";
}

#define VENDOR_BOOT_CNTRL_OFFSET 0x110
#define VENDOR_BOOT_CNTRL_UNDEFMASK 0xFFFFFFFC
union vendor_boot_cntrl_u {
    struct {
        unsigned int boot:1;                /* This bit enables/disable BootOption1.If set BootOption1 is enable, HW auto clears it when boot data is done. Writing 0 terminates the BootOption1  0 = DISABLE 1 = ENABLE */
        unsigned int boot_ack:1;            /* This bit is used to support Boot Option in MMC 4.3 version cards. If set Boot acknowledgment is given by card else not given by card  0 = DISABLE 1 = ENABLE */
        unsigned int undefined_bits_2_31:30;
    };

    u_int32_t reg32;
};

void SdhciDev::fill_vendor_boot_cntrl_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const vendor_boot_cntrl_u old_value_t = { .reg32 = value };
    const vendor_boot_cntrl_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: boot:1",
              "This bit enables/disable BootOption1.If set BootOption1 is enable, HW auto clears it when boot data is done. Writing 0 terminates the BootOption1 \n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.boot, new_value_t.boot };
    m_bit_details_model.bits.append(entry);
    entry = { "01: boot_ack:1",
              "This bit is used to support Boot Option in MMC 4.3 version cards. If set Boot acknowledgment is given by card else not given by card \n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.boot_ack, new_value_t.boot_ack };
    m_bit_details_model.bits.append(entry);
    entry = { "02: undefined_bits_2_31:30", "", 30, old_value_t.undefined_bits_2_31, new_value_t.undefined_bits_2_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "This Register is used to configure Boot Mode to support MMC v4.3 cards.\nVendor Boot Control Register";
}

#define VENDOR_BOOT_ACK_TIMEOUT_OFFSET 0x114
#define VENDOR_BOOT_ACK_TIMEOUT_UNDEFMASK 0xFFF00000
union vendor_boot_ack_timeout_u {
    struct {
        unsigned int value:20;              /* If Boot Acknowledgment is not received within the programmed number of cycles. Boot Acknowledgement Timeout error occurs(VENDOR_SPECIFIC_ERR[0]) */
        unsigned int undefined_bits_20_31:12;
    };

    u_int32_t reg32;
};

void SdhciDev::fill_vendor_boot_ack_timeout_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const vendor_boot_ack_timeout_u old_value_t = { .reg32 = value };
    const vendor_boot_ack_timeout_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: value:20",
              "If Boot Acknowledgment is not received within the programmed number of cycles. Boot Acknowledgement Timeout error occurs(VENDOR_SPECIFIC_ERR[0])",
              20, old_value_t.value, new_value_t.value };
    m_bit_details_model.bits.append(entry);
    entry = { "20: undefined_bits_20_31:12", "", 12, old_value_t.undefined_bits_20_31, new_value_t.undefined_bits_20_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Vendor Boot Acknowledgment Timeout Register";
}

#define VENDOR_BOOT_DAT_TIMEOUT_OFFSET 0x118
#define VENDOR_BOOT_DAT_TIMEOUT_UNDEFMASK 0xFE000000
union vendor_boot_dat_timeout_u {
    struct {
        unsigned int value:25;              /* If Boot Data is not received within the programmed number of cycles. Then Data Timeout error occurs */
        unsigned int undefined_bits_25_31:7;
    };

    u_int32_t reg32;
};

void SdhciDev::fill_vendor_boot_dat_timeout_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const vendor_boot_dat_timeout_u old_value_t = { .reg32 = value };
    const vendor_boot_dat_timeout_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: value:25",
              "If Boot Data is not received within the programmed number of cycles. Then Data Timeout error occurs",
              25, old_value_t.value, new_value_t.value };
    m_bit_details_model.bits.append(entry);
    entry = { "25: undefined_bits_25_31:7", "", 7, old_value_t.undefined_bits_25_31, new_value_t.undefined_bits_25_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "Boot Data Timeout Register";
}

#define VENDOR_DEBOUNCE_COUNT_OFFSET 0x11C
#define VENDOR_DEBOUNCE_COUNT_UNDEFMASK 0xFF000000
union vendor_debounce_count_u {
    struct {
        unsigned int value:24;              /* The number of 32KHz clock cycles is programmed to meet Debounce period of the card slot */
        unsigned int undefined_bits_24_31:8;
    };

    u_int32_t reg32;
};

void SdhciDev::fill_vendor_debounce_count_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const vendor_debounce_count_u old_value_t = { .reg32 = value };
    const vendor_debounce_count_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: value:24",
              "The number of 32KHz clock cycles is programmed to meet Debounce period of the card slot",
              24, old_value_t.value, new_value_t.value };
    m_bit_details_model.bits.append(entry);
    entry = { "24: undefined_bits_24_31:8", "", 8, old_value_t.undefined_bits_24_31, new_value_t.undefined_bits_24_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "The Debounce Counter runs on 32KHz clock.\nKeeping the default value to 100ms = ( 100 * 32cycles/1ms) = 3200 cycles for 100ms = 0xC80\nDebounce Counter Value Register";
}

bool SdhciDev::is_offset_valid(const u_int32_t &offset) const
{
    switch (offset) {
    case SYSTEM_ADDRESS_OFFSET:
    case BLOCK_SIZE_BLOCK_COUNT_OFFSET:
    case ARGUMENT_OFFSET:
    case CMD_XFER_MODE_OFFSET:
    case RESPONSE_R0_R1_OFFSET:
    case RESPONSE_R2_R3_OFFSET:
    case RESPONSE_R4_R5_OFFSET:
    case RESPONSE_R6_R7_OFFSET:
    case BUFFER_DATA_PORT_OFFSET:
    case PRESENT_STATE_OFFSET:
    case POWER_CONTROL_HOST_OFFSET:
    case SW_RESET_TIMEOUT_CTRL_CLOCK_CONTROL_OFFSET:
    case INTERRUPT_STATUS_OFFSET:
    case INTERRUPT_STATUS_ENABLE_OFFSET:
    case INTERRUPT_SIGNAL_ENABLE_OFFSET:
    case AUTO_CMD12_ERR_STATUS_OFFSET:
    case CAPABILITIES_OFFSET:
    case MAXIMUM_CURRENT_OFFSET:
    case FORCE_EVENT_OFFSET:
    case ADMA_ERR_STATUS_OFFSET:
    case ADMA_SYSTEM_ADDRESS_OFFSET:
    case SPI_INTERRUPT_SUPPORT_OFFSET:
    case SLOT_INTERRUPT_STATUS_OFFSET:
    case VENDOR_CLOCK_CNTRL_OFFSET:
    case VENDOR_SPI_CNTRL_OFFSET:
    case VENDOR_SPI_INTR_STATUS_OFFSET:
    case VENDOR_CEATA_CNTRL_OFFSET:
    case VENDOR_BOOT_CNTRL_OFFSET:
    case VENDOR_BOOT_ACK_TIMEOUT_OFFSET:
    case VENDOR_BOOT_DAT_TIMEOUT_OFFSET:
    case VENDOR_DEBOUNCE_COUNT_OFFSET:
        return true;
    default:
        break;
    }

    return false;
}

bool SdhciDev::is_undef_changed(const u_int32_t &offset,
                                           const u_int32_t &value,
                                           const u_int32_t &new_value) const
{
    switch (offset) {
    case SYSTEM_ADDRESS_OFFSET:
        if ((value ^ new_value) & SYSTEM_ADDRESS_UNDEFMASK)
            return true;
        break;
    case BLOCK_SIZE_BLOCK_COUNT_OFFSET:
        if ((value ^ new_value) & BLOCK_SIZE_BLOCK_COUNT_UNDEFMASK)
            return true;
        break;
    case ARGUMENT_OFFSET:
        if ((value ^ new_value) & ARGUMENT_UNDEFMASK)
            return true;
        break;
    case CMD_XFER_MODE_OFFSET:
        if ((value ^ new_value) & CMD_XFER_MODE_UNDEFMASK)
            return true;
        break;
    case RESPONSE_R0_R1_OFFSET:
        if ((value ^ new_value) & RESPONSE_R0_R1_UNDEFMASK)
            return true;
        break;
    case RESPONSE_R2_R3_OFFSET:
        if ((value ^ new_value) & RESPONSE_R2_R3_UNDEFMASK)
            return true;
        break;
    case RESPONSE_R4_R5_OFFSET:
        if ((value ^ new_value) & RESPONSE_R4_R5_UNDEFMASK)
            return true;
        break;
    case RESPONSE_R6_R7_OFFSET:
        if ((value ^ new_value) & RESPONSE_R6_R7_UNDEFMASK)
            return true;
        break;
    case BUFFER_DATA_PORT_OFFSET:
        if ((value ^ new_value) & BUFFER_DATA_PORT_UNDEFMASK)
            return true;
        break;
    case PRESENT_STATE_OFFSET:
        if ((value ^ new_value) & PRESENT_STATE_UNDEFMASK)
            return true;
        break;
    case POWER_CONTROL_HOST_OFFSET:
        if ((value ^ new_value) & POWER_CONTROL_HOST_UNDEFMASK)
            return true;
        break;
    case SW_RESET_TIMEOUT_CTRL_CLOCK_CONTROL_OFFSET:
        if ((value ^ new_value) & SW_RESET_TIMEOUT_CTRL_CLOCK_CONTROL_UNDEFMASK)
            return true;
        break;
    case INTERRUPT_STATUS_OFFSET:
        if ((value ^ new_value) & INTERRUPT_STATUS_UNDEFMASK)
            return true;
        break;
    case INTERRUPT_STATUS_ENABLE_OFFSET:
        if ((value ^ new_value) & INTERRUPT_STATUS_ENABLE_UNDEFMASK)
            return true;
        break;
    case INTERRUPT_SIGNAL_ENABLE_OFFSET:
        if ((value ^ new_value) & INTERRUPT_SIGNAL_ENABLE_UNDEFMASK)
            return true;
        break;
    case AUTO_CMD12_ERR_STATUS_OFFSET:
        if ((value ^ new_value) & AUTO_CMD12_ERR_STATUS_UNDEFMASK)
            return true;
        break;
    case CAPABILITIES_OFFSET:
        if ((value ^ new_value) & CAPABILITIES_UNDEFMASK)
            return true;
        break;
    case MAXIMUM_CURRENT_OFFSET:
        if ((value ^ new_value) & MAXIMUM_CURRENT_UNDEFMASK)
            return true;
        break;
    case FORCE_EVENT_OFFSET:
        if ((value ^ new_value) & FORCE_EVENT_UNDEFMASK)
            return true;
        break;
    case ADMA_ERR_STATUS_OFFSET:
        if ((value ^ new_value) & ADMA_ERR_STATUS_UNDEFMASK)
            return true;
        break;
    case ADMA_SYSTEM_ADDRESS_OFFSET:
        if ((value ^ new_value) & ADMA_SYSTEM_ADDRESS_UNDEFMASK)
            return true;
        break;
    case SPI_INTERRUPT_SUPPORT_OFFSET:
        if ((value ^ new_value) & SPI_INTERRUPT_SUPPORT_UNDEFMASK)
            return true;
        break;
    case SLOT_INTERRUPT_STATUS_OFFSET:
        if ((value ^ new_value) & SLOT_INTERRUPT_STATUS_UNDEFMASK)
            return true;
        break;
    case VENDOR_CLOCK_CNTRL_OFFSET:
        if ((value ^ new_value) & VENDOR_CLOCK_CNTRL_UNDEFMASK)
            return true;
        break;
    case VENDOR_SPI_CNTRL_OFFSET:
        if ((value ^ new_value) & VENDOR_SPI_CNTRL_UNDEFMASK)
            return true;
        break;
    case VENDOR_SPI_INTR_STATUS_OFFSET:
        if ((value ^ new_value) & VENDOR_SPI_INTR_STATUS_UNDEFMASK)
            return true;
        break;
    case VENDOR_CEATA_CNTRL_OFFSET:
        if ((value ^ new_value) & VENDOR_CEATA_CNTRL_UNDEFMASK)
            return true;
        break;
    case VENDOR_BOOT_CNTRL_OFFSET:
        if ((value ^ new_value) & VENDOR_BOOT_CNTRL_UNDEFMASK)
            return true;
        break;
    case VENDOR_BOOT_ACK_TIMEOUT_OFFSET:
        if ((value ^ new_value) & VENDOR_BOOT_ACK_TIMEOUT_UNDEFMASK)
            return true;
        break;
    case VENDOR_BOOT_DAT_TIMEOUT_OFFSET:
        if ((value ^ new_value) & VENDOR_BOOT_DAT_TIMEOUT_UNDEFMASK)
            return true;
        break;
    case VENDOR_DEBOUNCE_COUNT_OFFSET:
        if ((value ^ new_value) & VENDOR_DEBOUNCE_COUNT_UNDEFMASK)
            return true;
        break;

    default:
        break;
    }

    return false;
}

QString SdhciDev::get_register_name(const log_entry &entry) const
{
    switch (entry.offset) {
    case SYSTEM_ADDRESS_OFFSET:
        return QString("SYSTEM_ADDRESS");
    case BLOCK_SIZE_BLOCK_COUNT_OFFSET:
        return QString("BLOCK_SIZE_BLOCK_COUNT");
    case ARGUMENT_OFFSET:
        return QString("ARGUMENT");
    case CMD_XFER_MODE_OFFSET:
        return QString("CMD_XFER_MODE");
    case RESPONSE_R0_R1_OFFSET:
        return QString("RESPONSE_R0_R1");
    case RESPONSE_R2_R3_OFFSET:
        return QString("RESPONSE_R2_R3");
    case RESPONSE_R4_R5_OFFSET:
        return QString("RESPONSE_R4_R5");
    case RESPONSE_R6_R7_OFFSET:
        return QString("RESPONSE_R6_R7");
    case BUFFER_DATA_PORT_OFFSET:
        return QString("BUFFER_DATA_PORT");
    case PRESENT_STATE_OFFSET:
        return QString("PRESENT_STATE");
    case POWER_CONTROL_HOST_OFFSET:
        return QString("POWER_CONTROL_HOST");
    case SW_RESET_TIMEOUT_CTRL_CLOCK_CONTROL_OFFSET:
        return QString("SW_RESET_TIMEOUT_CTRL_CLOCK_CONTROL");
    case INTERRUPT_STATUS_OFFSET:
        return QString("INTERRUPT_STATUS");
    case INTERRUPT_STATUS_ENABLE_OFFSET:
        return QString("INTERRUPT_STATUS_ENABLE");
    case INTERRUPT_SIGNAL_ENABLE_OFFSET:
        return QString("INTERRUPT_SIGNAL_ENABLE");
    case AUTO_CMD12_ERR_STATUS_OFFSET:
        return QString("AUTO_CMD12_ERR_STATUS");
    case CAPABILITIES_OFFSET:
        return QString("CAPABILITIES");
    case MAXIMUM_CURRENT_OFFSET:
        return QString("MAXIMUM_CURRENT");
    case FORCE_EVENT_OFFSET:
        return QString("FORCE_EVENT");
    case ADMA_ERR_STATUS_OFFSET:
        return QString("ADMA_ERR_STATUS");
    case ADMA_SYSTEM_ADDRESS_OFFSET:
        return QString("ADMA_SYSTEM_ADDRESS");
    case SPI_INTERRUPT_SUPPORT_OFFSET:
        return QString("SPI_INTERRUPT_SUPPORT");
    case SLOT_INTERRUPT_STATUS_OFFSET:
        return QString("SLOT_INTERRUPT_STATUS");
    case VENDOR_CLOCK_CNTRL_OFFSET:
        return QString("VENDOR_CLOCK_CNTRL");
    case VENDOR_SPI_CNTRL_OFFSET:
        return QString("VENDOR_SPI_CNTRL");
    case VENDOR_SPI_INTR_STATUS_OFFSET:
        return QString("VENDOR_SPI_INTR_STATUS");
    case VENDOR_CEATA_CNTRL_OFFSET:
        return QString("VENDOR_CEATA_CNTRL");
    case VENDOR_BOOT_CNTRL_OFFSET:
        return QString("VENDOR_BOOT_CNTRL");
    case VENDOR_BOOT_ACK_TIMEOUT_OFFSET:
        return QString("VENDOR_BOOT_ACK_TIMEOUT");
    case VENDOR_BOOT_DAT_TIMEOUT_OFFSET:
        return QString("VENDOR_BOOT_DAT_TIMEOUT");
    case VENDOR_DEBOUNCE_COUNT_OFFSET:
        return QString("VENDOR_DEBOUNCE_COUNT");

    default:
        break;
    }

    qDebug() << QString().sprintf("SDHCI: %s: Ooops... 0x%x", __func__, entry.offset);

    return QString().sprintf("Ooops... @0x%X", entry.offset);
}

void SdhciDev::fill_bits_details(const u_int32_t &offset,
                                      const u_int32_t &value, const u_int32_t &new_value)
{
    switch (offset) {
    case SYSTEM_ADDRESS_OFFSET:
        fill_system_address_details(value, new_value);
        break;
    case BLOCK_SIZE_BLOCK_COUNT_OFFSET:
        fill_block_size_block_count_details(value, new_value);
        break;
    case ARGUMENT_OFFSET:
        fill_argument_details(value, new_value);
        break;
    case CMD_XFER_MODE_OFFSET:
        fill_cmd_xfer_mode_details(value, new_value);
        break;
    case RESPONSE_R0_R1_OFFSET:
        fill_response_r0_r1_details(value, new_value);
        break;
    case RESPONSE_R2_R3_OFFSET:
        fill_response_r2_r3_details(value, new_value);
        break;
    case RESPONSE_R4_R5_OFFSET:
        fill_response_r4_r5_details(value, new_value);
        break;
    case RESPONSE_R6_R7_OFFSET:
        fill_response_r6_r7_details(value, new_value);
        break;
    case BUFFER_DATA_PORT_OFFSET:
        fill_buffer_data_port_details(value, new_value);
        break;
    case PRESENT_STATE_OFFSET:
        fill_present_state_details(value, new_value);
        break;
    case POWER_CONTROL_HOST_OFFSET:
        fill_power_control_host_details(value, new_value);
        break;
    case SW_RESET_TIMEOUT_CTRL_CLOCK_CONTROL_OFFSET:
        fill_sw_reset_timeout_ctrl_clock_control_details(value, new_value);
        break;
    case INTERRUPT_STATUS_OFFSET:
        fill_interrupt_status_details(value, new_value);
        break;
    case INTERRUPT_STATUS_ENABLE_OFFSET:
        fill_interrupt_status_enable_details(value, new_value);
        break;
    case INTERRUPT_SIGNAL_ENABLE_OFFSET:
        fill_interrupt_signal_enable_details(value, new_value);
        break;
    case AUTO_CMD12_ERR_STATUS_OFFSET:
        fill_auto_cmd12_err_status_details(value, new_value);
        break;
    case CAPABILITIES_OFFSET:
        fill_capabilities_details(value, new_value);
        break;
    case MAXIMUM_CURRENT_OFFSET:
        fill_maximum_current_details(value, new_value);
        break;
    case FORCE_EVENT_OFFSET:
        fill_force_event_details(value, new_value);
        break;
    case ADMA_ERR_STATUS_OFFSET:
        fill_adma_err_status_details(value, new_value);
        break;
    case ADMA_SYSTEM_ADDRESS_OFFSET:
        fill_adma_system_address_details(value, new_value);
        break;
    case SPI_INTERRUPT_SUPPORT_OFFSET:
        fill_spi_interrupt_support_details(value, new_value);
        break;
    case SLOT_INTERRUPT_STATUS_OFFSET:
        fill_slot_interrupt_status_details(value, new_value);
        break;
    case VENDOR_CLOCK_CNTRL_OFFSET:
        fill_vendor_clock_cntrl_details(value, new_value);
        break;
    case VENDOR_SPI_CNTRL_OFFSET:
        fill_vendor_spi_cntrl_details(value, new_value);
        break;
    case VENDOR_SPI_INTR_STATUS_OFFSET:
        fill_vendor_spi_intr_status_details(value, new_value);
        break;
    case VENDOR_CEATA_CNTRL_OFFSET:
        fill_vendor_ceata_cntrl_details(value, new_value);
        break;
    case VENDOR_BOOT_CNTRL_OFFSET:
        fill_vendor_boot_cntrl_details(value, new_value);
        break;
    case VENDOR_BOOT_ACK_TIMEOUT_OFFSET:
        fill_vendor_boot_ack_timeout_details(value, new_value);
        break;
    case VENDOR_BOOT_DAT_TIMEOUT_OFFSET:
        fill_vendor_boot_dat_timeout_details(value, new_value);
        break;
    case VENDOR_DEBOUNCE_COUNT_OFFSET:
        fill_vendor_debounce_count_details(value, new_value);
        break;

    default:
        m_bit_details_model.bits.clear();
        break;
    }
}
