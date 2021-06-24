#include <SFML/Graphics.hpp>
#include <cmath>

#include "SnakeNode.h"

using namespace sfSnake;

const float SnakeNode::Width = 15.f;
const float SnakeNode::Height = 15.f;

static sf::Texture headshape;
static sf::Texture nodeshape;

extern void sfSnake::initialTexture()
{
	headshape.loadFromFile("Texture/head.png");
	nodeshape.loadFromFile("Texture/node.png");
}

SnakeNode::SnakeNode(int flag , sf::Vector2f position)
: position_(position)
{
	shape_.setPosition(position_);
	if(flag==0)
	{
		shape_.setTexture(headshape);
	}
	else if(flag== 1)
		shape_.setTexture(nodeshape);
	shape_.setScale(1.0f,1.0f);
	
	sf::Vector2f origin = shape_.getOrigin();
	shape_.setOrigin(origin.x+7.5 , origin.y+7.5);
}

void SnakeNode::setPosition(sf::Vector2f position)
{
	position_ = position;
	shape_.setPosition(position_);
}

void SnakeNode::setPosition(float x, float y)
{
	position_.x = x;
	position_.y = y;
	shape_.setPosition(position_);
}

void SnakeNode::setRotation(float x, float y)
{
	float angle;
	if(x>0)
		angle=-acos(y)*180/3.1416;
	else
		angle=acos(y)*180/3.1416;
	shape_.setRotation(angle+180);
}

void SnakeNode::imitateRotation(SnakeNode &source)
{
	float angle=source.shape_.getRotation();
	shape_.setRotation(angle);
}
void SnakeNode::move(float xOffset, float yOffset)
{
	position_.x += xOffset;
	position_.y += yOffset;
	shape_.setPosition(position_);
}

sf::FloatRect SnakeNode::getBounds() const
{
	return shape_.getGlobalBounds();
}

sf::Vector2f SnakeNode::getPosition() const
{
	return position_;
}

void SnakeNode::render(sf::RenderWindow& window)
{
	window.draw(shape_);
}