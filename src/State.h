//
// Created by Adam on 11.06.2020.
//

#ifndef GENERIC_GIERKA_STATE_H
#define GENERIC_GIERKA_STATE_H

//#include "Player.h"
#include "GraphicsSettings.h"

class State;

class StateData {
public:
    // variables
    float gridSize;
    sf::RenderWindow* window;
    GraphicsSettings* gfxSettings;
    std::map<std::string, int>* supportedKeys;
    std::stack<State*>* states;
};
class State {
private:

protected:
    // variables
    StateData* stateData;
    std::stack<State*>* states;
    sf::RenderWindow* window;
    std::map<std::string, int>* supportedKeys;
    std::map<std::string, int> keybinds;
    bool quit;
    bool paused;
    float keytime;
    float keytimeMax;
    float gridSize;

    sf::Vector2i mousePosScreen;
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;
    sf::Vector2i mousePosGrid;

    // resources
    std::map<std::string, sf::Texture> textures;

    // functions
    virtual void initKeybinds() = 0;

public:
    explicit State(StateData* state_data);
    virtual ~State();

    //Accessors
    const bool& getQuit() const;
    bool getKeytime();

    //Functions
    void endState();
    void pauseState();
    void unpauseState();

    virtual void updateMousePositions(sf::View* view);
    virtual void updateKeytime(const float& tm);
    virtual void updateInput(const float& tm) = 0;
    virtual void update(const float& tm) = 0;
    virtual void render(sf::RenderTarget* target) = 0;
};


#endif //GENERIC_GIERKA_STATE_H
