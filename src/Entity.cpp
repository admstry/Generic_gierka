//
// Created by Adam on 13.06.2020.
//
#include "pch.h"
#include "Entity.h"

void Entity::initVariables()
{
    hitboxComponent = nullptr;
    movementComponent = nullptr;
    animationComponent = nullptr;
}

Entity::Entity()
{
    initVariables();
}

Entity::~Entity()
{
    delete hitboxComponent;
    delete movementComponent;
    delete animationComponent;
}

//Component functions
void Entity::setTexture(sf::Texture& texture)
{
    sprite.setTexture(texture);
}

void Entity::createHitboxComponent(sf::Sprite & sprite,
                                   float offset_x, float offset_y,
                                   float width, float height)
{
    hitboxComponent = new HitboxComponent(sprite, offset_x, offset_y, width, height);
}

void Entity::createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration)
{
    movementComponent = new MovementComponent(sprite, maxVelocity, acceleration, deceleration);
}

void Entity::createAnimationComponent(sf::Texture & texture_sheet)
{
    animationComponent = new AnimationComponent(sprite, texture_sheet);
}

const sf::Vector2f & Entity::getPosition() const
{
    if (hitboxComponent)
        return hitboxComponent->getPosition();

    return sprite.getPosition();
}

const sf::Vector2f Entity::getCenter() const
{
    if (hitboxComponent)
        return
                hitboxComponent->getPosition() +
                sf::Vector2f
                        (
                                hitboxComponent->getGlobalBounds().width / 2.f,
                                hitboxComponent->getGlobalBounds().height / 2.f
                        );

    return
            sprite.getPosition() +
            sf::Vector2f
                    (
                            sprite.getGlobalBounds().width / 2.f,
                            sprite.getGlobalBounds().height / 2.f
                    );
}

const sf::Vector2i Entity::getGridPosition(const int gridSizeI) const
{
    if (hitboxComponent)
        return sf::Vector2i(
                static_cast<int>(hitboxComponent->getPosition().x) / gridSizeI,
                static_cast<int>(hitboxComponent->getPosition().y) / gridSizeI
        );

    return sf::Vector2i(
            static_cast<int>(sprite.getPosition().x) / gridSizeI,
            static_cast<int>(sprite.getPosition().y) / gridSizeI
    );
}

const sf::FloatRect Entity::getGlobalBounds() const
{
    if (hitboxComponent)
        return hitboxComponent->getGlobalBounds();

    return sprite.getGlobalBounds();
}

const sf::FloatRect Entity::getNextPositionBounds(const float& dt) const
{
    if (hitboxComponent && movementComponent)
        return hitboxComponent->getNextPosition(movementComponent->getVelocity() * dt);

    return sf::FloatRect(-1.f, -1.f, -1.f, -1.f);
}

//Functions
void Entity::setPosition(const float x, const float y)
{
    if (hitboxComponent)
        hitboxComponent->setPosition(x, y);
    else
        sprite.setPosition(x, y);
}

void Entity::move(const float dir_x, const float dir_y, const float& dt)
{
    if (movementComponent)
        movementComponent->move(dir_x, dir_y, dt); //Sets velocity
}

void Entity::stopVelocity()
{
    if (movementComponent)
        movementComponent->stopVelocity();

}

void Entity::stopVelocityX()
{
    if (movementComponent)
        movementComponent->stopVelocityX();
}

void Entity::stopVelocityY()
{
    if (movementComponent)
        movementComponent->stopVelocityY();
}

const float Entity::getDistance(const Entity& entity) const
{
    return sqrt(pow(getCenter().x - entity.getCenter().x, 2) + pow(getCenter().y - entity.getCenter().y, 2));
}