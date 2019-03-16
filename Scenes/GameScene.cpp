#pragma once
#include "GameScene.h"
GameScene::GameScene()
{
	m_bar1 = new Bar(0,275,RenderGameObject::Direction::LEFT);
	m_bar2 = new Bar(300, 425, RenderGameObject::Direction::RIGHT);


	m_timeAddBlackArmy = 1.0;
}

GameScene::~GameScene()
{

}
void GameScene::Event(sf::Event eventt, sf::RenderWindow &rd)
{

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			m_bar1->SetMovingRight(true);
			m_bar1->SetMovingLeft(false);

			m_bar2->SetMovingRight(false);
			m_bar2->SetMovingLeft(true);
		}
		else
	
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			m_bar1->SetMovingRight(false);
			m_bar1->SetMovingLeft(true);

			m_bar2->SetMovingRight(true);
			m_bar2->SetMovingLeft(false);
		}
		else
		{
			m_bar1->SetMovingRight(false);
			m_bar1->SetMovingLeft(false);

			m_bar2->SetMovingRight(false);
			m_bar2->SetMovingLeft(false);
		}
		if ( eventt.type==sf::Event::KeyPressed && eventt.key.code ==sf::Keyboard::P)
		{
			if (m_gameStatus == PLAYING) {
				m_gameStatus = PAUSE;
				m_timeLeft = m_currentTimeLeft;
			}
			else if (m_gameStatus == PAUSE) 
				{
			
					m_gameStatus = PLAYING;
					GameTime::GetInstance()->StartCounter();
				}
		}
		if (m_gameStatus == GAMEOVER)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				m_isPlayAgainSelected = !m_isPlayAgainSelected;
			}
			if (eventt.type==sf::Event::KeyReleased && eventt.key.code==sf::Keyboard::Enter)
			{
				if (m_isPlayAgainSelected)
				{					
					ResetGameParameter();
					ResetGameScene();
					return;
				}
				else
				{
					Scene *menuscene = new MenuScene(SCREEN_WIDTH, SCREEN_HEIGHT);
					SceneManager::GetInstance()->ReplaceScene(menuscene);
					ResetGameParameter();
					return;
				}
			}
		}

		
	/*if (eventt.type == sf::Event::MouseButtonPressed)
	{
		RenderGameObject *newArmy = new Army_Shotgun();
		newArmy->Init();
		newArmy->SetDirection(RenderGameObject::Direction::DOWN);
		newArmy->SetPosition(eventt.mouseButton.x, eventt.mouseButton.y);
		m_gameMap->AddArmy(newArmy);
		SoundManager::getInstance()->PlaySound(eIDSound::EXPLOSION_SOUND);
	}*/

}
void GameScene::Update(float deltime)
{	
	if (GameGlobal::getInstance()->GetHealth() <= 0) m_gameStatus = GAMEOVER;
	if (m_gameStatus == PAUSE || m_gameStatus==GAMEOVER) return;
	
	m_bar1->Update(deltime);
	m_bar2->Update(deltime);

	m_gameMap->Update(deltime);
	
	/*
	Animation* effect = new Animation(eID::TELEPORT, 3, "Teleport", 0.04f);
	effect->GetSprite()->setPosition(m_bar1->GetSprite()->getPosition().x,m_bar1->GetSprite()->getPosition().y + m_bar1->GetSprite()->getGlobalBounds().height / 2);
	effect->SetTimeExist(0.3f);
	effect->GetSprite()->setScale(0.5, 0.5);
	m_gameMap->AddEffect(effect);
	*/

	if (m_currentTime >= m_timeAddBlackArmy)
	{
		RenderGameObject *newArmy;
		int randType = rand() % 11;
		if (randType >= 1)
			newArmy = new Army_Shotgun();
		else
			newArmy = new Army_Knife();;
		newArmy->Init();
		srand((int)newArmy);
		int TopOrBottom = rand() % 2;
		int posX;
		if (randType!=0)
		do
		{
			posX=newArmy->GetSpriteAnim()->getGlobalBounds().width / 2 + newArmy->GetSpriteAnim()->getGlobalBounds().width*(rand() % ARMY_NUM_LANE);
		} while (abs(posX - m_lasPosX) < newArmy->GetSpriteAnim()->getGlobalBounds().width*2);
		else
		{
			int lane = rand() % (ARMY_NUM_LANE * 1 / 3) + (ARMY_NUM_LANE / 3);
			posX = newArmy->GetSpriteAnim()->getGlobalBounds().width / 2 + newArmy->GetSpriteAnim()->getGlobalBounds().width*lane;
		}
		newArmy->SetPosition(posX, 
			TopOrBottom*(SCREEN_HEIGHT+100)-50);
		m_lasPosX = posX;
		
		if (TopOrBottom == 0)//Top
		{			
			newArmy->SetDirection(RenderGameObject::Direction::DOWN);
		}
		else	//Bottom		
		{		
			newArmy->SetDirection(RenderGameObject::Direction::UP);
		}
		//newArmy->SetSpeed(ARMY_SHOTGUN_SPEED*m_difficult);
		m_gameMap->AddArmy(newArmy);
		m_currentTime = 0;
		srand(time(0));
		m_timeAddBlackArmy = 0.8 + (rand()%50 / 50.0);
	}
	else
	{
		m_currentTime += deltime;
	}
	CheckCollision();
	
	int timeTmp = m_currentTimeLeft;
	
	m_currentTimeLeft = m_timeLeft - (GameTime::GetInstance()->GetTimeInSecond() - GameTime::GetInstance()->GetStartTime());
	//GameTime::GetInstance()->StartCounter();
	if (m_currentTimeLeft % 15 == 0 && m_currentTimeLeft != timeTmp)
	{
		m_difficult = m_difficult + 0.12f;
		if (m_difficult > 2.0f) m_difficult = 2.0f;
		m_gameMap->SetDif(m_difficult);
	}

}

void GameScene::Init()
{
	m_textureBackGround = ResourcesManager::getInstance()->GetTexture(eID::TOP_LANE_BACKGROUND);
	m_spriteBackGround = new sf::Sprite();
	m_spriteBackGround->setTexture(*m_textureBackGround);
	m_spriteBackGround->setScale((float) SCREEN_WIDTH / m_spriteBackGround->getLocalBounds().width, (float) SCREEN_HEIGHT / m_spriteBackGround->getLocalBounds().height);


	m_textFont = new sf::Font();
	m_textFont->loadFromFile("Resources/Fonts/arial.ttf");
	m_scoreText = new sf::Text();
	m_scoreText->setFont(*m_textFont);
	m_currentTimeLeftText = new sf::Text();
	m_currentTimeLeftText->setFont(*m_textFont);
	m_healthText = new sf::Text();
	m_healthText->setFont(*m_textFont);

	m_scoreText->setPosition(SCREEN_WIDTH/3 -100 , SCREEN_HEIGHT/2);
	m_currentTimeLeftText->setPosition(SCREEN_WIDTH / 3 , SCREEN_HEIGHT / 2);
	m_healthText->setPosition(SCREEN_WIDTH / 3 +100, SCREEN_HEIGHT / 2);

	m_scoreText->setScale(0.5, 0.5);
	m_currentTimeLeftText->setScale(0.5, 0.5);
	m_healthText->setScale(0.5, 0.5);

	m_gameMap = new GameMap();
	GameTime::GetInstance()->StartCounter();

	

}

void GameScene::Render(sf::RenderWindow &rd)
{	
	rd.draw(*m_spriteBackGround);
	
	m_bar1->Render(rd);
	m_bar2->Render(rd);
	m_gameMap->Render(rd);

	
	//float timee = GameTime::GetInstance()->GetTimeInSecond() - GameTime::GetInstance()->GetStartTime();
	//m_score->setString("time: "+ std::to_string(timee));

	m_scoreText->setString("Score: " + std::to_string(GameGlobal::getInstance()->GetScore()));
	m_healthText->setString("Health: " + std::to_string(GameGlobal::getInstance()->GetHealth()));
	m_currentTimeLeftText->setString("Timeleft: " + std::to_string(m_currentTimeLeft));
	rd.draw(*m_scoreText);
	rd.draw(*m_healthText);
	rd.draw(*m_currentTimeLeftText);
	if (m_gameStatus == PAUSE)
	{
		sf::RectangleShape rect;
		rect.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
		rect.setPosition(0, 0);
		rect.setFillColor(sf::Color(0, 0, 0, 100));
		rd.draw(rect);
		sf::Text pause;
		sf::Font font;
		font.loadFromFile("Resources/Fonts/font.ttf");
		pause.setFont(font);
		pause.setScale(1.5, 1.5);
		pause.setPosition(SCREEN_WIDTH / 3, SCREEN_HEIGHT / 2);
		pause.setString("Paused");
		rd.draw(pause);
	}
	if (m_gameStatus == GAMEOVER)
	{
		sf::RectangleShape rect;
		rect.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
		rect.setPosition(0, 0);
		rect.setFillColor(sf::Color(0, 0, 0, 100));
		rd.draw(rect);
		sf::Text gameover;
		sf::Font font;
		font.loadFromFile("Resources/Fonts/font.ttf");
		gameover.setFont(font);
		gameover.setScale(1.5, 1.5);
		gameover.setPosition(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 3);
		gameover.setString("Game Over");
		sf::Text playAgain;
		playAgain.setFont(font);
		playAgain.setScale(0.8, 0.8);
		playAgain.setPosition(SCREEN_WIDTH/5,gameover.getGlobalBounds().top + gameover.getGlobalBounds().height + 20 );
		playAgain.setString("PlayAgain");

		sf::Text exit;
		exit.setFont(font);
		exit.setScale(0.8, 0.8);
		exit.setPosition(playAgain.getGlobalBounds().left+playAgain.getGlobalBounds().width+80, gameover.getGlobalBounds().top + gameover.getGlobalBounds().height + 20);
		exit.setString("Exit");
		if (m_isPlayAgainSelected)
		{
			playAgain.setFillColor(sf::Color::Green);
		}
		else
		{
			exit.setFillColor(sf::Color::Green);
		}
		rd.draw(gameover);
		rd.draw(playAgain);
		rd.draw(exit);
	}
	
}

void GameScene::CheckCollision()
{
	std::list<RenderGameObject*> listArmy = m_gameMap->GetListArmy();
	for (std::list<RenderGameObject*>::iterator it = listArmy.begin(); it != listArmy.end();it++ )
	{
		

		if ((*it)->GetSpriteAnim()->getGlobalBounds().intersects(m_bar1->GetSprite()->getGlobalBounds()))
		{
			(*it)->Collision(m_bar1);
			m_bar1->Collision((*it));
		}
		if ((*it)->GetSpriteAnim()->getGlobalBounds().intersects(m_bar2->GetSprite()->getGlobalBounds()))
		{
			(*it)->Collision(m_bar2);
			m_bar2->Collision((*it));
		}
		for (std::list<RenderGameObject*>::iterator it1 = listArmy.begin(); it1 != listArmy.end(); it1++)
		{
			if (*it1 != *it && (*it1)->GetSpriteAnim()->getGlobalBounds().intersects((*it)->GetSpriteAnim()->getGlobalBounds()))
			{
				(*it)->Collision(*it1);
				(*it1)->Collision(*it);
			}
		}
	}
	std::list<Bullet*> listArmyBullet = m_gameMap->GetListArmyBullet();
	for (std::list<Bullet*>::iterator bullet = listArmyBullet.begin(); bullet != listArmyBullet.end(); bullet++)
	{
		// Add Enemy if bullet get through 2 walls
		
			sf::FloatRect collisionBullet = (*bullet)->GetAnimation()->GetSprite()->getGlobalBounds();
			sf::FloatRect collisionBar1 = m_bar1->GetSprite()->getGlobalBounds();
			sf::FloatRect collisionBar2 = m_bar2->GetSprite()->getGlobalBounds();
		
			if ((*bullet)->GetDirection() == RenderGameObject::Direction::UP && collisionBullet.top + collisionBullet.height < collisionBar1.top
				&& (*bullet)->m_isFail == false)
			{
				RenderGameObject *newArmy = new Army_Knife();
				newArmy->Init();	
				newArmy->SetPosition((*bullet)->GetPosition().x, -20);
				newArmy->SetDirection(RenderGameObject::Direction::DOWN);
				//newArmy->SetSpeed(ARMY_KNIFE_SPEED*m_difficult);
				m_gameMap->AddArmy(newArmy);
				(*bullet)->m_isFail = true;

				m_lasPosX = newArmy->GetPosition().x;
			}
			else if ((*bullet)->GetDirection() == RenderGameObject::Direction::DOWN && collisionBullet.top  > collisionBar2.top + collisionBar2.height
				&& (*bullet)->m_isFail == false)
			{
				RenderGameObject *newArmy = new Army_Knife();
				newArmy->Init();
				newArmy->SetPosition((*bullet)->GetPosition().x, SCREEN_HEIGHT+20);
				newArmy->SetDirection(RenderGameObject::Direction::UP);
				//newArmy->SetSpeed(ARMY_KNIFE_SPEED*m_difficult);
				m_gameMap->AddArmy(newArmy);
				(*bullet)->m_isFail = true;
				m_lasPosX = newArmy->GetPosition().x;
			}

		if (collisionBullet.intersects(collisionBar1))
		{
			(*bullet)->Collision(m_bar1);
			m_bar1->Collision((*bullet));
		}
		if (collisionBullet.intersects(collisionBar2))
		{
			(*bullet)->Collision(m_bar2);
			m_bar2->Collision((*bullet));
		}
		for (std::list<RenderGameObject*>::iterator army = listArmy.begin(); army != listArmy.end(); army++)
		{
			if (collisionBullet.intersects((*army)->GetSpriteAnim()->getGlobalBounds()) && (*bullet)->GetDirection()!=(*army)->GetDirection())
			{
				if (abs((*bullet)->GetPosition().y - (*army)->GetPosition().y) <= (*army)->GetAnimation()->GetSprite()->getGlobalBounds().height / 2.0)
				{
					(*army)->Collision((*bullet));
					(*bullet)->Collision((*army));
				}
			}
		}
	}
}

void GameScene::ResetGameScene()
{
	Scene *gameScene = new GameScene();
	gameScene->Init();
	SceneManager::GetInstance()->ReplaceScene(gameScene);	
}
void GameScene::ResetGameParameter()
{
	GameGlobal::getInstance()->SetHealth(3);
	GameGlobal::getInstance()->SetScore(0);
	GameTime::GetInstance()->StartCounter();
}