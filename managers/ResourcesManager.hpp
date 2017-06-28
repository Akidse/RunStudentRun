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
	void loadGameResources();
	void unloadResources(SceneType p_scene);
	void unloadIntroResources();
	void unloadMenuResources();
	void unloadGameResources();

	void volumeIntroSound();
	void volumeIntroMusic();
	void volumeMenuSound();
	void volumeMenuMusic();
	void volumeGameSound();
	void volumeGameMusic();
	
	void setGlobalSoundVolume(int p_volume);
	void setGlobalMusicVolume(int p_volume);
	int getGlobalSoundVolume();
	int getGlobalMusicVolume();


	sf::Image* logoImage;
	sf::Texture* logoTexture;
	sf::Shader* logoShader;

	sf::Image* menuBackground;
	sf::Texture* menuBackgroundTexture;
	sf::Texture* menuButtonTexture;
	sf::Texture* menuLeftArrowTexture;
	sf::Texture* menuRightArrowTexture;
	sf::Texture* menuLangButtonEnTexture;
	sf::Texture* menuLangButtonUkTexture;
	sf::Texture* menuLangButtonRuTexture;
	sf::Texture* menuAboutTexture;
	sf::Texture* gameBackgroundTop;
	sf::Texture* gameBlock1;
	sf::Texture* gameBlock2;
	sf::Texture* gameBlock1_top;
	sf::Texture* gameBlock1_bottom;
	sf::Texture* gameStudentRunningSprite;
	sf::Music* menuMusic;
	sf::Music* gameMusic;
	sf::SoundBuffer* gameSoundLoseBuffer;
	sf::SoundBuffer* gameSoundWinBuffer;
	sf::SoundBuffer* gameSoundCollectBuffer;
	sf::Sound* gameCollect;
	sf::Sound* gameLose;
	sf::Sound* gameWin;
	sf::Font* menuFont;
	sf::Font* gameFont;
};
#endif