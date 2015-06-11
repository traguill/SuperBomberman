#pragma once
#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"


class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider*, Collider*);
	void CrossWall(Looking direction_player, Collider* c); 

	//Auxiliar methods
private:
	int RightLeft(const p2Point<int> p)const;
	int UpDown(const p2Point<int> p)const;
	void CheckLimits();
public:

	SDL_Texture* graphics;
	Collider* collider;
	Animation* current_animation;
	
	Looking direction_player;
	Animation idle;
	Animation right;
	Animation left;
	Animation up;
	Animation down;
	Animation die;
	Animation win;
	p2Point<float> position;
	p2Point<int> positon_level; //Posició en la matriu nivell.
	p2Point<float> last_position;
	Collider* last_bomb;
	bool bomb_collision;
	bool game_over_player; //S'encarrega de gestionar tot lo del player abans de tancar el joc.
	bool game_win;
	int current_bombs;
	int max_bombs;
	float speed;
	int lifes;

	unsigned int fxStep;
	unsigned int fxPut;
	unsigned int fxDie;
	int audioChannel;
};