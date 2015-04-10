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
	Animation* current_animation;
	//TODO: la variable de current_orientation serveix per quan es quedi quiet es quedi mirant en la direccio en la que es movia
	//pero de moment nomes aconsegueixo que segueixi canviant els frames en aquella direcció
	//Animation current_orientation;
	Animation idle;
	Animation right;
	Animation left;
	Animation up;
	Animation down;
	p2Point<int> position;

};