/*******************************************************************************
 * @file
 * @brief  OpenThread wrapper functions for OpenThread Mdns APIs
 *   allowing access to the thread stack in a multi-threaded environment.
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

#include "sl_ot_rtos_adaptation.h"
#include <openthread/mdns.h>

#if defined(__GNUC__)
#define REAL_NAME(function) __real_##function
#define WRAPPER_NAME(function) __wrap_##function
#define OT_API_REAL_NAME(function) REAL_NAME(function)
#define OT_API_WRAPPER_NAME(function) WRAPPER_NAME(function)
// #elif defined(__IAR_SYSTEMS_ICC__)
//     #define REAL_NAME(function)             $Super$$##function
//     #define WRAPPER_NAME(function)          $Sub$$##function
//     #define OT_API_REAL_NAME(function)      $Super$$__iar_dl##function
//     #define OT_API_WRAPPER_NAME(function)   $Sub$$__iar_dl##function
#else
#error Unsupported compiler
#endif

extern bool    OT_API_REAL_NAME(otMdnsIsEnabled)(otInstance *aInstance);
extern bool    OT_API_REAL_NAME(otMdnsIsQuestionUnicastAllowed)(otInstance *aInstance);
extern otError OT_API_REAL_NAME(otMdnsGetNextBrowser)(otInstance      *aInstance,
                                                      otMdnsIterator  *aIterator,
                                                      otMdnsBrowser   *aBrowser,
                                                      otMdnsCacheInfo *aInfo);
extern otError OT_API_REAL_NAME(otMdnsGetNextHost)(otInstance       *aInstance,
                                                   otMdnsIterator   *aIterator,
                                                   otMdnsHost       *aHost,
                                                   otMdnsEntryState *aState);
extern otError OT_API_REAL_NAME(otMdnsGetNextIp4AddressResolver)(otInstance            *aInstance,
                                                                 otMdnsIterator        *aIterator,
                                                                 otMdnsAddressResolver *aResolver,
                                                                 otMdnsCacheInfo       *aInfo);
extern otError OT_API_REAL_NAME(otMdnsGetNextIp6AddressResolver)(otInstance            *aInstance,
                                                                 otMdnsIterator        *aIterator,
                                                                 otMdnsAddressResolver *aResolver,
                                                                 otMdnsCacheInfo       *aInfo);
extern otError OT_API_REAL_NAME(otMdnsGetNextKey)(otInstance       *aInstance,
                                                  otMdnsIterator   *aIterator,
                                                  otMdnsKey        *aKey,
                                                  otMdnsEntryState *aState);
extern otError OT_API_REAL_NAME(otMdnsGetNextService)(otInstance       *aInstance,
                                                      otMdnsIterator   *aIterator,
                                                      otMdnsService    *aService,
                                                      otMdnsEntryState *aState);
extern otError OT_API_REAL_NAME(otMdnsGetNextSrvResolver)(otInstance        *aInstance,
                                                          otMdnsIterator    *aIterator,
                                                          otMdnsSrvResolver *aResolver,
                                                          otMdnsCacheInfo   *aInfo);
extern otError OT_API_REAL_NAME(otMdnsGetNextTxtResolver)(otInstance        *aInstance,
                                                          otMdnsIterator    *aIterator,
                                                          otMdnsTxtResolver *aResolver,
                                                          otMdnsCacheInfo   *aInfo);
extern otError OT_API_REAL_NAME(otMdnsRegisterHost)(otInstance            *aInstance,
                                                    const otMdnsHost      *aHost,
                                                    otMdnsRequestId        aRequestId,
                                                    otMdnsRegisterCallback aCallback);
extern otError OT_API_REAL_NAME(otMdnsRegisterKey)(otInstance            *aInstance,
                                                   const otMdnsKey       *aKey,
                                                   otMdnsRequestId        aRequestId,
                                                   otMdnsRegisterCallback aCallback);
extern otError OT_API_REAL_NAME(otMdnsRegisterService)(otInstance            *aInstance,
                                                       const otMdnsService   *aService,
                                                       otMdnsRequestId        aRequestId,
                                                       otMdnsRegisterCallback aCallback);
extern otError OT_API_REAL_NAME(otMdnsSetEnabled)(otInstance *aInstance, bool aEnable, uint32_t aInfraIfIndex);
extern otError OT_API_REAL_NAME(otMdnsStartBrowser)(otInstance *aInstance, const otMdnsBrowser *aBrowser);
extern otError OT_API_REAL_NAME(otMdnsStartIp4AddressResolver)(otInstance                  *aInstance,
                                                               const otMdnsAddressResolver *aResolver);
extern otError OT_API_REAL_NAME(otMdnsStartIp6AddressResolver)(otInstance                  *aInstance,
                                                               const otMdnsAddressResolver *aResolver);
extern otError OT_API_REAL_NAME(otMdnsStartSrvResolver)(otInstance *aInstance, const otMdnsSrvResolver *aResolver);
extern otError OT_API_REAL_NAME(otMdnsStartTxtResolver)(otInstance *aInstance, const otMdnsTxtResolver *aResolver);
extern otError OT_API_REAL_NAME(otMdnsStopBrowser)(otInstance *aInstance, const otMdnsBrowser *aBroswer);
extern otError OT_API_REAL_NAME(otMdnsStopIp4AddressResolver)(otInstance                  *aInstance,
                                                              const otMdnsAddressResolver *aResolver);
extern otError OT_API_REAL_NAME(otMdnsStopIp6AddressResolver)(otInstance                  *aInstance,
                                                              const otMdnsAddressResolver *aResolver);
extern otError OT_API_REAL_NAME(otMdnsStopSrvResolver)(otInstance *aInstance, const otMdnsSrvResolver *aResolver);
extern otError OT_API_REAL_NAME(otMdnsStopTxtResolver)(otInstance *aInstance, const otMdnsTxtResolver *aResolver);
extern otError OT_API_REAL_NAME(otMdnsUnregisterHost)(otInstance *aInstance, const otMdnsHost *aHost);
extern otError OT_API_REAL_NAME(otMdnsUnregisterKey)(otInstance *aInstance, const otMdnsKey *aKey);
extern otError OT_API_REAL_NAME(otMdnsUnregisterService)(otInstance *aInstance, const otMdnsService *aService);
extern otMdnsIterator *OT_API_REAL_NAME(otMdnsAllocateIterator)(otInstance *aInstance);
extern void            OT_API_REAL_NAME(otMdnsFreeIterator)(otInstance *aInstance, otMdnsIterator *aIterator);
extern void OT_API_REAL_NAME(otMdnsSetConflictCallback)(otInstance *aInstance, otMdnsConflictCallback aCallback);
extern void OT_API_REAL_NAME(otMdnsSetQuestionUnicastAllowed)(otInstance *aInstance, bool aAllow);

bool OT_API_WRAPPER_NAME(otMdnsIsEnabled)(otInstance *aInstance)
{
    sl_ot_rtos_acquire_stack_mutex();
    bool ret = OT_API_REAL_NAME(otMdnsIsEnabled)(aInstance);
    sl_ot_rtos_release_stack_mutex();
    return ret;
}

bool OT_API_WRAPPER_NAME(otMdnsIsQuestionUnicastAllowed)(otInstance *aInstance)
{
    sl_ot_rtos_acquire_stack_mutex();
    bool ret = OT_API_REAL_NAME(otMdnsIsQuestionUnicastAllowed)(aInstance);
    sl_ot_rtos_release_stack_mutex();
    return ret;
}

otError OT_API_WRAPPER_NAME(otMdnsGetNextBrowser)(otInstance      *aInstance,
                                                  otMdnsIterator  *aIterator,
                                                  otMdnsBrowser   *aBrowser,
                                                  otMdnsCacheInfo *aInfo)
{
    sl_ot_rtos_acquire_stack_mutex();
    otError ret = OT_API_REAL_NAME(otMdnsGetNextBrowser)(aInstance, aIterator, aBrowser, aInfo);
    sl_ot_rtos_release_stack_mutex();
    return ret;
}

otError OT_API_WRAPPER_NAME(otMdnsGetNextHost)(otInstance       *aInstance,
                                               otMdnsIterator   *aIterator,
                                               otMdnsHost       *aHost,
                                               otMdnsEntryState *aState)
{
    sl_ot_rtos_acquire_stack_mutex();
    otError ret = OT_API_REAL_NAME(otMdnsGetNextHost)(aInstance, aIterator, aHost, aState);
    sl_ot_rtos_release_stack_mutex();
    return ret;
}

otError OT_API_WRAPPER_NAME(otMdnsGetNextIp4AddressResolver)(otInstance            *aInstance,
                                                             otMdnsIterator        *aIterator,
                                                             otMdnsAddressResolver *aResolver,
                                                             otMdnsCacheInfo       *aInfo)
{
    sl_ot_rtos_acquire_stack_mutex();
    otError ret = OT_API_REAL_NAME(otMdnsGetNextIp4AddressResolver)(aInstance, aIterator, aResolver, aInfo);
    sl_ot_rtos_release_stack_mutex();
    return ret;
}

otError OT_API_WRAPPER_NAME(otMdnsGetNextIp6AddressResolver)(otInstance            *aInstance,
                                                             otMdnsIterator        *aIterator,
                                                             otMdnsAddressResolver *aResolver,
                                                             otMdnsCacheInfo       *aInfo)
{
    sl_ot_rtos_acquire_stack_mutex();
    otError ret = OT_API_REAL_NAME(otMdnsGetNextIp6AddressResolver)(aInstance, aIterator, aResolver, aInfo);
    sl_ot_rtos_release_stack_mutex();
    return ret;
}

otError OT_API_WRAPPER_NAME(otMdnsGetNextKey)(otInstance       *aInstance,
                                              otMdnsIterator   *aIterator,
                                              otMdnsKey        *aKey,
                                              otMdnsEntryState *aState)
{
    sl_ot_rtos_acquire_stack_mutex();
    otError ret = OT_API_REAL_NAME(otMdnsGetNextKey)(aInstance, aIterator, aKey, aState);
    sl_ot_rtos_release_stack_mutex();
    return ret;
}

otError OT_API_WRAPPER_NAME(otMdnsGetNextService)(otInstance       *aInstance,
                                                  otMdnsIterator   *aIterator,
                                                  otMdnsService    *aService,
                                                  otMdnsEntryState *aState)
{
    sl_ot_rtos_acquire_stack_mutex();
    otError ret = OT_API_REAL_NAME(otMdnsGetNextService)(aInstance, aIterator, aService, aState);
    sl_ot_rtos_release_stack_mutex();
    return ret;
}

otError OT_API_WRAPPER_NAME(otMdnsGetNextSrvResolver)(otInstance        *aInstance,
                                                      otMdnsIterator    *aIterator,
                                                      otMdnsSrvResolver *aResolver,
                                                      otMdnsCacheInfo   *aInfo)
{
    sl_ot_rtos_acquire_stack_mutex();
    otError ret = OT_API_REAL_NAME(otMdnsGetNextSrvResolver)(aInstance, aIterator, aResolver, aInfo);
    sl_ot_rtos_release_stack_mutex();
    return ret;
}

otError OT_API_WRAPPER_NAME(otMdnsGetNextTxtResolver)(otInstance        *aInstance,
                                                      otMdnsIterator    *aIterator,
                                                      otMdnsTxtResolver *aResolver,
                                                      otMdnsCacheInfo   *aInfo)
{
    sl_ot_rtos_acquire_stack_mutex();
    otError ret = OT_API_REAL_NAME(otMdnsGetNextTxtResolver)(aInstance, aIterator, aResolver, aInfo);
    sl_ot_rtos_release_stack_mutex();
    return ret;
}

otError OT_API_WRAPPER_NAME(otMdnsRegisterHost)(otInstance            *aInstance,
                                                const otMdnsHost      *aHost,
                                                otMdnsRequestId        aRequestId,
                                                otMdnsRegisterCallback aCallback)
{
    sl_ot_rtos_acquire_stack_mutex();
    otError ret = OT_API_REAL_NAME(otMdnsRegisterHost)(aInstance, aHost, aRequestId, aCallback);
    sl_ot_rtos_release_stack_mutex();
    return ret;
}

otError OT_API_WRAPPER_NAME(otMdnsRegisterKey)(otInstance            *aInstance,
                                               const otMdnsKey       *aKey,
                                               otMdnsRequestId        aRequestId,
                                               otMdnsRegisterCallback aCallback)
{
    sl_ot_rtos_acquire_stack_mutex();
    otError ret = OT_API_REAL_NAME(otMdnsRegisterKey)(aInstance, aKey, aRequestId, aCallback);
    sl_ot_rtos_release_stack_mutex();
    return ret;
}

otError OT_API_WRAPPER_NAME(otMdnsRegisterService)(otInstance            *aInstance,
                                                   const otMdnsService   *aService,
                                                   otMdnsRequestId        aRequestId,
                                                   otMdnsRegisterCallback aCallback)
{
    sl_ot_rtos_acquire_stack_mutex();
    otError ret = OT_API_REAL_NAME(otMdnsRegisterService)(aInstance, aService, aRequestId, aCallback);
    sl_ot_rtos_release_stack_mutex();
    return ret;
}

otError OT_API_WRAPPER_NAME(otMdnsSetEnabled)(otInstance *aInstance, bool aEnable, uint32_t aInfraIfIndex)
{
    sl_ot_rtos_acquire_stack_mutex();
    otError ret = OT_API_REAL_NAME(otMdnsSetEnabled)(aInstance, aEnable, aInfraIfIndex);
    sl_ot_rtos_release_stack_mutex();
    return ret;
}

otError OT_API_WRAPPER_NAME(otMdnsStartBrowser)(otInstance *aInstance, const otMdnsBrowser *aBrowser)
{
    sl_ot_rtos_acquire_stack_mutex();
    otError ret = OT_API_REAL_NAME(otMdnsStartBrowser)(aInstance, aBrowser);
    sl_ot_rtos_release_stack_mutex();
    return ret;
}

otError OT_API_WRAPPER_NAME(otMdnsStartIp4AddressResolver)(otInstance                  *aInstance,
                                                           const otMdnsAddressResolver *aResolver)
{
    sl_ot_rtos_acquire_stack_mutex();
    otError ret = OT_API_REAL_NAME(otMdnsStartIp4AddressResolver)(aInstance, aResolver);
    sl_ot_rtos_release_stack_mutex();
    return ret;
}

otError OT_API_WRAPPER_NAME(otMdnsStartIp6AddressResolver)(otInstance                  *aInstance,
                                                           const otMdnsAddressResolver *aResolver)
{
    sl_ot_rtos_acquire_stack_mutex();
    otError ret = OT_API_REAL_NAME(otMdnsStartIp6AddressResolver)(aInstance, aResolver);
    sl_ot_rtos_release_stack_mutex();
    return ret;
}

otError OT_API_WRAPPER_NAME(otMdnsStartSrvResolver)(otInstance *aInstance, const otMdnsSrvResolver *aResolver)
{
    sl_ot_rtos_acquire_stack_mutex();
    otError ret = OT_API_REAL_NAME(otMdnsStartSrvResolver)(aInstance, aResolver);
    sl_ot_rtos_release_stack_mutex();
    return ret;
}

otError OT_API_WRAPPER_NAME(otMdnsStartTxtResolver)(otInstance *aInstance, const otMdnsTxtResolver *aResolver)
{
    sl_ot_rtos_acquire_stack_mutex();
    otError ret = OT_API_REAL_NAME(otMdnsStartTxtResolver)(aInstance, aResolver);
    sl_ot_rtos_release_stack_mutex();
    return ret;
}

otError OT_API_WRAPPER_NAME(otMdnsStopBrowser)(otInstance *aInstance, const otMdnsBrowser *aBroswer)
{
    sl_ot_rtos_acquire_stack_mutex();
    otError ret = OT_API_REAL_NAME(otMdnsStopBrowser)(aInstance, aBroswer);
    sl_ot_rtos_release_stack_mutex();
    return ret;
}

otError OT_API_WRAPPER_NAME(otMdnsStopIp4AddressResolver)(otInstance *aInstance, const otMdnsAddressResolver *aResolver)
{
    sl_ot_rtos_acquire_stack_mutex();
    otError ret = OT_API_REAL_NAME(otMdnsStopIp4AddressResolver)(aInstance, aResolver);
    sl_ot_rtos_release_stack_mutex();
    return ret;
}

otError OT_API_WRAPPER_NAME(otMdnsStopIp6AddressResolver)(otInstance *aInstance, const otMdnsAddressResolver *aResolver)
{
    sl_ot_rtos_acquire_stack_mutex();
    otError ret = OT_API_REAL_NAME(otMdnsStopIp6AddressResolver)(aInstance, aResolver);
    sl_ot_rtos_release_stack_mutex();
    return ret;
}

otError OT_API_WRAPPER_NAME(otMdnsStopSrvResolver)(otInstance *aInstance, const otMdnsSrvResolver *aResolver)
{
    sl_ot_rtos_acquire_stack_mutex();
    otError ret = OT_API_REAL_NAME(otMdnsStopSrvResolver)(aInstance, aResolver);
    sl_ot_rtos_release_stack_mutex();
    return ret;
}

otError OT_API_WRAPPER_NAME(otMdnsStopTxtResolver)(otInstance *aInstance, const otMdnsTxtResolver *aResolver)
{
    sl_ot_rtos_acquire_stack_mutex();
    otError ret = OT_API_REAL_NAME(otMdnsStopTxtResolver)(aInstance, aResolver);
    sl_ot_rtos_release_stack_mutex();
    return ret;
}

otError OT_API_WRAPPER_NAME(otMdnsUnregisterHost)(otInstance *aInstance, const otMdnsHost *aHost)
{
    sl_ot_rtos_acquire_stack_mutex();
    otError ret = OT_API_REAL_NAME(otMdnsUnregisterHost)(aInstance, aHost);
    sl_ot_rtos_release_stack_mutex();
    return ret;
}

otError OT_API_WRAPPER_NAME(otMdnsUnregisterKey)(otInstance *aInstance, const otMdnsKey *aKey)
{
    sl_ot_rtos_acquire_stack_mutex();
    otError ret = OT_API_REAL_NAME(otMdnsUnregisterKey)(aInstance, aKey);
    sl_ot_rtos_release_stack_mutex();
    return ret;
}

otError OT_API_WRAPPER_NAME(otMdnsUnregisterService)(otInstance *aInstance, const otMdnsService *aService)
{
    sl_ot_rtos_acquire_stack_mutex();
    otError ret = OT_API_REAL_NAME(otMdnsUnregisterService)(aInstance, aService);
    sl_ot_rtos_release_stack_mutex();
    return ret;
}

otMdnsIterator *OT_API_WRAPPER_NAME(otMdnsAllocateIterator)(otInstance *aInstance)
{
    sl_ot_rtos_acquire_stack_mutex();
    otMdnsIterator *ret = OT_API_REAL_NAME(otMdnsAllocateIterator)(aInstance);
    sl_ot_rtos_release_stack_mutex();
    return ret;
}

void OT_API_WRAPPER_NAME(otMdnsFreeIterator)(otInstance *aInstance, otMdnsIterator *aIterator)
{
    sl_ot_rtos_acquire_stack_mutex();
    OT_API_REAL_NAME(otMdnsFreeIterator)(aInstance, aIterator);
    sl_ot_rtos_release_stack_mutex();
}

void OT_API_WRAPPER_NAME(otMdnsSetConflictCallback)(otInstance *aInstance, otMdnsConflictCallback aCallback)
{
    sl_ot_rtos_acquire_stack_mutex();
    OT_API_REAL_NAME(otMdnsSetConflictCallback)(aInstance, aCallback);
    sl_ot_rtos_release_stack_mutex();
}

void OT_API_WRAPPER_NAME(otMdnsSetQuestionUnicastAllowed)(otInstance *aInstance, bool aAllow)
{
    sl_ot_rtos_acquire_stack_mutex();
    OT_API_REAL_NAME(otMdnsSetQuestionUnicastAllowed)(aInstance, aAllow);
    sl_ot_rtos_release_stack_mutex();
}
