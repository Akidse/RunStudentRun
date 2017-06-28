#include "LevelButton.hpp"
#include <string>
#include "../managers/SceneManager.hpp"

LevelButton::LevelButton(sf::Vector2f pPosition, sf::Font& pFont)
	:mFont(pFont)
{
	mRectangleShape.setPosition(pPosition);
	mRectangleShape.setSize(sf::Vector2f(100.f, 100.f));

	mLevelNumber = 1;
	mLevelCollectedNumber = 0;
	mLevelFullCollectionNumber = 10;

	mLevelText.setFont(mFont);
	mLevelText.setCharacterSize(80);

	mCollectionText.setFont(mFont);
	mCollectionText.setCharacterSize(30);

	normalEffect();

	mLevelText.setString(std::to_string(mLevelNumber));
	mCollectionText.setString(std::to_string(mLevelCollectedNumber) + '/' + std::to_string(mLevelFullCollectionNumber));
	
	updateText();
}

void LevelButton::setLevelStats(int pLevelNumber, int pLevelCollectedNumber, int pLeelFullCollectionNumber)
{
	mLevelNumber = pLevelNumber;
	mLevelCollectedNumber = pLevelCollectedNumber;
	mLevelFullCollectionNumber = pLeelFullCollectionNumber;

	mLevelText.setString(std::to_string(mLevelNumber));

	mCollectionText.setString(std::to_string(mLevelCollectedNumber) + '/' + std::to_string(mLevelFullCollectionNumber));

	updateText();
	normalEffect();
}

void LevelButton::updateText()
{
	mLevelText.setOrigin(mLevelText.getLocalBounds().left + mLevelText.getLocalBounds().width / 2.f, mLevelText.getLocalBounds().top + mLevelText.getLocalBounds().height / 2.f);
	mLevelText.setPosition(mRectangleShape.getPosition().x + mRectangleShape.getGlobalBounds().width / 2,
		mRectangleShape.getPosition().y + mRectangleShape.getGlobalBounds().height / 2);

	mCollectionText.setOrigin(mCollectionText.getLocalBounds().left + mCollectionText.getLocalBounds().width / 2.f, mCollectionText.getLocalBounds().top + mCollectionText.getLocalBounds().height / 2.f);
	mCollectionText.setPosition(mRectangleShape.getPosition().x + mRectangleShape.getGlobalBounds().width / 2.f,
		mRectangleShape.getPosition().y + mRectangleShape.getGlobalBounds().height + 20);

}

void LevelButton::normalEffect()
{
	
	if (mLevelCollectedNumber  < mLevelFullCollectionNumber / 2)
	{
		mRectangleShape.setFillColor(sf::Color(228, 176, 184));
		mLevelText.setFillColor(sf::Color::White);
		mCollectionText.setFillColor(sf::Color(228, 176, 184));
	}
	else if (mLevelCollectedNumber < mLevelFullCollectionNumber)
	{
		mRectangleShape.setFillColor(sf::Color(233, 228, 180));
		mLevelText.setFillColor(sf::Color::White);
		mCollectionText.setFillColor(sf::Color(233, 228, 180));
	}
	else
	{
		mRectangleShape.setFillColor(sf::Color(172, 222, 202));
		mLevelText.setFillColor(sf::Color::White);
		mCollectionText.setFillColor(sf::Color(172, 222, 202));
	}
}

void LevelButton::pressedEffect()
{
	if (mLevelCollectedNumber  < mLevelFullCollectionNumber / 2)
	{
		mRectangleShape.setFillColor(sf::Color(210, 119, 133));
		mLevelText.setFillColor(sf::Color::White);
		mCollectionText.setFillColor(sf::Color(228, 176, 184));
	}
	else if (mLevelCollectedNumber < mLevelFullCollectionNumber)
	{
		mRectangleShape.setFillColor(sf::Color(215, 207, 120));
		mLevelText.setFillColor(sf::Color::White);
		mCollectionText.setFillColor(sf::Color(233, 228, 180));
	}
	else
	{
		mRectangleShape.setFillColor(sf::Color(118, 201, 166));
		mLevelText.setFillColor(sf::Color::White);
		mCollectionText.setFillColor(sf::Color(172, 222, 202));
	}
}

void LevelButton::disabledEffect()
{
	mRectangleShape.setFillColor(sf::Color(201, 201, 201));
	mLevelText.setFillColor(sf::Color::White);
	mCollectionText.setFillColor(sf::Color(201, 201, 201));
	mCollectionText.setString("xx/xx");
}

void LevelButton::handleEffect(Event pEvent)
{
	switch (pEvent)
	{
	case Event::PRESSED:
		pressedEffect();
		break;
	case Event::UNPRESSED:
		normalEffect();
		break;
	case Event::UNHOVER:
		normalEffect();
		break;
	}
}

void LevelButton::handleEffect(State pState)
{
	switch (pState)
	{
	case State::DISABLED:
		disabledEffect();
		break;
	}
}

bool LevelButton::isCollidedWithCursor()
{
	mousePosition = sf::Mouse::getPosition(*SceneManager::getInstance()->getWindow());
	mappedMousePosition = SceneManager::getInstance()->getWindow()->mapPixelToCoords(mousePosition);
	transformedMousePosition = mRectangleShape.getInverseTransform().transformPoint(mappedMousePosition);
	if (mRectangleShape.getLocalBounds().contains(transformedMousePosition))
		return true;
	return false;
}

void LevelButton::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(mRectangleShape, states);
	target.draw(mLevelText, states);
	target.draw(mCollectionText, states);
}