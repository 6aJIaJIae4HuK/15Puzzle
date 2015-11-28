#include <iostream>

#include "State.h"
#include "Table.h"

int main()
{
	Field::FieldType field;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			std::cin >> field[i][j];
		}
	}
	Table table(field);
	table.solve();
	table.showSolution();
	return 0;
}