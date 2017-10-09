#include "windows.h"
#include "setupapi.h"
#include "initguid.h"
#include "stdio.h"
#pragma comment(lib, "setupapi.lib")

#define NAME_SIZE 128
#define PRINT(_x_) printf _x_

DEFINE_GUID(GUID_CLASS_MONITOR,
	0x4d36e96e, 0xe325, 0x11ce, 0xbf, 0xc1, 0x08, 0x00, 0x2b, 0xe1,
	0x03, 0x18);

static void
PlayWithDeviceInfo(
	IN HDEVINFO devInfo,
	IN PSP_DEVINFO_DATA devInfoData
)
{
	HKEY hDevRegKey;
	DWORD uniID[123];

	if (SetupDiGetDeviceRegistryProperty(
		devInfo,
		devInfoData,
		SPDRP_DEVICEDESC,//SPDRP_UI_NUMBER,
		NULL,
		(PBYTE)(&uniID),
		sizeof(uniID),
		NULL))
	{
		printf("UID: %s\n", uniID);
	}
	else {
		printf("ERROR: %d\n", GetLastError());
	}



	hDevRegKey = SetupDiOpenDevRegKey(
		devInfo,
		devInfoData,
		DICS_FLAG_GLOBAL,
		0,
		DIREG_DEV,
		KEY_ALL_ACCESS);

	if (hDevRegKey) {
		LONG retValue, i;
		DWORD dwType, AcutalValueNameLength = NAME_SIZE;

		CHAR valueName[NAME_SIZE];

		for (i = 0, retValue = ERROR_SUCCESS; retValue !=
			ERROR_NO_MORE_ITEMS; i++)
		{
			unsigned char EDIDdata[1024];
			DWORD j, edidsize = sizeof(EDIDdata);

			retValue = RegEnumValue(
				hDevRegKey,
				i,
				&valueName[0],
				&AcutalValueNameLength,
				NULL,//reserved
				&dwType,
				EDIDdata, // buffer
				&edidsize); // buffer size

			if (retValue == ERROR_SUCCESS)
			{
				if (!strcmp(valueName, "EDID")) {
					printf("Found value EDID\n");
					{

						for (j = 0; j<edidsize; j++) {
							if (j % 16 == 0) printf("\n");
							printf("%02x ", EDIDdata[j]);
						}
						printf("\n");
					}

					break;
				}
			}
		}

		RegCloseKey(hDevRegKey);
	}
	else {
		printf("ERROR:%d\n", GetLastError());
	}

}
int EnumDevices()
{
	HDEVINFO devInfo = NULL;
	SP_DEVINFO_DATA devInfoData;
	SP_DEVINFO_LIST_DETAIL_DATA devInfoSetDetailData;
	ULONG i;

	do
	{

		devInfo = SetupDiGetClassDevsEx(
			&GUID_CLASS_MONITOR, //class GUID
			NULL, //enumerator
			NULL, //HWND
			DIGCF_PRESENT, // Flags //DIGCF_ALLCLASSES|
			NULL, // device info, create a new one.
			NULL, // machine name, local machine
			NULL);// reserved

		if (NULL == devInfo)
		{
			//PrintWin32Error("SetupDiGetClassDevsEx");
			break;
		}

		for (i = 0; ERROR_NO_MORE_ITEMS != GetLastError(); i++)
		{

			memset(&devInfoData, 0, sizeof(devInfoData));
			devInfoData.cbSize = sizeof(devInfoData);

			if (SetupDiEnumDeviceInfo(devInfo, i, &devInfoData))
			{
				PlayWithDeviceInfo(devInfo, &devInfoData);
			}
		}

	} while (FALSE);

	return i;
}

int __cdecl main()
{
	EnumDevices();
	Sleep(10000);
	return 0;
}