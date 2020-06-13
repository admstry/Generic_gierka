//
// Created by Adam on 13.06.2020.
//

#include "pch.h"
#include "GraphicsSettings.h"

GraphicsSettings::GraphicsSettings()
{
    this->title = "DEFAULT";
    this->resolution = sf::VideoMode::getDesktopMode();
    this->fullscreen = false;
    this->verticalSync = false;
    this->frameRateLimit = 120;
    this->contextSettings.antialiasingLevel = 0;
    this->videoModes = sf::VideoMode::getFullscreenModes();
}

//Functions
void GraphicsSettings::saveToFile(const std::string& path) const
{
    std::ofstream stream(path);

    if (stream.is_open())
    {
        stream << this->title;
        stream << this->resolution.width << " " << this->resolution.height;
        stream << this->fullscreen;
        stream << this->frameRateLimit;
        stream << this->verticalSync;
        stream << this->contextSettings.antialiasingLevel;
    }

    stream.close();
}

void GraphicsSettings::loadFromFile(const std::string& path) {
    std::ifstream stream(path);

    if (stream.is_open()) {
        std::getline(stream, this->title);
        stream >> this->resolution.width >> this->resolution.height;
        stream >> this->fullscreen;
        stream >> this->frameRateLimit;
        stream >> this->verticalSync;
        stream >> this->contextSettings.antialiasingLevel;
    }

    stream.close();
}