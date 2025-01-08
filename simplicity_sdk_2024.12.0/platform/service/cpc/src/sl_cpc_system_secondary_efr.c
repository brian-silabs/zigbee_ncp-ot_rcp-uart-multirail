/***************************************************************************/ /**
 * @file
 * @brief CPC System Endpoint RCP API implementation.
 *******************************************************************************
 * # License
 * <b>Copyright 2024 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * SPDX-License-Identifier: Zlib
 *
 * The licensor of this software is Silicon Laboratories Inc.
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 ******************************************************************************/

#include <stdbool.h>
#include <string.h>

#if defined(SL_COMPONENT_CATALOG_PRESENT)
#include "sl_component_catalog.h"
#endif

#include "sli_cpc_assert.h"
#include "sli_cpc_system_common.h"

#if (defined(SL_CATALOG_EMLIB_CORE_PRESENT))
#include "em_core.h"
#include "em_chip.h"
#include "em_rmu.h"
#if defined(EMU_PRESENT)
#include "em_emu.h"
#endif
#elif (defined(SL_CATALOG_HAL_EMU_PRESENT))
#include "sl_hal_emu.h"
#endif

/***************************************************************************//**
 * Get system reset reason.
 ******************************************************************************/
sl_cpc_system_status_t cpc_get_reset_reason(void)
{
  sl_cpc_system_status_t last_status = STATUS_RESET_UNKNOWN;
  uint32_t reset_cause;
#if defined(SL_CATALOG_EMLIB_RMU_PRESENT)
  reset_cause = RMU_ResetCauseGet();
  RMU_ResetCauseClear();
#elif defined(SL_CATALOG_HAL_EMU_PRESENT)
  reset_cause = sl_hal_emu_get_reset_cause();
  sl_hal_emu_clear_reset_cause();
#endif
#if defined(SL_CATALOG_EMLIB_RMU_PRESENT)
#if defined(RMU_PRESENT)
 #if defined(_RMU_RSTCAUSE_MASK)
  if (reset_cause & RMU_RSTCAUSE_PORST) {
    last_status = STATUS_RESET_POWER_ON;
  } else if (reset_cause & RMU_RSTCAUSE_AVDDBOD) {
    last_status = STATUS_RESET_FAULT;
  } else if (reset_cause & RMU_RSTCAUSE_DVDDBOD) {
    last_status = STATUS_RESET_FAULT;
  } else if (reset_cause & RMU_RSTCAUSE_DECBOD) {
    last_status = STATUS_RESET_FAULT;
  } else if (reset_cause & RMU_RSTCAUSE_EXTRST) {
    last_status = STATUS_RESET_EXTERNAL;
  } else if (reset_cause & RMU_RSTCAUSE_WDOGRST) {
    last_status = STATUS_RESET_WATCHDOG;
  } else if (reset_cause & RMU_RSTCAUSE_LOCKUPRST) {
    last_status = STATUS_RESET_CRASH;
  } else if (reset_cause & RMU_RSTCAUSE_SYSREQRST) {
    last_status = STATUS_RESET_SOFTWARE;
  } else if (reset_cause & RMU_RSTCAUSE_EM4RST) {
    last_status = STATUS_RESET_OTHER;
  }
  #endif

#elif defined(EMU_PRESENT)

 #if defined(_EMU_RSTCTRL_AVDDBODRMODE_MASK)
  if (reset_cause & rmuResetAVDD) {
    last_status = STATUS_RESET_FAULT;
  }
 #endif
 #if defined(_EMU_RSTCTRL_IOVDD0BODRMODE_MASK)
  if (reset_cause & rmuResetIOVDD0) {
    last_status = STATUS_RESET_FAULT;
  }
 #endif
 #if defined(_EMU_RSTCTRL_DECBODRMODE_MASK)
  if (reset_cause & rmuResetDecouple) {
    last_status = STATUS_RESET_FAULT;
  }
 #endif
 #if defined(_EMU_RSTCTRL_WDOG0RMODE_MASK)
  if (reset_cause & rmuResetWdog0) {
    last_status = STATUS_RESET_WATCHDOG;
  }
 #endif
 #if defined(_EMU_RSTCTRL_WDOG1RMODE_MASK)
  if (reset_cause & rmuResetWdog1) {
    last_status = STATUS_RESET_WATCHDOG;
  }
 #endif
 #if defined(_EMU_RSTCTRL_LOCKUPRMODE_MASK)
  if (reset_cause & rmuResetCoreLockup) {
    last_status = STATUS_RESET_CRASH;
  }
 #endif
 #if defined(_EMU_RSTCTRL_SELOCKUPRMODE_MASK)
  if (reset_cause & rmuResetSELockup) {
    last_status = STATUS_RESET_CRASH;
  }
 #endif
 #if defined(_EMU_RSTCTRL_SYSRMODE_MASK)
  if (reset_cause & rmuResetSys) {
    last_status = STATUS_RESET_SOFTWARE;
  }
 #endif
 #if defined(_EMU_RSTCTRL_SESYSRMODE_MASK)
  if (reset_cause & rmuResetSESys) {
    last_status = STATUS_RESET_SOFTWARE;
  }
  #endif  // _RMU_RSTCAUSE_MASK
 #endif // RMU_PRESENT
#else
  // FIXME: Return correct
  (void) reset_cause;
#endif // SL_CATALOG_EMLIB_RMU_PRESENT
  return last_status;
}

/***************************************************************************//**
 * Return bootloader
 ******************************************************************************/
void cpc_get_bootloader_info(sli_cpc_system_bootloader_info_t *infos)
{
#if defined(SL_CPC_HAS_BOOTLOADER_SUPPORT)
  BootloaderInformation_t bootloader_infos;

  bootloader_getInfo(&bootloader_infos);

  // set version, version might be overriden
  // below in case the bootloader is none
  infos->version = (uint32_t)bootloader_infos.version;
  // capabilitiesMask only exist for EMBER_APPLICATION, default to 0
  infos->capabilities = 0;

#if (defined(SL_CATALOG_EMBER_BOOTLOADER_PRESENT))
#if (SL_EMBER_BOOTLOADER_TYPE == SL_EMBER_BOOTLOADER_TYPE_STANDALONE)
  infos->type = SL_CPC_BOOTLOADER_EMBER_STANDALONE;
#elif (SL_EMBER_BOOTLOADER_TYPE == SL_CPC_BOOTLOADER_EMBER_APPLICATION)
  infos->type = SL_CPC_BOOTLOADER_EMBER_APPLICATION;
  infos->capabilities = (uint32_t)bootloader_infos.capabilitiesMask;
#else
  // should never end up here, but just in case
  // make sure the returned value is sound
  infos->type = (sl_cpc_bootloader_t)SL_CPC_BOOTLOADER_UNKNOWN;
#endif // SL_EMBER_BOOTLOADER_TYPE == SL_EMBER_BOOTLOADER_TYPE_STANDALONE
#else
  if (bootloader_infos.type == SL_BOOTLOADER) {
    infos->type = SL_CPC_BOOTLOADER_GECKO;
  } else if (bootloader_infos.type == NO_BOOTLOADER) {
    infos->type = SL_CPC_BOOTLOADER_NONE;
    infos->version = 0xFFFFFFFF;
  } else {
    // this should never happen, just make the code ready in
    // case BootloaderType_t get extended with new values
    infos->type = SL_CPC_BOOTLOADER_UNKNOWN;
  }
#endif // SL_CATALOG_EMBER_BOOTLOADER_PRESENT

#else
  infos->type = SL_CPC_BOOTLOADER_NONE;
  infos->version = 0xFFFFFFFF;
  infos->capabilities = 0xFFFFFFFF;
#endif // SL_CPC_HAS_BOOTLOADER_SUPPORT
}

/***************************************************************************//**
 * Reset system; Should not return
 ******************************************************************************/
void cpc_system_reset(sli_cpc_system_reboot_mode_t reboot_mode)
{
  (void)reboot_mode;

#if (defined(SL_CATALOG_GECKO_BOOTLOADER_INTERFACE_PRESENT))
  // The reset command asked to perform a reset.
  BootloaderResetCause_t* resetCause = (BootloaderResetCause_t*) (RAM_MEM_BASE);

  // Set reset reason to bootloader entry
  switch (reboot_mode) {
    case REBOOT_APPLICATION:
      resetCause->reason = BOOTLOADER_RESET_REASON_GO;
      break;
    case REBOOT_BOOTLOADER:
      resetCause->reason = BOOTLOADER_RESET_REASON_BOOTLOAD;
      break;
    default:
      SLI_CPC_ASSERT(0);
      break;
  }

  resetCause->signature = BOOTLOADER_RESET_SIGNATURE_VALID;
#endif  // SL_CATALOG_GECKO_BOOTLOADER_INTERFACE_PRESENT

#if (defined(SL_CATALOG_EMLIB_CORE_PRESENT))
#if defined(RMU_PRESENT)
// Clear reset cause
  RMU->CMD = RMU_CMD_RCCLR;
// Trigger a software system reset
  RMU->CTRL = (RMU->CTRL & ~_RMU_CTRL_SYSRMODE_MASK) | RMU_CTRL_SYSRMODE_EXTENDED;
#endif  // RMU_PRESENT

  CHIP_Reset();

#elif (defined(SL_CATALOG_HAL_EMU_PRESENT))
  // Clear reset cause
  sl_hal_emu_clear_reset_cause();
  // FIXME: Issue a CHIP_Reset() when it will be implemented by sl_peripheral
  NVIC_SystemReset();
#endif  // SL_CATALOG_EMLIB_CORE_PRESENT
  exit(1);
}
