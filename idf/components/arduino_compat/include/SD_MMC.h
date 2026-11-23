// SPDX-License-Identifier: CC-BY-NC-SA-4.0
#pragma once
#include "FS.h"
class SDMMCFS : public fs::FS {
public:
    bool setPins(int, int, int) { return true; }   // the Fake Pod's SDMMC pins are fixed in fp_pins.h
    bool begin(const char *mount = "/sdcard", bool mode1bit = false, bool format = false);
    uint64_t cardSize();
    uint64_t totalBytes();
    uint64_t usedBytes();
};
extern SDMMCFS SD_MMC;
