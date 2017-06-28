#include "Student.hpp"
#include <iostream>
#include "../managers/ResourcesManager.hpp"
Student::Student(sf::Vector2f pPosition)
{
	rectangleShape.setTexture(ResourcesManager::getInstance()->gameStudentRunningSprite);
	rectangleShape.setTextureRect(sf::IntRect(0, 0, 40, 75));
	rectangleShape.setSize(sf::Vector2f(50.f, 75.f));
	rectangleShape.setPosition(pPosition);
	jumpHigh = 0.f;
	spriteFramesTime = sf::Time::Zero;
}

sf::Vector2f Student::getCollisionCoordinates()
{
	return rectangleShape.getPosition();
}

void Student::checkCollision(std::list<LevelBlock*>& blocks)
{
	sf::FloatRect studentBounds = rectangleShape.getGlobalBounds();
	sf::FloatRect collisionPoints;
	bool collisionTop = false, collisionBottom = false, collisionRight = false, collisionWithPaper = false;
	std::list<LevelBlock*>::iterator it;
	for (it = blocks.begin(); it != blocks.end(); it++)
	{
		collisionPoints = (*it)->getCollisionPoints();
		if (studentBounds.left <= collisionPoints.left + collisionPoints.width && studentBounds.left + studentBounds.width >= collisionPoints.left)
		{
			if (studentBounds.top + studentBounds.height >= collisionPoints.top && studentBounds.top <= collisionPoints.top + collisionPoints.height)
			{
				if (studentBounds.top + studentBounds.height >= collisionPoints.top + collisionPoints.height)
				{
					if ((*it)->getBlockType() != BlockType::PAPER)collisionTop = true; // collision from top
					else if ((*it)->getBlockType() == BlockType::PAPER && (*it)->action("catch") == false)
					{
						collisionWithPaper = true;
					}
				}
				else
				{
					if ((*it)->getBlockType() != BlockType::PAPER)collisionBottom = true; // collision from bottom;
					else if ((*it)->getBlockType() == BlockType::PAPER && (*it)->action("catch") == false)
					{
						collisionWithPaper = true;
					}
				}
				if (studentBounds.top + studentBounds.height > collisionPoints.top && (*it)->getBlockType() != BlockType::PAPER)
				{
					if (studentBounds.top + studentBounds.height - collisionPoints.top > 5)collisionRight = true;
					else
					{
						rectangleShape.move(0, -(studentBounds.top + studentBounds.height - collisionPoints.top));
					}
				}
			}
		}
	}
	if (collisionBottom == true && isFalling == true)
	{
		isFalling = false;//stop falling
		rectangleShape.setPosition((int)rectangleShape.getPosition().x, floor(rectangleShape.getPosition().y));
	}
	if (collisionBottom == false && isJumping == false)isFalling = true;//start falling
	if (collisionTop == true && isJumping == true)//when collide with top block stop jumping and start falling
	{
		isJumping = false;
		isFalling = true;
	}
	
	if (collisionRight == true)
	{
		//game over
		dispatchEvent(Event::COLLISION_RIGHT);
	}

	if (collisionWithPaper == true)
	{
		dispatchEvent(Event::CATCH_PAPER);
	}
}

void Student::handleInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))jump();
}
void Student::jump()
{
	if (isJumping == false && isFalling == false)
	{
		jumpHigh = 0.f;
		isJumping = true;
		rectangleShape.setTextureRect(sf::IntRect(160, 0, 48, 75));
		spriteFramesTime = sf::Time::Zero;
		currentFrame = 0;
	}
}
void Student::updateRunningSprite()
{
	spriteFramesTime += sf::seconds(TimeManager::getInstance()->getTime(TimeType::ELAPSED_TIME));
	if (spriteFramesTime.asSeconds() > 250)
	{
		spriteFramesTime = sf::Time::Zero;
		if (currentFrame == 3)currentFrame = 0;
		else currentFrame++;
		rectangleShape.setTextureRect(sf::IntRect(40 * currentFrame, 0, 38, 75));
	}
}
void Student::update()
{
	handleInput();
	if (isFalling == false && isJumping == false)updateRunningSprite();
	float jumpY = (float)TimeManager::getInstance()->getTime(TimeType::ELAPSED_TIME) / (1000.f / 120.f) * (3.5f);
	rectangleShape.move((float)TimeManager::getInstance()->getTime(TimeType::ELAPSED_TIME) / (1000.f / 120.f) * (1.f), 0);
	if (isFalling == true)
	{
		rectangleShape.move(0, floor((float)TimeManager::getInstance()->getTime(TimeType::ELAPSED_TIME) / (1000.f / 120.f) * (2.f)));
		int tempY = floor(rectangleShape.getPosition().y);
		//if (tempY % 5 != 0)rectangleShape.move(0, -1);
		if (rectangleShape.getPosition().y > Constants::WINDOW_HEIGHT)dispatchEvent(Event::COLLISION_RIGHT);
	}
	if (isJumping == true)
	{
		if (jumpHigh <= 125)
		{
			jumpHigh += jumpY;
			rectangleShape.move(0, floor(-jumpY));
		}
		else
		{
			isJumping = false;
		}
	}
}
void Student::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(rectangleShape, states);
}