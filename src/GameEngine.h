//
// Created by Adam on 11.06.2020.
//

#ifndef GENERIC_GIERKA_GAMEENGINE_H
#define GENERIC_GIERKA_GAMEENGINE_H

#include "MainMenu.h"
#include "Graphics.h"

class MainMenu;
class Graphics;

class GameEngine {
private:
    // variables
    Graphics settings;
    StateData stateData{};
    sf::RenderWindow *window;
    sf::Event sfEvent{};
    sf::Clock tmClock;
    float tm;
    std::stack<State*> states;
    std::map<std::string, int> supportedKeys;
    float gridSize;

public:
    // initialization
    void initGraphicsSettings();
    void initWindow();
    void initKeys();
    void initStateData();
    void initStates();
    GameEngine();
    virtual ~GameEngine();
    // functions
    static void endApplication();
    // update
    void updateTm();
    void updateSFMLEvents();
    void update();

    // main
    void render();
    void run();
};


#endif //GENERIC_GIERKA_GAMEENGINE_H
