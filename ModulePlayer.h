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

public:

	SDL_Texture* graphics;
	//TODO:
	//Add here all the animations of the player and variables
	Animation idle;
	Animation right;
	Animation left;
	Animation up;
	Animation down;
	p2Point<int> position;

};