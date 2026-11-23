// SPDX-License-Identifier: CC-BY-NC-SA-4.0
// fs::FS / File over stdio (POSIX), the subset sdmon.cpp uses. Paths are relative to the mount point of the volume (FS::mount).
#pragma once
#include <stdint.h>
#include <stdio.h>
#include <stddef.h>
#include <string>
#include <dirent.h>
#define FILE_READ "r"
#define FILE_WRITE "w"
namespace fs { class FS; }
class File {
public:
    File() {}
    explicit File(FILE *f) : f_(f) {}
    File(DIR *d, const std::string &path) : d_(d), path_(path) {}
    File(const File &) = delete;
    File &operator=(const File &) = delete;
    File(File &&o) noexcept : f_(o.f_), d_(o.d_), path_(std::move(o.path_)), name_(std::move(o.name_)) { o.f_ = nullptr; o.d_ = nullptr; }
    File &operator=(File &&o) noexcept { if (this != &o) { close(); f_ = o.f_; d_ = o.d_; path_ = std::move(o.path_); name_ = std::move(o.name_); o.f_ = nullptr; o.d_ = nullptr; } return *this; }
    ~File() { close(); }
    explicit operator bool() const { return f_ != nullptr || d_ != nullptr; }
    File openNextFile();                 // directory listing
    const char *name() const { return name_.c_str(); }
    size_t size() const;
    size_t read(uint8_t *buf, size_t n) { return f_ ? fread(buf, 1, n, f_) : 0; }
    size_t write(const uint8_t *buf, size_t n) { return f_ ? fwrite(buf, 1, n, f_) : 0; }
    void close() { if (f_) { fclose(f_); f_ = nullptr; } if (d_) { closedir(d_); d_ = nullptr; } }
private:
    FILE *f_ = nullptr;
    DIR *d_ = nullptr;
    std::string path_, name_;
    friend class fs::FS;
};
namespace fs {
class FS {
public:
    void mount_(const char *root) { root_ = root; }
    File open(const std::string &path, const char *mode = FILE_READ);
    bool exists(const std::string &path);
    bool remove(const std::string &path);
    bool mkdir(const std::string &path);
    const std::string &root() const { return root_; }
private:
    std::string root_;
};
}
