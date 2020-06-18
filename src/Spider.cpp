//
// Created by Adam on 18.06.2020.
//

#include "pch.h"
#include "Spider.h"

void Spider::initVariables() {
    hp = 5;
}

void Spider::initComponents() {

}

void Spider::initAnimations() {
    animationComponent->addAnimation("IDLE", 15.f, 0, 0, 4, 0, 32, 32);
}

Spider::Spider(float x, float y, sf::Texture &texture_sheet) {
    createMovementComponent(250.f, 1600.f, 500.f);
    createAnimationComponent(texture_sheet);
    createHitboxComponent(sprite,32,64,32,32);
    sprite.setPosition(x,y);
    initAnimations();
    sprite.setScale(3.f,3.f);
}

Spider::~Spider() = default;

void Spider::updateAnimation(const float &tm) {
    if (this->movementComponent->getState(IDLE))
    {
        this->animationComponent->play("IDLE", tm);
    }
}

void Spider::update(const float &tm) {
    movementComponent->update(tm);
    updateAnimation(tm);
    hitboxComponent->update();
}

void Spider::render(sf::RenderTarget &target) {
    target.draw(sprite);
    hitboxComponent->render(target);
}

int Spider::getHp() const {
    return hp;
}

void Spider::loseHp(int hp) {
    this->hp -= hp;
}
