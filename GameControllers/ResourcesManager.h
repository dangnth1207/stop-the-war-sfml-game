#pragma once
#include "SFML\Graphics.hpp"
#include "define.h"
#include <map> 
#include <iostream>
#include "Point.h"

class ResourcesManager
{
public:
	static ResourcesManager* getInstance();
	static void release();

	void LoadResource();
	sf::Texture* GetTexture(eID id);

	sf::IntRect GetSourceRect(eID id, std::string name);
	void LoadTextureInfo(eID id, const char* fileInfoPath);
	Point GetOriginPoint(eID id, std::string name);

	void releaseTexture(eID id);	

	~ResourcesManager(void);


private:
	ResourcesManager(void);
	static ResourcesManager* _instance;
	std::map<eID, sf::Texture*> m_listTexture;
	std::map<eID, std::map<std::string, sf::IntRect> > m_sourceRectList;
	std::map<eID, std::map<std::string, Point >> m_originPointList;

	//Sprite* loadXMLDoc(LPD3DXSPRITE spritehandle, LPWSTR path);
};