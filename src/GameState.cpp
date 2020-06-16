//
// Created by Adam on 16.06.2020.
//
#include "pch.h"
#include "GameState.h"

void GameState::initVariables() {
    initKeyBinds();
}

void GameState::initFonts() {

}

void GameState::initKeyBinds() {
    std::ifstream stream("../Config/gamestate-keybinds.ini");

    if (stream.is_open()) {
        std::string key;
        std::string key2;
        while (stream >> key >> key2) {
            keyBinds[key] = supportedKeys->at(key2);
        }
    }
    stream.close();
}

void GameState::initTextures() {
    if (!texture_sheet.loadFromFile("../Resources/Sprites/player.png")) {
        throw std::exception();
    }
}

GameState::GameState(StateData *state_data) : State(state_data) {
    initVariables();
    initFonts();
    initTextures();


    const int level[] =
            {
                    0, 0, 0, 3, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                    0, 1, 1, 3, 1, 1, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0,
                    1, 1, 0, 3, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
                    1, 1, 0, 3, 2, 0, 3, 3, 3, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 3,
                    1, 1, 3, 0, 3, 3, 3, 0, 0, 0, 1, 1, 1, 2, 0, 0, 0, 0, 0, 3,
                    1, 3, 3, 0, 3, 0, 2, 2, 0, 0, 1, 1, 1, 1, 2, 0, 0, 0, 0, 3,
                    3, 0, 1, 0, 3, 0, 2, 2, 2, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                    0, 0, 1, 0, 3, 2, 2, 2, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1,
            };

    // create the tilemap from the level definition

    if (!map.load("tileset.png", sf::Vector2u(64, 64), level, 20, 8)) {
        throw std::exception();
    }
    player = new Player(0,0,texture_sheet);
}

GameState::~GameState() = default;

void GameState::updateInput(const float &tm) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("MOVE_LEFT"))))
        this->player->move(-1.f, 0.f, tm);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("MOVE_RIGHT"))))
        this->player->move(1.f, 0.f, tm);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("MOVE_UP"))))
    {
        this->player->move(0.f, -1.f, tm);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("MOVE_DOWN"))))
    {
        this->player->move(0.f, 1.f, tm);
    }
}

void GameState::update(const float &tm) {
    updateMousePosition(nullptr);
    updateInput(tm);
}

void GameState::render(sf::RenderTarget *target) {
    if(!target) {
        target = window;
    }

    target->draw(map);
    player->render(*target);
}


