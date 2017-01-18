#ifndef RESOURCES_MANAGER_HPP
#define RESOURCES_MANAGER_HPP

#include <SFML/Graphics.hpp>
#include "../SFMEngine/SceneType.hpp"
class ResourcesManager
{
private:
	static ResourcesManager* p_instance;
	ResourcesManager(){};
	ResourcesManager(const ResourcesManager&);
	ResourcesManager& operator = (ResourcesManager&);
public:
	static ResourcesManager* getInstance();

	void loadResources(SceneType p_scene);
	void loadIntroResources();
	void loadMenuResources();
	void unloadResources(SceneType p_scene);
	void unloadIntroResources();
	void unloadMenuResources();


	sf::Image* logoImage;
	sf::Texture* logoTexture;
	sf::Shader logoShader;
};
#endif