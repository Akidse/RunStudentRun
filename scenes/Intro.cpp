#include "Intro.hpp"
#include <iostream>
IntroScene::IntroScene()
{
	resourcesManager = ResourcesManager::getInstance();

	logoSprite.setTexture(*resourcesManager->logoTexture);
	logoSprite.scale(sf::Vector2f(0.5f, 0.5f));
	logoSprite.setPosition(SceneManager::getInstance()->getWindow()->getSize().x / 2 - logoSprite.getGlobalBounds().width / 2,
		SceneManager::getInstance()->getWindow()->getSize().y / 2 - logoSprite.getGlobalBounds().height / 2);
	
	(&resourcesManager->logoShader)->setUniform("texture", sf::Shader::CurrentTexture);
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
	currentDuration += sf::milliseconds(TimeManager::getInstance()->getTime(TimeType::ELAPSED_TIME));
	this->handleInput();
	if(currentDuration.asSeconds() < 5)(&resourcesManager->logoShader)->setUniform("percentTime", currentDuration.asSeconds() / 3);
	if (currentDuration.asSeconds() > 5)(&resourcesManager->logoShader)->setUniform("percentTime", (INTRO_SCENE_DURATION - currentDuration.asSeconds()) / 2);
	if (currentDuration.asSeconds() > INTRO_SCENE_DURATION)SceneManager::getInstance()->setScene(SceneType::MENU);
}

void IntroScene::draw(sf::RenderWindow *window)
{
	window->draw(logoSprite, &resourcesManager->logoShader);
}