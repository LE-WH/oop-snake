#include <SFML/Graphics.hpp>

#include <memory>
#include <cmath>

#include "Snake.h"
#include "Game.h"
#include "Fruit.h"
#include "SnakeNode.h"
#include "GameOverScreen.h"
#include "GameScreen.h"

using namespace sfSnake;

const int Snake::InitialSize = 5;

static sf::Vector2f getmouse(sf::RenderWindow& window)
{
	sf::Vector2i mouseposition = sf::Mouse::getPosition(window);
	sf::Vector2f mousepositionf(mouseposition.x,mouseposition.y);

	return mousepositionf;
}

static float distance(sf::Vector2f a, sf::Vector2f b)
{
	return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}

Snake::Snake() : hitSelf_(false) , direction_(0.0f,-1.0f) 
{
	initNodes();

	pickupBuffer_.loadFromFile("Sounds/ding.wav");
	pickupSound_.setBuffer(pickupBuffer_);
	pickupSound_.setVolume(30);

	dieBuffer_.loadFromFile("Sounds/die.wav");
	dieSound_.setBuffer(dieBuffer_);
	dieSound_.setVolume(50);
}

void Snake::initNodes()
{
	nodes_.push_back(SnakeNode(0, sf::Vector2f(
			Game::Width / 2 - SnakeNode::Width / 2,
			Game::Height / 2 - (SnakeNode::Height / 2) )));
	for (int i = 1; i < Snake::InitialSize; ++i)
	{
		nodes_.push_back(SnakeNode(1, sf::Vector2f(
			Game::Width / 2 - SnakeNode::Width / 2,
			Game::Height / 2 - (SnakeNode::Height / 2) + (SnakeNode::Height * i))));
	}
}


void Snake::handleInput(sf::RenderWindow& window1)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		sf::Vector2f direction = getmouse(window1) - nodes_[0].getPosition();
		float len = sqrt(direction.x * direction.x + direction.y * direction.y);
		direction.x = direction.x / len;
		direction.y = direction.y / len;

		//control the turning angle to avoid unexpected suicide 
		double angle = acos(direction.x * direction_.x + direction.y * direction_.y);
		if(angle< 3.1415 * 135 / 180)
		direction_ = direction;
	}

	//std::cout<<direction_.x<<" "<<direction_.y<<std::endl;
	//sf::Event event;
	// while (window1.pollEvent(event))
	// {
	// 	switch (event.type)
	// 	{
	// 		case (sf::Event::MouseButtonPressed):
	// 			if(event.mouseButton.button == sf::Mouse::Left)
	// 			{
	// 			sf::Vector2f direction = getmouse(window1) - nodes_[0].getPosition();
	// 			float len = sqrt(direction.x * direction.x + direction.y * direction.y);
	// 			direction.x = 10*direction.x / len;
	// 			direction.y = 10*direction.y / len;
	// 			direction_ = direction;
	// 			}
	// 	}
	// }
}

void Snake::update(sf::Time delta)
{
	move();
	checkEdgeCollisions();
	checkSelfCollisions();
}

void Snake::checkFruitCollisions(std::vector<Fruit>& fruits)
{
	decltype(fruits.begin()) toRemove = fruits.end();

	for (auto it = fruits.begin(); it != fruits.end(); ++it)
	{
		if (it->getBounds().intersects(nodes_[0].getBounds()))
			toRemove = it;
	}
	if (toRemove != fruits.end())
	{
		pickupSound_.play();
		if(toRemove->getFruitColor()==sf::Color::Red)
		{
			grow();grow();grow();
		}
		else if(toRemove->getFruitColor()==sf::Color::Blue)
		{
			grow();grow();
		}
		else if(toRemove->getFruitColor()==sf::Color::Green)
		grow();
		fruits.erase(toRemove);
	}
}

void Snake::grow()
{
	nodes_.push_back(SnakeNode(1, sf::Vector2f(nodes_[nodes_.size() - 1].getPosition().x,
		nodes_[nodes_.size() - 1].getPosition().y)));

}

bool Snake::hitSelf() const
{
	return hitSelf_;
}

unsigned Snake::getSize() const
{
	return nodes_.size();
}


void Snake::checkSelfCollisions()
{
	SnakeNode& headNode = nodes_[0];

	for (decltype(nodes_.size()) i = 1; i < nodes_.size()-1; ++i)
	{
		if (distance(headNode.getPosition(),nodes_[i].getPosition())<7.5)
		{
			dieSound_.play();
			sf::sleep(sf::seconds(dieBuffer_.getDuration().asSeconds()));
			hitSelf_ = true;
		}
	}
}

void Snake::checkEdgeCollisions()
{
	SnakeNode& headNode = nodes_[0];

	if (headNode.getPosition().x <= 0)
		headNode.setPosition(Game::Width, headNode.getPosition().y);
	else if (headNode.getPosition().x >= Game::Width)
		headNode.setPosition(0, headNode.getPosition().y);
	else if (headNode.getPosition().y <= 0)
		headNode.setPosition(headNode.getPosition().x, Game::Height);
	else if (headNode.getPosition().y >= Game::Height)
		headNode.setPosition(headNode.getPosition().x, 0);
}

void Snake::move()
{
	for (decltype(nodes_.size()) i = nodes_.size() - 1; i > 0; --i)
	{
		nodes_[i].setPosition(nodes_.at(i - 1).getPosition());
		nodes_[i].imitateRotation(nodes_[i-1]);
	}

	nodes_[0].move(10*direction_.x , 10*direction_.y);
	nodes_[0].setRotation(direction_.x , direction_.y);
}

void Snake::render(sf::RenderWindow& window)
{
	for (int i=nodes_.size()-1; i>=0; i--)
		nodes_[i].render(window);
}