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
#include "devices/res_semadev.h"
#include "devices/dummydev.h"

#include "device.h"
#include "iomap.h"
#include "tracea9.h"

TraceA9::TraceA9(MainWindow *window, QString name, QFile *recfile,
                 QObject *parent) :
    TraceCPU(window, name, recfile, parent)
{
    addDevice( new EmcDev("emc", TEGRA_EMC_BASE) );
    addDevice( new McDev("mc", TEGRA_MC_BASE) );
    addDevice( new GizmoDev("ahb gizmo", TEGRA_AHB_GIZMO_BASE) );
    addDevice( new FuseDev("apb fuse", TEGRA_FUSE_BASE) );
    addDevice( new Apb_dmaDev("apb dma", TEGRA_APB_DMA_BASE) );
    addDevice( new Apb_miscDev("apb misc", TEGRA_APB_MISC_BASE) );
    addDevice( new CarDev("car", TEGRA_CLK_RESET_BASE) );
    addDevice( new FlowDev("flow", TEGRA_FLOW_CTRL_BASE) );
    addDevice( new GpioDev("gpio", TEGRA_GPIO_BASE) );
    addDevice( new PmcDev("pmc", TEGRA_PMC_BASE) );
    addDevice( new RtcDev("rtc", TEGRA_RTC_BASE) );
    addDevice( new TimerDev("timer1", TEGRA_TMR1_BASE) );
    addDevice( new TimerDev("timer2", TEGRA_TMR2_BASE) );
    addDevice( new Timer_usDev("timer us", TEGRA_TMRUS_BASE) );
    addDevice( new TimerDev("timer3", TEGRA_TMR3_BASE) );
    addDevice( new TimerDev("timer4", TEGRA_TMR4_BASE) );
    addDevice( new DummyDev("ucq", 0x60010000) );
    addDevice( new BseDev("bsea", TEGRA_BSEA_BASE + 0x1000) );
    addDevice( new DummyDev("sxe", 0x6001A000) );
    addDevice( new BseDev("bsev", TEGRA_VDE_BASE + 0x1000) );
    addDevice( new DummyDev("mbe", 0x6001C000) );
    addDevice( new DummyDev("ppe", 0x6001C200) );
    addDevice( new DummyDev("mce", 0x6001C400) );
    addDevice( new DummyDev("tfe", 0x6001C600) );
    addDevice( new DummyDev("ppb", 0x6001C800) );
    addDevice( new DummyDev("vdma", 0x6001CA00) );
    addDevice( new DummyDev("ucq", 0x6001CC00) );
    addDevice( new DummyDev("bsea", 0x6001D000) );
    addDevice( new DummyDev("frameid", 0x6001D800) );
//    addDevice( new Host1x_channelDev("host1x ch prot", TEGRA_HOST1X_BASE + 0x20000) );
    addDevice( new Res_semaDev("res sema", TEGRA_RES_SEMA_BASE) );
    addDevice( new Arb_semaDev("arb sema", TEGRA_ARB_SEMA_BASE) );
    addDevice( new Arb_gnt_ictlrDev("arb gnt icrtrl", TEGRA_ARBGNT_ICTLR_BASE) );
    addDevice( new SdhciDev("sdhci4", TEGRA_SDMMC4_BASE) );
    addDevice( new EvpDev("evp", TEGRA_EXCEPTION_VECTORS_BASE) );
    addDevice( new Ictlr_priDev("ictlr_pri", TEGRA_PRIMARY_ICTLR_BASE) );
    addDevice( new Ictlr_secDev("ictlr_sec", TEGRA_SECONDARY_ICTLR_BASE) );
    addDevice( new Ictlr_triDev("ictlr_tri", TEGRA_TERTIARY_ICTLR_BASE) );
    addDevice( new Ictlr_quadDev("ictlr_quad", TEGRA_QUATERNARY_ICTLR_BASE) );

    addDevice( new Host1x_channelDev("host1x ch0", TEGRA_HOST1X_BASE) );
    addDevice( new Host1x_syncDev("host1x sync0", TEGRA_HOST1X_BASE + 0x3000) );
    addDevice( new Host1x_channelDev("host1x ch1", TEGRA_HOST1X_BASE + 0x4000) );
    addDevice( new Host1x_syncDev("host1x sync1", TEGRA_HOST1X_BASE + 0x7000) );
    addDevice( new Host1x_channelDev("host1x ch2", TEGRA_HOST1X_BASE + 0x8000) );
    addDevice( new Host1x_syncDev("host1x sync2", TEGRA_HOST1X_BASE + 0xB000) );
    addDevice( new Host1x_channelDev("host1x ch3", TEGRA_HOST1X_BASE + 0xC000) );
    addDevice( new Host1x_syncDev("host1x sync3", TEGRA_HOST1X_BASE + 0x9000) );
    addDevice( new Host1x_channelDev("host1x ch4", TEGRA_HOST1X_BASE + 0x10000) );
    addDevice( new Host1x_syncDev("host1x sync4", TEGRA_HOST1X_BASE + 0x13000) );
    addDevice( new Host1x_channelDev("host1x ch5", TEGRA_HOST1X_BASE + 0x14000) );
    addDevice( new Host1x_syncDev("host1x sync5", TEGRA_HOST1X_BASE + 0x17000) );
    addDevice( new Host1x_channelDev("host1x ch6", TEGRA_HOST1X_BASE + 0x18000) );
    addDevice( new Host1x_syncDev("host1x sync6", TEGRA_HOST1X_BASE + 0x1B000) );
    addDevice( new Host1x_channelDev("host1x ch7", TEGRA_HOST1X_BASE + 0x1C000) );
    addDevice( new Host1x_syncDev("host1x sync7", TEGRA_HOST1X_BASE + 0x1F000) );
    addDevice( new DcDev("host1x dc1", TEGRA_DISPLAY_BASE) );

    addDevice( new Host1xDev("host1x", 0x1) );
    addDevice( new Gr2dDev("host1x gr2d", 0x51) );
    addDevice( new Gr2dDev("host1x gr2d_sb", 0x52) );
    addDevice( new Gr2dDev("host1x gr3d", 0x60) );
}
