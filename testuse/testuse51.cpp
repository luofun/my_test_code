///testuse51
#include <stdio.h>
#include<stdlib.h>
#include<Windows.h>

void decodesmbios(unsigned char * smbiosdata, int datasize) {
	if (smbiosdata == NULL)
	{
		printf("Input data wrong!\n");
		return;
	}
	printf("Raw data:\n");
	for (int i = 0; i < datasize; i++)
	{
		if (i % 16 == 0)
			printf("\n");
		printf("0x%02x ", smbiosdata[i]);
		
	}
	printf("\nRaw data end. totall size is %d\n", datasize);
	int count = 0;
	int i = 0;
	i += 8;
	for (; i < datasize - 1;)
	{
		printf("table type: %d\n", smbiosdata[i]);
		printf("table length: %d\n", smbiosdata[i + 1]);
		printf("table handle: %d\n", smbiosdata[i + 3] * 256 + smbiosdata[i + 2]);
		i += smbiosdata[i + 1];
		while (smbiosdata[i] != 0 || smbiosdata[i + 1] != 0)
		{
			printf("%c", smbiosdata[i]);
			i += 1;
		}
		i += 2;
		printf("\n");
	}
}


void main() {
	int size = 0;
	PVOID buff = NULL;
	size = GetSystemFirmwareTable('RSMB', 0, buff, size);
	buff = malloc(sizeof(BYTE)*size);
	GetSystemFirmwareTable('RSMB', 0, buff, size);
	decodesmbios((unsigned char *)buff, size);
	free(buff);
}
///end