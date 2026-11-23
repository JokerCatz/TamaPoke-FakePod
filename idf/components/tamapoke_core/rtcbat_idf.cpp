// SPDX-License-Identifier: CC-BY-NC-SA-4.0
// Software clock + no battery reading for now (the PCF85063 / AXP2101 reads come next; the AXP2101 stays read-only).
#include "rtcbat.h"
#include "fp_keys.h"
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
void pwrSetup() { fp_keys_init(); }                 // both side keys: a short press of either is latched by a small task
bool pwrShortPressed() { return fp_keys_take_short(); }
