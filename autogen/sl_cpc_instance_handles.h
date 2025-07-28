/***************************************************************************//**
 * @file
 * @brief CPC Instance Handle Generated Header File.
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

#ifndef SL_CPC_INSTANCE_HANDLES_H
#define SL_CPC_INSTANCE_HANDLES_H

// needed to check if security is enabled and
// side loading of the user configuration header.
#include "sli_cpc.h"

#include "sli_cpc_instance.h"
#include "sl_cpc_drv_uart_eusart_vcom_config.h"


#if !defined(SL_CPC_ENDPOINT_DEFAULT_INSTANCE)
  #define SL_CPC_ENDPOINT_DEFAULT_INSTANCE uart_vcom
#endif
#if !defined(SL_CPC_DRV_UART_VCOM_RX_PAYLOAD_MAX_LENGTH)
  #define SL_CPC_DRV_UART_VCOM_RX_PAYLOAD_MAX_LENGTH         SL_CPC_RX_PAYLOAD_MAX_LENGTH
#endif
#if !defined(SL_CPC_DRV_UART_VCOM_RX_BUFFER_MAX_COUNT)
  #define SL_CPC_DRV_UART_VCOM_RX_BUFFER_MAX_COUNT           SL_CPC_RX_BUFFER_MAX_COUNT
#endif
#if !defined(SL_CPC_DRV_UART_VCOM_TX_QUEUE_ITEM_MAX_COUNT)
  #define SL_CPC_DRV_UART_VCOM_TX_QUEUE_ITEM_MAX_COUNT       SL_CPC_TX_QUEUE_ITEM_MAX_COUNT
#endif



#define SLI_CPC_DRV_UART_RX_DATA_MAX_LENGTH             (SLI_CPC_RX_DATA_MAX_LENGTH_CFG(SL_CPC_DRV_UART_VCOM_RX_PAYLOAD_MAX_LENGTH))
#define SLI_CPC_DRV_UART_HDLC_REJECT_MAX_COUNT          (SLI_CPC_HDLC_REJECT_MAX_COUNT_CFG(SL_CPC_DRV_UART_VCOM_RX_BUFFER_MAX_COUNT))
#define SLI_CPC_DRV_UART_RX_QUEUE_ITEM_MAX_COUNT        (SLI_CPC_RX_QUEUE_ITEM_MAX_COUNT_CFG(SL_CPC_DRV_UART_VCOM_RX_BUFFER_MAX_COUNT))
#define SLI_CPC_DRV_UART_TX_QUEUE_ITEM_SFRAME_MAX_COUNT (SLI_CPC_TX_QUEUE_ITEM_SFRAME_MAX_COUNT_CFG(SLI_CPC_DRV_UART_RX_QUEUE_ITEM_MAX_COUNT))
#define SLI_CPC_DRV_UART_BUFFER_HANDLE_MAX_COUNT        (SLI_CPC_BUFFER_HANDLE_MAX_COUNT_CFG( \
                                                                                  SL_CPC_DRV_UART_VCOM_TX_QUEUE_ITEM_MAX_COUNT,    \
                                                                                  SL_CPC_DRV_UART_VCOM_RX_BUFFER_MAX_COUNT,        \
                                                                                  SLI_CPC_DRV_UART_TX_QUEUE_ITEM_SFRAME_MAX_COUNT))
#define SLI_CPC_DRV_UART_HDLC_HEADER_MAX_COUNT          (SLI_CPC_HDLC_HEADER_MAX_COUNT_CFG(SLI_CPC_DRV_UART_BUFFER_HANDLE_MAX_COUNT))
#define SLI_CPC_DRV_UART_RX_FRAME_MAX_LENGTH            (SLI_CPC_RX_FRAME_MAX_LENGTH_CFG(SLI_CPC_DRV_UART_RX_DATA_MAX_LENGTH))
#define SLI_CPC_DRV_UART_RX_BUFFER_MAX_LENGTH           (SLI_CPC_RX_BUFFER_MAX_LENGTH_CFG(SLI_CPC_DRV_UART_RX_FRAME_MAX_LENGTH))


#if (SL_CPC_ENDPOINT_SECURITY_ENABLED >= 1)
#if (SL_CPC_DRV_UART_VCOM_RX_PAYLOAD_MAX_LENGTH > 4079)
  #error Invalid SL_CPC_DRV_UART_VCOM_RX_PAYLOAD_MAX_LENGTH; Must be less or equal to 4079
#endif
#else
#if (SL_CPC_DRV_UART_VCOM_RX_PAYLOAD_MAX_LENGTH > 4087)
  #error Invalid SL_CPC_DRV_UART_VCOM_RX_PAYLOAD_MAX_LENGTH; Must be less or equal to 4087
#endif
#endif

#if defined(SL_CATALOG_CPC_PRIMARY_PRESENT)
#define SLI_CPC_RX_DATA_MAX_LENGTH                                          (SLI_CPC_DRV_UART_RX_DATA_MAX_LENGTH)

extern sli_cpc_instance_t g_instance;
#endif

#if defined(SL_CATALOG_CPC_SECONDARY_PRESENT)
// Declaration of instances handles
extern sli_cpc_instance_t SL_CPC_INSTANCE_NAME(uart_vcom);

#define g_instance sli_cpc_instance_uart_vcom

extern sli_cpc_instance_t *sl_cpc_instances[];
extern const uint8_t sl_cpc_instances_count;
#endif

#endif // SL_CPC_INSTANCE_HANDLES_H
