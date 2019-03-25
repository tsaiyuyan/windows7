#pragma once
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