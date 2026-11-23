// SPDX-License-Identifier: CC-BY-NC-SA-4.0
// TamaPoke-FakePod, step 2: the gfx layer (Arduino_Canvas subset) end to end on the panel, then the OLED goes off. Upstream game logic still links in untouched.
#include <stdio.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "nvs_flash.h"
#include "Arduino_GFX_Library.h"
#include "fp_display.h"
#include "pet.h"

static const char *TAG = "tamapoke";

extern "C" void app_main(void)
{
    ESP_ERROR_CHECK(nvs_flash_init());
    Arduino_Canvas *gfx = new Arduino_Canvas(460, 460);
    if (!gfx->begin()) { ESP_LOGE(TAG, "gfx->begin() failed"); return; }

    gfx->fillScreen(RGB565(20, 24, 40));
    gfx->fillRoundRect(20, 20, 200, 80, 16, RGB565(60, 160, 90));
    gfx->drawRoundRect(20, 110, 200, 80, 16, RGB565(255, 255, 255));
    gfx->fillCircle(300, 70, 40, RGB565(220, 60, 60));
    gfx->drawCircle(300, 170, 40, RGB565(240, 220, 60));
    gfx->fillTriangle(40, 300, 140, 220, 200, 320, RGB565(80, 120, 255));
    gfx->drawLine(240, 220, 440, 330, RGB565(255, 255, 255));
    gfx->drawLine(240, 330, 440, 220, RGB565(255, 128, 0));
    gfx->drawRect(230, 210, 220, 130, RGB565(128, 128, 128));
    gfx->setTextColor(RGB565(255, 255, 255));
    gfx->setTextSize(1); gfx->setCursor(20, 350); gfx->print("size1: TamaPoke FakePod 0123456789");
    gfx->setTextSize(2); gfx->setCursor(20, 365); gfx->print("size2: Pikachu Lv.25");
    gfx->setTextSize(3); gfx->setCursor(20, 390); gfx->print("Size3 ABC");
    gfx->flush();
    ESP_ERROR_CHECK(fp_display_brightness(160));
    ESP_LOGI(TAG, "gfx scene drawn; Pet is %u bytes", (unsigned)sizeof(Pet));

    /* OLED: never leave a picture lit. */
    vTaskDelay(pdMS_TO_TICKS(15000));
    ESP_LOGI(TAG, "off: %s", esp_err_to_name(fp_display_off()));
}
