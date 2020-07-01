//
// Created by Adam on 16.06.2020.
//

#include "pch.h"
#include "Entity.h"

Entity::Entity() {
    animation = nullptr;
    movement = nullptr;
    hitbox = nullptr;
}

Entity::~Entity() {
    delete animation;
    delete hitbox;
    delete movement;
}

void Entity::createHitBox(sf::Sprite &sprite_, float offset_x, float offset_y, float width, float height) {
    hitbox = new HitBox(sprite_, offset_x, offset_y, width, height);
}

void Entity::createMovement(const float maxVelocity, const float acceleration, const float deceleration) {
    movement = new Movement(sprite, maxVelocity, acceleration, deceleration);
}

void Entity::createAnimation(sf::Texture &texture_sheet) {
    animation = new Animate(sprite, texture_sheet);
}

void Entity::move(const float dir_x, const float dir_y, const float& tm) {
    if (movement)
        movement->move(dir_x, dir_y, tm);
}

void Entity::stopVelocityX() {
    movement->stopVelocityX();
}

void Entity::stopVelocityY() {
    movement->stopVelocityY();
}

[[maybe_unused]] void Entity::stopVelocity() {
    movement->stopVelocity();
}

int Entity::getHp() const {
    return hp;
}

void Entity::loseHp(int hp_) {
    hp -= hp_;
}

sf::FloatRect Entity::getGlobalBounds() {
    return hitbox->getGlobalBounds();
}

const sf::Vector2f &Entity::getPosition() const {
    return sprite.getPosition();
}

sf::Vector2f Entity::getCenter() const
{
    if (hitbox) {
        return hitbox->getPosition() + sf::Vector2f(hitbox->getGlobalBounds().width / 2.f,
                                                    hitbox->getGlobalBounds().height / 2.f);
    }

    return sprite.getPosition() + sf::Vector2f(sprite.getGlobalBounds().width / 2.f,sprite.getGlobalBounds().height / 2.f);
}

float Entity::getDistance(const Entity &entity) const {
    return static_cast<float>(sqrt(pow(getCenter().x - entity.getCenter().x, 2) + pow(getCenter().y - entity.getCenter().y, 2)));
}

void Entity::setVelocity(sf::Vector2f velocity) {
    movement->setVelocity(velocity);
}

sf::Vector2f Entity::getVelocity() const {
    return movement->getVelocity();
}

void Entity::setPosition(sf::Vector2f position) {
    if (hitbox) {
        hitbox->setPosition(position);
    } else sprite.setPosition(position);
}

sf::Vector2i Entity::getGridPosition(const int &gridSize) const {
    if (hitbox) {
        return sf::Vector2i(
                static_cast<int>(hitbox->getPosition().x) / gridSize,
                static_cast<int>(hitbox->getPosition().y) / gridSize);
    }
    else {
        return sf::Vector2i(
                static_cast<int>(sprite.getPosition().x) / gridSize,
                static_cast<int>(sprite.getPosition().x) / gridSize);
    }
}

sf::FloatRect Entity::getNextBounds(const float& dt) const {
    if (hitbox && movement)
        return hitbox->getNextPosition(movement->getVelocity() * dt);

    return sf::FloatRect(-1.f, -1.f, -1.f, -1.f);
}

void Entity::setAttack() {
    attacking = true;
}

bool Entity::isAttacking() const {
    return attacking;
}


