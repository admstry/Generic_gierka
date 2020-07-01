//
// Created by Adam on 16.06.2020.
//

#ifndef GENERIC_GIERKA_ENTITY_H
#define GENERIC_GIERKA_ENTITY_H

#include "Animate.h"
#include "Movement.h"
#include "HitBox.h"

class Entity {
protected:
    // variables
    int hp{};
    int hpMax{};
    bool attacking{};
    sf::Sprite sprite;
    HitBox* hitbox;
    Movement* movement;
    Animate* animation;
public:
    Entity();
    virtual ~Entity();

    // functions
    void createHitBox(sf::Sprite& sprite_, float offset_x, float offset_y, float width, float height);
    void createMovement(float maxVelocity, float acceleration, float deceleration);
    void createAnimation(sf::Texture& texture_sheet);

    virtual void move(float dir_x, float dir_y, const float& tm);
    virtual void stopVelocityX();
    virtual void stopVelocityY();

    [[maybe_unused]] virtual void stopVelocity();
    virtual void setVelocity(sf::Vector2f velocity);
    virtual void setPosition(sf::Vector2f position);

    virtual void loseHp(int hp);
    virtual int getHp() const;
    virtual void setAttack();
    virtual bool isAttacking() const;

    virtual sf::FloatRect getGlobalBounds();
    virtual sf::FloatRect getNextBounds(const float& dt) const;
    virtual const sf::Vector2f& getPosition() const;
    virtual float getDistance(const Entity& entity) const;
    virtual sf::Vector2f getCenter() const;
    virtual sf::Vector2f getVelocity() const;
    virtual sf::Vector2i getGridPosition(const int &gridSize) const;

    virtual void update(const float& tm) = 0;
    virtual void render(sf::RenderTarget& target) = 0;
};


#endif //GENERIC_GIERKA_ENTITY_H
