// SPDX-License-Identifier: CC-BY-NC-SA-4.0
// TamaPoke-FakePod, step 1: bring the panel up, draw a test pattern, and prove the upstream game logic (pet.cpp, i18n.cpp) links.
#include <stdio.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "nvs_flash.h"
#include "fp_display.h"
#include "fp_pins.h"
#include "pet.h"

static const char *TAG = "tamapoke";
static inline uint16_t rgb(uint8_t r, uint8_t g, uint8_t b) { return (uint16_t)(((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3)); }

extern "C" void app_main(void)
{
    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(fp_display_init());
    uint16_t *fb = fp_display_fb();
    for (int y = 0; y < FP_LCD_H; y++)
        for (int x = 0; x < FP_LCD_W; x++) {
            const int bar = x * 8 / FP_LCD_W;
            static const uint8_t col[8][3] = { {255,255,255}, {255,255,0}, {0,255,255}, {0,255,0}, {255,0,255}, {255,0,0}, {0,0,255}, {0,0,0} };
            fb[y * FP_LCD_W + x] = (y < 8 || y >= FP_LCD_H - 8 || x < 8 || x >= FP_LCD_W - 8) ? rgb(255, 255, 255) : rgb(col[bar][0], col[bar][1], col[bar][2]);
        }
    ESP_ERROR_CHECK(fp_display_flush());
    ESP_ERROR_CHECK(fp_display_brightness(160));
    ESP_LOGI(TAG, "panel up, test pattern drawn; Pet is %u bytes", (unsigned)sizeof(Pet));
    /* OLED: never leave a picture lit. 10 s on, off, a wake test after 5 s (proves the soft-wake path), 10 s on, off for good. */
    vTaskDelay(pdMS_TO_TICKS(10000));
    ESP_LOGI(TAG, "off: %s", esp_err_to_name(fp_display_off()));
    vTaskDelay(pdMS_TO_TICKS(5000));
    ESP_LOGI(TAG, "wake: %s", esp_err_to_name(fp_display_on(160)));
    vTaskDelay(pdMS_TO_TICKS(10000));
    ESP_LOGI(TAG, "off for good: %s", esp_err_to_name(fp_display_off()));
}
