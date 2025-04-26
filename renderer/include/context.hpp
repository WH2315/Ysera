#pragma once

#include "dllexport.hpp"
#include <vulkan/vulkan.hpp>
#include <memory>

namespace Ysera {

class YSERA_API Manager;
class YSERA_API Context final {
public:
    ~Context() = default;

    static void init();
    static Context& context() { return *instance_; }
    static void quit();

    void initialize(const Manager& manager);
    void destroy();

public:
    vk::Instance instance;
    vk::SurfaceKHR surface;

private:
    void createInstance();
    void createSurface(const Manager& manager);

private:
    Context() = default;

    static std::unique_ptr<Context> instance_;
};

} // namespace Ysera