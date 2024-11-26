cmake_minimum_required(VERSION 3.29)
project(EjercicioCasoFinalIntegradorTema3)

set(CMAKE_CXX_STANDARD 14)

include_directories(script_loader)

add_executable(EjercicioCasoFinalIntegradorTema3
    script_loader/script_loader.cpp
    script_loader/script_loader.h
    main.cpp)
