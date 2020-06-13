//
// Created by Adam on 13.06.2020.
//

#ifndef GENERIC_GIERKA_PLAYER_H
#define GENERIC_GIERKA_PLAYER_H

#include "Entity.h"

class Player :
        public Entity
{
private:
    //Variables
    bool attacking;

    //Initializer functions
    void initVariables();
    void initComponents();
    void initAnimations();

public:
    Player(float x, float y, sf::Texture& texture_sheet);
    ~Player() override;

    //Functions

    void updateAnimation(const float& dt);
    void update(const float& dt, sf::Vector2f& mouse_pos_view) override;

    void render(sf::RenderTarget& target, sf::Shader* shader = nullptr, sf::Vector2f light_position = sf::Vector2f(), bool show_hitbox = false) override;
};

#endif //GENERIC_GIERKA_PLAYER_H
