#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"


ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	graphics = NULL;
	current_animation = NULL;


	position.x = 150;
	position.y = 120;

	// idle animation (just the ship)
	idle.frames.PushBack({ 70, 38, 16, 24 }); //LOOK DOWN
	idle.frames.PushBack({ 179, 38, 16, 24 }); //LOOK RIGHT
	idle.frames.PushBack({ 124, 38, 16, 24 });//LOOK LEFT
	idle.frames.PushBack({ 237, 38, 16, 24 });//LOOK UP


	// walk Right
	right.frames.PushBack({ 197, 38, 16, 24 });
	right.frames.PushBack({ 179, 38, 16, 24 });
	right.frames.PushBack({ 161, 38, 16, 24 });
	right.frames.PushBack({ 179, 38, 16, 24 });
	right.speed = 0.1f;

	// walk Left
	left.frames.PushBack({ 142, 38, 16, 24 });
	left.frames.PushBack({ 124, 38, 16, 24 });
	left.frames.PushBack({ 105, 38, 16, 24 });
	left.frames.PushBack({ 124, 38, 16, 24 });
	
	left.speed = 0.1f;

	// walk Down
	down.frames.PushBack({ 88, 38, 16, 22 });
	down.frames.PushBack({ 70, 38, 16, 24 });
	down.frames.PushBack({ 52, 38, 16, 24 });
	down.frames.PushBack({ 70, 38, 16, 24 });
	
	down.speed = 0.1f;

	// walk Up
	up.frames.PushBack({ 255, 38, 16, 24 });
	up.frames.PushBack({ 237, 38, 16, 24 });
	up.frames.PushBack({ 219, 38, 16, 24 });
	up.frames.PushBack({ 237, 38, 16, 24 });
	
	up.speed = 0.1f;


}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	graphics = App->textures->Load("Game/GameAssets.png");
	
	direction = downD;

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

	Animation* current_animation = &idle; //Posem la animacio de quiet per defecte i despres comprovem si ha apretat alguna tecla aixi evitem fer la comprovació que havies fet al final.

	int speed = 1;

	if (App->input->keyboard[SDL_SCANCODE_A])
	{
		current_animation = &left;
		position.x -= speed;
		direction = leftD;
		
	}

	if (App->input->keyboard[SDL_SCANCODE_D])
	{
		current_animation = &right;
		position.x += speed;
		direction = rightD;
	}

	if (App->input->keyboard[SDL_SCANCODE_S])
	{
		current_animation = &down;
		position.y += speed;
		direction = downD;
		
	}

	if (App->input->keyboard[SDL_SCANCODE_W])
	{
		current_animation = &up;
		position.y -= speed;
		direction = upD;
		
	}
	//AIXO ho guardo per si es pot aprofitar mes endavant
	/*if(App->input->keyboard_down[SDL_SCANCODE_B] == 1)
	{
	App->particles->AddParticle(App->particles->explosion, position.x, position.y + 25);
	App->particles->AddParticle(App->particles->explosion, position.x - 25, position.y, 500);
	App->particles->AddParticle(App->particles->explosion, position.x, position.y - 25, 1000);
	App->particles->AddParticle(App->particles->explosion, position.x + 25, position.y, 1500);
	}
	*/

	
	

	// Draw everything --------------------------------------
	SDL_Rect r;
	if (current_animation != &idle)																//Comprovem si esta en una animacio o parat, si esta parat li asignem el frame manualment.
		r = current_animation->GetCurrentFrame();
	else
		r = current_animation->frames[direction];

	App->renderer->Blit(graphics, position.x, position.y -r.h, &r);

	return UPDATE_CONTINUE;
}