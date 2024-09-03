cmake_minimum_required(VERSION 3.29)
project(Aero_Fighters)
add_compile_definitions(_DEBUG)

set(CMAKE_CXX_STANDARD 20)
set(BUILD_SHARED_LIBS OFF)
set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR /usr/local/lib/cmake/SFML)
find_package(SFML 2.6 COMPONENTS graphics audio REQUIRED)

add_executable(Aero_Fighters
    src/Game/Game.cpp
    src/Game/Game.h
    src/Level/Level.cpp
    src/Level/Level.h
    src/Object/Collectable/Collectable.cpp
    src/Object/Collectable/Collectable.h
    src/Object/Enemy/Air/Air.cpp
    src/Object/Enemy/Air/Air.h
    src/Object/Enemy/Boss/Boss.cpp
    src/Object/Enemy/Boss/Boss.h
    src/Object/Enemy/Land/Land.cpp
    src/Object/Enemy/Land/Land.h
    src/Object/Enemy/Enemy.cpp
    src/Object/Enemy/Enemy.h
    src/Object/Player/Player.cpp
    src/Object/Player/Player.h
    src/Object/Projectile/Explosion/Explosion.cpp
    src/Object/Projectile/Explosion/Explosion.h
    src/Object/Projectile/Projectile.cpp
    src/Object/Projectile/Projectile.h
    src/Object/Object.cpp
    src/Object/Object.h
    src/ControllerStuff.hpp
    src/Main.cpp)

target_link_libraries(Aero_Fighters PUBLIC
        debug sfml-audio
        debug sfml-graphics
        debug sfml-system
        debug sfml-window
        pthread
        dl
        ${OPENGL_gl_LIBRARY}
)