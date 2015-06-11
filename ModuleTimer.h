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
	SDL_Rect bar;
	SDL_Rect zero;
	SDL_Rect one;
	SDL_Rect two;
	SDL_Rect three;
	SDL_Rect four;
	SDL_Rect five;
	SDL_Rect six;
	SDL_Rect seven;
	SDL_Rect eight;
	SDL_Rect nine;



};