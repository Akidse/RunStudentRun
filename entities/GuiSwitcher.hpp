#ifndef GUI_SWITCHER_HPP
#define GUI_SWITCHER_HPP

#include <SFML/Graphics.hpp>
#include "../SFMEngine/Eventable.hpp"
#include <string>

class GuiSwitcher : public sf::Drawable, public sf::Transformable, public Eventable
{
	sf::Sprite sLeftArrow;
	sf::Sprite sRightArrow;
	sf::Text text;
	sf::Texture& tLeftArrow;
	sf::Texture& tRightArrow;
	sf::Vector2f position;
	float leftLimit, rightLimit, step;
	float currentLimit;
	int currentValue;
	float activeSwitcherValue;
	float* values;
	bool isValuableLimit;
	int valuesSize;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	int GuiSwitcher::isCollised();
	void updateText();
public:
	static enum Event
	{
		PRESSED,
		UNPRESSED,
		HOVER,
		UNHOVER,
		INCREASE_VALUE,
		DECREASE_VALUE
	};
	enum class State
	{
		INACTIVE,
		PRESSED,
		HOVERED
	};
	State currentState;
	void resize(float factor = 1, float arrow = 0);
	void place();
	GuiSwitcher(sf::Texture& pleftArrow, sf::Texture& prightArrow, sf::Font& pFont, sf::Vector2f pPosition);
	void setSwitchableValues(float* pValues, int valuesSize);
	void setSwitchableLimits(float pLeftLimit, float pRightLimit, float pStep);
	void update();
	void decreaseValue();
	void increaseValue();
	float getCurrentValue();
	void normalEffect();
	void pressedEffect(float arrow);
};
#endif