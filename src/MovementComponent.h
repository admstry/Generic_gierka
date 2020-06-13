//
// Created by Adam on 13.06.2020.
//

#ifndef GENERIC_GIERKA_MOVEMENTCOMPONENT_H
#define GENERIC_GIERKA_MOVEMENTCOMPONENT_H


enum movement_states { IDLE = 0, MOVING, MOVING_LEFT, MOVING_RIGHT, MOVING_UP, MOVING_DOWN };

class MovementComponent
{
private:
    sf::Sprite& sprite;

    float maxVelocity;
    float acceleration;
    float deceleration;

    sf::Vector2f velocity;

    //Initializer functions

public:
    MovementComponent(sf::Sprite& sprite,
                      float maxVelocity, float acceleration, float deceleration);
    virtual ~MovementComponent();

    //Accessors
    const float& getMaxVelocity() const;
    const sf::Vector2f& getVelocity() const;

    //Functions
    bool getState(short unsigned state) const;
    void stopVelocity();
    void stopVelocityX();
    void stopVelocityY();

    void move(float x, float y, const float& dt);
    void update(const float& dt);
};

#endif //GENERIC_GIERKA_MOVEMENTCOMPONENT_H
