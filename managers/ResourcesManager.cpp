#include "ResourcesManager.hpp"
#include "../managers/SceneManager.hpp"

ResourcesManager* ResourcesManager::p_instance = 0;

ResourcesManager* ResourcesManager::getInstance()
{
	if (!p_instance)
		p_instance = new ResourcesManager();
	return p_instance;
}

void ResourcesManager::init()
{
	globalSoundVolume = 100;
	globalMusicVolume = 100;
	loadLoadingResources();
}

void ResourcesManager::chooseSceneAction(SceneType p_scene, Action p_action)
{
	switch (p_scene)
	{
	case SceneType::INTRO:
		if (p_action == Action::LOAD_RESOURCES)loadIntroResources();
		if (p_action == Action::UNLOAD_RESOURCES)unloadIntroResources();
		if (p_action == Action::SOUND_VOLUME)volumeIntroSound();
		if (p_action == Action::MUSIC_VOLUME)volumeIntroMusic();
		break;
	case SceneType::MENU:
		if (p_action == Action::LOAD_RESOURCES)loadMenuResources();
		if (p_action == Action::UNLOAD_RESOURCES)unloadMenuResources();
		if (p_action == Action::SOUND_VOLUME)volumeMenuSound();
		if (p_action == Action::MUSIC_VOLUME)volumeMenuMusic();
		break;
	}
}
void ResourcesManager::loadResources(SceneType p_scene)
{
	chooseSceneAction(p_scene, Action::LOAD_RESOURCES);
}

void ResourcesManager::unloadResources(SceneType p_scene)
{
	chooseSceneAction(p_scene, Action::UNLOAD_RESOURCES);
}

void ResourcesManager::setGlobalSoundVolume(int p_volume)
{
	globalSoundVolume = p_volume;
	chooseSceneAction(SceneManager::getInstance()->getCurrentSceneType(), Action::SOUND_VOLUME);
}

void ResourcesManager::setGlobalMusicVolume(int p_volume)
{
	globalMusicVolume = p_volume;
	chooseSceneAction(SceneManager::getInstance()->getCurrentSceneType(), Action::MUSIC_VOLUME);
}

void ResourcesManager::loadIntroResources()
{
	logoImage = new sf::Image();
	logoImage->loadFromFile("resources/gfx/logo.png");

	logoTexture = new sf::Texture();
	logoTexture->loadFromImage(*logoImage);

	logoTexture->setSmooth(true);

	logoShader = new sf::Shader();
	logoShader->loadFromFile("resources/shaders/logoShader.frag", sf::Shader::Fragment);
}
void ResourcesManager::unloadIntroResources()
{
	delete logoTexture;
	delete logoImage;
	delete logoShader;
}

void ResourcesManager::loadMenuResources()
{
	menuBackground = new sf::Image();
	menuBackground->loadFromFile("resources/gfx/mainmenu.png");

	menuBackgroundTexture = new sf::Texture();
	menuBackgroundTexture->loadFromImage(*menuBackground);
	menuBackgroundTexture->setSmooth(false);

	menuButtonTexture = new sf::Texture();
	menuButtonTexture->loadFromFile("resources/gfx/menubutton_2.png");
	menuButtonTexture->setSmooth(false);

	menuLeftArrowTexture = new sf::Texture();
	menuLeftArrowTexture->loadFromFile("resources/gfx/leftArrow.png");
	menuLeftArrowTexture->setSmooth(false);

	menuRightArrowTexture = new sf::Texture();
	menuRightArrowTexture->loadFromFile("resources/gfx/rightArrow.png");
	menuRightArrowTexture->setSmooth(false);

	menuMusic = new sf::Music();
	menuMusic->openFromFile("resources/music/menu_stressedout.ogg");
	menuMusic->setVolume(globalMusicVolume);

	menuFont = new sf::Font();
	menuFont->loadFromFile("resources/fonts/menu.ttf");
}
void ResourcesManager::unloadMenuResources()
{
	delete menuBackground;
	delete menuBackgroundTexture;
	delete menuLeftArrowTexture;
	delete menuRightArrowTexture;
	delete menuButtonTexture;
	delete menuMusic;
	delete menuFont;
}

void ResourcesManager::loadLoadingResources(){}


void ResourcesManager::volumeIntroSound(){}
void ResourcesManager::volumeIntroMusic(){}

void ResourcesManager::volumeMenuSound(){}
void ResourcesManager::volumeMenuMusic()
{
	menuMusic->setVolume(globalMusicVolume);
}