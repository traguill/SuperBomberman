#pragma once

#include "Module.h"
#include "Animation.h"
#include "Globals.h"



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
	void AnimationExplosion();

public:

	SDL_Texture* graphics;
	SDL_Rect stage;

	SDL_Texture* boss_graphics;
	Animation boss_idle;
	Animation hit;
	Animation red; //When is hit by a bomb
	Animation explosion_boss;
	Animation* current_animation_boss;
	Collider* collider_boss;
	Collider* collider_mallet;
	Collider* collider_bossBig;

	p2Point<int> position_boss;
	p2Point<int> last_position_boss;
	Looking direction_boss;
	Looking last_direction_boss;

	//Timers
	Uint32 time;
	Uint32 hit_time;
	Uint32 move_time;
	Uint32 stunned_time;
	Uint32 explosion_time;
	Uint32 start_explode_time;
	Uint32 start_time;

	unsigned int lifes;
	bool stunned;

	bool scene_transition;
	bool game_over;
	bool game_over_boss;

	int delay_background;

	
	bool anim_floor_started;
	

};