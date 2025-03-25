option(SPDLOG_BUILD_PIC "Build position independent code (-fPIC)" ON)
option(SPDLOG_BUILD_EXAMPLE "Build example" OFF)
option(SPDLOG_INSTALL "Generate the install target" OFF)
add_subdirectory(3rdlibs/spdlog)