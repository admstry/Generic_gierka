//
// Created by Adam on 11.06.2020.
//

#ifndef GENERIC_GIERKA_GAME_H
#define GENERIC_GIERKA_GAME_H

#include "State.h"

class Game {
private:
    // variables
    StateData stateData;
    sf::RenderWindow *window;
    sf::Event sfEvent;
    sf::Clock tmClock;
    float tm;
    std::stack<State*> states;
    std::map<std::string, int> supportedKeys;
    float gridSize;

public:
    // initalization
    void initVariables();
    void initWindow();
    void initKeys();
    void initStateData();
    void initStates();
    Game();
    virtual ~Game();
    // functions
    void endApplication();
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
