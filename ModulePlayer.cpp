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
	idle.frames.PushBack({ 162, 1, 16, 24 }); //LOOK RIGHT
	idle.frames.PushBack({ 17, 1, 16, 24 });//LOOK LEFT
	idle.frames.PushBack({ 114, 1, 16, 24 });//LOOK UP


	// walk Right
	right.frames.PushBack({ 178, 1, 16, 24 });
	right.frames.PushBack({ 162, 1, 16, 24 });
	right.frames.PushBack({ 146, 1, 16, 24 });
	right.frames.PushBack({ 162, 1, 16, 24 });
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
	die.frames.PushBack({ 0, 68, 16, 24 }); //TODO 0: Posar imatges mort correcatament.
	die.frames.PushBack({ 16, 59, 16, 33 });
	die.frames.PushBack({ 32, 68, 16, 24 });
	die.frames.PushBack({ 48, 68, 16, 24 });
	die.frames.PushBack({ 64, 68, 16, 24 });
	die.frames.PushBack({ 80, 68, 16, 24 });
	die.frames.PushBack({ 96, 68, 16, 24 });
	die.frames.PushBack({ 112, 68, 16, 24 });
	die.speed = 0.2f;
	die.loop = false;

	//Win
	win.frames.PushBack({ 0, 26, 16, 24 });
	win.frames.PushBack({ 17, 26, 16, 24 });
	win.frames.PushBack({ 34, 26, 16, 24 });
	win.frames.PushBack({ 49, 26, 16, 24 });
	win.frames.PushBack({ 66, 26, 16, 24 });
	win.frames.PushBack({ 83, 26, 16, 24 });
	win.frames.PushBack({ 98, 26, 16, 24 });
	win.frames.PushBack({ 115, 26, 16, 24 });
	win.frames.PushBack({ 132, 26, 16, 24 });
	win.frames.PushBack({ 149, 26, 16, 24 });
	win.frames.PushBack({ 166, 26, 16, 24 });
	win.frames.PushBack({ 183, 26, 16, 24 });
	win.speed = 0.05f;
	win.loop = false;





}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	graphics = App->textures->Load("Bomberman.png");

	collider = App->collision->AddCollider({ position.x, position.y-16, 16, 16 }, COLLIDER_PLAYER, this);

	direction = downD;

	bomb_collision = false;

	game_over_player = false;

	game_win = false;


	current_bombs = 0;

	position.x = 24;
	position.y = 56;

	speed = 1;
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

		if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_UP && current_bombs < MAX_BOMBS)
		{
			last_bomb = App->particles->AddParticle(App->particles->bomb, 24 + collider->GetPosLevel().x * TILE, 40 + collider->GetPosLevel().y* TILE, COLLIDER_BOMB, bombT);
			bomb_collision = true;
			current_bombs++;
		}
	}
	else
	{
		if (game_win)
		{

			current_animation = &win;
		}
		else
		{
			current_animation = &die;
		}
		
	}

	
	collider->SetPos(position.x, position.y-16);

	//check collisions with bomb
	if (!bomb_collision)
	{
		last_bomb = NULL;
	}
	bomb_collision = false;
	
	CheckLimits();
	
	//Check win game

	
		

	// Draw everything --------------------------------------
	SDL_Rect r;
	
	if (current_animation != &idle)				//Comprovem si esta en una animacio o parat, si esta parat li asignem el frame manualment.
		r = current_animation->GetCurrentFrame();
	else
		r = current_animation->frames[direction];
	
	
	if (game_over_player && current_animation->Finished())
		App->scene->game_over = true;
	
	if (game_win && current_animation->Finished())
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
		ThrowWall(direction, c2);
	}

	//Killing objects-----------------------------------------------------------------
	if (c2->type == COLLIDER_ENEMY)
	{
		game_over_player = true;
		return;
	}
	if (c2->type == COLLIDER_EXPLOSION)
	{
		if (c1->GetPosLevel().x == c2->GetPosLevel().x || c1->GetPosLevel().y == c2->GetPosLevel().y)
			game_over_player = true;
	}
}


void ModulePlayer::ThrowWall(Looking direction, Collider* c){

	p2Point<int> tmp;
	tmp.x = c->rect.x;
	tmp.y = c->rect.y;

	switch (direction)
	{
	case upD:
		switch (RightLeft(tmp))
		{
		case 0:	//left
			//GO UP LEFT
			position.x -= speed;
			return;
			break;
		case 2: //right
			//GO UP RIGHT
			position.x += speed;
			return;
			break;
		}
		break;
	case downD:
		switch (RightLeft(tmp))
		{
		case 0:	//Left
			//GO DOWN LEFT
			position.x -= speed;
			return;
			break;
		case 2: //Right
			//GO DOWN RIGHT
			position.x += speed;
			return;
			break;
		}
		break;
	case rightD:
		switch (UpDown(tmp))
		{
		case 0:	//Up
			//RIGHT UP
			position.y -= speed;
			return;
			break;
		case 2: //Down
			//RIGHT DOWN
			position.y += speed;
			return;
			break;
		}
		break;
	case leftD:
		switch (UpDown(tmp))
		{
		case 0:	//Up
			//left UP
			position.y -= speed;
			return;
			break;
		case 2: //Down
			//left DOWN
			position.y += speed;
			break;
		}
		break;
	}
	position = last_position;

}

int ModulePlayer::RightLeft(const p2Point<int> p) const{
	int dir = 1; //Direction 0-left 1-NULL 2-right
	int tolerance = 6;
	if (collider->rect.x + 16 <= p.x + tolerance)
		dir = 0;
	if (collider->rect.x >= p.x +16 - tolerance)
		dir = 2;

	return dir;
}

int ModulePlayer::UpDown(const p2Point<int> p) const{
	int dir = 1; //Direction 0-Up 1-NULL 2-Down
	int tolerance = 6;
	if (collider->rect.y +16 <= p.y + tolerance)
		dir = 0;
	if (collider->rect.y >= p.y + 16 - tolerance)
		dir = 2;

	return dir;
}

void ModulePlayer::CheckLimits(){
	if (collider->rect.x < 24 || collider->rect.x + 16 > 232 || collider->rect.y < 40 || collider->rect.y > 216-16)
		position = last_position;
}