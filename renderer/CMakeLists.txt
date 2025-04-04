project(renderer)

file(GLOB_RECURSE sources "src/*.cpp")
file(GLOB_RECURSE headers "include/*.hpp")

add_library(${PROJECT_NAME} STATIC ${sources} ${headers})
target_include_directories(${PROJECT_NAME} PUBLIC ./include)
target_link_libraries(${PROJECT_NAME} PUBLIC Vulkan::Vulkan)

target_link_libraries(${PROJECT_NAME} PUBLIC spdlog::spdlog)