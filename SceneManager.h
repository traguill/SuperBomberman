#pragma once

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

class SceneManager : public Module
{
public:
	SceneManager(Application* app, bool start_enabled = true);
	~SceneManager();

	bool Start();
	update_status Update();
	bool CleanUp();

	void Reset();

public:

	float player_speed;
	int player_fire;
	int player_max_bombs;
	


};