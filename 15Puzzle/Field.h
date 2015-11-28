#pragma once

#include <array>

class Field
{
public:
	typedef std::array<std::array<int, 4>, 4> FieldType;
	static const FieldType goalState;
	explicit Field(FieldType table);
	void show() const;
private:
	FieldType m_field;
};