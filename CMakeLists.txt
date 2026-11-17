cmake_minimum_required(VERSION 3.16)
project(Stereometria3D VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Główna biblioteka logiki (bryły, matematyka, zadania JSON - niezależna od OpenGL do łatwych testów)
add_library(stereometria_core
    src/tasks/TaskValidator.cpp
)

target_include_directories(stereometria_core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Główny plik wykonywalny aplikacji
add_executable(Stereometria3D
    src/main.cpp
)

target_link_libraries(Stereometria3D PRIVATE stereometria_core)
