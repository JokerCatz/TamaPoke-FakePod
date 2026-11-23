// SPDX-License-Identifier: LGPL-2.1-or-later
/* CO5300 (460x460 AMOLED, QSPI) as an esp_lcd panel. Trimmed from the JukeDial project's bsp_co5300.c (same author).
 * Init values marked NP are facts from NightPlayer (c) 2026 ZYFDroid, MIT (https://gitee.com/ZYFDroid/night-player-fake-pod-nano), the working firmware of this panel on this board.
 * QSPI framing: opcode 0x02 + command in bits 8..15 for a command, 0x32 for colour. Every window must start on an even column/row and end on an odd one. */
#include <stdlib.h>
#include <sys/cdefs.h>
#include "co5300.h"
#include "driver/gpio.h"
#include "esp_check.h"
#include "esp_lcd_panel_commands.h"
#include "esp_lcd_panel_interface.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define OPC_WRITE_CMD   0x02u
#define OPC_WRITE_COLOR 0x32u
static const char *TAG = "co5300";

typedef struct { esp_lcd_panel_t base; esp_lcd_panel_io_handle_t io; int reset_gpio, x_gap, y_gap; } co5300_t;

static esp_err_t tx_cmd(co5300_t *p, uint8_t cmd, const void *data, size_t n)
{
    return esp_lcd_panel_io_tx_param(p->io, (int)((OPC_WRITE_CMD << 24) | ((uint32_t)cmd << 8)), data, n);
}
static esp_err_t pnl_del(esp_lcd_panel_t *panel) { free(__containerof(panel, co5300_t, base)); return ESP_OK; }
static esp_err_t pnl_reset(esp_lcd_panel_t *panel)
{
    co5300_t *p = __containerof(panel, co5300_t, base);
    gpio_set_level(p->reset_gpio, 0); vTaskDelay(pdMS_TO_TICKS(20));
    gpio_set_level(p->reset_gpio, 1); vTaskDelay(pdMS_TO_TICKS(120));   /* ends high, always */
    return ESP_OK;
}
typedef struct { uint8_t cmd, n, d[4]; uint16_t delay_ms; } init_t;
static const init_t INIT[] = {
    { 0xFE, 1, { 0x00 }, 0 },                    /* user command set */
    { 0xC4, 1, { 0x80 }, 0 },                    /* NP: SPI mode control (quad-pixel path); remove first if the first image is garbled */
    { 0x35, 1, { 0x00 }, 0 },                    /* NP: TE output on (not read by us) */
    { 0x3A, 1, { 0x55 }, 0 },                    /* RGB565 */
    { 0x53, 1, { 0x20 }, 0 },
    { 0x51, 1, { 0x00 }, 0 },                    /* brightness 0 until the first frame is drawn */
    { 0x63, 1, { 0xFF }, 0 },
    { 0x2A, 4, { 0x00, 0x0A, 0x01, 0xD5 }, 0 },  /* columns 10..469 */
    { 0x2B, 4, { 0x00, 0x00, 0x01, 0xCB }, 0 },  /* rows 0..459 */
    { 0x11, 0, { 0 }, 120 },                     /* sleep out */
    { 0x29, 0, { 0 }, 20 },                      /* display on */
    { 0x58, 1, { 0x07 }, 10 },                   /* NP: normal-mode brightness value, undocumented */
};
static esp_err_t pnl_init(esp_lcd_panel_t *panel)
{
    co5300_t *p = __containerof(panel, co5300_t, base);
    for (size_t i = 0; i < sizeof INIT / sizeof INIT[0]; i++) {
        ESP_RETURN_ON_ERROR(tx_cmd(p, INIT[i].cmd, INIT[i].n ? INIT[i].d : NULL, INIT[i].n), TAG, "init cmd %02x", INIT[i].cmd);
        if (INIT[i].delay_ms) vTaskDelay(pdMS_TO_TICKS(INIT[i].delay_ms));
    }
    return ESP_OK;
}
static esp_err_t pnl_draw(esp_lcd_panel_t *panel, int x0, int y0, int x1, int y1, const void *color)
{
    co5300_t *p = __containerof(panel, co5300_t, base);
    x0 += p->x_gap; x1 += p->x_gap; y0 += p->y_gap; y1 += p->y_gap;
    const uint8_t ca[4] = { (uint8_t)(x0 >> 8), (uint8_t)x0, (uint8_t)((x1 - 1) >> 8), (uint8_t)(x1 - 1) };
    const uint8_t ra[4] = { (uint8_t)(y0 >> 8), (uint8_t)y0, (uint8_t)((y1 - 1) >> 8), (uint8_t)(y1 - 1) };
    ESP_RETURN_ON_ERROR(tx_cmd(p, LCD_CMD_CASET, ca, 4), TAG, "caset");
    ESP_RETURN_ON_ERROR(tx_cmd(p, LCD_CMD_RASET, ra, 4), TAG, "raset");
    return esp_lcd_panel_io_tx_color(p->io, (int)((OPC_WRITE_COLOR << 24) | ((uint32_t)LCD_CMD_RAMWR << 8)), color, (size_t)(x1 - x0) * (size_t)(y1 - y0) * 2u);
}
static esp_err_t pnl_invert(esp_lcd_panel_t *panel, bool inv) { return tx_cmd(__containerof(panel, co5300_t, base), inv ? LCD_CMD_INVON : LCD_CMD_INVOFF, NULL, 0); }
static esp_err_t pnl_mirror(esp_lcd_panel_t *panel, bool mx, bool my)
{
    const uint8_t m = (uint8_t)((mx ? 0x40 : 0) | (my ? 0x80 : 0));
    return tx_cmd(__containerof(panel, co5300_t, base), LCD_CMD_MADCTL, &m, 1);
}
static esp_err_t pnl_swap(esp_lcd_panel_t *panel, bool swap) { (void)panel; (void)swap; return ESP_ERR_NOT_SUPPORTED; }
static esp_err_t pnl_gap(esp_lcd_panel_t *panel, int xg, int yg) { co5300_t *p = __containerof(panel, co5300_t, base); p->x_gap = xg; p->y_gap = yg; return ESP_OK; }
static esp_err_t pnl_onoff(esp_lcd_panel_t *panel, bool on) { return tx_cmd(__containerof(panel, co5300_t, base), on ? LCD_CMD_DISPON : LCD_CMD_DISPOFF, NULL, 0); }

esp_err_t fp_co5300_new(esp_lcd_panel_io_handle_t io, int reset_gpio, int x_gap, esp_lcd_panel_handle_t *out)
{
    ESP_RETURN_ON_FALSE(io && out && reset_gpio >= 0, ESP_ERR_INVALID_ARG, TAG, "args");
    co5300_t *p = calloc(1, sizeof *p);
    ESP_RETURN_ON_FALSE(p, ESP_ERR_NO_MEM, TAG, "no mem");
    gpio_set_level(reset_gpio, 1);                /* output register high BEFORE the pin becomes an output: GPIO36 is the flash-voltage strap, it must never dip */
    const gpio_config_t c = { .pin_bit_mask = 1ULL << reset_gpio, .mode = GPIO_MODE_OUTPUT };
    esp_err_t e = gpio_config(&c);
    if (e != ESP_OK) { free(p); return e; }
    gpio_set_level(reset_gpio, 1);
    p->io = io; p->reset_gpio = reset_gpio; p->x_gap = x_gap;
    p->base.del = pnl_del; p->base.reset = pnl_reset; p->base.init = pnl_init; p->base.draw_bitmap = pnl_draw;
    p->base.invert_color = pnl_invert; p->base.mirror = pnl_mirror; p->base.swap_xy = pnl_swap; p->base.set_gap = pnl_gap; p->base.disp_on_off = pnl_onoff;
    *out = &p->base;
    return ESP_OK;
}
esp_err_t fp_co5300_cmd(esp_lcd_panel_handle_t panel, uint8_t cmd, const uint8_t *data, size_t n)
{
    ESP_RETURN_ON_FALSE(panel, ESP_ERR_INVALID_STATE, TAG, "no panel");
    return tx_cmd(__containerof(panel, co5300_t, base), cmd, data, n);
}
