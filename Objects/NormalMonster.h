#pragma once
#include "Objects\Monster.h"
class NormalMonster:public Monster
{
public:
	NormalMonster();
	~NormalMonster();
	NormalMonster(float posX, float posY, int direction = Direction::DOWN, std::string filePath = "");
	
	virtual void Init();
	virtual void Render(sf::RenderWindow &);
	virtual void Update(float deltime);
	virtual sf::Sprite* GetSprite();
	virtual void Init(std::string filePath);
	virtual void CollisionWithScreenBound();
	virtual void SetTwoBar(Bar *bar1, Bar *bar2);
	void SetBar(Bar *bar);
};

