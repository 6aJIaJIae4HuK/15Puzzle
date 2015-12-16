#include <iostream>
#include <ctime>
#include <cstdlib>

#include "State.h"
#include "Table.h"


int main()
{
	freopen("res.txt", "w", stdout);
	srand(time(NULL));
	auto field = Field::goalState;
	
	int dx[4] = { -1, 1, 0, 0 };
	int dy[4] = { 0, 0, -1, 1 };
	for (int i = 0; i < 1000; i++)
	{
		std::pair<int, int> coords = std::make_pair(-1, -1);
		for (int row = 0; row < 4; row++)
		{
			for (int col = 0; col < 4; col++)
			{
				if (field[row][col] == 0)
				{
					coords = std::make_pair(row, col);
				}
			}
		}
		int dir = rand() % 4;
		while (coords.first + dx[dir] < 0 || coords.first + dx[dir] > 3 ||
			coords.second + dy[dir] < 0 || coords.second + dy[dir] > 3)
			dir = rand() % 4;
		std::swap(field[coords.first][coords.second], field[coords.first + dx[dir]][coords.second + dy[dir]]);
	}
	
	/*
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			std::cin >> field[i][j];
		}
	}
	*/
	Table table(field);
	table.solve();
	table.showSolution();
	return 0;
}