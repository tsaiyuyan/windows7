#include "define.h"

class Solution_771_Jewels_and_Stones:public Solution 
{
public:
    int numJewelsInStones(string J, string S) 
	{        
		unsigned int ret = 0;		
		std::unordered_map<char,int> umap;
		for (unsigned i=0; i<J.length(); ++i)
		{
			umap.insert( pair<char, int>( J.at(i), i));
		}

        for (unsigned i=0; i<S.length(); ++i)
		{
			if(umap.find(S.at(i)) != umap.end())
				ret ++;
		}        
        return ret;
    }
	int test()
	{	
		string J = "aA", S = "aAAbbbb";
		int ret = numJewelsInStones(J,S);
		cout << "ret : " << ret << endl;
		return 0;
	}
};
/*
You're given strings J representing the types of stones that are jewels, and S representing the stones you have.  Each character in S is a type of stone you have.  You want to know how many of the stones you have are also jewels.

The letters in J are guaranteed distinct, and all characters in J and S are letters. Letters are case sensitive, so "a" is considered a different type of stone from "A".

Example 1:

Input: J = "aA", S = "aAAbbbb"
Output: 3
Example 2:

Input: J = "z", S = "ZZ"
Output: 0
Note:

S and J will consist of letters and have length at most 50.
The characters in J are distinct.
*/

