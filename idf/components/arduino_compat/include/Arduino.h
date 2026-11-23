// SPDX-License-Identifier: CC-BY-NC-SA-4.0
// Minimal Arduino-API shim so the TamaPoke sources compile unchanged under plain ESP-IDF, and on a PC (host build, ESP_PLATFORM undefined) for layout tests.
// Only what those sources use.
#pragma once
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <algorithm>
#include <string>

#ifdef ESP_PLATFORM
#include "esp_timer.h"
#include "esp_random.h"
#include "esp_heap_caps.h"
#include "esp_system.h"
#include "esp_attr.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
static inline uint32_t millis() { return (uint32_t)(esp_timer_get_time() / 1000); }
static inline uint32_t micros() { return (uint32_t)esp_timer_get_time(); }
static inline void delay(uint32_t ms) { vTaskDelay(pdMS_TO_TICKS(ms)); }
static inline void *ps_malloc(size_t n) { return heap_caps_malloc(n, MALLOC_CAP_SPIRAM); }
static inline uint32_t hw_random32() { return esp_random(); }
#define FP_FREE_HEAP() ((uint32_t)esp_get_free_heap_size())
#define FP_MIN_FREE_HEAP() ((uint32_t)esp_get_minimum_free_heap_size())
#define FP_RESTART() esp_restart()
#else
#include <chrono>
#include <thread>
#define IRAM_ATTR
#define EXT_RAM_BSS_ATTR
typedef int gpio_num_t;
static inline uint32_t millis() { return (uint32_t)std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count(); }
static inline uint32_t micros() { return (uint32_t)std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now().time_since_epoch()).count(); }
static inline void delay(uint32_t ms) { std::this_thread::sleep_for(std::chrono::milliseconds(ms)); }
static inline void *ps_malloc(size_t n) { return malloc(n); }
static inline uint32_t hw_random32() { return (uint32_t)rand(); }
#define FP_FREE_HEAP() 0u
#define FP_MIN_FREE_HEAP() 0u
#define FP_RESTART() exit(0)
#endif

#ifndef PI
#define PI 3.1415926535897932384626433832795
#endif
#define PROGMEM
#define HIGH 1
#define LOW 0
#define INPUT 0
#define OUTPUT 1
#define INPUT_PULLUP 2
#define FALLING 2
#define RISING 1
#define digitalPinToInterrupt(p) (p)
void pinMode(int pin, int mode);
int digitalRead(int pin);
void digitalWrite(int pin, int v);
void attachInterrupt(int pin, void (*isr)(void), int mode);
void detachInterrupt(int pin);

long random(long hi);
long random(long lo, long hi);
static inline void randomSeed(unsigned long) {}
using std::min;
using std::max;
template <class T, class L, class H> static inline T constrain(T v, L lo, H hi) { return v < (T)lo ? (T)lo : v > (T)hi ? (T)hi : v; }

// Arduino String, the subset the serial protocol uses
class String : public std::string {
public:
    String() {}
    String(const char *s) : std::string(s ? s : "") {}
    String(const std::string &s) : std::string(s) {}
    const char *c_str() const { return std::string::c_str(); }
    int length() const { return (int)size(); }
    bool startsWith(const char *p) const { return rfind(p, 0) == 0; }
    int lastIndexOf(char c) const { size_t i = rfind(c); return i == npos ? -1 : (int)i; }
    int indexOf(char c) const { size_t i = find(c); return i == npos ? -1 : (int)i; }
    String substring(int from) const { return String(substr((size_t)from)); }
    String substring(int from, int to) const { return String(substr((size_t)from, (size_t)(to - from))); }
    void trim() { size_t a = find_first_not_of(" \t\r\n"); if (a == npos) { clear(); return; } size_t b = find_last_not_of(" \t\r\n"); *this = String(substr(a, b - a + 1)); }
    long toInt() const { return atol(c_str()); }
};

struct SerialShim {
    void begin(unsigned long) {}
    void setRxBufferSize(size_t) {}
    void setTxTimeoutMs(uint32_t) {}
    void setTimeout(uint32_t) {}
    int printf(const char *fmt, ...) __attribute__((format(printf, 2, 3)));
    void println(const char *s = "") { ::printf("%s\n", s); }
    void print(const char *s) { ::printf("%s", s); }
    int available() { return 0; }          // USB-CDC upload protocol: not wired yet
    String readStringUntil(char) { return String(); }
    size_t readBytes(uint8_t *, size_t) { return 0; }
};
extern SerialShim Serial;

struct EspShim {
    uint32_t getFreeHeap() { return FP_FREE_HEAP(); }
    uint32_t getMinFreeHeap() { return FP_MIN_FREE_HEAP(); }
    void restart() { FP_RESTART(); }
};
extern EspShim ESP;
