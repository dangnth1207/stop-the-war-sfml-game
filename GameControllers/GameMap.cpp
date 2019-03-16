#include "pch.h"
#include "GameMap.h"


GameMap::GameMap()
{
}


GameMap::~GameMap()
{
}

void GameMap::AddArmy(RenderGameObject * army)
{
	m_listArmy.push_back(army);
}

void GameMap::AddArmyBullet(Bullet * armyBullet)
{
	m_listArmyBullet.push_back(armyBullet);
}
void GameMap::AddEffect(Animation* effect)
{
	m_listEffect.push_back(effect);
}
void GameMap::SetDif(float dif)
{
	m_difficult = dif;
}


void GameMap::Init()
{

}

void GameMap::Render(sf::RenderWindow &rd)
{
	#pragma region Render Army
		for (std::list<RenderGameObject*>::iterator it = m_listArmy.begin(); it != m_listArmy.end(); it++)
		{
			(*it)->Render(rd);
		}
	#pragma endregion

	#pragma region Render Bullet
			for (std::list<Bullet*>::iterator it = m_listArmyBullet.begin(); it != m_listArmyBullet.end(); it++)
			{
				(*it)->Render(rd);
			}
	#pragma endregion

			/*
	#pragma region Render Effect
			for (std::list<Animation*>::iterator it = m_listEffect.begin(); it != m_listEffect.end(); it++)
			{
				(*it)->Render(rd,(*it)->GetSprite()->getPosition());
			}
	#pragma endregion
	*/
}

void GameMap::Update(float deltime)
{
	/*
	#pragma region Update Effect
		for (std::list<Animation*>::iterator it = m_listEffect.begin(); it != m_listEffect.end(); )
		{
			if ((*it)->GetTimeExist() > 0)
			{
				(*it)->Update(deltime);
			}
			else
			{
				Animation* tmp = *it;
				it++;
				m_listEffect.remove(tmp);
				delete tmp;
				tmp = NULL;
				continue;
			}
			it++;
			//(*it)->GetSprite()->scale(-0.11, -0.11);
			
		}
	#pragma endregion
	*/

	#pragma region Update Army
		for (std::list<RenderGameObject*>::iterator it = m_listArmy.begin(); it != m_listArmy.end(); )
		{
			if ((*it)->GetStatus() != RenderGameObject::Status::DEAD)
				(*it)->Update(deltime);
			else
			{
				RenderGameObject* tmp = *it;
				it++;
				m_listArmy.remove(tmp);
				delete tmp;
				tmp = NULL;
				continue;
			}

			if ((*it)->GetAnimation()->GeteID() == eID::BLACKARMY_SHOTGUN_SHOOT
				&& (*it)->GetAnimation()->GetCurrentFrameIndex() == (*it)->GetAnimation()->GetTotalFrame() - 2
				&& (*it)->GetStatus()!=RenderGameObject::Status::DESTROYING)
			{
				Bullet *bullet = new Bullet();
				bullet->Init();
				if ((*it)->GetDirection() == RenderGameObject::Direction::UP)
				{
					
					bullet->SetPosition((*it)->GetAnimation()->GetSprite()->getGlobalBounds().left + (*it)->GetAnimation()->GetSprite()->getGlobalBounds().width *0.75,
						(*it)->GetAnimation()->GetSprite()->getGlobalBounds().top);
					bullet->SetDirection((*it)->GetDirection());
				}
				else
				{
					
					bullet->SetPosition((*it)->GetAnimation()->GetSprite()->getGlobalBounds().left + (*it)->GetAnimation()->GetSprite()->getGlobalBounds().width *0.25,
						(*it)->GetAnimation()->GetSprite()->getGlobalBounds().top + (*it)->GetAnimation()->GetSprite()->getGlobalBounds().height);
					bullet->SetDirection((*it)->GetDirection());
				}
				bullet->SetSpeed(BULLET_SPEED*m_difficult);
				m_listArmyBullet.push_back(bullet);
				(*it)->SetStatus(RenderGameObject::Status::DESTROYING);
			}
			
			it++;
		}
	#pragma endregion

	#pragma region Update Bullet
		for (std::list<Bullet*>::iterator it = m_listArmyBullet.begin(); it != m_listArmyBullet.end(); )
		{
			if ((*it)->GetStatus() != RenderGameObject::Status::DEAD)
				(*it)->Update(deltime);
			else
			{
				Bullet* tmp = *it;
				it++;
				m_listArmyBullet.remove(tmp);
				delete tmp;
				tmp = NULL;
				continue;
			}
			it++;
		}
	#pragma endregion

}


std::list<RenderGameObject*> GameMap::GetListArmy()
{
	return m_listArmy;
}
std::list<Bullet*> GameMap::GetListArmyBullet()
{
	return m_listArmyBullet;
}