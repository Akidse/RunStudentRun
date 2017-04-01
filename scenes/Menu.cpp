#include "Menu.hpp"
#include <iostream>
void MenuScene::handleStartButtonEvents(int event)
{
	if (event == Button::Event::PRESSED)goToSubMenu();
}

void MenuScene::handleSettingsButtonEvents(int event)
{
}

void MenuScene::handleAboutButtonEvents(int event)
{
}

void MenuScene::handleExitButtonEvents(int event)
{
	SceneManager::getInstance()->getWindow()->close();
}

MenuScene::MenuScene()
{
	view = new sf::View(sf::FloatRect(0, 0, 1200, 900));
	menuLayer.setPosition(130, 260);
	resourcesManager = ResourcesManager::getInstance();
	i18nManager = I18nManager::getInstance();

	menuBackgroundSprite.setTexture(*resourcesManager->menuBackgroundTexture);
	menuBackgroundSprite.setPosition(0,0);
	resourcesManager->menuMusic->setLoop(true);
	resourcesManager->menuMusic->play();
	
	startButton = new Button(*resourcesManager->menuButtonTexture, sf::Vector2f(400, 80), sf::Vector2f(130, 260));
	startButton->setText(i18nManager->getText("Menu") , *resourcesManager->menuFont, 30, sf::Color::White);
	startButton->registerEventHandler<MenuScene>((int)Button::Event::HOVER, this, &MenuScene::handleStartButtonEvents);
	startButton->registerEventHandler<MenuScene>(Button::Event::PRESSED, this, &MenuScene::handleStartButtonEvents);
	startButton->registerEventHandler<MenuScene>(Button::Event::UNPRESSED, this, &MenuScene::handleStartButtonEvents);
	startButton->registerEventHandler<MenuScene>(Button::Event::UNHOVER, this, &MenuScene::handleStartButtonEvents);

	settingsButton = new Button(*resourcesManager->menuButtonTexture, sf::Vector2f(400, 80), sf::Vector2f(130, 360));
	settingsButton->setText(i18nManager->getText("Settings"), *resourcesManager->menuFont, 30, sf::Color::White);
	settingsButton->registerEventHandler<MenuScene>(Button::Event::HOVER, this, &MenuScene::handleSettingsButtonEvents);
	settingsButton->registerEventHandler<MenuScene>(Button::Event::PRESSED, this, &MenuScene::handleSettingsButtonEvents);
	settingsButton->registerEventHandler<MenuScene>(Button::Event::UNPRESSED, this, &MenuScene::handleSettingsButtonEvents);
	settingsButton->registerEventHandler<MenuScene>(Button::Event::UNHOVER, this, &MenuScene::handleSettingsButtonEvents);

	aboutButton = new Button(*resourcesManager->menuButtonTexture, sf::Vector2f(400, 80), sf::Vector2f(130, 460));
	aboutButton->setText(i18nManager->getText("About"), *resourcesManager->menuFont, 30, sf::Color::White);
	aboutButton->registerEventHandler<MenuScene>(Button::Event::HOVER, this, &MenuScene::handleAboutButtonEvents);
	aboutButton->registerEventHandler<MenuScene>(Button::Event::PRESSED, this, &MenuScene::handleAboutButtonEvents);
	aboutButton->registerEventHandler<MenuScene>(Button::Event::UNPRESSED, this, &MenuScene::handleAboutButtonEvents);
	aboutButton->registerEventHandler<MenuScene>(Button::Event::UNHOVER, this, &MenuScene::handleAboutButtonEvents);

	exitButton = new Button(*resourcesManager->menuButtonTexture, sf::Vector2f(400, 80), sf::Vector2f(130, 560));
	exitButton->setText(i18nManager->getText("Exit"), *resourcesManager->menuFont, 30, sf::Color::White);
	exitButton->registerEventHandler<MenuScene>(Button::Event::UNPRESSED, this, &MenuScene::handleExitButtonEvents);

	Button test(*resourcesManager->menuButtonTexture, sf::Vector2f(400, 80), sf::Vector2f(130, 260));
	test.setText(i18nManager->getText("Menu"), *resourcesManager->menuFont, 30, sf::Color::White);

	resourcesManager->setGlobalMusicVolume(0);
	menuLayer.addEntity(*startButton);
	menuLayer.addEntity(*settingsButton);
	menuLayer.addEntity(*aboutButton);
	menuLayer.addEntity(*exitButton);
}

void MenuScene::handleInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		SceneManager::getInstance()->setScene(SceneType::INTRO);
	}
}

void MenuScene::goToSubMenu()
{
}

void MenuScene::update()
{
	this->handleInput();
	startButton->update();
	settingsButton->update();
	aboutButton->update();
	exitButton->update();
}

void MenuScene::draw(sf::RenderWindow *window)
{
	SceneManager::getInstance()->getWindow()->setView(*view);
	window->draw(menuBackgroundSprite);
	window->draw(menuLayer);
}