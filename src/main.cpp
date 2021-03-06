/*
	be-eid card reader C++ authorization system test
	(C) 2016 An Phu Dupont
*/

#include "identitycard.h"
#include "sdlcardview.h"
#include <iostream>

void CardReader_CardInsertedEvent(IdentityCard card);
void CardReader_CardPulledEvent();
int main(int argc, char* argv[])
{
	// Initialize
	InitializeAuthSystem();
	CardReader::SetCardInsertedEvent(&CardReader_CardInsertedEvent);
	CardReader::SetCardPulledEvent(&CardReader_CardPulledEvent);

	// Create view object
	SDLCardView* cardView = SDLCardView::GetInstance();

	// Program loop
	while (cardView->SDLCardViewRunning()) cardView->Update();

	// Finalize
	delete cardView;
	DestroyAuthSystem();
	return 0;
}

void CardReader_CardInsertedEvent(IdentityCard card)
{
	printf("Card found !\n");
	std::cout << card.m_IdentityFile.surname.Info() << std::endl << card.m_IdentityFile.firstnames.Info() << std::endl;

	SDLCardView::GetInstance()->SetIdentityCard(card);
}

void CardReader_CardPulledEvent()
{
	printf("Card ejected !\n");
	SDLCardView::GetInstance()->RemoveCard();
}