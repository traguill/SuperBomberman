#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"



ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	graphics = NULL;

	position.x = 100;
	position.y = 216;

	// idle no animation
	idle.frames.PushBack({70, 38, 15, 23});
	idle.speed = 0;

	// walk Right
	right.frames.PushBack({ 178, 38, 18, 23 });
	right.frames.PushBack({ 160, 38, 18, 23 });
	right.frames.PushBack({ 178, 38, 18, 23 });
	right.frames.PushBack({ 197, 38, 18, 23 });
	right.speed = 0.1f;

	// walk Left
	left.frames.PushBack({ 124, 38, 18, 23 });
	left.frames.PushBack({ 106, 38, 18, 23 });
	left.frames.PushBack({ 124, 38, 18, 23 });
	left.frames.PushBack({ 143, 38, 18, 23 });
	left.speed = 0.1f;

	// walk Down
	down.frames.PushBack({ 70, 38, 15, 23 });
	down.frames.PushBack({ 52, 38, 15, 23 });
	down.frames.PushBack({ 70, 38, 15, 23 });
	down.frames.PushBack({ 88, 38, 15, 23 });
	down.speed = 0.1f;

	// walk Up
	up.frames.PushBack({ 237, 38, 15, 23 });
	up.frames.PushBack({ 219, 38, 15, 23 });
	up.frames.PushBack({ 237, 38, 15, 23 });
	up.frames.PushBack({ 255, 38, 15, 23 });
	up.speed = 0.1f;
	
	
	
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	graphics = App->textures->Load("GameAssets.png"); 

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(graphics);

	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	Animation* current_animation = &idle;
	// debug camera movement --------------------------------
	int speed = 1;

	if(App->input->keyboard[SDL_SCANCODE_A] == 1)
	{
		current_animation = &left;
		position.x -= speed;
	}

	if(App->input->keyboard[SDL_SCANCODE_D] == 1)
	{
		current_animation = &right;
		position.x += speed;
	}

	if (App->input->keyboard[SDL_SCANCODE_S] == 1)
	{
		current_animation = &down;
		position.y += speed;
	}

	if (App->input->keyboard[SDL_SCANCODE_W] == 1)
	{
		current_animation = &up;
		position.y -= speed;
	}

	// Draw everything --------------------------------------
	SDL_Rect r = current_animation->GetCurrentFrame();

	App->renderer->Blit(graphics, position.x, position.y - r.h, &r);

	return UPDATE_CONTINUE;
}