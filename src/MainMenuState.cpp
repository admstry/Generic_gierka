//
// Created by Adam on 14.06.2020.
//

#include "pch.h"
#include "MainMenuState.h"

void MainMenuState::initVariables() {
    initKeyBinds();
}

void MainMenuState::initFonts() {
    if(font.loadFromFile("../Fonts/rainyhearts.ttf")) {
        std::exception();
    }
}

void MainMenuState::initKeyBinds() {
    std::ifstream stream("../Config/mainmenustate-keybinds.ini");

    if (stream.is_open()) {
        std::string key;
        std::string key2;

        while (stream >> key >> key2) {
            keybinds[key] = supportedKeys.at(key2);
        }
    }

    stream.close();
}

void MainMenuState::initGui() {
    const sf::VideoMode &vm = stateData->gfxSettings.resolution;

    background.setSize(sf::Vector2f(static_cast<float>(vm.width), static_cast<float>(vm.height)));

    if (backgroundTexture.loadFromFile("../Resources/Backgrounds/bg.png")) {
        std::exception();
    }

    background.setTexture(&backgroundTexture);

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

void MainMenuState::resetGui() {
    for (auto it = buttons.begin(); it != buttons.end(); ++it) {
        delete it->second;
    }
    buttons.clear();

    initGui();
}

MainMenuState::MainMenuState(StateData *state_data)
    : State(state_data) {
    initVariables();
    initFonts();
    initGui();
    resetGui();
}

MainMenuState::~MainMenuState() {
    for (auto it = buttons.begin(); it != buttons.end(); ++it) {
        delete it->second;
    }
}

void MainMenuState::updateInput(const float &tm) {

}

void MainMenuState::updateButtons() {
    for (auto &it : buttons)
    {
        it.second->update(mousePosWindow);
    }

//    //New game
//    if (buttons["GAME_STATE"]->isPressed())
//    {
//        states.push(new GameState(stateData));
//    }
//
    //Settings
    if (buttons["SETTINGS_STATE"]->isPressed())
    {
        states->push(new SettingsState(stateData));
    }
//
//    //Editor
//    if (buttons["EDITOR_STATE"]->isPressed())
//    {
//        states.push(new EditorState(stateData));
//    }

    //Quit the game
    if (buttons["EXIT_STATE"]->isPressed())
    {
        endState();
    }
}

void MainMenuState::update(const float &tm) {
    updateMousePosition(nullptr);
    updateInput(tm);
    updateButtons();
}

void MainMenuState::renderButtons(sf::RenderTarget &target) {
    for (auto &it : buttons)
    {
        it.second->render(target);
    }
}

void MainMenuState::render(sf::RenderTarget *target) {
    if(!target) {
        target = window;
    }
    target->draw(background);
    renderButtons(*target);
}
