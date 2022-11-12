/*
 * Copyright (c) 2022 The ZMK Contributors
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <zephyr.h>
#include <zmk/event_manager.h>

struct zmk_calibration_event {
    bool place_holder;
};

ZMK_EVENT_DECLARE(zmk_calibration_event);
