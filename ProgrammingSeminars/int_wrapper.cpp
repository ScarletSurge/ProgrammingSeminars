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

int_wrapper& int_wrapper::operator+=(
	int value) &
{
	*_value += value;
	// *this += int_wrapper(value);

	return *this;
}

int_wrapper int_wrapper::operator+(
	int value) const
{
	auto result = *this;
	return result += value;
}

int_wrapper operator+(
	int value,
	int_wrapper const& obj)
{
	//return value + obj;
	return obj + value;

	// auto result(obj);
	// result += value;
	// return result;
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

int_wrapper & int_wrapper::operator-=(
	int_wrapper const &summand) &
{
	throw 52;
}

int_wrapper int_wrapper::operator-(
	int_wrapper const &summand) const
{
	throw 52;
}

int_wrapper &int_wrapper::operator*=(
	int_wrapper const &summand) &
{
	throw 52;
}

int_wrapper int_wrapper::operator*(
	int_wrapper const &summand) const
{
	throw 52;
}

int_wrapper &int_wrapper::operator/=(
	int_wrapper const &summand) &
{
	throw 52;
}

int_wrapper int_wrapper::operator/(
	int_wrapper const &summand) const
{
	throw 52;
}

int_wrapper &int_wrapper::operator%=(
	int_wrapper const &summand) &
{
	throw 52;
}

int_wrapper int_wrapper::operator%(
	int_wrapper const &summand) const
{
	throw 52;
}

int_wrapper &int_wrapper::operator++()
{
	++*_value;

	return *this;
}

int_wrapper int_wrapper::operator++(int)
{
	auto result = *this;
	
	++*this;

	return result;
}