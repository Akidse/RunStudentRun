#ifndef LEVELCLASS_HPP
#define LEVELCLASS_HPP

#include <SFML/Graphics.hpp>
#include "../managers/TimeManager.hpp"
#include "../utilities/Constants.hpp"
#include "../utilities/LevelParser.hpp"
#include "../utilities/INIFileParser.hpp"
#include "LevelBlockFactory.hpp"
#include "Student.hpp"
#include "../entities/GuiLayer.hpp"
#include <list>
class Level : public sf::Drawable, public sf::Transformable
{
	std::list<LevelBlock*> blocks;
	sf::RectangleShape backgroundTop1;
	sf::RectangleShape backgroundBottom;
	sf::RectangleShape backgroundBottom2;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	bool checkCollision();
	void updateParallaxBackground(float pStepX);
	sf::RectangleShape paperCountShape;
	sf::Text paperCountText;
	sf::Text pauseGameMessage, finishGameMessage, overGameMessage, continueMessage;
	sf::RectangleShape messageContainer;
	GuiLayer pauseMessageLayer, finishMessageLayer, overGameMessageLayer;
	int catchedPapers;
	int lastBlockX;
	int currentLevel;
	bool isGameFinished;
	bool isReadyReturnToMenu = false, isGameStarted = false, isGamePaused = false;
	INIFileParser* levelResultsParser;
	void updateMessageBlock();
	sf::Time timer;
	sf::Text timerText;
	void startSounds();
	void pauseSounds();
public:
	sf::View* view;
	Student* student;
	void gameOver();
	void gameFinish();
	void pauseGame();
	void unpauseGame();
	void saveLevelResults();
	void studentEventListener(std::string studentId, int event);
	Level(int levelNumber);
	void update();
	~Level();
};
#endif