#include "Globals.h"
#include "Application.h"
#include "ModuleScene.h"

ModuleScene::ModuleScene(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	graphics = NULL;
	
	stage = { 0, 0, 256, 192 };

	current_enemies = 0;

}

ModuleScene::~ModuleScene()
{}



void ModuleScene::AddEnemies()
{
	App->enemy->AddEnemy(App->enemy->copter, 216, 197, COLLIDER_ENEMY);
	App->enemy->AddEnemy(App->enemy->copter, 104, 197, COLLIDER_ENEMY);

	current_enemies = 2;
}

// Load assets
bool ModuleScene::Start()
{
	LOG("Loading scene");

	graphics = App->textures->Load("background_stage1.png");
	App->audio->PlayMusic("Area1.ogg", 0.0f);
	App->collision->Enable(); // enable before player
	App->enemy->Enable();
	App->player->Enable();
	App->timer->Enable();
	App->level->Enable();
	
	

	AddEnemies();

	scene_transition = false;
	game_over = false;

	


	return true;
}

// UnLoad assets
bool ModuleScene::CleanUp()
{
	LOG("Unloading scene");
	App->textures->Unload(graphics);
	App->level->Disable();
	App->timer->Disable();
	App->player->Disable();
	App->enemy->Disable();
	App->collision->Disable();

	return true;
}

// Update: draw background
//nota mental: nunca poner un log dentro del update, se sobrecarag todo
update_status ModuleScene::Update()
{
	if (current_enemies == 0)
		game_over = true;
	//Check Game Over
	if (game_over && !scene_transition)
	{
		App->fade->FadeToBlack(this, App->intro, 3.0f);
		scene_transition = true;
	}

	// Draw everything --------------------------------------
	App->renderer->Blit(graphics, 0, 32, &stage);


	return UPDATE_CONTINUE;
}
