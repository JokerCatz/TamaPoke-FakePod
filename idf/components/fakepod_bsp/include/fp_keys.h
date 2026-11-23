// SPDX-License-Identifier: LGPL-2.1-or-later
#pragma once
#include <stdbool.h>
#include "esp_err.h"
#ifdef __cplusplus
extern "C" {
#endif
/* The two side keys. A small task samples both every 10 ms and latches a SHORT press (down and up within 1.5 s) of either one. A long hold of the top key is the PMU's own
 * hard power-off (4 s) and is not touched. The ONLY writes to the AXP2101 are its IRQ-enable register 0x41 (= 0x0F: power-key edges, short and long press, nothing else) and
 * the write-1-to-clear of the status bits that were read: no voltage, rail, charger or power-key-timing register is ever written. fp_i2c_init() first. */
esp_err_t fp_keys_init(void);
bool fp_keys_take_short(void);     /* true once per short press of either key */
bool fp_keys_pmu_present(void);
#ifdef __cplusplus
}
#endif
