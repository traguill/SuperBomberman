#include "Globals.h"
#include "Application.h"
#include "ModuleMap.h"

ModuleMap::ModuleMap(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	graphics = NULL;

	map.frames.PushBack({0,0,256,224});
	map.frames.PushBack({256,0,256,224});
	map.loop = true;
	map.speed = 0.03f;


}

ModuleMap::~ModuleMap()
{}



// Load assets
bool ModuleMap::Start()
{
	LOG("Loading scene");

	
	graphics = App->textures->Load("world_map.png");
	App->audio->PlayMusic("map_song.ogg", 0.0f);
	



	return true;
}

// UnLoad assets
bool ModuleMap::CleanUp()
{
	LOG("Unloading scene");
	App->textures->Unload(graphics);

	return true;
}

// Update: draw background
//nota mental: nunca poner un log dentro del update, se sobrecarag todo
update_status ModuleMap::Update()
{

	SDL_Rect map_r = map.GetCurrentFrame();
	App->renderer->Blit(graphics, 0, 0, &map_r);
	
	//App->fade->FadeToBlack(this, App->level, 3.0f);
	return UPDATE_CONTINUE;
}
