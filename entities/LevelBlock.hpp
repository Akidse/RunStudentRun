#ifndef LEVEL_BLOCK_HPP
#define LEVEL_BLOCK_HPP

#include <SFML/Graphics.hpp>
enum class BlockType
{
	DEFAULT,
	GROUND,
	UNDERGROUND,
	PAPER
};
class LevelBlock : public sf::Drawable, public sf::Transformable
{
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
protected:
	BlockType blockType = BlockType::DEFAULT;
public:
	LevelBlock();
	BlockType getBlockType();
	LevelBlock(sf::Vector2f pPosition);
	sf::RectangleShape collisionBlock;
	sf::RectangleShape blockSprite;
	virtual sf::FloatRect getCollisionPoints();
	virtual bool action(std::string pAction);
	virtual void update();
};

class LevelGroundBlock : public LevelBlock
{
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
	sf::RectangleShape blockSprite_top;
	sf::RectangleShape blockSprite_bottom;
	LevelGroundBlock(sf::Vector2f pPosition);
	LevelGroundBlock(sf::Vector2f pPosition, int leftTopCorner, int rightTopCorner, int leftBottomCorner, int rightBottomCorner);
};

class LevelUnderGroundBlock : public LevelBlock
{
public:
	LevelUnderGroundBlock(sf::Vector2f pPosition);
};

class LevelPaperBlock : public LevelBlock
{
	float animationStepY = 0;
	bool isToUpAnimation = true;
	bool isCatched = false;
	bool isCatching = false;
	virtual void LevelPaperBlock::draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
	LevelPaperBlock(sf::Vector2f pPosition);
	bool action(std::string pAction);
	void update();
};
#endif