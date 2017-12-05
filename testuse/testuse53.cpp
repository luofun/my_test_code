///testuse53
#include<Windows.h>
#include<stdio.h>

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
typedef UINT(WINAPI* GETSYSTEMWOW64DIRECTORY)(LPTSTR, UINT);

void decodeedid(unsigned char* ediddata, int size)
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
	mName[1] = ((ediddata[i] & 0x03) << 3) + (ediddata[i + 1] >> 5) + 'A' - 1;
	mName[2] = ediddata[i + 1] & 0x1f + 'A' - 1;
	printf("%s\n", mName);
	i += 2;
	printf("Product Code:\n\tHex: ");
	printf("0x%02x%02x\n", ediddata[i + 1], ediddata[i]);
	printf("\tDec: %d\n", (ediddata[i + 1] << 8) + ediddata[i]);
	i += 2;
	printf("Serial Number:\n");
	printf("\tHex: 0x%02x%02x%02x%02x\n", ediddata[i + 3], ediddata[i + 2], ediddata[i + 1], ediddata[i]);
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
				printf("  #%d: %d x %d (16:10) %dHz\n", j, x, x / 16 * 10, (ediddata[i + 1] & 0x1f) + 60);
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
	for (int j = 0; j < 18; j++)
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
	switch ((ediddata[i + 17] >> 3) & 0x03)
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
			for (int j = 0; j < 12; j += 2)
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

bool cofrimediddata(unsigned char *indata,unsigned char *readdata) {
	return memcmp(indata, readdata, 128) == 0;
}

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
		return FALSE;
	getSystemWow64Directory = (GETSYSTEMWOW64DIRECTORY)GetProcAddress(hKernel32, "GetSystemWow64DirectoryW");
	if (getSystemWow64Directory == NULL)
		return FALSE;
	if ((getSystemWow64Directory(Wow64Directory, _countof(Wow64Directory)) == 0) && (GetLastError() == ERROR_CALL_NOT_IMPLEMENTED))
		return FALSE;
	return TRUE;
#endif
}

void io(unsigned int pos, unsigned int size) {
	HINSTANCE hdll;
	bool g_Is64BitOS = Is64BitOScopy();
	if (!g_Is64BitOS)
	{
		hdll = LoadLibrary(L"WinIo32.dll");
		if (hdll == NULL)
		{
			FreeLibrary(hdll);
			return;
		}
	}
	else
	{
		hdll = LoadLibrary(L"WinIo64.dll");
		if (hdll == NULL)
		{
			FreeLibrary(hdll);
			return;
		}
	}
	InitializeWinIo in1 = (InitializeWinIo)GetProcAddress(hdll, "InitializeWinIo");
	if (in1 == NULL)
	{
		FreeLibrary(hdll);
		return;
	}
	ShutdownWinIo out1 = (ShutdownWinIo)GetProcAddress(hdll, "ShutdownWinIo");
	if (in1 == NULL)
	{
		FreeLibrary(hdll);
		return;
	}
	MapPhysToLin to1 = (MapPhysToLin)GetProcAddress(hdll, "MapPhysToLin");
	if (to1 == NULL)
	{
		FreeLibrary(hdll);
		return;
	}
	UnmapPhysicalMemory back1 = (UnmapPhysicalMemory)GetProcAddress(hdll, "UnmapPhysicalMemory");
	if (back1 == NULL)
	{
		FreeLibrary(hdll);
		return;
	}
	if (!in1())
	{
		out1();
		FreeLibrary(hdll);
		return;
	}
	PDWORD pdwLinAddr = 0;
	tagPhysStruct PhysStruct = { 0 };
	if (g_Is64BitOS)
		PhysStruct.pvPhysAddress = (DWORD64)(pos + size - 128);
	else
		PhysStruct.pvPhysAddress = (DWORD64)(DWORD32)(pos + size - 128);
	PhysStruct.dwPhysMemSizeInBytes = 4;
	pdwLinAddr = (PDWORD)to1(PhysStruct);
	unsigned char data[128] = { 0 };
	memcpy(data, pdwLinAddr, 128);
	decodeedid(data, 128);
	back1(PhysStruct);
	out1();
	FreeLibrary(hdll);
}

int read4acpitable() {
	PVOID ACPIBuffer = NULL;
	DWORD ACPIBufferSize = 0;
	ACPIBufferSize = GetSystemFirmwareTable('ACPI', 'TDSD', NULL, ACPIBufferSize);
	ACPIBuffer = malloc(ACPIBufferSize);
	memset(ACPIBuffer, 0, ACPIBufferSize);
	GetSystemFirmwareTable('ACPI', 'TDSD', ACPIBuffer, ACPIBufferSize);
	int i;
	unsigned int mempos = 0, memsize = 0;
	for (i = 0; i < ACPIBufferSize - 4;)
	{
		if (((unsigned char *)ACPIBuffer)[i] == 'G' && ((unsigned char *)ACPIBuffer)[i + 1] == 'N' && ((unsigned char *)ACPIBuffer)[i + 2] == 'V' && ((unsigned char *)ACPIBuffer)[i + 3] == 'S')
		{
			i += 6;
			memcpy(&mempos, &((unsigned char *)ACPIBuffer)[i], 4);
			memcpy(&memsize, &((unsigned char *)ACPIBuffer)[i + 5], 2);
			break;
		}
		i += 4;
	}
	io(mempos, memsize);
	free(ACPIBuffer);
	return 0;
}

void main() {
	read4acpitable();
}
///end