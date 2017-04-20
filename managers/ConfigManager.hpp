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
	static ConfigManager* getInstance();
	void init();
	std::string get(std::string p_config);
	void set(std::string p_config, std::string p_newval);
	void rewriteConfig();
};
#endif