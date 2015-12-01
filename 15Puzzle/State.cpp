#include "State.h"

State::State(Field::FieldType field) : m_field(field), m_g(0), m_h(0)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			int n = m_field.getField()[i][j];
			if (n != 0)
			{
				m_h += (std::abs(i - (n - 1) / 4) + std::abs(j - (n - 1) % 4));
			}
			else
			{
				m_row = i;
				m_col = j;
			}
		}
	}
}

State::State(const State& state) : State::State(state.getField().getField())
{
	setLength(state.getG());
}

State& State::operator=(const State& state)
{
	*this = State(state.getField().getField());
	this->setLength(state.getG());
	return *this;
}

int State::getG() const
{
	return m_g;
}

int State::getFunction() const
{
	return m_h + m_g;
}

bool State::operator!=(const State& state) const
{
	return getField().getField() != state.getField().getField();
}

bool State::operator==(const State& state) const
{
	return getField().getField() == state.getField().getField();
}

bool State::operator<(const State& state) const
{
	if (*this != state)
	{
		if (getFunction() != state.getFunction())
			return getFunction() > state.getFunction();
		if (getG() != state.getG())
			return getG() < state.getG();
		return getField() < state.getField();
	}
	return false;
}

Field State::getField() const
{
	return m_field;
}

void State::setLength(const int& length)
{
	m_g = length;
}

std::pair<int, int> State::getCoordsOfEmptyCell() const
{
	return std::make_pair(m_row, m_col);
}