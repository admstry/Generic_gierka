//
// Created by Adam on 16.06.2020.
//

#ifndef GENERIC_GIERKA_GAMESTATE_H
#define GENERIC_GIERKA_GAMESTATE_H

#include "State.h"
#include "TileMap.h"
#include "Player.h"

class GameState : public State {
private:
    void initVariables();
    void initFonts();
    void initKeyBinds() override;
    void initTextures();
    void initPlayer();
    void initMap();
    sf::Texture texture_sheet;
    TileMap map;
    Player *player;


public:
    explicit GameState(StateData* state_data);
    ~GameState() override;
    void updateInput(const float & tm) override;
    void updatePlayerInput(const float &tm);
    void update(const float & tm) override;
    void render(sf::RenderTarget *target) override ;


};


#endif //GENERIC_GIERKA_GAMESTATE_H
