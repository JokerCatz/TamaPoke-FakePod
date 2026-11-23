// SPDX-License-Identifier: CC-BY-NC-SA-4.0
// TamaPoke-FakePod: runs the (ported) Arduino sketch's setup() / loop() under ESP-IDF.
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "nvs_flash.h"

void setup();
void loop();

extern "C" void app_main(void)
{
    ESP_ERROR_CHECK(nvs_flash_init());
    setup();
    for (;;) { loop(); vTaskDelay(1); }
}
