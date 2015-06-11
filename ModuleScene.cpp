#include "Globals.h"
#include "Application.h"
#include "ModuleScene.h"

ModuleScene::ModuleScene(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	graphics = NULL;
	
	stage = { 0, 0, 256, 192 };
}

ModuleScene::~ModuleScene()
{}





// Load assets
bool ModuleScene::Start()
{
	LOG("Loading scene");
	
	current_enemies = 0;

	graphics = App->textures->Load("background_stage1.png");
	App->audio->PlayMusic("Area1.ogg", 0.0f);
	App->collision->Enable(); // enable before player
	App->enemy->Enable(); //Enable before level//enemy s'hauria de fer enable a level, ja que son diferents per cadascun
	App->level->Enable();
	App->player->Enable();
	App->timer->Enable();
	App->particles->Enable();
	App->powerUp->Enable();


	scene_transition = false;
	game_over = false;

	return true;
}

// UnLoad assets
bool ModuleScene::CleanUp()
{
	LOG("Unloading scene");
	App->textures->Unload(graphics);
	App->particles->Disable();
	App->timer->Disable();
	App->player->Disable();
	App->level->Disable();
	App->enemy->Disable();
	App->collision->Disable();
	App->powerUp->Disable();

	return true;
}

// Update: draw background
update_status ModuleScene::Update()
{
	if (current_enemies == 0 && App->player->position.x == App->particles->position_portal_y && App->player->position.y - 16 == App->particles->position_portal_x)
	{
		App->player->game_win = true;
	}
		
	//Check Game Over
	if (game_over && !scene_transition)
	{
		if (App->player->game_over_player)
			App->fade->FadeToBlack(this, App->intro, 3.0f);
		if (App->player->game_win)
			App->fade->FadeToBlack(this, App->boss, 3.0f);
		scene_transition = true;
	}

	// Draw everything --------------------------------------
	App->renderer->Blit(graphics, 0, 32, &stage);


	return UPDATE_CONTINUE;
}
