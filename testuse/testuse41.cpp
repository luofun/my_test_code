///testuse41
#include<afx.h>
#include<windows.h>

using namespace std;

void MyGetDisplayCardInfo(DWORD &dwNum, CString chCardName[]);

void main() {
	DWORD x;
	CString xxx[20];
	CString temp;
	wchar_t* buf;
	int len = 0;
	int pos = 0;
	wchar_t a = ';';
	MyGetDisplayCardInfo(x, xxx);
	for (int i = 0; i < x; i++)
	{
		pos = xxx[i].FindOneOf(&a);
		xxx[i].Delete(0, pos + 1);
		temp.Append(xxx[i]);
		temp.AppendChar('\n');
	}
	temp.Delete(temp.GetLength() - 1, 1);
	temp.AppendChar('\0');
	len = temp.GetLength();
	buf = (wchar_t*)malloc(len * sizeof(wchar_t));
	memset(buf, 0, len * sizeof(wchar_t));
	wcscpy(buf, temp);
	MessageBox(NULL, buf, L"PCI Info", MB_OK);
	free(buf);
}


void MyGetDisplayCardInfo(DWORD &dwNum, CString chCardName[])
{
	HKEY keyPCI;
	HKEY keytemp;
	HKEY key;
	LONG lResult;
	int i = 0, count = 0;
	DWORD size = 0, type = 0;
	dwNum = 0;

	//查询"SYSTEM\\CurrentControlSet\\Enum\\PCI"下的所有子键保存到keyPCI  
	lResult = RegOpenKeyEx(HKEY_LOCAL_MACHINE, TEXT("SYSTEM\\CurrentControlSet\\Enum\\PCI"), 0, KEY_READ, &keyPCI);
	if (ERROR_SUCCESS != lResult)
		return;

	for (;; ++i)
	{
		Sleep(5);
		size = 512;
		TCHAR name1[512] = { 0 };//保存keyPCI下各子项的字段名称  

								//逐个枚举keyPCI下的各子项字段保存到name1中 
		//lResult= RegOpenKeyEx(HKEY_LOCAL_MACHINE, TEXT("SYSTEM\\CurrentControlSet\\Enum\\PCI"), 0, KEY_READ, &keyPCI);
		lResult = RegEnumKeyEx(keyPCI, i, name1, &size, NULL, NULL, NULL, NULL);

		//要读取的子项不存在，即keyPCI的子项全部遍历完时跳出循环  
		if (lResult == ERROR_NO_MORE_ITEMS)
			break;

		//根据名字打开子项的子项
		lResult = RegOpenKeyEx(keyPCI, name1, 0, KEY_READ, &keytemp);
		if (ERROR_SUCCESS != lResult)
			return;

		//获取孙子项的key
		lResult = RegEnumKeyEx(keytemp, 0, name1, &size, NULL, NULL, NULL, NULL);
		if (lResult == ERROR_NO_MORE_ITEMS)
			break;

		//打开keyServ的子项字段为name1所标识的字段的值保存到key  
		lResult = RegOpenKeyEx(keytemp, name1, 0, KEY_READ, &key);
		if (lResult != ERROR_SUCCESS)
		{
			RegCloseKey(keyPCI);
			RegCloseKey(keytemp);
			return;
		}

		size = 512;
		//查询key下的字段为Class的子键字段名保存到name1  
		lResult = RegQueryValueEx(key, TEXT("Class"), 0, &type, (LPBYTE)name1, &size);
		if (lResult == ERROR_FILE_NOT_FOUND)
		{
			//键不存在  
			RegCloseKey(key);
			continue;
		};

		//如果查询到的name1不是Net则说明该键不是网卡驱动项 （改成Display可查显卡，System查其他）
		if (_tcscmp(TEXT("Display"), name1) != 0)
		{
			RegCloseKey(key);
			continue;     //返回for循环  
		};

		//如果程序继续往下执行的话说明已经查到了有关网卡的信息  
						
		size = 512;

		lResult = RegQueryValueEx(key, TEXT("DeviceDesc"), 0, &type, (LPBYTE)name1, &size);
		if (lResult == ERROR_FILE_NOT_FOUND)
		{
			RegCloseKey(key);
			continue;
		};
		chCardName[count] = name1;//保存网卡名称
		count++;
		dwNum = count;
	}

}
///end