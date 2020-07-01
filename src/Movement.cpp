//
// Created by Adam on 16.06.2020.
//

#include "pch.h"
#include "Movement.h"

void Movement::initVariables() {
    velocity = sf::Vector2f(0.f,0.f);
}

Movement::Movement(sf::Sprite &sprite, float maxVelocity, float acceleration, float deceleration)
    : sprite(sprite), maxVelocity(maxVelocity), acceleration(acceleration), deceleration(deceleration) {
    initVariables();
}

Movement::~Movement() = default;

const float &Movement::getMaxVelocity() const {
    return maxVelocity;
}

const sf::Vector2f &Movement::getVelocity() const {
    return velocity;
}

bool Movement::getState(const unsigned short state) const {
    switch (state) {
        case IDLE:
            if (velocity.x == 0.f && velocity.y == 0.f)
                return true;
            break;
        case MOVING:
            if (velocity.x != 0.f || velocity.y != 0.f)
                return true;
            break;
        case MOVING_LEFT:
            if (velocity.x < 0.f)
                return true;
            break;
        case MOVING_RIGHT:
            if (velocity.x > 0.f)
                return true;
            break;
        case MOVING_UP:
            if (velocity.y < 0.f)
                return true;
            break;
        case MOVING_DOWN:
            if (velocity.y > 0.f)
                return true;
            break;
        default:
            break;
    }
    return false;
}

void Movement::stopVelocity() {
    velocity.x = 0;
    velocity.y = 0;
}

void Movement::stopVelocityX() {
    velocity.x = 0;
}

void Movement::stopVelocityY() {
    velocity.y = 0;
}

void Movement::move(const float dir_x, const float dir_y, const float &tm) {
    velocity.x += acceleration * dir_x * tm;
    velocity.y += acceleration * dir_y * tm;
}

void Movement::update(const float &tm) {
    // right
    if (velocity.x > 0.f) {
        // max velocity
        if (velocity.x > maxVelocity)
            velocity.x = maxVelocity;

        // deceleration
        velocity.x -= deceleration * tm;
        if (velocity.x < 0.f)
            velocity.x = 0.f;
    }
    // left
    else if(velocity.x < 0.f) {
        // max velocity
        if (velocity.x < -maxVelocity)
            velocity.x = -maxVelocity;

        // deceleration
        velocity.x += deceleration * tm;
        if (velocity.x > 0.f)
            velocity.x = 0.f;
    }

    // down
    if (velocity.y > 0.f) {
        // max velocity
        if (velocity.y > maxVelocity)
            velocity.y = maxVelocity;

        // deceleration
        velocity.y -= deceleration * tm;
        if (velocity.y < 0.f)
            velocity.y = 0.f;
    }
    // up
    else if (velocity.y < 0.f) {
        // max velocity
        if (velocity.y < -maxVelocity)
            velocity.y = -maxVelocity;

        // deceleration
        velocity.y += deceleration * tm;
        if (velocity.y > 0.f)
            velocity.y = 0.f;
    }

    // move with velocity
    sprite.move(velocity * tm);
}

void Movement::setVelocity(sf::Vector2f velocity_) {
    velocity.x = velocity_.x;
    velocity.y = velocity_.y;
}
