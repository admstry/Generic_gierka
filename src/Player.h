//
// Created by Adam on 16.06.2020.
//

#ifndef GENERIC_GIERKA_PLAYER_H
#define GENERIC_GIERKA_PLAYER_H

#include "Entity.h"

class Player : public Entity {
private:
    bool attacking;
    void initVariables();
    void initComponents();
    void initAnimations();
public:
    Player(float x, float y, sf::Texture& texture_sheet);
    ~Player();

    void updateAnimation(const float& tm);
    void update(const float& tm) override;
    void render(sf::RenderTarget& target) override;
};


#endif //GENERIC_GIERKA_PLAYER_H
