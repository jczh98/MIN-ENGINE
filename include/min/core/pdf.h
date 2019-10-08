/*
 * Copyright (C) 2018-2019, neverfelly <neverfelly@gmail.com>
 *
 * This software is licensed under the terms of the MIT License.
 * See COPYING for further information.
 */

#ifndef MIN_INCLUDE_MIN_CORE_PDF_H_
#define MIN_INCLUDE_MIN_CORE_PDF_H_

#include <min/min.h>

MIN_NAMESPACE_BEGIN

// Discrete probability distribution
class DiscretePDF {
 public:
  explicit DiscretePDF(size_t entries = 0) : sum_(0.0f), normalization_(0.0f), normalized_(false){
    Reserve(entries);
    Clear();
  }

  void Clear() {
    cdf_.clear();
    cdf_.emplace_back(0.0f);
    normalized_ = false;
  }

  void Reserve(size_t entries) {
    cdf_.reserve(entries);
  }

  void Append(real value) {
    cdf_.emplace_back(cdf_[cdf_.size() - 1] + value);
  }

  size_t Size() const { return cdf_.size() - 1; }

  real operator[](size_t entry) const {
    return cdf_[entry + 1] - cdf_[entry];
  }

  bool normalized() const { return normalized_; }

  real sum() const { return sum_; }

  real normalization() const { return normalization_; }

  // Normalize the distribution
  real Normalize() {
    sum_ = cdf_[cdf_.size() - 1];
    if (sum_ > 0) {
      normalization_ = 1.0f / sum_;
      for (size_t i = 1; i < cdf_.size(); i++) {
        cdf_[i] *= normalization_;
      }
      cdf_[cdf_.size() - 1] = 1.0f;
    } else {
      normalization_ = 0.0f;
    }
    return sum_;
  }

  // Return the discrete index associated with the sample value
  size_t Sample(real sample_value) const {
    auto entry = std::lower_bound(cdf_.begin(), cdf_.end(), sample_value);
    size_t index = (size_t) std::max((ptrdiff_t)0, entry - cdf_.begin() - 1);
    return std::min(index, cdf_.size() - 2);
  }

  size_t Sample(real sample_value, real &pdf) const {
    size_t index = Sample(sample_value);
    pdf = (*this)[index];
    return index;
  }

  // The original sample is value adjusted so that it can be reused.
  size_t SampleReuse(real &sample_value) const {
    size_t index = Sample(sample_value);
    sample_value = (sample_value - cdf_[index]) / (cdf_[index + 1] - cdf_[index]);
    return index;
  }

  size_t SampleReuse(real &sample_value, real &pdf) const {
    size_t index = Sample(sample_value, pdf);
    sample_value = (sample_value - cdf_[index]) / (cdf_[index + 1] - cdf_[index]);
    return index;
  }
 private:
  std::vector<real> cdf_;
  real sum_, normalization_;
  bool normalized_;
};
MIN_NAMESPACE_END

#endif //MIN_INCLUDE_MIN_CORE_PDF_H_
