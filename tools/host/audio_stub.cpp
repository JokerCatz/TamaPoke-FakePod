#include "audio.h"
static bool s_on = false; static uint8_t s_vol = 0;
void audioBegin() {} void sfxPlay(uint8_t) {} void audioSetEnabled(bool on) { s_on = on; } bool audioEnabled() { return s_on; }
void audioSetVolume(uint8_t l) { s_vol = l; } uint8_t audioVolume() { return s_vol; } void audioSetSleeping(bool) {} bool audioBusy() { return false; } void audioSetIdle(bool) {}
