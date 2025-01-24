#include <Ysera.hpp>

int main() {

    auto manager = std::make_unique<Ysera::Manager>();

    manager.reset();

    return 0;
}