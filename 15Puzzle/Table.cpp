#include <iostream>
#include <queue>
#include <set>

#include "Table.h"

Table::Table(Field::FieldType field) : m_state(field), m_isSolved(false)
{

}

void Table::showTable() const
{

}

void Table::solve()
{
	std::set<State> closed;
	std::set<State> opened;
	opened.insert(m_state);
	while (!opened.empty())
	{
		State state = *opened.rbegin();
		if (state.getField().getField() == Field::goalState)
		{
			std::cout << closed.size() << ' ' << opened.size() << std::endl;
			m_isSolved = true;
			return;
		}
		closed.insert(state);
		std::pair<int, int> coords = state.getCoordsOfEmptyCell();
		Field::FieldType tmp(state.getField().getField());
		opened.erase(state);

		int dx[4] = { -1, 1, 0, 0 };
		int dy[4] = { 0, 0, -1, 1 };

		for (int i = 0; i < 4; i++)
		{
			if (coords.first + dx[i] >= 0 && coords.first + dx[i] < 4 &&
				coords.second + dy[i] >= 0 && coords.second + dy[i] < 4)
			{
				std::swap(tmp[coords.first + dx[i]][coords.second + dy[i]], tmp[coords.first][coords.second]);
				State tmpState(tmp);
				if (closed.find(tmpState) == closed.end())
				{
					int g_score = 1 + state.getG();
					if (opened.find(tmpState) == opened.end())
					{
						tmpState.setLength(g_score);
						opened.insert(tmpState);
					}
					else
					{
						if (g_score < tmpState.getG())
						{
							opened.erase(tmpState);
							tmpState.setLength(g_score);
							opened.insert(tmpState);
						}
					}
				}
				std::swap(tmp[coords.first + dx[i]][coords.second + dy[i]], tmp[coords.first][coords.second]);
			}
		}
	}
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