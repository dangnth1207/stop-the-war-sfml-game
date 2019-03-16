#include "SoundManager.h"


SoundManager* SoundManager::_instance = nullptr;
SoundManager::SoundManager(void)
{
}


SoundManager::~SoundManager(void)
{
}
SoundManager* SoundManager::getInstance()
{
	if (_instance == nullptr)
		_instance = new SoundManager();
	return _instance;
}
void SoundManager::LoadSoundResources()
{
	m_explosionSoundBuffer.loadFromFile("Resources/Sounds/explosion.wav");
	m_explosionSound.setBuffer(m_explosionSoundBuffer);
}
void SoundManager::release()
{
	delete _instance;			// _instance is static attribute, only static function can delete it.
	_instance = nullptr;
}
void SoundManager::PlaySound(int eIDSound)
{
	switch (eIDSound)
	{
	case eIDSound::EXPLOSION_SOUND:
		m_explosionSound.play();
		break;
	case eIDSound::MENU_SOUND:
		m_menuSound.play();
		break;
	case eIDSound::GAME_PLAYING_SOUND:
		m_gamePlayingSound.play();
		break;
	}
}