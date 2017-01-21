#ifndef LOCALIZATION_MANAGER_HPP
#define LOCALIZATION_MANAGER_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../SFMEngine/SceneType.hpp"
class LocalizationManager
{
private:
	static LocalizationManager* p_instance;
	LocalizationManager(){};
	LocalizationManager(const LocalizationManager&);
	LocalizationManager& operator = (LocalizationManager&);
public:
	static LocalizationManager* getInstance();
	void init();
};
#endif