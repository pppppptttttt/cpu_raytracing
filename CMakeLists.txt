cmake_minimum_required(VERSION 3.7)
project(CPURT VERSION 0.1.0 LANGUAGES C CXX)

set(SOURCE src/main.cpp
           src/renderer/renderer.cpp
           src/renderer/core/sdl_core.cpp
           src/renderer/core/x11_core.cpp
           src/renderer/shapes/shapes.cpp
           src/renderer/material/material.cpp)
find_package(SDL2 REQUIRED)
find_package(X11 REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

add_executable(CPURT ${SOURCE})
target_link_libraries(CPURT ${SDL2_LIBRARIES} ${X11_LIBRARIES})