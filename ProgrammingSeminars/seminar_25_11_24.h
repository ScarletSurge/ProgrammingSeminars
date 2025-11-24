#ifndef SEMINAR_25_11_24
#define SEMINAR_25_11_24

#include <stdio.h>
#include <limits.h>

typedef union float_converter
{
	int i;
	float f;
} float_converter;

int seminar_25_11_24(
	int argc,
	char* argv[])
{
	// +: Z, Z -> Z
	// a + b -> -1.4
	// trie
	// 3 - 7 -> 3 + (0-7)
	// (1 - 10) * (4 - (1 - 3)) * 7 + ((5/(1-1)))

	// 2 + 2 * 2

	float_converter obj;
	printf("&obj.i = %p\n&obj.f = %p\n\n", &obj.i, &obj.f);
	//obj.f = -123.45;
	obj.i = INT_MAX - 50000000;
	printf("%.5f(10) = %08X(F)", obj.f, obj.i);

	return 0;
}

#endif