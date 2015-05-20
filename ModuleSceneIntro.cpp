#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include <math.h>


ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	background = NULL;
	planes = NULL;
	text = NULL;

	zepelin = { 75, 0, 32, 19};
	ballon = { 80, 47, 44, 77};
	zepelin_fire = { 0, 0, 73, 41 };

	text_up = {0,0,255,66};

	text_down = {0, 66, 255, 85};

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
	text = App->textures->Load("title.png");

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

	//Text
	text_up_position.x = -256;
	text_up_position.y = 0;

	text_down_position.x = 257;
	text_down_position.y = 66;

	//Variables
	flash = 0;
	start_time = SDL_GetTicks();


	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	App->textures->Unload(background);
	App->textures->Unload(planes);
	App->textures->Unload(text);

	return true;
}

update_status ModuleSceneIntro::Update()
{
	actual_time = SDL_GetTicks() - start_time;

	zepelin_position.x += 0.3f;
	zepelin_fire_position.x -= 0.8f;
	ballon_position.x += 0.4f;
	ballon_position.y += sin(0.003f*SDL_GetTicks())*0.3f;

	//Text apears after 3s---------------------------------------
	if (actual_time > 3000) 
	{
		if (text_up_position.x < 0)
		{
			text_up_position.x += 8;
			text_down_position.x -= 8;
		}
		else
		{
			
			if (flash == 0)
			{
				flash = 1;
				flash_startime = actual_time;
			}

			text_up_position.x = 0;
			text_down_position.x = 0;
		}
	}
	
	
	

	// Draw background --------------------------------------	
	App->renderer->Blit(background, 0, 0, NULL);
	
	//Draw items----------------------------------------------
	App->renderer->Blit(planes, zepelin_position.x, zepelin_position.y, &zepelin);
	App->renderer->Blit(planes, zepelin_fire_position.x, zepelin_fire_position.y, &zepelin_fire);
	App->renderer->Blit(planes, ballon_position.x, ballon_position.y, &ballon);

	//Draw text------------------------------------------------
	App->renderer->Blit(text, text_up_position.x, text_up_position.y, &text_up);
	App->renderer->Blit(text, text_down_position.x, text_down_position.y, &text_down);

	if (flash == 1 && actual_time - 50 <= flash_startime)
		App->renderer->DrawQuad({0,0,1000,1000}, 255, 255, 255, 255, false);


	//Change scene--------------------------------------------
	if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_UP)
	{
		App->audio->PlayFx(fx);
		App->fade->FadeToBlack(this, App->scene, 3.0f);
	}

	return UPDATE_CONTINUE;
}