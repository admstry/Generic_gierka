//
// Created by Adam on 13.06.2020.
//
#include "pch.h"
#include "GameState.h"

void GameState::initView()
{
    this->view.setSize(
            sf::Vector2f(
                    static_cast<float>(this->stateData->gfxSettings->resolution.width),
                    static_cast<float>(this->stateData->gfxSettings->resolution.height)
            )
    );

    this->view.setCenter(
            sf::Vector2f(
                    static_cast<float>(this->stateData->gfxSettings->resolution.width) / 2.f,
                    static_cast<float>(this->stateData->gfxSettings->resolution.height) / 2.f
            )
    );
}

void GameState::initKeybinds()
{
    std::ifstream ifs("../Config/gamestate_keybinds.ini");

    if (ifs.is_open())
    {
        std::string key;
        std::string key2;

        while (ifs >> key >> key2)
        {
            this->keybinds[key] = this->supportedKeys->at(key2);
        }
    }

    ifs.close();
}

void GameState::initFonts()
{
    if (!this->font.loadFromFile("../Fonts/rainyhearts.ttf"))
    {
        throw std::exception();
    }
}

void GameState::initTextures()
{
    if (!this->textures["PLAYER_SHEET"].loadFromFile("../Resources/Sprites/player.png"))
    {
        throw std::exception();
    }
}

void GameState::initPauseMenu()
{
    const sf::VideoMode& vm = this->stateData->gfxSettings->resolution;
    this->pmenu = new PauseMenu(this->stateData->gfxSettings->resolution, this->font);

    this->pmenu->addButton("QUIT", gui::p2pY(74.f, vm), gui::p2pX(13.f, vm), gui::p2pY(6.f, vm), gui::calcCharSize(vm), "Quit");
}

void GameState::initKeyTime()
{
    this->keyTimeMax = 0.3f;
    this->keyTimer.restart();
}

void GameState::initPlayer()
{

}

void GameState::initTileMap()
{

}

GameState::GameState(StateData* state_data)
        : State(state_data)
{
    this->initView();
    this->initKeybinds();
    this->initFonts();
    this->initTextures();
    this->initPauseMenu();
    this->initKeyTime();

    this->initPlayer();
    this->initTileMap();
}

GameState::~GameState() {
    delete this->pmenu;
    delete this->player;
}

const bool GameState::getKeyTime()
{
    if (this->keyTimer.getElapsedTime().asSeconds() >= this->keyTimeMax)
    {
        this->keyTimer.restart();
        return true;
    }

    return false;
}

void GameState::updateView(const float & dt)
{
    this->view.setCenter(
			std::floor(this->player->getPosition().x + (static_cast<float>(this->mousePosWindow.x) - static_cast<float>(this->stateData->gfxSettings->resolution.width / 2)) / 10.f),
			std::floor(this->player->getPosition().y + (static_cast<float>(this->mousePosWindow.y) - static_cast<float>(this->stateData->gfxSettings->resolution.height / 2)) / 10.f)
		);
//    if (this->tileMap->getMaxSizeF().x >= this->view.getSize().x)
//    {
//        if (this->view.getCenter().x - this->view.getSize().x / 2.f < 0.f)
//        {
//            this->view.setCenter(0.f + this->view.getSize().x / 2.f, this->view.getCenter().y);
//        }
//        else if (this->view.getCenter().x + this->view.getSize().x / 2.f > this->tileMap->getMaxSizeF().x)
//        {
//            this->view.setCenter(this->tileMap->getMaxSizeF().x - this->view.getSize().x / 2.f, this->view.getCenter().y);
//        }
//    }
//
//    if (this->tileMap->getMaxSizeF().y >= this->view.getSize().y)
//    {
//        if (this->view.getCenter().y - this->view.getSize().y / 2.f < 0.f)
//        {
//            this->view.setCenter(this->view.getCenter().x, 0.f + this->view.getSize().y / 2.f);
//        }
//        else if (this->view.getCenter().y + this->view.getSize().y / 2.f > this->tileMap->getMaxSizeF().y)
//        {
//            this->view.setCenter(this->view.getCenter().x, this->tileMap->getMaxSizeF().y - this->view.getSize().y / 2.f);
//        }
//    }

    this->viewGridPosition.x = static_cast<int>(this->view.getCenter().x) / static_cast<int>(this->stateData->gridSize);
    this->viewGridPosition.y = static_cast<int>(this->view.getCenter().y) / static_cast<int>(this->stateData->gridSize);
}

void GameState::updateInput(const float & dt)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) && this->getKeytime())
    {
        if (!this->paused)
            this->pauseState();
        else
            this->unpauseState();
    }
}

void GameState::updatePlayerInput(const float & dt)
{
//    Update player input
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT")))) {
        this->player->move(-1.f, 0.f, dt);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT")))) {
        this->player->move(1.f, 0.f, dt);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_UP")))) {
        this->player->move(0.f, -1.f, dt);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN")))) {
        this->player->move(0.f, 1.f, dt);
    }
}

void GameState::updatePauseMenuButtons()
{
    if (this->pmenu->isButtonPressed("QUIT"))
        this->endState();
}

void GameState::updateTileMap(const float & dt)
{

}

void GameState::updatePlayer(const float & dt)
{
    this->player->update(dt, this->mousePosView);
}

void GameState::update(const float& dt)
{
    this->updateMousePositions(&this->view);
    this->updateKeytime(dt);
    this->updateInput(dt);

    if (!this->paused) //Unpaused update
    {
        this->updateView(dt);

        this->updatePlayerInput(dt);

        this->updateTileMap(dt);

        this->updatePlayer(dt);
    }
    else //Paused update
    {
        this->pmenu->update(this->mousePosWindow);
        this->updatePauseMenuButtons();
    }
}

void GameState::render(sf::RenderTarget* target)
{
    if (!target)
        target = this->window;

    //Render GUI
    if (this->paused) //Pause menu render
    {
        this->pmenu->render(this->renderTexture);
    }

    //FINAL RENDER
    this->renderTexture.display();
    target->draw(this->renderSprite);
}