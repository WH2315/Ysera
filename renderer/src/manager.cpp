#include "manager.hpp"

namespace Ysera {

Configuration g_config;
Context* g_manager = nullptr;

Manager::Manager(const Configuration& config) {
    g_log = new Log;
    LOGI("Initialize Engine!")
    g_config = config;
    window_ = std::make_unique<Window>(config.window_info);
}

void Manager::initializeRenderer() {
    Context::init();
    g_manager = &Context::context();
    g_manager->initialize(*this);
}

void Manager::destroyRenderer() {
    g_manager->destroy();
    g_manager = nullptr;
    delete g_manager;
    Context::quit();
}

Manager::~Manager() {
    window_.reset();
    LOGI("Destroy Engine!")
    g_log = nullptr;
    delete g_log;
}

} // namespace Ysera