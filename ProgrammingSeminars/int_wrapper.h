#ifndef INT_WRAPPER_H
#define INT_WRAPPER_H

#include <iostream>

class int_wrapper
{

private:

	void destruct();

	void copy(
		int_wrapper const& from);

private:

	int* _value;

public:

	explicit int_wrapper(
		int value = 0) :
		_value(new int(value))
	{
		//std::cout << *_value;
	}

public:

	~int_wrapper() noexcept
	{
		destruct();
	}

	int_wrapper(
		int_wrapper const& other)
	{
		copy(other);
	}

	int_wrapper& operator=(
		int_wrapper const& other)
	{
		// in some cases, we can implement assignment operator in easier way
		// *this->_value = *other._value;
		// return *this;

		// but in common implementation steps are:
		// 1. self-assignment check
		if (this == &other)
		{
			return *this;
		}

		// 2. destruct old state
		destruct();

		// 3. copy new state
		copy(other);

		//int y = 10;
		//int z = 10;
		//auto func = [&](int x) { return x * y * z; };
		//std::cout << func(10) << std::endl;

		// 4. support Fluent API chain
		return *this;
	}

	// TODO: read about disposable/closable

	// a = b = c = d';
	// a''' += e;
	// builder

	// c = (int_wrapper(a) += b);
	int_wrapper& operator+=(
		int value) &;

	int_wrapper operator+(
		int value) const;

	// Matrix Matrix::operator*(double value) const;
	// friend Matrix operator*(double value, Matrix const &matr)
	// {
	//     return matr * value;
	// }
	// Matrix matr; auto matr_modified = 7 * matr;

	// static: int_wrapper::operator+()
	friend int_wrapper operator+(
		int value,
		int_wrapper const &obj);

	int_wrapper& operator+=(
		int_wrapper const& summand)&;

	int_wrapper operator+(
		int_wrapper const& summand) const;

	int_wrapper &operator-=(
		int_wrapper const &summand) &;

	int_wrapper operator-(
		int_wrapper const &summand) const;

	int_wrapper &operator*=(
		int_wrapper const &summand) &;

	int_wrapper operator*(
		int_wrapper const &summand) const;

	int_wrapper &operator/=(
		int_wrapper const &summand) &;

	int_wrapper operator/(
		int_wrapper const &summand) const;

	int_wrapper &operator%=(
		int_wrapper const &summand) &;

	int_wrapper operator%(
		int_wrapper const &summand) const;

	int_wrapper operator-() const;

	int_wrapper operator+() const;

	// int_wrapper obj(10);
	// auto obj2 = ++obj;
	// prefix
	int_wrapper &operator++();

	// postfix (infix)
	int_wrapper operator++(int);

	friend std::ostream& operator<<(
		std::ostream& stream,
		int_wrapper const& obj);

	friend std::istream &operator>>(
		std::istream &stream,
		int_wrapper &obj);

	bool operator==(
		int_wrapper const& other) const;

	bool operator!=(
		int_wrapper const& other) const;

	bool operator<(
		int_wrapper const& other) const;

	bool operator<=(
		int_wrapper const& other) const;

	bool operator>(
		int_wrapper const& other) const;

	bool operator>=(
		int_wrapper const& other) const;

	// std::cin >> x >> y >> z;
	// int_wrapper x;
	// x << std::cout;
	// std::cout << x;

	// += -= *= /= %=
	// + - * / %
	// ++x, x++, --x, x--
	// -x, +x
	
	// <<, >> (IO)
	// <<, <<=, >>, >>=, &, &=, |, |=, ^, ^=, ~
	// &&, &&=, ||, ||=, !
	// ==, !=
	// <, <=, >, >=
	// <=>

	// [], ()

};

#endif // INT_WRAPPER_H