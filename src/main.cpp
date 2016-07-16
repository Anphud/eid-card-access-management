/*
	be-eid card reader C++ authorization system test
	(C) 2016 An Phu Dupont
*/

#include "identitycard.h"
#include <iostream>

void CardReader_CardInsertedEvent(IdentityCard* card);
void CardReader_CardPulledEvent();
int main()
{
	// Initialize
	InitializeAuthSystem();
	CardReader::SetCardInsertedEvent(&CardReader_CardInsertedEvent);
	CardReader::SetCardPulledEvent(&CardReader_CardPulledEvent);

	// Wait
	getchar();

	// Finalize
	DestroyAuthSystem();
}

void CardReader_CardInsertedEvent(IdentityCard* card)
{
	printf("Card found !\n");
	std::cout << card->m_IdentityFile.surname.Info() << std::endl << card->m_IdentityFile.firstnames.Info() << std::endl;
}

void CardReader_CardPulledEvent()
{
	printf("Card ejected !\n");
}