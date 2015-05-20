#include "Globals.h"
#include "Application.h"
#include "ModulePowerUp.h"

ModulePowerUp::ModulePowerUp(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	graphics = NULL;

	//animations
	//TODO: cada cop que es reinicia loa partida el canvi de frames va encara mes rapid
	PowerSpeed.frames.PushBack({ 581, 35, TILE, TILE });
	PowerSpeed.frames.PushBack({ 581, 52, TILE, TILE });
	PowerSpeed.speed = 0.1f;

	PowerBomb.frames.PushBack({ 564, 35, TILE, TILE });
	PowerBomb.frames.PushBack({ 564, 52, TILE, TILE });
	PowerBomb.speed = 0.1f;

	PowerFire.frames.PushBack({ 632, 35, TILE, TILE });
	PowerFire.frames.PushBack({ 632, 52, TILE, TILE });
	PowerFire.speed = 0.1f;
}

void ModulePowerUp::AddPowerUp(POWERUP_TYPE type)
{
	PowerUp* power = new PowerUp(type);
	levelPowerUps.PushBack(power);
}

void ModulePowerUp::ActivePowerUp(int x, int y)
{
	PowerUp* power;

	levelPowerUps.Pop(power);
	
	power->position.x = x;
	power->position.y = y;

	//power->collider = App->collision->AddCollider({ power->position.x, power->position.y, TILE, TILE }, COLLIDER_POWERUP);
	
	active.add(power);
}

void ModulePowerUp::DrawPowerUp(PowerUp* power)
{
	SDL_Rect r;

	switch (power->type)
	{
	case POWERUP_BOMB:
		r = PowerBomb.GetCurrentFrame();
		break;
	case POWERUP_SPEED:
		r = PowerSpeed.GetCurrentFrame();
		break;
	case POWERUP_FIRE:
		r = PowerFire.GetCurrentFrame();
		break;
	}

	App->renderer->Blit(graphics, power->position.x, power->position.y, &r);
}
ModulePowerUp::~ModulePowerUp()
{}

// Load assets
bool ModulePowerUp::Start()
{
	LOG("Loading PowerUp");

	graphics = App->textures->Load("GameAssets.png");

	return true;
}

update_status ModulePowerUp::Update()
{
	// Draw everything --------------------------------------
	p2List_item<PowerUp*>* tmp = active.getFirst();

	while (tmp != NULL)
	{
		DrawPowerUp(tmp->data);
		tmp = tmp->next;
	}
	return UPDATE_CONTINUE;
}


// UnLoad assets
bool ModulePowerUp::CleanUp()
{
	LOG("Unloading PowerUP");

	App->textures->Unload(graphics);

	return true;
}

/*
Of PowerUp
*/

PowerUp::PowerUp(POWERUP_TYPE type_) : type(type_), collider(NULL)
{
	position.SetToZero();
}
