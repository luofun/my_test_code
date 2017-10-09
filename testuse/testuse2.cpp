#include<stdio.h>
#include<Windows.h>


void main() {
	DWORD Signature = 0x0000;

	PVOID Buffer = NULL;

	DWORD BufferSize = 0;

	EnumSystemFirmwareTables(Signature, Buffer, BufferSize);

	wprintf(L"buffersize\t%d\n", BufferSize);

	Buffer = malloc(BufferSize);

	EnumSystemFirmwareTables(Signature, Buffer, BufferSize);

	//wprintf(L"%s\n",Buffer);

	free(Buffer);

	char pBuffer[BUFSIZ] = { 0 };
	int nRes = EnumSystemFirmwareTables('ACPI', pBuffer, BUFSIZ);
	printf("teststr:\t%s\nnres:\t%d\n", pBuffer,nRes);

	nRes = GetSystemFirmwareTable('RSMB', 0x0000, NULL, 0);
	printf("nres2:\t%d\n", nRes);
	char *nData = new char[nRes];
	ZeroMemory(nData, nRes);
	nRes = GetSystemFirmwareTable('RSMB', 0x0000, nData, nRes);
	printf("teststr2:\t%s\n", nData);
	printf("nres3:\t%d\n", nRes);

	FILE * fp;
	fp = fopen("biosbin.bin","wb");
	fwrite(nData,nRes,1,fp);
	fclose(fp);

}