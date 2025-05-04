#include "basic/swapchain.hpp"
#include "base/utils.hpp"
#include "context.hpp"

namespace Ysera {

Swapchain::Swapchain() {
    vk::SwapchainKHR old_swapchain = swapchain;

    SwapchainSupportDetails details = {
        .capabilities = g_manager->device->physical_device.getSurfaceCapabilitiesKHR(g_manager->surface),
        .formats = g_manager->device->physical_device.getSurfaceFormatsKHR(g_manager->surface),
        .modes = g_manager->device->physical_device.getSurfacePresentModesKHR(g_manager->surface)
    };

    format = details.formats[0];
    mode = details.modes[0];

    vk::SurfaceFormatKHR desired_format;
    if (g_config.desired_format.has_value()) {
        desired_format = g_config.desired_format.value();
    } else {
        desired_format = {vk::Format::eB8G8R8A8Unorm,
                          vk::ColorSpaceKHR::eSrgbNonlinear};
    }
    for (auto format : details.formats) {
        if (format.format == desired_format.format &&
            format.colorSpace == desired_format.colorSpace) {
            this->format = format;
            break;
        }
    }

    vk::PresentModeKHR desired_mode;
    if (g_config.desired_mode.has_value()) {
        desired_mode = g_config.desired_mode.value();
    } else {
        if (g_config.vsync) {
            desired_mode = vk::PresentModeKHR::eFifo;
        } else {
            desired_mode = vk::PresentModeKHR::eMailbox;
        }
    }
    for (auto mode : details.modes) {
        if (mode == desired_mode) {
            this->mode = mode;
            break;
        }
    }

    uint32_t desired_image_count = details.capabilities.minImageCount + 1;
    if (details.capabilities.maxImageCount > 0 &&
        desired_image_count > details.capabilities.maxImageCount) {
        desired_image_count = details.capabilities.maxImageCount;
    }

    uint32_t width =
        std::clamp<uint32_t>(details.capabilities.currentExtent.width,
                             details.capabilities.minImageExtent.width,
                             details.capabilities.maxImageExtent.width);
    uint32_t height =
        std::clamp<uint32_t>(details.capabilities.currentExtent.height,
                             details.capabilities.minImageExtent.height,
                             details.capabilities.maxImageExtent.height);
    g_config.resetWindowSize(width, height);

    vk::SwapchainCreateInfoKHR swapchain_ci;
    swapchain_ci.setOldSwapchain(old_swapchain)
        .setSurface(g_manager->surface)
        .setPreTransform(details.capabilities.currentTransform)
        .setCompositeAlpha(vk::CompositeAlphaFlagBitsKHR::eOpaque)
        .setPresentMode(mode)
        .setClipped(true)
        .setMinImageCount(desired_image_count)
        .setImageFormat(format.format)
        .setImageColorSpace(format.colorSpace)
        .setImageExtent({width, height})
        .setImageArrayLayers(1)
        .setImageUsage(vk::ImageUsageFlagBits::eColorAttachment);

    uint32_t queue_family_indices[] = {g_manager->device->graphics_queue_family,
                                       g_manager->device->present_queue_family};
    if (queue_family_indices[0] != queue_family_indices[1]) {
        swapchain_ci.setImageSharingMode(vk::SharingMode::eConcurrent)
            .setQueueFamilyIndices(queue_family_indices);
    } else {
        swapchain_ci.setImageSharingMode(vk::SharingMode::eExclusive);
    }

    swapchain = g_manager->device->device.createSwapchainKHR(swapchain_ci);

    if (old_swapchain != nullptr) {
        for (auto& image_view : image_views) {
            g_manager->device->device.destroyImageView(image_view);
        }
        image_views.clear();
        g_manager->device->device.destroySwapchainKHR(old_swapchain);
    }

    images = g_manager->device->device.getSwapchainImagesKHR(swapchain);
    image_count = images.size();
    image_views.resize(image_count);
    for (uint32_t i = 0; i < image_count; i++) {
        image_views[i] = createImageView(images[i], format.format,
                                         vk::ImageAspectFlagBits::eColor, 1);
    }
}

Swapchain::~Swapchain() {
    for (auto& image_view : image_views) {
        g_manager->device->device.destroyImageView(image_view);
    }
    image_views.clear();
    g_manager->device->device.destroySwapchainKHR(swapchain);
}

} // namespace Ysera