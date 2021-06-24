#ifndef SNAKE_NODE_H
#define SNAKE_NODE_H

#include <SFML/Graphics.hpp>

namespace sfSnake
{
extern void initialTexture();

class SnakeNode
{
public:
	SnakeNode(int flag, sf::Vector2f position = sf::Vector2f(0, 0));

	void setPosition(sf::Vector2f position);
	void setPosition(float x, float y);
	void setRotation(float x, float y);
	void imitateRotation(SnakeNode &source);

	void move(float xOffset, float yOffset);

	void render(sf::RenderWindow& window);

	sf::Vector2f getPosition() const;
	sf::FloatRect getBounds() const;

	static const float Width;
	static const float Height;

private:
	sf::Sprite shape_;
	sf::Vector2f position_;
};
}

#endif