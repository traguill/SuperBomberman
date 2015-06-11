#include "Globals.h"
#include "Application.h"
#include "ModuleCredits.h"

ModuleCredits::ModuleCredits(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	graphics = NULL;

	//Status bar, animation
	bar = { 0, 0, 256, 32 };
}

ModuleCredits::~ModuleCredits()
{}

// Load assets
bool ModuleCredits::Start()
{
	LOG("Loading Credits");

	graphics = App->textures->Load("interface.png");

	return true;
}

// UnLoad assets
bool ModuleCredits::CleanUp()
{
	LOG("Unloading Credits");

	App->textures->Unload(graphics);

	return true;
}

// Update: draw background
update_status ModuleCredits::Update()
{
	// Draw everything --------------------------------------
	App->renderer->Blit(graphics, 0, 0, &bar);

	return UPDATE_CONTINUE;
}