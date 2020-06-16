//
// Created by Adam on 16.06.2020.
//

#include "pch.h"
#include "Entity.h"

void Entity::initVariables() {
}

Entity::Entity() {
    initVariables();
}

Entity::~Entity() {
    delete animationComponent;
}

void Entity::createHitboxComponent(sf::Sprite &sprite, float offset_x, float offset_y, float width, float height) {

}

void Entity::createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration) {

}

void Entity::createAnimationComponent(sf::Texture &texture_sheet) {
    animationComponent = new AnimationComponent(sprite, texture_sheet);
}

void Entity::stopVelocityX() {

}

void Entity::stopVelocityY() {

}


