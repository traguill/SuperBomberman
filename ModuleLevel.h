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
	void OnCollision(Collider*, Collider*);


	void DrawLevel();
	void SetColliders();
	void InitLevel();

public:

	SDL_Texture* graphics;
	SDL_Rect wall;
	Animation block;
	int level[11][13];
};