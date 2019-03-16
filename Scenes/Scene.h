#pragma once
#include "SFML\Graphics.hpp"

class Scene
{
protected:
	sf::Sprite *m_spriteBackGround;
	sf::Texture *m_textureBackGround;

public:
	virtual void Update(float deltime);
	virtual void Init();
	virtual void Render(sf::RenderWindow&);

	virtual void Event(sf::Event event, sf::RenderWindow &);

	~Scene();

protected:
	Scene();

private:

};