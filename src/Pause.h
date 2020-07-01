//
// Created by Adam on 01.07.2020.
//

#ifndef GENERIC_GIERKA_PAUSE_H
#define GENERIC_GIERKA_PAUSE_H

#include"Gui.h"

class Pause
{
private:
    // variables
    sf::Font& font;
    sf::Text menuText;

    sf::RectangleShape background;
    sf::RectangleShape container;

    std::map<std::string, gui::Button*> buttons;


public:
    Pause(sf::VideoMode& vm, sf::Font& font);
    virtual ~Pause();

    [[maybe_unused]] std::map<std::string, gui::Button*>& getButtons();

    // functions
    bool isButtonPressed(const std::string& key);
    void addButton(const std::string& key,
                   float y,
                   float width,
                   float height,
                   unsigned char_size,
                   const std::string& text);
    void update(const sf::Vector2i& mousePosWindow);
    void render(sf::RenderTarget& target);
};


#endif //GENERIC_GIERKA_PAUSE_H
