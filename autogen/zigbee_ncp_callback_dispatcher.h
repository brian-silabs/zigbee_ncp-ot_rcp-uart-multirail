/***************************************************************************//**
 * @file zigbee_ncp_callback_dispatcher.h
 * @brief ZigBee ncp dispatcher declarations.
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

#ifndef SL_ZIGBEE_NCP_CALLBACK_DISPATCHER_H
#define SL_ZIGBEE_NCP_CALLBACK_DISPATCHER_H

#include PLATFORM_HEADER
#include "stack/include/sl_zigbee.h"
#include "app/em260/command-context.h" // sl_zigbee_af_plugin_ezsp_value_command_context_t


// get_value
void sl_zigbee_af_ezsp_get_value_command_cb(sl_zigbee_af_plugin_ezsp_value_command_context_t* context);
void sl_zigbee_xncp_get_value_command_cb(sl_zigbee_af_plugin_ezsp_value_command_context_t* context);
void sl_zigbee_xncp_zigbee_pro_get_value_command_cb(sl_zigbee_af_plugin_ezsp_value_command_context_t* context);
void sl_zigbee_xncp_security_get_value_command_cb(sl_zigbee_af_plugin_ezsp_value_command_context_t* context);




void sl_zigbee_af_ezsp_get_extended_value_command_cb(sl_zigbee_af_plugin_ezsp_value_command_context_t* context);
void sl_zigbee_xncp_zigbee_pro_get_extended_value_command_cb(sl_zigbee_af_plugin_ezsp_value_command_context_t* context);



void sl_zigbee_af_ezsp_set_value_command_cb(sl_zigbee_af_plugin_ezsp_value_command_context_t* context);
void sl_zigbee_xncp_set_value_command_cb(sl_zigbee_af_plugin_ezsp_value_command_context_t* context);
void sl_zigbee_xncp_zigbee_pro_set_value_command_cb(sl_zigbee_af_plugin_ezsp_value_command_context_t* context);
void sl_zigbee_xncp_security_set_value_command_cb(sl_zigbee_af_plugin_ezsp_value_command_context_t* context);



void sl_zigbee_af_ezsp_get_policy_command_cb(sl_zigbee_af_plugin_ezsp_policy_command_context_t* context);
void sl_zigbee_xncp_policy_command_cb(sl_zigbee_af_plugin_ezsp_policy_command_context_t* context);
void sl_zigbee_xncp_zigbee_pro_policy_command_cb(sl_zigbee_af_plugin_ezsp_policy_command_context_t* context);
void sl_zigbee_xncp_security_policy_command_cb(sl_zigbee_af_plugin_ezsp_policy_command_context_t* context);
void sl_zigbee_xncp_binding_policy_command_cb(sl_zigbee_af_plugin_ezsp_policy_command_context_t* context);
void sl_zigbee_xncp_zll_policy_command_cb(sl_zigbee_af_plugin_ezsp_policy_command_context_t* context);



void sl_zigbee_af_ezsp_set_policy_command_cb(sl_zigbee_af_plugin_ezsp_policy_command_context_t* context);
void  sl_zigbee_xncp_policy_command_cb(sl_zigbee_af_plugin_ezsp_policy_command_context_t* context);
void  sl_zigbee_xncp_zigbee_pro_policy_command_cb(sl_zigbee_af_plugin_ezsp_policy_command_context_t* context);
void  sl_zigbee_xncp_security_policy_command_cb(sl_zigbee_af_plugin_ezsp_policy_command_context_t* context);
void  sl_zigbee_xncp_binding_policy_command_cb(sl_zigbee_af_plugin_ezsp_policy_command_context_t* context);
void  sl_zigbee_xncp_zll_policy_command_cb(sl_zigbee_af_plugin_ezsp_policy_command_context_t* context);


void sl_zigbee_af_ezsp_get_configuration_value_command_cb(sl_zigbee_af_plugin_ezsp_configuration_value_command_context_t* context);
void sl_zigbee_xncp_get_configuration_value_command_cb(sl_zigbee_af_plugin_ezsp_configuration_value_command_context_t* context);
void sl_zigbee_xncp_source_route_get_configuration_value_command_cb(sl_zigbee_af_plugin_ezsp_configuration_value_command_context_t* context);
void sl_zigbee_xncp_zigbee_pro_get_configuration_value_command_cb(sl_zigbee_af_plugin_ezsp_configuration_value_command_context_t* context);
void sl_zigbee_xncp_security_get_configuration_value_command_cb(sl_zigbee_af_plugin_ezsp_configuration_value_command_context_t* context);
void sl_zigbee_xncp_binding_configuration_value_command_cb(sl_zigbee_af_plugin_ezsp_configuration_value_command_context_t* context);
void sl_zigbee_xncp_zll_configuration_value_command_cb(sl_zigbee_af_plugin_ezsp_configuration_value_command_context_t* context);



void sl_zigbee_af_ezsp_set_configuration_value_command_cb(sl_zigbee_af_plugin_ezsp_configuration_value_command_context_t* context);
void sl_zigbee_xncp_set_configuration_value_command_cb(sl_zigbee_af_plugin_ezsp_configuration_value_command_context_t* context);
void sl_zigbee_xncp_source_route_set_configuration_value_command_cb(sl_zigbee_af_plugin_ezsp_configuration_value_command_context_t* context);
void sl_zigbee_xncp_zigbee_pro_set_configuration_value_command_cb(sl_zigbee_af_plugin_ezsp_configuration_value_command_context_t* context);
void sl_zigbee_xncp_security_set_configuration_value_command_cb(sl_zigbee_af_plugin_ezsp_configuration_value_command_context_t* context);
void sl_zigbee_xncp_binding_configuration_value_command_cb(sl_zigbee_af_plugin_ezsp_configuration_value_command_context_t* context);
void sl_zigbee_xncp_zll_configuration_value_command_cb(sl_zigbee_af_plugin_ezsp_configuration_value_command_context_t* context);


void sl_zigbee_xncp_modify_memory_allocation_cb(void);
void sl_zigbee_xncp_zigbee_pro_modify_memory_allocation_cb(void);
void sli_zigbee_initialize_binding_table(void);



void sl_zigbee_xncp_permit_host_to_ncp_frame_cb(bool* permit);
void sl_zigbee_xncp_binding_permit_host_to_ncp_frame_cb(bool* permit);

#endif // SL_ZIGBEE_NCP_CALLBACK_DISPATCHER_H