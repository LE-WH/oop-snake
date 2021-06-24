#include <SFML/Graphics.hpp>

#include <random>
#include <memory>

#include "GameScreen.h"
#include "GameOverScreen.h"
#include "Game.h"

using namespace sfSnake;

GameScreen::GameScreen() : snake_()
{

}

void GameScreen::handleInput(sf::RenderWindow& window)
{
	snake_.handleInput(window);
}

void GameScreen::update(sf::Time delta)
{
	while (fruit_.size() <= 6)
	{
		static std::default_random_engine engine(time(NULL));
		static std::uniform_int_distribution<int> randomDistribution(1,100);
		int dice=randomDistribution(engine);
		if(dice<=12)
			generateFruit(sf::Color::Black);
		else if(dice<=25)
			generateFruit(sf::Color(96,57,18,255));	//it's brown//
		else if(dice<=50)
			generateFruit(sf::Color::Red);
		else if(dice<=75)
			generateFruit(sf::Color::Blue);
		else 
			generateFruit(sf::Color::Green);
	}

	snake_.update(delta);
	snake_.checkFruitCollisions(fruit_);

	if (snake_.hitSelf())
		Game::Screen = std::make_shared<GameOverScreen>(snake_.getSize());
}

void GameScreen::render(sf::RenderWindow& window)
{
	window.draw(Game::background);
	if(Game::grid.gridflag != 1)
		window.draw(Game::grid.grid_);
	snake_.render(window);
	for (auto fruit : fruit_)
		fruit.render(window);
	window.draw(Game::cover);
}

void GameScreen::generateFruit(sf::Color color)
{
	static std::default_random_engine engine(time(NULL));
	static std::uniform_int_distribution<int> xDistribution(0, Game::Width - SnakeNode::Width);
	static std::uniform_int_distribution<int> yDistribution(0, Game::Height - SnakeNode::Height);

	fruit_.push_back(Fruit( color, sf::Vector2f(xDistribution(engine), yDistribution(engine))));
}
