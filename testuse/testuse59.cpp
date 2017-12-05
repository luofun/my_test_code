///testuse59
#include<Windows.h>
#include<stdio.h>

#define PCI_CONFIG_ADDRESS 0xcf8
#define PCI_CONFIG_DATA 0xcfc

typedef bool(*InitializeWinIo)();
typedef void(*ShutdownWinIo)();
typedef bool(*GetPortVal)(WORD, PDWORD, BYTE);
typedef bool(*SetPortVal)(WORD, DWORD, BYTE);
//typedef bool(*Is64BitOS)();

int main() {
	HINSTANCE hdll;
	hdll = LoadLibrary(L"WinIo64.dll");
	if (hdll == NULL)
	{
		DWORD xxx = GetLastError();

		printf("load 64dll fail\terror: %u\n", xxx);

		FreeLibrary(hdll);

		return 1;
	}

	InitializeWinIo init = (InitializeWinIo)GetProcAddress(hdll, "InitializeWinIo");

	ShutdownWinIo shutdown = (ShutdownWinIo)GetProcAddress(hdll, "ShutdownWinIo");

	GetPortVal getio = (GetPortVal)GetProcAddress(hdll, "GetPortVal");

	SetPortVal setio = (SetPortVal)GetProcAddress(hdll, "SetPortVal");

	if (!init())
	{
		printf("die\n");
		shutdown();
		return 1;
	}

	int bus, dev, func, count = 0;
	DWORD dwAddr = 0, dwData = 0, VID = 0, DID = 0, SVID = 0, SDID = 0, dwData1 = 0, dwClassCode = 0;

	printf("BUS#\tDEV#\tFUNC#\tVID\tDID\tSVID\tSDID\tClass code\n");
	for (bus = 0; bus <= 255; bus++)
	{
		for (dev = 0; dev < 32; dev++)
		{
			for (func = 0; func < 8; func++)
			{
				dwAddr = 0x80000000 + (bus << 16) + (dev << 11) + (func << 8);

				/* read vendor id */
				if (!setio(PCI_CONFIG_ADDRESS, dwAddr, 4))
					printf("wrong\n");
				if (!getio(PCI_CONFIG_DATA, &dwData, 4))
					printf("wrong\n");

				/*  read sub-vendor id*/
				if (!setio(PCI_CONFIG_ADDRESS, dwAddr | 0x2C, 4))
					printf("wrong\n");
				if (!getio(PCI_CONFIG_DATA, &dwData1, 4))
					printf("wrong\n");

				/*  read class code*/
				if (!setio(PCI_CONFIG_ADDRESS, dwAddr | 0x08, 4))
					printf("wrong\n");
				if (!getio(PCI_CONFIG_DATA, &dwClassCode, 4))
					printf("wrong\n");

				if (dwData != 0xffffffff)
				{
					count++;
					VID = dwData & 0xffff;
					DID = (dwData >> 16) & 0xffff;
					SVID = dwData1 & 0xffff;
					SDID = (dwData1 >> 16) & 0xffff;
					printf("%02X\t%02X\t%02X\t%04X\t%04X\t%04X\t%04X\t%6.6lX\n",
						bus, dev, func, VID, DID, SVID, SDID, dwClassCode >> 8);
				}
			}
		}
	}

	shutdown();
	return 0;
}
///end