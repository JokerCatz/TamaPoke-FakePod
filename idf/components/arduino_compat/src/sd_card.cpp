// SPDX-License-Identifier: CC-BY-NC-SA-4.0
// SD_MMC.begin: the Fake Pod's TF card, SDMMC 4-bit (pins from fakepod_bsp/fp_pins.h), mounted as FAT at `mount`. On the PC the "card" is the directory in $TAMAPOKE_SD.
#include "SD_MMC.h"
#include <stdlib.h>
#ifdef ESP_PLATFORM
#include "esp_vfs_fat.h"
#include "sdmmc_cmd.h"
#include "driver/sdmmc_host.h"
#include "esp_log.h"
#include "fp_pins.h"
static sdmmc_card_t *s_card;
bool SDMMCFS::begin(const char *mount, bool mode1bit, bool /*format: ignored on purpose*/)
{
    sdmmc_host_t host = SDMMC_HOST_DEFAULT();
    sdmmc_slot_config_t slot = SDMMC_SLOT_CONFIG_DEFAULT();
    slot.width = mode1bit ? 1 : 4;
    slot.clk = (gpio_num_t)FP_PIN_SD_CLK; slot.cmd = (gpio_num_t)FP_PIN_SD_CMD;
    slot.d0 = (gpio_num_t)FP_PIN_SD_D0; slot.d1 = (gpio_num_t)FP_PIN_SD_D1; slot.d2 = (gpio_num_t)FP_PIN_SD_D2; slot.d3 = (gpio_num_t)FP_PIN_SD_D3;
    esp_vfs_fat_sdmmc_mount_config_t mc = {};
    mc.format_if_mount_failed = false;   /* upstream asks to format an unmountable card; never do that here: it may be a good exFAT card this FatFs build cannot read */ mc.max_files = 6; mc.allocation_unit_size = 16 * 1024;
    if (esp_vfs_fat_sdmmc_mount(mount, &host, &slot, &mc, &s_card) != ESP_OK) return false;
    mount_(mount);
    return true;
}
uint64_t SDMMCFS::cardSize() { return s_card ? (uint64_t)s_card->csd.capacity * s_card->csd.sector_size : 0; }
#else
bool SDMMCFS::begin(const char *, bool, bool) { const char *d = getenv("TAMAPOKE_SD"); if (!d) return false; mount_(d); return true; }
uint64_t SDMMCFS::cardSize() { return 0; }
#endif
uint64_t SDMMCFS::totalBytes() { return cardSize(); }
uint64_t SDMMCFS::usedBytes() { return 0; }
