#include "Globals.h"
#include "Application.h"
#include "ModuleSceneBoss.h"

ModuleSceneBoss::ModuleSceneBoss(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	graphics = NULL;
	boss_graphics = NULL;
	current_animation_boss = NULL;
	collider_mallet = NULL;


	stage = { 0, 0, 256, 256 };

	boss_idle.frames.PushBack ({ 0, 0, 77, 156 });
	boss_idle.loop = false;

	hit.frames.PushBack({ 77, 0, 77, 156 });
	hit.frames.PushBack({ 154, 0,77, 156 });
	hit.frames.PushBack({ 231, 0,77, 156 });
	hit.speed = 0.05f;
	hit.loop = false;

	red.frames.PushBack({ 0, 140, 77, 156 });
	red.loop = false;

	
}

ModuleSceneBoss::~ModuleSceneBoss()
{}





// Load assets
bool ModuleSceneBoss::Start()
{
	
	LOG("Loading Boss");

	graphics = App->textures->Load("boss_stage.png");
	boss_graphics = App->textures->Load("boss.png");
	App->audio->PlayMusic("music_boss.ogg", 0.0f);
	App->collision->Enable(); // enable before player
	App->timer->Enable();
	App->particles->Enable();
	App->powerUp->Enable();
	App->player->Enable();

	position_boss.x = 88;
	position_boss.y = 30;
	last_position_boss = position_boss;
	direction_boss = downD;
	last_direction_boss = direction_boss;
	current_animation_boss = &boss_idle;

	lifes = 10;
	stunned = false;
	delay_background = 0;
	

	hit.Reset();

	start_time = SDL_GetTicks();
	time = start_time;
	hit_time = time;
	move_time = time;
	stunned_time = time;
	explosion_time = time;

	scene_transition = false;
	game_over = false;
	game_over_boss = false;
	anim_floor_started = false;

	SetColliders();

	return true;
}

void ModuleSceneBoss::SetColliders()
{
	//Blocks Collider
	for (int i = 0; i < 13; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			if (i%2 != 0 && j%2 != 0)
			App->collision->AddCollider({ 24 + i*TILE, 40 + j*TILE, 16, 16 }, COLLIDER_WALL, this);

		}
	}
	

	//Boss Collider
	collider_boss = App->collision->AddCollider({ position_boss.x + 32, position_boss.y + 66, 16, 16 }, COLLIDER_ENEMY, this);
	collider_bossBig = App->collision->AddCollider({ position_boss.x, position_boss.y + 26, 81, 77 }, COLLIDER_BOSS, this);
	collider_mallet = App->collision->AddCollider({0, 0, 16, 16 }, COLLIDER_ENEMY, this);
}

// UnLoad assets
bool ModuleSceneBoss::CleanUp()
{
	LOG("Unloading Boss");
	App->textures->Unload(graphics);
	App->textures->Unload(boss_graphics);
	App->particles->Disable();
	App->timer->Disable();
	App->player->Disable();
	App->collision->Disable();
	App->powerUp->Disable();


	return true;
}


update_status ModuleSceneBoss::Update()
{
	if (game_over_boss == false && start_time + 3000 < time)
	{

		if (!stunned)
			BossIA();
		else
		{
			current_animation_boss = &red;
			if (stunned_time + 500 < time)
				stunned = false;

		}

		if (lifes == 0 && !game_over_boss)
		{
			game_over_boss = true;
			start_explode_time = time;
		}
			
	}
	
	

	//Check Game Over
	if (game_over && !scene_transition)
	{
		App->fade->FadeToBlack(this, App->intro, 3.0f);
		scene_transition = true;
	}
		

	

	// Draw everything --------------------------------------
	App->renderer->Blit(graphics, 0, 24+delay_background, &stage);

	SDL_Rect r = current_animation_boss->GetCurrentFrame();

	App->renderer->Blit(boss_graphics, position_boss.x, position_boss.y ,&r);

	if (game_over_boss && !game_over)
	{
		AnimationExplosion();
		if (start_explode_time + 5000 < time)
			game_over = true;
	}

	time = SDL_GetTicks();

	return UPDATE_CONTINUE;
}

void ModuleSceneBoss::AnimationExplosion(){

	srand(SDL_GetTicks());
	//Create
	if (explosion_time + 100 < time)
	{
		int bombX = (rand() % (28 - (-50) + 1) - 50) + collider_boss->rect.x;
		int bombY = (rand() % (28 - (-50) + 1) - 50) + collider_boss->rect.y;

		App->particles->AddParticle(App->particles->explosion_boss, bombX , bombY, COLLIDER_NONE, explosionT);
		explosion_time = time;
	}
	
}

void ModuleSceneBoss::BossIA(){

	if (time > hit_time + 4000 && current_animation_boss != &hit)
		current_animation_boss = &hit;

	if (time > move_time + 1000)
	{
		GetNewDirection();
		move_time = time;
	}
	


	if (current_animation_boss == &hit)
	{
		if (current_animation_boss->Finished())
		{
			hit.Reset();
			hit_time = time;
			current_animation_boss = &boss_idle;
			collider_mallet->SetPos(0, 0); //Out of the map
			delay_background = 0;
			anim_floor_started = false;
			
		}
		else
		{
			if (current_animation_boss->CurrentFrame() == 2) //Hits with the mallet
			{
				collider_mallet->SetPos(position_boss.x + 32, position_boss.y + 110);
				delay_background = 3;

				if (!anim_floor_started)
				{
					//Create the pieces of floor
					for (int i = 1; i < 6; i++)
					{
						App->particles->AddParticle(App->particles->floor, position_boss.x + 32, position_boss.y + 110, COLLIDER_ENEMY, floorT, -0.5f + (i*1.5f) / 10.0f, float (-(i-3)*(i-3)+8)/6);
					}
					anim_floor_started = true;
				}	
				
			}
				

			return;
		}
			
	}
	current_animation_boss = &boss_idle;

	switch (direction_boss)
	{
	case upD:
		position_boss.y -= VELOCITY_ENEMY;
		break;
	case downD:
		position_boss.y += VELOCITY_ENEMY;
		break;
	case rightD:
		position_boss.x += VELOCITY_ENEMY;
		break;
	case leftD:
		position_boss.x -= VELOCITY_ENEMY;
		break;
	}

	collider_boss->SetPos(position_boss.x +32, position_boss.y + 66);
	collider_bossBig->SetPos(position_boss.x, position_boss.y + 26);
	

	//Limits-----------------------------------------------------------------
	if (collider_boss->rect.x < 24 || collider_boss->rect.x + 16 > 232 || collider_boss->rect.y < 40 || collider_boss->rect.y > 216 - 16)
	{
		position_boss = last_position_boss;
		GetNewDirection();
	}

	last_position_boss = position_boss;

	
}

void ModuleSceneBoss::GetNewDirection(){

	last_direction_boss = direction_boss;

	Looking new_direction = direction_boss;

	srand(SDL_GetTicks());
	while (new_direction == direction_boss)
	{
		int random = rand() % (3 - 0 + 1) + 0; //3-max 0-min
		new_direction = (Looking)random;
	}

	direction_boss = new_direction;

}

void ModuleSceneBoss::CrossWall(Looking direction_boss, Collider* c){


	p2Point<int> tmp;
	tmp.x = c->rect.x;
	tmp.y = c->rect.y;

	switch (direction_boss)
	{
	case upD:
		switch (RightLeft(tmp))
		{
		case 0:	//left
			//GO UP LEFT
			position_boss.x -= 1;
			return;
			break;
		case 2: //right
			//GO UP RIGHT
			position_boss.x += 1;
			return;
			break;
		}
		break;
	case downD:
		switch (RightLeft(tmp))
		{
		case 0:	//Left
			//GO DOWN LEFT
			position_boss.x -= 1;
			return;
			break;
		case 2: //Right
			//GO DOWN RIGHT
			position_boss.x += 1;
			return;
			break;
		}
		break;
	case rightD:
		switch (UpDown(tmp))
		{
		case 0:	//Up
			//RIGHT UP
			position_boss.y -= 1;
			return;
			break;
		case 2: //Down
			//RIGHT DOWN
			position_boss.y += 1;
			return;
			break;
		}
		break;
	case leftD:
		switch (UpDown(tmp))
		{
		case 0:	//Up
			//left UP
			position_boss.y -= 1;
			return;
			break;
		case 2: //Down
			//left DOWN
			position_boss.y += 1;
			return;
			break;
		}
		break;
	}

	switch (last_direction_boss)
	{
	case upD:
		position_boss.y -= 1;
		break;
	case downD:
		position_boss.y += 1;
		break;
	case rightD:
		position_boss.x += 1;
		break;
	case leftD:
		position_boss.x -= 1;
		break;

	}

}

int ModuleSceneBoss::RightLeft(const p2Point<int> p) const{
	int dir = 1; //direction_player 0-left 1-NULL 2-right
	int tolerance = 8;
	if (collider_boss->rect.x + 16 <= p.x + tolerance)
		dir = 0;
	if (collider_boss->rect.x >= p.x + 16 - tolerance)
		dir = 2;

	return dir;
}

int ModuleSceneBoss::UpDown(const p2Point<int> p) const{
	int dir = 1; //Direction 0-Up 1-NULL 2-Down
	int tolerance = 8;
	if (collider_boss->rect.y + 16 <= p.y + tolerance)
		dir = 0;
	if (collider_boss->rect.y >= p.y + 16 - tolerance)
		dir = 2;

	return dir;
}


void ModuleSceneBoss::OnCollision(Collider* c1, Collider* c2)
{
	if (c1->type == COLLIDER_BOSS && c2->type == COLLIDER_EXPLOSION && !stunned)
	{
		lifes--;
		stunned = true;
		stunned_time = time;
		return;
	}

	//Blocks-----------------------------------------------------------------------
	if (c2->type == COLLIDER_BLOCK || c2->type == COLLIDER_WALL || c2->type == COLLIDER_BOMB)
	{
		if (current_animation_boss == &boss_idle)
			CrossWall(direction_boss, c2);
	}

}

