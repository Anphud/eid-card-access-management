#include "sdlcardview.h"
#include "authsystem.h"
#include <stdio.h>

SDLCardView::SDLCardView()
{
	SDL_Init(SDL_INIT_VIDEO);
	m_pWindow = SDL_CreateWindow("An SDL2 window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 320, 240, SDL_WINDOW_OPENGL);

	if (m_pWindow == NULL) 
	{
		printf("Could not create window: %s\n", SDL_GetError());
	}
}

SDLCardView::~SDLCardView()
{
	SDL_DestroyWindow(m_pWindow);
	SDL_Quit();
}

void SDLCardView::Update()
{
	SDL_Event e;
	while (SDL_PollEvent(&e) != 0)
	{
		if (e.type == SDL_QUIT)
		{
			m_IsRunning = false;
		}
	}

	AuthSysSleep(100);
}