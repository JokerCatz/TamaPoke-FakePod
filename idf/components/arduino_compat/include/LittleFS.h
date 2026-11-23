// SPDX-License-Identifier: CC-BY-NC-SA-4.0
// Only the 1.75C (sprites in flash) uses LittleFS; kept as an empty type so the #if-ed code stays parseable.
#pragma once
#include "FS.h"
class LittleFSFS : public fs::FS {
public:
    bool begin(bool = false, const char * = "/littlefs", uint8_t = 10, const char * = "storage") { return false; }
    uint64_t totalBytes() { return 0; }
    uint64_t usedBytes() { return 0; }
    bool mkdir(const char *) { return false; }
};
extern LittleFSFS LittleFS;
