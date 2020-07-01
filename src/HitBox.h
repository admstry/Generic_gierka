//
// Created by Adam on 18.06.2020.
//

#ifndef GENERIC_GIERKA_HITBOX_H
#define GENERIC_GIERKA_HITBOX_H

class HitBox
{
private:
    // variables
    sf::Sprite& sprite;
    sf::RectangleShape hitBox;
    sf::FloatRect nextPosition;
    float offsetX;
    float offsetY;

public:
    HitBox(sf::Sprite& sprite_,
           float offset_x, float offset_y,
           float width, float height);
    virtual ~HitBox();

    // functions
    const sf::Vector2f& getPosition() const;
    sf::FloatRect getGlobalBounds() const;
    const sf::FloatRect& getNextPosition(const sf::Vector2f& velocity);


    void setPosition(const sf::Vector2f& position);
    void setPosition(float x, float y);

    bool intersects(const sf::FloatRect& floatRect);

    void update();
    void render(sf::RenderTarget& target);
};


#endif //GENERIC_GIERKA_HITBOX_H
