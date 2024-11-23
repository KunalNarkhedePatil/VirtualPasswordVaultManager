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

class UserFunc
{
public:
    StoreLoginInfo* ptrStoreLoginInfo;
	StoreCreditCardInfo * ptrStoreCreditCardInfo;
    char Logs[2000];
	//int countLoginInfo;

	UserFunc()
	{
		ptrStoreLoginInfo=NULL;
		ptrStoreCreditCardInfo=NULL;
		this->Logs[0]='\0';
		//countLoginInfo=0;
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
};