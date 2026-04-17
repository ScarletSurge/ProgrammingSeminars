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

void dynamic_cast_demo()
{
	class puk1 { public: virtual ~puk1() noexcept = default; };
	class puk2 : public puk1 {};
	class puk3 {};

	puk1 *obj = new puk2;
	if (dynamic_cast<puk3*>(obj) == nullptr)
	{
		std::cout << "Invalid cast";
	}
	else
	{
		std::cout << "OK cast";
	}
}

#include "binomial_priority_queue.h"

int priorities_comparer(
	int first,
	int second)
{
	return first - second;
}

void bpq_demo()
{
	srand((unsigned)time(NULL));

	binomial_priority_queue instance(priorities_comparer);

	binomial_priority_queue meld_from_all(priorities_comparer);

	char *removed_value;
	for (int i = 0; i < 250; i++)
	{
		switch (rand() % 1)
		{
		case 0:
			instance.insert(rand() % 9000 + 1000, "pukpuk");
			break;
		case 1:
			try
			{
				delete (removed_value = instance.remove_max());
			}
			catch (binomial_priority_queue::empty_priority_queue_exception const &ex)
			{
				std::cout << ex.what() << std::endl;
			}
			break;
		}

		binomial_priority_queue *melded = dynamic_cast<binomial_priority_queue*>(meld_from_all.meld(&instance));
		meld_from_all = *melded;
		delete melded;

		std::cout << "instance: ";
		instance.debug_print();
		std::cout << "melded: ";
		meld_from_all.debug_print();
	}
}

int c_strings_demo()
{
	char const* buf = "123abc\0p2345678";

	printf("%s\n", buf + 7);

	return 0;
}

#include "trie.h"

int trie_demo()
{
	char const *alphabet = "abcdefghijklmnopqrstuvwxyz0123456789_ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	size_t const alphabet_length = strlen(alphabet);
	char buf[BUFSIZ];
	trie instance(alphabet);

	srand((unsigned)time(nullptr));

	for (int i = 0; i < 50000; ++i)
	{
		size_t str_len = rand() % 21 + 10;

		for (int j = 0; j < str_len; ++j)
		{
			buf[j] = alphabet[rand() % alphabet_length];
		}

		buf[str_len] = '\0';

		try
		{
			instance.insert(buf, i);
			std::cout << "Successfully inserted key == \"" << buf << "\" with value == " << i << std::endl;
		}
		catch (std::logic_error const &ex)
		{
			std::cout << ex.what() << std::endl;
		}
	}

	return 0;
}

#include "arithmetic_expressions_context.h"

int expression_tree_demo()
{
	trie variables("abcdefghijklmnopqrstuvwxyz0123456789_");
	variables.insert("x1", 75);
	variables.insert("x2", -9);
	std::cout << arithmetic_expressions_context::get_instance().calculate_expression("x2 - ((9 - 7) * (11 - 81) + 4) / (3 - x1) * 8", variables);

	// "x2 - 8"

	return 0;
}

class static_demo_ final
{

private:

	static int x;

public:

	void print() const { std::cout << x++ << std::endl; }

};

int static_demo_::x = 10;

int static_demo()
{
	//static_demo_::x = 10;
	static_demo_ obj1, obj2, obj3;
	obj1.print();
	obj2.print();
	obj3.print();


	return 0;
}

int main()
{
	//return static_demo();
	return expression_tree_demo();
	// destructors_chain_demo();
	// return 0;

	// std::cout << "punjk srenjk((9(9";
	// char c = 10;
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

	// exceptions_demo();

	//return c_strings_demo();

	return trie_demo();

	std::cout << ((sqrt(2.0) * sqrt(2.0) == 2.0)
		? "Equal"
		: "Not equal")
		<< std::endl;
	std::cout << (-1 << 3) << std::endl;

	// dynamic_cast_demo();
	bpq_demo();

	return 0;
}