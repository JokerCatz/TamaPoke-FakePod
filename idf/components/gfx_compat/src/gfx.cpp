// SPDX-License-Identifier: BSD-3-Clause
// See include/Arduino_GFX_Library.h and LICENSE-Adafruit-BSD.txt.
#include "Arduino_GFX_Library.h"
#include "fp_display.h"
#include "glcdfont.h"
#include "U8g2lib.h"
#include <string.h>

#include <stdint.h>
#include "font_zh_unifont16.inc"
#include <stdlib.h>

static inline void swap16(int16_t &a, int16_t &b) { int16_t t = a; a = b; b = t; }
static inline int16_t diff16(int16_t a, int16_t b) { return a > b ? a - b : b - a; }

Arduino_Canvas::Arduino_Canvas(int16_t w, int16_t h, void *) : w_(w), h_(h) {}

bool Arduino_Canvas::begin(int32_t)
{
    if (fp_display_init() != ESP_OK) return false;
    fb_ = fp_display_fb();
    return fb_ != nullptr;
}

void Arduino_Canvas::flush() { if (fp_display_is_on()) fp_display_flush(); }

void Arduino_Canvas::writePixel(int16_t x, int16_t y, uint16_t c)
{
    if ((uint16_t)x < (uint16_t)w_ && (uint16_t)y < (uint16_t)h_) fb_[(int32_t)y * w_ + x] = c;
}

void Arduino_Canvas::writeFillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t c)
{
    if (w <= 0 || h <= 0) return;
    int32_t x1 = x + w, y1 = y + h;
    if (x < 0) x = 0;
    if (y < 0) y = 0;
    if (x1 > w_) x1 = w_;
    if (y1 > h_) y1 = h_;
    if (x >= x1 || y >= y1) return;
    for (int32_t yy = y; yy < y1; yy++) {
        uint16_t *p = fb_ + yy * w_ + x;
        for (int32_t xx = x; xx < x1; xx++) *p++ = c;
    }
}
void Arduino_Canvas::writeFastHLine(int16_t x, int16_t y, int16_t w, uint16_t c) { writeFillRect(x, y, w, 1, c); }
void Arduino_Canvas::writeFastVLine(int16_t x, int16_t y, int16_t h, uint16_t c) { writeFillRect(x, y, 1, h, c); }

void Arduino_Canvas::drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t c)
{
    writeFastHLine(x, y, w, c);
    writeFastHLine(x, y + h - 1, w, c);
    writeFastVLine(x, y, h, c);
    writeFastVLine(x + w - 1, y, h, c);
}

void Arduino_Canvas::drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t c)
{
    if (x0 == x1) { if (y0 > y1) swap16(y0, y1); writeFastVLine(x0, y0, y1 - y0 + 1, c); return; }
    if (y0 == y1) { if (x0 > x1) swap16(x0, x1); writeFastHLine(x0, y0, x1 - x0 + 1, c); return; }
    const bool steep = diff16(y1, y0) > diff16(x1, x0);
    if (steep) { swap16(x0, y0); swap16(x1, y1); }
    if (x0 > x1) { swap16(x0, x1); swap16(y0, y1); }
    const int16_t dx = x1 - x0, dy = diff16(y1, y0), step = (y0 < y1) ? 1 : -1;
    int16_t err = dx >> 1;
    for (; x0 <= x1; x0++) {
        if (steep) writePixel(y0, x0, c); else writePixel(x0, y0, c);
        err -= dy;
        if (err < 0) { err += dx; y0 += step; }
    }
}

// corners bit mask: 1 = upper left, 2 = upper right, 4 = lower right, 8 = lower left
void Arduino_Canvas::ellipse(int32_t x, int32_t y, int32_t rx, int32_t ry, uint8_t cn, uint16_t c)
{
    if (rx < 0 || ry < 0 || (rx == 0 && ry == 0)) return;
    if (ry == 0) { writeFastHLine(x - rx, y, (ry << 2) + 1, c); return; }
    if (rx == 0) { writeFastVLine(x, y - ry, (rx << 2) + 1, c); return; }
    int32_t xt, yt, s, i;
    const int32_t rx2 = rx * rx, ry2 = ry * ry;
    i = -1; xt = 0; yt = ry;
    s = (ry2 << 1) + rx2 * (1 - (ry << 1));
    do {
        while (s < 0) s += ry2 * ((++xt << 2) + 2);
        if (cn & 1) writeFastHLine(x - xt, y - yt, xt - i, c);
        if (cn & 2) writeFastHLine(x + i + 1, y - yt, xt - i, c);
        if (cn & 4) writeFastHLine(x + i + 1, y + yt, xt - i, c);
        if (cn & 8) writeFastHLine(x - xt, y + yt, xt - i, c);
        i = xt;
        s -= (--yt) * rx2 << 2;
    } while (ry2 * xt <= rx2 * yt);
    i = -1; yt = 0; xt = rx;
    s = (rx2 << 1) + ry2 * (1 - (rx << 1));
    do {
        while (s < 0) s += rx2 * ((++yt << 2) + 2);
        if (cn & 1) writeFastVLine(x - xt, y - yt, yt - i, c);
        if (cn & 2) writeFastVLine(x + xt, y - yt, yt - i, c);
        if (cn & 4) writeFastVLine(x + xt, y + i + 1, yt - i, c);
        if (cn & 8) writeFastVLine(x - xt, y + i + 1, yt - i, c);
        i = yt;
        s -= (--xt) * ry2 << 2;
    } while (rx2 * yt <= ry2 * xt);
}

// corners: 1 = upper half, 2 = lower half; delta widens the fill (round rects)
void Arduino_Canvas::fillEllipse(int32_t x, int32_t y, int32_t rx, int32_t ry, uint8_t cn, int16_t delta, uint16_t c)
{
    if (rx < 0 || ry < 0 || (rx == 0 && ry == 0)) return;
    if (ry == 0) { writeFastHLine(x - rx, y, (ry << 2) + 1, c); return; }
    if (rx == 0) { writeFastVLine(x, y - ry, (rx << 2) + 1, c); return; }
    int32_t xt, yt, i, s;
    const int32_t rx2 = rx * rx, ry2 = ry * ry;
    writeFastHLine(x - rx, y, (rx << 1) + 1, c);
    i = 0; yt = 0; xt = rx;
    s = (rx2 << 1) + ry2 * (1 - (rx << 1));
    do {
        while (s < 0) s += rx2 * ((++yt << 2) + 2);
        if (cn & 1) writeFillRect(x - xt, y - yt, (xt << 1) + 1 + delta, yt - i, c);
        if (cn & 2) writeFillRect(x - xt, y + i + 1, (xt << 1) + 1 + delta, yt - i, c);
        i = yt;
        s -= (--xt) * ry2 << 2;
    } while (rx2 * yt <= ry2 * xt);
    xt = 0; yt = ry;
    s = (ry2 << 1) + rx2 * (1 - (ry << 1));
    do {
        while (s < 0) s += ry2 * ((++xt << 2) + 2);
        if (cn & 1) writeFastHLine(x - xt, y - yt, (xt << 1) + 1 + delta, c);
        if (cn & 2) writeFastHLine(x - xt, y + yt, (xt << 1) + 1 + delta, c);
        s -= (--yt) * rx2 << 2;
    } while (ry2 * xt <= rx2 * yt);
}

void Arduino_Canvas::drawRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t c)
{
    const int16_t mr = ((w < h) ? w : h) / 2;
    if (r > mr) r = mr;
    writeFastHLine(x + r, y, w - 2 * r, c);
    writeFastHLine(x + r, y + h - 1, w - 2 * r, c);
    writeFastVLine(x, y + r, h - 2 * r, c);
    writeFastVLine(x + w - 1, y + r, h - 2 * r, c);
    ellipse(x + r, y + r, r, r, 1, c);
    ellipse(x + w - r - 1, y + r, r, r, 2, c);
    ellipse(x + w - r - 1, y + h - r - 1, r, r, 4, c);
    ellipse(x + r, y + h - r - 1, r, r, 8, c);
}

void Arduino_Canvas::fillRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t c)
{
    const int16_t mr = ((w < h) ? w : h) / 2;
    if (r > mr) r = mr;
    writeFillRect(x, y + r, w, h - (r << 1), c);
    fillEllipse(x + r, y + r, r, r, 1, w - 2 * r - 1, c);
    fillEllipse(x + r, y + h - r - 1, r, r, 2, w - 2 * r - 1, c);
}

void Arduino_Canvas::fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t c)
{
    int16_t a, b, y, last;
    if (y0 > y1) { swap16(y0, y1); swap16(x0, x1); }
    if (y1 > y2) { swap16(y2, y1); swap16(x2, x1); }
    if (y0 > y1) { swap16(y0, y1); swap16(x0, x1); }
    if (y0 == y2) {
        a = b = x0;
        if (x1 < a) a = x1; else if (x1 > b) b = x1;
        if (x2 < a) a = x2; else if (x2 > b) b = x2;
        writeFastHLine(a, y0, b - a + 1, c);
        return;
    }
    const int16_t dx01 = x1 - x0, dy01 = y1 - y0, dx02 = x2 - x0, dy02 = y2 - y0, dx12 = x2 - x1, dy12 = y2 - y1;
    int32_t sa = 0, sb = 0;
    last = (y1 == y2) ? y1 : y1 - 1;
    for (y = y0; y <= last; y++) {
        a = x0 + sa / dy01;
        b = x0 + sb / dy02;
        sa += dx01; sb += dx02;
        if (a > b) swap16(a, b);
        writeFastHLine(a, y, b - a + 1, c);
    }
    sa = (int32_t)dx12 * (y - y1);
    sb = (int32_t)dx02 * (y - y0);
    for (; y <= y2; y++) {
        a = x1 + sa / dy12;
        b = x0 + sb / dy02;
        sa += dx12; sb += dx02;
        if (a > b) swap16(a, b);
        writeFastHLine(a, y, b - a + 1, c);
    }
}

// ---- text: classic 5x7, cell 6x8 ----
void Arduino_Canvas::drawChar(int16_t x, int16_t y, uint8_t ch)
{
    if (x >= w_ || y >= h_ || x + 6 * sx_ - 1 < 0 || y + 8 * sy_ - 1 < 0) return;
    for (int8_t i = 0; i < 5; i++) {
        uint8_t line = font[ch * 5 + i];
        for (int8_t j = 0; j < 8; j++, line >>= 1) {
            if (line & 1) {
                if (sx_ == 1 && sy_ == 1) writePixel(x + i, y + j, fg_);
                else writeFillRect(x + i * sx_, y + j * sy_, sx_, sy_, fg_);
            } else if (bg_ != fg_) {
                if (sx_ == 1 && sy_ == 1) writePixel(x + i, y + j, bg_);
                else writeFillRect(x + i * sx_, y + j * sy_, sx_, sy_, bg_);
            }
        }
    }
    if (bg_ != fg_) writeFillRect(x + 5 * sx_, y, sx_, 8 * sy_, bg_);   // opaque text: the spacing column
}

// ---- CJK text (GNU Unifont 16 px subset): the cursor y is the BASELINE (row 14 of the 16-row cell), like U8g2 fonts in Arduino_GFX; text size scales the bitmap ----
static const ZhGlyph *zhFind(uint32_t cp)
{
    int lo = 0, hi = (int)(sizeof ZH_GLYPHS / sizeof ZH_GLYPHS[0]) - 1;
    while (lo <= hi) { int m = (lo + hi) / 2; if (ZH_GLYPHS[m].cp == cp) return &ZH_GLYPHS[m]; if (ZH_GLYPHS[m].cp < cp) lo = m + 1; else hi = m - 1; }
    return nullptr;
}
static const int ZH_BASE = 14;
// UTF-8 -> code point, one byte at a time; returns true when `cp` is complete
static bool utf8Step(uint8_t b, uint32_t &pend, int &need, uint32_t &cp)
{
    if (need == 0) {
        if (b < 0x80) { cp = b; return true; }
        if ((b & 0xE0) == 0xC0) { pend = b & 0x1F; need = 1; } else if ((b & 0xF0) == 0xE0) { pend = b & 0x0F; need = 2; } else if ((b & 0xF8) == 0xF0) { pend = b & 0x07; need = 3; }
        return false;
    }
    if ((b & 0xC0) != 0x80) { need = 0; return false; }
    pend = (pend << 6) | (b & 0x3F);
    if (--need == 0) { cp = pend; return true; }
    return false;
}
void Arduino_Canvas::writeCjk(uint8_t b)
{
    uint32_t cp;
    if (!utf8Step(b, pend_, need_, cp)) return;
    if (cp == '\n') { cx_ = 0; cy_ += sy_ * 16; return; }
    if (cp == '\r') return;
    const ZhGlyph *g = (font_ == fp_font_zh_unifont16) ? zhFind(cp) : nullptr;
    const int adv = g ? g->adv : (cp < 0x80 ? 8 : 16);
    if (wrap_ && cx_ + adv * sx_ > w_) { cx_ = 0; cy_ += sy_ * 16; }
    if (g) {
        const int top = cy_ - ZH_BASE * sy_;
        const int bpr = g->adv / 8;
        for (int r = g->y0; r <= g->y1; r++) {
            uint32_t row = 0;
            for (int k = 0; k < bpr; k++) row = (row << 8) | g->rows[r * bpr + k];
            for (int x = g->x0; x <= g->x1; x++)
                if (row >> (g->adv - 1 - x) & 1) writeFillRect(cx_ + x * sx_, top + r * sy_, sx_, sy_, fg_);
        }
    }
    cx_ += adv * sx_;
}
void Arduino_Canvas::cjkBounds(const char *s, int16_t x, int16_t y, int16_t *x1, int16_t *y1, uint16_t *w, uint16_t *h)
{
    int minx = 0x7FFF, miny = 0x7FFF, maxx = -0x7FFF, maxy = -0x7FFF;
    uint32_t pend = 0, cp; int need = 0;
    for (const uint8_t *p = (const uint8_t *)s; p && *p; p++) {
        if (!utf8Step(*p, pend, need, cp)) continue;
        if (cp == '\n') { x = 0; y += sy_ * 16; continue; }
        if (cp == '\r') continue;
        const ZhGlyph *g = (font_ == fp_font_zh_unifont16) ? zhFind(cp) : nullptr;
        const int adv = g ? g->adv : (cp < 0x80 ? 8 : 16);
        if (g && (g->x1 >= g->x0) && !(g->x0 == 0 && g->x1 == 0 && g->y0 == 0 && g->y1 == 0)) {
            const int gx0 = x + g->x0 * sx_, gx1 = x + (g->x1 + 1) * sx_ - 1;
            const int gy0 = y + (g->y0 - ZH_BASE) * sy_, gy1 = y + (g->y1 + 1 - ZH_BASE) * sy_ - 1;
            if (gx0 < minx) minx = gx0;
            if (gx1 > maxx) maxx = gx1;
            if (gy0 < miny) miny = gy0;
            if (gy1 > maxy) maxy = gy1;
        }
        x += adv * sx_;
    }
    *x1 = x; *y1 = y; *w = *h = 0;
    if (maxx >= minx) { *x1 = minx; *w = maxx - minx + 1; }
    if (maxy >= miny) { *y1 = miny; *h = maxy - miny + 1; }
}

size_t Arduino_Canvas::write(uint8_t ch)
{
    if (cjk()) { writeCjk(ch); return 1; }
    if (ch == '\n') { cx_ = 0; cy_ += sy_ * 8; }
    else if (ch != '\r') {
        if (wrap_ && (cx_ + sx_ * 6 - 1) > w_ - 1) { cx_ = 0; cy_ += sy_ * 8; }
        drawChar(cx_, cy_, ch);
        cx_ += sx_ * 6;
    }
    return 1;
}

void Arduino_Canvas::charBounds(uint8_t ch, int16_t *x, int16_t *y, int16_t *minx, int16_t *miny, int16_t *maxx, int16_t *maxy)
{
    if (ch == '\n') { *x = 0; *y += sy_ * 8; }
    else if (ch != '\r') {
        if (wrap_ && (*x + sx_ * 6 - 1) > w_ - 1) { *x = 0; *y += sy_ * 8; }
        const int16_t x2 = *x + sx_ * 6 - 1, y2 = *y + sy_ * 8 - 1;
        if (x2 > *maxx) *maxx = x2;
        if (y2 > *maxy) *maxy = y2;
        if (*x < *minx) *minx = *x;
        if (*y < *miny) *miny = *y;
        *x += sx_ * 6;
    }
}

void Arduino_Canvas::getTextBounds(const char *s, int16_t x, int16_t y, int16_t *x1, int16_t *y1, uint16_t *w, uint16_t *h)
{
    if (cjk()) { cjkBounds(s, x, y, x1, y1, w, h); return; }
    *x1 = x; *y1 = y; *w = *h = 0;
    int16_t minx = w_ - 1, miny = h_ - 1, maxx = 0, maxy = 0;
    for (uint8_t ch; s && (ch = (uint8_t)*s++);) charBounds(ch, &x, &y, &minx, &miny, &maxx, &maxy);
    if (maxx >= minx) { *x1 = minx; *w = maxx - minx + 1; }
    if (maxy >= miny) { *y1 = miny; *h = maxy - miny + 1; }
}

void Arduino_CO5300::setBrightness(uint8_t v) { fp_display_brightness(v); }
void Arduino_CO5300::displayOn() { fp_display_on(255); }
void Arduino_CO5300::displayOff() { fp_display_off(); }

const uint8_t fp_font_zh_unifont16[1] = {0};   // identity token for setFont(); the glyph data is ZH_GLYPHS
