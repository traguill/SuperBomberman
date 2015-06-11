#include "Globals.h"
#include "Application.h"
#include "ModuleCredits.h"

ModuleCredits::ModuleCredits(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	graphics = NULL;

	//Status bar, animation
	text = { 0, 0, 256, 252 };
}

ModuleCredits::~ModuleCredits()
{}

// Load assets
bool ModuleCredits::Start()
{
	LOG("Loading Credits");

	graphics = App->textures->Load("credits.png");
	App->audio->PlayMusic("credit.ogg", 0.0f);

	positionY = 230;
	scene_transition = false;

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
	positionY -= 0.5f;

	if (positionY < -252 && !scene_transition)
	{
		App->fade->FadeToBlack(this, App->intro, 3.0f);
		scene_transition = true;
	}
		
	// Draw everything --------------------------------------
	App->renderer->Blit(graphics, 0, positionY , &text);

	return UPDATE_CONTINUE;
}