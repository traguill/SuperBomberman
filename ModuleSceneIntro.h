#pragma once
#include "Module.h"
#include "Animation.h"
#include "Globals.h"

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* background;
	SDL_Texture* planes;
	SDL_Rect ballon;
	SDL_Rect zepelin;
	SDL_Rect zepelin_fire;
	unsigned int fx;
};