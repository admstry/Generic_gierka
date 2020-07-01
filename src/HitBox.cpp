//
// Created by Adam on 18.06.2020.
//

#include "pch.h"
#include "HitBox.h"

HitBox::HitBox(sf::Sprite& sprite_,
               float offset_x, float offset_y,
               float width, float height)
        : sprite(sprite_), offsetX(offset_x), offsetY(offset_y) {
    nextPosition.left = 0.f;
    nextPosition.top = 0.f;
    nextPosition.width = width;
    nextPosition.height = height;

    hitBox.setPosition(sprite.getPosition().x + offset_x, sprite.getPosition().y + offset_y);
    hitBox.setSize(sf::Vector2f(width, height));
    hitBox.setFillColor(sf::Color::Transparent);
    hitBox.setOutlineThickness(-1.f);
    hitBox.setOutlineColor(sf::Color::Green);

}

HitBox::~HitBox()
= default;

//Accessors
const sf::Vector2f & HitBox::getPosition() const {
    return hitBox.getPosition();
}

sf::FloatRect HitBox::getGlobalBounds() const {
    return hitBox.getGlobalBounds();
}

const sf::FloatRect & HitBox::getNextPosition(const sf::Vector2f & velocity) {
    nextPosition.left = hitBox.getPosition().x + velocity.x;
    nextPosition.top = hitBox.getPosition().y + velocity.y;

    return nextPosition;
}

//Modifiers
void HitBox::setPosition(const sf::Vector2f& position) {
    hitBox.setPosition(position);
    sprite.setPosition(position.x - offsetX, position.y - offsetY);
}

void HitBox::setPosition(const float x, const float y) {
    hitBox.setPosition(x, y);
    sprite.setPosition(x - offsetX, y - offsetY);
}

//Functions
[[maybe_unused]] bool HitBox::intersects(const sf::FloatRect& floatRect) {
    return hitBox.getGlobalBounds().intersects(floatRect);
}

void HitBox::update() {
    hitBox.setPosition(sprite.getPosition().x + offsetX, sprite.getPosition().y + offsetY);
}

void HitBox::render(sf::RenderTarget & target) {
    target.draw(hitBox);
}