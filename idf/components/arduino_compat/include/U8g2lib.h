// SPDX-License-Identifier: CC-BY-NC-SA-4.0
// U8g2 is only used for the Japanese / Korean fonts (applyLangFont); those are not ported. The symbols exist so the upstream code compiles.
#pragma once
#include <stdint.h>
// our own: the Traditional Chinese subset of GNU Unifont 16 (gfx_compat). Selected like the others, with setFont().
extern const uint8_t fp_font_zh_tc[];   // Traditional Chinese (body text: Noto Sans CJK TC 22 px anti-aliased; bigger text: Unifont scaled)
extern const uint8_t fp_font_zh_sc[];   // Simplified Chinese (same, Noto Sans CJK SC)
