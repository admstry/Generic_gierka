//
// Created by Adam on 13.06.2020.
//

#ifndef GENERIC_GIERKA_GAMESTATE_H
#define GENERIC_GIERKA_GAMESTATE_H

#include "State.h"
#include "PauseMenu.h"
#include "Player.h"

class GameState :
        public State
{
private:
    sf::View view;
    sf::Vector2i viewGridPosition;
    sf::RenderTexture renderTexture;
    sf::Sprite renderSprite;

    sf::Font font;
    PauseMenu* pmenu;

    sf::Shader core_shader;

    sf::Clock keyTimer;
    float keyTimeMax;

    Player* player;
    sf::Texture texture;

    //Functions
    void initView();
    void initKeybinds() override;
    void initFonts();
    void initTextures();
    void initPauseMenu();
    void initKeyTime();
    void initPlayer();
    void initTileMap();

public:
    explicit GameState(StateData* state_data);
    ~GameState() override;

    //Accessors
    const bool getKeyTime();

    //Functions
    void updateView(const float& dt);
    void updateInput(const float& dt) override;
    void updatePlayerInput(const float& dt);
    void updatePauseMenuButtons();
    void updateTileMap(const float& dt);
    void updatePlayer(const float& dt);
    void update(const float& dt) override;

    void render(sf::RenderTarget* target) override;
};


#endif //GENERIC_GIERKA_GAMESTATE_H
