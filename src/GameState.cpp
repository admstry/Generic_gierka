//
// Created by Adam on 16.06.2020.
//
#include "pch.h"
#include "GameState.h"

void GameState::initVariables() {
    srand(time(nullptr));
    initKeyBinds();
}

void GameState::initFonts() {
    if(font.loadFromFile("../Fonts/rainyhearts.ttf")) {
        std::exception();
    }
}

void GameState::initKeyBinds() {
    std::ifstream stream("../Config/gamestate_keybinds.ini");

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
    if (!player_sheet.loadFromFile("../Resources/Sprites/player.png")) {
        throw std::exception();
    }
    if (!spider_sheet.loadFromFile("../Resources/Sprites/spider.png")) {
        throw std::exception();
    }
}

void GameState::initMap() {
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
}

void GameState::initPlayer() {
    player = new Player(0, 0, player_sheet);
    for (int i = 0; i < 5; i++) {
        activeEntities.emplace_back(new Spider(rand() % 1900 + i, rand() % 900 + i * 10, spider_sheet));
    }
}

void GameState::initView() {
    view.setSize(sf::Vector2f(stateData->gfxSettings->resolution.width, stateData->gfxSettings->resolution.height));
    view.setCenter(sf::Vector2f(stateData->gfxSettings->resolution.width / 2.f, stateData->gfxSettings->resolution.height) / 2.f);
}

void GameState::initGui() {
    hpText.setFont(font);
    hpText.setFillColor(sf::Color::Red);
    hpText.setPosition(10.f,10.f);
    hpText.setString(std::to_string(player->getHp()));
}

GameState::GameState(StateData *state_data) : State(state_data) {
    initVariables();
    initFonts();
    initTextures();
    initMap();
    initPlayer();
    initView();
    initGui();
}

GameState::~GameState() {
        delete player;
        for (auto &entity : activeEntities) {
            delete entity;
        }
}

void GameState::updateView() {
    view.setCenter(sf::Vector2f(player->getPosition()));
}

void GameState::updateInput(const float &tm) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("CLOSE"))) && getKeyTime())
    {
        endState();
    }
}

void GameState::updatePlayerInput(const float &tm) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("MOVE_LEFT")))) {
        this->player->move(-1.f, 0.f, tm);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("MOVE_RIGHT")))) {
        this->player->move(1.f, 0.f, tm);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("MOVE_UP"))))
    {
        this->player->move(0.f, -1.f, tm);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("MOVE_DOWN"))))
    {
        this->player->move(0.f, 1.f, tm);
    }
}


void GameState::updateCombat(const float &tm) {
    unsigned counter = 0;
    for (auto &entity : activeEntities) {
        if (player->getGlobalBounds().intersects(entity->getGlobalBounds()) && getKeyTime()) {
            player->loseHp(1);
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Right)
            && entity->getDistance(*player) < player->getWeapon()->getRange()
            && (player->getFaceDirection(*entity) || entity->getDistance(*player) < 5.f)
            && player->getWeapon()->getAttackTimer()) {
            entity->loseHp(player->getWeapon()->getDamage());
            entity->stopVelocity();
        }
        if (entity->getHp() <= 0) {
            activeEntities.erase(activeEntities.begin()+counter);
            counter--;
        }
        if (player->getDistance(*entity) < 100.f) {
            if (player->getCenter().x > entity->getCenter().x) {
                entity->move(1.f,0.f,tm);
            }
            if (player->getCenter().x < entity->getCenter().x) {
                entity->move(-1.f,0.f,tm);
            }
            if (player->getCenter().y < entity->getCenter().y) {
                entity->move(0.f,-1.f,tm);
            }
            if (player->getCenter().y > entity->getCenter().y) {
                entity->move(0.f,1.f,tm);
            }
        }
    counter++;
    }
}

void GameState::updateGui() {
    hpText.setString(std::to_string(player->getHp()));
}

void GameState::update(const float &tm) {
    updateView();
    updateMousePosition(&view);
    updateInput(tm);
    updateKeyTime(tm);
    updatePlayerInput(tm);
    player->update(tm);
    for (auto &entity : activeEntities) {
        entity->update(tm);
    }
    updateCombat(tm);
    updateGui();
}

void GameState::render(sf::RenderTarget *target) {
    if(!target) {
        target = window;
    }
    window->setView(view);
    target->draw(map);
    player->render(*target);
    for (auto &entity : activeEntities) {
        entity->render(*target);
    }
    window->setView(window->getDefaultView());
    target->draw(hpText);
}


















