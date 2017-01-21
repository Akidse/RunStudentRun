#include "LocalizationManager.hpp"

LocalizationManager* LocalizationManager::p_instance = 0;

LocalizationManager* LocalizationManager::getInstance()
{
	if (!p_instance)
		p_instance = new LocalizationManager();
	return p_instance;
}

void LocalizationManager::init()
{

}