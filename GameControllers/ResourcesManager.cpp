#include "ResourcesManager.h"

ResourcesManager* ResourcesManager::_instance = nullptr;
ResourcesManager::ResourcesManager(void)
{
	// do nothing.
}

ResourcesManager::~ResourcesManager(void)
{
	for (auto spr = m_listTexture.begin(); spr != m_listTexture.end(); ++spr)
	{
		delete spr->second;			// delete sprite
	}
	if (m_listTexture.empty() == false)
		m_listTexture.clear();		// remove all from MAP
}


void ResourcesManager::LoadResource()
{

	sf::Texture* texture = NULL;

	texture = new sf::Texture();
	texture->loadFromFile("Resources/Textures/Backgrounds/Land.png");
	this->m_listTexture.insert(std::pair<eID, sf::Texture*>(eID::TOP_LANE_BACKGROUND, texture));	


	texture = new sf::Texture();
	texture->loadFromFile("Resources/Textures/Bar/Bar.png");
	this->m_listTexture.insert(std::pair<eID, sf::Texture*>(eID::BAR, texture));
	this->LoadTextureInfo(eID::BAR, "Resources//Textures//Bar//Bar.txt");

	texture = new sf::Texture();
	texture->loadFromFile("Resources/Textures/Monsters/YellowRedMonster.png");
	this->m_listTexture.insert(std::pair<eID, sf::Texture*>(eID::REDMONSTER, texture));
	this->LoadTextureInfo(eID::REDMONSTER, "Resources//Textures//Monsters//YellowRedMonster.txt");\


	texture = new sf::Texture();
	texture->loadFromFile("Resources/Textures/Army/blackarmy_knife_move.png");
	this->m_listTexture.insert(std::pair<eID, sf::Texture*>(eID::BLACKARMY_KNIFE_MOVE, texture));
	this->LoadTextureInfo(eID::BLACKARMY_KNIFE_MOVE, "Resources//Textures//Army//blackarmy_knife_move.txt");

	texture = new sf::Texture();
	texture->loadFromFile("Resources/Textures/Army/blackarmy_knife_run_feet.png");
	this->m_listTexture.insert(std::pair<eID, sf::Texture*>(eID::BLACKARMY_RUN_FEET, texture));
	this->LoadTextureInfo(eID::BLACKARMY_RUN_FEET, "Resources//Textures//Army//blackarmy_knife_run_feet.txt");
	
		texture = new sf::Texture();
	texture->loadFromFile("Resources/Textures/Army/blackarmy_knife_attack.png");
	this->m_listTexture.insert(std::pair<eID, sf::Texture*>(eID::BLACKARMY_KNIFE_ATTACK, texture));
	this->LoadTextureInfo(eID::BLACKARMY_KNIFE_ATTACK, "Resources//Textures//Army//blackarmy_knife_attack.txt");

	texture = new sf::Texture();
	texture->loadFromFile("Resources/Textures/Army/blackarmy_walk_feet.png");
	this->m_listTexture.insert(std::pair<eID, sf::Texture*>(eID::BLACKARMY_WALK_FEET, texture));
	this->LoadTextureInfo(eID::BLACKARMY_WALK_FEET, "Resources//Textures//Army//blackarmy_walk_feet.txt");

	texture = new sf::Texture();
	texture->loadFromFile("Resources/Textures/Army/blackarmy_shotgun_move.png");
	this->m_listTexture.insert(std::pair<eID, sf::Texture*>(eID::BLACKARMY_SHOTGUN_MOVE, texture));
	this->LoadTextureInfo(eID::BLACKARMY_SHOTGUN_MOVE, "Resources//Textures//Army//blackarmy_shotgun_move.txt");

	
	texture = new sf::Texture();
	texture->loadFromFile("Resources/Textures/Army/blackarmy_shotgun_shoot.png");
	this->m_listTexture.insert(std::pair<eID, sf::Texture*>(eID::BLACKARMY_SHOTGUN_SHOOT, texture));
	this->LoadTextureInfo(eID::BLACKARMY_SHOTGUN_SHOOT, "Resources//Textures//Army//blackarmy_shotgun_shoot.txt");

	texture = new sf::Texture();
	texture->loadFromFile("Resources/Textures/Effects/Explosion.png");
	this->m_listTexture.insert(std::pair<eID, sf::Texture*>(eID::EXPLOSION, texture));
	this->LoadTextureInfo(eID::EXPLOSION, "Resources//Textures//Effects//Explosion.txt");

	texture = new sf::Texture();
	texture->loadFromFile("Resources/Textures/Lazer/Lazer.png");
	this->m_listTexture.insert(std::pair<eID, sf::Texture*>(eID::LAZER, texture));
	this->LoadTextureInfo(eID::LAZER, "Resources//Textures//Lazer//Lazer.txt");

	texture = new sf::Texture();
	texture->loadFromFile("Resources/Textures/Effects/TeleportPoint.png");
	this->m_listTexture.insert(std::pair<eID, sf::Texture*>(eID::TELEPORT, texture));
	this->LoadTextureInfo(eID::TELEPORT, "Resources//Textures//Effects//TeleportPoint.txt");
}




sf::Texture* ResourcesManager::GetTexture(eID id)
{
	sf::Texture *it = this->m_listTexture.find(id)->second;
	return new sf::Texture(*it);			
}

sf::IntRect ResourcesManager::GetSourceRect(eID id, std::string name)
{

	return m_sourceRectList[id][name];
}

Point ResourcesManager::GetOriginPoint(eID id, std::string name)
{
	return m_originPointList[id][name];
}
void ResourcesManager::LoadTextureInfo(eID id, const char* fileInfoPath)
{
	FILE* file;
	file = fopen(fileInfoPath, "r");

	if (file)
	{
		while (!feof(file))
		{
			sf::IntRect rect =sf::IntRect();
			Point pivot;			
			char name[100];			
			fscanf(file, "%s %d %d %d %d %d %d", &name, &rect.left, &rect.top, &rect.width, &rect.height, &pivot.x, &pivot.y);	
			m_sourceRectList[id][std::string(name)] = rect;
			m_originPointList[id][std::string(name)] = pivot;
		}
	}

	fclose(file);
}


void ResourcesManager::releaseTexture(eID id)
{
	sf::Texture *spr = this->m_listTexture.find(id)->second;				// release image
	delete spr;
	this->m_listTexture.erase(id);		// erase funciotn only remove the pointer from MAP, dont delete it.
}
ResourcesManager* ResourcesManager::getInstance()
{
	if (_instance == nullptr)
		_instance = new ResourcesManager();
	return _instance;
}

void ResourcesManager::release()
{
	delete _instance;			// _instance is static attribute, only static function can delete it.
	_instance = nullptr;
}