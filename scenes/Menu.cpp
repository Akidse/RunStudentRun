#include "Menu.hpp"
#include <iostream>

void MenuScene::handleStartButtonEvents(int e)
{
	std::cout << "handled" << std::endl;
}
void MenuScene::handleSettingsButtonEvents(int e)
{

}
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
	startButton->registerEventHandler<MenuScene>((int)Button::Event::HOVER, this, &MenuScene::handleStartButtonEvents);
	//startButton->registerEventHandler<MenuScene>(Button::Event::PRESSED, this, &MenuScene::handleStartButtonEvents);
	//startButton->registerEventHandler<MenuScene>(Button::Event::UNPRESSED, this, &MenuScene::handleStartButtonEvents);
	//startButton->registerEventHandler<MenuScene>(Button::Event::UNHOVER, this, &MenuScene::handleStartButtonEvents);

	settingsButton = new Button("Settings", *resourcesManager->menuButtonTexture, sf::Vector2f(300, 75));
	settingsButton->setTextColor(sf::Color::White);
	settingsButton->setTextFont(*resourcesManager->menuFont);
	settingsButton->setTextSize(30);
	settingsButton->setPosition(sf::Vector2f(175, 250));
	//settingsButton->registerEventHandler<MenuScene>(Button::Event::HOVER, this, &MenuScene::handleSettingsButtonEvents);
	//settingsButton->registerEventHandler<MenuScene>(Button::Event::PRESSED, this, &MenuScene::handleSettingsButtonEvents);
	//settingsButton->registerEventHandler<MenuScene>(Button::Event::UNPRESSED, this, &MenuScene::handleSettingsButtonEvents);
	//settingsButton->registerEventHandler<MenuScene>(Button::Event::UNHOVER, this, &MenuScene::handleSettingsButtonEvents);
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
	startButton->update();
	settingsButton->update();
}

void MenuScene::draw(sf::RenderWindow *window)
{
	window->draw(menuBackgroundSprite);
	window->draw(*startButton);
	window->draw(*settingsButton);
}