//
// Created by Adam on 13.06.2020.
//

#ifndef GENERIC_GIERKA_HITBOXCOMPONENT_H
#define GENERIC_GIERKA_HITBOXCOMPONENT_H


class HitboxComponent
{
private:
    sf::Sprite& sprite;
    sf::RectangleShape hitbox;
    sf::FloatRect nextPosition;
    float offsetX;
    float offsetY;

public:
    HitboxComponent(sf::Sprite& sprite,
                    float offset_x, float offset_y,
                    float width, float height);
    virtual ~HitboxComponent();

    //Accessors
    const sf::Vector2f& getPosition() const;
    sf::FloatRect getGlobalBounds() const;
    const sf::FloatRect& getNextPosition(const sf::Vector2f& velocity);

    //Modifiers
    void setPosition(const sf::Vector2f& position);
    void setPosition(float x, float y);

    //Functions
    bool intersects(const sf::FloatRect& frect);

    void update();
    void render(sf::RenderTarget& target);
};

#endif //GENERIC_GIERKA_HITBOXCOMPONENT_H
