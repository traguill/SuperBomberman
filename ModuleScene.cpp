#include "Globals.h"
#include "Application.h"
#include "ModuleScene.h"

ModuleScene::ModuleScene(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	graphics = NULL;

	

	//tiles distribution to numbers
	tiles.PushBack({ 305, 49, 16, 16 });//0//terra estandard
	tiles.PushBack({ 305, 32, 16, 16 });//1//terra sota edifici
	tiles.PushBack({ 305, 15, 16, 16 });//2/pared superior
	tiles.PushBack({ 288, 49, 16, 16 });//3/pared inferior
	tiles.PushBack({ 271, 15, 16, 16 });//4//*pareds del costat esquerra 
	tiles.PushBack({ 271, 49, 16, 16 });//5*/
	tiles.PushBack({ 254, 32, 16, 16 });//6*/
	tiles.PushBack({ 254, 15, 16, 16 });//7*7
	tiles.PushBack({ 254, 49, 16, 16 });//8*/
	tiles.PushBack({ 271, 32, 16, 16 });//9*/
	tiles.PushBack({ 288, 32, 16, 16 });//10//Son les cases del mig de l'escenari

	//TODO: s'han de copiar i invertir les imatges dels tiles de l'esquerra per poderles utilitzar a la dreta
	//Cuidado, pot fer que el archiu sigui incompatible segons com es fagi, en tot cas, els cambis millor guardarlos en un archiu apart per comprovar


	int l[13][17] = { { 7, 4, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 4, 7 },
	{ 6, 9, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9, 6 },
	{ 6, 9, 0, 10, 0, 10, 0, 10, 0, 10, 0, 10, 0, 10, 0, 9, 6 },
	{ 6, 9, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 9, 6 },
	{ 6, 9, 0, 10, 0, 10, 0, 10, 0, 10, 0, 10, 0, 10, 0, 9, 6 },
	{ 6, 9, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 9, 6 },
	{ 6, 9, 0, 10, 0, 10, 0, 10, 0, 10, 0, 10, 0, 10, 0, 9, 6 },
	{ 6, 9, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 9, 6 },
	{ 6, 9, 0, 10, 0, 10, 0, 10, 0, 10, 0, 10, 0, 10, 0, 9, 6 },
	{ 6, 9, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 9, 6 },
	{ 6, 9, 0, 10, 0, 10, 0, 10, 0, 10, 0, 10, 0, 10, 0, 9, 6 },
	{ 6, 9, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 9, 6 },
	{ 8, 5, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 5, 8 }
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
			App->renderer->Blit(graphics, -8 + j*TILE, 26 + i*TILE, &(tiles[a]));
		}
	}
}

void ModuleScene::SetColliders()
{
	App->collision->AddCollider({0,0, 16, 16 }, COLLIDER_WALL, this);
}

// Load assets
bool ModuleScene::Start()
{
	LOG("Loading scene");

	graphics = App->textures->Load("GameTiles.png");
	App->collision->Enable(); // enable before player
	App->player->Enable();
	App->timer->Enable();

	SetColliders();

	return true;
}

// UnLoad assets
bool ModuleScene::CleanUp()
{
	LOG("Unloading scene");

	App->textures->Unload(graphics);
	App->player->Disable();
	App->collision->Disable();

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
