/***************************************************************************//**
 * @file
 * @brief
 *******************************************************************************
 * # License
 * <b>Copyright 2019 Silicon Laboratories Inc. www.silabs.com</b>
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

#ifndef LOWER_MAC_H
#define LOWER_MAC_H

#include "mac-phy.h"
#include "multi-mac.h"
#include "mac-multi-network.h"
#include "sl_status.h"
#include "lower-mac-common.h"

//------------------------------------------------------------------------------
// Merged from both zigbee/flex:

#ifdef DOXYGEN_SHOULD_SKIP_THIS
enum LowerMacState
#else
typedef uint8_t LowerMacState;
enum
#endif
{
  // Common states
  SL_802154_STATE_IDLE,
  SL_802154_STATE_EXPECTING_DATA,
  SL_802154_STATE_TX,   // also pro2plus driver
  SL_802154_STATE_TX_ACK_COMPLETE,

  // These apply to the pro2 driver and the RAIL driver
  SL_802154_STATE_BUSY, // also scripted tests
  SL_802154_STATE_TX_NO_ACK,
  SL_802154_STATE_TX_WAITING_FOR_ACK,

  // These states are specific to the pro2 driver
  SL_802154_STATE_SENDING_ACK,
  SL_802154_STATE_CCA_FAILED,
  SL_802154_STATE_BACKOFF,

  // These states are specific to RAIL
  SL_802154_STATE_RADIO_INIT,

#ifdef CSL_SUPPORT
  // These states are specific to the CSL feature within the lower mac
  SL_802154_STATE_WUF_RX, // a wake up frame has been received and we have scheduled an RX
#endif // CSL_SUPPORT
};

extern LowerMacState sli_802154mac_lower_mac_state;
#ifdef HIGH_DATARATE_PHY
#define PHY_HEADER_SIZE_ADJUST_2MBPS    4u
#define HIGH_DATARATE_PHY_PACKET_START_INDEX  1u
// 802.15.4 2-byte PHR
// Spec: [       0     |    1-2   |     3    |     4     |     5-15     ]
//       [ Mode Switch | Reserved | FCS Type | Whitening | Frame Length ]
// RBIT: [      15     |   14-13  |    12    |    11     |     10-0     ]
#define PHR2BYTE_REV_LENGTH_MASK (0x07FFu) // <10:0> 11-bit length field
#define PHR2BYTE_REV_WHITEN_MASK (0x0800u) // <11> 0=unwhitened, 1=whitened
#define PHR2BYTE_REV_CRC_2_MASK  (0x1000u) // <12> 0=4-byte CRC, 1=2-byte CRC
#endif //HIGH_DATARATE_PHY
// MAC TX Options Bitmask
#ifdef DOXYGEN_SHOULD_SKIP_THIS
enum sl_mac_tx_options_bitmask_t
#else
typedef uint8_t sl_mac_tx_options_bitmask_t;
enum
#endif
{
  SL_802154_USE_NO_TX_OPTION        = 0x00, // 00000000
  SL_802154_USE_CSMA                = 0x01, // 00000001
  SL_802154_USE_WAKEUP_FRAMES       = 0x02, // 00000010
  SL_802154_USE_HIGH_DATARATE_PHY   = 0x04, // 00000100
};

bool sli_mac_lower_mac_is_idle(uint8_t mac_index);
void sli_mac_lower_mac_set_idle(uint8_t mac_index);
#ifdef CSL_SUPPORT
bool sli_mac_lower_mac_rx_wakeup_frame(uint8_t mac_index);
#endif // CSL_SUPPORT

void sli_mac_lower_mac_send(uint8_t mac_index, uint8_t *packet, sl_mac_tx_options_bitmask_t tx_options);
void sli_mac_packet_send_complete_callback(uint8_t mac_index, sl_status_t status);

sl_status_t sli_mac_receive_callback(uint8_t mac_index, sli_zigbee_packet_header_t rawPacket);

void sli_mac_lower_mac_tick(void);
void sli_mac_lower_mac_init(uint8_t mac_index, RadioPowerMode mode);
sl_status_t sli_mac_lower_mac_set_radio_channel(uint8_t mac_index, uint8_t channel);

sl_status_t sli_mac_lower_mac_set_radio_idle_mode(uint8_t mac_index, RadioPowerMode mode);
RadioPowerMode sli_mac_lower_mac_get_radio_idle_mode(uint8_t mac_index);

void sli_mac_purge_incoming_queue(uint8_t mac_index);
bool sli_mac_lower_mac_is_expecting_data(void);
bool sli_mac_lower_mac_radio_is_on(uint8_t mac_index);
void sli_mac_lower_mac_update_active_radio_config(void);

// Symbol timer APIs.
sl_status_t sli_mac_lower_mac_schedule_symbol_timer(uint8_t mac_index, uint16_t symbols);
void sli_mac_lower_mac_cancel_symbol_timer(uint8_t mac_index);

// This handler is invoked when the symbol timer expires.
void sli_mac_symbol_timer_expired_handler_isr(uint8_t mac_index);

//mfglib requirement
bool sli_mac_lower_mac_get_check_cca(uint8_t mac_index);

void sli_mac_lower_mac_disable_check_cca(uint8_t mac_index);

void sli_mac_lower_mac_enable_check_cca(uint8_t mac_index);

void sli_mac_lower_mac_start_transmit_stream(uint8_t mac_index);

void sli_mac_lower_mac_stop_transmit_stream(uint8_t mac_index);

void sli_mac_lower_mac_start_transmit_tone(uint8_t mac_index);

void sli_mac_lower_mac_stop_transmit_tone(uint8_t mac_index);

//zigbee specific, and only needed for mac certification
uint8_t sli_mac_lower_mac_convert_rssi_to_ed(uint8_t mac_index, int8_t rssi);

bool sli_802154phy_radio_packet_trace_enabled(void);

// This function will handle radio state for force sleep/wakeup calls
// to the device when component zigbee_force_sleep_and_wakeup is enabled
// sleep is TRUE for force-sleep and FALSE to undo force-sleep
void sli_mac_stack_lower_mac_force_sleep(bool sleep);

//------------------------------------------------------------------------------
// zigbee only:

#define MAC_MAX_ACKD_RETRIES_DEFAULT (3)
#define TRANSMIT_BUFFER_SIZE 126

//------------------------------------------------------------------------------
// flex only:

// CSMA-CA default parameters
#define SL_802154_CSMA_ENABLE_DEFAULT                       1
#define SL_802154_MAX_CSMA_BACKOFF_DEFAULT                  4
#define SL_802154_BACKOFF_EXPONENT_MIN_DEFAULT              3
#define SL_802154_BACKOFF_EXPONENT_MAX_DEFAULT              5

#define DEFAULT_MAC_MAX_RETRIES                             3

#define FORCE_TX_AFTER_FAILED_CCA_ATTEMPTS_LIMIT            3

// The number of symbols forming the basic time period used by the CSMA-CA
// algorithm.
#define SL_802154_UNIT_BACKOFF_PERIOD_SYMBOLS               20

// TODO: read the spec and set the proper DATA timeout
#define SL_802154_DATA_REQUEST_TIMEOUT_MS                   100

// macSIFSPeriod is 12 symbols for all non-UWB PHYs
#define SL_802154_ACK_TURNAROUND_DELAY_SYMBOLS              12

// Defines for the scheduler to estimate packet time on air
// (stolen from platform/base/phy/rail/phy.c)
//@TODO: This should be re-evaluated at some point, but for now this will help
// the scheduler make better choices
#define CSMA_OVERHEAD_US                                    1000

#define RADIO_SCHEDULER_BACKGROUND_RX_DEFAULT_PRIORITY      255
#define RADIO_SCHEDULER_ACTIVE_RX_DEFAULT_PRIORITY          255
#define RADIO_SCHEDULER_TX_DEFAULT_PRIORITY                 100

#define SL_ZIGBEE_APPENDED_INFO_FLAG_ACK_FRAME_PENDING_SET      0x01
// Appended info defines
#ifdef MAC_TEST_STACK
#define SL_ZIGBEE_APPENDED_INFO_RSSI_OFFSET                     0
#define SL_ZIGBEE_APPENDED_INFO_RSSI_LENGTH                     1
#define SL_ZIGBEE_APPENDED_INFO_SYNC_TIME_OFFSET                1
#define SL_ZIGBEE_APPENDED_INFO_SYNC_TIME_LENGTH                4
#define SL_ZIGBEE_APPENDED_INFO_FLAGS_OFFSET                    5
#define SL_ZIGBEE_APPENDED_INFO_FLAGS_LENGTH                    1
#define SL_ZIGBEE_APPENDED_INFO_TOTAL_LENGTH  \
  (SL_ZIGBEE_APPENDED_INFO_RSSI_LENGTH        \
   + SL_ZIGBEE_APPENDED_INFO_SYNC_TIME_LENGTH \
   + SL_ZIGBEE_APPENDED_INFO_FLAGS_LENGTH)
#else
  #ifdef ZIGBEE_STACK_ON_HOST
  #define SL_ZIGBEE_APPENED_INFO_SYNC_TIMESTAMP_LENGTH 8
  #else
  #define SL_ZIGBEE_APPENED_INFO_SYNC_TIMESTAMP_LENGTH 0
  #endif
  #define SL_ZIGBEE_APPENDED_INFO_TOTAL_LENGTH (8 + SL_ZIGBEE_APPENED_INFO_SYNC_TIMESTAMP_LENGTH)
  #define APPENDED_INFO_FRAME_STATUS_BYTE_1_INDEX 0 // MSByte
  #define APPENDED_INFO_FRAME_STATUS_BYTE_0_INDEX 1 // LSByte
  #define APPENDED_INFO_RSSI_BYTE_INDEX           2
  #define APPENDED_INFO_LQI_BYTE_INDEX            3
  #define APPENDED_INFO_GAIN_BYTE_INDEX           4
  #define APPENDED_INFO_MAC_TIMER_BYTE_2_INDEX    5 // MSByte
  #define APPENDED_INFO_MAC_TIMER_BYTE_1_INDEX    6
  #define APPENDED_INFO_MAC_TIMER_BYTE_0_INDEX    7 // LSByte
  #define APPENDED_INFO_SYNC_RX_TIME_BYTE_7_INDEX 8
  #define APPENDED_INFO_SYNC_RX_TIME_BYTE_6_INDEX 9
  #define APPENDED_INFO_SYNC_RX_TIME_BYTE_5_INDEX 10
  #define APPENDED_INFO_SYNC_RX_TIME_BYTE_4_INDEX 11
  #define APPENDED_INFO_SYNC_RX_TIME_BYTE_3_INDEX 12
  #define APPENDED_INFO_SYNC_RX_TIME_BYTE_2_INDEX 13
  #define APPENDED_INFO_SYNC_RX_TIME_BYTE_1_INDEX 14
  #define APPENDED_INFO_SYNC_RX_TIME_BYTE_0_INDEX 15

#define APPENDED_INFO_CHANNEL_OVERWRITE_BYTE_INDEX 0
// Multi-network: we overwrite the second byte of the frame status with the
// network index. This will make the stack aware at higher levels of the network
// on which the packet was received.
#define APPENDED_INFO_NETWORK_OVERWRITE_BYTE_INDEX 1
#define APPENDED_INFO_NETWORK_OVERWRITE_NET_ID_MASK 0x0F
#define APPENDED_INFO_NETWORK_OVERWRITE_NET_ID_SHIFT 0
#define APPENDED_INFO_NETWORK_OVERWRITE_PHY_ID_MASK 0xF0
#define APPENDED_INFO_NETWORK_OVERWRITE_PHY_ID_SHIFT 4

#endif

extern uint8_t emberMacAckTimeoutMS;
extern int8_t emRadioCcaThreshold;

//------------------------------------------------------------------------------
// Flex: Internal API prototypes

bool sli_mac_incoming_pending(uint8_t mac_index);
bool sli_mac_activity_pending(void);

void sli_mac_timer_isr(void);

void sli_mac_stack_set_csma_params(sl_mac_csma_parameters_t *csmaParams);
void sli_mac_stack_get_csma_params(sl_mac_csma_parameters_t *csmaParams);

// Returns the current packet RSSI.
// This API should be called only in the context of processing an incoming
// packet.
int8_t sli_mac_get_current_packet_rssi(void);

// This API looks at the appended info of the current incoming packet and
// returns the elapsed time in microseconds since the sync word was received.
// This API should be called only in the context of processing an incoming
// packet.
uint32_t sli_mac_get_current_packet_sync_word_detection_elapsed_time_us(void);

// Returns the current packet appended flags.
// This API should be called only in the context of processing an incoming
// packet.
uint8_t sli_mac_get_current_packet_appended_flags(void);

void sli_mac_set_aux_address_filtering(sl_802154_short_addr_t nodeId, uint8_t index);

// nwk radio address params
void sli_mac_lower_mac_set_node_id(uint8_t mac_index, uint8_t addr_filter_index, sl_802154_short_addr_t nodeId);
void sli_mac_lower_mac_set_pan_id(uint8_t mac_index, uint8_t addr_filter_index, sl_802154_pan_id_t panId);
void sli_mac_lower_mac_set_eui64(uint8_t mac_index, uint8_t addr_filter_index, sl_802154_long_addr_t eui64);

// Radio/PHY related APIs.
sl_status_t sli_mac_lower_mac_set_radio_power(uint8_t mac_index, int8_t power);
int8_t sli_mac_lower_mac_get_radio_power(uint8_t mac_index);
uint8_t sli_mac_lower_mac_get_radio_channel(uint8_t mac_index);
void sli_mac_radio_ok_to_idle(void);
void sli_mac_set_coordinator(bool isCoordinator);
void sli_mac_stack_set_cca_threshold(int8_t threshold);
int8_t sli_mac_stack_get_ed_cca_threshold(void);
uint16_t sli_mac_get_symbol_duration_us(void);
uint16_t sli_mac_get_bit_duration_us(void);
int8_t sli_mac_radio_energy_detection(uint8_t mac_index);
void sli_mac_stack_calibrate_current_channel(void);
void sli_mac_lower_mac_radio_sleep(void);
void sli_mac_lower_mac_radio_wakeup(void);
uint32_t sli_mac_get_mac_timer(void);
bool sli_mac_lower_mac_channel_is_valid(uint8_t mac_index, uint8_t mac_page_chan);
void sli_mac_lower_mac_force_idle(uint8_t mac_index);

//------------------------------------------------------------------------------
// New APIs created after the zigbee/flex merge

sl_status_t sli_mac_set_cca_mode(uint8_t ccaMode);

// CSL related structs and APIs
typedef struct {
  uint16_t frame_type : 3;
  uint16_t long_frame_control : 1;
  uint16_t dest_addr_mode : 2;
  uint16_t src_addr_mode : 2;
  uint16_t pan_id_present : 1;
  uint16_t security_enabled : 1;
  uint16_t seq_num_suppression : 1;
  uint16_t frame_pending : 1;
  uint16_t frame_version : 2;
  uint16_t ack_request : 1;
  uint16_t ie_present : 1;
} sl_mac_long_frame_control_t;

typedef struct {
  uint16_t length : 7;
  uint16_t element_id : 8;
  uint16_t type : 1;
} sl_mac_header_ie_t;

typedef struct {
  uint16_t rendezvous_time;
  uint16_t wakeup_interval;
} sl_mac_rendezvous_ie_t;

sl_status_t sli_mac_set_mac_csl_max_period(uint8_t mac_index, uint16_t mac_csl_max_period_ms);
uint16_t sli_mac_get_mac_csl_max_period(uint8_t mac_index);
sl_status_t sli_mac_set_mac_csl_period(uint8_t mac_index, uint16_t mac_csl_period_ms);
uint16_t sli_mac_get_mac_csl_period(uint8_t mac_index);
sl_status_t sli_mac_set_mac_csl_channel_sample(uint8_t mac_index, uint16_t mac_csl_channel_sample_ms);
uint16_t sli_mac_get_mac_csl_channel_sample(uint8_t mac_index);
void sli_mac_get_eui64(sl_802154_long_addr_t eui64);
// 802.15.4 software filtering APIs (see lower-mac-802.15.4-filtering.c)

// Return true if the packet is accepted, false if the packet is filtered.
bool sli_mac_802154_filter(uint8_t *packet);

#define RADIO_CCA_ATTEMPT_MAX_DEFAULT      5 // 1 + macMaxCSMAAttempts' retries
#define RADIO_BACKOFF_EXPONENT_MIN_DEFAULT 3
#define RADIO_BACKOFF_EXPONENT_MAX_DEFAULT 5
#define RADIO_MINIMUM_BACKOFF_DEFAULT      0
#ifndef MAC_TEST_STACK // Causes a warning on Connect
//workraound
//#undef  MAX_RADIO_POWER
//#define MAX_RADIO_POWER 3
#endif

#define sli_mac_inactivate_event(x) sli_zigbee_event_set_inactive(&(x))
#define sli_mac_activate_event(x) sli_zigbee_event_set_active(&(x))
#define sli_mac_set_event_delay_ms(x, y) sli_zigbee_event_set_delay_ms(&(x), y)
#define sli_mac_event_is_active(x) sli_zigbee_event_is_scheduled(&(x))

#ifdef SL_COMPONENT_CATALOG_PRESENT
#include "sl_component_catalog.h"
#endif

#ifdef RAIL_MUX // from jam
#define SL_CATALOG_RAIL_MULTIPLEXER_PRESENT 1
#endif

#ifdef SL_CATALOG_RAIL_MULTIPLEXER_PRESENT
sl_status_t sli_lower_mac_lock_radio (void);
sl_status_t sli_lower_mac_unlock_radio (void);
#else
#define sli_lower_mac_lock_radio() SL_STATUS_OK
#define sli_lower_mac_unlock_radio() SL_STATUS_OK
#endif //SL_CATALOG_RAIL_MULTIPLEXER_PRESENT

#endif //LOWER_MAC_H
