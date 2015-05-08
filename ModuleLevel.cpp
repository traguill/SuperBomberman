#include "Globals.h"
#include "Application.h"
#include "ModuleLevel.h"

ModuleLevel::ModuleLevel(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	graphics = NULL;

	wall = { 288, 32, 16, 16 };

	block.frames.PushBack({ 322, 15, 16, 16 });
	block.frames.PushBack({ 339, 15, 16, 16 });
	block.frames.PushBack({ 356, 15, 16, 16 });
	block.frames.PushBack({ 373, 15, 16, 16 });
	block.speed = 0.1f;

	InitLevel();
	
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
			int a = level[j][i];
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
			int a = level[j][i];
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


	SetColliders();

	return true;
}

// UnLoad assets
bool ModuleLevel::CleanUp()
{
	LOG("Unloading Level");

	App->textures->Unload(graphics);


	return true;
}

void ModuleLevel::InitLevel(){
	


	//Crea l'escena basica amb aquesta funció

	//0- Nothing
	//1-Wall
	//2-Block


	int l[11][13] =
	{ 
		
		{ 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		

		
	};

	memcpy(level, l, 13*11*sizeof(int));
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
			if (c1->GetPosLevel().x == c2->GetPosLevel().x || c1->GetPosLevel().y == c2->GetPosLevel().y)
			{
				level[c1->GetPosLevel().x][c1->GetPosLevel().y] = 3;
				c1->to_delete = true;
				App->particles->AddParticle(App->particles->block, c1->rect.x, c1->rect.y, COLLIDER_WALL, blockT);
			}
			
		}
	}
}
