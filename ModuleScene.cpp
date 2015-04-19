#include "Globals.h"
#include "Application.h"
#include "ModuleScene.h"

ModuleScene::ModuleScene(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	graphics = NULL;
	background = NULL;
	
	stage = { 0, 0, 256, 192 };

	tiles.PushBack({ 305, 32, 16, 16 });//No serveix de res nomes es per omplir
	tiles.PushBack({ 288, 32, 16, 16 });//10//Son les cases del mig de l'escenari

	for (int i = 0; i < 13; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			if (i % 2 != 0 && j % 2 != 0)
				level[i][j] = 1;
			else
				level[i][j] = 0;
		}
	}
	
}

ModuleScene::~ModuleScene()
{}

void ModuleScene::PaintLevel()
{
	for (int i = 0; i < 13; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			int a = level[i][j];
			if (a != 0)
			App->renderer->Blit(graphics, 24 + i*TILE, 40 + j*TILE, &(tiles[a]));
		}
	}
}

void ModuleScene::SetColliders()
{
	for (int i = 0; i < 13; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			int a = level[i][j];
			if (a == 1)
				App->collision->AddCollider({ 24 + i*TILE, 40 + j*TILE, 16, 16 }, COLLIDER_WALL, this);
		}
	}
	
}

void ModuleScene::AddEnemies()
{
	App->enemy->AddEnemy(App->enemy->copter, 60, 10, COLLIDER_ENEMY);
}

// Load assets
bool ModuleScene::Start()
{
	LOG("Loading scene");

	graphics = App->textures->Load("GameTiles.png");
	background = App->textures->Load("background_stage1.png");
	App->collision->Enable(); // enable before player
	App->enemy->Enable();
	App->player->Enable();
	App->timer->Enable();

	SetColliders();
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
	//Check Game Over
	if (game_over && !scene_transition)
	{
		App->fade->FadeToBlack(this, App->intro, 3.0f);
		scene_transition = true;
	}

	// Draw everything --------------------------------------
	App->renderer->Blit(background, 0, 32, &stage);
	PaintLevel();


	return UPDATE_CONTINUE;
}
