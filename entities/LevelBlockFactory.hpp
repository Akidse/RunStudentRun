#ifndef LEVELBLOCKFACTORY_HPP
#define LEVELBLOCKFACTORY_HPP

#include "LevelBlock.hpp"
#include <memory>
class LevelBlockFactory
{
public:
	static LevelBlock* createBlock(int blockID, sf::Vector2f pPosition);
	static LevelBlock* createGroundBlock(sf::Vector2f pPosition, int leftTopCorner, int rightTopCorner, int leftBottomCorner, int rightBottomCorner);
};
#endif