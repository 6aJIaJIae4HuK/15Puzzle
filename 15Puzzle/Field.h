#pragma once

#include <array>

class Field
{
public:
	typedef std::array<std::array<int, 4>, 4> FieldType;
	explicit Field(FieldType table);
	//explicit Field(unsigned long long fieldId);
	Field(const Field& field);
	void show() const;
	bool operator<(const Field& field) const;
	bool operator!=(const Field& field) const;
	Field& operator=(const Field& field);
	FieldType getField() const;
	unsigned long long getFieldID() const;
	int getAtPos(const int& row, const int& col) const;
	std::pair<int, int> getCoordsOfEmptyCell() const;
	bool match(const unsigned long long& mask) const;
private:
	unsigned long long m_fieldID;
	std::pair<int, int> m_coordsOfEmpty;
};