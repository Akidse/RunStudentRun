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
	case SceneType::GAME:
		if (p_action == Action::LOAD_RESOURCES)loadGameResources();
		if (p_action == Action::UNLOAD_RESOURCES)unloadGameResources();
		if (p_action == Action::SOUND_VOLUME)volumeGameSound();
		if (p_action == Action::MUSIC_VOLUME)volumeGameMusic();
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

int ResourcesManager::getGlobalSoundVolume()
{
	return globalSoundVolume;
}

int ResourcesManager::getGlobalMusicVolume()
{
	return globalMusicVolume;
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

	menuLangButtonEnTexture = new sf::Texture();
	menuLangButtonEnTexture->loadFromFile("resources/gfx/langbutton_en.png");
	menuLangButtonEnTexture->setSmooth(false);

	menuLangButtonUkTexture = new sf::Texture();
	menuLangButtonUkTexture->loadFromFile("resources/gfx/langbutton_uk.png");
	menuLangButtonUkTexture->setSmooth(false);

	menuLangButtonRuTexture = new sf::Texture();
	menuLangButtonRuTexture->loadFromFile("resources/gfx/langbutton_ru.png");
	menuLangButtonRuTexture->setSmooth(false);

	menuAboutTexture = new sf::Texture();
	menuAboutTexture->loadFromFile("resources/gfx/student_dog.png");
	menuAboutTexture->setSmooth(false);

	menuMusic = new sf::Music();
	menuMusic->openFromFile("resources/music/menu_stressedout.ogg");
	menuMusic->setVolume(globalMusicVolume);

	menuFont = new sf::Font();
	menuFont->loadFromFile("resources/fonts/pixel_font3.ttf");
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

void ResourcesManager::loadGameResources()
{
	gameBackgroundTop = new sf::Texture();
	gameBackgroundTop->loadFromFile("resources/gfx/1_top.png");
	gameBackgroundTop->setSmooth(false);

	gameBlock1 = new sf::Texture();
	gameBlock1->loadFromFile("resources/gfx/block_5.png");
	gameBlock1->setSmooth(false);

	gameBlock1_top = new sf::Texture();
	gameBlock1_top->loadFromFile("resources/gfx/block_6_top.png");
	gameBlock1_top->setSmooth(false);

	gameBlock1_bottom = new sf::Texture();
	gameBlock1_bottom->loadFromFile("resources/gfx/block_6_bottom.png");
	gameBlock1_bottom->setSmooth(false);

	gameBlock2 = new sf::Texture();
	gameBlock2->loadFromFile("resources/gfx/block_4.png");
	gameBlock2->setSmooth(false);

	gameStudentRunningSprite = new sf::Texture();
	gameStudentRunningSprite->loadFromFile("resources/gfx/student_run.png");
	gameStudentRunningSprite->setSmooth(false);

	gameMusic = new sf::Music();
	gameMusic->openFromFile("resources/music/game_lane.ogg");
	gameMusic->setVolume(globalMusicVolume);

	gameSoundLoseBuffer = new sf::SoundBuffer;
	gameSoundLoseBuffer->loadFromFile("resources/music/game_lose.ogg");

	gameSoundWinBuffer = new sf::SoundBuffer;
	gameSoundWinBuffer->loadFromFile("resources/music/game_win.ogg");

	gameSoundCollectBuffer = new sf::SoundBuffer;
	gameSoundCollectBuffer->loadFromFile("resources/music/game_collect.ogg");

	gameLose = new sf::Sound();
	gameLose->setBuffer(*gameSoundLoseBuffer);
	gameLose->setVolume(globalSoundVolume);

	gameWin = new sf::Sound();
	gameWin->setBuffer(*gameSoundWinBuffer);
	gameWin->setVolume(globalSoundVolume);

	gameCollect = new sf::Sound;
	gameCollect->setBuffer(*gameSoundCollectBuffer);
	gameCollect->setVolume(globalSoundVolume);

	gameFont = new sf::Font();
	gameFont->loadFromFile("resources/fonts/pixel_font3.ttf");
}
void ResourcesManager::unloadGameResources()
{
	delete gameBackgroundTop;
	delete gameBlock1;
	delete gameBlock1_top;
	delete gameBlock1_bottom;
	delete gameBlock2;
	delete gameStudentRunningSprite;
	delete gameFont;
	delete gameLose;
	delete gameWin;
	delete gameCollect;
	delete gameMusic;
	delete gameSoundCollectBuffer;
	delete gameSoundLoseBuffer;
	delete gameSoundWinBuffer;
}

void ResourcesManager::volumeGameSound(){}
void ResourcesManager::volumeGameMusic(){}

void ResourcesManager::volumeIntroSound(){}
void ResourcesManager::volumeIntroMusic(){}

void ResourcesManager::volumeMenuSound(){}
void ResourcesManager::volumeMenuMusic()
{
	menuMusic->setVolume(globalMusicVolume);
}

