//
// Created by Adam on 13.06.2020.
//

#include "pch.h"
#include "MovementComponent.h"

MovementComponent::MovementComponent(sf::Sprite &sprite,
                                     float maxVelocity, float acceleration, float deceleration)
        : sprite(sprite),
          maxVelocity(maxVelocity), acceleration(acceleration), deceleration(deceleration) {

}

MovementComponent::~MovementComponent() = default;

//Accessors
const float &MovementComponent::getMaxVelocity() const {
    return maxVelocity;
}

const sf::Vector2f &MovementComponent::getVelocity() const {
    return velocity;
}

//Functions
bool MovementComponent::getState(const short unsigned state) const {
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

void MovementComponent::stopVelocity() {
    /* Resets the velocity to 0.*/

    velocity.x = 0.f;
    velocity.y = 0.f;
}

void MovementComponent::stopVelocityX() {
    /* Resets the velocity x to 0.*/

    velocity.x = 0.f;
}

void MovementComponent::stopVelocityY() {
    /* Resets the velocity y to 0.*/

    velocity.y = 0.f;
}

void MovementComponent::move(const float dir_x, const float dir_y, const float &dt) {
    /* Accelerating a sprite until it reaches the max velocity. */

    velocity.x += acceleration * dir_x * dt;
    velocity.y += acceleration * dir_y * dt;
}

void MovementComponent::update(const float &dt) {
    /*
    Decelerates the sprite and controls the maximum velocity.
    Moves the sprite.
    */

    if (velocity.x > 0.f) //Check for positive x
    {
        //Max velocity check
        if (velocity.x > maxVelocity)
            velocity.x = maxVelocity;

        //Deceleration
        velocity.x -= deceleration * dt;
        if (velocity.x < 0.f)
            velocity.x = 0.f;
    } else if (velocity.x < 0.f) //Check for negative x
    {
        //Max velocity check
        if (velocity.x < -maxVelocity)
            velocity.x = -maxVelocity;

        //Deceleration
        velocity.x += deceleration * dt;
        if (velocity.x > 0.f)
            velocity.x = 0.f;
    }

    if (velocity.y > 0.f) //Check for positive y
    {
        //Max velocity check
        if (velocity.y > maxVelocity)
            velocity.y = maxVelocity;

        //Deceleration
        velocity.y -= deceleration * dt;
        if (velocity.y < 0.f)
            velocity.y = 0.f;
    } else if (velocity.y < 0.f) //Check for negative y
    {
        //Max velocity check
        if (velocity.y < -maxVelocity)
            velocity.y = -maxVelocity;

        //Deceleration
        velocity.y += deceleration * dt;
        if (velocity.y > 0.f)
            velocity.y = 0.f;
    }

    //Final move
    sprite.move(velocity * dt); //Uses velocity
}