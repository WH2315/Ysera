option(SPDLOG_BUILD_PIC "Build position independent code (-fPIC)" ON)
add_subdirectory(3rdlibs/spdlog)

set(GLFW_LIBRARY_TYPE SHARED)
add_subdirectory(3rdlibs/glfw)