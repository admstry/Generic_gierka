//
// Created by Adam on 18.06.2020.
//
#include "pch.h"
#include "Pause.h"

Pause::Pause(sf::VideoMode& vm, sf::Font& font)
        : font(font) {
    // initialize background
    background.setSize(sf::Vector2f(static_cast<float>(vm.width),static_cast<float>(vm.height)));
    background.setFillColor(sf::Color(20, 20, 20, 100));

    // initialize container
    container.setSize(sf::Vector2f(static_cast<float>(vm.width) / 4.f,static_cast<float>(vm.height) - gui::p2pY(9.3f, vm)));
    container.setFillColor(sf::Color(20, 20, 20, 200));
    container.setPosition(static_cast<float>(vm.width) / 2.f - container.getSize().x / 2.f,30.f);

    // initialize text
    menuText.setFont(font);
    menuText.setFillColor(sf::Color(255, 255, 255, 200));
    menuText.setCharacterSize(gui::calcCharSize(vm));
    menuText.setString("PAUSED");
    menuText.setPosition(container.getPosition().x + container.getSize().x / 2.f - menuText.getGlobalBounds().width / 2.f,container.getPosition().y + gui::p2pY(4.f, vm));
}

Pause::~Pause() {
    auto it = buttons.begin();
    for (it = buttons.begin(); it != buttons.end(); ++it) {
        delete it->second;
    }
}

[[maybe_unused]] std::map<std::string, gui::Button*>& Pause::getButtons() {
    return buttons;
}

//Functions
bool Pause::isButtonPressed(const std::string& key) {
    return buttons[key]->isPressed();
}

void Pause::addButton(
        const std::string& key,
        const float y,
        const float width,
        const float height,
        const unsigned char_size,
        const std::string& text) {
    float x = container.getPosition().x + container.getSize().x / 2.f - width / 2.f;

    buttons[key] = new gui::Button(x, y, width, height,&font, text, char_size,sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));
}

void Pause::update(const sf::Vector2i& mousePosWindow) {
    for (auto &i : buttons) {
        i.second->update(mousePosWindow);
    }
}

void Pause::render(sf::RenderTarget & target) {
    target.draw(background);
    target.draw(container);

    for (auto &i : buttons) {
        i.second->render(target);
    }

    target.draw(menuText);
}