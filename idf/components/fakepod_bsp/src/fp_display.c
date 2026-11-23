// SPDX-License-Identifier: LGPL-2.1-or-later
#include <stdlib.h>
#include <string.h>
#include "fp_display.h"
#include "fp_pins.h"
#include "co5300.h"
#include "driver/gpio.h"
#include "driver/spi_master.h"
#include "esp_check.h"
#include "esp_heap_caps.h"
#include "esp_lcd_panel_io.h"
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "freertos/task.h"

#define CHUNK_ROWS 16     /* even: the panel takes windows from an even row to an odd one */
static const char *TAG = "fp_display";
static esp_lcd_panel_io_handle_t s_io;
static esp_lcd_panel_handle_t s_panel;
static uint16_t *s_fb;          /* PSRAM canvas */
static uint16_t *s_bounce;      /* internal DMA row chunk, byte-swapped */
static SemaphoreHandle_t s_done;

static bool on_done(esp_lcd_panel_io_handle_t io, esp_lcd_panel_io_event_data_t *ed, void *ctx)
{
    BaseType_t hp = pdFALSE;
    xSemaphoreGiveFromISR(s_done, &hp);
    return hp == pdTRUE;
}

esp_err_t fp_display_init(void)
{
    /* AMOLED supply: a clean off/on cycle, then time for the rails before the reset pulse (JukeDial board day 2026-11-22: 20 ms left the panel in its power-on RAM) */
    gpio_set_level(FP_PIN_LCD_VCI_EN, 0);
    const gpio_config_t c = { .pin_bit_mask = 1ULL << FP_PIN_LCD_VCI_EN, .mode = GPIO_MODE_OUTPUT };
    ESP_RETURN_ON_ERROR(gpio_config(&c), TAG, "vci_en");
    gpio_set_level(FP_PIN_LCD_VCI_EN, 0);
    vTaskDelay(pdMS_TO_TICKS(50));
    gpio_set_level(FP_PIN_LCD_VCI_EN, 1);
    vTaskDelay(pdMS_TO_TICKS(120));

    s_fb = heap_caps_calloc(FP_LCD_W * FP_LCD_H, 2, MALLOC_CAP_SPIRAM);
    s_bounce = heap_caps_malloc(FP_LCD_W * CHUNK_ROWS * 2, MALLOC_CAP_DMA | MALLOC_CAP_INTERNAL);
    s_done = xSemaphoreCreateBinary();
    ESP_RETURN_ON_FALSE(s_fb && s_bounce && s_done, ESP_ERR_NO_MEM, TAG, "no mem");

    const spi_bus_config_t bus = {
        .sclk_io_num = FP_PIN_LCD_SCL, .data0_io_num = FP_PIN_LCD_D0, .data1_io_num = FP_PIN_LCD_D1,
        .data2_io_num = FP_PIN_LCD_D2, .data3_io_num = FP_PIN_LCD_D3, .max_transfer_sz = FP_LCD_W * CHUNK_ROWS * 2,
    };
    ESP_RETURN_ON_ERROR(spi_bus_initialize(FP_LCD_SPI_HOST, &bus, SPI_DMA_CH_AUTO), TAG, "spi bus");
    const esp_lcd_panel_io_spi_config_t io_cfg = {
        .cs_gpio_num = FP_PIN_LCD_CS, .dc_gpio_num = -1, .spi_mode = 0, .pclk_hz = 40 * 1000 * 1000,   /* 40 MHz: the maker found 80 draws a stray black line on partial redraws */
        .trans_queue_depth = 2, .lcd_cmd_bits = 32, .lcd_param_bits = 8, .flags = { .quad_mode = true },
        .on_color_trans_done = on_done,
    };
    ESP_RETURN_ON_ERROR(esp_lcd_new_panel_io_spi((esp_lcd_spi_bus_handle_t)FP_LCD_SPI_HOST, &io_cfg, &s_io), TAG, "panel io");
    ESP_RETURN_ON_ERROR(fp_co5300_new(s_io, FP_PIN_LCD_RST, FP_LCD_X_GAP, &s_panel), TAG, "co5300");
    ESP_RETURN_ON_ERROR(esp_lcd_panel_reset(s_panel), TAG, "reset");
    ESP_RETURN_ON_ERROR(esp_lcd_panel_init(s_panel), TAG, "init");
    return ESP_OK;
}

uint16_t *fp_display_fb(void) { return s_fb; }

esp_err_t fp_display_flush(void)
{
    ESP_RETURN_ON_FALSE(s_fb, ESP_ERR_INVALID_STATE, TAG, "not initialised");
    for (int y = 0; y < FP_LCD_H; y += CHUNK_ROWS) {
        const int rows = (FP_LCD_H - y < CHUNK_ROWS) ? FP_LCD_H - y : CHUNK_ROWS;
        const uint16_t *src = s_fb + (size_t)y * FP_LCD_W;
        for (int i = 0; i < rows * FP_LCD_W; i++) s_bounce[i] = __builtin_bswap16(src[i]);
        xSemaphoreTake(s_done, 0);
        ESP_RETURN_ON_ERROR(esp_lcd_panel_draw_bitmap(s_panel, 0, y, FP_LCD_W, y + rows, s_bounce), TAG, "draw");
        ESP_RETURN_ON_FALSE(xSemaphoreTake(s_done, pdMS_TO_TICKS(200)) == pdTRUE, ESP_ERR_TIMEOUT, TAG, "flush timeout");
    }
    return ESP_OK;
}

esp_err_t fp_display_brightness(uint8_t v) { return fp_co5300_cmd(s_panel, 0x51, &v, 1); }
