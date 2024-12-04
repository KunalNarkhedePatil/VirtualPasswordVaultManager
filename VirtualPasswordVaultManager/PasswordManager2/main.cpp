#include "logins.h"
#include "creditcard.h"

Logins::Logins(UserLoginInfo *UsersArr)
{
	this->UsersArr = UsersArr;
}
bool Logins::searchByLoginName(const string &SearchLoginName)
{
	bool bFlag = 0;
	if (SearchLoginName.empty())
	{
		return false;
	}
	StoreLoginInfo *temp = UsersArr->ptrUserFunc->ptrStoreLoginInfo;

	while (temp != NULL)
	{
		if (temp->loginName == SearchLoginName)
		{
			bFlag = 1;
			cout << "Title Name: " << temp->titleName << endl;
			cout << "Login Name: " << temp->loginName << endl;
			cout << "Password: " << temp->password << endl;
			cout << "Site Name: " << temp->URL << endl;
			cout << "-------------------------------------" << endl;
		}
		temp = temp->next;
	}
	if (temp == NULL && bFlag == 0)
	{
		return false;
	}
}

void Logins::resetLoginNo()
{
	int iCnt = 1;
	StoreLoginInfo *temp = UsersArr->ptrUserFunc->ptrStoreLoginInfo;
	while (temp != NULL)
	{
		temp->LoginNo = iCnt;
		temp = temp->next;
		iCnt++;
	}
}
void Logins::viewAllUserLoginInfo()
{
	if (UsersArr == NULL)
	{
		return;
	}

	StoreLoginInfo *temp = UsersArr->ptrUserFunc->ptrStoreLoginInfo;
	cout << "=============================================" << endl;
	while (temp != NULL)
	{
		cout << "LoginNo:" << temp->LoginNo << endl;
		cout << "Title Name: " << temp->titleName << endl;
		cout << "Login Name: " << temp->loginName << endl;
		cout << "Password: " << temp->password << endl;
		cout << "Site Name: " << temp->URL << endl;
		cout << "=============================================" << endl;
		temp = temp->next;
	}
}
bool Logins::deleteByLoginNo(int loginNo)
{
	StoreLoginInfo *first = UsersArr->ptrUserFunc->ptrStoreLoginInfo;
	StoreLoginInfo *current = first;
	StoreLoginInfo *prev = NULL;

	while (first != NULL && first->LoginNo == loginNo)
	{
		StoreLoginInfo *temp = first;
		first = first->next;
		delete temp;
	}
	UsersArr->ptrUserFunc->ptrStoreLoginInfo = first;

	current = first;

	while (current != NULL)
	{
		if (current->LoginNo == loginNo)
		{
			prev->next = current->next;
			delete current;
			resetLoginNo();
			return true;
		}
		else
		{
			prev = current;
			current = current->next;
		}
	}
	return false;
}

bool Logins::addLoginRecord(string titleName, string loginName, string password, string URL)
{
	if (UsersArr == NULL)
		return false;

	StoreLoginInfo *newRecord = new StoreLoginInfo(titleName, loginName, password, URL);
	if (!newRecord)
		return false;
	StoreLoginInfo *temp = UsersArr->ptrUserFunc->ptrStoreLoginInfo;

	if (temp == NULL)
	{
		UsersArr->ptrUserFunc->ptrStoreLoginInfo = newRecord;
	}
	else
	{
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next = newRecord;
	}
	resetLoginNo();
	return true;
}

void Logins::updateLoginRecord(int loginNo)
{
	StoreLoginInfo *temp = UsersArr->ptrUserFunc->ptrStoreLoginInfo;

	while (temp != NULL)
	{
		if (temp->LoginNo == loginNo)
		{
			int choice = 0;
			do
			{
				cout << "Enter what you want to update" << endl;
				cout << "\n1. Title Name\n2. Login Name\n3. Password\n4. Site Name or URL\n5. Exit\n"
					 << endl;
				cout << "Enter choice: ";
				cin >> choice;
				cin.ignore();
				if (cin.fail())
				{
					cin.clear();
					cin.ignore(100, '\n');
					cout << "Invalid option. Please enter a number." << endl;
					continue;
				}
				if (choice < 1 || choice > 5)
				{
					cout << "Number out of range. Please enter a number between 1 and 5." << endl;
					continue;
				}
				switch (choice)
				{
				case 1:
				{
					string newTitleName;
					cout << "Enter New Title Name: ";
					cin >> newTitleName;
					temp->titleName = newTitleName;
					break;
				}
				case 2:
				{
					string newLoginName;
					cout << "Enter New Login Name: ";
					cin >> newLoginName;
					temp->loginName = newLoginName;
					break;
				}
				case 3:
				{
					string newPassword;
					cout << "Enter New Password: ";
					cin >> newPassword;

					temp->password = newPassword;
					break;
				}
				case 4:
				{
					string newURL;
					cout << "Enter New URL: ";
					cin >> newURL;
					temp->URL = newURL;
					break;
				}
				case 5:
				{
					return;
				}
				default:
					cout << "Invalid choice. Please try again." << endl;
					strcat(UsersArr->ptrUserFunc->Logs, "Invalid choice. Please try again.\n");
					break;
				}
			} while (choice != 5);
		}
		temp = temp->next;
	}
}



void Logins::loginInfoOptions(char *Log)
{
	strcat(UsersArr->ptrUserFunc->Logs, Log);
	Log[0] = '\0';
	int choice = 0;

	do
	{
		cout << "Enter the Functionality\n";
		cout << "1. Add Info\n2. View All User Login Info\n3. Search By Login Name\n4. Delete By Login No\n5. Update By Login No\n6. Exit\n";
		cout << "Enter choice: ";

		cin >> choice;

		if (cin.fail())
		{
			cin.clear();
			cin.ignore(100, '\n');
			cout << "Invalid option. Please enter a number." << endl;
			continue;
		}

		if (choice < 1 || choice > 6)
		{
			cout << "Number out of range. Please enter a number between 1 and 6." << endl;
			continue;
		}

		switch (choice)
		{
		case 1:
		{
			cin.ignore();
			string titleName, loginName, password, URL;

			cout << "Enter the title Name: ";
			getline(cin, titleName);

			cout << "Enter the login Name: ";
			getline(cin, loginName);

			cout << "Enter password: ";
			getline(cin, password);

			cout << "Enter the site Name or URL: ";
			getline(cin, URL);

			if (addLoginRecord(titleName, loginName, password, URL))
			{
				cout << "New record inserted successfully into Login Info." << endl;
				char logMessage[LOG_MSG_SIZE];
				sprintf(logMessage, "New record inserted successfully into Login Info with %s\n", loginName.c_str());
				strcat(UsersArr->ptrUserFunc->Logs, logMessage);
			}
			else
			{
				cout << "Failed to insert record." << endl;
				strcat(UsersArr->ptrUserFunc->Logs, "Failed to insert record.\n");
			}
			break;
		}
		case 2:
		{
			strcat(UsersArr->ptrUserFunc->Logs, "View All User Login Info.\n");
			viewAllUserLoginInfo();
			break;
		}
		case 3:
		{
			strcat(UsersArr->ptrUserFunc->Logs, "Search By Login Name.\n");
			string searchLoginName;
			cin.ignore();
			cout << "Enter the login name to search: ";
			getline(cin, searchLoginName);

			bool found = Logins::searchByLoginName(searchLoginName);

			if (found==false)
			{
				cout << "There is no such Login present." << endl;
				strcat(UsersArr->ptrUserFunc->Logs, "There is no such Login present.\n");
			}
			else
			{
				char logMessage[LOG_MSG_SIZE];
				sprintf(logMessage, "Search By Login Name with %s\n", searchLoginName.c_str());
				strcat(UsersArr->ptrUserFunc->Logs, logMessage);
			}
			break;
		}
		case 4:
		{
			viewAllUserLoginInfo();
			int loginNo = 0;
			cin.ignore();
			cout << "Enter the Login No to delete: ";
			cin >> loginNo;

			bool deleted = deleteByLoginNo(loginNo);

			if (deleted)
			{
				cout << "Deleted the login with No " << loginNo << endl;
				char logMessage[50];
				sprintf(logMessage, "Deleted the login with No %d\n", loginNo);
				strcat(UsersArr->ptrUserFunc->Logs, logMessage);
			}
			break;
		}
		case 5:
		{
			viewAllUserLoginInfo();
			int loginNo = 0;

			cout << "Enter the Login No to update: ";
			cin >> loginNo;

			updateLoginRecord(loginNo);

			char logMessage[50];
			sprintf(logMessage, "Updated the login with No %d\n", loginNo);
			strcat(UsersArr->ptrUserFunc->Logs, logMessage);
			break;
		}
		case 6:
			strcat(UsersArr->ptrUserFunc->Logs, "Exit\n");
			return;
		default:
			cout << "Invalid choice. Please try again." << endl;
			strcat(UsersArr->ptrUserFunc->Logs, "Invalid choice. Please try again.\n");
			break;
		}
	} while (choice != 6);
}

CreditCard::CreditCard(UserLoginInfo *UsersArr)
{
	this->UsersArr=UsersArr;
}

void CreditCard::viewAllUserCreditCardInfo()
{
	if (UsersArr == NULL || UsersArr->ptrUserFunc == NULL || UsersArr->ptrUserFunc->ptrStoreCreditCardInfo == NULL)
    {
        return;
    }

    StoreCreditCardInfo *temp = UsersArr->ptrUserFunc->ptrStoreCreditCardInfo;
    cout << "=============================================" << endl;
    while (temp != NULL)
    {
        cout << "Credit Card Title: " << temp->creditCardTitle << endl;
        cout << "Cardholder Name: " << temp->cardholderName << endl;
        cout << "Credit Card Number: " << temp->creditCardNumber << endl;
        cout << "CVV: " << temp->cardCVV << endl;
        cout << "Expiration Date: " << temp->cardExpirationDate << endl;
        cout << "Issuing Bank Name: " << temp->issuingBankName << endl;
        cout << "Bank Website URL: " << temp->bankWebsiteURL << endl;
        cout << "Bank Phone Number: " << temp->bankPhoneNumber << endl;
        cout << "=============================================" << endl;
        temp = temp->next;
    }
}
bool CreditCard::addCreditCardRecord(string creditCardTitle, string additionalNotes, string cardholderName,
                                      string creditCardNumber, string cardCVV, string cardExpirationDate,
                                      string issuingBankName, string bankWebsiteURL, string bankPhoneNumber)
{
    if (UsersArr == NULL || UsersArr->ptrUserFunc == NULL)
	{
        return false;
	}

    StoreCreditCardInfo *newRecord = new StoreCreditCardInfo(creditCardTitle, additionalNotes, cardholderName,
                                                              creditCardNumber, cardCVV, cardExpirationDate,
                                                              issuingBankName, bankWebsiteURL, bankPhoneNumber);
    
    if (newRecord == NULL)
    {
        return false;
    }

    StoreCreditCardInfo *temp = UsersArr->ptrUserFunc->ptrStoreCreditCardInfo;

    if (temp == NULL)
    {
        UsersArr->ptrUserFunc->ptrStoreCreditCardInfo = newRecord;
    }
    else
    {
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newRecord;
    }

    return true;
}

bool CreditCard::updateCreditCardRecord(string creditCardNumber)
{
    StoreCreditCardInfo *temp = UsersArr->ptrUserFunc->ptrStoreCreditCardInfo;

    while (temp != NULL)
    {
        if (temp->creditCardNumber == creditCardNumber)
        {
            int choice = 0;
            do
            {
                cout << "Enter what you want to update" << endl;
                cout << "\n1. Credit Card Title\n"
                     << "2. Additional Notes\n"
                     << "3. Cardholder Name\n"
                     << "4. Card CVV\n"
                     << "5. Card Expiration Date (MM/YY)\n"
                     << "6. Issuing Bank Name\n"
                     << "7. Bank Website URL\n"
                     << "8. Bank Customer Service Phone Number\n"
                     << "9. Exit\n" << endl;
                cout << "Enter choice: ";
                cin >> choice;
                cin.ignore(); // Clear the input buffer

                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(100, '\n');
                    cout << "Invalid option. Please enter a number." << endl;
                    continue;
                }

                if (choice < 1 || choice > 9)
                {
                    cout << "Number out of range. Please enter a number between 1 and 9." << endl;
                    continue;
                }

                switch (choice)
                {
                    case 1:
                    {
                        string newTitle;
                        cout << "Enter New Credit Card Title: ";
                        getline(cin, newTitle);
                        temp->creditCardTitle = newTitle;
                        cout << "Credit Card Title updated successfully." << endl;
                        break;
                    }
                    case 2:
                    {
                        string newNotes;
                        cout << "Enter New Additional Notes: ";
                        getline(cin, newNotes);
                        temp->additionalNotes = newNotes;
                        cout << "Additional Notes updated successfully." << endl;
                        break;
                    }
                    case 3:
                    {
                        string newCardholderName;
                        cout << "Enter New Cardholder Name: ";
                        getline(cin, newCardholderName);
                        temp->cardholderName = newCardholderName;
                        cout << "Cardholder Name updated successfully." << endl;
                        break;
                    }
                    case 4:
                    {
                        string newCVV;
                        cout << "Enter New Card CVV: ";
                        getline(cin, newCVV);
                        temp->cardCVV = newCVV;
                        cout << "Card CVV updated successfully." << endl;
                        break;
                    }
                    case 5:
                    {
                        string newExpirationDate;
                        cout << "Enter New Card Expiration Date (MM/YY): ";
                        getline(cin, newExpirationDate);
                        temp->cardExpirationDate = newExpirationDate;
                        cout << "Card Expiration Date updated successfully." << endl;
                        break;
                    }
                    case 6:
                    {
                        string newBankName;
                        cout << "Enter New Issuing Bank Name: ";
                        getline(cin, newBankName);
                        temp->issuingBankName = newBankName;
                        cout << "Issuing Bank Name updated successfully." << endl;
                        break;
                    }
                    case 7:
                    {
                        string newWebsiteURL;
                        cout << "Enter New Bank Website URL: ";
                        getline(cin, newWebsiteURL);
                        temp->bankWebsiteURL = newWebsiteURL;
                        cout << "Bank Website URL updated successfully." << endl;
                        break;
                    }
                    case 8:
                    {
                        string newPhoneNumber;
                        cout << "Enter New Bank Customer Service Phone Number: ";
                        getline(cin, newPhoneNumber);
                        temp->bankPhoneNumber = newPhoneNumber;
                        cout << "Bank Customer Service Phone Number updated successfully." << endl;
                        break;
                    }
                    case 9:
                    {
                        cout << "Exiting update menu." << endl;
                        return false; 
                    }
                    default:
                        cout << "Invalid choice. Please try again." << endl;
                        break;
                }
            } while (choice != 9); 
            return true;
        }
        temp = temp->next; 
    }
    cout << "Credit Card with number " << creditCardNumber << " not found." << endl;
	char logMessage[LOG_MSG_SIZE];
    sprintf(logMessage, "Credit Card with number  %s not found.\n", creditCardNumber.c_str());
    strcat(UsersArr->ptrUserFunc->Logs, logMessage);
}

void CreditCard::showLog()
{
	cout << "==============================================" << endl;
	cout << UsersArr->ptrUserFunc->Logs << endl;
	cout << "==============================================" << endl;
}

bool CreditCard::searchByCreditCardNumber(const string &searchCreditCardNumber)
{
    if (searchCreditCardNumber.empty())
    {
        return false;
    }

    StoreCreditCardInfo *temp = UsersArr->ptrUserFunc->ptrStoreCreditCardInfo;
    bool found = false;

    while (temp != NULL)
    {
        if (temp->creditCardNumber == searchCreditCardNumber)
        {
            found = true;
            cout << "Credit Card Title: " << temp->creditCardTitle << endl;
            cout << "Cardholder Name: " << temp->cardholderName << endl;
            cout << "Credit Card Number: " << temp->creditCardNumber << endl;
            cout << "CVV: " << temp->cardCVV << endl;
            cout << "Expiration Date: " << temp->cardExpirationDate << endl;
            cout << "Issuing Bank Name: " << temp->issuingBankName << endl;
            cout << "Bank Website URL: " << temp->bankWebsiteURL << endl;
            cout << "Bank Phone Number: " << temp->bankPhoneNumber << endl;
            cout << "-------------------------------------" << endl;
        }
        temp = temp->next;
    }

    return found;
}
bool CreditCard::deleteByCreditCardNo(string creditCardNumber)
{
    StoreCreditCardInfo *current = UsersArr->ptrUserFunc->ptrStoreCreditCardInfo;
    StoreCreditCardInfo *prev = NULL;

    while (current != NULL)
    {
        if (current->creditCardNumber == creditCardNumber)
        {
            if (prev == NULL) 
            {
                UsersArr->ptrUserFunc->ptrStoreCreditCardInfo = current->next;
            }
            else
            {
                prev->next = current->next;
            }
            delete current;
            
            return true;
        }
        prev = current;
        current = current->next;
    }
    return false;
}
void CreditCard::CreditCardInfoOptions(char *Log)
{
    strcat(UsersArr->ptrUserFunc->Logs, Log);
    Log[0] = '\0';
    int choice = 0;

    do
    {
        cout << "Enter the Functionality\n";
        cout << "1. Add Credit Card Info\n2. View All User CreditCard Info\n3. Search By CreditCard Number\n4. Delete By CreditCard No\n5. Update By CreditCard No\n6. Show Logs\n7. Exit\n";
        cout << "Enter choice: ";

        cin >> choice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(100, '\n');
            cout << "Invalid option. Please enter a number." << endl;
            continue;
        }

        if (choice < 1 || choice > 7)
        {
            cout << "Number out of range. Please enter a number between 1 and 7." << endl;
            continue;
        }

        switch (choice)
        {
        case 1:
        {
            cin.ignore();
            string creditCardTitle, additionalNotes, cardholderName, creditCardNumber, cardCVV, cardExpirationDate, issuingBankName, bankWebsiteURL, bankPhoneNumber;

            cout << "Enter the credit card title: ";
            getline(cin, creditCardTitle);

            cout << "Enter additional notes: ";
            getline(cin, additionalNotes);

            cout << "Enter the cardholder name: ";
            getline(cin, cardholderName);

            cout << "Enter the credit card number: ";
            getline(cin, creditCardNumber);

            cout << "Enter the card CVV: ";
            getline(cin, cardCVV);

            cout << "Enter the card expiration date (MM/YY): ";
            getline(cin, cardExpirationDate);

            cout << "Enter the issuing bank name: ";
            getline(cin, issuingBankName);

            cout << "Enter the bank website URL: ";
            getline(cin, bankWebsiteURL);

            cout << "Enter the bank customer service phone number: ";
            getline(cin, bankPhoneNumber);

            if (addCreditCardRecord(creditCardTitle, additionalNotes, cardholderName, creditCardNumber, cardCVV, cardExpirationDate, issuingBankName, bankWebsiteURL, bankPhoneNumber))
            {
                cout << "New record inserted successfully into CreditCardInfo." << endl;
                char logMessage[LOG_MSG_SIZE];
                sprintf(logMessage, "New record inserted successfully into CreditCardInfo %s\n", cardholderName.c_str());
                strcat(UsersArr->ptrUserFunc->Logs, logMessage);
            }
            else
            {
                cout << "Failed to insert record." << endl;
                strcat(UsersArr->ptrUserFunc->Logs, "Failed to insert record.\n");
            }
            break;
        }
        case 2:
        {
            strcat(UsersArr->ptrUserFunc->Logs, "View All User CreditCard Info.\n");
            viewAllUserCreditCardInfo(); 
            break;
        }
        case 3:
        {
            strcat(UsersArr->ptrUserFunc->Logs, "Search By Card Number.\n");
            string searchCardNumber;
            cin.ignore();
            cout << "Enter the Credit Card Number to search: ";
            getline(cin, searchCardNumber);

            bool found = searchByCreditCardNumber(searchCardNumber);

            if (!found)
            {
                cout << "There is no such Credit Card present." << endl;
                strcat(UsersArr->ptrUserFunc->Logs, "There is no such Credit Card present.\n");
            }
            else
            {
                char logMessage[LOG_MSG_SIZE];
                sprintf(logMessage, "Found Credit Card with number %s\n", searchCardNumber.c_str());
                strcat(UsersArr->ptrUserFunc->Logs, logMessage);
            }
            break;
        }
        case 4:
        {
            viewAllUserCreditCardInfo(); 
            string creditCardNumber;
            cin.ignore();
            cout << "Enter the Credit Card Number to delete: ";
            getline(cin, creditCardNumber);

            bool deleted = deleteByCreditCardNo(creditCardNumber);

            if (deleted)
            {
                cout << "Deleted the Credit Card with number " << creditCardNumber << endl;
                char logMessage[LOG_MSG_SIZE];
                sprintf(logMessage, "Deleted the Credit Card with number %s\n", creditCardNumber.c_str());
                strcat(UsersArr->ptrUserFunc->Logs, logMessage);
            }
            else
            {
                cout << "Failed to delete the Credit Card." << endl;
                strcat(UsersArr->ptrUserFunc->Logs, "Failed to delete the Credit Card.\n");
            }
            break;
        }
        case 5:
        {
        viewAllUserCreditCardInfo(); 
        string creditCardNumber;
        cout << "Enter the Credit Card Number to update: ";
        cin.ignore();
        getline(cin, creditCardNumber);

        bool updated = updateCreditCardRecord(creditCardNumber); 

        if (updated)
        {
            char logMessage[LOG_MSG_SIZE];
            sprintf(logMessage, "Updated the Credit Card with number %s\n", creditCardNumber.c_str());
            strcat(UsersArr->ptrUserFunc->Logs, logMessage);
        }
        else
        {
            cout << "Failed to update the Credit Card." << endl;
            strcat(UsersArr->ptrUserFunc->Logs, "Failed to update the Credit Card.\n");
        }
            break;
        }
        case 6:
        {
            showLog();  
            break;
        }
        case 7:
            strcat(UsersArr->ptrUserFunc->Logs, "Exit\n");
            return;
        default:
            cout << "Invalid choice. Please try again." << endl;
            strcat(UsersArr->ptrUserFunc->Logs, "Invalid choice. Please try again.\n");
            break;
        }
    } while (choice != 7);
}

PasswordManager::PasswordManager()
{
	for (int i = 0; i < MAX_USER; i++)
	{
		UsersArr[i] = NULL;
	}
}
PasswordManager::~PasswordManager()
{
	for (int i = 0; i < MAX_USER; i++)
	{
		delete UsersArr[i];
	}
}
UserLoginInfo *PasswordManager::getUser(int userIndex)
{
	return this->UsersArr[userIndex];
}
bool PasswordManager::registerUser(const string &userName, const string &password)
{
	if (userName.empty() || password.empty())
	{
		return false;
	}

	for (int i = 0; i < MAX_USER; i++)
	{
		if (UsersArr[i] == NULL)
		{
			UsersArr[i] = new UserLoginInfo();
			if (!UsersArr[i])
				return false; // Check for allocation failure
			UsersArr[i]->userName = userName;
			UsersArr[i]->password = password;
			UsersArr[i]->ptrUserFunc = new UserFunc;
			superBlock.freeInode--;
			return true;
		}
	}
	return false;
}
bool PasswordManager::loginUser(const string &userName, const string &password)
{
	if (userName.empty() || password.empty())
	{
		return false;
	}

	for (int i = 0; i < MAX_USER; i++)
	{
		if (UsersArr[i] != NULL &&
			UsersArr[i]->userName == userName &&
			UsersArr[i]->password == password)
		{

			return true;
		}
	}
	return false;
}
int PasswordManager::findUserByUserName(const string &userName, const string &password)
{
	bool bFlag = false;
	for (int i = 0; i < MAX_USER; i++)
	{
		if (UsersArr[i] != NULL && UsersArr[i]->userName == userName && UsersArr[i]->password == password)
		{
			bFlag = true;
			return i;
		}
	}
	if (bFlag == false)
	{
		return -1;
	}
}

void PasswordManager::waitFor20Seconds()
{
	cout << "Waiting for 20 seconds..." << endl;
	Sleep(20000);
	return;
}
bool PasswordManager::changeMasterPassword(const int userIndex)
{
	string oldPassword, newPassword, confirmPassword;
	cin.ignore();

	cout << "Enter your current password: ";
	getline(cin, oldPassword);

	cout << "Enter your new password: ";
	getline(cin, newPassword);

	cout << "Re-enter your new password to confirm: ";
	getline(cin, confirmPassword);

	if (newPassword != confirmPassword)
	{
		cout << "Passwords don't match. Try again." << endl;
		return false;
	}

	UsersArr[userIndex]->password = newPassword;
	
	return true;
}
int PasswordManager::deleteAccount(const int userIndex)
{
	
    char ch = '\0';
    cout << "Are you sure you want to delete your account? (Y/N): ";

    while (true) 
	{
        cin >> ch;

        if (ch == 'Y' || ch == 'y' || ch == 'N' || ch == 'n') 
		{
            break; 
        } 
		else 
		{
            cout << "Invalid input. Please enter Y or N." << endl;
            strcat(UsersArr[userIndex]->ptrUserFunc->Logs, "Invalid input. Please enter Y or N.\n");
        }
    }
 
    if (ch == 'Y' || ch == 'y') 
	{
        delete UsersArr[userIndex]; 
        UsersArr[userIndex] = NULL; 
        return 1;
    } 
	else 
	{
        return -2; 
    }
}
int PasswordManager::Settings(const int userIndex)
{
	int choice = 0;
	cout << "Select an option:" << endl;

	do
	{
		cout << "\n1. Change Master Password\n2. Delete Account\n3. Exit\n4. Logout\n";
		cout << "Enter your choice: ";
		cin >> choice;

		if (cin.fail())
		{
			cin.clear();
			cin.ignore(100, '\n');
			cout << "Invalid input. Please enter a number." << endl;
			strcat(UsersArr[userIndex]->ptrUserFunc->Logs, "Invalid input. Please enter a number.\n");
			continue;
		}

		if (choice < 1 || choice > 4)
		{
			cout << "Please enter a number between 1 and 4." << endl;
			continue;
		}

		switch (choice)
		{
		case 1:
		{

			bool success = changeMasterPassword(userIndex);
			if (success)
			{
				cout << "Master password chnage successfully." << endl;
				strcat(UsersArr[userIndex]->ptrUserFunc->Logs, "Master password chnage successfully.\n");
			}
			break;
		}
		case 2:
		{
			int iRet = deleteAccount(userIndex);
			if (iRet==1)
			{
				cout << "Account deleted successfully." << endl;
				return 2;
			}
			else if(iRet==-2)
			{
				 cout << "Account deletion canceled." << endl;
				 strcat(UsersArr[userIndex]->ptrUserFunc->Logs, "Account deletion canceled.\n");
			}
			break;
			
		}
		case 3:
			return 1;

		case 4:
			return 2;

		default:
			cout << "An error occurred. Try again." << endl;
			strcat(UsersArr[userIndex]->ptrUserFunc->Logs, "Invalid choice. Try again.\n");
			break;
		}
	} while (choice != 4);
}
void PasswordManager::Functionality(const int userIndex, char *Log)
{
	int choice = 0;
	cout << "-------------------------------------" << endl;
	cout << "Enter the Functionality" << endl;

	do
	{
		cout << "1. Logins\n2. Credit Card\n3. Bank Details\n4. Settings\n5. Logout\n";
		cout << "Enter choice: ";
		cin >> choice;

		if (cin.fail())
		{
			cin.clear();
			cin.ignore(100, '\n');
			cout << "Invalid option. Please enter a number." << endl;
			continue;
		}

		if (choice < 1 || choice > 5)
		{
			cout << "Number out of range. Please enter a number between 1 and 5." << endl;
			continue;
		}

		switch (choice)
		{
		case 1:
		{
			strcat(Log, "Login Functionality\n");
			Logins logins(UsersArr[userIndex]);
			logins.loginInfoOptions(Log);
			break;
		}
		case 2:
		{
			strcat(Log, "Login Functionality\n");
			CreditCard cobj(UsersArr[userIndex]);
			cobj.CreditCardInfoOptions(Log);
			break;
		}
		case 3:
		{
			// For Bank Details functionality 
			break;
		}
		case 4:
		{
			int iRet = Settings(userIndex);
			if (iRet == 1)
			{
				break;
			}
			if (iRet == 2)
			{
				return;
			}
			break;
		}
		case 5:
		{
			return;
		}
		default:
			cout << "Invalid choice. Please try again." << endl;
			break;
		}
	} while (choice != 5);
}
int main()
{

	cout << "\n";
	cout << "                                +--------------------------------------------------+" << endl;
	cout << "                                |                                                  |" << endl;
	cout << "                                |      >>> Virtual Password Vault Manager <<<      |" << endl;
	cout << "                                |                                                  |" << endl;
	cout << "                                +--------------------------------------------------+" << endl;
	cout << "                                |           Secure your passwords safely!          |" << endl;
	cout << "                                +--------------------------------------------------+" << endl;

	PasswordManager pm;
	int choice = 0;
	int MaxAttempt = 0;
	char Log[LOG_SIZE] = ""; // Log buffer

	do
	{
		cout << "\n--- Virtual Password Manager ---\n";
		cout << "1. Register\n2. Login\n3. Exit\n";
		cout << "----------------------------------\n";
		cout << "Enter choice: ";
		cin >> choice;
		cin.ignore();
  
		//GFG reference
		//We can use the cin.fail() method to check if the last input operation was successful or not.
		//This function returns true if the last cin command failed and false otherwise.
		//So, it can be used to validate user input and ensure that it meets certain criteria.

		if (cin.fail())  // Check if the input is valid
		{
			cin.clear();
			cin.ignore(100, '\n');
			cout << "Invalid option. Please enter a number." << endl;
			continue;
		}
		if (choice < 1 || choice > 3)
		{
			cout << "Number out of range. Please enter a number between 1 and 3." << endl;
			continue;
		}

		string username, password;

		switch (choice)
		{
		case 1: // Register
		{
			cout << "Enter username: ";
			getline(cin, username);
			cout << "Enter password: ";
			getline(cin, password);
			int userIndex = 0;
			userIndex = pm.findUserByUserName(username, password);
			if (userIndex >= 0)
			{
				cout << "User Already Exists\n"<< endl;
				char logMessage[LOG_MSG_SIZE];
				sprintf(logMessage, "User Already Exists: %s\n", username.c_str());
				strcat(Log, logMessage);
				break;
			}

			if (pm.registerUser(username, password))
			{
				cout << "User  registered successfully." << endl;

				char logMessage[LOG_MSG_SIZE];
				sprintf(logMessage, "User  registered successfully: %s\n", username.c_str());
				strcat(Log, logMessage);
				MaxAttempt = 0;
			}
			else
			{
				cout << "Registration failed. Maximum users reached or input error." << endl;
				strcat(Log, "Registration failed. Maximum users reached or input error.\n");
			}
			break;
		}

		case 2: // Login
			if (MaxAttempt >= 3)
			{
				cout << "You have reached the maximum attempts. Please wait 20 seconds." << endl;
				pm.waitFor20Seconds();
				MaxAttempt = 0;
				break;
			}

			cout << "Enter username: ";
			getline(cin, username);
			cout << "Enter password: ";
			getline(cin, password);

			if (pm.loginUser(username, password))
			{

				cout << "User  logged in successfully." << endl;
				strcat(Log, "User  logged in successfully.\n");
				int userIndex = pm.findUserByUserName(username, password);

				pm.Functionality(userIndex, Log);
				MaxAttempt = 0;
			}
			else
			{
				MaxAttempt++;
				cout << "Login failed. Incorrect username or password." << endl;
				strcat(Log, "Login failed. Incorrect username or password.\n");
			}
			break;

		case 3: // Exit
			cout << "Exiting the application." << endl;
			exit(0);
			break;

		default:
			cout << "Invalid choice. Please try again." << endl;
			strcat(Log, "Invalid choice. Please try again.\n");
			break;
		}
	} while (choice != 3);

	return 0;
}