#include <iostream>

// using namespace std;

int main(
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

	return 0;
}