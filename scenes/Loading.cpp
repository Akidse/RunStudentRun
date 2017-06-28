#include "Loading.hpp"

LoadingScene::LoadingScene()
{
	circle = sf::CircleShape(150);
	circle.setFillColor(sf::Color(50, 150, 2));
}
void LoadingScene::handleInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		//SceneManager::getInstance()->setScene(SceneType::INTRO);
	}
}

void LoadingScene::update()
{
	handleInput();
	circle.move(0.1f, 0.1f);
}

void LoadingScene::draw(sf::RenderWindow *window)
{
	window->draw(circle);
}