#include "Globals.h"
#include "Application.h"
#include "ModuleLevel.h"

ModuleLevel::ModuleLevel(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	graphics = NULL;


	
}

ModuleLevel::~ModuleLevel()
{}

void ModuleLevel::DrawLevel()
{
	SDL_Rect block_r = block.GetCurrentFrame();
	for (int i = 0; i < 13; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			int a = level[i][j];
			if (a == 1)
				App->renderer->Blit(graphics, 24 + i*TILE, 40 + j*TILE, &wall);
			if (a == 2)
				App->renderer->Blit(graphics, 24 + i*TILE, 40 + j*TILE, &block_r);
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
			if (a == 2)
				App->collision->AddCollider({ 24 + i*TILE, 40 + j*TILE, 16, 16 }, COLLIDER_BLOCK, this);
		}
	}

}



// Load assets
bool ModuleLevel::Start()
{
	LOG("Loading scene");

	graphics = App->textures->Load("GameTiles.png");

	InitLevel();

	SetColliders();

	return true;
}

void ModuleLevel::InitLevel(){
	wall = { 288, 32, 16, 16 };

	block.frames.PushBack({ 322, 15, 16, 16 });
	block.frames.PushBack({ 339, 15, 16, 16 });
	block.frames.PushBack({ 356, 15, 16, 16 });
	block.frames.PushBack({ 373, 15, 16, 16 });
	block.speed = 0.1f;


	//Crea l'escena basica amb aquesta funció

	//0- Nothing
	//1-Wall
	//2-Block

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
	//Put Blocks
	level[6][0] = 2;
	level[8][0] = 1;

	level[4][1] = 2;
	level[10][1] = 1;

	level[1][2] = 2;
	level[8][2] = 2;

	level[2][3] = 2;
	level[4][3] = 2;
	level[8][3] = 1;
	level[10][3] = 1;

	level[0][4] = 1;
	level[2][4] = 2;
	level[4][4] = 2;
	level[8][4] = 2;
	level[10][4] = 2;
	level[11][4] = 2;
	level[12][4] = 2;

	level[12][5] = 2;

	level[1][6] = 2;
	level[2][6] = 2;
	level[3][6] = 1;
	level[4][6] = 1;
	level[5][6] = 2;
	level[6][6] = 2;
	level[11][6] = 2;

	level[0][7] = 2;
	level[4][7] = 2;
	level[10][7] = 2;

	level[2][8] = 2;
	level[4][8] = 2;
	level[6][8] = 2;

	level[0][9] = 2;
	level[4][9] = 2;
	level[8][9] = 2;
	level[10][9] = 2;

	level[3][10] = 1;
	level[4][10] = 2;
	level[7][10] = 2;
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

void ModuleLevel::OnCollision(Collider* c1, Collider* c2)
{
	if (c1->type == COLLIDER_BLOCK)
	{
		if (c2->type == COLLIDER_EXPLOSION)
		{
			level[c1->GetPosLevel().x][c1->GetPosLevel().y] = 3;
			c1->to_delete = true;
			App->particles->AddParticle(App->particles->block, c1->rect.x,c1->rect.y, COLLIDER_WALL, blockT);
		}
	}
}
