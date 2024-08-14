/*
 *  Copyright (c) 2023, The OpenThread Authors.
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 *  1. Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *  2. Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *  3. Neither the name of the copyright holder nor the
 *     names of its contributors may be used to endorse or promote products
 *     derived from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 *  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 *  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 *  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 *  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 *  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file
 * @brief
 *   This file includes the platform-specific initializers.
 */

#include <assert.h>
#include <string.h>

#include <openthread-core-config.h>
#include <openthread-system.h>
#include "utils/uart.h"

#include "common/logging.hpp"

#include "em_chip.h"
#include "em_emu.h"
#include "em_system.h"
#include "rail.h"
#include "sl_mpu.h"
#include "sl_sleeptimer.h"

#if defined(SL_COMPONENT_CATALOG_PRESENT)
#include "sl_component_catalog.h"
#endif
#include "sl_memory_manager.h"

#if OPENTHREAD_CONFIG_MULTIPAN_RCP_ENABLE
#include "sl_gp_interface.h"
#endif

#include "alarm.h"
#include "platform-efr32.h"

#define USE_EFR32_LOG (OPENTHREAD_CONFIG_LOG_OUTPUT == OPENTHREAD_CONFIG_LOG_OUTPUT_PLATFORM_DEFINED)

#if defined(SL_CATALOG_OPENTHREAD_CLI_PRESENT) && defined(SL_CATALOG_KERNEL_PRESENT)
#define CLI_TASK_ENABLED        (SL_OPENTHREAD_ENABLE_CLI_TASK)
#else
#define CLI_TASK_ENABLED        (0)
#endif

otInstance *sInstance;

static void efr32SerialProcess(void);

#if (OPENTHREAD_RADIO)
static void efr32NcpProcess(void);
#elif (CLI_TASK_ENABLED == 0)
static void efr32CliProcess(void);
#endif

#ifndef SL_COMPONENT_CATALOG_PRESENT
__WEAK void sl_openthread_init(void)
{
    // Placeholder for enabling Silabs specific features available only through Simplicity Studio
}
#else
void sl_openthread_init(void);
#endif // SL_COMPONENT_CATALOG_PRESENT

void otSysInit(int argc, char *argv[])
{
    OT_UNUSED_VARIABLE(argc);
    OT_UNUSED_VARIABLE(argv);
    sl_ot_sys_init();
}

void sl_ot_sys_init(void)
{
    sl_openthread_init();

#if USE_EFR32_LOG
    efr32LogInit();
#endif
    efr32RadioInit();
    efr32AlarmInit();
    efr32MiscInit();
}

bool otSysPseudoResetWasRequested(void)
{
    return false;
}

void otSysDeinit(void)
{
    efr32RadioDeinit();

#if USE_EFR32_LOG
    efr32LogDeinit();
#endif
}

void otSysProcessDrivers(otInstance *aInstance)
{
    sInstance = aInstance;

    // should sleep and wait for interrupts here
#if OPENTHREAD_CONFIG_MULTIPAN_RCP_ENABLE
    efr32GpProcess();
#endif

    efr32SerialProcess();

    efr32RadioProcess(aInstance);

    // See alarm.c: Wrapped in a critical section
    efr32AlarmProcess(aInstance);
}

__WEAK void otSysEventSignalPending(void)
{
    // Intentionally empty
}

/* Serial process helper functions */

static void efr32SerialProcess(void)
{

#if (OPENTHREAD_RADIO)
    efr32NcpProcess();
#elif (CLI_TASK_ENABLED == 0)
    efr32CliProcess();
#endif // OPENTHREAD_RADIO0
}

#if (OPENTHREAD_RADIO)
static void efr32NcpProcess(void)
{
#if OPENTHREAD_CONFIG_NCP_HDLC_ENABLE
    efr32UartProcess();
#elif OPENTHREAD_CONFIG_NCP_CPC_ENABLE
    efr32CpcProcess();
#elif OPENTHREAD_CONFIG_NCP_SPI_ENABLE
    efr32SpiProcess();
#endif
}
#elif (CLI_TASK_ENABLED == 0)
static void efr32CliProcess(void)
{
    efr32UartProcess();
}
#endif
