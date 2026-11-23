// SPDX-License-Identifier: CC-BY-NC-SA-4.0
// TwoWire stub: the real I2C traffic (touch, PMU, RTC) goes through fakepod_bsp's I2C bus, not through this object. Only the calls setup() makes.
#pragma once
#include <stdint.h>
struct TwoWire {
    bool begin(int = -1, int = -1) { return true; }
    void setTimeOut(uint16_t) {}
    void setTimeout(uint32_t) {}
    void beginTransmission(uint8_t) {}
    uint8_t endTransmission(bool = true) { return 0; }   // the touch chip's presence probe: answered by TouchDrvCST92xx::begin
};
extern TwoWire Wire;
