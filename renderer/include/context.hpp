#pragma once

#include "base/configuration.hpp"

namespace Ysera {

class YSERA_API Manager;
class YSERA_API Context final {
public:
    ~Context() = default;

    static void init();
    static Context& context() { return *instance_; }
    static void quit();

    void initialize(const Manager& manager);
    void destroy();

private:
    Context() = default;

    static std::unique_ptr<Context> instance_;
};

} // namespace Ysera