

#include <stdint.h>

#include "sl_cpc_drv_uart_config.h"
#include "sl_cos.h"
#include "sl_cpc_drv_uart_eusart_vcom_config.h"

#define WITH_HWFC              eusartHwFlowControlCtsAndRts_D
#define WITHOUT_HWFC           eusartHwFlowControlNone_D

void sl_cpc_config_vcom(void)
{
  uint8_t flowcontrol;

  #if (SL_CPC_DRV_UART_FLOW_CONTROL_TYPE == WITH_HWFC)
    flowcontrol = COS_CONFIG_FLOWCONTROL_CTS_RTS;
  #else 
    flowcontrol = COS_CONFIG_FLOWCONTROL_NONE;
  #endif

  sl_cos_config_vcom(SL_CPC_DRV_UART_VCOM_BAUDRATE, flowcontrol);
}


