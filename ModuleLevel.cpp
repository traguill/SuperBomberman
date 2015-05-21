#include "Globals.h"
#include "Application.h"
#include "ModuleLevel.h"

ModuleLevel::ModuleLevel(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	graphics = NULL;

	wall = { 195, 0, 17, 17 };

	block.frames.PushBack({ 128, 0, 17, 18 });
	block.frames.PushBack({ 145, 0, 17, 18 });
	block.frames.PushBack({ 162, 0, 17, 18 });
	block.frames.PushBack({ 179, 0, 16, 18 });
	block.speed = 0.1f;



	portal.frames.PushBack({ 80, 32, 16, 15 });
	portal.frames.PushBack({ 80, 48, 16, 15 });
	portal.speed = 0.1f;

	
	

}

ModuleLevel::~ModuleLevel()
{}

void ModuleLevel::DrawLevel()
{
	SDL_Rect block_r = block.GetCurrentFrame();

	SDL_Rect portal_r = portal.GetCurrentFrame();


	//Blocks

	for (int i = 0; i < 13; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			int a = level[j][i];
			if (a == 1)
				App->renderer->Blit(graphics, 24 + i*TILE, 40 + j*TILE, &wall);
			if (a == 2)
				App->renderer->Blit(graphics, 24 + i*TILE, 40 + j*TILE, &block_r);
			if (a == 3)
				App->renderer->Blit(graphics, 24 + i*TILE, 40 + j*TILE, &portal_r);
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
			if (a == 4)
			{
				App->powerUp->ActivePowerUp(24 + i*TILE, 40 + j*TILE);
			}
		}
	}

}



// Load assets
bool ModuleLevel::Start()
{
	LOG("Loading Level");

	graphics = App->textures->Load("powerups_obstacles.png");
	num_portals = 0;
	num_blocks = 7;


	App->powerUp->AddPowerUp(POWERUP_BOMB);
	App->powerUp->AddPowerUp(POWERUP_SPEED);
	App->powerUp->AddPowerUp(POWERUP_FIRE);

	InitLevel();
	SetColliders();
	InitEnemies();

	return true;
}

// UnLoad assets
bool ModuleLevel::CleanUp()
{
	LOG("Unloading Level");

	App->textures->Unload(graphics);

	App->powerUp->levelPowerUps.Clear();

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
		{ 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0 },
		{ 0, 4, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		

		
	};

	memcpy(level, l, 13*11*sizeof(int));
}

void ModuleLevel::InitEnemies(){
	App->enemy->AddEnemy(App->enemy->copter, 24 + 5 * TILE, 40 + 6* TILE, COLLIDER_ENEMY, copterT);
 	App->scene->current_enemies++;
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
								
				num_blocks--;

				App->particles->AddParticle(App->particles->block, c1->rect.x, c1->rect.y, COLLIDER_WALL, blockT);

				c1->to_delete = true;
				
			}
						
		}
		
	}
	
}
