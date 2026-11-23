// SPDX-License-Identifier: LGPL-2.1-or-later
#pragma once
#include <stdbool.h>
#include <stdint.h>
#include "esp_err.h"
#ifdef __cplusplus
extern "C" {
#endif
/* I2C0 (touch CST820 0x15, AXP2101 0x34, QMI8658, PCF85063 0x51; 2.2 k pull-ups on the board). fp_i2c_init is idempotent. */
esp_err_t fp_i2c_init(void);
void *fp_i2c_bus(void);                       /* i2c_master_bus_handle_t */
/* CST820: reset pulse on GPIO46, INT on GPIO45. Reads the first finger; x is scaled 29/30 (the maker's calibration for this panel, NightPlayer, MIT). */
esp_err_t fp_touch_init(void);
bool fp_touch_read(uint16_t *x, uint16_t *y);  /* true = a finger is down */
#ifdef __cplusplus
}
#endif
