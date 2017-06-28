#include "LevelBlock.hpp"
#include <iostream>
#include "../managers/ResourcesManager.hpp"
#include "../managers/TimeManager.hpp"
LevelBlock::LevelBlock()
{
}

BlockType LevelBlock::getBlockType()
{
	return blockType;
}

LevelBlock::LevelBlock(sf::Vector2f pPosition)
{
	collisionBlock.setSize(sf::Vector2f(100.f, 100.f));
	collisionBlock.setPosition(pPosition);

	blockSprite.setTexture(ResourcesManager::getInstance()->gameBlock1);
	blockSprite.setSize(sf::Vector2f(100.f, 109.f));
	blockSprite.setPosition(pPosition.x, pPosition.y - 9.f);
}

void LevelBlock::update()
{
}

bool LevelBlock::action(std::string pAction)
{
	return false;
}

sf::FloatRect LevelBlock::getCollisionPoints()
{
	return collisionBlock.getGlobalBounds();
}

void LevelBlock::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(blockSprite, states);
}



LevelGroundBlock::LevelGroundBlock(sf::Vector2f pPosition)
{
	collisionBlock.setSize(sf::Vector2f(100.f, 100.f));
	collisionBlock.setPosition(pPosition);

	blockSprite.setFillColor(sf::Color(127, 173, 113));
	blockSprite.setSize(sf::Vector2f(100.f, 50));
	blockSprite.setPosition(pPosition.x, pPosition.y + 35.f);

	blockSprite_top.setTexture(ResourcesManager::getInstance()->gameBlock1_top);
	blockSprite_top.setTextureRect(sf::IntRect(0, 0, 100.f, 44.f));
	blockSprite_top.setSize(sf::Vector2f(100.f, 44.f));
	blockSprite_top.setPosition(pPosition.x, pPosition.y - 9.f);

	blockSprite_bottom.setTexture(ResourcesManager::getInstance()->gameBlock1_bottom);
	blockSprite_bottom.setTextureRect(sf::IntRect(0, 0, 100.f, 15.f));
	blockSprite_bottom.setSize(sf::Vector2f(100.f, 15));
	blockSprite_bottom.setPosition(pPosition.x, pPosition.y + 85.f);

	blockType = BlockType::GROUND;
}

LevelGroundBlock::LevelGroundBlock(sf::Vector2f pPosition, int leftTopCorner, int rightTopCorner, int leftBottomCorner, int rightBottomCorner)
{
	collisionBlock.setSize(sf::Vector2f(100.f, 100.f));
	collisionBlock.setPosition(pPosition);

	blockSprite.setFillColor(sf::Color(127, 173, 113));
	blockSprite.setSize(sf::Vector2f(100.f, 50));
	blockSprite.setPosition(pPosition.x, pPosition.y + 35.f);

	blockSprite_top.setTexture(ResourcesManager::getInstance()->gameBlock1_top);
	blockSprite_top.setTextureRect(sf::IntRect(0, 0, 100.f, 44.f));
	blockSprite_top.setSize(sf::Vector2f(100.f, 44.f));
	blockSprite_top.setPosition(pPosition.x, pPosition.y - 9.f);

	blockSprite_bottom.setTexture(ResourcesManager::getInstance()->gameBlock1_bottom);
	blockSprite_bottom.setTextureRect(sf::IntRect(0, 0, 100.f, 15.f));
	blockSprite_bottom.setSize(sf::Vector2f(100.f, 15.f));
	blockSprite_bottom.setPosition(pPosition.x, pPosition.y + 85.f);

	blockType = BlockType::GROUND;

	if (leftTopCorner == 1 && rightTopCorner == 1)blockSprite_top.setTextureRect(sf::IntRect(102, 0, 100.f, 44.f));
	else if (leftTopCorner == 1)blockSprite_top.setTextureRect(sf::IntRect(200, 0, 100.f, 44.f));
	else if (rightTopCorner == 1)blockSprite_top.setTextureRect(sf::IntRect(300, 0, 100.f, 44.f));

	if (leftBottomCorner == 1 && rightBottomCorner == 1)blockSprite_bottom.setTextureRect(sf::IntRect(102, 0, 100.f, 15.f));
	else if (leftBottomCorner == 1)blockSprite_bottom.setTextureRect(sf::IntRect(207, 0, 100.f, 15.f));
	else if (rightBottomCorner == 1)blockSprite_bottom.setTextureRect(sf::IntRect(300, 0, 100.f, 15.f));
}

void LevelGroundBlock::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(blockSprite_top, states);
	target.draw(blockSprite, states);
	target.draw(blockSprite_bottom, states);
}

LevelUnderGroundBlock::LevelUnderGroundBlock(sf::Vector2f pPosition)
{
	collisionBlock.setSize(sf::Vector2f(100.f, 100.f));
	collisionBlock.setPosition(pPosition);

	blockSprite.setFillColor(sf::Color(127,173,113));
	blockSprite.setSize(sf::Vector2f(100.f, 100.f));
	blockSprite.setPosition(pPosition);

	blockType = BlockType::UNDERGROUND;
}

LevelPaperBlock::LevelPaperBlock(sf::Vector2f pPosition)
{
	collisionBlock.setSize(sf::Vector2f(50.f, 50.f));
	collisionBlock.setPosition(pPosition.x + 25.f, pPosition.y + 25.f);

	blockSprite.setTexture(ResourcesManager::getInstance()->gameBlock2);
	blockSprite.setSize(sf::Vector2f(50.f, 50.f));
	blockSprite.setPosition(pPosition.x + 25.f, pPosition.y + 25.f);

	blockType = BlockType::PAPER;
}

void LevelPaperBlock::update()
{
	if (isCatching == false && isCatched == false)
	{
		float stepY = (float)TimeManager::getInstance()->getTime(TimeType::ELAPSED_TIME) / (1000.f / 120.f) * (0.1f);

		if (animationStepY > 20)isToUpAnimation = false;
		if (animationStepY < 0)isToUpAnimation = true;

		if (animationStepY <= 20 && isToUpAnimation)
		{
			animationStepY += stepY;
			collisionBlock.move(0, stepY);
			blockSprite.move(0, stepY);
		}
		else if (animationStepY >= 0 && !isToUpAnimation)
		{
			animationStepY -= stepY;
			collisionBlock.move(0, -stepY);
			blockSprite.move(0, -stepY);
		}
	}
	else if (isCatching == true)
	{
		if (collisionBlock.getPosition().y > 0)
		{
			float stepY = (float)TimeManager::getInstance()->getTime(TimeType::ELAPSED_TIME) / (1000.f / 120.f) * (2.f);
			float stepX = (float)TimeManager::getInstance()->getTime(TimeType::ELAPSED_TIME) / (1000.f / 120.f) * (0.1f);
			collisionBlock.move(-stepX, -stepY);
			blockSprite.move(-stepX, -stepY);
		}
		else
		{
			isCatching = false;
		}
	}
}

bool LevelPaperBlock::action(std::string pAction)
{
	if (isCatched == true)return true;
	else
	{
		ResourcesManager::getInstance()->gameCollect->play();
		isCatched = true;
		isCatching = true;
		return false;
	}
}

void LevelPaperBlock::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if ((isCatched && isCatching) || !isCatched) target.draw(blockSprite, states);
}