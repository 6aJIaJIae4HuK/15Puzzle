#include <iostream>
#include <ctime>
#include <cstdlib>

#include "State.h"
#include "Table.h"


int main()
{
	freopen("res.txt", "w", stdout);
	srand(time(NULL));
	Field::FieldType field{ { {4,13,3,15},{14,10,9,6},{5,12,0,1},{8,7,2,11} } };
	/*
	for (int i = 0; i < 16; i++)
	{
		field[i / 4][i % 4] = i;
	}


	for (int i = 1; i <= 16; i++)
	{
		int j = (rand() % i) + 1;
		std::swap(field[(i - 1) / 4][(i - 1) % 4], field[(j - 1) / 4][(j - 1) % 4]);
	}
	*/
	Table table(field);
	table.solve();
	table.showSolution();
	return 0;
}