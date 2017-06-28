#include "Level.hpp"
#include "../managers/SceneManager.hpp"
#include "../managers/i18nManager.hpp"
#include <iostream>
#include <string>
Level::Level(int levelNumber)
{
	timer = sf::Time::Zero;
	currentLevel = levelNumber;
	levelResultsParser = new INIFileParser("./userdata/levels.dat");
	student = new Student(sf::Vector2f(50, Constants::WINDOW_HEIGHT - 175));
	view = new sf::View(sf::FloatRect(0, 0, Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT));
	LevelParser levelParser("./resources/data/"+std::to_string(currentLevel)+".dat");
	std::vector<std::vector<int>> parsedLevel = levelParser.parse();
	int leftTopCorner = 0, rightTopCorner = 0, leftBottomCorner = 0, rightBottomCorner = 0;
	int leftBlock = 0, topBlock = 0, bottomBlock = 0, rightBlock = 0;
	for (int i = 0; i < parsedLevel.size(); i++)
	{
		for (int j = 0; j < parsedLevel[i].size(); j++)
		{
			leftBlock = 0, topBlock = 0, bottomBlock = 0, rightBlock = 0;
			leftTopCorner = 0, rightTopCorner = 0, leftBottomCorner = 0, rightBottomCorner = 0;
			if (parsedLevel[i][j] != 0)
			{
				if (parsedLevel[i][j] == 1 && j + 1 <= parsedLevel[i].size() && parsedLevel[i][j+1] == 1)
				{
					blocks.push_back(LevelBlockFactory::createBlock(3, sf::Vector2f(i * 100.f, Constants::WINDOW_HEIGHT - (j + 1) * 100.f)));
				}
				else if (parsedLevel[i][j] == 1)
				{
					if (i > 0 && parsedLevel[i - 1][j] != 1){ leftBlock = 1; }
					if (i < parsedLevel.size()-1 && parsedLevel[i + 1][j] != 1){ rightBlock = 1; }
					if (j > 0 && parsedLevel[i][j - 1] != 1){ bottomBlock = 1; }
					if (j < parsedLevel[i].size()-1 && parsedLevel[i][j + 1] != 1){ topBlock = 1; }
					if (leftBlock == 1){ leftTopCorner = 1; leftBottomCorner = 1; }
					if (rightBlock == 1){ rightTopCorner = 1; rightBottomCorner = 1;}
					if (bottomBlock == 0){ leftBottomCorner = 0; rightBottomCorner = 0;}

					blocks.push_back(LevelBlockFactory::createGroundBlock(sf::Vector2f(i * 100.f, Constants::WINDOW_HEIGHT - (j + 1) * 100.f), leftTopCorner, rightTopCorner, leftBottomCorner, rightBottomCorner));
				}
				else blocks.push_back(LevelBlockFactory::createBlock(parsedLevel[i][j], sf::Vector2f(i * 100.f, Constants::WINDOW_HEIGHT - (j + 1) * 100.f)));
				lastBlockX = i * 100 + 100;
			}
		}
	}
	backgroundTop1.setTexture(ResourcesManager::getInstance()->gameBackgroundTop);
	backgroundTop1.setSize(sf::Vector2f(Constants::WINDOW_WIDTH, 707));
	backgroundBottom.setFillColor(sf::Color(121, 201, 249));
	backgroundBottom.setSize(sf::Vector2f(Constants::WINDOW_WIDTH, 200));
	backgroundBottom2.setFillColor(sf::Color(105, 146, 242));
	backgroundBottom2.setSize(sf::Vector2f(Constants::WINDOW_WIDTH, 200));

	backgroundTop1.setPosition(0, 95.f);
	backgroundBottom.setPosition(0, 0);
	backgroundBottom2.setPosition(0, Constants::WINDOW_HEIGHT - 100);

	paperCountShape.setTexture(ResourcesManager::getInstance()->gameBlock2);
	paperCountShape.setSize(sf::Vector2f(50.f, 50.f));
	paperCountShape.setPosition(10.f, 10.f);

	paperCountText.setFont(*ResourcesManager::getInstance()->gameFont);
	paperCountText.setString(std::to_string(catchedPapers) + " / 10");
	paperCountText.setPosition(70.f, 17.5f);

	student->registerEventHandler<Level>(Student::Event::CATCH_PAPER, this, &Level::studentEventListener);
	student->registerEventHandler<Level>(Student::Event::COLLISION_RIGHT, this, &Level::studentEventListener);

	messageContainer.setSize(sf::Vector2f(Constants::WINDOW_WIDTH / 2.f, Constants::WINDOW_HEIGHT / 4.f));
	messageContainer.setPosition(view->getCenter().x - (messageContainer.getSize().x) / 2.f, view->getCenter().y - (messageContainer.getSize().y) / 2.f);
	messageContainer.setFillColor(sf::Color(0, 0, 0, 50));


	timerText.setString("3");
	timerText.setFillColor(sf::Color::Black);
	timerText.setFont(*ResourcesManager::getInstance()->gameFont);
	timerText.setCharacterSize(70.f);
	timerText.setPosition(view->getCenter().x - timerText.getGlobalBounds().width / 2.f, view->getCenter().y - timerText.getGlobalBounds().height / 2.f);

	overGameMessage.setString(I18nManager::getInstance()->getText("Game Over =("));
	overGameMessage.setFillColor(sf::Color::White);
	overGameMessage.setFont(*ResourcesManager::getInstance()->gameFont);
	overGameMessage.setCharacterSize(50.f);
	overGameMessage.setPosition(view->getCenter().x - overGameMessage.getGlobalBounds().width / 2.f, view->getCenter().y - overGameMessage.getGlobalBounds().height / 2.f - 50.f);

	pauseGameMessage.setString(I18nManager::getInstance()->getText("Game Paused"));
	pauseGameMessage.setFillColor(sf::Color::White);
	pauseGameMessage.setFont(*ResourcesManager::getInstance()->gameFont);
	pauseGameMessage.setCharacterSize(50.f);
	pauseGameMessage.setPosition(view->getCenter().x - pauseGameMessage.getGlobalBounds().width / 2.f, view->getCenter().y - pauseGameMessage.getGlobalBounds().height / 2.f - 50.f);

	finishGameMessage.setString(I18nManager::getInstance()->getText("Game Finished"));
	finishGameMessage.setFillColor(sf::Color::White);
	finishGameMessage.setFont(*ResourcesManager::getInstance()->gameFont);
	finishGameMessage.setCharacterSize(50.f);
	finishGameMessage.setPosition(view->getCenter().x - finishGameMessage.getGlobalBounds().width / 2.f, view->getCenter().y - finishGameMessage.getGlobalBounds().height / 2.f - 50.f);

	continueMessage.setString(I18nManager::getInstance()->getText("Press Enter to continue"));
	continueMessage.setFillColor(sf::Color::White);
	continueMessage.setFont(*ResourcesManager::getInstance()->gameFont);
	continueMessage.setCharacterSize(30.f);
	continueMessage.setPosition(view->getCenter().x - continueMessage.getGlobalBounds().width / 2.f, view->getCenter().y - continueMessage.getGlobalBounds().height / 2.f + 50.f);

	overGameMessageLayer.addEntity(messageContainer);
	overGameMessageLayer.addEntity(overGameMessage);
	overGameMessageLayer.addEntity(continueMessage);
	pauseMessageLayer.addEntity(messageContainer);
	pauseMessageLayer.addEntity(pauseGameMessage);
	pauseMessageLayer.addEntity(continueMessage);
	finishMessageLayer.addEntity(messageContainer);
	finishMessageLayer.addEntity(finishGameMessage);
	finishMessageLayer.addEntity(continueMessage);
	
	overGameMessageLayer.setActive(false);
	pauseMessageLayer.setActive(false);
	finishMessageLayer.setActive(false);

	ResourcesManager::getInstance()->gameMusic->setLoop(true);
	ResourcesManager::getInstance()->gameMusic->setVolume(ResourcesManager::getInstance()->getGlobalMusicVolume() / 2);
}
void Level::updateMessageBlock()
{
	messageContainer.setPosition(view->getCenter().x - (messageContainer.getSize().x) / 2.f, view->getCenter().y - (messageContainer.getSize().y) / 2.f);
	overGameMessage.setPosition(view->getCenter().x - overGameMessage.getGlobalBounds().width / 2.f, view->getCenter().y - overGameMessage.getGlobalBounds().height / 2.f - 50.f);
	pauseGameMessage.setPosition(view->getCenter().x - pauseGameMessage.getGlobalBounds().width / 2.f, view->getCenter().y - pauseGameMessage.getGlobalBounds().height / 2.f - 50.f);
	finishGameMessage.setPosition(view->getCenter().x - finishGameMessage.getGlobalBounds().width / 2.f, view->getCenter().y - finishGameMessage.getGlobalBounds().height / 2.f - 50.f);
	continueMessage.setPosition(view->getCenter().x - continueMessage.getGlobalBounds().width / 2.f, view->getCenter().y - continueMessage.getGlobalBounds().height / 2.f + 50.f);
}
void Level::studentEventListener(std::string studentId, int event)
{
	if (event == Student::Event::CATCH_PAPER)
	{
		catchedPapers++;
		paperCountText.setString(std::to_string(catchedPapers) + " / 10");
	}
	else if (event == Student::Event::COLLISION_RIGHT)
	{
		gameOver();
	}
}

bool Level::checkCollision()
{
	student->checkCollision(blocks);
	return false;
}

void Level::pauseGame()
{
	isGamePaused = true;
	updateMessageBlock();
	pauseMessageLayer.setActive(true);
}

void Level::unpauseGame()
{
	isGamePaused = false;
	pauseMessageLayer.setActive(false);
}

void Level::gameOver()
{
	isGameFinished = true;
	pauseSounds();
	ResourcesManager::getInstance()->gameLose->play();
	updateMessageBlock();
	overGameMessageLayer.setActive(true);
}

void Level::gameFinish()
{
	isGameFinished = true;
	pauseSounds();
	ResourcesManager::getInstance()->gameWin->play();
	saveLevelResults();
	//isReadyReturnToMenu = true;
	updateMessageBlock();
	finishMessageLayer.setActive(true);
}
void Level::saveLevelResults()
{
	std::map<std::string, std::string> levelsResults = levelResultsParser->parse();
	if (std::stoi(levelsResults.at(std::to_string(currentLevel))) < catchedPapers)
	{
		levelsResults.at(std::to_string(currentLevel)) = std::to_string(catchedPapers);

		std::ofstream file("./userdata/levels.dat", std::ios_base::trunc);
		std::string tempString;
		for (auto it = levelsResults.begin(); it != levelsResults.end(); ++it)
		{
			tempString = '"' + (*it).first + '"' + " = " + '"' + (*it).second + '"';
			file << tempString << std::endl;
		}
		file.close();
	}
}

void Level::startSounds()
{
	ResourcesManager::getInstance()->gameMusic->play();
}

void Level::pauseSounds()
{
	ResourcesManager::getInstance()->gameMusic->pause();
	ResourcesManager::getInstance()->gameWin->stop();
	ResourcesManager::getInstance()->gameLose->stop();
	ResourcesManager::getInstance()->gameCollect->stop();
}
void Level::updateParallaxBackground(float pStepX)
{
}

void Level::update()
{
	if (isGameStarted == false)
	{
		if (TimeManager::getInstance()->getTime(TimeType::ELAPSED_TIME) < 50)timer += sf::seconds((float)TimeManager::getInstance()->getTime(TimeType::ELAPSED_TIME) / 1000.f);
		timerText.setString(std::to_string(3 - (int)floor(timer.asSeconds())));
		if (timer.asSeconds() > 3)
		{
			isGameStarted = true;
			timer = sf::Time::Zero;
			startSounds();
		}
	}
	if (isGamePaused == true)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
		{
			unpauseGame();
			startSounds();
		}
	}
	if (isGamePaused == false && isGameFinished == false && isGameStarted == true)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
		{
			pauseGame();
			pauseSounds();
		}
	}
	if (isGameFinished == true)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
		{
			isReadyReturnToMenu = true;
			pauseSounds();
			ConfigManager::getInstance()->openLevelLayer = true;
		}
	}
	if (isGameFinished == false && isGameStarted == true && isGamePaused == false)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			isReadyReturnToMenu = true;
			pauseSounds();
			ConfigManager::getInstance()->openLevelLayer = true;
		}
		float stepX = (float)TimeManager::getInstance()->getTime(TimeType::ELAPSED_TIME) / (1000.f / 120.f) * (1.f);
		updateParallaxBackground(stepX);
		backgroundBottom2.move(stepX, 0);
		backgroundBottom.move(stepX, 0);
		backgroundTop1.move(stepX, 0);
		view->move(stepX, 0);
		if (view->getCenter().x - view->getSize().x / 2.f >= lastBlockX)gameFinish();
		student->update();
		std::list<LevelBlock*>::iterator it;
		for (it = blocks.begin(); it != blocks.end(); it++)
		{
			(*it)->update();
		}
		checkCollision();

		paperCountShape.move(stepX, 0);
		paperCountText.move(stepX, 0);
		SceneManager::getInstance()->getWindow()->setView(*view);
	}

	if (isReadyReturnToMenu == true)SceneManager::getInstance()->setScene(SceneType::MENU);
}

void Level::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(backgroundBottom, states);
	target.draw(backgroundBottom2, states);
	target.draw(backgroundTop1, states);
	std::list<LevelBlock*>::const_iterator it;
	it = blocks.begin();
	for (it = blocks.begin(); it != blocks.end(); it++)
	{
		target.draw(*(*it), states);
	}
	target.draw(*student, states);
	target.draw(paperCountShape, states);
	target.draw(paperCountText, states);
	target.draw(overGameMessageLayer, states);
	target.draw(finishMessageLayer, states);
	target.draw(pauseMessageLayer, states);
	
	if (isGameStarted == false)target.draw(timerText, states);
}

Level::~Level()
{
	delete levelResultsParser;
	delete student;
	delete view;
}