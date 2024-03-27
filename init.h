#ifndef PROGRAMMING_LANGUAGES_AND_METHODS_INIT_H
#define PROGRAMMING_LANGUAGES_AND_METHODS_INIT_H

class T
{

private:

    int _value;

public:

    T(
        int value = 0):
            _value(value)
    {

    }

    void foo() const
    {
        T a(4);
        T b = a;
        T c(b);
        b = a;
    }

};

#endif //PROGRAMMING_LANGUAGES_AND_METHODS_INIT_H