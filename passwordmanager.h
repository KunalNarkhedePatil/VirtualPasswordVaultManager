#pragma once
#include <iostream>
#include <limits>
#include <string>
#include <cstdlib>
#include <string.h>
#include <cstdio>
#include <windows.h> 

#define MAX_USER 50
#define LOG_SIZE 1024
#define LOG_MSG_SIZE 100
using namespace std;
char Log[LOG_SIZE];
#define DATE_AND_TIME "[" __DATE__ " " __TIME__ "] "
class StoreLoginInfo 
{
public:
	int LoginNo;
    string titleName;
    string loginName;
    string password;
    string URL;
    StoreLoginInfo* next;

   StoreLoginInfo(string titleName,string loginName,string password,string URL)
   {
	   this->LoginNo=0;
	   this->titleName=titleName;
	   this->loginName=loginName;
	   this->password=password;
	   this->URL=URL;
	   this->next=NULL;
   }
};

class StoreCreditCardInfo 
{
public:
    string creditCardTitle;      
    string additionalNotes;      
    string cardholderName;      
    string creditCardNumber;   
    string cardCVV;           
    string cardExpirationDate;  
    string issuingBankName;     
    string bankWebsiteURL;      
    string bankPhoneNumber; 
    StoreCreditCardInfo* next;  
    
    StoreCreditCardInfo(string creditCardTitle, string additionalNotes, string cardholderName,string creditCardNumber, string cardCVV, string cardExpirationDate,string issuingBankName, string bankWebsiteURL, string bankPhoneNumber) 
	{
        this->creditCardTitle = creditCardTitle;   
        this->additionalNotes = additionalNotes;   
        this->cardholderName = cardholderName;    
        this->creditCardNumber = creditCardNumber;  
        this->cardCVV = cardCVV;           
        this->cardExpirationDate = cardExpirationDate;
        this->issuingBankName = issuingBankName;   
        this->bankWebsiteURL = bankWebsiteURL;    
        this->bankPhoneNumber = bankPhoneNumber; 
        this->next = NULL; 
    }
};

class StoreBankAccountInfo
{
public:
	string accountNumber;
    string accountHolderName;
    string bankName;
    string accountType;
    double currentBalance;
    string accountCurrency;
    string accountPassword;
    string additionalNotes;
    string accountLinkMobileNumber;
    StoreBankAccountInfo* next;

    StoreBankAccountInfo(string accountNumber, string accountHolderName, string bankName, string accountType, double currentBalance, string accountCurrency, string accountPassword, string additionalNotes, string accountLinkMobileNumber) {
        this->accountNumber = accountNumber;
        this->accountHolderName = accountHolderName;
        this->bankName = bankName;
        this->accountType = accountType;
        this->currentBalance = currentBalance;
        this->accountCurrency = accountCurrency;
        this->accountPassword = accountPassword;
        this->additionalNotes = additionalNotes;
        this->accountLinkMobileNumber = accountLinkMobileNumber;
        this->next = NULL;
    }
};

class StorePassportInfo
{
public:
    string fullName;
    string passportNumber;
    string nationality;
    string birthDate;
    string birthPlace;
    string issueDate;
    string expirationDate;
    string issuingAuthority;
    StorePassportInfo* next;

    StorePassportInfo(string fullName, string passportNumber, string nationality, string birthDate, string birthPlace, string issueDate, string expirationDate, string issuingAuthority) 
	{
        this->fullName = fullName;
        this->passportNumber = passportNumber;
        this->nationality = nationality;
        this->birthDate = birthDate;
        this->birthPlace = birthPlace;
        this->issueDate = issueDate;
        this->expirationDate = expirationDate;
        this->issuingAuthority = issuingAuthority;
        this->next = NULL;
    }
};
#include <string>
#include <iostream>

using namespace std; // Using the standard namespace

class StoreDriverLicenseInfo
{
public:
    string driverFullName;
    string licenseNumber;
    string driverAddress;
    string driverDateOfBirth;
    string driverGender;
    string driverState;
    string driverCountry;
    string licenseIssueDate;
    string licenseExpDate;
	string additionalNotes;
	StoreDriverLicenseInfo *next;

    // Constructor
    StoreDriverLicenseInfo(string driverFullName,string licenseNumber,string driverAddress,string driverDateOfBirth,string driverGender,string driverState,string driverCountry,string licenseIssueDate,string licenseExpDate,string additionalNotes)
    {
        this->driverFullName = driverFullName;
        this->licenseNumber = licenseNumber;
        this->driverAddress = driverAddress;
        this->driverDateOfBirth = driverDateOfBirth;
        this->driverGender = driverGender;
        this->driverState = driverState;
        this->driverCountry = driverCountry; 
        this->licenseIssueDate = licenseIssueDate; 
        this->licenseExpDate = licenseExpDate; 
		this->additionalNotes= additionalNotes;
		this->next=NULL;
    }
};


class UserFunc
{
public:
    StoreLoginInfo* ptrStoreLoginInfo;
	StoreCreditCardInfo * ptrStoreCreditCardInfo;
	StoreBankAccountInfo * ptrStoreBankAccountInfo;
	StorePassportInfo * ptrStorePassportInfo;
	StoreDriverLicenseInfo *ptrStoreDriverLicenseInfo;

    char Logs[2000];

	UserFunc()
	{
		ptrStoreLoginInfo=NULL;
		ptrStoreCreditCardInfo=NULL;
		ptrStoreBankAccountInfo=NULL;
		ptrStorePassportInfo=NULL;
		ptrStoreDriverLicenseInfo=NULL;
		this->Logs[0]='\0';
	}
};

class UserLoginInfo 
{
public:
    string userName;
    string password;
    UserFunc* ptrUserFunc;
    UserLoginInfo()
	{
		this->ptrUserFunc=NULL;
	} 
};

class SuperBlock 
{
public:
    int totalInodes;
    int freeInode;

	SuperBlock()
	{
	    this->totalInodes=MAX_USER;
	   this->freeInode=MAX_USER;
	}

};

class PasswordManager 
{
private:
    UserLoginInfo* UsersArr[MAX_USER];
    SuperBlock superBlock;

public:
    PasswordManager();
    ~PasswordManager();
	UserLoginInfo* getUser(int userIndex);
	bool registerUser (const string& userName, const string& password);
	bool loginUser (const string& userName, const string& password);
	int findUserByUserName(const string& userName, const string& password);
	void waitFor20Seconds();
	void Functionality(const int userIndex,char *Log);
	int Settings(const int userIndex);
	bool changeMasterPassword(const int userIndex);
	int deleteAccount(const int userIndex);
	bool isStrongPassword(const string password);
};