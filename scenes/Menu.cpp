#include "Menu.hpp"

MenuScene::MenuScene()
{
	resourcesManager = ResourcesManager::getInstance();

	menuBackgroundSprite.setTexture(*resourcesManager->menuBackgroundTexture);
	menuBackgroundSprite.setPosition(0,0);
	resourcesManager->menuMusic->setLoop(true);
	resourcesManager->menuMusic->play();
	
	startButton = new Button("Start", *resourcesManager->menuButtonTexture, sf::Vector2f(300, 75));
	startButton->setTextColor(sf::Color::White);
	startButton->setTextFont(*resourcesManager->menuFont);
	startButton->setTextSize(30);
	startButton->setPosition(sf::Vector2f(175, 150));

	settingsButton = new Button("Settings", *resourcesManager->menuButtonTexture, sf::Vector2f(300, 75));
	settingsButton->setTextColor(sf::Color::White);
	settingsButton->setTextFont(*resourcesManager->menuFont);
	settingsButton->setTextSize(30);
	settingsButton->setPosition(sf::Vector2f(175, 250));
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
}

void MenuScene::draw(sf::RenderWindow *window)
{
	window->draw(menuBackgroundSprite);
	window->draw(*startButton);
	window->draw(*settingsButton);
}