// SPDX-License-Identifier: CC-BY-NC-SA-4.0
// Audio is off in the first port steps (the Fake Pod has a CS43131 headphone DAC, no ES8311 / speaker): same API as upstream audio.h, no sound.
#include "audio.h"
static bool s_on = false;
static uint8_t s_vol = 0;
void audioBegin() {}
void sfxPlay(uint8_t) {}
void audioSetEnabled(bool on) { s_on = on; }
bool audioEnabled() { return s_on; }
void audioSetVolume(uint8_t level) { s_vol = level; }
uint8_t audioVolume() { return s_vol; }
void audioSetSleeping(bool) {}
bool audioBusy() { return false; }
void audioSetIdle(bool) {}
