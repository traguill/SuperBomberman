#include "Globals.h"
#include "Application.h"
#include "ModuleTimer.h"

ModuleTimer::ModuleTimer(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	graphics = NULL;

	//Status bar, animation
	bar = { 0, 0, 256, 32 };
	zero = { 0, 33, 8, 12 };
	one = { 9, 33, 8, 12 };
	two = { 18, 33, 8, 12 };
	three = { 27, 33, 8, 12 };
	four = { 36, 33, 8, 12 };
	five = { 45, 33, 8, 12 };
	six = { 54, 33, 8, 12 };
	seven = { 63, 33, 8, 12 };
	eight = { 72, 33, 8, 12 };
	nine = { 91, 33, 8, 12 };

}

ModuleTimer::~ModuleTimer()
{}

// Load assets
bool ModuleTimer::Start()
{
	LOG("Loading Timer");

	graphics = App->textures->Load("interface.png");

	return true;
}

// UnLoad assets
bool ModuleTimer::CleanUp()
{
	LOG("Unloading Timer");

	App->textures->Unload(graphics);

	return true;
}

// Update: draw background
update_status ModuleTimer::Update()
{
	// Draw everything --------------------------------------
	App->renderer->Blit(graphics, 0, 0, &bar);
	
	SDL_Rect r;
	switch (App->player->lifes)
	{
	case 0:
		r = zero;
		break;
	case 1:
		r = one;
		break;
	case 2:
		r = two;
		break;
	case 3:
		r = three;
		break;
	case 4:
		r = four;
		break;
	case 5:
		r = five;
		break;
	case 6:
		r = six;
		break;
	case 7:
		r = seven;
		break;
	case 8:
		r = eight;
		break;
	default:
		r = nine;
		break;
	}

	App->renderer->Blit(graphics, 23, 10, &r);

	return UPDATE_CONTINUE;
}