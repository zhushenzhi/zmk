/*
 * Copyright (c) 2020 The ZMK Contributors
 *
 * SPDX-License-Identifier: MIT
 */

#define DT_DRV_COMPAT zmk_behavior_calib

#include <device.h>
#include <drivers/behavior.h>
#include <logging/log.h>

#include <zmk/event_manager.h>
#include <zmk/events/calibration_event.h>

LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);

#if DT_HAS_COMPAT_STATUS_OKAY(DT_DRV_COMPAT)

static int behavior_calib_init(const struct device *dev) { return 0; };

static int on_keymap_binding_pressed(struct zmk_behavior_binding *binding,
                                     struct zmk_behavior_binding_event event) {
    LOG_DBG("force recalibration");
    return ZMK_EVENT_RAISE(new_zmk_calibration_event((struct zmk_calibration_event){.place_holder=true}));
}

static const struct behavior_driver_api behavior_calib_driver_api = {
    .binding_pressed = on_keymap_binding_pressed,
    .locality = BEHAVIOR_LOCALITY_EVENT_SOURCE,
};

#define CALIB_INST(n)                                                                                \
    DEVICE_DT_INST_DEFINE(n, behavior_calib_init, NULL, NULL, NULL,          \
                          APPLICATION, CONFIG_KERNEL_INIT_PRIORITY_DEFAULT,                        \
                          &behavior_calib_driver_api);

DT_INST_FOREACH_STATUS_OKAY(CALIB_INST)

#endif
