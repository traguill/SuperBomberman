#pragma once
#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"


class ModuleEnemy : public Module
{
public:
	ModuleEnemy(Application* app, bool start_enabled = true);
	~ModuleEnemy();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider*, Collider*);



public:

	SDL_Texture* graphics;
	Collider* collider;
	Animation* current_animation;
	Animation idle;
	Animation right;
	Animation left;
	Animation up;
	Animation down;
	Animation die;
	p2Point<int> position;
	p2Point<int> last_position;

};