#include <iostream>

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

class int_wrapper
{

private:

	void destruct()
	{
		delete _value;
		_value = nullptr;
	}

	void copy(
		int_wrapper const& from)
	{
		_value = new int(*from._value);
	}

private:

	int *_value;

public:

	/*explicit*/ int_wrapper(
		int value = 0):
			_value(new int(value))
	{
		std::cout << *_value;
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

	int_wrapper &operator=(
		int_wrapper const &other)
	{
		// 1. self-assignment check
		if (this == &other)
		{
			return *this;
		}

		// 2. destruct old state
		destruct();

		// 3. copy new state
		copy(other);

		// 4. support Fluent API chain
		return *this;
	}

	// a = b = c = d';
	// a''' += e;
	// builder
};

void int_wrapper_demo()
{
	int_wrapper wr(52);
}

int main()
{
	char c = 10;
	// TODO: find case when this not works
	// int_wrapper x(10);
	// int_wrapper x1(c);
	// references_demo();
	//rule_of_3_demo();
	int_wrapper_demo();
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


	return 0;
}