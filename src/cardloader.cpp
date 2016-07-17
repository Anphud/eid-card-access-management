#include "cardloader.h"
#include "authsystem.h"
#include "identitycard.h"
#include <string>
#include <thread>

CardReaderInsertedEvent CardReader::m_CardReader_CardInsertedEvent = NULL;
CardReaderPulledEvent CardReader::m_CardReader_CardPulledEvent = NULL;
CardReader* CardReader::m_Instance = nullptr;

extern int gIsCardInserted;

void loadCard(CK_FUNCTION_LIST_PTR f, CK_SESSION_HANDLE ses)
{
	CardReader* reader = CardReader::Create(f, ses);
	IdentityCard* card = reader->GetCard();
	CardReaderInsertedEvent event = CardReader::GetCardInsertedEvent();
	if (event) event(*card);
}

void destroyReader()
{
	delete CardReader::GetInstance();
}

CardProperty::CardProperty(const char* propertyName) :
	isPresent(false),
	propertyLabel(propertyName)
{
	char* pValue = NULL;
	CK_ULONG valueLength = 0;

	CardReader* reader = CardReader::GetInstance();
	if (!reader) return;

	int retVal = Beidsdk_GetObjectValue(reader->GetReaderFunctions(), reader->GetSessionHandle(), (CK_CHAR_PTR)propertyName, (CK_VOID_PTR*)&pValue, &valueLength);
	if (retVal == CKR_OK)
	{
		data.resize(valueLength);
		char* pDataDest = (char*)data.data();
		memcpy(pDataDest, pValue, valueLength);
		isPresent = true;
	}

	if (pValue != NULL) free(pValue);
}

void CheckCardPresent();
CardReader::CardReader() :
	m_IdentityCard(nullptr)
{

}

CardReader::~CardReader()
{
	m_Instance = nullptr;
	delete m_IdentityCard;
	m_IdentityCard = nullptr;
}

CardReader* CardReader::GetInstance()
{
	return m_Instance;
}

CardReader* CardReader::Create(CK_FUNCTION_LIST_PTR f, CK_SESSION_HANDLE ses)
{
	if (!m_Instance) 
	{
		m_Instance = new CardReader();
		m_Instance->m_pFunctions = f;
		m_Instance->m_Session = ses;
	}
	return m_Instance;
}

void CardReader::SetCard(IdentityCard* card)
{
	CardReader* reader = CardReader::GetInstance();
	if (reader->m_IdentityCard)
	{
		delete reader->m_IdentityCard;
		reader->m_IdentityCard = nullptr;
	}

	reader->m_IdentityCard = card;
}

IdentityCard* CardReader::GetCard() 
{
	if (!m_IdentityCard) m_IdentityCard = new IdentityCard();
	return m_IdentityCard; 
}

void CardReader::SetCardInsertedEvent(CardReaderInsertedEvent p) { m_CardReader_CardInsertedEvent = p; }
void CardReader::SetCardPulledEvent(CardReaderPulledEvent p) { m_CardReader_CardPulledEvent = p; }

void cardPulled() 
{
	CardReader* reader = CardReader::GetInstance();
	reader->SetCard(nullptr);
	CardReaderPulledEvent event = reader->GetCardPulledEvent();
	if (event) event();
}

bool gRunAuthSystem = true;
void CheckCardPresent()
{
	while (gRunAuthSystem)
	{
		beidsdk_GetData();
		AuthSysSleep(2000);
	}
}

std::thread* gReaderThread;
void InitializeAuthSystem()
{
	gReaderThread = new std::thread(CheckCardPresent);
}

void DestroyAuthSystem()
{
	gRunAuthSystem = false;
	gReaderThread->join();
	delete gReaderThread;
	destroyReader();
}