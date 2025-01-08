Edits made to allow build of ncp/rcp multi-rail following UG392 (branch FEATURE_GreenPower)

```l33
In sdk/protocol/zigbee/app/framework/common/zigbee_app_framework_rtos_adaptation.c
1. Line 35
#if defined(SL_CATALOG_ZIGBEE_REAL_IPC_PRESENT)

#endif```

2. Line 162

```remove use of sli_zigbee_process_stack_callbacks_event
using #if !defined(SL_ZIGBEE_AF_NCP)```

```
