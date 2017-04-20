#include "Engine.hpp"

Engine::Engine()
{
	this->settings = ContextSettings();
	this->settings.antialiasingLevel = 8;

	window.create(VideoMode(Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT), Constants::WINDOW_NAME, Style::Default, this->settings);

	this->window.setFramerateLimit(Constants::FRAMERATE);
	this->window.setVerticalSyncEnabled(true);
	ConfigManager::getInstance()->init();
	I18nManager::getInstance()->init();
	I18nManager::getInstance()->loadLocale(ConfigManager::getInstance()->get("locale"));
	ResourcesManager::getInstance()->init();
	ResourcesManager::getInstance()->setGlobalMusicVolume(10*std::stoi(ConfigManager::getInstance()->get("music")));
	ResourcesManager::getInstance()->setGlobalSoundVolume(10*std::stoi(ConfigManager::getInstance()->get("sound")));
	SceneManager::getInstance()->init(&window);
	SceneManager::getInstance()->setScene(SceneType::MENU);
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