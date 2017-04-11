#ifndef RESOURCES_MANAGER_HPP
#define RESOURCES_MANAGER_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../SFMEngine/SceneType.hpp"
class ResourcesManager
{
private:
	enum class Action
	{
		LOAD_RESOURCES,
		UNLOAD_RESOURCES,
		SOUND_VOLUME,
		MUSIC_VOLUME
	};
	bool isAudioMuted;
	int globalSoundVolume;
	int globalMusicVolume;
	static ResourcesManager* p_instance;
	ResourcesManager(){};
	ResourcesManager(const ResourcesManager&);
	ResourcesManager& operator = (ResourcesManager&);
	void chooseSceneAction(SceneType p_sceneType, Action p_action);
public:
	static ResourcesManager* getInstance();
	void init();

	void loadResources(SceneType p_scene);
	void loadIntroResources();
	void loadMenuResources();
	void loadLoadingResources();
	void unloadResources(SceneType p_scene);
	void unloadIntroResources();
	void unloadMenuResources();

	void volumeIntroSound();
	void volumeIntroMusic();
	void volumeMenuSound();
	void volumeMenuMusic();
	
	void setGlobalSoundVolume(int p_volume);
	void setGlobalMusicVolume(int p_volume);


	sf::Image* logoImage;
	sf::Texture* logoTexture;
	sf::Shader* logoShader;

	sf::Image* menuBackground;
	sf::Texture* menuBackgroundTexture;
	sf::Texture* menuButtonTexture;
	sf::Texture* menuLeftArrowTexture;
	sf::Texture* menuRightArrowTexture;
	sf::Music* menuMusic;
	sf::Font* menuFont;
};
#endif