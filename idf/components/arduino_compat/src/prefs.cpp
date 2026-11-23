// SPDX-License-Identifier: CC-BY-NC-SA-4.0
#include "Preferences.h"
#include <string.h>
#ifdef ESP_PLATFORM
bool Preferences::begin(const char *ns, bool ro) { ro_ = ro; open_ = nvs_open(ns, ro ? NVS_READONLY : NVS_READWRITE, &h_) == ESP_OK; return open_; }
void Preferences::end() { if (open_) { nvs_close(h_); open_ = false; } }
bool Preferences::clear() { return open_ && !ro_ && nvs_erase_all(h_) == ESP_OK && nvs_commit(h_) == ESP_OK; }
bool Preferences::isKey(const char *k) { size_t n = 0; return open_ && nvs_get_blob(h_, k, nullptr, &n) == ESP_OK; }
#define PUT(T, FN) { if (!open_ || ro_ || FN(h_, k, v) != ESP_OK) return 0; nvs_commit(h_); return sizeof(T); }
size_t Preferences::putChar(const char *k, int8_t v) PUT(int8_t, nvs_set_i8)
size_t Preferences::putUChar(const char *k, uint8_t v) PUT(uint8_t, nvs_set_u8)
size_t Preferences::putShort(const char *k, int16_t v) PUT(int16_t, nvs_set_i16)
size_t Preferences::putUShort(const char *k, uint16_t v) PUT(uint16_t, nvs_set_u16)
size_t Preferences::putUInt(const char *k, uint32_t v) PUT(uint32_t, nvs_set_u32)
size_t Preferences::putBytes(const char *k, const void *b, size_t n) { if (!open_ || ro_ || nvs_set_blob(h_, k, b, n) != ESP_OK) return 0; nvs_commit(h_); return n; }
size_t Preferences::putString(const char *k, const char *v) { if (!open_ || ro_ || nvs_set_str(h_, k, v) != ESP_OK) return 0; nvs_commit(h_); return strlen(v); }
int8_t Preferences::getChar(const char *k, int8_t d) { int8_t v; return open_ && nvs_get_i8(h_, k, &v) == ESP_OK ? v : d; }
uint8_t Preferences::getUChar(const char *k, uint8_t d) { uint8_t v; return open_ && nvs_get_u8(h_, k, &v) == ESP_OK ? v : d; }
int16_t Preferences::getShort(const char *k, int16_t d) { int16_t v; return open_ && nvs_get_i16(h_, k, &v) == ESP_OK ? v : d; }
uint16_t Preferences::getUShort(const char *k, uint16_t d) { uint16_t v; return open_ && nvs_get_u16(h_, k, &v) == ESP_OK ? v : d; }
uint32_t Preferences::getUInt(const char *k, uint32_t d) { uint32_t v; return open_ && nvs_get_u32(h_, k, &v) == ESP_OK ? v : d; }
size_t Preferences::getBytes(const char *k, void *b, size_t n) { size_t len = n; return open_ && nvs_get_blob(h_, k, b, &len) == ESP_OK ? len : 0; }
size_t Preferences::getString(const char *k, char *b, size_t n) { size_t len = n; return open_ && nvs_get_str(h_, k, b, &len) == ESP_OK ? len - 1 : 0; }
#else
static std::map<std::string, std::vector<uint8_t>> &store() { static std::map<std::string, std::vector<uint8_t>> m; return m; }
bool Preferences::begin(const char *ns, bool ro) { ns_ = ns; ro_ = ro; open_ = true; return true; }
void Preferences::end() { open_ = false; }
bool Preferences::clear() { if (!open_ || ro_) return false; for (auto it = store().begin(); it != store().end();) it = it->first.rfind(ns_ + "/", 0) == 0 ? store().erase(it) : std::next(it); return true; }
bool Preferences::isKey(const char *k) { return store().count(ns_ + "/" + k) != 0; }
static size_t put(Preferences *, bool open, bool ro, const std::string &key, const void *b, size_t n) { if (!open || ro) return 0; auto &v = store()[key]; v.assign((const uint8_t *)b, (const uint8_t *)b + n); return n; }
#define KEY (ns_ + "/" + k)
size_t Preferences::putChar(const char *k, int8_t v) { return put(this, open_, ro_, KEY, &v, sizeof v); }
size_t Preferences::putUChar(const char *k, uint8_t v) { return put(this, open_, ro_, KEY, &v, sizeof v); }
size_t Preferences::putBool(const char *k, bool v) { return putUChar(k, v ? 1 : 0); }
size_t Preferences::putShort(const char *k, int16_t v) { return put(this, open_, ro_, KEY, &v, sizeof v); }
size_t Preferences::putUShort(const char *k, uint16_t v) { return put(this, open_, ro_, KEY, &v, sizeof v); }
size_t Preferences::putUInt(const char *k, uint32_t v) { return put(this, open_, ro_, KEY, &v, sizeof v); }
size_t Preferences::putBytes(const char *k, const void *b, size_t n) { return put(this, open_, ro_, KEY, b, n); }
size_t Preferences::putString(const char *k, const char *v) { return put(this, open_, ro_, KEY, v, strlen(v) + 1) - 1; }
template <class T> static T get(const std::string &key, T d) { auto it = store().find(key); T v; if (it == store().end() || it->second.size() != sizeof v) return d; memcpy(&v, it->second.data(), sizeof v); return v; }
int8_t Preferences::getChar(const char *k, int8_t d) { return get<int8_t>(KEY, d); }
uint8_t Preferences::getUChar(const char *k, uint8_t d) { return get<uint8_t>(KEY, d); }
int16_t Preferences::getShort(const char *k, int16_t d) { return get<int16_t>(KEY, d); }
uint16_t Preferences::getUShort(const char *k, uint16_t d) { return get<uint16_t>(KEY, d); }
uint32_t Preferences::getUInt(const char *k, uint32_t d) { return get<uint32_t>(KEY, d); }
size_t Preferences::getBytes(const char *k, void *b, size_t n) { auto it = store().find(KEY); if (it == store().end()) return 0; size_t m = it->second.size() < n ? it->second.size() : n; memcpy(b, it->second.data(), m); return m; }
size_t Preferences::getString(const char *k, char *b, size_t n) { auto it = store().find(KEY); if (it == store().end() || n == 0) return 0; size_t m = it->second.size() < n ? it->second.size() : n; memcpy(b, it->second.data(), m); b[m - 1] = 0; return strlen(b); }
#endif
bool Preferences::getBool(const char *k, bool d) { return getUChar(k, d ? 1 : 0) != 0; }
#ifdef ESP_PLATFORM
size_t Preferences::putBool(const char *k, bool v) { return putUChar(k, v ? 1 : 0); }
#endif
