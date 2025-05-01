#pragma once

#include "dllexport.hpp"
#include <vulkan/vulkan.hpp>

namespace Ysera {

class YSERA_API Device {
public:
    Device();
    ~Device();

public:
    vk::PhysicalDevice physical_device;
    vk::Device device;

    vk::Queue graphics_queue;
    uint32_t graphics_queue_family = -1;
    vk::Queue present_queue;
    uint32_t present_queue_family = -1;
    vk::Queue transfer_queue;
    uint32_t transfer_queue_family = -1;
    vk::Queue compute_queue;
    uint32_t compute_queue_family = -1;

private:
    bool suitable(const vk::PhysicalDevice& candidate);
};

} // namespace Ysera