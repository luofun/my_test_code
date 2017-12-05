///testuse42
#include<afx.h>
#include<string.h>
#include<Windows.h>
#include<winerror.h>
#include <strsafe.h>

struct tagPhysStruct
{
	DWORD64 dwPhysMemSizeInBytes;
	DWORD64 pvPhysAddress;
	DWORD64 PhysicalMemoryHandle;
	DWORD64 pvPhysMemLin;
	DWORD64 pvPhysSection;
};

typedef bool(*InitializeWinIo)();
typedef void(*ShutdownWinIo)();
typedef PBYTE(*MapPhysToLin)(tagPhysStruct &);
typedef bool(*UnmapPhysicalMemory)(tagPhysStruct &);

void decodeedid(unsigned char* ediddata,int size)
{
	if (size != 128)
		return;
	int i;
	printf("\n\nedidheader: ");
	for (i = 0; i < 8; i++)
	{
		printf("0x%02x ", ediddata[i]);
	}
	printf("\n");
	printf("Manufacturer Name: ");
	char mName[4] = { 0 };
	mName[0] = (ediddata[i] >> 2) + 'A' - 1;
	mName[1] = ((ediddata[i] & 0x03)<<3) + (ediddata[i + 1] >> 5) + 'A' - 1;
	mName[2] = ediddata[i + 1]&0x1f + 'A' - 1;
	printf("%s\n", mName);
	i += 2;
	printf("Product Code:\n\tHex: ");
	printf("0x%02x%02x\n", ediddata[i + 1], ediddata[i]);
	printf("\tDec: %d\n", (ediddata[i + 1] << 8) + ediddata[i]);
	i += 2;
	printf("Serial Number:\n");
	printf("\tHex: 0x%02x%02x%02x%02x\n", ediddata[i + 3], ediddata[i + 2], ediddata[i + 1], ediddata[i]);
	/*
	char sNum[5] = { 0 };
	sNum[0] = ediddata[i + 3];
	sNum[1] = ediddata[i + 2];
	sNum[2] = ediddata[i + 1];
	sNum[3] = ediddata[i];
	printf("\tstr: %s\n", sNum);
	*/
	i += 4;
	printf("Week of Manufacture: %d\n", ediddata[i]);
	i += 1;
	printf("Year of Manufacture: %d\n", ediddata[i] + 1990);
	i += 1;
	printf("EDID version: %d\nrevision: %d\n", ediddata[i], ediddata[i + 1]);
	i += 2;
	printf("video Input: 0x%02x\n", ediddata[i]);
	printf("  Input: %s\n", (ediddata[i] >> 7) ? "Digital" : "Analog");
	if ((ediddata[i] >> 7))
		printf("  DFP 1.x: %s\n", (ediddata[i] & 0x01) ? "YES" : "NO");
	else
	{
		printf("  value\twhite above blank\tlevel of sync\ttip below blank\n");
		switch ((ediddata[i] >> 5) & 0x03)
		{
		case 0:
			printf("  0 0\t0.700\t0.300\t(1.000 V p-p)\n");
			break;
		case 1:
			printf("  0 1\t0.714\t0.286\t(1.000 V p-p)\n");
			break;
		case 2:
			printf("  1 0\t1.000\t0.400\t(1.400 V p-p)\n");
			break;
		case 3:
			printf("  1 1\t0.700\t0.000\t(0.700 V p-p)\n");
			break;
		default:
			printf("  read error\n");
			break;
		}
		printf("  setup: %d\n", (ediddata[i] >> 4) & 0x01);
		printf("  separate syncs: %s\n", ((ediddata[i] >> 3) & 0x01) ? "supported" : "unsupported");
		printf("  composite sync: %s\n", ((ediddata[i] >> 2) & 0x01) ? "supported" : "unsupported");
		printf("  sync. on green video: %s\n", ((ediddata[i] >> 1) & 0x01) ? "supported" : "unsupported");
		printf("  Serration of Vsync. pulse: %s\n", (ediddata[i] & 0x01) ? "YES" : "NO");
	}
	i += 1;
	printf("Max. Horizontal Image Size: %dcm\n", ediddata[i]);
	printf("Max. Vertical Image size: %dcm\n", ediddata[i + 1]);
	i += 2;
	printf("gamma: %f\n", ((float)ediddata[i] + 100) / 100);
	i += 1;
	printf("feature support: 0x%02x\n", ediddata[i]);
	printf("  Standby: %s\n", (ediddata[i] >> 7) ? "YES" : "NO");
	printf("  Suspend: %s\n", ((ediddata[i] >> 6) & 0x01) ? "YES" : "NO");
	printf("  Active Off/Very Low Power: %s\n", ((ediddata[i] >> 5) & 0x01) ? "YES" : "NO");
	switch ((ediddata[i] >> 3) & 0x03)
	{
	case 0:
		printf("  Display type: Monochrome /grayscale\n");
		break;
	case 1:
		printf("  Display type: RGB\n");
		break;
	case 2:
		printf("  Display type: Non-RGB\n");
		break;
	case 3:
		printf("  Display type: Undefined\n");
		break;
	default:
		printf("read error\n");
		break;
	}
	printf("  Color Space,sRGB: %d\n", ((ediddata[i] >> 2) & 0x01));
	printf("  Preferred Timing Mode: %d\n", ((ediddata[i] >> 1) & 0x01));
	printf("  Default GTF supported: %d\n", (ediddata[i] & 0x01));
	i += 1;
	printf("Color Characteristic: ");
	for (int j = 0; j < 10; j++)
		printf("0x%02x ", ediddata[i + j]);
	printf("\n");
	float xxxtable[1024] = { 0 };
	for (int j = 0; j < 1024; j++)
	{
		xxxtable[j] = 0.0009765625*j;
	}
	printf("  Red_x: %0.3f\n", xxxtable[(ediddata[i] >> 6) + (ediddata[i + 2] << 2)]);
	printf("  Red_y: %0.3f\n", xxxtable[((ediddata[i] >> 4) & 0x03) + (ediddata[i + 3] << 2)]);
	printf("  Green_x: %0.3f\n", xxxtable[((ediddata[i] >> 2) & 0x03) + (ediddata[i + 4] << 2)]);
	printf("  Green_y: %0.3f\n", xxxtable[(ediddata[i] & 0x03) + (ediddata[i + 5] << 2)]);
	printf("  Blue_x: %0.3f\n", xxxtable[(ediddata[i + 1] >> 6) + (ediddata[i + 6] << 2)]);
	printf("  Blue_y: %0.3f\n", xxxtable[((ediddata[i + 1] >> 4) & 0x03) + (ediddata[i + 7] << 2)]);
	printf("  White_x: %0.3f\n", xxxtable[((ediddata[i + 1] >> 2) & 0x03) + (ediddata[i + 8] << 2)]);
	printf("  White_y: %0.3f\n", xxxtable[(ediddata[i + 1] & 0x03) + (ediddata[i + 9] << 2)]);
	i += 10;
	printf("Established Timing I:\n");
	unsigned char check = 0x80;
	char timingtable1[][20] = { "720 x 400 @ 70Hz",
							    "720 x 400 @ 88Hz",
							    "640 x 480 @ 60Hz",
							    "640 x 480 @ 67Hz",
							    "640 x 480 @ 72Hz",
							    "640 x 480 @ 75Hz",
							    "800 x 600 @ 56Hz",
							    "800 x 600 @ 60Hz" };
	for (int j = 0; j < 8; j++)
	{
		if (ediddata[i] & (check >> j))
			printf("  %s\n", timingtable1[j]);
	}
	i += 1;
	printf("Established Timing II:\n");
	char timingtable2[][20] = { "800 x 600 @ 72Hz",
								"800 x 600 @ 75Hz",
								"832 x 624 @ 75Hz",
								"1024 x 768 @ 87Hz",
								"1024 x 768 @ 60Hz",
								"1024 x 768 @ 60Hz",
								"1024 x 768 @ 75Hz",
								"1280 x 1024 @ 75Hz" };
	for (int j = 0; j < 8; j++)
	{
		if (ediddata[i] & (check >> j))
			printf("  %s\n", timingtable2[j]);
	}
	i += 1;
	printf("Manufacturer's Timings:\n");
	char timingtable3[][20] = { "1152 x 870 @ 75Hz" };
	if (ediddata[i] & check)
		printf("  %s\n", timingtable3[0]);
	i += 1;
	printf("additional timings:\n");
	for (int j = 0; j < 8; j++)
	{
		if (ediddata[i] != 0x01)
		{
			int x = (ediddata[i] + 31) * 8;
			switch ((ediddata[i + 1] >> 6) & 0x03)
			{
			case 0:
				printf("  #%d: %d x %d (16:10) %dHz\n", j, x, x / 16 * 10 , (ediddata[i + 1] & 0x1f) + 60);
				break;
			case 1:
				printf("  #%d: %d x %d (4:3) %dHz\n", j, x, x / 4 * 3, (ediddata[i + 1] & 0x1f) + 60);
				break;
			case 2:
				printf("  #%d: %d x %d (5:4) %dHz\n", j, x, x / 5 * 4, (ediddata[i + 1] & 0x1f) + 60);
				break;
			case 3:
				printf("  #%d: %d x %d (16:9) %dHz\n", j, x, x / 16 * 9, (ediddata[i + 1] & 0x1f) + 60);
				break;
			default:
				break;
			}
		}
		else
		{
			printf("  #%d: unused\n", j);
		}
		i += 2;
	}
	printf("Detailed Timing Descriptor:\n");
	printf("  Data: ");
	for (int j = 0; j < 18;j++) 
	{
		printf("0x%02x ", ediddata[i + j]);
	}
	printf("\n");
	printf("  Pixel clock: %0.3fMHz\n", (float)((ediddata[i + 1] << 8) + ediddata[i]) / 100);
	printf("  Horizontal Active: %d\n", ediddata[i + 2] + ((ediddata[i + 4] & 0xf0) << 4));
	printf("  Horizontal Blanking: %d\n", ediddata[i + 3] + ((ediddata[i + 4] & 0x0f) << 8));
	printf("  Vertical Active: %d\n", ediddata[i + 5] + ((ediddata[i + 7] & 0xf0) << 4));
	printf("  Vertical Blanking: %d\n", ediddata[i + 6] + ((ediddata[i + 7] & 0x0f) << 8));
	printf("  Horizontal Sync. Offset: %d\n", ediddata[i + 8] + ((ediddata[i + 11] & 0xc0) << 2));
	printf("  Horizontal Sync Pulse Width: %d\n", ediddata[i + 9] + ((ediddata[i + 11] & 0x30) << 4));
	printf("  Vertical Sync Offset: %d lines\n", ((ediddata[i + 10] & 0xf0) >> 4) + ((ediddata[i + 11] & 0xc0) << 6));
	printf("  Vertical Sync Pulse Width: %d lines\n", (ediddata[i + 10] & 0x0f) + ((ediddata[i + 11] & 0x03) << 8));
	printf("  Horizontal Image Size: %d\n", ediddata[i + 12] + ((ediddata[i + 14] & 0xf0) << 4));
	printf("  Vertical Image Size: %d\n", ediddata[i + 13] + ((ediddata[i + 14] & 0x0f) << 8));
	printf("  Horizontal Border: %d\n", ediddata[i + 15]);
	printf("  Vertical Border: %d\n", ediddata[i + 16]);
	printf("  Flags:\n");
	printf("\t%s\n", (ediddata[i + 17] >> 7) ? "Interlaced" : "Non-interlaced");
	switch (((ediddata[i + 17] >> 5) & 0x03))
	{
	case 0:
		printf("\tNormal display, no stereo\n");
		break;
	case 1:
		if (ediddata[i + 17] & 0x01)
			printf("\t2-way interleaved stereo, right image on even lines\n");
		else
			printf("\tField sequential stereo, right image when stereo sync. = 1\n");
		break;
	case 2:
		if (ediddata[i + 17] & 0x01)
			printf("\t2-way interleaved stereo, left image on even lines\n");
		else
			printf("\tField sequential stereo, left image when stereo sync. = 1\n");
		break;
	case 3:
		if (ediddata[i + 17] & 0x01)
			printf("\tSide-by-Side interleaved stereo\n");
		else 
			printf("\t4-way interleaved stereo\n");
		break;
	default:
		printf("\tread error\n");
		break;
	}
	switch ((ediddata[i+17]>>3)&0x03)
	{
	case 0:
		printf("\tAnalog composite\n\t%s\n\t%s\n", ((ediddata[i + 17] >> 2) & 0x01) ? "Serrate" : "", ((ediddata[i + 17] >> 1) & 0x01) ? "on all 3 video signal lines." : "on green video line only");
		break;
	case 1:
		printf("\tBipolar analog composite\n\t%s\n\t%s\n", ((ediddata[i + 17] >> 2) & 0x01) ? "Serrate" : "", ((ediddata[i + 17] >> 1) & 0x01) ? "on all 3 video signal lines." : "on green video line only");
		break;
	case 2:
		printf("\tDigital composite\n\t%s\n\tComposite Polarity: %d\n", ((ediddata[i + 17] >> 2) & 0x01) ? "Serrate" : "", ((ediddata[i + 17] >> 1) & 0x01));
		break;
	case 3:
		printf("\tDigital separate\n\tVertical Polarity: %d\n\tHorizontal Polarity: %d\n", ((ediddata[i + 17] >> 2) & 0x01), ((ediddata[i + 17] >> 1) & 0x01));
		break;
	default:
		printf("read error\n");
		break;
	}
	i += 18;
	for (int k = 0; k < 3; k++)
	{
		printf("Monitor Descriptor Description:\n");
		printf("  Data: ");
		for (int j = 0; j < 18; j++)
		{
			printf("0x%02x ", ediddata[i + j]);
		}
		printf("\n");
		printf("  Used as: %s\n", ((ediddata[i + 1] << 8) + ediddata[i]) ? "detailed timings" : "Monitor Descriptors");
		switch (ediddata[i + 3])
		{
		case 0xff:
			printf("  Data Type: Monitor Serial Number\n");
			printf("  ");
			for (int j = 0; j < 13; j++)
			{
				if (ediddata[i + 5 + j] != 0x0a)
					printf("%c", ediddata[i + 5 + j]);
				else
					break;
			}
			printf("\n");
			break;
		case 0xfe:
			printf("  Data Type: ASCII String\n");
			printf("  ");
			for (int j = 0; j < 13; j++)
			{
				if (ediddata[i + 5 + j] != 0x0a)
					printf("%c", ediddata[i + 5 + j]);
				else
					break;
			}
			printf("\n");
			break;
		case 0xfd:
			printf("  Data Type: Monitor range limits\n");
			printf("  Min. Vertical rate: %d Hz\n", ediddata[i + 5]);
			printf("  Max. Vertical rate: %d Hz\n", ediddata[i + 6]);
			printf("  Min. Horizontal: %d kHz\n", ediddata[i + 7]);
			printf("  Max. Horizontal: %d kHz\n", ediddata[i + 8]);
			printf("  Max. Horizontal: %d MHz\n", ediddata[i + 9] * 10);
			switch (ediddata[i + 10])
			{
			case 0x00:
				printf("  No secondary timing formula supported\n");
				break;
			case 0x02:
				printf("  Secondary GTF curve supported\n");
				printf("\tStart frequency for secondary curve: %d\n", ediddata[i + 12] * 2);
				printf("\tC: %d\n", ediddata[i + 13] / 2);
				printf("\tM: %d\n", (ediddata[i + 15] << 8) + ediddata[i + 14]);
				printf("\tK: %d\n", ediddata[i + 16]);
				printf("\tJ: %d\n", ediddata[i + 17] / 2);
				break;
			default:
				printf("  read error\n");
				break;
			}
			break;
		case 0xfc:
			printf("  Data Type: Monitor name\n");
			printf("  Data Type: ASCII String\n");
			printf("  ");
			for (int j = 0; j < 13; j++)
			{
				if (ediddata[i + 5 + j] != 0x0a)
					printf("%c", ediddata[i + 5 + j]);
				else
					break;
			}
			printf("\n");
			break;
		case 0xfb:
			printf("  Data Type: Descriptor contains additional color point data\n");
			for (int j = 0; j < 10; j += 5)
			{
				printf("\tWhite point index number: %d\n", ediddata[i + j + 5]);
				printf("\tWhite_x: %0.3f\n", xxxtable[(ediddata[i + j + 7] << 4) + (ediddata[i + j + 6] >> 4)]);
				printf("\tWhite_y: %0.3f\n", xxxtable[(ediddata[i + j + 8] << 4) + (ediddata[i + j + 6] & 0x0f)]);
				printf("\tWhite Gamma: %f\n", ((float)ediddata[i + j + 9] + 100) / 100);
			}
			break;
		case 0xfa:
			printf("  Data Type: Descriptor contains additional Standard Timing Identifications\n");
			for (int j = 0; j < 12; j+=2)
			{
				if (ediddata[i + j + 5] != 0x01)
				{
					int x = (ediddata[i + j + 5] + 31) * 8;
					switch ((ediddata[i + j + 6] >> 6) & 0x03)
					{
					case 0:
						printf("\t#%d: %d x %d (16:10) %dHz\n", j + 8, x, x / 16 * 10, (ediddata[i + j + 6] & 0x1f) + 60);
						break;
					case 1:
						printf("\t#%d: %d x %d (4:3) %dHz\n", j + 8, x, x / 4 * 3, (ediddata[i + j + 6] & 0x1f) + 60);
						break;
					case 2:
						printf("\t#%d: %d x %d (5:4) %dHz\n", j + 8, x, x / 5 * 4, (ediddata[i + j + 6] & 0x1f) + 60);
						break;
					case 3:
						printf("\t#%d: %d x %d (16:9) %dHz\n", j + 8, x, x / 16 * 9, (ediddata[i + j + 6] & 0x1f) + 60);
						break;
					default:
						break;
					}
				}
				else
				{
					printf("  #%d: unused\n", j + 8);
				}
			}
			break;
		case 0x10:
			printf("  Data Type: Dummy descriptor\n");
			break;
		default:
			if (ediddata[i + 3] >= 0x00 && ediddata[i + 3] <= 0x0f)
			{
				printf("  Data Type: Descriptor defined by manufacturer\n");
				printf("\tDate: ");
				for (int j = 0; j < 13; j++)
				{
					printf("0x%02x ", ediddata[i + 5 + j]);
				}
				printf("\n");
			}
			else
				printf("  Data Type: Currently undefined\n");
			break;
		}
		i += 18;
	}
	printf("Extension Flag: 0x%02x\n", ediddata[i]);
	printf("Checksum: 0x%02x\n", ediddata[i + 1]);

}

int win7edid() {
	HKEY RootKey;
	HKEY SubKey;
	HKEY key;
	HKEY readkey;
	LONG lResult;
	int i = 0, j = 0, k = 0, count = 0;
	DWORD size = 0, type = 0;
	unsigned char ediddata[1024];
	DWORD edidsize = sizeof(ediddata);

	//查询"SYSTEM\\CurrentControlSet\\Enum\\DISPLAY
	lResult = RegOpenKeyEx(HKEY_LOCAL_MACHINE, TEXT("SYSTEM\\CurrentControlSet\\Enum\\DISPLAY"), 0, KEY_READ, &RootKey);
	if (ERROR_SUCCESS != lResult)
		return 1;
	for (;; ++i)
	{
		TCHAR name1[512] = { 0 };//保存RootKey下各子项的字段名称  
		size = 512;
		j = 0;

		//逐个枚举RootKey下的各子项字段保存到name1中 						 
		lResult = RegEnumKeyEx(RootKey, i, name1, &size, NULL, NULL, NULL, NULL);

		//RootKey的子项全部遍历完时跳出循环  
		if (lResult == ERROR_NO_MORE_ITEMS)
			break;
		//根据名字打开子项
		lResult = RegOpenKeyEx(RootKey, name1, 0, KEY_READ, &SubKey);

		if (ERROR_SUCCESS != lResult)
			return 1;

		for (;; ++j)
		{
			k = 0;
			size = 512;
			//逐个枚举SubKey下的各子项字段保存到name1中
			lResult = RegEnumKeyEx(SubKey, j, name1, &size, NULL, NULL, NULL, NULL);

			//SubKey的子项全部遍历完时跳出循环  
			if (lResult == ERROR_NO_MORE_ITEMS)
				break;
			//根据名字打开子项
			lResult = RegOpenKeyEx(SubKey, name1, 0, KEY_READ, &key);

			if (ERROR_SUCCESS != lResult)
				return 1;

			for (;; ++k)
			{
				
				size = 512;
				lResult = RegEnumKeyEx(key, k, name1, &size, NULL, NULL, NULL, NULL);

				//key的子项全部遍历完时跳出循环  
				if (lResult == ERROR_NO_MORE_ITEMS)
					break;

				if (_tcscmp(TEXT("Control"), name1) == 0)
				{
					lResult = RegOpenKeyEx(key, TEXT("Device Parameters"), 0, KEY_READ, &readkey);					
					if (ERROR_SUCCESS != lResult)
						return 1;

					//查询readkey下的字段为EDID的子键字段名保存到edtddata  
					lResult = RegQueryValueEx(readkey, TEXT("EDID"), 0, &type, (LPBYTE)ediddata, &edidsize);
					if (lResult == ERROR_FILE_NOT_FOUND)
					{  
						RegCloseKey(readkey);
						return 1;
					};
					
					printf("Found value EDID\n");					
					for (int x = 0; x<edidsize; x++) 
					{
						if (x % 16 == 0) 
							printf("\n");
						printf("%02x ", ediddata[x]);
					}
					printf("\n");
					decodeedid(ediddata, edidsize);
					RegCloseKey(RootKey);
					RegCloseKey(SubKey);
					RegCloseKey(key);
					RegCloseKey(readkey);
					return 0;
				}

			}

		}		
	}
	RegCloseKey(RootKey);
	RegCloseKey(SubKey);
	RegCloseKey(key);
	RegCloseKey(readkey);
	return 1;
}

int win10edid() {
	HKEY RootKey;
	LONG lResult;
	unsigned char ediddata[1024];
	DWORD edidsize = sizeof(ediddata);
	DWORD type;

	lResult = RegOpenKeyEx(HKEY_LOCAL_MACHINE, TEXT("SYSTEM\\ControlSet001\\Control\\GraphicsDrivers\\InternalMonEdid"), 0, KEY_READ, &RootKey);
	if (ERROR_SUCCESS != lResult)
	{
		printf("open fail\n");
		return 1;
	}
	lResult = RegQueryValueEx(RootKey, TEXT("EDID"), 0, &type, (LPBYTE)ediddata, &edidsize);
	if (lResult == ERROR_FILE_NOT_FOUND)
	{
		RegCloseKey(RootKey);
		printf("read fail\n");
		return 1;
	};
	printf("Found value EDID\n");
	for (int x = 0; x<edidsize; x++)
	{
		if (x % 16 == 0)
			printf("\n");
		printf("%02x ", ediddata[x]);
	}
	printf("\n");
	decodeedid(ediddata, edidsize);
	RegCloseKey(RootKey);
	return 0;
}

typedef UINT(WINAPI* GETSYSTEMWOW64DIRECTORY)(LPTSTR, UINT);

BOOL Is64BitOScopy()
{
#ifdef _WIN64
	return TRUE;
#else
	GETSYSTEMWOW64DIRECTORY getSystemWow64Directory;
	HMODULE hKernel32;
	TCHAR Wow64Directory[32767];

	hKernel32 = GetModuleHandle(TEXT("kernel32.dll"));
	if (hKernel32 == NULL)
	{
		//
		// This shouldn't happen, but if we can't get 
		// kernel32's module handle then assume we are 
		// on x86. We won't ever install 32-bit drivers
		// on 64-bit machines, we just want to catch it 
		// up front to give users a better error message.
		//
		return FALSE;
	}

	getSystemWow64Directory = (GETSYSTEMWOW64DIRECTORY)GetProcAddress(hKernel32, "GetSystemWow64DirectoryW");

	if (getSystemWow64Directory == NULL)
	{
		//
		// This most likely means we are running 
		// on Windows 2000, which didn't have this API 
		// and didn't have a 64-bit counterpart.
		//
		return FALSE;
	}

	if ((getSystemWow64Directory(Wow64Directory, _countof(Wow64Directory)) == 0) &&
		(GetLastError() == ERROR_CALL_NOT_IMPLEMENTED)) {
		return FALSE;
	}

	//
	// GetSystemWow64Directory succeeded 
	// so we are on a 64-bit OS.
	//
	return TRUE;
#endif
}

void mmio(unsigned int pos, unsigned int size) {
	//todo
	//try the winio
	HINSTANCE hdll;
	bool g_Is64BitOS = Is64BitOScopy();
	if (!g_Is64BitOS)
	{
		hdll = LoadLibrary(L"WinIo32.dll");
		if (hdll == NULL)
		{
			DWORD xxx = GetLastError();
			
			printf("load 32dll fail\terror: %u\n", xxx);

			LPVOID lpMsgBuf;
			LPVOID lpDisplayBuf;

			FormatMessage(
				FORMAT_MESSAGE_ALLOCATE_BUFFER |
				FORMAT_MESSAGE_FROM_SYSTEM |
				FORMAT_MESSAGE_IGNORE_INSERTS,
				NULL,
				xxx,
				MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
				(LPTSTR)&lpMsgBuf,
				0, NULL);
			lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT,
				(lstrlen((LPCTSTR)lpMsgBuf) + lstrlen(L"test") + 40) * sizeof(TCHAR));
			StringCchPrintf((LPTSTR)lpDisplayBuf,
				LocalSize(lpDisplayBuf) / sizeof(TCHAR),
				TEXT("%s failed with error %d: %s"),
				L"test", xxx, lpMsgBuf);
			MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK);

			LocalFree(lpMsgBuf);
			LocalFree(lpDisplayBuf);

			FreeLibrary(hdll);

			return;
		}
	}
	else
	{
		hdll = LoadLibrary(L"WinIo64.dll");
		if (hdll == NULL)
		{
			DWORD xxx = GetLastError();
			
			printf("load 64dll fail\terror: %u\n", xxx);

			LPVOID lpMsgBuf;
			LPVOID lpDisplayBuf;

			FormatMessage(
				FORMAT_MESSAGE_ALLOCATE_BUFFER |
				FORMAT_MESSAGE_FROM_SYSTEM |
				FORMAT_MESSAGE_IGNORE_INSERTS,
				NULL,
				xxx,
				MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
				(LPTSTR)&lpMsgBuf,
				0, NULL);
			lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT,
				(lstrlen((LPCTSTR)lpMsgBuf) + lstrlen(L"test") + 40) * sizeof(TCHAR));
			StringCchPrintf((LPTSTR)lpDisplayBuf,
				LocalSize(lpDisplayBuf) / sizeof(TCHAR),
				TEXT("%s failed with error %d: %s"),
				L"test", xxx, lpMsgBuf);
			MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK);

			LocalFree(lpMsgBuf);
			LocalFree(lpDisplayBuf);

			FreeLibrary(hdll);

			return;
		}
	}
	printf("success to load the winio.dll!\n");

	InitializeWinIo in1 = (InitializeWinIo)GetProcAddress(hdll, "InitializeWinIo");
	if (in1 == NULL)
	{
		printf("InitializeWinIo function fail\n");
		FreeLibrary(hdll);
		return;
	}
	ShutdownWinIo out1=(ShutdownWinIo)GetProcAddress(hdll, "ShutdownWinIo");
	if (in1 == NULL)
	{
		printf("ShutdownWinIo function fail\n");
		FreeLibrary(hdll);
		return;
	}
	MapPhysToLin to1=(MapPhysToLin)GetProcAddress(hdll, "MapPhysToLin");
	if (to1 == NULL)
	{
		printf("MapPhysToLin function fail\n");
		FreeLibrary(hdll);
		return;
	}
	UnmapPhysicalMemory back1=(UnmapPhysicalMemory)GetProcAddress(hdll, "UnmapPhysicalMemory");
	if (back1 == NULL)
	{
		printf("UnmapPhysicalMemory function fail\n");
		FreeLibrary(hdll);
		return;
	}
	if (!in1())
	{
		printf("init fail\n");
		
		DWORD xxx = GetLastError();

		LPVOID lpMsgBuf;
		LPVOID lpDisplayBuf;

		FormatMessage(
			FORMAT_MESSAGE_ALLOCATE_BUFFER |
			FORMAT_MESSAGE_FROM_SYSTEM |
			FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			xxx,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPTSTR)&lpMsgBuf,
			0, NULL);
		lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT,
			(lstrlen((LPCTSTR)lpMsgBuf) + lstrlen(L"test") + 40) * sizeof(TCHAR));
		StringCchPrintf((LPTSTR)lpDisplayBuf,
			LocalSize(lpDisplayBuf) / sizeof(TCHAR),
			TEXT("%s failed with error %d: %s"),
			L"test", xxx, lpMsgBuf);
		MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK);

		LocalFree(lpMsgBuf);
		LocalFree(lpDisplayBuf);

		out1();
		FreeLibrary(hdll);
		return;
	}

	PDWORD pdwLinAddr = 0;
	tagPhysStruct PhysStruct = { 0 };

	if (g_Is64BitOS)
	{
		PhysStruct.pvPhysAddress = (DWORD64)(pos + size - 128);
	}
	else
	{
		// Avoid sign extension issues
		PhysStruct.pvPhysAddress = (DWORD64)(DWORD32)(pos + size - 128);
	}

	PhysStruct.dwPhysMemSizeInBytes = 4;

	pdwLinAddr = (PDWORD)to1(PhysStruct);

	printf("phy address: 0x%x\tlinear address: 0x%x\nlinear value: 0x%x\n", pos, pdwLinAddr, *pdwLinAddr);

	unsigned char data[128] = { 0 };

	memcpy(data, pdwLinAddr, 128);

	decodeedid(data, 128);

	back1(PhysStruct);
	out1();

	FreeLibrary(hdll);

}

int read4acpitable() {
	PVOID EnumACPIBuffer = NULL;
	DWORD EnumACPIBufferSize = 0;

	EnumACPIBufferSize = EnumSystemFirmwareTables('ACPI', NULL, EnumACPIBufferSize);
	printf("EnumACPIBufferSize: %d\n",EnumACPIBuffer);

	EnumACPIBuffer = malloc(EnumACPIBufferSize);
	memset(EnumACPIBuffer, 0, EnumACPIBufferSize);
	EnumSystemFirmwareTables('ACPI', EnumACPIBuffer, EnumACPIBufferSize);

	PVOID showEnumACPIBuffer = malloc(EnumACPIBufferSize + 1);
	memset(showEnumACPIBuffer, 0, EnumACPIBufferSize + 1);
	memcpy(showEnumACPIBuffer, EnumACPIBuffer, EnumACPIBufferSize);
	printf("enum: %s\n", showEnumACPIBuffer);

	PVOID ACPIBuffer = NULL;
	DWORD ACPIBufferSize = 0;

	ACPIBufferSize = GetSystemFirmwareTable('ACPI', 'TDSD', NULL, ACPIBufferSize);

	printf("ACPIBufferSize: %d\n", ACPIBufferSize);

	ACPIBuffer = malloc(ACPIBufferSize);
	memset(ACPIBuffer, 0, ACPIBufferSize);
	GetSystemFirmwareTable('ACPI', 'TDSD', ACPIBuffer, ACPIBufferSize);
	
	int i;
	unsigned int mempos = 0, memsize = 0;

	for (i = 0; i < ACPIBufferSize - 4;)
	{
		if (((unsigned char *)ACPIBuffer)[i] == 'G' && ((unsigned char *)ACPIBuffer)[i + 1] == 'N' && ((unsigned char *)ACPIBuffer)[i + 2] == 'V' && ((unsigned char *)ACPIBuffer)[i + 3] == 'S')
		{
			printf("get the GNVS & pos: %d\n", i);

			i += 6;

			memcpy(&mempos, &((unsigned char *)ACPIBuffer)[i], 4);
			memcpy(&memsize, &((unsigned char *)ACPIBuffer)[i + 5], 2);

			printf("mempos: 0x%x\t%u\n", mempos, mempos);
			printf("memsize: 0x%x\t%u\n", memsize, memsize);
			
			break;
		}
		i += 4;
	}

	mmio(mempos, memsize);
	free(ACPIBuffer);
	free(EnumACPIBuffer);

	return 0;
}

int main(int argc,char* argv[])
{
	if (argc <= 1)
	{
		printf("\nargv no enough\n");
		return 1;
	}
	if (0 == strcmp(argv[1], "win7"))
	{
		printf("\nrun the win7\n");
		if(win7edid())
			printf("\nfail\n");
		return 0;
	}
	if (0 == strcmp(argv[1], "win10"))
	{
		printf("\nrun the win10\n");
		if(win10edid())
			printf("\nfail\n");
		return 0;
	}
	if (0 == strcmp(argv[1], "acpi"))
	{
		printf("\nrun the acpi mode\n");
		read4acpitable();
		return 0;
	}
	printf("\nargv[1] not right. try to use the 'win7' or 'win10' or 'acpi'\n");
	return 1;
}
///end