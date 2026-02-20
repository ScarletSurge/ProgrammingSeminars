#include <iostream>

int x;

class compiler_defaults
{

public:

	compiler_defaults() = default;

	compiler_defaults(
		compiler_defaults const& param) = default;

};

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

int main()
{
	references_demo();
	int x = 15; // sizeof(int) == 4
	// Little endian, Big endian
	// 00001111 00000000 00000000 00000000

	x << 3;

	// 01111000 00000000 00000000 00000000
	// 2^3 + 2^4 + 2^5 + 2^6 = 2^3 * (1 + 2 + 4 + 8)

	// n << k <-> n * 2^k

	// operator<<
	operator<<(std::cout, "string\n\n");
	//std::cout
	//	<< "string"
	//	<< std::endl
	//	<< "string2";

	int z = 10, y = 5;
	z* y;
	int* p = &z;
	*p = 20;

	x = y = z;
	x + y + z;


	return 0;
}