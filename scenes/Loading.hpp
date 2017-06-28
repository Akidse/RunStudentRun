#ifndef LOADING_SCENE_HPP
#define LOADING_SCENE_HPP

#include "../SFMEngine/Scene.hpp"
#include <SFML/Graphics.hpp>
#include "../managers/SceneManager.hpp"
#include <iostream>
class LoadingScene : public Scene
{
	sf::CircleShape circle;
public:
	LoadingScene();
	void draw(sf::RenderWindow *window);
	void update();
	void handleInput();
};
#endif