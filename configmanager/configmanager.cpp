#include "configmanager.hpp"

void CConfigManager::GetValue(string szSection, string szKey, string* Value, string szPath) {
	TCHAR KeyValue[32];
	GetPrivateProfileString(szSection.c_str(), szKey.c_str(), "", KeyValue, 32, szPath.c_str());

	string szKeyValue = KeyValue;

	*Value = szKeyValue;
}

void CConfigManager::GetValue(string szSection, string szKey, double* Value, string szPath) {
	TCHAR KeyValue[32];
	GetPrivateProfileString(szSection.c_str(), szKey.c_str(), "", KeyValue, 32, szPath.c_str());

	string szKeyValue = KeyValue;

	double nKeyValue = atof(szKeyValue.c_str());

	*Value = nKeyValue;
}

void CConfigManager::GetValue(string szSection, string szKey, int* Value, string szPath) {
	TCHAR KeyValue[32];
	GetPrivateProfileString(szSection.c_str(), szKey.c_str(), "", KeyValue, 32, szPath.c_str());

	string szKeyValue = KeyValue;

	int nKeyValue = atoi(szKeyValue.c_str());

	*Value = nKeyValue;
}

void CConfigManager::GetValue(string szSection, string szKey, float* Value, string szPath) {
	TCHAR KeyValue[32];
	GetPrivateProfileString(szSection.c_str(), szKey.c_str(), "", KeyValue, 32, szPath.c_str());

	string szKeyValue = KeyValue;

	float nKeyValue = (float)atof(szKeyValue.c_str());

	*Value = nKeyValue;
}

void CConfigManager::GetValue(string szSection, string szKey, bool* Value, string szPath) {
	TCHAR KeyValue[32];
	GetPrivateProfileString(szSection.c_str(), szKey.c_str(), "", KeyValue, 32, szPath.c_str());

	string szKeyValue = KeyValue;

	bool bKeyValue = StringToBool(szKeyValue);

	*Value = bKeyValue;
}

void CConfigManager::PushValue(string szSection, string szKey, string Value, string szPath) {
	WritePrivateProfileString(szSection.c_str(), szKey.c_str(), Value.c_str(), szPath.c_str());
}

void CConfigManager::PushValue(string szSection, string szKey, double* Value, string szPath) {
	string szKeyValue = to_string(*Value);

	WritePrivateProfileString(szSection.c_str(), szKey.c_str(), szKeyValue.c_str(), szPath.c_str());
}

void CConfigManager::PushValue(string szSection, string szKey, int* Value, string szPath) {
	string szKeyValue = to_string(*Value);

	WritePrivateProfileString(szSection.c_str(), szKey.c_str(), szKeyValue.c_str(), szPath.c_str());
}

void CConfigManager::PushValue(string szSection, string szKey, float* Value, string szPath) {
	string szKeyValue = to_string(*Value);

	WritePrivateProfileString(szSection.c_str(), szKey.c_str(), szKeyValue.c_str(), szPath.c_str());
}

void CConfigManager::PushValue(string szSection, string szKey, bool* Value, string szPath) {
	string szKeyValue = BoolToString(*Value);

	WritePrivateProfileString(szSection.c_str(), szKey.c_str(), szKeyValue.c_str(), szPath.c_str());
}

void CConfigManager::MakeValue(string szSection, string szKey, string Value, string szPath, bool bIsSave) {
	if (!bIsSave)
		GetValue(szSection, szKey, &Value, szPath);
	else
		PushValue(szSection, szKey, Value, szPath);
}

void CConfigManager::MakeValue(string szSection, string szKey, double* Value, string szPath, bool bIsSave) {
	if (!bIsSave)
		GetValue(szSection, szKey, Value, szPath);
	else
		PushValue(szSection, szKey, Value, szPath);
}

void CConfigManager::MakeValue(string szSection, string szKey, int* Value, string szPath, bool bIsSave) {
	if (!bIsSave)
		GetValue(szSection, szKey, Value, szPath);
	else
		PushValue(szSection, szKey, Value, szPath);
}

void CConfigManager::MakeValue(string szSection, string szKey, float* Value, string szPath, bool bIsSave) {
	if (!bIsSave)
		GetValue(szSection, szKey, Value, szPath);
	else
		PushValue(szSection, szKey, Value, szPath);
}

void CConfigManager::MakeValue(string szSection, string szKey, bool* Value, string szPath, bool bIsSave) {
	if (!bIsSave)
		GetValue(szSection, szKey, Value, szPath);
	else
		PushValue(szSection, szKey, Value, szPath);
}

string CConfigManager::BoolToString(bool value)
{
	return value ? "true" : "false";
}

bool CConfigManager::StringToBool(string value)
{
	return (value == "true") ? true : false;
}

CConfigManager* configmanager;