//
// Created by Adam on 18.06.2020.
//

#ifndef GENERIC_GIERKA_SPIDER_H
#define GENERIC_GIERKA_SPIDER_H

#include "Entity.h"

class Spider : public Entity {
private:
    int hp;
    bool attacking;
    void initVariables();
    void initComponents();
    void initAnimations();
public:
    Spider(float x, float y, sf::Texture &texture_sheet);
    ~Spider();
    int getHp() const;
    void loseHp(int hp);
    void updateAnimation(const float& tm);
    void update(const float& tm) override;
    void render(sf::RenderTarget& target) override;
};


#endif //GENERIC_GIERKA_SPIDER_H
