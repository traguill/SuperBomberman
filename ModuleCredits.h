#pragma once

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

class ModuleCredits : public Module
{
public:
	ModuleCredits(Application* app, bool start_enabled = true);
	~ModuleCredits();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphics;
	SDL_Rect text;
	bool scene_transition; 
	float positionY;


};