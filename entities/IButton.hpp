#ifndef I_BUTTON_HPP
#define I_BUTTON_HPP

#include <SFML/Graphics.hpp>
#include "../SFMEngine/Eventable.hpp"
class IButton : public sf::Drawable, public Eventable, public sf::Transformable
{
protected:
	static enum Event
	{
		PRESSED,
		UNPRESSED,
		HOVER,
		UNHOVER
	};
	enum class State
	{
		NORMAL,
		ACTIVE,
		DISABLED
	};
	enum class ActionState
	{
		INACTIVE,
		HOVERED,
		PRESSED
	};
private:
	State currentState = State::NORMAL;
	ActionState currentActionState = ActionState::INACTIVE;
public:
	void update();
	void setState(State pState);
	void setActionState(ActionState pActionState);
	virtual bool isCollidedWithCursor(){ return false; };
	virtual void handleEffect(ActionState pState){};
	virtual void handleEffect(State pState){};
	virtual void handleEffect(Event pEvent){};
	void handleButtonEvent(Event pEvent);
};

#endif