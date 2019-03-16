#include "GameTime.h"

GameTime *GameTime::mInstance = NULL;

GameTime::GameTime()
{

}

GameTime::~GameTime()
{
}

GameTime* GameTime::GetInstance()
{
	if (!mInstance)
		mInstance = new GameTime();

	return mInstance;

}

void GameTime::StartCounter()
{
	m_StartTime = clock()/1000.0;
}

float GameTime::GetTimeInSecond()
{
	
	return clock()/1000.0;
}

float GameTime::GetStartTime()
{
	return m_StartTime;

}
