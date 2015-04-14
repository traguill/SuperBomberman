#pragma once
#include "Application.h"

Application::Application()
{
	renderer = new ModuleRender(this);
	window = new ModuleWindow(this);
	textures = new ModuleTextures(this);
	input = new ModuleInput(this);
	audio = new ModuleAudio(this);
	timer = new ModuleTimer(this, true);
	//TODO:
	//Init the modules/scenes here:
	//yourscene = new ModuleYourScene(this, false);  -->Set to true the first scene.
	player = new ModulePlayer(this, false);
	scene = new ModuleScene(this, false);
	fade = new ModuleFadeToBlack(this);

	// The order of calls is very important!
	// Modules will Init() Start() and Update in this order
	// They will CleanUp() in reverse order

	// Main Modules
	AddModule(window);
	AddModule(renderer);
	AddModule(textures);
	AddModule(input);
	AddModule(audio);

	// Scenes
	AddModule(scene);

	// Timer and status
	AddModule(timer);
	
	// Characters
	AddModule(player);

	// Misc
	AddModule(fade); // let this after all drawing
}

Application::~Application()
{
	delete renderer;
	delete window;
	delete textures;
	delete input;
	delete audio;
	//TODO:
	//Delete the modules here, IN THE SAME ORDER!
	delete timer;
	delete player;
	delete fade;
	
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