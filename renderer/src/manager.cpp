#include "manager.hpp"
#include "core/log.hpp"

namespace Ysera {

Manager::Manager() {
    g_log = new Log;
    LOGI("Initialize Engine!")
}

Manager::~Manager() {
    LOGI("Destroy Engine!")
    g_log = nullptr;
    delete g_log;
}

} // namespace Ysera