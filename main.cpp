#include "include/bugint.h"

int main(
    int argc,
    char *argv[])
{
    int value[10] = { INT_MIN, INT_MAX, 3, 4, 5, 6, INT_MIN };
    bugint test(value, 1);

    std::cout << test << std::endl;
    //std::cout << ++test << std::endl;
    std::cout << --test << std::endl;

    return 0;
}