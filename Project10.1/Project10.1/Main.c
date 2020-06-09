#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <locale.h>


int main()
{
	setlocale(LC_ALL, "RUS");
	HANDLE handle;
	DWORD result;

	handle = CreateMutex(NULL, TRUE, "MutexOfTheMyApplication");
	result = WaitForSingleObject(handle, NULL);

	if (result != WAIT_OBJECT_0)
	{
		printf("Программа уже запущена!\n");
		system("pause");
		return 0;
	}
	else
	{
		printf("Программа работает...\n");
	}
	_getche();
}