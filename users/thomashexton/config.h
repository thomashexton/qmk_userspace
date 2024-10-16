#ifdef MACCEL_ENABLE
    #include "features/maccel/maccel.h"
#endif

#ifdef POINTING_DEVICE_ENABLE
#    ifdef MACCEL_ENABLE
#        define MACCEL_DEBUG
#        define MACCEL_USE_KEYCODES
#        define EECONFIG_USER_DATA_SIZE 20
#        undef PRINTF_SUPPORT_DECIMAL_SPECIFIERS
#        define PRINTF_SUPPORT_DECIMAL_SPECIFIERS 1
#    endif
#    define MOUSE_EXTENDED_REPORT
#endif
