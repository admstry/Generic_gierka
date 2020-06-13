//
// Created by Adam on 13.06.2020.
//

#include "pch.h"
#include "Gui.h"

float gui::p2pX(const float perc, const sf::VideoMode& vm)
{
    /*
     * Converts a percentage value to pixels relative to the current resolution in the x-axis.
     *
     * @param		float perc				The percentage value.
     * @param		sf::VideoMode& vm		The current videomode of the window (resolution).
     *
     * @return		float					The calculated pixel value.
     */

    return std::floor(static_cast<float>(vm.width) * (perc / 100.f));
}

float gui::p2pY(const float perc, const sf::VideoMode& vm)
{
    /*
     * Converts a percentage value to pixels relative to the current resolution in the y-axis.
     *
     * @param		float perc				The percentage value.
     * @param		sf::VideoMode& vm		The current videomode of the window (resolution).
     *
     * @return		float					The calculated pixel value.
     */

    return std::floor(static_cast<float>(vm.height) * (perc / 100.f));
}

unsigned gui::calcCharSize(const sf::VideoMode& vm, const unsigned modifier)
{
    /*
     * Calculates the character size for text using the current resolution and a constant.
     *
     * @param		sf::VideoMode& vm		The current videomode of the window (resolution).
     * @param		unsigned modifier		Used to modify the character size in a more custom way.
     *
     * @return		unsigned				The calculated character size value.
     */

    return static_cast<unsigned>((vm.width + vm.height) / modifier);
}

gui::Button::Button(float x, float y, float width, float height,
                    sf::Font* font_, const std::string& text_, unsigned character_size,
                    sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
                    sf::Color idle_color, sf::Color hover_color, sf::Color active_color,
                    sf::Color outline_idle_color, sf::Color outline_hover_color, sf::Color outline_active_color,
                    short unsigned id_)
{
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

gui::Button::~Button() = default;

//Accessors
bool gui::Button::isPressed() const
{
    return buttonState == BTN_ACTIVE;

}

std::string gui::Button::getText() const
{
    return text.getString();
}

const short unsigned & gui::Button::getId() const
{
    return id;
}

//Modifiers
void gui::Button::setText(const std::string& text_)
{
    text.setString(text_);
}

void gui::Button::setId(const short unsigned id_)
{
    id = id_;
}

//Functions
void gui::Button::update(const sf::Vector2i& mousePosWindow)
{
    /*Update the booleans for hover and pressed*/

    //Idle
    buttonState = BTN_IDLE;

    //Hover
    if (shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow)))
    {
        buttonState = BTN_HOVER;

        //Pressed
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            buttonState = BTN_ACTIVE;
        }
    }

    switch (buttonState)
    {
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

void gui::Button::render(sf::RenderTarget& target)
{
    target.draw(shape);
    target.draw(text);
}

//DROP DOWN LIST =============================================

gui::DropDownList::DropDownList(float x, float y, float width, float height,
                                sf::Font& font, std::string list[],
                                unsigned nrOfElements, unsigned default_index)
        : font(font), showList(false), keytimeMax(1.f), keytime(0.f)
{
    //unsigned nrOfElements = sizeof(list) / sizeof(std::string);

    activeElement = new gui::Button(
            x, y, width, height,
            &this->font, list[default_index], 14,
            sf::Color(255, 255, 255, 150), sf::Color(255, 255, 255, 200), sf::Color(20, 20, 20, 50),
            sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200),
            sf::Color(255, 255, 255, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50)
    );

    for (unsigned i = 0; i < nrOfElements; i++)
    {
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

gui::DropDownList::~DropDownList()
{
    delete activeElement;
    for (auto & i : list)
    {
        delete i;
    }
}

//Accessors
bool gui::DropDownList::getKeytime()
{
    if (keytime >= keytimeMax)
    {
        keytime = 0.f;
        return true;
    }

    return false;
}

const unsigned short & gui::DropDownList::getActiveElementId() const
{
    return activeElement->getId();
}

//Functions
void gui::DropDownList::updateKeytime(const float& dt)
{
    if (keytime < keytimeMax)
        keytime += 10.f * dt;
}

void gui::DropDownList::update(const sf::Vector2i & mousePosWindow, const float& dt)
{
    updateKeytime(dt);

    activeElement->update(mousePosWindow);

    //Show and hide the list
    if (activeElement->isPressed() && getKeytime())
    {
        showList = !showList;
    }

    if (showList)
    {
        for (auto &i : list)
        {
            i->update(mousePosWindow);

            if (i->isPressed() && getKeytime())
            {
                showList = false;
                activeElement->setText(i->getText());
                activeElement->setId(i->getId());
            }
        }
    }
}

void gui::DropDownList::render(sf::RenderTarget & target)
{
    activeElement->render(target);

    if (showList)
    {
        for (auto &i : list)
        {
            i->render(target);
        }
    }
}

//TEXTURE SELECTOR ===================================================
gui::TextureSelector::TextureSelector(float x, float y, float width, float height,
                                      float gridSize, const sf::Texture* texture_sheet,
                                      sf::Font& font, const std::string& text)
        : keytimeMax(1.f), keytime(0.f)
{
    this->gridSize = gridSize;
    active = false;
    hidden = false;
    float offset = gridSize;

    bounds.setSize(sf::Vector2f(width, height));
    bounds.setPosition(x + offset, y);
    bounds.setFillColor(sf::Color(50, 50, 50, 100));
    bounds.setOutlineThickness(1.f);
    bounds.setOutlineColor(sf::Color(255, 255, 255, 200));

    sheet.setTexture(*texture_sheet);
    sheet.setPosition(x + offset, y);

    if (sheet.getGlobalBounds().width > bounds.getGlobalBounds().width)
    {
        sheet.setTextureRect(sf::IntRect(0, 0, static_cast<int>(bounds.getGlobalBounds().width), static_cast<int>(sheet.getGlobalBounds().height)));
    }
    if (sheet.getGlobalBounds().height > bounds.getGlobalBounds().height)
    {
        sheet.setTextureRect(sf::IntRect(0, 0, static_cast<int>(sheet.getGlobalBounds().width), static_cast<int>(bounds.getGlobalBounds().height)));
    }

    selector.setPosition(x + offset, y);
    selector.setSize(sf::Vector2f(gridSize, gridSize));
    selector.setFillColor(sf::Color::Transparent);
    selector.setOutlineThickness(1.f);
    selector.setOutlineColor(sf::Color::Red);

    textureRect.width = static_cast<int>(gridSize);
    textureRect.height = static_cast<int>(gridSize);

    hide_btn = new gui::Button(
            x, y, 50.f, 50.f,
            &font, text, 16,
            sf::Color(255, 255, 255, 200), sf::Color(255, 255, 255, 250), sf::Color(255, 255, 255, 50),
            sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 250), sf::Color(20, 20, 20, 50)
    );
}

gui::TextureSelector::~TextureSelector()
{
    delete hide_btn;
}

//Accessors
const bool& gui::TextureSelector::getActive() const
{
    return active;
}

const sf::IntRect& gui::TextureSelector::getTextureRect() const
{
    return textureRect;
}

bool gui::TextureSelector::getKeytime()
{
    if (keytime >= keytimeMax)
    {
        keytime = 0.f;
        return true;
    }

    return false;
}

//Functions
void gui::TextureSelector::updateKeytime(const float& dt)
{
    if (keytime < keytimeMax)
        keytime += 10.f * dt;
}

void gui::TextureSelector::update(const sf::Vector2i& mousePosWindow, const float& dt)
{
    updateKeytime(dt);
    hide_btn->update(mousePosWindow);

    if (hide_btn->isPressed() && getKeytime())
    {
        hidden = !hidden;
    }

    if (!hidden)
    {
        active = false;

        if (bounds.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow)))
        {
            active = true;

            mousePosGrid.x = (mousePosWindow.x - static_cast<int>(bounds.getPosition().x)) / static_cast<unsigned>(gridSize);
            mousePosGrid.y = (mousePosWindow.y - static_cast<int>(bounds.getPosition().y)) / static_cast<unsigned>(gridSize);

            selector.setPosition(
                    bounds.getPosition().x + mousePosGrid.x * gridSize,
                    bounds.getPosition().y + mousePosGrid.y * gridSize
            );

            //Update texture rectangle
            textureRect.left = static_cast<int>(selector.getPosition().x - bounds.getPosition().x);
            textureRect.top = static_cast<int>(selector.getPosition().y - bounds.getPosition().y);
        }
    }
}

void gui::TextureSelector::render(sf::RenderTarget& target)
{
    if (!hidden)
    {
        target.draw(bounds);
        target.draw(sheet);

        if (active)
            target.draw(selector);
    }

    hide_btn->render(target);
}

// PROGRESSBAR ============================================================================= PROGRESSBAR

gui::ProgressBar::ProgressBar(float _x, float _y, float _width, float _height, int max_value,
                              sf::Color inner_color, unsigned character_size,
                              sf::VideoMode& vm, sf::Font* font)
{
    float width = gui::p2pX(_width, vm);
    float height = gui::p2pY(_height, vm);
    float x = gui::p2pX(_x, vm);
    float y = gui::p2pY(_y, vm);

    maxWidth = width;
    maxValue = max_value;

    back.setSize(sf::Vector2f(width, height));
    back.setFillColor(sf::Color(50, 50, 50, 200));
    back.setPosition(x, y);

    inner.setSize(sf::Vector2f(width, height));
    inner.setFillColor(inner_color);
    inner.setPosition(back.getPosition());

    if (font)
    {
        text.setFont(*font);
        text.setCharacterSize(gui::calcCharSize(vm, character_size));
        text.setPosition(
                inner.getPosition().x + gui::p2pX(0.53f, vm),
                inner.getPosition().y + gui::p2pY(0.5f, vm)
        );
    }
}

gui::ProgressBar::~ProgressBar() = default;

//Functions
void gui::ProgressBar::update(const int current_value)
{
    float percent = static_cast<float>(current_value) / static_cast<float>(maxValue);

    inner.setSize(
            sf::Vector2f(
                    static_cast<float>(std::floor(maxWidth * percent)),
                    inner.getSize().y
            )
    );

    barString = std::to_string(current_value) + " / " + std::to_string(maxValue);
    text.setString(barString);
}

void gui::ProgressBar::render(sf::RenderTarget & target)
{
    target.draw(back);
    target.draw(inner);
    target.draw(text);
}