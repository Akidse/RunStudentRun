#ifndef GAME_SCENE_HPP
#define GAME_SCENE_HPP

#include "../SFMEngine/Scene.hpp"
#include <SFML/Graphics.hpp>
#include "../managers/SceneManager.hpp"
#include "../managers/ResourcesManager.hpp"
#include "../entities/Level.hpp"
class GameScene : public Scene
{
	ResourcesManager* resourcesManager;
public:
	Level level;
	GameScene();
	void draw(sf::RenderWindow *window);
	void update();
	void handleInput();

	~GameScene();
};
#endif