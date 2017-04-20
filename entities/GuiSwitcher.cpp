#include "GuiSwitcher.hpp"
#include "../managers/SceneManager.hpp"
#include <iostream>
GuiSwitcher::GuiSwitcher(sf::Texture& pLeftArrow, sf::Texture& pRightArrow, sf::Font& pFont, sf::Vector2f pPosition)
	:
	tLeftArrow(pLeftArrow),
	tRightArrow(pRightArrow)
{
	currentValue = 0;
	sLeftArrow = sf::Sprite(pLeftArrow);
	sRightArrow = sf::Sprite(pRightArrow);
	isValuableLimit = false;
	leftLimit = 0;
	rightLimit = 10;
	step = 1;

	text = sf::Text(std::to_string((int)rightLimit), pFont, 30);
	text.setFillColor(sf::Color::Black);

	position = pPosition;
	
	resize();

	place();

	currentState = State::INACTIVE;
}

void GuiSwitcher::resize(float factor, float arrow)
{
	if(arrow == 1 || arrow == 0)sLeftArrow.setScale(40 * factor / sLeftArrow.getLocalBounds().width, 40 * factor / sLeftArrow.getLocalBounds().width);
	if(arrow == 2 || arrow == 0)sRightArrow.setScale(40 * factor / sRightArrow.getLocalBounds().width, 40 * factor / sRightArrow.getLocalBounds().width);
}

void GuiSwitcher::place()
{
	sLeftArrow.setPosition(position.x, position.y);
	text.setOrigin(text.getLocalBounds().left + text.getLocalBounds().width / 2.0f, text.getLocalBounds().top + text.getLocalBounds().height / 2.0f);
	text.setPosition(position.x + sLeftArrow.getGlobalBounds().width + 30, position.y + sLeftArrow.getGlobalBounds().height/2);
	sRightArrow.setPosition(text.getGlobalBounds().left + text.getGlobalBounds().width/2 + 30, position.y);
}
void GuiSwitcher::setSwitchableValues(float* pValues, int pValuesSize)
{
	isValuableLimit = true;
	values = pValues;
	valuesSize = pValuesSize;
}
void GuiSwitcher::pressedEffect(float arrow)
{
	resize(0.95, arrow);
}
void GuiSwitcher::normalEffect()
{
	resize();
}
void GuiSwitcher::setSwitchableLimits(float pLeftLimit, float pRightLimit, float pStep)
{
	isValuableLimit = false;
	leftLimit = pLeftLimit;
	rightLimit = pRightLimit;
	step = pStep;
	currentLimit = rightLimit;
}
void GuiSwitcher::setCurrentValue(int value)
{
	if (!isValuableLimit)
	{
		currentLimit = value;
		updateText();
	}
}
void GuiSwitcher::decreaseValue()
{
	if (isValuableLimit)
	{
		if (currentValue > 0)currentValue -= 1;
	}
	else
	{
		if (currentLimit > leftLimit)currentLimit -= step;
	}
	updateText();
	dispatchEvent(Event::DECREASE_VALUE);
}
void GuiSwitcher::increaseValue()
{
	if (isValuableLimit)
	{
		if (currentValue < valuesSize)currentValue += 1;
	}
	else
	{
		if (currentLimit < rightLimit)currentLimit += step;
	}
	updateText();
	dispatchEvent(Event::INCREASE_VALUE);
}
float GuiSwitcher::getCurrentValue()
{
	if (isValuableLimit)
	{
		return values[currentValue];
	}
	else
	{
		return currentLimit;
	}
}
void GuiSwitcher::updateText()
{
	text.setString(std::to_string((int)getCurrentValue()));
	place();
}
int GuiSwitcher::isCollised()
{
	sf::Vector2i mousePosition = sf::Mouse::getPosition(*SceneManager::getInstance()->getWindow());
	sf::Vector2f mappedMousePosition = SceneManager::getInstance()->getWindow()->mapPixelToCoords(mousePosition);
	sf::Vector2f transformedMousePositionOnLeftArrow = sLeftArrow.getInverseTransform().transformPoint(mappedMousePosition);
	sf::Vector2f transformedMousePositionOnRightArrow = sRightArrow.getInverseTransform().transformPoint(mappedMousePosition);

	if (sLeftArrow.getLocalBounds().contains(transformedMousePositionOnLeftArrow))
		return 1;
	else if (sRightArrow.getLocalBounds().contains(transformedMousePositionOnRightArrow))
		return 2;
	else
		return 0;
}
void GuiSwitcher::update()
{
	switch (isCollised())
	{
	case 0:
		currentState = State::INACTIVE;
		normalEffect();
		break;
	case 1:
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && currentState == State::INACTIVE)
		{
			currentState = State::INACTIVE;
			normalEffect();
		}
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && currentState != State::PRESSED)
		{
			decreaseValue();
			currentState = State::PRESSED;
			pressedEffect(1);
		}
		else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && currentState == State::PRESSED)
		{
			currentState = State::HOVERED;
			normalEffect();
		}
		else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			currentState = State::HOVERED;
			normalEffect();
		}
		break;
	case 2:
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && currentState == State::INACTIVE)
		{
			currentState = State::INACTIVE;
			normalEffect();
		}
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && currentState != State::PRESSED)
		{
			increaseValue();
			currentState = State::PRESSED;
			pressedEffect(2);
		}
		else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && currentState == State::PRESSED)
		{
			currentState = State::HOVERED;
			normalEffect();
		}
		else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			currentState = State::HOVERED;
			normalEffect();
		}
		break;
	}
}
void GuiSwitcher::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sLeftArrow, states);
	target.draw(text, states);
	target.draw(sRightArrow, states);
}