#pragma once
#include "Objects/RenderGameObject.h"
#include "Animation.h"
#include "Objects/RenderGameObject.h"
class Lazer :public RenderGameObject
{
protected:
	Animation *m_lazerAnim;

public:
	Lazer();
	~Lazer();

	virtual sf::Sprite* GetSprite();
	virtual sf::Sprite* GetSpriteAnim();

	virtual void Init();


	virtual void Render(sf::RenderWindow &);
	virtual void Update(float deltime);
	virtual void Collision(RenderGameObject* collisionObject);

	void Scale();
};

