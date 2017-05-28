#ifndef MENU_SCENE_HPP
#define MENU_SCENE_HPP

#include "../SFMEngine/Scene.hpp"
#include <SFML/Graphics.hpp>
#include "../managers/SceneManager.hpp"
#include "../managers/ConfigManager.hpp"
#include "../managers/ResourcesManager.hpp"
#include "../managers/I18nManager.hpp"
#include "../entities/GuiLayer.hpp"
#include "../entities/Button.hpp"
#include "../entities/GuiSwitcher.hpp"
#include "../entities/LevelButton.hpp"
#include <iostream>
class MenuScene : public Scene
{
	ResourcesManager* resourcesManager;
	I18nManager* i18nManager;
	ConfigManager* configManager;

	GuiLayer menuLayer;
	GuiLayer settingsLayer;
	GuiLayer langSwitcherLayer;
	Button* startButton;
	Button* settingsButton;
	Button* aboutButton;
	Button* exitButton;
	Button* langButtonEn;
	Button* langButtonUk;
	Button* langButtonRu;
	Button* scoresButton;
	GuiSwitcher* soundSwitcher;
	GuiSwitcher* musicSwitcher;
	
	LevelButton* testLevelButton;

	sf::Text langSwitcherLabel;
	sf::Text soundSwitcherLabel;
	sf::Text musicSwitcherLabel;

	sf::View* view;

	bool isReadyForRefresh = false;
	void generateMenuLayer();
	void generateSettingsLayer();
	void generateLevelsLayer();
public:

	MenuScene();
	void draw(sf::RenderWindow *window);
	void update();
	void handleInput();
	void handleStartButtonEvents(int e);
	void handleSettingsButtonEvents(int e);
	void handleAboutButtonEvents(int e);
	void handleExitButtonEvents(int e);
	void handleSoundSwitcherEvents(int e);
	void handleMusicSwitcherEvents(int e);
	void handleScoresButtonEvents(int e);

	void handleLangButtonEnEvents(int e);
	void handleLangButtonUkEvents(int e);
	void handleLangButtonRuEvents(int e);

	sf::Sprite menuBackgroundSprite;
	~MenuScene();
};
#endif