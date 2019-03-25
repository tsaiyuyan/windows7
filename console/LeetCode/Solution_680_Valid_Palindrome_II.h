#pragma once

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
