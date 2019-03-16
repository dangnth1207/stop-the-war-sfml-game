#pragma once
#include "Objects\Monster.h"
class SpecialMonster :public Monster
{
private:
	Bar* m_bar2;
public:
	SpecialMonster();
	~SpecialMonster();
	SpecialMonster(float posX, float posY, int direction = Direction::DOWN, std::string filePath = "");

	virtual void Init();
	virtual void Render(sf::RenderWindow &);
	virtual void Update(float deltime);
	virtual sf::Sprite* GetSprite();
	virtual void Init(std::string filePath);
	virtual void CollisionWithScreenBound();
	virtual void SetTwoBar(Bar *bar1, Bar *bar2);
	void SetBar(Bar *bar);
};

