#include<Windows.h>
#include<stdio.h>

#define VALUENAMEMAX 2048

/* 函数名 : GetSerialPortsReg
*  说  明 : 通过注册表枚举系统串口数量，并列出所有串口的系统名
*
*  参  数 : pListStr, 串口名称列表
*  返回值 : int, 系统串口个数
*/
int GetSerialPortsReg(wchar_t(*pListStr)[80])
{
	HKEY hKey;
	LPCTSTR data_Set = L"HARDWARE\\DEVICEMAP\\SERIALCOMM\\";
	long ret0 = (::RegOpenKeyEx(HKEY_LOCAL_MACHINE, data_Set, 0, KEY_READ, &hKey));

	if (ret0 != ERROR_SUCCESS)
	{
		return -1;
	}

	int i = 0;
	WCHAR Name[25] = { 0 };
	UCHAR szPortName[80] = { 0 };
	LONG Status;

	DWORD dwIndex = 0;
	DWORD dwName;
	DWORD dwSizeofPortName;
	DWORD Type;

	dwName = sizeof(Name);
	dwSizeofPortName = sizeof(szPortName);

	do
	{
		memset(Name, 0, 25);
		memset(szPortName, 0, sizeof(szPortName));
		dwName = VALUENAMEMAX;
		dwSizeofPortName = VALUENAMEMAX;

		Status = RegEnumValue(hKey, dwIndex++, Name, &dwName, NULL, &Type,
			szPortName, &dwSizeofPortName);
		if (wcscmp(Name, L"Winachsf0") == 0)//过滤掉识别出来的蓝牙设备

			continue;
		if ((Status == ERROR_SUCCESS) || (Status == ERROR_MORE_DATA))
		{
			if (pListStr != NULL)
			{
				memcpy(*(pListStr + i), (LPCSTR)szPortName, 80);
			}
			i++;
		}
	} while ((Status == ERROR_SUCCESS) || (Status == ERROR_MORE_DATA));

	RegCloseKey(hKey);

	return i;
}

int main(int argc,char* argv[]) {

	WCHAR pListStr[80][80];

	printf("\ntestfunc:\t%d\n\n",GetSerialPortsReg(pListStr));

	for (int i = 0; i < 80;i++) {
		wprintf(L"%s\n", pListStr[i]);
	}

	return 0;


}