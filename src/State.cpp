//
// Created by Adam on 14.06.2020.
//
#include "pch.h"
#include "State.h"

State::State(StateData* state_data) {
    stateData = state_data;
    window = state_data->window;
    supportedKeys = state_data->supportedKeys;
    states = state_data->states;
    quit = false;
    paused = false;
    keyTime = 0.f;
    keyTimeMax = 10.f;
    gridSize = state_data->gridSize;
}

State::~State() = default;

bool State::getQuit() const {
    return quit;
}

bool State::getKeyTime() {
    if (keyTime >= keyTimeMax) {
        keyTime = 0.f;
        return true;
    }
    return false;
}

void State::endState() {
    quit = true;
}

void State::pauseState() {
    paused = true;
}

void State::unpauseState() {
    paused = false;
}

void State::updateMousePosition(sf::View *view) {
    mousePositionScreen = sf::Mouse::getPosition();
    mousePositionWindow = sf::Mouse::getPosition(*window);

    if (view) {
        window->setView(*view);
    }
    mousePositionView = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
    mousePositionGrid = (sf::Vector2i(
            static_cast<int>(mousePositionView.x) / static_cast<int>(gridSize),
            static_cast<int>(mousePositionView.y) / static_cast<int>(gridSize))
    );
    window->setView(window->getDefaultView());
}

void State::updateKeyTime(const float &tm) {
    if (keyTime < keyTimeMax) {
        keyTime += 100.f * tm;
    }
}
