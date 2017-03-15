#ifndef I18N_MANAGER_HPP
#define I18N_MANAGER_HPP
#include <string>
#include <map>
#include "../utilities/INIFileParser.hpp"
class I18nManager
{
private:
	std::string getLocaleFileName();
	std::string currentLocale;
	std::map<std::string, std::string> phrases;
	static I18nManager* p_instance;
	I18nManager(){};
	I18nManager(const I18nManager&);
	I18nManager& operator = (I18nManager&);
public:
	static I18nManager* getInstance();
	void init();
	void loadLocale(std::string p_localeName);
	std::string getText(std::string p_phrase);
};
#endif