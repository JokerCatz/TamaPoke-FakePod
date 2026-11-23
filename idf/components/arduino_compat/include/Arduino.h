// SPDX-License-Identifier: CC-BY-NC-SA-4.0
// Minimal Arduino-API shim so the portable upstream TamaPoke sources compile unchanged under plain ESP-IDF.
// Only what those sources use: millis, micros, delay, random, min/max/constrain, Serial.printf/println, PROGMEM.
#pragma once
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>
#include "esp_timer.h"
#include "esp_random.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define PROGMEM
#define HIGH 1
#define LOW 0
#define INPUT 0
#define OUTPUT 1
#define INPUT_PULLUP 2

static inline uint32_t millis() { return (uint32_t)(esp_timer_get_time() / 1000); }
static inline uint32_t micros() { return (uint32_t)esp_timer_get_time(); }
static inline void delay(uint32_t ms) { vTaskDelay(pdMS_TO_TICKS(ms)); }
long random(long hi);
long random(long lo, long hi);
static inline void randomSeed(unsigned long) {}   // esp_random() is hardware-seeded

using std::min;
using std::max;
template <class T, class L, class H> static inline T constrain(T v, L lo, H hi) { return v < (T)lo ? (T)lo : v > (T)hi ? (T)hi : v; }

struct SerialShim {
    void begin(unsigned long) {}
    int printf(const char *fmt, ...) __attribute__((format(printf, 2, 3)));
    void println(const char *s = "") { ::printf("%s\n", s); }
    void print(const char *s) { ::printf("%s", s); }
};
extern SerialShim Serial;
