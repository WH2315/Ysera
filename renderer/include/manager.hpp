#pragma once

#include "dllexport.hpp"
#include "base/configuration.hpp"
#include "context.hpp"

namespace Ysera {

class YSERA_API Manager {
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

YSERA_API extern Configuration g_config;
YSERA_API extern Context* g_manager;

} // namespace Ysera