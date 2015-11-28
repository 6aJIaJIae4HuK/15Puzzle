#include <iostream>

#include "Table.h"

Table::Table(Field::FieldType field) : m_state(field), m_isSolved(false)
{

}

void Table::showTable() const
{

}

void Table::solve()
{

}

void Table::showSolution() const
{
	if (!m_isSolved)
	{
		std::cout << "Table isn't solved yet" << std::endl;
	}
	else
	{
		for (auto it = m_solution.begin(); it != m_solution.end(); it++)
		{
			it->show();
			std::cout << std::endl;
		}
	}
}