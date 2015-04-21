#include "Globals.h"
#include "Application.h"
#include "ModuleLevel.h"

ModuleLevel::ModuleLevel(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	graphics = NULL;


	wall = { 288, 32, 16, 16 };


	//Crea l'escena basica amb aquesta funció
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

ModuleLevel::~ModuleLevel()
{}

void ModuleLevel::DrawLevel()
{
	for (int i = 0; i < 13; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			int a = level[i][j];
			if (a == 1)
				App->renderer->Blit(graphics, 24 + i*TILE, 40 + j*TILE, &wall);
		}
	}
}

void ModuleLevel::SetColliders()
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



// Load assets
bool ModuleLevel::Start()
{
	LOG("Loading scene");

	graphics = App->textures->Load("GameTiles.png");


	SetColliders();

	return true;
}

// UnLoad assets
bool ModuleLevel::CleanUp()
{
	LOG("Unloading scene");

	App->textures->Unload(graphics);


	return true;
}

// Update: draw background
update_status ModuleLevel::Update()
{
	

	// Draw everything --------------------------------------
	DrawLevel();


	return UPDATE_CONTINUE;
}