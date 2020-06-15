//
// Created by Adam on 14.06.2020.
//

#ifndef GENERIC_GIERKA_STATE_H
#define GENERIC_GIERKA_STATE_H

#include "GraphicsSettings.h"

class State;
class GraphicsSettings;

class StateData {
public:
    // variables
    float gridSize;
    sf::RenderWindow* window;
    GraphicsSettings gfxSettings;
    std::map<std::string, int> supportedKeys;
    std::stack<State*>* states;
};

class State {
private:
protected:
    StateData *stateData;
    std::stack<State*>* states;
    sf::RenderWindow *window;
    std::map<std::string, int> supportedKeys;
    std::map<std::string, int> keybinds;
    bool quit;
    bool paused;
    float keyTime;
    float keyTimeMax;
    float gridSize;

    sf::Vector2i mousePosScreen;
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;
    sf::Vector2i mousePosGrid;

    std::map<std::string, sf::Texture> textures;

    // functions

    virtual void initKeyBinds() = 0;

public:
    explicit State(StateData *state_data);
    virtual ~State();

    // accessors

    bool getQuit() const;
    bool getKeyTime();

    // functions

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
