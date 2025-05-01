#pragma once

#include "base/configuration.hpp"

namespace Ysera {

class YSERA_API Manager {
public:
    Manager(const Configuration& config);
    ~Manager();

    void initializeRenderer();
    void destroyRenderer();

    auto getWindow() const { return window_.get(); }

private:
    std::unique_ptr<Window> window_;
};

extern Configuration g_config;
class Context;
extern Context* g_manager;

} // namespace Ysera