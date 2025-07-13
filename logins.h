#pragma once
#include "passwordmanager.h"
class Logins
{
private:
	    UserLoginInfo* UsersArr;
public:
	    Logins(UserLoginInfo* UsersArr);
		bool searchByLoginName(const string &SearchLoginName);
		void resetLoginNo();
		bool viewAllUserLoginInfo();
		bool deleteByLoginNo(int loginNo);
		bool addLoginRecord(string titleName,string loginName,string password,string URL);
		void updateLoginRecord(int loginNo);
		void showLog();
		void loginInfoOptions(char * Log);
};