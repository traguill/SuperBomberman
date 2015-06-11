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


public:

	SDL_Texture* graphics;
	SDL_Rect stage;

	bool scene_transition;
	bool game_over;


};