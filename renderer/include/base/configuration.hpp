#pragma once

#include "core/log.hpp"
#include "core/window.hpp"

namespace Ysera {

struct Configuration {
    WindowInfo window_info;
    std::string app_name;
    std::string engine_name;
    bool debug = false;
};

} // namespace Ysera