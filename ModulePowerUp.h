#ifndef _ModulePowerUP_H_
#define _ModulePowerUP_H_

#include "Module.h"
#include "p2List.h"

enum POWERUP_TYPE
{
	POWERUP_NONE = -1,
	POWERUP_SPEED,
	POWERUP_BOMB,

	POWEUP_MAX
};

struct PowerUp
{
	SDL_Rect rect;
	bool to_delete;
	POWERUP_TYPE type;


	PowerUp(SDL_Rect rectangle, POWERUP_TYPE type) :
		rect(rectangle),
		type(type),
		to_delete(false)
	{}



};

class ModulePowerUp : public Module
{
public:

	ModulePowerUp(Application* app, bool start_enabled = true);
	//destructor, ponerModulePowerUp();

	update_status PreUpdate();
	update_status Update();
	bool CleanUp();

	Collider* AddCollider(SDL_Rect rect, COLLIDER_TYPE type, Module* callback = NULL);
	void DrawDebug(Collider* col);

private:

	p2List<Collider*>	colliders;
	bool matrix[COLLIDER_MAX][COLLIDER_MAX];
	bool debug;
};

#endif // __ModuleCollision_H__