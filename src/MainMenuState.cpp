//
// Created by Adam on 11.06.2020.
//
#include "pch.h"
#include "MainMenuState.h"

// initialization
void MainMenuState::initVariables() {

}

void MainMenuState::initFonts() {
    if (!font.loadFromFile("../Fonts/rainyhearts.ttf"))
    {
        throw std::exception();
    }
}

void MainMenuState::initKeybinds() {
    std::ifstream stream("../Config/mainmenustate_keybinds.ini");

    if (stream.is_open())
    {
        std::string key;
        std::string key2;
        while (stream >> key >> key2)
        {
            keybinds[key] = supportedKeys->at(key2);
        }
    }
    stream.close();
}

void MainMenuState::initGui() {
    const sf::VideoMode& vm = this->stateData->gfxSettings->resolution;

    background.setSize(sf::Vector2f(1920,1080));
    if (!backgroundTexture.loadFromFile("../Resources/Backgrounds/bg.png"))
    {
        throw std::exception();
    }
    background.setTexture(&backgroundTexture);

    //Buttons
    this->buttons["GAME_STATE"] = new gui::Button(
            gui::p2pX(15.6f, vm), gui::p2pY(30.f, vm),
            gui::p2pX(13.f, vm), gui::p2pY(6.f, vm),
            &this->font, "New Game", gui::calcCharSize(vm),
            sf::Color(200, 200, 200, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
            sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
    );

    this->buttons["SETTINGS_STATE"] = new gui::Button(
            gui::p2pX(15.6f, vm), gui::p2pY(40.f, vm),
            gui::p2pX(13.f, vm), gui::p2pY(6.f, vm),
            &this->font, "Settings", gui::calcCharSize(vm),
            sf::Color(200, 200, 200, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
            sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

    this->buttons["EDITOR_STATE"] = new gui::Button(
            gui::p2pX(15.6f, vm), gui::p2pY(50.f, vm),
            gui::p2pX(13.f, vm), gui::p2pY(6.f, vm),
            &font, "Editor", gui::calcCharSize(vm),
            sf::Color(200, 200, 200, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
            sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

    this->buttons["EXIT_STATE"] = new gui::Button(
            gui::p2pX(15.6f, vm), gui::p2pY(65.f, vm),
            gui::p2pX(13.f, vm), gui::p2pY(6.f, vm),
            &font, "Quit", gui::calcCharSize(vm),
            sf::Color(200, 200, 200, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
            sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));
}


void MainMenuState::resetGui() {
    auto it = buttons.begin();
    for (it = buttons.begin(); it != buttons.end(); ++it)
    {
        delete it->second;
    }
    buttons.clear();

    initGui();
}

MainMenuState::MainMenuState(StateData *state_data) : State(state_data) {
    this->initVariables();
    this->initFonts();
    this->initKeybinds();
    this->initGui();
    this->resetGui();
}

MainMenuState::~MainMenuState() {
    auto it = buttons.begin();
    for (it = buttons.begin(); it != buttons.end(); ++it)
    {
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
//        states->push(new GameState(tateData));
//    }
//
    //Settings
    if (buttons["SETTINGS_STATE"]->isPressed())
    {
        states->push(new SettingsState(stateData));
    }

//    //Editor
//    if (buttons["EDITOR_STATE"]->isPressed())
//    {
//        states->push(new EditorState(stateData));
//    }
//
    //Quit the game
    if (buttons["EXIT_STATE"]->isPressed())
    {
        endState();
    }
}

void MainMenuState::update(const float &tm) {
    updateMousePositions(nullptr);
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
    if (!target)
        target = window;

    target->draw(background);

    target->draw(btnBackground);

    renderButtons(*target);

//    TODO DEBUG ONLY REMOVE LATER
//    sf::Text mouseText;
//    mouseText.setPosition(this->mousePosView.x, this->mousePosView.y - 50);
//    mouseText.setFont(this->font);
//    mouseText.setCharacterSize(12);
//    std::stringstream ss;
//    ss << this->mousePosView.x << " " << this->mousePosView.y;
//    mouseText.setString(ss.str());
//    target->draw(mouseText);
}
