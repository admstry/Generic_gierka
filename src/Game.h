//
// Created by Adam on 16.06.2020.
//

#ifndef GENERIC_GIERKA_GAME_H
#define GENERIC_GIERKA_GAME_H

#include "State.h"
#include "TileMap.h"
#include "Player.h"
#include "Spider.h"
#include "Pause.h"

class Game : public State {
private:
    // functions
    void initFonts();
    void initKeyBinds() override;
    void initTextures();
    void initPlayer();
    void initEnemies();
    void initView();
    void initMap();
    void initGui();
    // variables
    sf::View view;
    int mapSizeX;
    int mapSizeY;
    sf::Vector2i gridViewPosition;
    float invicibleTime;
    float InvicibleTimeMax;

    TileMap map;
    Player *player;
    Pause *menu;
    std::vector<Entity*> activeEntities;
    std::stack<Entity*> entityStack;
    sf::Texture player_sheet;
    sf::Texture spider_sheet;

    sf::Font font;
    sf::Text hpText;
    sf::Text guideText;


public:
    explicit Game(StateData* state_data);
    ~Game() override;
    // functions
    bool getInvicibleTime();
    void updateView();
    void updateInput(const float & tm) override;
    void updatePlayerInput(const float &tm);
    void updateCombat(const float & tm);
    void updateInvTime(const float & tm);
    void updateGui();
    void update(const float & tm) override;
    void render(sf::RenderTarget *target) override ;

};


#endif //GENERIC_GIERKA_GAME_H
