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

#include "gizmodev.h"

#include <QDebug>

#define AHB_MEM_OFFSET 0xC
#define AHB_MEM_UNDEFMASK 0x00F8FF38
union ahb_mem_u {
    struct {
        unsigned int enable_split:1;        /* AHB slave gizmo (memory controller) - Enable splitting AHB transaction. 1 = enable 0 = disable; 0 = DISABLE; 1 = ENABLE */
        unsigned int force_to_ahb_single:1; /* AHB slave gizmo (memory controller) - Force all AHB transaction to single data request transaction 1 = force to single data transaction always. 0 = don’t force to single data transaction. 0 = NOT_SINGLE_DATA; 1 = SINGLE_DATA */
        unsigned int enb_fast_rearbitrate:1;/* AHB slave gizmo - Enable fast re-arbitration. 1 = allow AHB master re-arbitration as soon as the device returns one read data into the gizmos queue. 0 = allow AHB master re-arbitration only when the device returns all read data into the gizmos queue; 0 = DISABLE; 1 = ENABLE */
        unsigned int undefined_bits_3_5:3;
        unsigned int accept_ahb_wr_always:1;/* AHB slave gizmo (memory controller) - Accept AHB write request always. 1= always accept AHB write request without checking whether there is room in the queue to store the write data. Bypass Memory Controller AHB slave gizmo write queue. 0 = accept AHB write request only when there’s enough room in the queue to store all the write data. Memory controller AHB slave gizmos write queue is used in this case; 0 = ACCEPT_ON_CHECK; 1 = ACCEPT_ON_NOCHECK */
        unsigned int dont_split_ahb_wr:1;   /* AHB slave gizmo (memory controller) - don’t split AHB write transaction 1 =  don’t split AHB write transaction ever. 0 (and enable_split=1) = allow AHB write transaction to be split; 0 = ENABLE; 1 = DISABLE */
        unsigned int undefined_bits_8_15:8;
        unsigned int max_ahb_burstsize:2;   /* AHB master gizmo (AHB-DMA) - Maximum allowed AHB burst size. 00 = single transfer. 01 = burst-of-4. 10 = burst-of-8 11 = burst-of-16; 0 = DMA_BURST_1WORDS; 1 = DMA_BURST_4WORDS; 2 = DMA_BURST_8WORDS; 3 = DMA_BURST_16WORDS */
        unsigned int immediate:1;           /* AHB master gizmo (AHB-DMA) - Start AHB write request immediately 1 = start the AHB write request immediately as soon as the device has put one write data in the AHB gizmos queue. 0 = start the AHB write request only when all the write data has transferred from the device to the AHB gizmos queue; 0 = DISABLE; 1 = ENABLE */
        unsigned int undefined_bits_19_23:5;
        unsigned int req_neg_cnt:8;         /* AHB master request negate count. This is an 8-bit counter used to indicate the minimum number of clk count between requests from this AHB master */
    };

    u_int32_t reg32;
};

void GizmoDev::fill_ahb_mem_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const ahb_mem_u old_value_t = { .reg32 = value };
    const ahb_mem_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: enable_split:1",
              "AHB slave gizmo (memory controller) - Enable splitting AHB transaction.\n1 = enable\n0 = disable;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.enable_split, new_value_t.enable_split };
    m_bit_details_model.bits.append(entry);
    entry = { "01: force_to_ahb_single:1",
              "AHB slave gizmo (memory controller) - Force all AHB transaction to single data request transaction\n1 = force to single data transaction always.\n0 = don’t force to single data transaction.\n0 = NOT_SINGLE_DATA;\n1 = SINGLE_DATA",
              1, old_value_t.force_to_ahb_single, new_value_t.force_to_ahb_single };
    m_bit_details_model.bits.append(entry);
    entry = { "02: enb_fast_rearbitrate:1",
              "AHB slave gizmo - Enable fast re-arbitration.\n1 = allow AHB master re-arbitration as soon as the device returns one read data into the gizmos queue.\n0 = allow AHB master re-arbitration only when the device returns all read data into the gizmos queue;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.enb_fast_rearbitrate, new_value_t.enb_fast_rearbitrate };
    m_bit_details_model.bits.append(entry);
    entry = { "03: undefined_bits_3_5:3", "", 3, old_value_t.undefined_bits_3_5, new_value_t.undefined_bits_3_5 };
    m_bit_details_model.bits.append(entry);
    entry = { "06: accept_ahb_wr_always:1",
              "AHB slave gizmo (memory controller) - Accept AHB write request always.\n1= always accept AHB write request without checking whether there is room in the queue to store the write data. Bypass Memory Controller AHB slave gizmo write queue.\n0 = accept AHB write request only when there’s enough room in the queue to store all the write data. Memory controller AHB slave gizmos write queue is used in this case;\n0 = ACCEPT_ON_CHECK;\n1 = ACCEPT_ON_NOCHECK",
              1, old_value_t.accept_ahb_wr_always, new_value_t.accept_ahb_wr_always };
    m_bit_details_model.bits.append(entry);
    entry = { "07: dont_split_ahb_wr:1",
              "AHB slave gizmo (memory controller) - don’t split AHB write transaction\n1 =  don’t split AHB write transaction ever. 0 (and enable_split=1) = allow AHB write transaction to be split;\n0 = ENABLE;\n1 = DISABLE",
              1, old_value_t.dont_split_ahb_wr, new_value_t.dont_split_ahb_wr };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_15:8", "", 8, old_value_t.undefined_bits_8_15, new_value_t.undefined_bits_8_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: max_ahb_burstsize:2",
              "AHB master gizmo (AHB-DMA) - Maximum allowed AHB burst size.\n00 = single transfer.\n01 = burst-of-4.\n10 = burst-of-8\n11 = burst-of-16;\n0 = DMA_BURST_1WORDS;\n1 = DMA_BURST_4WORDS;\n2 = DMA_BURST_8WORDS;\n3 = DMA_BURST_16WORDS",
              2, old_value_t.max_ahb_burstsize, new_value_t.max_ahb_burstsize };
    m_bit_details_model.bits.append(entry);
    entry = { "18: immediate:1",
              "AHB master gizmo (AHB-DMA) - Start AHB write request immediately\n1 = start the AHB write request immediately as soon as the device has put one write data in the AHB gizmos queue.\n0 = start the AHB write request only when all the write data has transferred from the device to the AHB gizmos queue;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.immediate, new_value_t.immediate };
    m_bit_details_model.bits.append(entry);
    entry = { "19: undefined_bits_19_23:5", "", 5, old_value_t.undefined_bits_19_23, new_value_t.undefined_bits_19_23 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: req_neg_cnt:8",
              "AHB master request negate count. This is an 8-bit counter used to indicate the minimum number of clk count between requests from this AHB master",
              8, old_value_t.req_neg_cnt, new_value_t.req_neg_cnt };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "AHB Master/Slave Gizmo Register\nGiven below is a description of each configuration field, what they are used for and the pros and cons of using them.\nNote:\n If the gizmo configuration bits are changed while the particular gizmo is transferring data, behavior of the system is non-deterministic.\nAHB gizmo configuration bit definition:\n(1) AHB Master Gizmo\n1. MAX_AHB_BURSTSIZE: Controls the maximum burst size that this gizmo can generate on the AHB bus. For the current system, this field should be set to burst-of-8.\n2. IMMEDIATE: Controls how quickly an AHB write request on the bus can start.\n- If 1, gizmo will start an AHB write request once the IP side provides one beat of data of a burst. For IP that can provide quick continuous burst data, this setting provides parallelism between AHB request and IP data transfer. However, for IP that cannot provide quick burst data, this setting will force this gizmo to hold the AHB bus longer, reducing bus efficiency.\n- If 0, gizmo will wait until all beats of data of a burst are provided before starting an AHB write request. With this setting, AHB bus efficiency is realized but IP latency and efficiency may be reduced.\n3. RD_DATA: Controls how read data will be returned from the gizmo to the IP side.\n- If 1, all betas of data of a burst have to be available before it indicates to the IP logic that read data is ready. This setting ensures there's no wait-state (bubble) between read data burst, but it will increase latency.\n- If 0, each beat of data of a burst will be sent from gizmo to the IP logic immediately. This setting will reduce latency, but can create non-consecutive data burst or bubble between data.\n4. REQ_NEG_CNT: Provides a way to limit (in terms of number of AHB bus clock) how fast/often this master can request the AHB bus. The bigger the number, the slower the rate of AHB request.\n(2) AHB Slave Gizmo\n1. ENABLE_SPLIT: Controls enabling the split feature of the AHB bus.\n- If 1, gizmo will always generate split response for a read. If ' DON’T_SPLIT_AHB_WR' is set to 0, gizmo also generates split response if it cannot accept write request from the AHB master anymore. This setting can increase AHB bus utilization since it allows other AHB masters to talk to other AHB slaves while this original AHB slave is fetching read data. However, the flip side is that it takes longer time for the original AHB master to get\nthe read data, because the original AHB master has to re-arbitrate for the AHB bus again in order to get to the data it asked for.\n- If 0, gizmo will not generate split response. Instead, it will hold on to the AHB bus until all the requested read data is returned back to the AHB master. This setting will reduce read latency to the master, but decrease AHB bus utilization.\n2. FORCE_TO_AHB_SINGLE: Controls how the gizmo treats the AHB master's burst request.\n- If 1, gizmo will break up the burst request internally into individual single word requests.\n- If 0, gizmo will burst request internally as burst request.\n3. ENB_FAST_REARBITRATE: Controls when the gizmo can allow the original read requested AHB master to re-arbitrate for the AHB bus again so the AHB master can retrieve the originally requested read data.\n- If 1, once first read data of a burst is in the slave gizmo's FIFO, it will allow the original AHB master to re-arbitrate, thus, allowing arbitration to happen in parallel with subsequent read data of a burst. However, if the data burst has wait-states or bubbles, then this setting will decrease AHB bus utilization because the slave gizmo will hold on to the AHB bus longer.\n- If 0, all read data of a burst must be in the slave gizmo's FIFO before it allows the original AHB master to re-arbitrate to retrieve the read data. This increases read data latency, and also increase AHB bus utilization.\n4. IP_WR_REQ_IMMEDIATE: Controls when gizmo will start write data request to the IP logic.\n- If 1, gizmo will start write request to the IP logic once it gets one write data of a burst from the AHB side. This setting will create non-consecutive/bubbles in a write data burst.\n- If 0, gizmo will start write request to the IP logic only when it gets all write data of a burst from the AHB side. This setting will create consecutive data burst (no bubbles or wait-states).\n5. MAX_IP_BURSTSIZE: Controls the maximum burst size that this gizmo can generate to the IP logic.\n6. ACCEPT_AHB_WR_ALWAYS: Controls how the slave gizmo will treat AHB write request.\n- If 1, gizmo will always accept a write request without checking whether it's FIFOs can accept the write or not. This setting can reduce bus utilization, but can reduce the rate of AHB retry.\n- If 0, gizmo will check its FIFOs to make sure they have room before accepting the AHB write request. This setting increase bus utilization, but can create a lot of AHB retry.\n7.  DON’T_SPLIT_AHB_WR: Controls whether to split AHB write request when the slave gizmo determines it cannot accept the write request.\n- If 1 and when ENABLE_SPLIT=1, gizmo will generate split for write if its FIFOs are not ready to accept the AHB write request or data. This setting can improve AHB bus utilization as there are no continuous AHB master retries on the bus.\n- If 0, gizmo will generate retry response for write if its FIFOs are not ready to accept the AHB write request. Software should leave this bit at 0 since this feature has not been proven.\nAHB Gizmo AHB-DMA/Memory Control Register";
}

#define APB_DMA_OFFSET 0x10
#define APB_DMA_UNDEFMASK 0x00F0FFFF
union apb_dma_u {
    struct {
        unsigned int undefined_bits_0_15:16;
        unsigned int max_ahb_burstsize:2;   /* AHB master gizmo - Maximum allowed AHB burst size. 00 = single transfer. 01 = burst-of-4. 10 = burst-of-8. 11 = burst-of-16; 0 = DMA_BURST_1WORDS; 1 = DMA_BURST_4WORDS; 2 = DMA_BURST_8WORDS; 3 = DMA_BURST_16WORDS */
        unsigned int immediate:1;           /* AHB master gizmo (AHB-DMA) - Start AHB write request immediately. 1 = start the AHB write request immediately as soon as the device has put one write data in the AHB gizmos queue. 0 = start the AHB write request only when all the write data has transferred from the device to the AHB gizmos queue; 0 = DISABLE; 1 = ENABLE */
        unsigned int rd_data:1;             /* AHB master gizmo - Pack all AHB read data. 1 = wait for all requested read data to be in the AHB gizmos queue before returning the data back to the IP. 0 = transfer each read data from the AHB to the IP immediately; 0 = NO_WAIT; 1 = WAIT */
        unsigned int undefined_bits_20_23:4;
        unsigned int req_neg_cnt:8;         /* AHB master request negate count. This is an 8-bit counter used to indicate the minimum number of clk count between requests from this AHB master */
    };

    u_int32_t reg32;
};

void GizmoDev::fill_apb_dma_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const apb_dma_u old_value_t = { .reg32 = value };
    const apb_dma_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_15:16", "", 16, old_value_t.undefined_bits_0_15, new_value_t.undefined_bits_0_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: max_ahb_burstsize:2",
              "AHB master gizmo - Maximum allowed AHB burst size.\n00 = single transfer.\n01 = burst-of-4.\n10 = burst-of-8.\n11 = burst-of-16;\n0 = DMA_BURST_1WORDS;\n1 = DMA_BURST_4WORDS;\n2 = DMA_BURST_8WORDS;\n3 = DMA_BURST_16WORDS",
              2, old_value_t.max_ahb_burstsize, new_value_t.max_ahb_burstsize };
    m_bit_details_model.bits.append(entry);
    entry = { "18: immediate:1",
              "AHB master gizmo (AHB-DMA) - Start AHB write request immediately.\n1 = start the AHB write request immediately as soon as the device has put one write data in the AHB gizmos queue.\n0 = start the AHB write request only when all the write data has transferred from the device to the AHB gizmos queue;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.immediate, new_value_t.immediate };
    m_bit_details_model.bits.append(entry);
    entry = { "19: rd_data:1",
              "AHB master gizmo - Pack all AHB read data.\n1 = wait for all requested read data to be in the AHB gizmos queue before returning the data back to the IP.\n0 = transfer each read data from the AHB to the IP immediately;\n0 = NO_WAIT;\n1 = WAIT",
              1, old_value_t.rd_data, new_value_t.rd_data };
    m_bit_details_model.bits.append(entry);
    entry = { "20: undefined_bits_20_23:4", "", 4, old_value_t.undefined_bits_20_23, new_value_t.undefined_bits_20_23 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: req_neg_cnt:8",
              "AHB master request negate count. This is an 8-bit counter used to indicate the minimum number of clk count between requests from this AHB master",
              8, old_value_t.req_neg_cnt, new_value_t.req_neg_cnt };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "AHB Gizmo APB-DMA Control Register";
}

#define IDE_OFFSET 0x18
#define IDE_UNDEFMASK 0x00F0FF00
union ide_u {
    struct {
        unsigned int enable_split:1;        /* AHB slave gizmo - Enable splitting AHB transactions. 1 = enable, 0 = disable; 0 = DISABLE; 1 = ENABLE */
        unsigned int force_to_ahb_single:1; /* AHB slave gizmo - Force all AHB transaction to single data request transaction. 1 = force to single data transaction always. 0 = don’t force to single data transaction; 0 = NOT_SINGLE_DATA; 1 = SINGLE_DATA */
        unsigned int enb_fast_rearbitrate:1;/* AHB slave gizmo - Enable fast re-arbitration. 1 = allow AHB master re-arbitration as soon as the device returns one read data into the gizmos queue.0 = allow AHB master re-arbitration only when the device returns all read data into the gizmos queue; 0 = DISABLE; 1 = ENABLE */
        unsigned int ip_wr_req_immediate:1; /* AHB slave gizmo Start write request to device immediately. 1 = start write request on the device side as soon as the AHB master puts data into the gizmos queue. 0 = start the device write request only when the AHB master has placed all write data into the gizmos queue */
        unsigned int max_ip_burstsize:2;    /* AHB slave gizmo Maximum allowed IP burst size. 00 = single transfer. 01 = burst-of-4. 10 = burst-of-8.11 = burst-of-16; 0 = DMA_BURST_1WORDS; 1 = DMA_BURST_4WORDS; 2 = DMA_BURST_8WORDS; 3 = DMA_BURST_16WORDS */
        unsigned int accept_ahb_wr_always:1;/* AHB slave gizmo - Accept AHB write request always. 1 = always accept AHB write request without checking whether there is room in the queue to store the write data. 0 = accept AHB write request only when there’s enough room in the queue to store all the write data; 0 = ACCEPT_ON_CHECK; 1 = ACCEPT_ON_NOCHECK */
        unsigned int dont_split_ahb_wr:1;   /* AHB slave gizmo - Dont split AHB write transaction.  1 = dont split AHB write transaction  ever. 0 (and enable_split=1) = allow AHB write  transaction to be split. */
        unsigned int undefined_bits_8_15:8;
        unsigned int max_ahb_burstsize:2;   /* AHB master gizmo - Maximum allowed AHB burst size. 00 = single transfer. 01 = burst-of-4. 10 = burst-of-8. 11 = burst-of-16; 0 = DMA_BURST_1WORDS; 1 = DMA_BURST_4WORDS; 2 = DMA_BURST_8WORDS; 3 = DMA_BURST_16WORDS */
        unsigned int immediate:1;           /* AHB master gizmo (AHB-DMA) - Start AHB write request immediately. 1 = start the AHB write request immediately as soon as the device has put one write data in the AHB gizmos queue. 0 = start the AHB write request only when all the write data has transferred from the device to the AHB gizmos queue; 0 = DISABLE; 1 = ENABLE */
        unsigned int rd_data:1;             /* AHB master gizmo - Pack all AHB read data. 1 = wait for all requested read data to be in the AHB gizmos queue before returning the data back to the IP. 0 = transfer each read data from the AHB to the IP immediately; 0 = NO_WAIT; 1 = WAIT */
        unsigned int undefined_bits_20_23:4;
        unsigned int req_neg_cnt:8;         /* AHB master request negate count. This is an 8-bit counter use to indicate the minimum number of clk count between requests from this AHB master */
    };

    u_int32_t reg32;
};

void GizmoDev::fill_ide_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const ide_u old_value_t = { .reg32 = value };
    const ide_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: enable_split:1",
              "AHB slave gizmo - Enable splitting AHB transactions.\n1 = enable,\n0 = disable;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.enable_split, new_value_t.enable_split };
    m_bit_details_model.bits.append(entry);
    entry = { "01: force_to_ahb_single:1",
              "AHB slave gizmo - Force all AHB transaction to single data request transaction.\n1 = force to single data transaction always.\n0 = don’t force to single data transaction;\n0 = NOT_SINGLE_DATA;\n1 = SINGLE_DATA",
              1, old_value_t.force_to_ahb_single, new_value_t.force_to_ahb_single };
    m_bit_details_model.bits.append(entry);
    entry = { "02: enb_fast_rearbitrate:1",
              "AHB slave gizmo - Enable fast re-arbitration.\n1 = allow AHB master re-arbitration as soon as the device returns one read data into the gizmos queue.\n0 = allow AHB master re-arbitration only when the device returns all read data into the gizmos queue;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.enb_fast_rearbitrate, new_value_t.enb_fast_rearbitrate };
    m_bit_details_model.bits.append(entry);
    entry = { "03: ip_wr_req_immediate:1",
              "AHB slave gizmo Start write request to device immediately.\n1 = start write request on the device side as soon as the AHB master puts data into the gizmos queue.\n0 = start the device write request only when the AHB master has placed all write data into the gizmos queue",
              1, old_value_t.ip_wr_req_immediate, new_value_t.ip_wr_req_immediate };
    m_bit_details_model.bits.append(entry);
    entry = { "04: max_ip_burstsize:2",
              "AHB slave gizmo Maximum allowed IP burst size.\n00 = single transfer.\n01 = burst-of-4.\n10 = burst-of-8.\n11 = burst-of-16;\n0 = DMA_BURST_1WORDS;\n1 = DMA_BURST_4WORDS;\n2 = DMA_BURST_8WORDS;\n3 = DMA_BURST_16WORDS",
              2, old_value_t.max_ip_burstsize, new_value_t.max_ip_burstsize };
    m_bit_details_model.bits.append(entry);
    entry = { "06: accept_ahb_wr_always:1",
              "AHB slave gizmo - Accept AHB write request always.\n1 = always accept AHB write request without checking whether there is room in the queue to store the write data.\n0 = accept AHB write request only when there’s enough room in the queue to store all the write data;\n0 = ACCEPT_ON_CHECK;\n1 = ACCEPT_ON_NOCHECK",
              1, old_value_t.accept_ahb_wr_always, new_value_t.accept_ahb_wr_always };
    m_bit_details_model.bits.append(entry);
    entry = { "07: dont_split_ahb_wr:1",
              "AHB slave gizmo - Dont split AHB write transaction.\n1 = dont split AHB write transaction  ever. 0 (and enable_split=1) = allow AHB write  transaction to be split.",
              1, old_value_t.dont_split_ahb_wr, new_value_t.dont_split_ahb_wr };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_15:8", "", 8, old_value_t.undefined_bits_8_15, new_value_t.undefined_bits_8_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: max_ahb_burstsize:2",
              "AHB master gizmo - Maximum allowed AHB burst size.\n00 = single transfer.\n01 = burst-of-4.\n10 = burst-of-8.\n11 = burst-of-16;\n0 = DMA_BURST_1WORDS;\n1 = DMA_BURST_4WORDS;\n2 = DMA_BURST_8WORDS;\n3 = DMA_BURST_16WORDS",
              2, old_value_t.max_ahb_burstsize, new_value_t.max_ahb_burstsize };
    m_bit_details_model.bits.append(entry);
    entry = { "18: immediate:1",
              "AHB master gizmo (AHB-DMA) - Start AHB write request immediately.\n1 = start the AHB write request immediately as soon as the device has put one write data in the AHB gizmos queue.\n0 = start the AHB write request only when all the write data has transferred from the device to the AHB gizmos queue;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.immediate, new_value_t.immediate };
    m_bit_details_model.bits.append(entry);
    entry = { "19: rd_data:1",
              "AHB master gizmo - Pack all AHB read data.\n1 = wait for all requested read data to be in the AHB gizmos queue before returning the data back to the IP.\n0 = transfer each read data from the AHB to the IP immediately;\n0 = NO_WAIT;\n1 = WAIT",
              1, old_value_t.rd_data, new_value_t.rd_data };
    m_bit_details_model.bits.append(entry);
    entry = { "20: undefined_bits_20_23:4", "", 4, old_value_t.undefined_bits_20_23, new_value_t.undefined_bits_20_23 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: req_neg_cnt:8",
              "AHB master request negate count. This is an 8-bit counter use to indicate the minimum number of clk count between requests from this AHB master",
              8, old_value_t.req_neg_cnt, new_value_t.req_neg_cnt };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "AHB Gizmo IDE Control Register";
}

#define USB_OFFSET 0x1C
#define USB_UNDEFMASK 0x00F0FF30
union usb_u {
    struct {
        unsigned int enable_split:1;        /* AHB slave gizmo - Enable splitting AHB transactions. 1 = enable 0 = disable; 0 = DISABLE; 1 = ENABLE */
        unsigned int force_to_ahb_single:1; /* AHB slave gizmo - Force all AHB transaction to single data request transaction. 1 = force to single data transaction always. 0 =  don’t force to single data transaction; 0 = NOT_SINGLE_DATA; 1 = SINGLE_DATA */
        unsigned int enb_fast_rearbitrate:1;/* AHB slave gizmo - Enable fast re-arbitration. 1 = allow AHB master re-arbitration as soon as the device returns one read data into the gizmos queue. 0 = allow AHB master re-arbitration only when the device returns all read data into the gizmos queue; 0 = DISABLE; 1 = ENABLE */
        unsigned int ip_wr_req_immediate:1; /* AHB slave gizmo Start write request to device immediately. 1 = start write request on the device side as soon as the AHB master puts data into the gizmos queue. 0 = start the device write request only when the AHB master has placed all write data into the gizmos queue; 0 = DISABLE; 1 = ENABLE */
        unsigned int undefined_bits_4_5:2;
        unsigned int accept_ahb_wr_always:1;/* AHB slave gizmo - Accept AHB write request always. 1 = always accept AHB write request without checking whether there is room in the queue to store the write data. 0 = accept AHB write request only when there’s enough room in the queue to store all the write data; 0 = ACCEPT_ON_CHECK; 1 = ACCEPT_ON_NOCHECK */
        unsigned int dont_split_ahb_wr:1;   /* AHB slave gizmo - Dont split AHB write transaction.  1 = dont split AHB write transaction  ever. 0 (and enable_split=1) = allow AHB write  transaction to be split. */
        unsigned int undefined_bits_8_15:8;
        unsigned int max_ahb_burstsize:2;   /* AHB master gizmo - Maximum allowed AHB burst size. 00 = single transfer. 01 = burst-of-4. 10 = burst-of-8. 11 = burst-of-16; 0 = DMA_BURST_1WORDS; 1 = DMA_BURST_4WORDS; 2 = DMA_BURST_8WORDS; 3 = DMA_BURST_16WORDS */
        unsigned int immediate:1;           /* AHB master gizmo (AHB-DMA) - Start AHB write request immediately. 1 = start the AHB write request immediately as soon as the device has put one write data in the AHB gizmos queue. 0 = start the AHB write request only when all the write data has transferred from the device to the AHB gizmos queue; 0 = DISABLE; 1 = ENABLE */
        unsigned int rd_data:1;             /* AHB master gizmo - Pack all AHB read data. 1 = wait for all requested read data to be in the AHB gizmos queue before returning the data back to the IP. 0 = transfer each read data from the AHB to the IP immediately; 0 = NO_WAIT; 1 = WAIT */
        unsigned int undefined_bits_20_23:4;
        unsigned int req_neg_cnt:8;         /* AHB master request negate count. This is an 8-bit counter used to indicate the minimum number of clk count between requests from this AHB master */
    };

    u_int32_t reg32;
};

void GizmoDev::fill_usb_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const usb_u old_value_t = { .reg32 = value };
    const usb_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: enable_split:1",
              "AHB slave gizmo - Enable splitting AHB transactions.\n1 = enable\n0 = disable;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.enable_split, new_value_t.enable_split };
    m_bit_details_model.bits.append(entry);
    entry = { "01: force_to_ahb_single:1",
              "AHB slave gizmo - Force all AHB transaction to single data request transaction.\n1 = force to single data transaction always.\n0 =  don’t force to single data transaction;\n0 = NOT_SINGLE_DATA;\n1 = SINGLE_DATA",
              1, old_value_t.force_to_ahb_single, new_value_t.force_to_ahb_single };
    m_bit_details_model.bits.append(entry);
    entry = { "02: enb_fast_rearbitrate:1",
              "AHB slave gizmo - Enable fast re-arbitration.\n1 = allow AHB master re-arbitration as soon as the device returns one read data into the gizmos queue.\n0 = allow AHB master re-arbitration only when the device returns all read data into the gizmos queue;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.enb_fast_rearbitrate, new_value_t.enb_fast_rearbitrate };
    m_bit_details_model.bits.append(entry);
    entry = { "03: ip_wr_req_immediate:1",
              "AHB slave gizmo Start write request to device immediately.\n1 = start write request on the device side as soon as the AHB master puts data into the gizmos queue.\n0 = start the device write request only when the AHB master has placed all write data into the gizmos queue;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.ip_wr_req_immediate, new_value_t.ip_wr_req_immediate };
    m_bit_details_model.bits.append(entry);
    entry = { "04: undefined_bits_4_5:2", "", 2, old_value_t.undefined_bits_4_5, new_value_t.undefined_bits_4_5 };
    m_bit_details_model.bits.append(entry);
    entry = { "06: accept_ahb_wr_always:1",
              "AHB slave gizmo - Accept AHB write request always.\n1 = always accept AHB write request without checking whether there is room in the queue to store the write data.\n0 = accept AHB write request only when there’s enough room in the queue to store all the write data;\n0 = ACCEPT_ON_CHECK;\n1 = ACCEPT_ON_NOCHECK",
              1, old_value_t.accept_ahb_wr_always, new_value_t.accept_ahb_wr_always };
    m_bit_details_model.bits.append(entry);
    entry = { "07: dont_split_ahb_wr:1",
              "AHB slave gizmo - Dont split AHB write transaction.\n1 = dont split AHB write transaction  ever. 0 (and enable_split=1) = allow AHB write  transaction to be split.",
              1, old_value_t.dont_split_ahb_wr, new_value_t.dont_split_ahb_wr };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_15:8", "", 8, old_value_t.undefined_bits_8_15, new_value_t.undefined_bits_8_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: max_ahb_burstsize:2",
              "AHB master gizmo - Maximum allowed AHB burst size.\n00 = single transfer.\n01 = burst-of-4.\n10 = burst-of-8.\n11 = burst-of-16;\n0 = DMA_BURST_1WORDS;\n1 = DMA_BURST_4WORDS;\n2 = DMA_BURST_8WORDS;\n3 = DMA_BURST_16WORDS",
              2, old_value_t.max_ahb_burstsize, new_value_t.max_ahb_burstsize };
    m_bit_details_model.bits.append(entry);
    entry = { "18: immediate:1",
              "AHB master gizmo (AHB-DMA) - Start AHB write request immediately.\n1 = start the AHB write request immediately as soon as the device has put one write data in the AHB gizmos queue.\n0 = start the AHB write request only when all the write data has transferred from the device to the AHB gizmos queue;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.immediate, new_value_t.immediate };
    m_bit_details_model.bits.append(entry);
    entry = { "19: rd_data:1",
              "AHB master gizmo - Pack all AHB read data.\n1 = wait for all requested read data to be in the AHB gizmos queue before returning the data back to the IP.\n0 = transfer each read data from the AHB to the IP immediately;\n0 = NO_WAIT;\n1 = WAIT",
              1, old_value_t.rd_data, new_value_t.rd_data };
    m_bit_details_model.bits.append(entry);
    entry = { "20: undefined_bits_20_23:4", "", 4, old_value_t.undefined_bits_20_23, new_value_t.undefined_bits_20_23 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: req_neg_cnt:8",
              "AHB master request negate count. This is an 8-bit counter used to indicate the minimum number of clk count between requests from this AHB master",
              8, old_value_t.req_neg_cnt, new_value_t.req_neg_cnt };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "AHB Gizmo USB Control Register";
}

#define AHB_XBAR_BRIDGE_OFFSET 0x20
#define AHB_XBAR_BRIDGE_UNDEFMASK 0xFFFFFF00
union ahb_xbar_bridge_u {
    struct {
        unsigned int enable_split:1;        /* AHB slave gizmo - Enable splitting AHB transactions. 1 = enable 0 = disable; 0 = DISABLE; 1 = ENABLE */
        unsigned int force_to_ahb_single:1; /* AHB slave gizmo - Force all AHB transaction to single data request transaction. 1 = force to single data transaction always. 0 = don’t force to single data transaction; 0 = NOT_SINGLE_DATA; 1 = SINGLE_DATA */
        unsigned int enb_fast_rearbitrate:1;/* AHB slave gizmo - Enable fast re-arbitration. 1 = allow AHB master re-arbitration as soon as the device returns one read data into the gizmos queue. 0 = allow AHB master re-arbitration only when the device returns all read data into the gizmos queue; 0 = DISABLE; 1 = ENABLE */
        unsigned int immediate:1;           /* AHB slave gizmo - Start write request to device immediately. 1 = start write request on the device side as soon as the AHB master puts data into the gizmos queue. 0 = start the device write request only when the AHB master has placed all write data into the gizmos queue; 0 = DISABLE; 1 = ENABLE */
        unsigned int max_ip_burstsize:2;    /* AHB slave gizmo - Maximum allowed IP burst size. 00 = single transfer. 01 = burst-of-4. 10 = burst-of-8. 11 = burst-of-16; 0 = DMA_BURST_1WORDS; 1 = DMA_BURST_4WORDS; 2 = DMA_BURST_8WORDS; 3 = DMA_BURST_16WORDS */
        unsigned int accept_ahb_wr_always:1;/* AHB slave gizmo - Accept AHB write request always. 1 = always accept AHB write request without checking whether there is room in the queue to store the write data. 0 = accept AHB write request only when there’s enough room in the queue to store all the write data; 0 = ACCEPT_ON_CHECK; 1 = ACCEPT_ON_NOCHECK */
        unsigned int dont_split_ahb_wr:1;   /* AHB slave gizmo - Dont split AHB write transaction.  1 = dont split AHB write transaction ever.  0 (and enable_split=1) = allow AHB write  transaction to be split. */
        unsigned int undefined_bits_8_31:24;
    };

    u_int32_t reg32;
};

void GizmoDev::fill_ahb_xbar_bridge_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const ahb_xbar_bridge_u old_value_t = { .reg32 = value };
    const ahb_xbar_bridge_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: enable_split:1",
              "AHB slave gizmo - Enable splitting AHB transactions.\n1 = enable\n0 = disable;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.enable_split, new_value_t.enable_split };
    m_bit_details_model.bits.append(entry);
    entry = { "01: force_to_ahb_single:1",
              "AHB slave gizmo - Force all AHB transaction to single data request transaction.\n1 = force to single data transaction always.\n0 = don’t force to single data transaction;\n0 = NOT_SINGLE_DATA;\n1 = SINGLE_DATA",
              1, old_value_t.force_to_ahb_single, new_value_t.force_to_ahb_single };
    m_bit_details_model.bits.append(entry);
    entry = { "02: enb_fast_rearbitrate:1",
              "AHB slave gizmo - Enable fast re-arbitration.\n1 = allow AHB master re-arbitration as soon as the device returns one read data into the gizmos queue.\n0 = allow AHB master re-arbitration only when the device returns all read data into the gizmos queue;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.enb_fast_rearbitrate, new_value_t.enb_fast_rearbitrate };
    m_bit_details_model.bits.append(entry);
    entry = { "03: immediate:1",
              "AHB slave gizmo - Start write request to device immediately.\n1 = start write request on the device side as soon as the AHB master puts data into the gizmos queue.\n0 = start the device write request only when the AHB master has placed all write data into the gizmos queue;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.immediate, new_value_t.immediate };
    m_bit_details_model.bits.append(entry);
    entry = { "04: max_ip_burstsize:2",
              "AHB slave gizmo - Maximum allowed IP burst size.\n00 = single transfer.\n01 = burst-of-4.\n10 = burst-of-8.\n11 = burst-of-16;\n0 = DMA_BURST_1WORDS;\n1 = DMA_BURST_4WORDS;\n2 = DMA_BURST_8WORDS;\n3 = DMA_BURST_16WORDS",
              2, old_value_t.max_ip_burstsize, new_value_t.max_ip_burstsize };
    m_bit_details_model.bits.append(entry);
    entry = { "06: accept_ahb_wr_always:1",
              "AHB slave gizmo - Accept AHB write request always.\n1 = always accept AHB write request without checking whether there is room in the queue to store the write data.\n0 = accept AHB write request only when there’s enough room in the queue to store all the write data;\n0 = ACCEPT_ON_CHECK;\n1 = ACCEPT_ON_NOCHECK",
              1, old_value_t.accept_ahb_wr_always, new_value_t.accept_ahb_wr_always };
    m_bit_details_model.bits.append(entry);
    entry = { "07: dont_split_ahb_wr:1",
              "AHB slave gizmo - Dont split AHB write transaction.\n1 = dont split AHB write transaction ever.  0 (and enable_split=1) = allow AHB write  transaction to be split.",
              1, old_value_t.dont_split_ahb_wr, new_value_t.dont_split_ahb_wr };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_31:24", "", 24, old_value_t.undefined_bits_8_31, new_value_t.undefined_bits_8_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "AHB Gizmo AHB XBAR Bridge Control Register";
}

#define CPU_AHB_BRIDGE_OFFSET 0x24
#define CPU_AHB_BRIDGE_UNDEFMASK 0x00F0FFFF
union cpu_ahb_bridge_u {
    struct {
        unsigned int undefined_bits_0_15:16;
        unsigned int max_ahb_burstsize:2;   /* AHB master gizmo - Maximum allowed AHB burst size. 00 = single transfer. 01 = burst-of-4. 10 = burst-of-8. 11 = burst-of-16; 0 = DMA_BURST_1WORDS; 1 = DMA_BURST_4WORDS; 2 = DMA_BURST_8WORDS; 3 = DMA_BURST_16WORDS */
        unsigned int immediate:1;           /* AHB master gizmo (AHB-DMA) - Start AHB write request immediately. 1 = start the AHB write request immediately as soon as the device has put one write data in the AHB gizmos queue. 0 = start the AHB write request only when all the write data has transferred from the device to the AHB gizmos queue; 0 = DISABLE; 1 = ENABLE */
        unsigned int rd_data:1;             /* AHB master gizmo - Pack all AHB read data. 1 = wait for all requested read data to be in the AHB gizmos queue before returning the data back to the IP. 0 = transfer each read data from the AHB to the IP immediately; 0 = NO_WAIT; 1 = WAIT */
        unsigned int undefined_bits_20_23:4;
        unsigned int req_neg_cnt:8;         /* AHB master request negate count. This is an 8-bit counter use to indicate the minimum number of clk count between requests from this AHB master */
    };

    u_int32_t reg32;
};

void GizmoDev::fill_cpu_ahb_bridge_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const cpu_ahb_bridge_u old_value_t = { .reg32 = value };
    const cpu_ahb_bridge_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_15:16", "", 16, old_value_t.undefined_bits_0_15, new_value_t.undefined_bits_0_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: max_ahb_burstsize:2",
              "AHB master gizmo - Maximum allowed AHB burst size.\n00 = single transfer.\n01 = burst-of-4.\n10 = burst-of-8.\n11 = burst-of-16;\n0 = DMA_BURST_1WORDS;\n1 = DMA_BURST_4WORDS;\n2 = DMA_BURST_8WORDS;\n3 = DMA_BURST_16WORDS",
              2, old_value_t.max_ahb_burstsize, new_value_t.max_ahb_burstsize };
    m_bit_details_model.bits.append(entry);
    entry = { "18: immediate:1",
              "AHB master gizmo (AHB-DMA) - Start AHB write request immediately.\n1 = start the AHB write request immediately as soon as the device has put one write data in the AHB gizmos queue.\n0 = start the AHB write request only when all the write data has transferred from the device to the AHB gizmos queue;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.immediate, new_value_t.immediate };
    m_bit_details_model.bits.append(entry);
    entry = { "19: rd_data:1",
              "AHB master gizmo - Pack all AHB read data.\n1 = wait for all requested read data to be in the AHB gizmos queue before returning the data back to the IP.\n0 = transfer each read data from the AHB to the IP immediately;\n0 = NO_WAIT;\n1 = WAIT",
              1, old_value_t.rd_data, new_value_t.rd_data };
    m_bit_details_model.bits.append(entry);
    entry = { "20: undefined_bits_20_23:4", "", 4, old_value_t.undefined_bits_20_23, new_value_t.undefined_bits_20_23 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: req_neg_cnt:8",
              "AHB master request negate count. This is an 8-bit counter use to indicate the minimum number of clk count between requests from this AHB master",
              8, old_value_t.req_neg_cnt, new_value_t.req_neg_cnt };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "AHB Gizmo CPU AHB Bridge Control Register";
}

#define COP_AHB_BRIDGE_OFFSET 0x28
#define COP_AHB_BRIDGE_UNDEFMASK 0x00F0FFFF
union cop_ahb_bridge_u {
    struct {
        unsigned int undefined_bits_0_15:16;
        unsigned int max_ahb_burstsize:2;   /* AHB master gizmo - Maximum allowed AHB burst size. 00 = single transfer. 01 = burst-of-4. 10 = burst-of-8. 11 = burst-of-16; 0 = DMA_BURST_1WORDS; 1 = DMA_BURST_4WORDS; 2 = DMA_BURST_8WORDS; 3 = DMA_BURST_16WORDS */
        unsigned int immediate:1;           /* AHB master gizmo (AHB-DMA) - Start AHB write request immediately. 1 = start the AHB write request immediately as soon as the device has put one write data in the AHB gizmos queue. 0 = start the AHB write request only when all the write data has transferred from the device to the AHB gizmos queue; 0 = DISABLE; 1 = ENABLE */
        unsigned int rd_data:1;             /* AHB master gizmo - Pack all AHB read data. 1 = wait for all requested read data to be in the AHB gizmos queue before returning the data back to the IP. 0 = transfer each read data from the AHB to the IP immediately; 0 = NO_WAIT; 1 = WAIT */
        unsigned int undefined_bits_20_23:4;
        unsigned int req_neg_cnt:8;         /* AHB master request negate count. This is an 8-bit counter use to indicate the minimum number of clk count between requests from this AHB master */
    };

    u_int32_t reg32;
};

void GizmoDev::fill_cop_ahb_bridge_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const cop_ahb_bridge_u old_value_t = { .reg32 = value };
    const cop_ahb_bridge_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_15:16", "", 16, old_value_t.undefined_bits_0_15, new_value_t.undefined_bits_0_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: max_ahb_burstsize:2",
              "AHB master gizmo - Maximum allowed AHB burst size.\n00 = single transfer.\n01 = burst-of-4.\n10 = burst-of-8.\n11 = burst-of-16;\n0 = DMA_BURST_1WORDS;\n1 = DMA_BURST_4WORDS;\n2 = DMA_BURST_8WORDS;\n3 = DMA_BURST_16WORDS",
              2, old_value_t.max_ahb_burstsize, new_value_t.max_ahb_burstsize };
    m_bit_details_model.bits.append(entry);
    entry = { "18: immediate:1",
              "AHB master gizmo (AHB-DMA) - Start AHB write request immediately.\n1 = start the AHB write request immediately as soon as the device has put one write data in the AHB gizmos queue.\n0 = start the AHB write request only when all the write data has transferred from the device to the AHB gizmos queue;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.immediate, new_value_t.immediate };
    m_bit_details_model.bits.append(entry);
    entry = { "19: rd_data:1",
              "AHB master gizmo - Pack all AHB read data.\n1 = wait for all requested read data to be in the AHB gizmos queue before returning the data back to the IP.\n0 = transfer each read data from the AHB to the IP immediately;\n0 = NO_WAIT;\n1 = WAIT",
              1, old_value_t.rd_data, new_value_t.rd_data };
    m_bit_details_model.bits.append(entry);
    entry = { "20: undefined_bits_20_23:4", "", 4, old_value_t.undefined_bits_20_23, new_value_t.undefined_bits_20_23 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: req_neg_cnt:8",
              "AHB master request negate count. This is an 8-bit counter use to indicate the minimum number of clk count between requests from this AHB master",
              8, old_value_t.req_neg_cnt, new_value_t.req_neg_cnt };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "AHB Gizmo COP AHB Bridge Control Register";
}

#define XBAR_APB_CTLR_OFFSET 0x2C
#define XBAR_APB_CTLR_UNDEFMASK 0xFFFFFFC7
union xbar_apb_ctlr_u {
    struct {
        unsigned int undefined_bits_0_2:3;
        unsigned int immediate:1;           /* AHB slave gizmo - Start write request to device immediately. 1 = start write request on the device side as soon as the AHB master puts data into the gizmos queue. 0 = start the device write request only when the AHB master has placed all write data into the gizmos queue; 0 = DISABLE; 1 = ENABLE */
        unsigned int max_ip_burstsize:2;    /* AHB slave gizmo - Maximum allowed IP burst size. 00 = single transfer. 01 = burst-of-4. 10 = burst-of-8. 11 = burst-of-16; 0 = DMA_BURST_1WORDS; 1 = DMA_BURST_4WORDS; 2 = DMA_BURST_8WORDS; 3 = DMA_BURST_16WORDS */
        unsigned int undefined_bits_6_31:26;
    };

    u_int32_t reg32;
};

void GizmoDev::fill_xbar_apb_ctlr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const xbar_apb_ctlr_u old_value_t = { .reg32 = value };
    const xbar_apb_ctlr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_2:3", "", 3, old_value_t.undefined_bits_0_2, new_value_t.undefined_bits_0_2 };
    m_bit_details_model.bits.append(entry);
    entry = { "03: immediate:1",
              "AHB slave gizmo - Start write request to device immediately.\n1 = start write request on the device side as soon as the AHB master puts data into the gizmos queue.\n0 = start the device write request only when the AHB master has placed all write data into the gizmos queue;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.immediate, new_value_t.immediate };
    m_bit_details_model.bits.append(entry);
    entry = { "04: max_ip_burstsize:2",
              "AHB slave gizmo - Maximum allowed IP burst size.\n00 = single transfer.\n01 = burst-of-4.\n10 = burst-of-8.\n11 = burst-of-16;\n0 = DMA_BURST_1WORDS;\n1 = DMA_BURST_4WORDS;\n2 = DMA_BURST_8WORDS;\n3 = DMA_BURST_16WORDS",
              2, old_value_t.max_ip_burstsize, new_value_t.max_ip_burstsize };
    m_bit_details_model.bits.append(entry);
    entry = { "06: undefined_bits_6_31:26", "", 26, old_value_t.undefined_bits_6_31, new_value_t.undefined_bits_6_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "AHB Gizmo XBAR APB Control Register";
}

#define VCP_AHB_BRIDGE_OFFSET 0x30
#define VCP_AHB_BRIDGE_UNDEFMASK 0x00F0FFFF
union vcp_ahb_bridge_u {
    struct {
        unsigned int undefined_bits_0_15:16;
        unsigned int max_ahb_burstsize:2;   /* AHB master gizmo - Maximum allowed AHB burst size. 00 = single transfer. 01 = burst-of-4. 10 = burst-of-8. 11 = burst-of-16. 0 = DMA_BURST_1WORDS 1 = DMA_BURST_4WORDS 2 = DMA_BURST_8WORDS 3 = DMA_BURST_16WORDS */
        unsigned int immediate:1;           /* AHB master gizmo (AHB-DMA) - Start AHB write request immediately. 1 = start the AHB write request immediately as soon as the device has put one write data in the AHB gizmos queue. 0 = start the AHB write request only when all the write data has transferred from the device to the AHB gizmos queue. 0 = DISABLE 1 = ENABLE */
        unsigned int rd_data:1;             /* AHB master gizmo - Pack all AHB read data. 1 = wait for all requested read data to be in the AHB gizmos queue before returning the data back to the IP. 0 = transfer each read data from the AHB to the IP immediately. 0 = NO_WAIT 1 = WAIT */
        unsigned int undefined_bits_20_23:4;
        unsigned int req_neg_cnt:8;         /* AHB master request negate count. This is an 8-bit counter use to indicate the minimum number of clk count between requests from this AHB master */
    };

    u_int32_t reg32;
};

void GizmoDev::fill_vcp_ahb_bridge_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const vcp_ahb_bridge_u old_value_t = { .reg32 = value };
    const vcp_ahb_bridge_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_15:16", "", 16, old_value_t.undefined_bits_0_15, new_value_t.undefined_bits_0_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: max_ahb_burstsize:2",
              "AHB master gizmo - Maximum allowed AHB burst size.\n00 = single transfer.\n01 = burst-of-4.\n10 = burst-of-8.\n11 = burst-of-16.\n0 = DMA_BURST_1WORDS\n1 = DMA_BURST_4WORDS\n2 = DMA_BURST_8WORDS\n3 = DMA_BURST_16WORDS",
              2, old_value_t.max_ahb_burstsize, new_value_t.max_ahb_burstsize };
    m_bit_details_model.bits.append(entry);
    entry = { "18: immediate:1",
              "AHB master gizmo (AHB-DMA) - Start AHB write request immediately.\n1 = start the AHB write request immediately as soon as the device has put one write data in the AHB gizmos queue.\n0 = start the AHB write request only when all the write data has transferred from the device to the AHB gizmos queue.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.immediate, new_value_t.immediate };
    m_bit_details_model.bits.append(entry);
    entry = { "19: rd_data:1",
              "AHB master gizmo - Pack all AHB read data.\n1 = wait for all requested read data to be in the AHB gizmos queue before returning the data back to the IP.\n0 = transfer each read data from the AHB to the IP immediately.\n0 = NO_WAIT\n1 = WAIT",
              1, old_value_t.rd_data, new_value_t.rd_data };
    m_bit_details_model.bits.append(entry);
    entry = { "20: undefined_bits_20_23:4", "", 4, old_value_t.undefined_bits_20_23, new_value_t.undefined_bits_20_23 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: req_neg_cnt:8",
              "AHB master request negate count. This is an 8-bit counter use to indicate the minimum number of clk count between requests from this AHB master",
              8, old_value_t.req_neg_cnt, new_value_t.req_neg_cnt };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "AHB Gizmo VCP AHB Bridge Control Register";
}

#define NAND_OFFSET 0x3C
#define NAND_UNDEFMASK 0x00F0FFFF
union nand_u {
    struct {
        unsigned int undefined_bits_0_15:16;
        unsigned int max_ahb_burstsize:2;   /* AHB master gizmo - Maximum allowed AHB burst size. 00 = single transfer. 01 = burst-of-4. 10 = burst-of-8. 11 = burst-of-16; 0 = DMA_BURST_1WORDS; 1 = DMA_BURST_4WORDS; 2 = DMA_BURST_8WORDS; 3 = DMA_BURST_16WORDS */
        unsigned int immediate:1;           /* AHB master gizmo (AHB-DMA) - Start AHB write request immediately. 1 = start the AHB write request immediately as soon as the device has put one write data in the AHB gizmos queue. 0 = start the AHB write request only when all the write data has transferred from the device to the AHB gizmos queue; 0 = DISABLE; 1 = ENABLE */
        unsigned int rd_data:1;             /* AHB master gizmo - Pack all AHB read data. 1 = wait for all requested read data to be in the AHB gizmos queue before returning the data back to the IP. 0 = transfer each read data from the AHB to the IP immediately; 0 = NO_WAIT; 1 = WAIT */
        unsigned int undefined_bits_20_23:4;
        unsigned int req_neg_cnt:8;         /* AHB master request negate count. This is an 8-bit counter use to indicate the minimum number of clk count between requests from this AHB master */
    };

    u_int32_t reg32;
};

void GizmoDev::fill_nand_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const nand_u old_value_t = { .reg32 = value };
    const nand_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_15:16", "", 16, old_value_t.undefined_bits_0_15, new_value_t.undefined_bits_0_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: max_ahb_burstsize:2",
              "AHB master gizmo - Maximum allowed AHB burst size.\n00 = single transfer.\n01 = burst-of-4.\n10 = burst-of-8.\n11 = burst-of-16;\n0 = DMA_BURST_1WORDS;\n1 = DMA_BURST_4WORDS;\n2 = DMA_BURST_8WORDS;\n3 = DMA_BURST_16WORDS",
              2, old_value_t.max_ahb_burstsize, new_value_t.max_ahb_burstsize };
    m_bit_details_model.bits.append(entry);
    entry = { "18: immediate:1",
              "AHB master gizmo (AHB-DMA) - Start AHB write request immediately.\n1 = start the AHB write request immediately as soon as the device has put one write data in the AHB gizmos queue.\n0 = start the AHB write request only when all the write data has transferred from the device to the AHB gizmos queue;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.immediate, new_value_t.immediate };
    m_bit_details_model.bits.append(entry);
    entry = { "19: rd_data:1",
              "AHB master gizmo - Pack all AHB read data.\n1 = wait for all requested read data to be in the AHB gizmos queue before returning the data back to the IP.\n0 = transfer each read data from the AHB to the IP immediately;\n0 = NO_WAIT;\n1 = WAIT",
              1, old_value_t.rd_data, new_value_t.rd_data };
    m_bit_details_model.bits.append(entry);
    entry = { "20: undefined_bits_20_23:4", "", 4, old_value_t.undefined_bits_20_23, new_value_t.undefined_bits_20_23 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: req_neg_cnt:8",
              "AHB master request negate count. This is an 8-bit counter use to indicate the minimum number of clk count between requests from this AHB master",
              8, old_value_t.req_neg_cnt, new_value_t.req_neg_cnt };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "AHB Gizmo NAND Control Register";
}

#define SDMMC4_OFFSET 0x44
#define SDMMC4_UNDEFMASK 0x00F8FF38
union sdmmc4_u {
    struct {
        unsigned int enable_split:1;        /* AHB slave gizmo - Enable splitting AHB transactions. 1 = enable 0 = disable 0 = DISABLE 1 = ENABLE */
        unsigned int force_to_ahb_single:1; /* AHB slave gizmo - Force all AHB transaction to single data request transaction. 1 = force to single data transaction always. 0 = don’t force to single data transaction. 0 = NOT_SINGLE_DATA 1 = SINGLE_DATA */
        unsigned int enb_fast_rearbitrate:1;/* AHB slave gizmo - Enable fast re-arbitration. 1 = allow AHB master re-arbitration as soon as the device returns one read data into the gizmos queue. 0 = allow AHB master re-arbitration only when the device returns all read data into the gizmos queue. 0 = DISABLE; 0 = DISABLE; 1 = ENABLE */
        unsigned int undefined_bits_3_5:3;
        unsigned int accept_ahb_wr_always:1;/* AHB slave gizmo - Accept AHB write request always. 1 = always accept AHB write request without checking whether there is room in the queue to store the write data. 0 = accept AHB write request only when there’s enough room in the queue to store all the write data. 0 = ACCEPT_ON_CHECK 1 = ACCEPT_ON_NOCHECK */
        unsigned int dont_split_ahb_wr:1;   /* AHB slave gizmo - Dont split AHB write transaction. 1 = dont split AHB write transaction ever. 0 (and enable_split=1) = allow AHB write transaction to be split. 0 = ENABLE 1 = DISABLE */
        unsigned int undefined_bits_8_15:8;
        unsigned int max_ahb_burstsize:2;   /* AHB master gizmo - Maximum allowed AHB burst size. 00 = single transfer. 01 = burst-of-4. 10 = burst-of-8. 11 = burst-of-16. 0 = DMA_BURST_1WORDS 1 = DMA_BURST_4WORDS 2 = DMA_BURST_8WORDS 3 = DMA_BURST_16WORDS */
        unsigned int immediate:1;           /* AHB master gizmo - Start AHB write request immediately. 1 = start the AHB write request immediately as soon as the device puts data in the AHB gizmos queue. 0 = start the AHB write request only when all the write data has transferred from the device to the AHB gizmos queue. 0 = DISABLE 1 = ENABLE */
        unsigned int undefined_bits_19_23:5;
        unsigned int req_neg_cnt:8;         /* AHB master request negate count. This is an 8-bit counter use to indicate the minimum number of clk count between requests from this AHB master */
    };

    u_int32_t reg32;
};

void GizmoDev::fill_sdmmc4_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const sdmmc4_u old_value_t = { .reg32 = value };
    const sdmmc4_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: enable_split:1",
              "AHB slave gizmo - Enable splitting AHB transactions.\n1 = enable\n0 = disable\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.enable_split, new_value_t.enable_split };
    m_bit_details_model.bits.append(entry);
    entry = { "01: force_to_ahb_single:1",
              "AHB slave gizmo - Force all AHB transaction to single data request transaction.\n1 = force to single data transaction always.\n0 = don’t force to single data transaction.\n0 = NOT_SINGLE_DATA\n1 = SINGLE_DATA",
              1, old_value_t.force_to_ahb_single, new_value_t.force_to_ahb_single };
    m_bit_details_model.bits.append(entry);
    entry = { "02: enb_fast_rearbitrate:1",
              "AHB slave gizmo - Enable fast re-arbitration.\n1 = allow AHB master re-arbitration as soon as the device returns one read data into the gizmos queue.\n0 = allow AHB master re-arbitration only when the device returns all read data into the gizmos queue.\n0 = DISABLE;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.enb_fast_rearbitrate, new_value_t.enb_fast_rearbitrate };
    m_bit_details_model.bits.append(entry);
    entry = { "03: undefined_bits_3_5:3", "", 3, old_value_t.undefined_bits_3_5, new_value_t.undefined_bits_3_5 };
    m_bit_details_model.bits.append(entry);
    entry = { "06: accept_ahb_wr_always:1",
              "AHB slave gizmo - Accept AHB write request always.\n1 = always accept AHB write request without checking whether there is room in the queue to store the write data.\n0 = accept AHB write request only when there’s enough room in the queue to store all the write data.\n0 = ACCEPT_ON_CHECK\n1 = ACCEPT_ON_NOCHECK",
              1, old_value_t.accept_ahb_wr_always, new_value_t.accept_ahb_wr_always };
    m_bit_details_model.bits.append(entry);
    entry = { "07: dont_split_ahb_wr:1",
              "AHB slave gizmo - Dont split AHB write transaction.\n1 = dont split AHB write transaction ever. 0 (and enable_split=1) = allow AHB write transaction to be split.\n0 = ENABLE\n1 = DISABLE",
              1, old_value_t.dont_split_ahb_wr, new_value_t.dont_split_ahb_wr };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_15:8", "", 8, old_value_t.undefined_bits_8_15, new_value_t.undefined_bits_8_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: max_ahb_burstsize:2",
              "AHB master gizmo - Maximum allowed AHB burst size.\n00 = single transfer.\n01 = burst-of-4.\n10 = burst-of-8.\n11 = burst-of-16.\n0 = DMA_BURST_1WORDS\n1 = DMA_BURST_4WORDS\n2 = DMA_BURST_8WORDS\n3 = DMA_BURST_16WORDS",
              2, old_value_t.max_ahb_burstsize, new_value_t.max_ahb_burstsize };
    m_bit_details_model.bits.append(entry);
    entry = { "18: immediate:1",
              "AHB master gizmo - Start AHB write request immediately.\n1 = start the AHB write request immediately as soon as the device puts data in the AHB gizmos queue.\n0 = start the AHB write request only when all the write data has transferred from the device to the AHB gizmos queue.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.immediate, new_value_t.immediate };
    m_bit_details_model.bits.append(entry);
    entry = { "19: undefined_bits_19_23:5", "", 5, old_value_t.undefined_bits_19_23, new_value_t.undefined_bits_19_23 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: req_neg_cnt:8",
              "AHB master request negate count. This is an 8-bit counter use to indicate the minimum number of clk count between requests from this AHB master",
              8, old_value_t.req_neg_cnt, new_value_t.req_neg_cnt };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "This is now SDMMC4 master gizmo configuration\nAHB Gizmo SDMMC4 Control Register";
}

#define XIO_OFFSET 0x48
#define XIO_UNDEFMASK 0x00F0FFFF
union xio_u {
    struct {
        unsigned int undefined_bits_0_15:16;
        unsigned int max_ahb_burstsize:2;   /* AHB master gizmo - Maximum allowed AHB burst size. 00 = single transfer. 01 = burst-of-4. 10 = burst-of-8. 11 = burst-of-16. 0 = DMA_BURST_1WORDS 1 = DMA_BURST_4WORDS 2 = DMA_BURST_8WORDS 3 = DMA_BURST_16WORDS */
        unsigned int immediate:1;           /* AHB master gizmo (AHB-DMA) - Start AHB write request immediately. 1 = start the AHB write request immediately as soon as the device has put one write data in the AHB gizmos queue. 0 = start the AHB write request only when all the write data has transferred from the device to the AHB gizmos queue. 0 = DISABLE 1 = ENABLE */
        unsigned int rd_data:1;             /* AHB master gizmo - Pack all AHB read data. 1 = wait for all requested read data to be in the AHB gizmos queue before returning the data back to the IP. 0 = transfer each read data from the AHB to the IP immediately. 0 = NO_WAIT 1 = WAIT */
        unsigned int undefined_bits_20_23:4;
        unsigned int req_neg_cnt:8;         /* AHB master request negate count. This is an 8-bit counter use to indicate the minimum number of clk count between requests from this AHB master */
    };

    u_int32_t reg32;
};

void GizmoDev::fill_xio_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const xio_u old_value_t = { .reg32 = value };
    const xio_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_15:16", "", 16, old_value_t.undefined_bits_0_15, new_value_t.undefined_bits_0_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: max_ahb_burstsize:2",
              "AHB master gizmo - Maximum allowed AHB burst size.\n00 = single transfer.\n01 = burst-of-4.\n10 = burst-of-8.\n11 = burst-of-16.\n0 = DMA_BURST_1WORDS\n1 = DMA_BURST_4WORDS\n2 = DMA_BURST_8WORDS\n3 = DMA_BURST_16WORDS",
              2, old_value_t.max_ahb_burstsize, new_value_t.max_ahb_burstsize };
    m_bit_details_model.bits.append(entry);
    entry = { "18: immediate:1",
              "AHB master gizmo (AHB-DMA) - Start AHB write request immediately.\n1 = start the AHB write request immediately as soon as the device has put one write data in the AHB gizmos queue.\n0 = start the AHB write request only when all the write data has transferred from the device to the AHB gizmos queue.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.immediate, new_value_t.immediate };
    m_bit_details_model.bits.append(entry);
    entry = { "19: rd_data:1",
              "AHB master gizmo - Pack all AHB read data.\n1 = wait for all requested read data to be in the AHB gizmos queue before returning the data back to the IP.\n0 = transfer each read data from the AHB to the IP immediately.\n0 = NO_WAIT\n1 = WAIT",
              1, old_value_t.rd_data, new_value_t.rd_data };
    m_bit_details_model.bits.append(entry);
    entry = { "20: undefined_bits_20_23:4", "", 4, old_value_t.undefined_bits_20_23, new_value_t.undefined_bits_20_23 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: req_neg_cnt:8",
              "AHB master request negate count. This is an 8-bit counter use to indicate the minimum number of clk count between requests from this AHB master",
              8, old_value_t.req_neg_cnt, new_value_t.req_neg_cnt };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "AHB Gizmo XIO Control Register";
}

#define BSEV_OFFSET 0x60
#define BSEV_UNDEFMASK 0x00F0FFFF
union bsev_u {
    struct {
        unsigned int undefined_bits_0_15:16;
        unsigned int max_ahb_burstsize:2;   /* AHB master gizmo - Maximum allowed AHB burst size. 00 = single transfer. 01 = burst-of-4. 10 = burst-of-8 11 = burst-of-16; 0 = DMA_BURST_1WORDS; 1 = DMA_BURST_4WORDS; 2 = DMA_BURST_8WORDS; 3 = DMA_BURST_16WORDS */
        unsigned int immediate:1;           /* AHB master gizmo (AHB-DMA) - Start AHB write request immediately. 1 = start the AHB write request immediately as soon as the device has put one write data in the AHB gizmos queue. 0 = start the AHB write request only when all the write data has transferred from the device to the AHB gizmos queue. NOTE: THIS SHOULD NEVER BE SET TO ENABLE (BSEV requires this bit to be 0); 0 = DISABLE; 1 = ENABLE */
        unsigned int rd_data:1;             /* AHB master gizmo - Pack all AHB read data. 1 = wait for all requested read data to be in the AHB gizmos queue before returning the data back to the IP. 0 = transfer each read data from the AHB to the IP immediately; 0 = NO_WAIT; 1 = WAIT */
        unsigned int undefined_bits_20_23:4;
        unsigned int req_neg_cnt:8;         /* AHB master request negate count. This is an 8-bit counter use to indicate the minimum number of clk count between requests from this AHB master */
    };

    u_int32_t reg32;
};

void GizmoDev::fill_bsev_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const bsev_u old_value_t = { .reg32 = value };
    const bsev_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_15:16", "", 16, old_value_t.undefined_bits_0_15, new_value_t.undefined_bits_0_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: max_ahb_burstsize:2",
              "AHB master gizmo - Maximum allowed AHB burst size.\n00 = single transfer.\n01 = burst-of-4.\n10 = burst-of-8\n11 = burst-of-16;\n0 = DMA_BURST_1WORDS;\n1 = DMA_BURST_4WORDS;\n2 = DMA_BURST_8WORDS;\n3 = DMA_BURST_16WORDS",
              2, old_value_t.max_ahb_burstsize, new_value_t.max_ahb_burstsize };
    m_bit_details_model.bits.append(entry);
    entry = { "18: immediate:1",
              "AHB master gizmo (AHB-DMA) - Start AHB write request immediately.\n1 = start the AHB write request immediately as soon as the device has put one write data in the AHB gizmos queue.\n0 = start the AHB write request only when all the write data has transferred from the device to the AHB gizmos queue. NOTE: THIS SHOULD NEVER BE SET TO ENABLE (BSEV requires this bit to be 0);\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.immediate, new_value_t.immediate };
    m_bit_details_model.bits.append(entry);
    entry = { "19: rd_data:1",
              "AHB master gizmo - Pack all AHB read data.\n1 = wait for all requested read data to be in the AHB gizmos queue before returning the data back to the IP.\n0 = transfer each read data from the AHB to the IP immediately;\n0 = NO_WAIT;\n1 = WAIT",
              1, old_value_t.rd_data, new_value_t.rd_data };
    m_bit_details_model.bits.append(entry);
    entry = { "20: undefined_bits_20_23:4", "", 4, old_value_t.undefined_bits_20_23, new_value_t.undefined_bits_20_23 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: req_neg_cnt:8",
              "AHB master request negate count. This is an 8-bit counter use to indicate the minimum number of clk count between requests from this AHB master",
              8, old_value_t.req_neg_cnt, new_value_t.req_neg_cnt };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "This is now VDE's BSEV master gizmo configuration.\nAHB Gizmo BSE Control Register";
}

#define BSEA_OFFSET 0x70
#define BSEA_UNDEFMASK 0x00F8FFFF
union bsea_u {
    struct {
        unsigned int undefined_bits_0_15:16;
        unsigned int max_ahb_burstsize:2;   /* AHB master gizmo - Maximum allowed AHB burst size. 00 = single transfer. 01 = burst-of-4. 10 = burst-of-8. 11 = burst-of-16; 0 = DMA_BURST_1WORDS; 1 = DMA_BURST_4WORDS; 2 = DMA_BURST_8WORDS; 3 = DMA_BURST_16WORDS */
        unsigned int immediate:1;           /* AHB master gizmo - Start AHB write request immediately. 1 = start the AHB write request immediately as soon as the device puts data in the AHB gizmos queue. 0 = start the AHB write request only when all the write data has transferred from the device to the AHB gizmos queue. NOTE: THIS SHOULD NEVER BE SET TO ENABLE (BSEV requires this bit to be 0); 0 = DISABLE; 1 = ENABLE */
        unsigned int undefined_bits_19_23:5;
        unsigned int req_neg_cnt:8;         /* AHB master request negate count. This is an 8-bit counter use to indicate the minimum number of clk count between requests from this AHB master */
    };

    u_int32_t reg32;
};

void GizmoDev::fill_bsea_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const bsea_u old_value_t = { .reg32 = value };
    const bsea_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: undefined_bits_0_15:16", "", 16, old_value_t.undefined_bits_0_15, new_value_t.undefined_bits_0_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: max_ahb_burstsize:2",
              "AHB master gizmo - Maximum allowed AHB burst size.\n00 = single transfer.\n01 = burst-of-4.\n10 = burst-of-8.\n11 = burst-of-16;\n0 = DMA_BURST_1WORDS;\n1 = DMA_BURST_4WORDS;\n2 = DMA_BURST_8WORDS;\n3 = DMA_BURST_16WORDS",
              2, old_value_t.max_ahb_burstsize, new_value_t.max_ahb_burstsize };
    m_bit_details_model.bits.append(entry);
    entry = { "18: immediate:1",
              "AHB master gizmo - Start AHB write request immediately.\n1 = start the AHB write request immediately as soon as the device puts data in the AHB gizmos queue.\n0 = start the AHB write request only when all the write data has transferred from the device to the AHB gizmos queue. NOTE: THIS SHOULD NEVER BE SET TO ENABLE (BSEV requires this bit to be 0);\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.immediate, new_value_t.immediate };
    m_bit_details_model.bits.append(entry);
    entry = { "19: undefined_bits_19_23:5", "", 5, old_value_t.undefined_bits_19_23, new_value_t.undefined_bits_19_23 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: req_neg_cnt:8",
              "AHB master request negate count. This is an 8-bit counter use to indicate the minimum number of clk count between requests from this AHB master",
              8, old_value_t.req_neg_cnt, new_value_t.req_neg_cnt };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "VDE's BSEA master gizmo configuration\nAHB Gizmo BSEA Control Register";
}

#define NOR_OFFSET 0x74
#define NOR_UNDEFMASK 0xFFFFFF38
union nor_u {
    struct {
        unsigned int enable_split:1;        /* AHB slave gizmo - Enable splitting AHB transactions. 1 = enable 0 = disable; 0 = DISABLE; 1 = ENABLE */
        unsigned int force_to_ahb_single:1; /* AHB slave gizmo - Force all AHB transaction to single data request transaction. 1 = force to single data transaction always. 0 = don’t force to single data transaction; 0 = NOT_SINGLE_DATA; 1 = SINGLE_DATA */
        unsigned int enb_fast_rearbitrate:1;/* AHB slave gizmo - Enable fast re-arbitration. 1 = allow AHB master re-arbitration as soon as the device returns one read data into the gizmos queue. 0 = allow AHB master re-arbitration only when the device returns all read data into the gizmos queue; 0 = DISABLE; 1 = ENABLE */
        unsigned int undefined_bits_3_5:3;
        unsigned int accept_ahb_wr_always:1;/* AHB slave gizmo - Accept AHB write request always. 1 = always accept AHB write request without checking whether there is room in the queue to store the write data. 0 = accept AHB write request only when there’s enough room in the queue to store all the write data; 0 = ACCEPT_ON_CHECK; 1 = ACCEPT_ON_NOCHECK */
        unsigned int dont_split_ahb_wr:1;   /* AHB slave gizmo - Dont split AHB write transaction.  1 = dont split AHB  write transaction ever. 0 (and enable_split=1) = allow AHB write   transaction to be split. */
        unsigned int undefined_bits_8_31:24;
    };

    u_int32_t reg32;
};

void GizmoDev::fill_nor_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const nor_u old_value_t = { .reg32 = value };
    const nor_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: enable_split:1",
              "AHB slave gizmo - Enable splitting AHB transactions.\n1 = enable\n0 = disable;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.enable_split, new_value_t.enable_split };
    m_bit_details_model.bits.append(entry);
    entry = { "01: force_to_ahb_single:1",
              "AHB slave gizmo - Force all AHB transaction to single data request transaction.\n1 = force to single data transaction always.\n0 = don’t force to single data transaction;\n0 = NOT_SINGLE_DATA;\n1 = SINGLE_DATA",
              1, old_value_t.force_to_ahb_single, new_value_t.force_to_ahb_single };
    m_bit_details_model.bits.append(entry);
    entry = { "02: enb_fast_rearbitrate:1",
              "AHB slave gizmo - Enable fast re-arbitration.\n1 = allow AHB master re-arbitration as soon as the device returns one read data into the gizmos queue.\n0 = allow AHB master re-arbitration only when the device returns all read data into the gizmos queue;\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.enb_fast_rearbitrate, new_value_t.enb_fast_rearbitrate };
    m_bit_details_model.bits.append(entry);
    entry = { "03: undefined_bits_3_5:3", "", 3, old_value_t.undefined_bits_3_5, new_value_t.undefined_bits_3_5 };
    m_bit_details_model.bits.append(entry);
    entry = { "06: accept_ahb_wr_always:1",
              "AHB slave gizmo - Accept AHB write request always.\n1 = always accept AHB write request without checking whether there is room in the queue to store the write data.\n0 = accept AHB write request only when there’s enough room in the queue to store all the write data;\n0 = ACCEPT_ON_CHECK;\n1 = ACCEPT_ON_NOCHECK",
              1, old_value_t.accept_ahb_wr_always, new_value_t.accept_ahb_wr_always };
    m_bit_details_model.bits.append(entry);
    entry = { "07: dont_split_ahb_wr:1",
              "AHB slave gizmo - Dont split AHB write transaction.\n1 = dont split AHB  write transaction ever. 0 (and enable_split=1) = allow AHB write   transaction to be split.",
              1, old_value_t.dont_split_ahb_wr, new_value_t.dont_split_ahb_wr };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_31:24", "", 24, old_value_t.undefined_bits_8_31, new_value_t.undefined_bits_8_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "AHB Gizmo AHB NOR flash Control Register";
}

#define USB2_OFFSET 0x78
#define USB2_UNDEFMASK 0x00F8FF38
union usb2_u {
    struct {
        unsigned int enable_split:1;        /* AHB slave gizmo - Enable splitting AHB transactions. 1 = enable 0 = disable 0 = DISABLE 1 = ENABLE */
        unsigned int force_to_ahb_single:1; /* AHB slave gizmo - Force all AHB transaction to single data request transaction. 1 = force to single data transaction always. 0 = dont force to single data transaction. 0 = NOT_SINGLE_DATA 1 = SINGLE_DATA */
        unsigned int enb_fast_rearbitrate:1;/* AHB slave gizmo - Enable fast re-arbitration. 1 = allow AHB master re-arbitration as soon as the device returns one read data into the gizmos queue. 0 = allow AHB master re-arbitration only when the device returns all read data into the gizmos queue. 0 = DISABLE 1 = ENABLE */
        unsigned int undefined_bits_3_5:3;
        unsigned int accept_ahb_wr_always:1;/* AHB slave gizmo - Accept AHB write request always.  1 = always accept AHB write request without checking whether there is room in the queue to store the write data. 0 = accept AHB write request only when theres  enough room in the queue to store all the write data. */
        unsigned int dont_split_ahb_wr:1;   /* AHB slave gizmo - Dont split AHB write transaction. 1 = dont split AHB write transaction ever. 0 (and enable_split=1) = allow AHB write transaction to be split. 0 = ENABLE 1 = DISABLE */
        unsigned int undefined_bits_8_15:8;
        unsigned int max_ahb_burstsize:2;   /* AHB master gizmo - Maximum allowed AHB burst size. 00 = single transfer. 01 = burst-of-4. 10 = burst-of-8. 11 = burst-of-16. 0 = DMA_BURST_1WORDS 1 = DMA_BURST_4WORDS 2 = DMA_BURST_8WORDS 3 = DMA_BURST_16WORDS */
        unsigned int immediate:1;           /* AHB master gizmo - Start AHB write request immediately. 1 = start the AHB write request immediately as soon as the device puts data in the AHB gizmos queue. 0 = start the AHB write request only when all the write data has transferred from the device to the AHB gizmos queue. 0 = DISABLE 1 = ENABLE */
        unsigned int undefined_bits_19_23:5;
        unsigned int req_neg_cnt:8;         /* AHB master request negate count. This is an 8-bit counter use to indicate the minimum number of clk count between requests from this AHB master */
    };

    u_int32_t reg32;
};

void GizmoDev::fill_usb2_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const usb2_u old_value_t = { .reg32 = value };
    const usb2_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: enable_split:1",
              "AHB slave gizmo - Enable splitting AHB transactions.\n1 = enable\n0 = disable\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.enable_split, new_value_t.enable_split };
    m_bit_details_model.bits.append(entry);
    entry = { "01: force_to_ahb_single:1",
              "AHB slave gizmo - Force all AHB transaction to single data request transaction.\n1 = force to single data transaction always.\n0 = dont force to single data transaction.\n0 = NOT_SINGLE_DATA\n1 = SINGLE_DATA",
              1, old_value_t.force_to_ahb_single, new_value_t.force_to_ahb_single };
    m_bit_details_model.bits.append(entry);
    entry = { "02: enb_fast_rearbitrate:1",
              "AHB slave gizmo - Enable fast re-arbitration.\n1 = allow AHB master re-arbitration as soon as the device returns one read data into the gizmos queue.\n0 = allow AHB master re-arbitration only when the device returns all read data into the gizmos queue.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.enb_fast_rearbitrate, new_value_t.enb_fast_rearbitrate };
    m_bit_details_model.bits.append(entry);
    entry = { "03: undefined_bits_3_5:3", "", 3, old_value_t.undefined_bits_3_5, new_value_t.undefined_bits_3_5 };
    m_bit_details_model.bits.append(entry);
    entry = { "06: accept_ahb_wr_always:1",
              "AHB slave gizmo - Accept AHB write request always.\n1 = always accept AHB write request without checking whether there is room in the queue to store the write data.\n0 = accept AHB write request only when theres  enough room in the queue to store all the write data.",
              1, old_value_t.accept_ahb_wr_always, new_value_t.accept_ahb_wr_always };
    m_bit_details_model.bits.append(entry);
    entry = { "07: dont_split_ahb_wr:1",
              "AHB slave gizmo - Dont split AHB write transaction.\n1 = dont split AHB write transaction ever. 0 (and enable_split=1) = allow AHB write transaction to be split.\n0 = ENABLE\n1 = DISABLE",
              1, old_value_t.dont_split_ahb_wr, new_value_t.dont_split_ahb_wr };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_15:8", "", 8, old_value_t.undefined_bits_8_15, new_value_t.undefined_bits_8_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: max_ahb_burstsize:2",
              "AHB master gizmo - Maximum allowed AHB burst size.\n00 = single transfer.\n01 = burst-of-4.\n10 = burst-of-8.\n11 = burst-of-16.\n0 = DMA_BURST_1WORDS\n1 = DMA_BURST_4WORDS\n2 = DMA_BURST_8WORDS\n3 = DMA_BURST_16WORDS",
              2, old_value_t.max_ahb_burstsize, new_value_t.max_ahb_burstsize };
    m_bit_details_model.bits.append(entry);
    entry = { "18: immediate:1",
              "AHB master gizmo - Start AHB write request immediately.\n1 = start the AHB write request immediately as soon as the device puts data in the AHB gizmos queue.\n0 = start the AHB write request only when all the write data has transferred from the device to the AHB gizmos queue.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.immediate, new_value_t.immediate };
    m_bit_details_model.bits.append(entry);
    entry = { "19: undefined_bits_19_23:5", "", 5, old_value_t.undefined_bits_19_23, new_value_t.undefined_bits_19_23 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: req_neg_cnt:8",
              "AHB master request negate count. This is an 8-bit counter use to indicate the minimum number of clk count between requests from this AHB master",
              8, old_value_t.req_neg_cnt, new_value_t.req_neg_cnt };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "This is now USB2 master gizmo configuration\nAHB Gizmo USB2 Control Register";
}

#define USB3_OFFSET 0x7C
#define USB3_UNDEFMASK 0x00F8FF38
union usb3_u {
    struct {
        unsigned int enable_split:1;        /* AHB slave gizmo - Enable splitting AHB transactions. 1 = enable 0 = disable 0 = DISABLE 1 = ENABLE */
        unsigned int force_to_ahb_single:1; /* AHB slave gizmo - Force all AHB transaction to single data request transaction. 1 = force to single data transaction always. 0 = dont force to single data transaction. 0 = NOT_SINGLE_DATA 1 = SINGLE_DATA */
        unsigned int enb_fast_rearbitrate:1;/* AHB slave gizmo - Enable fast re-arbitration. 1 = allow AHB master re-arbitration as soon as the device returns one read data into the gizmos queue. 0 = allow AHB master re-arbitration only when the device returns all read data into the gizmos queue. 0 = DISABLE 1 = ENABLE */
        unsigned int undefined_bits_3_5:3;
        unsigned int accept_ahb_wr_always:1;/* AHB slave gizmo - Accept AHB write request always. 1 = always accept AHB write request without checking whether there is room in the queue to store the write data. 0 = accept AHB write request only when theres enough room in the queue to store all the write data. 0 = ACCEPT_ON_CHECK 1 = ACCEPT_ON_NOCHECK */
        unsigned int dont_split_ahb_wr:1;   /* AHB slave gizmo – Don’t split AHB write transaction. 1 = don’t split AHB write transaction ever. 0 (and enable_split=1) = allow AHB write transaction to be split. 0 = ENABLE 1 = DISABLE */
        unsigned int undefined_bits_8_15:8;
        unsigned int max_ahb_burstsize:2;   /* AHB master gizmo - Maximum allowed AHB burst size. 00 = single transfer. 01 = burst-of-4. 10 = burst-of-8. 11 = burst-of-16. 0 = DMA_BURST_1WORDS 1 = DMA_BURST_4WORDS 2 = DMA_BURST_8WORDS 3 = DMA_BURST_16WORDS */
        unsigned int immediate:1;           /* AHB master gizmo - Start AHB write request immediately. 1 = start the AHB write request immediately as soon as the device puts data in the AHB gizmos queue. 0 = start the AHB write request only when all the write data has transferred from the device to the AHB gizmos queue. 0 = DISABLE 1 = ENABLE */
        unsigned int undefined_bits_19_23:5;
        unsigned int req_neg_cnt:8;         /* AHB master request negate count. This is an 8-bit counter use to indicate the minimum number of clk count between requests from this AHB master */
    };

    u_int32_t reg32;
};

void GizmoDev::fill_usb3_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const usb3_u old_value_t = { .reg32 = value };
    const usb3_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: enable_split:1",
              "AHB slave gizmo - Enable splitting AHB transactions.\n1 = enable\n0 = disable\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.enable_split, new_value_t.enable_split };
    m_bit_details_model.bits.append(entry);
    entry = { "01: force_to_ahb_single:1",
              "AHB slave gizmo - Force all AHB transaction to single data request transaction.\n1 = force to single data transaction always.\n0 = dont force to single data transaction.\n0 = NOT_SINGLE_DATA\n1 = SINGLE_DATA",
              1, old_value_t.force_to_ahb_single, new_value_t.force_to_ahb_single };
    m_bit_details_model.bits.append(entry);
    entry = { "02: enb_fast_rearbitrate:1",
              "AHB slave gizmo - Enable fast re-arbitration.\n1 = allow AHB master re-arbitration as soon as the device returns one read data into the gizmos queue.\n0 = allow AHB master re-arbitration only when the device returns all read data into the gizmos queue.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.enb_fast_rearbitrate, new_value_t.enb_fast_rearbitrate };
    m_bit_details_model.bits.append(entry);
    entry = { "03: undefined_bits_3_5:3", "", 3, old_value_t.undefined_bits_3_5, new_value_t.undefined_bits_3_5 };
    m_bit_details_model.bits.append(entry);
    entry = { "06: accept_ahb_wr_always:1",
              "AHB slave gizmo - Accept AHB write request always.\n1 = always accept AHB write request without checking whether there is room in the queue to store the write data.\n0 = accept AHB write request only when theres enough room in the queue to store all the write data.\n0 = ACCEPT_ON_CHECK\n1 = ACCEPT_ON_NOCHECK",
              1, old_value_t.accept_ahb_wr_always, new_value_t.accept_ahb_wr_always };
    m_bit_details_model.bits.append(entry);
    entry = { "07: dont_split_ahb_wr:1",
              "AHB slave gizmo – Don’t split AHB write transaction.\n1 = don’t split AHB write transaction ever. 0 (and enable_split=1) = allow AHB write transaction to be split.\n0 = ENABLE\n1 = DISABLE",
              1, old_value_t.dont_split_ahb_wr, new_value_t.dont_split_ahb_wr };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_15:8", "", 8, old_value_t.undefined_bits_8_15, new_value_t.undefined_bits_8_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: max_ahb_burstsize:2",
              "AHB master gizmo - Maximum allowed AHB burst size.\n00 = single transfer.\n01 = burst-of-4.\n10 = burst-of-8.\n11 = burst-of-16.\n0 = DMA_BURST_1WORDS\n1 = DMA_BURST_4WORDS\n2 = DMA_BURST_8WORDS\n3 = DMA_BURST_16WORDS",
              2, old_value_t.max_ahb_burstsize, new_value_t.max_ahb_burstsize };
    m_bit_details_model.bits.append(entry);
    entry = { "18: immediate:1",
              "AHB master gizmo - Start AHB write request immediately.\n1 = start the AHB write request immediately as soon as the device puts data in the AHB gizmos queue.\n0 = start the AHB write request only when all the write data has transferred from the device to the AHB gizmos queue.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.immediate, new_value_t.immediate };
    m_bit_details_model.bits.append(entry);
    entry = { "19: undefined_bits_19_23:5", "", 5, old_value_t.undefined_bits_19_23, new_value_t.undefined_bits_19_23 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: req_neg_cnt:8",
              "AHB master request negate count. This is an 8-bit counter use to indicate the minimum number of clk count between requests from this AHB master",
              8, old_value_t.req_neg_cnt, new_value_t.req_neg_cnt };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = " USB3 master gizmo configuration\n AHB Gizmo USB3 Control Register";
}

#define SDMMC1_OFFSET 0x80
#define SDMMC1_UNDEFMASK 0x00F8FF38
union sdmmc1_u {
    struct {
        unsigned int enable_split:1;        /* AHB slave gizmo - Enable splitting AHB transactions. 1 = enable 0 = disable 0 = DISABLE 1 = ENABLE */
        unsigned int force_to_ahb_single:1; /* AHB slave gizmo - Force all AHB transaction to single data request transaction. 1 = force to single data transaction always. 0 = dont force to single data transaction. 0 = NOT_SINGLE_DATA; 1 = SINGLE_DATA */
        unsigned int enb_fast_rearbitrate:1;/* AHB slave gizmo - Enable fast re-arbitration. 1 = allow AHB master re-arbitration as soon as the device returns one read data into the gizmos queue. 0 = allow AHB master re-arbitration only when the device returns all read data into the gizmos queue. 0 = DISABLE 1 = ENABLE */
        unsigned int undefined_bits_3_5:3;
        unsigned int accept_ahb_wr_always:1;/* AHB slave gizmo - Accept AHB write request always. 1 = always accept AHB write request without checking whether there is room in the queue to store the write data. 0 = accept AHB write request only when theres enough room in the queue to store all the write data. 0 = ACCEPT_ON_CHECK 1 = ACCEPT_ON_NOCHECK */
        unsigned int dont_split_ahb_wr:1;   /* AHB slave gizmo - Dont split AHB write transaction. 1 = dont split AHB write transaction ever. 0 (and enable_split=1) = allow AHB write transaction to be split. 0 = ENABLE 1 = DISABLE */
        unsigned int undefined_bits_8_15:8;
        unsigned int max_ahb_burstsize:2;   /* AHB master gizmo - Maximum allowed AHB burst size. 00 = single transfer. 01 = burst-of-4. 10 = burst-of-8. 11 = burst-of-16. 0 = DMA_BURST_1WORDS 1 = DMA_BURST_4WORDS 2 = DMA_BURST_8WORDS 3 = DMA_BURST_16WORDS */
        unsigned int immediate:1;           /* AHB master gizmo - Start AHB write request immediately. 1 = start the AHB write request immediately as soon as the device puts data in the AHB gizmos queue. 0 = start the AHB write request only when all the write data has transferred from the device to the AHB gizmos queue. 0 = DISABLE 1 = ENABLE */
        unsigned int undefined_bits_19_23:5;
        unsigned int req_neg_cnt:8;         /* AHB master request negate count. This is an 8-bit counter use to indicate the minimum number of clk count between requests from this AHB master */
    };

    u_int32_t reg32;
};

void GizmoDev::fill_sdmmc1_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const sdmmc1_u old_value_t = { .reg32 = value };
    const sdmmc1_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: enable_split:1",
              "AHB slave gizmo - Enable splitting AHB transactions.\n1 = enable\n0 = disable\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.enable_split, new_value_t.enable_split };
    m_bit_details_model.bits.append(entry);
    entry = { "01: force_to_ahb_single:1",
              "AHB slave gizmo - Force all AHB transaction to single data request transaction.\n1 = force to single data transaction always.\n0 = dont force to single data transaction.\n0 = NOT_SINGLE_DATA;\n1 = SINGLE_DATA",
              1, old_value_t.force_to_ahb_single, new_value_t.force_to_ahb_single };
    m_bit_details_model.bits.append(entry);
    entry = { "02: enb_fast_rearbitrate:1",
              "AHB slave gizmo - Enable fast re-arbitration.\n1 = allow AHB master re-arbitration as soon as the device returns one read data into the gizmos queue.\n0 = allow AHB master re-arbitration only when the device returns all read data into the gizmos queue.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.enb_fast_rearbitrate, new_value_t.enb_fast_rearbitrate };
    m_bit_details_model.bits.append(entry);
    entry = { "03: undefined_bits_3_5:3", "", 3, old_value_t.undefined_bits_3_5, new_value_t.undefined_bits_3_5 };
    m_bit_details_model.bits.append(entry);
    entry = { "06: accept_ahb_wr_always:1",
              "AHB slave gizmo - Accept AHB write request always.\n1 = always accept AHB write request without checking whether there is room in the queue to store the write data.\n0 = accept AHB write request only when theres enough room in the queue to store all the write data.\n0 = ACCEPT_ON_CHECK\n1 = ACCEPT_ON_NOCHECK",
              1, old_value_t.accept_ahb_wr_always, new_value_t.accept_ahb_wr_always };
    m_bit_details_model.bits.append(entry);
    entry = { "07: dont_split_ahb_wr:1",
              "AHB slave gizmo - Dont split AHB write transaction.\n1 = dont split AHB write transaction ever. 0 (and enable_split=1) = allow AHB write transaction to be split.\n0 = ENABLE\n1 = DISABLE",
              1, old_value_t.dont_split_ahb_wr, new_value_t.dont_split_ahb_wr };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_15:8", "", 8, old_value_t.undefined_bits_8_15, new_value_t.undefined_bits_8_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: max_ahb_burstsize:2",
              "AHB master gizmo - Maximum allowed AHB burst size.\n00 = single transfer.\n01 = burst-of-4.\n10 = burst-of-8.\n11 = burst-of-16.\n0 = DMA_BURST_1WORDS\n1 = DMA_BURST_4WORDS\n2 = DMA_BURST_8WORDS\n3 = DMA_BURST_16WORDS",
              2, old_value_t.max_ahb_burstsize, new_value_t.max_ahb_burstsize };
    m_bit_details_model.bits.append(entry);
    entry = { "18: immediate:1",
              "AHB master gizmo - Start AHB write request immediately.\n1 = start the AHB write request immediately as soon as the device puts data in the AHB gizmos queue.\n0 = start the AHB write request only when all the write data has transferred from the device to the AHB gizmos queue.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.immediate, new_value_t.immediate };
    m_bit_details_model.bits.append(entry);
    entry = { "19: undefined_bits_19_23:5", "", 5, old_value_t.undefined_bits_19_23, new_value_t.undefined_bits_19_23 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: req_neg_cnt:8",
              "AHB master request negate count. This is an 8-bit counter use to indicate the minimum number of clk count between requests from this AHB master",
              8, old_value_t.req_neg_cnt, new_value_t.req_neg_cnt };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = " SDMMC1 master gizmo configuration\nAHB Gizmo SDMMC1 Control Register";
}

#define SDMMC2_OFFSET 0x84
#define SDMMC2_UNDEFMASK 0x00F8FF38
union sdmmc2_u {
    struct {
        unsigned int enable_split:1;        /* AHB slave gizmo - Enable splitting AHB transactions. 1 = enable 0 = disable 0 = DISABLE 1 = ENABLE */
        unsigned int force_to_ahb_single:1; /* AHB slave gizmo - Force all AHB transaction to single data request transaction. 1 = force to single data transaction always. 0 = dont force to single data transaction. 0 = NOT_SINGLE_DATA 1 = SINGLE_DATA */
        unsigned int enb_fast_rearbitrate:1;/* AHB slave gizmo - Enable fast re-arbitration. 1 = allow AHB master re-arbitration as soon as the device returns one read data into the gizmos queue. 0 = allow AHB master re-arbitration only when the device returns all read data into the gizmos queue. 0 = DISABLE 1 = ENABLE */
        unsigned int undefined_bits_3_5:3;
        unsigned int accept_ahb_wr_always:1;/* AHB slave gizmo - Accept AHB write request always. 1 = always accept AHB write request without checking whether there is room in the queue to store the write data. 0 = accept AHB write request only when theres enough room in the queue to store all the write data. 0 = ACCEPT_ON_CHECK 1 = ACCEPT_ON_NOCHECK */
        unsigned int dont_split_ahb_wr:1;   /* AHB slave gizmo - Dont split AHB write transaction. 1 = dont split AHB write transaction ever. 0 (and enable_split=1) = allow AHB write transaction to be split. 0 = ENABLE;  1 = DISABLE */
        unsigned int undefined_bits_8_15:8;
        unsigned int max_ahb_burstsize:2;   /* AHB master gizmo - Maximum allowed AHB burst size. 00 = single transfer. 01 = burst-of-4. 10 = burst-of-8. 11 = burst-of-16. 0 = DMA_BURST_1WORDS 1 = DMA_BURST_4WORDS 2 = DMA_BURST_8WORDS 3 = DMA_BURST_16WORDS */
        unsigned int immediate:1;           /* AHB master gizmo - Start AHB write request immediately. 1 = start the AHB write request immediately as soon as the device puts data in the AHB gizmos queue. 0 = start the AHB write request only when all the write data has transferred from the device to the AHB gizmos queue. 0 = DISABLE; 1 = ENABLE */
        unsigned int undefined_bits_19_23:5;
        unsigned int req_neg_cnt:8;         /* AHB master request negate count. This is an 8-bit counter use to indicate the minimum number of clk count between requests from this AHB master */
    };

    u_int32_t reg32;
};

void GizmoDev::fill_sdmmc2_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const sdmmc2_u old_value_t = { .reg32 = value };
    const sdmmc2_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: enable_split:1",
              "AHB slave gizmo - Enable splitting AHB transactions.\n1 = enable\n0 = disable\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.enable_split, new_value_t.enable_split };
    m_bit_details_model.bits.append(entry);
    entry = { "01: force_to_ahb_single:1",
              "AHB slave gizmo - Force all AHB transaction to single data request transaction.\n1 = force to single data transaction always.\n0 = dont force to single data transaction.\n0 = NOT_SINGLE_DATA\n1 = SINGLE_DATA",
              1, old_value_t.force_to_ahb_single, new_value_t.force_to_ahb_single };
    m_bit_details_model.bits.append(entry);
    entry = { "02: enb_fast_rearbitrate:1",
              "AHB slave gizmo - Enable fast re-arbitration.\n1 = allow AHB master re-arbitration as soon as the device returns one read data into the gizmos queue.\n0 = allow AHB master re-arbitration only when the device returns all read data into the gizmos queue.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.enb_fast_rearbitrate, new_value_t.enb_fast_rearbitrate };
    m_bit_details_model.bits.append(entry);
    entry = { "03: undefined_bits_3_5:3", "", 3, old_value_t.undefined_bits_3_5, new_value_t.undefined_bits_3_5 };
    m_bit_details_model.bits.append(entry);
    entry = { "06: accept_ahb_wr_always:1",
              "AHB slave gizmo - Accept AHB write request always.\n1 = always accept AHB write request without checking whether there is room in the queue to store the write data.\n0 = accept AHB write request only when theres enough room in the queue to store all the write data.\n0 = ACCEPT_ON_CHECK\n1 = ACCEPT_ON_NOCHECK",
              1, old_value_t.accept_ahb_wr_always, new_value_t.accept_ahb_wr_always };
    m_bit_details_model.bits.append(entry);
    entry = { "07: dont_split_ahb_wr:1",
              "AHB slave gizmo - Dont split AHB write transaction.\n1 = dont split AHB write transaction ever. 0 (and enable_split=1) = allow AHB write transaction to be split.\n0 = ENABLE;\n1 = DISABLE",
              1, old_value_t.dont_split_ahb_wr, new_value_t.dont_split_ahb_wr };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_15:8", "", 8, old_value_t.undefined_bits_8_15, new_value_t.undefined_bits_8_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: max_ahb_burstsize:2",
              "AHB master gizmo - Maximum allowed AHB burst size.\n00 = single transfer.\n01 = burst-of-4.\n10 = burst-of-8.\n11 = burst-of-16.\n0 = DMA_BURST_1WORDS\n1 = DMA_BURST_4WORDS\n2 = DMA_BURST_8WORDS\n3 = DMA_BURST_16WORDS",
              2, old_value_t.max_ahb_burstsize, new_value_t.max_ahb_burstsize };
    m_bit_details_model.bits.append(entry);
    entry = { "18: immediate:1",
              "AHB master gizmo - Start AHB write request immediately.\n1 = start the AHB write request immediately as soon as the device puts data in the AHB gizmos queue.\n0 = start the AHB write request only when all the write data has transferred from the device to the AHB gizmos queue.\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.immediate, new_value_t.immediate };
    m_bit_details_model.bits.append(entry);
    entry = { "19: undefined_bits_19_23:5", "", 5, old_value_t.undefined_bits_19_23, new_value_t.undefined_bits_19_23 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: req_neg_cnt:8",
              "AHB master request negate count. This is an 8-bit counter use to indicate the minimum number of clk count between requests from this AHB master",
              8, old_value_t.req_neg_cnt, new_value_t.req_neg_cnt };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "SDMMC2 master gizmo configuration\nAHB Gizmo SDMMC2 Control Register";
}

#define SDMMC3_OFFSET 0x88
#define SDMMC3_UNDEFMASK 0x00F8FF38
union sdmmc3_u {
    struct {
        unsigned int enable_split:1;        /* AHB slave gizmo - Enable splitting AHB transactions. 1 = enable 0 = disable 0 = DISABLE; 1 = ENABLE */
        unsigned int force_to_ahb_single:1; /* AHB slave gizmo - Force all AHB transaction to single data request transaction. 1 = force to single data transaction always. 0 = dont force to single data transaction. 0 = NOT_SINGLE_DATA 1 = SINGLE_DATA */
        unsigned int enb_fast_rearbitrate:1;/* AHB slave gizmo - Enable fast re-arbitration. 1 = allow AHB master re-arbitration as soon as the device returns one read data into the gizmos queue. 0 = allow AHB master re-arbitration only when the device returns all read data into the gizmos queue. 0 = DISABLE 1 = ENABLE */
        unsigned int undefined_bits_3_5:3;
        unsigned int accept_ahb_wr_always:1;/* AHB slave gizmo - Accept AHB write request always. 1 = always accept AHB write request without checking whether there is room in the queue to store the write data. 0 = accept AHB write request only when theres enough room in the queue to store all the write data. 0 = ACCEPT_ON_CHECK 1 = ACCEPT_ON_NOCHECK */
        unsigned int dont_split_ahb_wr:1;   /* AHB slave gizmo - Dont split AHB write transaction. 1 = dont split AHB write transaction ever. 0 (and enable_split=1) = allow AHB write transaction to be split. 0 = ENABLE; 1 = DISABLE */
        unsigned int undefined_bits_8_15:8;
        unsigned int max_ahb_burstsize:2;   /* AHB master gizmo - Maximum allowed AHB burst size. 00 = single transfer. 01 = burst-of-4. 10 = burst-of-8. 11 = burst-of-16. 0 = DMA_BURST_1WORDS 1 = DMA_BURST_4WORDS 2 = DMA_BURST_8WORDS 3 = DMA_BURST_16WORDS */
        unsigned int immediate:1;           /* AHB master gizmo - Start AHB write request immediately. 1 = start the AHB write request immediately as soon as the device puts data in the AHB gizmos queue. 0 = start the AHB write request only when all the write data has transferred from the device to the AHB gizmos queue. 0 = DISABLE 1 = ENABLE */
        unsigned int undefined_bits_19_23:5;
        unsigned int req_neg_cnt:8;         /* AHB master request negate count. This is an 8-bit counter use to indicate the minimum number of clk count between requests from this AHB master */
    };

    u_int32_t reg32;
};

void GizmoDev::fill_sdmmc3_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const sdmmc3_u old_value_t = { .reg32 = value };
    const sdmmc3_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: enable_split:1",
              "AHB slave gizmo - Enable splitting AHB transactions.\n1 = enable\n0 = disable\n0 = DISABLE;\n1 = ENABLE",
              1, old_value_t.enable_split, new_value_t.enable_split };
    m_bit_details_model.bits.append(entry);
    entry = { "01: force_to_ahb_single:1",
              "AHB slave gizmo - Force all AHB transaction to single data request transaction.\n1 = force to single data transaction always.\n0 = dont force to single data transaction.\n0 = NOT_SINGLE_DATA\n1 = SINGLE_DATA",
              1, old_value_t.force_to_ahb_single, new_value_t.force_to_ahb_single };
    m_bit_details_model.bits.append(entry);
    entry = { "02: enb_fast_rearbitrate:1",
              "AHB slave gizmo - Enable fast re-arbitration.\n1 = allow AHB master re-arbitration as soon as the device returns one read data into the gizmos queue.\n0 = allow AHB master re-arbitration only when the device returns all read data into the gizmos queue.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.enb_fast_rearbitrate, new_value_t.enb_fast_rearbitrate };
    m_bit_details_model.bits.append(entry);
    entry = { "03: undefined_bits_3_5:3", "", 3, old_value_t.undefined_bits_3_5, new_value_t.undefined_bits_3_5 };
    m_bit_details_model.bits.append(entry);
    entry = { "06: accept_ahb_wr_always:1",
              "AHB slave gizmo - Accept AHB write request always.\n1 = always accept AHB write request without checking whether there is room in the queue to store the write data.\n0 = accept AHB write request only when theres enough room in the queue to store all the write data.\n0 = ACCEPT_ON_CHECK\n1 = ACCEPT_ON_NOCHECK",
              1, old_value_t.accept_ahb_wr_always, new_value_t.accept_ahb_wr_always };
    m_bit_details_model.bits.append(entry);
    entry = { "07: dont_split_ahb_wr:1",
              "AHB slave gizmo - Dont split AHB write transaction.\n1 = dont split AHB write transaction ever. 0 (and enable_split=1) = allow AHB write transaction to be split.\n0 = ENABLE;\n1 = DISABLE",
              1, old_value_t.dont_split_ahb_wr, new_value_t.dont_split_ahb_wr };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_15:8", "", 8, old_value_t.undefined_bits_8_15, new_value_t.undefined_bits_8_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: max_ahb_burstsize:2",
              "AHB master gizmo - Maximum allowed AHB burst size.\n00 = single transfer.\n01 = burst-of-4.\n10 = burst-of-8.\n11 = burst-of-16.\n0 = DMA_BURST_1WORDS\n1 = DMA_BURST_4WORDS\n2 = DMA_BURST_8WORDS\n3 = DMA_BURST_16WORDS",
              2, old_value_t.max_ahb_burstsize, new_value_t.max_ahb_burstsize };
    m_bit_details_model.bits.append(entry);
    entry = { "18: immediate:1",
              "AHB master gizmo - Start AHB write request immediately.\n1 = start the AHB write request immediately as soon as the device puts data in the AHB gizmos queue.\n0 = start the AHB write request only when all the write data has transferred from the device to the AHB gizmos queue.\n0 = DISABLE\n1 = ENABLE",
              1, old_value_t.immediate, new_value_t.immediate };
    m_bit_details_model.bits.append(entry);
    entry = { "19: undefined_bits_19_23:5", "", 5, old_value_t.undefined_bits_19_23, new_value_t.undefined_bits_19_23 };
    m_bit_details_model.bits.append(entry);
    entry = { "24: req_neg_cnt:8",
              "AHB master request negate count. This is an 8-bit counter use to indicate the minimum number of clk count between requests from this AHB master",
              8, old_value_t.req_neg_cnt, new_value_t.req_neg_cnt };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "SDMMC3 master gizmo configuration\nAHB Gizmo SDMMC3 Control Register";
}

#define MEM_PREFETCH_CFG_X_OFFSET 0xD8
#define MEM_PREFETCH_CFG_X_UNDEFMASK 0xFFFFFFF0
union mem_prefetch_cfg_x_u {
    struct {
        unsigned int disable_check_size_master1:1;/*  */
        unsigned int disable_check_size_master2:1;/*  */
        unsigned int disable_check_size_master3:1;/*  */
        unsigned int disable_check_size_master4:1;/*  */
        unsigned int undefined_bits_4_31:28;
    };

    u_int32_t reg32;
};

void GizmoDev::fill_mem_prefetch_cfg_x_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const mem_prefetch_cfg_x_u old_value_t = { .reg32 = value };
    const mem_prefetch_cfg_x_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: disable_check_size_master1:1",
              "",
              1, old_value_t.disable_check_size_master1, new_value_t.disable_check_size_master1 };
    m_bit_details_model.bits.append(entry);
    entry = { "01: disable_check_size_master2:1",
              "",
              1, old_value_t.disable_check_size_master2, new_value_t.disable_check_size_master2 };
    m_bit_details_model.bits.append(entry);
    entry = { "02: disable_check_size_master3:1",
              "",
              1, old_value_t.disable_check_size_master3, new_value_t.disable_check_size_master3 };
    m_bit_details_model.bits.append(entry);
    entry = { "03: disable_check_size_master4:1",
              "",
              1, old_value_t.disable_check_size_master4, new_value_t.disable_check_size_master4 };
    m_bit_details_model.bits.append(entry);
    entry = { "04: undefined_bits_4_31:28", "", 28, old_value_t.undefined_bits_4_31, new_value_t.undefined_bits_4_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "If DISABLE_CHECK_SIZE is 0, then only read requests that have the exact same size as the original read request that kick-started the prefetch process will cause a \"hit\". In addition, the address must be the exact next one in the sequence.\nFor instance, if the first request on a prefetch-enabled AHB Master arrives with SIZE=ONE_BYTE and ADDR[31:0]=0x3, then the next access must have SIZE=ONE_BYTE and ADDR[31:0]=0x4 in order to be considered a hit.\nIf DISABLE_CHECK_SIZE is 1, then a read request will hit as long as the incoming ADDR[31:4]matches the expected_ADDR[31:4]. expected_ADDR[31:4] is always either \"last ADDR[31:4]\" or \"last ADDR[31:4] + 1\", where last ADDR is the prior read request actually issued by the AHB Master(as opposed to the last request to the CIF, which could have been a speculative read).\nexpected_ADDR[31:4] is always \"last ADDR[31:4]\" unless \"SIZE\" field in the last request uses the last byte in the 16-byte CIF word.";
}

#define AHB_ARBITRATION_XBAR_CTRL_OFFSET 0xDC
#define AHB_ARBITRATION_XBAR_CTRL_UNDEFMASK 0xFFFEFFFC
union ahb_arbitration_xbar_ctrl_u {
    struct {
        unsigned int post_dis:1;            /* SW writes to modify 0 = ENABLE 1 = DISABLE */
        unsigned int hold_dis:1;            /* By default CPU accesses to IRAMs will be held if there are any pending requests from the AHB to the IRAMs. This is done to avoid data coherency issues. If SW handles coherency then this can be turned off to improve performance.SW writes to modify 0 = ENABLE 1 = DISABLE */
        unsigned int undefined_bits_2_15:14;
        unsigned int mem_init_done:1;       /* SW should set this bit when memory has been initialized 0 = NOT_DONE 1 = DONE */
        unsigned int undefined_bits_17_31:15;
    };

    u_int32_t reg32;
};

void GizmoDev::fill_ahb_arbitration_xbar_ctrl_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const ahb_arbitration_xbar_ctrl_u old_value_t = { .reg32 = value };
    const ahb_arbitration_xbar_ctrl_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: post_dis:1",
              "SW writes to modify\n0 = ENABLE\n1 = DISABLE",
              1, old_value_t.post_dis, new_value_t.post_dis };
    m_bit_details_model.bits.append(entry);
    entry = { "01: hold_dis:1",
              "By default CPU accesses to IRAMs will be held if there are any pending requests from the AHB to the IRAMs. This is done to avoid data coherency issues. If SW handles coherency then this can be turned off to improve performance.SW writes to modify\n0 = ENABLE\n1 = DISABLE",
              1, old_value_t.hold_dis, new_value_t.hold_dis };
    m_bit_details_model.bits.append(entry);
    entry = { "02: undefined_bits_2_15:14", "", 14, old_value_t.undefined_bits_2_15, new_value_t.undefined_bits_2_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: mem_init_done:1",
              "SW should set this bit when memory has been initialized\n0 = NOT_DONE\n1 = DONE",
              1, old_value_t.mem_init_done, new_value_t.mem_init_done };
    m_bit_details_model.bits.append(entry);
    entry = { "17: undefined_bits_17_31:15", "", 15, old_value_t.undefined_bits_17_31, new_value_t.undefined_bits_17_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "XBAR Control Register";
}

#define MEM_PREFETCH_CFG3_OFFSET 0xE0
#define MEM_PREFETCH_CFG3_UNDEFMASK 0x00000000
union mem_prefetch_cfg3_u {
    struct {
        unsigned int inactivity_timeout:16; /* 2048 cycles */
        unsigned int spec_throttle:5;       /* not used for AP20 and beyond */
        unsigned int addr_bndry:5;          /* 2^(n+4) byte boundary. any value >16 will use n=16 */
        unsigned int ahb_mst_id:5;          /* AHBDMA master 0 = CPU 1 = COP 2 = VCP 3 = UNUSED_03 4 = IDE 5 = AHBDMA 6 = USB 7 = APBDMA 8 = XIO 9 = SDMMC1 10 = NAND_FLASH 11 = SNOR 12 = SDMMC4 13 = BSEV 14 = UNUSED_0E 15 = UNUSED_0F 12 = SDMMC4 16 = BSEA 17 = USB3 18 = USB2 19 = SDMMC2 20 = SDMMC3 21 = UNUSED_15 22 = UNUSED_16 23 = UNUSED_17 24 = UNUSED_18 25 = UNUSED_19 26 = UNUSED_1A 27 = UNUSED_1B 28 = UNUSED_1C 29 = UNUSED_1D 30 = UNUSED_1E 31 = UNUSED_1F */
        unsigned int enable:1;              /* 1=enable 0=disable */
    };

    u_int32_t reg32;
};

void GizmoDev::fill_mem_prefetch_cfg3_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const mem_prefetch_cfg3_u old_value_t = { .reg32 = value };
    const mem_prefetch_cfg3_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: inactivity_timeout:16",
              "2048 cycles",
              16, old_value_t.inactivity_timeout, new_value_t.inactivity_timeout };
    m_bit_details_model.bits.append(entry);
    entry = { "16: spec_throttle:5",
              "not used for AP20 and beyond",
              5, old_value_t.spec_throttle, new_value_t.spec_throttle };
    m_bit_details_model.bits.append(entry);
    entry = { "21: addr_bndry:5",
              "2^(n+4) byte boundary. any value >16 will use n=16",
              5, old_value_t.addr_bndry, new_value_t.addr_bndry };
    m_bit_details_model.bits.append(entry);
    entry = { "26: ahb_mst_id:5",
              "AHBDMA master\n0 = CPU\n1 = COP\n2 = VCP\n3 = UNUSED_03\n4 = IDE\n5 = AHBDMA\n6 = USB\n7 = APBDMA\n8 = XIO\n9 = SDMMC1\n10 = NAND_FLASH\n11 = SNOR\n12 = SDMMC4\n13 = BSEV\n14 = UNUSED_0E\n15 = UNUSED_0F\n12 = SDMMC4\n16 = BSEA\n17 = USB3\n18 = USB2\n19 = SDMMC2\n20 = SDMMC3\n21 = UNUSED_15\n22 = UNUSED_16\n23 = UNUSED_17\n24 = UNUSED_18\n25 = UNUSED_19\n26 = UNUSED_1A\n27 = UNUSED_1B\n28 = UNUSED_1C\n29 = UNUSED_1D\n30 = UNUSED_1E\n31 = UNUSED_1F",
              5, old_value_t.ahb_mst_id, new_value_t.ahb_mst_id };
    m_bit_details_model.bits.append(entry);
    entry = { "31: enable:1",
              "1=enable\n0=disable",
              1, old_value_t.enable, new_value_t.enable };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "See the description of the pre-fetcher above.";
}

#define MEM_PREFETCH_CFG4_OFFSET 0xE4
#define MEM_PREFETCH_CFG4_UNDEFMASK 0x00000000
union mem_prefetch_cfg4_u {
    struct {
        unsigned int inactivity_timeout:16; /* 2048 cycles */
        unsigned int spec_throttle:5;       /* not used for AP20 and beyond */
        unsigned int addr_bndry:5;          /* 2^(n+4) byte boundary. any value >16 will use n=16 */
        unsigned int ahb_mst_id:5;          /* AHBDMA master 0 = CPU 1 = COP 2 = VCP 3 = UNUSED_03 4 = IDE 5 = AHBDMA 6 = USB 7 = APBDMA; 8 = XIO 9 = SDMMC1 10 = NAND_FLASH 11 = SNOR 12 = SDMMC4 13 = BSEV 14 = UNUSED_0E 15 = UNUSED_0F 12 = SDMMC4 16 = BSEA 17 = USB3 18 = USB2 19 = SDMMC2 20 = SDMMC3 21 = UNUSED_15 22 = UNUSED_16 23 = UNUSED_17 24 = UNUSED_18 25 = UNUSED_19 26 = UNUSED_1A 27 = UNUSED_1B 28 = UNUSED_1C 29 = UNUSED_1D 30 = UNUSED_1E 31 = UNUSED_1F */
        unsigned int enable:1;              /* 1=enable 0=disable */
    };

    u_int32_t reg32;
};

void GizmoDev::fill_mem_prefetch_cfg4_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const mem_prefetch_cfg4_u old_value_t = { .reg32 = value };
    const mem_prefetch_cfg4_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: inactivity_timeout:16",
              "2048 cycles",
              16, old_value_t.inactivity_timeout, new_value_t.inactivity_timeout };
    m_bit_details_model.bits.append(entry);
    entry = { "16: spec_throttle:5",
              "not used for AP20 and beyond",
              5, old_value_t.spec_throttle, new_value_t.spec_throttle };
    m_bit_details_model.bits.append(entry);
    entry = { "21: addr_bndry:5",
              "2^(n+4) byte boundary. any value >16 will use n=16",
              5, old_value_t.addr_bndry, new_value_t.addr_bndry };
    m_bit_details_model.bits.append(entry);
    entry = { "26: ahb_mst_id:5",
              "AHBDMA master\n0 = CPU\n1 = COP\n2 = VCP\n3 = UNUSED_03\n4 = IDE\n5 = AHBDMA\n6 = USB\n7 = APBDMA;\n8 = XIO\n9 = SDMMC1\n10 = NAND_FLASH\n11 = SNOR\n12 = SDMMC4\n13 = BSEV\n14 = UNUSED_0E\n15 = UNUSED_0F\n12 = SDMMC4\n16 = BSEA\n17 = USB3\n18 = USB2\n19 = SDMMC2\n20 = SDMMC3\n21 = UNUSED_15\n22 = UNUSED_16\n23 = UNUSED_17\n24 = UNUSED_18\n25 = UNUSED_19\n26 = UNUSED_1A\n27 = UNUSED_1B\n28 = UNUSED_1C\n29 = UNUSED_1D\n30 = UNUSED_1E\n31 = UNUSED_1F",
              5, old_value_t.ahb_mst_id, new_value_t.ahb_mst_id };
    m_bit_details_model.bits.append(entry);
    entry = { "31: enable:1",
              "1=enable\n0=disable",
              1, old_value_t.enable, new_value_t.enable };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "See the description of the pre-fetcher above.";
}

#define AHB_AVP_PPCS_RD_COH_STATUS_OFFSET 0xE8
#define AHB_AVP_PPCS_RD_COH_STATUS_UNDEFMASK 0xFFFEFFFE
union ahb_avp_ppcs_rd_coh_status_u {
    struct {
        unsigned int wrs_outstanding:1;
        unsigned int undefined_bits_1_15:15;
        unsigned int rds_outstanding:1;
        unsigned int undefined_bits_17_31:15;
    };

    u_int32_t reg32;
};

void GizmoDev::fill_ahb_avp_ppcs_rd_coh_status_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const ahb_avp_ppcs_rd_coh_status_u old_value_t = { .reg32 = value };
    const ahb_avp_ppcs_rd_coh_status_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: wrs_outstanding:1", "", 1, old_value_t.wrs_outstanding, new_value_t.wrs_outstanding };
    m_bit_details_model.bits.append(entry);
    entry = { "01: undefined_bits_1_15:15", "", 15, old_value_t.undefined_bits_1_15, new_value_t.undefined_bits_1_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: rds_outstanding:1", "", 1, old_value_t.rds_outstanding, new_value_t.rds_outstanding };
    m_bit_details_model.bits.append(entry);
    entry = { "17: undefined_bits_17_31:15", "", 15, old_value_t.undefined_bits_17_31, new_value_t.undefined_bits_17_31 };
    m_bit_details_model.bits.append(entry);
}

#define MEM_PREFETCH_CFG1_OFFSET 0xEC
#define MEM_PREFETCH_CFG1_UNDEFMASK 0x00000000
union mem_prefetch_cfg1_u {
    struct {
        unsigned int inactivity_timeout:16; /* 2048 cycles */
        unsigned int spec_throttle:5;       /* not used for Tegra 200 Series and beyond */
        unsigned int addr_bndry:5;          /* 2^(n+4) byte boundary. any value >16 will use n=16 */
        unsigned int ahb_mst_id:5;          /* AHBDMA master 0 = CPU 1 = COP 2 = VCP 3 = UNUSED_03 4 = IDE 5 = AHBDMA 6 = USB 7 = APBDMA 8 = XIO 9 = SDMMC1 10 = NAND_FLASH 11 = SNOR 12 = SDMMC4 13 = BSEV 14 = UNUSED_0E 15 = UNUSED_0F 12 = SDMMC4 16 = BSEA 17 = USB3 18 = USB2 19 = SDMMC2 20 = SDMMC3 21 = UNUSED_15 22 = UNUSED_16 23 = UNUSED_17 24 = UNUSED_18 25 = UNUSED_19 26 = UNUSED_1A 27 = UNUSED_1B 28 = UNUSED_1C 29 = UNUSED_1D 30 = UNUSED_1E 31 = UNUSED_1F */
        unsigned int enable:1;              /* 1=enable 0=disable */
    };

    u_int32_t reg32;
};

void GizmoDev::fill_mem_prefetch_cfg1_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const mem_prefetch_cfg1_u old_value_t = { .reg32 = value };
    const mem_prefetch_cfg1_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: inactivity_timeout:16",
              "2048 cycles",
              16, old_value_t.inactivity_timeout, new_value_t.inactivity_timeout };
    m_bit_details_model.bits.append(entry);
    entry = { "16: spec_throttle:5",
              "not used for Tegra 200 Series and beyond",
              5, old_value_t.spec_throttle, new_value_t.spec_throttle };
    m_bit_details_model.bits.append(entry);
    entry = { "21: addr_bndry:5",
              "2^(n+4) byte boundary. any value >16 will use n=16",
              5, old_value_t.addr_bndry, new_value_t.addr_bndry };
    m_bit_details_model.bits.append(entry);
    entry = { "26: ahb_mst_id:5",
              "AHBDMA master\n0 = CPU\n1 = COP\n2 = VCP\n3 = UNUSED_03\n4 = IDE\n5 = AHBDMA\n6 = USB\n7 = APBDMA\n8 = XIO\n9 = SDMMC1\n10 = NAND_FLASH\n11 = SNOR\n12 = SDMMC4\n13 = BSEV\n14 = UNUSED_0E\n15 = UNUSED_0F\n12 = SDMMC4\n16 = BSEA\n17 = USB3\n18 = USB2\n19 = SDMMC2\n20 = SDMMC3\n21 = UNUSED_15\n22 = UNUSED_16\n23 = UNUSED_17\n24 = UNUSED_18\n25 = UNUSED_19\n26 = UNUSED_1A\n27 = UNUSED_1B\n28 = UNUSED_1C\n29 = UNUSED_1D\n30 = UNUSED_1E\n31 = UNUSED_1F",
              5, old_value_t.ahb_mst_id, new_value_t.ahb_mst_id };
    m_bit_details_model.bits.append(entry);
    entry = { "31: enable:1",
              "1=enable\n0=disable",
              1, old_value_t.enable, new_value_t.enable };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "See the description of the pre-fetcher above.";
}

#define MEM_PREFETCH_CFG2_OFFSET 0xF0
#define MEM_PREFETCH_CFG2_UNDEFMASK 0x00000000
union mem_prefetch_cfg2_u {
    struct {
        unsigned int inactivity_timeout:16; /*  */
        unsigned int spec_throttle:5;       /* not used for Tegra 200 Series and beyond */
        unsigned int addr_bndry:5;          /* 2^(n+4) byte boundary. any value >16 will use n=16 */
        unsigned int ahb_mst_id:5;          /* AHBDMA master 0 = CPU 1 = COP 2 = VCP 3 = UNUSED_03 4 = IDE 5 = AHBDMA 6 = USB 7 = APBDMA 8 = XIO 9 = SDMMC1 10 = NAND_FLASH 11 = SNOR 12 = SDMMC4 13 = BSEV 14 = UNUSED_0E 15 = UNUSED_0F 12 = SDMMC4 16 = BSEA 17 = USB3 18 = USB2 19 = SDMMC2 20 = SDMMC3 21 = UNUSED_15 22 = UNUSED_16 23 = UNUSED_17 24 = UNUSED_18 25 = UNUSED_19 26 = UNUSED_1A 27 = UNUSED_1B 28 = UNUSED_1C 29 = UNUSED_1D 30 = UNUSED_1E 31 = UNUSED_1F */
        unsigned int enable:1;              /* 1=enable 0=disable */
    };

    u_int32_t reg32;
};

void GizmoDev::fill_mem_prefetch_cfg2_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const mem_prefetch_cfg2_u old_value_t = { .reg32 = value };
    const mem_prefetch_cfg2_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: inactivity_timeout:16",
              "",
              16, old_value_t.inactivity_timeout, new_value_t.inactivity_timeout };
    m_bit_details_model.bits.append(entry);
    entry = { "16: spec_throttle:5",
              "not used for Tegra 200 Series and beyond",
              5, old_value_t.spec_throttle, new_value_t.spec_throttle };
    m_bit_details_model.bits.append(entry);
    entry = { "21: addr_bndry:5",
              "2^(n+4) byte boundary. any value >16 will use n=16",
              5, old_value_t.addr_bndry, new_value_t.addr_bndry };
    m_bit_details_model.bits.append(entry);
    entry = { "26: ahb_mst_id:5",
              "AHBDMA master\n0 = CPU\n1 = COP\n2 = VCP\n3 = UNUSED_03\n4 = IDE\n5 = AHBDMA\n6 = USB\n7 = APBDMA\n8 = XIO\n9 = SDMMC1\n10 = NAND_FLASH\n11 = SNOR\n12 = SDMMC4\n13 = BSEV\n14 = UNUSED_0E\n15 = UNUSED_0F\n12 = SDMMC4\n16 = BSEA\n17 = USB3\n18 = USB2\n19 = SDMMC2\n20 = SDMMC3\n21 = UNUSED_15\n22 = UNUSED_16\n23 = UNUSED_17\n24 = UNUSED_18\n25 = UNUSED_19\n26 = UNUSED_1A\n27 = UNUSED_1B\n28 = UNUSED_1C\n29 = UNUSED_1D\n30 = UNUSED_1E\n31 = UNUSED_1F",
              5, old_value_t.ahb_mst_id, new_value_t.ahb_mst_id };
    m_bit_details_model.bits.append(entry);
    entry = { "31: enable:1",
              "1=enable\n0=disable",
              1, old_value_t.enable, new_value_t.enable };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "See the description of the pre-fetcher above.";
}

#define AHB_AHBSLVMEM_STATUS_OFFSET 0xF4
#define AHB_AHBSLVMEM_STATUS_UNDEFMASK 0xFFFFFFFC
union ahb_ahbslvmem_status_u {
    struct {
        unsigned int gizmo_ip_rdque_empty:1;
        unsigned int ppcs_rds_outstanding:1;
        unsigned int undefined_bits_2_31:30;
    };

    u_int32_t reg32;
};

void GizmoDev::fill_ahb_ahbslvmem_status_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const ahb_ahbslvmem_status_u old_value_t = { .reg32 = value };
    const ahb_ahbslvmem_status_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: gizmo_ip_rdque_empty:1", "", 1, old_value_t.gizmo_ip_rdque_empty, new_value_t.gizmo_ip_rdque_empty };
    m_bit_details_model.bits.append(entry);
    entry = { "01: ppcs_rds_outstanding:1", "", 1, old_value_t.ppcs_rds_outstanding, new_value_t.ppcs_rds_outstanding };
    m_bit_details_model.bits.append(entry);
    entry = { "02: undefined_bits_2_31:30", "", 30, old_value_t.undefined_bits_2_31, new_value_t.undefined_bits_2_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "0x6000_C0F8: ahbslv outstanding rd, rdque_empty status";
}

#define AHB_ARBITRATION_AHB_MEM_WRQUE_MST_ID_OFFSET 0xF8
#define AHB_ARBITRATION_AHB_MEM_WRQUE_MST_ID_UNDEFMASK 0x80000000
union ahb_arbitration_ahb_mem_wrque_mst_id_u {
    struct {
        unsigned int ahb_master_id:31;      /* 0 = there is no write data in the write queue from that AHB master */
        unsigned int undefined_bit_31:1;
    };

    u_int32_t reg32;
};

void GizmoDev::fill_ahb_arbitration_ahb_mem_wrque_mst_id_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const ahb_arbitration_ahb_mem_wrque_mst_id_u old_value_t = { .reg32 = value };
    const ahb_arbitration_ahb_mem_wrque_mst_id_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: ahb_master_id:31",
              "0 = there is no write data in the write queue from that AHB master",
              31, old_value_t.ahb_master_id, new_value_t.ahb_master_id };
    m_bit_details_model.bits.append(entry);
    entry = { "31: undefined_bit_31:1", "", 1, old_value_t.undefined_bit_31, new_value_t.undefined_bit_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "AHB Memory Write Queue AHB Master ID Register";
}

#define AHB_ARBITRATION_CPU_ABORT_INFO_OFFSET 0xFC
#define AHB_ARBITRATION_CPU_ABORT_INFO_UNDEFMASK 0xFFFF0000
union ahb_arbitration_cpu_abort_info_u {
    struct {
        unsigned int size:2;                /* Aborted transaction Request Size 00=byte, 01=hword, 10=word; 0 = BYTE_ABT; 1 = HWORD_ABT; 2 = WORD_ABT */
        unsigned int data:1;                /* Aborted transaction was a Data access; 0 = ABT_DIS; 1 = ABT_EN */
        unsigned int write:1;               /* Aborted transaction was a Write; 0 = ABT_DIS; 1 = ABT_EN */
        unsigned int badsize:1;             /* TRUE for abort caused by Bad Size (i.e. word access at odd byte address); 0 = ABT_DIS; 1 = ABT_EN */
        unsigned int align:1;               /* TRUE for abort caused by Misalignment (i.e. word access at odd byte address); 0 = ABT_DIS; 1 = ABT_EN */
        unsigned int protection:1;          /* TRUE for any protection violation; 0 = ABT_DIS; 1 = ABT_EN */
        unsigned int cache:1;               /* Abort occurred due to a Cache protection violation; 0 = ABT_DIS; 1 = ABT_EN */
        unsigned int ahb:1;                 /* Abort occurred due to an AHB protection violation; 0 = ABT_DIS; 1 = ABT_EN */
        unsigned int apb:1;                 /* Abort occurred due to an APB protection violation; 0 = ABT_DIS; 1 = ABT_EN */
        unsigned int ppsb:1;                /* Abort occurred due to a PPSB protection violation; 0 = ABT_DIS; 1 = ABT_EN */
        unsigned int inv_iram:1;            /* Abort occurred due to an access to invalid iRAM address space; 0 = ABT_DIS; 1 = ABT_EN */
        unsigned int iramd:1;               /* Abort occurred due to an iRAMd protection violation; 0 = ABT_DIS; 1 = ABT_EN */
        unsigned int iramc:1;               /* Abort occurred due to an iRAMc protection violation; 0 = ABT_DIS; 1 = ABT_EN */
        unsigned int iramb:1;               /* Abort occurred due to an iRAMb protection violation; 0 = ABT_DIS; 1 = ABT_EN */
        unsigned int irama:1;               /* Abort occurred due to an iRAMa protection violation; 0 = ABT_DIS; 1 = ABT_EN */
        unsigned int undefined_bits_16_31:16;
    };

    u_int32_t reg32;
};

void GizmoDev::fill_ahb_arbitration_cpu_abort_info_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const ahb_arbitration_cpu_abort_info_u old_value_t = { .reg32 = value };
    const ahb_arbitration_cpu_abort_info_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: size:2",
              "Aborted transaction Request Size\n00=byte,\n01=hword,\n10=word;\n0 = BYTE_ABT;\n1 = HWORD_ABT;\n2 = WORD_ABT",
              2, old_value_t.size, new_value_t.size };
    m_bit_details_model.bits.append(entry);
    entry = { "02: data:1",
              "Aborted transaction was a Data access;\n0 = ABT_DIS;\n1 = ABT_EN",
              1, old_value_t.data, new_value_t.data };
    m_bit_details_model.bits.append(entry);
    entry = { "03: write:1",
              "Aborted transaction was a Write;\n0 = ABT_DIS;\n1 = ABT_EN",
              1, old_value_t.write, new_value_t.write };
    m_bit_details_model.bits.append(entry);
    entry = { "04: badsize:1",
              "TRUE for abort caused by Bad Size (i.e. word access at odd byte address);\n0 = ABT_DIS;\n1 = ABT_EN",
              1, old_value_t.badsize, new_value_t.badsize };
    m_bit_details_model.bits.append(entry);
    entry = { "05: align:1",
              "TRUE for abort caused by Misalignment (i.e. word access at odd byte address);\n0 = ABT_DIS;\n1 = ABT_EN",
              1, old_value_t.align, new_value_t.align };
    m_bit_details_model.bits.append(entry);
    entry = { "06: protection:1",
              "TRUE for any protection violation;\n0 = ABT_DIS;\n1 = ABT_EN",
              1, old_value_t.protection, new_value_t.protection };
    m_bit_details_model.bits.append(entry);
    entry = { "07: cache:1",
              "Abort occurred due to a Cache protection violation;\n0 = ABT_DIS;\n1 = ABT_EN",
              1, old_value_t.cache, new_value_t.cache };
    m_bit_details_model.bits.append(entry);
    entry = { "08: ahb:1",
              "Abort occurred due to an AHB protection violation;\n0 = ABT_DIS;\n1 = ABT_EN",
              1, old_value_t.ahb, new_value_t.ahb };
    m_bit_details_model.bits.append(entry);
    entry = { "09: apb:1",
              "Abort occurred due to an APB protection violation;\n0 = ABT_DIS;\n1 = ABT_EN",
              1, old_value_t.apb, new_value_t.apb };
    m_bit_details_model.bits.append(entry);
    entry = { "10: ppsb:1",
              "Abort occurred due to a PPSB protection violation;\n0 = ABT_DIS;\n1 = ABT_EN",
              1, old_value_t.ppsb, new_value_t.ppsb };
    m_bit_details_model.bits.append(entry);
    entry = { "11: inv_iram:1",
              "Abort occurred due to an access to invalid iRAM address space;\n0 = ABT_DIS;\n1 = ABT_EN",
              1, old_value_t.inv_iram, new_value_t.inv_iram };
    m_bit_details_model.bits.append(entry);
    entry = { "12: iramd:1",
              "Abort occurred due to an iRAMd protection violation;\n0 = ABT_DIS;\n1 = ABT_EN",
              1, old_value_t.iramd, new_value_t.iramd };
    m_bit_details_model.bits.append(entry);
    entry = { "13: iramc:1",
              "Abort occurred due to an iRAMc protection violation;\n0 = ABT_DIS;\n1 = ABT_EN",
              1, old_value_t.iramc, new_value_t.iramc };
    m_bit_details_model.bits.append(entry);
    entry = { "14: iramb:1",
              "Abort occurred due to an iRAMb protection violation;\n0 = ABT_DIS;\n1 = ABT_EN",
              1, old_value_t.iramb, new_value_t.iramb };
    m_bit_details_model.bits.append(entry);
    entry = { "15: irama:1",
              "Abort occurred due to an iRAMa protection violation;\n0 = ABT_DIS;\n1 = ABT_EN",
              1, old_value_t.irama, new_value_t.irama };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_31:16", "", 16, old_value_t.undefined_bits_16_31, new_value_t.undefined_bits_16_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "CPU Abort Info Register";
}

#define AHB_ARBITRATION_CPU_ABORT_ADDR_OFFSET 0x100
#define AHB_ARBITRATION_CPU_ABORT_ADDR_UNDEFMASK 0x00000000
union ahb_arbitration_cpu_abort_addr_u {
    struct {
        unsigned int addr:32;               /* Instruction Address which caused the abort */
    };

    u_int32_t reg32;
};

void GizmoDev::fill_ahb_arbitration_cpu_abort_addr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const ahb_arbitration_cpu_abort_addr_u old_value_t = { .reg32 = value };
    const ahb_arbitration_cpu_abort_addr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: addr:32",
              "Instruction Address which caused the abort",
              32, old_value_t.addr, new_value_t.addr };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "CPU Abort Address Register";
}

#define AHB_ARBITRATION_COP_ABORT_INFO_OFFSET 0x104
#define AHB_ARBITRATION_COP_ABORT_INFO_UNDEFMASK 0xFFFF1800
union ahb_arbitration_cop_abort_info_u {
    struct {
        unsigned int size:2;                /* Aborted transaction Request Size 00=byte, 01=hword, 10=word; 0 = BYTE_ABT; 1 = HWORD_ABT; 2 = WORD_ABT */
        unsigned int data:1;                /* Aborted transaction was a Data access; 0 = ABT_DIS; 1 = ABT_EN */
        unsigned int write:1;               /* Aborted transaction was a Write; 0 = ABT_DIS; 1 = ABT_EN */
        unsigned int badsize:1;             /* TRUE for abort caused by Bad Size (i.e. word access at odd byte address); 0 = ABT_DIS; 1 = ABT_EN */
        unsigned int align:1;               /* TRUE for abort caused by Misalignment (i.e. word access at odd byte address); 0 = ABT_DIS; 1 = ABT_EN */
        unsigned int protection:1;          /* TRUE for any protection violation; 0 = ABT_DIS; 1 = ABT_EN */
        unsigned int cache:1;               /* Abort occurred due to a Cache protection violation; 0 = ABT_DIS; 1 = ABT_EN */
        unsigned int ahb:1;                 /* Abort occurred due to an AHB protection violation; 0 = ABT_DIS; 1 = ABT_EN */
        unsigned int apb:1;                 /* Abort occurred due to an APB protection violation; 0 = ABT_DIS; 1 = ABT_EN */
        unsigned int ppsb:1;                /* Abort occurred due to a PPSB protection violation; 0 = ABT_DIS; 1 = ABT_EN */
        unsigned int undefined_bits_11_12:2;
        unsigned int iramc:1;               /* Abort occurred due to an iRAMc protection violation; 0 = ABT_DIS; 1 = ABT_EN */
        unsigned int iramb:1;               /* Abort occurred due to an iRAMb protection violation; 0 = ABT_DIS; 1 = ABT_EN */
        unsigned int irama:1;               /* Abort occurred due to an iRAMa protection violation; 0 = ABT_DIS; 1 = ABT_EN */
        unsigned int undefined_bits_16_31:16;
    };

    u_int32_t reg32;
};

void GizmoDev::fill_ahb_arbitration_cop_abort_info_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const ahb_arbitration_cop_abort_info_u old_value_t = { .reg32 = value };
    const ahb_arbitration_cop_abort_info_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: size:2",
              "Aborted transaction Request Size\n00=byte,\n01=hword,\n10=word;\n0 = BYTE_ABT;\n1 = HWORD_ABT;\n2 = WORD_ABT",
              2, old_value_t.size, new_value_t.size };
    m_bit_details_model.bits.append(entry);
    entry = { "02: data:1",
              "Aborted transaction was a Data access;\n0 = ABT_DIS;\n1 = ABT_EN",
              1, old_value_t.data, new_value_t.data };
    m_bit_details_model.bits.append(entry);
    entry = { "03: write:1",
              "Aborted transaction was a Write;\n0 = ABT_DIS;\n1 = ABT_EN",
              1, old_value_t.write, new_value_t.write };
    m_bit_details_model.bits.append(entry);
    entry = { "04: badsize:1",
              "TRUE for abort caused by Bad Size (i.e. word access at odd byte address);\n0 = ABT_DIS;\n1 = ABT_EN",
              1, old_value_t.badsize, new_value_t.badsize };
    m_bit_details_model.bits.append(entry);
    entry = { "05: align:1",
              "TRUE for abort caused by Misalignment (i.e. word access at odd byte address);\n0 = ABT_DIS;\n1 = ABT_EN",
              1, old_value_t.align, new_value_t.align };
    m_bit_details_model.bits.append(entry);
    entry = { "06: protection:1",
              "TRUE for any protection violation;\n0 = ABT_DIS;\n1 = ABT_EN",
              1, old_value_t.protection, new_value_t.protection };
    m_bit_details_model.bits.append(entry);
    entry = { "07: cache:1",
              "Abort occurred due to a Cache protection violation;\n0 = ABT_DIS;\n1 = ABT_EN",
              1, old_value_t.cache, new_value_t.cache };
    m_bit_details_model.bits.append(entry);
    entry = { "08: ahb:1",
              "Abort occurred due to an AHB protection violation;\n0 = ABT_DIS;\n1 = ABT_EN",
              1, old_value_t.ahb, new_value_t.ahb };
    m_bit_details_model.bits.append(entry);
    entry = { "09: apb:1",
              "Abort occurred due to an APB protection violation;\n0 = ABT_DIS;\n1 = ABT_EN",
              1, old_value_t.apb, new_value_t.apb };
    m_bit_details_model.bits.append(entry);
    entry = { "10: ppsb:1",
              "Abort occurred due to a PPSB protection violation;\n0 = ABT_DIS;\n1 = ABT_EN",
              1, old_value_t.ppsb, new_value_t.ppsb };
    m_bit_details_model.bits.append(entry);
    entry = { "11: undefined_bits_11_12:2", "", 2, old_value_t.undefined_bits_11_12, new_value_t.undefined_bits_11_12 };
    m_bit_details_model.bits.append(entry);
    entry = { "13: iramc:1",
              "Abort occurred due to an iRAMc protection violation;\n0 = ABT_DIS;\n1 = ABT_EN",
              1, old_value_t.iramc, new_value_t.iramc };
    m_bit_details_model.bits.append(entry);
    entry = { "14: iramb:1",
              "Abort occurred due to an iRAMb protection violation;\n0 = ABT_DIS;\n1 = ABT_EN",
              1, old_value_t.iramb, new_value_t.iramb };
    m_bit_details_model.bits.append(entry);
    entry = { "15: irama:1",
              "Abort occurred due to an iRAMa protection violation;\n0 = ABT_DIS;\n1 = ABT_EN",
              1, old_value_t.irama, new_value_t.irama };
    m_bit_details_model.bits.append(entry);
    entry = { "16: undefined_bits_16_31:16", "", 16, old_value_t.undefined_bits_16_31, new_value_t.undefined_bits_16_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "COP Abort Info Register";
}

#define AHB_ARBITRATION_COP_ABORT_ADDR_OFFSET 0x108
#define AHB_ARBITRATION_COP_ABORT_ADDR_UNDEFMASK 0x00000000
union ahb_arbitration_cop_abort_addr_u {
    struct {
        unsigned int addr:32;               /* Instruction Address which caused the abort */
    };

    u_int32_t reg32;
};

void GizmoDev::fill_ahb_arbitration_cop_abort_addr_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const ahb_arbitration_cop_abort_addr_u old_value_t = { .reg32 = value };
    const ahb_arbitration_cop_abort_addr_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: addr:32",
              "Instruction Address which caused the abort",
              32, old_value_t.addr, new_value_t.addr };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "COP Abort Address Register";
}

#define AHB_AVPC_MCCIF_FIFOCTRL_OFFSET 0x23C
#define AHB_AVPC_MCCIF_FIFOCTRL_UNDEFMASK 0xFFFFFFF0
union ahb_avpc_mccif_fifoctrl_u {
    struct {
        unsigned int avpc_mccif_wrcl_mcle2x:1;/* 0 = DISABLE 1 = ENABLE */
        unsigned int avpc_mccif_rdmc_rdfast:1;/* 0 = DISABLE 1 = ENABLE */
        unsigned int avpc_mccif_wrmc_clle2x:1;/* 0 = DISABLE 1 = ENABLE */
        unsigned int avpc_mccif_rdcl_rdfast:1;/* 0 = DISABLE 1 = ENABLE */
        unsigned int undefined_bits_4_31:28;
    };

    u_int32_t reg32;
};

void GizmoDev::fill_ahb_avpc_mccif_fifoctrl_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const ahb_avpc_mccif_fifoctrl_u old_value_t = { .reg32 = value };
    const ahb_avpc_mccif_fifoctrl_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: avpc_mccif_wrcl_mcle2x:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.avpc_mccif_wrcl_mcle2x, new_value_t.avpc_mccif_wrcl_mcle2x };
    m_bit_details_model.bits.append(entry);
    entry = { "01: avpc_mccif_rdmc_rdfast:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.avpc_mccif_rdmc_rdfast, new_value_t.avpc_mccif_rdmc_rdfast };
    m_bit_details_model.bits.append(entry);
    entry = { "02: avpc_mccif_wrmc_clle2x:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.avpc_mccif_wrmc_clle2x, new_value_t.avpc_mccif_wrmc_clle2x };
    m_bit_details_model.bits.append(entry);
    entry = { "03: avpc_mccif_rdcl_rdfast:1",
              "0 = DISABLE\n1 = ENABLE",
              1, old_value_t.avpc_mccif_rdcl_rdfast, new_value_t.avpc_mccif_rdcl_rdfast };
    m_bit_details_model.bits.append(entry);
    entry = { "04: undefined_bits_4_31:28", "", 28, old_value_t.undefined_bits_4_31, new_value_t.undefined_bits_4_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "The registers below allow optimizing the synchronization timing in the memory client asynchronous FIFOs. When they can be used depends on the client and memory controller clock ratio.\n Additionally, the RDMC_RDFAST/RDCL_RDFAST fields can increase power consumption if the asynchronous FIFO is implemented as a real RAM. There is no power impact on latch-based FIFOs. Flipflop-based FIFOs do not use these fields.\nRecommended Settings\nClient writing to FIFO, memory controller reading from FIFO\n    * mcclk_freq <= clientclk_freq\nYou can enable both RDMC_RDFAST and WRCL_CLLE2X. If one of the FIFOs is a real RAM and power is a concern, avoid enabling RDMC_RDFAST.\n    * clientclk_freq < mcclk_freq <= 2 * clientclk_freq\nYou can enable RDMC_RDFAST or WRCL_MCLE2X, but because the client clock is slower, enable only WRCL_MCLE2X.\n    * 2 * clientclk_freq < mcclk_freq\nYou can only enable RDMC_RDFAST. If one of the FIFOs is a real RAM and power is a concern, avoid enabling RDMC_RDFAST.\nMemory controller writing to FIFO, client reading from FIFO\n    * clientclk_freq <= mcclk_freq\nYou can enable both RDCL_RDFAST and WRMC_CLLE2X. If one of the FIFOs is a real RAM and power is a concern, avoid enabling RDCL_RDFAST.\n    * mcclk_freq < clientclk_freq <= 2 * mcclk_freq\nYou can enable RDCL_RDFAST or WRMC_CLLE2X, but because the memory controller clock is slower, enable only WRMC_CLLE2X.\n    * 2 * mcclk_freq < clientclk_freq\nYou can only enable RDCL_RDFAST. If one of the FIFOs is a real RAM and power is a concern, avoid enabling RDCL_RDFAST.\nMemory Client Interface FIFO Control Register";
}

#define AHB_TIMEOUT_WCOAL_AVPC_OFFSET 0x240
#define AHB_TIMEOUT_WCOAL_AVPC_UNDEFMASK 0xFFFFFF00
union ahb_timeout_wcoal_avpc_u {
    struct {
        unsigned int avpcarm7w_wcoal_tmval:8;
        unsigned int undefined_bits_8_31:24;
    };

    u_int32_t reg32;
};

void GizmoDev::fill_ahb_timeout_wcoal_avpc_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const ahb_timeout_wcoal_avpc_u old_value_t = { .reg32 = value };
    const ahb_timeout_wcoal_avpc_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: avpcarm7w_wcoal_tmval:8", "", 8, old_value_t.avpcarm7w_wcoal_tmval, new_value_t.avpcarm7w_wcoal_tmval };
    m_bit_details_model.bits.append(entry);
    entry = { "08: undefined_bits_8_31:24", "", 24, old_value_t.undefined_bits_8_31, new_value_t.undefined_bits_8_31 };
    m_bit_details_model.bits.append(entry);

    m_bit_details_model.desc = "This register exists only for write clients. Reset value defaults to 50 for most clients, but may be different for certain clients.\n Write coalescing happens inside the memory client. Coalescing means two (NV_MC_MW/2)-bit requests are grouped together in one NV_MC_MW-bit request. The register value indicates how many cycles a first write request is going to wait for a subsequent one for possible coalescing. The coalescing can only happen if the request addresses are compatible. A value of zero means that coalescing is off and requests are sent right away to the memory controller.\n Write coalescing can have a very significant impact performance when accessing the internal memory, because its memory word is NV_MC_WM-bit wide. Grouping two half-word accesses is much more efficient, because the two accesses would actually have taken three cycles, due to a stall when accessing the same memory bank. It also reduces the number of accessing (one instead of two), freeing up internal memory bandwidth for other accesses.\n The impact on external memory accesses is not as significant as the burst access is for NV_MC_MW/2 bits. But a coalesced write guarantees two consecutive same page accesses which is good for external memory bandwidth utilization.\n The write coalescing time-out should be programmed depending on the client behavior. The first write is obviously delayed by an amount of client cycles equal to the time-out value.\nNote:\n Writes tagged by the client (i.e. the client expects a write response, usually for coherency), and the last write of a block transfer are not delayed. They only have a one-cycle opportunity to get coalesced.\nWrite Coalescing Time-Out Register";
}

#define AHB_ARBITRATION_DISABLE_OFFSET 0x0
#define AHB_ARBITRATION_DISABLE_UNDEFMASK 0x7FE0C000
union ahb_arbitration_disable_u {
    struct {
        unsigned int cpu:1;                 /*  1 = disable CPU from arbitration. */
        unsigned int cop:1;                 /*  1 = disable COP from arbitration. */
        unsigned int vcp:1;                 /*  1 = disable VCP from arbitration. */
        unsigned int csite:1;               /*  1 = disable CoreSight from arbitration. */
        unsigned int eide:1;                /*  1 = disable EIDE from arbitration. */
        unsigned int ahbdma:1;              /*  1 = disable AHB-DMA from arbitration. */
        unsigned int usb:1;                 /*  1 = disable USB from arbitration. */
        unsigned int apbdma:1;              /*  1 = disable APB-DMA from arbitration. */
        unsigned int xio:1;                 /*  1 = disable XIO from arbitration. */
        unsigned int sdmmc1:1;              /*  1 = disable SDMMC1 from arbitration. */
        unsigned int nand:1;                /*  1 = disable NAND from arbitration. */
        unsigned int snor:1;                /*  1 = disable SNOR from arbitration. */
        unsigned int sdmmc4:1;              /*  1 = disable SDMMC4 from arbitration. */
        unsigned int bsev:1;                /*  1 = disable BSEV from arbitration. */
        unsigned int undefined_bits_14_15:2;
        unsigned int bsea:1;                /*  1 = disable BSEA from arbitration. */
        unsigned int usb3:1;                /*  1 = disable USB3 from arbitration. */
        unsigned int usb2:1;                /*  1 = disable USB2 from arbitration. */
        unsigned int sdmmc2:1;              /*  1 = disable SDMMC2 from arbitration. */
        unsigned int sdmmc3:1;              /*  1 = disable SDMMC3 from arbitration. */
        unsigned int undefined_bits_21_30:10;
        unsigned int dis_bus_park:1;        /*  1 = disable bus parking. */
    };

    u_int32_t reg32;
};

void GizmoDev::fill_ahb_arbitration_disable_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const ahb_arbitration_disable_u old_value_t = { .reg32 = value };
    const ahb_arbitration_disable_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: cpu:1",
              "1 = disable CPU from arbitration.",
              1, old_value_t.cpu, new_value_t.cpu };
    m_bit_details_model.bits.append(entry);
    entry = { "01: cop:1",
              "1 = disable COP from arbitration.",
              1, old_value_t.cop, new_value_t.cop };
    m_bit_details_model.bits.append(entry);
    entry = { "02: vcp:1",
              "1 = disable VCP from arbitration.",
              1, old_value_t.vcp, new_value_t.vcp };
    m_bit_details_model.bits.append(entry);
    entry = { "03: csite:1",
              "1 = disable CoreSight from arbitration.",
              1, old_value_t.csite, new_value_t.csite };
    m_bit_details_model.bits.append(entry);
    entry = { "04: eide:1",
              "1 = disable EIDE from arbitration.",
              1, old_value_t.eide, new_value_t.eide };
    m_bit_details_model.bits.append(entry);
    entry = { "05: ahbdma:1",
              "1 = disable AHB-DMA from arbitration.",
              1, old_value_t.ahbdma, new_value_t.ahbdma };
    m_bit_details_model.bits.append(entry);
    entry = { "06: usb:1",
              "1 = disable USB from arbitration.",
              1, old_value_t.usb, new_value_t.usb };
    m_bit_details_model.bits.append(entry);
    entry = { "07: apbdma:1",
              "1 = disable APB-DMA from arbitration.",
              1, old_value_t.apbdma, new_value_t.apbdma };
    m_bit_details_model.bits.append(entry);
    entry = { "08: xio:1",
              "1 = disable XIO from arbitration.",
              1, old_value_t.xio, new_value_t.xio };
    m_bit_details_model.bits.append(entry);
    entry = { "09: sdmmc1:1",
              "1 = disable SDMMC1 from arbitration.",
              1, old_value_t.sdmmc1, new_value_t.sdmmc1 };
    m_bit_details_model.bits.append(entry);
    entry = { "10: nand:1",
              "1 = disable NAND from arbitration.",
              1, old_value_t.nand, new_value_t.nand };
    m_bit_details_model.bits.append(entry);
    entry = { "11: snor:1",
              "1 = disable SNOR from arbitration.",
              1, old_value_t.snor, new_value_t.snor };
    m_bit_details_model.bits.append(entry);
    entry = { "12: sdmmc4:1",
              "1 = disable SDMMC4 from arbitration.",
              1, old_value_t.sdmmc4, new_value_t.sdmmc4 };
    m_bit_details_model.bits.append(entry);
    entry = { "13: bsev:1",
              "1 = disable BSEV from arbitration.",
              1, old_value_t.bsev, new_value_t.bsev };
    m_bit_details_model.bits.append(entry);
    entry = { "14: undefined_bits_14_15:2", "", 2, old_value_t.undefined_bits_14_15, new_value_t.undefined_bits_14_15 };
    m_bit_details_model.bits.append(entry);
    entry = { "16: bsea:1",
              "1 = disable BSEA from arbitration.",
              1, old_value_t.bsea, new_value_t.bsea };
    m_bit_details_model.bits.append(entry);
    entry = { "17: usb3:1",
              "1 = disable USB3 from arbitration.",
              1, old_value_t.usb3, new_value_t.usb3 };
    m_bit_details_model.bits.append(entry);
    entry = { "18: usb2:1",
              "1 = disable USB2 from arbitration.",
              1, old_value_t.usb2, new_value_t.usb2 };
    m_bit_details_model.bits.append(entry);
    entry = { "19: sdmmc2:1",
              "1 = disable SDMMC2 from arbitration.",
              1, old_value_t.sdmmc2, new_value_t.sdmmc2 };
    m_bit_details_model.bits.append(entry);
    entry = { "20: sdmmc3:1",
              "1 = disable SDMMC3 from arbitration.",
              1, old_value_t.sdmmc3, new_value_t.sdmmc3 };
    m_bit_details_model.bits.append(entry);
    entry = { "21: undefined_bits_21_30:10", "", 10, old_value_t.undefined_bits_21_30, new_value_t.undefined_bits_21_30 };
    m_bit_details_model.bits.append(entry);
    entry = { "31: dis_bus_park:1",
              "1 = disable bus parking.",
              1, old_value_t.dis_bus_park, new_value_t.dis_bus_park };
    m_bit_details_model.bits.append(entry);
}

#define AHB_ARBITRATION_PRIORITY_CTRL_OFFSET 0x4
#define AHB_ARBITRATION_PRIORITY_CTRL_UNDEFMASK 0x00000000
union ahb_arbitration_priority_ctrl_u {
    struct {
        unsigned int ahb_priority_select:29;/*  0 = low priority */
        unsigned int ahb_priority_weight:3; /* AHB priority weight count. This 3-bit field is  use to control  the amount of attention (weight) giving to the high priority  group before switching to the low priority group. */
    };

    u_int32_t reg32;
};

void GizmoDev::fill_ahb_arbitration_priority_ctrl_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const ahb_arbitration_priority_ctrl_u old_value_t = { .reg32 = value };
    const ahb_arbitration_priority_ctrl_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: ahb_priority_select:29",
              "0 = low priority",
              29, old_value_t.ahb_priority_select, new_value_t.ahb_priority_select };
    m_bit_details_model.bits.append(entry);
    entry = { "29: ahb_priority_weight:3",
              "AHB priority weight count. This 3-bit field is  use to control  the amount of attention (weight) giving to the high priority  group before switching to the low priority group.",
              3, old_value_t.ahb_priority_weight, new_value_t.ahb_priority_weight };
    m_bit_details_model.bits.append(entry);
}

#define AHB_ARBITRATION_USR_PROTECT_OFFSET 0x8
#define AHB_ARBITRATION_USR_PROTECT_UNDEFMASK 0xFFFFFE00
union ahb_arbitration_usr_protect_u {
    struct {
        unsigned int irama:1;               /* Abort on USR mode access to iRAMa memory space */
        unsigned int iramb:1;               /* Abort on USR mode access to iRAMb memory space */
        unsigned int iramc:1;               /* Abort on USR mode access to iRAMc memory space */
        unsigned int iramd:1;               /* Abort on USR mode access to iRAMd memory space */
        unsigned int ppsb:1;                /* Abort on USR mode access to PPSB memory space */
        unsigned int ahb:1;                 /* Abort on USR mode access to AHB memory space */
        unsigned int apb:1;                 /* Abort on USR mode access to APB memory space */
        unsigned int rom:1;                 /* Abort on USR mode access to internal ROM memory  space */
        unsigned int cache:1;               /* Abort on USR mode access to Cache memory space */
        unsigned int undefined_bits_9_31:23;
    };

    u_int32_t reg32;
};

void GizmoDev::fill_ahb_arbitration_usr_protect_details(const u_int32_t &value, const u_int32_t &new_value)
{
    const ahb_arbitration_usr_protect_u old_value_t = { .reg32 = value };
    const ahb_arbitration_usr_protect_u new_value_t = { .reg32 = new_value };
    BitDetails::bit_entry entry;

    m_bit_details_model.has_changed_bits = (value != new_value);

    entry = { "00: irama:1",
              "Abort on USR mode access to iRAMa memory space",
              1, old_value_t.irama, new_value_t.irama };
    m_bit_details_model.bits.append(entry);
    entry = { "01: iramb:1",
              "Abort on USR mode access to iRAMb memory space",
              1, old_value_t.iramb, new_value_t.iramb };
    m_bit_details_model.bits.append(entry);
    entry = { "02: iramc:1",
              "Abort on USR mode access to iRAMc memory space",
              1, old_value_t.iramc, new_value_t.iramc };
    m_bit_details_model.bits.append(entry);
    entry = { "03: iramd:1",
              "Abort on USR mode access to iRAMd memory space",
              1, old_value_t.iramd, new_value_t.iramd };
    m_bit_details_model.bits.append(entry);
    entry = { "04: ppsb:1",
              "Abort on USR mode access to PPSB memory space",
              1, old_value_t.ppsb, new_value_t.ppsb };
    m_bit_details_model.bits.append(entry);
    entry = { "05: ahb:1",
              "Abort on USR mode access to AHB memory space",
              1, old_value_t.ahb, new_value_t.ahb };
    m_bit_details_model.bits.append(entry);
    entry = { "06: apb:1",
              "Abort on USR mode access to APB memory space",
              1, old_value_t.apb, new_value_t.apb };
    m_bit_details_model.bits.append(entry);
    entry = { "07: rom:1",
              "Abort on USR mode access to internal ROM memory  space",
              1, old_value_t.rom, new_value_t.rom };
    m_bit_details_model.bits.append(entry);
    entry = { "08: cache:1",
              "Abort on USR mode access to Cache memory space",
              1, old_value_t.cache, new_value_t.cache };
    m_bit_details_model.bits.append(entry);
    entry = { "09: undefined_bits_9_31:23", "", 23, old_value_t.undefined_bits_9_31, new_value_t.undefined_bits_9_31 };
    m_bit_details_model.bits.append(entry);
}

bool GizmoDev::is_offset_valid(const u_int32_t &offset) const
{
    switch (offset) {
    case AHB_MEM_OFFSET:
    case APB_DMA_OFFSET:
    case IDE_OFFSET:
    case USB_OFFSET:
    case AHB_XBAR_BRIDGE_OFFSET:
    case CPU_AHB_BRIDGE_OFFSET:
    case COP_AHB_BRIDGE_OFFSET:
    case XBAR_APB_CTLR_OFFSET:
    case VCP_AHB_BRIDGE_OFFSET:
    case NAND_OFFSET:
    case SDMMC4_OFFSET:
    case XIO_OFFSET:
    case BSEV_OFFSET:
    case BSEA_OFFSET:
    case NOR_OFFSET:
    case USB2_OFFSET:
    case USB3_OFFSET:
    case SDMMC1_OFFSET:
    case SDMMC2_OFFSET:
    case SDMMC3_OFFSET:
    case MEM_PREFETCH_CFG_X_OFFSET:
    case AHB_ARBITRATION_XBAR_CTRL_OFFSET:
    case MEM_PREFETCH_CFG3_OFFSET:
    case MEM_PREFETCH_CFG4_OFFSET:
    case AHB_AVP_PPCS_RD_COH_STATUS_OFFSET:
    case MEM_PREFETCH_CFG1_OFFSET:
    case MEM_PREFETCH_CFG2_OFFSET:
    case AHB_AHBSLVMEM_STATUS_OFFSET:
    case AHB_ARBITRATION_AHB_MEM_WRQUE_MST_ID_OFFSET:
    case AHB_ARBITRATION_CPU_ABORT_INFO_OFFSET:
    case AHB_ARBITRATION_CPU_ABORT_ADDR_OFFSET:
    case AHB_ARBITRATION_COP_ABORT_INFO_OFFSET:
    case AHB_ARBITRATION_COP_ABORT_ADDR_OFFSET:
    case AHB_AVPC_MCCIF_FIFOCTRL_OFFSET:
    case AHB_TIMEOUT_WCOAL_AVPC_OFFSET:
    case AHB_ARBITRATION_DISABLE_OFFSET:
    case AHB_ARBITRATION_PRIORITY_CTRL_OFFSET:
    case AHB_ARBITRATION_USR_PROTECT_OFFSET:
        return true;
    default:
        break;
    }

    return false;
}

bool GizmoDev::is_undef_changed(const u_int32_t &offset,
                                           const u_int32_t &value,
                                           const u_int32_t &new_value) const
{
    switch (offset) {
    case AHB_MEM_OFFSET:
        if ((value ^ new_value) & AHB_MEM_UNDEFMASK)
            return true;
        break;
    case APB_DMA_OFFSET:
        if ((value ^ new_value) & APB_DMA_UNDEFMASK)
            return true;
        break;
    case IDE_OFFSET:
        if ((value ^ new_value) & IDE_UNDEFMASK)
            return true;
        break;
    case USB_OFFSET:
        if ((value ^ new_value) & USB_UNDEFMASK)
            return true;
        break;
    case AHB_XBAR_BRIDGE_OFFSET:
        if ((value ^ new_value) & AHB_XBAR_BRIDGE_UNDEFMASK)
            return true;
        break;
    case CPU_AHB_BRIDGE_OFFSET:
        if ((value ^ new_value) & CPU_AHB_BRIDGE_UNDEFMASK)
            return true;
        break;
    case COP_AHB_BRIDGE_OFFSET:
        if ((value ^ new_value) & COP_AHB_BRIDGE_UNDEFMASK)
            return true;
        break;
    case XBAR_APB_CTLR_OFFSET:
        if ((value ^ new_value) & XBAR_APB_CTLR_UNDEFMASK)
            return true;
        break;
    case VCP_AHB_BRIDGE_OFFSET:
        if ((value ^ new_value) & VCP_AHB_BRIDGE_UNDEFMASK)
            return true;
        break;
    case NAND_OFFSET:
        if ((value ^ new_value) & NAND_UNDEFMASK)
            return true;
        break;
    case SDMMC4_OFFSET:
        if ((value ^ new_value) & SDMMC4_UNDEFMASK)
            return true;
        break;
    case XIO_OFFSET:
        if ((value ^ new_value) & XIO_UNDEFMASK)
            return true;
        break;
    case BSEV_OFFSET:
        if ((value ^ new_value) & BSEV_UNDEFMASK)
            return true;
        break;
    case BSEA_OFFSET:
        if ((value ^ new_value) & BSEA_UNDEFMASK)
            return true;
        break;
    case NOR_OFFSET:
        if ((value ^ new_value) & NOR_UNDEFMASK)
            return true;
        break;
    case USB2_OFFSET:
        if ((value ^ new_value) & USB2_UNDEFMASK)
            return true;
        break;
    case USB3_OFFSET:
        if ((value ^ new_value) & USB3_UNDEFMASK)
            return true;
        break;
    case SDMMC1_OFFSET:
        if ((value ^ new_value) & SDMMC1_UNDEFMASK)
            return true;
        break;
    case SDMMC2_OFFSET:
        if ((value ^ new_value) & SDMMC2_UNDEFMASK)
            return true;
        break;
    case SDMMC3_OFFSET:
        if ((value ^ new_value) & SDMMC3_UNDEFMASK)
            return true;
        break;
    case MEM_PREFETCH_CFG_X_OFFSET:
        if ((value ^ new_value) & MEM_PREFETCH_CFG_X_UNDEFMASK)
            return true;
        break;
    case AHB_ARBITRATION_XBAR_CTRL_OFFSET:
        if ((value ^ new_value) & AHB_ARBITRATION_XBAR_CTRL_UNDEFMASK)
            return true;
        break;
    case MEM_PREFETCH_CFG3_OFFSET:
        if ((value ^ new_value) & MEM_PREFETCH_CFG3_UNDEFMASK)
            return true;
        break;
    case MEM_PREFETCH_CFG4_OFFSET:
        if ((value ^ new_value) & MEM_PREFETCH_CFG4_UNDEFMASK)
            return true;
        break;
    case AHB_AVP_PPCS_RD_COH_STATUS_OFFSET:
        if ((value ^ new_value) & AHB_AVP_PPCS_RD_COH_STATUS_UNDEFMASK)
            return true;
        break;
    case MEM_PREFETCH_CFG1_OFFSET:
        if ((value ^ new_value) & MEM_PREFETCH_CFG1_UNDEFMASK)
            return true;
        break;
    case MEM_PREFETCH_CFG2_OFFSET:
        if ((value ^ new_value) & MEM_PREFETCH_CFG2_UNDEFMASK)
            return true;
        break;
    case AHB_AHBSLVMEM_STATUS_OFFSET:
        if ((value ^ new_value) & AHB_AHBSLVMEM_STATUS_UNDEFMASK)
            return true;
        break;
    case AHB_ARBITRATION_AHB_MEM_WRQUE_MST_ID_OFFSET:
        if ((value ^ new_value) & AHB_ARBITRATION_AHB_MEM_WRQUE_MST_ID_UNDEFMASK)
            return true;
        break;
    case AHB_ARBITRATION_CPU_ABORT_INFO_OFFSET:
        if ((value ^ new_value) & AHB_ARBITRATION_CPU_ABORT_INFO_UNDEFMASK)
            return true;
        break;
    case AHB_ARBITRATION_CPU_ABORT_ADDR_OFFSET:
        if ((value ^ new_value) & AHB_ARBITRATION_CPU_ABORT_ADDR_UNDEFMASK)
            return true;
        break;
    case AHB_ARBITRATION_COP_ABORT_INFO_OFFSET:
        if ((value ^ new_value) & AHB_ARBITRATION_COP_ABORT_INFO_UNDEFMASK)
            return true;
        break;
    case AHB_ARBITRATION_COP_ABORT_ADDR_OFFSET:
        if ((value ^ new_value) & AHB_ARBITRATION_COP_ABORT_ADDR_UNDEFMASK)
            return true;
        break;
    case AHB_AVPC_MCCIF_FIFOCTRL_OFFSET:
        if ((value ^ new_value) & AHB_AVPC_MCCIF_FIFOCTRL_UNDEFMASK)
            return true;
        break;
    case AHB_TIMEOUT_WCOAL_AVPC_OFFSET:
        if ((value ^ new_value) & AHB_TIMEOUT_WCOAL_AVPC_UNDEFMASK)
            return true;
        break;
    case AHB_ARBITRATION_DISABLE_OFFSET:
        if ((value ^ new_value) & AHB_ARBITRATION_DISABLE_UNDEFMASK)
            return true;
        break;
    case AHB_ARBITRATION_PRIORITY_CTRL_OFFSET:
        if ((value ^ new_value) & AHB_ARBITRATION_PRIORITY_CTRL_UNDEFMASK)
            return true;
        break;
    case AHB_ARBITRATION_USR_PROTECT_OFFSET:
        if ((value ^ new_value) & AHB_ARBITRATION_USR_PROTECT_UNDEFMASK)
            return true;
        break;

    default:
        break;
    }

    return false;
}

QString GizmoDev::get_register_name(const log_entry &entry) const
{
    switch (entry.offset) {
    case AHB_MEM_OFFSET:
        return QString("AHB_MEM");
    case APB_DMA_OFFSET:
        return QString("APB_DMA");
    case IDE_OFFSET:
        return QString("IDE");
    case USB_OFFSET:
        return QString("USB");
    case AHB_XBAR_BRIDGE_OFFSET:
        return QString("AHB_XBAR_BRIDGE");
    case CPU_AHB_BRIDGE_OFFSET:
        return QString("CPU_AHB_BRIDGE");
    case COP_AHB_BRIDGE_OFFSET:
        return QString("COP_AHB_BRIDGE");
    case XBAR_APB_CTLR_OFFSET:
        return QString("XBAR_APB_CTLR");
    case VCP_AHB_BRIDGE_OFFSET:
        return QString("VCP_AHB_BRIDGE");
    case NAND_OFFSET:
        return QString("NAND");
    case SDMMC4_OFFSET:
        return QString("SDMMC4");
    case XIO_OFFSET:
        return QString("XIO");
    case BSEV_OFFSET:
        return QString("BSEV");
    case BSEA_OFFSET:
        return QString("BSEA");
    case NOR_OFFSET:
        return QString("NOR");
    case USB2_OFFSET:
        return QString("USB2");
    case USB3_OFFSET:
        return QString("USB3");
    case SDMMC1_OFFSET:
        return QString("SDMMC1");
    case SDMMC2_OFFSET:
        return QString("SDMMC2");
    case SDMMC3_OFFSET:
        return QString("SDMMC3");
    case MEM_PREFETCH_CFG_X_OFFSET:
        return QString("MEM_PREFETCH_CFG_X");
    case AHB_ARBITRATION_XBAR_CTRL_OFFSET:
        return QString("AHB_ARBITRATION_XBAR_CTRL");
    case MEM_PREFETCH_CFG3_OFFSET:
        return QString("MEM_PREFETCH_CFG3");
    case MEM_PREFETCH_CFG4_OFFSET:
        return QString("MEM_PREFETCH_CFG4");
    case AHB_AVP_PPCS_RD_COH_STATUS_OFFSET:
        return QString("AHB_AVP_PPCS_RD_COH_STATUS");
    case MEM_PREFETCH_CFG1_OFFSET:
        return QString("MEM_PREFETCH_CFG1");
    case MEM_PREFETCH_CFG2_OFFSET:
        return QString("MEM_PREFETCH_CFG2");
    case AHB_AHBSLVMEM_STATUS_OFFSET:
        return QString("AHB_AHBSLVMEM_STATUS");
    case AHB_ARBITRATION_AHB_MEM_WRQUE_MST_ID_OFFSET:
        return QString("AHB_ARBITRATION_AHB_MEM_WRQUE_MST_ID");
    case AHB_ARBITRATION_CPU_ABORT_INFO_OFFSET:
        return QString("AHB_ARBITRATION_CPU_ABORT_INFO");
    case AHB_ARBITRATION_CPU_ABORT_ADDR_OFFSET:
        return QString("AHB_ARBITRATION_CPU_ABORT_ADDR");
    case AHB_ARBITRATION_COP_ABORT_INFO_OFFSET:
        return QString("AHB_ARBITRATION_COP_ABORT_INFO");
    case AHB_ARBITRATION_COP_ABORT_ADDR_OFFSET:
        return QString("AHB_ARBITRATION_COP_ABORT_ADDR");
    case AHB_AVPC_MCCIF_FIFOCTRL_OFFSET:
        return QString("AHB_AVPC_MCCIF_FIFOCTRL");
    case AHB_TIMEOUT_WCOAL_AVPC_OFFSET:
        return QString("AHB_TIMEOUT_WCOAL_AVPC");
    case AHB_ARBITRATION_DISABLE_OFFSET:
        return QString("AHB_ARBITRATION_DISABLE");
    case AHB_ARBITRATION_PRIORITY_CTRL_OFFSET:
        return QString("AHB_ARBITRATION_PRIORITY_CTRL");
    case AHB_ARBITRATION_USR_PROTECT_OFFSET:
        return QString("AHB_ARBITRATION_USR_PROTECT");

    default:
        break;
    }

    qDebug() << QString().sprintf("GIZMO: %s: Ooops... 0x%x", __func__, entry.offset);

    return QString().sprintf("Ooops... @0x%X", entry.offset);
}

void GizmoDev::fill_bits_details(const u_int32_t &offset,
                                      const u_int32_t &value, const u_int32_t &new_value)
{
    switch (offset) {
    case AHB_MEM_OFFSET:
        fill_ahb_mem_details(value, new_value);
        break;
    case APB_DMA_OFFSET:
        fill_apb_dma_details(value, new_value);
        break;
    case IDE_OFFSET:
        fill_ide_details(value, new_value);
        break;
    case USB_OFFSET:
        fill_usb_details(value, new_value);
        break;
    case AHB_XBAR_BRIDGE_OFFSET:
        fill_ahb_xbar_bridge_details(value, new_value);
        break;
    case CPU_AHB_BRIDGE_OFFSET:
        fill_cpu_ahb_bridge_details(value, new_value);
        break;
    case COP_AHB_BRIDGE_OFFSET:
        fill_cop_ahb_bridge_details(value, new_value);
        break;
    case XBAR_APB_CTLR_OFFSET:
        fill_xbar_apb_ctlr_details(value, new_value);
        break;
    case VCP_AHB_BRIDGE_OFFSET:
        fill_vcp_ahb_bridge_details(value, new_value);
        break;
    case NAND_OFFSET:
        fill_nand_details(value, new_value);
        break;
    case SDMMC4_OFFSET:
        fill_sdmmc4_details(value, new_value);
        break;
    case XIO_OFFSET:
        fill_xio_details(value, new_value);
        break;
    case BSEV_OFFSET:
        fill_bsev_details(value, new_value);
        break;
    case BSEA_OFFSET:
        fill_bsea_details(value, new_value);
        break;
    case NOR_OFFSET:
        fill_nor_details(value, new_value);
        break;
    case USB2_OFFSET:
        fill_usb2_details(value, new_value);
        break;
    case USB3_OFFSET:
        fill_usb3_details(value, new_value);
        break;
    case SDMMC1_OFFSET:
        fill_sdmmc1_details(value, new_value);
        break;
    case SDMMC2_OFFSET:
        fill_sdmmc2_details(value, new_value);
        break;
    case SDMMC3_OFFSET:
        fill_sdmmc3_details(value, new_value);
        break;
    case MEM_PREFETCH_CFG_X_OFFSET:
        fill_mem_prefetch_cfg_x_details(value, new_value);
        break;
    case AHB_ARBITRATION_XBAR_CTRL_OFFSET:
        fill_ahb_arbitration_xbar_ctrl_details(value, new_value);
        break;
    case MEM_PREFETCH_CFG3_OFFSET:
        fill_mem_prefetch_cfg3_details(value, new_value);
        break;
    case MEM_PREFETCH_CFG4_OFFSET:
        fill_mem_prefetch_cfg4_details(value, new_value);
        break;
    case AHB_AVP_PPCS_RD_COH_STATUS_OFFSET:
        fill_ahb_avp_ppcs_rd_coh_status_details(value, new_value);
        break;
    case MEM_PREFETCH_CFG1_OFFSET:
        fill_mem_prefetch_cfg1_details(value, new_value);
        break;
    case MEM_PREFETCH_CFG2_OFFSET:
        fill_mem_prefetch_cfg2_details(value, new_value);
        break;
    case AHB_AHBSLVMEM_STATUS_OFFSET:
        fill_ahb_ahbslvmem_status_details(value, new_value);
        break;
    case AHB_ARBITRATION_AHB_MEM_WRQUE_MST_ID_OFFSET:
        fill_ahb_arbitration_ahb_mem_wrque_mst_id_details(value, new_value);
        break;
    case AHB_ARBITRATION_CPU_ABORT_INFO_OFFSET:
        fill_ahb_arbitration_cpu_abort_info_details(value, new_value);
        break;
    case AHB_ARBITRATION_CPU_ABORT_ADDR_OFFSET:
        fill_ahb_arbitration_cpu_abort_addr_details(value, new_value);
        break;
    case AHB_ARBITRATION_COP_ABORT_INFO_OFFSET:
        fill_ahb_arbitration_cop_abort_info_details(value, new_value);
        break;
    case AHB_ARBITRATION_COP_ABORT_ADDR_OFFSET:
        fill_ahb_arbitration_cop_abort_addr_details(value, new_value);
        break;
    case AHB_AVPC_MCCIF_FIFOCTRL_OFFSET:
        fill_ahb_avpc_mccif_fifoctrl_details(value, new_value);
        break;
    case AHB_TIMEOUT_WCOAL_AVPC_OFFSET:
        fill_ahb_timeout_wcoal_avpc_details(value, new_value);
        break;
    case AHB_ARBITRATION_DISABLE_OFFSET:
        fill_ahb_arbitration_disable_details(value, new_value);
        break;
    case AHB_ARBITRATION_PRIORITY_CTRL_OFFSET:
        fill_ahb_arbitration_priority_ctrl_details(value, new_value);
        break;
    case AHB_ARBITRATION_USR_PROTECT_OFFSET:
        fill_ahb_arbitration_usr_protect_details(value, new_value);
        break;

    default:
        m_bit_details_model.bits.clear();
        break;
    }
}
