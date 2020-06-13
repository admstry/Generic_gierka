//
// Created by Adam on 11.06.2020.
//

#ifndef GENERIC_GIERKA_MAINMENUSTATE_H
#define GENERIC_GIERKA_MAINMENUSTATE_H

#include "State.h"
#include "SettingsState.h"
#include "Gui.h"

class MainMenuState :
        public State {
private:
    //Variables
    sf::Texture backgroundTexture;
    sf::RectangleShape background;
    sf::Font font;

    sf::RectangleShape btnBackground;
    std::map<std::string, gui::Button*> buttons;

    //Functions
    void initVariables();
    void initFonts();
    void initKeybinds() override;
    void initGui();
    void resetGui();

public:
    explicit MainMenuState(StateData* state_data);
    ~MainMenuState() override;

    //Functions
    void updateInput(const float& dt) override;
    void updateButtons();
    void update(const float& tm) override;
    void renderButtons(sf::RenderTarget& target);
    void render(sf::RenderTarget* target) override;
};


#endif //GENERIC_GIERKA_MAINMENUSTATE_H
