#pragma once

#ifdef MACCEL_ENABLE
#    include "features/maccel/maccel.h"
#endif

// clang-format off
enum user_layers {
    LAYER_BASE = 0,
    LAYER_RAISE,
    LAYER_LOWER,
    LAYER_POINTER
};
// clang-format on
