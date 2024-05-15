cmake_minimum_required(VERSION 3.5)

project(Praktikum5 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Praktikum5 main.cpp
    battleship.h battleship.cpp
    gameboard.h gameboard.cpp
    part.h part.cpp
    player.h player.cpp
    ship.h ship.cpp
    random.h random.cpp
    aicotroller.h aicotroller.cpp)

include(GNUInstallDirs)
install(TARGETS Praktikum5
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
