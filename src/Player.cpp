//
// Created by Adam on 16.06.2020.
//

#include "pch.h"
#include "Player.h"

void Player::initVariables() {
    attacking = false;
    hpMax = 100;
    hp = hpMax;
    weapon = new Weapon(3,50,1);
}

void Player::initComponents() {

}

void Player::initAnimations() {
    animationComponent->addAnimation("IDLE", 15.f, 0, 0, 6, 0, 64, 64);
    animationComponent->addAnimation("WALK_RIGHT", 16.f, 0, 1, 6, 1, 64, 64);
    animationComponent->addAnimation("WALK_LEFT", 16.f, 0, 2, 6, 2, 64, 64);
}

Player::Player(float x, float y, sf::Texture &texture_sheet) {
    initVariables();
    initComponents();
    createMovementComponent(250.f, 1600.f, 500.f);
    createAnimationComponent(texture_sheet);
    createHitboxComponent(sprite,10,0,45,60);
    sprite.setPosition(x,y);
    initAnimations();
}

Player::~Player() = default;

Weapon *Player::getWeapon() {
    return weapon;
}

void Player::updateAnimation(const float &tm) {
    if (movementComponent->getState(IDLE))
    {
        animationComponent->play("IDLE", tm);
    }
    else if (movementComponent->getState(MOVING_LEFT))
    {
        animationComponent->play("WALK_LEFT", tm, movementComponent->getVelocity().x, movementComponent->getMaxVelocity());
        last_move = MOVING_LEFT;
    }
    else if (movementComponent->getState(MOVING_RIGHT) || movementComponent->getState(MOVING_DOWN))
    {
        animationComponent->play("WALK_RIGHT", tm, movementComponent->getVelocity().x, movementComponent->getMaxVelocity());
        last_move = MOVING_RIGHT;
    }
    else if (movementComponent->getState(MOVING_UP))
    {
        animationComponent->play("WALK_LEFT", tm, movementComponent->getVelocity().x, movementComponent->getMaxVelocity());
    }
}

void Player::update(const float &tm) {
    movementComponent->update(tm);
    updateAnimation(tm);
    hitboxComponent->update();
}

void Player::render(sf::RenderTarget &target) {
    target.draw(sprite);
    hitboxComponent->render(target);
}

bool Player::getFaceDirection(Entity& entity) const {
    if ((movementComponent->getState(MOVING_RIGHT) || last_move == MOVING_RIGHT) && entity.getPosition().x > sprite.getPosition().x) {
        return true;
    }
    else return (movementComponent->getState(MOVING_LEFT) || last_move == MOVING_LEFT) && entity.getPosition().x < sprite.getPosition().x ;
}



