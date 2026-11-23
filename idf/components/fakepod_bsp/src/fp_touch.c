// SPDX-License-Identifier: LGPL-2.1-or-later
#include "fp_touch.h"
#include "fp_pins.h"
#include "driver/gpio.h"
#include "driver/i2c_master.h"
#include "esp_check.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static const char *TAG = "fp_touch";
static i2c_master_bus_handle_t s_bus;
static i2c_master_dev_handle_t s_tp;

esp_err_t fp_i2c_init(void)
{
    if (s_bus) return ESP_OK;
    const i2c_master_bus_config_t cfg = {
        .i2c_port = I2C_NUM_0, .sda_io_num = FP_PIN_I2C_SDA, .scl_io_num = FP_PIN_I2C_SCL,
        .clk_source = I2C_CLK_SRC_DEFAULT, .glitch_ignore_cnt = 7, .flags.enable_internal_pullup = 1,
    };
    return i2c_new_master_bus(&cfg, &s_bus);
}
void *fp_i2c_bus(void) { return s_bus; }

esp_err_t fp_touch_init(void)
{
    ESP_RETURN_ON_ERROR(fp_i2c_init(), TAG, "i2c");
    const gpio_config_t rst = { .pin_bit_mask = 1ULL << FP_PIN_TP_RST, .mode = GPIO_MODE_OUTPUT };
    ESP_RETURN_ON_ERROR(gpio_config(&rst), TAG, "rst");
    const gpio_config_t irq = { .pin_bit_mask = 1ULL << FP_PIN_TP_INT, .mode = GPIO_MODE_INPUT, .pull_up_en = GPIO_PULLUP_ENABLE };
    ESP_RETURN_ON_ERROR(gpio_config(&irq), TAG, "int");
    gpio_set_level(FP_PIN_TP_RST, 0); vTaskDelay(pdMS_TO_TICKS(10));
    gpio_set_level(FP_PIN_TP_RST, 1); vTaskDelay(pdMS_TO_TICKS(60));
    const i2c_device_config_t dc = { .dev_addr_length = I2C_ADDR_BIT_LEN_7, .device_address = FP_I2C_ADDR_TOUCH, .scl_speed_hz = FP_I2C_FREQ_HZ };
    ESP_RETURN_ON_ERROR(i2c_master_bus_add_device(s_bus, &dc, &s_tp), TAG, "add dev");
    uint8_t reg = 0xA7, id = 0;                       /* chip id: also proves the chip answers */
    esp_err_t e = i2c_master_transmit_receive(s_tp, &reg, 1, &id, 1, 50);
    ESP_LOGI(TAG, "CST820 chip id reg 0xA7 = 0x%02x (%s)", id, esp_err_to_name(e));
    return e;
}

bool fp_touch_read(uint16_t *x, uint16_t *y)
{
    if (!s_tp) return false;
    uint8_t reg = 0x02, b[5] = { 0 };                 /* finger count, XH, XL, YH, YL */
    if (i2c_master_transmit_receive(s_tp, &reg, 1, b, sizeof b, 20) != ESP_OK) return false;
    if ((b[0] & 0x0F) == 0) return false;
    uint32_t px = (uint32_t)(((b[1] & 0x0F) << 8) | b[2]), py = (uint32_t)(((b[3] & 0x0F) << 8) | b[4]);
    px = px * 29 / 30;
    if (x) *x = (uint16_t)px;
    if (y) *y = (uint16_t)py;
    return true;
}
