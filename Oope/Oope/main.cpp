#include <iostream>
#include <limits.h>

// using namespace std;

int code_from_20250920(
	int argc,
	char *argv[])
{
	int x = 5;
	int* p = &x;

	*p = 10;
	printf("%s", *(argv + 0));

	std::cout << "Hello, world!"
		<< 52
		<< x; // TODO: read about trie

	std::cin >> x;
	int& ref = x;

	int puk = 1, srenjk = 2;

	puk += srenjk; // int& int::operator+=(int) &;

	int* puksrenjk = (int*)12345678;
	*puksrenjk = 52;

	// a + b + c;
	// a = b = c;

	// Герберт Шилдт "Самоучитель С++" (изд. 3)
	// Стивен Прата "Язык программирования C++"
	// Липпман "C++ Базовый курс" (must have)
	// Майерc "Современный и эффективный C++"
	// Кнут "Искусство программирования" 1.2.5

	return 0;
}

class Array
{
public:
	Array();
	Array(size_t const n, unsigned char const t = 0);
	Array(std::initializer_list<unsigned char const> const &t);
	Array(std::string const& t);
};

class puk_srenjk
{

protected:
	
	int _value;

public:

	puk_srenjk(
		int value = 52)
	{
		std::cout << "Called puk_srenjk::puk_srenjk(int)" << std::endl;
		_value = value;
	}

public:

	int get_value()
	{
		return _value;
	}

public:

	virtual ~puk_srenjk() = default;

};

class puk:
	public puk_srenjk
{

private:

	int* kill_me_plz;

public:

	puk():
		kill_me_plz(new int[52])
	{
		std::cout << "Called puk::puk()" << std::endl;
	}

public:

	~puk()
	{
		delete[] kill_me_plz;
		std::cout << "Called puk::~puk()" << std::endl;
	}

};

void print_array(
	// int& const val2, - препад не смог в погромирование((9(9
	int const *arr,
	size_t arr_size)
{
	for (auto i = 0; i < arr_size; ++i)
	{
		std::cout << i[arr] << ' ';
	}
	std::cout << std::endl;
}

int code_from_20251004(
	int argc,
	char* argv[])
{
	int x = 10;
	x = 10;

	int arr[10] = { 0 };
	arr[3] = 4;
	3[arr] = 4;
	*(arr + 3) = 4;

	print_array(arr, 10);

	
	// void *malloc(size_t)
	// void *calloc(size_t, size_t)
	// void *realloc(void *, size_t)
	// void free(void *)

	int* p = reinterpret_cast<int *>(malloc(52));
	if (!p)
	{
		// TODO: throw an exception instance
	}
	int* p1 = (int *)realloc((void*)p, 52 * sizeof(int));

	// allocation
	//new, new[], ::operator new
	// constructor invokation
	//new (ptr) T(<constructor parameters>);

	// deallocation
	//delete, delete[], ::operator delete
// #define MUL(x, y) ((x)+(y))

	// std::cout << 3 * MUL(1 + 2, 3 + 4);
//#define NULL ((void *)(0))
//#define NULL (0)

	// TODO: std::move, std::forward, std::exchange, rvalue ref
	return 0;
}

int main(
	int argc,
	char *argv[])
{
	//return code_from_20250920(argc, argv);
	//return code_from_20251004(argc, argv);

	puk_srenjk *obj = new puk;
	std::cout << "Work with obj..." << std::endl;
	delete obj;
	return 52;
}