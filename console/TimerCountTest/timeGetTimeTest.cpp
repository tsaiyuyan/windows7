#include <stdio.h>
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib,"Winmm.lib")
int timeGetTimeTest ()
{
	timeBeginPeriod(1);
	DWORD start = timeGetTime();
	Sleep(1);
	DWORD end = timeGetTime();
	printf("Sleep(1); end - start = %u\n",end - start);


	start = timeGetTime();
	Sleep(100);
	end = timeGetTime();
	printf("Sleep(100); end - start = %u\n",end - start);

	timeEndPeriod(1);
	return 0;
}


/*

The only difference between this function and the timeGetSystemTime function is that timeGetSystemTime uses the MMTIME structure to return the system time.
The timeGetTime function has less overhead than timeGetSystemTime.

Note that the value returned by the timeGetTime function is a DWORD value. 
The return value wraps around to 0 every 2^32 milliseconds, which is about 49.71 days. 
This can cause problems in code that directly uses the timeGetTime return value in computations, particularly 
where the value is used to control code execution. 
You should always use the difference between two timeGetTime return values in computations.

The default precision of the timeGetTime function can be five milliseconds or more, depending on the machine. 
You can use the timeBeginPeriod and timeEndPeriod functions to increase the precision of timeGetTime. 
If you do so, the minimum difference between successive values returned by timeGetTime can be as large as the minimum
period value set using timeBeginPeriod and timeEndPeriod. 

Use the QueryPerformanceCounter and QueryPerformanceFrequency functions to measure short time intervals at a high resolution.
*/