#include "Globals.h"
#include "Application.h"
#include "ModuleTimer.h"

ModuleTimer::ModuleTimer(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	graphics = NULL;

	//Status bar, animation
	status.frames.PushBack({ 412, 77, 256, 32 });
	current_status = &status;

}

ModuleTimer::~ModuleTimer()
{}

// Load assets
bool ModuleTimer::Start()
{
	LOG("Loading Timer");

	graphics = App->textures->Load("GameAssets.png");

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
	App->renderer->Blit(graphics, 0, 0, &(current_status->GetCurrentFrame()));

	return UPDATE_CONTINUE;
}