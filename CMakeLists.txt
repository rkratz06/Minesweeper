cmake_minimum_required(VERSION 3.29.6)
project(Minesweeper)

set(CMAKE_CXX_STANDARD 20)

set(SFML_DIR "C:/Libraries/SFML-2.5.1/lib/cmake/SFML")
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(Minesweeper minesweeper.cpp
        Button.cpp
        Button.h
        GameState.cpp
        GameState.h
        Tile.cpp
        Tile.h
        Toolbox.cpp
        Toolbox.h
        minesweeper.h)

target_link_libraries(Minesweeper sfml-graphics sfml-audio)