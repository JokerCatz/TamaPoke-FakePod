// SPDX-License-Identifier: LGPL-2.1-or-later
#pragma once
#include "esp_err.h"
#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_ops.h"
esp_err_t fp_co5300_new(esp_lcd_panel_io_handle_t io, int reset_gpio, int x_gap, esp_lcd_panel_handle_t *out);
esp_err_t fp_co5300_cmd(esp_lcd_panel_handle_t panel, uint8_t cmd, const uint8_t *data, size_t n);
