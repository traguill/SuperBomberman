#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"



ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	background = NULL;
	fx = 0;
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;


	background = App->textures->Load("buildings.png");
	App->audio->PlayMusic("TitleMusic.ogg", 0.0f);

	fx = App->audio->LoadFx("Game/Audios/Menu/enter.wav");  
	App->renderer->camera.x = App->renderer->camera.y = 0;

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	App->textures->Unload(background);

	return true;
}

// Update: draw background
update_status ModuleSceneIntro::Update()
{
	// Draw everything --------------------------------------	
	App->renderer->Blit(background, 0, 0, NULL);

	if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_UP)
	{
		App->audio->PlayFx(fx);
		App->fade->FadeToBlack(this, App->scene, 3.0f);
	}

	return UPDATE_CONTINUE;
}