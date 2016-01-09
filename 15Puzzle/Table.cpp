#include <iostream>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include <memory>
#include <ctime>
#include <omp.h>

#include "Table.h"

std::map<Field, Field> Table::m_parent;

Table::Table(Field::FieldType field) : m_startField(field), m_isSolved(false)
{

}

void Table::showTable() const
{

}

void Table::solve()
{
	if (!isSolvable())
		return;
	clock_t t1 = clock();
	unsigned long long masks[9] =
	{
		0x0000000000000000ll,
		0x1000000000000000ll,
		0x1200000000000000ll,
		0x1230000000000000ll,
		0x1230000400000000ll,
		0x1234000000000000ll,
		0x1234500000000000ll,
		0x1234560000000000ll,
		0x123456789ABCDEF0ll
	};
	Field field = m_startField;
	for (int i = 1; i < 9; i++)
	{
		field = searchForMask(field, masks[(i == 5 ? i - 3 : i - 1)], masks[i]);
	}

	while (field != m_startField)
	{
		m_solution.push_back(field);
		field = m_parent.at(field);
	}
	m_solution.push_back(m_startField);
	std::reverse(m_solution.begin(), m_solution.end());
	m_isSolved = true;
	clock_t t2 = clock();
	printf("%.3lf seconds\n", double(t2 - t1) / 1000);
}

bool Table::isSolvable() const
{
	int inv = 0;
	for (int i = 0; i < 16; i++)
	{
		if (m_startField.getAtPos(i / 4, i % 4) != 0)
		{
			for (int j = 0; j < i; j++)
			{
				if (m_startField.getAtPos(j / 4, j % 4) > m_startField.getAtPos(i / 4, i % 4))
				{
					inv++;
				}
			}
		}
	}

	for (int i = 0; i < 16; i++)
	{
		if (m_startField.getAtPos(i / 4, i % 4) == 0)
		{
			inv += (i / 4 + 1);
		}
	}

	return (inv & 1) ? false : true;
}

Field Table::searchForMask(const Field& field, const unsigned long long& prevMask, const unsigned long long& mask)
{
	std::queue<Field> q;
	q.push(field);
	if (m_parent.find(field) == m_parent.end())
		m_parent.insert(std::make_pair(field, field));

	//omp_lock_t lock;
	//omp_init_lock(&lock);


	while (!q.empty())
	{
		Field f = q.front();
		q.pop();
		if (f.match(mask))
			return f;

		const int dx[4] = { -1, 1, 0, 0 };
		const int dy[4] = { 0, 0, -1, 1 };

		auto tmp = f.getField();
		auto coords = f.getCoordsOfEmptyCell();

		//#pragma omp parallel for private(tmp) shared(coords, f, q, m_parent)
		for (int i = 0; i < 4; i++)
		{
			tmp = f.getField();
			if (coords.first + dx[i] >= 0 && coords.first + dx[i] < 4 &&
				coords.second + dy[i] >= 0 && coords.second + dy[i] < 4)
			{

				std::swap(tmp[coords.first + dx[i]][coords.second + dy[i]], tmp[coords.first][coords.second]);
				Field tmpField(tmp);

				if (tmpField.match(prevMask) && m_parent.find(tmpField) == m_parent.end())
				{
					//omp_set_lock(&lock);
					m_parent.insert(std::make_pair(tmpField, f));
					q.push(tmpField);
					//omp_unset_lock(&lock);
				}

				std::swap(tmp[coords.first + dx[i]][coords.second + dy[i]], tmp[coords.first][coords.second]);
			}
		}
	}

	//omp_destroy_lock(&lock);
}

void Table::showSolution() const
{
	if (m_isSolved)
	{
		for (auto it = m_solution.begin(); it != m_solution.end(); it++)
		{
			it->show();
			std::cout << std::endl;
		}
	}
	else
	{
		std::cout << "Not solvable!!!" << std::endl;
	}
}