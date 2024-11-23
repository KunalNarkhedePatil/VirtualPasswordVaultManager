#pragma once
#include "passwordmanager.h"

class BankAccount
{
private:
	    UserLoginInfo* UsersArr;
public:
	    BankAccount(UserLoginInfo* UsersArr);
		bool searchByBankAccountNumber(const string &accountNumber);
		bool viewAllUserBankAccountInfo();
		bool deleteByBankAccountNo(const string &accountNumber);
		bool addBankAccountRecord(string accountNumber,string accountHolderName,string bankName,string accountType,double currentBalance,string accountCurrency,string accountPassword,string additionalNotes,string accountLinkMobileNumber);
		bool updateBankAccountRecord(string accountNumber);
		void showLog();
		void BankAccountInfoOptions(char * Log);
		int isValidAccountNumber(const string& accountNumber);
};