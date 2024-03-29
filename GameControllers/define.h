#pragma once
#define SCREEN_WIDTH 400
#define SCREEN_HEIGHT 700
#define LIMIT_FPS 120

#define ARMY_NUM_LANE 10

#define ARMY_KNIFE_SPEED 70.0f
#define ARMY_KNIFE_TELEPORT_DISTANCE 78
#define ARMY_SHOTGUN_SPEED 100.0f
#define ARMY_SHOTGUN_DISTANCE_MOVE_SHOOT 80.0f
#define BULLET_SPEED 230.0f
enum eID
{
	BAR,
	REDMONSTER,
	YELLOWMONSTER,
	BLACKARMY_KNIFE_MOVE,
	BLACKARMY_RUN_FEET,
	BLACKARMY_KNIFE_ATTACK,
	BLACKARMY_WALK_FEET,
	BLACKARMY_SHOTGUN_MOVE,
	BLACKARMY_SHOTGUN_SHOOT,
	EXPLOSION,
	LAZER,
	TOP_LANE_BACKGROUND,
	TELEPORT
};
enum eIDSound
{
	MENU_SOUND,
	GAME_PLAYING_SOUND,
	EXPLOSION_SOUND
};



