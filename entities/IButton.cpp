#include "IButton.hpp"

void IButton::update()
{
	if (currentState == State::NORMAL)
	{
		if (isCollidedWithCursor())
		{
			if (currentActionState == ActionState::INACTIVE && !sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				//hovered
				handleButtonEvent(Event::HOVER);
				setActionState(ActionState::HOVERED);
			}
			else if(currentActionState == ActionState::HOVERED && sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				//pressed
				handleButtonEvent(Event::PRESSED);
				setActionState(ActionState::PRESSED);
			}
			else if (currentActionState == ActionState::PRESSED && !sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				//unpressed
				handleButtonEvent(Event::UNPRESSED);
				//setState(State::ACTIVE);
				setActionState(ActionState::HOVERED);
			}
		}
		else
		{
			if (currentActionState == ActionState::HOVERED)
			{
				//unhovered
				handleButtonEvent(Event::UNHOVER);
				setActionState(ActionState::INACTIVE);
			}
			else if (currentActionState == ActionState::PRESSED && !sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				//unhovered
				handleButtonEvent(Event::UNHOVER);
				setActionState(ActionState::INACTIVE);
			}
		}
	}
}

void IButton::setState(State pState)
{
	currentState = pState;
	handleEffect(pState);
}

void IButton::setActionState(ActionState pActionState)
{
	currentActionState = pActionState;
	handleEffect(pActionState);
}

void IButton::handleButtonEvent(Event pEvent)
{
	dispatchEvent(pEvent);
	handleEffect(pEvent);
}