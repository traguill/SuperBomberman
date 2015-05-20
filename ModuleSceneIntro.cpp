#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include <math.h>


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

	//Items
	zepelin_fire_position.x = 242;
	zepelin_fire_position.y = 88;

	zepelin_position.x = 60;
	zepelin_position.y = 130;

	ballon_position.x = 5;
	ballon_position.y = 10;

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
	zepelin_position.x += 0.3f;
	zepelin_fire_position.x -= 0.8f;
	ballon_position.x += 0.4f;
	ballon_position.y += sin(0.003f*SDL_GetTicks())*0.3f;
	

	// Draw background --------------------------------------	
	App->renderer->Blit(background, 0, 0, NULL);
	
	//Draw items----------------------------------------------
	App->renderer->Blit(planes, zepelin_position.x, zepelin_position.y, &zepelin);
	App->renderer->Blit(planes, zepelin_fire_position.x, zepelin_fire_position.y, &zepelin_fire);
	App->renderer->Blit(planes, ballon_position.x, ballon_position.y, &ballon);



	//Change scene--------------------------------------------
	if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_UP)
	{
		App->audio->PlayFx(fx);
		App->fade->FadeToBlack(this, App->scene, 3.0f);
	}

	return UPDATE_CONTINUE;
}