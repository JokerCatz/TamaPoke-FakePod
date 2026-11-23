// SPDX-License-Identifier: CC-BY-NC-SA-4.0
#include "Arduino.h"
#include "Preferences.h"
#include <stdarg.h>

SerialShim Serial;
int SerialShim::printf(const char *fmt, ...) { va_list a; va_start(a, fmt); int n = vprintf(fmt, a); va_end(a); return n; }

long random(long hi) { return hi <= 0 ? 0 : (long)(esp_random() % (uint32_t)hi); }
long random(long lo, long hi) { return hi <= lo ? lo : lo + random(hi - lo); }

bool Preferences::begin(const char *ns, bool ro) { ro_ = ro; open_ = nvs_open(ns, ro ? NVS_READONLY : NVS_READWRITE, &h_) == ESP_OK; return open_; }
void Preferences::end() { if (open_) { nvs_close(h_); open_ = false; } }
bool Preferences::clear() { return open_ && !ro_ && nvs_erase_all(h_) == ESP_OK && nvs_commit(h_) == ESP_OK; }
bool Preferences::isKey(const char *k) { size_t n = 0; return open_ && nvs_get_blob(h_, k, nullptr, &n) == ESP_OK; }
#define PUT(T, FN) { if (!open_ || ro_ || FN(h_, k, v) != ESP_OK) return 0; nvs_commit(h_); return sizeof(T); }
size_t Preferences::putUChar(const char *k, uint8_t v) PUT(uint8_t, nvs_set_u8)
size_t Preferences::putBool(const char *k, bool v) { return putUChar(k, v ? 1 : 0); }
size_t Preferences::putShort(const char *k, int16_t v) PUT(int16_t, nvs_set_i16)
size_t Preferences::putUShort(const char *k, uint16_t v) PUT(uint16_t, nvs_set_u16)
size_t Preferences::putUInt(const char *k, uint32_t v) PUT(uint32_t, nvs_set_u32)
size_t Preferences::putBytes(const char *k, const void *b, size_t n) { if (!open_ || ro_ || nvs_set_blob(h_, k, b, n) != ESP_OK) return 0; nvs_commit(h_); return n; }
size_t Preferences::putString(const char *k, const char *v) { if (!open_ || ro_ || nvs_set_str(h_, k, v) != ESP_OK) return 0; nvs_commit(h_); return strlen(v); }
uint8_t Preferences::getUChar(const char *k, uint8_t d) { uint8_t v; return open_ && nvs_get_u8(h_, k, &v) == ESP_OK ? v : d; }
bool Preferences::getBool(const char *k, bool d) { return getUChar(k, d ? 1 : 0) != 0; }
int16_t Preferences::getShort(const char *k, int16_t d) { int16_t v; return open_ && nvs_get_i16(h_, k, &v) == ESP_OK ? v : d; }
uint16_t Preferences::getUShort(const char *k, uint16_t d) { uint16_t v; return open_ && nvs_get_u16(h_, k, &v) == ESP_OK ? v : d; }
uint32_t Preferences::getUInt(const char *k, uint32_t d) { uint32_t v; return open_ && nvs_get_u32(h_, k, &v) == ESP_OK ? v : d; }
size_t Preferences::getBytes(const char *k, void *b, size_t n) { size_t len = n; return open_ && nvs_get_blob(h_, k, b, &len) == ESP_OK ? len : 0; }
size_t Preferences::getString(const char *k, char *b, size_t n) { size_t len = n; return open_ && nvs_get_str(h_, k, b, &len) == ESP_OK ? len - 1 : 0; }
size_t Preferences::putChar(const char *k, int8_t v) PUT(int8_t, nvs_set_i8)
int8_t Preferences::getChar(const char *k, int8_t d) { int8_t v; return open_ && nvs_get_i8(h_, k, &v) == ESP_OK ? v : d; }
