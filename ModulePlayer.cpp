#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"


ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	graphics = NULL;
	current_animation = NULL;


	position.x = 150;
	position.y = 120;

	// idle animation (just the ship)
	idle.frames.PushBack({ 69, 37, 17, 26 });

	// walk Right
	right.frames.PushBack({ 178, 38, 18, 23 });
	right.frames.PushBack({ 160, 38, 18, 23 });
	right.frames.PushBack({ 178, 38, 18, 23 });
	right.frames.PushBack({ 197, 38, 18, 23 });
	right.speed = 0.1f;

	// walk Left
	left.frames.PushBack({ 124, 38, 18, 23 });
	left.frames.PushBack({ 106, 38, 18, 23 });
	left.frames.PushBack({ 124, 38, 18, 23 });
	left.frames.PushBack({ 143, 38, 18, 23 });
	left.speed = 0.1f;

	// walk Down
	down.frames.PushBack({ 70, 38, 15, 23 });
	down.frames.PushBack({ 52, 38, 15, 23 });
	down.frames.PushBack({ 70, 38, 15, 23 });
	down.frames.PushBack({ 88, 38, 15, 23 });
	down.speed = 0.1f;

	// walk Up
	up.frames.PushBack({ 237, 38, 15, 23 });
	up.frames.PushBack({ 219, 38, 15, 23 });
	up.frames.PushBack({ 237, 38, 15, 23 });
	up.frames.PushBack({ 255, 38, 15, 23 });
	up.speed = 0.1f;

	//TODO
	//current_orientation = idle;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	graphics = App->textures->Load("SuperBomberman/GameAssets.png");

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(graphics);

	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	int speed = 1;

	if (App->input->keyboard[SDL_SCANCODE_A])
	{
		position.x -= speed;
		if (current_animation != &left)
		{
			left.Reset();
			current_animation = &left;
			//TODO
			//current_orientation = left;

		}
	}



	if (App->input->keyboard[SDL_SCANCODE_D])
	{
		position.x += speed;
		if (current_animation != &right)
		{
			right.Reset();
			current_animation = &right;
			//TODO
			//current_orientation = right;
		}
	}

	if (App->input->keyboard[SDL_SCANCODE_S])
	{
		position.y += speed;
		if (current_animation != &down)
		{
			down.Reset();
			current_animation = &down;
			//TODO
			//current_orientation = down;
		}
	}

	if (App->input->keyboard[SDL_SCANCODE_W])
	{
		position.y -= speed;
		if (current_animation != &up)
		{
			up.Reset();
			current_animation = &up;
			//TODO
			//current_orientation = up;
		}
	}
	//AIXO ho guardo per si es pot aprofitar mes endavant
	/*if(App->input->keyboard_down[SDL_SCANCODE_B] == 1)
	{
	App->particles->AddParticle(App->particles->explosion, position.x, position.y + 25);
	App->particles->AddParticle(App->particles->explosion, position.x - 25, position.y, 500);
	App->particles->AddParticle(App->particles->explosion, position.x, position.y - 25, 1000);
	App->particles->AddParticle(App->particles->explosion, position.x + 25, position.y, 1500);
	}
	*/

	if (App->input->keyboard[SDL_SCANCODE_S] == 0 && App->input->keyboard[SDL_SCANCODE_W] == 0
		&& App->input->keyboard[SDL_SCANCODE_A] == 0 && App->input->keyboard[SDL_SCANCODE_D] == 0)
		current_animation = &idle;
	//current_animation = &current_orientation;
	//TODO

	// Draw everything --------------------------------------

	App->renderer->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()));

	return UPDATE_CONTINUE;
}