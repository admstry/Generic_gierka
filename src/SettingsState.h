//
// Created by Adam on 14.06.2020.
//

#ifndef GENERIC_GIERKA_SETTINGSSTATE_H
#define GENERIC_GIERKA_SETTINGSSTATE_H

#include "State.h"
#include "Gui.h"

class SettingsState : public State {
private:
    sf::Texture backgroundTexture;
    sf::RectangleShape background;
    sf::Font font;

    std::map<std::string, gui::Button*> buttons;
    std::map<std::string, gui::DropDownList*> dropDownLists;
    sf::Text optionsText;

    std::vector<sf::VideoMode> modes;

    // functions
    void initVariables();
    void initFonts();
    void initKeyBinds() override;
    void initGui();
    void resetGui();
public:
    explicit SettingsState(StateData* state_data);
    ~SettingsState() override;

    // functions
    void updateInput(const float& tm) override;
    void updateGui(const float& tm);
    void update(const float& dt) override;
    void renderGui(sf::RenderTarget& target);
    void render(sf::RenderTarget* target) override;


};


#endif //GENERIC_GIERKA_SETTINGSSTATE_H
