cmake_minimum_required(VERSION 3.26)
project(test_project C)

set(CMAKE_C_STANDARD 11)

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

target_link_libraries(
        test_project PRIVATE
        /Library/Frameworks/SDL2.framework/Versions/A/SDL2
        /Library/Frameworks/SDL2_image.framework/Versions/A/SDL2_image
        /Library/Frameworks/SDL2_ttf.framework/Versions/A/SDL2_ttf
)

target_include_directories(
        test_project PRIVATE
        /Library/Frameworks/SDL2.framework/Versions/A/Headers
        /Library/Frameworks/SDL2_image.framework/Versions/A/Headers
        /Library/Frameworks/SDL2_ttf.framework/Versions/A/Headers
)






