//
// Created by Adam on 14.06.2020.
//

#ifndef GENERIC_GIERKA_STATE_H
#define GENERIC_GIERKA_STATE_H

#include "Graphics.h"

class State;
class Graphics;

class StateData {
public:
    // variables
    float gridSize;
    sf::RenderWindow* window;
    Graphics* settings;
    std::map<std::string, int>* supportedKeys;
    std::stack<State*>* states;
};

class State {
private:
protected:
    // variables
    StateData *stateData;
    std::stack<State*>* states;
    sf::RenderWindow *window;
    std::map<std::string, int>* supportedKeys;
    std::map<std::string, int> keyBinds;
    bool quit;
    bool paused;
    float keyTime;
    float keyTimeMax;
    float gridSize;

    sf::Vector2i mousePositionScreen;
    sf::Vector2i mousePositionWindow;
    sf::Vector2f mousePositionView;
    sf::Vector2i mousePositionGrid;

    std::map<std::string, sf::Texture> textures;

    // functions

    virtual void initKeyBinds() = 0;

public:
    explicit State(StateData *state_data);
    virtual ~State();

    // functions
    [[nodiscard]] bool getQuit() const;
    bool getKeyTime();

    void endState();
    void pauseState();
    void unpauseState();

    virtual void updateMousePosition(sf::View *view);
    virtual void updateKeyTime(const float & tm);
    virtual void updateInput(const float & tm) = 0;
    virtual void update(const float & tm) = 0;
    virtual void render(sf::RenderTarget *target) = 0;
};


#endif //GENERIC_GIERKA_STATE_H
