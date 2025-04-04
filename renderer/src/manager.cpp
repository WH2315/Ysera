#include "manager.hpp"
#include "core/log.hpp"

namespace Ysera {

Manager::Manager(const WindowInfo& info) {
    g_log = new Log;
    LOGI("Initialize Engine!")
    window_ = std::make_unique<Window>(info);
}

void Manager::initializeRenderer() {
}

void Manager::destroyRenderer() {
}

Manager::~Manager() {
    window_.reset();
    LOGI("Destroy Engine!")
    g_log = nullptr;
    delete g_log;
}

} // namespace Ysera