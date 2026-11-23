#pragma once
#include <stdint.h>
#include <stdbool.h>
#include "esp_err.h"
#ifdef __cplusplus
extern "C" {
#endif
esp_err_t fp_display_init(void); uint16_t *fp_display_fb(void); esp_err_t fp_display_flush(void); esp_err_t fp_display_brightness(uint8_t v);
esp_err_t fp_display_off(void); esp_err_t fp_display_on(uint8_t b); bool fp_display_is_on(void);
#ifdef __cplusplus
}
#endif
