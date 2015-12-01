#include "Field.h"

const Field::FieldType 
Field::goalState{ { { 1, 2, 3, 4 },{ 5, 6, 7, 8 },{ 9, 10, 11, 12 },{ 13, 14, 15, 0 } } };

Field::Field(Field::FieldType field) : m_field(field)
{

}

void Field::show() const
{

}

Field::FieldType Field::getField() const
{
	return m_field;
}

bool Field::operator<(const Field& field) const
{
	return m_field < field.getField();
}