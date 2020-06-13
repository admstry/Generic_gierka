//
// Created by Adam on 13.06.2020.
//
#include "pch.h"
#include "SettingsState.h"

void SettingsState::initVariables()
{
    modes = sf::VideoMode::getFullscreenModes();
}

void SettingsState::initFonts()
{
    if (!font.loadFromFile("../Fonts/rainyhearts.ttf"))
    {
        throw std::exception();
    }
}

void SettingsState::initKeybinds()
{
    std::ifstream stream("../Config/mainmenustate_keybinds.ini");

    if (stream.is_open())
    {
        std::string key;
        std::string key2;

        while (stream >> key >> key2)
        {
            keybinds[key] = supportedKeys->at(key2);
        }
    }

    stream.close();
}

void SettingsState::initGui()
{
    const sf::VideoMode& vm = stateData->gfxSettings->resolution;

    //Background
    background.setSize(
            sf::Vector2f
                    (
                            static_cast<float>(vm.width),
                            static_cast<float>(vm.height)
                    )
    );

    if (!backgroundTexture.loadFromFile("../Resources/Backgrounds/bg.png"))
    {
        throw std::exception();
    }

    background.setTexture(&backgroundTexture);

    //Buttons
    buttons["BACK"] = new gui::Button(
            gui::p2pX(72.f, vm), gui::p2pY(81.5f, vm),
            gui::p2pX(13.f, vm), gui::p2pY(6.f, vm),
            &font, "Back", gui::calcCharSize(vm),
            sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
            sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

    buttons["APPLY"] = new gui::Button(
            gui::p2pX(60.f, vm), gui::p2pY(81.5f, vm),
            gui::p2pX(13.f, vm), gui::p2pY(6.f, vm),
            &font, "Apply", gui::calcCharSize(vm),
            sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
            sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

    //Modes
    std::vector<std::string> modes_str;
    for (auto &i : modes)
    {
        modes_str.push_back(std::to_string(i.width) + 'x' + std::to_string(i.height));
    }

    //Drop down lists
    dropDownLists["RESOLUTION"] = new gui::DropDownList(
            gui::p2pX(42.f, vm), gui::p2pY(42.f, vm),
            gui::p2pX(10.4f, vm), gui::p2pY(4.5f, vm),
            font, modes_str.data(), modes_str.size()
    );

    //Text init
    optionsText.setFont(font);
    optionsText.setPosition(sf::Vector2f(gui::p2pX(5.2f, vm), gui::p2pY(41.7f, vm)));
    optionsText.setCharacterSize(gui::calcCharSize(vm, 70));
    optionsText.setFillColor(sf::Color(255, 255, 255, 200));

    optionsText.setString(
            "Resolution \n\n"
    );
}

void SettingsState::resetGui()
{
    /*
     * Clears the GUI elements and re-initialises the GUI.
     *
     * @return void
     */

    auto it = buttons.begin();
    for (it = buttons.begin(); it != buttons.end(); ++it)
    {
        delete it->second;
    }
    buttons.clear();

    auto it2 = dropDownLists.begin();
    for (it2 = dropDownLists.begin(); it2 != dropDownLists.end(); ++it2)
    {
        delete it2->second;
    }
    dropDownLists.clear();

    initGui();
}

SettingsState::SettingsState(StateData* state_data)
        : State(state_data)
{
    initVariables();
    initFonts();
    initKeybinds();
    initGui();
}

SettingsState::~SettingsState()
{
    auto it = buttons.begin();
    for (it = buttons.begin(); it != buttons.end(); ++it)
    {
        delete it->second;
    }

    auto it2 = dropDownLists.begin();
    for (it2 = dropDownLists.begin(); it2 != dropDownLists.end(); ++it2)
    {
        delete it2->second;
    }
}

//Accessors

//Functions
void SettingsState::updateInput(const float & dt)
{

}

void SettingsState::updateGui(const float & dt)
{
    /*Updates all the gui elements in the state and handle their functionlaity.*/
    //Buttons
    for (auto &it : buttons)
    {
        it.second->update(mousePosWindow);
    }

    //Button functionality
    //Quit the game
    if (buttons["BACK"]->isPressed())
    {
        endState();
    }

    //Apply selected settings
    if (buttons["APPLY"]->isPressed())
    {
        //TEST REMOVE LATER
        stateData->gfxSettings->resolution = modes[dropDownLists["RESOLUTION"]->getActiveElementId()];

        window->create(stateData->gfxSettings->resolution, stateData->gfxSettings->title, sf::Style::Default);

        resetGui();
    }

    //Dropdown lists
    for (auto &it : dropDownLists)
    {
        it.second->update(mousePosWindow, dt);
    }

    //Dropdown lists functionality
}

void SettingsState::update(const float& dt)
{
    updateMousePositions(nullptr);
    updateInput(dt);

    updateGui(dt);
}

void SettingsState::renderGui(sf::RenderTarget& target)
{
    for (auto &it : buttons)
    {
        it.second->render(target);
    }

    for (auto &it : dropDownLists)
    {
        it.second->render(target);
    }
}

void SettingsState::render(sf::RenderTarget* target)
{
    if (!target)
        target = window;

    target->draw(background);

    renderGui(*target);

    target->draw(optionsText);

    // TODO DEBUG ONLY REMOVE LATER
    sf::Text mouseText;
    mouseText.setPosition(mousePosView.x, mousePosView.y - 50);
    mouseText.setFont(font);
    mouseText.setCharacterSize(12);
    std::stringstream ss;
    ss << mousePosView.x << " " << mousePosView.y;
    mouseText.setString(ss.str());
    target->draw(mouseText);
}