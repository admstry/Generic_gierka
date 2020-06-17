//
// Created by Adam on 11.06.2020.
//

#include "pch.h"
#include "Game.h"

// initalization
void Game::initVariables() {
    window = nullptr;
    tm = 0.f;
    gridSize = 64.f;
}

void Game::initGraphicsSettings()
{
    this->gfxSettings.loadFromFile("../Config/graphics.ini");
}

void Game::initWindow() {
    if(this->gfxSettings.fullscreen)
        this->window = new sf::RenderWindow(
                this->gfxSettings.resolution,
                this->gfxSettings.title,
                sf::Style::Fullscreen,
                this->gfxSettings.contextSettings);
    else
        this->window = new sf::RenderWindow(
                this->gfxSettings.resolution,
                this->gfxSettings.title,
                sf::Style::Titlebar | sf::Style::Close,
                this->gfxSettings.contextSettings);

    this->window->setFramerateLimit(this->gfxSettings.frameRateLimit);
    this->window->setVerticalSyncEnabled(this->gfxSettings.verticalSync);
}

void Game::initKeys() {
    std::ifstream stream("../Config/supported_keys.ini");

    if (stream.is_open())
    {
        std::string key;
        int key_value = 0;

        while (stream >> key >> key_value)
        {
            supportedKeys[key] = key_value;
        }
    }

    stream.close();
    // TODO remove later debug only
    for (const auto& i : supportedKeys)
    {
        std::cout << i.first << " " << i.second << "\n";
    }
}

void Game::initStateData() {
    stateData.window = window;
    stateData.gfxSettings = &gfxSettings;
    stateData.supportedKeys = &supportedKeys;
    stateData.states = &states;
    stateData.gridSize = gridSize;
}

void Game::initStates() {
    states.push(new MainMenuState(&stateData));
}
// constructor/destructor
Game::Game() {
    initVariables();
    initGraphicsSettings();
    initWindow();
    initKeys();
    initStateData();
    initStates();
}

Game::~Game() {
    delete window;
    while (!states.empty())
    {
        delete states.top();
        states.pop();
    }
}
// functions
void Game::endApplication() {
    std::cout << "Ending Application!" << "\n";
}
// updates
void Game::updateTm() {
    tm = tmClock.restart().asSeconds();
}

void Game::updateSFMLEvents() {
    while (window->pollEvent(sfEvent))
    {
        if (sfEvent.type == sf::Event::Closed)
            window->close();
    }
}

void Game::update() {
    updateSFMLEvents();

    if (!states.empty())
    {
        if (window->hasFocus())
        {
            states.top()->update(tm);

            if (states.top()->getQuit())
            {
                states.top()->endState();
                delete states.top();
                states.pop();
            }
        }
    }
        //Application end
    else
    {
        endApplication();
        window->close();
    }
}
// render
void Game::render() {
    window->clear();

    //Render items
    if (!states.empty())
        states.top()->render(nullptr);

    window->display();
}
// core
void Game::run() {
    while (window->isOpen())
    {
        updateTm();
        update();
        render();
    }
}
