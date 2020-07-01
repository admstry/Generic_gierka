//
// Created by Adam on 18.06.2020.
//

#ifndef GENERIC_GIERKA_SPIDER_H
#define GENERIC_GIERKA_SPIDER_H

#include "Entity.h"

class Spider : public Entity {
private:
    // functions
    void initVariables();
    void initAnimations();
    void initGui();
    // variables
    sf::RectangleShape hpBar;
public:
    Spider(float x, float y, sf::Texture &texture_sheet);
    ~Spider() override;
    // functions
    void updateGui();
    void updateAnimation(const float& tm);
    void update(const float& tm) override;
    void render(sf::RenderTarget& target) override;
};


#endif //GENERIC_GIERKA_SPIDER_H
