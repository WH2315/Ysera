#pragma once

#include "dllexport.hpp"
#include "core/log.hpp"
#include "core/window.hpp"
#include <vulkan/vulkan.hpp>
#include <optional>

namespace Ysera {

struct YSERA_API Configuration {
    WindowInfo window_info;

    std::string app_name;
    std::string engine_name;
    bool debug = false;

    std::optional<vk::SurfaceFormatKHR> desired_format = std::nullopt;
    std::optional<vk::PresentModeKHR> desired_mode = std::nullopt;
    bool vsync = false;

    void resetWindowSize(uint32_t width, uint32_t height) {
        window_info.width = width;
        window_info.height = height;
    }
    uint32_t getWindowWidth() const { return window_info.width; }
    uint32_t getWindowHeight() const { return window_info.height; }
};

} // namespace Ysera