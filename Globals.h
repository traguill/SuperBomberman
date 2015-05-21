#pragma once
#include <windows.h>
#include <stdio.h>

#define LOG(format, ...) log(__FILE__, __LINE__, format, __VA_ARGS__);

void log(const char file[], int line, const char* format, ...);

#define CAP(n) ((n <= 0.0f) ? n=0.0f : (n >= 1.0f) ? n=1.0f : n=n)

enum update_status
{
	UPDATE_CONTINUE = 1,
	UPDATE_STOP,
	UPDATE_ERROR
};

enum Looking {				//Les variables tenen una D al final de direccio, no es poden dir up,down,right i left perque es confonen amb les animacions.		
	downD = 0,
	rightD = 1,
	leftD = 2,
	upD = 3
};


// Configuration -----------
#define SCREEN_WIDTH 256
#define SCREEN_HEIGHT 224
#define SCREEN_SIZE 3  
#define TILE 16
#define TILE_WIDTH 16
#define TILE_HEIGHT 12
#define WIN_FULLSCREEN false
#define WIN_RESIZABLE false
#define WIN_BORDERLESS false
#define WIN_FULLSCREEN_DESKTOP false
#define VSYNC true
#define TITLE "SuperBomberman"


//BOMBERMAN

#define VELOCITY_ENEMY 1
#define DELAY_LEVEL_X 24
#define DELAY_LEVEL_Y 40

