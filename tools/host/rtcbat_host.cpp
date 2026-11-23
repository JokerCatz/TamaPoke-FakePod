// Host stand-in for rtcbat.cpp (AXP2101 + PCF85063): a software clock, no battery.
#include "rtcbat.h"
#include <time.h>
static uint32_t g_offset = 0;
bool rtcBegin() { return true; }
uint32_t rtcEpoch() { return (uint32_t)time(nullptr) + g_offset; }
void rtcSetEpoch(uint32_t e) { g_offset = e - (uint32_t)time(nullptr); }
bool batBegin() { return true; }
void pmuEnablePanel() {}
void batSetPollMs(uint32_t) {}
int batPercent() { return -1; }
bool batCharging() { return false; }
int batMillivolts() { return 0; }
bool batShouldShutdown() { return false; }
void batPowerOff() {}
bool usbPresent() { return true; }
bool usbPresentNow() { return true; }
void pwrSetup() {}
bool pwrShortPressed() { return false; }
