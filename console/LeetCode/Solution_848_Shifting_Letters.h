#pragma once
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