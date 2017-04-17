cmake_minimum_required(VERSION 3.6)
project(CartDS)

option(PI_BUILD "Is this being built on a pi?" OFF)

set(SDL2_INCLUDE_DIR /usr/include/SDL2)
if (PI_BUILD)
    set(SDL2_LIBRARY /usr/lib/arm-linux-gnueabihf/libSDL2.so) #TODO Find the path of sdl2 on the pi
else()
    set(SDL2_LIBRARY /usr/lib/x86_64-linux-gnu/libSDL2.so)
endif()

include_directories(${SDL2_INCLUDE_DIR})

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(lib)

file(GLOB SOURCE_FILES
        "*.hpp"
        "*.cpp")

add_executable(CartDS ${SOURCE_FILES})
target_link_libraries(CartDS pthread libds wiringpi ${SDL2_LIBRARY}) #Link libds and wiringpi to the main executable