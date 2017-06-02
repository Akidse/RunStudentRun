#include "Menu.hpp"

void MenuScene::handleLevelButton(std::string objectID, int event)
{
	if(objectID == "testLevelButton")std::cout << "UNPRESSED" << std::endl;
}
void MenuScene::handleStartButtonEvents(std::string objectID, int event)
{
	if (event == Button::Event::UNPRESSED)
	{
		startButton->setActive();
		levelButtonsLayer.setActive(true);
		settingsButton->setInActive();
		settingsLayer.setActive(false);
	}
}

void MenuScene::handleSettingsButtonEvents(std::string objectID, int event)
{
	if (event == Button::Event::UNPRESSED)
	{
		startButton->setInActive();
		levelButtonsLayer.setActive(false);
		settingsButton->setActive();
		settingsLayer.setActive(true);
	}
}

void MenuScene::handleAboutButtonEvents(std::string objectID, int event)
{
}

void MenuScene::handleExitButtonEvents(std::string objectID, int event)
{
	SceneManager::getInstance()->getWindow()->close();
}

void MenuScene::handleMusicSwitcherEvents(std::string objectID, int event)
{
	if (event == GuiSwitcher::Event::DECREASE_VALUE || event == GuiSwitcher::Event::INCREASE_VALUE)
	{
		ResourcesManager::getInstance()->setGlobalMusicVolume(musicSwitcher->getCurrentValue() * 10);
		configManager->set("music", std::to_string((int)musicSwitcher->getCurrentValue()));
	}	
}

void MenuScene::handleSoundSwitcherEvents(std::string objectID, int event)
{
	if (event == GuiSwitcher::Event::DECREASE_VALUE || event == GuiSwitcher::Event::INCREASE_VALUE)
	{
		ResourcesManager::getInstance()->setGlobalSoundVolume(soundSwitcher->getCurrentValue() * 10);
		configManager->set("sound", std::to_string((int)soundSwitcher->getCurrentValue()));
	}
}

void MenuScene::handleLangButtonEnEvents(std::string objectID, int event)
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
void MenuScene::handleLangButtonUkEvents(std::string objectID, int event)
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
void MenuScene::handleLangButtonRuEvents(std::string objectID, int event)
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
{
	view = new sf::View(sf::FloatRect(0, 0, 1200, 900));
	configManager = ConfigManager::getInstance();
	resourcesManager = ResourcesManager::getInstance();
	i18nManager = I18nManager::getInstance();

	menuBackgroundSprite.setTexture(*resourcesManager->menuBackgroundTexture);
	menuBackgroundSprite.setPosition(0,0);
	resourcesManager->menuMusic->setLoop(true);
	resourcesManager->menuMusic->play();

	generateMenuLayer();
	generateLevelsLayer();
	generateSettingsLayer();
}

void MenuScene::generateMenuLayer()
{
	menuLayer.setPosition(130, 260);

	startButton = new Button(*resourcesManager->menuButtonTexture, sf::Vector2f(400, 80), sf::Vector2f(130, 260));
	startButton->setText(i18nManager->getText("Play"), *resourcesManager->menuFont, 30, sf::Color::White);
	startButton->registerEventHandler<MenuScene>(Button::Event::UNPRESSED, this, &MenuScene::handleStartButtonEvents);

	settingsButton = new Button(*resourcesManager->menuButtonTexture, sf::Vector2f(400, 80), sf::Vector2f(130, 360));
	settingsButton->setText(i18nManager->getText("Settings"), *resourcesManager->menuFont, 30, sf::Color::White);
	settingsButton->registerEventHandler<MenuScene>(Button::Event::UNPRESSED, this, &MenuScene::handleSettingsButtonEvents);

	aboutButton = new Button(*resourcesManager->menuButtonTexture, sf::Vector2f(400, 80), sf::Vector2f(130, 460));
	aboutButton->setText(i18nManager->getText("About"), *resourcesManager->menuFont, 30, sf::Color::White);
	aboutButton->registerEventHandler<MenuScene>(Button::Event::UNPRESSED, this, &MenuScene::handleAboutButtonEvents);

	exitButton = new Button(*resourcesManager->menuButtonTexture, sf::Vector2f(400, 80), sf::Vector2f(130, 560));
	exitButton->setText(i18nManager->getText("Exit"), *resourcesManager->menuFont, 30, sf::Color::White);
	exitButton->registerEventHandler<MenuScene>(Button::Event::UNPRESSED, this, &MenuScene::handleExitButtonEvents);

	menuLayer.addEntity(*startButton);
	menuLayer.addEntity(*settingsButton);
	menuLayer.addEntity(*aboutButton);
	menuLayer.addEntity(*exitButton);
}

void MenuScene::generateLevelsLayer()
{
	levelButtonsLayer.setPosition(600, 200);

	INIFileParser parser("userdata/levels.dat");
	std::map<std::string, std::string> levelsData = parser.parse();
	bool isNotCompleted = false;
	for (int i = 0; i < 7; i++)
	{
		std::cout << (i - i / 3 * 3) << std::endl;
		
		levelButtons[i] = new LevelButton(sf::Vector2f(670.f + 150 * (i - i/3*3), 150.f + 150*(i/3)), *ResourcesManager::getInstance()->menuFont);
		levelButtons[i]->setLevelStats(i+1, std::stoi(levelsData.at(std::to_string(i+1))), 10);
		levelButtons[i]->setID("levelButton" + std::to_string(i));
		levelButtons[i]->registerEventHandler<MenuScene>(LevelButton::Event::UNPRESSED, this, &MenuScene::handleLevelButton);

		if (isNotCompleted)levelButtons[i]->setState(IButton::State::DISABLED);
		if (std::stoi(levelsData.at(std::to_string(i + 1))) == 0)isNotCompleted = true;
		levelButtonsLayer.addEntity(*levelButtons[i]);
	}

	levelButtonsLayer.setActive(false);
}

void MenuScene::generateSettingsLayer()
{
	soundSwitcher = new GuiSwitcher(*ResourcesManager::getInstance()->menuLeftArrowTexture, *ResourcesManager::getInstance()->menuRightArrowTexture, *ResourcesManager::getInstance()->menuFont, sf::Vector2f(900, 257)),
	musicSwitcher = new GuiSwitcher(*ResourcesManager::getInstance()->menuLeftArrowTexture, *ResourcesManager::getInstance()->menuRightArrowTexture, *ResourcesManager::getInstance()->menuFont, sf::Vector2f(900, 317)),
	settingsLayer.setPosition(600, 200);
	langSwitcherLayer.setPosition(700, 150);
	langButtonEn = new Button(*resourcesManager->menuLangButtonEnTexture, sf::Vector2f(100, 60), sf::Vector2f(821, 180));
	langButtonEn->registerEventHandler<MenuScene>(Button::Event::PRESSED, this, &MenuScene::handleLangButtonEnEvents);

	langButtonUk = new Button(*resourcesManager->menuLangButtonUkTexture, sf::Vector2f(100, 60), sf::Vector2f(721, 180));
	langButtonUk->registerEventHandler<MenuScene>(Button::Event::PRESSED, this, &MenuScene::handleLangButtonUkEvents);

	langButtonRu = new Button(*resourcesManager->menuLangButtonRuTexture, sf::Vector2f(100, 60), sf::Vector2f(921, 180));
	langButtonRu->registerEventHandler<MenuScene>(Button::Event::PRESSED, this, &MenuScene::handleLangButtonRuEvents);

	soundSwitcher->setSwitchableLimits(0, 10, 1);
	soundSwitcher->setCurrentValue(resourcesManager->getGlobalSoundVolume() / 10);
	soundSwitcher->registerEventHandler<MenuScene>(GuiSwitcher::Event::DECREASE_VALUE, this, &MenuScene::handleSoundSwitcherEvents);
	soundSwitcher->registerEventHandler<MenuScene>(GuiSwitcher::Event::INCREASE_VALUE, this, &MenuScene::handleSoundSwitcherEvents);

	musicSwitcher->setSwitchableLimits(0, 10, 1);
	musicSwitcher->setCurrentValue(resourcesManager->getGlobalMusicVolume() / 10);
	musicSwitcher->registerEventHandler<MenuScene>(GuiSwitcher::Event::DECREASE_VALUE, this, &MenuScene::handleMusicSwitcherEvents);
	musicSwitcher->registerEventHandler<MenuScene>(GuiSwitcher::Event::INCREASE_VALUE, this, &MenuScene::handleMusicSwitcherEvents);


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

	settingsLayer.addEntity(langSwitcherLayer);
	settingsLayer.addEntity(musicSwitcherLabel);
	settingsLayer.addEntity(*musicSwitcher);
	settingsLayer.addEntity(soundSwitcherLabel);
	settingsLayer.addEntity(*soundSwitcher);

	settingsLayer.setActive(false);
}

void MenuScene::handleInput()
{
}

void MenuScene::update()
{
	this->handleInput();
	startButton->update();
	settingsButton->update();
	aboutButton->update();
	exitButton->update();
	if (settingsLayer.isActive())
	{
		soundSwitcher->update();
		musicSwitcher->update();
		langButtonEn->update();
		langButtonRu->update();
		langButtonUk->update();
	}
	if (levelButtonsLayer.isActive())
	{
		for (int i = 0; i < 7; i++)levelButtons[i]->update();
	}
	if (isReadyForRefresh)SceneManager::getInstance()->setScene(SceneType::INTRO);
}

void MenuScene::draw(sf::RenderWindow *window)
{
	SceneManager::getInstance()->getWindow()->setView(*view);
	window->draw(menuBackgroundSprite);
	window->draw(menuLayer);
	window->draw(settingsLayer);
	window->draw(levelButtonsLayer);
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
	delete soundSwitcher;
	delete musicSwitcher;
}