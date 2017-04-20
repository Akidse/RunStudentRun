#include "ConfigManager.hpp"

ConfigManager* ConfigManager::p_instance = 0;

ConfigManager* ConfigManager::getInstance()
{
	if (!p_instance)
		p_instance = new ConfigManager();
	return p_instance;
}

void ConfigManager::init()
{
	INIFileParser parser("userdata/settings.dat");
	configs = parser.parse();
}

std::string ConfigManager::get(std::string p_config)
{
	for (auto it = configs.begin(); it != configs.end(); ++it)
	{
		if ((*it).first == p_config)return (*it).second;
	}
	return "null";
}

void ConfigManager::set(std::string p_config, std::string p_newval)
{
	configs.at(p_config) = p_newval;
	rewriteConfig();
}

void ConfigManager::rewriteConfig()
{
	std::ofstream file("userdata/settings.dat", std::ios_base::trunc);
	std::string tempString;
	for (auto it = configs.begin(); it != configs.end(); ++it)
	{
		tempString = '"' + (*it).first + '"' + " = " + '"' + (*it).second  + '"';
		file << tempString << std::endl;
	}
	file.close();
}