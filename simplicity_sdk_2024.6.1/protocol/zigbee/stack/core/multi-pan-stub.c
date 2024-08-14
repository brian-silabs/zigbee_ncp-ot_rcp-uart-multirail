/***************************************************************************//**
 * @file
 * @brief Code for multi PAN stubs.
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
#include "hal/hal.h"
#include "core/multi-pan.h"
#include "core/sl_zigbee_multi_network.h" // for sli_zigbee_network_descriptor and sli_zigbee_pan_info_data
#include "mac-child.h" // for sl_mac_child_entry_t
#include "stack/include/sl_zigbee_types_internal.h" // for PAN_ID_OKAY

const sl_zigbee_library_status_t sli_zigbee_multi_pan_library_status = SL_ZIGBEE_LIBRARY_IS_STUB;

#ifndef SL_ZIGBEE_MULTI_NETWORK_STRIPPED

extern sl_mac_child_entry_t sli_zigbee_child_table_data[];
extern uint16_t sli_zigbee_child_status_data[];
extern uint32_t sli_zigbee_child_timers_data[];
extern uint16_t sli_zigbee_child_lqi_data[];
extern uint8_t sli_zigbee_end_device_timeout_data[];
extern uint8_t sli_zigbee_route_record_table_data[];
extern sl_zigbee_broadcast_table_entry_t sli_zigbee_broadcast_table_data[];

void sli_zigbee_network_pan_info_data_init(uint8_t nwkIndex, sl_zigbee_network_info_t *curNetwork)
{
  (void)nwkIndex;
  curNetwork->panInfoData->childTable = &(sli_zigbee_child_table_data[0]);
  curNetwork->panInfoData->childStatus = &(sli_zigbee_child_status_data[0]);
  curNetwork->panInfoData->childTimers = &(sli_zigbee_child_timers_data[0]);
  curNetwork->panInfoData->childLqi = &(sli_zigbee_child_lqi_data[0]);
  curNetwork->panInfoData->endDeviceTimeout = &(sli_zigbee_end_device_timeout_data[0]);
  curNetwork->panInfoData->endDeviceChildCount = 0;
  curNetwork->panInfoData->routeRecordTable = &(sli_zigbee_route_record_table_data[0]);
  curNetwork->panInfoData->broadcastTable = &(sli_zigbee_broadcast_table_data[0]);
  curNetwork->panInfoData->broadcastHead = 0;
  curNetwork->panInfoData->fastLinkStatusCount = 0;
  curNetwork->panInfoData->permitJoining = false;
  curNetwork->panInfoData->macPermitAssociation = false;
  curNetwork->panInfoData->allowRejoinsWithWellKnownKey = false;
  curNetwork->panInfoData->parentAnnounceIndex = 0;
  curNetwork->panInfoData->totalInitialChildren = 0;
  curNetwork->panInfoData->newPanId = PAN_ID_OKAY;
}

void sli_zigbee_set_child_table_for_current_network(void)
{
}

void sli_zigbee_get_child_token_for_current_network(void *data,
                                                    uint16_t tokenAddress,
                                                    uint8_t childIndex)
{
  switch (tokenAddress) {
    case TOKEN_STACK_CHILD_TABLE: {
      halCommonGetIndexedToken(data, TOKEN_STACK_CHILD_TABLE, childIndex);
      break;
    }

    case TOKEN_STACK_ADDITIONAL_CHILD_DATA: {
      halCommonGetIndexedToken(data, TOKEN_STACK_ADDITIONAL_CHILD_DATA, childIndex);
      break;
    }

    default:
      break;
  }
}

void sli_zigbee_set_child_token_for_current_network(uint16_t tokenAddress,
                                                    uint8_t childIndex,
                                                    void *data)
{
  switch (tokenAddress) {
    case TOKEN_STACK_CHILD_TABLE: {
      halCommonSetIndexedToken(TOKEN_STACK_CHILD_TABLE, childIndex, data);
      break;
    }

    case TOKEN_STACK_ADDITIONAL_CHILD_DATA: {
      halCommonSetIndexedToken(TOKEN_STACK_ADDITIONAL_CHILD_DATA, childIndex, data);
      break;
    }

    default:
      break;
  }
}

sli_zigbee_event_t* sli_zigbee_get_forked_event(sli_zigbee_event_t *list)
{
  return list;
}
uint8_t sli_zigbee_get_network_index_from_event(sli_zigbee_event_t *event,
                                                sli_zigbee_event_t *list)
{
  return SL_ZIGBEE_NULL_NETWORK_INDEX;
}

uint8_t sli_zigbee_get_network_index_for_forked_global(void)
{
  return 0;
}

bool sli_zigbee_is_pan_id_in_use(sl_802154_pan_id_t panId)
{
  return false;
}

#endif // SL_ZIGBEE_MULTI_NETWORK_STRIPPED
