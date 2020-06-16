//
// Created by Adam on 14.06.2020.
//
#include "pch.h"
#include "GraphicsSettings.h"

GraphicsSettings::GraphicsSettings()
{
    title = "DEFAULT";
    resolution = sf::VideoMode::getDesktopMode();
    fullscreen = false;
    verticalSync = false;
    frameRateLimit = 120;
    contextSettings.antialiasingLevel = 0;
    videoModes = sf::VideoMode::getFullscreenModes();
}

//Functions
void GraphicsSettings::saveToFile(const std::string& path) const
{
    std::ofstream stream(path);

    if (stream.is_open())
    {
        stream << title;
        stream << resolution.width << " " << resolution.height;
        stream << fullscreen;
        stream << frameRateLimit;
        stream << verticalSync;
        stream << contextSettings.antialiasingLevel;
    }

    stream.close();
}

void GraphicsSettings::loadFromFile(const std::string& path)
{
    std::ifstream stream(path);


    if (stream.is_open())
    {
        std::getline(stream, title);
        stream >> resolution.width >> resolution.height;
        stream >> fullscreen;
        stream >> frameRateLimit;
        stream >> verticalSync;
        stream >> contextSettings.antialiasingLevel;
    }

    stream.close();
}

