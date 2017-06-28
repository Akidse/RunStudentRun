#ifndef STUDENT_HPP
#define STUDENT_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "../SFMEngine/Eventable.hpp"
#include "../entities/LevelBlock.hpp"
#include "../managers/TimeManager.hpp"
#include "../utilities/Constants.hpp"
#include <list>
class Student : public sf::Drawable, public sf::Transformable, public Eventable
{
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
	static enum Event
	{
		COLLISION_BOTTOM,
		COLLISION_RIGHT,
		COLLISION_TOP,
		CATCH_PAPER
	};
	Student(sf::Vector2f pPosition);
	sf::RectangleShape rectangleShape;
	float jumpHigh;
	void checkCollision(std::list<LevelBlock*>& blocks);
	void update();
	void handleInput();
	void jump();
	void updateRunningSprite();
	sf::Time spriteFramesTime;
	int currentFrame;
	bool isJumping = false;
	bool isFalling = false;
	sf::Vector2f getCollisionCoordinates();
};
#endif