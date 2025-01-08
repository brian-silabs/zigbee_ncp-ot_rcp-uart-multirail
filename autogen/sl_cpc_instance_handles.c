/***************************************************************************//**
 * @file
 * @brief CPC Instance Handle Generated Source File.
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


#include "sl_common.h"
#include "sli_cpc_memory.h"
#include "sli_cpc_instance.h"

#if defined(SL_COMPONENT_CATALOG_PRESENT)
#include "sl_component_catalog.h"
#endif

#if !defined(SL_CATALOG_MEMORY_MANAGER_PRESENT)
#include "sli_mem_pool.h"
#endif

#if defined(SL_CATALOG_CPC_PRIMARY_PRESENT)
// needed for definition of sli_cpc_system_command_handle_t;
#include "sli_cpc_system_primary.h"
#endif

#if defined(SL_CATALOG_CPC_SECONDARY_PRESENT)
// needed for SLI_CPC_SYSTEM_COMMAND_BUFFER_SIZE
#include "sli_cpc_system_secondary.h"
#endif

#include "sl_cpc_config.h"
#include "sl_cpc_instance_handles.h"

/*******************************************************************************
 ***************************  GLOBAL VARIABLES   *******************************
 ******************************************************************************/

// Declaration of instances handles
sli_cpc_instance_t SL_CPC_INSTANCE_NAME(uart_vcom) = {
  // user config
  .rx_user_payload_max_length = SL_CPC_DRV_UART_VCOM_RX_PAYLOAD_MAX_LENGTH,
  .tx_queue_item_max_count = SL_CPC_DRV_UART_VCOM_TX_QUEUE_ITEM_MAX_COUNT,
  .rx_buffer_max_count = SL_CPC_DRV_UART_VCOM_RX_BUFFER_MAX_COUNT,

  // driver pointer
  .driver = &uart_driver,
};


sli_cpc_instance_t *sl_cpc_instances[] = {
  SL_CPC_INSTANCE_PTR(uart_vcom),
};

const uint8_t sl_cpc_instances_count = sizeof(sl_cpc_instances) / sizeof(sl_cpc_instances[0]);

