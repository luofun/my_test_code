#include<stdio.h>
#include<Windows.h>
//#include<wchar.h>

void main() {
	
	//WCHAR *test;
	//test = GetEnvironmentStrings();
	
	//wprintf(L"%s\n",test);

	LPWCH lpEnvString = GetEnvironmentStringsW();
	LPWSTR lpszVariable = (LPWSTR)lpEnvString;
	while (*lpszVariable)
	{
		wprintf(L"%s\n", lpszVariable);
		lpszVariable += wcslen(lpszVariable) + 1;
	}
	FreeEnvironmentStringsW(lpEnvString);

	

}