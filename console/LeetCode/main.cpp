#include <stdio.h>
#include <stdlib.h>
#include "SolutionList.h"

int main()
{
	Solution *sol = new Solution_1008_Construct_Binary_Search_Tree_from_Preorder_Traversal;
	sol->test();
	//sol.limit_test();
	delete sol;
	system("pause");
	return 0;
}