// SPDX-License-Identifier: LGPL-2.1-or-later
/* Adapted from the JukeDial project's bsp_keys.c (same author): same AXP2101 registers and the same rule of what may be written. */
#include "fp_keys.h"
#include "fp_pins.h"
#include "fp_touch.h"
#include "driver/gpio.h"
#include "driver/i2c_master.h"
#include "esp_check.h"
#include "esp_log.h"
#include "esp_timer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static const char *TAG = "fp_keys";
#define REG_CHIP_ID 0x03
#define REG_INTEN2  0x41
#define REG_INTSTS1 0x48
#define REG_INTSTS2 0x49
#define REG_INTSTS3 0x4A
#define ST2_POS 0x01        /* power key released */
#define ST2_NEG 0x02        /* power key pressed  */
#define EN2_VALUE 0x0F      /* key edges + short + long press, nothing else: any other enabled IRQ (the gauge's events) floods nIRQ, as found on another board */
#define SHORT_MAX_US 1500000

static i2c_master_dev_handle_t s_pmu;
static bool s_pmu_ok;
static volatile int s_short_events;

static esp_err_t rd(uint8_t reg, uint8_t *v) { return i2c_master_transmit_receive(s_pmu, &reg, 1, v, 1, 30); }
static esp_err_t wr(uint8_t reg, uint8_t v) { const uint8_t b[2] = { reg, v }; return i2c_master_transmit(s_pmu, b, 2, 30); }

bool fp_keys_pmu_present(void) { return s_pmu_ok; }
bool fp_keys_take_short(void)
{
    if (s_short_events <= 0) return false;
    s_short_events = 0;
    return true;
}

static void keys_task(void *arg)
{
    int64_t top_down = 0, bot_down = 0;
    bool bot_prev = false;
    for (;;) {
        const int64_t now = esp_timer_get_time();
        if (s_pmu_ok && gpio_get_level(FP_PIN_PMU_IRQ) == 0) {
            uint8_t st = 0;
            if (rd(REG_INTSTS2, &st) == ESP_OK && st) {
                wr(REG_INTSTS2, st);                                   /* write-1-to-clear only what was read (nIRQ goes high) */
                if ((st & (ST2_POS | ST2_NEG)) == (ST2_POS | ST2_NEG)) s_short_events++;   /* press and release inside one read: a quick tap */
                else if (st & ST2_NEG) top_down = now;
                else if (st & ST2_POS) { if (top_down && now - top_down < SHORT_MAX_US) s_short_events++; top_down = 0; }
            }
            for (uint8_t reg = REG_INTSTS1; reg <= REG_INTSTS3; reg += 2) {   /* any other PMU event holding nIRQ low is read and cleared too: the line must go quiet */
                uint8_t o = 0;
                if (rd(reg, &o) == ESP_OK && o) wr(reg, o);
            }
        }
        const bool bot = gpio_get_level(FP_PIN_KEY_BOTTOM) == 0;
        if (bot && !bot_prev) bot_down = now;
        if (!bot && bot_prev && bot_down && now - bot_down > 20000 && now - bot_down < SHORT_MAX_US) s_short_events++;   /* 20 ms debounce */
        bot_prev = bot;
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

esp_err_t fp_keys_init(void)
{
    static bool started;
    if (started) return ESP_OK;
    const gpio_config_t k = { .pin_bit_mask = 1ULL << FP_PIN_KEY_BOTTOM, .mode = GPIO_MODE_INPUT, .pull_up_en = GPIO_PULLUP_DISABLE, .pull_down_en = GPIO_PULLDOWN_DISABLE };   /* strapping pin: the board's 10k pull-up only */
    ESP_RETURN_ON_ERROR(gpio_config(&k), TAG, "key gpio");
    const gpio_config_t q = { .pin_bit_mask = 1ULL << FP_PIN_PMU_IRQ, .mode = GPIO_MODE_INPUT };   /* the level shifter's pull-up is on the board */
    ESP_RETURN_ON_ERROR(gpio_config(&q), TAG, "irq gpio");
    ESP_RETURN_ON_ERROR(fp_i2c_init(), TAG, "i2c");
    const i2c_device_config_t dc = { .dev_addr_length = I2C_ADDR_BIT_LEN_7, .device_address = FP_I2C_ADDR_PMU, .scl_speed_hz = FP_I2C_FREQ_HZ };
    ESP_RETURN_ON_ERROR(i2c_master_bus_add_device((i2c_master_bus_handle_t)fp_i2c_bus(), &dc, &s_pmu), TAG, "pmu dev");
    uint8_t id = 0, en = 0;
    if (rd(REG_CHIP_ID, &id) != ESP_OK || (id & 0xCF) != 0x4A) { ESP_LOGW(TAG, "no AXP2101 (chip id 0x%02x): only the bottom key works", id); }
    else {
        s_pmu_ok = true;
        ESP_RETURN_ON_ERROR(rd(REG_INTEN2, &en), TAG, "inten2");
        if (en != EN2_VALUE) ESP_RETURN_ON_ERROR(wr(REG_INTEN2, EN2_VALUE), TAG, "inten2 write");
        ESP_RETURN_ON_ERROR(wr(REG_INTSTS2, 0xFF), TAG, "clear");   /* the start-up's old events (the press that powered the device) */
    }
    started = xTaskCreate(keys_task, "fp_keys", 3072, NULL, 5, NULL) == pdPASS;
    ESP_LOGI(TAG, "keys ready (pmu %s)", s_pmu_ok ? "ok" : "absent");
    return started ? ESP_OK : ESP_FAIL;
}
