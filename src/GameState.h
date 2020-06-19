//
// Created by Adam on 16.06.2020.
//

#ifndef GENERIC_GIERKA_GAMESTATE_H
#define GENERIC_GIERKA_GAMESTATE_H

#include "State.h"
#include "TileMap.h"
#include "Player.h"
#include "Spider.h"

class GameState : public State {
private:
    void initVariables();
    void initFonts();
    void initKeyBinds() override;
    void initTextures();
    void initPlayer();
    void initView();
    void initMap();
    void initGui();
    sf::View view;
    TileMap map;

    Player *player;
    std::vector<Entity*> activeEntities;
    std::stack<Entity*> entityStack;
    sf::Texture player_sheet;
    sf::Texture spider_sheet;

    sf::Font font;
    sf::Text hpText;


public:
    explicit GameState(StateData* state_data);
    ~GameState() override;
    void updateView();
    void updateInput(const float & tm) override;
    void updatePlayerInput(const float &tm);
    void updateCombat(const float & tm);
    void updateMonsterAi();
    void updateGui();
    void update(const float & tm) override;
    void render(sf::RenderTarget *target) override ;


};


#endif //GENERIC_GIERKA_GAMESTATE_H
