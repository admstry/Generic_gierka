//
// Created by Adam on 16.06.2020.
//

#include "pch.h"
#include "Player.h"

void Player::initAnimations() {
    animation->addAnimation("IDLE", 15.f, 0, 0, 6, 0, 64, 64);
    animation->addAnimation("WALK_RIGHT", 16.f, 0, 1, 6, 1, 64, 64);
    animation->addAnimation("WALK_LEFT", 16.f, 0, 2, 6, 2, 64, 64);
    animation->addAnimation("ATTACK_RIGHT", 2.f, 0, 3, 4, 3, 64, 64);
    animation->addAnimation("ATTACK_LEFT", 2.f, 0, 4, 4, 4, 64, 64);
}

Player::Player(float x, float y, sf::Texture &texture_sheet) {
    attacking = false;
    hpMax = 100;
    hp = hpMax;
    weapon = new Weapon(3,50,1);
    last_move = MOVING_RIGHT;
    createMovement(250.f, 1600.f, 500.f);
    createAnimation(texture_sheet);
    createHitBox(sprite, 10, 0, 45, 60);
    sprite.setPosition(x,y);
    initAnimations();
}

Player::~Player() = default;

Weapon *Player::getWeapon() {
    return weapon;
}

void Player::updateAnimation(const float &tm) {
    if (attacking) {
        if (last_move == MOVING_RIGHT) {
            animation->play("ATTACK_RIGHT", tm, true);
            if (animation->isDone("ATTACK_RIGHT")) {
                attacking = false;
            }
        }
        if (last_move == MOVING_LEFT) {
            animation->play("ATTACK_LEFT", tm, true);
            if (animation->isDone("ATTACK_LEFT")) {
                attacking = false;
            }
        }
    }
    if (movement->getState(IDLE)) {
        animation->play("IDLE", tm);
    }
    else if (movement->getState(MOVING_LEFT)) {
        animation->play("WALK_LEFT", tm, movement->getVelocity().x, movement->getMaxVelocity());
        last_move = MOVING_LEFT;
    }
    else if (movement->getState(MOVING_RIGHT) || movement->getState(MOVING_DOWN)) {
        animation->play("WALK_RIGHT", tm, movement->getVelocity().x, movement->getMaxVelocity());
        last_move = MOVING_RIGHT;
    }
    else if (movement->getState(MOVING_UP)) {
        animation->play("WALK_LEFT", tm, movement->getVelocity().x, movement->getMaxVelocity());
    }
}

void Player::update(const float &tm) {
    movement->update(tm);
    updateAnimation(tm);
    hitbox->update();
}

void Player::render(sf::RenderTarget &target) {
    target.draw(sprite);
}

bool Player::getFaceDirection(Entity& entity) const {
    if ((movement->getState(MOVING_RIGHT) || last_move == MOVING_RIGHT) && entity.getPosition().x > sprite.getPosition().x) {
        return true;
    }
    else return (movement->getState(MOVING_LEFT) || last_move == MOVING_LEFT) && entity.getPosition().x < sprite.getPosition().x ;
}


