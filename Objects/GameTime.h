#pragma once
#include <ctime>
#include <iostream>
#include <chrono>
class GameTime
{
public:
	void StartCounter();
	float GetTimeInSecond();
	float GetStartTime();
	static GameTime* GetInstance();
	~GameTime();

private:
	GameTime();
	float m_StartTime, m_EndTime, m_Delta, m_ClockRate;
	static GameTime *mInstance;

};

