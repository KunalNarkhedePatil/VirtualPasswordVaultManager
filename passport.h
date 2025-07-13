#pragma once
#include "passwordmanager.h"

class Passport
{
private:
    UserLoginInfo* UsersArr;
public:
    Passport(UserLoginInfo* UsersArr);
    bool searchByPassportNumber(const string &passportNumber);
    bool viewAllUserPassportInfo();
    bool deleteByPassportNumber(const string &passportNumber);
    bool addPassportRecord(string fullName, string passportNumber, string nationality, 
                           string birthDate, string birthPlace, 
                           string issueDate, string expirationDate, 
                           string issuingAuthority);
   bool updatePassportRecord(string passportNumber);
   int isValidPassportNumber(const string& passportNumber);
   void showLog();
   void PassportInfoOptions(char * Log);
};