#ifndef TIME_MANAGER_HPP
#define TIME_MANAGER_HPP

#include <SFML/Graphics.hpp>
#include "../SFMEngine/TimeType.hpp"

class TimeManager
{
private:
	static TimeManager* p_instance;
	TimeManager(){};
	TimeManager(const TimeManager&);
	TimeManager& operator = (TimeManager&);
	int stepPreviousTime, stepLagTime, stepCurrentTime, stepElapsedTime;
	sf::Clock clock;
public:
	static TimeManager* getInstance();
	void init();
	sf::Clock* getClock();
	void setTime(int timeValue, TimeType timeType);
	int getTime(TimeType timeType);
	void updateLoopData();
};
#endif