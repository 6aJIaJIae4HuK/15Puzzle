#pragma once

#include <vector>
#include "State.h"
#include "Field.h"

class Table
{
public:
	explicit Table(Field::FieldType field);
	void showTable() const;
	void solve();
	void showSolution() const;
private:
	State m_state;
	bool m_isSolved;
	std::vector<Field> m_solution;
};