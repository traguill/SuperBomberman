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


public:

	SDL_Texture* graphics;
	Collider* collider;
	Animation* current_animation;
	enum looking {				//Les variables tenen una D al final de direccio, no es poden dir up,down,right i left perque es confonen amb les animacions.		
		downD = 0,
		rightD = 1,
		leftD = 2,
		upD = 3
	};
	looking direction;
	Animation idle;
	Animation right;
	Animation left;
	Animation up;
	Animation down;
	Animation die;
	p2Point<int> position;
	p2Point<int> positon_level; //Posició en la matriu nivell.
	p2Point<int> last_position;
	Collider* last_bomb;
	bool bomb_collision;
	bool game_over_player; //S'encarrega de gestionar tot lo del player abans de tancar el joc.
};