#include "Menu.hpp"
#include <iostream>
void MenuScene::handleStartButtonEvents(int event)
{
	if (event == Button::Event::PRESSED)startButton->setActive();
	if (event == Button::Event::PRESSED)goToSubMenu();
}

void MenuScene::handleSettingsButtonEvents(int event)
{
	if (event == Button::Event::PRESSED)
	{
		startButton->setInActive();
		settingsButton->setActive();
	}
}

void MenuScene::handleAboutButtonEvents(int event)
{
}

void MenuScene::handleExitButtonEvents(int event)
{
	SceneManager::getInstance()->getWindow()->close();
}

void MenuScene::handleMusicSwitcherEvents(int event)
{
	if (event == GuiSwitcher::Event::DECREASE_VALUE || event == GuiSwitcher::Event::INCREASE_VALUE)
	{
		ResourcesManager::getInstance()->setGlobalMusicVolume(musicSwitcher.getCurrentValue() * 10);
		configManager->set("music", std::to_string((int)musicSwitcher.getCurrentValue()));
	}	
}

void MenuScene::handleSoundSwitcherEvents(int event)
{
	if (event == GuiSwitcher::Event::DECREASE_VALUE || event == GuiSwitcher::Event::INCREASE_VALUE)
	{
		ResourcesManager::getInstance()->setGlobalSoundVolume(soundSwitcher.getCurrentValue() * 10);
		configManager->set("sound", std::to_string((int)soundSwitcher.getCurrentValue()));
	}
}

void MenuScene::handleLangButtonEnEvents(int event)
{
	if (configManager->get("locale") != "en")
	{
		langButtonEn->setActive();
		langButtonRu->setInActive();
		langButtonUk->setInActive();

		configManager->set("locale", "en");
		i18nManager->loadLocale("en");
		isReadyForRefresh = true;
	}
}
void MenuScene::handleLangButtonUkEvents(int event)
{
	if (configManager->get("locale") != "uk")
	{
		langButtonUk->setActive();
		langButtonRu->setInActive();
		langButtonEn->setInActive();

		configManager->set("locale", "uk");
		i18nManager->loadLocale("uk");
		isReadyForRefresh = true;
	}
}
void MenuScene::handleLangButtonRuEvents(int event)
{
	if (configManager->get("locale") != "ru")
	{
		langButtonRu->setActive();
		langButtonUk->setInActive();
		langButtonEn->setInActive();

		configManager->set("locale", "ru");
		i18nManager->loadLocale("ru");
		isReadyForRefresh = true;
	}
}

MenuScene::MenuScene()
	:
	soundSwitcher(*ResourcesManager::getInstance()->menuLeftArrowTexture, *ResourcesManager::getInstance()->menuRightArrowTexture, *ResourcesManager::getInstance()->menuFont, sf::Vector2f(900,257)),
	musicSwitcher(*ResourcesManager::getInstance()->menuLeftArrowTexture, *ResourcesManager::getInstance()->menuRightArrowTexture, *ResourcesManager::getInstance()->menuFont, sf::Vector2f(900, 317)),
	isReadyForRefresh(false)
{
	view = new sf::View(sf::FloatRect(0, 0, 1200, 900));
	menuLayer.setPosition(130, 260);
	settingsLayer.setPosition(600, 200);
	langSwitcherLayer.setPosition(700, 150);
	configManager = ConfigManager::getInstance();
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

	langButtonEn = new Button(*resourcesManager->menuLangButtonEnTexture, sf::Vector2f(100, 60), sf::Vector2f(821, 180));
	langButtonEn->registerEventHandler<MenuScene>(Button::Event::PRESSED, this, &MenuScene::handleLangButtonEnEvents);

	langButtonUk = new Button(*resourcesManager->menuLangButtonUkTexture, sf::Vector2f(100, 60), sf::Vector2f(721, 180));
	langButtonUk->registerEventHandler<MenuScene>(Button::Event::PRESSED, this, &MenuScene::handleLangButtonUkEvents);

	langButtonRu = new Button(*resourcesManager->menuLangButtonRuTexture, sf::Vector2f(100, 60), sf::Vector2f(921, 180));
	langButtonRu->registerEventHandler<MenuScene>(Button::Event::PRESSED, this, &MenuScene::handleLangButtonRuEvents);

	soundSwitcher.setSwitchableLimits(0, 10, 1);
	soundSwitcher.setCurrentValue(resourcesManager->getGlobalSoundVolume() / 10);
	soundSwitcher.registerEventHandler<MenuScene>(GuiSwitcher::Event::DECREASE_VALUE, this, &MenuScene::handleSoundSwitcherEvents);
	soundSwitcher.registerEventHandler<MenuScene>(GuiSwitcher::Event::INCREASE_VALUE, this, &MenuScene::handleSoundSwitcherEvents);

	musicSwitcher.setSwitchableLimits(0, 10, 1);
	musicSwitcher.setCurrentValue(resourcesManager->getGlobalMusicVolume()/10);
	std::cout << musicSwitcher.getCurrentValue() << std::endl;
	musicSwitcher.registerEventHandler<MenuScene>(GuiSwitcher::Event::DECREASE_VALUE, this, &MenuScene::handleMusicSwitcherEvents);
	musicSwitcher.registerEventHandler<MenuScene>(GuiSwitcher::Event::INCREASE_VALUE, this, &MenuScene::handleMusicSwitcherEvents);


	langSwitcherLabel = sf::Text(i18nManager->getText("Language:"), *resourcesManager->menuFont);
	soundSwitcherLabel = sf::Text(i18nManager->getText("Sound:"), *resourcesManager->menuFont);
	musicSwitcherLabel = sf::Text(i18nManager->getText("Music:"), *resourcesManager->menuFont);

	langSwitcherLabel.setPosition(680, 130);
	langSwitcherLabel.setFillColor(sf::Color(17, 23, 45));

	soundSwitcherLabel.setPosition(680, 260);
	soundSwitcherLabel.setFillColor(sf::Color(17, 23, 45));


	musicSwitcherLabel.setPosition(680, 320);
	musicSwitcherLabel.setFillColor(sf::Color(17, 23, 45));

	langSwitcherLayer.addEntity(langSwitcherLabel);
	langSwitcherLayer.addEntity(*langButtonUk);
	langSwitcherLayer.addEntity(*langButtonEn);
	langSwitcherLayer.addEntity(*langButtonRu);

	if (configManager->get("locale") == "en")langButtonEn->setActive();
	if (configManager->get("locale") == "ru")langButtonRu->setActive();
	if (configManager->get("locale") == "uk")langButtonUk->setActive();

	menuLayer.addEntity(*startButton);
	menuLayer.addEntity(*settingsButton);
	menuLayer.addEntity(*aboutButton);
	menuLayer.addEntity(*exitButton);

	settingsLayer.addEntity(langSwitcherLayer);
	settingsLayer.addEntity(musicSwitcherLabel);
	settingsLayer.addEntity(musicSwitcher);
	settingsLayer.addEntity(soundSwitcherLabel);
	settingsLayer.addEntity(soundSwitcher);
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
	soundSwitcher.update();
	musicSwitcher.update();
	langButtonEn->update();
	langButtonRu->update();
	langButtonUk->update();
	if (isReadyForRefresh)SceneManager::getInstance()->setScene(SceneType::INTRO);
}

void MenuScene::draw(sf::RenderWindow *window)
{
	SceneManager::getInstance()->getWindow()->setView(*view);
	window->draw(menuBackgroundSprite);
	window->draw(menuLayer);
	window->draw(settingsLayer);
}

MenuScene::~MenuScene()
{
	delete startButton;
	delete settingsButton;
	delete aboutButton;
	delete exitButton;
	delete langButtonEn;
	delete langButtonUk;
	delete langButtonRu;
	delete view;
	delete resourcesManager;
	delete i18nManager;
	delete configManager;
}