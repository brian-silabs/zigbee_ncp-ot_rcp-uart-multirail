/***************************************************************************//**
 * @file zigbee_common_callback_dispatcher.c
 * @brief ZigBee common dispatcher definitions.
 *******************************************************************************
 * # License
 * <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/

#include PLATFORM_HEADER
#include "stack/include/sl_zigbee.h"
#include "sl_zigbee_system_common.h"
#include "zigbee_common_callback_dispatcher.h"

void sli_zigbee_af_event_init(void)
{
  sl_zigbee_af_green_power_client_init_cb(SL_ZIGBEE_INIT_LEVEL_EVENT);
  sl_zigbee_af_green_power_server_init_cb(SL_ZIGBEE_INIT_LEVEL_EVENT);
}

void sli_zigbee_af_local_data_init(void)
{
  sl_zigbee_af_green_power_client_init_cb(SL_ZIGBEE_INIT_LEVEL_LOCAL_DATA);
}

void sli_zigbee_af_init_done(void)
{
  sli_zb_af_support_init_callback(SL_ZIGBEE_INIT_LEVEL_DONE);
  sl_zigbee_af_init(SL_ZIGBEE_INIT_LEVEL_DONE);
  sl_zigbee_af_green_power_client_init_cb(SL_ZIGBEE_INIT_LEVEL_DONE);
  sl_zigbee_af_green_power_server_init_cb(SL_ZIGBEE_INIT_LEVEL_DONE);
}


void sli_zigbee_af_tick(void)
{
}
