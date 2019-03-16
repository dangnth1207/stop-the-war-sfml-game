#pragma once
#include "SFML/Audio.hpp"
#include "../GameControllers/define.h"
class SoundManager
{
public:
	static SoundManager* getInstance();
	static void release();
	void LoadSoundResources();

	void PlaySound(int eIDSound);

	~SoundManager(void);


private:
	SoundManager(void);
	sf::SoundBuffer m_menuSoundBuffer;
	sf::SoundBuffer m_gamePlayingSoundBuffer;
	sf::SoundBuffer m_explosionSoundBuffer;

	sf::Sound m_menuSound;
	sf::Sound m_gamePlayingSound;
	sf::Sound m_explosionSound;
	static SoundManager* _instance;
	

};