#pragma once

#include "core/window.hpp"
#include <memory>

namespace Ysera {

class Manager {
public:
    Manager(const WindowInfo& info);
    ~Manager();

    bool shouldClose() const { return window_->shouldClose(); }
    void pollEvents() const { window_->pollEvents(); }

    void initializeRenderer();
    void destroyRenderer();

private:
    std::unique_ptr<Window> window_;
};

} // namespace Ysera