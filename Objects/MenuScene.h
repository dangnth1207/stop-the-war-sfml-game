#pragma once
#include "SFML-2.5.1\include\SFML\Graphics.hpp"
#include <iostream>
#include "GameControllers/Scene.h"
#include "GameControllers/GameScene.h"
#define MaxItem 3

class MenuScene : public Scene
{
public:
	MenuScene(float w, float h);

	~MenuScene();

	void Init(float, float);
	void Render(sf::RenderWindow &window);
	void MoveUp();
	void MoveDown();
	virtual void Update(float deltime);
	virtual void Event(sf::Event event, sf::RenderWindow &);
	int GetPress() {
		return selectItemIndex;
	}
private:
	int selectItemIndex;
	sf::Font font;
	sf::Text menu[MaxItem];
	sf::Text GameName;
	sf::Texture m_textureBackGround;
	sf::Sprite m_spriteBackGround;
	bool isPlay;
	sf::Text sound;
};

