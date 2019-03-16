#include "SpecialMonster.h"

#define SpecialMonster_TEXTURE "Resources/Textures/SpecialMonsters/YellowRedSpecialMonster.png"
#define SpecialMonster_SPEED 100.0f
void SpecialMonster::Init()
{
	Init(SpecialMonster_TEXTURE);
}
SpecialMonster::SpecialMonster(float posX, float posY, int direction, std::string filePath)
{
	if (filePath == "")
		Init();
	else
		Init(filePath);
	m_sprite->setPosition(posX, posY);
	m_currentDirection = direction;
}
void SpecialMonster::Init(std::string filePath)
{

	m_sprite = new sf::Sprite();

	m_texture = ResourcesManager::getInstance()->GetTexture(eID::REDMONSTER);
	m_sprite->setTexture(*m_texture);
	m_speed = 100.0f;
	m_currentDirection = DOWN;
	m_currentTime = 0;
	m_timePerFrame = 0.1f;
	m_numFrames = 8;
	HP = 2;
	
	m_sprite->setTextureRect(sf::IntRect((m_currentFrame - 1) * 51, 52, 51, 51));
	m_sprite->setColor( sf::Color(0, 0, 255, 255));
}
void SpecialMonster::SetBar(Bar *bar)
{
	m_bar = bar;
}
void SpecialMonster::SetTwoBar(Bar *bar1, Bar *bar2)
{
	m_bar = bar1;
	m_bar2 = bar2;
}
void SpecialMonster::Update(float deltime)
{
	m_sprite->setPosition(m_sprite->getPosition().x, m_sprite->getPosition().y + m_speed * deltime*(m_currentDirection / 2));
	if (m_numFrames == 1) return;
	else
	{
		if (m_currentTime >= m_timePerFrame)
		{

			if (m_currentFrame < m_numFrames)
			{
				m_currentFrame += 1;
				if (m_currentDirection == DOWN)
					m_sprite->setTextureRect(ResourcesManager::getInstance()->GetSourceRect(eID::REDMONSTER, "down" + std::to_string(m_currentFrame)));
				else
					m_sprite->setTextureRect(ResourcesManager::getInstance()->GetSourceRect(eID::REDMONSTER, "up" + std::to_string(m_currentFrame)));
			}
			else
			{
				m_currentFrame = 0;
			}

			m_currentTime = 0;
		}
		else
		{
			m_currentTime += deltime;
		}
	}

	if (m_bar!=NULL)
	if (m_sprite->getGlobalBounds().intersects(m_bar->GetSprite()->getGlobalBounds()) && HP>0)
	{
		HP -= 1;
		if (HP==0)
		if (m_currentDirection == DOWN) m_currentDirection = UP;
		else
			m_currentDirection = DOWN;
		m_bar = NULL;
	}
		if (m_bar2 != NULL)
			if (m_sprite->getGlobalBounds().intersects(m_bar2->GetSprite()->getGlobalBounds()) && HP>0)
	{
		HP -= 1;
		if (HP == 0)
		if (m_currentDirection == DOWN) m_currentDirection = UP;
		else
			m_currentDirection = DOWN;
		m_bar2 = NULL;
	}

}
sf::Sprite* SpecialMonster::GetSprite()
{
	return m_sprite;
}
void SpecialMonster::Render(sf::RenderWindow& rd)
{
	RenderGameObject::Render(rd);
}


void SpecialMonster::CollisionWithScreenBound()
{
	if (m_sprite->getPosition().y + m_sprite->getTextureRect().height > SCREEN_HEIGHT || m_sprite->getPosition().y < 0)
	{
		if (m_currentDirection == DOWN) m_currentDirection = UP;
		else
			m_currentDirection = DOWN;
	}
}