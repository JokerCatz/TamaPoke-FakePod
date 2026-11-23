// SPDX-License-Identifier: CC-BY-NC-SA-4.0
// U8g2 is only used for the Japanese / Korean fonts (applyLangFont); those are not ported. The symbols exist so the upstream code compiles.
#pragma once
#include <stdint.h>
extern const uint8_t u8g2_font_unifont_t_japanese3[];
extern const uint8_t u8g2_font_unifont_t_korean2[];
// our own: the Traditional Chinese subset of GNU Unifont 16 (gfx_compat). Selected like the others, with setFont().
extern const uint8_t fp_font_zh_unifont16[];
