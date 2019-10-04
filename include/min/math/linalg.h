/*
 * Copyright (C) 2018-2019, neverfelly <neverfelly@gmail.com>
 *
 * This software is licensed under the terms of the MIT License.
 * See COPYING for further information.
 */

#ifndef MIN_INCLUDE_MIN_MATH_LINALG_H_
#define MIN_INCLUDE_MIN_MATH_LINALG_H_

#include <vector>
#include <array>
#include <type_traits>
#include <min/common/util.h>
#include <immintrin.h>
#include "scalar.h"

MIN_NAMESPACE_BEGIN

/////////////////////////////////////////////////////////////////
/////              N dimensional Vector
/////////////////////////////////////////////////////////////////

template<int dim, typename T, class Enable = void>
struct VectorNDBase {
  static constexpr int storage_elements = dim;
  T d[dim];
};

template<typename T>
struct VectorNDBase<1, T, void> {
  static constexpr int storage_elements = 1;
  union {
    T d[1];
    struct {
      T x;
    };
  };
};

template<typename T>
struct VectorNDBase<2, T, void> {
  static constexpr int storage_elements = 2;
  union {
    T d[2];
    struct {
      T x, y;
    };
  };
};

template<typename T>
struct VectorNDBase<3, T,
                    typename std::enable_if_t<!std::is_same<T, float32>::value>> {
  static constexpr int storage_elements = 3;
  union {
    T d[3];
    struct {
      T x, y, z;
    };
  };
};

template<>
struct MIN_ALIGNED(16) VectorNDBase<3, float32, void> {
  static constexpr int storage_elements = 4;
  union {
    __m128 v;
    struct {
      float32 x, y, z, _w;
    };
    float32 d[4];
  };

  MIN_FORCE_INLINE VectorNDBase(float32 x = 0.0_f) : v(_mm_set_ps1(x)) {}

  explicit VectorNDBase(__m128 v) : v(v) {}

};

template<typename T>
struct VectorNDBase<4, T,
                    typename std::enable_if_t<!std::is_same<T, float32>::value>> {
  static constexpr int storage_elements = 4;
  union {
    T d[4];
    struct {
      T x, y, z, w;
    };
  };
};

template<int dim__, typename T>
struct VectorND : public VectorNDBase<dim__, T> {
  static constexpr int dim = dim__;
  using ScalarType = T;
  using VectorBase = VectorNDBase<dim, T>;
  using VectorBase::d;
  static constexpr int storage_elements = VectorBase::storage_elements;

  MIN_FORCE_INLINE VectorND() {
    for (int i = 0; i < dim; i++) {
      this->d[i] = T(0);
    }
  }

  static MIN_FORCE_INLINE VectorND from_array(const T new_val[dim]) {
    VectorND ret;
    for (int i = 0; i < dim; i++) {
      ret.d[i] = new_val[i];
    }
    return ret;
  }

  template<int dim_, typename T_>
  explicit MIN_FORCE_INLINE VectorND(const VectorND<dim_, T_> &o) : VectorND() {
    for (int i = 0; i < std::min(dim_, dim__); i++) {
      d[i] = o[i];
    }
  }

  explicit MIN_FORCE_INLINE VectorND(const std::array<T, dim> &o) {
    for (int i = 0; i < dim; i++) {
      d[i] = o[i];
    }
  }

  // Vector3f
  template<int dim_ = dim,
      typename T_ = T,
      typename std::enable_if_t<dim_==3, int> = 0>
  explicit MIN_FORCE_INLINE VectorND(float32 x) : VectorNDBase<dim, T>(x) {}

  // Vector4f
  template<int dim_ = dim,
      typename T_ = T,
      typename std::enable_if_t<dim_==4>>
  explicit MIN_FORCE_INLINE VectorND(float32 x) : VectorNDBase<dim, T>(x) {}

  // Vector initialization
  template<typename F,
      std::enable_if_t<std::is_same<F, VectorND>::value, int> = 0>
  explicit MIN_FORCE_INLINE VectorND(const F &f) {
    for (int i = 0; i < dim; i++) {
      this->d[i] = f[i];
    }
  }

  // Scalar initialization
  template<typename F,
      std::enable_if_t<std::is_same<F, T>::value, int> = 0>
  explicit MIN_FORCE_INLINE VectorND(const F &f) {
    for (int i = 0; i < dim; i++) {
      this->d[i] = f;
    }
  }

  // Function initialization
  template<typename F,
      std::enable_if_t<std::is_convertible<F, std::function<T(int)>>::value, int> = 0>
  explicit MIN_FORCE_INLINE VectorND(const F &f) {
    for (int i = 0; i < dim; ++i) {
      this->d[i] = f(i);
    }
  }

  MIN_FORCE_INLINE T &operator[](int i) {
    return this->d[i];
  }

  MIN_FORCE_INLINE const T &operator[](int i) const {
    return this->d[i];
  }

  MIN_FORCE_INLINE T &operator()(int i) {
    return d[i];
  }

  MIN_FORCE_INLINE const T &operator()(int i) const {
    return d[i];
  }

  MIN_FORCE_INLINE T dot(VectorND<dim, T> o) const {
    T ret = T(0);
    for (int i = 0; i < dim; i++) {
      ret += this->d[i]*o[i];
    }
    return ret;
  }

  MIN_FORCE_INLINE VectorND &operator=(const VectorND &o) {
    memcpy(this, &o, sizeof(*this));
    return *this;
  }

  template<int dim_ = dim,
      typename T_ = T>
  MIN_FORCE_INLINE VectorND operator+(const VectorND &o) const {
    return VectorND([=](int i) { return this->d[i] + o[i]; });
  }

  template<int dim_ = dim,
      typename T_ = T>
  MIN_FORCE_INLINE VectorND operator-(const VectorND &o) const {
    return VectorND([=](int i) { return this->d[i] - o[i]; });
  }

  template<int dim_ = dim,
      typename T_ = T>
  MIN_FORCE_INLINE VectorND operator*(const VectorND &o) const {
    return VectorND([=](int i) { return this->d[i]*o[i]; });
  }

  template<int dim_ = dim,
      typename T_ = T>
  MIN_FORCE_INLINE VectorND operator/(const VectorND &o) const {
    return VectorND([=](int i) { return this->d[i]/o[i]; });
  }

  template<int dim_ = dim,
      typename T_ = T>
  MIN_FORCE_INLINE VectorND operator%(const VectorND &o) const {
    return VectorND([=](int i) { return this->d[i]%o[i]; });
  }

  // Inplace operations
  MIN_FORCE_INLINE VectorND &operator+=(const VectorND &o) {
    (*this) = (*this) + o;
    return *this;
  }

  MIN_FORCE_INLINE VectorND &operator-=(const VectorND &o) {
    (*this) = (*this) - o;
    return *this;
  }

  MIN_FORCE_INLINE VectorND &operator*=(const VectorND &o) {
    (*this) = (*this)*o;
    return *this;
  }

  MIN_FORCE_INLINE VectorND &operator*=(const T &o) {
    (*this) = (*this)%o;
    return *this;
  }

  MIN_FORCE_INLINE VectorND &operator/=(const VectorND &o) {
    (*this) = (*this)/o;
    return *this;
  }

  MIN_FORCE_INLINE VectorND &operator/=(const T &o) {
    (*this) = (*this)/o;
    return *this;
  }

  MIN_FORCE_INLINE VectorND operator-() const {
    return VectorND([=](int i) { return -this->d[i]; });
  }

  MIN_FORCE_INLINE bool operator==(const VectorND &o) const {
    for (int i = 0; i < dim; i++) {
      if (this->d[i]!=o[i]) {
        return false;
      }
    }
    return true;
  }

  MIN_FORCE_INLINE bool operator<(const VectorND &o) const {
    for (int i = 0; i < dim; i++) {
      if (this->d[i] >= o[i]) {
        return false;
      }
    }
    return true;
  }

  MIN_FORCE_INLINE bool operator<=(const VectorND &o) const {
    for (int i = 0; i < dim; i++) {
      if (this->d[i] > o[i]) {
        return false;
      }
    }
    return true;
  }

  MIN_FORCE_INLINE bool operator>(const VectorND &o) const {
    for (int i = 0; i < dim; i++) {
      if (this->d[i] <= o[i]) {
        return false;
      }
    }
    return true;
  }

  MIN_FORCE_INLINE bool operator>=(const VectorND &o) const {
    for (int i = 0; i < dim; i++) {
      if (this->d[i] < o[i]) {
        return false;
      }
    }
    return true;
  }

  MIN_FORCE_INLINE bool operator!=(const VectorND &o) const {
    for (int i = 0; i < dim; i++) {
      if (this->d[i]!=o[i]) {
        return true;
      }
    }
    return false;
  }

  MIN_FORCE_INLINE VectorND abs() const {
    return VectorND([&](int i) { return std::abs(d[i]); });
  }

  MIN_FORCE_INLINE VectorND floor() const {
    return VectorND([&](int i) { return std::floor(d[i]); });
  }

  void print() const {
    for (int i = 0; i < dim; i++) {
      std::cout << this->d[i] << " ";
    }
    std::cout << std::endl;
  }

  // member function
  template<int dim_ = dim,
      typename T_ = T>
  MIN_FORCE_INLINE T Length2() const {
    T ret = T(0);
    for (int i = 0; i < dim; i++) {
      ret += this->d[i]*this->d[i];
    }
    return ret;
  }

  MIN_FORCE_INLINE auto Length() const {
    return std::sqrt(Length2());
  }

};

template <typename T, int dim>
using TVector = VectorND<dim, T>;

template <int dim, typename T>
MIN_FORCE_INLINE VectorND<dim, T> operator*(T a, const VectorND<dim, T> &v) {
  return VectorND<dim, T>(a) * v;
}

template <int dim, typename T>
MIN_FORCE_INLINE VectorND<dim, T> operator*(const VectorND<dim, T> &v, T a) {
  return a * v;
}

template <int dim, typename T>
MIN_FORCE_INLINE VectorND<dim, T> operator/(T a, const VectorND<dim, T> &v) {
  return VectorND<dim, T>(a) / v;
}

template <int dim, typename T>
MIN_FORCE_INLINE VectorND<dim, T> operator/(const VectorND<dim, T> &v, T a) {
  return v / VectorND<dim, T>(a);
}

using Vector1 = VectorND<1, real>;
using Vector2 = VectorND<2, real>;
using Vector3 = VectorND<3, real>;
using Vector4 = VectorND<4, real>;

using Vector1f = VectorND<1, float32>;
using Vector2f = VectorND<2, float32>;
using Vector3f = VectorND<3, float32>;
using Vector4f = VectorND<4, float32>;

using Vector1d = VectorND<1, float64>;
using Vector2d = VectorND<2, float64>;
using Vector3d = VectorND<3, float64>;
using Vector4d = VectorND<4, float64>;

using Vector1i = VectorND<1, int>;
using Vector2i = VectorND<2, int>;
using Vector3i = VectorND<3, int>;
using Vector4i = VectorND<4, int>;

/////////////////////////////////////////////////////////////////
/////              N dimensional Matrix
/////////////////////////////////////////////////////////////////


MIN_NAMESPACE_END

#endif //MIN_INCLUDE_MIN_MATH_LINALG_H_
