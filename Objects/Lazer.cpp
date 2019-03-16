
#include "Lazer.h"

Lazer::Lazer()
{

}


Lazer::~Lazer()
{
	
	delete m_currentAnim;
	delete m_lazerAnim;
}


void Lazer::Init()
{
	m_lazerAnim = new Animation(eID::LAZER, 10, "Lazer", 0.2f);
	m_currentAnim = m_lazerAnim;

	Scale();

	m_position = sf::Vector2f(0, 0);

	m_status = ALIVE;
	m_type = Type::LAZER;
}

void Lazer::Scale()
{
	//scale
	float ratioWidth, ratioHeight;
	ratioWidth = SCREEN_WIDTH  / m_lazerAnim->GetSprite()->getLocalBounds().width;

	m_lazerAnim->GetSprite()->setScale(ratioWidth, 0.55);

}

sf::Sprite* Lazer::GetSprite()
{
	return m_sprite;

}
sf::Sprite* Lazer::GetSpriteAnim()
{
	return m_currentAnim->GetSprite();
}
void Lazer::Render(sf::RenderWindow &rd)
{

	m_currentAnim->Render(rd, m_position);

}

void Lazer::Update(float deltime)
{

	RenderGameObject::Update(deltime);

	Scale();
}

void Lazer::Collision(RenderGameObject* collisionObject)
{
	
}

