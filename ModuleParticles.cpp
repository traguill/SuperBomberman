#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleParticles.h"

ModuleParticles::ModuleParticles(Application* app, bool start_enabled) : Module(app, start_enabled), graphics(NULL)
{



	graphics = NULL;


	// Explosion particle
	explosion.anim.frames.PushBack({ 49, 49, 48, 48 });
	explosion.anim.frames.PushBack({ 0, 49, 48, 48 });
	explosion.anim.frames.PushBack({ 98, 0, 48, 48 });
	explosion.anim.frames.PushBack({ 49, 0, 48, 48 });
	explosion.anim.frames.PushBack({ 0, 0, 48, 48 });
	explosion.anim.speed = 0.17f;

	// Bomb particle
	bomb.anim.frames.PushBack({ 115, 70, 16, 16 });
	bomb.anim.frames.PushBack({ 132, 70, 16, 16 });
	bomb.anim.frames.PushBack({ 149, 70, 16, 16 });
	bomb.anim.frames.PushBack({ 132, 70, 16, 16 });
	bomb.life = 2000;
	bomb.anim.speed = 0.075f;


	//Block explosion
	block.anim.frames.PushBack({ 147, 0, 16, 16 });
	block.anim.frames.PushBack({ 164, 0, 16, 16 });
	block.anim.frames.PushBack({ 181, 0, 16, 16 });
	block.anim.frames.PushBack({ 198, 0, 16, 16 });
	block.anim.frames.PushBack({ 215, 0, 16, 16 });
	block.anim.frames.PushBack({ 232, 0, 16, 16 });
	block.anim.speed = 0.18f;




}

ModuleParticles::~ModuleParticles()
{}

// Load assets
bool ModuleParticles::Start()
{
	LOG("Loading particles");
	graphics = App->textures->Load("particles.png");


	fxExplode = App->audio->LoadFx("game/Audios/Gameplay/Explode.wav");
	


	position_portal_x = position_portal_y = 0;



	return true;
}

// Unload assets
bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");
	App->textures->Unload(graphics);
	 
	p2List_item<Particle*>* item = active.getLast();

	while (item != NULL)
	{
		delete item->data;
		item = item->prev;
	}

	active.clear();


	return true;
}

// Update: draw background
update_status ModuleParticles::Update()
{
	p2List_item<Particle*>* tmp = active.getFirst();
	p2List_item<Particle*>* tmp_next = active.getFirst();

	while(tmp != NULL)
	{
		Particle* p = tmp->data;
		tmp_next = tmp->next;

		if(p->Update() == false)
		{
			if (p->type == bombT)
			{
				App->particles->AddParticle(App->particles->explosion, p->position.x - 16, p->position.y - 16, COLLIDER_EXPLOSION, explosionT); //DOIT: si es una bomba crea una particula explosio
				App->audio->PlayFx(fxExplode);
			}
			if (p->type == explosionT)

				App->player->current_bombs = 0;

			if (p->type == blockT)
				App->level->level[p->collider->GetPosLevel().y][p->collider->GetPosLevel().x] = 0; //actualitzem la matriu nivell i li diem que no hi ha res.

				 App->player->current_bombs = 0;
			if (p->type == blockT ){

				srand(SDL_GetTicks());
				random_portal = rand() % (5 - 1 + 1)+1;
				
				

				if (App->level->num_portals == 0 && random_portal == 2)
				{
					App->level->level[p->collider->GetPosLevel().y][p->collider->GetPosLevel().x] = 3; //posem portal
					position_portal_x = p->position.y;
					position_portal_y = p->position.x;
 					App->level->num_portals++;
				}
				else
				{
					if (App->level->num_blocks  == 0 && App->level->num_portals == 0)
					{
						App->level->level[p->collider->GetPosLevel().y][p->collider->GetPosLevel().x] = 3; //posem portal
						position_portal_x = p->position.y;
						position_portal_y = p->position.x;

						App->level->num_portals++;
					}
					else
						App->level->level[p->collider->GetPosLevel().y][p->collider->GetPosLevel().x] = 0; //actualitzem la matriu nivell i li diem que no hi ha res.
				}
				
			}
			

			delete p;
			active.del(tmp);
		}
		else if(SDL_GetTicks() >= p->born)
		{
			App->renderer->Blit(graphics, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
			if(p->fx_played == false)
			{
				p->fx_played = true;
				App->audio->PlayFx(p->fx);
			}
		}

		tmp = tmp_next;
	}

	return UPDATE_CONTINUE;
}

// Always destroy particles that collide
void ModuleParticles::OnCollision(Collider* c1, Collider* c2)
{
	/*
  	p2List_item<Particle*>* tmp = active.getFirst();

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

Collider* ModuleParticles::AddParticle(const Particle& particle, int x, int y, COLLIDER_TYPE collider_type, Type _type, Uint32 delay)
{
	Particle* p = new Particle(particle);
	p->born = SDL_GetTicks() + delay;
	p->position.x = x;
	p->position.y = y;

	p->type = _type;

	if(collider_type != COLLIDER_NONE)
	{
		p->collider = App->collision->AddCollider({p->position.x, p->position.y, 0, 0}, collider_type, this);
	}

	active.add(p);
	return p->collider;
}

// -------------------------------------------------------------
// -------------------------------------------------------------

Particle::Particle() : fx(0), born(0), life(0), fx_played(false), collider(NULL)
{
	position.SetToZero();
	speed.SetToZero();
}

Particle::Particle(const Particle& p) : anim(p.anim), position(p.position), speed(p.speed), fx_played(false), collider(p.collider)
{
	fx = p.fx;
	born = p.born;
	life = p.life;
}

Particle::~Particle()
{
	if(collider)
		collider->to_delete = true;
}

bool Particle::Update()
{
	bool ret = true;

	if(life > 0)
	{
		if((SDL_GetTicks() - born) > life)
			ret = false;
	}
	else
		if(anim.Finished())
			ret = false;

	

	if(collider != NULL)
	{
		SDL_Rect r = anim.PeekCurrentFrame();
		collider->rect = {position.x, position.y, r.w, r.h};
	}

	return ret;
}