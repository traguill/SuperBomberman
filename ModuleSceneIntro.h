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
	SDL_Texture* text;

	SDL_Rect ballon;
	SDL_Rect zepelin;
	Animation zepelin_fire;

	SDL_Rect text_up;
	SDL_Rect text_down;
	SDL_Rect text_menu;

	p2Point<float> ballon_position;
	p2Point<float> zepelin_position;
	p2Point<float> zepelin_fire_position;

	p2Point<float> text_up_position;
	p2Point<float> text_down_position;


	int flash; //0- No 1-Need to flash 2-Has flashed
	Uint32 flash_startime;

	Uint32 start_time;
	Uint32 actual_time;

	bool scene_transition;

	unsigned int fx;
};