#pragma once
#include "SFML\Graphics.hpp"
#include "../Scenes/Scene.h"
class SceneManager
{
public:
	static SceneManager *GetInstance();
	~SceneManager();

	Scene* GetCurrentScene();
	void Update(float dt);
	void Render(sf::RenderWindow &);
	void ReplaceScene(Scene *scene);
private:
	SceneManager();
	static SceneManager *mInstance;
	Scene *mCurrentScene;

};