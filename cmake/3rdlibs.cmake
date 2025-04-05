option(SPDLOG_BUILD_SHARED "Build shared library" ON)
option(SPDLOG_BUILD_PIC "Build position independent code (-fPIC)" ON)
add_subdirectory(3rdlibs/spdlog)

option(BUILD_SHARED_LIBS "Build shared libraries" ON)
option(GLFW_BUILD_EXAMPLES "Build the GLFW example programs" OFF)
option(GLFW_BUILD_TESTS "Build the GLFW test programs" OFF)
option(GLFW_BUILD_DOCS "Build the GLFW documentation" OFF)
option(GLFW_INSTALL "Generate installation target" OFF)
add_subdirectory(3rdlibs/glfw)