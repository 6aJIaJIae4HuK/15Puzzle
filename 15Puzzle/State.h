#pragma once

#include "Field.h"

class State
{
public:
	explicit State(Field::FieldType field);
	State(const State& state);
	State& operator=(const State& state);
	bool operator==(const State& state) const;
	bool operator!=(const State& state) const;
	bool operator<(const State& state) const;
	int getFunction() const;
	Field getField() const;
	void setLength(const int& length);
	std::pair<int, int> getCoordsOfEmptyCell() const;
	int getG() const;
private:
	Field m_field;
	int m_g;
	int m_h;
	int m_col;
	int m_row;
};