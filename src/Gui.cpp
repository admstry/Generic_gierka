//
// Created by Adam on 14.06.2020.
//
#include "pch.h"
#include "Gui.h"

float gui::p2pX(const float perc, const sf::VideoMode& vm) {
    return std::floor(static_cast<float>(vm.width) * (perc / 100.f));
}

float gui::p2pY(const float perc, const sf::VideoMode& vm) {
    return std::floor(static_cast<float>(vm.height) * (perc / 100.f));
}

unsigned gui::calcCharSize(const sf::VideoMode& vm, const unsigned modifier) {
     return static_cast<unsigned>((vm.width + vm.height) / modifier);
}

gui::Button::Button(float x, float y, float width, float height,
                    sf::Font* font_, const std::string& text_, unsigned character_size,
                    sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
                    sf::Color idle_color, sf::Color hover_color, sf::Color active_color,
                    sf::Color outline_idle_color, sf::Color outline_hover_color, sf::Color outline_active_color,
                    short unsigned id_) {
    buttonState = BTN_IDLE;
    id = id_;

    shape.setPosition(sf::Vector2f(x, y));
    shape.setSize(sf::Vector2f(width, height));
    shape.setFillColor(idle_color);
    shape.setOutlineThickness(1.f);
    shape.setOutlineColor(outline_idle_color);

    font = font_;
    text.setFont(*font);
    text.setString(text_);
    text.setFillColor(text_idle_color);
    text.setCharacterSize(character_size);
    std::cout << text.getGlobalBounds().width << "\n";
    text.setPosition(
            shape.getPosition().x + (shape.getGlobalBounds().width / 2.f) - text.getGlobalBounds().width / 2.f,
            shape.getPosition().y
    );

    textIdleColor = text_idle_color;
    textHoverColor = text_hover_color;
    textActiveColor = text_active_color;

    idleColor = idle_color;
    hoverColor = hover_color;
    activeColor = active_color;

    outlineIdleColor = outline_idle_color;
    outlineHoverColor = outline_hover_color;
    outlineActiveColor = outline_active_color;
}

gui::Button::~Button()
= default;

//Accessors
bool gui::Button::isPressed() const {
    if (buttonState == BTN_ACTIVE)
        return true;

    return false;
}

std::string gui::Button::getText() const {
    return text.getString();
}

const short unsigned & gui::Button::getId() const {
    return id;
}

// modifiers
void gui::Button::setText(const std::string& text_) {
    text.setString(text_);
}

void gui::Button::setId(const short unsigned id_) {
    id = id_;
}

// functions
void gui::Button::update(const sf::Vector2i& mousePosWindow) {

    // idle
    buttonState = BTN_IDLE;

    // hover
    if (shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow))) {
        buttonState = BTN_HOVER;

        // pressed
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            buttonState = BTN_ACTIVE;
        }
    }

    switch (buttonState) {
        case BTN_IDLE:
            shape.setFillColor(idleColor);
            text.setFillColor(textIdleColor);
            shape.setOutlineColor(outlineIdleColor);
            break;

        case BTN_HOVER:
            shape.setFillColor(hoverColor);
            text.setFillColor(textHoverColor);
            shape.setOutlineColor(outlineHoverColor);
            break;

        case BTN_ACTIVE:
            shape.setFillColor(activeColor);
            text.setFillColor(textActiveColor);
            shape.setOutlineColor(outlineActiveColor);
            break;

        default:
            shape.setFillColor(sf::Color::Red);
            text.setFillColor(sf::Color::Blue);
            shape.setOutlineColor(sf::Color::Green);
            break;
    }
}

void gui::Button::render(sf::RenderTarget& target) {
    target.draw(shape);
    target.draw(text);
}

// DropDownList [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]
gui::DropDownList::DropDownList(float x, float y, float width, float height,
                                sf::Font& font, std::string list[],
                                unsigned nrOfElements, unsigned default_index)
        : font(font), showList(false), keytimeMax(1.f), keytime(0.f) {

    activeElement = new gui::Button(
            x, y, width, height,
            &this->font, list[default_index], 14,
            sf::Color(255, 255, 255, 150), sf::Color(255, 255, 255, 200), sf::Color(20, 20, 20, 50),
            sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200),
            sf::Color(255, 255, 255, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50)
    );

    for (unsigned i = 0; i < nrOfElements; i++) {
        this->list.push_back(
                new gui::Button(
                        x, y + ((i+1) * height), width, height,
                        &this->font, list[i], 14,
                        sf::Color(255, 255, 255, 150), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
                        sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200),
                        sf::Color(255, 255, 255, 0), sf::Color(255, 255, 255, 0), sf::Color(20, 20, 20, 0),
                        i
                )
        );
    }
}

gui::DropDownList::~DropDownList() {
    delete activeElement;
    for (auto & i : list)
    {
        delete i;
    }
}

//Accessors
bool gui::DropDownList::getKeytime() {
    if (keytime >= keytimeMax)
    {
        keytime = 0.f;
        return true;
    }

    return false;
}

const unsigned short & gui::DropDownList::getActiveElementId() const {
    return activeElement->getId();
}

//Functions
void gui::DropDownList::updateKeytime(const float& tm) {
    if (keytime < keytimeMax)
        keytime += 10.f * tm;
}

void gui::DropDownList::update(const sf::Vector2i & mousePosWindow, const float& tm) {
    updateKeytime(tm);

    activeElement->update(mousePosWindow);

    //Show and hide the list
    if (activeElement->isPressed() && getKeytime()) {
        showList = !showList;
    }

    if (showList) {
        for (auto &i : list) {
            i->update(mousePosWindow);

            if (i->isPressed() && getKeytime()) {
                showList = false;
                activeElement->setText(i->getText());
                activeElement->setId(i->getId());
            }
        }
    }
}

void gui::DropDownList::render(sf::RenderTarget & target) {
    activeElement->render(target);

    if (showList) {
        for (auto &i : list) {
            i->render(target);
        }
    }
}
// DropDownList [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]