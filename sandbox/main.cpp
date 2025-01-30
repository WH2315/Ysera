#include <Ysera.hpp>

int main() {

    auto window_info = Ysera::WindowInfo{"sanbox", 900, 900};
    auto manager = std::make_unique<Ysera::Manager>(window_info);

    while (!manager->shouldClose()) {
        manager->pollEvents();
    }

    manager.reset();

    return 0;
}