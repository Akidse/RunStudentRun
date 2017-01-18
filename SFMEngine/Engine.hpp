#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <SFML/Graphics.hpp>
#include "../utilities/Constants.hpp"
#include "../managers/SceneManager.hpp"
#include "../managers/TimeManager.hpp"

using namespace sf;

class Engine
{
	ContextSettings settings;
	void loop();
	RenderWindow window;
public:
	Engine();
	void start();
	void handleInput();
};

#endif
