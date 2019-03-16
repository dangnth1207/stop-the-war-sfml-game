#pragma once
#include "../RenderGameObject.h"

class Bar :public RenderGameObject
{
private:
	float m_timePerFrame;
	float m_currentTime;
	int m_numFrames;
	int m_currentFrame;

	void CollisionWithScreenBound();

	bool m_isMovingLeft;
	bool m_isMovingRight;
public:
	Bar();
	Bar(int posX,int posY,int direction=RIGHT);
	~Bar();

	bool isMovingLeft();
	void SetMovingLeft(bool flag);

	bool isMovingRight();
	void SetMovingRight(bool flag);

	virtual void Init();
	virtual void Init(std::string);
	virtual sf::Sprite* GetSprite();
	virtual void Update(float);
	virtual void Render(sf::RenderWindow&);
};
