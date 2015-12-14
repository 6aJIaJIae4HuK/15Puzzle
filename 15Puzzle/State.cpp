#include <memory>

#include "State.h"

State::State(Field::FieldType field) : m_field(field), m_g(0), m_h(0)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			int n = m_field.getAtPos(i, j);
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
	m_parent.reset();
}

State::State(const State& state) : State::State(state.getField().getField())
{
	setG(state.getG());
	if (state.getParent().get() != NULL)
		setParent(*state.getParent().get());
}

State& State::operator=(const State& state)
{
	m_field = state.getField();
	m_h = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			int n = m_field.getAtPos(i, j);
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
	setG(state.getG());
	if (state.getParent().get() != NULL)
		setParent(*state.getParent().get());
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
	return getField().getFieldID() != state.getField().getFieldID();
}

bool State::operator==(const State& state) const
{
	return getField().getFieldID() == state.getField().getFieldID();
}

bool State::operator<(const State& state) const
{
	if (getFunction() != state.getFunction())
		return getFunction() > state.getFunction();
	if (getG() != state.getG())
		return getG() > state.getG();
	if (getField().getFieldID() != state.getField().getFieldID())
		return getField().getFieldID() < state.getField().getFieldID();
	if (getParent().get() == NULL || state.getParent().get() == NULL)
	{
		if (getParent().get() == NULL && state.getParent().get() == NULL)
			return false;
		if (getParent().get() == NULL)
			return true;
	}
	if (getParent()->getField().getFieldID() != state.getParent()->getField().getFieldID())
		return getParent()->getField().getFieldID() < state.getParent()->getField().getFieldID();
	return false;
}

Field State::getField() const
{
	return m_field;
}

void State::setG(const int& length)
{
	m_g = length;
}

std::pair<int, int> State::getCoordsOfEmptyCell() const
{
	return std::make_pair(m_row, m_col);
}

std::shared_ptr<State> State::getParent() const
{
	return m_parent;
}

void State::setParent(const State& parent)
{
	m_parent = std::make_shared<State>(parent);
}