// SPDX-License-Identifier: BSD-3-Clause
// Drop-in subset of Arduino_GFX's Arduino_Canvas for the TamaPoke sources, drawing into the Fake Pod's PSRAM frame buffer (fakepod_bsp/fp_display).
// Algorithms (Bresenham line, midpoint ellipse/circle/round-rect helpers, triangle fill, classic 5x7 text) follow Arduino_GFX (moononournation), itself a rewrite of
// Adafruit-GFX (c) 2012 Adafruit Industries, BSD: see LICENSE-Adafruit-BSD.txt. Only the calls TamaPoke makes are provided.
#pragma once
#include <stdint.h>
#include <stddef.h>

#define RGB565_BLACK 0x0000
#define RGB565_WHITE 0xFFFF
#define RGB565(r, g, b) ((((r) & 0xF8) << 8) | (((g) & 0xFC) << 3) | ((b) >> 3))

// The bus / panel objects the sketch constructs. The Fake Pod's CO5300 is driven by fakepod_bsp, so these only carry the few calls the sketch makes.
struct Arduino_DataBus {};
struct Arduino_ESP32QSPI : Arduino_DataBus { template <class... A> Arduino_ESP32QSPI(A...) {} };
struct Arduino_CO5300 {
    template <class... A> Arduino_CO5300(A...) {}
    void setBrightness(uint8_t v);       // CO5300 command 0x51
    void displayOn();                    // soft wake: SLEEP OUT + init table + frame
    void displayOff();                   // brightness 0, DISPOFF, SLEEP IN
};

class Arduino_Canvas {
public:
    Arduino_Canvas(int16_t w, int16_t h, void * /*output panel: the BSP owns it*/ = nullptr);
    bool begin(int32_t speed = 0);       // brings the panel up (fp_display_init); `speed` is ignored (the QSPI clock is the BSP's)
    void flush();                         // push the frame to the panel (only while the panel is on)
    uint16_t *getFramebuffer() { return fb_; }
    int16_t width() const { return w_; }
    int16_t height() const { return h_; }

    void writePixel(int16_t x, int16_t y, uint16_t c);
    void writeFastHLine(int16_t x, int16_t y, int16_t w, uint16_t c);
    void writeFastVLine(int16_t x, int16_t y, int16_t h, uint16_t c);
    void writeFillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t c);
    void fillScreen(uint16_t c) { writeFillRect(0, 0, w_, h_, c); }
    void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t c) { writeFillRect(x, y, w, h, c); }
    void drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t c);
    void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t c);
    void drawCircle(int16_t x, int16_t y, int16_t r, uint16_t c) { ellipse(x, y, r, r, 0xf, c); }
    void fillCircle(int16_t x, int16_t y, int16_t r, uint16_t c) { fillEllipse(x, y, r, r, 3, 0, c); }
    void drawRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t c);
    void fillRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t c);
    void fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t c);

    // text: the classic 5x7 CP437 font, cell 6x8, scaled by the text size; a one-argument setTextColor is transparent (as in Arduino_GFX)
    void setCursor(int16_t x, int16_t y) { cx_ = x; cy_ = y; }
    int16_t getCursorX() const { return cx_; }
    int16_t getCursorY() const { return cy_; }
    void setTextColor(uint16_t c) { fg_ = bg_ = c; }
    void setTextColor(uint16_t c, uint16_t bg) { fg_ = c; bg_ = bg; }
    void setTextSize(uint8_t s) { sx_ = sy_ = s ? s : 1; }
    void setTextSize(uint8_t sx, uint8_t sy) { sx_ = sx ? sx : 1; sy_ = sy ? sy : 1; }
    void setTextWrap(bool w) { wrap_ = w; }
    void setFont() { font_ = nullptr; }                 // back to the classic 5x7
    void setFont(const uint8_t *f) { font_ = f; }       // a CJK font: fp_font_zh_unifont16 is the only one with glyphs; the Japanese / Korean ones draw blanks
    void setUTF8Print(bool b) { utf8_ = b; pend_ = 0; need_ = 0; }
    void getTextBounds(const char *s, int16_t x, int16_t y, int16_t *x1, int16_t *y1, uint16_t *w, uint16_t *h);
    size_t write(uint8_t c);
    size_t print(char c) { return write((uint8_t)c); }
    size_t print(const char *s) { size_t n = 0; while (s && *s) n += write((uint8_t)*s++); return n; }

private:
    void ellipse(int32_t x, int32_t y, int32_t rx, int32_t ry, uint8_t corners, uint16_t c);
    void fillEllipse(int32_t x, int32_t y, int32_t rx, int32_t ry, uint8_t corners, int16_t delta, uint16_t c);
    void drawChar(int16_t x, int16_t y, uint8_t ch);
    bool cjk() const { return font_ != nullptr && utf8_; }
    void writeCjk(uint8_t b);
    void cjkBounds(const char *s, int16_t x, int16_t y, int16_t *x1, int16_t *y1, uint16_t *w, uint16_t *h);
    void charBounds(uint8_t ch, int16_t *x, int16_t *y, int16_t *minx, int16_t *miny, int16_t *maxx, int16_t *maxy);
    int16_t w_, h_, cx_ = 0, cy_ = 0;
    uint16_t fg_ = 0xFFFF, bg_ = 0xFFFF;
    uint8_t sx_ = 1, sy_ = 1;
    bool wrap_ = true, utf8_ = false;
    const uint8_t *font_ = nullptr;
    uint32_t pend_ = 0; int need_ = 0;     // UTF-8 decoder state
    uint16_t *fb_ = nullptr;
};
