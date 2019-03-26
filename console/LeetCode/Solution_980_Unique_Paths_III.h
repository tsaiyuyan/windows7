#pragma once

class Solution_980_Unique_Paths_III : public Solution
{
public:

	bool IsAllPassed(vector<vector<int>> grid)
	{
		for (int i = 0; i < grid.size(); i++)
		{
			for (int j = 0; j < grid[i].size(); j++)
			{
				if (grid[i][j] == 0)
					return false;
			}
		}
		return true;
	}
	bool IsValid(int x, int y, int x_max, int y_max)
	{
		if (x >= 0 && x < x_max && y >= 0 && y < y_max)
		{
			return true;
		}
		return false;
	}

	void DFS(int &paths_num, vector<vector<int>> grid, int x, int y)
	{
		const int steps[4][2] = { { 1,0 },{ 0,1 },{ -1,0 },{ 0,-1 } };


		grid[x][y] = -1;

		for (int i = 0; i < 4; i++)
		{
			int next_x = x + steps[i][0];
			int next_y = y + steps[i][1];
			if (IsValid(next_x, next_y, grid.size(), grid[0].size()))
			{
				printf(" (%d %d) -> (%d %d) = %d\n", x, y, next_x, next_y, grid[next_x][next_y]);
				if (grid[next_x][next_y] == -1)
				{
					//continue;
				}
				else if (grid[next_x][next_y] == 0)
				{
					DFS(paths_num, grid, next_x, next_y);
				}
				else if (grid[next_x][next_y] == 2)
				{
					if (IsAllPassed(grid))
						paths_num++;
				}
			}
		}
	}

	int uniquePathsIII(vector<vector<int>>& grid) {
		int start_x = 0;
		int start_y = 0;
		int paths_num = 0;

		//find start point
		for (int i = 0; i < grid.size(); i++)
		{
			for (int j = 0; j < grid[i].size(); j++)
			{
				if (grid[i][j] == 1)
				{
					start_x = i;
					start_y = j;
					break;
				}
			}
		}
		DFS(paths_num, grid, start_x, start_y);

		return paths_num;
	}
	int test()
	{
		vector<vector<int>> grid = { { 1,0,0,0 },{ 0,0,0,0 },{ 0,0,2,-1 } };

		auto res = uniquePathsIII(grid);
		cout << res << endl;
		return 0;
	}
};