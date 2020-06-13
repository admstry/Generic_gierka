//
// Created by Adam on 13.06.2020.
//

#ifndef GENERIC_GIERKA_SETTINGSSTATE_H
#define GENERIC_GIERKA_SETTINGSSTATE_H

#include "State.h"
#include "Gui.h"

class SettingsState :
        public State
{
private:
    //Variables
    sf::Texture backgroundTexture;
    sf::RectangleShape background;
    sf::Font font;

    std::map<std::string, gui::Button*> buttons;
    std::map<std::string, gui::DropDownList*> dropDownLists;

    sf::Text optionsText;

    std::vector<sf::VideoMode> modes;

    //Functions
    void initVariables();
    void initFonts();
    void initKeybinds() override;
    void initGui();
    void resetGui();

public:
    explicit SettingsState(StateData* state_data);
    ~SettingsState() override;

    //Accessors

    //Functions
    void updateInput(const float& dt) override;
    void updateGui(const float& dt);
    void update(const float& dt) override;
    void renderGui(sf::RenderTarget& target);
    void render(sf::RenderTarget* target) override;
};


#endif //GENERIC_GIERKA_SETTINGSSTATE_H
