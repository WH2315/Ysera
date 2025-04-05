project(renderer)

option(YSERA_BUILD_SHARED "build shared library" ON)

file(GLOB_RECURSE sources "src/*.cpp")
file(GLOB_RECURSE headers "include/*.hpp")

macro(target_library TARGET_NAME)
    target_sources(${TARGET_NAME} PRIVATE ${sources} ${headers})
    target_include_directories(${TARGET_NAME} PUBLIC ./include)
    target_link_libraries(${TARGET_NAME} PUBLIC Vulkan::Vulkan glfw)
    target_link_libraries(${TARGET_NAME} PUBLIC spdlog::spdlog)

    if(WIN32)
        target_compile_definitions(${TARGET_NAME} PUBLIC PLATFORM_WINDOWS)
    endif()
endmacro()

if(YSERA_BUILD_SHARED)
    set(CMAKE_POSITION_INDEPENDENT_CODE ON)

    set(SHARED_LIB_NAME ${PROJECT_NAME}-shared)
    add_library(${SHARED_LIB_NAME} SHARED)

    target_compile_definitions(${SHARED_LIB_NAME} PRIVATE YSERA_BUILD_SHARED)
    target_compile_definitions(${SHARED_LIB_NAME} PRIVATE YSERA_DLLEXPORT)
    target_library(${SHARED_LIB_NAME})

    add_library(${PROJECT_NAME} ALIAS ${SHARED_LIB_NAME})
    message(STATUS "Build Shared Library")
else()
    set(STATIC_LIB_NAME ${PROJECT_NAME}-static)
    add_library(${STATIC_LIB_NAME} STATIC)

    target_library(${STATIC_LIB_NAME})

    add_library(${PROJECT_NAME} ALIAS ${STATIC_LIB_NAME})
    message(STATUS "Build Static Library")
endif()

function(COPYDLL TARGET_NAME PATH)
    set(POSITION ".")

    if(MSVC)
        set(POSITION $<CONFIG>)
    endif()

    add_custom_command(
        TARGET ${TARGET_NAME}
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${PATH}/3rdlibs/spdlog/${POSITION}/spdlogd.dll
        ${PATH}/3rdlibs/glfw/src/${POSITION}/glfw3.dll
        $<$<BOOL:${YSERA_BUILD_SHARED}>:${PATH}/renderer/${POSITION}/renderer-shared.dll>
        $<TARGET_FILE_DIR:${TARGET_NAME}>
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    )
endfunction()