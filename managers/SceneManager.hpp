#ifndef SCENE_MANAGER_HPP
#define SCENE_MANAGER_HPP

#include <SFML/Graphics.hpp>
#include "ResourcesManager.hpp"
#include "../SFMEngine/Scene.hpp"
#include "../SFMEngine/SceneType.hpp"
#include "../scenes/Intro.hpp"
#include "../scenes/Menu.hpp"
class SceneManager
{
private:
	SceneType currentSceneType;
	Scene* currentScene;
	sf::RenderWindow* window;
	static SceneManager* p_instance;
	SceneManager(){};
	SceneManager(const SceneManager&);
	SceneManager& operator = (SceneManager&);
	void createScene(SceneType p_scene);
public:
	static SceneManager* getInstance();
	void init(sf::RenderWindow* p_window);
	void setScene(SceneType p_scene);
	Scene* getCurrentScene();
	SceneType getCurrentSceneType();
	sf::RenderWindow* getWindow();
};

#endif