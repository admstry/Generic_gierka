//
// Created by Adam on 18.06.2020.
//

#include "pch.h"
#include "Spider.h"

void Spider::initVariables() {
    hpMax = 10;
    hp = hpMax;
}

void Spider::initAnimations() {
    animationComponent->addAnimation("IDLE", 15.f, 0, 0, 4, 0, 32, 32);
}

void Spider::initGui() {
    hpBar.setFillColor(sf::Color::Red);
    hpBar.setSize(sf::Vector2f(60.f,10.f));
    hpBar.setPosition(sprite.getPosition());
}

Spider::Spider(float x, float y, sf::Texture &texture_sheet) {
    initVariables();
    initGui();
    createMovementComponent(200.f, 800.f, 500.f);
    createAnimationComponent(texture_sheet);
    createHitboxComponent(sprite,32,64,32,32);
    sprite.setPosition(x,y);
    initAnimations();
    sprite.setColor(sf::Color(rand()%255,rand()%255,rand()%255,255));
    sprite.setScale(3.f,3.f);
}

Spider::~Spider() = default;

void Spider::updateGui() {
    hpBar.setSize(sf::Vector2f(60.f * hp / hpMax,10.f));
    hpBar.setPosition(sprite.getPosition());
}

void Spider::updateAnimation(const float &tm) {
    if (this->movementComponent->getState(IDLE))
    {
        this->animationComponent->play("IDLE", tm);
    }
}

void Spider::update(const float &tm) {
    movementComponent->update(tm);
    updateGui();
    updateAnimation(tm);
    hitboxComponent->update();
}

void Spider::render(sf::RenderTarget &target) {
    target.draw(sprite);
    hitboxComponent->render(target);
    target.draw(hpBar);
}





