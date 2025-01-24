#include <Ysera.hpp>

int main() {

    auto window_info = Ysera::WindowInfo{"sandbox", 900, 900};
    auto manager = std::make_unique<Ysera::Manager>(window_info);

    manager->initializeRenderer();

    while (!manager->shouldClose()) {
        manager->pollEvents();
    }

    manager->destroyRenderer();

    manager.reset();

    return 0;
}