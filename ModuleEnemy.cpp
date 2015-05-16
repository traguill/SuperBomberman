#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleEnemy.h"

ModuleEnemy::ModuleEnemy(Application* app, bool start_enabled) : Module(app, start_enabled), graphics(NULL)
{}

ModuleEnemy::~ModuleEnemy()
{}

// Load assets
bool ModuleEnemy::Start()
{
	LOG("Loading Enemy");
	graphics = App->textures->Load("Enemy.png");

	// copter Enemy
	copter.anim.frames.PushBack({ 0, 0, 16, 24 });
	copter.anim.frames.PushBack({ 16, 0, 16, 24 });
	copter.anim.frames.PushBack({ 32, 0, 16, 24 });
	copter.anim.frames.PushBack({ 48, 0, 16, 24 });
	copter.anim.speed = 0.17f;

	

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
			App->renderer->Blit(graphics, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
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
	/*
	p2List_item<Enemy*>* tmp = active.getFirst();

	while(tmp != NULL)
	{
	if(tmp->data->collider == c1 )
	{
	delete tmp->data;
	active.del(tmp);
	break;
	}

	tmp = tmp->next;
	}*/
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

	active.add(p);
	return p->collider;
}

// -------------------------------------------------------------
// -------------------------------------------------------------

Enemy::Enemy() : fx(0), fx_played(false), collider(NULL)
{
	position.SetToZero();
	speed.SetToZero();
}

Enemy::Enemy(const Enemy& p) : anim(p.anim), position(p.position), speed(p.speed), fx_played(false), collider(p.collider)
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

	//TODO: posar condicio de retornar false quan volguem matar-lo
		


	if (collider != NULL)
	{
		SDL_Rect r = anim.PeekCurrentFrame();
		collider->rect = { position.x, position.y, r.w, r.h };
	}

	return ret;
}