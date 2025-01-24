#include "core/log.hpp"
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Ysera {

Log* g_log = nullptr;

Log::Log() {
    logger_ = spdlog::stdout_color_mt("Ysera");
    logger_->set_pattern("%^[%T] %n: %v%$");
    logger_->set_level(spdlog::level::trace);
}

Log::~Log() {
    spdlog::shutdown();
    logger_.reset();
}

} // namespace Ysera