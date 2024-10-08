/***************************************************************************//**
 * @file
 * @brief Data store and fetch routines.
 * See @ref byte-utilities for documentation.
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

#ifndef SILABS_BYTE_UTILITIES_H
#define SILABS_BYTE_UTILITIES_H

#include "stack/include/sl_zigbee_types.h"

/**
 * @addtogroup stack_info
 *
 * See byte-utilities.h for source code.
 * @{
 */

#ifndef ZNET_HEADER_SCRIPT
/** @brief Copy an array of bytes and reverses the order
 *  before writing the data to the destination.
 *
 * @param dest A pointer to the location where the data will be copied to.
 * @param src A pointer to the location where the data will be copied from.
 * @param length The length (in bytes) of the data to be copied.
 */
void sl_util_reverse_mem_copy(uint8_t* dest,
                              const uint8_t* src,
                              uint16_t length);

/** @brief Return the value built from the two \c uint8_t values
 *  \c contents[0] and \c contents[1]. \c contents[0] is the low byte.
 */
uint16_t sl_util_fetch_low_high_int16u(const uint8_t *contents);

/** @brief Return the value built from the two \c uint8_t values
 *  \c contents[0] and \c contents[1]. \c contents[0] is the high byte.
 */
uint16_t sl_util_fetch_high_low_int16u(const uint8_t *contents);

/** @brief Store \c value in \c contents[0] and \c contents[1]. \c
 *  contents[0] is the low byte.
 */
void sl_util_store_low_high_int16u(uint8_t *contents,
                                   uint16_t value);

/** @brief Store \c value in \c contents[0] and \c contents[1]. \c
 *  contents[0] is the high byte.
 */
void sl_util_store_high_low_int16u(uint8_t *contents,
                                   uint16_t value);

#if !defined DOXYGEN_SHOULD_SKIP_THIS
uint32_t sli_util_fetch_int32u(bool lowHigh, const uint8_t* contents);
#endif

/** @brief Return the value built from the four \c uint8_t values
 *  \c contents[0], \c contents[1], \c contents[2] and \c contents[3]. \c
 *  contents[0] is the low byte.
 */
#if defined DOXYGEN_SHOULD_SKIP_THIS
uint32_t sl_util_fetch_low_high_int32u(const uint8_t *contents);
#else
#define sl_util_fetch_low_high_int32u(contents) \
  (sli_util_fetch_int32u(true, contents))
#endif

/** @description Return the value built from the four \c uint8_t values
 *  \c contents[0], \c contents[1], \c contents[2] and \c contents[3]. \c
 *  contents[3] is the low byte.
 */
#if defined DOXYGEN_SHOULD_SKIP_THIS
uint32_t sl_util_fetch_high_low_int32u(const uint8_t *contents);
#else
#define sl_util_fetch_high_low_int32u(contents) \
  (sli_util_fetch_int32u(false, contents))
#endif

#if !defined DOXYGEN_SHOULD_SKIP_THIS
void sli_util_store_int32u(bool lowHigh, uint8_t* contents, uint32_t value);
#endif

/** @brief Store \c value in \c contents[0], \c contents[1], \c
 *  contents[2] and \c contents[3]. \c contents[0] is the low byte.
 */
#if defined DOXYGEN_SHOULD_SKIP_THIS
void sl_util_store_low_high_int32u(uint8_t *contents, uint32_t value);
#else
#define sl_util_store_low_high_int32u(contents, value) \
  (sli_util_store_int32u(true, contents, value))
#endif

/** @description Store \c value in \c contents[0], \c contents[1], \c
 *  contents[2] and \c contents[3]. \c contents[3] is the low byte.
 */
#if defined DOXYGEN_SHOULD_SKIP_THIS
void sl_util_store_high_low_int32u(uint8_t *contents, uint32_t value);
#else
#define sl_util_store_high_low_int32u(contents, value) \
  (sli_util_store_int32u(false, contents, value))
#endif

#endif // ZNET_HEADER_SCRIPT

/** @} END addtogroup */

#endif // SILABS_BYTE_UTILITIES_H
