#include "pch.h"
#include "MenuScene.h"
#include "GameControllers\SceneManager.h"
#include "GameGlobal.h"

MenuScene::MenuScene(float w, float h)
{
	Init(w, h);
	font.loadFromFile("font.ttf");

	menu[0].setFont(font);
	menu[0].setString("Play");
	menu[0].setFillColor(sf::Color::Green);
	menu[0].setPosition(sf::Vector2f(15, h / (MaxItem + 1) * 1));

	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("Sound");
	sound.setPosition(sf::Vector2f(w/2, h / (MaxItem + 1) *1.25f));
	menu[1].setPosition(sf::Vector2f(15, h / (MaxItem + 1) * 1.25f));

	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setString("Quit");
	menu[2].setPosition(sf::Vector2f(15, h / (MaxItem + 1) * 1.5f));

	GameName.setFont(font);
	GameName.setScale(1.5f, 1.5f);
	GameName.setFillColor(sf::Color::Yellow);
	GameName.setString("STOP THE WAR");
	GameName.setPosition(sf::Vector2f(60, 40));

	selectItemIndex = 0;
	sound.setFont(font);
}


MenuScene::~MenuScene()
{
}

void MenuScene::Init(float w, float h) {
	if (!m_textureBackGround.loadFromFile("BackgroundMenu.jpg")) std::cout << "error" << std::endl ;
	m_spriteBackGround.setTexture(m_textureBackGround);

	m_spriteBackGround.setScale((float)SCREEN_WIDTH / m_textureBackGround.getSize().x, (float)SCREEN_HEIGHT / m_textureBackGround.getSize().y);
	isPlay = false;
}

void MenuScene::Render(sf::RenderWindow &window) {
	window.draw(m_spriteBackGround);
	window.draw(GameName);
	for (int i = 0; i < MaxItem; i++)
		window.draw(menu[i]);


	window.draw(sound);
}

void MenuScene::MoveUp() {
	if (selectItemIndex - 1 >= 0) {
		menu[selectItemIndex].setFillColor(sf::Color::White);
		menu[--selectItemIndex].setFillColor(sf::Color::Green);
	}
}

void MenuScene::MoveDown() {
	if (selectItemIndex + 1 < MaxItem) {
		menu[selectItemIndex].setFillColor(sf::Color::White);
		menu[++selectItemIndex].setFillColor(sf::Color::Green);
	}
}

void MenuScene::Update(float deltime) {
	if (GameGlobal::getInstance()->GetSoundEffect())
		sound.setString("v");
	else sound.setString("x");
}
void MenuScene::Event(sf::Event event, sf::RenderWindow &rd)
{
	Scene *gameScene;
	switch (event.type)
	{
	case  sf::Event::KeyReleased:
		switch (event.key.code)
		{
		case sf::Keyboard::Up:
			MoveUp();
			break;
		case sf::Keyboard::Down:
			MoveDown();
			break;
		
		case sf::Keyboard::Enter:
			switch (selectItemIndex) {
			case 0:
				//Play			
				gameScene = new GameScene();
				gameScene->Init();
				SceneManager::GetInstance()->ReplaceScene(gameScene);
				break;
			case 1:
				//Setting;
				GameGlobal::getInstance()->SetSoundEffect(!GameGlobal::getInstance()->GetSoundEffect());
				break;
			case 2:
				//Quit;
			rd.close();
				
				break;
			}
			break;
		}

	}
}
