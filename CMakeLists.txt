cmake_minimum_required(VERSION 3.16)
project(Generic_gierka)

set(CMAKE_CXX_STANDARD 17)
set(SFML_DIR "C:/SFML-2.5.1/lib/cmake/SFML")
find_package(SFML 2.5 COMPONENTS graphics audio system window REQUIRED)

add_executable(Generic_gierka src/main.cpp src/Game.cpp src/Game.h src/State.cpp src/State.h src/MainMenuState.cpp src/MainMenuState.h src/Gui.cpp src/Gui.h src/GraphicsSettings.cpp src/GraphicsSettings.h src/SettingsState.cpp src/SettingsState.h)
target_link_libraries(Generic_gierka sfml-graphics sfml-audio sfml-system sfml-window)
target_precompile_headers(Generic_gierka PUBLIC src/pch.h)