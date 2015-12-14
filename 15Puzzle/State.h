#pragma once

#include <memory>

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

	int getG() const;
	void setG(const int& g);
	
	std::shared_ptr<State> getParent() const;
	void setParent(const State& parent);

	std::pair<int, int> getCoordsOfEmptyCell() const;
private:
	Field m_field;
	int m_g;
	int m_h;
	int m_col;
	int m_row;
	std::shared_ptr<State> m_parent;
};