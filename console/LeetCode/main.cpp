#include <stdio.h>
#include <stdlib.h>
#include "SolutionList.h"

int main()
{
	Solution *sol = new Solution_980_Unique_Paths_III;
	sol->test();
	//sol.limit_test();
	delete sol;
	system("pause");
	return 0;
}