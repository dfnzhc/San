//
// Created by 秋鱼 on 2022/5/6.
//

#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/async.h>
#include <spdlog/fmt/fmt.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

#include "common.hpp"

namespace San {
static const char* LOGGER_NAME = "San_Logger";

class LogSystem final
{
public:
    LogSystem()
    {
        auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        console_sink->set_level(spdlog::level::debug);
        console_sink->set_pattern("[%^%=9l%$] %v");

        std::vector<spdlog::sink_ptr> sinks{console_sink};
        logger_ = std::make_shared<spdlog::logger>(San::LOGGER_NAME,
                                                   sinks.begin(),
                                                   sinks.end());

        logger_->set_level(spdlog::level::trace);
        spdlog::register_logger(logger_);
    }

    ~LogSystem()
    {
        logger_->flush_on(spdlog::level::trace);
        spdlog::drop_all();
    }
    
    DEL_COPY_IN_CLASS(LogSystem)
    
private:
    std::shared_ptr<spdlog::logger> logger_ = nullptr;
};

extern inline std::unique_ptr<LogSystem> GlobalLogger = nullptr;

inline LogSystem* GetLog()
{
    if (GlobalLogger == nullptr) {
        GlobalLogger = std::make_unique<LogSystem>();
    }
    
    return GlobalLogger.get();
}

} // namespace San

#define LOG_INFO(...)    if (spdlog::get(San::LOGGER_NAME) != nullptr) {spdlog::get(San::LOGGER_NAME)->info(__VA_ARGS__);}
#define LOG_DEBUG(...)   if (spdlog::get(San::LOGGER_NAME) != nullptr) {spdlog::get(San::LOGGER_NAME)->debug(__VA_ARGS__);}
#define LOG_WARN(...)    if (spdlog::get(San::LOGGER_NAME) != nullptr) {spdlog::get(San::LOGGER_NAME)->warn(__VA_ARGS__);}
#define LOG_ERROR(...)   if (spdlog::get(San::LOGGER_NAME) != nullptr) \
    {spdlog::get(San::LOGGER_NAME)->error("[{}:{}:{}] {}", __FILE__, __LINE__, __FUNCTION__, fmt::format(__VA_ARGS__));}
#define LOG_FATAL(...)   if (spdlog::get(San::LOGGER_NAME) != nullptr) \
    {const std::string format_str = fmt::format("[{}:{}:{}] {}", __FILE__, __LINE__, __FUNCTION__, fmt::format(__VA_ARGS__)); \
    throw std::runtime_error(format_str);}

#define INIT_LOG() \
        if (San::GlobalLogger) {LOG_INFO("Log system has been initialized")} \
        else {San::GlobalLogger = std::make_unique<San::LogSystem>(); LOG_INFO("Init log system") }
