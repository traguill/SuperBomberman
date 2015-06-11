#include "Globals.h"
#include "Application.h"
#include "ModuleSceneBoss.h"

ModuleSceneBoss::ModuleSceneBoss(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	graphics = NULL;


	stage = { 0, 0, 256, 256 };

	
}

ModuleSceneBoss::~ModuleSceneBoss()
{}





// Load assets
bool ModuleSceneBoss::Start()
{
	
	LOG("Loading Boss");

	graphics = App->textures->Load("boss_stage.png");
	App->audio->PlayMusic("music_boss.ogg", 0.0f);
	App->collision->Enable(); // enable before player s
	App->particles->Enable();
	App->powerUp->Enable();
	App->player->Enable();
	App->boss_enemy->Enable();
	App->timer->Enable();

	scene_transition = false;
	game_over = false;
	game_win = false;

	return true;
}



// UnLoad assets
bool ModuleSceneBoss::CleanUp()
{
	LOG("Unloading Boss");
	App->textures->Unload(graphics);
	App->boss_enemy->Disable();
	App->particles->Disable();
	App->timer->Disable();
	App->player->Disable();
	App->collision->Disable();
	App->powerUp->Disable();
	


	return true;
}


update_status ModuleSceneBoss::Update()
{
	
	//Check Game Over
	if (game_over && !scene_transition)
	{
		App->fade->FadeToBlack(this, App->intro, 3.0f);
		scene_transition = true;
	}
	//Check win
	if (game_win && !scene_transition)
	{
		App->fade->FadeToBlack(this, App->credits, 3.0f);
		scene_transition = true;
	}
		

	

	// Draw everything --------------------------------------
	App->renderer->Blit(graphics, 0, 24+App->boss_enemy->delay_background, &stage);

	

	return UPDATE_CONTINUE;
}


