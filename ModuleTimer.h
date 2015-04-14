#pragma once

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

class ModuleTimer : public Module
{
public:
	ModuleTimer(Application* app, bool start_enabled = true);
	~ModuleTimer();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphics;
	Animation* current_status;
	Animation status;
	
	
};