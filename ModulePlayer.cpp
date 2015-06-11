#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"


ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	graphics = NULL;
	current_animation = NULL;
	last_bomb = NULL;
	
	fxStep = 0;
	fxPut = 0;
	audioChannel = 0;
	

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
	die.frames.PushBack({ 112, 68, 16, 24 });
	die.speed = 0.2f;
	die.loop = false;

	//Win
	
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
	win.frames.PushBack({ 209, 26, 16, 24 });
	win.speed = 0.1f;
	win.loop = false;





}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	graphics = App->textures->Load("Bomberman.png");
	fxStep = App->audio->LoadFx("Game/Audios/Gameplay/Step.wav");
	fxPut = App->audio->LoadFx("Game/Audios/Gameplay/PutBomb.wav");
	fxDie = App->audio->LoadFx("Game/Audios/Gameplay/bomberman_die.wav");

	if (App->scene->IsEnabled())
	{
		position.x = 24;
		position.y = 56;
		direction_player = downD;
	}
	if (App->boss->IsEnabled())
	{
		position.x = 104;
		position.y = 216;
		direction_player = upD;
	}
	

	collider = App->collision->AddCollider({ position.x, position.y-16, 16, 16 }, COLLIDER_PLAYER, this);


	

	bomb_collision = false;
	game_over_player = false;

	game_win = false;
	win.Reset();
	die.Reset();

	current_bombs = 0;
	max_bombs = App->sceneManager->player_max_bombs;
	lifes = 5;
	speed = App->sceneManager->player_speed;


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


	

	//Checks the intro of the boss scene
	bool can_start = true;
	if (App->boss->IsEnabled())
		can_start = false;
	if (!can_start)
	{
		if (App->boss_enemy->start_time + 3000 < App->boss_enemy->time)
			can_start = true;
	}
	

	if (!game_over_player && can_start &&!game_win && !App->boss_enemy->game_over_boss)
	{
		if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
		{
			current_animation = &left;

			for (int i = 0; i < speed; i++)
			{
				position.x--;
			}
			direction_player = leftD;

		

			
			if (!App->audio->IsPlaying(audioChannel))
			{
				audioChannel = App->audio->PlayFx(fxStep);
			}

		}


			

		if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
		{
			current_animation = &right;

			for (int i = 0; i < speed; i++)
			{
				position.x++;
			}
			direction_player = rightD;

			if (!App->audio->IsPlaying(audioChannel))
			{
				audioChannel = App->audio->PlayFx(fxStep);
			}
			
		}

		if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
		{
			current_animation = &down;
			for (int i = 0; i < speed; i++)
			{
				position.y++;
			}
			direction_player = downD;



			if (!App->audio->IsPlaying(audioChannel))
			{
				audioChannel = App->audio->PlayFx(fxStep);
			}

		}

		if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
		{
			current_animation = &up;

			for (int i = 0; i < speed; i++)
			{
				position.y--;
			}
			direction_player = upD;

		


			if (!App->audio->IsPlaying(audioChannel))
			{
				audioChannel = App->audio->PlayFx(fxStep);
			}
		}

		if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_UP && current_bombs < max_bombs)
		{

 			last_bomb = App->particles->AddParticle(App->particles->bomb, 24 + collider->GetPosLevel().x * TILE, 40 + collider->GetPosLevel().y* TILE, COLLIDER_BOMB, bombT);
			App->audio->PlayFx(fxPut);
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
		if (game_over_player)
		{
			current_animation = &die;
		}
		
	}

	if (game_over_player && current_animation->Finished() && current_animation == &die)
	{
		if (App->scene->IsEnabled())
		{
			if (lifes != 0)
			{
				position.x = 24;
				position.y = 56;
				game_over_player = false;
				current_animation = &idle;
				direction_player = downD;
			}
			else
				App->scene->game_over = true;
		}


		if (App->boss->IsEnabled())
		{
			if (lifes != 0)
			{
				position.x = 104;
				position.y = 216;
				direction_player = upD;
				game_over_player = false;
				current_animation = &idle;
			}
			else
				App->boss->game_over = true;
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
		r = current_animation->frames[direction_player];
	
	
	
		
	
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
		CrossWall(direction_player, c2);
	}

	//Killing objects-----------------------------------------------------------------
	if (c2->type == COLLIDER_ENEMY)
	{
		if (!game_over_player)
		{
			die.Reset();
			lifes--;
			game_over_player = true;
			App->audio->PlayFx(fxDie);
		}
		
		return;
	}
	if (c2->type == COLLIDER_EXPLOSION)
	{
		if (c1->GetPosLevel().x == c2->GetPosLevel().x || c1->GetPosLevel().y == c2->GetPosLevel().y)
		{
			if (!game_over_player)
			{
				die.Reset();
				lifes--;
				game_over_player = true;
				App->audio->PlayFx(fxDie);
			}
			
		}
			
	}
}





void ModulePlayer::CrossWall(Looking direction_player, Collider* c){


	p2Point<int> tmp;
	tmp.x = c->rect.x;
	tmp.y = c->rect.y;

	switch (direction_player)
	{
	case upD:
		switch (RightLeft(tmp))
		{
		case 0:	//left
			//GO UP LEFT
			position.x -= 1;
			return;
			break;
		case 2: //right
			//GO UP RIGHT
			position.x += 1;
			return;
			break;
		}
		break;
	case downD:
		switch (RightLeft(tmp))
		{
		case 0:	//Left
			//GO DOWN LEFT
			position.x -= 1;
			return;
			break;
		case 2: //Right
			//GO DOWN RIGHT
			position.x += 1;
			return;
			break;
		}
		break;
	case rightD:
		switch (UpDown(tmp))
		{
		case 0:	//Up
			//RIGHT UP
			position.y -= 1;
			return;
			break;
		case 2: //Down
			//RIGHT DOWN
			position.y += 1;
			return;
			break;
		}
		break;
	case leftD:
		switch (UpDown(tmp))
		{
		case 0:	//Up
			//left UP
			position.y -= 1;
			return;
			break;
		case 2: //Down
			//left DOWN
			position.y += 1;
			return;
			break;
		}
		break;
	}
	position = last_position;

}

int ModulePlayer::RightLeft(const p2Point<int> p) const{
	int dir = 1; //direction_player 0-left 1-NULL 2-right
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