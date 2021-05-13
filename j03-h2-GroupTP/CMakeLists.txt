cmake_minimum_required(VERSION 3.17)
set(
        project_name
        j03-h2-GroupTP
)
file(
        GLOB_RECURSE
        source_file
        src/*
)
#si besoin de repertoire assets
file(
        COPY
        assets
        DESTINATION
       ${CMAKE_BINARY_DIR}
)
project(${project_name})
set(CMAKE_CXX_STANDARD 17)
add_executable(${project_name} ${source_file} src/managers/WallManager.cpp src/managers/WallManager.h)
if (WIN32)
    target_link_libraries(
            ${project_name}
            -lmingw32
            -lSDL2main
            -lSDL2
            -lSDL2_image
            -lSDL2_mixer
            -lopengl32
            -lglu32
            -lSDL2_ttf
    )
endif ()
if(UNIX)
    target_link_libraries(
            ${project_name}
            -lSDL2main
            -lSDL2
            -lSDL2_image
            -lSDL2_mixer
            -lGL
            -lGLU
            -lSDL2_ttf
    )
endif()