#pragma once
#include "../RenderGameObject.h"
#include "../../GameControllers/SoundManager.h"
class Bullet :public RenderGameObject
{
protected:
	Animation *m_movingAnim;
	Animation *m_attackingAnim;

	Animation *m_Explosion;

	int m_HP;
	float m_timeToActive;
public:
	Bullet();
	~Bullet();

	bool m_isFail = false;
	virtual void Init();


	virtual void Render(sf::RenderWindow &);
	virtual void Update(float deltime);
	virtual void Collision(RenderGameObject* collisionObject);

	virtual void SetDirection(int direction);
	void Scale();
};

