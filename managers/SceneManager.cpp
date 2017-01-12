#include "SceneManager.hpp"

SceneManager* SceneManager::p_instance = 0;

SceneManager* SceneManager::getInstance()
{
	if (!p_instance)
		p_instance = new SceneManager();
	return p_instance;
}

void SceneManager::init(sf::RenderWindow* p_window)
{
	window = p_window;
	setScene(SceneType::INTRO);
}

void SceneManager::setScene(SceneType p_scene)
{
	if (currentScene != NULL)
	{
		ResourcesManager::getInstance()->unloadResources(currentSceneType);
		delete currentScene;
	}
	this->currentSceneType = p_scene;
	ResourcesManager::getInstance()->loadResources(p_scene);
	createScene(p_scene);
}

void SceneManager::createScene(SceneType p_scene)
{
	switch (p_scene)
	{
	case SceneType::INTRO:
		currentScene = new IntroScene();
		break;
	case SceneType::MENU:
		currentScene = new MenuScene();
		break;
	}
}

Scene* SceneManager::getCurrentScene()
{
	return currentScene;
}

SceneType SceneManager::getCurrentSceneType()
{
	return currentSceneType;
}

sf::RenderWindow* SceneManager::getWindow()
{
	return window;
}