################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../gecko_sdk_4.4.3/platform/emdrv/gpiointerrupt/src/gpiointerrupt.c 

OBJS += \
./gecko_sdk_4.4.3/platform/emdrv/gpiointerrupt/src/gpiointerrupt.o 

C_DEPS += \
./gecko_sdk_4.4.3/platform/emdrv/gpiointerrupt/src/gpiointerrupt.d 


# Each subdirectory must supply rules for building sources it contributes
gecko_sdk_4.4.3/platform/emdrv/gpiointerrupt/src/gpiointerrupt.o: ../gecko_sdk_4.4.3/platform/emdrv/gpiointerrupt/src/gpiointerrupt.c gecko_sdk_4.4.3/platform/emdrv/gpiointerrupt/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m33 -mthumb -std=c99 '-DEMBER_CUSTOM_MAC_FILTER_TABLE_SIZE=15' '-DEFR32MG24B210F1536IM48=1' '-DSL_APP_PROPERTIES=1' '-DSL_BOARD_NAME="BRD4186C"' '-DSL_BOARD_REV="A01"' '-DHARDWARE_BOARD_DEFAULT_RF_BAND_2400=1' '-DHARDWARE_BOARD_SUPPORTS_1_RF_BAND=1' '-DHARDWARE_BOARD_SUPPORTS_RF_BAND_2400=1' '-DHFXO_FREQ=39000000' '-DconfigNUM_SDK_THREAD_LOCAL_STORAGE_POINTERS=2' '-DSL_COMPONENT_CATALOG_PRESENT=1' '-DCORTEXM3=1' '-DCORTEXM3_EFM32_MICRO=1' '-DCORTEXM3_EFR32=1' '-DPHY_RAIL=1' '-DPLATFORM_HEADER="platform-header.h"' '-DSL_LEGACY_HAL_ENABLE_WATCHDOG=1' '-DMBEDTLS_CONFIG_FILE=<sl_mbedtls_config.h>' '-DOPENTHREAD_CONFIG_ENABLE_BUILTIN_MBEDTLS=0' '-DOPENTHREAD_CONFIG_NCP_CPC_ENABLE=1' '-DOPENTHREAD_CONFIG_NCP_CPC_TX_CHUNK_SIZE=2048' '-DOPENTHREAD_CONFIG_NCP_HDLC_ENABLE=0' '-DSPINEL_PLATFORM_HEADER="spinel_platform.h"' '-D_GNU_SOURCE=1' '-DOPENTHREAD_ENABLE_NCP_VENDOR_HOOK=1' '-DOPENTHREAD_CONFIG_PLATFORM_RADIO_COEX_ENABLE=1' '-DRADIO_CONFIG_DMP_SUPPORT=1' '-DSL_OPENTHREAD_PHY_SELECT_STACK_SUPPORT=1' '-DOPENTHREAD_CORE_CONFIG_PLATFORM_CHECK_FILE="openthread-core-efr32-config-check.h"' '-DOPENTHREAD_PROJECT_CORE_CONFIG_FILE="openthread-core-efr32-config.h"' '-DOPENTHREAD_CONFIG_LOG_OUTPUT=OPENTHREAD_CONFIG_LOG_OUTPUT_PLATFORM_DEFINED' '-DOPENTHREAD_CONFIG_FILE="sl_openthread_generic_config.h"' '-DOPENTHREAD_CONFIG_PLATFORM_KEY_REFERENCES_ENABLE=0' '-DOPENTHREAD_RADIO=1' '-DOPENTHREAD_SPINEL_CONFIG_OPENTHREAD_MESSAGE_ENABLE=0' '-DSL_OPENTHREAD_STACK_FEATURES_CONFIG_FILE="sl_openthread_features_config.h"' '-DMBEDTLS_PSA_CRYPTO_CONFIG_FILE=<psa_crypto_config.h>' '-DSL_RAIL_LIB_MULTIPROTOCOL_SUPPORT=1' '-DSL_RAIL_UTIL_PA_CONFIG_HEADER=<sl_rail_util_pa_config.h>' '-DRTT_USE_ASM=0' '-DSEGGER_RTT_SECTION="SEGGER_RTT"' '-DSLI_RADIOAES_REQUIRES_MASKING=1' '-DCUSTOM_TOKEN_HEADER="sl_token_manager_af_token_header.h"' '-DUSE_NVM3=1' '-DUC_BUILD=1' '-DEZSP_CPC=1' '-DEMBER_AF_NCP=1' '-DEMBER_MULTI_NETWORK_STRIPPED=1' '-DSL_ZIGBEE_PHY_SELECT_STACK_SUPPORT=1' '-DSL_ZIGBEE_STACK_COMPLIANCE_REVISION=22' -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/config" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/autogen" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/platform/Device/SiliconLabs/EFR32MG24/Include" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/platform/common/inc" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/hardware/board/inc" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/platform/bootloader" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/platform/bootloader/api" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/platform/CMSIS/Core/Include" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/platform/CMSIS/RTOS2/Include" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/hardware/driver/configuration_over_swo/inc" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/platform/service/cpc/inc" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/platform/driver/debug/inc" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/platform/service/device_init/inc" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/platform/emdrv/dmadrv/inc" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/platform/emdrv/common/inc" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/platform/emlib/inc" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/platform/emdrv/gpiointerrupt/inc" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/platform/service/hfxo_manager/inc" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/platform/service/iostream/inc" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/platform/service/legacy_hal/inc" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/platform/service/legacy_hal_wdog/inc" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/platform/security/sl_component/sl_mbedtls_support/config" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/platform/security/sl_component/sl_mbedtls_support/inc" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/util/third_party/mbedtls/include" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/util/third_party/mbedtls/library" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/platform/service/mem_pool/inc" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/platform/micrium_os/common/source" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/platform/micrium_os/common/include" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/platform/micrium_os/cpu/include" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/platform/micrium_os/ports/source" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/platform/micrium_os" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/platform/micrium_os/kernel/source" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/platform/micrium_os/kernel/include" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/platform/service/mpu/inc" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/hardware/driver/mx25_flash_shutdown/inc/sl_mx25_flash_shutdown_usart" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/platform/emdrv/nvm3/inc" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/protocol/openthread/include" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/protocol/openthread/platform-abstraction/ncp" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/util/third_party/openthread/include" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/util/third_party/openthread/include/openthread" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/util/third_party/openthread/src/core" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/util/third_party/openthread/src/lib" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/util/third_party/openthread/third_party/tcplp" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/util/third_party/openthread/src" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/util/third_party/openthread/src/ncp" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/util/third_party/openthread/src/lib/spinel" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/util/third_party/openthread/src/lib/hdlc" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/protocol/openthread/platform-abstraction/include" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/protocol/openthread/platform-abstraction/rtos" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/util/third_party/openthread/examples/platforms" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/util/third_party/openthread/examples/platforms/utils" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/protocol/openthread/platform-abstraction/efr32" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/platform/peripheral/inc" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/platform/service/power_manager/inc" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/util/third_party/printf" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/util/third_party/printf/inc" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/platform/security/sl_component/sl_psa_driver/inc" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/platform/radio/rail_lib/common" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/platform/radio/rail_lib/protocol/ble" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/platform/radio/rail_lib/protocol/ieee802154" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/platform/radio/rail_lib/protocol/wmbus" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/platform/radio/rail_lib/protocol/zwave" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/platform/radio/rail_lib/chip/efr32/efr32xg2x" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/platform/radio/rail_lib/protocol/sidewalk" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/platform/radio/mac" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/platform/radio/mac/rail_mux" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/platform/radio/rail_lib/plugin" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/platform/radio/rail_lib/plugin/coexistence/protocol/ieee802154_uc" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/platform/radio/rail_lib/plugin/rail_util_built_in_phys/efr32xg24" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/platform/radio/rail_lib/plugin/coexistence/common" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/platform/radio/rail_lib/plugin/coexistence/hal/efr32" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/protocol/zigbee/stack/include" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/platform/radio/rail_lib/plugin/rail_util_dma" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/platform/radio/rail_lib/plugin/rail_util_ieee802154" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/platform/radio/rail_lib/plugin/pa-conversions" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/platform/radio/rail_lib/plugin/pa-conversions/efr32xg24" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/platform/radio/rail_lib/plugin/rail_util_power_manager_init" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/platform/radio/rail_lib/plugin/rail_util_pti" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/platform/radio/rail_lib/plugin/rail_util_rssi" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/platform/security/sl_component/se_manager/inc" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/platform/security/sl_component/se_manager/src" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/util/plugin/security_manager" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/util/third_party/segger/systemview/SEGGER" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/util/silicon_labs/silabs_core/memory_manager" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/platform/common/toolchain/inc" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/platform/service/system/inc" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/platform/service/sleeptimer/inc" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/platform/security/sl_component/sl_protocol_crypto/src" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/platform/service/token_manager/inc" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/platform/service/udelay/inc" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/platform/emdrv/ustimer/inc" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/protocol/zigbee/app/framework/plugin/af-support" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/protocol/zigbee/app/framework/plugin/groups-server" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/protocol/zigbee/app/framework/common" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/protocol/zigbee/app/framework/service-function" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/protocol/zigbee/stack/framework" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/protocol/zigbee/app/framework/plugin/debug-print" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/protocol/zigbee/stack/gp" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/protocol/zigbee/app/framework/plugin/green-power-adapter" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/protocol/zigbee/app/framework/include" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/protocol/zigbee/app/framework/util" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/protocol/zigbee/app/framework/security" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/protocol/zigbee/app/framework/signature-decode" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/protocol/zigbee/app/util/zigbee-framework" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/protocol/zigbee/app/util/serial" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/protocol/zigbee/app/framework/plugin/green-power-client" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/protocol/zigbee/app/framework/plugin/green-power-common" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/protocol/zigbee/app/framework/plugin/green-power-server" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/protocol/zigbee/app/framework/plugin/green-power-translation-table" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/protocol/zigbee/app/framework/plugin/multirail-demo" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/protocol/zigbee/app/em260" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/protocol/zigbee/app/xncp" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/protocol/zigbee/app/util/ezsp" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/protocol/zigbee/app/util/security" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/protocol/zigbee/stack/security" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/protocol/zigbee/stack/zigbee" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/protocol/zigbee" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/protocol/zigbee/stack" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/util/silicon_labs/silabs_core" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/protocol/zigbee/stack/core" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/protocol/zigbee/stack/mac" -I"/Users/brrodrig/SimplicityStudio/v5_workspace/zigbee_ncp-ot_rcp-uart_MULTIRAIL/gecko_sdk_4.4.3/protocol/zigbee/stack/zll" -O0 -Wall -Wextra -fomit-frame-pointer -ffunction-sections -fdata-sections -imacrossl_openthread_coex_config.h -imacrossl_openthread_rtos_config.h -imacrossl_gcc_preinclude.h -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mcmse -Werror=unused-variable -Werror=unused-function -Wno-unused-parameter -Wno-missing-field-initializers -Wno-missing-braces -fno-builtin-printf -fno-builtin-sprintf --specs=nano.specs -c -fmessage-length=0 -MMD -MP -MF"gecko_sdk_4.4.3/platform/emdrv/gpiointerrupt/src/gpiointerrupt.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


