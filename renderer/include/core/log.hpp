#pragma once

#include <spdlog/spdlog.h>

namespace Ysera {

class Log final {
public:
    Log();
    ~Log();

    template <typename... Args>
    void debug(fmt::format_string<Args...> format, Args&&... args) {
        logger_->debug(fmt::format(format, std::forward<Args>(args)...));
    }

    template <typename... Args>
    void info(fmt::format_string<Args...> format, Args&&... args) {
        logger_->info(fmt::format(format, std::forward<Args>(args)...));
    }

    template <typename... Args>
    void warn(fmt::format_string<Args...> format, Args&&... args) {
        logger_->warn(fmt::format(format, std::forward<Args>(args)...));
    }

    template <typename... Args>
    void error(fmt::format_string<Args...> format, Args&&... args) {
        logger_->error(fmt::format(format, std::forward<Args>(args)...));
    }

private:
    std::shared_ptr<spdlog::logger> logger_;
};

extern Log* g_log;

} // namespace Ysera

#define LOGD(...) ::Ysera::g_log->debug(__VA_ARGS__);
#define LOGI(...) ::Ysera::g_log->info(__VA_ARGS__);
#define LOGW(...) ::Ysera::g_log->warn(__VA_ARGS__);
#define LOGE(...) ::Ysera::g_log->error(__VA_ARGS__);