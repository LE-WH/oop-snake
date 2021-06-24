#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <vector>
#include <memory>

#include "Screen.h"

namespace sfSnake
{

static sf::Texture grid_white;
static sf::Texture grid_brown;
static sf::Texture grid_black;

class BGGrid
{
public: 
	sf::Sprite grid_;
	int gridflag;// 1 for transparent; 2 for black; 3 for white; 4 for brown.
};



enum screenFlag
{
	menu, game
};

class Game
{
public:
	Game();

	void run();

	void handleInput();
	void update(sf::Time delta);
	void render();
	
	static void changeGrid();

	static sf::RectangleShape background; //color : black, white, brown
	static BGGrid grid;	//transparent, black, white, brown(138,54,15,120)
	static screenFlag screenFlag_;

	static sf::RectangleShape cover;

	static const int Width = 1280;
	static const int Height = 720;

	static std::shared_ptr<Screen> Screen;

private:
	sf::RenderWindow window_;
	sf::Music bgMusic_;
	


	static const sf::Time TimePerFrame;
};


}
#endif