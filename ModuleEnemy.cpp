#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleEnemy.h"

ModuleEnemy::ModuleEnemy(Application* app, bool start_enabled) : Module(app, start_enabled), graphics(NULL)
{
	// copter Enemy
	copter.left.frames.PushBack({ 0, 0, 16, 24 });
	copter.left.frames.PushBack({ 16, 0, 16, 24 });
	copter.left.frames.PushBack({ 32, 0, 16, 24 });
	copter.left.frames.PushBack({ 48, 0, 16, 24 });
	copter.left.speed = 0.8f;


	copter.down.frames.PushBack({ 64, 0, 16, 24 });
	copter.down.frames.PushBack({ 80, 0, 16, 24 });
	copter.down.frames.PushBack({ 96, 0, 16, 24 });
	copter.down.frames.PushBack({ 112, 0, 16, 24 });
	copter.down.speed = 0.8f;

	copter.up.frames.PushBack({ 128, 0, 16, 24 });
	copter.up.frames.PushBack({ 144, 0, 16, 24 });
	copter.up.frames.PushBack({ 160, 0, 16, 24 });
	copter.up.frames.PushBack({ 176, 0, 16, 24 });
	copter.up.speed = 0.8f;

	copter.right.frames.PushBack({ 192, 0, 16, 24 });
	copter.right.frames.PushBack({ 208, 0, 16, 24 });
	copter.right.frames.PushBack({ 224, 0, 16, 24 });
	copter.right.frames.PushBack({ 240, 0, 16, 24 });
	copter.right.speed = 0.8f;

	explosion_copter.up.frames.PushBack({ 0,   198, 22, 40});
	explosion_copter.up.frames.PushBack({ 22,  198, 22, 40 });
	explosion_copter.up.frames.PushBack({ 44,  198, 22, 40 });
	explosion_copter.up.frames.PushBack({ 66,  198, 22, 40 });
	explosion_copter.up.frames.PushBack({ 88,  198, 22, 40 });
	explosion_copter.up.frames.PushBack({ 110,  198, 22, 40 });
	explosion_copter.up.frames.PushBack({ 132, 198, 22, 40 });
	explosion_copter.up.frames.PushBack({ 154, 198, 22, 40 });
	explosion_copter.up.speed = 0.25f;
	explosion_copter.up.loop = false;
}

ModuleEnemy::~ModuleEnemy()
{}

// Load assets
bool ModuleEnemy::Start()
{
	LOG("Loading Enemy");
	graphics = App->textures->Load("Enemy.png");

	fxExplode = App->audio->LoadFx("game/Audios/Gameplay/enemy_explosion.wav");

	return true;
}

// Unload assets
bool ModuleEnemy::CleanUp()
{
	LOG("Unloading Enemy");
	App->textures->Unload(graphics);

	p2List_item<Enemy*>* item = active.getLast();

	while (item != NULL)
	{
		delete item->data;
		item = item->prev;
	}

	active.clear();

	return true;
}

// Update: draw background
update_status ModuleEnemy::Update()
{
	p2List_item<Enemy*>* tmp = active.getFirst();
	p2List_item<Enemy*>* tmp_next = active.getFirst();

	while (tmp != NULL)
	{
		Enemy* p = tmp->data;
		tmp_next = tmp->next;

		if (p->Update() == false)
		{

			
			delete p;
			active.del(tmp);
		}
		else
		{
			App->renderer->Blit(graphics, p->position.x, p->position.y, &(p->current_anim->GetCurrentFrame()));
			if (p->fx_played == false)
			{
				p->fx_played = true;
				App->audio->PlayFx(p->fx);
			}
		}

		tmp = tmp_next;
	}

	return UPDATE_CONTINUE;
}

// Always destroy Enemy that collide
void ModuleEnemy::OnCollision(Collider* c1, Collider* c2)
{
	//Blocks-----------------------------------------------------------------------
	if (c2->type == COLLIDER_BLOCK || c2->type == COLLIDER_WALL || c2->type == COLLIDER_BOMB)
	{
		p2List_item<Enemy*>* tmp = active.getFirst();

		while (tmp != NULL)
		{
			if (tmp->data->collider == c1)
			{
				tmp->data->position = tmp->data->last_position;
				tmp->data->GetNewDirection();
				break;
			}

			tmp = tmp->next;
		}
	}

	//Explosions
	if (c2->type == COLLIDER_EXPLOSION)
	{
		p2List_item<Enemy*>* tmp = active.getFirst();

		while (tmp != NULL)
		{
			if (tmp->data->collider == c1)
			{
				App->enemy->AddEnemy(App->enemy->explosion_copter, tmp->data->position.x-2, tmp->data->position.y - 10, COLLIDER_NONE, explosionE);
				delete tmp->data;
				active.del(tmp);
				App->scene->current_enemies--;
				App->audio->PlayFx(fxExplode);
				break;
			}

			tmp = tmp->next;
		}

	}
	
	
}

Collider* ModuleEnemy::AddEnemy(const Enemy& enemy, int x, int y, COLLIDER_TYPE collider_type, TypeE _type)
{
	Enemy* p = new Enemy(enemy);
	p->position.x = x;
	p->position.y = y;

	p->type = _type;

	if (collider_type != COLLIDER_NONE)
	{
		p->collider = App->collision->AddCollider({ p->position.x, p->position.y, 0, 0 }, collider_type, this);
	}

	srand(SDL_GetTicks());
	int random_direction = rand() % (3 - 0 + 1) + 0; //3-max 0-min
	p->direction_enemy = (Looking) random_direction; //TODO: Posar random a la direcció inicial.

	active.add(p);
	return p->collider;
}

// -------------------------------------------------------------
// -------------------------------------------------------------

Enemy::Enemy() : fx(0), fx_played(false), collider(NULL)
{
	position.SetToZero();
	current_anim = NULL;
}

Enemy::Enemy(const Enemy& p) : left(p.left), right(p.right), up(p.up), down(p.down), position(p.position), fx_played(false), collider(p.collider)
{
	fx = p.fx;
}

Enemy::~Enemy()
{
	if (collider)
		collider->to_delete = true;
}

bool Enemy::Update()
{
	bool ret = true;
	
	if (type == explosionE)
	{
		current_anim = &up;
		if (current_anim->Finished())
			ret = false;

		return ret;
	}

	last_position = position;

	current_anim = &right;

	switch (direction_enemy)
	{
	case upD:
		position.y -= VELOCITY_ENEMY;
		current_anim = &up;
		break;
	case downD:
		position.y += VELOCITY_ENEMY;
		current_anim = &down;
		break;
	case rightD:
		position.x += VELOCITY_ENEMY;
		current_anim = &right;
		break;
	case leftD:
		position.x -= VELOCITY_ENEMY;
		current_anim = &left;
		break;
	}


	if (collider != NULL)
	{
		SDL_Rect r = current_anim->PeekCurrentFrame();
		collider->rect = { position.x, position.y+(r.h-TILE), TILE, TILE };
	}

	//Limits-----------------------------------------------------------------
	if (collider->rect.x < 24 || collider->rect.x + 16 > 232 || collider->rect.y < 40 || collider->rect.y > 216 - 16)
	{
		position = last_position;
		GetNewDirection();
	}

	return ret;
}

void Enemy::GetNewDirection(){

	Looking new_direction = direction_enemy;
	
	srand(SDL_GetTicks());
	while (new_direction == direction_enemy)
	{
		int random = rand() % (3 - 0 + 1) + 0; //3-max 0-min
		new_direction = (Looking)random;
	}

	direction_enemy = new_direction;

}