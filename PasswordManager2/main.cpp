#include "logins.h"
#include "creditcard.h"
#include "backaccount.h"
#include "passport.h"
#include "driverlicence.h"
// #include <regex>
#include <cstdlib>
#include <cctype>
#include <string>

Logins::Logins(UserLoginInfo *UsersArr)
{
    this->UsersArr = UsersArr;
}
bool Logins::searchByLoginName(const string &SearchLoginName)
{
    bool bFlag = 0;
    StoreLoginInfo *temp = UsersArr->ptrUserFunc->ptrStoreLoginInfo;

    while (temp != NULL)
    {
        if (temp->loginName == SearchLoginName)
        {
            bFlag = 1;
            cout << "-------------------------------------" << endl;
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
bool Logins::viewAllUserLoginInfo()
{
    StoreLoginInfo *temp = UsersArr->ptrUserFunc->ptrStoreLoginInfo;
    if (temp == NULL)
    {
        return false;
    }
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
    StoreLoginInfo *current = UsersArr->ptrUserFunc->ptrStoreLoginInfo;
    StoreLoginInfo *prev = NULL;

    while (current != NULL)
    {
        if (current->LoginNo == loginNo)
        {
            if (prev == NULL)
            {
                UsersArr->ptrUserFunc->ptrStoreLoginInfo = current->next;
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

bool Logins::addLoginRecord(string titleName, string loginName, string password, string URL)
{
    if (UsersArr == NULL)
    {
        return false;
    }

    StoreLoginInfo *newRecord = new StoreLoginInfo(titleName, loginName, password, URL);
    if (newRecord == NULL)
    {
        return false;
    }
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
                    if (newTitleName.empty())
                    {
                        cout << "newTitleName should not empty\n"
                             << endl;
                        strcat(Log, "newTitleName should not empty\n");
                        break;
                    }
                    temp->titleName = newTitleName;
                    break;
                }
                case 2:
                {
                    string newLoginName;
                    cout << "Enter New Login Name: ";
                    cin >> newLoginName;
                    if (newLoginName.empty())
                    {
                        cout << "newLoginName should not empty\n"
                             << endl;
                        strcat(Log, "newLoginName should not empty\n");
                        break;
                    }
                    temp->loginName = newLoginName;
                    break;
                }
                case 3:
                {
                    string newPassword;
                    cout << "Enter New Password: ";
                    cin >> newPassword;
                    if (newPassword.empty())
                    {
                        cout << "newPassword should not empty\n"
                             << endl;
                        strcat(Log, "newPassword should not empty\n");
                        break;
                    }
                    temp->password = newPassword;
                    break;
                }
                case 4:
                {
                    string newURL;
                    cout << "Enter New URL: ";
                    cin >> newURL;
                    if (newURL.empty())
                    {
                        cout << "newURL should not empty\n"
                             << endl;
                        strcat(Log, "newURL should not empty\n");
                        break;
                    }
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
        cout << "Enter the Operation\n";
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
            if (titleName.empty())
            {
                cout << "titleName should not empty" << endl;
                strcat(UsersArr->ptrUserFunc->Logs, "titleName should not empty\n");
                break;
            }

            cout << "Enter the login Name: ";
            getline(cin, loginName);
            if (loginName.empty())
            {
                cout << "loginName should not empty" << endl;
                strcat(UsersArr->ptrUserFunc->Logs, "loginName should not empty\n");
                break;
            }

            cout << "Enter password: ";
            getline(cin, password);
            if (password.empty())
            {
                cout << "password should not empty" << endl;
                strcat(UsersArr->ptrUserFunc->Logs, "password should not empty\n");
                break;
            }

            cout << "Enter the site Name or URL: ";
            getline(cin, URL);

            if (URL.empty())
            {
                cout << "URL should not empty" << endl;
                strcat(UsersArr->ptrUserFunc->Logs, "URL should not empty\n");
                break;
            }

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
            bool bRet = viewAllUserLoginInfo();
            if (bRet == false)
            {
                cout << "There is no any record presents in Logins\n";
                strcat(UsersArr->ptrUserFunc->Logs, "There is no any record presents in Logins.\n");
            }
            break;
        }
        case 3:
        {
            strcat(UsersArr->ptrUserFunc->Logs, "Search By Login Name.\n");
            string searchLoginName;
            cin.ignore();
            cout << "Enter the login name to search: ";
            getline(cin, searchLoginName);

            if (searchLoginName.empty())
            {
                cout << "searchLoginName should not empty" << endl;
                strcat(UsersArr->ptrUserFunc->Logs, "searchLoginName should not empty\n");
                break;
            }

            bool found = Logins::searchByLoginName(searchLoginName);

            if (!found)
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
            bool bRet = viewAllUserLoginInfo();

            if (bRet == false)
            {
                cout << "There is no any record presents in Logins\n";
                strcat(UsersArr->ptrUserFunc->Logs, "There is no any record presents in Logins.\n");
                break;
            }
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
            bool bRet = viewAllUserLoginInfo();

            if (bRet == false)
            {
                cout << "There is no any record presents in Logins\n";
                strcat(UsersArr->ptrUserFunc->Logs, "There is no any record presents in Logins.\n");
                break;
            }
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
            strcat(UsersArr->ptrUserFunc->Logs, "Exit From Logins\n");
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
    this->UsersArr = UsersArr;
}

bool CreditCard::viewAllUserCreditCardInfo()
{
    if (UsersArr->ptrUserFunc->ptrStoreCreditCardInfo == NULL)
    {
        return false;
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
                     << "9. Exit\n"
                     << endl;
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
                    if (newTitle.empty())
                    {
                        cout << "newTitle should not empty\n"
                             << endl;
                        strcat(UsersArr->ptrUserFunc->Logs, "newTitle should not empty\n");
                        break;
                    }
                    temp->creditCardTitle = newTitle;
                    cout << "Credit Card Title updated successfully." << endl;
                    break;
                }
                case 2:
                {
                    string newNotes;
                    cout << "Enter New Additional Notes: ";
                    getline(cin, newNotes);
                    if (newNotes.empty())
                    {
                        cout << "newNotes should not empty\n"
                             << endl;
                        strcat(UsersArr->ptrUserFunc->Logs, "newNotes should not empty\n");
                        break;
                    }
                    temp->additionalNotes = newNotes;
                    cout << "Additional Notes updated successfully." << endl;
                    break;
                }
                case 3:
                {
                    string newCardholderName;
                    cout << "Enter New Cardholder Name: ";
                    getline(cin, newCardholderName);
                    if (newCardholderName.empty())
                    {
                        cout << "newCardholderName should not empty\n"
                             << endl;
                        strcat(UsersArr->ptrUserFunc->Logs, "newCardholderName should not empty\n");
                        break;
                    }
                    temp->cardholderName = newCardholderName;
                    cout << "Cardholder Name updated successfully." << endl;
                    break;
                }
                case 4:
                {
                    string newCVV;
                    cout << "Enter New Card CVV: ";
                    getline(cin, newCVV);
                    if (newCVV.empty())
                    {
                        cout << "newCVV should not empty\n"
                             << endl;
                        strcat(UsersArr->ptrUserFunc->Logs, "newCVV should not empty\n");
                        break;
                    }
                    temp->cardCVV = newCVV;
                    cout << "Card CVV updated successfully." << endl;
                    break;
                }
                case 5:
                {
                    string newExpirationDate;
                    cout << "Enter New Card Expiration Date (MM/YY): ";
                    getline(cin, newExpirationDate);
                    if (newExpirationDate.empty())
                    {
                        cout << "newExpirationDate should not empty\n"
                             << endl;
                        strcat(UsersArr->ptrUserFunc->Logs, "newExpirationDate should not empty\n");
                        break;
                    }
                    temp->cardExpirationDate = newExpirationDate;
                    cout << "Card Expiration Date updated successfully." << endl;
                    break;
                }
                case 6:
                {
                    string newBankName;
                    cout << "Enter New Issuing Bank Name: ";
                    getline(cin, newBankName);
                    if (newBankName.empty())
                    {
                        cout << "newBankName should not empty\n"
                             << endl;
                        strcat(UsersArr->ptrUserFunc->Logs, "newBankName should not empty\n");
                        break;
                    }
                    temp->issuingBankName = newBankName;
                    cout << "Issuing Bank Name updated successfully." << endl;
                    break;
                }
                case 7:
                {
                    string newWebsiteURL;
                    cout << "Enter New Bank Website URL: ";
                    getline(cin, newWebsiteURL);
                    if (newWebsiteURL.empty())
                    {
                        cout << "newWebsiteURL should not empty\n"
                             << endl;
                        strcat(UsersArr->ptrUserFunc->Logs, "newWebsiteURL should not empty\n");
                        break;
                    }
                    temp->bankWebsiteURL = newWebsiteURL;
                    cout << "Bank Website URL updated successfully." << endl;
                    break;
                }
                case 8:
                {
                    string newPhoneNumber;
                    cout << "Enter New Bank Customer Service Phone Number: ";
                    getline(cin, newPhoneNumber);
                    if (newPhoneNumber.empty())
                    {
                        cout << "newPhoneNumber should not empty\n"
                             << endl;
                        strcat(UsersArr->ptrUserFunc->Logs, "newPhoneNumber should not empty\n");
                        break;
                    }
                    temp->bankPhoneNumber = newPhoneNumber;
                    cout << "Bank Customer Service Phone Number updated successfully." << endl;
                    break;
                }
                case 9:
                {
                    cout << "Exiting from update menu." << endl;
                    strcat(UsersArr->ptrUserFunc->Logs, "Exiting from update menu.\n");
                    return false;
                }
                default:
                    cout << "Invalid choice. Please try again." << endl;
                    strcat(UsersArr->ptrUserFunc->Logs, "Invalid choice. Please try again.\n");
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
            cout << "-------------------------------------" << endl;
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
int CreditCard::isValidCreditCardNumber(const string &creditCardNumber)
{

    if (creditCardNumber.length() < 13 || creditCardNumber.length() > 19)
    {

        return -1;
    }

    for (int i = 0; i < creditCardNumber.length(); i++)
    {
        if (!isdigit(creditCardNumber[i]))
        {

            return -2;
        }
    }

    return 1;
}
void CreditCard::CreditCardInfoOptions(char *Log)
{
    strcat(UsersArr->ptrUserFunc->Logs, Log);
    Log[0] = '\0';
    int choice = 0;

    do
    {
        cout << "Enter the Operation\n";
        cout << "1. Add Credit Card Info\n2. View All User CreditCard Info\n3. Search By CreditCard Number\n4. Delete By CreditCard No\n5. Update By CreditCard No\n7. Exit\n";
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
            string creditCardTitle, additionalNotes, cardholderName, creditCardNumber, cardCVV, cardExpirationDate, issuingBankName, bankWebsiteURL, bankPhoneNumber;

            cout << "Enter the credit card title: ";
            getline(cin, creditCardTitle);
            if (creditCardTitle.empty())
            {
                cout << "creditCardTitle should not empty" << endl;
                strcat(UsersArr->ptrUserFunc->Logs, "creditCardTitle should not empty\n");
                break;
            }

            cout << "Enter additional notes: ";
            getline(cin, additionalNotes);

            cout << "Enter the cardholder name: ";
            getline(cin, cardholderName);
            if (cardholderName.empty())
            {
                cout << "cardholderName should not empty" << endl;
                strcat(UsersArr->ptrUserFunc->Logs, "cardholderName should not empty\n");
                break;
            }

            cout << "Enter the credit card number: ";
            getline(cin, creditCardNumber);

            if (creditCardNumber.empty())
            {
                cout << "creditCardNumber should not empty" << endl;
                strcat(UsersArr->ptrUserFunc->Logs, "creditCardNumber should not empty\n");
                break;
            }

            while (true)
            {
                cout << "Enter the credit card number: ";
                getline(cin, creditCardNumber);

                int iRet = isValidCreditCardNumber(creditCardNumber);

                if (iRet < 0)
                {
                    if (iRet == -1)
                    {
                        cout << "Credit card number must be between 13 to 19 digits." << endl;
                    }
                    else
                    {
                        cout << "Credit card number must contain only numeric characters." << endl;
                    }
                }
                else
                {
                    break;
                }
            }

            cout << "Enter the card CVV: ";
            getline(cin, cardCVV);
            if (cardCVV.empty())
            {
                cout << "cardCVV should not empty" << endl;
                strcat(UsersArr->ptrUserFunc->Logs, "cardCVV should not empty\n");
                break;
            }

            cout << "Enter the card expiration date (MM/YY): ";
            getline(cin, cardExpirationDate);
            if (cardExpirationDate.empty())
            {
                cout << "cardExpirationDate should not empty" << endl;
                strcat(UsersArr->ptrUserFunc->Logs, "cardExpirationDate should not empty\n");
                break;
            }

            cout << "Enter the issuing bank name: ";
            getline(cin, issuingBankName);
            if (issuingBankName.empty())
            {
                cout << "issuingBankName should not empty" << endl;
                strcat(UsersArr->ptrUserFunc->Logs, "issuingBankName should not empty\n");
                break;
            }

            cout << "Enter the bank website URL: ";
            getline(cin, bankWebsiteURL);
            if (bankWebsiteURL.empty())
            {
                cout << "bankWebsiteURL should not empty" << endl;
                strcat(UsersArr->ptrUserFunc->Logs, "bankWebsiteURL should not empty\n");
                break;
            }

            cout << "Enter the bank customer service phone number: ";
            getline(cin, bankPhoneNumber);
            if (bankPhoneNumber.empty())
            {
                cout << "bankPhoneNumber should not empty" << endl;
                strcat(UsersArr->ptrUserFunc->Logs, "bankPhoneNumber should not empty\n");
                break;
            }

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
            bool bRet = viewAllUserCreditCardInfo();

            if (bRet == false)
            {
                cout << "There is no any record presents in CreditCard\n";
                strcat(UsersArr->ptrUserFunc->Logs, "There is no any record presents in CreditCard\n");
                break;
            }
            break;
        }
        case 3:
        {
            strcat(UsersArr->ptrUserFunc->Logs, "Search By Card Number.\n");
            string searchCardNumber;
            cin.ignore();
            cout << "Enter the Credit Card Number to search: ";
            getline(cin, searchCardNumber);
            if (searchCardNumber.empty())
            {
                cout << "searchCardNumber should not empty" << endl;
                strcat(UsersArr->ptrUserFunc->Logs, "searchCardNumber should not empty\n");
                break;
            }

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
            bool bRet = viewAllUserCreditCardInfo();

            if (bRet == false)
            {
                cout << "There is no any record presents in CreditCard\n";
                strcat(UsersArr->ptrUserFunc->Logs, "There is no any record presents in CreditCard\n");
                break;
            }
            string creditCardNumber;
            cin.ignore();
            cout << "Enter the Credit Card Number to delete: ";

            getline(cin, creditCardNumber);
            if (creditCardNumber.empty())
            {
                cout << "creditCardNumber should not empty" << endl;
                strcat(UsersArr->ptrUserFunc->Logs, "creditCardNumber should not empty\n");
                break;
            }

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
            bool bRet = viewAllUserCreditCardInfo();

            if (bRet == false)
            {
                cout << "There is no any record presents in CreditCard\n";
                strcat(UsersArr->ptrUserFunc->Logs, "There is no any record presents in CreditCard\n");
                break;
            }
            string creditCardNumber;
            cout << "Enter the Credit Card Number to update: ";
            cin.ignore();
            getline(cin, creditCardNumber);
            if (creditCardNumber.empty())
            {
                cout << "creditCardNumber should not empty" << endl;
                strcat(UsersArr->ptrUserFunc->Logs, "creditCardNumber should not empty\n");
                break;
            }
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
            strcat(UsersArr->ptrUserFunc->Logs, "Exit From Credit card\n");
            return;
        default:
            cout << "Invalid choice. Please try again." << endl;
            strcat(UsersArr->ptrUserFunc->Logs, "Invalid choice. Please try again.\n");
            break;
        }
    } while (choice != 6);
}

BankAccount::BankAccount(UserLoginInfo *UsersArr)
{
    this->UsersArr = UsersArr;
}

bool BankAccount::addBankAccountRecord(string accountNumber, string accountHolderName, string bankName, string accountType, double currentBalance, string accountCurrency, string accountPassword, string additionalNotes, string accountLinkMobileNumber)
{
    if (UsersArr == NULL)
    {
        return false;
    }

    StoreBankAccountInfo *newRecord = new StoreBankAccountInfo(accountNumber, accountHolderName, bankName, accountType, currentBalance, accountCurrency, accountPassword, additionalNotes, accountLinkMobileNumber);
    if (newRecord == NULL)
    {
        return false;
    }
    StoreBankAccountInfo *temp = UsersArr->ptrUserFunc->ptrStoreBankAccountInfo;

    if (temp == NULL)
    {
        UsersArr->ptrUserFunc->ptrStoreBankAccountInfo = newRecord;
    }
    else
    {
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newRecord;
    }
    // resetLoginNo();
    return true;
}
bool BankAccount::viewAllUserBankAccountInfo()
{
    if (UsersArr->ptrUserFunc->ptrStoreBankAccountInfo == NULL)
    {
        return false;
    }

    StoreBankAccountInfo *temp = UsersArr->ptrUserFunc->ptrStoreBankAccountInfo;
    cout << "=============================================" << endl;
    while (temp != NULL)
    {

        cout << "Account Number: " << temp->accountNumber << endl;
        cout << "Account Holder Name: " << temp->accountHolderName << endl;
        cout << "Bank Name: " << temp->bankName << endl;
        cout << "Account Type: " << temp->accountType << endl;
        cout << "Current Balance: " << temp->currentBalance << " " << temp->accountCurrency << endl;
        cout << "Account Password: " << temp->accountPassword << endl;
        cout << "Additional Notes: " << temp->additionalNotes << endl;
        cout << "Account Link Mobile Number: " << temp->accountLinkMobileNumber << endl;
        cout << "=============================================" << endl;
        temp = temp->next;
    }
}
bool BankAccount::searchByBankAccountNumber(const string &accountNumber)
{
    if (accountNumber.empty())
    {
        return false;
    }

    StoreBankAccountInfo *temp = UsersArr->ptrUserFunc->ptrStoreBankAccountInfo;
    bool found = false;

    while (temp != NULL)
    {
        if (temp->accountNumber == accountNumber)
        {
            cout << "=============================================" << endl;
            cout << "Account Number: " << temp->accountNumber << endl;
            cout << "Account Holder Name: " << temp->accountHolderName << endl;
            cout << "Bank Name: " << temp->bankName << endl;
            cout << "Account Type: " << temp->accountType << endl;
            cout << "Current Balance: " << temp->currentBalance << " " << temp->accountCurrency << endl;
            cout << "Account Password: " << temp->accountPassword << endl;
            cout << "Additional Notes: " << temp->additionalNotes << endl;
            cout << "Account Link Mobile Number: " << temp->accountLinkMobileNumber << endl;
            cout << "=============================================" << endl;
            found = true;
        }
        temp = temp->next;
    }

    return found;
}
bool BankAccount::deleteByBankAccountNo(const string &accountNumber)
{
    StoreBankAccountInfo *current = UsersArr->ptrUserFunc->ptrStoreBankAccountInfo;
    StoreBankAccountInfo *prev = NULL;

    while (current != NULL)
    {
        if (current->accountNumber == accountNumber)
        {
            if (prev == NULL)
            {
                UsersArr->ptrUserFunc->ptrStoreBankAccountInfo = current->next;
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
bool BankAccount::updateBankAccountRecord(string accountNumber)
{
    StoreBankAccountInfo *temp = UsersArr->ptrUserFunc->ptrStoreBankAccountInfo;
    string newAccountNumber, newAccountHolderName, newBankName, newAccountType, newAccountCurrency, newAccountPassword, newAdditionalNotes, newAccountLinkMobileNumber;
    double newCurrentBalance;

    while (temp != NULL)
    {
        if (temp->accountNumber == accountNumber)
        {
            int choice = 0;
            do
            {
                cout << "Enter what you want to update" << endl;
                cout << "\n1. Account Number\n"
                     << "2. Account Holder Name\n"
                     << "3. Bank Name\n"
                     << "4. Account Type\n"
                     << "5. Account Currency\n"
                     << "6. Current Balance\n"
                     << "7. Account Password/PIN\n"
                     << "8. Additional Notes\n"
                     << "9. Account Link Mobile Number\n"
                     << "10. Exit\n"
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

                if (choice < 1 || choice > 10)
                {
                    cout << "Number out of range. Please enter a number between 1 and 10." << endl;
                    continue;
                }

                switch (choice)
                {
                case 1:
                {

                    while (true)
                    {
                        cout << "Enter the new account number: ";
                        getline(cin, newAccountNumber);
                        if (newBankName.empty())
                        {
                            cout << "newBankName should not empty\n"
                                 << endl;
                            strcat(UsersArr->ptrUserFunc->Logs, "newBankName should not empty\n");
                            break;
                        }
                        int iRet = isValidAccountNumber(newAccountNumber);

                        if (iRet < 0)
                        {
                            if (iRet == -1)
                            {
                                cout << "Account number cannot be empty." << endl;
                            }
                            else if (iRet == -2)
                            {

                                cout << "Account number must be in digit." << endl;
                            }
                            else
                            {
                                cout << "Account number must be 12 digit number." << endl;
                            }
                        }
                        else
                        {
                            break;
                        }
                    }
                    temp->accountNumber = newAccountNumber;
                    cout << "Account number updated successfully." << endl;
                    break;
                }
                case 2:
                {
                    cout << "Enter New account holder name: ";
                    getline(cin, newAccountHolderName);
                    if (newAccountHolderName.empty())
                    {
                        cout << "newAccountHolderName should not empty" << endl;
                        strcat(UsersArr->ptrUserFunc->Logs, "newAccountHolderName should not empty\n");
                        break;
                    }
                    temp->accountHolderName = newAccountHolderName;
                    cout << "Account holder name updated successfully." << endl;
                    break;
                }
                case 3:
                {
                    cout << "Enter New bank name: ";
                    getline(cin, newBankName);
                    if (newBankName.empty())
                    {
                        cout << "newBankName should not empty" << endl;
                        strcat(UsersArr->ptrUserFunc->Logs, "newBankName should not empty\n");
                        break;
                    }
                    temp->bankName = newBankName;
                    cout << "Bank name updated successfully." << endl;
                    break;
                }
                case 4:
                {
                    cout << "Enter the new account type: ";
                    getline(cin, newAccountType);
                    if (newAccountType.empty())
                    {
                        cout << "newAccountType should not empty" << endl;
                        strcat(UsersArr->ptrUserFunc->Logs, "newAccountType should not empty\n");
                        break;
                    }
                    temp->accountType = newAccountType;
                    cout << "Account type updated successfully." << endl;
                    break;
                }
                case 5:
                {
                    cout << "Enter New account currency: ";
                    getline(cin, newAccountCurrency);
                    if (newAccountCurrency.empty())
                    {
                        cout << "newAccountCurrency should not empty" << endl;
                        strcat(UsersArr->ptrUserFunc->Logs, "newAccountCurrency should not empty\n");
                        break;
                    }
                    temp->accountCurrency = newAccountCurrency;
                    cout << "Account currency updated successfully." << endl;
                    break;
                }
                case 6:
                {
                    cout << "Enter the new current balance: ";
                    cin >> newCurrentBalance;

                    temp->currentBalance = newCurrentBalance;
                    cout << "Current balance updated successfully." << endl;
                    break;
                }
                case 7:
                {
                    cout << "Enter the new account password/PIN: ";
                    getline(cin, newAccountPassword);
                    if (newAccountPassword.empty())
                    {
                        cout << "newAccountPassword should not empty" << endl;
                        strcat(UsersArr->ptrUserFunc->Logs, "newAccountPassword should not empty\n");
                        break;
                    }
                    temp->accountPassword = newAccountPassword;
                    cout << "Account password updated successfully." << endl;
                    break;
                }
                case 8:
                {
                    cout << "Enter new additional notes: ";
                    getline(cin, newAdditionalNotes);
                    if (newAdditionalNotes.empty())
                    {
                        cout << "newAdditionalNotes should not empty" << endl;
                        strcat(UsersArr->ptrUserFunc->Logs, "newAdditionalNotes should not empty\n");
                        break;
                    }
                    temp->additionalNotes = newAdditionalNotes;
                    cout << "Additional notes updated successfully." << endl;
                    break;
                }
                case 9:
                {
                    cout << "Enter new account link mobile number: ";
                    getline(cin, newAccountLinkMobileNumber);
                    if (newAccountLinkMobileNumber.empty())
                    {
                        cout << "newAccountLinkMobileNumber should not empty" << endl;
                        strcat(UsersArr->ptrUserFunc->Logs, "newAccountLinkMobileNumber should not empty\n");
                        break;
                    }
                    temp->accountLinkMobileNumber = newAccountLinkMobileNumber;
                    cout << "Account link mobile number updated successfully." << endl;
                    break;
                }
                case 10:
                {
                    return false;
                }
                default:
                    cout << "Invalid choice. Please try again." << endl;
                    strcat(UsersArr->ptrUserFunc->Logs, "Invalid choice. Please try again.\n");
                    break;
                }
            } while (choice != 10);
            return true;
        }
        temp = temp->next;
    }
    cout << "Account with number " << accountNumber << " not found." << endl;
    char logMessage[LOG_MSG_SIZE];
    sprintf(logMessage, "Account with number %s not found.\n", accountNumber.c_str());
    strcat(UsersArr->ptrUserFunc->Logs, logMessage);

    return false;
}

int BankAccount::isValidAccountNumber(const string &accountNumber)
{
    if (accountNumber.empty())
    {
        return -1;
    }

    for (int i = 0; i < accountNumber.length(); i++)
    {
        if (isdigit(accountNumber[i]))
        {
            return -2;
        }
    }
    if (accountNumber.length() > 9 && accountNumber.length() < 17)
    {
        return -3;
    }
    return 1;
}
void BankAccount::BankAccountInfoOptions(char *Log)
{
    strcat(UsersArr->ptrUserFunc->Logs, Log);
    Log[0] = '\0';
    int choice = 0;

    do
    {
        cout << "Enter the Operation\n";
        cout << "1. Add BankAccount Info\n2. View All User BankAccount Info\n3. Search By BankAccountNumber\n4. Delete By BankAccountNumber\n5. Update By BankAccountNumber\n7. Exit\n";
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
        cin.ignore();
        string accountNumber, accountHolderName, bankName, accountType, accountCurrency, accountPassword, additionalNotes, accountLinkMobileNumber;
        double currentBalance;
        switch (choice)
        {

        case 1:
        {

            while (true)
            {
                cout << "Enter the accountNumber: ";
                getline(cin, accountNumber);
                if (accountNumber.empty())
                {
                    cout << "accountNumber should not empty" << endl;
                    strcat(UsersArr->ptrUserFunc->Logs, "accountNumber should not empty\n");
                    break;
                }

                int iRet = isValidAccountNumber(accountNumber);

                if (iRet < 0)
                {
                    if (iRet == -1)
                    {
                        cout << "Account number cannot be empty." << endl;
                    }
                    else if (iRet == -2)
                    {

                        cout << "Account number must be in digit." << endl;
                    }
                    else
                    {
                        cout << "Account number must be between 10 to 16 digits." << endl;
                    }
                }
                else
                {
                    break;
                }
            }
            cout << "Enter the accountHolderName: ";
            getline(cin, accountHolderName);

            if (accountHolderName.empty())
            {
                cout << "accountHolderName should not empty" << endl;
                strcat(UsersArr->ptrUserFunc->Logs, "accountHolderName should not empty\n");
                break;
            }

            cout << "Enter the bank name: ";
            getline(cin, bankName);
            if (bankName.empty())
            {
                cout << "bankName should not empty" << endl;
                strcat(UsersArr->ptrUserFunc->Logs, "bankName should not empty\n");
                break;
            }

            cout << "Enter the account type: ";
            getline(cin, accountType);
            if (accountType.empty())
            {
                cout << "accountType should not empty" << endl;
                strcat(UsersArr->ptrUserFunc->Logs, "accountType should not empty\n");
                break;
            }

            cout << "Enter the currentBalance: ";
            cin >> currentBalance;

            cout << "Enter the account Currency: ";
            getline(cin, accountCurrency);
            if (accountCurrency.empty())
            {
                cout << "accountCurrency should not empty" << endl;
                strcat(UsersArr->ptrUserFunc->Logs, "accountCurrency should not empty\n");
                break;
            }

            cout << "Enter the accountPassword/PIN: ";
            getline(cin, accountPassword);
            if (accountPassword.empty())
            {
                cout << "accountPassword should not empty" << endl;
                strcat(UsersArr->ptrUserFunc->Logs, "accountPassword should not empty\n");
                break;
            }

            cout << "Enter additional notes: ";
            getline(cin, additionalNotes);

            cout << "Enter accountLinkMobileNumber: ";
            getline(cin, accountLinkMobileNumber);
            if (accountLinkMobileNumber.empty())
            {
                cout << "accountLinkMobileNumber should not empty" << endl;
                strcat(UsersArr->ptrUserFunc->Logs, "accountLinkMobileNumber should not empty\n");
                break;
            }

            if (addBankAccountRecord(accountNumber, accountHolderName, bankName, accountType, currentBalance, accountCurrency, accountPassword, additionalNotes, accountLinkMobileNumber))
            {
                cout << "New record inserted successfully into BankAccountInfo." << endl;
                char logMessage[LOG_MSG_SIZE];
                sprintf(logMessage, "New record inserted successfully into BankAccountInfo for %s\n", accountHolderName.c_str());
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
            strcat(UsersArr->ptrUserFunc->Logs, "View All User BankAccount Info.\n");
            bool bRet = viewAllUserBankAccountInfo();

            if (bRet == false)
            {
                cout << "There is no any record presents in BackAccount\n";
                strcat(UsersArr->ptrUserFunc->Logs, "There is no any record presents in BackAccount\n");
                break;
            }
            break;
        }
        case 3:
        {
            strcat(UsersArr->ptrUserFunc->Logs, "Search By BankAccountNumber.\n");
            string accountNumber;
            cin.ignore();
            cout << "Enter the BankAccountNumber to search: ";
            getline(cin, accountNumber);
            if (accountNumber.empty())
            {
                cout << "accountNumber should not empty" << endl;
                strcat(UsersArr->ptrUserFunc->Logs, "accountNumber should not empty\n");
                break;
            }

            bool found = searchByBankAccountNumber(accountNumber);

            if (!found)
            {
                cout << "There is no such Bank Account present." << endl;
                strcat(UsersArr->ptrUserFunc->Logs, "There is no such Bank Account present.\n");
            }
            else
            {
                char logMessage[LOG_MSG_SIZE];
                sprintf(logMessage, "Found Bank Account with number %s\n", accountNumber.c_str());
                strcat(UsersArr->ptrUserFunc->Logs, logMessage);
            }
            break;
        }
        case 4:
        {
            bool bRet = viewAllUserBankAccountInfo();

            if (bRet == false)
            {
                cout << "There is no any record presents in BackAccount\n";
                strcat(UsersArr->ptrUserFunc->Logs, "There is no any record presents in BackAccount\n");
                break;
            }
            string accountNumber;
            cin.ignore();
            cout << "Enter the BankAccountNumber to delete: ";
            getline(cin, accountNumber);
            if (accountNumber.empty())
            {
                cout << "accountNumber should not empty" << endl;
                strcat(UsersArr->ptrUserFunc->Logs, "accountNumber should not empty\n");
                break;
            }
            bool deleted = deleteByBankAccountNo(accountNumber);

            if (deleted)
            {
                cout << "Deleted the Bank Account with number " << accountNumber << endl;
                char logMessage[LOG_MSG_SIZE];
                sprintf(logMessage, "Deleted the Bank Account with number %s\n", accountNumber.c_str());
                strcat(UsersArr->ptrUserFunc->Logs, logMessage);
            }
            else
            {
                cout << "Failed to delete the BankAccount." << endl;
                strcat(UsersArr->ptrUserFunc->Logs, "Failed to delete the Bank Account.\n");
            }
            break;
        }
        case 5:
        {
            bool bRet = viewAllUserBankAccountInfo();

            if (bRet == false)
            {
                cout << "There is no any record presents in BackAccount\n";
                strcat(UsersArr->ptrUserFunc->Logs, "There is no any record presents in BackAccount\n");
                break;
            }
            string accountNumber;
            cin.ignore();
            cout << "Enter the BankAccountNumber to update: ";
            getline(cin, accountNumber);
            if (accountNumber.empty())
            {
                cout << "accountNumber should not empty" << endl;
                strcat(UsersArr->ptrUserFunc->Logs, "accountNumber should not empty\n");
                break;
            }
            bool updated = updateBankAccountRecord(accountNumber);

            if (updated)
            {
                char logMessage[LOG_MSG_SIZE];
                sprintf(logMessage, "Updated the Bank Account with number %s\n", accountNumber.c_str());
                strcat(UsersArr->ptrUserFunc->Logs, logMessage);
            }
            else
            {
                cout << "Failed to update the Bank Account." << endl;
                strcat(UsersArr->ptrUserFunc->Logs, "Failed to update the Bank Account.\n");
            }
            break;
        }
        case 6:
            strcat(UsersArr->ptrUserFunc->Logs, "Exit from Bank Account\n");
            return;
        default:
            cout << "Invalid choice. Please try again." << endl;
            strcat(UsersArr->ptrUserFunc->Logs, "Invalid choice. Please try again.\n");
            break;
        }
    } while (choice != 6);
}

Passport::Passport(UserLoginInfo *UsersArr)
{
    this->UsersArr = UsersArr;
}
bool Passport::addPassportRecord(string fullName, string passportNumber, string nationality, string birthDate, string birthPlace, string issueDate, string expirationDate, string issuingAuthority)
{
    if (UsersArr == NULL)
    {
        return false;
    }

    StorePassportInfo *newRecord = new StorePassportInfo(fullName, passportNumber, nationality, birthDate, birthPlace, issueDate, expirationDate, issuingAuthority);
    if (newRecord == NULL)
    {
        return false;
    }

    if (newRecord == NULL)
    {
        return false;
    }
    StorePassportInfo *temp = UsersArr->ptrUserFunc->ptrStorePassportInfo;

    if (temp == NULL)
    {
        UsersArr->ptrUserFunc->ptrStorePassportInfo = newRecord;
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
bool Passport::searchByPassportNumber(const string &passportNumber)
{
    if (passportNumber.empty())
    {
        return false;
    }

    StorePassportInfo *temp = UsersArr->ptrUserFunc->ptrStorePassportInfo;
    bool found = false;

    while (temp != NULL)
    {
        if (temp->passportNumber == passportNumber)
        {
            cout << "=============================================" << endl;
            cout << "Full Name: " << temp->fullName << endl;
            cout << "Passport Number: " << temp->passportNumber << endl;
            cout << "Nationality: " << temp->nationality << endl;
            cout << "Birth Date: " << temp->birthDate << endl;
            cout << "Birth Place: " << temp->birthPlace << endl;
            cout << "Issue Date: " << temp->issueDate << endl;
            cout << "Expiration Date: " << temp->expirationDate << endl;
            cout << "Issuing Authority: " << temp->issuingAuthority << endl;
            cout << "=============================================" << endl;
            found = true;
        }
        temp = temp->next;
    }

    return found;
}
bool Passport::deleteByPassportNumber(const string &passportNumber)
{
    StorePassportInfo *current = UsersArr->ptrUserFunc->ptrStorePassportInfo;
    StorePassportInfo *prev = NULL;

    while (current != NULL)
    {
        if (current->passportNumber == passportNumber)
        {
            if (prev == NULL)
            {
                UsersArr->ptrUserFunc->ptrStorePassportInfo = current->next;
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
bool Passport::updatePassportRecord(string passportNumber)
{
    StorePassportInfo *temp = UsersArr->ptrUserFunc->ptrStorePassportInfo;
    string newFullName, newPassportNumber, newNationality, newBirthDate, newBirthPlace, newIssuingAuthority;
    string newIssueDate, newExpirationDate;
    char newGender;

    while (temp != NULL)
    {
        if (temp->passportNumber == passportNumber)
        {
            int choice = 0;
            do
            {
                // Display the update options to the user.
                cout << "Enter what you want to update" << endl;
                cout << "\n1. Full Name\n"
                     << "2. Passport Number\n"
                     << "3. Nationality\n"
                     << "4. Birth Date (YYYY-MM-DD)\n"
                     << "5. Birth Place\n"
                     << "6. Issue Date (YYYY-MM-DD)\n"
                     << "7. Expiration Date (YYYY-MM-DD)\n"
                     << "8. Issuing Authority\n"
                     << "9. Exit\n"
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

                if (choice < 1 || choice > 9)
                {
                    cout << "Number out of range. Please enter a number between 1 and 9." << endl;
                    continue;
                }

                switch (choice)
                {
                case 1:
                    cout << "Enter the new full name: ";
                    getline(cin, newFullName);
                    if (newFullName.empty())
                    {
                        cout << "newFullName should not empty" << endl;
                        strcat(UsersArr->ptrUserFunc->Logs, "newFullName should not empty\n");
                        break;
                    }
                    temp->fullName = newFullName;
                    cout << "Full name updated successfully." << endl;
                    break;
                case 2:

                    while (true)
                    {
                        cout << "Enter the new passport number: ";
                        getline(cin, newPassportNumber);
                        if (newPassportNumber.empty())
                        {
                            cout << "newPassportNumber should not empty" << endl;
                            strcat(UsersArr->ptrUserFunc->Logs, "newPassportNumber should not empty\n");
                            break;
                        }
                        int iRet = isValidPassportNumber(newPassportNumber);

                        if (iRet < 0)
                        {
                            if (iRet == -1)
                            {
                                cout << "Passport number cannot be empty." << endl;
                            }
                            else if (iRet == -2)
                            {

                                cout << "Passport number can only contain alphanumeric characters." << endl;
                            }
                            else
                            {
                                cout << "Passport number must be between 6 and 9 characters long." << endl;
                            }
                            continue;
                        }
                        else
                        {
                            break;
                        }
                    }
                    temp->passportNumber = newPassportNumber;
                    cout << "Passport number updated successfully." << endl;
                    break;
                case 3:
                    cout << "Enter new nationality: ";
                    getline(cin, newNationality);
                    if (newNationality.empty())
                    {
                        cout << "newNationality should not empty" << endl;
                        strcat(UsersArr->ptrUserFunc->Logs, "newNationality should not empty\n");
                        break;
                    }
                    temp->nationality = newNationality;
                    cout << "Nationality updated successfully." << endl;
                    break;
                case 4:
                    cout << "Enter the new birth date (format: YYYY-MM-DD): ";
                    getline(cin, newBirthDate);
                    if (newBirthDate.empty())
                    {
                        cout << "newBirthDate should not empty" << endl;
                        strcat(UsersArr->ptrUserFunc->Logs, "newBirthDate should not empty\n");
                        break;
                    }
                    temp->birthDate = newBirthDate;
                    cout << "Birth date updated successfully." << endl;
                    break;
                case 5:
                    cout << "Enter the new birth place: ";
                    getline(cin, newBirthPlace);
                    if (newBirthPlace.empty())
                    {
                        cout << "newBirthPlace should not empty" << endl;
                        strcat(UsersArr->ptrUserFunc->Logs, "newBirthPlace should not empty\n");
                        break;
                    }
                    temp->birthPlace = newBirthPlace;
                    cout << "Birth place updated successfully." << endl;
                    break;
                case 6:
                    cout << "Enter the new issue date (format: YYYY-MM-DD): ";
                    getline(cin, newIssueDate);
                    if (newIssueDate.empty())
                    {
                        cout << "newIssueDate should not empty" << endl;
                        strcat(UsersArr->ptrUserFunc->Logs, "newIssueDate should not empty\n");
                        break;
                    }
                    temp->issueDate = newIssueDate;
                    cout << "Issue date updated successfully." << endl;
                    break;
                case 7:
                    cout << "Enter the new expiration date (format: YYYY-MM-DD): ";
                    getline(cin, newExpirationDate);
                    if (newExpirationDate.empty())
                    {
                        cout << "newExpirationDate should not empty" << endl;
                        strcat(UsersArr->ptrUserFunc->Logs, "newExpirationDate should not empty\n");
                        break;
                    }
                    temp->expirationDate = newExpirationDate;
                    cout << "Expiration date updated successfully." << endl;
                    break;
                case 8:
                    cout << "Enter the new issuing authority: ";
                    getline(cin, newIssuingAuthority);
                    if (newIssuingAuthority.empty())
                    {
                        cout << "newIssuingAuthority should not empty" << endl;
                        strcat(UsersArr->ptrUserFunc->Logs, "newIssuingAuthority should not empty\n");
                        break;
                    }
                    temp->issuingAuthority = newIssuingAuthority;
                    cout << "Issuing authority updated successfully." << endl;
                    break;
                case 9:
                    return false;
                default:
                    cout << "Invalid choice. Please try again." << endl;
                    strcat(UsersArr->ptrUserFunc->Logs, "Invalid choice. Please try again.\n");
                    break;
                }
            } while (choice != 9);

            return true;
        }
        temp = temp->next;
    }

    cout << "Passport with number " << passportNumber << " not found." << endl;
    char logMessage[LOG_MSG_SIZE];
    sprintf(logMessage, "Passport with number %s not found.\n", passportNumber.c_str());
    strcat(UsersArr->ptrUserFunc->Logs, logMessage);

    return false;
}
bool Passport::viewAllUserPassportInfo()
{
    if (UsersArr->ptrUserFunc->ptrStorePassportInfo == NULL)
    {
        return false;
    }

    StorePassportInfo *temp = UsersArr->ptrUserFunc->ptrStorePassportInfo;
    cout << "=============================================" << endl;
    while (temp != NULL)
    {
        cout << "Full Name: " << temp->fullName << endl;
        cout << "Passport Number: " << temp->passportNumber << endl;
        cout << "Nationality: " << temp->nationality << endl;
        cout << "Birth Date: " << temp->birthDate << endl;
        cout << "Birth Place: " << temp->birthPlace << endl;
        cout << "Issue Date: " << temp->issueDate << endl;
        cout << "Expiration Date: " << temp->expirationDate << endl;
        cout << "Issuing Authority: " << temp->issuingAuthority << endl;
        cout << "=============================================" << endl;
        temp = temp->next;
    }
}
int Passport::isValidPassportNumber(const string &passportNumber)
{

    if (passportNumber.empty())
    {
        return -1;
    }

    for (int i = 0; i < passportNumber.length(); i++)
    {
        if (!isalnum(passportNumber[i]))
        {
            return -2;
        }
    }
    if (passportNumber.length() < 6 || passportNumber.length() > 9)
    {
        return -3;
    }

    return 1;
}
void Passport::PassportInfoOptions(char *Log)
{
    strcat(UsersArr->ptrUserFunc->Logs, Log);
    Log[0] = '\0';
    int choice = 0;

    do
    {
        cout << "Enter the Operation\n";
        cout << "1. Add Passport Info\n2. View All User Passport Info\n3. Search By Passport Number\n4. Delete By Passport Number\n5. Update By Passport Number\n6. Exit\n";
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

            string fullName, passportNumber, nationality, birthDate, birthPlace, issuingAuthority, issueDate, expirationDate;

            cout << "Enter the full name: ";
            getline(cin, fullName);

            while (true)
            {
                cout << "Enter the passport number: ";
                getline(cin, passportNumber);
                if (passportNumber.empty())
                {
                    cout << "passportNumber should not empty" << endl;
                    strcat(UsersArr->ptrUserFunc->Logs, "passportNumber should not empty\n");
                    break;
                }
                int iRet = isValidPassportNumber(passportNumber);

                if (iRet < 0)
                {
                    if (iRet == -1)
                    {
                        cout << "Passport number cannot be empty." << endl;
                    }
                    else if (iRet == -2)
                    {

                        cout << "Passport number can only contain alphanumeric characters." << endl;
                    }
                    else
                    {
                        cout << "Passport number must be between 6 and 9 characters long." << endl;
                    }
                    continue;
                }
                else
                {
                    break;
                }
            }

            cout << "Enter the nationality: ";
            getline(cin, nationality);
            if (nationality.empty())
            {
                cout << "nationality should not empty" << endl;
                strcat(UsersArr->ptrUserFunc->Logs, "nationality should not empty\n");
                break;
            }
            cout << "Enter the birth date (YYYY-MM-DD): ";
            getline(cin, birthDate);
            if (birthDate.empty())
            {
                cout << "birthDate should not empty" << endl;
                strcat(UsersArr->ptrUserFunc->Logs, "birthDate should not empty\n");
                break;
            }
            cout << "Enter the birth place: ";
            getline(cin, birthPlace);
            if (birthPlace.empty())
            {
                cout << "birthPlace should not empty" << endl;
                strcat(UsersArr->ptrUserFunc->Logs, "birthPlace should not empty\n");
                break;
            }
            cout << "Enter the issue date (YYYY-MM-DD): ";
            getline(cin, issueDate);
            if (issueDate.empty())
            {
                cout << "issueDate should not empty" << endl;
                strcat(UsersArr->ptrUserFunc->Logs, "issueDate should not empty\n");
                break;
            }
            cout << "Enter the expiration date (YYYY-MM-DD): ";
            getline(cin, expirationDate);
            if (expirationDate.empty())
            {
                cout << "expirationDate should not empty" << endl;
                strcat(UsersArr->ptrUserFunc->Logs, "expirationDate should not empty\n");
                break;
            }
            cout << "Enter the issuing authority: ";
            getline(cin, issuingAuthority);
            if (issuingAuthority.empty())
            {
                cout << "issuingAuthority should not empty" << endl;
                strcat(UsersArr->ptrUserFunc->Logs, "issuingAuthority should not empty\n");
                break;
            }
            if (addPassportRecord(fullName, passportNumber, nationality, birthDate, birthPlace, issueDate, expirationDate, issuingAuthority))
            {
                cout << "New record inserted successfully into Passport Info." << endl;
                char logMessage[LOG_MSG_SIZE];
                sprintf(logMessage, "New record inserted successfully into Passport Info for %s\n", fullName.c_str());
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
            strcat(UsersArr->ptrUserFunc->Logs, "View All User Passport Info.\n");

            bool bRet = viewAllUserPassportInfo();

            if (bRet == false)
            {
                cout << "There is no any record presents in Passport\n";
                strcat(UsersArr->ptrUserFunc->Logs, "There is no any record presents in Passport\n");
                break;
            }
            break;
        }
        case 3:
        {
            strcat(UsersArr->ptrUserFunc->Logs, "Search By Passport Number.\n");
            string passportNumber;
            cin.ignore();
            cout << "Enter the Passport Number to search: ";
            getline(cin, passportNumber);
            if (passportNumber.empty())
            {
                cout << "passportNumber should not empty" << endl;
                strcat(UsersArr->ptrUserFunc->Logs, "passportNumber should not empty\n");
                break;
            }
            bool found = searchByPassportNumber(passportNumber);

            if (!found)
            {
                cout << "There is no such Passport present." << endl;
                strcat(UsersArr->ptrUserFunc->Logs, "There is no such Passport present.\n");
            }
            else
            {
                char logMessage[LOG_MSG_SIZE];
                sprintf(logMessage, "Found Passport with number %s\n", passportNumber.c_str());
                strcat(UsersArr->ptrUserFunc->Logs, logMessage);
            }
            break;
        }
        case 4:
        {
            bool bRet = viewAllUserPassportInfo();

            if (bRet == false)
            {
                cout << "There is no any record presents in Passport\n";
                strcat(UsersArr->ptrUserFunc->Logs, "There is no any record presents in Passport\n");
                break;
            }
            string passportNumber;
            cin.ignore();
            cout << "Enter the Passport Number to delete: ";
            getline(cin, passportNumber);
            if (passportNumber.empty())
            {
                cout << "passportNumber should not empty" << endl;
                strcat(UsersArr->ptrUserFunc->Logs, "passportNumber should not empty\n");
                break;
            }
            bool deleted = deleteByPassportNumber(passportNumber);

            if (deleted)
            {
                cout << "Deleted the Passport with number " << passportNumber << endl;
                char logMessage[LOG_MSG_SIZE];
                sprintf(logMessage, "Deleted the Passport with number %s\n", passportNumber.c_str());
                strcat(UsersArr->ptrUserFunc->Logs, logMessage);
            }
            else
            {
                cout << "Failed to delete the Passport." << endl;
                strcat(UsersArr->ptrUserFunc->Logs, "Failed to delete the Passport.\n");
            }
            break;
        }
        case 5:
        {
            bool bRet = viewAllUserPassportInfo();

            if (bRet == false)
            {
                cout << "There is no any record presents in Passport\n";
                strcat(UsersArr->ptrUserFunc->Logs, "There is no any record presents in Passport\n");
                break;
            }
            string passportNumber;
            cin.ignore();
            cout << "Enter the Passport Number to update: ";
            getline(cin, passportNumber);
            if (passportNumber.empty())
            {
                cout << "passportNumber should not empty" << endl;
                strcat(UsersArr->ptrUserFunc->Logs, "passportNumber should not empty\n");
                break;
            }
            bool updated = updatePassportRecord(passportNumber);

            if (updated)
            {
                char logMessage[LOG_MSG_SIZE];
                sprintf(logMessage, "Updated the Passport with number %s\n", passportNumber.c_str());
                strcat(UsersArr->ptrUserFunc->Logs, logMessage);
            }
            else
            {
                cout << "Failed to update the Passport." << endl;
                strcat(UsersArr->ptrUserFunc->Logs, "Failed to update the Passport.\n");
            }
            break;
        }
       
        case 6:

            strcat(UsersArr->ptrUserFunc->Logs, "Exit from Passport Management\n");
            return;
        default:
            cout << "Invalid choice. Please try again." << endl;
            strcat(UsersArr->ptrUserFunc->Logs, "Invalid choice. Please try again.\n");
            break;
        }
    } while (choice != 6);
}
DriverLicence::DriverLicence(UserLoginInfo *UsersArr)
{
    this->UsersArr = UsersArr;
}
bool DriverLicence::addLicenseRecord(string driverFullName, string licenseNumber, string driverAddress, string driverDateOfBirth, string driverGender, string driverState, string driverCountry, string licenseIssueDate, string licenseExpDate, string additionalNotes)
{
    if (UsersArr == NULL)
    {
        return false;
    }

    StoreDriverLicenseInfo *newRecord = new StoreDriverLicenseInfo(driverFullName, licenseNumber, driverAddress, driverDateOfBirth, driverGender, driverState, driverCountry, licenseIssueDate, licenseExpDate, additionalNotes);
    if (newRecord == NULL)
    {
        return false;
    }

    StoreDriverLicenseInfo *temp = UsersArr->ptrUserFunc->ptrStoreDriverLicenseInfo;

    if (temp == NULL)
    {
        UsersArr->ptrUserFunc->ptrStoreDriverLicenseInfo = newRecord;
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
bool DriverLicence::searchByLicenseNumber(const string &licenseNumber)
{
    if (licenseNumber.empty())
    {
        return false;
    }

    StoreDriverLicenseInfo *temp = UsersArr->ptrUserFunc->ptrStoreDriverLicenseInfo;
    bool found = false;

    while (temp != NULL)
    {
        if (temp->licenseNumber == licenseNumber)
        {
            found = true;
            cout << "-------------------------------------" << endl;
            cout << "Driver Full Name: " << temp->driverFullName << endl;
            cout << "License Number: " << temp->licenseNumber << endl;
            cout << "Address: " << temp->driverAddress << endl;
            cout << "Date of Birth: " << temp->driverDateOfBirth << endl;
            cout << "Gender: " << temp->driverGender << endl;
            cout << "State: " << temp->driverState << endl;
            cout << "Country: " << temp->driverCountry << endl;
            cout << "Issue Date: " << temp->licenseIssueDate << endl;
            cout << "Expiration Date: " << temp->licenseExpDate << endl;
            cout << "Additional Notes: " << temp->additionalNotes << endl;
            cout << "-------------------------------------" << endl;
        }
        temp = temp->next;
    }

    return found;
}
bool DriverLicence::deleteByLicenseNumber(string licenseNumber)
{
    StoreDriverLicenseInfo *current = UsersArr->ptrUserFunc->ptrStoreDriverLicenseInfo;
    StoreDriverLicenseInfo *prev = NULL;

    while (current != NULL)
    {
        if (current->licenseNumber == licenseNumber)
        {
            if (prev == NULL)
            {
                UsersArr->ptrUserFunc->ptrStoreDriverLicenseInfo = current->next;
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
bool DriverLicence::updateLicenseRecord(const string &licenseNumber)
{
    StoreDriverLicenseInfo *temp = UsersArr->ptrUserFunc->ptrStoreDriverLicenseInfo;

    while (temp != NULL)
    {
        if (temp->licenseNumber == licenseNumber)
        {
            int choice = 0;
            do
            {
                cout << "Enter what you want to update" << endl;
                cout << "\n1. Driver Full Name\n"
                     << "2. Address\n"
                     << "3. Date of Birth\n"
                     << "4. Gender\n"
                     << "5. State\n"
                     << "6. Country\n"
                     << "7. Issue Date\n"
                     << "8. Expiration Date\n"
                     << "9. Additional Notes\n"
                     << "10. Exit\n"
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

                if (choice < 1 || choice > 10)
                {
                    cout << "Number out of range. Please enter a number between 1 and 10." << endl;
                    continue;
                }

                switch (choice)
                {
                case 1:
                {
                    string newFullName;
                    cout << "Enter New Driver Full Name: ";
                    getline(cin, newFullName);
                    if (newFullName.empty())
                    {
                        cout << "newFullName should not empty" << endl;
                        strcat(UsersArr->ptrUserFunc->Logs, "newFullName should not empty\n");
                        break;
                    }
                    temp->driverFullName = newFullName;
                    cout << "Driver Full Name updated successfully." << endl;
                    break;
                }
                case 2:
                {
                    string newAddress;
                    cout << "Enter New Address: ";
                    getline(cin, newAddress);
                    if (newAddress.empty())
                    {
                        cout << "newAddress should not empty" << endl;
                        strcat(UsersArr->ptrUserFunc->Logs, "newAddress should not empty\n");
                        break;
                    }
                    temp->driverAddress = newAddress;
                    cout << "Address updated successfully." << endl;
                    break;
                }
                case 3:
                {
                    string newDOB;
                    cout << "Enter New Date of Birth (YYYY-MM-DD): ";
                    getline(cin, newDOB);
                    if (newDOB.empty())
                    {
                        cout << "newDOB should not empty" << endl;
                        strcat(UsersArr->ptrUserFunc->Logs, "newDOB should not empty\n");
                        break;
                    }
                    temp->driverDateOfBirth = newDOB;
                    cout << "Date of Birth updated successfully." << endl;
                    break;
                }
                case 4:
                {
                    string newGender;
                    cout << "Enter New Gender: ";
                    getline(cin, newGender);
                    if (newGender.empty())
                    {
                        cout << "newGender should not empty" << endl;
                        strcat(UsersArr->ptrUserFunc->Logs, "newGender should not empty\n");
                        break;
                    }
                    temp->driverGender = newGender;
                    cout << "Gender updated successfully." << endl;
                    break;
                }
                case 5:
                {
                    string newState;
                    cout << "Enter New State: ";
                    getline(cin, newState);
                    if (newState.empty())
                    {
                        cout << "newState should not empty" << endl;
                        strcat(UsersArr->ptrUserFunc->Logs, "newState should not empty\n");
                        break;
                    }
                    temp->driverState = newState;
                    cout << "State updated successfully." << endl;
                    break;
                }
                case 6:
                {
                    string newCountry;
                    cout << "Enter New Country: ";
                    getline(cin, newCountry);
                    if (newCountry.empty())
                    {
                        cout << "newCountry should not empty" << endl;
                        strcat(UsersArr->ptrUserFunc->Logs, "newCountry should not empty\n");
                        break;
                    }
                    temp->driverCountry = newCountry;
                    cout << "Country updated successfully." << endl;
                    break;
                }
                case 7:
                {
                    string newIssueDate;
                    cout << "Enter New Issue Date (YYYY-MM-DD): ";
                    getline(cin, newIssueDate);
                    if (newIssueDate.empty())
                    {
                        cout << "newIssueDate should not empty" << endl;
                        strcat(UsersArr->ptrUserFunc->Logs, "newIssueDate should not empty\n");
                        break;
                    }
                    temp->licenseIssueDate = newIssueDate;
                    cout << "Issue Date updated successfully." << endl;
                    break;
                }
                case 8:
                {
                    string newExpirationDate;
                    cout << "Enter New Expiration Date (YYYY-MM-DD): ";
                    getline(cin, newExpirationDate);
                    if (newExpirationDate.empty())
                    {
                        cout << "newExpirationDate should not empty" << endl;
                        strcat(UsersArr->ptrUserFunc->Logs, "newExpirationDate should not empty\n");
                        break;
                    }
                    temp->licenseExpDate = newExpirationDate;
                    cout << "Expiration Date updated successfully." << endl;
                    break;
                }
                case 9:
                {
                    string newNotes;
                    cout << "Enter New Additional Notes: ";
                    getline(cin, newNotes);
                    if (newNotes.empty())
                    {
                        cout << "newNotes should not empty" << endl;
                        strcat(UsersArr->ptrUserFunc->Logs, "newNotes should not empty\n");
                        break;
                    }
                    temp->additionalNotes = newNotes;
                    cout << "Additional Notes updated successfully." << endl;
                    break;
                }
                case 10:
                {
                    cout << "Exiting update menu." << endl;
                    return false;
                }
                default:
                    cout << "Invalid choice. Please try again." << endl;
                    break;
                }
            } while (choice != 10);
            return true;
        }
        temp = temp->next;
    }
    cout << "License with number " << licenseNumber << " not found." << endl;
    char logMessage[LOG_MSG_SIZE];
    sprintf(logMessage, "License with number %s not found.\n", licenseNumber.c_str());
    strcat(UsersArr->ptrUserFunc->Logs, logMessage);
    return false;
}
bool DriverLicence::viewAllUserLicenseInfo()
{
    StoreDriverLicenseInfo *temp = UsersArr->ptrUserFunc->ptrStoreDriverLicenseInfo;

    if (temp == NULL)
    {
        return false;
    }
    cout << "=============================================" << endl;
    while (temp != NULL)
    {
        cout << "Driver Full Name: " << temp->driverFullName << endl;
        cout << "License Number: " << temp->licenseNumber << endl;
        cout << "Address: " << temp->driverAddress << endl;
        cout << "Date of Birth: " << temp->driverDateOfBirth << endl;
        cout << "Gender: " << temp->driverGender << endl;
        cout << "State: " << temp->driverState << endl;
        cout << "Country: " << temp->driverCountry << endl;
        cout << "Issue Date: " << temp->licenseIssueDate << endl;
        cout << "Expiration Date: " << temp->licenseExpDate << endl;
        cout << "Additional Notes: " << temp->additionalNotes << endl;
        cout << "=============================================" << endl;
        temp = temp->next;
    }
    return true;
}

int DriverLicence::isValidLicenseNumber(const string &licenseNumber)
{
    if (licenseNumber.length() < 8 || licenseNumber.length() > 15)
    {
        return -1;
    }

    for (int i = 0; i < licenseNumber.length(); i++)
    {
        if (!isalnum(licenseNumber[i]))
        {
            return -2;
        }
    }
    return 1;
}
void DriverLicence::LicenseInfoOptions(char *Log)
{
    strcat(UsersArr->ptrUserFunc->Logs, Log);
    Log[0] = '\0';
    int choice = 0;

    do
    {
        cout << "Enter the Operation\n";
        cout << "1. Add License Info\n2. View All User License Info\n3. Search By License Number\n4. Delete By License Number\n5. Update By License Number\n6. Exit\n";
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

            string driverFullName, licenseNumber, driverAddress, driverDateOfBirth, driverGender, driverState, driverCountry, licenseIssueDate, licenseExpDate, additionalNotes;

            cout << "Enter the full name: ";
            getline(cin, driverFullName);

            if (driverFullName.empty())
            {
                cout << "driverFullName should not empty" << endl;
                strcat(UsersArr->ptrUserFunc->Logs, "driverFullName should not empty\n");
                break;
            }

            while (true)
            {
                cout << "Enter the license number: ";
                getline(cin, licenseNumber);
                int iRet = isValidLicenseNumber(licenseNumber);

                if (iRet < 0)
                {
                    if (iRet == -1)
                    {
                        cout << "Invalid license number: Length must be between 8 and 15 characters." << endl;
                    }
                    else if (iRet == -2)
                    {
                        cout << "Invalid license number: Only alphanumeric characters are allowed." << endl;
                    }
                    continue;
                }
                else
                {
                    break;
                }
            }

            cout << "Enter the address: ";
            getline(cin, driverAddress);
            if (driverAddress.empty())
            {
                cout << "driverAddress should not empty" << endl;
                strcat(UsersArr->ptrUserFunc->Logs, "driverAddress should not empty\n");
                break;
            }

            cout << "Enter the birth date (YYYY-MM-DD): ";
            getline(cin, driverDateOfBirth);
            if (driverDateOfBirth.empty())
            {
                cout << "driverDateOfBirth should not empty" << endl;
                strcat(UsersArr->ptrUserFunc->Logs, "driverDateOfBirth should not empty\n");
                break;
            }

            cout << "Enter the gender: ";
            getline(cin, driverGender);
            if (driverGender.empty())
            {
                cout << "driverGender should not empty" << endl;
                strcat(UsersArr->ptrUserFunc->Logs, "driverGender should not empty\n");
                break;
            }

            cout << "Enter the state: ";
            getline(cin, driverState);
            if (driverState.empty())
            {
                cout << "driverState should not empty" << endl;
                strcat(UsersArr->ptrUserFunc->Logs, "driverState should not empty\n");
                break;
            }
            cout << "Enter the country: ";
            getline(cin, driverCountry);
            if (driverCountry.empty())
            {
                cout << "driverCountry should not empty" << endl;
                strcat(UsersArr->ptrUserFunc->Logs, "driverCountry should not empty\n");
                break;
            }
            cout << "Enter the issue date (YYYY-MM-DD): ";
            getline(cin, licenseIssueDate);
            if (licenseIssueDate.empty())
            {
                cout << "licenseIssueDate should not empty" << endl;
                strcat(UsersArr->ptrUserFunc->Logs, "licenseIssueDate should not empty\n");
                break;
            }
            cout << "Enter the expiration date (YYYY-MM-DD): ";
            getline(cin, licenseExpDate);
            if (licenseExpDate.empty())
            {
                cout << "licenseExpDate should not empty" << endl;
                strcat(UsersArr->ptrUserFunc->Logs, "licenseExpDate should not empty\n");
                break;
            }
            cout << "Enter any additional notes: ";
            getline(cin, additionalNotes);

            if (addLicenseRecord(driverFullName, licenseNumber, driverAddress, driverDateOfBirth, driverGender, driverState, driverCountry, licenseIssueDate, licenseExpDate, additionalNotes))
            {
                cout << "New record inserted successfully into License Info." << endl;
                char logMessage[LOG_MSG_SIZE];
                sprintf(logMessage, "New record inserted successfully into License Info for %s\n", driverFullName.c_str());
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
            strcat(UsersArr->ptrUserFunc->Logs, "View All User License Info.\n");
            bool bRet = viewAllUserLicenseInfo();

            if (!bRet)
            {
                cout << "There are no records present in License Info.\n";
                strcat(UsersArr->ptrUserFunc->Logs, "There are no records present in License Info.\n");
                break;
            }
            break;
        }
        case 3:
        {
            strcat(UsersArr->ptrUserFunc->Logs, "Search By License Number.\n");
            string licenseNumber;
            cin.ignore();
            cout << "Enter the License Number to search: ";
            getline(cin, licenseNumber);
            if (licenseNumber.empty())
            {
                cout << "licenseNumber should not empty" << endl;
                strcat(UsersArr->ptrUserFunc->Logs, "licenseNumber should not empty\n");
                break;
            }
            bool found = searchByLicenseNumber(licenseNumber);

            if (!found)
            {
                cout << "There is no such License present." << endl;
                strcat(UsersArr->ptrUserFunc->Logs, "There is no such License present.\n");
            }
            else
            {
                char logMessage[LOG_MSG_SIZE];
                sprintf(logMessage, "Found License with number %s\n", licenseNumber.c_str());
                strcat(UsersArr->ptrUserFunc->Logs, logMessage);
            }
            break;
        }
        case 4:
        {
            bool bRet = viewAllUserLicenseInfo();

            if (!bRet)
            {
                cout << "There are no records present in License Info.\n";
                strcat(UsersArr->ptrUserFunc->Logs, "There are no records present in License Info.\n");
                break;
            }
            string licenseNumber;
            cin.ignore();
            cout << "Enter the License Number to delete: ";
            getline(cin, licenseNumber);
            if (licenseNumber.empty())
            {
                cout << "licenseNumber should not empty" << endl;
                strcat(UsersArr->ptrUserFunc->Logs, "licenseNumber should not empty\n");
                break;
            }
            bool deleted = deleteByLicenseNumber(licenseNumber);

            if (deleted)
            {
                cout << "Deleted the License with number " << licenseNumber << endl;
                char logMessage[LOG_MSG_SIZE];
                sprintf(logMessage, "Deleted the License with number %s\n", licenseNumber.c_str());
                strcat(UsersArr->ptrUserFunc->Logs, logMessage);
            }
            else
            {
                cout << "Failed to delete the License." << endl;
                strcat(UsersArr->ptrUserFunc->Logs, "Failed to delete the License.\n");
            }
            break;
        }
        case 5:
        {
            bool bRet = viewAllUserLicenseInfo();

            if (!bRet)
            {
                cout << "There are no records present in License Info.\n";
                strcat(UsersArr->ptrUserFunc->Logs, "There are no records present in License Info.\n");
                break;
            }
            string licenseNumber;
            cin.ignore();
            cout << "Enter the License Number to update: ";
            getline(cin, licenseNumber);
            if (licenseNumber.empty())
            {
                cout << "licenseNumber should not empty" << endl;
                strcat(UsersArr->ptrUserFunc->Logs, "licenseNumber should not empty\n");
                break;
            }
            bool updated = updateLicenseRecord(licenseNumber);

            if (updated)
            {
                char logMessage[LOG_MSG_SIZE];
                sprintf(logMessage, "Updated the License with number %s\n", licenseNumber.c_str());
                strcat(UsersArr->ptrUserFunc->Logs, logMessage);
            }
            else
            {
                cout << "Failed to update the License." << endl;
                strcat(UsersArr->ptrUserFunc->Logs, "Failed to update the License.\n");
            }
            break;
        }
        case 6:
            strcat(UsersArr->ptrUserFunc->Logs, "Exit from License Management\n");
            return;
        default:
            cout << "Invalid choice. Please try again." << endl;
            strcat(UsersArr->ptrUserFunc->Logs, "Invalid choice. Please try again.\n");
            break;
        }
    } while (choice != 6);
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
            {
                return false;
            }
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

    if (UsersArr[userIndex]->password != oldPassword)
    {
        cout << "Enter the valid Current Password" << endl;
        return false;
    }

    cout << "Enter your new password: ";
    getline(cin, newPassword);
    if (newPassword.empty())
    {
        cout << "newPassword should not empty" << endl;
        strcat(UsersArr[userIndex]->ptrUserFunc->Logs, "newPassword should not empty\n");
        return false;
    }
    if (!isStrongPassword(newPassword))
    {
        cout << "Password is weak. Please choose a stronger password." << endl;
        strcat(UsersArr[userIndex]->ptrUserFunc->Logs, "Password is weak. Please choose a stronger password.\n");
        return false;
    }

    cout << "Re-enter your new password to confirm: ";
    getline(cin, confirmPassword);
    if (confirmPassword.empty())
    {
        cout << "confirmPassword should not empty" << endl;
        strcat(UsersArr[userIndex]->ptrUserFunc->Logs, "confirmPassword should not empty\n");
        return false;
    }
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
        superBlock.freeInode++;
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
            if (iRet == 1)
            {
                cout << "Account deleted successfully." << endl;
                return 2;
            }
            else if (iRet == -2)
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
void PasswordManager::ShowLogMain(const int userIndex,char *Log)

{
    strcat(UsersArr[userIndex]->ptrUserFunc->Logs, Log);
    Log[0] = '\0';
    cout << "==============================================" << endl;
    cout << UsersArr[userIndex]->ptrUserFunc->Logs << endl;
    cout << "==============================================" << endl;
}
bool PasswordManager::isStrongPassword(const string password)
{
    if (password.length() < 8)
    {
        return false;
    }

    bool hasUpper = false;
    bool hasLower = false;
    bool hasDigit = false;
    bool hasSpecial = false;

    string specialChars = "!@#$%";

    for (size_t i = 0; i < password.length(); ++i)
    {
        char ch = password[i];
        if (isupper(ch))
        {
            hasUpper = true;
        }
        else if (islower(ch))
        {
            hasLower = true;
        }
        else if (isdigit(ch))
        {
            hasDigit = true;
        }
        else if (specialChars.find(ch) != string::npos)
        {
            hasSpecial = true;
        }
    }

    return hasUpper && hasLower && hasDigit && hasSpecial;
}
void PasswordManager::Functionality(const int userIndex, char *Log)
{
    int choice = 0;
    cout << "-------------------------------------" << endl;
    cout << "Enter the Functionality" << endl;

    do
    {
        cout << "1. Logins\n2. Credit Card\n3. Bank Details\n4. Passport\n5. DriverLicenses\n6. Settings\n7. Show Log\n8. Logout\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(100, '\n');
            cout << "Invalid option. Please enter a number." << endl;
            continue;
        }

        if (choice < 1 || choice > 8)
        {
            cout << "Number out of range. Please enter a number between 1 and 8." << endl;
            continue;
        }

        switch (choice)
        {
        case 1:
            strcat(Log, "Login Functionality\n");
            {
                Logins logins(UsersArr[userIndex]);
                logins.loginInfoOptions(Log);
            }
            break;
        case 2:
            strcat(Log, "Credit Card Functionality\n");
            {
                CreditCard cobj(UsersArr[userIndex]);
                cobj.CreditCardInfoOptions(Log);
            }
            break;
        case 3:
            strcat(Log, "Bank Account Functionality\n");
            {
                BankAccount bobj(UsersArr[userIndex]);
                bobj.BankAccountInfoOptions(Log);
            }
            break;
        case 4:
            strcat(Log, "Passport Functionality\n");
            {
                Passport pobj(UsersArr[userIndex]);
                pobj.PassportInfoOptions(Log);
            }
            break;

        case 5:
            strcat(Log, "Driver License Functionality\n");
            {
                DriverLicence dobj(UsersArr[userIndex]);
                dobj.LicenseInfoOptions(Log);
            }
            break;
        case 6:
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
        }
        break;
        case 7:
               ShowLogMain(userIndex,Log);
               break;
        case 8:
            return;
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
    } while (true);
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

        // GFG reference
        // We can use the cin.fail() method to check if the last input operation was successful or not.
        // This function returns true if the last cin command failed and false otherwise.
        // So, it can be used to validate user input and ensure that it meets certain criteria.

        if (cin.fail()) // Check if the input is valid
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

            if (username.empty() || password.empty())
            {
                cout << "UserName or Password should not empty\n"
                     << endl;
                strcat(Log, "UserName or Password should not empty\n");
                break;
            }
            int userIndex = 0;

            if (!pm.isStrongPassword(password))
            {
                cout << "Password is weak. Please choose a stronger password." << endl;
                strcat(Log, "Password is weak. Please choose a stronger password.\n");
                continue;
            }
            userIndex = pm.findUserByUserName(username, password);
            if (userIndex >= 0)
            {
                cout << "User Already Exists\n"
                     << endl;
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
        {
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

            if (username.empty() || password.empty())
            {
                cout << "UserName or Password should not empty\n"
                     << endl;
                strcat(Log, "UserName or Password should not empty\n");
                break;
            }

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
        }
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
