cmake_minimum_required(VERSION 3.16)
project(Generic_gierka)

set(CMAKE_CXX_STANDARD 17)
set(SFML_DIR "C:/SFML-2.5.1/lib/cmake/SFML")
find_package(SFML 2.5 COMPONENTS graphics audio system window REQUIRED)

add_executable(Generic_gierka src/main.cpp src/GameEngine.cpp src/GameEngine.h src/State.cpp src/State.h src/MainMenu.cpp src/MainMenu.h src/Gui.cpp src/Gui.h src/Graphics.cpp src/Graphics.h src/Settings.cpp src/Settings.h src/TileMap.cpp src/TileMap.h src/Game.cpp src/Game.h src/Entity.cpp src/Entity.h src/Player.cpp src/Player.h src/Animate.cpp src/Animate.h src/Movement.cpp src/Movement.h src/Spider.cpp src/Spider.h src/HitBox.cpp src/HitBox.h src/Weapon.cpp src/Weapon.h src/Pause.cpp src/Pause.h)
target_link_libraries(Generic_gierka sfml-graphics sfml-audio sfml-system sfml-window)
target_precompile_headers(Generic_gierka PUBLIC src/pch.h)