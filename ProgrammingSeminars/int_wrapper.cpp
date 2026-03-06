#include "int_wrapper.h"
#include <stdexcept>

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
	throw int_wrapper(10);
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

// maybe, variant
// Maybe<T> -> Empty | T

// either, any
// Either<T1, T2> -> T1 | T2
int_wrapper &int_wrapper::operator/=(
	int_wrapper const &summand) &
{
	if (*summand._value == 0)
	{
		throw std::logic_error("dividing by zero!!1!1");
	}

	*_value /= *summand._value;

	return *this;
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

std::ostream &operator<<(
	std::ostream &stream,
	int_wrapper const &obj)
{
	return stream << *obj._value;
}

std::istream& operator>>(
	std::istream& stream,
	int_wrapper& obj)
{
	return stream >> *obj._value;
}

bool int_wrapper::operator==(
	int_wrapper const& other) const
{
	return *_value == *other._value;
	// return !(*this != other);
}

bool int_wrapper::operator!=(
	int_wrapper const& other) const
{
	return !(*this == other);
	// return *_value != *other._value;
}

bool int_wrapper::operator<(
	int_wrapper const& other) const
{
	return *(this->_value) < *other._value;
}

bool int_wrapper::operator<=(
	int_wrapper const& other) const
{
	// return *(this->_value) <= *other._value;
	return *this < other || *this == other;
}

bool int_wrapper::operator>(
	int_wrapper const& other) const
{
	return !(*this <= other);
}

bool int_wrapper::operator>=(
	int_wrapper const& other) const
{
	return !(*this < other);
}