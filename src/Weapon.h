//
// Created by Adam on 18.06.2020.
//

#ifndef GENERIC_GIERKA_WEAPON_H
#define GENERIC_GIERKA_WEAPON_H


class Weapon {
private:
    void initVariables();
protected:
    unsigned damage;
    unsigned range;
    sf::Clock attackTimer;
    sf::Int32 attackTimerMax;
public:
    Weapon(unsigned damage,unsigned range,unsigned atk_speed);
    ~Weapon();

    unsigned getDamage() const;
    const unsigned& getRange() const;
    bool getAttackTimer();

};


#endif //GENERIC_GIERKA_WEAPON_H
