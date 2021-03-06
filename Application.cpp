#pragma once
#include "Application.h"

Application::Application()
{
	renderer = new ModuleRender(this);
	window = new ModuleWindow(this);
	textures = new ModuleTextures(this);
	input = new ModuleInput(this);
	audio = new ModuleAudio(this);
	scene = new ModuleScene(this, false);
	boss = new ModuleSceneBoss(this, false);
	fade = new ModuleFadeToBlack(this);
	particles = new ModuleParticles(this,false);
	player = new ModulePlayer(this, false);
	collision = new ModuleCollision(this, false);
	timer = new ModuleTimer(this, false);
	intro = new ModuleSceneIntro(this, true);
	level = new ModuleLevel(this, false);
	enemy = new ModuleEnemy(this, false);
	powerUp = new ModulePowerUp(this, false);
	credits = new ModuleCredits(this, false);
	sceneManager = new SceneManager(this);

	boss_enemy = new ModuleBossEnemy(this, false);
	

	map = new ModuleMap(this, false);


	// The order of calls is very important!
	// Modules will Init() Start() and Update in this order
	// They will CleanUp() in reverse order

	// Main Modules
	AddModule(window);
	AddModule(renderer);
	AddModule(textures);
	AddModule(input);
	AddModule(audio);
	
	AddModule(sceneManager);
	
	// Scenes
	AddModule(intro);
	AddModule(scene);

	AddModule(boss);
	
	

	AddModule(timer);
	AddModule(map);
	

	// Misc
	
	AddModule(particles);
	AddModule(collision);
	AddModule(level);
	AddModule(powerUp);

	// Characters
	AddModule(player);
	AddModule(enemy);
	AddModule(boss_enemy);
	AddModule(timer);

	AddModule(credits);


	AddModule(fade); // let this after all drawing
}

Application::~Application()
{
	delete renderer;
	delete window;
	delete textures;
	delete input;
	delete particles;
	delete audio;
	delete scene;
	delete boss;
	delete enemy;
	delete boss_enemy;
	delete player;
	delete level;
	delete fade;
	delete timer;
	delete collision;
	delete powerUp;
	delete credits;
}

bool Application::Init()
{
	bool ret = true;

	// Call Init() in all modules
	p2List_item<Module*>* item = list_modules.getFirst();

	while(item != NULL && ret == true)
	{
		ret = item->data->Init();
		item = item->next;
	}

	// After all Init calls we call Start() in all modules
	LOG("Application Start --------------");
	item = list_modules.getFirst();

	while(item != NULL && ret == true)
	{
		if(item->data->IsEnabled())
			ret = item->data->Start();
		item = item->next;
	}
	
	return ret;
}

// Call PreUpdate, Update and PostUpdate on all modules
update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;
	p2List_item<Module*>* item = list_modules.getFirst();

	while(item != NULL && ret == UPDATE_CONTINUE)
	{
		if(item->data->IsEnabled())
			ret = item->data->PreUpdate();
		item = item->next;
	}

	item = list_modules.getFirst();

	while(item != NULL && ret == UPDATE_CONTINUE)
	{
		if(item->data->IsEnabled())
  			ret = item->data->Update();
		item = item->next;
	}

	item = list_modules.getFirst();

	while(item != NULL && ret == UPDATE_CONTINUE)
	{
		if(item->data->IsEnabled())
			ret = item->data->PostUpdate();
		item = item->next;
	}

	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;
	p2List_item<Module*>* item = list_modules.getLast();

	while(item != NULL && ret == true)
	{
		ret = item->data->CleanUp();
		item = item->prev;
	}
	return ret;
}

void Application::AddModule(Module* mod)
{
	list_modules.add(mod);
}