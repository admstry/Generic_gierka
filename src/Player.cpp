//
// Created by Adam on 16.06.2020.
//

#include "pch.h"
#include "Player.h"

void Player::initVariables() {
    attacking = false;
}

void Player::initComponents() {

}

void Player::initAnimations() {

}

Player::Player(float x, float y, sf::Texture &texture_sheet) {
    initVariables();
    initComponents();
    initAnimations();

    createAnimationComponent(texture_sheet);
}

Player::~Player() = default;

void Player::updateAnimation(float &tm) {

}

void Player::update(const float &tm) {

}

void Player::render(sf::RenderTarget &target) {

    this->render(target);
}
