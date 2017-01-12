#ifndef INTRO_SCENE_HPP
#define INTRO_SCENE_HPP

#include "../SFMEngine/Scene.hpp"
#include <SFML/Graphics.hpp>
#include "../managers/SceneManager.hpp"
#include "../managers/ResourcesManager.hpp"
#include <iostream>
class IntroScene : public Scene
{
	ResourcesManager* resourcesManager;
	sf::CircleShape circle;
public:
	IntroScene();
	void draw(sf::RenderWindow *window);
	void update();
	void handleInput();

	sf::Sprite logoSprite;
	sf::Image logoImage;
	sf::Texture logoTexture;
};
#endif