/**
 * Copyright (c) 2026 Trollycat
 * Defines common function wrappers for the TEST_APP codebase.
 */

#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <cstring>
#include <ctime>
#include <cstdlib>

#if defined(_WIN32)
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#else
#include <unistd.h>
#endif

template <typename T>
TEST_APP_ALWAYS_INLINE VOID print(IN T value) {
    std::cout << value;
}

template <typename T, typename... Args>
TEST_APP_ALWAYS_INLINE VOID print(IN T first, IN Args... args) {
    std::cout << first;
    print(args...);
}

template <typename... Args>
TEST_APP_ALWAYS_INLINE VOID println(IN Args... args) {
    print(args...);
    std::cout << std::endl;
}

TEST_APP_ALWAYS_INLINE VOID println() {
    std::cout << std::endl;
}

template <typename... Args>
TEST_APP_ALWAYS_INLINE VOID printf_t(IN CONST CHAR* format, IN Args... args) {
    std::printf(format, args...);
}

TEST_APP_ALWAYS_INLINE VOID flush() {
    std::cout.flush();
}

TEST_APP_ALWAYS_INLINE VOID clear_screen() {
#if defined(_WIN32)
    std::system("cls");
#else
    std::system("clear");
#endif
}

TEST_APP_ALWAYS_INLINE VOID wait_for_enter() {
    std::cin.get();
}

template <typename T>
TEST_APP_ALWAYS_INLINE BOOL is_null(IN T* ptr) {
    return (ptr == NULL) ? TRUE : FALSE;
}

template <typename T>
TEST_APP_ALWAYS_INLINE std::string to_string_t(IN T value) {
    return std::to_string(value);
}

TEST_APP_ALWAYS_INLINE std::string to_string_t(IN CONST CHAR* value) {
    return std::string(value);
}

TEST_APP_ALWAYS_INLINE BOOL string_equals(IN std::string a, IN std::string b) {
    return a == b ? TRUE : FALSE;
}

TEST_APP_ALWAYS_INLINE BOOL string_empty(IN std::string s) {
    return s.empty() ? TRUE : FALSE;
}

TEST_APP_ALWAYS_INLINE SIZE_T string_length(IN std::string s) {
    return s.length();
}

TEST_APP_ALWAYS_INLINE VOID exit_program(IN INT code) {
    std::exit(code);
}

TEST_APP_ALWAYS_INLINE VOID abort_program() {
    std::abort();
}

template <typename T>
TEST_APP_ALWAYS_INLINE T clamp_t(IN T value, IN T min, IN T max) {
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

template <typename T>
TEST_APP_ALWAYS_INLINE T min_t(IN T a, IN T b) {
    return (a < b) ? a : b;
}

template <typename T>
TEST_APP_ALWAYS_INLINE T max_t(IN T a, IN T b) {
    return (a > b) ? a : b;
}

TEST_APP_ALWAYS_INLINE DOUBLE to_double(IN CONST CHAR* s) {
    return std::stod(s);
}

TEST_APP_ALWAYS_INLINE INT to_int(IN CONST CHAR* s) {
    return std::stoi(s);
}

TEST_APP_ALWAYS_INLINE VOID mem_set(IN VOID* ptr, IN INT value, IN SIZE_T num) {
    if (is_null(ptr) || num == 0) return;
    std::memset(ptr, value, num);
}

TEST_APP_ALWAYS_INLINE VOID mem_copy(IN VOID* dest, IN CONST VOID* src, IN SIZE_T num) {
    if (is_null(dest) || is_null(src) || num == 0) return;
    if (dest == src) return;
    std::memmove(dest, src, num);
}

TEST_APP_ALWAYS_INLINE INT mem_compare(IN CONST VOID* ptr1, IN CONST VOID* ptr2, IN SIZE_T num) {
    if (is_null(ptr1) || is_null(ptr2) || num == 0) return 0;
    if (ptr1 == ptr2) return 0;
    return std::memcmp(ptr1, ptr2, num);
}

template <typename T>
TEST_APP_ALWAYS_INLINE VOID swap_t(INOUT T& a, INOUT T& b) {
    T temp = a;
    a = b;
    b = temp;
}

TEST_APP_ALWAYS_INLINE VOID sleep_ms(IN INT ms) {
#if defined(_WIN32)
    Sleep(ms);
#else
    usleep(ms * 1000);
#endif
}

template <typename T>
TEST_APP_ALWAYS_INLINE VOID safe_delete(INOUT T*& ptr) {
    if (ptr != NULL) {
        delete ptr;
        ptr = NULL;
    }
}

template <typename T>
TEST_APP_ALWAYS_INLINE VOID safe_delete_array(INOUT T*& ptr) {
    if (ptr != NULL) {
        delete[] ptr;
        ptr = NULL;
    }
}

TEST_APP_ALWAYS_INLINE CONST CHAR* get_env(IN CONST CHAR* name) {
    return std::getenv(name);
}

TEST_APP_ALWAYS_INLINE INT set_env(IN CONST CHAR* name, IN CONST CHAR* value, IN INT overwrite) {
#if defined(_WIN32)
    if (!overwrite && std::getenv(name) != NULL) return 0;
    return _putenv_s(name, value) == 0 ? 0 : -1;
#else
    return setenv(name, value, overwrite);
#endif
}

template <typename T>
TEST_APP_ALWAYS_INLINE VOID vector_add(INOUT std::vector<T>& v, IN T value) {
    v.push_back(value);
}

template <typename T>
TEST_APP_ALWAYS_INLINE VOID vector_clear(INOUT std::vector<T>& v) {
    v.clear();
}

template <typename T>
TEST_APP_ALWAYS_INLINE SIZE_T vector_size(IN CONST std::vector<T>& v) {
    return v.size();
}

TEST_APP_ALWAYS_INLINE DOUBLE get_time_seconds() {
    return (DOUBLE)std::time(NULL);
}

TEST_APP_ALWAYS_INLINE VOID log_info(IN CONST CHAR* msg) {
    print("[INFO] ");
    println(msg);
}

TEST_APP_ALWAYS_INLINE VOID log_warning(IN CONST CHAR* msg) {
    print("[WARN] ");
    println(msg);
}

TEST_APP_ALWAYS_INLINE VOID log_error(IN CONST CHAR* msg) {
    print("[ERROR] ");
    println(msg);
}