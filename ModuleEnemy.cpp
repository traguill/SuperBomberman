#include "Globals.h"
#include "Application.h"
#include "ModuleEnemy.h"


ModuleEnemy::ModuleEnemy(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	graphics = NULL;
	current_animation = NULL;



	position.x = 60;
	position.y = 30;

	// idle 
	idle.frames.PushBack({ 0, 1, 15, 23 }); //LOOK DOWN
	idle.frames.PushBack({ 15, 1, 15, 23 }); //LOOK RIGHT
	idle.frames.PushBack({ 31, 1, 15, 23 });//LOOK LEFT
	idle.frames.PushBack({ 47, 1, 15, 23 });//LOOK UP
	idle.speed = 0.1f;

	// walk Right
	right.frames.PushBack({ 197, 38, 16, 24 });
	right.frames.PushBack({ 179, 38, 16, 24 });
	right.frames.PushBack({ 161, 38, 16, 24 });
	right.frames.PushBack({ 179, 38, 16, 24 });
	right.speed = 0.1f;

	// walk Left
	left.frames.PushBack({ 142, 38, 16, 24 });
	left.frames.PushBack({ 124, 38, 16, 24 });
	left.frames.PushBack({ 105, 38, 16, 24 });
	left.frames.PushBack({ 124, 38, 16, 24 });

	left.speed = 0.1f;

	// walk Down
	down.frames.PushBack({ 88, 38, 16, 22 });
	down.frames.PushBack({ 70, 38, 16, 24 });
	down.frames.PushBack({ 52, 38, 16, 24 });
	down.frames.PushBack({ 70, 38, 16, 24 });

	down.speed = 0.1f;

	// walk Up
	up.frames.PushBack({ 255, 38, 16, 24 });
	up.frames.PushBack({ 237, 38, 16, 24 });
	up.frames.PushBack({ 219, 38, 16, 24 });
	up.frames.PushBack({ 237, 38, 16, 24 });

	up.speed = 0.1f;

	




}

ModuleEnemy::~ModuleEnemy()
{}

// Load assets
bool ModuleEnemy::Start()
{
	LOG("Loading Enemy");

	graphics = App->textures->Load("Enemy.png");

	collider = App->collision->AddCollider({ position.x, position.y - 23, 16, 16 }, COLLIDER_ENEMY, this);

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
	last_position = position;

	Animation* current_animation = &idle; //Posem la animacio de quiet per defecte i despres comprovem si ha apretat alguna tecla aixi evitem fer la comprovació que havies fet al final.

	int speed = 1;



	collider->SetPos(position.x, position.y-23);





	// Draw everything --------------------------------------
	SDL_Rect r;

	r = current_animation->GetCurrentFrame();


	

	App->renderer->Blit(graphics, position.x, position.y - r.h, &r);


	return UPDATE_CONTINUE;
}

void ModuleEnemy::OnCollision(Collider* c1, Collider* c2)
{
	



}