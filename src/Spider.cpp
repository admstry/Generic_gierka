//
// Created by Adam on 18.06.2020.
//

#include "pch.h"
#include "Spider.h"

void Spider::initVariables() {
    hpMax = 5;
    hp = hpMax;
}

void Spider::initAnimations() {
    animation->addAnimation("IDLE", 15.f, 0, 0, 4, 0, 16, 16);
    animation->addAnimation("WALK_LEFT", 16.f, 0, 1, 5, 1, 16, 16);
    animation->addAnimation("WALK_RIGHT", 16.f, 0, 2, 5, 2, 16, 16);
}

void Spider::initGui() {
    hpBar.setFillColor(sf::Color::Red);
    hpBar.setSize(sf::Vector2f(60.f,10.f));
    hpBar.setPosition(sprite.getPosition());
}

Spider::Spider(float x, float y, sf::Texture &texture_sheet) {
    initVariables();
    initGui();
    createMovement(200.f, 800.f, 500.f);
    createAnimation(texture_sheet);
    createHitBox(sprite, 0, 0, 16 * 3, 16 * 3);
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
    if (this->movement->getState(IDLE)) {
        this->animation->play("IDLE", tm);
    }
    else if (movement->getState(MOVING_LEFT)) {
        animation->play("WALK_LEFT", tm, movement->getVelocity().x, movement->getMaxVelocity());
    }
    else if (movement->getState(MOVING_RIGHT) || movement->getState(MOVING_DOWN)) {
        animation->play("WALK_RIGHT", tm, movement->getVelocity().x, movement->getMaxVelocity());
    }
    else if (movement->getState(MOVING_UP)) {
        animation->play("WALK_LEFT", tm, movement->getVelocity().x, movement->getMaxVelocity());
    }
}

void Spider::update(const float &tm) {
    movement->update(tm);
    updateGui();
    updateAnimation(tm);
    hitbox->update();
}

void Spider::render(sf::RenderTarget &target) {
    target.draw(sprite);
    target.draw(hpBar);
}





