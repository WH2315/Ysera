#include "context.hpp"
#include "manager.hpp"
#include <map>

namespace Ysera {

std::unique_ptr<Context> Context::instance_ = nullptr;

void Context::init() {
    if (!instance_.get()) {
        instance_.reset(new Context);
    }
}

void Context::quit() { instance_.reset(); }

void Context::initialize(const Manager& manager) {
    createInstance();
    createSurface(manager);
    LOGI("Vulkan Context Initialized!")
}

void Context::destroy() {
    instance.destroySurfaceKHR(surface);
    instance.destroy();
    LOGI("Vulkan Context Destroyed!")
}

void Context::createInstance() {
    vk::ApplicationInfo app_info;
    app_info.setPApplicationName(g_config.app_name.c_str())
        .setApplicationVersion(1)
        .setPEngineName(g_config.engine_name.c_str())
        .setEngineVersion(1)
        .setApiVersion(vk::ApiVersion13);

    vk::InstanceCreateInfo ins_ci;
    ins_ci.setPApplicationInfo(&app_info);

    std::map<std::string, bool> requiredExtensions;
    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
    for (uint32_t i = 0; i < glfwExtensionCount; i++) {
        requiredExtensions.insert(std::make_pair(static_cast<std::string>(glfwExtensions[i]), false));
    }

    std::vector<const char*> extensions;
    auto eps = vk::enumerateInstanceExtensionProperties();
    for (const auto& ep : eps) {
        if (requiredExtensions.find(ep.extensionName) != requiredExtensions.end()) {
            requiredExtensions[ep.extensionName] = true;
            extensions.push_back(ep.extensionName);
        }
    }
    for (const auto& [ep, success] : requiredExtensions) {
        if (!success) {
            LOGE("unsupported instance extension: {}", ep)
        }
    }
    ins_ci.setPEnabledExtensionNames(extensions);

    const char* layer = "VK_LAYER_KHRONOS_validation";
    if (g_config.debug) {
        auto lps = vk::enumerateInstanceLayerProperties();
        auto it = std::find_if(lps.begin(), lps.end(), [layer](const auto& lp) {
            return strcmp(lp.layerName, layer) == 0;
        });
        if (it != lps.end()) {
            ins_ci.setPEnabledLayerNames(layer);
        } else {
            LOGE("Instance validation layer not support!")
        }
    }

    instance = vk::createInstance(ins_ci);
}

void Context::createSurface(const Manager& manager) {
    VkSurfaceKHR vk_surface;
    glfwCreateWindowSurface(instance, manager.getWindow()->window(), nullptr, &vk_surface);
    surface = static_cast<vk::SurfaceKHR>(vk_surface);
}

} // namespace Ysera