#include "context.hpp"
#include "manager.hpp"

namespace Ysera {

std::unique_ptr<Context> Context::instance_ = nullptr;

void Context::init() {
    if (!instance_.get()) {
        instance_.reset(new Context);
    }
}

void Context::quit() { instance_.reset(); }

void Context::initialize(const Manager& manager) {
    LOGI("Vulkan Context Initialized!")
}

void Context::destroy() {
    LOGI("Vulkan Context Destroyed!")
}

} // namespace Ysera