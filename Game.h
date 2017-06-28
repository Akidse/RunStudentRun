#include "SFMEngine/Engine.h"

class Game : public Engine
{
public:
	Game(RenderWindow& pWindow);
	void draw();
};
Game::Game(RenderWindow& pWindow) :Engine(pWindow)
{
}
void Game::draw()
{
	this->window.clear();
	this->window.draw(this->circle);
	this->window.display();
}