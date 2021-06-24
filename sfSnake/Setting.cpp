#include "Setting.h"
#include "MenuScreen.h"

using namespace sfSnake;

settingScreen::settingScreen()
{
    font_.loadFromFile("Fonts/game_over.ttf");

    setting_.setFont(font_);
    setting_.setString("Setting");
    setting_.setFillColor(sf::Color::Green);
    setting_.setOutlineColor(sf::Color::White);
    setting_.setCharacterSize(48);

    hint_.setFont(font_);
    hint_.setString("Press [Z] to change the background\n"
                    "Press [X] to change the grid\n"
                    "Press [Enter] to confirm");
    hint_.setFillColor(sf::Color::Green);
    hint_.setOutlineColor(sf::Color::Green);

    bgSwitch_.setFont(font_);
    if (Game::background.getFillColor() == sf::Color::Black)
        bgSwitch_.setString("BackGround:       Black");
    else if (Game::background.getFillColor() == sf::Color::White)
        bgSwitch_.setString("BackGround:       White");
    else if (Game::background.getFillColor() == sf::Color(138, 54, 15, 255))
        bgSwitch_.setString("BackGround:       Brown");
    bgSwitch_.setFillColor(sf::Color::Green);
    bgSwitch_.setOutlineColor(sf::Color::Green);

    gridSwitch_.setFont(font_);
    if (Game::grid.gridflag ==1 )
        gridSwitch_.setString("Grid:              None");
    else if (Game::grid.gridflag == 2)
        gridSwitch_.setString("Grid:             Black");
    else if (Game::grid.gridflag == 3)
        gridSwitch_.setString("Grid:             White");
    else if (Game::grid.gridflag == 4)
        gridSwitch_.setString("Grid:             Brown");
    gridSwitch_.setFillColor(sf::Color::Green);
    gridSwitch_.setOutlineColor(sf::Color::Green);

    sf::FloatRect textBound1 = setting_.getLocalBounds();
    setting_.setOrigin(textBound1.left + textBound1.width / 2,
                       textBound1.top + textBound1.height / 2);
    setting_.setPosition(Game::Width / 2, Game::Height / 10);

    sf::FloatRect textBound2 = hint_.getLocalBounds();
    hint_.setOrigin(textBound2.left + textBound2.width / 2,
                    textBound2.top + textBound2.height / 2);
    hint_.setPosition(Game::Width / 2, Game::Height / 4);

    sf::FloatRect textBound3 = bgSwitch_.getLocalBounds();
    bgSwitch_.setOrigin(textBound3.left + textBound3.width / 2,
                        textBound3.top + textBound3.height / 2);
    bgSwitch_.setPosition(Game::Width / 2, Game::Height / 2);

    sf::FloatRect textBound4 = gridSwitch_.getLocalBounds();
    gridSwitch_.setOrigin(textBound4.left + textBound4.width / 2,
                          textBound4.top + textBound4.height / 2);
    gridSwitch_.setPosition(Game::Width / 2, Game::Height / 2 + textBound3.height *2);
}

void settingScreen::handleInput(sf::RenderWindow &window)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
        Game::Screen = std::make_shared<MenuScreen>();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
    {
        changeBG();
        sf::sleep(sf::seconds(0.2));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
    {
        Game::changeGrid();
        changeGridFlag();
        sf::sleep(sf::seconds(0.2));
    }
}

void settingScreen::changeGridFlag()
{
    switch (Game::grid.gridflag)
    {
    case 1:
        Game::grid.gridflag = 2;
        gridSwitch_.setString("Grid:             Black");
        break;
    case 2:
        Game::grid.gridflag = 3;
        gridSwitch_.setString("Grid:             White");
        break;
    case 3:
        Game::grid.gridflag = 4;
        gridSwitch_.setString("Grid:             Brown");
        break;
    case 4:
        gridSwitch_.setString("Grid:              None");
        Game::grid.gridflag = 1;
        break;
    default:
        break;
    }
}
void settingScreen::changeBG()
{
    if (Game::background.getFillColor() == sf::Color::Black)
    {
        Game::background.setFillColor(sf::Color::White);
        bgSwitch_.setString("BackGround:       White");
    }
    else if (Game::background.getFillColor() == sf::Color::White)
    {
        Game::background.setFillColor(sf::Color(138, 54, 15, 255));
        bgSwitch_.setString("BackGround:       Brown");
    }
    else if (Game::background.getFillColor() == sf::Color(138, 54, 15, 255))
    {
        Game::background.setFillColor(sf::Color::Black);
        bgSwitch_.setString("BackGround:       Black");
    }
}

void settingScreen::update(sf::Time delta)
{
}

void settingScreen::render(sf::RenderWindow &window)
{
    window.draw(Game::background);

    if(Game::grid.gridflag != 1)
    window.draw(Game::grid.grid_);

    window.draw(setting_);
    window.draw(hint_);
    window.draw(bgSwitch_);
    window.draw(gridSwitch_);
    window.draw(Game::cover);
}
