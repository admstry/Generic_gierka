//
// Created by Adam on 14.06.2020.
//

#ifndef GENERIC_GIERKA_GRAPHICSSETTINGS_H
#define GENERIC_GIERKA_GRAPHICSSETTINGS_H


class GraphicsSettings
{
public:
    GraphicsSettings();

    //Variables
    std::string title;
    sf::VideoMode resolution;
    bool fullscreen;
    bool verticalSync;
    unsigned frameRateLimit;
    sf::ContextSettings contextSettings;
    std::vector<sf::VideoMode> videoModes;

    //Functions
    void saveToFile(const std::string& path) const;
    void loadFromFile(const std::string& path);
};


#endif //GENERIC_GIERKA_GRAPHICSSETTINGS_H
