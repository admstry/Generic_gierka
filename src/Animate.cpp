//
// Created by Adam on 16.06.2020.
//

#include "pch.h"
#include "Animate.h"

Animate::Animate(sf::Sprite& sprite, sf::Texture& texture_sheet)
        :sprite(sprite), textureSheet(texture_sheet), lastAnimation(nullptr), priorityAnimation(nullptr) {

}

Animate::~Animate() {
    for (auto &animation : animations)
    {
        delete animation.second;
    }
}

//Accessors
const bool & Animate::isDone(const std::string& key) {
    return animations[key]->isDone();
}

//Functions
void Animate::addAnimation(
        const std::string& key,
        float animation_timer,
        int start_frame_x, int start_frame_y, int frames_x, int frames_y, int width, int height) {
    animations[key] = new Animation(
            sprite, textureSheet,
            animation_timer,
            start_frame_x, start_frame_y, frames_x, frames_y, width, height
    );
}

const bool& Animate::play(const std::string& key, const float & tm, const bool priority) {
    if (priorityAnimation) {
        if (priorityAnimation == animations[key]) {
            if (lastAnimation != animations[key]) {
                if (lastAnimation == nullptr) {
                    lastAnimation = animations[key];
                }
                else {
                    lastAnimation->reset();
                    lastAnimation = animations[key];
                }
            }

            if (animations[key]->play(tm)) {
                priorityAnimation = nullptr;
            }
        }
    }
    else {
        if (priority) {
            priorityAnimation = animations[key];
        }

        if (lastAnimation != animations[key]) {
            if (lastAnimation == nullptr)
                lastAnimation = animations[key];
            else {
                lastAnimation->reset();
                lastAnimation = animations[key];
            }
        }

        animations[key]->play(tm);
    }
    return animations[key]->isDone();
}

const bool& Animate::play(const std::string& key, const float & tm, const float& modifier, const float& modifier_max, const bool priority) {
    if (priorityAnimation) {
        if (priorityAnimation == animations[key]) {
            if (lastAnimation != animations[key]) {
                if (lastAnimation == nullptr)
                    lastAnimation = animations[key];
                else {
                    lastAnimation->reset();
                    lastAnimation = animations[key];
                }
            }

            if (animations[key]->play(tm, std::abs(modifier / modifier_max))) {
                priorityAnimation = nullptr;
            }
        }
    }
    else {
        if (priority) {
            priorityAnimation = animations[key];
        }

        if (lastAnimation != animations[key]) {
            if (lastAnimation == nullptr)
                lastAnimation = animations[key];
            else {
                lastAnimation->reset();
                lastAnimation = animations[key];
            }
        }

        animations[key]->play(tm, std::abs(modifier / modifier_max));
    }

    return animations[key]->isDone();
}