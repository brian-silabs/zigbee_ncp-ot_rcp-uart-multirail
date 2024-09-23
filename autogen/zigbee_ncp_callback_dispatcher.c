/***************************************************************************//**
 * @file zigbee_ncp_callback_dispatcher.c
 * @brief ZigBee ncp dispatcher definitions.
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
#include "stack/include/ember.h"
#include "zigbee_ncp_callback_dispatcher.h"


void emberAfEzspGetValueCommandCallback(EmberAfPluginEzspValueCommandContext* context)
{
  emberAfPluginEzspGetValueCommandCallback(context);
  emberAfPluginEzspZigbeeProGetValueCommandCallback(context);
  emberAfPluginEzspSecurityGetValueCommandCallback(context);
}


void emberAfEzspGetExtendedValueCommandCallback(EmberAfPluginEzspValueCommandContext* context)
{
  emberAfPluginEzspZigbeeProGetExtendedValueCommandCallback(context);
}


void emberAfEzspSetValueCommandCallback(EmberAfPluginEzspValueCommandContext* context)
{
  emberAfPluginEzspSetValueCommandCallback(context);
  emberAfPluginEzspZigbeeProSetValueCommandCallback(context);
  emberAfPluginEzspSecuritySetValueCommandCallback(context);
}


void emberAfEzspGetPolicyCommandCallback(EmberAfPluginEzspPolicyCommandContext* context)
{
  emberAfPluginEzspPolicyCommandCallback(context);
  emberAfPluginEzspZigbeeProPolicyCommandCallback(context);
  emberAfPluginEzspSecurityPolicyCommandCallback(context);
  emberAfPluginEzspBindingPolicyCommandCallback(context);
  emberAfPluginEzspZllPolicyCommandCallback(context);
}


void emberAfEzspSetPolicyCommandCallback(EmberAfPluginEzspPolicyCommandContext* context)
{
  emberAfPluginEzspPolicyCommandCallback(context);
  emberAfPluginEzspZigbeeProPolicyCommandCallback(context);
  emberAfPluginEzspSecurityPolicyCommandCallback(context);
  emberAfPluginEzspBindingPolicyCommandCallback(context);
  emberAfPluginEzspZllPolicyCommandCallback(context);
}


void emberAfEzspGetConfigurationValueCommandCallback(EmberAfPluginEzspConfigurationValueCommandContext* context)
{
  emberAfPluginEzspGetConfigurationValueCommandCallback(context);
  emberAfPluginEzspSourceRouteGetConfigurationValueCommandCallback(context);
  emberAfPluginEzspZigbeeProGetConfigurationValueCommandCallback(context);
  emberAfPluginEzspSecurityGetConfigurationValueCommandCallback(context);
  emberAfPluginEzspBindingConfigurationValueCommandCallback(context);
  emberAfPluginEzspZllConfigurationValueCommandCallback(context);
}


void emberAfEzspSetConfigurationValueCommandCallback(EmberAfPluginEzspConfigurationValueCommandContext* context)
{
  emberAfPluginEzspSetConfigurationValueCommandCallback(context);
  emberAfPluginEzspSourceRouteSetConfigurationValueCommandCallback(context);
  emberAfPluginEzspZigbeeProSetConfigurationValueCommandCallback(context);
  emberAfPluginEzspSecuritySetConfigurationValueCommandCallback(context);
  emberAfPluginEzspBindingConfigurationValueCommandCallback(context);
  emberAfPluginEzspZllConfigurationValueCommandCallback(context);
}


void emberAfPluginEzspModifyMemoryAllocationCallback(void)
{
  emberAfPluginEzspZigbeeProModifyMemoryAllocationCallback();
  sli_zigbee_initialize_binding_table();
}


void emberAfPluginEzspPermitHostToNcpFrameCallback(bool* permit)
{
  emberAfPluginEzspBindingPermitHostToNcpFrameCallback(permit);
}
