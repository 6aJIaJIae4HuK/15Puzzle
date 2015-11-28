#pragma once

#include "Field.h"

class State
{
public:
	explicit State(Field::FieldType field);
private:
	Field m_field;
};