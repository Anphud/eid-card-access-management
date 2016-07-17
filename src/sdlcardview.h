#pragma once
#include "SDL.h"
#undef main

class SDLCardView
{
public:
	SDLCardView();
	~SDLCardView();

	bool SDLCardViewRunning() { return m_IsRunning; }
	void Update();

private:
	SDL_Window* m_pWindow;
	bool m_IsRunning;
};