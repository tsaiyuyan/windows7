�b���į���R�ɡA�̦n���覡���O�q�t��k�ۤ�C�Y�t��k���j�P�p���A
�����٭n�j���įണ�@�A���H��ĳ�� machine code�A�����|�� machine code ���ܡA
�]�u��q��ڪ����ɵۤ�A�G�p�ɾ��b���K��o���n�A���g�峹�K���X�@�ǭp�ɪ���k�P�����C

1. time �G
��ץu���A�o���O�̤��Ǫ��p�ɾ��C

2. clock�G
��׬� 1/CLOCKS_PER_SEC�A�j�h�t�� CLK_TCK �� 1000�A�G��׬��@��C

3. GetTickCount�G
�I�s���禡�ɡA�N�Ǧ^�q�t�ζ}���ܷ�ɸg�L�h�ֲ@��A�ѩ�Ǧ^�Ȭ�DWORD�A�G�̦h���i�p�� 49.7 �ѡC

4. timeGetTime: 
���禡�P GetTickCount�@�����õL���P�A�����@�� timeGetTime ��׸� GetTickCount ���A�]���@�����禡��ں�ץu�� 50ms�A�ݬd�ҡC

5. QueryPerformanceCount / QueryPerformanceFrequency�G
�o���O�ثe��׳̰����禡�A��׹F�L��A���b MSDN �W������A���禡�Y�w�餣�䴩�A�N�u�Ǧ^ 1000�A
�A�� GetTickCount �N���� (�p�G�ڨS�N�|�����������p��)�C�ϥΦ��禡�ɱN���Ӹ귽�C

6. GetSystemTimeAsFileTime (20131230 �s�W) �G
�o��k���֨��CFILETIME ���c�鬰��� 32 �줸�� unsigned integer�A�@�ӬO high , �@�ӬO low�A
�ҥN��N�q���A�q 1601 �~ 1 �� 1 ��ܲ{�b�ɶ��g�L�F�h�֭� (100 ns)�C��׻P�ǫ׫ݬd�ҡC

7. inline _asm�G
���k����uWindows�ϧνs�{�v�A�æ��S�w���w��W���i��{�A�]�ѩ���䤧�n�w�駡���䧡�A�󦹫K���i�ܡC
�ڪ�ܡA���k�̰���׬̩ۨ�w�� (CPU �ɯ߲v�A���Ө����A�i�F�`��)�A��ڤW���ݬd�ҡC

1. time �p��

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
��X�G1 secs

2. clock �p��

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
 ��X�G1.234000 secs

3. GetTickCount() �p�ɡG

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
  ��X�G1.235000 secs

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
 

��X�G1.235000 secs

5. QueryPerformanceCount / QueryPerformanceFrequency�G

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
��X�G1.234009 secs

 

 

6. GetSystemTimeAsFileTime �p��

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

��X�G1.234375 secs