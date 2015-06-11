#ifndef _ModulePowerUP_H_
#define _ModulePowerUP_H_

#include "Module.h"
#include "p2DynArray.h"
#include "p2List.h"

enum POWERUP_TYPE
{
	POWERUP_NONE = -1,
	POWERUP_SPEED,
	POWERUP_BOMB,
	POWERUP_FIRE,

	POWEUP_MAX
};

struct PowerUp
{
	p2Point<int> position;
	Collider* collider;
	POWERUP_TYPE type;


	PowerUp(POWERUP_TYPE type_);
};

class ModulePowerUp : public Module
{
public:

	ModulePowerUp(Application* app, bool start_enabled = true);
	~ModulePowerUp();

	bool Start();
	update_status Update();
	bool CleanUp();

	void AddPowerUp(POWERUP_TYPE type);
	void ActivePowerUp(int x, int y);
	void DrawPowerUp(PowerUp* power);
	void DeletePowerUp(PowerUp* power);
	void OnCollision(Collider* c1, Collider* c2);
	//TODO: especificar el modul, ONcollision per afegir els efectes de cada PowerUp

public:

	p2DynArray<PowerUp*> levelPowerUps;
	p2List<PowerUp*> active;
	SDL_Texture* graphics;
	Animation PowerSpeed;
	int limitSpeed;
	Animation PowerBomb;
	int limitBomb;
	Animation PowerFire;
	int limitFire;
};

#endif // __ModulePowerUp_H__