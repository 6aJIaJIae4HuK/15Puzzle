#include <iostream>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include <memory>

#include "Table.h"

Table::Table(Field::FieldType field) : m_startField(field), m_isSolved(false)
{

}

void Table::showTable() const
{

}

void Table::solve()
{
	m_bound = m_startField.getHeuristic();

	while (m_bound <= 100)
	{
		m_minPrev = 1000000000;
		bool found = search(m_startField, 0, m_startField);
		if (found)
		{
			std::reverse(m_solution.begin(), m_solution.end());
			return;
		}
		m_bound = m_minPrev;
	}
}

bool Table::search(Field field, int g, Field parent)
{
	//m_lookedNodes.insert(field);
	//if (m_lookedNodes.size() % 1000 == 0)
	//	std::cout << m_lookedNodes.size() << std::endl;
	int f = g + field.getHeuristic();
	if (f > m_bound)
	{
		if (m_minPrev > f)
			m_minPrev = f;
		return false;
	}
	Field::FieldType tmp = field.getField();
	if (tmp == Field::goalState)
	{
		m_isSolved = true;
		m_solution.push_back(field);
		return true;
	}
	int min = 100000000;
	int dx[4] = { -1, 1, 0, 0 };
	int dy[4] = { 0, 0, -1, 1 };
	std::pair<int, int> coords = field.getCoordsOfEmptyCell();
	for (int i = 0; i < 4; i++)
	{
		if (coords.first + dx[i] < 0 || coords.first + dx[i] > 3 ||
			coords.second + dy[i] < 0 || coords.second + dy[i] > 3)
			continue;
		std::swap(tmp[coords.first + dx[i]][coords.second + dy[i]], tmp[coords.first][coords.second]);
		if (Field(tmp) != parent)
		{
			bool found = search(Field(tmp), g + 1, field);
			if (found)
			{
				m_solution.push_back(field);
				return found;
			}
		}
		std::swap(tmp[coords.first + dx[i]][coords.second + dy[i]], tmp[coords.first][coords.second]);
	}
	return false;
}
/*
void Table::solve()
{
	std::map<Field, std::pair<int, Field>> openedNodes;
	std::map<Field, std::pair<int, Field>> closedNodes;
	openedNodes.insert(std::make_pair(m_startField, std::make_pair(0, m_startField)));
	while (!openedNodes.empty())
	{
		int f = 10000000;
		auto field = openedNodes.begin();
		for (auto it = openedNodes.begin(); it != openedNodes.end(); it++)
		{
			if (it->first.getHeuristic() + it->second.first < f)
			{
				f = it->first.getHeuristic() + it->second.first;
				field = it;
			} else
			if (it->first.getHeuristic() + it->second.first == f)
			{
				if (it->second.first > field->second.first)
				{
					f = it->first.getHeuristic() + it->second.first;
					field = it;
				}
			}
		}
		if (field->first.getField() == Field::goalState)
		{
			while (field->first != m_startField)
			{
				m_solution.push_back(field->first);
				field = closedNodes.find(field->second.second);
			}
			m_solution.push_back(field->first);
			reverse(m_solution.begin(), m_solution.end());
			m_isSolved = true;
			return;
		}
		if (closedNodes.find(field->first) == closedNodes.end())
			closedNodes.insert(std::make_pair(field->first, field->second));
		std::pair<int, int> coords = field->first.getCoordsOfEmptyCell();
		Field::FieldType tmp(field->first.getField());
		Field parent = field->first;
		int g = field->second.first;

		openedNodes.erase(field);

		int dx[4] = { -1, 1, 0, 0 };
		int dy[4] = { 0, 0, -1, 1 };

		for (int i = 0; i < 4; i++)
		{
			if (coords.first + dx[i] >= 0 && coords.first + dx[i] < 4 &&
				coords.second + dy[i] >= 0 && coords.second + dy[i] < 4)
			{
				std::swap(tmp[coords.first + dx[i]][coords.second + dy[i]], tmp[coords.first][coords.second]);
				Field tmpField(tmp);
				if (openedNodes.find(tmpField) == openedNodes.end())
				{
					int g_score = g + 1;
					auto it = openedNodes.find(tmpField);
					if (it == openedNodes.end())
					{
						openedNodes.insert(std::make_pair(tmpField, std::make_pair(g_score, parent)));
					}
					else
					{
						if (g_score < it->second.first)
						{
							it->second = std::make_pair(g_score, parent);
						}
					}
				}
				if (openedNodes.size() % 1000 == 0)
					std::cout << openedNodes.size() << ' ' << closedNodes.size() << std::endl;
				std::swap(tmp[coords.first + dx[i]][coords.second + dy[i]], tmp[coords.first][coords.second]);
			}
		}
	}
}
*/
void Table::showSolution() const
{
	if (!m_isSolved)
	{
		std::cout << "Table isn't solved yet" << std::endl;
	}
	else
	{
		std::cout << "SOLVED" << std::endl;
		for (auto it = m_solution.begin(); it != m_solution.end(); it++)
		{
			it->show();
			std::cout << std::endl;
		}
	}
}