# Notices for the Fake Pod Nano Pro port

This repository is a port of **TamaPoke** by Quique Tortosa and contributors (https://github.com/socquique/TamaPoke), kept connected to it through the `upstream` remote.

| What | License / source |
|---|---|
| TamaPoke game code and everything derived from it (including the files in `idf/main`, `idf/components/arduino_compat`, `gfx_compat`, `tamapoke_core`, `help_text.h`, `i18n.cpp` changes) | **CC BY-NC-SA 4.0** — attribution, non-commercial, share-alike. See `LICENSE`. |
| Pokémon names, designs, sprites | © Nintendo / Game Freak / The Pokémon Company. Animated sprites: PMD SpriteCollab (https://github.com/PMDCollab/SpriteCollab), **CC BY-NC 4.0**, per-artist credit in its `tracker.json`. For personal, non-commercial use only. See `CREDITS.md`. |
| Pokémon names in Traditional / Simplified Chinese | PokéAPI (https://pokeapi.co) `zh-Hant` / `zh-Hans` species names, fetched by `tools/gen_names.py` |
| Chinese body text (22 px anti-aliased bitmaps, subset, rasterised from Noto Sans CJK TC / SC) | **SIL OFL 1.1**, (c) Adobe / Google and the Noto Project Authors. `idf/components/gfx_compat/LICENSE-NotoSansCJK-OFL.txt`. "Noto" is a trademark of Google LLC. |
| Chinese larger text (16 px bitmaps, subset, scaled) | **GNU Unifont**, SIL OFL 1.1 (and GPL-2.0-or-later with the font embedding exception). `idf/components/gfx_compat/LICENSE-Unifont.txt` |
| Drawing routines (lines, circles, round rectangles, triangles, 5x7 text) | follow Arduino_GFX (moononournation) / Adafruit-GFX, **BSD**. `idf/components/gfx_compat/LICENSE-Adafruit-BSD.txt` |
| `idf/components/fakepod_bsp`, `idf/tools/make_fatfs_exfat.sh` | **LGPL-2.1-or-later**, taken from the author's JukeDial project. The CO5300 initialisation values come from NightPlayer (c) 2026 ZYFDroid, **MIT** (https://gitee.com/ZYFDroid/night-player-fake-pod-nano). |
| Board design | Fake Pod Nano by ZYFDroid (open hardware) |

## The sprites zip (`tamapoke-fakepod-VERSION-sprites.zip`)

**These files are not made by this project.** They are the sprite pack that ships with the upstream TamaPoke repository (https://github.com/socquique/TamaPoke, folder `tools/sdcard/mons`), packed by its `tools/pack_pmd.py` from the animated sprites of **PMD SpriteCollab** (https://github.com/PMDCollab/SpriteCollab, CC BY-NC 4.0; per-artist credit in its `tracker.json`). The pictures are of Pokémon characters, © Nintendo / Game Freak / The Pokémon Company. They are included here, unchanged, only for personal, non-commercial use, as upstream does. If you republish this project and prefer not to host them, delete the zip and let users build the pack with upstream's `tools/pack_*.py`.

Not affiliated with or endorsed by Nintendo, Game Freak, The Pokémon Company or Waveshare.
