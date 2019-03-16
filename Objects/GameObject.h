#pragma once
#include "SFML/Graphics.hpp"

class GameObject
{
public:
	GameObject()
	{
	};
	~GameObject()
	{
	};
	virtual void Init()=0;
	virtual void Render(sf::RenderWindow &) = 0;
	virtual void Update(float) = 0;
};