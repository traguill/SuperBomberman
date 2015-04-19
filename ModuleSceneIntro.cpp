#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"



ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	graphics = NULL;
	fx = 0;
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

<<<<<<< HEAD
	graphics = App->textures->Load("Game/TitleScreen.png");
	App->audio->PlayMusic("Game/TitleMusic.ogg", 0.0f);
=======
	graphics = App->textures->Load("TitleScreen.png");
	App->audio->PlayMusic("TitleMusic.ogg", 0.0f);
>>>>>>> origin/master
	//fx = App->audio->LoadFx("rtype/starting.wav");
	App->renderer->camera.x = App->renderer->camera.y = 0;

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	App->textures->Unload(graphics);

	return true;
}

// Update: draw background
update_status ModuleSceneIntro::Update()
{
	// Draw everything --------------------------------------	
	App->renderer->Blit(graphics, 0, 0, NULL);

	if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_UP)
	{
		//App->audio->PlayFx(fx);
		App->fade->FadeToBlack(this, App->scene, 3.0f);
	}

	return UPDATE_CONTINUE;
}