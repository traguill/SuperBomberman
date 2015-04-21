#pragma once

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

class ModuleLevel : public Module
{
public:
	ModuleLevel(Application* app, bool start_enabled = true);
	~ModuleLevel();

	bool Start();
	update_status Update();
	bool CleanUp();

	void DrawLevel();
	void SetColliders();
	

public:

	SDL_Texture* graphics;
	SDL_Rect wall;
	int level[13][11];
};