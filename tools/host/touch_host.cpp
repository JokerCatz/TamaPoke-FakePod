// Host stand-in for the CST820 reader: a scripted pointer the test sets (host_touch_set).
#include "TouchDrvCSTXXX.hpp"
static bool g_down; static int16_t g_x, g_y;
void host_touch_set(bool down, int16_t x, int16_t y) { g_down = down; g_x = x; g_y = y; }
bool TouchDrvCST92xx::begin(TwoWire &, uint8_t, int, int) { return true; }
void TouchDrvCST92xx::reset() {}
uint8_t TouchDrvCST92xx::getPoint(int16_t *x, int16_t *y, uint8_t) { if (!g_down) return 0; *x = g_x; *y = g_y; return 1; }
