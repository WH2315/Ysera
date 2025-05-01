#include "basic/device.hpp"
#include "context.hpp"
#include <map>
#include <set>

namespace Ysera {

Device::Device() {
    auto devices = g_manager->instance.enumeratePhysicalDevices();

    bool selected = false;
    for (const auto& candidate : devices) {
        if (suitable(candidate)) {
            selected = true;
            break;
        }
    }
    if (!selected) {
        LOGE("No suitable physical device found!")
    } else {
        auto properties = physical_device.getProperties();
        LOGI("Selected GPU: {}", static_cast<std::string>(properties.deviceName.data()))
        if (g_config.debug) {
            LOGD("  GPU Driver Version: {}.{}.{}", VK_VERSION_MAJOR(properties.driverVersion), VK_VERSION_MINOR(properties.driverVersion), VK_VERSION_PATCH(properties.driverVersion))
            LOGD("  GPU API Version: {}.{}.{}", VK_VERSION_MAJOR(properties.apiVersion), VK_VERSION_MINOR(properties.apiVersion), VK_VERSION_PATCH(properties.apiVersion))
            auto memory_properties = physical_device.getMemoryProperties();
            for (uint32_t i = 0; i < memory_properties.memoryHeapCount; i++) {
                auto size = (float)memory_properties.memoryHeaps[i].size / 1024.0f / 1024.0f / 1024.0f;
                if (memory_properties.memoryHeaps[i].flags & vk::MemoryHeapFlagBits::eDeviceLocal) {
                    LOGD("  Local GPU Memory: {} Gib", size)
                } else {
                    LOGD("  Shared GPU Memory: {} Gib", size)
                }
            }
        }
    }

    vk::DeviceCreateInfo device_ci;

    std::map<std::string, bool> requiredExtensions = {
        {VK_KHR_SWAPCHAIN_EXTENSION_NAME, false},
    };

    std::vector<const char*> extensions;
    auto eps = physical_device.enumerateDeviceExtensionProperties();
    for (const auto& ep : eps) {
        if (requiredExtensions.find(ep.extensionName) != requiredExtensions.end()) {
            requiredExtensions[ep.extensionName] = true;
            extensions.push_back(ep.extensionName);
        }
    }
    for (const auto& [ep, success] : requiredExtensions) {
        if (!success) {
            LOGE("unsupported device extension: {}", ep)
        }
    }
    device_ci.setPEnabledExtensionNames(extensions);

    const char* layer = "VK_LAYER_KHRONOS_validation";
    if (g_config.debug) {
        auto lps = physical_device.enumerateDeviceLayerProperties();
        auto it = std::find_if(lps.begin(), lps.end(), [layer](const auto& lp) {
            return strcmp(lp.layerName, layer) == 0;
        });
        if (it != lps.end()) {
            device_ci.setPEnabledLayerNames(layer);
        } else {
            LOGE("Device validation layer not support!")
        }
    }

    std::set<uint32_t> queue_family_indices = {
        graphics_queue_family,
        present_queue_family,
        transfer_queue_family,
        compute_queue_family
    };
    std::vector<vk::DeviceQueueCreateInfo> queue_cis(queue_family_indices.size());
    size_t i = 0;
    float priorities = 1.0f;
    for (auto index : queue_family_indices) {
        queue_cis[i].setQueueFamilyIndex(index)
            .setQueueCount(1)
            .setQueuePriorities(priorities);
        i++;
    }
    device_ci.setQueueCreateInfos(queue_cis);

    device = physical_device.createDevice(device_ci);

    graphics_queue = device.getQueue(graphics_queue_family, 0);
    present_queue = device.getQueue(present_queue_family, 0);
    transfer_queue = device.getQueue(transfer_queue_family, 0);
    compute_queue = device.getQueue(compute_queue_family, 0);
}

Device::~Device() {
    physical_device = nullptr;
    device.destroy();
}

bool Device::suitable(const vk::PhysicalDevice& candidate) {
    auto properties = candidate.getProperties();

    std::string device_name = properties.deviceName;
    if (properties.deviceType != vk::PhysicalDeviceType::eDiscreteGpu) {
        LOGE("PhysicalDevice: {} not a discrete GPU", device_name)
        return false;
    }

    bool found = false;
    auto qfproperties = candidate.getQueueFamilyProperties();
    auto flags = vk::QueueFlagBits::eGraphics|vk::QueueFlagBits::eTransfer|vk::QueueFlagBits::eCompute;
    for (uint32_t i = 0; i < qfproperties.size(); i++) {
        auto present_support = candidate.getSurfaceSupportKHR(i, g_manager->surface);
        if (qfproperties[i].queueFlags & flags && present_support) {
            graphics_queue_family = i;
            present_queue_family = i;
            transfer_queue_family = i;
            compute_queue_family = i;
            found = true;
            break;
        }
    }
    if (!found) {
        LOGE("PhysicalDevice: {} not support required queue family", device_name)
        return false;
    }

    physical_device = candidate;
    return true;
}

} // namespace Ysera