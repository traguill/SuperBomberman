#pragma once

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct Floor{
	p2Point<int> position;
	Collider* collider;
	p2Point<float> velocity;
	bool isBig;
	Floor();
	~Floor();
};


class ModuleSceneBoss : public Module
{
public:
	ModuleSceneBoss(Application* app, bool start_enabled = true);
	~ModuleSceneBoss();

	bool Start();
	update_status Update();
	bool CleanUp();

	void OnCollision(Collider*, Collider*);

	//other methods
	void BossIA();
	void GetNewDirection();
	void SetColliders();

	void CrossWall(Looking direction_player, Collider* c);

	//Auxiliar methods
private:
	int RightLeft(const p2Point<int> p)const;
	int UpDown(const p2Point<int> p)const;

public:

	SDL_Texture* graphics;
	SDL_Rect stage;

	SDL_Texture* boss_graphics;
	Animation boss_idle;
	Animation hit;
	Animation red; //When is hit by a bomb
	Animation* current_animation_boss;
	Collider* collider_boss;
	Collider* collider_mallet;
	Collider* collider_bossBig;

	p2Point<int> position_boss;
	p2Point<int> last_position_boss;
	Looking direction_boss;
	Looking last_direction_boss;

	Uint32 time;
	Uint32 hit_time;
	Uint32 move_time;
	Uint32 stunned_time;

	unsigned int lifes;
	bool stunned;

	bool scene_transition;
	bool game_over;

	int delay_background;

	p2DynArray<Floor*> pieces_floor;
	bool anim_floor_started;



};