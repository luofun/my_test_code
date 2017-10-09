#include <windows.h> 
#include <stdio.h>
#include <setupapi.h>
#include <devguid.h>
#include <regstr.h>
#include <shlwapi.h>
//#include <wchar.h>

#pragma comment(lib, "setupapi.lib")

#define BUFSIZE    1024
#define SM_SERVERR    289

int main()
{
	HDEVINFO hDevInfo;
	SP_DEVINFO_DATA DeviceInfoData;
	DWORD i;

	hDevInfo = SetupDiGetClassDevs((LPGUID)&GUID_DEVCLASS_PORTS, 0, 0, DIGCF_PRESENT);
	/*
	GUID_DEVCLASS_FDC���̿�����
	GUID_DEVCLASS_DISPLAY��ʾ��
	GUID_DEVCLASS_CDROM����
	GUID_DEVCLASS_KEYBOARD����
	GUID_DEVCLASS_COMPUTER�����
	GUID_DEVCLASS_SYSTEMϵͳ
	GUID_DEVCLASS_DISKDRIVE����������
	GUID_DEVCLASS_MEDIA��������Ƶ����Ϸ������
	GUID_DEVCLASS_MODEMMODEM
	GUID_DEVCLASS_MOUSE��������ָ���豸
	GUID_DEVCLASS_NET�����豸��
	GUID_DEVCLASS_USBͨ�ô������߿�����
	GUID_DEVCLASS_FLOPPYDISK����������
	GUID_DEVCLASS_UNKNOWNδ֪�豸
	GUID_DEVCLASS_SCSIADAPTERSCSI �� RAID ������
	GUID_DEVCLASS_HDCIDE ATA/ATAPI ������
	GUID_DEVCLASS_PORTS�˿ڣ�COM �� LPT��
	GUID_DEVCLASS_MONITOR������
	*/

	if (hDevInfo == INVALID_HANDLE_VALUE)
	{
		DWORD dwError = GetLastError();
		// Insert error handling here.
		return 1;
	}

	// Enumerate through all devices in Set.

	DeviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);

	for (i = 0; SetupDiEnumDeviceInfo(hDevInfo, i, &DeviceInfoData); i++)

	{
		DWORD DataT;
		wchar_t buffer[2048];
		DWORD buffersize = sizeof(buffer);
		printf("%d\n",buffersize);
		memset(buffer, (wchar_t)0, buffersize);
		while (!SetupDiGetDeviceRegistryProperty(
			hDevInfo,
			&DeviceInfoData,
			SPDRP_FRIENDLYNAME,
			&DataT,
			(PBYTE)buffer,
			buffersize,
			&buffersize))
		{
			if (GetLastError() == ERROR_INSUFFICIENT_BUFFER)
			{
				// Change the buffer size.
				//if (buffer) LocalFree(buffer);
			}
			else
			{
				// Insert error handling here.
				break;
			}
		}

		if (buffer != NULL)
		{
			//wprintf(L"%s\n", buffer);
			for (int test = 0;; test++) 
			{
				if (buffer[i] == '\0')
				{
					break;
					//putwchar(buffer[test]);
				}
				putwchar(buffer[test]);
			}
		}
		break;
		if (buffer)

		{

			LocalFree(buffer);
		}

	}
	if (GetLastError() != NO_ERROR &&   GetLastError() != ERROR_NO_MORE_ITEMS)
	{
		return 1;
	}

	// Cleanup
	SetupDiDestroyDeviceInfoList(hDevInfo);

	return 0;
}