// Host stand-in for fakepod_bsp's display: a plain RGB565 buffer you can dump to a PNG/PPM.
#include <stdlib.h>
#include "fp_display.h"
static uint16_t *FB; static bool on = true;
extern "C" {
esp_err_t fp_display_init(void) { if (!FB) FB = (uint16_t *)calloc(460 * 460, 2); return 0; }
uint16_t *fp_display_fb(void) { return FB; }
esp_err_t fp_display_flush(void) { return 0; }
esp_err_t fp_display_brightness(uint8_t) { return 0; }
esp_err_t fp_display_off(void) { on = false; return 0; }
esp_err_t fp_display_on(uint8_t) { on = true; return 0; }
bool fp_display_is_on(void) { return on; }
}
