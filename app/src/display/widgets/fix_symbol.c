#include <zephyr/kernel.h>
#include <zephyr/bluetooth/services/bas.h>

#include <zephyr/logging/log.h>
LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);
#include <zmk/display.h>
#include <zmk/display/widgets/fix_symbol.h>

static sys_slist_t widgets = SYS_SLIST_STATIC_INIT(&widgets);

const char* left_text = "gulai's corne";
const char* right_text = "have a nice day!";

int zmk_widget_fix_symbol_init(struct zmk_widget_fix_symbol *widget, lv_obj_t *parent){
    widget->obj = lv_label_create(parent);
    lv_label_set_text(widget->obj, right_text);
    sys_slist_append(&widgets, &widget->node);
    return 0;
}

lv_obj_t *zmk_widget_fix_symbol_obj(struct zmk_widget_fix_symbol *widget){
    return widget->obj;
}