#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"


ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	graphics = NULL;
	current_animation = NULL;
	last_bomb = NULL;


	

	// idle animation (just the ship)
	idle.frames.PushBack({ 66, 1, 16, 24 }); //LOOK DOWN
	idle.frames.PushBack({ 1, 38, 16, 24 }); //LOOK RIGHT
	idle.frames.PushBack({ 17, 1, 16, 24 });//LOOK LEFT
	idle.frames.PushBack({ 114, 1, 16, 24 });//LOOK UP


	// walk Right
	right.frames.PushBack({ 197, 38, 16, 24 });
	right.frames.PushBack({ 179, 38, 16, 24 });
	right.frames.PushBack({ 161, 38, 16, 24 });
	right.frames.PushBack({ 179, 38, 16, 24 });
	right.speed = 0.1f;

	// walk Left
	left.frames.PushBack({ 34, 1, 16, 24 });
	left.frames.PushBack({ 17, 1, 16, 24 });
	left.frames.PushBack({ 0, 1, 16, 24 });
	left.frames.PushBack({ 17, 1, 16, 24 });

	left.speed = 0.1f;

	// walk Down
	down.frames.PushBack({ 82, 1, 16, 24 });
	down.frames.PushBack({ 66, 1, 16, 24 });
	down.frames.PushBack({ 50, 1, 16, 24 });
	down.frames.PushBack({ 66, 1, 16, 24 });

	down.speed = 0.1f;

	// walk Up
	up.frames.PushBack({ 98, 1, 16, 24 });
	up.frames.PushBack({ 114, 1, 16, 24 });
	up.frames.PushBack({ 130, 1, 16, 24 });
	up.frames.PushBack({ 114, 1, 16, 24 });

	up.speed = 0.1f;

	//Dying
	die.frames.PushBack({ 343, 38, 16, 24 }); //TODO 0: Posar imatges mort correcatament.
	die.frames.PushBack({ 361, 38, 16, 24 });
	die.frames.PushBack({ 379, 38, 16, 24 });
	die.frames.PushBack({ 397, 38, 16, 24 });
	die.speed = 0.1f;
	die.loop = false;




}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	graphics = App->textures->Load("Bomberman.png");

	collider = App->collision->AddCollider({ position.x, position.y-8, 12, 12 }, COLLIDER_PLAYER, this);

	direction = downD;

	bomb_collision = false;

	game_over_player = false;

	position.x = 30;
	position.y = 30;

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
	last_position = position;

	Animation* current_animation = &idle; //Posem la animacio de quiet per defecte i despres comprovem si ha apretat alguna tecla aixi evitem fer la comprovació que havies fet al final.

	int speed = 1;

	if (!game_over_player)
	{
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
			last_bomb = App->particles->AddParticle(App->particles->bomb, position.x, position.y - 13, COLLIDER_BOMB, bombT);
			bomb_collision = true;
		}
	}
	else
	{
		current_animation = &die;
	}

	
	collider->SetPos(position.x, position.y-12);

	//check collisions with bomb
	if (!bomb_collision)
	{
		last_bomb = NULL;
	}
	bomb_collision = false;
	
	

	// Draw everything --------------------------------------
	SDL_Rect r;
	
	if (current_animation != &idle)				//Comprovem si esta en una animacio o parat, si esta parat li asignem el frame manualment.
		r = current_animation->GetCurrentFrame();
	else
		r = current_animation->frames[direction];
	
	
	if (game_over_player && current_animation->Finished())
		App->scene->game_over = true;
	

	App->renderer->Blit(graphics, position.x, position.y - r.h, &r);


	return UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	if (c2 == last_bomb)
	{
		bomb_collision = true;
		return;
	}
		
	//Blocks-----------------------------------------------------------------------
	if (c2->type == COLLIDER_BLOCK || c2->type == COLLIDER_WALL || c2->type == COLLIDER_BOMB)
	{
		position = last_position;
	}

	//Killing objects-----------------------------------------------------------------
	if (c2->type == COLLIDER_EXPLOSION || c2->type == COLLIDER_ENEMY)
	{
		game_over_player = true;
	}


	
	
	
	
	
}