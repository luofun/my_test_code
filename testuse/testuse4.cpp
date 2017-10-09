#include<stdio.h>
#include<Windows.h>

int enum_usb_disk(char usb_paths[], int cnt)
{
	int usb_disk_cnt = 0;

	char disk_path[5] = { 0 };
	char device_path[10] = { 0 };
	DWORD all_disk = GetLogicalDrives();
	printf("System volume flag:0x%X\n", all_disk);

	int i = 0;
	DWORD bytes_returned = 0;
	while (all_disk && usb_disk_cnt < cnt)
	{
		if ((all_disk & 0x1) == 1)
		{
			sprintf_s(disk_path, "%c:", 'A' + i);
			sprintf_s(device_path, "\\\\.\\%s", disk_path);
			if (GetDriveTypeA(disk_path) == DRIVE_REMOVABLE)
			{
				usb_paths[usb_disk_cnt++] = 'A' + i;
			}
		}
		all_disk = all_disk >> 1;
		i++;
	}
	printf("\n%s\n\n",device_path);
	return usb_disk_cnt;
}

int main(int argc, char* argv[])
{


	char usb_volume[8] = { 0 };
	int usb_cnt = enum_usb_disk(usb_volume, 8);
	printf("System has %d usb disk, their volume are:", usb_cnt);
	for (int i = 0; i < usb_cnt; i++)
	{
		printf("%c: ", usb_volume[i]);
	}


	return 0;

}