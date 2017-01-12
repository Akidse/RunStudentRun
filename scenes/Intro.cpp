#include "Intro.hpp"

IntroScene::IntroScene()
{
	resourcesManager = ResourcesManager::getInstance();
	this->circle = sf::CircleShape(150);
	this->circle.setFillColor(sf::Color(304, 37, 74));

	logoSprite.setTexture(*resourcesManager->logoTexture);
	logoSprite.scale(sf::Vector2f(0.5f, 0.5f));
	logoSprite.setPosition(SceneManager::getInstance()->getWindow()->getSize().x / 2 - logoSprite.getGlobalBounds().width / 2,
		SceneManager::getInstance()->getWindow()->getSize().y / 2 - logoSprite.getGlobalBounds().height / 2);
}

void IntroScene::handleInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		SceneManager::getInstance()->setScene(SceneType::MENU);
	}
}

void IntroScene::update()
{
	this->handleInput();
	this->circle.move(0.1f, 0.1f);
}

void IntroScene::draw(sf::RenderWindow *window)
{
	window->draw(logoSprite);
}