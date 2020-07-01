//
// Created by Adam on 14.06.2020.
//

#ifndef GENERIC_GIERKA_GRAPHICS_H
#define GENERIC_GIERKA_GRAPHICS_H


class Graphics
{
public:
    Graphics();

    // variables
    std::string title;
    sf::VideoMode resolution;
    bool fullscreen;
    bool verticalSync;
    unsigned frameRateLimit;
    sf::ContextSettings contextSettings;
    std::vector<sf::VideoMode> videoModes;

    // functions
    [[maybe_unused]] void saveToFile(const std::string& path) const;
    void loadFromFile(const std::string& path);
};


#endif //GENERIC_GIERKA_GRAPHICS_H
