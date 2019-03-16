#include "Bar.h"
#define BAR_TEXTURE "Resources/Textures/Bar/Bar.png"
#define BAR_SPEED 250.0f;
#include "../../GameControllers/define.h"
Bar::Bar()
{

}
Bar::~Bar()
{

}

Bar::Bar(int posX, int posY,int direction)
{
	Init();
	m_sprite->setPosition(sf::Vector2f(posX, posY));
	m_currentDirection = direction;
	m_sprite->setScale((float)((SCREEN_WIDTH/ 4)/m_sprite->getLocalBounds().width), 0.75);
	m_type = RenderGameObject::Type::BARRIER;

}
sf::Sprite* Bar::GetSprite()
{
	return m_sprite;
}
void Bar::Init()
{
	Init(BAR_TEXTURE);
	m_speed = BAR_SPEED;
	m_currentDirection = RIGHT;
	m_type = RenderGameObject::Type::BARRIER;
	m_isMovingLeft = false;
	m_isMovingRight = false;
}
void Bar::Init(std::string filePath)
{
	RenderGameObject::Init(filePath);
}
void Bar::Update(float deltime)
{
	//m_sprite->setPosition(m_sprite->getPosition().x+ m_speed * deltime*m_currentDirection, m_sprite->getPosition().y);
	if (isMovingLeft())
	{
		m_sprite->setPosition(m_sprite->getPosition().x - m_speed * deltime, m_sprite->getPosition().y);
	}
	else
		if (isMovingRight())
		{
			m_sprite->setPosition(m_sprite->getPosition().x + m_speed * deltime, m_sprite->getPosition().y);
		}


	CollisionWithScreenBound();
}
void Bar::Render(sf::RenderWindow& rd)
{
	RenderGameObject::Render(rd);
}


void Bar::CollisionWithScreenBound()
{
	if (m_sprite->getGlobalBounds().left+m_sprite->getGlobalBounds().width > SCREEN_WIDTH )
	{
		m_sprite->setPosition(m_sprite->getPosition().x - (m_sprite->getGlobalBounds().left + m_sprite->getGlobalBounds().width - SCREEN_WIDTH), m_sprite->getPosition().y);

	}
	else if (m_sprite->getPosition().x < 0)
	{
		m_sprite->setPosition(0, m_sprite->getPosition().y);
	}
}


bool Bar::isMovingLeft()
{
	return m_isMovingLeft;
}
void Bar::SetMovingLeft(bool flag)
{
	m_isMovingLeft = flag;
}

bool Bar::isMovingRight()
{
	return m_isMovingRight;
}
void Bar::SetMovingRight(bool flag)
{
	m_isMovingRight = flag;
}