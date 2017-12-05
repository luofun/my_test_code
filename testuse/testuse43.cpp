///testuse43
#include<stdio.h>
#include<Windows.h>

struct RawSMBIOSData
{
	BYTE    Used20CallingMethod;
	BYTE    SMBIOSMajorVersion;
	BYTE    SMBIOSMinorVersion;
	BYTE    DmiRevision;
	DWORD    Length;
	BYTE    SMBIOSTableData[];
};

void main() {
	//DWORD Signature = 0x0000;
	PVOID EnumACPIBuffer = NULL, EnumRSMBBuffer = NULL, EnumFIRMBuffer = NULL;
	DWORD EnumACPIBufferSize = 0, EnumSMBIOSBufferSize = 0, EnumFIRMBufferSize = 0;

	EnumACPIBufferSize = EnumSystemFirmwareTables('ACPI', NULL, EnumACPIBufferSize);
	EnumSMBIOSBufferSize = EnumSystemFirmwareTables('RSMB', NULL, EnumSMBIOSBufferSize);
	EnumFIRMBufferSize = EnumSystemFirmwareTables('FIRM', NULL, EnumFIRMBufferSize);
	
	printf("EnumACPIBufferSize: %d\nEnumSMBIOSBufferSize: %d\nEnumFIRMBufferSize: %d\n", EnumACPIBufferSize, EnumSMBIOSBufferSize, EnumFIRMBufferSize);
	
	EnumACPIBuffer = malloc(EnumACPIBufferSize);
	memset(EnumACPIBuffer, 0, EnumACPIBufferSize);
	EnumSystemFirmwareTables('ACPI', EnumACPIBuffer, EnumACPIBufferSize);
	
	EnumRSMBBuffer = malloc(EnumSMBIOSBufferSize);
	memset(EnumRSMBBuffer, 0, EnumSMBIOSBufferSize);
	EnumSystemFirmwareTables('ACPI', EnumRSMBBuffer, EnumSMBIOSBufferSize);
	
	EnumFIRMBuffer = malloc(EnumFIRMBufferSize);
	memset(EnumFIRMBuffer, 0, EnumFIRMBufferSize);
	EnumSystemFirmwareTables('ACPI', EnumFIRMBuffer, EnumFIRMBufferSize);

	RawSMBIOSData testmssmbiosbin;

	PVOID ACPIBuffer = NULL, RSMBBuffer = NULL, FIRMBuffer = NULL;
	DWORD ACPIBufferSize = 0, SMBIOSBufferSize = 0, FIRMBufferSize = 0;

	ACPIBufferSize = GetSystemFirmwareTable('ACPI', 'TDSS', NULL, ACPIBufferSize);
	SMBIOSBufferSize = GetSystemFirmwareTable('RSMB', 0x00, NULL, SMBIOSBufferSize);
	FIRMBufferSize = GetSystemFirmwareTable('FIRM', 0x00, NULL, FIRMBufferSize);

	printf("ACPIBufferSize: %d\nSMBIOSBufferSize: %d\nFIRMBufferSize: %d\n", ACPIBufferSize, SMBIOSBufferSize, FIRMBufferSize);
	printf("test: %d\n", GetSystemFirmwareTable('ACPI', 'TDSD', NULL, 0));
	//printf("%s", EnumACPIBuffer);
	free(EnumACPIBuffer);
	free(EnumRSMBBuffer);
	free(EnumFIRMBuffer);
}
///end