#include "sl_event_handler.h"

#include "em_chip.h"
#include "sl_rail_mux.h"
#include "sl_interrupt_manager.h"
#include "sl_board_init.h"
#include "multirail-demo.h"
#include "sl_clock_manager_init.h"
#include "sl_device_init_dcdc.h"
#include "sl_clock_manager.h"
#include "sl_hfxo_manager.h"
#include "SEGGER_RTT.h"
#include "coexistence-802154.h"
#include "sl_rail_util_dma.h"
#include "pa_conversions_efr32.h"
#include "sl_rail_util_power_manager_init.h"
#include "sl_rail_util_pti.h"
#include "sl_rail_util_rssi.h"
#include "sl_zigbee_system_common.h"
#include "sl_event_system.h"
#include "btl_interface.h"
#include "sl_board_control.h"
#include "platform-efr32.h"
#include "sl_sleeptimer.h"
#include "sl_cpc.h"
#include "sl_mpu.h"
#include "sl_debug_swo.h"
#include "gpiointerrupt.h"
#include "sl_iostream_debug.h"
#include "hal.h"
#include "sl_mbedtls.h"
#include "nvm3_default.h"
#include "sl_ot_rtos_adaptation.h"
#include "psa/crypto.h"
#include "sli_protocol_crypto.h"
#include "cmsis_os2.h"
#include "sl_iostream_init_instances.h"
#include "sl_power_manager.h"
#include "sl_cos.h"

void sl_platform_init(void)
{
  CHIP_Init();
  sli_rail_mux_local_init();
  sl_interrupt_manager_init();
  sl_board_preinit();
  sl_clock_manager_init();
  sl_device_init_dcdc();
  sl_clock_manager_runtime_init();
  sl_hfxo_manager_init_hardware();
  SEGGER_RTT_Init();
  sl_board_init();
  sl_event_system_init();
  bootloader_init();
  halInit();
  nvm3_initDefault();
  osKernelInitialize();
  sl_power_manager_init();
}

void sl_kernel_start(void)
{
  osKernelStart();
}

void sl_driver_init(void)
{
  sl_debug_swo_init();
  GPIOINT_Init();
  sl_cos_send_config();
}

void sl_service_init(void)
{
  sl_board_configure_vcom();
  sl_sleeptimer_init();
  sl_hfxo_manager_init();
  sl_cpc_init();
  sl_mpu_disable_execute_from_ram();
  sl_mbedtls_init();
  psa_crypto_init();
  sli_aes_seed_mask();
  sl_iostream_init_instances();
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
  sl_ot_sys_init();
}

void sl_internal_app_init(void)
{
  sl_zigbee_multirail_gp_tx_queue_init();
  sl_ot_rtos_stack_init();
  sl_ot_rtos_app_init();
}

void sl_iostream_init_instances(void)
{
  sl_iostream_debug_init();
}

