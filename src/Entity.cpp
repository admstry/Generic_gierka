//
// Created by Adam on 16.06.2020.
//

#include "pch.h"
#include "Entity.h"

void Entity::initVariables() {
    animationComponent = nullptr;
    movementComponent = nullptr;
}

Entity::Entity() {
    initVariables();
}

Entity::~Entity() {
    delete animationComponent;
}

void Entity::createHitboxComponent(sf::Sprite &sprite, float offset_x, float offset_y, float width, float height) {
    hitboxComponent = new HitboxComponent(sprite,offset_x,offset_y,width,height);
}

void Entity::createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration) {
    movementComponent = new MovementComponent(sprite, maxVelocity, acceleration, deceleration);
}

void Entity::createAnimationComponent(sf::Texture &texture_sheet) {
    animationComponent = new AnimationComponent(sprite, texture_sheet);
}

void Entity::move(const float dir_x, const float dir_y, const float& tm) {
    if (movementComponent)
        movementComponent->move(dir_x, dir_y, tm);
}

void Entity::stopVelocityX() {

}

void Entity::stopVelocityY() {

}

void Entity::stopVelocity() {
    movementComponent->stopVelocity();
}

int Entity::getHp() const {
    return hp;
}

void Entity::loseHp(int hp_) {
    hp -= hp_;
}

sf::FloatRect Entity::getGlobalBounds() {
    return hitboxComponent->getGlobalBounds();
}

const sf::Vector2f &Entity::getPosition() const {
    return sprite.getPosition();
}

sf::Vector2f Entity::getCenter() const
{
    if (this->hitboxComponent) {
        return hitboxComponent->getPosition() + sf::Vector2f(this->hitboxComponent->getGlobalBounds().width / 2.f,
                                                             this->hitboxComponent->getGlobalBounds().height / 2.f);
    }

    return sprite.getPosition() + sf::Vector2f(this->sprite.getGlobalBounds().width / 2.f,this->sprite.getGlobalBounds().height / 2.f);
}

float Entity::getDistance(const Entity &entity) const {
    return static_cast<float>(sqrt(pow(getCenter().x - entity.getCenter().x, 2) + pow(getCenter().y - entity.getCenter().y, 2)));
}




