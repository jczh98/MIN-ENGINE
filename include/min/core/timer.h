/*
 * Copyright (C) 2018-2019, neverfelly <neverfelly@gmail.com>
 *
 * This software is licensed under the terms of the MIT License.
 * See COPYING for further information.
 */

#ifndef MIN_INCLUDE_MIN_CORE_TIMER_H_
#define MIN_INCLUDE_MIN_CORE_TIMER_H_

#include <min/min.h>

MIN_NAMESPACE_BEGIN


class Timer {
 public:
  Timer() { Reset(); }
  void Reset() { start_ = std::chrono::system_clock::now(); }

  float32 Elapsed() const {
    auto now = std::chrono::system_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - start_);
    return (double) duration.count();
  }

  std::string ElapsedString(bool precise = false) {
    return TimeString(Elapsed(), precise);
  }

  double Lap() {
    auto now = std::chrono::system_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - start_);
    start_ = now;
    return (double) duration.count();
  }

  std::string LapString(bool precise = false) {
    return TimeString(Lap(), precise);
  }

  std::string TimeString(double time, bool precise) {
    if (std::isnan(time) || std::isinf(time))
      return "inf";

    std::string suffix = "ms";
    if (time > 1000) {
      time /= 1000; suffix = "s";
      if (time > 60) {
        time /= 60; suffix = "m";
        if (time > 60) {
          time /= 60; suffix = "h";
          if (time > 12) {
            time /= 12; suffix = "d";
          }
        }
      }
    }

    std::ostringstream os;
    os << std::setprecision(precise ? 4 : 1)
       << std::fixed << time << suffix;

    return os.str();
  }
 private:
  std::chrono::system_clock::time_point start_;
};
MIN_NAMESPACE_END

#endif //MIN_INCLUDE_MIN_CORE_TIMER_H_
