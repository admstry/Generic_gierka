//
// Created by Adam on 16.06.2020.
//

#ifndef GENERIC_GIERKA_ENTITY_H
#define GENERIC_GIERKA_ENTITY_H

#include "AnimationComponents.h"
#include "MovementComponent.h"

class Entity {
private:
    void initVariables();
protected:

    sf::Sprite sprite;
//    HitboxComponent* hitboxComponent;
    MovementComponent* movementComponent;
    AnimationComponent* animationComponent;
public:
    Entity();
    ~Entity();

    void createHitboxComponent(sf::Sprite& sprite, float offset_x, float offset_y, float width, float height);
    void createMovementComponent(float maxVelocity, float acceleration, float deceleration);
    void createAnimationComponent(sf::Texture& texture_sheet);

    virtual void move(float dir_x, float dir_y, const float& tm);
    virtual void stopVelocityX();
    virtual void stopVelocityY();

    virtual void update(const float& tm) = 0;
    virtual void render(sf::RenderTarget& target) = 0;
};


#endif //GENERIC_GIERKA_ENTITY_H
