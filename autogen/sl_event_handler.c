#include "sl_event_handler.h"

#include "sl_rail_mux.h"
#include "sl_board_init.h"
#include "sl_clock_manager.h"
#include "sl_hfxo_manager.h"
#include "coexistence-802154.h"
#include "sl_rail_util_dma.h"
#include "pa_conversions_efr32.h"
#include "sl_rail_util_power_manager_init.h"
#include "sl_rail_util_pti.h"
#include "sl_rail_util_rssi.h"
#include "sl_zigbee_system_common.h"
#include "gp-types.h"
#include "sl_event_system.h"
#include "btl_interface.h"
#include "sl_board_control.h"
#include "platform-efr32.h"
#include "sl_cpc.h"
#include "sl_debug_swo.h"
#include "sl_gpio.h"
#include "gpiointerrupt.h"
#include "sl_iostream_debug.h"
#include "sl_mbedtls.h"
#include "sl_ot_rtos_adaptation.h"
#include "psa/crypto.h"
#include "sl_se_manager.h"
#include "sli_protocol_crypto.h"
#include "sl_iostream_init_instances.h"
#include "cmsis_os2.h"
#include "sl_token_manager_api.h"
#include "nvm3_default.h"
#include "sl_cos.h"
#include "sl_cpc_config_vcom.h"
#include "sl_iostream_handles.h"

void sli_driver_permanent_allocation(void)
{
}

void sli_service_permanent_allocation(void)
{
  sl_cpc_init_permanent_allocations();
}

void sli_stack_permanent_allocation(void)
{
  sli_zigbee_stack_rtos_perm_allocation();
  sli_legacy_buffer_manager_initialize_buffers();
  sli_zigbee_app_framework_rtos_perm_allocation();
  sl_ot_rtos_perm_allocation();
}

void sli_internal_permanent_allocation(void)
{
}

void sl_platform_init(void)
{
  sli_rail_mux_local_init();
  sl_board_preinit();
  sl_clock_manager_runtime_init();
  sl_hfxo_manager_init_hardware();
  sl_board_init();
  sl_event_system_init();
  bootloader_init();
  nvm3_initDefault();
}

void sli_internal_init_early(void)
{
}

void sl_kernel_start(void)
{
  osKernelStart();
}

void sl_driver_init(void)
{
  sl_debug_swo_init();
  sl_gpio_init();
  GPIOINT_Init();
  sl_cos_send_config();
  sl_cpc_config_vcom();
}

void sl_service_init(void)
{
  sl_board_configure_vcom();
  sl_hfxo_manager_init();
  sl_cpc_init();
  sl_mbedtls_init();
  psa_crypto_init();
  sl_se_init();
  sli_protocol_crypto_init();
  sli_aes_seed_mask();
  sl_iostream_init_instances_stage_1();
  sl_iostream_init_instances_stage_2();
  sl_token_manager_init();
}

void sl_stack_init(void)
{
  sl_rail_util_coex_init();
  sl_rail_util_dma_init();
  sl_rail_util_pa_init();
  sl_rail_util_power_manager_init();
  sl_rail_util_pti_init();
  sl_rail_util_rssi_init();
  sli_zigbee_stack_rtos_task_init_cb();
  sli_zigbee_stack_sleep_init();
  sli_zigbee_app_framework_rtos_task_init_cb();
  sli_zigbee_app_framework_sleep_init();
  sli_zigbee_gp_init_tokens();
  sl_ot_sys_init();
}

void sl_internal_app_init(void)
{
  sl_ot_rtos_stack_init();
  sl_ot_rtos_app_init();
}

void sl_iostream_init_instances_stage_1(void)
{
  sl_iostream_debug_init();
}

void sl_iostream_init_instances_stage_2(void)
{
  sl_iostream_set_console_instance();
}

