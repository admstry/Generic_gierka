//
// Created by Adam on 11.06.2020.
//
#include "pch.h"
#include "State.h"

State::State(StateData* state_data)
{
    stateData = state_data;
    window = state_data->window;
    supportedKeys = state_data->supportedKeys;
    states = state_data->states;
    quit = false;
    paused = false;
    keytime = 0.f;
    keytimeMax = 10.f;
    gridSize = state_data->gridSize;
}

State::~State() = default;

const bool & State::getQuit() const
{
    return quit;
}

bool State::getKeytime()
{
    if (keytime >= keytimeMax)
    {
        keytime = 0.f;
        return true;
    }
    return false;
}
void State::endState()
{
    this->quit = true;
}

void State::pauseState()
{
    this->paused = true;
}

void State::unpauseState()
{
    this->paused = false;
}

void State::updateMousePositions(sf::View* view)
{
    mousePosScreen = sf::Mouse::getPosition();
    mousePosWindow = sf::Mouse::getPosition(*window);

    if(view) {
        window->setView(*view);
    }

    mousePosView = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
    mousePosGrid =
            sf::Vector2i(
                    static_cast<int>(mousePosView.x) / static_cast<int>(gridSize),
                    static_cast<int>(mousePosView.y) / static_cast<int>(gridSize)
            );

    window->setView(window->getDefaultView());
}

void State::updateKeytime(const float& tm)
{
    if (keytime < keytimeMax) {
        keytime += 100.f * tm;
    }
}