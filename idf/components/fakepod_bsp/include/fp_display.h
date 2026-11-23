// SPDX-License-Identifier: LGPL-2.1-or-later
#pragma once
#include <stdint.h>
#include "esp_err.h"
#ifdef __cplusplus
extern "C" {
#endif
/* Full-frame RGB565 canvas in PSRAM (host byte order, 460x460), flushed to the CO5300. Draw into fp_display_fb(), then fp_display_flush(). */
esp_err_t fp_display_init(void);
uint16_t *fp_display_fb(void);
esp_err_t fp_display_flush(void);               /* whole frame, byte-swapped to the panel's order on the way */
esp_err_t fp_display_brightness(uint8_t v);     /* panel command 0x51, 0..255 (AMOLED: no backlight pin) */
#ifdef __cplusplus
}
#endif
