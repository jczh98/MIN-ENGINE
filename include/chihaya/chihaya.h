/*
 * Copyright (C) 2018-2019, neverfelly <neverfelly@gmail.com>
 *
 * This software is licensed under the terms of the MIT License.
 * See COPYING for further information.
 */

#ifndef CHIHAYA_INCLUDE_CHIHAYA_CHIHAYA_H_
#define CHIHAYA_INCLUDE_CHIHAYA_CHIHAYA_H_

#include <iostream>
#include <cmath>
#include <limits>
#include <chrono>
#include <algorithm>
#include <string>
#include <vector>
#include <cstdio>
#include <cstdlib>

#include <fmt/format.h>
#include <glog/logging.h>

//******************************************************************************
//                                 System State
//******************************************************************************

// Reference:
// https://blog.kowalczyk.info/article/j/guide-to-predefined-macros-in-c-compilers-gcc-clang-msvc-etc..html

// Platforms

// Windows
#if defined(_WIN64)
#define PLATFORM_WINDOWS
#endif

#if defined(_WIN32) && !defined(_WIN64)
static_assert(false, "32-bit Windows systems are not supported")
#endif

// Linux
#if defined(__linux__)
#define PLATFORM_LINUX
#endif

// OSX
#if defined(__APPLE__)
#define PLATFORM_OSX
#endif

#if (defined(TC_PLATFORM_LINUX) || defined(TC_PLATFORM_OSX))
#define PLATFORM_UNIX
#endif

// Compilers


// MSVC
#if defined(_MSC_VER)
#define COMPILER_MSVC
#endif

// MINGW
#if defined(__MINGW64__)
#define COMPILER_MINGW
#endif

// gcc
#if defined(__GNUC__)
#define COMPILER__GCC
#endif

// clang
#if defined(__clang__)
#define COMPILER_CLANG
#endif

#if defined(COMPILER_MSVC)
#define CHIHAYA_ALIGNED(x) __declspec(align(x))
#else
#define CHIHAYA_ALIGNED(x) __attribute__((aligned(x)))
#endif

#if __cplusplus >= 201703L
#define CHIHAYA_CPP17
#else
#if defined(COMPILER_CLANG)
static_assert(false, "For clang compilers, use -std=c++17");
#endif
static_assert(__cplusplus >= 201402L, "C++14 required.");
#define CHIHAYA_CPP14
#endif

// Do not disable assert...
#ifdef NDEBUG
#undef NDEBUG
#endif

#define CHIHAYA_NAMESPACE_BEGIN namespace chihaya {

#define CHIHAYA_NAMESPACE_END }

CHIHAYA_NAMESPACE_BEGIN

//******************************************************************************
//                                 Types
//******************************************************************************

using uchar = unsigned char;
using uint = unsigned int;

#ifdef _WIN64
#define FORCE_INLINE __forceinline
#else
#define FORCE_INLINE inline __attribute__((always_inline))
#endif

using float32 = float;
using float64 = double;

#ifdef USE_DOUBLE
using real = float64;
#else
using real = float32;
#endif

CHIHAYA_NAMESPACE_END

#endif //CHIHAYA_INCLUDE_CHIHAYA_CHIHAYA_H_
