cmake_minimum_required(VERSION 3.17)
project(DonkeyC C)

set(CMAKE_C_STANDARD 99)
set(SDL2_INCLUDE_DIR C:/Users/adrii/OneDrive/Escritorio/Chango/SDL/include)
set(SDL2_LIB_DIR C:/Users/adrii/OneDrive/Escritorio/Chango/SDL/lib/x86)

include_directories(${SDL2_INCLUDE_DIR})
link_directories(${SDL2_LIB_DIR})

link_libraries(ws2_32 wsock32)

add_executable(DonkeyC main.c graphics.c graphics.h)

target_link_libraries(${PROJECT_NAME} SDL2main SDL2 SDL2_image)