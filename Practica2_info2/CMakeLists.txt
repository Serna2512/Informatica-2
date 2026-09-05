cmake_minimum_required(VERSION 3.16)

project(Practica2_info2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Practica2_info2 main.cpp
    funciones.cpp
    existentes.h)

include(GNUInstallDirs)
install(TARGETS Practica2_info2
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
