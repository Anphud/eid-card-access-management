#pragma once
#include "base.h"
#include <string>

// Predefinitions
struct IdentityCard;
typedef void(*CardReaderInsertedEvent)(IdentityCard);
typedef void(*CardReaderPulledEvent)();

// Card propertes
class CardProperty
{
public:
	bool isPresent;
	std::string data;
	const char* propertyLabel;

	CardProperty(const char* propertyName);
	std::string ToString() { return data; }
	const char* ToCString() { return data.c_str(); }
	std::string Info() { return std::string(propertyLabel).append(": ").append(data); }
	size_t Length() { return data.size(); }
};

struct IdentityFile
{
	CardProperty gender = CardProperty("gender");
	CardProperty surname = CardProperty("surname");
	CardProperty firstnames = CardProperty("firstnames");
	CardProperty cardNumber = CardProperty("card_number");
	CardProperty chipNumber = CardProperty("chip_number");
	CardProperty nationality = CardProperty("nationality");
	CardProperty dateOfBirth = CardProperty("date_of_birth");
	CardProperty validityEnd = CardProperty("validity_end_date");
	CardProperty nationalNumber = CardProperty("national_number");
	CardProperty validityBegin = CardProperty("validity_begin_date");
	CardProperty locationOfBirth = CardProperty("location_of_birth");
	CardProperty issuingMunicipality = CardProperty("issuing_municipality");
};

struct Address
{
	CardProperty zip = CardProperty("address_zip");
	CardProperty municipality = CardProperty("address_municipality");
	CardProperty streetAndNumber = CardProperty("address_street_and_number");
};

struct Photo
{
	CardProperty photo = CardProperty("PHOTO_FILE");
};

struct IdentityCard
{
	IdentityFile m_IdentityFile;
	Address m_Address;
	Photo m_Photo;
};

class CardReader
{
public:
	~CardReader();
	static CardReader* Create(CK_FUNCTION_LIST_PTR f, CK_SESSION_HANDLE ses);
	static CardReader* GetInstance();
	void SetCard(IdentityCard*);
	IdentityCard* GetCard();

	CK_FUNCTION_LIST_PTR GetReaderFunctions() { return m_pFunctions; }
	CK_SESSION_HANDLE GetSessionHandle() { return m_Session; }

	static void SetCardInsertedEvent(CardReaderInsertedEvent);
	static void SetCardPulledEvent(CardReaderPulledEvent);
	static CardReaderInsertedEvent GetCardInsertedEvent() { return m_CardReader_CardInsertedEvent; }
	static CardReaderPulledEvent GetCardPulledEvent() { return m_CardReader_CardPulledEvent; }

private:
	CardReader();

	static CardReaderInsertedEvent m_CardReader_CardInsertedEvent;
	static CardReaderPulledEvent m_CardReader_CardPulledEvent;
	static CardReader* m_Instance;
	IdentityCard* m_IdentityCard;
	CK_FUNCTION_LIST_PTR m_pFunctions;
	CK_SESSION_HANDLE m_Session;
};

void InitializeAuthSystem();
void DestroyAuthSystem();