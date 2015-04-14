
#include "Globals.h"
#include "Application.h"
#include "ModuleScene.h"

ModuleScene::ModuleScene(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	status = NULL;
	
	a = {409, 75, 258, 34 };
	bar = &a;
	
}

ModuleScene::~ModuleScene()
{}

// Load assets
bool ModuleScene::Start()
{
	LOG("Loading scene");

	status = App->textures->Load("Game/GameAssets.png");
	App->player->Enable();

	return true;
}

// UnLoad assets
bool ModuleScene::CleanUp()
{
	LOG("Unloading space scene");

	App->textures->Unload(status);
	App->player->Disable();

	return true;
}

// Update: draw background
update_status ModuleScene::Update()
{
	// Draw everything --------------------------------------
	App->renderer->Blit(status, 0, 0, bar);

	return UPDATE_CONTINUE;
}
