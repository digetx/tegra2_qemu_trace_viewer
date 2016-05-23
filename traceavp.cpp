/*
 * Copyright (c) 2015 Dmitry Osipenko <digetx@gmail.com>
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

#include <QCheckBox>
#include <QDate>
#include "ui_mainwindow.h"

#include "devices/emcdev.h"
#include "devices/mcdev.h"
#include "devices/gizmodev.h"
#include "devices/apb_dmadev.h"
#include "devices/apb_miscdev.h"
#include "devices/cardev.h"
#include "devices/flowdev.h"
#include "devices/gpiodev.h"
#include "devices/pmcdev.h"
#include "devices/rtcdev.h"
#include "devices/sdhcidev.h"
#include "devices/timer_usdev.h"
#include "devices/timerdev.h"
#include "devices/uartdev.h"
#include "devices/fusedev.h"
#include "devices/dcdev.h"
#include "devices/bsedev.h"
#include "devices/host1x_channeldev.h"
#include "devices/host1x_syncdev.h"
#include "devices/arb_semadev.h"
#include "devices/arb_gnt_ictlrdev.h"
#include "devices/evpdev.h"
#include "devices/ictlr_pridev.h"
#include "devices/ictlr_secdev.h"
#include "devices/ictlr_tridev.h"
#include "devices/ictlr_quaddev.h"
#include "devices/host1x_dev.h"
#include "devices/gr2ddev.h"
#include "devices/avp_cch.h"
#include "devices/res_semadev.h"
#include "devices/dummydev.h"

#include "iomap.h"
#include "traceavp.h"

#define RECORD_IRQ      0
#define RECORD_READ     1
#define RECORD_WRITE    2

TraceAVP::TraceAVP(MainWindow *window, QString name, QFile *recfile,
                   QObject *parent) :
      TraceCPU(window, name, recfile, parent)
{
    addDevice( new EmcDev(this, "emc", TEGRA_EMC_BASE) );
    addDevice( new McDev(this, "mc", TEGRA_MC_BASE) );
    addDevice( new GizmoDev(this, "ahb_gizmo", TEGRA_AHB_GIZMO_BASE) );
    addDevice( new FuseDev(this, "apb fuse", TEGRA_FUSE_BASE) );
    addDevice( new Apb_dmaDev(this, "apb_dma", TEGRA_APB_DMA_BASE) );
    addDevice( new Apb_miscDev(this, "apb_misc", TEGRA_APB_MISC_BASE) );
    addDevice( new CarDev(this, "car", TEGRA_CLK_RESET_BASE) );
    addDevice( new FlowDev(this, "flow", TEGRA_FLOW_CTRL_BASE) );
    addDevice( new GpioDev(this, "gpio", TEGRA_GPIO_BASE) );
    addDevice( new PmcDev(this, "pmc", TEGRA_PMC_BASE) );
    addDevice( new RtcDev(this, "rtc", TEGRA_RTC_BASE) );
    addDevice( new TimerDev(this, "timer1", TEGRA_TMR1_BASE) );
    addDevice( new TimerDev(this, "timer2", TEGRA_TMR2_BASE) );
    addDevice( new Timer_usDev(this, "timer_us", TEGRA_TMRUS_BASE) );
    addDevice( new TimerDev(this, "timer3", TEGRA_TMR3_BASE) );
    addDevice( new TimerDev(this, "timer4", TEGRA_TMR4_BASE) );
    addDevice( new DummyDev(this, "ucq", 0x60010000) );
    addDevice( new BseDev(this, "bsea", TEGRA_BSEA_BASE + 0x1000) );
    addDevice( new DummyDev(this, "sxe", 0x6001A000) );
    addDevice( new BseDev(this, "bsev", TEGRA_VDE_BASE + 0x1000) );
    addDevice( new DummyDev(this, "mbe", 0x6001C000) );
    addDevice( new DummyDev(this, "ppe", 0x6001C200) );
    addDevice( new DummyDev(this, "mce", 0x6001C400) );
    addDevice( new DummyDev(this, "tfe", 0x6001C600) );
    addDevice( new DummyDev(this, "ppb", 0x6001C800) );
    addDevice( new DummyDev(this, "vdma", 0x6001CA00) );
    addDevice( new DummyDev(this, "ucq", 0x6001CC00) );
    addDevice( new DummyDev(this, "bsea", 0x6001D000) );
    addDevice( new DummyDev(this, "frameid", 0x6001D800) );
//    addDevice( new Host1x_channelDev(this, "host1x_ch_prot", TEGRA_HOST1X_BASE + 0x20000) );
    addDevice( new Res_semaDev(this, "res_sema", TEGRA_RES_SEMA_BASE) );
    addDevice( new Arb_semaDev(this, "arb_sema", TEGRA_ARB_SEMA_BASE) );
    addDevice( new Arb_gnt_ictlrDev(this, "arb_gnt_icrtrl", TEGRA_ARBGNT_ICTLR_BASE) );
    addDevice( new SdhciDev(this, "sdhci4", TEGRA_SDMMC4_BASE) );
    addDevice( new EvpDev(this, "evp", TEGRA_EXCEPTION_VECTORS_BASE) );
    addDevice( new Ictlr_priDev(this, "ictlr_pri", TEGRA_PRIMARY_ICTLR_BASE) );
    addDevice( new Ictlr_secDev(this, "ictlr_sec", TEGRA_SECONDARY_ICTLR_BASE) );
    addDevice( new Ictlr_triDev(this, "ictlr_tri", TEGRA_TERTIARY_ICTLR_BASE) );
    addDevice( new Ictlr_quadDev(this, "ictlr_quad", TEGRA_QUATERNARY_ICTLR_BASE) );
    addDevice( new AVP_CchDev(this, "AVP_MMU", 0xF0000000) );

    addDevice( new Host1x_channelDev(this, "host1x_ch0", TEGRA_HOST1X_BASE) );
    addDevice( new Host1x_syncDev(this, "host1x_sync0", TEGRA_HOST1X_BASE + 0x3000) );
    addDevice( new Host1x_channelDev(this, "host1x_ch1", TEGRA_HOST1X_BASE + 0x4000) );
    addDevice( new Host1x_syncDev(this, "host1x_sync1", TEGRA_HOST1X_BASE + 0x7000) );
    addDevice( new Host1x_channelDev(this, "host1x_ch2", TEGRA_HOST1X_BASE + 0x8000) );
    addDevice( new Host1x_syncDev(this, "host1x_sync2", TEGRA_HOST1X_BASE + 0xB000) );
    addDevice( new Host1x_channelDev(this, "host1x_ch3", TEGRA_HOST1X_BASE + 0xC000) );
    addDevice( new Host1x_syncDev(this, "host1x_sync3", TEGRA_HOST1X_BASE + 0x9000) );
    addDevice( new Host1x_channelDev(this, "host1x_ch4", TEGRA_HOST1X_BASE + 0x10000) );
    addDevice( new Host1x_syncDev(this, "host1x_sync4", TEGRA_HOST1X_BASE + 0x13000) );
    addDevice( new Host1x_channelDev(this, "host1x_ch5", TEGRA_HOST1X_BASE + 0x14000) );
    addDevice( new Host1x_syncDev(this, "host1x_sync5", TEGRA_HOST1X_BASE + 0x17000) );
    addDevice( new Host1x_channelDev(this, "host1x_ch6", TEGRA_HOST1X_BASE + 0x18000) );
    addDevice( new Host1x_syncDev(this, "host1x_sync6", TEGRA_HOST1X_BASE + 0x1B000) );
    addDevice( new Host1x_channelDev(this, "host1x_ch7", TEGRA_HOST1X_BASE + 0x1C000) );
    addDevice( new Host1x_syncDev(this, "host1x_sync7", TEGRA_HOST1X_BASE + 0x1F000) );
    addDevice( new DcDev(this, "host1x_dc1", TEGRA_DISPLAY_BASE) );

    addDevice( new Host1xDev(this, "host1x", 0x1) );
    addDevice( new Gr2dDev(this, "host1x_gr2d", 0x51) );
    addDevice( new Gr2dDev(this, "host1x_gr2d_sb", 0x52) );
    addDevice( new Gr2dDev(this, "host1x_gr3d", 0x60) );

    addDevice( new DummyDev(this, "dram", 0x2F600000) );
    addDevice( new DummyDev(this, "iram", 0x40000400) );
}
