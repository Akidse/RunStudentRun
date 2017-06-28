#ifndef CONFIG_MANAGER_HPP
#define CONFIG_MANAGER_HPP
#include <string>
#include <map>
#include "../utilities/INIFileParser.hpp"
class ConfigManager
{
private:
	std::map<std::string, std::string> configs;
	static ConfigManager* p_instance;
	ConfigManager(){};
	ConfigManager(const ConfigManager&);
	ConfigManager& operator = (ConfigManager&);
public:
	int currentGameLevel = 1;
	bool openLevelLayer = false;
	int getCurrentGameLevel();
	void setCurrentGameLevel(int levelNumber);
	static ConfigManager* getInstance();
	void init();
	std::string get(std::string p_config);
	void set(std::string p_config, std::string p_newval);
	void rewriteConfig();
};
#endif