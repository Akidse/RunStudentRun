#include "LevelBlockFactory.hpp"

LevelBlock* LevelBlockFactory::createBlock(int blockID, sf::Vector2f pPosition)
{
	LevelBlock* instance = nullptr;
	switch (blockID)
	{
	case 1:
		instance = new LevelGroundBlock(pPosition);
		break;
	case 2:
		instance = new LevelPaperBlock(pPosition);
		break;
	case 3:
		instance = new LevelUnderGroundBlock(pPosition);
		break;
	}

	if (instance != nullptr)
		return instance;
	else
		return nullptr;
}

LevelBlock* LevelBlockFactory::createGroundBlock(sf::Vector2f pPosition, int leftTopCorner, int rightTopCorner, int leftBottomCorner, int rightBottomCorner)
{
	LevelBlock* instance = nullptr;
	instance = new LevelGroundBlock(pPosition, leftTopCorner, rightTopCorner, leftBottomCorner, rightBottomCorner);

	if (instance != nullptr)
		return instance;
	else
		return nullptr;
}