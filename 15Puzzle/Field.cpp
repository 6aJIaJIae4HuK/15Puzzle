#include <iostream>
#include <iomanip>
//#include <omp.h>

#include "Field.h"


Field::Field(Field::FieldType field) : m_fieldID(0)
{
	unsigned long long res = 0;
	//std::pair<int, int> coords;
	//#pragma omp parallel for reduction(|:res)
	for (int i = 0; i < 16; i++)
	{
		res |= ((unsigned long long(field[i / 4][i % 4] & 0xFF)) << (4 * (15 - i)));
	}
	
	for (int i = 0; i < 16; i++)
	{
		if (field[i / 4][i % 4] == 0)
			m_coordsOfEmpty = std::make_pair(i / 4, i % 4);
	}

	m_fieldID = res;
}


Field::Field(const Field& field) : m_fieldID(field.getFieldID()),
								   m_coordsOfEmpty(field.getCoordsOfEmptyCell())
{

}

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
	//#pragma omp parallel for shared(res) 
	for (int i = 0; i < 16; i++)
	{
		res[i / 4][i % 4] = getAtPos(i / 4, i % 4);
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
	m_coordsOfEmpty = field.getCoordsOfEmptyCell();
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

std::pair<int, int> Field::getCoordsOfEmptyCell() const
{
	return m_coordsOfEmpty;
}

bool Field::match(const unsigned long long& mask) const
{
	bool res = true;
	for (int i = 0; i < 4 && res; i++)
	{
		for (int j = 0; j < 4 && res; j++)
		{
			int num = (mask >> (4 * (15 - (4 * i + j)))) & 0x0F;
			if (num > 0 && getAtPos(i, j) != num)
				res = false;
		}
	}
	return res;
}