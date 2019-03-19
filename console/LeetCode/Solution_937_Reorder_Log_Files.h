#pragma once
#include "define.h"

class Solution_937_Reorder_Log_Files :public Solution
{
public:

	static bool compare(string s1, string s2)
	{
		s1.erase(0, 0 + s1.find(' '));
		s2.erase(0, 0 + s2.find(' '));

		for (int i = 0; i < s1.length() && i <s2.length(); i++)
		{
			if (s2[i] > s1[i])
				return true;
			else if (s2[i] < s1[i])
				return false;
		}
		return false;
	}
	vector<string> reorderLogFiles(vector<string>& logs)
	{
		vector<string> output;
		output.resize(logs.size());

		int l = logs.size() - 1;
		int f = 0;

		for (int i = logs.size() - 1; i >= 0; i--)
		{
			if (isalpha(logs[i][logs[i].length() - 1]))
			{
				output[f++] = logs[i];
			}
			else
			{
				output[l--] = logs[i];
			}
		}
		sort(output.begin(), output.begin() + f, compare);
		return output;
	}
	//["a1 9 2 3 1","g1 act car","zo4 4 7","ab1 off key dog","a8 act zoo"]
	int test()
	{
		vector <string> input;
		input.emplace_back(string("a1 9 2 3 1"));
		input.emplace_back(string("g1 act car"));
		input.emplace_back(string("zo4 4 7"));
		input.emplace_back(string("ab1 off key dog"));
		input.emplace_back(string("a8 act zoo"));
		vector <string> output = reorderLogFiles(input);

		for_each(output.begin(), output.end(), [](string str) {cout << str << endl; });
		return 0;
	}
};
