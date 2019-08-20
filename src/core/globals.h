/*
 * Copyright (C) 2018-2019, neverfelly <neverfelly@gmail.com>
 *
 * This software is licensed under the terms of the MIT License.
 * See COPYING for further information.
 */

#ifndef CHIHAYA_SRC_CORE_GLOBALS_H_
#define CHIHAYA_SRC_CORE_GLOBALS_H_

#include <iostream>
#include <algorithm>
#include <memory>
#include <string>
#include <vector>
#include <limits>
#include <cmath>

#include <glog/logging.h>

// Global Macros
#define ALLOCA(TYPE, COUNT) (TYPE *) alloca((COUNT) * sizeof(TYPE))

namespace chihaya {

// Global Forward Declarations
class Scene;
class Integrator;
class SamplerIntegrator;
template <typename T>
class Vector2;
template <typename T>
class Vector3;
template <typename T>
class Point3;
template <typename T>
class Point2;
template <typename T>
class Normal3;
class Ray;
class RayDifferential;
template <typename T>
class Bounds2;
template <typename T>
class Bounds3;
class Transform;
struct Interaction;
class SurfaceInteraction;
class Shape;
class Primitive;
class GeometricPrimitive;
class TransformedPrimitive;
template <int nSpectrumSamples>
class CoefficientSpectrum;
class RGBSpectrum;
class SampledSpectrum;
#ifdef PBRT_SAMPLED_SPECTRUM
typedef SampledSpectrum Spectrum;
#else
typedef RGBSpectrum Spectrum;
#endif
class Camera;
struct CameraSample;
class ProjectiveCamera;
class Sampler;
class Filter;
class Film;
class FilmTile;
class BxDF;
class BRDF;
class BTDF;
class BSDF;
class Material;
template <typename T>
class Texture;
class Medium;
class MediumInteraction;
struct MediumInterface;
class BSSRDF;
class SeparableBSSRDF;
class TabulatedBSSRDF;
struct BSSRDFTable;
class Light;
class VisibilityTester;
class AreaLight;
struct Distribution1D;
class Distribution2D;
#ifdef PBRT_FLOAT_AS_DOUBLE
typedef double Float;
#else
typedef float Float;
#endif  // PBRT_FLOAT_AS_DOUBLE
class RNG;
class ProgressReporter;
class MemoryArena;
template <typename T, int logBlockSize = 2>
class BlockedArray;
struct Matrix4x4;
class ParamSet;
template <typename T>
struct ParamSetItem;
struct Options {
  Options() {
    cropWindow[0][0] = 0;
    cropWindow[0][1] = 1;
    cropWindow[1][0] = 0;
    cropWindow[1][1] = 1;
  }
  int nThreads = 0;
  bool quickRender = false;
  bool quiet = false;
  bool cat = false, toPly = false;
  std::string imageFile;
  // x0, x1, y0, y1
  Float cropWindow[2][2];
};

extern Options PbrtOptions;
class TextureParams;

// Global Constants
#ifdef _MSC_VER
#define MaxFloat std::numeric_limits<Float>::max()
#define Infinity std::numeric_limits<Float>::infinity()
#else
static constexpr Float MaxFloat = std::numeric_limits<Float>::max();
static constexpr Float Infinity = std::numeric_limits<Float>::infinity();
#endif
#ifdef _MSC_VER
#define MachineEpsilon (std::numeric_limits<Float>::epsilon() * 0.5)
#else
static constexpr Float MachineEpsilon =
std::numeric_limits<Float>::epsilon() * 0.5;
#endif
static constexpr Float ShadowEpsilon = 0.0001f;
static constexpr Float Pi = 3.14159265358979323846;
static constexpr Float InvPi = 0.31830988618379067154;
static constexpr Float Inv2Pi = 0.15915494309189533577;
static constexpr Float Inv4Pi = 0.07957747154594766788;
static constexpr Float PiOver2 = 1.57079632679489661923;
static constexpr Float PiOver4 = 0.78539816339744830961;
static constexpr Float Sqrt2 = 1.41421356237309504880;
#if defined(PBRT_IS_MSVC)
#define alloca _alloca
#endif


// Global Inline Functions

inline uint32_t FloatToBits(float f) {
  uint32_t ui;
  memcpy(&ui, &f, sizeof(float));
  return ui;
}

inline float BitsToFloat(uint32_t ui) {
  float f;
  memcpy(&f, &ui, sizeof(uint32_t));
  return f;
}

inline uint64_t FloatToBits(double f) {
  uint64_t ui;
  memcpy(&ui, &f, sizeof(double));
  return ui;
}

inline double BitsToFloat(uint64_t ui) {
  double f;
  memcpy(&f, &ui, sizeof(uint64_t));
  return f;
}

inline Float Lerp(Float t, Float v1, Float v2) { return (1 - t) * v1 + t * v2; }

template<typename T, typename U, typename V>
inline T Clamp(T val, U low, V high) {
  if (val < low)
    return low;
  else if (val > high)
    return high;
  else
    return val;
}

inline float NextFloatUp(float v) {
  // Handle infinity and negative zero for _NextFloatUp()_
  if (std::isinf(v) && v > 0.) return v;
  if (v == -0.f) v = 0.f;

  // Advance _v_ to next higher float
  uint32_t ui = FloatToBits(v);
  if (v >= 0)
    ++ui;
  else
    --ui;
  return BitsToFloat(ui);
}

inline float NextFloatDown(float v) {
  // Handle infinity and positive zero for _NextFloatDown()_
  if (std::isinf(v) && v < 0.) return v;
  if (v == 0.f) v = -0.f;
  uint32_t ui = FloatToBits(v);
  if (v > 0)
    --ui;
  else
    ++ui;
  return BitsToFloat(ui);
}

inline double NextFloatUp(double v, int delta = 1) {
  if (std::isinf(v) && v > 0.) return v;
  if (v == -0.f) v = 0.f;
  uint64_t ui = FloatToBits(v);
  if (v >= 0.)
    ui += delta;
  else
    ui -= delta;
  return BitsToFloat(ui);
}

inline double NextFloatDown(double v, int delta = 1) {
  if (std::isinf(v) && v < 0.) return v;
  if (v == 0.f) v = -0.f;
  uint64_t ui = FloatToBits(v);
  if (v > 0.)
    ui -= delta;
  else
    ui += delta;
  return BitsToFloat(ui);
}

inline Float gamma(int n) {
  return (n * MachineEpsilon) / (1 - n * MachineEpsilon);
}

}

#endif //CHIHAYA_SRC_CORE_GLOBALS_H_
