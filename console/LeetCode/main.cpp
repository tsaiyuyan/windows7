#include <stdio.h>
#include <stdlib.h>
#include "SolutionList.h"

int main()
{
	Solution *sol = new Solution_575_Distribute_Candies;
	sol->test();
	//sol.limit_test();
	delete sol;
	system("pause");
	return 0;
}