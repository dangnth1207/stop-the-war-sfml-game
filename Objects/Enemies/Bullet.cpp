
#include "Bullet.h"



Bullet::Bullet()
{

}


Bullet::~Bullet()
{
	
	delete m_movingAnim;
	delete m_Explosion;
}


void Bullet::Init()
{
	m_movingAnim = new Animation(eID::EXPLOSION, 1, "Explosion", 0.01f);
	m_Explosion = new Animation(eID::EXPLOSION, 24, "Explosion", 0.01f);

	m_currentAnim = m_movingAnim;



	//Scale();
	m_speed = BULLET_SPEED;
	m_position = sf::Vector2f(0, 0);
	m_HP = 1;

	m_movingAnim->GetSprite()->setRotation(-90);

	m_status = DESTROYING;
	m_type = Type::BULLET;
	m_timeToActive = 0.15f;
}

void Bullet::Scale()
{
	//scale
	float ratioWidth, ratioHeight;
	ratioWidth = (SCREEN_WIDTH / (3*ARMY_NUM_LANE)) / m_movingAnim->GetSprite()->getLocalBounds().height;


	m_movingAnim->GetSprite()->setScale(ratioWidth, ratioWidth);
	m_Explosion->GetSprite()->setScale(ratioWidth*1.5, ratioWidth*1.5);
}

void Bullet::Render(sf::RenderWindow &rd)
{
	
	m_currentAnim->Render(rd, m_position);

}

void Bullet::Update(float deltime)
{
	switch (m_currentDirection)
	{
	case UP:
		m_velocityY = -m_speed;
		break;
	case DOWN:
		m_velocityY = m_speed;
		break;
	}
	if (m_status == RenderGameObject::Status::DESTROYING && m_HP>0)
	{
		m_timeToActive -= deltime;
		if (m_timeToActive <= 0) m_status = RenderGameObject::Status::ALIVE;
	}
		RenderGameObject::Update(deltime);
		Scale();
	if (m_currentAnim == m_Explosion && m_currentAnim->GetCurrentFrameIndex() == m_currentAnim->GetTotalFrame() - 1)
	{
		m_status = RenderGameObject::Status::DEAD;
	}

	if (m_currentAnim->GetSprite()->getGlobalBounds().top >= SCREEN_HEIGHT || m_currentAnim->GetSprite()->getGlobalBounds().top + m_currentAnim->GetSprite()->getGlobalBounds().height <= 0)
		m_status = RenderGameObject::Status::DEAD;

}

void Bullet::Collision(RenderGameObject* collisionObject)
{

	switch (collisionObject->GetType())
	{
	case  RenderGameObject::Type::BARRIER:
		if (m_position.y >= collisionObject->GetSprite()->getGlobalBounds().top
			&& m_position.y <= collisionObject->GetSprite()->getGlobalBounds().top +  collisionObject->GetSprite()->getGlobalBounds().height)
		{
			if (m_status == RenderGameObject::Status::ALIVE && m_HP > 0)
			{
				m_HP -= 1;
				GameGlobal::getInstance()->SetScore(GameGlobal::getInstance()->GetScore() + 1);
			}
			if (m_HP <= 0 && m_status== RenderGameObject::Status::ALIVE)
			{
				m_currentAnim = m_Explosion;
				m_speed = 0;
				m_status = RenderGameObject::Status::DESTROYING;
				SoundManager::getInstance()->PlaySound(eIDSound::EXPLOSION_SOUND);
			}
		}
		break;
	case RenderGameObject::Type::BLACKARMY:
		if (m_status == RenderGameObject::Status::ALIVE && m_HP >= 0)
		{
			m_status= RenderGameObject::Status::DEAD;
			SoundManager::getInstance()->PlaySound(eIDSound::EXPLOSION_SOUND);
		}
	
		
		break;
	}
}

void Bullet::SetDirection(int direction)
{
	RenderGameObject::SetDirection(direction);
	switch (direction)
	{
	case RenderGameObject::Direction::DOWN:
		m_movingAnim->GetSprite()->setRotation(90);
	
		break;
	case RenderGameObject::Direction::UP:
		m_movingAnim->GetSprite()->setRotation(-90);

		break;
	}
}