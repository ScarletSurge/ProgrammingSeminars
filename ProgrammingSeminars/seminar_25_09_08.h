#ifndef SEMINAR_25_09_08
#define SEMINAR_25_09_08

#include <stdio.h>

int seminar_25_09_08(
	int argc,
	char* argv[])
{
    // variables & types
    int summand1, summand2; // integral
    int X = 138;
    // int, char, short, long, long long
    // unsigned --//--
    // void
    // float, double

    printf("Hello World");

    float f = -123.45;
    printf("%08X", *((unsigned int*)&f));
    // ' ', '\n', '\t', '\v', '\r', '\f', '\\'
    printf("%u %i %c %s %f %lf %o %x %X", X, X, X, "this is string o_O", 123.45, 197776.52, 64, X, X);
    printf("puk %d srenjk", X);

    return 0;
}

#endif