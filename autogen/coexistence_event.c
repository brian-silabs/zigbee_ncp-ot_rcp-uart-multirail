/***************************************************************************//**
 * @file
 * @brief
 *******************************************************************************
 * # License
 * <b>Copyright 2021 Silicon Laboratories Inc. www.silabs.com</b>
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

#include "coexistence.h"
#include "coexistence-802154.h"
#include "coexistence-ot.h"

void COEX_on_event(COEX_Events_t events)
{
  if ((sli_rail_util_ieee802154_coex_event_filter & events) != 0U) {
    sli_rail_util_ieee802154_coex_on_event(sli_rail_util_ieee802154_coex_event_filter & events);
  }
  if ((sli_rail_util_ot_coex_state_event_filter & events) != 0U) {
    sli_rail_util_ot_coex_state_on_event(sli_rail_util_ot_coex_state_event_filter & events);
  }
}
