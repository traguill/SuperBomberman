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

	void PaintLevel();

public:

	SDL_Texture* graphics;
	p2DynArray<SDL_Rect> tiles;
	p2Point<int> position;
	int level[12][16];


};