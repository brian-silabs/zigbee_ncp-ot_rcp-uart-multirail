Edits made to allow build of ncp/rcp multi-rail following UG392 (branch FEATURE_GreenPower)

1.

```l33
zigbee_app_framework_rtos_adaptation.c
# ifdef REAL_IPC

# endif```

2.

```remove use of sli_zigbee_process_stack_callbacks_event
using #if !defined(SL_ZIGBEE_AF_NCP)```

3.

```Add IOSTREAM_VUART (or other)```

4.

```In legacy_hal/src-disagnostic replace SL_CATALOG_IOSTREAM_UART_COMMON_PRESENT by SL_CATALOG_IOSTREAM_PRESENT```
```
