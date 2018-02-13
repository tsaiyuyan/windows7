#include "define.h"

class Solution_412_Fizz_Buzz :public Solution //O(n) by using hashtable
{
public:
	vector<string> fizzBuzz(int n) 
	{
		vector<string> res;
		for(int i = 1;i <= n;i++)
		{
			string foo;
			if(i%3 == 0)
			{
				foo += "Fizz";
			}
			if(i%5 == 0)
			{
				foo += "Buzz";
			}
			if(foo.length()==0)
			{
				foo += std::to_string(i);
			}
			res.push_back(foo);
		}
		return res;
	}

	int test()
	{
		vector <string> res = fizzBuzz(15);
		for_each(res.begin(),res.end(),[](string str){cout << str << endl;});

		return 0;
	}

};

/*
Write a program that outputs the string representation of numbers from 1 to n.

But for multiples of three it should output ¡§Fizz¡¨ instead of the number and for the multiples of five output ¡§Buzz¡¨. For numbers which are multiples of both three and five output ¡§FizzBuzz¡¨.

Example:

n = 15,

Return:
[
    "1",
    "2",
    "Fizz",
    "4",
    "Buzz",
    "Fizz",
    "7",
    "8",
    "Fizz",
    "Buzz",
    "11",
    "Fizz",
    "13",
    "14",
    "FizzBuzz"
]
*/