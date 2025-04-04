#pragma once

namespace Ysera {

class Manager {
public:
    Manager();
    ~Manager();

    void initializeRenderer();
    void destroyRenderer();
};

} // namespace Ysera