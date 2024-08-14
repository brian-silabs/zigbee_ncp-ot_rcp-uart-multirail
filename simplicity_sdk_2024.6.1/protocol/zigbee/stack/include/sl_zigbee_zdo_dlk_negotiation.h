/***************************************************************************//**
 * @file sl_zigbee_zdo_dlk_negotiation.h
 * @brief declarations of ZDO interface for dynamic link key negotiation
 *******************************************************************************
 * # License
 * <b>Copyright 2023 Silicon Laboratories Inc. www.silabs.com</b>
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

#ifndef SL_ZIGBEE_ZDO_DLK_NEGOTIATION_H
#define SL_ZIGBEE_ZDO_DLK_NEGOTIATION_H

#include "stack/include/sl_zigbee_dlk_negotiation.h"
#include "stack/include/sl_zigbee_tlv_core.h"

/**
 * @brief returns true if dlk is enabled by the stack
 */
bool sl_zigbee_zdo_dlk_enabled(void);

/**
 * @brief callback to override values of the supported key negotiation bitmask
 */
extern void slx_zigbee_gu_zdo_dlk_override_supported_params(sl_zigbee_dlk_supported_negotiation_method *method_mask,
                                                            sl_zigbee_dlk_negotiation_supported_shared_secret_source *secret_mask);
extern bool slx_zigbee_gu_zdo_dlk_override_psk(uint8_t *key_buffer);
extern bool slx_zigbee_gu_zdo_dlk_mangle_packet(sli_buffer_manager_buffer_t *buffer);

/**
 * @brief returns the bitmask indicating the supported key negotiation methods, shared secrets
 */
void sl_zigbee_zdo_dlk_get_supported_negotiation_parameters(sl_zigbee_dlk_supported_negotiation_method *method_mask,
                                                            sl_zigbee_dlk_negotiation_supported_shared_secret_source *secret_mask);

// TODO PSK search
// NOTE parameter selection mechanism determined by the application
extern sl_status_t sl_zigbee_zdo_dlk_select_negotiation_parameters_callback(sl_zigbee_address_info *partner,
                                                                            sl_zigbee_dlk_supported_negotiation_method their_supported_methods,
                                                                            sl_zigbee_dlk_negotiation_supported_shared_secret_source their_supported_secrets,
                                                                            sl_zigbee_dlk_negotiation_method *selected_method,
                                                                            sl_zigbee_dlk_negotiation_shared_secret_source *selected_secret);

// external apis, does state checks, then calls zdo primitive
/**
 * @brief initiates a ZDO Start Key Update request, notifying the target the methods and parameters to use in key negotiation
 * @param target the short id of the device (not neccessarily on network) to initiate key update
 * @param selected_method the enumeration indicating the selected negotiation methods
 * @param selected_secret the enumeration indicating the selected shared secret
 * @return status code indicating if request is submitted successfully...
 */
sl_status_t sl_zigbee_zdo_dlk_start_key_update(sl_zigbee_address_info *target,
                                               sl_zigbee_dlk_negotiation_method selected_method,
                                               sl_zigbee_dlk_negotiation_shared_secret_source selected_secret);
/**
 * @brief initiates a ZDO Start Key Negotiation request
 * @param partner the id-pair of the negotiation partner
 * NOTE only supports trust center?
 * @param selected_method the enumeration indicating the selected negotiation methods
 * @param selected_secret the enumeration indicating the selected shared secret
 * @return status code indicating if request is submitted successfully...
 */
sl_status_t sl_zigbee_zdo_dlk_start_key_negotiation(sl_zigbee_address_info *partner,
                                                    sl_zigbee_dlk_negotiation_method selected_method,
                                                    sl_zigbee_dlk_negotiation_shared_secret_source selected_secret);

#endif // SL_ZIGBEE_ZDO_DLK_NEGOTIATION_H
