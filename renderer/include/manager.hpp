#pragma once

#include "core/log.hpp"
#include "core/window.hpp"

namespace Ysera {

class Manager {
public:
    Manager(const WindowInfo& info);
    ~Manager();

    void initializeRenderer();
    bool shouldClose() const { return window_->shouldClose(); }
    void pollEvents() const { window_->pollEvents(); }
    void destroyRenderer();

private:
    std::unique_ptr<Window> window_;
};

} // namespace Ysera