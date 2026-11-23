// SPDX-License-Identifier: CC-BY-NC-SA-4.0
// TouchDrvCST92xx (the SensorLib class the sketch calls) backed by fakepod_bsp's CST820 reader.
#include "TouchDrvCSTXXX.hpp"
#include "fp_touch.h"
bool TouchDrvCST92xx::begin(TwoWire &, uint8_t, int, int) { return fp_touch_init() == ESP_OK; }
void TouchDrvCST92xx::reset() {}   // fp_touch_init already pulsed the reset line
uint8_t TouchDrvCST92xx::getPoint(int16_t *x, int16_t *y, uint8_t)
{
    uint16_t px, py;
    if (!fp_touch_read(&px, &py)) return 0;
    *x = (int16_t)px; *y = (int16_t)py;   // mirror / swap flags the sketch sets are for the Waveshare panel: ignored until the orientation is measured on this one
    return 1;
}
