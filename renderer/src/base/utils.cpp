#include "base/utils.hpp"
#include "context.hpp"

namespace Ysera {

vk::ImageView createImageView(vk::Image image, vk::Format format,
                              vk::ImageAspectFlags aspect, uint32_t level_count,
                              uint32_t layer_count,
                              vk::ImageViewType view_type) {
    vk::ImageViewCreateInfo image_view_ci;

    vk::ImageSubresourceRange subresource_range;
    subresource_range.setAspectMask(aspect)
        .setBaseMipLevel(0)
        .setLevelCount(level_count)
        .setBaseArrayLayer(0)
        .setLayerCount(layer_count);

    vk::ComponentMapping components;
    components.setR(vk::ComponentSwizzle::eR)
        .setG(vk::ComponentSwizzle::eG)
        .setB(vk::ComponentSwizzle::eB)
        .setA(vk::ComponentSwizzle::eA);

    image_view_ci.setImage(image)
        .setFormat(format)
        .setViewType(view_type)
        .setComponents(components)
        .setSubresourceRange(subresource_range);

    return g_manager->device->device.createImageView(image_view_ci);
}

} // namespace Ysera