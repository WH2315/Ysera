#pragma once

#include "dllexport.hpp"
#include <vulkan/vulkan.hpp>

namespace Ysera {

class YSERA_API Swapchain {
public:
    Swapchain();
    ~Swapchain();

public:
    vk::SwapchainKHR swapchain = nullptr;
    vk::SurfaceFormatKHR format;
    vk::PresentModeKHR mode;

    uint32_t image_count;
    std::vector<vk::Image> images;
    std::vector<vk::ImageView> image_views;

private:
    struct SwapchainSupportDetails {
        vk::SurfaceCapabilitiesKHR capabilities;
        std::vector<vk::SurfaceFormatKHR> formats;
        std::vector<vk::PresentModeKHR> modes;
    };
};

} // namespace Ysera