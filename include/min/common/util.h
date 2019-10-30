/*
 * Copyright (C) 2018-2019, neverfelly <neverfelly@gmail.com>
 *
 * This software is licensed under the terms of the MIT License.
 * See COPYING for further information.
 */

#ifndef MIN_INCLUDE_MIN_COMMON_UTIL_H_
#define MIN_INCLUDE_MIN_COMMON_UTIL_H_

#include <iostream>
#include <algorithm>
#include <vector>
#include <memory>
#include <limits>
#include <filesystem>
#include <thread>
#include <chrono>
#include <type_traits>
#include <fstream>
#include <cstddef>
#include <sstream>
#include "fmt/format.h"
#include "log.h"

//******************************************************************************
//                                 System State
//******************************************************************************

// Reference:
// https://blog.kowalczyk.info/article/j/guide-to-predefined-macros-in-c-compilers-gcc-clang-msvc-etc..html

// Platforms

// Windows
#if defined(_WIN64)
#define MIN_PLATFORM_WINDOWS
#endif

#if defined(_WIN32) && !defined(_WIN64)
static_assert(false, "32-bit Windows systems are not supported")
#endif

// Linux
#if defined(__linux__)
#define MIN_PLATFORM_LINUX
#endif

// OSX
#if defined(__APPLE__)
#define MIN_PLATFORM_OSX
#endif

#if (defined(MIN_PLATFORM_LINUX) || defined(MIN_PLATFORM_OSX))
#define MIN_PLATFORM_UNIX
#endif

// Compilers

// MSVC
#if defined(_MSC_VER)
#define MIN_COMPILER_MSVC
#endif

// MINGW
#if defined(__MINGW64__)
#define MIN_COMPILER_MINGW
#endif

// gcc
#if defined(__GNUC__)
#define MIN_COMPILER__GCC
#endif

// clang
#if defined(__clang__)
#define MIN_COMPILER_CLANG
#endif

#if defined(MIN_COMPILER_MSVC)
#define MIN_ALIGNED(x) __declspec(align(x))
#else
#define MIN_ALIGNED(x) __attribute__((aligned(x)))
#endif

#if __cplusplus >= 201703L
#define MIN_CPP17
#else
#if defined(MIN_COMPILER_CLANG)
static_assert(false, "For clang compilers, use -std=c++17");
#endif
static_assert(__cplusplus >= 201402L, "C++14 required.");
#define MIN_CPP14
#endif

// Do not disable assert...
#ifdef NDEBUG
#undef NDEBUG
#endif

#ifndef _WIN64
#define sscanf_s sscanf
#define sprintf_s sprintf
#endif

#define MIN_ASSERT(x, ...) { if(!(x)) { MIN_ERROR("Assertion Failed: {0}", __VA_ARGS__); }}
#define MIN_CORE_ASSERT(x, ...) { if(!(x)) { MIN_ERROR("Assertion Failed: {0}", __VA_ARGS__); }}

#define MIN_NAMESPACE_BEGIN namespace min {
#define MIN_NAMESPACE_END }

MIN_NAMESPACE_BEGIN

//******************************************************************************
//                                 System State
//******************************************************************************

namespace fs = std::filesystem;

//******************************************************************************
//                                 Types
//******************************************************************************

using uchar = unsigned char;

using int8 = int8_t;
using uint8 = uint8_t;

using int16 = int16_t;
using uint16 = uint16_t;

using int32 = int32_t;
using uint32 = uint32_t;
using uint = unsigned int;

using int64 = int64_t;
using uint64 = uint64_t;

#ifdef _WIN64
#define MIN_FORCE_INLINE __forceinline
#else
#define MIN_FORCE_INLINE inline __attribute__((always_inline))
#endif

using float32 = float;
using float64 = double;

#ifdef MIN_USE_DOUBLE
using Float = float64;
#else
using Float = float32;
#endif

// Float literal for both float32/64
// (Learned from https://github.com/hi2p-perim/lightmetrica-v2)
Float constexpr operator "" _f(long double v) {
  return Float(v);
}
Float constexpr operator "" _f(unsigned long long v) {
  return Float(v);
}

float32 constexpr operator "" _f32(long double v) {
  return float32(v);
}
float32 constexpr operator "" _f32(unsigned long long v) {
  return float32(v);
}

float32 constexpr operator "" _fs(long double v) {
  return float32(v);
}
float32 constexpr operator "" _fs(unsigned long long v) {
  return float32(v);
}

float64 constexpr operator "" _f64(long double v) {
  return float64(v);
}
float64 constexpr operator "" _f64(unsigned long long v) {
  return float64(v);
}

float64 constexpr operator "" _fd(long double v) {
  return float64(v);
}
float64 constexpr operator "" _fd(unsigned long long v) {
  return float64(v);
}

MIN_NAMESPACE_END

//******************************************************************************
//                               Constants
//******************************************************************************

MIN_NAMESPACE_BEGIN


MIN_NAMESPACE_END

MIN_NAMESPACE_BEGIN

//******************************************************************************
//                               String Utils
//******************************************************************************


inline std::vector<std::string> split_string(const std::string &s,
                                             const std::string &seperators) {
  std::vector<std::string> ret;
  bool is_seperator[256] = {false};
  for (auto &ch : seperators) {
    is_seperator[(unsigned int) ch] = true;
  }
  int begin = 0;
  for (int i = 0; i <= (int) s.size(); i++) {
    if (is_seperator[(uint8) s[i]] || i==(int) s.size()) {
      ret.emplace_back(std::string(s.begin() + begin, s.begin() + i));
      begin = i + 1;
    }
  }
  return ret;
}

MIN_NAMESPACE_END

//******************************************************************************
//                                   Misc.
//******************************************************************************

MIN_NAMESPACE_BEGIN

inline bool running_on_windows() {
#if defined(MIN_PLATFORM_WINDOWS)
  return true;
#else
  return false;
#endif
}

MIN_NAMESPACE_END

#endif //MIN_INCLUDE_MIN_COMMON_UTIL_H_
