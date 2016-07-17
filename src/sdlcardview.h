#pragma once
#include "SDL.h"
#include "identitycard.h"
//#undef main

class SDLCardView
{
public:
	~SDLCardView();

	static SDLCardView* GetInstance();

	bool SDLCardViewRunning() { return m_IsRunning; }
	void SetIdentityCard(IdentityCard& card);
	void RendererClear();
	void RemoveCard();
	void Update();

private:
	SDLCardView();
	static SDLCardView* m_pInstance;

	SDL_Window* m_pWindow;
	SDL_Surface* m_pIdentityPhotoSurface;
	SDL_Texture* m_pIdentityPhotoTexture;
	SDL_Renderer* m_pRenderer;

	IdentityCard m_Card;
	bool m_IsCardSet;
	bool m_IsRunning;
};