#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleParticles.h"

ModuleParticles::ModuleParticles(Application* app, bool start_enabled) : Module(app, start_enabled), graphics(NULL)
{

	fire = 1;

	graphics = NULL;


	// Explosion particle
	/*
	explosion.anim.frames.PushBack({ 49, 49, 48, 48 });
	explosion.anim.frames.PushBack({ 0, 49, 48, 48 });
	explosion.anim.frames.PushBack({ 98, 0, 48, 48 });
	explosion.anim.frames.PushBack({ 49, 0, 48, 48 });
	explosion.anim.frames.PushBack({ 0, 0, 48, 48 });
	explosion.anim.speed = 0.17f;
	*/
	expCenter.anim.frames.PushBack({ 16, 16, 16, 16 });
	expCenter.anim.frames.PushBack({ 65, 16, 16, 16 });
	expCenter.anim.frames.PushBack({114, 16, 16, 16 });
	expCenter.anim.frames.PushBack({ 16, 65, 16, 16 });
	expCenter.anim.frames.PushBack({ 65, 65, 16, 16 });
	expCenter.anim.speed = 0.17f;

	expUp.anim.frames.PushBack({ 16, 0, 16, 16 });
	expUp.anim.frames.PushBack({ 65, 0, 16, 16 });
	expUp.anim.frames.PushBack({114, 0, 16, 16 });
	expUp.anim.frames.PushBack({ 16, 49, 16, 16 });
	expUp.anim.frames.PushBack({ 65, 49, 16, 16 });
	expUp.anim.speed = 0.17f;

	expDown.anim.frames.PushBack({ 16, 32, 16, 16 });
	expDown.anim.frames.PushBack({ 65, 32, 16, 16 });
	expDown.anim.frames.PushBack({ 114, 32, 16, 16 });
	expDown.anim.frames.PushBack({ 16, 81, 16, 16 });
	expDown.anim.frames.PushBack({ 65, 81, 16, 16 });
	expDown.anim.speed = 0.17f;

	expRight.anim.frames.PushBack({ 32, 16, 16, 16 });
	expRight.anim.frames.PushBack({ 81, 16, 16, 16 });
	expRight.anim.frames.PushBack({ 130, 16, 16, 16 });
	expRight.anim.frames.PushBack({ 32, 65, 16, 16 });
	expRight.anim.frames.PushBack({ 81, 65, 16, 16 });
	expRight.anim.speed = 0.17f;

	expLeft.anim.frames.PushBack({ 0, 16, 16, 16 });
	expLeft.anim.frames.PushBack({ 49, 16, 16, 16 });
	expLeft.anim.frames.PushBack({ 98, 16, 16, 16 });
	expLeft.anim.frames.PushBack({ 0, 65, 16, 16 });
	expLeft.anim.frames.PushBack({ 49, 65, 16, 16 });
	expLeft.anim.speed = 0.17f;

	expVert.anim.frames.PushBack({ 16, 256, 16, 16 });
	expVert.anim.frames.PushBack({ 16, 305, 16, 16 });
	expVert.anim.frames.PushBack({ 16, 353, 16, 16 });
	expVert.anim.frames.PushBack({ 16, 402, 16, 16 });
	expVert.anim.frames.PushBack({ 16, 451, 16, 16 });
	expVert.anim.speed = 0.17f;

	expHor.anim.frames.PushBack({ 32, 272, 16, 16 });
	expHor.anim.frames.PushBack({ 32, 321, 16, 16 });
	expHor.anim.frames.PushBack({ 32, 369, 16, 16 });
	expHor.anim.frames.PushBack({ 32, 418, 16, 16 });
	expHor.anim.frames.PushBack({ 32, 467, 16, 16 });
	expHor.anim.speed = 0.17f;
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

	//Floor particle
	floor.anim.frames.PushBack({ 0, 99, 14, 17 });
	floor.life = 4000;

	explosion_boss.anim.frames.PushBack({ 15,  97, 20, 34 });
	explosion_boss.anim.frames.PushBack({ 36,  97, 30, 34 });
	explosion_boss.anim.frames.PushBack({ 67,  97, 32, 34 });
	explosion_boss.anim.frames.PushBack({ 100, 97, 32, 34 });
	explosion_boss.anim.frames.PushBack({ 133, 97, 32, 34 });
	explosion_boss.anim.speed = 0.2f;


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
				//Explosion creation
				App->particles->AddParticle(App->particles->expCenter, p->position.x, p->position.y, COLLIDER_EXPLOSION, explosionT); 
				for (int i = 1; i <= fire; i++)
				{
					if (i < fire)
					{
						App->particles->AddParticle(App->particles->expVert, p->position.x, p->position.y - i*TILE, COLLIDER_EXPLOSION, explosionT);
						App->particles->AddParticle(App->particles->expVert, p->position.x, p->position.y + i*TILE, COLLIDER_EXPLOSION, explosionT);
						App->particles->AddParticle(App->particles->expHor, p->position.x + i*TILE, p->position.y, COLLIDER_EXPLOSION, explosionT);
						App->particles->AddParticle(App->particles->expHor, p->position.x - i*TILE, p->position.y, COLLIDER_EXPLOSION, explosionT);
					}
					else
					{
						App->particles->AddParticle(App->particles->expUp, p->position.x, p->position.y - i*TILE, COLLIDER_EXPLOSION, explosionT);
						App->particles->AddParticle(App->particles->expDown, p->position.x, p->position.y + i*TILE, COLLIDER_EXPLOSION, explosionT);
						App->particles->AddParticle(App->particles->expRight, p->position.x + i*TILE, p->position.y, COLLIDER_EXPLOSION, explosionT);
						App->particles->AddParticle(App->particles->expLeft, p->position.x - i*TILE, p->position.y, COLLIDER_EXPLOSION, explosionT);
					}
				}
				App->audio->PlayFx(fxExplode);
			}
			if (p->type == explosionT)

				App->player->current_bombs--;

			
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
					//else
						//App->level->level[p->collider->GetPosLevel().y][p->collider->GetPosLevel().x] = 0; //actualitzem la matriu nivell i li diem que no hi ha res.
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

Collider* ModuleParticles::AddParticle(const Particle& particle, int x, int y, COLLIDER_TYPE collider_type, Type _type, float sx, float sy, Uint32 delay)
{
	Particle* p = new Particle(particle);
	p->born = SDL_GetTicks() + delay;
	p->position.x = x;
	p->position.y = y;
	p->speed.x = sx;
	p->speed.y = sy;

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
	if (type == floorT)
	{
		position.x += speed.x;
		speed.y -= GRAVITY_PARTICLE;
		position.y -= speed.y;
		
		if (speed.y < -2.5f)
			ret = false;
	}
	

	if(collider != NULL)
	{
		SDL_Rect r = anim.PeekCurrentFrame();
		collider->rect = {position.x, position.y, r.w, r.h};
	}

	return ret;
}