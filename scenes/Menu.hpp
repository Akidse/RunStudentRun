#ifndef MENU_SCENE_HPP
#define MENU_SCENE_HPP

#include "../SFMEngine/Scene.hpp"
#include <SFML/Graphics.hpp>
#include "../managers/SceneManager.hpp"
#include "../managers/ResourcesManager.hpp"
#include <iostream>
class MenuScene : public Scene
{
	ResourcesManager* resourcesManager;
	sf::CircleShape circle;
public:
	MenuScene();
	void draw(sf::RenderWindow *window);
	void update();
	void handleInput();
};
#endif