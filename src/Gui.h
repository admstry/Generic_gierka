//
// Created by Adam on 14.06.2020.
//

#ifndef GENERIC_GIERKA_GUI_H
#define GENERIC_GIERKA_GUI_H

enum button_states{BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE};

namespace gui {
    float p2pX(float perc, const sf::VideoMode& vm);
    float p2pY(float perc, const sf::VideoMode& vm);
    unsigned calcCharSize(const sf::VideoMode& vm, unsigned modifier = 60);

    class Button
    {
    private:
        short unsigned buttonState;
        short unsigned id;

        sf::RectangleShape shape;
        sf::Font* font;
        sf::Text text;

        sf::Color textIdleColor;
        sf::Color textHoverColor;
        sf::Color textActiveColor;

        sf::Color idleColor;
        sf::Color hoverColor;
        sf::Color activeColor;

        sf::Color outlineIdleColor;
        sf::Color outlineHoverColor;
        sf::Color outlineActiveColor;

    public:
        Button(float x, float y, float width, float height,
               sf::Font* font, const std::string& text, unsigned character_size,
               sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
               sf::Color idle_color, sf::Color hover_color, sf::Color active_color,
               sf::Color outline_idle_color = sf::Color::Transparent, sf::Color outline_hover_color = sf::Color::Transparent, sf::Color outline_active_color = sf::Color::Transparent,
               short unsigned id = 0);
        ~Button();

        // functions
        bool isPressed() const;
        std::string getText() const;
        const short unsigned& getId() const;

        void setText(const std::string& text);
        void setId(short unsigned id_);

        void update(const sf::Vector2i& mousePosWindow);
        void render(sf::RenderTarget& target);
    };

    class DropDownList
    {
    private:
        // variables
        float keyTime;
        float keyTimeMax;

        sf::Font& font;
        gui::Button* activeElement;
        std::vector<gui::Button*> list;
        bool showList;

    public:
        DropDownList(float x, float y, float width, float height,
                     sf::Font& font, std::string list[],
                     unsigned nrOfElements, unsigned default_index = 0);
        ~DropDownList();
        // functions
        [[nodiscard]] const unsigned short& getActiveElementId() const;

        bool getKeytime();
        void updateKeytime(const float& tm);
        void update(const sf::Vector2i& mousePosWindow, const float& tm);
        void render(sf::RenderTarget& target);
    };
}


#endif //GENERIC_GIERKA_GUI_H
