#pragma once

#include <array>

class Field
{
public:
	typedef std::array<std::array<int, 4>, 4> FieldType;
	static const FieldType goalState;
	explicit Field(FieldType table);
	//explicit Field(unsigned long long fieldId);
	void show() const;
	bool operator<(const Field& field) const;
	bool operator!=(const Field& field) const;
	Field& operator=(const Field& field);
	FieldType getField() const;
	unsigned long long getFieldID() const;
	int getAtPos(const int& row, const int& col) const;
	int getHeuristic() const;
	std::pair<int, int> getCoordsOfEmptyCell() const;
private:
	unsigned long long m_fieldID;
	int m_heuristic;
	std::pair<int, int> m_coordsOfEmpty;
};