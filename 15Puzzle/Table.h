#pragma once

#include <vector>
#include <set>
#include <map>

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
	bool isSolvable() const;
	Field searchForMask(const Field& start, const unsigned long long& prevMask, const unsigned long long& mask);
	Field m_startField;
	bool m_isSolved;
	int m_minPrev;
	int m_bound;
	std::vector<Field> m_solution;
	static std::map<Field, Field> m_parent;
	//std::set<Field> m_lookedNodes;
};