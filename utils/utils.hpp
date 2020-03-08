#include <string>
#include <Windows.h>
#include <ShlObj_core.h>
#include <fstream>

#include "../configmanager/configmanager.hpp"

using namespace std;

class CUtils
{
public:
	string GetAppData();
	bool dirExists(const string& dirName);
	void StoreLogin(string username, string password, string file);
};

extern CUtils* utils;