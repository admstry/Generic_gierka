//
// Created by Adam on 16.06.2020.
//

#ifndef GENERIC_GIERKA_ANIMATE_H
#define GENERIC_GIERKA_ANIMATE_H


class Animate
{
private:
    class Animation
    {
    public:
        // variables
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

        Animation(sf::Sprite& sprite_, sf::Texture& texture_sheet,
                  float animation_timer,
                  int start_frame_x, int start_frame_y, int frames_x, int frames_y, int width_, int height_)
                : sprite(sprite_), textureSheet(texture_sheet),
                  animationTimer(animation_timer), timer(0.f), done(false),
                  width(width_), height(height_) {
            startRect = sf::IntRect(start_frame_x * width, start_frame_y * height, width, height);
            currentRect = startRect;
            endRect = sf::IntRect(frames_x * width, frames_y * height, width, height);

            sprite.setTexture(textureSheet, true);
            sprite.setTextureRect(startRect);
        }
        // functions
        [[nodiscard]] const bool& isDone() const {
            return done;
        }

        const bool& play(const float& tm) {
            done = false;
            timer += 100.f * tm;
            if (timer >= animationTimer) {
                timer = 0.f;

                if (currentRect != endRect) {
                    currentRect.left += width;
                }
                else {
                    currentRect.left = startRect.left;
                    done = true;
                }

                sprite.setTextureRect(currentRect);
            }

            return done;
        }

        const bool& play(const float& tm, float mod_percent) {
            if (mod_percent < 0.5f)
                mod_percent = 0.5f;

            done = false;
            timer += mod_percent * 100.f * tm;
            if (timer >= animationTimer) {
                timer = 0.f;

                if (currentRect != endRect) {
                    currentRect.left += width;
                }
                else {
                    currentRect.left = startRect.left;
                    done = true;
                }

                sprite.setTextureRect(currentRect);
            }

            return done;
        }

        void reset() {
            timer = animationTimer;
            currentRect = startRect;
        }
    };

    // variables
    sf::Sprite& sprite;
    sf::Texture& textureSheet;
    std::map<std::string, Animation*> animations;
    Animation* lastAnimation;
    Animation* priorityAnimation;

public:
    Animate(sf::Sprite& sprite, sf::Texture& texture_sheet);
    virtual ~Animate();
    // functions
    const bool& isDone(const std::string& key);

    void addAnimation(const std::string& key,
                      float animation_timer,
                      int start_frame_x, int start_frame_y, int frames_x, int frames_y, int width, int height);

    const bool& play(const std::string& key, const float& tm, bool priority = false);
    const bool& play(const std::string& key, const float& tm, const float& modifier, const float& modifier_max, bool priority = false);
};


#endif //GENERIC_GIERKA_ANIMATE_H
