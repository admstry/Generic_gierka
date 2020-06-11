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

void Game::initWindow() {
    window = new sf::RenderWindow(sf::VideoMode(1920,1080),"Generic_gierka");
    window->setFramerateLimit(120);
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
    for (auto i : supportedKeys)
    {
        std::cout << i.first << " " << i.second << "\n";
    }
}

void Game::initStateData() {
    stateData.window = window;
    stateData.supportedKeys = &supportedKeys;
    stateData.states = &states;
    stateData.gridSize = gridSize;
}

void Game::initStates() {
    states.push(new MainMenuState(&stateData));
}
// constructor/destructor
Game::Game() {
    this->initVariables();
    this->initWindow();
    this->initKeys();
    this->initStateData();
    this->initStates();
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
    this->updateSFMLEvents();

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
