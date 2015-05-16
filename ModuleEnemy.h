#pragma once
#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "p2List.h"
#include "ModuleCollision.h"

enum TypeE{  
	copterT,
	nullE,
};

struct Enemy
{
	Looking direction_enemy;
	Animation anim;
	unsigned int fx;
	p2Point<int> position;
	p2Point<int> last_position;
	p2Point<int> speed;
	bool fx_played;
	Collider* collider;
	TypeE type;
	Enemy();
	Enemy(const Enemy& p);
	~Enemy();
	bool Update();
	void GetNewDirection();
};

class ModuleEnemy : public Module
{
public:
	ModuleEnemy(Application* app, bool start_enabled = true);
	~ModuleEnemy();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider*, Collider*);

	Collider* AddEnemy(const Enemy& Enemy, int x, int y, COLLIDER_TYPE = COLLIDER_NONE, TypeE _type = nullE);

private:

	SDL_Texture* graphics;
	p2List<Enemy*> active;

public:

	Enemy copter;


};