
#include "Army_Knife.h"



Army_Knife::Army_Knife()
{

}


Army_Knife::~Army_Knife()
{
	delete m_attackingAnim;
	delete m_movingAnim;
	delete m_movingFeetAnim;
	delete m_Explosion;
	delete m_TeleportAnim;
}


void Army_Knife::Init()
{
	m_movingAnim = new Animation(eID::BLACKARMY_KNIFE_MOVE, 20, "blackarmy_knife_move", 0.04f);
	m_attackingAnim = new Animation(eID::BLACKARMY_KNIFE_ATTACK, 15, "blackarmy_knife_attack", 0.04f);
	m_movingFeetAnim = new Animation(eID::BLACKARMY_WALK_FEET, 20, "blackarmy_walk_feet", 0.04f);
	m_Explosion = new Animation(eID::EXPLOSION, 24, "Explosion", 0.04f);
	m_TeleportAnim = new Animation(eID::TELEPORT, 3, "Teleport", 0.04f);
	m_currentAnim = m_movingAnim;
	


	Scale();
	m_speed = ARMY_KNIFE_SPEED;
	m_currentDirection = UP;
	m_HP = 2;
	if (rand() % 4 == 0)
		m_HP = 1;

	m_position = sf::Vector2f(0, 0);
	m_framePerRotation = 2;
	m_distanceTeleport = ARMY_KNIFE_TELEPORT_DISTANCE;

	
	m_movingAnim->GetSprite()->setRotation(-90);
	m_movingFeetAnim->GetSprite()->setRotation(-90);
	m_attackingAnim->GetSprite()->setRotation(-90);

	m_status = ALIVE;
	m_type = Type::BLACKARMY;
}

void Army_Knife::Scale()
{
	//scale
	float ratioWidth, ratioHeight;
	ratioWidth = (SCREEN_WIDTH / ARMY_NUM_LANE) / m_movingAnim->GetSprite()->getLocalBounds().height;


	m_movingAnim->GetSprite()->setScale(ratioWidth, ratioWidth);
	m_attackingAnim->GetSprite()->setScale(ratioWidth, ratioWidth);
	m_movingFeetAnim->GetSprite()->setScale(ratioWidth, ratioWidth);
	m_TeleportAnim->GetSprite()->rotate(1);
}

void Army_Knife::ChangeDirection()
{
	if(m_currentDirection == RenderGameObject::Direction::UP)
		m_currentDirection = RenderGameObject::Direction::DOWN;
	else
	m_currentDirection = RenderGameObject::Direction::UP;
	m_movingAnim->GetSprite()->setRotation(m_movingAnim->GetSprite()->getRotation() + 180);
	m_attackingAnim->GetSprite()->setRotation(m_attackingAnim->GetSprite()->getRotation() + 180);
	m_movingFeetAnim->GetSprite()->setRotation(m_movingFeetAnim->GetSprite()->getRotation() + 180);
}

sf::Sprite* Army_Knife::GetSprite()
{
	return m_sprite;

}

sf::Sprite* Army_Knife::GetSpriteAnim()
{
	return m_currentAnim->GetSprite();
}

void Army_Knife::Render(sf::RenderWindow &rd)
{
	if (m_currentAnim == m_movingAnim)
	{
		m_movingFeetAnim->Render(rd,m_position);
	}
	if (m_frameRotation > 3 && m_HP>0)
	{
		m_TeleportAnim->Render(rd, m_position - sf::Vector2f(0, m_distanceTeleport));
	}
	m_currentAnim->Render(rd,m_position);
	
}

void Army_Knife::Update(float deltime)
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

	m_frameRotation -= 1;
	if (m_frameRotation > 0)
	{
		if (m_frameRotation % m_framePerRotation == 0)
		{
			m_movingAnim->GetSprite()->setRotation(m_movingAnim->GetSprite()->getRotation() + 15);
			m_attackingAnim->GetSprite()->setRotation(m_attackingAnim->GetSprite()->getRotation() + 15);
			m_movingFeetAnim->GetSprite()->setRotation(m_movingFeetAnim->GetSprite()->getRotation() + 15);
			if (m_HP <= 0)
			{
				m_currentAnim->GetSprite()->scale(0.98, 0.98);
				m_movingFeetAnim->GetSprite()->scale(0.98,0.98);
			}
		}
		
		if (m_frameRotation == 1)
			if (m_HP>0) m_position -= sf::Vector2f(0, m_distanceTeleport);
			else
			{
				m_status = RenderGameObject::Status::DEAD;
				GameGlobal::getInstance()->SetScore(GameGlobal::getInstance()->GetScore() + 1);
			}
	/*	if (m_HP <= 0)
		{
			m_currentAnim->GetSprite()->scale(0.9, 0.9);
			if (m_frameRotation == 1)
				m_status = RenderGameObject::Status::DEAD;
		}
		else
		{
			if (m_frameRotation == 1)
				m_position -= sf::Vector2f(0, m_distanceTeleport);
		}*/
	}
	else
	RenderGameObject::Update(deltime);
	m_TeleportAnim->Update(deltime);
	if (m_currentAnim == m_movingAnim)
	{
		m_movingFeetAnim->Update(deltime);
		}
	if (m_HP>0) Scale();

	if ((m_currentAnim == m_Explosion || m_currentAnim==m_attackingAnim) && m_currentAnim->GetCurrentFrameIndex()==m_currentAnim->GetTotalFrame()-1)
	{
		m_status = RenderGameObject::Status::DEAD;

	}

	if (m_currentAnim->GetSprite()->getGlobalBounds().top >= SCREEN_HEIGHT+50 || m_currentAnim->GetSprite()->getGlobalBounds().top + m_currentAnim->GetSprite()->getGlobalBounds().height <=-50)
		m_status = RenderGameObject::Status::DEAD;
	
}

void Army_Knife::Collision(RenderGameObject* collisionObject)
{

	switch (collisionObject->GetType())
	{
	case  RenderGameObject::Type::BARRIER:
		
		if (m_status == RenderGameObject::Status::ALIVE && m_HP >= 0
			&&m_frameRotation<=-15)
		{
			m_HP -= 1;
			m_frameRotation = 48 * m_framePerRotation;
		
		}
		//ChangeDirection();
		break;
	case RenderGameObject::Type::BLACKARMY:
		if (collisionObject->GetDirection() == m_currentDirection
			||m_position.x!=collisionObject->GetPosition().x) 
			return;
		if (m_currentAnim == m_movingAnim
			&& abs(m_position.y - collisionObject->GetPosition().y) < m_currentAnim->GetSprite()->getGlobalBounds().height  )
		{
			m_currentAnim = m_attackingAnim;
			m_speed = 0;
		}
			break;
	case RenderGameObject::Type::BULLET:
		if (m_HP >= 0 && collisionObject->GetStatus() == RenderGameObject::Status::ALIVE)
		{
			m_status = RenderGameObject::Status::DESTROYING;
			m_currentAnim = m_Explosion;
			m_speed = 0;
			GameGlobal::getInstance()->SetHealth(GameGlobal::getInstance()->GetHealth() - 1);
		}
		break;
	case RenderGameObject::Type::LAZER:
		if (
	//		m_position.y > collisionObject->GetSpriteAnim()->getGlobalBounds().top
	//		&& m_position.y <= collisionObject->GetSpriteAnim()->getGlobalBounds().top + collisionObject->GetSpriteAnim()->getGlobalBounds().height
			 m_status == RenderGameObject::Status::ALIVE)
		{
			m_speed = 0;
			m_currentAnim = m_Explosion;
			m_status = RenderGameObject::Status::DESTROYING;
		}
		break;
	}
 }

void Army_Knife::SetDirection(int direction)
{
	RenderGameObject::SetDirection(direction);
	switch (direction)
	{
	case RenderGameObject::Direction::DOWN:
		m_movingAnim->GetSprite()->setRotation(90);
		m_movingFeetAnim->GetSprite()->setRotation(90);
		m_attackingAnim->GetSprite()->setRotation(90);
		m_distanceTeleport = -abs(m_distanceTeleport);
		break;
	case RenderGameObject::Direction::UP:
		m_movingAnim->GetSprite()->setRotation(-90);
		m_movingFeetAnim->GetSprite()->setRotation(-90);
		m_attackingAnim->GetSprite()->setRotation(-90);
		m_distanceTeleport = abs(m_distanceTeleport);
		break;
	}
}