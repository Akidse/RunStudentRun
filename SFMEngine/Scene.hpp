#ifndef INTERFACE_SCENE_HPP
#define INTERFACE_SCENE_HPP

#include <SFML/Graphics.hpp>
#include "SceneType.hpp"
class Scene
{
	SceneType sceneType;
public:
	virtual void draw(sf::RenderWindow *window){};
	virtual void update(){};
	virtual void handleInput(){};
	virtual void loadResourses(){};
	SceneType getSceneType()
	{
		return sceneType;
	}
};
#endif