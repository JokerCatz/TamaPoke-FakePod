// SPDX-License-Identifier: LGPL-2.1-or-later
#pragma once
/* Fake Pod Nano Pro (ESP32-S31) pin map, from the maker's schematic FAKE_POD_NANO_S31 V1.0 as recorded in the JukeDial project's bsp_pins.h.
 * HAZARD: GPIO36 (LCD reset) is also the flash-voltage strap: only ever driven high, or pulsed low for the panel reset while running. */
#define FP_LCD_W 460
#define FP_LCD_H 460
#define FP_LCD_X_GAP 10          /* the panel RAM columns start at 10 */
#define FP_LCD_SPI_HOST SPI2_HOST
#define FP_PIN_LCD_SCL 38
#define FP_PIN_LCD_CS 37
#define FP_PIN_LCD_D0 39
#define FP_PIN_LCD_D1 40
#define FP_PIN_LCD_D2 42
#define FP_PIN_LCD_D3 43
#define FP_PIN_LCD_RST 36
#define FP_PIN_LCD_VCI_EN 44     /* AMOLED supply enable, high = on. NOT the AXP2101: no PMU voltage register is ever written */
/* TF card, SDMMC 4-bit (the same GPIOs as the round board) */
#define FP_PIN_SD_CLK 24
#define FP_PIN_SD_CMD 25
#define FP_PIN_SD_D0 20
#define FP_PIN_SD_D1 21
#define FP_PIN_SD_D2 22
#define FP_PIN_SD_D3 23
