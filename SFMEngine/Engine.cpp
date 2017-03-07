#include "Engine.hpp"

Engine::Engine()
{
	this->settings = ContextSettings();
	this->settings.antialiasingLevel = 8;

	window.create(VideoMode(Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT), Constants::WINDOW_NAME, Style::Default, this->settings);

	this->window.setFramerateLimit(Constants::FRAMERATE);
	this->window.setVerticalSyncEnabled(true);
	ResourcesManager::getInstance()->init();
	SceneManager::getInstance()->init(&window);
	TimeManager::getInstance()->init();
}

void Engine::start()
{
	this->loop();
}
void Engine::loop()
{
	while (true)
	{
		TimeManager::getInstance()->updateLoopData();

		while (TimeManager::getInstance()->getTime(TimeType::LAG_TIME) >= 1000 / Constants::FRAMERATE)
		{
			this->handleInput();
			SceneManager::getInstance()->getCurrentScene()->update();
			TimeManager::getInstance()->setTime(TimeManager::getInstance()->getTime(TimeType::LAG_TIME) - 1000 / Constants::FRAMERATE, TimeType::LAG_TIME);
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