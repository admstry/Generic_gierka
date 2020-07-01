//
// Created by Adam on 14.06.2020.
//

#include "pch.h"
#include "MainMenu.h"

void MainMenu::initVariables() {
    initKeyBinds();
    if (!music.openFromFile("../Resources/Audio/BoxCat - theme.ogg")) {
        throw std::exception();
    }
    music.setVolume(5.f);
    music.setLoop(true);
    music.play();
}

void MainMenu::initFonts() {
    if(!font.loadFromFile("../Fonts/rainyhearts.ttf")) {
        throw std::exception();
    }
}

void MainMenu::initKeyBinds() {
    std::ifstream stream("../Config/menu_keys.ini");

    if (stream.is_open()) {
        std::string key;
        std::string key2;

        while (stream >> key >> key2) {
            keyBinds[key] = supportedKeys->at(key2);
        }
    }

    stream.close();
}

void MainMenu::initGui() {
    const sf::VideoMode &vm = stateData->settings->resolution;

    background.setSize(sf::Vector2f(static_cast<float>(vm.width), static_cast<float>(vm.height)));

    if (!backgroundTexture.loadFromFile("../Resources/Backgrounds/bg.png")) {
        throw std::exception();
    }

    background.setTexture(&backgroundTexture);

    buttons["GAME_STATE"] = new gui::Button(
            gui::p2pX(15.6f, vm), gui::p2pY(45.f, vm),
            gui::p2pX(13.f, vm), gui::p2pY(6.f, vm),
            &this->font, "New Game", gui::calcCharSize(vm),
            sf::Color(200, 200, 200, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
            sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

    buttons["SETTINGS_STATE"] = new gui::Button(
            gui::p2pX(15.6f, vm), gui::p2pY(55.f, vm),
            gui::p2pX(13.f, vm), gui::p2pY(6.f, vm),
            &this->font, "Settings", gui::calcCharSize(vm),
            sf::Color(200, 200, 200, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
            sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));


    buttons["EXIT_STATE"] = new gui::Button(
            gui::p2pX(15.6f, vm), gui::p2pY(65.f, vm),
            gui::p2pX(13.f, vm), gui::p2pY(6.f, vm),
            &this->font, "Quit", gui::calcCharSize(vm),
            sf::Color(200, 200, 200, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
            sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));
}

void MainMenu::resetGui() {
    for (auto & button : buttons) {
        delete button.second;
    }
    buttons.clear();

    initGui();
}

MainMenu::MainMenu(StateData *state_data)
    : State(state_data) {
    initVariables();
    initFonts();
    initGui();
    resetGui();
}

MainMenu::~MainMenu() {
    for (auto & button : buttons) {
        delete button.second;
    }
}

void MainMenu::updateInput(const float &tm) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("CLOSE"))) && getKeyTime()) {
        endState();
    }
}

void MainMenu::updateButtons() {
    for (auto &it : buttons) {
        it.second->update(mousePositionWindow);
    }

    // push new game
    if (buttons["GAME_STATE"]->isPressed() && getKeyTime()) {
        states->push(new Game(stateData));
    }

    // push settings
    if (buttons["SETTINGS_STATE"]->isPressed() && getKeyTime()) {
        states->push(new Settings(stateData));
    }

    // end the game
    if (buttons["EXIT_STATE"]->isPressed() && getKeyTime()) {
        endState();
    }
}

void MainMenu::update(const float &tm) {
    updateMousePosition(nullptr);
    updateKeyTime(tm);
    updateInput(tm);
    updateButtons();
}

void MainMenu::renderButtons(sf::RenderTarget &target) {
    for (auto &it : buttons) {
        it.second->render(target);
    }
}

void MainMenu::render(sf::RenderTarget *target) {
    if(!target) {
        target = window;
    }
    target->draw(background);
    renderButtons(*target);
}
