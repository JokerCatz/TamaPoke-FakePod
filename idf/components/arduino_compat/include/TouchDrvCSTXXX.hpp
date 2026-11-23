// SPDX-License-Identifier: CC-BY-NC-SA-4.0
// Same method names as SensorLib's TouchDrvCST92xx, so setup()/handleTouch() compile unchanged. Backed by fakepod_bsp's CST820 reader (fp_touch.h) on the device,
// and by a scripted pointer on the PC. The CST820 is the Fake Pod's panel; the CST9217 of the Waveshare board is not supported here.
#pragma once
#include <stdint.h>
class TwoWire;
class TouchDrvCST92xx {
public:
    void setPins(int rst, int irq) { rst_ = rst; irq_ = irq; }
    bool begin(TwoWire &, uint8_t addr, int sda, int scl);
    void reset();
    void setMaxCoordinates(uint16_t w, uint16_t h) { w_ = w; h_ = h; }
    void setMirrorXY(bool mx, bool my) { mx_ = mx; my_ = my; }
    void setSwapXY(bool s) { swap_ = s; }
    uint8_t getPoint(int16_t *x, int16_t *y, uint8_t maxPoints = 1);
private:
    int rst_ = -1, irq_ = -1; uint16_t w_ = 0, h_ = 0; bool mx_ = false, my_ = false, swap_ = false;
};
using TouchDrvCST816 = TouchDrvCST92xx;
