/***************************************************************************//**
 * @file
 * @brief This file contains function that processes global ZCL message.
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

#include "sl_common.h"

#include "app/framework/include/af.h"
#ifdef SL_COMPONENT_CATALOG_PRESENT
#include "sl_component_catalog.h"
#endif
#include "app/framework/util/common.h"
#ifdef SL_CATALOG_ZIGBEE_IAS_ZONE_CLIENT_PRESENT
#include "ias-zone-client.h"
#define IAS_ZONE_CLIENT_PRESENT
#endif
#ifdef SL_CATALOG_ZIGBEE_KEY_ESTABLISHMENT_PRESENT
#include "key-establishment.h"
#define KEY_ESTABLISHMENT_PRESENT
#endif
#ifdef SL_CATALOG_ZIGBEE_SMART_ENERGY_REGISTRATION_PRESENT
#include "smart-energy-registration.h"
#endif
#ifdef SL_CATALOG_ZIGBEE_TRUST_CENTER_KEEPALIVE_PRESENT
#include "trust-center-keepalive.h"
#define TRUST_CENTER_KEEPALIVE_PRESENT
#endif
#ifdef SL_CATALOG_ZIGBEE_TEST_HARNESS_PRESENT
#include "test-harness.h"
#define TEST_HARNESS_PRESENT
#endif
#ifdef SL_CATALOG_ZIGBEE_WWAH_SERVER_SILABS_PRESENT
#include "wwah-server-silabs.h"
#define WWAH_SERVER_SILABS_PRESENT
#endif
#ifdef SL_CATALOG_ZIGBEE_COMMS_HUB_FUNCTION_SUB_GHZ_PRESENT
#include "comms-hub-function-sub-ghz.h"
#define COMMS_HUB_FUNCTION_SUB_GHZ_PRESENT
#endif
#ifdef SL_CATALOG_ZIGBEE_SIMPLE_METERING_SERVER_PRESENT
#include "simple-metering-server.h"
#define SIMPLE_METERING_SERVER_PRESENT
#endif
#include "zigbee_zcl_callback_dispatcher.h" // sli_zigbee_af_retrieve_attribute_and_craft_response
#ifdef SL_CATALOG_ZIGBEE_GBCS_COMPATIBILITY_PRESENT
#define GBCS_COMPATIBILITY_PRESENT
#endif

// flag to keep track of the fact that we just sent a read attr for time and
// we should set our time to the result of the read attr response.
bool sli_zigbee_af_syncing_time = false;

#ifdef GBCS_COMPATIBILITY_PRESENT
// Some GBCS use cases (e.g. GCS15e, GCS21f) require that ReadAttributesResponse
// should be send back with Disable Default Response flag set. The only pattern
// is that the decision is based on the cluster and attribute IDs requested.
// To reduce the possibility of false positives, we disable default response
// only for responses containing at least the specified minimum of attributes.
#define MIN_MATCHING_ATTR_IDS_TO_DISABLE_DEFAULT_RESPONSE       3
#endif

#define DISC_ATTR_RSP_MAX_ATTRIBUTES                                             \
  (((SL_ZIGBEE_AF_MAXIMUM_APS_PAYLOAD_LENGTH                                     \
     - SL_ZIGBEE_AF_ZCL_MANUFACTURER_SPECIFIC_OVERHEAD /* max ZCL header size */ \
     - 1)       /* discovery is complete bool */                                 \
    / 3)        /* size of one discover attributes response entry */             \
   % UINT8_MAX) /* make count fit in an 8 bit integer */
#define DISC_ATTR_EXT_RSP_MAX_ATTRIBUTES                                         \
  (((SL_ZIGBEE_AF_MAXIMUM_APS_PAYLOAD_LENGTH                                     \
     - SL_ZIGBEE_AF_ZCL_MANUFACTURER_SPECIFIC_OVERHEAD /* max ZCL header size */ \
     - 1)       /* discovery is complete bool */                                 \
    / 4)        /* size of one discover attributes extended response entry */    \
   % UINT8_MAX) /* make count fit in an 8 bit integer */

#if defined(SL_ZIGBEE_AF_SUPPORT_COMMAND_DISCOVERY)
static void printDiscoverCommandsResponse(bool generated,
                                          uint16_t clusterId,
                                          bool discoveryComplete,
                                          uint8_t* buffer,
                                          uint16_t length)
{
  uint16_t i;
  sl_zigbee_af_service_discovery_print("Discover Commands response (complete: %c), %s IDs: ",
                                       (discoveryComplete
                                        ? 'y'
                                        : 'n'),
                                       (generated
                                        ? "Generated"
                                        : "Received"));
  for (i = 0; i < length; i++) {
    sl_zigbee_af_service_discovery_print("0x%X ", buffer[i]);
  }
  sl_zigbee_af_service_discovery_println(".");
}
#endif

bool sli_zigbee_af_process_global_command(sl_zigbee_af_cluster_command_t *cmd)
{
  uint16_t attrId;
  uint8_t frameControl;
  uint8_t *mfgCodePtr = NULL;
  // This is a little clumsy but easier to read and port
  // from earlier implementation.
  sl_zigbee_af_cluster_id_t clusterId = cmd->apsFrame->clusterId;
  uint8_t zclCmd = cmd->commandId;
  uint8_t *message = cmd->buffer;
  uint16_t msgLen = cmd->bufLen;
  uint16_t msgIndex = cmd->payloadStartIndex;
  uint8_t clientServerMask = (cmd->direction == ZCL_DIRECTION_CLIENT_TO_SERVER
                              ? CLUSTER_MASK_SERVER
                              : CLUSTER_MASK_CLIENT);

  // If we are disabled then we can only respond to read or write commands
  // or identify cluster (see device enabled attr of basic cluster)
  if (!sl_zigbee_af_is_device_enabled(cmd->apsFrame->destinationEndpoint)
      && zclCmd != ZCL_READ_ATTRIBUTES_COMMAND_ID
      && zclCmd != ZCL_WRITE_ATTRIBUTES_COMMAND_ID
      && zclCmd != ZCL_WRITE_ATTRIBUTES_UNDIVIDED_COMMAND_ID
      && zclCmd != ZCL_WRITE_ATTRIBUTES_NO_RESPONSE_COMMAND_ID
      && clusterId != ZCL_IDENTIFY_CLUSTER_ID) {
    sl_zigbee_af_core_println("disabled");
    sl_zigbee_af_debug_println("%pd, dropping global cmd:%x", "disable", zclCmd);
    sl_zigbee_af_send_default_response(cmd, SL_ZIGBEE_ZCL_STATUS_FAILURE);
    return true;
  }

  // If a manufacturer-specific command arrives using our special internal "not
  // manufacturer specific" code, we need to reject it outright without letting
  // it pass through to the rest of the code.  The internal read and write APIs
  // would interpret it as a standard attribute or cluster and return incorrect
  // results.
  if (cmd->mfgSpecific && cmd->mfgCode == SL_ZIGBEE_AF_NULL_MANUFACTURER_CODE) {
    goto kickout;
  }

  // Clear out the response buffer by setting its length to zero
  appResponseLength = 0;

  // Make the ZCL header for the response
  // note: cmd byte is set below
  frameControl = (ZCL_GLOBAL_COMMAND
                  | (cmd->direction == ZCL_DIRECTION_CLIENT_TO_SERVER
                     ? ZCL_FRAME_CONTROL_SERVER_TO_CLIENT
                     | SL_ZIGBEE_AF_DEFAULT_RESPONSE_POLICY_RESPONSES
                     : ZCL_FRAME_CONTROL_CLIENT_TO_SERVER
                     | SL_ZIGBEE_AF_DEFAULT_RESPONSE_POLICY_RESPONSES));
  if (cmd->mfgSpecific) {
    frameControl |= ZCL_MANUFACTURER_SPECIFIC_MASK;
  }
  (void) sl_zigbee_af_put_int8u_in_resp(frameControl);
#if (SL_ZIGBEE_AF_PLUGIN_ZCL_CLUSTER_ENABLE_DISABLE_RUN_TIME == 1)
#if !defined(SL_ZIGBEE_TEST)
  if (!sl_zigbee_af_contains_cluster_with_mfg_code(cmd->apsFrame->destinationEndpoint,
                                                   clusterId,
                                                   cmd->mfgCode)) {
    sl_zigbee_af_send_default_response(cmd, SL_ZIGBEE_ZCL_STATUS_UNSUPPORTED_CLUSTER);
    return true;
  }
#endif //SL_ZIGBEE_TEST
#endif //SL_ZIGBEE_AF_PLUGIN_ZCL_CLUSTER_ENABLE_DISABLE_RUN_TIME
  if (cmd->mfgSpecific) {
    mfgCodePtr = (uint8_t *)sl_zigbee_af_put_int16u_in_resp(cmd->mfgCode);
  }
  (void) sl_zigbee_af_put_int8u_in_resp(cmd->seqNum);

  switch (zclCmd) {
    // The format of the read attributes cmd is:
    // ([attr ID:2]) * N
    // The format of the read attributes response is:
    // ([attr ID:2] [status:1] [data type:0/1] [data:0/N]) * N
    case ZCL_READ_ATTRIBUTES_COMMAND_ID:
    {
      sl_zigbee_af_status_t status;
      sl_zigbee_af_attributes_println("%p: clus %2x", "READ_ATTR", clusterId);
      // Set the cmd byte - this is byte 3 index 2, but since we have
      // already incremented past the 3 byte ZCL header (our index is at 3),
      // this gets written to "-1" since 3 - 1 = 2.
      (void) sl_zigbee_af_put_int8u_in_resp(ZCL_READ_ATTRIBUTES_RESPONSE_COMMAND_ID);

      // This message contains N 2-byte attr IDs after the 3 byte ZCL header,
      // for each one we need to look it up and make a response
      while (msgIndex + 2u <= msgLen) {
        // Get the attribute ID and store it in the response buffer
        // least significant byte is first OTA
        attrId = sl_zigbee_af_get_int16u(message, msgIndex, msgLen);

#ifdef GBCS_COMPATIBILITY_PRESENT
        // GBCS explicitly lists some commands that need to be sent with "disable
        // default response" flag set, including some ReadAttributes responses.
        // We make it conditional on GBCS so it does not affect standard SE apps.
        {
          static const struct {
            sl_zigbee_af_cluster_id_t clusterId;
            uint16_t attrId;
          } noDefaultResponseSet[] = {
            { ZCL_PRICE_CLUSTER_ID, ZCL_THRESHOLD_MULTIPLIER_ATTRIBUTE_ID },
            { ZCL_PRICE_CLUSTER_ID, ZCL_THRESHOLD_DIVISOR_ATTRIBUTE_ID },
            { ZCL_PRICE_CLUSTER_ID, ZCL_STANDING_CHARGE_ATTRIBUTE_ID },
            { ZCL_PRICE_CLUSTER_ID, ZCL_TARIFF_UNIT_OF_MEASURE_ATTRIBUTE_ID },
            { ZCL_SIMPLE_METERING_CLUSTER_ID, ZCL_UNIT_OF_MEASURE_ATTRIBUTE_ID },
            { ZCL_SIMPLE_METERING_CLUSTER_ID, ZCL_MULTIPLIER_ATTRIBUTE_ID },
            { ZCL_SIMPLE_METERING_CLUSTER_ID, ZCL_DIVISOR_ATTRIBUTE_ID },
          };
          uint8_t i;
          uint8_t foundMatchingAttrIdsCount = 0;

          for (i = 0; i < sizeof noDefaultResponseSet / sizeof noDefaultResponseSet[0]; ++i) {
            if (noDefaultResponseSet[i].clusterId == clusterId
                && noDefaultResponseSet[i].attrId == attrId) {
              if (++foundMatchingAttrIdsCount >= MIN_MATCHING_ATTR_IDS_TO_DISABLE_DEFAULT_RESPONSE) {
                sl_zigbee_af_set_disable_default_response(SL_ZIGBEE_AF_DISABLE_DEFAULT_RESPONSE_ONE_SHOT);
                break;
              }
            }
          }
        }

  #ifdef COMMS_HUB_FUNCTION_SUB_GHZ_PRESENT
        // This plugin sets channel change notification flags and needs to know
        // when those flags have been read.
        if (clientServerMask == CLUSTER_MASK_SERVER) {
          sli_zigbee_af_comms_hub_function_sub_ghz_read_attribute_notification(cmd->source,
                                                                               clusterId,
                                                                               attrId);
        }
  #endif
#endif

        // This function reads the attribute and creates the correct response
        // in the response buffer
        if (!sli_zigbee_af_retrieve_attribute_and_craft_response(cmd->apsFrame->destinationEndpoint,
                                                                 clusterId,
                                                                 attrId,
                                                                 clientServerMask,
                                                                 cmd->mfgCode,
                                                                 (SL_ZIGBEE_AF_RESPONSE_BUFFER_LEN
                                                                  - appResponseLength))) {
          status = sl_zigbee_af_retrieve_attribute_and_craft_response(cmd->apsFrame->destinationEndpoint,
                                                                      clusterId,
                                                                      attrId,
                                                                      clientServerMask,
                                                                      cmd->mfgCode,
                                                                      (SL_ZIGBEE_AF_RESPONSE_BUFFER_LEN
                                                                       - appResponseLength));
          if (status == SL_ZIGBEE_ZCL_STATUS_INSUFFICIENT_SPACE) {
            break;
          }
        }

        // Go to next attrID
        msgIndex += 2u;
      }
    }

      sl_zigbee_af_send_response();
      return true;

    // Write undivided means all attributes must be written in order to write
    // any of them. So first do a check. If the check fails, send back a fail
    // response. If it works, fall through to the normal write attr code.
    // write attr responses are the same for undivided and normal writes.
    case ZCL_WRITE_ATTRIBUTES_UNDIVIDED_COMMAND_ID:
    {
      uint8_t numFailures = 0;
      uint8_t dataType;
      uint16_t dataSize;
      sl_zigbee_af_status_t status;

      (void) sl_zigbee_af_put_int8u_in_resp(ZCL_WRITE_ATTRIBUTES_RESPONSE_COMMAND_ID);

      // Go through the message until there are no more attrID/type/data
      while (msgIndex < msgLen - 3u) {
        attrId = sl_zigbee_af_get_int16u(message, msgIndex, msgLen);
        dataType = sl_zigbee_af_get_int8u(message, msgIndex + 2u, msgLen);

        dataSize = sl_zigbee_af_attribute_value_size(dataType,
                                                     message + msgIndex + 3,
                                                     msgLen - (msgIndex + 3u));

        // Check to see if there are dataSize bytes available in the message
        if (dataSize == 0u) {
          // This command is malformed
          status = SL_ZIGBEE_ZCL_STATUS_MALFORMED_COMMAND;
        } else {
          status = sl_zigbee_af_verify_attribute_write(cmd->apsFrame->destinationEndpoint,
                                                       clusterId,
                                                       attrId,
                                                       clientServerMask,
                                                       cmd->mfgCode,
                                                       &(message[msgIndex + 3u]),
                                                       dataType);
        }

        if (status != SL_ZIGBEE_ZCL_STATUS_SUCCESS) {
          numFailures++;
          // Write to the response buffer - status and then attrID
          (void) sl_zigbee_af_put_int8u_in_resp(status);
          (void) sl_zigbee_af_put_int16u_in_resp(attrId);

          sl_zigbee_af_attributes_println("WRITE: clus %2x attr %2x ", clusterId, attrId);
          sl_zigbee_af_attributes_println("FAIL %x", status);
          sl_zigbee_af_core_flush();
          if (status == SL_ZIGBEE_ZCL_STATUS_MALFORMED_COMMAND) {
            // this attribute is malformed, terminate attribute processing.
            break;
          }
        }

        // Increment past the attribute id (two bytes), the type (one byte), and
        // the data (N bytes, including the length byte for strings).
        msgIndex += 3u + dataSize;
      }
      // If there are any failures, send the response and exit
      if (numFailures > 0u) {
        sl_zigbee_af_send_response();
        return true;
      }
    }
      // Reset message back to start
      msgIndex = cmd->payloadStartIndex;
      appResponseLength = (cmd->mfgSpecific ? 4u : 2u);
      SL_FALLTHROUGH
    // DO NOT BREAK from this case

    // the format of the write attributes cmd is:
    // ([attr ID:2] [data type:1] [data:N]) * N
    // the format of the write attributes response is:
    // ([status 1] [attr ID 2]) * n
    // ONLY errors are reported unless all are successful then a single success
    // is sent. write attr no response is handled by just executing the same
    // code but not setting the flag that sends the response at the end.
    case ZCL_WRITE_ATTRIBUTES_NO_RESPONSE_COMMAND_ID:
    case ZCL_WRITE_ATTRIBUTES_COMMAND_ID:
    {
      uint8_t numFailures = 0;
      uint8_t numSuccess = 0;
      uint8_t dataType;
      uint16_t dataSize;
#if (BIGENDIAN_CPU)
      uint8_t writeData[ZCL_ATTRIBUTE_MAX_DATA_SIZE];
#endif //(BIGENDIAN_CPU)
      sl_zigbee_af_status_t status;

      // set the cmd byte - this is byte 3 index 2, but since we have
      // already incremented past the 3 byte ZCL header (our index is at 3),
      // this gets written to "-1" since 3 - 1 = 2.
      (void) sl_zigbee_af_put_int8u_in_resp(ZCL_WRITE_ATTRIBUTES_RESPONSE_COMMAND_ID);

      // go through the message until there are no more attrID/type/data
      while (msgLen > msgIndex + 3u) {
        attrId = sl_zigbee_af_get_int16u(message, msgIndex, msgLen);
        dataType = sl_zigbee_af_get_int8u(message, msgIndex + 2u, msgLen);

        dataSize = sl_zigbee_af_attribute_value_size(dataType,
                                                     message + msgIndex + 3,
                                                     msgLen - (msgIndex + 3u));

        // the data is sent little endian over-the-air, it needs to be
        // inserted into the table big endian for the EM250 and little
        // endian for the EZSP hosts. This means for the EM250 the data
        // needs to be reversed before sending to writeAttributes
#if (BIGENDIAN_CPU)
        if (dataSize != 0 && dataSize <= ZCL_ATTRIBUTE_MAX_DATA_SIZE) {
          // strings go over the air as length byte and then in human
          // readable format. These should not be flipped.
          if (sl_zigbee_af_is_this_data_type_a_string_type(dataType)) {
            memmove(writeData, message + msgIndex + 3, dataSize);
          } else {
            // the data is sent little endian over-the-air, it needs to be
            // inserted into the table big endian
            uint16_t i;
            for (i = 0; i < dataSize; i++) {
              writeData[i] = message[msgIndex + 3 + dataSize - i - 1];
            }
          }
#else //(BIGENDIAN_CPU)
        if (dataSize != 0u) {
#endif //(BIGENDIAN_CPU)

          status = sl_zigbee_af_write_attribute_external(cmd->apsFrame->destinationEndpoint,
                                                         clusterId,
                                                         attrId,
                                                         clientServerMask,
                                                         cmd->mfgCode,
  #if (BIGENDIAN_CPU)
                                                         writeData,
  #else //(BIGENDIAN_CPU)
                                                         &(message[msgIndex + 3u]),
  #endif //(BIGENDIAN_CPU)
                                                         dataType);
          sl_zigbee_af_attributes_print("WRITE: clus %2x attr %2x ",
                                        clusterId,
                                        attrId);
          if (status == SL_ZIGBEE_ZCL_STATUS_SUCCESS) {
            numSuccess++;
            sl_zigbee_af_attributes_println("OK");
          } else {
            numFailures++;
            // write to the response buffer - status and then attrID
            (void) sl_zigbee_af_put_int8u_in_resp(status);
            (void) sl_zigbee_af_put_int16u_in_resp(attrId);
            sl_zigbee_af_attributes_println("FAIL %x", status);
          }
          sl_zigbee_af_core_flush();

          // Increment past the attribute id (two bytes), the type (one byte), and
          // the data (N bytes, including the length byte for strings).
          msgIndex += 3u + dataSize;
        } else {
          numFailures++;
          status = SL_ZIGBEE_ZCL_STATUS_INVALID_VALUE;
          // write to the response buffer - status and then attrID
          (void) sl_zigbee_af_put_int8u_in_resp(status);
          (void) sl_zigbee_af_put_int16u_in_resp(attrId);
          sl_zigbee_af_attributes_println("FAIL %x", status);
          // size exceeds buffer, terminate loop
          break;
        }
      }

      // always send a response unless the cmd requested no response
      if (zclCmd == ZCL_WRITE_ATTRIBUTES_NO_RESPONSE_COMMAND_ID) {
        return true;
      }

      if (numFailures == 0u) {
        // if no failures and no success this means the packet was too short
        // print an error message but still return true as we consumed the
        // message
        if (numSuccess == 0u) {
          sl_zigbee_af_attributes_println("WRITE: too short");
          sl_zigbee_af_send_default_response(cmd, SL_ZIGBEE_ZCL_STATUS_MALFORMED_COMMAND);
          return true;
        }
        // if no failures and at least one success, write a success status
        // that means everything worked
        else {
          (void) sl_zigbee_af_put_int8u_in_resp(SL_ZIGBEE_ZCL_STATUS_SUCCESS);
        }
      }
      sl_zigbee_af_send_response();
      return true;
    }

    // the format of discover is: [start attr ID:2] [max attr IDs:1]
    // the format of the response is: [done:1] ([attrID:2] [type:1]) * N
    case ZCL_DISCOVER_ATTRIBUTES_COMMAND_ID:
    case ZCL_DISCOVER_ATTRIBUTES_EXTENDED_COMMAND_ID:
    {
      sl_zigbee_af_attribute_id_t startingAttributeId;
      uint8_t numberAttributes;
      uint8_t *complete;

      sl_zigbee_af_attributes_println("%p%p: clus %2x", "DISC_ATTR",
                                      (zclCmd == ZCL_DISCOVER_ATTRIBUTES_EXTENDED_COMMAND_ID ? "_EXT" : ""),
                                      clusterId);

      // set the cmd byte - this is byte 3 index 2, but since we have
      // already incremented past the 3 byte ZCL header (our index is at 3),
      // this gets written to "-1" since 3 - 1 = 2.
      (void) sl_zigbee_af_put_int8u_in_resp(
        (zclCmd == ZCL_DISCOVER_ATTRIBUTES_COMMAND_ID
         ? ZCL_DISCOVER_ATTRIBUTES_RESPONSE_COMMAND_ID
         : ZCL_DISCOVER_ATTRIBUTES_EXTENDED_RESPONSE_COMMAND_ID));

      // get the attrId to start on and the max count
      startingAttributeId = sl_zigbee_af_get_int16u(message, msgIndex, msgLen);
      numberAttributes = sl_zigbee_af_get_int8u(message, msgIndex + 2u, msgLen);

      // BUGZID: EMAPPFWKV2-828, EMAPPFWKV2-1401
      if (zclCmd == ZCL_DISCOVER_ATTRIBUTES_COMMAND_ID
          && numberAttributes > DISC_ATTR_RSP_MAX_ATTRIBUTES) {
        numberAttributes = DISC_ATTR_RSP_MAX_ATTRIBUTES;
      } else if (zclCmd == ZCL_DISCOVER_ATTRIBUTES_EXTENDED_COMMAND_ID
                 && numberAttributes > DISC_ATTR_EXT_RSP_MAX_ATTRIBUTES) {
        numberAttributes = DISC_ATTR_EXT_RSP_MAX_ATTRIBUTES;
      } else {
        // MISRA requires ..else if.. to have terminating else.
      }

      // Check for mfg-spec wildcard and resolve mfg code if necessary.
      if (cmd->mfgSpecific && cmd->mfgCode == 0xFFFFu) {
        uint16_t resolvedMfgCode
          = sli_zigbee_af_resolve_mfg_code_for_discover_attribute(cmd->apsFrame->destinationEndpoint,
                                                                  clusterId,
                                                                  startingAttributeId,
                                                                  clientServerMask);
        if (resolvedMfgCode != 0xFFFFu && mfgCodePtr != NULL) {
          // (Note: retain wildcard mfg code and let it fail if not resolved.)
          // Replace wildcard mfg code in cmd for subsequent extract processing.
          cmd->mfgCode = resolvedMfgCode;
          // Write Response's mfg code field with resolved value (LE order).
          *mfgCodePtr = (uint8_t)(resolvedMfgCode & 0x00FFu);
          *(mfgCodePtr + 1) = (uint8_t)((resolvedMfgCode & 0xFF00u) >> 8);
        }
      }

      // The response has a one-byte field indicating whether discovery is
      // complete.  We can't populate that field until we've finished going
      // through all the attributes, so save a placeholder, write a temporary
      // value for now (so that the offset moves forward), and write the real
      // value when we're done.
      complete = &(appResponseData[appResponseLength]);
      (void) sl_zigbee_af_put_int8u_in_resp(false);
      *complete = sl_zigbee_af_read_sequential_attributes_add_to_response(
        cmd->apsFrame->destinationEndpoint,
        clusterId,
        startingAttributeId,
        clientServerMask,
        cmd->mfgCode,
        numberAttributes,
        (zclCmd == ZCL_DISCOVER_ATTRIBUTES_EXTENDED_COMMAND_ID));
      sl_zigbee_af_send_response();
      return true;
    }

    case ZCL_CONFIGURE_REPORTING_COMMAND_ID:
      if (sl_zigbee_af_configure_reporting_command_cb(cmd)) {
        return true;
      }
      break;

    case ZCL_READ_REPORTING_CONFIGURATION_COMMAND_ID:
      if (sl_zigbee_af_read_reporting_configuration_command_cb(cmd)) {
        return true;
      }
      break;

    // ([attribute id:2] [status:1] [type:0/1] [value:0/V])+
    case ZCL_READ_ATTRIBUTES_RESPONSE_COMMAND_ID:
      // The "timesync" command in the CLI sends a Read Attributes command for the
      // Time attribute on another device and then sets a flag.  If that flag is
      // set and a Read Attributes Response command for the time comes in, we set
      // the time to the value in the message.
      if (clusterId == ZCL_TIME_CLUSTER_ID) {
        if (sli_zigbee_af_syncing_time
            && !cmd->mfgSpecific
            && msgLen - msgIndex == 8u // attr:2 status:1 type:1 data:4
            && (sl_zigbee_af_get_int16u(message, msgIndex, msgLen)
                == ZCL_TIME_ATTRIBUTE_ID)
            && (sl_zigbee_af_get_int8u(message, msgIndex + 2u, msgLen)
                == SL_ZIGBEE_ZCL_STATUS_SUCCESS)
            && (sl_zigbee_af_get_int8u(message, msgIndex + 3u, msgLen)
                == ZCL_UTC_TIME_ATTRIBUTE_TYPE)) {
          sl_zigbee_af_set_time(sl_zigbee_af_get_int32u(message, msgIndex + 4u, msgLen));
          sl_zigbee_af_debug_println("time sync ok, time: %4x", sl_zigbee_af_get_current_time());
          sli_zigbee_af_syncing_time = false;
        }
#ifdef SL_ZIGBEE_AF_PLUGIN_SMART_ENERGY_REGISTRATION_TIME_SOURCE_REQUIRED
        sli_zigbee_af_smart_energy_registration_read_attributes_response_callback(message + msgIndex,
                                                                                  msgLen - msgIndex);
#endif //SL_ZIGBEE_AF_PLUGIN_SMART_ENERGY_REGISTRATION_TIME_SOURCE_REQUIRED
#ifdef WWAH_SERVER_SILABS_PRESENT
        sli_zigbee_af_sl_wwah_read_attributes_response_callback(clusterId, message, msgLen);
#endif // WWAH_SERVER_SILABS_PRESENT
      }

#ifdef TRUST_CENTER_KEEPALIVE_PRESENT
      if (clusterId == ZCL_KEEPALIVE_CLUSTER_ID
          && !cmd->mfgSpecific) {
        sli_zigbee_af_trust_center_keepalive_read_attributes_response_callback(message + msgIndex,
                                                                               msgLen - msgIndex);
      }
#endif // TRUST_CENTER_KEEPALIVE_PRESENT

#ifdef KEY_ESTABLISHMENT_PRESENT
      if (clusterId == ZCL_KEY_ESTABLISHMENT_CLUSTER_ID
          && !cmd->mfgSpecific
          && msgLen - msgIndex == 6u //attr:2 status:1 type:1 data:2
          && (sl_zigbee_af_get_int16u(message, msgIndex, msgLen)
              == ZCL_KEY_ESTABLISHMENT_SUITE_CLIENT_ATTRIBUTE_ID)
          && (sl_zigbee_af_get_int8u(message, msgIndex + 2u, msgLen)
              == SL_ZIGBEE_ZCL_STATUS_SUCCESS)
          && ((sl_zigbee_af_get_int8u(message, msgIndex + 3u, msgLen) == ZCL_ENUM16_ATTRIBUTE_TYPE)
              || (sl_zigbee_af_get_int8u(message, msgIndex + 3u, msgLen) == ZCL_BITMAP16_ATTRIBUTE_TYPE))) {
        uint16_t suite = sl_zigbee_af_get_int16u(message, msgIndex + 4u, msgLen);
        sl_zigbee_af_key_establishment_read_attributes_cb(suite);
      }
#endif // KEY_ESTABLISHMENT_PRESENT

#ifdef TEST_HARNESS_PRESENT
      sl_zigbee_af_test_harness_read_attributes_response_cb(clusterId,
                                                            message + msgIndex,
                                                            msgLen - msgIndex);
#endif // TEST_HARNESS_PRESENT

#ifdef IAS_ZONE_CLIENT_PRESENT
      sl_zigbee_af_ias_zone_client_read_attributes_response_cb(clusterId,
                                                               message + msgIndex,
                                                               msgLen - msgIndex);
#endif // IAS_ZONE_CLIENT_PRESENT

#ifdef SIMPLE_METERING_SERVER_PRESENT
      sl_zigbee_af_simple_metering_cluster_read_attributes_response_cb(clusterId,
                                                                       message + msgIndex,
                                                                       msgLen - msgIndex);
#endif // SIMPLE_METERING_SERVER_PRESENT

      if (!sli_zigbee_af_read_attributes_response(clusterId,
                                                  message + msgIndex,
                                                  msgLen - msgIndex)) {
        sl_zigbee_af_send_default_response(cmd, SL_ZIGBEE_ZCL_STATUS_SUCCESS);
      }
      return true;

    // ([status:1] [attribute id:2])+
    case ZCL_WRITE_ATTRIBUTES_RESPONSE_COMMAND_ID:

  #ifdef TEST_HARNESS_PRESENT
      sl_zigbee_af_test_harness_write_attributes_response_cb(clusterId,
                                                             message + msgIndex,
                                                             msgLen - msgIndex);
  #endif // TEST_HARNESS_PRESENT

  #ifdef IAS_ZONE_CLIENT_PRESENT
      sl_zigbee_af_ias_zone_client_write_attributes_response_cb(clusterId,
                                                                message + msgIndex,
                                                                msgLen - msgIndex);
  #endif // IAS_ZONE_CLIENT_PRESENT

      if (!sl_zigbee_af_write_attributes_response_cb(clusterId,
                                                     message + msgIndex,
                                                     msgLen - msgIndex)) {
        sl_zigbee_af_send_default_response(cmd, SL_ZIGBEE_ZCL_STATUS_SUCCESS);
      }
      return true;

    // ([status:1] [direction:1] [attribute id:2])+
    case ZCL_CONFIGURE_REPORTING_RESPONSE_COMMAND_ID:
      if (!sl_zigbee_af_configure_reporting_response_cb(clusterId,
                                                        message + msgIndex,
                                                        msgLen - msgIndex)) {
        sl_zigbee_af_send_default_response(cmd, SL_ZIGBEE_ZCL_STATUS_SUCCESS);
      }
      return true;

    // ([status:1] [direction:1] [attribute id:2] [type:0/1] ...
    // ... [min interval:0/2] [max interval:0/2] [reportable change:0/V] ...
    // ... [timeout:0/2])+
    case ZCL_READ_REPORTING_CONFIGURATION_RESPONSE_COMMAND_ID:
      if (!sl_zigbee_af_read_reporting_configuration_response_cb(clusterId,
                                                                 message + msgIndex,
                                                                 msgLen - msgIndex)) {
        sl_zigbee_af_send_default_response(cmd, SL_ZIGBEE_ZCL_STATUS_SUCCESS);
      }
      return true;

    // ([attribute id:2] [type:1] [data:V])+
    case ZCL_REPORT_ATTRIBUTES_COMMAND_ID:
      if (!sli_zigbee_af_report_attributes(clusterId,
                                           message + msgIndex,
                                           msgLen - msgIndex)) {
        sl_zigbee_af_send_default_response(cmd, SL_ZIGBEE_ZCL_STATUS_SUCCESS);
      }
      return true;

    // [command id:1] [status:1]
    case ZCL_DEFAULT_RESPONSE_COMMAND_ID:
    {
      sl_zigbee_af_status_t status;
      uint8_t commandId;
      commandId = sl_zigbee_af_get_int8u(message, msgIndex, msgLen);
      msgIndex++;
      status = (sl_zigbee_af_status_t)sl_zigbee_af_get_int8u(message, msgIndex, msgLen);

      sl_zigbee_af_cluster_default_response_with_mfg_code_cb(cmd->apsFrame->destinationEndpoint,
                                                             clusterId,
                                                             commandId,
                                                             status,
                                                             clientServerMask,
                                                             cmd->mfgCode);
      sl_zigbee_af_default_response_cb(clusterId, commandId, status);
      return true;
    }

    // [discovery complete:1] ([attribute id:2] [type:1])*
    case ZCL_DISCOVER_ATTRIBUTES_RESPONSE_COMMAND_ID:
    case ZCL_DISCOVER_ATTRIBUTES_EXTENDED_RESPONSE_COMMAND_ID:
    {
      bool discoveryComplete = (sl_zigbee_af_get_int8u(message, msgIndex, msgLen) != 0u);
      msgIndex++;
      if (!sl_zigbee_af_discover_attributes_response_cb(clusterId,
                                                        discoveryComplete,
                                                        message + msgIndex,
                                                        msgLen - msgIndex,
                                                        (zclCmd
                                                         == ZCL_DISCOVER_ATTRIBUTES_EXTENDED_RESPONSE_COMMAND_ID))) {
        sl_zigbee_af_send_default_response(cmd, SL_ZIGBEE_ZCL_STATUS_SUCCESS);
      }
      return true;
    }

#ifdef SL_ZIGBEE_AF_SUPPORT_COMMAND_DISCOVERY
    // Command discovery takes a bit of flash because we need to add structs
    // for commands into the generated hader. Hence it's all configurable.
    case ZCL_DISCOVER_COMMANDS_RECEIVED_COMMAND_ID:
    case ZCL_DISCOVER_COMMANDS_GENERATED_COMMAND_ID:
    {
      uint8_t startCommandIdentifier = sl_zigbee_af_get_int8u(message, msgIndex, msgLen);
      uint8_t maximumCommandIdentifiers = sl_zigbee_af_get_int8u(message, msgIndex + 1, msgLen);
      uint16_t savedIndex;
      bool flag;

      // Ok. This is the command that matters.
      if ( zclCmd == ZCL_DISCOVER_COMMANDS_RECEIVED_COMMAND_ID ) {
        (void) sl_zigbee_af_put_int8u_in_resp(ZCL_DISCOVER_COMMANDS_RECEIVED_RESPONSE_COMMAND_ID);
        flag = false;
      } else {
        (void) sl_zigbee_af_put_int8u_in_resp(ZCL_DISCOVER_COMMANDS_GENERATED_RESPONSE_COMMAND_ID);
        flag = true;
      }

      // Check for mfg-spec wildcard and resolve mfg code if necessary.
      if (cmd->mfgSpecific && cmd->mfgCode == 0xFFFF) {
        uint16_t resolvedMfgCode
          = sli_zigbee_af_resolve_mfg_code_for_discover_command(flag, cmd, clusterId, startCommandIdentifier);
        if (resolvedMfgCode != 0xFFFF && mfgCodePtr != NULL) {
          // (Note: retain wildcard mfg code and let it fail if not resolved.)
          // Replace wildcard mfg code in cmd for subsequent extract processing.
          cmd->mfgCode = resolvedMfgCode;
          // Write Response's mfg code field with resolved value (LE order).
          *mfgCodePtr = (uint8_t)(resolvedMfgCode & 0x00FF);
          *(mfgCodePtr + 1) = (uint8_t)((resolvedMfgCode & 0xFF00) >> 8);
        }
      }

      savedIndex = appResponseLength;
      flag = sl_zigbee_af_extract_command_ids(flag,
                                              cmd,
                                              clusterId,
                                              appResponseData + appResponseLength + 1,
                                              SL_ZIGBEE_AF_RESPONSE_BUFFER_LEN - appResponseLength - 1,
                                              &appResponseLength,
                                              startCommandIdentifier,
                                              maximumCommandIdentifiers);
      appResponseData[savedIndex] = (flag ? 1 : 0);
      appResponseLength++;
      sl_zigbee_af_send_response();
      return true;
    }
    case ZCL_DISCOVER_COMMANDS_RECEIVED_RESPONSE_COMMAND_ID:
    {
      bool discoveryComplete = sl_zigbee_af_get_int8u(message, msgIndex, msgLen);
      msgIndex++;
      if ( msgIndex <= msgLen ) {
        printDiscoverCommandsResponse(false,  // is ZCL command generated?
                                      clusterId,
                                      discoveryComplete,
                                      message + msgIndex,
                                      msgLen - msgIndex);
        if (!sl_zigbee_af_discover_commands_received_response_cb(clusterId,
                                                                 cmd->mfgCode,
                                                                 discoveryComplete,
                                                                 message + msgIndex,
                                                                 msgLen - msgIndex)) {
          sl_zigbee_af_send_default_response(cmd, SL_ZIGBEE_ZCL_STATUS_SUCCESS);
        }
        return true;
      } else {
        return false;
      }
    }
    case ZCL_DISCOVER_COMMANDS_GENERATED_RESPONSE_COMMAND_ID:
    {
      bool discoveryComplete = sl_zigbee_af_get_int8u(message, msgIndex, msgLen);
      msgIndex++;
      if ( msgIndex <= msgLen ) {
        printDiscoverCommandsResponse(true,  // is ZCL command generated?
                                      clusterId,
                                      discoveryComplete,
                                      message + msgIndex,
                                      msgLen - msgIndex);
        if (!sl_zigbee_af_discover_commands_generated_response_cb(clusterId,
                                                                  cmd->mfgCode,
                                                                  discoveryComplete,
                                                                  message + msgIndex,
                                                                  msgLen - msgIndex)) {
          sl_zigbee_af_send_default_response(cmd, SL_ZIGBEE_ZCL_STATUS_SUCCESS);
        }
        return true;
      } else {
        return false;
      }
    }

#endif
    default:
      // MISRA requires default case.
      break;
  }

  kickout:
  sl_zigbee_af_send_default_response(cmd, SL_ZIGBEE_ZCL_STATUS_UNSUP_COMMAND);
  return true;
}
