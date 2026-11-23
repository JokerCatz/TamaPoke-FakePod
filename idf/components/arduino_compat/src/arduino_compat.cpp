// SPDX-License-Identifier: CC-BY-NC-SA-4.0
#include "Arduino.h"
#include "Wire.h"
#include "FS.h"
#include "SD_MMC.h"
#include "LittleFS.h"
#include "U8g2lib.h"   /* declares the font symbols extern: a const array otherwise has internal linkage in C++ */
#include <stdarg.h>
#include <sys/stat.h>
#include <unistd.h>

SerialShim Serial;
#ifdef ESP_PLATFORM
#include "driver/usb_serial_jtag.h"
#include "driver/usb_serial_jtag_vfs.h"
static bool s_serial_up = false;
static uint8_t s_rx[512]; static size_t s_rx_n = 0, s_rx_i = 0;
void SerialShim::begin(unsigned long)
{
    if (s_serial_up) return;
    usb_serial_jtag_driver_config_t c = USB_SERIAL_JTAG_DRIVER_CONFIG_DEFAULT();
    c.rx_buffer_size = 8192;
    if (usb_serial_jtag_driver_install(&c) == ESP_OK) { usb_serial_jtag_vfs_use_driver(); s_serial_up = true; }
}
static void rx_fill(uint32_t wait_ms)
{
    if (!s_serial_up || s_rx_i < s_rx_n) return;
    int n = usb_serial_jtag_read_bytes(s_rx, sizeof s_rx, pdMS_TO_TICKS(wait_ms));
    s_rx_i = 0; s_rx_n = n > 0 ? (size_t)n : 0;
}
int SerialShim::available() { rx_fill(0); return (int)(s_rx_n - s_rx_i); }
size_t SerialShim::readBytes(uint8_t *buf, size_t n)
{
    size_t got = 0; const uint32_t t0 = millis();
    while (got < n && millis() - t0 < timeout_ms) {
        rx_fill(20);
        while (got < n && s_rx_i < s_rx_n) buf[got++] = s_rx[s_rx_i++];
    }
    return got;
}
String SerialShim::readStringUntil(char term)
{
    String out; const uint32_t t0 = millis();
    while (millis() - t0 < timeout_ms) {
        rx_fill(20);
        while (s_rx_i < s_rx_n) { char ch = (char)s_rx[s_rx_i++]; if (ch == term) return out; out += String(std::string(1, ch)); }
    }
    return out;
}
#else
void SerialShim::begin(unsigned long) {}
int SerialShim::available() { return 0; }
size_t SerialShim::readBytes(uint8_t *, size_t) { return 0; }
String SerialShim::readStringUntil(char) { return String(); }
#endif
EspShim ESP;
TwoWire Wire;
LittleFSFS LittleFS;
SDMMCFS SD_MMC;
const uint8_t u8g2_font_unifont_t_japanese3[1] = {0};
const uint8_t u8g2_font_unifont_t_korean2[1] = {0};

int SerialShim::printf(const char *fmt, ...) { va_list a; va_start(a, fmt); int n = vprintf(fmt, a); va_end(a); return n; }
long random(long hi) { return hi <= 0 ? 0 : (long)(hw_random32() % (uint32_t)hi); }
long random(long lo, long hi) { return hi <= lo ? lo : lo + random(hi - lo); }

// ---- GPIO ----
#ifdef ESP_PLATFORM
void pinMode(int pin, int mode)
{
    gpio_config_t c = {}; c.pin_bit_mask = 1ULL << pin;
    c.mode = (mode == OUTPUT) ? GPIO_MODE_OUTPUT : GPIO_MODE_INPUT;
    c.pull_up_en = (mode == INPUT_PULLUP) ? GPIO_PULLUP_ENABLE : GPIO_PULLUP_DISABLE;
    gpio_config(&c);
}
int digitalRead(int pin) { return gpio_get_level((gpio_num_t)pin); }
void digitalWrite(int pin, int v) { gpio_set_level((gpio_num_t)pin, v); }
void attachInterrupt(int pin, void (*isr)(void), int mode)
{
    static bool svc = false;
    if (!svc) { gpio_install_isr_service(0); svc = true; }
    gpio_set_intr_type((gpio_num_t)pin, mode == FALLING ? GPIO_INTR_NEGEDGE : GPIO_INTR_POSEDGE);
    gpio_isr_handler_add((gpio_num_t)pin, (gpio_isr_t)isr, nullptr);
    gpio_intr_enable((gpio_num_t)pin);
}
void detachInterrupt(int pin) { gpio_isr_handler_remove((gpio_num_t)pin); }
#else
void pinMode(int, int) {}
int digitalRead(int) { return 1; }
void digitalWrite(int, int) {}
void attachInterrupt(int, void (*)(void), int) {}
void detachInterrupt(int) {}
#endif

// ---- files: stdio under the volume's mount point ----
size_t File::size() const
{
    if (!f_) return 0;
    long cur = ftell(f_); fseek(f_, 0, SEEK_END); long n = ftell(f_); fseek(f_, cur, SEEK_SET);
    return n < 0 ? 0 : (size_t)n;
}
namespace fs {
File FS::open(const std::string &path, const char *mode)
{
    const std::string full = root_ + path;
    struct stat st;
    if (mode[0] == 'r' && stat(full.c_str(), &st) == 0 && S_ISDIR(st.st_mode)) { DIR *d = opendir(full.c_str()); return d ? File(d, full) : File(); }
    return File(fopen(full.c_str(), mode));
}
bool FS::exists(const std::string &path) { struct stat st; return stat((root_ + path).c_str(), &st) == 0; }
bool FS::remove(const std::string &path) { return ::remove((root_ + path).c_str()) == 0; }
bool FS::mkdir(const std::string &path) { return ::mkdir((root_ + path).c_str(), 0777) == 0; }
}
File File::openNextFile()
{
    if (!d_) return File();
    while (struct dirent *e = readdir(d_)) {
        if (!strcmp(e->d_name, ".") || !strcmp(e->d_name, "..")) continue;
        File f(fopen((path_ + "/" + e->d_name).c_str(), "r"));
        f.name_ = e->d_name;
        return f;
    }
    return File();
}
