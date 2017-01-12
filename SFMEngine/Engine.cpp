#include "Engine.hpp"

Engine::Engine()
{
	this->settings = ContextSettings();
	this->settings.antialiasingLevel = 8;

	window.create(VideoMode(Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT), Constants::WINDOW_NAME, Style::Default, this->settings);

	this->window.setFramerateLimit(Constants::FRAMERATE);
	this->window.setVerticalSyncEnabled(true);
	SceneManager::getInstance()->init(&window);
}

void Engine::start()
{
	this->loop();
}
void Engine::loop()
{
	this->previousTime = this->clock.getElapsedTime().asMilliseconds();
	this->lagTime = 0;
	while (true)
	{
		this->currentTime = this->clock.getElapsedTime().asMilliseconds();
		this->elapsedTime = this->currentTime - this->previousTime;
		this->previousTime = this->currentTime;
		this->lagTime += this->elapsedTime;

		while (this->lagTime >= 1000 / Constants::FRAMERATE)
		{
			this->handleInput();
			SceneManager::getInstance()->getCurrentScene()->update();
			this->lagTime -= 1000 / Constants::FRAMERATE;
		}

		this->window.clear(sf::Color(255,255,255));
		SceneManager::getInstance()->getCurrentScene()->draw(&window);
		this->window.display();
	}
}

void Engine::handleInput()
{
	Event event;
	while (this->window.pollEvent(event))
	{
		if (event.type == Event::Closed)
		{
			this->window.close();
		}
	}
}