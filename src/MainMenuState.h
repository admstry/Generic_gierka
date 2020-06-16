//
// Created by Adam on 14.06.2020.
//

#ifndef GENERIC_GIERKA_MAINMENUSTATE_H
#define GENERIC_GIERKA_MAINMENUSTATE_H

#include "State.h"
#include "SettingsState.h"
#include "GameState.h"
#include "Gui.h"

class State;
class Gui;

class MainMenuState : public State {
private:
    sf::Texture backgroundTexture;
    sf::RectangleShape background;
    sf::Font font;

    std::map<std::string, gui::Button*> buttons;

    // functions
    void initVariables();
    void initFonts();
    void initKeyBinds() override ;
    void initGui();
    void resetGui();

public:
    explicit MainMenuState(StateData* state_data);
    ~MainMenuState() override;

    // functions
    void updateInput(const float& tm) override;
    void updateButtons();
    void update(const float & tm) override;
    void renderButtons(sf::RenderTarget &target);
    void render(sf::RenderTarget *target) override;
};


#endif //GENERIC_GIERKA_MAINMENUSTATE_H
