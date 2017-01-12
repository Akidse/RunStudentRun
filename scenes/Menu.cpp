#include "Menu.hpp"

MenuScene::MenuScene()
{
	resourcesManager = ResourcesManager::getInstance();
	this->circle = sf::CircleShape(150);
	this->circle.setFillColor(sf::Color(122, 122, 122));
}

void MenuScene::handleInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		SceneManager::getInstance()->setScene(SceneType::INTRO);
	}
}

void MenuScene::update()
{
	this->handleInput();
	this->circle.move(0.1f, 0.1f);
}

void MenuScene::draw(sf::RenderWindow *window)
{
	window->draw(circle);
}