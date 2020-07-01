//
// Created by Adam on 14.06.2020.
//

#ifndef GENERIC_GIERKA_SETTINGS_H
#define GENERIC_GIERKA_SETTINGS_H

#include "State.h"
#include "Gui.h"

class Settings : public State {
private:
    // variables
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
    explicit Settings(StateData* state_data);
    ~Settings() override;

    // functions
    void updateGui(const float& tm);
    void updateInput(const float & tm) override;
    void update(const float& dt) override;
    void renderGui(sf::RenderTarget& target);
    void render(sf::RenderTarget* target) override;


};


#endif //GENERIC_GIERKA_SETTINGS_H
