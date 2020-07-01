//
// Created by Adam on 16.06.2020.
//

#ifndef GENERIC_GIERKA_PLAYER_H
#define GENERIC_GIERKA_PLAYER_H

#include "Entity.h"
#include "Weapon.h"

class Player : public Entity {
private:
    // functions
    void initAnimations();
    // variables;
    short last_move;
    Weapon *weapon;
public:
    Player(float x, float y, sf::Texture& texture_sheet);
    ~Player() override;

    // functions
    Weapon* getWeapon();

    bool getFaceDirection(Entity& entity) const;
    void updateAnimation(const float& tm);
    void update(const float& tm) override;
    void render(sf::RenderTarget& target) override;
};


#endif //GENERIC_GIERKA_PLAYER_H
