#include "TimeManager.hpp"

TimeManager* TimeManager::p_instance = 0;

TimeManager* TimeManager::getInstance()
{
	if (!p_instance)
		p_instance = new TimeManager();
	return p_instance;
}

void TimeManager::init()
{
	clock = sf::Clock();
	setTime(clock.getElapsedTime().asMilliseconds(), TimeType::PREVIOUS_TIME);
	setTime(0, TimeType::LAG_TIME);
}

sf::Clock* TimeManager::getClock()
{
	return &clock;
}

void TimeManager::setTime(int timeValue, TimeType timeType)
{
	switch (timeType)
	{
	case TimeType::CURRENT_TIME:
		stepCurrentTime = timeValue;
		break;
	case TimeType::ELAPSED_TIME:
		stepElapsedTime = timeValue;
		break;
	case TimeType::LAG_TIME:
		stepLagTime = timeValue;
		break;
	case TimeType::PREVIOUS_TIME:
		stepPreviousTime = timeValue;
		break;
	}
}

int TimeManager::getTime(TimeType timeType)
{
	switch (timeType)
	{
	case TimeType::CURRENT_TIME:
		return stepCurrentTime;
		break;
	case TimeType::ELAPSED_TIME:
		return stepElapsedTime;
		break;
	case TimeType::LAG_TIME:
		return stepLagTime;
		break;
	case TimeType::PREVIOUS_TIME:
		return stepPreviousTime;
		break;
	}
}

void TimeManager::updateLoopData()
{
	setTime(this->clock.getElapsedTime().asMilliseconds(), TimeType::CURRENT_TIME);
	setTime(getTime(TimeType::CURRENT_TIME) - getTime(TimeType::PREVIOUS_TIME), TimeType::ELAPSED_TIME);
	setTime(getTime(TimeType::CURRENT_TIME), TimeType::PREVIOUS_TIME);
	setTime(getTime(TimeType::LAG_TIME) + getTime(TimeType::ELAPSED_TIME), TimeType::LAG_TIME);
}