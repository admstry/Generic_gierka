//
// Created by Adam on 16.06.2020.
//

#ifndef GENERIC_GIERKA_MOVEMENT_H
#define GENERIC_GIERKA_MOVEMENT_H


enum movement_states { IDLE = 0, MOVING, MOVING_LEFT, MOVING_RIGHT, MOVING_UP, MOVING_DOWN };

class Movement
{
private:
    // variables
    sf::Sprite& sprite;

    float maxVelocity;
    float acceleration;
    float deceleration;

    sf::Vector2f velocity;

    // functions

    void initVariables();

public:
    Movement(sf::Sprite& sprite,
             float maxVelocity, float acceleration, float deceleration);
    virtual ~Movement();
    // functions
    [[nodiscard]] const float& getMaxVelocity() const;
    [[nodiscard]] const sf::Vector2f& getVelocity() const;
    [[nodiscard]] bool getState(short unsigned state) const;
    void stopVelocity();
    void stopVelocityX();
    void stopVelocityY();
    void setVelocity(sf::Vector2f velocity);

    void move(float dir_x, float dir_y, const float& tm);
    void update(const float& tm);
};


#endif //GENERIC_GIERKA_MOVEMENT_H
