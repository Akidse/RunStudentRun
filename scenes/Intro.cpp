#include "Intro.hpp"
#include <iostream>
IntroScene::IntroScene()
{
	resourcesManager = ResourcesManager::getInstance();

	logoSprite.setTexture(*resourcesManager->logoTexture);
	logoSprite.scale(sf::Vector2f(0.5f, 0.5f));
	logoSprite.setPosition(SceneManager::getInstance()->getWindow()->getSize().x / 2 - logoSprite.getGlobalBounds().width / 2,
		SceneManager::getInstance()->getWindow()->getSize().y / 2 - logoSprite.getGlobalBounds().height / 2);
	
	resourcesManager->logoShader->setUniform("texture", sf::Shader::CurrentTexture);
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
	resourcesManager->logoShader->setUniform("duration", INTRO_SCENE_DURATION);
	resourcesManager->logoShader->setUniform("currentTime", currentDuration.asSeconds());
	if (currentDuration.asSeconds() >= INTRO_SCENE_DURATION)SceneManager::getInstance()->setScene(SceneType::MENU);
}

void IntroScene::draw(sf::RenderWindow *window)
{
	window->draw(logoSprite, resourcesManager->logoShader);
}

IntroScene::~IntroScene()
{
	delete resourcesManager;
}