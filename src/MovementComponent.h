//
// Created by Adam on 16.06.2020.
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

    void initVariables();

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
    void setVelocity(sf::Vector2f velocity);

    void move(float dir_x, float dir_y, const float& tm);
    void update(const float& tm);
};


#endif //GENERIC_GIERKA_MOVEMENTCOMPONENT_H
