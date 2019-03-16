#pragma once
#include "../../Objects/RenderGameObject.h"
#include <list>
#include "../Objects/Enemies/Bullet.h"
class GameMap
{
private:
	std::list<RenderGameObject*> m_listArmy;
	std::list<Bullet*> m_listArmyBullet;

	std::list<Animation*> m_listEffect;

	float m_difficult = 1.0;
public:	

	GameMap();
	~GameMap();

	std::list<RenderGameObject*> GetListArmy();
	std::list<Bullet*> GetListArmyBullet();
	void AddArmy(RenderGameObject * army);
	void AddArmyBullet(Bullet * armyBullet);
	void AddEffect(Animation* effect);
	void SetDif(float dif);
	virtual void Init() ;
	virtual void Render(sf::RenderWindow &) ;
	virtual void Update(float) ;
};

