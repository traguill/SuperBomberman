#pragma once
#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "p2List.h"
#include "ModuleCollision.h"

struct Enemy
{
	Animation anim;
	p2Point<int> position;
	p2Point<int> speed;
	Collider* collider;
	Enemy();
	Enemy(const Enemy& e);
	~Enemy();
	bool Update();
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

	Collider* AddEnemy(const Enemy& enemy, int x, int y, COLLIDER_TYPE = COLLIDER_NONE);

private:

	SDL_Texture* graphics;
	p2List<Enemy*> active;

public:
	Enemy copter;
	

};