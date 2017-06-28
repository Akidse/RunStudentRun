#include "Game.hpp"

GameScene::GameScene() : level(ConfigManager::getInstance()->getCurrentGameLevel())
{
	resourcesManager = ResourcesManager::getInstance();
}

void GameScene::handleInput()
{

}

void GameScene::update()
{
	this->handleInput();
	level.update();
}

void GameScene::draw(sf::RenderWindow *window)
{
	window->draw(level);
}

GameScene::~GameScene()
{
	delete resourcesManager;
}