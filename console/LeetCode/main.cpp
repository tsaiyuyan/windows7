#include <stdio.h>
#include <stdlib.h>
#include "SolutionList.h"

class Solution_848_Shifting_Letters : public Solution
{
public:
	string shiftingLetters(string S, vector<int>& shifts)
	{
		int offset = 0;
		for (int i = shifts.size() - 1; i >= 0; i--)
		{	
			int tmp = shifts[i];
			shifts[i] += offset;
			offset += tmp;
		}

		for (int i = 0; i < S.size(); i++)
		{
			S[i] = ((S[i] - 'a') + shifts[i]) % 26 + 'a';
		}

		return S;

	}
	int test()
	{
		vector<int> shifts = { 3, 5, 9 };	
		string res = shiftingLetters(string("abc"), shifts);
		cout << res << endl;
		return 0;
	}

};

class Solution_680_Valid_Palindrome_II : public Solution
{
public:
	bool validPalindrome(string s)
	{
		int f = 0;
		int l = s.size() - 1;
		int  chance = 0;
		int save_f, save_l;
		while (f < l)
		{
			if (s[f] != s[l])
			{
				if (chance == 0)
				{
					save_f = f++;
					save_l = l - 1;

				}
				else if (chance == 1)
				{
					f = save_f;
					l = save_l;
					chance++;
				}
				chance++;
				if (chance == 2)
					return false;
			}
			else
			{
				f++;
				l--;
			}
		}
		return true;
	}
	int test()
	{
		bool res = validPalindrome(string("aguokepatgbnvfqmgmlcupuufxoohdfpgjdmysgvhmvffcnqxjjxqncffvmhvgsymdjgpfdhooxfuupuculmgmqfvnbgtapekouga"));
		cout << res << endl;
		return 0;
	}

};


class Solution_125_Valid_Palindrome : public Solution
{
public:
	char easytolower(char in) {
		if (in <= 'Z' && in >= 'A')
			return in - ('Z' - 'z');
		return in;
	}
	bool isPalindrome(string s)
	{
		int f = 0;
		int l = s.size() - 1;
		while (f < l)
		{
			if (!isalnum(s[f]))
			{
				f++;
				continue;
			}

			if (!isalnum(s[l]))
			{
				l--;
				continue;
			}

			if (easytolower(s[f]) != easytolower(s[l]))
				return false;

			f++; l--;
		}
		return true;
	}
	int test()
	{
		bool res = isPalindrome(string("race a car"));//"race a car""0P"
		cout << res << endl;
		return 0;
	}

};
int main()
{
	Solution *sol = new Solution_125_Valid_Palindrome;
	sol->test();
	//sol.limit_test();
	delete sol;
	system("pause");
	return 0;
}