cmake_minimum_required(VERSION 3.16)

project(Practica4_info2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Practica4_info2 main.cpp
    enrutador.h
    enrutador.cpp
    red.h
    red.cpp
    camino.cpp
    camino.h)

include(GNUInstallDirs)
install(TARGETS Practica4_info2
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
