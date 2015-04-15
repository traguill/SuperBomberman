#include "Globals.h"
#include "Application.h"
#include "ModuleScene.h"

ModuleScene::ModuleScene(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	graphics = NULL;

	position.x = -8;
	position.y = 26;

	//tiles distribution to numbers
	tiles.PushBack({ 305, 49, 16, 16 });//0//terra estandard
	tiles.PushBack({ 305, 32, 16, 16 });//1//terra sota edifici
	tiles.PushBack({ 305, 15, 16, 16 });//2
	tiles.PushBack({ 288, 49, 16, 16 });//3
	tiles.PushBack({ 271, 15, 16, 16 });//4
	tiles.PushBack({ 271, 49, 16, 16 });//5
	tiles.PushBack({ 254, 32, 16, 16 });//6
	tiles.PushBack({ 254, 15, 16, 16 });//7
	tiles.PushBack({ 254, 49, 16, 16 });//8
	tiles.PushBack({ 271, 32, 16, 16 });//9//Son les cases del mig de l'escenari
	tiles.PushBack({ 288, 32, 16, 16 });//10//terra a sota de edifici, no colisionable

	//tiles distribution to level (preguntar al ricard perque no em funciona
	//level[0][0] = 2;
	//level[0] = { 7, 4, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 4, 7 };

	
	int l[13][17] = {   { 7, 4,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 4, 7 },
						{ 6, 9,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 9, 6 },
						{ 6, 9,  0, 10,  0, 10,  0, 10,  0, 10,  0, 10,  0, 10,  0, 9, 6 },
						{ 6, 9,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0, 9, 6 },
						{ 6, 9,  0, 10,  0, 10,  0, 10,  0, 10,  0, 10,  0, 10,  0, 9, 6 },
						{ 6, 9,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0, 9, 6 },
						{ 6, 9,  0, 10,  0, 10,  0, 10,  0, 10,  0, 10,  0, 10,  0, 9, 6 },
						{ 6, 9,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0, 9, 6 },
						{ 6, 9,  0, 10,  0, 10,  0, 10,  0, 10,  0, 10,  0, 10,  0, 9, 6 },
						{ 6, 9,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0, 9, 6 },
						{ 6, 9,  0, 10,  0, 10,  0, 10,  0, 10,  0, 10,  0, 10,  0, 9, 6 },
						{ 6, 9,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0, 9, 6 },
						{ 8, 5,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3, 5, 8 } 
	};

	memcpy(level, l, sizeof(level));
}

ModuleScene::~ModuleScene()
{}

void ModuleScene::PaintLevel()
{
	for (int i = 0; i < 13; i++)
	{
		for (int j = 0; j < 17; j++)
		{
			int a = level[i][j];
			App->renderer->Blit(graphics, position.x + j*TILE, position.y + i*TILE, &(tiles[a]));
		}
	}
}


// Load assets
bool ModuleScene::Start()
{
	LOG("Loading scene");

	graphics = App->textures->Load("Game/GameTiles.png");
	App->player->Enable();

	return true;
}

// UnLoad assets
bool ModuleScene::CleanUp()
{
	LOG("Unloading scene");

	App->textures->Unload(graphics);
	App->player->Disable();

	return true;
}

// Update: draw background
//nota mental: nunca poner un log dentro del update, se sobrecarag todo
update_status ModuleScene::Update()
{

	// Draw everything --------------------------------------
	PaintLevel();

	return UPDATE_CONTINUE;
}
