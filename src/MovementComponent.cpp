//
// Created by Adam on 16.06.2020.
//

#include "pch.h"
#include "MovementComponent.h"

void MovementComponent::initVariables() {
    velocity = sf::Vector2f(0.f,0.f);
}

MovementComponent::MovementComponent(sf::Sprite &sprite, float maxVelocity, float acceleration, float deceleration)
    : sprite(sprite), maxVelocity(maxVelocity), acceleration(acceleration), deceleration(deceleration) {
    initVariables();
}

MovementComponent::~MovementComponent() = default;

const float &MovementComponent::getMaxVelocity() const {
    return maxVelocity;
}

const sf::Vector2f &MovementComponent::getVelocity() const {
    return velocity;
}

bool MovementComponent::getState(const unsigned short state) const {
    switch (state)
    {
        case IDLE:
            if (this->velocity.x == 0.f && this->velocity.y == 0.f)
                return true;
            break;
        case MOVING:
            if (this->velocity.x != 0.f || this->velocity.y != 0.f)
                return true;
            break;
        case MOVING_LEFT:
            if (this->velocity.x < 0.f)
                return true;
            break;
        case MOVING_RIGHT:
            if (this->velocity.x > 0.f)
                return true;
            break;
        case MOVING_UP:
            if (this->velocity.y < 0.f)
                return true;
            break;
        case MOVING_DOWN:
            if (this->velocity.y > 0.f)
                return true;
            break;
        default:
            break;
    }
    return false;
}

void MovementComponent::stopVelocity() {
    velocity.x = 0;
    velocity.y = 0;
}

void MovementComponent::stopVelocityX() {
    velocity.x = 0;
}

void MovementComponent::stopVelocityY() {
    velocity.y = 0;
}

void MovementComponent::move(const float dir_x, const float dir_y, const float &tm) {
    velocity.x += acceleration * dir_x * tm;
    velocity.y += acceleration * dir_y * tm;
}

void MovementComponent::update(const float &tm) {
    if (velocity.x > 0.f) //Check for positive x
    {
        //Max velocity check
        if (velocity.x > maxVelocity)
            velocity.x = maxVelocity;

        //Deceleration
        velocity.x -= deceleration * tm;
        if (velocity.x < 0.f)
            velocity.x = 0.f;
    }
    else if(velocity.x < 0.f) //Check for negative x
    {
        //Max velocity check
        if (velocity.x < -maxVelocity)
            velocity.x = -maxVelocity;

        //Deceleration
        velocity.x += deceleration * tm;
        if (velocity.x > 0.f)
            velocity.x = 0.f;
    }

    if (velocity.y > 0.f) //Check for positive y
    {
        //Max velocity check
        if (velocity.y > maxVelocity)
            velocity.y = maxVelocity;

        //Deceleration
        velocity.y -= deceleration * tm;
        if (velocity.y < 0.f)
            velocity.y = 0.f;
    }
    else if (velocity.y < 0.f) //Check for negative y
    {
        //Max velocity check
        if (velocity.y < -maxVelocity)
            velocity.y = -maxVelocity;

        //Deceleration
        velocity.y += deceleration * tm;
        if (velocity.y > 0.f)
            velocity.y = 0.f;
    }

    //Final move
    sprite.move(velocity * tm); //Uses velocity
}

void MovementComponent::setVelocity(sf::Vector2f velocity_) {
    velocity.x = velocity_.x;
    velocity.y = velocity_.y;
}
