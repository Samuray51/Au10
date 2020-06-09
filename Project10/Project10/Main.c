#include <windows.h> 
#include <stdio.h> 
#include <psapi.h> 

int Count = 0;

void PrintProcessNameAndID(DWORD processID) 
{
	char szProcessName[257];
	HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processID);

	if (NULL != hProcess) 
	{
		HMODULE hMod;
		DWORD cbNeeded;

		if (EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeeded)) 
		{
			GetModuleBaseName(hProcess, hMod, szProcessName, sizeof(szProcessName) / sizeof(TCHAR));
			printf("%s\n", szProcessName);
			Count = Count + 1;
		}
	}

	CloseHandle(hProcess);
}

int main() 
{
	DWORD aProcesses[1024], cbNeeded, cProcesses;
	unsigned int i;

	if (!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded))
	{
		return 1;
	}

	cProcesses = cbNeeded / sizeof(DWORD);
	
	for (i = 0; i < cProcesses; i++)
	{
		if (aProcesses[i] != 0)
		{
			PrintProcessNameAndID(aProcesses[i]);
		}
	}
	printf("\n");
	printf("Get access to %d from %d processes\n", Count, cProcesses);
	getchar();
	return 0;
}