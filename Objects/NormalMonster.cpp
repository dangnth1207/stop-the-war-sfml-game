#include "NormalMonster.h"

#define NormalMonster_TEXTURE "Resources/Textures/NormalMonsters/YellowRedNormalMonster.png"
#define NormalMonster_SPEED 100.0f
void NormalMonster::Init()
{
	Init(NormalMonster_TEXTURE);
}
NormalMonster::NormalMonster(float posX, float posY, int direction, std::string filePath)
{
	if (filePath == "")
		Init();
	else
		Init(filePath);
	m_sprite->setPosition(posX, posY);
	m_currentDirection = direction;

	/*switch (direction)
	{
	case Direction::DOWN:
		m_sprite->setColor(sf::Color(255, 0, 0, 255));
		break;
	case Direction::UP:
		m_sprite->setColor(sf::Color(255, 255, 0, 255));
		break;
	default:
		break;
	}*/
}
void NormalMonster::Init(std::string filePath)
{

	m_sprite = new sf::Sprite();

	m_texture = ResourcesManager::getInstance()->GetTexture(eID::BLACKARMY_KNIFE_MOVE);
	m_sprite->setTexture(*m_texture);
	m_speed = 100.0f;
	m_currentDirection = DOWN;
	m_currentTime = 0;
	m_timePerFrame = 0.1f;
	m_numFrames = 20;
	HP = 1;
	//m_sprite->setTextureRect(sf::IntRect((m_currentFrame - 1) * 51, 52, 51, 51));
	m_sprite->setScale(0.5, 0.50);
}
void NormalMonster::SetBar(Bar *bar)
{
	m_bar = bar;
}
void NormalMonster::SetTwoBar(Bar *bar1,Bar *bar2)
{

}
void NormalMonster::Update(float deltime)
{
//	m_sprite->setPosition(m_sprite->getPosition().x, m_sprite->getPosition().y + m_speed * deltime*(m_currentDirection / 2));
	//CollisionWithScreenBound();

	if (m_numFrames == 1) return;
	else
	{
		if (m_currentTime >= m_timePerFrame)
		{

		
			
			m_sprite->setTextureRect(ResourcesManager::getInstance()->GetSourceRect(eID::BLACKARMY_KNIFE_MOVE, "blackarmy_knife_move" + std::to_string(m_currentFrame)));
			sf::IntRect rect;
			rect = ResourcesManager::getInstance()->GetSourceRect(eID::BLACKARMY_KNIFE_MOVE, "blackarmy_knife_move" + std::to_string(m_currentFrame));
			m_currentFrame += 1;
			if (m_currentFrame >= m_numFrames)
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

	/*if (m_sprite->getGlobalBounds().intersects(m_bar->GetSprite()->getGlobalBounds()) && HP>0)
	{
		HP -= 1;
		if (m_currentDirection == DOWN) m_currentDirection = UP;
		else
			m_currentDirection = DOWN;
	}*/
}
sf::Sprite* NormalMonster::GetSprite()
{
	return m_sprite;
}
void NormalMonster::Render(sf::RenderWindow& rd)
{
	RenderGameObject::Render(rd);
}


void NormalMonster::CollisionWithScreenBound()
{
	if (m_sprite->getPosition().y + m_sprite->getTextureRect().height > SCREEN_HEIGHT || m_sprite->getPosition().y < 0)
	{
		if (m_currentDirection == DOWN) m_currentDirection = UP;
		else
			m_currentDirection = DOWN;
	}
}