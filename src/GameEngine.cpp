//
// Created by Adam on 11.06.2020.
//

#include "pch.h"
#include "GameEngine.h"

// initalization

void GameEngine::initGraphicsSettings()
{
    settings.loadFromFile("../Config/window_settings.ini");
}

void GameEngine::initWindow() {
    if(settings.fullscreen)
        window = new sf::RenderWindow(
                settings.resolution,
                settings.title,
                sf::Style::Fullscreen,
                settings.contextSettings);
    else
        window = new sf::RenderWindow(
                settings.resolution,
                settings.title,
                sf::Style::Titlebar | sf::Style::Close,
                settings.contextSettings);

    window->setFramerateLimit(settings.frameRateLimit);
    window->setVerticalSyncEnabled(settings.verticalSync);
}

void GameEngine::initKeys() {
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
}

void GameEngine::initStateData() {
    stateData.window = window;
    stateData.settings = &settings;
    stateData.supportedKeys = &supportedKeys;
    stateData.states = &states;
    stateData.gridSize = gridSize;
}

void GameEngine::initStates() {
    states.push(new MainMenu(&stateData));
}
GameEngine::GameEngine() {
    window = nullptr;
    tm = 0.f;
    gridSize = 64.f;
    initGraphicsSettings();
    initWindow();
    initKeys();
    initStateData();
    initStates();
}

GameEngine::~GameEngine() {
    delete window;
    while (!states.empty())
    {
        delete states.top();
        states.pop();
    }
}
// functions
void GameEngine::endApplication() {
    std::cout << "Ending Application!" << "\n";
}
// updates
void GameEngine::updateTm() {
    tm = tmClock.restart().asSeconds();
}

void GameEngine::updateSFMLEvents() {
    while (window->pollEvent(sfEvent))
    {
        if (sfEvent.type == sf::Event::Closed)
            window->close();
    }
}

void GameEngine::update() {
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
void GameEngine::render() {
    window->clear();

    //Render items
    if (!states.empty())
        states.top()->render(nullptr);

    window->display();
}
// core
void GameEngine::run() {
    while (window->isOpen())
    {
        updateTm();
        update();
        render();
    }
}
