/***************************************************************************//**
 * @file  zap-cli.c
 * @brief Generated file for zcl cli using ZAP. Do not update file manually.
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

#ifdef SL_COMPONENT_CATALOG_PRESENT
#include "sl_component_catalog.h"
#endif

#ifdef SL_CATALOG_ZIGBEE_ZCL_CLI_PRESENT

#include <stdlib.h>
#include "sl_cli_config.h"
#include "sl_cli_command.h"
#include "sl_cli.h"
#include "zcl-cli.h"
#ifdef SL_CATALOG_ZIGBEE_DEBUG_PRINT_PRESENT
#include "sl_zigbee_debug_print.h"
#endif // SL_CATALOG_ZIGBEE_DEBUG_PRINT_PRESENT
#include "zap-type.h"
#include "zap-id.h"
#include "af.h"
#include "zap-config.h"

extern void sli_zigbee_zcl_simple_command(uint8_t frameControl,
                        uint16_t clusterId,
                        uint8_t commandId,
                        sl_cli_command_arg_t *arguments,
                        uint8_t *argumentTypes);
extern sl_cli_command_info_t cli_cmd_zcl_global_group;
extern sl_cli_command_info_t cli_cmd_zcl_mfg_code_command;
extern sl_cli_command_info_t cli_cmd_zcl_time_command;
extern sl_cli_command_info_t cli_cmd_zcl_use_next_sequence_command;
extern sl_cli_command_info_t cli_cmd_zcl_x_default_resp_command;
extern sl_cli_command_info_t cli_cmd_zcl_test_response_on_command;
extern sl_cli_command_info_t cli_cmd_zcl_test_response_off_command;
#if defined(ZCL_USING_IDENTIFY_CLUSTER_SERVER) || defined(ZCL_USING_IDENTIFY_CLUSTER_CLIENT)
extern sl_cli_command_info_t cli_cmd_zcl_identify_on_command;
extern sl_cli_command_info_t cli_cmd_zcl_identify_off_command;
#endif
#if defined(ZCL_USING_BACNET_PROTOCOL_TUNNEL_CLUSTER_CLIENT) || defined(ZCL_USING_BACNET_PROTOCOL_TUNNEL_CLUSTER_SERVER)
extern sl_cli_command_info_t cli_cmd_zcl_bacnet_transfer_whois_command;
#endif
#if defined(ZCL_USING_TUNNELING_CLUSTER_CLIENT) || defined(ZCL_USING_TUNNELING_CLUSTER_SERVER)
extern sl_cli_command_info_t cli_cmd_zcl_tunneling_random_to_server_command;
extern sl_cli_command_info_t cli_cmd_zcl_tunneling_transfer_to_server_command;
extern sl_cli_command_info_t cli_cmd_zcl_tunneling_random_to_client_command;
extern sl_cli_command_info_t cli_cmd_zcl_tunneling_transfer_to_client_command;
#endif

#ifdef __cplusplus
extern "C" {
#endif

// Provide function declarations

// Command structs. Names are command names prefixed by cli_cmd_zcl_[cluster name]_cluster

// Create group command tables and structs if cli_groups given
// in template. Group name is suffixed with [cluster name]_[cluster_side]_cluster_group_table for tables
// and group commands are cli_cmd_( group name )_group

// ZCL cluster commands

static const sl_cli_command_entry_t zcl_group_table[] = {
  { "global", &cli_cmd_zcl_global_group, false },
  { "mfg-code", &cli_cmd_zcl_mfg_code_command, false},
  { "time", &cli_cmd_zcl_time_command, false},
  { "use-next-sequence", &cli_cmd_zcl_use_next_sequence_command, false},
  { "x-default-resp", &cli_cmd_zcl_x_default_resp_command, false},
  { "test-response-on", &cli_cmd_zcl_test_response_on_command, false},
  { "test-response-off", &cli_cmd_zcl_test_response_off_command, false},
  { NULL, NULL, false },
};

sl_cli_command_info_t cli_cmd_zcl_group = \
  SL_CLI_COMMAND_GROUP(zcl_group_table, "ZCL commands");

// Create root command table
const sl_cli_command_entry_t sl_cli_zcl_command_table[] = {
  { "zcl", &cli_cmd_zcl_group, false },
  { NULL, NULL, false },
};

sl_cli_command_group_t sl_cli_zcl_command_group =
{
  { NULL },
  false,
  sl_cli_zcl_command_table
};


#ifdef __cplusplus
}
#endif
#endif