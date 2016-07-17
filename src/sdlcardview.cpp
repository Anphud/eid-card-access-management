#include "sdlcardview.h"
#include "authsystem.h"
#include "SDL_image.h"
#include <stdio.h>

SDLCardView* SDLCardView::m_pInstance = nullptr;
SDLCardView* SDLCardView::GetInstance()
{
	if (!m_pInstance)
		m_pInstance = new SDLCardView();

	return m_pInstance;
}

SDLCardView::SDLCardView() :
	m_pIdentityPhotoSurface(nullptr),
	m_pIdentityPhotoTexture(nullptr),
	m_IsCardSet(false)
{
	SDL_Init(SDL_INIT_VIDEO);
	m_pWindow = SDL_CreateWindow("An SDL2 window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 320, 240, SDL_WINDOW_OPENGL);
	if (m_pWindow == NULL)
		printf("Could not create window: %s\n", SDL_GetError());

	m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
}

SDLCardView::~SDLCardView()
{
	if (m_pIdentityPhotoSurface) SDL_FreeSurface(m_pIdentityPhotoSurface);
	if (m_pIdentityPhotoTexture) SDL_DestroyTexture(m_pIdentityPhotoTexture);
	SDL_DestroyRenderer(m_pRenderer);
	SDL_DestroyWindow(m_pWindow);

	SDL_Quit();
}

void SDLCardView::Update()
{
	if (m_IsCardSet)
	{
		SDL_RenderCopy(m_pRenderer, m_pIdentityPhotoTexture, NULL, NULL);
		SDL_RenderPresent(m_pRenderer);
	}
	else
	{
	}

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

void SDLCardView::SetIdentityCard(IdentityCard& card)
{
	m_Card = card;

	SDL_RWops* pixelsWop = SDL_RWFromConstMem(card.m_Photo.photo.ToCString(), card.m_Photo.photo.Length());
	m_pIdentityPhotoSurface = IMG_LoadJPG_RW(pixelsWop);
	m_pIdentityPhotoTexture = SDL_CreateTextureFromSurface(m_pRenderer, m_pIdentityPhotoSurface);

	m_IsCardSet = true;
}

void SDLCardView::RemoveCard()
{
	m_IsCardSet = false;
	RendererClear();
}

void SDLCardView::RendererClear()
{
	SDL_SetRenderDrawColor(m_pRenderer, 255, 255, 255, 255);
	SDL_RenderClear(m_pRenderer);
	SDL_RenderPresent(m_pRenderer);
}