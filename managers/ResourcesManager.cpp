#include "ResourcesManager.hpp"

ResourcesManager* ResourcesManager::p_instance = 0;

ResourcesManager* ResourcesManager::getInstance()
{
	if (!p_instance)
		p_instance = new ResourcesManager();
	return p_instance;
}

void ResourcesManager::init()
{
	loadLoadingResources();
}

void ResourcesManager::loadResources(SceneType p_scene)
{
	//SceneManager::getInstance()->setScene(SceneType::LOADING);
	switch (p_scene)
	{
		case SceneType::INTRO:
			loadIntroResources();
		break;
		case SceneType::MENU:
			loadMenuResources();
		break;
	}
}

void ResourcesManager::unloadResources(SceneType p_scene)
{
	switch (p_scene)
	{
	case SceneType::INTRO:
		unloadIntroResources();
		break;
	case SceneType::MENU:
		unloadMenuResources();
		break;
	}
}

void ResourcesManager::loadIntroResources()
{
	logoImage = new sf::Image();
	logoImage->loadFromFile("resources/gfx/logo.png");

	logoTexture = new sf::Texture();
	logoTexture->loadFromImage(*logoImage);

	logoTexture->setSmooth(true);

	logoShader = new sf::Shader();
	logoShader->loadFromFile("resources/shaders/logoShader.frag", sf::Shader::Fragment);
}

void ResourcesManager::loadMenuResources()
{
	menuBackground = new sf::Image();
	menuBackground->loadFromFile("resources/gfx/mainmenu.png");

	menuBackgroundTexture = new sf::Texture();
	menuBackgroundTexture->loadFromImage(*menuBackground);

	menuBackgroundTexture->setSmooth(true);
}

void ResourcesManager::loadLoadingResources()
{

}

void ResourcesManager::unloadIntroResources()
{
	delete logoTexture;
	delete logoImage;
	delete logoShader;
}

void ResourcesManager::unloadMenuResources()
{

}
