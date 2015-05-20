#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"



ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	background = NULL;
	planes = NULL;

	zepelin = { 75, 0, 32, 19};
	ballon = { 80, 47, 44, 77};
	zepelin_fire = { 0, 0, 73, 41 };

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
	planes = App->textures->Load("planes.png");

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
	App->textures->Unload(planes);

	return true;
}

update_status ModuleSceneIntro::Update()
{
	// Draw background --------------------------------------	
	App->renderer->Blit(background, 0, 0, NULL);
	
	//Draw items----------------------------------------------
	App->renderer->Blit(planes, 0, 0, &zepelin);
	App->renderer->Blit(planes, 100, 100, &zepelin_fire);
	App->renderer->Blit(planes, 0, 0, &ballon);



	//Change scene--------------------------------------------
	if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_UP)
	{
		App->audio->PlayFx(fx);
		App->fade->FadeToBlack(this, App->scene, 3.0f);
	}

	return UPDATE_CONTINUE;
}