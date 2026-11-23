// SPDX-License-Identifier: CC-BY-NC-SA-4.0
// Preferences on top of NVS (same method names / defaults as arduino-esp32's, only the subset TamaPoke uses). NVS must be initialised (nvs_flash_init) first.
#pragma once
#include <stdint.h>
#include <stddef.h>
#include "nvs.h"

class Preferences {
public:
    bool begin(const char *ns, bool readOnly = false);
    void end();
    bool clear();
    bool isKey(const char *key);
    size_t putChar(const char *k, int8_t v);
    int8_t getChar(const char *k, int8_t def = 0);
    size_t putUChar(const char *k, uint8_t v);
    size_t putBool(const char *k, bool v);
    size_t putShort(const char *k, int16_t v);
    size_t putUShort(const char *k, uint16_t v);
    size_t putUInt(const char *k, uint32_t v);
    size_t putBytes(const char *k, const void *buf, size_t len);
    size_t putString(const char *k, const char *v);
    uint8_t getUChar(const char *k, uint8_t def = 0);
    bool getBool(const char *k, bool def = false);
    int16_t getShort(const char *k, int16_t def = 0);
    uint16_t getUShort(const char *k, uint16_t def = 0);
    uint32_t getUInt(const char *k, uint32_t def = 0);
    size_t getBytes(const char *k, void *buf, size_t len);
    size_t getString(const char *k, char *buf, size_t len);
private:
    nvs_handle_t h_ = 0;
    bool open_ = false, ro_ = false;
};
