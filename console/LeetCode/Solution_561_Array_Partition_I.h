class Solution_561_Array_Partition_I:public Solution   //O(n) by using hashtable
{
public:
	int arrayPairSumbyUsingSort(vector<int>& nums) 
	{
		int ret = 0;
		
		// 當如果input的數組量太大時sort 應該會排序過久 所以這邊改成使用 hashtable 來實作
		sort(nums.begin(), nums.end(),less<int>());
		assert (nums.size()%2 == 0);
		for(size_t i = 0; i <nums.size();i+=2)
		{
			ret += min(nums[i],nums[i+1]);		

		}
		return ret;
	
	}
    int arrayPairSum(vector<int>& nums) 
    {
		int ret = 0;
		
		// 當如果input的數組量太大時sort 應該會排序過久 所以這邊改成使用 hashtable 來實作
		sort(nums.begin(), nums.end(),less<int>());
		assert (nums.size()%2 == 0);
		for(size_t i = 0; i < nums.size();i+=2)
		{
			ret += min(nums[i],nums[i+1]);		

		}
		return ret;
        

		vector<int> hashtable(20001,0);  // All the integers in the array will be in the range of [-10000, 10000].
		
		for(const auto n:nums)
		{
			hashtable[n + 10000] ++;		
		}
		bool flag = true;
		for(size_t i =0 ;i< hashtable.size();)
		{
			if(hashtable[i] > 0 )
			{
				if(flag) 
				{
					flag = false;
					ret += (i - 10000);
                    hashtable[i]--;
				}else
				{
					flag = true;
					hashtable[i]--;
				}			
			}else
				i++;
		}
		return ret;
    }
	int test()
	{	
		int arr[4] = {1,4,2,3};

		vector<int> vec;

		size_t size = sizeof(arr) / sizeof(int);
		vec.resize(size);
		std::copy(arr, arr + size ,vec.begin());
				
		int ret = arrayPairSum(vec);
		cout << "ret : " << ret << endl;
		return 0;
	}
	int limit_test()
	{	
		timeBeginPeriod(1);
		srand(timeGetTime());
		
		int arr[20000] = {0};
		size_t size = sizeof(arr) / sizeof(int);
		for(size_t i =0 ; i < size ; i++)
		{			
			arr[i] = (int)i - 10000; 			
		}

		for(size_t i =0 ; i < (size_t) rand() %10000 + 10000 ; i++)
		{
			size_t pos = rand() % size;
			//swap
			arr[i]^=arr[pos];
			arr[pos]^=arr[i];
			arr[i]^=arr[pos];			
		}


		vector<int> vec;
		vec.resize(size);
		std::copy(arr, arr + size ,vec.begin());
		int ret = 0;
		DWORD start = 0,end = 0;
		
		start = timeGetTime();
		ret = arrayPairSum(vec);
		end = timeGetTime();		
		cout << "arrayPairSum(vec); ret : "<< ret << " time = "<< end - start <<" ms"<< endl;

		start = timeGetTime();
		ret = arrayPairSumbyUsingSort(vec);
		end = timeGetTime();	
		cout << "arrayPairSumbyUsingSort ret : "<< ret << " time = "<< end - start <<" ms"<< endl;

			
		timeEndPeriod(1);
		return 0;
	}
};
/*
Given an array of 2n integers, your task is to group these integers into n pairs of integer, say (a1, b1), (a2, b2), ..., (an, bn) which makes sum of min(ai, bi) for all i from 1 to n as large as possible.

Example 1:
Input: [1,4,3,2]

Output: 4
Explanation: n is 2, and the maximum sum of pairs is 4 = min(1, 2) + min(3, 4).
Note:
n is a positive integer, which is in the range of [1, 10000].
All the integers in the array will be in the range of [-10000, 10000].
*/


