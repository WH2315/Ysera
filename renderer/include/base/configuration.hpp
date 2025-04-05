#pragma once

#include "dllexport.hpp"
#include "core/log.hpp"
#include "core/window.hpp"

namespace Ysera {

struct YSERA_API Configuration {
    WindowInfo window_info;

    void resetWindowSize(uint32_t width, uint32_t height) {
        window_info.width = width;
        window_info.height = height;
    }
    uint32_t getWindowWidth() const { return window_info.width; }
    uint32_t getWindowHeight() const { return window_info.height; }
};

} // namespace Ysera