#include "I18nManager.hpp"

I18nManager* I18nManager::p_instance = 0;

I18nManager* I18nManager::getInstance()
{
	if (!p_instance)
		p_instance = new I18nManager();
	return p_instance;
}

void I18nManager::init()
{

}

void I18nManager::loadLocale(std::string p_localeName)
{
	currentLocale = p_localeName;
	INIFileParser parser("resources/locale/"+getLocaleFileName());
	phrases = parser.parse();
}

std::string I18nManager::getLocaleFileName()
{
	return currentLocale + ".locale";
}

std::string I18nManager::getText(std::string p_phrase)
{
	for (auto it = phrases.begin(); it != phrases.end(); ++it)
	{
		if ((*it).first == p_phrase)return (*it).second;
	}
	return "phrase not found";
}