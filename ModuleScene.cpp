#include "Globals.h"
#include "Application.h"
#include "ModuleScene.h"

ModuleScene::ModuleScene(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	graphics = NULL;

	position.x = 0;
	position.y = 26;

	//tiles distribution to numbers
	tiles.PushBack({ 305, 49, 16, 16 });//0
	tiles.PushBack({ 271, 32, 16, 16 });//1
	tiles.PushBack({ 305, 15, 16, 16 });//2
	tiles.PushBack({ 288, 49, 16, 16 });//3
	tiles.PushBack({ 271, 15, 16, 16 });//4
	tiles.PushBack({ 271, 49, 16, 16 });//5
	tiles.PushBack({ 254, 32, 16, 16 });//6
	tiles.PushBack({ 254, 15, 16, 16 });//7
	tiles.PushBack({ 254, 49, 16, 16 });//8

	//tiles distribution to level (preguntar al ricard perque no em funciona
	/* int level[12][16] = {   { 7, 4, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 4, 7 },
							{ 6, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 6 },
							{ 6, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 6 },
							{ 6, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 6 },
							{ 6, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 6 },
							{ 6, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 6 },
							{ 6, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 6 },
							{ 6, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 6 },
							{ 6, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 6 },
							{ 6, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 6 },
							{ 6, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 6 },
							{ 8, 5, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 5, 8 }, };*/
}

ModuleScene::~ModuleScene()
{}
//TODO: modificar perque va moooolt lent
void ModuleScene::PaintLevel()
{
	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			int a = 0;
			LOG("value of the tile is: %d /n", a);
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
update_status ModuleScene::Update()
{
	// Draw everything --------------------------------------
	PaintLevel();

	return UPDATE_CONTINUE;
}
