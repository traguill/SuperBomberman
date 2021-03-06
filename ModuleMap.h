#pragma once

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

class ModuleMap : public Module
{
public:
	ModuleMap(Application* app, bool start_enabled = true);
	~ModuleMap();

	bool Start();
	update_status Update();
	bool CleanUp();

	//other methods



public:

	SDL_Texture* graphics;
	Animation map;
	Uint32 time;
	bool scene_transition;

	

};