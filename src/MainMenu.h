//
// Created by Adam on 14.06.2020.
//

#ifndef GENERIC_GIERKA_MAINMENU_H
#define GENERIC_GIERKA_MAINMENU_H

#include "State.h"
#include "Settings.h"
#include "Game.h"
#include "Gui.h"

class State;

class MainMenu : public State {
private:
    // variables
    sf::Texture backgroundTexture;
    sf::RectangleShape background;
    sf::Font font;
    sf::Music music;

    std::map<std::string, gui::Button*> buttons;

    // functions
    void initVariables();
    void initFonts();
    void initKeyBinds() override;
    void initGui();
    void resetGui();

public:
    explicit MainMenu(StateData* state_data);
    ~MainMenu() override;

    // functions
    void updateInput(const float& tm) override;
    void updateButtons();
    void update(const float & tm) override;
    void renderButtons(sf::RenderTarget &target);
    void render(sf::RenderTarget *target) override;
};


#endif //GENERIC_GIERKA_MAINMENU_H
