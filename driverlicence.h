#pragma once
#include "passwordmanager.h"
#include <string>

using namespace std; 

class DriverLicence
{
private:
    UserLoginInfo* UsersArr;
public:
    DriverLicence(UserLoginInfo* UsersArr);
    bool searchByLicenseNumber(const string &licenseNumber);
    bool viewAllUserLicenseInfo();
    bool deleteByLicenseNumber(string licenseNumber);
    bool addLicenseRecord(string driverFullName,string licenseNumber, string driverAddress,string driverDateOfBirth,string driverGender, string driverState, string driverCountry,string licenseIssueDate,string licenseExpDate,string additionalNotes);
    bool updateLicenseRecord(const string &licenseNumber);
    void showLog();
    void LicenseInfoOptions(char *log);
    int isValidLicenseNumber(const string &licenseNumber);
};