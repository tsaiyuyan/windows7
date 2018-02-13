在做效能分析時，最好的方式應是從演算法著手。若演算法都大同小異，
接著還要強迫效能提昇，有人建議看 machine code，但不會看 machine code 的話，
也只能從實際的測時著手，故計時器在此便顯得重要，本篇文章便提出一些計時的方法與說明。

1. time ：
精度只到秒，這應是最不準的計時器。

2. clock：
精度為 1/CLOCKS_PER_SEC，大多系統 CLK_TCK 為 1000，故精度為毫秒。

3. GetTickCount：
呼叫此函式時，將傳回從系統開機至當時經過多少毫秒，由於傳回值為DWORD，故最多約可計時 49.7 天。

4. timeGetTime: 
此函式與 GetTickCount　解釋並無不同，但有一說 timeGetTime 精度較 GetTickCount 高，也有一說此函式實際精度只到 50ms，待查證。

5. QueryPerformanceCount / QueryPerformanceFrequency：
這應是目前精度最高之函式，精度達微秒，但在 MSDN 上亦註明，此函式若硬體不支援，將只傳回 1000，
再用 GetTickCount 代替它 (如果我沒意會錯的話應為如此)。使用此函式時將較耗資源。

6. GetSystemTimeAsFileTime (20131230 新增) ：
這方法較少見。FILETIME 結構體為兩個 32 位元之 unsigned integer，一個是 high , 一個是 low，
所代表意義為，從 1601 年 1 月 1 日至現在時間經過了多少個 (100 ns)。精度與準度待查證。

7. inline _asm：
此法見於「Windows圖形編程」，並有特定之硬體規格方可實現，也由於手邊之軟硬體均不支均，於此便不展示。
據表示，此法最高精度相依於硬體 (CPU 時脈率，換而言之，可達奈秒)，實際上仍需查證。

1. time 計時

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    time_t t1, t2; // typedef time_t long;
    t1 = time(NULL);
    Sleep(1234);
    t2 = time(NULL);
    printf("%ld secs\n", t2-t1);
    return 0;
}
輸出：1 secs

2. clock 計時

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{    
    clock_t t1, t2;
    t1 = clock();
    Sleep(1234);
    t2 = clock();
    printf("%lf\n", (t2-t1)/(double)(CLOCKS_PER_SEC));
    return 0;
}
 輸出：1.234000 secs

3. GetTickCount() 計時：

#include <windows.h>
#include <stdio.h>

int main()
{    
    DWORD t1, t2;
    t1 = GetTickCount();
    Sleep(1234);
    t2 = GetTickCount();
    printf("Lasting Time: %lf\n",(t2-t1)/1000.0);
    return 0;
}
  輸出：1.235000 secs

4. timeGetTime:

#pragma comment(lib, "Winmm.lib")
#include <windows.h>
#include <stdio.h>

int main()
{    
    DWORD t1, t2;
    t1 = timeGetTime();
    Sleep(1234);
    t2 = timeGetTime();
    printf("Lasting Time: %lf\n",(t2-t1)/1000.0);
    return 0;
}
 

輸出：1.235000 secs

5. QueryPerformanceCount / QueryPerformanceFrequency：

#include <windows.h>
#include <stdio.h>

int main()
{    
    LARGE_INTEGER t1, t2, ts;
    QueryPerformanceFrequency(&ts);
    QueryPerformanceCounter(&t1);
    Sleep(1234);
    QueryPerformanceCounter(&t2);
    printf("Lasting Time: %lf\n",(t2.QuadPart-t1.QuadPart)/(double)(ts.QuadPart));
    return 0;
}
輸出：1.234009 secs

 

 

6. GetSystemTimeAsFileTime 計時

#include <cstdio>
#include <WINDOWS.H>
 
int main()
{
	FILETIME	ftBeg, ftEnd;
	GetSystemTimeAsFileTime(&ftBeg);
	Sleep(1234) ;
	GetSystemTimeAsFileTime(&ftEnd);
	printf("%lf secs \n", (ftEnd.dwLowDateTime - ftBeg.dwLowDateTime) * 1E-7);
	return 0;
}

輸出：1.234375 secs