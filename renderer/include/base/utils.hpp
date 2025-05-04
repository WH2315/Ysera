#pragma once

#include "dllexport.hpp"
#include <vulkan/vulkan.hpp>

namespace Ysera {

YSERA_API vk::ImageView
createImageView(vk::Image image, vk::Format format, vk::ImageAspectFlags aspect,
                uint32_t level_count, uint32_t layer_count = 1,
                vk::ImageViewType view_type = vk::ImageViewType::e2D);

} // namespace Ysera