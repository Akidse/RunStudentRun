#ifndef LEVEL_BUTTON_HPP
#define LEVEL_BUTTON_HPP

#include "IButton.hpp"
class LevelButton : public IButton
{
	sf::Font& mFont;
	sf::Text mLevelText, mCollectionText;
	sf::RectangleShape mRectangleShape;
	int mLevelNumber;
	int mLevelCollectedNumber, mLevelFullCollectionNumber;
public:
	bool isCollidedWithCursor();
	LevelButton(sf::Vector2f pPosition, sf::Font& pFont);
	void normalEffect();
	void pressedEffect();
	void disabledEffect();
	void setLevelStats(int pLevelNumber, int pLevelCollectedNumber, int pLeelFullCollectionNumber);
	void updateText();
	void handleEffect(ActionState pState){};
	void handleEffect(State pState);
	void handleEffect(Event pEvent);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::Vector2i mousePosition;
	sf::Vector2f mappedMousePosition;
	sf::Vector2f transformedMousePosition;
};
#endif