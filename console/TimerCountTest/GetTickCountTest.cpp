#include <stdio.h>
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib,"Winmm.lib")

int GetTickCountTest()  //time Begin Period 無效 最低為16ms
{
	timeBeginPeriod(1);
	DWORD t1, t2;
    t1 = GetTickCount();
    Sleep(10);
    t2 = GetTickCount();
    printf("Sleep(10); Lasting Time: %lf\n",(t2-t1)/1000.0);

	t1 = GetTickCount();
    Sleep(1);
    t2 = GetTickCount();
    printf("Sleep(1); Lasting Time: %lf\n",(t2-t1)/1000.0);
	timeEndPeriod(1);
    return 0;
}

/*
改函数测试时间的精度是 10~16 ms，所以，

如果你两次调用 GetTickCount() 之间的工作如果在 16 ms 内完成，那么返回的时间差就有可能为 0

*/