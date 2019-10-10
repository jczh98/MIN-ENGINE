/*
 * Copyright (C) 2018-2019, neverfelly <neverfelly@gmail.com>
 *
 * This software is licensed under the terms of the MIT License.
 * See COPYING for further information.
 */

#ifndef MIN_INCLUDE_MIN_CORE_COLOR_H_
#define MIN_INCLUDE_MIN_CORE_COLOR_H_

#include <min/min.h>

MIN_NAMESPACE_BEGIN

class Color3f : public Eigen::Array3f {
 public:
  typedef Eigen::Array3f Base;

  explicit Color3f(float32 value = 0.f) : Base(value, value, value) {}

  Color3f(float r, float g, float b) : Base(r, g, b) {}

  template<typename Derived>
  explicit Color3f(const Eigen::ArrayBase<Derived> &p) : Base(p) {}

  template<typename Derived>
  Color3f &operator=(const Eigen::ArrayBase<Derived> &p) {
    this->Base::operator=(p);
    return *this;
  }

  float32 &r() { return x(); }
  const float32 &r() const { return x(); }
  float32 &g() { return y(); }
  const float32 &g() const { return y(); }
  float32 &b() { return z(); }
  const float32 &b() const { return z(); }

  bool valid() const;

  Color3f Clamp() const {
    return Color3f(
        std::max(r(), 0.0f),
        std::max(g(), 0.0f),
        std::max(b(), 0.0f)
    );
  }

  std::string string() const {
    return fmt::format("[{}, {}, {}]", coeff(0), coeff(1), coeff(2));
  }
};

class Color4f : public Eigen::Array4f {
 public:
  typedef Eigen::Array4f Base;

  Color4f() : Base(0.0f, 0.0f, 0.0f, 0.0f) {}

  explicit Color4f(const Color3f &c) : Base(c.r(), c.g(), c.b(), 1.0f) {}

  Color4f(float r, float g, float b, float w) : Base(r, g, b, w) {}

  template<typename Derived>
  Color4f(const Eigen::ArrayBase<Derived> &p)
      : Base(p) {}

  template<typename Derived>
  Color4f &operator=(const Eigen::ArrayBase<Derived> &p) {
    this->Base::operator=(p);
    return *this;
  }

  // Divide by the filter weight and convert into a \ref Color3f value
  Color3f DivideByFilterWeight() const {
    if (w()!=0)
      return Color3f(x() / w(), y() / w(), z() / w());
    else
      return Color3f(0.0f);
  }

  std::string string() const {
    return fmt::format("[{}, {}, {}, {}]", coeff(0), coeff(1), coeff(2), coeff(3));
  }

};
MIN_NAMESPACE_END

#endif //MIN_INCLUDE_MIN_CORE_COLOR_H_
