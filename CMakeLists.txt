cmake_minimum_required(VERSION 3.26)
project(test_project C)

set(CMAKE_C_STANDARD 11)

FIND_PACKAGE(SDL2 REQUIRED)
FIND_PACKAGE(SDL2_Image)
FIND_PACKAGE(SDL2_Mixer)
FIND_PACKAGE(SDL2_TTF)
FIND_PACKAGE(SDL2_NET)

add_executable(test_project main.c
        structs.h
        defs.h
        init.c
        render.c
        processInput.c
        init.h
        render.h
        processInput.h
        main.h)

target_link_libraries(test_project ${SDL2_LIBRARIES})
include_directories(SDL2 ${SDL2_INCLUDE_DIRS})
include_directories(SDL2_ttf ${SDL2TTF_INCLUDE_DIR})
include_directories(SDL2_image ${SDL2_IMAGE_INCLUDE_DIR})
include_directories(SDL2_mixer ${SDL2Mixer_INCLUDE_DIR})
include_directories(SDL_net ${SDL2Net_INCLUDE_DIR})





