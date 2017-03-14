#ifndef INTRO_SCENE_HPP
#define INTRO_SCENE_HPP

#include "../SFMEngine/Scene.hpp"
#include <SFML/Graphics.hpp>
#include "../managers/SceneManager.hpp"
#include "../managers/ResourcesManager.hpp"
#include "../managers/TimeManager.hpp"
#include <iostream>

#define INTRO_SCENE_DURATION 5.f

class IntroScene : public Scene
{
	ResourcesManager* resourcesManager;
	sf::Time currentDuration;
public:
	IntroScene();
	void draw(sf::RenderWindow *window);
	void update();
	void handleInput();

	sf::Sprite logoSprite;
};
#endif