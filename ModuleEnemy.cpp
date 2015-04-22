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

	//Copter enemy
	copter.anim.frames.PushBack({0,1,15,19});
	copter.anim.frames.PushBack({ 16, 1, 15, 19 });
	copter.anim.frames.PushBack({ 31, 1, 15, 19 });
	copter.anim.frames.PushBack({ 48, 1, 15, 19 });
	copter.anim.speed = 0.1f;

	return true;
}

// Unload assets
bool ModuleEnemy::CleanUp()
{
	LOG("Unloading Enemy");

	App->textures->Unload(graphics);

	return true;
}

// Update: draw background
update_status ModuleEnemy::Update()
{
	p2List_item<Enemy*>* tmp = active.getFirst();
	p2List_item<Enemy*>* tmp_next = active.getFirst();

	while (tmp != NULL)
	{
		Enemy* e = tmp->data;
		tmp_next = tmp->next;

		if (e->Update() == false)
		{
			delete e;
			active.del(tmp);
		}
		else
		{
			App->renderer->Blit(graphics, e->position.x, e->position.y, &(e->anim.GetCurrentFrame()));
		}
		tmp = tmp_next;
	}
	return UPDATE_CONTINUE;
}

void ModuleEnemy::OnCollision(Collider* c1, Collider* c2)
{
	//DOIT: destrueix sempre que colisiona amb algu
	p2List_item<Enemy*>* tmp = active.getFirst();

	while (tmp != NULL)
	{
		if (tmp->data->collider == c1) //Hem trobat el enemic que ha colisionat
		{
			if (c2->type == COLLIDER_EXPLOSION) //Es borra l'enemic al colisionar amb una explosio
			{
				if (c1->GetPosLevel().x == c2->GetPosLevel().x || c1->GetPosLevel().y == c2->GetPosLevel().y)
				{
					App->scene->current_enemies--;
					tmp->data->collider->to_delete = true;//he posta aixo perque el collider del enemic no es borraba
					delete tmp->data;
					active.del(tmp);
					break;
				}
				
			}
			
		}

		tmp = tmp->next;
	}

}

Collider* ModuleEnemy::AddEnemy(const Enemy& enemy, int x, int y, COLLIDER_TYPE collider_type)
{
	Enemy* e = new Enemy(enemy);
	e->position.x = x;
	e->position.y = y;

	if (collider_type != COLLIDER_NONE)
	{
		e->collider = App->collision->AddCollider({ e->position.x, e->position.y, 0, 0 }, collider_type, this);
	}

	active.add(e);
	return e->collider;
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
Enemy::Enemy() : collider(NULL)
{
	position.SetToZero();
	speed.SetToZero();
}

Enemy::Enemy(const Enemy& e) : anim(e.anim), position(e.position), speed(e.speed), collider(e.collider)
{}

Enemy::~Enemy()
{
	if (collider)
		collider->to_delete;
}

bool Enemy::Update()
{
	bool ret = true;

	if (collider != NULL)
	{
		collider->rect = { position.x, position.y + 3, 16, 16 }; //Canviar el +3 nomes funciona pel copter
	}
	
	return ret;
}