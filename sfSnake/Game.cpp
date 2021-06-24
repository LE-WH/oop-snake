#include <SFML/Graphics.hpp>

#include <memory>

#include "MenuScreen.h"
#include "Game.h"
#include "SnakeNode.h"

using namespace sfSnake;

const sf::Time Game::TimePerFrame = sf::seconds(1.f / 10.f);
sf::RectangleShape Game::cover;
sf::RectangleShape Game::background;
BGGrid Game::grid;

screenFlag Game::screenFlag_ = menu;

static 	sf::Vector2<unsigned int> size;

std::shared_ptr<Screen> Game::Screen = std::make_shared<MenuScreen>();

Game::Game()
: window_(sf::VideoMode(Game::Width, Game::Height), "sfSnake")
{
	bgMusic_.openFromFile("Music/bg_music.wav");
	bgMusic_.setLoop(true);
	bgMusic_.play();
}

void Game::handleInput()
{
	sf::Event event;

	while (window_.pollEvent(event))
	{
		if (event.type == sf::Event::Resized)
		{
			window_.setSize(size);
		}
		if (event.type == sf::Event::Closed)
			window_.close();
	}

	Game::Screen->handleInput(window_);
}

void Game::update(sf::Time delta)
{
	Game::Screen->update(delta);
}

void Game::render()
{
	window_.clear();
	Game::Screen->render(window_);
	window_.display();
}

static void initialSize()
{
	size.x=Game::Width;
	size.y=Game::Height;
}

static void initialBackground()
{
	Game::background.setPosition(0,0);
	Game::background.setSize(sf::Vector2f(Game::Width,Game::Height));
	Game::background.setFillColor(sf::Color::Black);
}

static void initialGrid()
{ 
	grid_white.loadFromFile("Texture/grid_white.png");
	grid_brown.loadFromFile("Texture/grid_brown.png");
	grid_black.loadFromFile("Texture/grid_black.png");
	Game::grid.grid_.setTexture(grid_black);
	//Game::grid.grid_.setColor(sf::Color::Transparent);
	Game::grid.gridflag = 1;
	Game::grid.grid_.setPosition(0,0);
}

static void initialCover()
{
	Game::cover.setPosition(0,0);
	Game::cover.setSize(sf::Vector2f(Game::Width,Game::Height));
	Game::cover.setFillColor(sf::Color(0,0,0,50));
}
void Game::changeGrid()
{
    switch (Game::grid.gridflag)
    {
    case 1:
        break;
    case 2:
        Game::grid.grid_.setTexture(grid_white);
        break;
    case 3:
        Game::grid.grid_.setTexture(grid_brown);
        break;
    case 4:
        Game::grid.grid_.setTexture(grid_black);
        break;
    default:
        break;
    }
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	initialTexture();
	initialSize();
	initialBackground();
	initialGrid();
	initialCover();

	while (window_.isOpen())
	{
		sf::Time delta = clock.restart();
		timeSinceLastUpdate += delta;

		while (timeSinceLastUpdate > Game::TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;
			handleInput();
			update(TimePerFrame);
		}

		render();
	}
}

