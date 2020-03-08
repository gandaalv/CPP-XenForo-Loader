#include <string>
#include <Windows.h>

using namespace std;

class CConfigManager
{
public:
	void GetValue(string szSection, string szKey, string* Value, string szPath);
	void GetValue(string szSection, string szKey, double* Value, string szPath);
	void GetValue(string szSection, string szKey, int* Value, string szPath);
	void GetValue(string szSection, string szKey, float* Value, string szPath);
	void GetValue(string szSection, string szKey, bool* Value, string szPath);

	void PushValue(string szSection, string szKey, string Value, string szPath);
	void PushValue(string szSection, string szKey, double* Value, string szPath);
	void PushValue(string szSection, string szKey, int* Value, string szPath);
	void PushValue(string szSection, string szKey, float* Value, string szPath);
	void PushValue(string szSection, string szKey, bool* Value, string szPath);

	void MakeValue(string szSection, string szKey, string Value, string szPath, bool bIsSave);
	void MakeValue(string szSection, string szKey, double* Value, string szPath, bool bIsSave);
	void MakeValue(string szSection, string szKey, int* Value, string szPath, bool bIsSave);
	void MakeValue(string szSection, string szKey, float* Value, string szPath, bool bIsSave);
	void MakeValue(string szSection, string szKey, bool* Value, string szPath, bool bIsSave);
private:
	string BoolToString(bool value);
	bool StringToBool(string value);
};

extern CConfigManager* configmanager;