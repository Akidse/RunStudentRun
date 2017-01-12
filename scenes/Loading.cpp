#include "Loading.hpp"
void LoadingScene::handleInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		SceneManager::getInstance()->setScene(SceneType::INTRO);
	}
}

void LoadingScene::update()
{
	this->handleInput();
	this->circle.move(0.1f, 0.1f);
}

void LoadingScene::draw(sf::RenderWindow *window)
{
	window->draw(circle);
}

void LoadingScene::loadResourses()
{
	this->circle = sf::CircleShape(150);
	this->circle.setFillColor(sf::Color(50, 150, 2));
}