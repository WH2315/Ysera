project(sandbox)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE renderer)

if(WIN32)
    COPYDLL(${PROJECT_NAME} ..)
endif()