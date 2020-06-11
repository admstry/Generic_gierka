cmake_minimum_required(VERSION 3.16)
project(Generic_gierka)

set(CMAKE_CXX_STANDARD 17)
set(SFML_DIR "C:/SFML-2.5.1/lib/cmake/SFML")
find_package(SFML 2.5 COMPONENTS graphics audio system window REQUIRED)

add_executable(Generic_gierka main.cpp)
target_link_libraries(Generic_gierka sfml-graphics sfml-audio sfml-system sfml-window)
target_precompile_headers(Generic_gierka PUBLIC src/pch.h)