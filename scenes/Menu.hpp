#ifndef MENU_SCENE_HPP
#define MENU_SCENE_HPP

#include "../SFMEngine/Scene.hpp"
#include <SFML/Graphics.hpp>
#include "../managers/SceneManager.hpp"
#include "../managers/ResourcesManager.hpp"
#include "../managers/I18nManager.hpp"
#include "../entities/Button.hpp"
#include <iostream>
class MenuScene : public Scene
{
	ResourcesManager* resourcesManager;
	I18nManager* i18nManager;

	Button* startButton;
	Button* settingsButton;
public:
	MenuScene();
	void draw(sf::RenderWindow *window);
	void update();
	void handleInput();
	void handleStartButtonEvents(int e);
	void handleSettingsButtonEvents(int e);

	sf::Sprite menuBackgroundSprite;
};
#endif