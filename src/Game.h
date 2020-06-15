//
// Created by Adam on 11.06.2020.
//

#ifndef GENERIC_GIERKA_GAME_H
#define GENERIC_GIERKA_GAME_H

#include "MainMenuState.h"
#include "GraphicsSettings.h"

class MainMenuState;
class GraphicsSettings;

class Game {
private:
    // variables
    GraphicsSettings gfxSettings;
    StateData stateData;
    sf::RenderWindow *window;
    sf::Event sfEvent;
    sf::Clock tmClock;
    float tm;
    std::stack<State*> states;
    std::map<std::string, int> supportedKeys;
    float gridSize;

public:
    // initialization
    void initVariables();
    void initGraphicsSettings();
    void initWindow();
    void initKeys();
    void initStateData();
    void initStates();
    Game();
    virtual ~Game();
    // functions
    static void endApplication();
    // update
    void updateTm();
    void updateSFMLEvents();
    void update();
    // render
    void render();
    // core
    void run();
};


#endif //GENERIC_GIERKA_GAME_H
