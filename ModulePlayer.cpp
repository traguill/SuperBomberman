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

	graphics = App->textures->Load("GameAssets.png");

	collider = App->collision->AddCollider({ position.x-8, position.y-12, 16, 24 }, COLLIDER_PLAYER, this);

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

	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		current_animation = &left;
		position.x -= speed;
		direction = leftD;

	}

	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		current_animation = &right;
		position.x += speed;
		direction = rightD;
	}

	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
	{
		current_animation = &down;
		position.y += speed;
		direction = downD;

	}

	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
	{
		current_animation = &up;
		position.y -= speed;
		direction = upD;

	}


	

	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_UP)
	{
		App->particles->AddParticle(App->particles->bomb, position.x, position.y-13, COLLIDER_BOMB, bombT);
	}

	collider->SetPos(position.x, position.y-24);

	last_position = position; //Executar SEMPRE despres d'actualitzar el collider

	// Draw everything --------------------------------------
	SDL_Rect r;
	if (current_animation != &idle)																//Comprovem si esta en una animacio o parat, si esta parat li asignem el frame manualment.
		r = current_animation->GetCurrentFrame();
	else
		r = current_animation->frames[direction];

	App->renderer->Blit(graphics, position.x, position.y - r.h, &r);

	return UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	if (c2->type == COLLIDER_BLOCK || c2->type == COLLIDER_WALL)
	{
		position = last_position;
	}
}