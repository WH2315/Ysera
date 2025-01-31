#pragma once

#include <GLFW/glfw3.h>
#include <string>

namespace Ysera {

struct WindowInfo {
    std::string title;
    uint32_t width, height;
};

class Window final {
public:
    Window(const WindowInfo& info);
    ~Window();

    bool shouldClose() const { return glfwWindowShouldClose(window_); }
    void pollEvents() const { glfwPollEvents(); }

    auto window() const { return window_; }

private:
    GLFWwindow* window_;
};

} // namespace Ysera