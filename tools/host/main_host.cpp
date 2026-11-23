// Host harness: runs the real TamaPoke app (setup + render) against the fake hardware and writes each screen, in each language, as a PPM. See tools/host/shots.sh.
#include <stdio.h>
#include <string.h>
#include "Arduino.h"
#include "Arduino_GFX_Library.h"
#include "fp_display.h"
#include "i18n.h"
#define private public   /* test harness only: poke the pet state directly */
#include "pet.h"
#undef private
void setup();
bool render();
extern Arduino_Canvas *gfx;
extern Pet pet;
extern bool gLangPick;
extern bool cardOpen, galleryOpen, clockOpen, gameOpen, kbOpen, screenKeyValid;
extern uint8_t cardPage, choiceKind;
extern uint32_t choiceUntil;
extern int16_t galleryDetail;
extern bool galleryDirty;
void openClock();
void applyLangFont();
void startGame();

static void shot(const char *dir, const char *lang, const char *name)
{
    screenKeyValid = false;
    render(); render();
    char path[256]; snprintf(path, sizeof path, "%s/%s_%s.ppm", dir, lang, name);
    FILE *f = fopen(path, "wb"); fprintf(f, "P6\n460 460\n255\n");
    const uint16_t *fb = fp_display_fb();
    for (int i = 0; i < 460 * 460; i++) { uint16_t p = fb[i]; fputc(((p >> 11) & 31) * 255 / 31, f); fputc(((p >> 5) & 63) * 255 / 63, f); fputc((p & 31) * 255 / 31, f); }
    fclose(f);
}
static void reset_ui() { gLangPick = false; cardOpen = galleryOpen = clockOpen = gameOpen = kbOpen = false; cardPage = 0; choiceKind = 0; galleryDetail = 0; }

int main(int argc, char **argv)
{
    const char *dir = argc > 1 ? argv[1] : ".";
    setup();
    pet.starterPick = false;
    pet.speciesId = 25; pet.ageMinutes = 60 * 30; pet.streak = 5; pet.bestStreak = 9; pet.bond = 120; pet.medals = 0x2F; pet.totalMedals = 12;
    strcpy(pet.nick, "");
    static const struct { Lang l; const char *tag; } L[] = { {LANG_EN, "en"}, {LANG_DE, "de"}, {LANG_ES, "es"}, {LANG_JA, "ja"}, {LANG_ZH, "zh"}, {LANG_ZHS, "zhs"} };
    for (auto &x : L) {
        setLang(x.l); applyLangFont();
        reset_ui(); shot(dir, x.tag, "main");
        reset_ui(); cardOpen = true; for (int p = 0; p < 4; p++) { cardPage = p; char n[16]; snprintf(n, sizeof n, "card%d", p); shot(dir, x.tag, n); }
        reset_ui(); galleryOpen = true; galleryDirty = true; shot(dir, x.tag, "gallery");
        reset_ui(); openClock(); shot(dir, x.tag, "clock");
        reset_ui(); startGame(); shot(dir, x.tag, "game");
        reset_ui(); pet.starterPick = true; shot(dir, x.tag, "starter"); pet.starterPick = false;
    }
    gLangPick = true; setLang(LANG_EN); applyLangFont(); shot(dir, "en", "langpick"); gLangPick = false;
    printf("done\n");
    return 0;
}
