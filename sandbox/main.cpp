#include <Ysera.hpp>

int main() {

    auto config = Ysera::Configuration{};
    config.window_info = Ysera::WindowInfo{"sanbox", 900, 900};

    auto manager = std::make_unique<Ysera::Manager>(config);

    manager->initializeRenderer();

    while (!manager->getWindow()->shouldClose()) {
        manager->getWindow()->pollEvents();
    }

    manager->destroyRenderer();

    manager.reset();

    return 0;
}