//
// Created by Adam on 16.06.2020.
//
#include "pch.h"
#include "Game.h"

void Game::initFonts() {
    if(!font.loadFromFile("../Fonts/rainyhearts.ttf")) {
        throw std::exception();
    }
}

void Game::initKeyBinds() {
    std::ifstream stream("../Config/game_keys.ini");

    if (stream.is_open()) {
        std::string key;
        std::string key2;
        while (stream >> key >> key2) {
            keyBinds[key] = supportedKeys->at(key2);
        }
    }
    stream.close();
}

void Game::initTextures() {
    if (!player_sheet.loadFromFile("../Resources/Sprites/player.png")) {
        throw std::exception();
    }
    if (!spider_sheet.loadFromFile("../Resources/Sprites/spider.png")) {
        throw std::exception();
    }
}

void Game::initMap() {

    // create the tilemap from the level definition
    if (!map.load("../Resources/Tilemap/tiles1.png", sf::Vector2u(64, 64), "../Resources/Tilemap/tiles.txt", "../Resources/Tilemap/colliders.txt", mapSizeY, mapSizeX, 0)) {
        throw std::exception();
    }
}

void Game::initPlayer() {
    initKeyBinds();
    player = new Player(855.f,580.f, player_sheet);
}

void Game::initEnemies() {

    for (int i = 0; i < 3; i++) {
        activeEntities.emplace_back(new Spider(static_cast<float>(rand()%300)+1470,
                                               static_cast<float>(rand()%100)+270, spider_sheet));
    }
    for (int i = 0; i < 2; i++) {
        activeEntities.emplace_back(new Spider(static_cast<float>(rand()%300)+2050,
                                               static_cast<float>(rand()%100)+770, spider_sheet));
    }
    for (int i = 0; i < 7; i++) {
        activeEntities.emplace_back(new Spider(static_cast<float>(rand()%128)+2500,
                                               static_cast<float>(rand()%256)+512, spider_sheet));
    }
    for (int i = 0; i < 3; i++) {
        activeEntities.emplace_back(new Spider(static_cast<float>(rand()%350)+2600,
                                               static_cast<float>(rand()%120)+1220, spider_sheet));
    }
    for (int i = 0; i < 3; i++) {
        activeEntities.emplace_back(new Spider(static_cast<float>(rand()%350)+2600,
                                               static_cast<float>(rand()%120)+1220, spider_sheet));
    }
    for (int i = 0; i < 20; i++) {
        activeEntities.emplace_back(new Spider(static_cast<float>(rand()%1250)+1420,
                                               static_cast<float>(rand()%300)+1750, spider_sheet));
    }
    for (int i = 0; i < 4; i++) {
        activeEntities.emplace_back(new Spider(static_cast<float>(rand()%150)+1440,
                                               static_cast<float>(rand()%100)+1170, spider_sheet));
    }
    for (int i = 0; i < 4; i++) {
        activeEntities.emplace_back(new Spider(static_cast<float>(rand()%280)+215,
                                               static_cast<float>(rand()%80)+1622, spider_sheet));
    }
}

void Game::initView() {
    view.setSize(sf::Vector2f(stateData->settings->resolution.width, stateData->settings->resolution.height));
    view.setCenter(sf::Vector2f(static_cast<float>(stateData->settings->resolution.width) / 2.f, stateData->settings->resolution.height) / 2.f);
    view.zoom(0.5f);
}

void Game::initGui() {
    hpText.setFont(font);
    hpText.setFillColor(sf::Color::Red);
    hpText.setPosition(10.f,10.f);
    hpText.setString(std::to_string(player->getHp()));
    hpText.setCharacterSize(50);
    guideText.setFont(font);
    guideText.setFillColor(sf::Color(190,190,190,255));
    guideText.setPosition(710.f,600.f);
    guideText.setString("WASD - Move\nRMB - Attack");
    const sf::VideoMode& vm = stateData->settings->resolution;
    menu = new Pause(stateData->settings->resolution, font);
    menu->addButton("QUIT", gui::p2pY(74.f, vm), gui::p2pX(13.f, vm), gui::p2pY(6.f, vm), gui::calcCharSize(vm), "Quit");
}

Game::Game(StateData *state_data) : State(state_data) {
    srand(time(nullptr));
    player = nullptr;
    menu = nullptr;
    mapSizeX = 50;
    mapSizeY = 50;
    invicibleTime = 0.f;
    InvicibleTimeMax = 200.f;
    initFonts();
    initTextures();
    initMap();
    initPlayer();
    initEnemies();
    initView();
    initGui();

}

Game::~Game() {
        delete player;
        delete menu;
        for (auto &entity : activeEntities) {
            delete entity;
        }
}

void Game::updateView() {
    view.setCenter(sf::Vector2f(player->getPosition()));

    gridViewPosition = sf::Vector2i(view.getCenter().x / stateData->gridSize,view.getCenter().y / stateData->gridSize);
}

void Game::updateInput(const float &tm) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keyBinds.at("CLOSE"))) && getKeyTime())
    {
        if (!paused) {
            pauseState();
        }
        else unpauseState();
    }
    if (menu->isButtonPressed("QUIT")) {
        endState();
    }
}

void Game::updatePlayerInput(const float &tm) {
        if (!player->isAttacking()) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keyBinds.at("MOVE_LEFT")))) {
                player->move(-1.f, 0.f, tm);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keyBinds.at("MOVE_RIGHT")))) {
                player->move(1.f, 0.f, tm);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keyBinds.at("MOVE_UP")))) {
                player->move(0.f, -1.f, tm);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keyBinds.at("MOVE_DOWN")))) {
                player->move(0.f, 1.f, tm);
            }
        }
}

void Game::updateCombat(const float &tm) {
    if (player->getHp() < 0) {
        std::cout << "YoU dIeD\n";
        endState();
    }
    auto it = activeEntities.begin();
    for (auto &entity : activeEntities) {
        if (player->getGlobalBounds().intersects(entity->getGlobalBounds()) && getInvicibleTime()) {
            player->loseHp(5);
            if (entity->getGlobalBounds().left > player->getGlobalBounds().left) {
                entity->setVelocity(sf::Vector2f(-1000.f, entity->getVelocity().y));
            }
            else if (entity->getGlobalBounds().left < player->getGlobalBounds().left) {
                entity->setVelocity(sf::Vector2f(1000.f, entity->getVelocity().y));
            }
            if (entity->getGlobalBounds().top > player->getGlobalBounds().top) {
                entity->setVelocity(sf::Vector2f(entity->getVelocity().x, -1000.f));
            }
            else if (entity->getGlobalBounds().left > player->getGlobalBounds().left) {
                entity->setVelocity(sf::Vector2f(entity->getVelocity().y, 1000.f));
            }
        }
        if (entity->getDistance(*player) < static_cast<float>(player->getWeapon()->getRange())
            && (player->getFaceDirection(*entity) || entity->getDistance(*player) < 5.f)) {
            entityStack.push(entity);
        }
        if (entity->getHp() <= 0) {
            delete entity;
            activeEntities.erase(std::remove(activeEntities.begin(),activeEntities.end(),entity),activeEntities.end());
            --it;
            break;
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
        ++it;
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && player->getWeapon()->getAttackTimer()) {
        player->setAttack();
        while (!entityStack.empty()) {
            entityStack.top()->loseHp(static_cast<int>(player->getWeapon()->getDamage()));
            entityStack.top()->setVelocity(-entityStack.top()->getVelocity());
            entityStack.pop();
        }
    }
    while (!entityStack.empty()) {
        entityStack.pop();
    }
}

void Game::updateInvTime(const float &tm) {
    if (invicibleTime < InvicibleTimeMax) {
        invicibleTime += 100.f * tm;
    }
}

void Game::updateGui() {
    hpText.setString(std::to_string(player->getHp()));
}

void Game::update(const float &tm) {
    updateView();
    updateMousePosition(&view);
    updateKeyTime(tm);
    updateInput(tm);
    if (!paused) {
        updatePlayerInput(tm);
        player->update(tm);
        map.updateGlobalBounds(*player);
        map.updateTileCollision(player, tm);
        for (auto &entity : activeEntities) {
            entity->update(tm);
            map.updateGlobalBounds(*entity);
            map.updateTileCollision(entity,tm);
        }
        updateCombat(tm);
        updateInvTime(tm);
        updateGui();
    }
    else {
        menu->update(mousePositionWindow);
    }
}

void Game::render(sf::RenderTarget *target) {
    if(!target) {
        target = window;
    }
    window->setView(view);
    map.render(*target,gridViewPosition);
    target->draw(guideText);
    player->render(*target);
    for (auto &entity : activeEntities) {
        entity->render(*target);
    }

    window->setView(window->getDefaultView());
    target->draw(hpText);

    if (paused) {
        menu->render(*target);
    }
}

bool Game::getInvicibleTime() {
    if (invicibleTime >= InvicibleTimeMax)
    {
        invicibleTime = 0.f;
        return true;
    }
    return false;
}






















