#pragma once

#include "dllexport.hpp"
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <string>

namespace Ysera {

struct YSERA_API WindowInfo {
    std::string title;
    uint32_t width, height;
};

class YSERA_API Window final {
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