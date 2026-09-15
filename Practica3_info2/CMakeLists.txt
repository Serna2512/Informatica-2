cmake_minimum_required(VERSION 3.16)

project(Practica3_info2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Practica3_info2 main.cpp)

include(GNUInstallDirs)
install(TARGETS Practica3_info2
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
