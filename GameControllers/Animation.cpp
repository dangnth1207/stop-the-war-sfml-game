#include "Animation.h"



Animation::Animation()
{
}


Animation::~Animation()
{
	
	delete m_spriteAnim;
	m_spriteAnim = NULL;
}

Animation::Animation(eID texture_eID, int totalFrame, std::string nameAnimation, float timePerFrame)
{
	m_eID = texture_eID;
	m_nameAnimation = nameAnimation;

	m_textureAnim = ResourcesManager::getInstance()->GetTexture(texture_eID);
	m_spriteAnim = new sf::Sprite();
	m_spriteAnim->setTexture(*m_textureAnim);
	m_spriteAnim->setTextureRect(ResourcesManager::getInstance()->GetSourceRect(texture_eID, nameAnimation + "0"));
	Point origin = ResourcesManager::getInstance()->GetOriginPoint(texture_eID, nameAnimation+ "0");
	m_spriteAnim->setOrigin(sf::Vector2f(origin.x, origin.y));


	m_totalFrame = totalFrame;
	m_timePerFrame = timePerFrame;
	m_currentTime = 0;
	m_frameUpdate = (int)(m_timePerFrame / (1.0 / LIMIT_FPS));
}
sf::Sprite* Animation::GetSprite()
{
	return m_spriteAnim;
}
int Animation::GetCurrentFrameIndex()
{
	return m_currentFrame;
}
int Animation::GetTotalFrame()
{
	return m_totalFrame;
}
float Animation::GetTimeExist()
{
	return m_timeExist;
}
void  Animation::SetTimeExist(float timeExist)
{
	 m_timeExist=timeExist;
}
void Animation::Update(float deltime)
{
	m_timeExist -= deltime;
	if (m_timeExist < -5.0f)
		m_timeExist = 5.0f;
	if (m_totalFrame == 1) return;
	if (m_currentFrameCount >= m_frameUpdate)
	{
		m_spriteAnim->setTextureRect(ResourcesManager::getInstance()->GetSourceRect(m_eID, m_nameAnimation + std::to_string(m_currentFrame)));
		sf::IntRect rect;
		rect = ResourcesManager::getInstance()->GetSourceRect(m_eID, m_nameAnimation + std::to_string(m_currentFrame));
		Point origin = ResourcesManager::getInstance()->GetOriginPoint(m_eID, m_nameAnimation + std::to_string(m_currentFrame));
		m_spriteAnim->setOrigin(sf::Vector2f(origin.x,origin.y));

		m_currentFrame += 1;

		if (m_currentFrame >= m_totalFrame)
		{
			m_currentFrame = 0;
		}

		m_currentFrameCount = 0;
	}
	else
	{
		m_currentFrameCount +=1;
	}
}
void Animation::Render(sf::RenderWindow &rd,sf::Vector2f position)
{
	m_spriteAnim->setPosition(position);
	sf::RectangleShape rectangle(sf::Vector2f(m_spriteAnim->getGlobalBounds().width, m_spriteAnim->getGlobalBounds().height));
	rectangle.setPosition(m_spriteAnim->getGlobalBounds().left,m_spriteAnim->getGlobalBounds().top);

	//rd.draw(rectangle);
	rd.draw(*m_spriteAnim);
}

std::string Animation::GetNameAnimation()
{
	return m_nameAnimation;


}

	eID Animation::GeteID()
	{
		return m_eID;

	}