#pragma once

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

	//other methods
	
	
	void AddEnemies();

public:

	SDL_Texture* graphics;
	SDL_Rect stage;
	
	bool scene_transition;
	bool game_over;

	int current_enemies;

};