//
// Created by Adam on 13.06.2020.
//

#ifndef GENERIC_GIERKA_ANIMATIONCOMPONENT_H
#define GENERIC_GIERKA_ANIMATIONCOMPONENT_H


class AnimationComponent
{
private:
    class Animation
    {
    public:
        //Variables
        sf::Sprite& sprite;
        sf::Texture& textureSheet;
        float animationTimer;
        float timer;
        bool done;
        int width;
        int height;
        sf::IntRect startRect;
        sf::IntRect currentRect;
        sf::IntRect endRect;

        Animation(sf::Sprite& sprite, sf::Texture& texture_sheet,
                  float animation_timer,
                  int start_frame_x, int start_frame_y, int frames_x, int frames_y, int width, int height)
                : sprite(sprite), textureSheet(texture_sheet),
                  animationTimer(animation_timer), timer(0.f), done(false),
                  width(width), height(height)
        {
            startRect = sf::IntRect(start_frame_x * width, start_frame_y * height, width, height);
            currentRect = startRect;
            endRect = sf::IntRect(frames_x * width, frames_y * height, width, height);

            this->sprite.setTexture(textureSheet, true);
            this->sprite.setTextureRect(startRect);
        }

        //Accessor
        const bool& isDone() const
        {
            return done;
        }

        //Functions
        const bool& play(const float& dt)
        {
            //Update timer
            done = false;
            timer += 100.f * dt;
            if (timer >= animationTimer)
            {
                //reset timer
                timer = 0.f;

                //Animate
                if (currentRect != endRect)
                {
                    currentRect.left += width;
                }
                else //Reset
                {
                    currentRect.left = startRect.left;
                    done = true;
                }

                sprite.setTextureRect(currentRect);
            }

            return done;
        }

        const bool& play(const float& dt, float mod_percent)
        {
            //Update timer
            if (mod_percent < 0.5f)
                mod_percent = 0.5f;

            done = false;
            timer += mod_percent * 100.f * dt;
            if (timer >= animationTimer)
            {
                //reset timer
                timer = 0.f;

                //Animate
                if (currentRect != endRect)
                {
                    currentRect.left += width;
                }
                else //Reset
                {
                    currentRect.left = startRect.left;
                    done = true;
                }

                sprite.setTextureRect(currentRect);
            }

            return done;
        }

        void reset()
        {
            timer = animationTimer;
            currentRect = startRect;
        }
    };

    sf::Sprite& sprite;
    sf::Texture& textureSheet;
    std::map<std::string, Animation*> animations;
    Animation* lastAnimation;
    Animation* priorityAnimation;

public:
    AnimationComponent(sf::Sprite& sprite, sf::Texture& texture_sheet);
    virtual ~AnimationComponent();

    //Accessor
    const bool& isDone(const std::string& key);

    //Functions
    void addAnimation(const std::string& key,
                      float animation_timer,
                      int start_frame_x, int start_frame_y, int frames_x, int frames_y, int width, int height);

    const bool& play(const std::string& key, const float& dt, bool priority = false);
    const bool& play(const std::string& key, const float& dt, const float& modifier, const float& modifier_max, bool priority = false);
};

#endif //GENERIC_GIERKA_ANIMATIONCOMPONENT_H
