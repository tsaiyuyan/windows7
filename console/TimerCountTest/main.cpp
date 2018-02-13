#include <stdlib.h>
#include <stdio.h>
extern int QueryPerformanceCounterTest();
extern int timeGetTimeTest();
extern int ftimeTest();
extern int GetTickCountTest();

#ifdef _MSC_VER >= 1900 
extern int std_cronoTest();
#endif
int main (int argc,char *argv[])
{
	printf("QueryPerformanceCounterTest()\n");
	QueryPerformanceCounterTest();

	printf("\nGetTickCountTest\n");
	GetTickCountTest();

	printf("\nftimeTest()\n");
	ftimeTest();

	printf("\ntimeGetTimeTest()\n");
	timeGetTimeTest();

	//need (since C++17)
	printf("\nstd_cronoTest\n");
	std_cronoTest();

	system("pause");
	return 0;
}
