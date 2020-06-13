//
// Created by Adam on 13.06.2020.
//

#include "pch.h"
#include "AnimationComponent.h"

AnimationComponent::AnimationComponent(sf::Sprite& sprite, sf::Texture& texture_sheet)
        :sprite(sprite), textureSheet(texture_sheet), lastAnimation(nullptr), priorityAnimation(nullptr)
{

}

AnimationComponent::~AnimationComponent()
{
    for (auto &i : animations)
    {
        delete i.second;
    }
}

//Accessors
const bool & AnimationComponent::isDone(const std::string& key)
{
    return animations[key]->isDone();
}

//Functions
void AnimationComponent::addAnimation(
        const std::string& key,
        float animation_timer,
        int start_frame_x, int start_frame_y, int frames_x, int frames_y, int width, int height
)
{
    animations[key] = new Animation(
            sprite, textureSheet,
            animation_timer,
            start_frame_x, start_frame_y, frames_x, frames_y, width, height
    );
}

const bool& AnimationComponent::play(const std::string& key, const float & dt, const bool priority)
{
    if (priorityAnimation) //If there is a priority animation
    {
        if (priorityAnimation == animations[key])
        {
            if (lastAnimation != animations[key])
            {
                if (lastAnimation == nullptr)
                    lastAnimation = animations[key];
                else
                {
                    lastAnimation->reset();
                    lastAnimation = animations[key];
                }
            }

            //If the priority animation is done, remove it
            if (animations[key]->play(dt))
            {
                priorityAnimation = nullptr;
            }
        }
    }
    else //Play animation of no other priority animation is set
    {
        //If this is a priority animation, set it.
        if (priority)
        {
            priorityAnimation = animations[key];
        }

        if (lastAnimation != animations[key])
        {
            if (lastAnimation == nullptr)
                lastAnimation = animations[key];
            else
            {
                lastAnimation->reset();
                lastAnimation = animations[key];
            }
        }

        animations[key]->play(dt);
    }

    return animations[key]->isDone();
}

const bool& AnimationComponent::play(const std::string& key, const float & dt, const float& modifier, const float& modifier_max, const bool priority)
{
    if (priorityAnimation) //If there is a priority animation
    {
        if (priorityAnimation == animations[key])
        {
            if (lastAnimation != animations[key])
            {
                if (lastAnimation == nullptr)
                    lastAnimation = animations[key];
                else
                {
                    lastAnimation->reset();
                    lastAnimation = animations[key];
                }
            }

            //If the priority animation is done, remove it
            if (animations[key]->play(dt, std::abs(modifier / modifier_max)))
            {
                priorityAnimation = nullptr;
            }
        }
    }
    else //Play animation of no other priority animation is set
    {
        //If this is a priority animation, set it.
        if (priority)
        {
            priorityAnimation = animations[key];
        }

        if (lastAnimation != animations[key])
        {
            if (lastAnimation == nullptr)
                lastAnimation = animations[key];
            else
            {
                lastAnimation->reset();
                lastAnimation = animations[key];
            }
        }

        animations[key]->play(dt, std::abs(modifier / modifier_max));
    }

    return animations[key]->isDone();
}