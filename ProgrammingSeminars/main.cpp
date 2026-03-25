#include <iostream>

#include "int_wrapper.h"

int x;

class compiler_defaults
{

	int _x;

public:

	compiler_defaults() = default;

	~compiler_defaults() noexcept = default;

	// 1. при инициализации объекта другим объектом такого же типа
	// 2. при передаче объекта в функцию по значению
	// 3. при возврате объекта из функции по значению
	compiler_defaults(
		// compiler_defaults *this,
		compiler_defaults const &param)
	{
		//this
			// T obj2;
			// T obj = obj2; -> obj.T(obj2); -> T::T(&obj, obj2);
	}

	// a = b;
	compiler_defaults &operator=(
		compiler_defaults const &param);
	// int a, b, c;
	// a = b = c;
	// a + b + c;
	void foo()
	{
		_x++; // this->_x++;
	}

	// T obj1; // obj1._x = 10;
	// T obj2; // obj2._x = 20;

	// obj1.foo(); // foo(&obj1)
	// obj2.foo(); // foo(&obj2)

	//operator=

};

// class by_default
// {
// 
// public:
// 
// };
// 
// void foo()
// {
// 	by_default obj1;
// 	by_default obj2(obj1); // copy constructor call
// 	auto result = bar(obj1); // copy constructor // call x3
// 	result = bar(obj1);
// 
// 	int x = 10; // initialization
// 	x = 20; // assignment
// }
// 
// by_default bar(
// 	by_default param)
// {
// 	// TODO: business logic here...
// 
// 	return by_default(param); // RVO/NRVO
// }

class point_2D
{

private:

	// new/delete, new[]/delete[], ::operator new, ::operator delete
	double* _x;
	double* _y;

public:

	~point_2D()
	{
		delete _x;
		delete _y;
	}

	point_2D(
		double x,
		double y)
	{
		// read about: exceptions, раскрутка stack, try/catch/throw
		_x = new double(x);
		_y = new double(y);
	}

	double& get_x() const
	{
		return *_x;
	}

	double get_y() const
	{
		return *_y;
	}

};

class vector_2D
{

private:

	point_2D _start;
	point_2D _end;

	// int x = 10;
	// x = 20;

public:

	vector_2D(
		point_2D end):
			_start(0.0, 0.0),
			_end(end)
	{
		_start = point_2D(10.0, 5.0);
		_start.get_x() = 8.0;
		int x = 10;
	}

	vector_2D(
		point_2D start,
		point_2D end):
			_start(start),
			_end(end)
	{

	}

};

// man7.org

// vtable

void class_example_demo()
{
	{
		auto p = point_2D(52.0, 1337.0);
		point_2D p2 = p; // copy constructor
	}

	vector_2D vector(point_2D(1.5, 4.5));

	//(*(int*)&obj) = 10; // reverse engineering
	//std::cout << obj.get_data();
	//obj2.data = 10;

	// operator<<(std::cout, .func<>_class_example::get_data(&obj2)); // class_example *
}

void references_demo()
{
	auto x = 10;

	int& r = x;
	int* p = &x;

	*p = 20; // typeof(*p) == int&
	r = 30;
}

class rule_of_3
{

public:

	rule_of_3()
	{
		std::cout << "rule_of_3::rule_of_3() working..." << std::endl;
	}

public:

	~rule_of_3() noexcept
	{
		std::cout << "rule_of_3::~rule_of_3() working..." << std::endl;
	}

	rule_of_3(
		rule_of_3 const& obj)
	{
		std::cout << "rule_of_3::rule_of_3(rule_of_3 const &) working..." << std::endl;
	}

	rule_of_3 &operator=(
		rule_of_3 const& obj)
	{
		std::cout << "rule_of_3 &rule_of_3::operator=(rule_of_3 const &) working..." << std::endl;

		return *this;
	}

};

void rule_of_3_demo()
{
	rule_of_3 obj1;

	rule_of_3 obj2(obj1);
	rule_of_3 obj3 = obj1;
	rule_of_3 obj4 { obj1 };

	obj1 = rule_of_3(obj2);

	std::cout << "rule_of_3_demo work ends..." << std::endl;
}

class number
{

private:

	int value;

public:

	number(int value = 0):
		value(value)
	{

	}

public:

	number& operator+=(
		number const& other) &
	{
		value += other.value;

		return *this;
	}

	number operator+(
		number const& other) const
	{
		number result = *this;
		return result += other;
	}

};

void int_wrapper_demo()
{
	int_wrapper wr1(52);
	int_wrapper wr2(80);

	(std::cout << 10) << "string" << wr1;

	wr1 = wr2;
	// TODO: read about prototype construction pattern
	// auto obj = wr1.clone();
	int_wrapper wr3 = wr1 + wr2;
	wr1 += wr2;
	wr1 += 10;
	wr1 + 10;
	10 + wr1;
	// a + b; b + a;
	//auto x = wr1 + 10;
	//x =  + 10
}

void exceptions_demo()
{
	int_wrapper x(10);
	int_wrapper y(1);

	int* values = new int[10];

	try
	{
		std::cout << (x /= y);
	}
	catch (std::logic_error const& ex)
	{
		delete[] values;
		std::cout << "Something went wrong: \"" << ex.what() << "\"";
	}

	std::cout << std::endl << "We got here!";

	delete[] values;
}

class base
{
public:
	base()
	{
		std::cout << "base::base() called" << std::endl;
	}

	virtual ~base() noexcept
	{
		std::cout << "base::~base() called" << std::endl;
	}
};

class derived:
	public base
{
private:
	int* _ptr;
public:
	derived() :
		_ptr(new int[10])
	{
		std::cout << "derived::derived() called" << std::endl;
	}
public:
	~derived()
	{
		std::cout << "derived::~derived() called" << std::endl;
		delete[] _ptr;
	}
};

void destructors_chain_demo()
{
	base *obj = new derived;

	// TODO: 

	delete obj;
}

int main()
{
	// destructors_chain_demo();
	return 0;

	std::cout << "punjk srenjk((9(9";
	char c = 10;
	// TODO: find case when this not works
	// int_wrapper x(10);
	// int_wrapper x1(c);
	// references_demo();
	//rule_of_3_demo();
	//int_wrapper_demo();
	// int x = 15; // sizeof(int) == 4
	// // Little endian, Big endian
	// // 00001111 00000000 00000000 00000000
	// 
	// x << 3;
	// 
	// // 01111000 00000000 00000000 00000000
	// // 2^3 + 2^4 + 2^5 + 2^6 = 2^3 * (1 + 2 + 4 +  8)
	// 
	// // n << k <-> n * 2^k
	// 
	// // operator<<
	// operator<<(std::cout, "string\n\n");
	// //std::cout
	// //	<< "string"
	// //	<< std::endl
	// //	<< "string2";
	// 
	// int z = 10, y = 5;
	// z* y;
	// int* p = &z;
	// *p = 20;
	// 
	// x = y = z;
	// x + y + z;

	exceptions_demo();

	return 0;
}