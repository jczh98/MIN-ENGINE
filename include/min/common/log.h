/*
 * Copyright (C) 2018-2019, neverfelly <neverfelly@gmail.com>
 *
 * This software is licensed under the terms of the MIT License.
 * See COPYING for further information.
 */
#pragma once

#include "util.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace min {

class Log {
 public:
  static void Init() {
    spdlog::set_pattern("%^[%T] %n: %v%$");
    core_logger = spdlog::stdout_color_mt("MIN");
    core_logger->set_level(spdlog::level::trace);

    client_logger = spdlog::stdout_color_mt("APP");
    client_logger->set_level(spdlog::level::trace);
  }

  inline static std::shared_ptr<spdlog::logger> core_logger;
  inline static std::shared_ptr<spdlog::logger> client_logger;
};

#define MIN_CORE_TRACE(...) Log::core_logger->trace(__VA_ARGS__)
#define MIN_CORE_INFO(...) Log::core_logger->info(__VA_ARGS__)
#define MIN_CORE_WARN(...) Log::core_logger->warn(__VA_ARGS__)
#define MIN_CORE_ERROR(...) Log::core_logger->error(__VA_ARGS__)

#define MIN_TRACE(...) Log::client_logger->trace(__VA_ARGS__)
#define MIN_INFO(...) Log::client_logger->info(__VA_ARGS__)
#define MIN_WARN(...) Log::client_logger->warn(__VA_ARGS__)
#define MIN_ERROR(...) Log::client_logger->error(__VA_ARGS__)
}

