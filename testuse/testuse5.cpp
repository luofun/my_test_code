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
	GUID_DEVCLASS_FDC软盘控制器
	GUID_DEVCLASS_DISPLAY显示卡
	GUID_DEVCLASS_CDROM光驱
	GUID_DEVCLASS_KEYBOARD键盘
	GUID_DEVCLASS_COMPUTER计算机
	GUID_DEVCLASS_SYSTEM系统
	GUID_DEVCLASS_DISKDRIVE磁盘驱动器
	GUID_DEVCLASS_MEDIA声音、视频和游戏控制器
	GUID_DEVCLASS_MODEMMODEM
	GUID_DEVCLASS_MOUSE鼠标和其他指针设备
	GUID_DEVCLASS_NET网络设备器
	GUID_DEVCLASS_USB通用串行总线控制器
	GUID_DEVCLASS_FLOPPYDISK软盘驱动器
	GUID_DEVCLASS_UNKNOWN未知设备
	GUID_DEVCLASS_SCSIADAPTERSCSI 和 RAID 控制器
	GUID_DEVCLASS_HDCIDE ATA/ATAPI 控制器
	GUID_DEVCLASS_PORTS端口（COM 和 LPT）
	GUID_DEVCLASS_MONITOR监视器
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