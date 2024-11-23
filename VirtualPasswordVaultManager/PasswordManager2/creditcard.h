#pragma once
#include "passwordmanager.h"
class CreditCard
{
private:
	    UserLoginInfo* UsersArr;
public:
	    CreditCard(UserLoginInfo* UsersArr);
		bool searchByCreditCardNumber(const string &searchCreditCardNumber);
		void viewAllUserCreditCardInfo();
		bool deleteByCreditCardNo(string creditCardNumber);
		bool addCreditCardRecord(string creditCardTitle, string additionalNotes, string cardholderName,
                         string creditCardNumber, string cardCVV, string cardExpirationDate,
                         string issuingBankName, string bankWebsiteURL, string bankPhoneNumber);
		bool updateCreditCardRecord( string creditCardNumber);
		void showLog();
		void CreditCardInfoOptions(char * Log);
};