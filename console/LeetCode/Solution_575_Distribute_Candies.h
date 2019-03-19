#include "define.h"

class Solution_575_Distribute_Candies : public Solution
{
public:
	int distributeCandies(vector<int>& candies) 
	{
        bitset<2000001> hash_table;
		/*
Construct bitset
Constructs a bitset container object:
(1) default constructor
The object is initialized with zeros.   <=========== key point
(2) initialization from integer value
Initializes the object with the bit values of val:
(3) initialization from string or (4) C-string
Uses the sequence of zeros and/or ones in str to initialize the first n bit positions of the constructed bitset object.	
		*/
		unsigned int kinds_count = 0;
			
		for (auto i : candies)
		{			
			if(!hash_table[i+100000])
			{
				hash_table.set(i+100000);
				kinds_count++;
			}
		}
		
		return min(kinds_count, candies.size() / 2);
    }
	int test()
	{
		int arr[4] = {1,1,2,3};
		size_t size = sizeof(arr) / sizeof(int);
		vector<int> vec;		
		vec.resize(size);
		std::copy(arr, arr + size ,vec.begin());
		
		cout << "output:"<< distributeCandies(vec) <<endl;
		return 0;
	}
};

/*
Given an integer array with even length, where different numbers in this array represent different kinds of candies. Each number means one candy of the corresponding kind. You need to distribute these candies equally in number to brother and sister. Return the maximum number of kinds of candies the sister could gain.
Example 1:
Input: candies = [1,1,2,2,3,3]
Output: 3
Explanation:
There are three different kinds of candies (1, 2 and 3), and two candies for each kind.
Optimal distribution: The sister has candies [1,2,3] and the brother has candies [1,2,3], too. 
The sister has three different kinds of candies. 
Example 2:
Input: candies = [1,1,2,3]
Output: 2
Explanation: For example, the sister has candies [2,3] and the brother has candies [1,1]. 
The sister has two different kinds of candies, the brother has only one kind of candies. 
Note:

The length of the given array is in range [2, 10,000], and will be even.
The number in given array is in range [-100,000, 100,000].

*/