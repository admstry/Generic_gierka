//
// Created by Adam on 18.06.2020.
//

#include "pch.h"
#include "Weapon.h"

Weapon::Weapon(unsigned int damage_, unsigned int range_, unsigned int atk_speed) {
    attackTimer.restart();
    attackTimerMax = 300;
    damage = damage_;
    range = range_;
}

Weapon::~Weapon() = default;

unsigned Weapon::getDamage() const {
    return damage;
}

const unsigned &Weapon::getRange() const {
    return range;
}

bool Weapon::getAttackTimer() {
    if (attackTimer.getElapsedTime().asMilliseconds() >= attackTimerMax) {
        attackTimer.restart();
        return true;
    }
    return false;
}


