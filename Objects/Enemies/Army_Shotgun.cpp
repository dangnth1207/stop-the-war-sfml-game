
#include "Army_Shotgun.h"



Army_Shotgun::Army_Shotgun()
{

}


Army_Shotgun::~Army_Shotgun()
{
	delete m_attackingAnim;
	delete m_movingAnim;
	delete m_movingFeetAnim;
	delete m_Explosion;
}


void Army_Shotgun::Init()
{
	m_movingAnim = new Animation(eID::BLACKARMY_SHOTGUN_MOVE, 20, "blackarmy_shotgun_move", 0.02f);
	m_attackingAnim = new Animation(eID::BLACKARMY_SHOTGUN_SHOOT,5, "blackarmy_shotgun_shoot", 0.2f);
	m_movingFeetAnim = new Animation(eID::BLACKARMY_WALK_FEET, 20, "blackarmy_walk_feet", 0.02f);
	m_Explosion = new Animation(eID::EXPLOSION, 24, "Explosion", 0.04f);

	m_currentAnim = m_movingAnim;



	Scale();
	m_speed = ARMY_SHOTGUN_SPEED;
	m_currentDirection = UP;
	m_HP = 1;
	m_position = sf::Vector2f(0, 0);

	m_movingAnim->GetSprite()->setRotation(-90);
	m_movingFeetAnim->GetSprite()->setRotation(-90);
	m_attackingAnim->GetSprite()->setRotation(-90);

	m_status = ALIVE;
	m_type = Type::BLACKARMY;
	m_distanceMove = ARMY_SHOTGUN_DISTANCE_MOVE_SHOOT;
}

void Army_Shotgun::Scale()
{
	//scale
	float ratioWidth, ratioHeight;
	ratioWidth = (SCREEN_WIDTH / ARMY_NUM_LANE) / m_movingAnim->GetSprite()->getLocalBounds().height;


	m_movingAnim->GetSprite()->setScale(ratioWidth, ratioWidth);
	m_attackingAnim->GetSprite()->setScale(ratioWidth, ratioWidth);
	m_movingFeetAnim->GetSprite()->setScale(ratioWidth, ratioWidth);
}
sf::Sprite* Army_Shotgun::GetSprite()
{
	return m_sprite;

}
sf::Sprite* Army_Shotgun::GetSpriteAnim()
{
	return m_currentAnim->GetSprite();
}
void Army_Shotgun::Render(sf::RenderWindow &rd)
{
	if (m_currentAnim == m_movingAnim)
	{
		m_movingFeetAnim->Render(rd,m_position);
	}
	m_currentAnim->Render(rd,m_position);

}

void Army_Shotgun::ChangeDirection()
{
	if (m_currentDirection == RenderGameObject::Direction::UP)
		m_currentDirection = RenderGameObject::Direction::DOWN;
	else
		m_currentDirection = RenderGameObject::Direction::UP;
	m_movingAnim->GetSprite()->setRotation(m_movingAnim->GetSprite()->getRotation() + 180);
	m_attackingAnim->GetSprite()->setRotation(m_attackingAnim->GetSprite()->getRotation() + 180);
	m_movingFeetAnim->GetSprite()->setRotation(m_movingFeetAnim->GetSprite()->getRotation() + 180);
}
void Army_Shotgun::Update(float deltime)
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
	if (m_currentAnim==m_movingAnim)
		
	m_position += sf::Vector2f(m_velocityX*deltime, m_velocityY*deltime);
	m_currentAnim->Update(deltime);
	
	Scale();

	if (m_currentAnim == m_attackingAnim)
	{	
		if (m_currentAnim->GetCurrentFrameIndex() == m_currentAnim->GetTotalFrame() - 1)
		{
			m_currentAnim = m_movingAnim;
			

			ChangeDirection();
		
		}
	}
		if (m_distanceMove < 0)
		{
			m_currentAnim = m_attackingAnim;
			m_distanceMove = 9999;
		}
		else
		{
			m_distanceMove -= m_speed * deltime;
		}

		if (m_currentAnim == m_Explosion && m_currentAnim->GetCurrentFrameIndex() == m_currentAnim->GetTotalFrame() - 1)
		{
			m_status = RenderGameObject::Status::DEAD;
		}

	if (m_currentAnim->GetSprite()->getGlobalBounds().top >= SCREEN_HEIGHT || m_currentAnim->GetSprite()->getGlobalBounds().top + m_currentAnim->GetSprite()->getGlobalBounds().height <= 0)
		m_status = RenderGameObject::Status::DEAD;

}

void Army_Shotgun::Collision(RenderGameObject* collisionObject)
{
	switch (collisionObject->GetType())
	{
	case RenderGameObject::Type::BULLET:
		if ( m_HP >= 0 && collisionObject->GetStatus()== RenderGameObject::Status::ALIVE)
		{
			m_HP -= 1;
			m_status = RenderGameObject::Status::DESTROYING;
			m_currentAnim = m_Explosion;
			m_speed = 0;
			GameGlobal::getInstance()->SetHealth(GameGlobal::getInstance()->GetHealth() - 1);
		}


		break;
	}
}

void Army_Shotgun::SetDirection(int direction)
{
	RenderGameObject::SetDirection(direction);
	switch (direction)
	{
	case RenderGameObject::Direction::DOWN:
		m_movingAnim->GetSprite()->setRotation(90);
		m_movingFeetAnim->GetSprite()->setRotation(90);
		m_attackingAnim->GetSprite()->setRotation(90);
		break;
	case RenderGameObject::Direction::UP:
		m_movingAnim->GetSprite()->setRotation(-90);
		m_movingFeetAnim->GetSprite()->setRotation(-90);
		m_attackingAnim->GetSprite()->setRotation(-90);
		break;
	}
}