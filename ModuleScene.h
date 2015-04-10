/*#pragma once
#include "Module.h"
#include "Animation.h"
#include "Globals.h"

class ModuleScene : public Module
{
public:
	ModuleScene(Application* app, bool start_enabled = true);
	~ModuleScene();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* status;
	
};