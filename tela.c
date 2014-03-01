#include <stdio.h>
#include <SDL/SDL.h>
#include <math.h>
#include <stdlib.h>
#include "SDL/SDL_rotozoom.h"

#define TRUE  1
#define FALSE 0

int main(int argc, char** argv)
{
	SDL_Surface* screen1;
	SDL_Init(SDL_INIT_EVERYTHING);
	screen1 = SDL_SetVideoMode(640,480,32,SDL_SWSURFACE);

	int quit = 0;

	SDL_Event event;

	while (!quit)
	{
		while(SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				quit = TRUE;
			}
		}
	}

	SDL_Quit();

	return 0;
}
