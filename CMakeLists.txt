cmake_minimum_required(VERSION 3.20)

project(engine_lab2
    DESCRIPTION "Simple command engine with method wrappers"
    VERSION 0.1.0
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(engine_lab2
    main.cpp
    engine/Engine.cpp
    modules/MathModule.cpp
)

target_include_directories(engine_lab2
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/engine
        ${CMAKE_CURRENT_SOURCE_DIR}/modules
        ${CMAKE_CURRENT_SOURCE_DIR}/wrapper
        ${CMAKE_CURRENT_SOURCE_DIR}/showcase
)
