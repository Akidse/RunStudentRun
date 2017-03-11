#include "Menu.hpp"
#include <iostream>

void MenuScene::handleStartButtonEvents(int e)
{
	std::cout << "handled" << std::endl;
}
void MenuScene::handleSettingsButtonEvents(int e)
{
	std::cout << "handled 2" << std::endl;
}
MenuScene::MenuScene()
{
	resourcesManager = ResourcesManager::getInstance();

	menuBackgroundSprite.setTexture(*resourcesManager->menuBackgroundTexture);
	menuBackgroundSprite.setPosition(0,0);
	resourcesManager->menuMusic->setLoop(true);
	resourcesManager->menuMusic->play();
	
	startButton = new Button(*resourcesManager->menuButtonTexture, sf::Vector2f(300, 75), sf::Vector2f(175, 150));
	startButton->setText("Start", *resourcesManager->menuFont, 30, sf::Color::White);
	startButton->registerEventHandler<MenuScene>((int)Button::Event::HOVER, this, &MenuScene::handleStartButtonEvents);
	startButton->registerEventHandler<MenuScene>(Button::Event::PRESSED, this, &MenuScene::handleStartButtonEvents);
	startButton->registerEventHandler<MenuScene>(Button::Event::UNPRESSED, this, &MenuScene::handleStartButtonEvents);
	startButton->registerEventHandler<MenuScene>(Button::Event::UNHOVER, this, &MenuScene::handleStartButtonEvents);

	settingsButton = new Button(*resourcesManager->menuButtonTexture, sf::Vector2f(300, 75), sf::Vector2f(175, 250));
	settingsButton->setText("Settings", *resourcesManager->menuFont, 30, sf::Color::White);
	settingsButton->registerEventHandler<MenuScene>(Button::Event::HOVER, this, &MenuScene::handleSettingsButtonEvents);
	settingsButton->registerEventHandler<MenuScene>(Button::Event::PRESSED, this, &MenuScene::handleSettingsButtonEvents);
	settingsButton->registerEventHandler<MenuScene>(Button::Event::UNPRESSED, this, &MenuScene::handleSettingsButtonEvents);
	settingsButton->registerEventHandler<MenuScene>(Button::Event::UNHOVER, this, &MenuScene::handleSettingsButtonEvents);
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