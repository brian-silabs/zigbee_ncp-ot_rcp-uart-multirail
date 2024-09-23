/***************************************************************************//**
 * @file zigbee_common_callback_dispatcher.h
 * @brief ZigBee common dispatcher declarations.
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

#ifndef SL_ZIGBEE_COMMON_CALLBACK_DISPATCHER_H
#define SL_ZIGBEE_COMMON_CALLBACK_DISPATCHER_H

#include PLATFORM_HEADER
#include "stack/include/ember.h"

// Event Init
void sli_zigbee_af_event_init(void);
void emberAfPluginGreenPowerClientInitCallback(uint8_t init_level);
void emberAfPluginGreenPowerServerInitCallback(uint8_t init_level);
void sli_zigbee_watchdog_refresh_handler_init(uint8_t init_level);
// Local data Init
void sli_zigbee_af_local_data_init(void);
void emberAfPluginGreenPowerClientInitCallback(uint8_t init_level);
// Init done
void sli_zigbee_af_initDone(void);
void sli_zb_af_support_init_callback(uint8_t init_level);
void emberAfInit(uint8_t init_level);
void emberAfPluginGreenPowerClientInitCallback(uint8_t init_level);
void emberAfPluginGreenPowerServerInitCallback(uint8_t init_level);

// Tick
void sli_zigbee_af_tick(void);

#endif // SL_ZIGBEE_COMMON_CALLBACK_DISPATCHER_H