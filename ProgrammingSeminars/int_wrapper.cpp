#include "int_wrapper.h"

void int_wrapper::destruct()
{
	delete _value;
	_value = nullptr;
}

void int_wrapper::copy(
	int_wrapper const& from)
{
	_value = new int(*from._value);
}

int_wrapper &int_wrapper::operator+=(
	int_wrapper const &summand) &
{
	*this->_value += *summand._value;
	return *this;
}

int_wrapper int_wrapper::operator+(
	int_wrapper const &summand) const
{
	//return int_wrapper(*this->_value + *summand._value);
	int_wrapper result(*this);
	return result += summand;
	
	// return result;
}