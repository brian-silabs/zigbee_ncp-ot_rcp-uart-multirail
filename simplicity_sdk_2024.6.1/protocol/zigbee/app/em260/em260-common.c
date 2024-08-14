/***************************************************************************//**
 * @file
 * @brief Public common code for NCP applications.
 *******************************************************************************
 * # License
 * <b>Copyright 2018 Silicon Laboratories Inc. www.silabs.com</b>
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
#include "stack/internal/inc/internal-defs-patch.h"
#include "hal/hal.h"

#include "app/util/ezsp/ezsp-enum.h"
#include "app/util/ezsp/ezsp-frame-utilities.h"
#include "stack/config/sl_zigbee_configuration_defaults.h"

#define DEFAULT_TC_POLICY (SL_ZIGBEE_EZSP_DECISION_ALLOW_JOINS | SL_ZIGBEE_EZSP_DECISION_ALLOW_UNSECURED_REJOINS)
extern uint8_t sli_zigbee_num_multi_pan_forks;
extern uint16_t trustCenterPolicies[];

//------------------------------------------------------------------------------
// Common APIs

void sli_zigbee_xncp_init(void)
{
#ifdef SL_ZIGBEE_MULTI_NETWORK_STRIPPED
  trustCenterPolicies[0] = DEFAULT_TC_POLICY;
#else // SL_ZIGBEE_MULTI_NETWORK_STRIPPED
  for (uint8_t i = 0; i < sli_zigbee_num_multi_pan_forks; i++) {
    trustCenterPolicies[i] = DEFAULT_TC_POLICY;
  }
#endif  // SL_ZIGBEE_MULTI_NETWORK_STRIPPED

  sl_status_t status = sli_zigbee_stack_set_radio_ieee802154_cca_mode(SL_ZIGBEE_RADIO_802154_CCA_MODE);
  sl_zigbee_debug_printf("Init: default CCA mode set to %d: 0x%X",
                         SL_ZIGBEE_RADIO_802154_CCA_MODE,
                         status);
#ifndef DEBUG_ROUTINES_PRESENT
  (void)status;
#endif // DEBUG_ROUTINES_PRESENT
}

// *****************************************
// Convenience Stubs
// *****************************************

// The stub when the AF Support component is not present.
WEAK(bool sli_zigbee_af_get_endpoint_description(uint8_t endpoint,
                                                 sl_zigbee_endpoint_description_t *result))
{
  (void)endpoint;
  (void)result;
  // always return false if AF Support component is not present
  return false;
}

WEAK(uint16_t sli_zigbee_af_get_endpoint_cluster(uint8_t endpoint,
                                                 sl_zigbee_cluster_list_id_t listId,
                                                 uint8_t listIndex))
{
  (void)endpoint;
  (void)listId;
  (void)listIndex;
  // always return 0xFFFF if AF Support component is not present
  return 0xFFFF;
}

WEAK(uint8_t sli_zigbee_af_get_endpoint(uint8_t index))
{
  (void)index;
  // always return 0xFF if AF Support component is not present
  return 0xFF;
}

// Hook from command handler for the af support related commands
WEAK(bool sli_zigbee_af_process_ezsp_af_support_commands(uint16_t commandId))
{
  (void)commandId;
  return false;
}

#ifndef __NCP_CONFIG__

#ifndef SL_ZIGBEE_APPLICATION_HAS_SET_OR_GET_EZSP_TOKEN_HANDLER
void sl_zigbee_set_or_get_ezsp_token_command_handler(bool isSet)
{
  appendInt32u(SL_STATUS_INVALID_STATE);
}
#endif

#endif /* __NCP_CONFIG__ */
