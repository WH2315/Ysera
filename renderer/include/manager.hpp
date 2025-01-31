#pragma once

#include "base/configuration.hpp"
#include "context.hpp"

namespace Ysera {

class Manager {
public:
    Manager(const Configuration& config);
    ~Manager();

    void initializeRenderer();
    void destroyRenderer();

    auto getWindow() const { return window_.get(); }

private:
    std::shared_ptr<Configuration> config_;
    std::unique_ptr<Window> window_;
};

extern Configuration g_config;
extern Context* g_manager;

} // namespace Ysera