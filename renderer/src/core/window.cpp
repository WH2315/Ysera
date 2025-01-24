#include "core/window.hpp"
#include "core/log.hpp"

namespace Ysera {

Window::Window(const WindowInfo& info) {
    LOGI("Create window: ({}, {}, {})", info.title, info.width, info.height)

    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    window_ = glfwCreateWindow(info.width, info.height, info.title.c_str(),
                               nullptr, nullptr);
}

Window::~Window() {
    glfwDestroyWindow(window_);
    window_ = nullptr;
    glfwTerminate();
}

} // namespace Ysera