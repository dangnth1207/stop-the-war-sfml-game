#pragma once
#include "../RenderGameObject.h"
#include "../../GameControllers/Animation.h"
#include "Bullet.h"
class Army_Shotgun :public RenderGameObject
{
protected:
	Animation *m_movingAnim;
	Animation *m_movingFeetAnim;
	Animation *m_attackingAnim;

	Animation *m_Explosion;
	int m_HP;

	float m_distanceMove;
public:
	Army_Shotgun();
	~Army_Shotgun();

	void ChangeDirection();

	virtual sf::Sprite* GetSprite();
	virtual sf::Sprite* GetSpriteAnim();

	virtual void Init();


	virtual void Render(sf::RenderWindow &);
	virtual void Update(float deltime);
	virtual void Collision(RenderGameObject* collisionObject);

	virtual void SetDirection(int direction);
	void Scale();
};

