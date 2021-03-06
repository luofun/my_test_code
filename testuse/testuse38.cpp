///testuse38
#include <afxtempl.h>  

class GetSysInfo
{
public:
	GetSysInfo(void);
	~GetSysInfo(void);

public:
	/********获取操作系统版本，Service pack版本、系统类型************/
	void GetOSVersion(CString &strOSVersion, CString &strServiceVersion);
	BOOL IsWow64();//判断是否为64位操作系统  

				   /***********获取网卡数目和名字***********/
	int  GetInterFaceCount();
	void GetInterFaceName(CString &InterfaceName, int pNum);

	/***获取物理内存和虚拟内存大小***/
	void GetMemoryInfo(CString &dwTotalPhys, CString &dwTotalVirtual);

	/****获取CPU名称、内核数目、主频*******/
	void GetCpuInfo(CString &chProcessorName, CString &chProcessorType, DWORD &dwNum, DWORD &dwMaxClockSpeed);

	/****获取硬盘信息****/
	void GetDiskInfo(DWORD &dwNum, CString chDriveInfo[]);

	/****获取显卡信息*****/
	void GetDisplayCardInfo(DWORD &dwNum, CString chCardName[]);
private:
	CStringList Interfaces;                       //保存所有网卡的名字  
	CList < DWORD, DWORD &>       Bandwidths;   //各网卡的带宽  
	CList < DWORD, DWORD &>       TotalTraffics;    //各网卡的总流量  
};
//#include "GetsysInfo.h"  
#include <atlbase.h>  
#include "float.h"  
#include "winperf.h"  

GetSysInfo::GetSysInfo(void)
{
}

GetSysInfo::~GetSysInfo(void)
{
}

void GetSysInfo::GetOSVersion(CString &strOSVersion, CString &strServiceVersion)
{
	CString str;
	OSVERSIONINFOEX osvi;
	SYSTEM_INFO si;
	BOOL bOsVersionInfoEx;

	ZeroMemory(&si, sizeof(SYSTEM_INFO));
	ZeroMemory(&osvi, sizeof(OSVERSIONINFOEX));

	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
	if (!(bOsVersionInfoEx = GetVersionEx((OSVERSIONINFO *)&osvi)))
	{
		osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
		GetVersionEx((OSVERSIONINFO *)&osvi);
	}


	GetProcAddress(GetModuleHandle(TEXT("kernel32.dll")),
		"GetNativeSystemInfo");

	GetSystemInfo(&si);
	switch (osvi.dwPlatformId)
	{
	case VER_PLATFORM_WIN32_NT:
		if (osvi.dwMajorVersion == 6 && osvi.dwMinorVersion == 0)
		{
			if (osvi.wProductType == VER_NT_WORKSTATION)
			{
				str.Format(_T("Windows Vista "));
			}
			else
			{
				str.Format(_T("Windows Server \"Longhorn\" "));
			}
		}
		if (osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 2)
		{
			if (GetSystemMetrics(SM_SERVERR2))
			{
				str.Format(_T("Microsoft Windows Server 2003 \"R2\" "));
			}
			else if (osvi.wProductType == VER_NT_WORKSTATION &&
				si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64)
			{
				str.Format(_T("Microsoft Windows XP Professional x64 Edition "));
			}
			else
			{
				str.Format(_T("Microsoft Windows Server 2003, "));
			}
		}

		if (osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 1)
		{
			str.Format(_T("Microsoft Windows XP "));
		}

		if (osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 0)
			str.Format(_T("Microsoft Windows 2000 "));

		if (osvi.dwMajorVersion <= 4)
		{
			str.Format(_T("Microsoft Windows NT "));
		}

		// Test for specific product on Windows NT 4.0 SP6 and later.  
		if (bOsVersionInfoEx)
		{

			//将Service Pack 版本保存  
			strServiceVersion.Format(_T("Service Pack %d"), osvi.wServicePackMajor);

			// Test for the workstation type.  
			if (osvi.wProductType == VER_NT_WORKSTATION &&
				si.wProcessorArchitecture != PROCESSOR_ARCHITECTURE_AMD64)
			{
				if (osvi.dwMajorVersion == 4)
					str = str + _T("Workstation 4.0");
				else if (osvi.wSuiteMask & VER_SUITE_PERSONAL)
					str = str + _T("Home Edition");
				else str = str + _T("Professional");
			}

			// Test for the server type.  
			else if (osvi.wProductType == VER_NT_SERVER ||
				osvi.wProductType == VER_NT_DOMAIN_CONTROLLER)
			{
				if (osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 2)
				{
					if (si.wProcessorArchitecture ==
						PROCESSOR_ARCHITECTURE_IA64)
					{
						if (osvi.wSuiteMask & VER_SUITE_DATACENTER)
							str = str + _T("Datacenter Edition for Itanium-based Systems");
						else if (osvi.wSuiteMask & VER_SUITE_ENTERPRISE)
							str = str + _T("Enterprise Edition for Itanium-based Systems");
					}

					else if (si.wProcessorArchitecture ==
						PROCESSOR_ARCHITECTURE_AMD64)
					{
						if (osvi.wSuiteMask & VER_SUITE_DATACENTER)
							str = str + _T("Datacenter x64 Edition ");
						else if (osvi.wSuiteMask & VER_SUITE_ENTERPRISE)
							str = str + _T("Enterprise x64 Edition ");
						else str = str + _T("Standard x64 Edition ");
					}

					else
					{
						if (osvi.wSuiteMask & VER_SUITE_DATACENTER)
							str = str + _T("Datacenter Edition ");
						else if (osvi.wSuiteMask & VER_SUITE_ENTERPRISE)
							str = str + _T("Enterprise Edition ");
						else if (osvi.wSuiteMask & VER_SUITE_BLADE)
							str = str + _T("Web Edition ");
						else str = str + _T("Standard Edition ");
					}
				}
				else if (osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 0)
				{
					if (osvi.wSuiteMask & VER_SUITE_DATACENTER)
						str = str + _T("Datacenter Server ");
					else if (osvi.wSuiteMask & VER_SUITE_ENTERPRISE)
						str = str + _T("Advanced Server ");
					else str = str + _T("Server ");
				}
				else  // Windows NT 4.0   
				{
					if (osvi.wSuiteMask & VER_SUITE_ENTERPRISE)
						str = str + _T("Server 4.0, Enterprise Edition ");
					else str = str + _T("Server 4.0 ");
				}
			}
		}
		// Test for specific product on Windows NT 4.0 SP5 and earlier  
		else
		{
			HKEY hKey;
			TCHAR szProductType[256];
			DWORD dwBufLen = 256 * sizeof(TCHAR);
			LONG lRet;

			lRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE,
				_T("SYSTEM\\CurrentControlSet\\Control\\ProductOptions"), 0, KEY_QUERY_VALUE, &hKey);
			if (lRet != ERROR_SUCCESS)
				strOSVersion = str;
			return;

			lRet = RegQueryValueEx(hKey, TEXT("ProductType"),
				NULL, NULL, (LPBYTE)szProductType, &dwBufLen);
			RegCloseKey(hKey);

			if ((lRet != ERROR_SUCCESS) ||
				(dwBufLen > 256 * sizeof(TCHAR)))
				strOSVersion = str;
			return;

			if (lstrcmpi(TEXT("WINNT"), szProductType) == 0)
				str = str + _T("Workstation ");
			if (lstrcmpi(TEXT("LANMANNT"), szProductType) == 0)
				str = str + _T("Server ");
			if (lstrcmpi(TEXT("SERVERNT"), szProductType) == 0)
				str = str + _T("Advanced Server ");
			str.Format(_T("%d.%d "), osvi.dwMajorVersion, osvi.dwMinorVersion);
		}

		// Display service pack (if any) and build number.  

		if (osvi.dwMajorVersion == 4 &&
			lstrcmpi(osvi.szCSDVersion, TEXT("Service Pack 6")) == 0)
		{
			HKEY hKey;
			LONG lRet;

			// Test for SP6 versus SP6a.  
			lRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE,
				_T("SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Hotfix\\Q246009"), 0, KEY_QUERY_VALUE, &hKey);
			if (lRet == ERROR_SUCCESS)
				str.Format(_T("Service Pack 6a (Build %d)\n"),
					osvi.dwBuildNumber & 0xFFFF);
			else // Windows NT 4.0 prior to SP6a  
			{
				_tprintf(TEXT("%s (Build %d)\n"),
					osvi.szCSDVersion,
					osvi.dwBuildNumber & 0xFFFF);
			}

			RegCloseKey(hKey);
		}
		else // not Windows NT 4.0   
		{
			_tprintf(TEXT("%s (Build %d)\n"),
				osvi.szCSDVersion,
				osvi.dwBuildNumber & 0xFFFF);
		}

		break;

		// Test for the Windows Me/98/95.  
	case VER_PLATFORM_WIN32_WINDOWS:

		if (osvi.dwMajorVersion == 4 && osvi.dwMinorVersion == 0)
		{
			str.Format(_T("Microsoft Windows 95 "));
			if (osvi.szCSDVersion[1] == 'C' || osvi.szCSDVersion[1] == 'B')
				str = str + _T("OSR2 ");
		}

		if (osvi.dwMajorVersion == 4 && osvi.dwMinorVersion == 10)
		{
			str.Format(_T("Microsoft Windows 98 "));
			if (osvi.szCSDVersion[1] == 'A' || osvi.szCSDVersion[1] == 'B')
				str = str + _T("SE ");
		}
		if (osvi.dwMajorVersion == 4 && osvi.dwMinorVersion == 90)
		{
			str.Format(_T("Microsoft Windows Millennium Edition\n"));
		}
		break;

	case VER_PLATFORM_WIN32s:
		str.Format(_T("Microsoft Win32s\n"));
		break;
	default:
		break;
	}

	strOSVersion = str;
}

BOOL GetSysInfo::IsWow64()
{
	typedef BOOL(WINAPI *LPFN_ISWOW64PROCESS) (HANDLE, PBOOL);
	LPFN_ISWOW64PROCESS fnIsWow64Process;
	BOOL bIsWow64 = FALSE;
	fnIsWow64Process = (LPFN_ISWOW64PROCESS)GetProcAddress(GetModuleHandle(_T("kernel32")), "IsWow64Process");
	if (NULL != fnIsWow64Process)
	{
		fnIsWow64Process(GetCurrentProcess(), &bIsWow64);
	}
	return bIsWow64;
}

void GetSysInfo::GetCpuInfo(CString &chProcessorName, CString &chProcessorType, DWORD &dwNum, DWORD &dwMaxClockSpeed)
{

	CString strPath = _T("HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0");//注册表子键路径  
	CRegKey regkey;//定义注册表类对象  
	LONG lResult;//LONG型变量－反应结果  
	lResult = regkey.Open(HKEY_LOCAL_MACHINE, LPCTSTR(strPath), KEY_ALL_ACCESS); //打开注册表键  
	if (lResult != ERROR_SUCCESS)
	{
		return;
	}
	WCHAR chCPUName[50] = { 0 };
	DWORD dwSize = 50;

	//获取ProcessorNameString字段值  
	if (ERROR_SUCCESS == regkey.QueryStringValue(_T("ProcessorNameString"), chCPUName, &dwSize))
	{
		chProcessorName = chCPUName;
	}

	//查询CPU主频  
	DWORD dwValue;
	if (ERROR_SUCCESS == regkey.QueryDWORDValue(_T("~MHz"), dwValue))
	{
		dwMaxClockSpeed = dwValue;
	}
	regkey.Close();//关闭注册表  
				   //UpdateData(FALSE);  

				   //获取CPU核心数目  
	SYSTEM_INFO si;
	memset(&si, 0, sizeof(SYSTEM_INFO));
	GetSystemInfo(&si);
	dwNum = si.dwNumberOfProcessors;

	switch (si.dwProcessorType)
	{
	case PROCESSOR_INTEL_386:
	{
		chProcessorType.Format(_T("Intel 386 processor"));
	}
	break;
	case PROCESSOR_INTEL_486:
	{
		chProcessorType.Format(_T("Intel 486 Processor"));
	}
	break;
	case PROCESSOR_INTEL_PENTIUM:
	{
		chProcessorType.Format(_T("Intel Pentium Processor"));
	}
	break;
	case PROCESSOR_INTEL_IA64:
	{
		chProcessorType.Format(_T("Intel IA64 Processor"));
	}
	break;
	case PROCESSOR_AMD_X8664:
	{
		chProcessorType.Format(_T("AMD X8664 Processor"));
	}
	break;
	default:
		chProcessorType.Format(_T("未知"));
		break;
	}

	//GetDisplayName()  
}

void  GetSysInfo::GetMemoryInfo(CString &dwTotalPhys, CString &dwTotalVirtual)
{
	//   TODO:     Add   extra   initialization   here   
	MEMORYSTATUS   Mem;
	//   get   the   memory   status   
	GlobalMemoryStatus(&Mem);

	DWORD dwSize = (DWORD)Mem.dwTotalPhys / (1024 * 1024);
	DWORD dwVirtSize = (DWORD)Mem.dwTotalVirtual / (1024 * 1024);

	dwTotalPhys.Format(_T("物理内存:%ld MB"), dwSize);
	dwTotalVirtual.Format(_T("虚拟内存:%ld MB"), dwVirtSize);
}

int GetSysInfo::GetInterFaceCount()
{
	/*CGetNetData pNet;
	DWORD pCount = pNet.GetNetworkInterfacesCount();
	return pCount;*/


	try
	{
#define DEFAULT_BUFFER_SIZE 40960L  

		unsigned char *data = (unsigned char*)malloc(DEFAULT_BUFFER_SIZE);
		DWORD type;
		DWORD size = DEFAULT_BUFFER_SIZE;
		DWORD ret;

		char s_key[4096];
		sprintf_s(s_key, 4096, "510");
		//RegQueryValueEx的固定调用格式          
		CString str(s_key);

		//如果RegQueryValueEx函数执行失败则进入循环  
		while ((ret = RegQueryValueEx(HKEY_PERFORMANCE_DATA, str, 0, &type, data, &size)) != ERROR_SUCCESS)
		{
			Sleep(10);
			//如果RegQueryValueEx的返回值为ERROR_MORE_DATA(申请的内存区data太小，不能容纳RegQueryValueEx返回的数据)  
			if (ret == ERROR_MORE_DATA)
			{
				Sleep(10);
				size += DEFAULT_BUFFER_SIZE;
				data = (unsigned char*)realloc(data, size);//重新分配足够大的内存  

				ret = RegQueryValueEx(HKEY_PERFORMANCE_DATA, str, 0, &type, data, &size);//重新执行RegQueryValueEx函数  
			}
			//如果RegQueryValueEx返回值仍旧未成功则函数返回.....(注意内存泄露“free函数”~~~)。  
			//这个if保证了这个while只能进入一次~~~避免死循环  
			if (ret != ERROR_SUCCESS)
			{
				if (NULL != data)
				{
					free(data);
					data = NULL;
				}
				return 0;//0个接口  
			}
		}

		//函数执行成功之后就是对返回的data内存中数据的解析了，这个建议去查看MSDN有关RegQueryValueEx函数参数数据结构的说明  
		//得到数据块       
		PERF_DATA_BLOCK  *dataBlockPtr = (PERF_DATA_BLOCK *)data;
		//得到第一个对象  
		PERF_OBJECT_TYPE *objectPtr = (PERF_OBJECT_TYPE *)((BYTE *)dataBlockPtr + dataBlockPtr->HeaderLength);

		for (int a = 0; a<(int)dataBlockPtr->NumObjectTypes; a++)
		{
			char nameBuffer[255] = { 0 };
			if (objectPtr->ObjectNameTitleIndex == 510)
			{
				DWORD processIdOffset = ULONG_MAX;
				PERF_COUNTER_DEFINITION *counterPtr = (PERF_COUNTER_DEFINITION *)((BYTE *)objectPtr + objectPtr->HeaderLength);

				for (int b = 0; b<(int)objectPtr->NumCounters; b++)
				{
					if (counterPtr->CounterNameTitleIndex == 520)
						processIdOffset = counterPtr->CounterOffset;

					counterPtr = (PERF_COUNTER_DEFINITION *)((BYTE *)counterPtr + counterPtr->ByteLength);
				}

				if (processIdOffset == ULONG_MAX) {
					if (data != NULL)
					{
						free(data);
						data = NULL;
					}
					return 0;
				}

				PERF_INSTANCE_DEFINITION *instancePtr = (PERF_INSTANCE_DEFINITION *)((BYTE *)objectPtr + objectPtr->DefinitionLength);

				for (int b = 0; b<objectPtr->NumInstances; b++)
				{
					wchar_t *namePtr = (wchar_t *)((BYTE *)instancePtr + instancePtr->NameOffset);
					PERF_COUNTER_BLOCK *counterBlockPtr = (PERF_COUNTER_BLOCK *)((BYTE *)instancePtr + instancePtr->ByteLength);

					char pName[256] = { 0 };
					WideCharToMultiByte(CP_ACP, 0, namePtr, -1, pName, sizeof(nameBuffer), 0, 0);

					DWORD bandwith = *((DWORD *)((BYTE *)counterBlockPtr + processIdOffset));
					DWORD tottraff = 0;

					Interfaces.AddTail(CString(pName)); //各网卡的名称  
					Bandwidths.AddTail(bandwith);       //带宽  
					TotalTraffics.AddTail(tottraff);    // 流量初始化为0  

					PERF_COUNTER_BLOCK  *pCtrBlk = (PERF_COUNTER_BLOCK *)((BYTE *)instancePtr + instancePtr->ByteLength);


					instancePtr = (PERF_INSTANCE_DEFINITION *)((BYTE *)instancePtr + instancePtr->ByteLength + pCtrBlk->ByteLength);
				}
			}
			objectPtr = (PERF_OBJECT_TYPE *)((BYTE *)objectPtr + objectPtr->TotalByteLength);
		}
		if (data != NULL)
		{
			free(data);
			data = NULL;
		}
	}
	catch (...)
	{
		return 0;
	}
	return Interfaces.GetCount();
}

void GetSysInfo::GetInterFaceName(CString &InterfaceName, int pNum)
{
	/*CGetNetData pNet;
	pNet.GetNetworkInterfaceName(&InterfaceName,pNum);*/

	POSITION pos = Interfaces.FindIndex(pNum);
	if (pos == NULL)
		return;

	InterfaceName = Interfaces.GetAt(pos);
	pos = Bandwidths.FindIndex(pNum);
	if (pos == NULL)
		return;
	DWORD dwBandwidth = Bandwidths.GetAt(pos);

	CString str;
	str.Format(_T("%d"), dwBandwidth);

	InterfaceName = InterfaceName + str;
}

void GetSysInfo::GetDiskInfo(DWORD &dwNum, CString chDriveInfo[])
{
	DWORD DiskCount = 0;

	//利用GetLogicalDrives()函数可以获取系统中逻辑驱动器的数量，函数返回的是一个32位无符号整型数据。  
	DWORD DiskInfo = GetLogicalDrives();

	//通过循环操作查看每一位数据是否为1，如果为1则磁盘为真,如果为0则磁盘不存在。  
	while (DiskInfo)
	{
		//通过位运算的逻辑与操作，判断是否为1  
		Sleep(10);
		if (DiskInfo & 1)
		{
			DiskCount++;
		}
		DiskInfo = DiskInfo >> 1;//通过位运算的右移操作保证每循环一次所检查的位置向右移动一位。*/  
	}

	if (dwNum < DiskCount)
	{
		return;//实际的磁盘数目大于dwNum  
	}
	dwNum = DiskCount;//将磁盘分区数量保存  


					  //-------------------------------------------------------------------//  
					  //通过GetLogicalDriveStrings()函数获取所有驱动器字符串信息长度  
	int DSLength = GetLogicalDriveStrings(0, NULL);

	WCHAR* DStr = new WCHAR[DSLength];
	memset(DStr, 0, DSLength);

	//通过GetLogicalDriveStrings将字符串信息复制到堆区数组中,其中保存了所有驱动器的信息。  
	GetLogicalDriveStrings(DSLength, DStr);

	int DType;
	int si = 0;
	BOOL fResult;
	unsigned _int64 i64FreeBytesToCaller;
	unsigned _int64 i64TotalBytes;
	unsigned _int64 i64FreeBytes;

	//读取各驱动器信息，由于DStr内部数据格式是A:\NULLB:\NULLC:\NULL，所以DSLength/4可以获得具体大循环范围  
	for (int i = 0; i<DSLength / 4; ++i)
	{
		Sleep(10);
		CString strdriver = DStr + i * 4;
		CString strTmp, strTotalBytes, strFreeBytes;
		DType = GetDriveType(strdriver);//GetDriveType函数，可以获取驱动器类型，参数为驱动器的根目录  
		switch (DType)
		{
		case DRIVE_FIXED:
		{
			strTmp.Format(_T("本地磁盘"));
		}
		break;
		case DRIVE_CDROM:
		{
			strTmp.Format(_T("DVD驱动器"));
		}
		break;
		case DRIVE_REMOVABLE:
		{
			strTmp.Format(_T("可移动磁盘"));
		}
		break;
		case DRIVE_REMOTE:
		{
			strTmp.Format(_T("网络磁盘"));
		}
		break;
		case DRIVE_RAMDISK:
		{
			strTmp.Format(_T("虚拟RAM磁盘"));
		}
		break;
		case DRIVE_UNKNOWN:
		{
			strTmp.Format(_T("虚拟RAM未知设备"));
		}
		break;
		default:
			strTmp.Format(_T("未知设备"));
			break;
		}

		//GetDiskFreeSpaceEx函数，可以获取驱动器磁盘的空间状态,函数返回的是个BOOL类型数据  
		fResult = GetDiskFreeSpaceEx(strdriver,
			(PULARGE_INTEGER)&i64FreeBytesToCaller,
			(PULARGE_INTEGER)&i64TotalBytes,
			(PULARGE_INTEGER)&i64FreeBytes);

		if (fResult)
		{
			strTotalBytes.Format(_T("磁盘总容量%fMB"), (float)i64TotalBytes / 1024 / 1024);
			strFreeBytes.Format(_T("磁盘剩余空间%fMB"), (float)i64FreeBytesToCaller / 1024 / 1024);
		}
		else
		{
			strTotalBytes.Format(_T(""));
			strFreeBytes.Format(_T(""));
		}
		chDriveInfo[i] = strTmp + _T("(") + strdriver + _T("):") + strTotalBytes + strFreeBytes;
		si += 4;
	}
}

void GetSysInfo::GetDisplayCardInfo(DWORD &dwNum, CString chCardName[])
{
	HKEY keyServ;
	HKEY keyEnum;
	HKEY key;
	HKEY key2;
	LONG lResult;//LONG型变量－保存函数返回值  

				 //查询"SYSTEM\\CurrentControlSet\\Services"下的所有子键保存到keyServ  
	lResult = RegOpenKeyEx(HKEY_LOCAL_MACHINE, TEXT("SYSTEM\\CurrentControlSet\\Services"), 0, KEY_READ, &keyServ);
	if (ERROR_SUCCESS != lResult)
		return;


	//查询"SYSTEM\\CurrentControlSet\\Enum"下的所有子键保存到keyEnum  
	lResult = RegOpenKeyEx(HKEY_LOCAL_MACHINE, TEXT("SYSTEM\\CurrentControlSet\\Enum"), 0, KEY_READ, &keyEnum);
	if (ERROR_SUCCESS != lResult)
		return;

	int i = 0, count = 0;
	DWORD size = 0, type = 0;
	for (;; ++i)
	{
		Sleep(5);
		size = 512;
		TCHAR name[512] = { 0 };//保存keyServ下各子项的字段名称  

								//逐个枚举keyServ下的各子项字段保存到name中  
		lResult = RegEnumKeyEx(keyServ, i, name, &size, NULL, NULL, NULL, NULL);

		//要读取的子项不存在，即keyServ的子项全部遍历完时跳出循环  
		if (lResult == ERROR_NO_MORE_ITEMS)
			break;

		//打开keyServ的子项字段为name所标识的字段的值保存到key  
		lResult = RegOpenKeyEx(keyServ, name, 0, KEY_READ, &key);
		if (lResult != ERROR_SUCCESS)
		{
			RegCloseKey(keyServ);
			return;
		}


		size = 512;
		//查询key下的字段为Group的子键字段名保存到name  
		lResult = RegQueryValueEx(key, TEXT("Group"), 0, &type, (LPBYTE)name, &size);
		if (lResult == ERROR_FILE_NOT_FOUND)
		{
			//?键不存在  
			RegCloseKey(key);
			continue;
		};



		//如果查询到的name不是Video则说明该键不是显卡驱动项  
		if (_tcscmp(TEXT("Video"), name) != 0)
		{
			RegCloseKey(key);
			continue;     //返回for循环  
		};

		//如果程序继续往下执行的话说明已经查到了有关显卡的信息，所以在下面的代码执行完之后要break第一个for循环，函数返回  
		lResult = RegOpenKeyEx(key, TEXT("Enum"), 0, KEY_READ, &key2);
		RegCloseKey(key);
		key = key2;
		size = sizeof(count);
		lResult = RegQueryValueEx(key, TEXT("Count"), 0, &type, (LPBYTE)&count, &size);//查询Count字段（显卡数目）  

		dwNum = count;//保存显卡数目  
		for (int j = 0; j <count; ++j)
		{
			TCHAR sz[512] = { 0 };
			TCHAR name[64] = { 0 };
			wsprintf(name, TEXT("%d"), j);
			size = sizeof(sz);
			lResult = RegQueryValueEx(key, name, 0, &type, (LPBYTE)sz, &size);


			lResult = RegOpenKeyEx(keyEnum, sz, 0, KEY_READ, &key2);
			if (ERROR_SUCCESS)
			{
				RegCloseKey(keyEnum);
				return;
			}


			size = sizeof(sz);
			lResult = RegQueryValueEx(key2, TEXT("FriendlyName"), 0, &type, (LPBYTE)sz, &size);
			if (lResult == ERROR_FILE_NOT_FOUND)
			{
				size = sizeof(sz);
				lResult = RegQueryValueEx(key2, TEXT("DeviceDesc"), 0, &type, (LPBYTE)sz, &size);
				chCardName[j] = sz;//保存显卡名称  
			};
			RegCloseKey(key2);
			key2 = NULL;
		};
		RegCloseKey(key);
		key = NULL;
		break;
	}
}
// Test_cpu.cpp : 定义控制台应用程序的入口点。  
//  

//=====================================================================================  
/*                 CPUID指令是intel IA32架构下获得CPU信息的汇编指令，
可以得到CPU类型，型号，制造商信息，商标信息，序列号，
缓存等一系列CPU相关的东西。
*/

//#include <windows.h>  
//#include "GetsysInfo.h"  
#include <iostream>  
#include <string>  

using namespace std;


//用来存储eax,ebx,ecx,edx四个寄存器的信息  
DWORD deax;
DWORD debx;
DWORD decx;
DWORD dedx;

void ExeCPUID(DWORD veax)  //初始化CPU  
{
	__asm
	{
		mov eax, veax
		cpuid
		mov deax, eax
		mov debx, ebx
		mov decx, ecx
		mov dedx, edx
	}
}

/*    在Intel Pentium以上级别的CPU中，有一个称为“时间戳（Time Stamp）”的部件，
它以64位无符号整型数的格式，记录了自CPU上电以来所经过的时钟周期数。
由于目前的CPU主频都非常高，因此这个部件可以达到纳秒级的计时精度。
这个精确性是上述两种方法所无法比拟的。
在Pentium以上的CPU中，提供了一条机器指令RDTSC（Read Time Stamp Counter）
来读取这个时间戳的数字，并将其保存在EDX:EAX寄存器对中
*/
long GetCPUFreq()       //获取CPU频率,单位: MHZ  
{
	int start, over;
	_asm
	{
		RDTSC
		mov start, eax
	}
	Sleep(50);
	_asm
	{
		RDTSC
		mov over, eax
	}
	return (over - start) / 50000;
}



/*   把eax = 0作为输入参数，可以得到CPU的制造商信息。
cpuid指令执行以后，会返回一个12字符的制造商信息，
前四个字符的ASC码按低位到高位放在ebx，中间四个放在edx，最后四个字符放在ecx。
*/
string GetManID()   //获取制造商信息  
{
	char ID[25];
	memset(ID, 0, sizeof(ID));

	ExeCPUID(0);          //初始化  
	memcpy(ID + 0, &debx, 4); //制造商信息复制到数组  
	memcpy(ID + 4, &dedx, 4);
	memcpy(ID + 8, &decx, 4);

	return string(ID);
}


/*  在我的电脑上点击右键，选择属性，可以在窗口的下面看到一条CPU的信息，
这就是CPU的商标字符串。CPU的商标字符串也是通过cpuid得到的。
由于商标的字符串很长(48个字符)，所以不能在一次cpuid指令执行时全部得到，
所以intel把它分成了3个操作，eax的输入参数分别是0x80000002,0x80000003,0x80000004，
每次返回的16个字符，按照从低位到高位的顺序依次放在eax, ebx, ecx, edx。
因此，可以用循环的方式，每次执行完以后保存结果，然后执行下一次cpuid。
*/
string GetCPUType()
{
	const DWORD id = 0x80000002; //从0x80000002开始,到0x80000004结束  
	char CPUType[49];//用来存储CPU型号信息  
	memset(CPUType, 0, sizeof(CPUType));//初始化数组  

	for (DWORD t = 0; t < 3; t++)
	{
		ExeCPUID(id + t);
		//每次循环结束,保存信息到数组  
		memcpy(CPUType + 16 * t + 0, &deax, 4);
		memcpy(CPUType + 16 * t + 4, &debx, 4);
		memcpy(CPUType + 16 * t + 8, &decx, 4);
		memcpy(CPUType + 16 * t + 12, &dedx, 4);
	}

	return string(CPUType);
}

void main()
{
	cout << "本机CPU信息如下:" << endl;
	cout << "CPU 主 频: " << GetCPUFreq() << " MHZ" << endl;
	cout << "CPU 制造商: " << GetManID() << endl;
	cout << "CPU 型 号: " << GetCPUType() << endl;
	// cin.get();  


	cout << "------------------------------------------" << endl;
	DWORD dwnum = 0;
	CString info[20];
	CString totalmemery, totalvirtual;
	GetSysInfo* sys = new GetSysInfo();
	//sys->GetDiskInfo(dwnum,info);  
	//sys->GetMemoryInfo(totalmemery,totalvirtual);  
	//wstring total = totalmemery.GetBuffer(0);  
	//wstring processname = chProcessorName.GetBuffer(0);  
	//wcout<<total<<endl;  
	//wcout<<totalvirtual.GetBuffer(0)<<endl;  



	CString chProcessorName;
	CString chProcessorType;
	DWORD dwNum;
	DWORD dwMaxClockSpeed;
	sys->GetCpuInfo(chProcessorName, chProcessorType, dwNum, dwMaxClockSpeed);
	//wstring processname = chProcessorName.GetBuffer(0);//unicode要使用对应版本的函数  
	wcout << chProcessorName.GetBuffer(0) << endl;
	wcout << chProcessorType.GetBuffer(0) << endl;
	

	DWORD x;
	CString xxx[20];
	sys->GetDisplayCardInfo(x, xxx);
	delete sys;

	getchar();

}
///end