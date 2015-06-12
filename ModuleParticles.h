#pragma once
#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "p2List.h"
#include "ModuleCollision.h"

enum Type{  //Guarda el tipus de particle per saber si ha d'explotar.
	bombT,
	explosionT,
	blockT,
	floorT,
	floorST,
	nullT,
};

struct Particle
{
	Animation anim;
	unsigned int fx;
	p2Point<float> position;
	p2Point<float> speed;
	Uint32 born;
	Uint32 life;
	bool fx_played;
	Collider* collider;
	Type type;
	Particle();
	Particle(const Particle& p);
	~Particle();
	bool Update();
};

class ModuleParticles : public Module
{
public:
	ModuleParticles(Application* app, bool start_enabled = true);
	~ModuleParticles();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider*, Collider*);

	Collider* AddParticle(const Particle& particle, int x, int y, COLLIDER_TYPE = COLLIDER_NONE, Type _type = nullT, float sx = 0, float sy = 0, Uint32 delay = 0);
	void DetectBlock(Collider*);

private:

	SDL_Texture* graphics;
	p2List<Particle*> active;

public:

	Particle bomb;
	//Particle explosion;
	//Explosion Parts
	Particle expCenter;
	Particle expUp;
	Particle expDown;
	Particle expRight;
	Particle expLeft;
	Particle expVert;
	Particle expHor;
	int fire;
	int fireUp;
	int fireDown;
	int fireRight;
	int fireLeft;

	//
	Particle block;
	Particle floor;
	Particle floorS;
	Particle explosion_boss;

	unsigned int fxExplode;

	int random_portal;
	int position_portal_x;
	int position_portal_y;



};