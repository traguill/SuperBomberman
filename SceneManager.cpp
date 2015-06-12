#include "Globals.h"
#include "Application.h"
#include "SceneManager.h"

SceneManager::SceneManager(Application* app, bool start_enabled) : Module(app, start_enabled)
{




}

SceneManager::~SceneManager()
{}

// Load assets
bool SceneManager::Start()
{
	LOG("Loading SceneManager");

	player_fire = 1;
	player_max_bombs = 1;
	player_speed = 1;
	player_lifes = 5;



	return true;
}

// UnLoad assets
bool SceneManager::CleanUp()
{
	LOG("Unloading SceneManager");


	return true;
}

// Update: draw background
update_status SceneManager::Update()
{
	if (App->particles->IsEnabled())
		player_fire = App->particles->fire;

	if (App->player->IsEnabled())
	{
		player_max_bombs = App->player->max_bombs;
		player_speed = App->player->speed;
		player_lifes = App->player->lifes;
	}


	return UPDATE_CONTINUE;
}

void SceneManager::Reset()
{
	player_fire = 1;
	player_max_bombs = 1;
	player_speed = 1;
	player_lifes = 5;
}