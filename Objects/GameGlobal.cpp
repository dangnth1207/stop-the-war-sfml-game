#include "GameGlobal.h"

GameGlobal* GameGlobal::_instance = nullptr;
GameGlobal::GameGlobal(void)
{
	// do nothing.
}
GameGlobal::~GameGlobal(void)
{

}

void GameGlobal::release()
{
	delete _instance;			// _instance is static attribute, only static function can delete it.
	_instance = nullptr;
}

GameGlobal* GameGlobal::getInstance()
{
	if (_instance == nullptr)
		_instance = new GameGlobal();
	return _instance;
}


int GameGlobal::GetScore()
{
	return m_score;
 }
void GameGlobal::SetScore(int score)
{
	m_score = score;
 }
int GameGlobal::GetHealth()
{
	return m_health;
 }
void GameGlobal::SetHealth(int health)
{
	m_health = health;
 }


void GameGlobal::SetSoundEffect(bool isSound) {
	
	 m_isSoundEffect = isSound;
}

bool GameGlobal::GetSoundEffect() {
	return m_isSoundEffect;
}
