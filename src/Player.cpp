//
// Created by Adam on 16.06.2020.
//

#include "pch.h"
#include "Player.h"

void Player::initVariables() {
    attacking = false;

}

void Player::initComponents() {

}

void Player::initAnimations() {
    animationComponent->addAnimation("IDLE", 15.f, 0, 0, 8, 0, 64, 64);
    animationComponent->addAnimation("WALK_DOWN", 11.f, 0, 1, 3, 1, 64, 64);
    animationComponent->addAnimation("WALK_LEFT", 11.f, 4, 1, 7, 1, 64, 64);
    animationComponent->addAnimation("WALK_RIGHT", 11.f, 8, 1, 11, 1, 64, 64);
    animationComponent->addAnimation("WALK_UP", 11.f, 12, 1, 15, 1, 64, 64);
}

Player::Player(float x, float y, sf::Texture &texture_sheet) {
    initVariables();
    initComponents();
    createMovementComponent(200.f, 1600.f, 1000.f);
    createAnimationComponent(texture_sheet);
    sprite.setPosition(x,y);
    initAnimations();
}

Player::~Player() = default;

void Player::updateAnimation(const float &tm) {
    if (this->movementComponent->getState(IDLE))
    {
        this->animationComponent->play("IDLE", tm);
    }
    else if (this->movementComponent->getState(MOVING_LEFT))
    {
        this->animationComponent->play("WALK_LEFT", tm, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
    }
    else if (this->movementComponent->getState(MOVING_RIGHT))
    {
        this->animationComponent->play("WALK_RIGHT", tm, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
    }
    else if (this->movementComponent->getState(MOVING_UP))
    {
        this->animationComponent->play("WALK_UP", tm, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
    }
    else if (this->movementComponent->getState(MOVING_DOWN))
    {
        this->animationComponent->play("WALK_DOWN", tm, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
    }
}

void Player::update(const float &tm) {
    movementComponent->update(tm);
    updateAnimation(tm);
}

void Player::render(sf::RenderTarget &target) {
    target.draw(sprite);
}
