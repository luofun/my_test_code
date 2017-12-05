///testuse39
//#include<afx.h>
//#define _AFXDLL
#include <afxtempl.h> 
#include <atlbase.h>  
#include "float.h"  
#include "winperf.h" 
#include <iostream>  
#include <string>  

using namespace std;

void GetDisplayCardInfo(DWORD &dwNum, CString chCardName[]);


void main()
{
	DWORD x;
	CString xxx[20];
	GetDisplayCardInfo(x, xxx);
	getchar();
}

void GetDisplayCardInfo(DWORD &dwNum, CString chCardName[])
{
	HKEY keyServ;
	HKEY keyEnum;
	HKEY key;
	HKEY key2;
	LONG lResult;//LONG型变量－保存函数返回值  

				 //查询"SYSTEM\\CurrentControlSet\\Services"下的所有子键保存到keyServ  
	lResult = RegOpenKeyEx(HKEY_LOCAL_MACHINE, TEXT("SYSTEM\\CurrentControlSet\\Services"), 0, KEY_READ, &keyServ);
	if (ERROR_SUCCESS != lResult)
		return;


	//查询"SYSTEM\\CurrentControlSet\\Enum"下的所有子键保存到keyEnum  
	lResult = RegOpenKeyEx(HKEY_LOCAL_MACHINE, TEXT("SYSTEM\\CurrentControlSet\\Enum"), 0, KEY_READ, &keyEnum);
	if (ERROR_SUCCESS != lResult)
		return;

	int i = 0, count = 0;
	DWORD size = 0, type = 0;
	for (;; ++i)
	{
		Sleep(5);
		size = 512;
		TCHAR name[512] = { 0 };//保存keyServ下各子项的字段名称  

								//逐个枚举keyServ下的各子项字段保存到name中  
		lResult = RegEnumKeyEx(keyServ, i, name, &size, NULL, NULL, NULL, NULL);

		//要读取的子项不存在，即keyServ的子项全部遍历完时跳出循环  
		if (lResult == ERROR_NO_MORE_ITEMS)
			break;

		//打开keyServ的子项字段为name所标识的字段的值保存到key  
		lResult = RegOpenKeyEx(keyServ, name, 0, KEY_READ, &key);
		if (lResult != ERROR_SUCCESS)
		{
			RegCloseKey(keyServ);
			return;
		}


		size = 512;
		//查询key下的字段为Group的子键字段名保存到name  
		lResult = RegQueryValueEx(key, TEXT("Group"), 0, &type, (LPBYTE)name, &size);
		if (lResult == ERROR_FILE_NOT_FOUND)
		{
			//?键不存在  
			RegCloseKey(key);
			continue;
		};



		//如果查询到的name不是Video则说明该键不是显卡驱动项  
		if (_tcscmp(TEXT("Video"), name) != 0)
		{
			RegCloseKey(key);
			continue;     //返回for循环  
		};

		//如果程序继续往下执行的话说明已经查到了有关显卡的信息，所以在下面的代码执行完之后要break第一个for循环，函数返回  
		lResult = RegOpenKeyEx(key, TEXT("Enum"), 0, KEY_READ, &key2);
		RegCloseKey(key);
		key = key2;
		size = sizeof(count);
		lResult = RegQueryValueEx(key, TEXT("Count"), 0, &type, (LPBYTE)&count, &size);//查询Count字段（显卡数目）  

		dwNum = count;//保存显卡数目  
		for (int j = 0; j <count; ++j)
		{
			TCHAR sz[512] = { 0 };
			TCHAR name[64] = { 0 };
			wsprintf(name, TEXT("%d"), j);
			size = sizeof(sz);
			lResult = RegQueryValueEx(key, name, 0, &type, (LPBYTE)sz, &size);


			lResult = RegOpenKeyEx(keyEnum, sz, 0, KEY_READ, &key2);
			if (ERROR_SUCCESS)
			{
				RegCloseKey(keyEnum);
				return;
			}


			size = sizeof(sz);
			lResult = RegQueryValueEx(key2, TEXT("FriendlyName"), 0, &type, (LPBYTE)sz, &size);
			if (lResult == ERROR_FILE_NOT_FOUND)
			{
				size = sizeof(sz);
				lResult = RegQueryValueEx(key2, TEXT("DeviceDesc"), 0, &type, (LPBYTE)sz, &size);
				chCardName[j] = sz;//保存显卡名称  
			};
			RegCloseKey(key2);
			key2 = NULL;
		};
		RegCloseKey(key);
		key = NULL;
		break;
	}
}
///end