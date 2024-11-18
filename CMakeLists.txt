cmake_minimum_required(VERSION 3.28)
project(Aero_Fighters)
add_compile_definitions(_DEBUG)

set(CMAKE_CXX_STANDARD 20)
set(BUILD_SHARED_LIBS OFF)
set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR /usr/local/lib/cmake/SFML)
find_package(SFML 2.6 COMPONENTS graphics audio REQUIRED)
file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.hpp" "src/*.h")

add_executable(Aero_Fighters ${SOURCES})

target_link_libraries(Aero_Fighters PUBLIC
        debug sfml-audio
        debug sfml-graphics
        debug sfml-system
        debug sfml-window
        pthread
        dl
        ${OPENGL_gl_LIBRARY}
)