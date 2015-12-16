#include <iostream>
#include <iomanip>

#include "Field.h"

const Field::FieldType 
Field::goalState{ { { 1, 2, 3, 4 },{ 5, 6, 7, 8 },{ 9, 10, 11, 12 },{ 13, 14, 15, 0 } } };

Field::Field(Field::FieldType field) : m_fieldID(0), m_heuristic(0)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (field[i][j] > 0)
				m_heuristic += (std::abs(i - (field[i][j] - 1) / 4) + std::abs(j - (field[i][j] - 1) % 4));
			else
				m_coordsOfEmpty = std::make_pair(i, j);
			m_fieldID |= ((unsigned long long(field[i][j] & 0xFF)) << (4 * (15 - (4 * i + j))));
		}
	}
	
}
/*
Field::Field(unsigned long long fieldID) : m_fieldID(fieldID)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			int n = getAtPos(i, j);
			if (n > 0)
				m_mnh += (std::abs(i - (n - 1) / 4) + std::abs(j - (n - 1) % 4));
			else
				m_coordsOfEmpty = std::make_pair(i, j);
		}
	}
}
*/
void Field::show() const
{
	FieldType f = getField();
	std::cout.width(3);
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			std::cout << std::setw(3) << f[i][j];
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

Field::FieldType Field::getField() const
{
	FieldType res;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			res[i][j] = getAtPos(i, j);
		}
	}
	return res;
}

bool Field::operator<(const Field& field) const
{
	return m_fieldID < field.getFieldID();
}

bool Field::operator!=(const Field& field) const
{
	return m_fieldID != field.getFieldID();
}

Field& Field::operator=(const Field& field)
{
	m_fieldID = field.getFieldID();
	return *this;
}

unsigned long long Field::getFieldID() const
{
	return m_fieldID;
}

int Field::getAtPos(const int& row, const int& col) const
{
	return (m_fieldID >> (4 * (15 - 4 * row - col))) & 0x0F;
}

int Field::getHeuristic() const
{
	return m_heuristic;
}

std::pair<int, int> Field::getCoordsOfEmptyCell() const
{
	return m_coordsOfEmpty;
}