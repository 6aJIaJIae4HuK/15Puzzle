#pragma once

#include <vector>
#include <set>

#include "State.h"
#include "Field.h"

class Table
{
public:
	explicit Table(Field::FieldType field);
	void showTable() const;
	void solve();
	void ida();
	void showSolution() const;
private:
	bool search(Field field, int g, Field parent);
	Field m_startField;
	bool m_isSolved;
	int m_minPrev;
	int m_bound;
	std::vector<Field> m_solution;
	//std::set<Field> m_lookedNodes;
};