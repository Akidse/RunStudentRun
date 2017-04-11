#ifndef MENU_SCENE_HPP
#define MENU_SCENE_HPP

#include "../SFMEngine/Scene.hpp"
#include <SFML/Graphics.hpp>
#include "../managers/SceneManager.hpp"
#include "../managers/ResourcesManager.hpp"
#include "../managers/I18nManager.hpp"
#include "../entities/GuiLayer.hpp"
#include "../entities/Button.hpp"
#include "../entities/GuiSwitcher.hpp"
#include <iostream>
class MenuScene : public Scene
{
	ResourcesManager* resourcesManager;
	I18nManager* i18nManager;

	GuiLayer menuLayer;
	GuiLayer settingsLayer;
	Button* startButton;
	Button* settingsButton;
	Button* aboutButton;
	Button* exitButton;
	GuiSwitcher soundSwitcher;
	GuiSwitcher musicSwitcher;

	void goToSubMenu();
	sf::View* view;
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

	sf::Sprite menuBackgroundSprite;
};
#endif