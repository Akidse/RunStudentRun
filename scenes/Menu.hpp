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
	GuiLayer levelButtonsLayer;
	GuiLayer aboutLayer;
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
	
	LevelButton* levelButtons[7];

	sf::Text langSwitcherLabel;
	sf::Text soundSwitcherLabel;
	sf::Text musicSwitcherLabel;
	sf::Text aboutText;

	sf::RectangleShape aboutSprite;

	sf::View* view;

	bool isReadyForRefresh = false;
	bool isReadyForGameScreen = false;
	void generateMenuLayer();
	void generateSettingsLayer();
	void generateAboutLayer();
	void generateLevelsLayer();
public:

	MenuScene();
	void draw(sf::RenderWindow *window);
	void update();
	void handleInput();
	void handleStartButtonEvents(std::string objectID, int e);
	void handleSettingsButtonEvents(std::string objectID, int e);
	void handleAboutButtonEvents(std::string objectID, int e);
	void handleExitButtonEvents(std::string objectID, int e);
	void handleSoundSwitcherEvents(std::string objectID, int e);
	void handleMusicSwitcherEvents(std::string objectID, int e);
	void handleScoresButtonEvents(std::string objectID, int e);

	void handleLangButtonEnEvents(std::string objectID, int e);
	void handleLangButtonUkEvents(std::string objectID, int e);
	void handleLangButtonRuEvents(std::string objectID, int e);

	void handleLevelButton(std::string objectID, int e);

	sf::Sprite menuBackgroundSprite;
	~MenuScene();
};
#endif